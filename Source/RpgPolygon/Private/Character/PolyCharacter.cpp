// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PolyCharacter.h"

#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "AbilitySys/Core/PolyAttributeSet.h"
#include "Camera/CameraComponent.h"
#include "Component/Combat/PolyCombatComp.h"
#include "Component/Equipment/PolyEquipmentComp.h"
#include "Component/Input/PolyEnhancedInputComponent.h"
#include "Component/Interactive/PolyInteractComp.h"
#include "Component/UI/PolyUiComp.h"
#include "Component/Weapon/PolyWeaponComp.h"
#include "Controller/Player/PolyController.h"
#include "CoreTypes/PolyCoreStruct.h"
#include "CoreTypes/PolyGameplayTags.h"
#include "DataAssets/CharacterStartUp/DataAssetPolyStartUp.h"
#include "FunctionLibrary/PolyFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Hud/BasePolyHud.h"
#include "PlayerStates/PlayerStateBase.h"

DEFINE_LOG_CATEGORY_STATIC(PolyCharacterLog, All, All);


APolyCharacter::APolyCharacter()
{
	CameraFollow        = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraBoom          = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	PlayerCombatComp    = CreateDefaultSubobject<UPolyCombatComp>("PlayerCombatComp");
	PlayerWeaponComp    = CreateDefaultSubobject<UPolyWeaponComp>("PlayerWeaponComp");
	PlayerEquipmentComp = CreateDefaultSubobject<UPolyEquipmentComp>("PlayerEquipmentComp");
	PlayerInteractComp  = CreateDefaultSubobject<UPolyInteractComp>("PlayerInteractComp");
	PlayerUIComp        = CreateDefaultSubobject<UPolyUiComp>("PlayerUIComp");
	Attach_Wing1        = CreateDefaultSubobject<USkeletalMeshComponent>("Attach_Wing1");
	Attach_Wing2        = CreateDefaultSubobject<USkeletalMeshComponent>("Attach_Wing2");
	Attach_Beard        = CreateDefaultSubobject<USkeletalMeshComponent>("Attach_Beard");
	Attach_Head         = CreateDefaultSubobject<USkeletalMeshComponent>("Attach_Head");

	CameraBoom->SetupAttachment(GetRootComponent());
	CameraFollow->SetupAttachment(CameraBoom);

	CameraBoom->SetRelativeLocation(FVector(0, 0, 85));
	CameraBoom->SetRelativeRotation(FRotator(-45, 0, 0));
	CameraBoom->TargetArmLength  = 750.f;
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->bInheritPitch    = false;
	CameraBoom->bInheritRoll     = false;
	CameraBoom->bInheritYaw      = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate              = FRotator(0, 400, 0);

	// 限制角色的移动能力在平面上 
	GetCharacterMovement()->bConstrainToPlane   = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationRoll  = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;


	GetMesh()->SetRelativeLocation(FVector(0, 0, -85));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	// 默认在构造器Attach操作只支持KeepRelative
	InitSubMesh();

	CharacterRoleType = ERoleType::Elementalist;
}

void APolyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitializeAscInfo();
};

void APolyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	ensureMsgf(DataAssetInputConfig, TEXT("DataAssetInputConfig cant be null"));
	if (!DataAssetInputConfig) { return; }

	const auto InController = Cast<APolyController>(GetController());

	ensureMsgf(InController, TEXT("WarriorController Cant be null"));
	if (!InController) { return; }

	// 获得增强输入的本地玩家子系统,通过这个根据添加我们的上下文映射
	const auto SubSystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(InController->GetLocalPlayer());

	checkf(SubSystem, TEXT("EnhancedInputLocalPlayerSubsystem Cant be null"));

	SubSystem->AddMappingContext(DataAssetInputConfig->DefaultMappingContext,
	                             InController->GetMappingContextCurrentPriorityCnt(true));

	const auto WarriorInputComp = CastChecked<UPolyEnhancedInputComponent>(PlayerInputComponent);

	WarriorInputComp->BindNormalInputAction(DataAssetInputConfig,
	                                        PolyGameplayTags::RpgPoly_InputTag_Move,
	                                        ETriggerEvent::Triggered,
	                                        this,
	                                        &ThisClass::InputMove);
	WarriorInputComp->BindNormalInputAction(DataAssetInputConfig,
	                                        PolyGameplayTags::RpgPoly_InputTag_Move,
	                                        ETriggerEvent::Completed,
	                                        this,
	                                        &ThisClass::InputMoveCompleted);

	WarriorInputComp->BindNormalInputAction(DataAssetInputConfig,
	                                        PolyGameplayTags::RpgPoly_InputTag_Look,
	                                        ETriggerEvent::Triggered,
	                                        this,
	                                        &ThisClass::InputLook);
	WarriorInputComp->BindNormalInputAction(DataAssetInputConfig,
	                                        PolyGameplayTags::RpgPoly_InputTag_SwitchTarget_Left,
	                                        ETriggerEvent::Completed,
	                                        this,
	                                        &ThisClass::InputSwitchTargetLeftCompleted);
	WarriorInputComp->BindNormalInputAction(DataAssetInputConfig,
	                                        PolyGameplayTags::RpgPoly_InputTag_SwitchTarget_Right,
	                                        ETriggerEvent::Completed,
	                                        this,
	                                        &ThisClass::InputSwitchTargetRightCompleted);


	WarriorInputComp->BindAbilityInputActions(DataAssetInputConfig,
	                                          this,
	                                          &ThisClass::InputAbilityPressed,
	                                          &ThisClass::InputAbilityReleased);
}

