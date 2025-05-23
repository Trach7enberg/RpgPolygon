// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PolyCharacterBase.h"

#include "MotionWarpingComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SubSystem/PolyGiSubSystem.h"

DEFINE_LOG_CATEGORY_STATIC(PolyCharacterBaseLog, All, All);

APolyCharacterBase::APolyCharacterBase()
{
	MotionWarpingComp = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarpingComp");
	LockIndicatorComp = CreateDefaultSubobject<UWidgetComponent>("LockIndicatorComp");

	PrimaryActorTick.bCanEverTick          = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	LockIndicatorComp->SetWidgetSpace(EWidgetSpace::Screen);
	LockIndicatorComp->SetDrawAtDesiredSize(true);
	LockIndicatorComp->SetupAttachment(GetMesh());

	GetMesh()->SetReceivesDecals(false);
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	// 可以阻挡visibility通道,能被cursor hit
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
}

void APolyCharacterBase::BeginPlay() { Super::BeginPlay(); }

void APolyCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


void APolyCharacterBase::InitializeAscInfo() {}

UPolyGiSubSystem* APolyCharacterBase::GetGiSubSystem()
{
	if (!GetGameInstance()) { return nullptr; }

	if (!PolyGiSubSystem) { PolyGiSubSystem = GetGameInstance()->GetSubsystem<UPolyGiSubSystem>(); }
	return PolyGiSubSystem.Get();
}


UPolyAbilitySysComp* APolyCharacterBase::GetPolyAbilitySysComp() const { return PolyAsc; }

UAbilitySystemComponent* APolyCharacterBase::GetAbilitySystemComponent() const { return GetPolyAbilitySysComp(); }

void APolyCharacterBase::PossessedBy(AController* NewController) { Super::PossessedBy(NewController); }
