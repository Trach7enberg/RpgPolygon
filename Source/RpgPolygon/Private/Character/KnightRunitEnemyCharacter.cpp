// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/KnightRunitEnemyCharacter.h"

#include "AbilitySys/Core/PolyAttributeSet.h"
#include "Component/Combat/EnemyCombatComp.h"
#include "Component/UI/EnemyUiComp.h"
#include "Component/Weapon/EnemyWeaponComp.h"
#include "Components/WidgetComponent.h"
#include "DataAssets/CharacterStartUp/DataAssetEnemyStartUp.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widgets/Enemy/EnemyWidget.h"

AKnightRunitEnemyCharacter::AKnightRunitEnemyCharacter()
{
	EnemyWeaponComp     = CreateDefaultSubobject<UEnemyWeaponComp>("EnemyWeaponComp");
	EnemyCombatComp     = CreateDefaultSubobject<UEnemyCombatComp>("EnemyCombatComp");
	EnemyUiComp         = CreateDefaultSubobject<UEnemyUiComp>("EnemyUIComponent");
	NameplateWidgetComp = CreateDefaultSubobject<UWidgetComponent>("NameplateWidget");
	PolyAsc             = CreateDefaultSubobject<UPolyAbilitySysComp>("PolyAsc");
	PolyAs              = CreateDefaultSubobject<UPolyAttributeSet>("PolyAs");

	Attach_Wing1 = CreateDefaultSubobject<USkeletalMeshComponent>("Attach_Wing1");
	Attach_Wing2 = CreateDefaultSubobject<USkeletalMeshComponent>("Attach_Wing2");
	Attach_Beard = CreateDefaultSubobject<USkeletalMeshComponent>("Attach_Beard");
	Attach_Head  = CreateDefaultSubobject<USkeletalMeshComponent>("Attach_Head");


	PolyAsc->SetIsReplicated(true);
	PolyAsc->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	EnemyWeaponComp->SetIsReplicated(true);
	EnemyCombatComp->SetIsReplicated(true);
	EnemyUiComp->SetIsReplicated(true);
	NameplateWidgetComp->SetIsReplicated(true);

	SetReplicates(true);
	AutoPossessAI               = EAutoPossessAI::PlacedInWorld;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll  = false;
	bUseControllerRotationYaw   = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement     = true;
	GetCharacterMovement()->RotationRate                  = FRotator(0.f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed                  = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking    = 1000.f;

	NameplateWidgetComp->SetRelativeLocation(FVector(0.f,
	                                                 0.f,
	                                                 176));
	NameplateWidgetComp->SetupAttachment(GetMesh());
	NameplateWidgetComp->SetRelativeLocation(FVector(0.f, 12.f, 190.f));
	NameplateWidgetComp->SetDrawAtDesiredSize(true);
	NameplateWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	LockIndicatorComp->SetRelativeLocation(FVector(0.f, 12.f, 130.f));

	GetMesh()->SetRelativeLocation(FVector(0, 0, -85));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	InitSubMesh();
}

void AKnightRunitEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitEnemyUI();
}

void AKnightRunitEnemyCharacter::InitAbilityInfo()
{
	if (!DataAssetStarUpAbilities) { return; };


	PolyAsc->InitAbilityActorInfo(this, this);

	if (HasAuthority())
	{
		if (const auto DataAsset = Cast<UDataAssetEnemyStartUp>(DataAssetStarUpAbilities))
		{
			PolyAsc->GiveInitialAbilities(DataAsset->EnemyCombatAbilities);
			PolyAsc->GiveInitialAbilities(DataAsset->StartUpAbilities);
			PolyAsc->GiveInitialAbilities(DataAsset->ReactAbilities);
			PolyAsc->ApplyInitialGameplayEffectToSelf({DataAsset->PrimaryAttributes});
			PolyAsc->ApplyInitialGameplayEffectToSelf({DataAsset->SecondaryAttributes});
			PolyAsc->ApplyInitialGameplayEffectToSelf({DataAsset->SecondaryResistanceAttributes});
		}
	}


	FAttachmentTransformRules Rules{EAttachmentRule::SnapToTarget, false};
	Rules.LocationRule = EAttachmentRule::SnapToTarget;
	Rules.RotationRule = EAttachmentRule::KeepRelative;
	Rules.ScaleRule    = EAttachmentRule::KeepWorld;
	InitSubMesh(Rules);

	InitEnemyUI();
	EnemyCombatComp->InitDependencies(EnemyWeaponComp.Get(), MotionWarpingComp.Get());
}

void AKnightRunitEnemyCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitAbilityInfo();
}

void AKnightRunitEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityInfo();
}

TScriptInterface<ICombatInterface> AKnightRunitEnemyCharacter::GetCombatInterface() { return EnemyCombatComp; }

UAbilitySystemComponent* AKnightRunitEnemyCharacter::GetAbilitySystemComponent() const
{
	return Super::GetAbilitySystemComponent();
}

UPolyAbilitySysComp* AKnightRunitEnemyCharacter::GetPolyAbilitySysComp() const { return PolyAsc; }


void AKnightRunitEnemyCharacter::InitializeAscInfo() { Super::InitializeAscInfo(); }
void AKnightRunitEnemyCharacter::InitEnemyUI()
{
	auto NameplateWidget = Cast<UEnemyWidget>(NameplateWidgetComp->GetUserWidgetObject());
	if (!NameplateWidget) { return; }
	NameplateWidget->InitializePolyWidget(EnemyUiComp);
	EnemyUiComp->InitializePawnComponent();
	EnemyUiComp->BroadcastHealthManaInitValue();
}

void AKnightRunitEnemyCharacter::InitSubMesh(FAttachmentTransformRules Rules)
{
	Attach_Head->AttachToComponent(GetMesh(), Rules, "headSocket");
	Attach_Beard->AttachToComponent(GetMesh(), Rules, "BeardSocket");
	Attach_Wing1->AttachToComponent(GetMesh(), Rules, "WingLeftSocket");
	Attach_Wing2->AttachToComponent(GetMesh(), Rules, "WingRightSocket");
}