TScriptInterface<ICombatInterface> APolyCharacter::GetCombatInterface() { return PlayerCombatComp; }


void APolyCharacter::BeginPlay() { Super::BeginPlay(); }

void APolyCharacter::InitializeAscInfo()
{

	if (!DataAssetStarUpAbilities || !GetPolyController()) { return; }


	const auto MyPlayerState = GetPlayerState<APlayerStateBase>();
	if (!MyPlayerState) { return; }

	PolyAsc = Cast<UPolyAbilitySysComp>(MyPlayerState->GetAbilitySystemComponent());
	PolyAs  = Cast<UPolyAttributeSet>(MyPlayerState->GetAttributeSet());

	if (!PolyAsc)
	{
		UE_LOG(PolyCharacterLog, Warning, TEXT("%hs:Cant Get Asc"), __FUNCTION__);
		return;
	}

	PolyAsc->InitAbilityActorInfo(MyPlayerState, this);

	const auto PolyHud = GetPolyController()->GetHUD<ABasePolyHud>();
	if (!PolyHud) { UE_LOG(PolyCharacterLog, Warning, TEXT("%hs:Cant Get Player Hud"), __FUNCTION__); }
	if (PolyHud) { PolyHud->InitHudMainWidget(); }

	PlayerUIComp->InitialUiComponent();
	PlayerWeaponComp->InitializePawnComponent();
	PlayerCombatComp->InitDependencies(PlayerWeaponComp.Get(), MotionWarpingComp.Get());

	if (HasAuthority())
	{
		if (const auto PlayerDataAsset = Cast<UDataAssetPolyStartUp>(DataAssetStarUpAbilities))
		{
			PolyAsc->GiveInitialAbilities(PlayerDataAsset->StartUpAbilities);
			PolyAsc->GiveInitialAbilities(PlayerDataAsset->ReactAbilities);
			PolyAsc->GiveInitialAbilities(PlayerDataAsset->PlayerStartupAbilities);
			PolyAsc->ApplyInitialGameplayEffectToSelf({PlayerDataAsset->PrimaryAttributes});
			PolyAsc->ApplyInitialGameplayEffectToSelf({PlayerDataAsset->SecondaryAttributes});
			PolyAsc->ApplyInitialGameplayEffectToSelf({PlayerDataAsset->SecondaryResistanceAttributes});
		}
	}

	// 由于网络延迟问题 客户端玩家GE的应用会在初始化Hud之前,导致不会触发子系统中的委托回调
	// 因此本地需要手动广播初始值以便widget回调触发
	if (IsLocallyControlled()) { PlayerUIComp->BroadcastHealthManaInitValue(); }

	FAttachmentTransformRules Rules{EAttachmentRule::SnapToTarget, false};
	Rules.LocationRule = EAttachmentRule::SnapToTarget;
	Rules.RotationRule = EAttachmentRule::KeepRelative;
	Rules.ScaleRule    = EAttachmentRule::KeepWorld;
	InitSubMesh(Rules);
}

void APolyCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	InitializeAscInfo();
}

APolyController* APolyCharacter::GetPolyController()
{
	if (!PolyController.IsValid())
	{
		const auto Con = GetController();
		if (!Con) { return nullptr; }
		PolyController = Cast<APolyController>(Con);
	}

	return PolyController.Get();
}

void APolyCharacter::InputMove(const FInputActionValue& InputActionValue)
{
	if (!GetController()) { return; }

	const auto MovementVector = InputActionValue.Get<FVector2D>();


	AddMovementInput(GetControlRotation().Euler().ForwardVector, MovementVector.Y);
	AddMovementInput(GetControlRotation().Euler().RightVector, MovementVector.X);
	PlayerInteractComp->SendAbilityStatusTag(PolyGameplayTags::RpgPoly_Player_Status_Action_Move_ManualMoving);
}

void APolyCharacter::InputMoveCompleted(const FInputActionInstance& InputActionInstance)
{
	PlayerInteractComp->RemoveAbilityStatusTag(PolyGameplayTags::RpgPoly_Player_Status_Action_Move_ManualMoving);
}

void APolyCharacter::InputLook(const FInputActionValue& InputActionValue)
{
	if (!GetController()) { return; }
	const auto MovementVector = InputActionValue.Get<FVector2D>();
	if (!FMath::IsNearlyZero(MovementVector.Y)) { AddControllerPitchInput(MovementVector.Y); }
	if (!FMath::IsNearlyZero(MovementVector.X)) { AddControllerYawInput(MovementVector.X); }
}

void APolyCharacter::InputAbilityPressed(FGameplayTag InGt)
{
	if (!GetPolyAbilitySysComp()) { return; }
	GetPolyAbilitySysComp()->OnAbilityInputPressed(PlayerInteractComp->AnalyzeAbilityClickInputTag(InGt));
}

void APolyCharacter::InputAbilityReleased(FGameplayTag InGt) {}
void APolyCharacter::InputSwitchTargetLeftCompleted(const FInputActionInstance& InputActionInstance) {}
void APolyCharacter::InputSwitchTargetRightCompleted(const FInputActionInstance& InputActionInstance) {}

void APolyCharacter::InitSubMesh(const FAttachmentTransformRules Rules)
{
	Attach_Head->AttachToComponent(GetMesh(), Rules, "headSocket");
	Attach_Beard->AttachToComponent(GetMesh(), Rules, "BeardSocket");
	Attach_Wing1->AttachToComponent(GetMesh(), Rules, "WingLeftSocket");
	Attach_Wing2->AttachToComponent(GetMesh(), Rules, "WingRightSocket");
}
