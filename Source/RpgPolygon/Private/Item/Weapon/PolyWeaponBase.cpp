// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Weapon/PolyWeaponBase.h"

#include "Character/PolyCharacterBase.h"
#include "Components/BoxComponent.h"
#include "FunctionLibrary/PolyFunctionLibrary.h"
#include "Net/UnrealNetwork.h"

APolyWeaponBase::APolyWeaponBase()
{
	bReplicates                   = true;
	PrimaryActorTick.bCanEverTick = false;
	SetReplicateMovement(true);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>("WeaponCollisionBox");
	WeaponMesh         = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");

	SetRootComponent(WeaponMesh);
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);

	WeaponCollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnWeaponBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnEndWeaponOverlap);
}

void APolyWeaponBase::EnableCollision(bool Enabled) const
{
	WeaponCollisionBox->SetCollisionEnabled(Enabled
		                                        ? ECollisionEnabled::Type::QueryOnly
		                                        : ECollisionEnabled::Type::NoCollision);
}

void APolyWeaponBase::DestroyWeapon() {}

void APolyWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APolyWeaponBase, WeaponMesh);
}

float APolyWeaponBase::GetWeaponDataBaseDamage(float InAbilityLevel) const
{
	return WeaponData.WeaponBaseDamage.GetValueAtLevel(InAbilityLevel);
}

TObjectPtr<UPolyAbilitySysComp> APolyWeaponBase::GetOwnerAsc()
{
	if (!OwnerAsc)
	{
		if (!GetOwner()) { return nullptr; }
		const auto Character = Cast<APolyCharacterBase>(GetOwner());
		if (!Character) { return nullptr; }

		OwnerAsc = Character->GetPolyAbilitySysComp();
	}

	return OwnerAsc;
}

void APolyWeaponBase::InitialDissolveTimeline() {}

void APolyWeaponBase::StartDissolveTimeline() {}

void APolyWeaponBase::OnDissolveTimelineUpdate(float Value) {}

void APolyWeaponBase::OnDissolveTimelineFinished() {}

void APolyWeaponBase::OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                           AActor*              OtherActor,
                                           UPrimitiveComponent* OtherComp,
                                           int32                OtherBodyIndex,
                                           bool                 bFromSweep,
                                           const FHitResult&    SweepResult)
{
	if (UPolyFunctionLibrary::AreActorsFriendly(GetOwner(), OtherActor)) { return; }
	if (OtherActor != GetOwner())
	{
		bIsOverlap = true;
		OnWeaponBeginOverlapDelegate.ExecuteIfBound(OtherActor, &SweepResult);
	}
}

void APolyWeaponBase::OnEndWeaponOverlap(UPrimitiveComponent* OverlappedComponent,
                                         AActor*              OtherActor,
                                         UPrimitiveComponent* OtherComp,
                                         int32                OtherBodyIndex)
{
	if (!bIsOverlap || !OtherActor) { return; }
	OnWeaponEndOverlapDelegate.ExecuteIfBound(OtherActor, nullptr);
	bIsOverlap = false;
}

void APolyWeaponBase::OnRep_WeaponMesh(USkeletalMeshComponent* OldValue) {}

FVector APolyWeaponBase::GetWeaponSocketLocByTag(const FGameplayTag& InSocketTypeTag)
{
	return WeaponMesh->GetSocketLocation(WeaponData.FindSocketNameByTag(InSocketTypeTag));
}

void APolyWeaponBase::BeginPlay() { Super::BeginPlay(); }
