// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Projectile/PolyProjectileBase.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interface/CombatInterface.h"
#include "Interface/Provider/CombatProvider.h"
#include "Kismet/GameplayStatics.h"
#include "RpgPolygon/RpgPolygon.h"

// Sets default values
APolyProjectileBase::APolyProjectileBase()
{
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	SphereComponent             = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	NiagaraComponent            = CreateDefaultSubobject<UNiagaraComponent>("NiagaraComponent");

	PrimaryActorTick.bCanEverTick = false;
	bReplicates                   = true;
	SetLifeSpan(ProjectileLifeSpawn);
	SetReplicateMovement(true);

	bIgnoreFriend = true;

	SetRootComponent(SphereComponent);
	NiagaraComponent->SetupAttachment(GetRootComponent());


	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::Type::QueryOnly);

	ProjectileMovementComponent->InitialSpeed           = 550.f;
	ProjectileMovementComponent->MaxSpeed               = 550.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnSphereEneOverlap);
}


void APolyProjectileBase::BeginPlay()
{
	Super::BeginPlay();


	if (LoopingSound)
	{
		LoopSoundAudioComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
	}
}

void APolyProjectileBase::SpawnVfxAndSound() const
{
	if (!ImpactSound || !ImpactEffect) { return; }
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
}

void APolyProjectileBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                               AActor*              OtherActor,
                                               UPrimitiveComponent* OtherComp,
                                               int32                OtherBodyIndex,
                                               bool                 bFromSweep,
                                               const FHitResult&    SweepResult) {}

void APolyProjectileBase::OnSphereEneOverlap(UPrimitiveComponent* OverlappedComponent,
                                             AActor*              OtherActor,
                                             UPrimitiveComponent* OtherComp,
                                             int32                OtherBodyIndex) {}

void APolyProjectileBase::HomingActorOnMissing(AActor* Actor)
{
	if (!GetProjectileMovementComponent()) { return; }
	GetProjectileMovementComponent()->bIsHomingProjectile = false;
}

void APolyProjectileBase::RegisterHomingActorOnMissingEvent()
{
	if (!GetProjectileMovementComponent() || !GetProjectileMovementComponent()->HomingTargetComponent.Get()) { return; }

	const auto HomingCompOwner = GetProjectileMovementComponent()->HomingTargetComponent.Get()->GetOwner();
	const auto InCombatProvider = Cast<ICombatProvider>(HomingCompOwner);
	
	if (!InCombatProvider) { return; }
	const auto CombatInt       = InCombatProvider->GetCombatInterface();
	if (CombatInt->GetCharacterPreOnDeathDelegate().IsBoundToObject(this)) { return; }

	CombatInt->GetCharacterPreOnDeathDelegate().AddUObject(this, &APolyProjectileBase::HomingActorOnMissing);
}

