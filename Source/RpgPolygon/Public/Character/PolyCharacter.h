// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PolyCharacterBase.h"
#include "Interface/Provider/CombatProvider.h"
#include "PolyCharacter.generated.h"

class UPolyInteractComp;
class UPolyEquipmentComp;
class APolyController;
class UPolyWeaponComp;
class UDataAssetInputConfig;
class UPawnCombatComp;
struct FInputActionInstance;
struct FInputActionValue;
class UPolyUiComp;
class UPolyCombatComp;
class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API APolyCharacter : public APolyCharacterBase, public ICombatProvider
{
	GENERATED_BODY()

public:
	APolyCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual TScriptInterface<ICombatInterface> GetCombatInterface() override;

protected:
	virtual void BeginPlay() override;

	/// 跟随弹簧的摄像机
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Poly|Comp")
	TObjectPtr<UCameraComponent> CameraFollow;

	/// 弹簧
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Poly|Comp")
	TObjectPtr<USpringArmComponent> CameraBoom;

	/// 角色的战斗组件
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Poly|Comp")
	TObjectPtr<UPolyCombatComp> PlayerCombatComp;

	/// 角色的武器组件
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Poly|Comp")
	TObjectPtr<UPolyWeaponComp> PlayerWeaponComp;

	/// 角色与UI通信的组件
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Poly|Comp")
	TObjectPtr<UPolyUiComp> PlayerUIComp;

	/// 角色装备组件
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Poly|Comp")
	TObjectPtr<UPolyEquipmentComp> PlayerEquipmentComp;

	/// 角色的互动组件,主要是和输入左键点击相关的事情分析
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Poly|Comp")
	TObjectPtr<UPolyInteractComp> PlayerInteractComp;

	/// 翅膀1
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category="Poly|Comp",
		meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Attach_Wing1{};

	/// 翅膀2
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category="Poly|Comp",
		meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Attach_Wing2{};

	/// 胡子
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category="Poly|Comp",
		meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Attach_Beard{};

	/// 头部
	UPROPERTY(VisibleAnywhere,
		BlueprintReadOnly,
		Category="Poly|Comp",
		meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Attach_Head{};


	/// 初始化Asc信息
	virtual void InitializeAscInfo() override;

	/// 客户端初始化ASC
	virtual void OnRep_PlayerState() override;

	/// 玩家的输入与能力映射配置
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Poly|DataAsset")
	TObjectPtr<UDataAssetInputConfig> DataAssetInputConfig{};


	APolyController* GetPolyController();

private:
	TWeakObjectPtr<APolyController> PolyController{};

	void InitSubMesh(
		FAttachmentTransformRules Rules = {EAttachmentRule::KeepRelative, false});

	void InputMove(const FInputActionValue& InputActionValue);
	void InputMoveCompleted(const FInputActionInstance& InputActionInstance);
	void InputLook(const FInputActionValue& InputActionValue);
	void InputSwitchTargetLeftCompleted(const FInputActionInstance& InputActionInstance);
	void InputSwitchTargetRightCompleted(const FInputActionInstance& InputActionInstance);
	void InputAbilityPressed(FGameplayTag InGt);
	void InputAbilityReleased(FGameplayTag InGt);
};
