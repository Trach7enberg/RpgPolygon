// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PolyCharacterBase.h"
#include "Interface/Provider/CombatProvider.h"
#include "KnightRunitEnemyCharacter.generated.h"

class UEnemyUiComp;
class UEnemyWeaponComp;
class UEnemyCombatComp;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API AKnightRunitEnemyCharacter : public APolyCharacterBase, public ICombatProvider
{
	GENERATED_BODY()

public:
	AKnightRunitEnemyCharacter();
	virtual void              PossessedBy(AController* NewController) override;
	virtual TScriptInterface<ICombatInterface> GetCombatInterface() override;

	//~ Begin IAbilitySystem Interface
	/// 获取默认的Asc
	/// @return 
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	/// 获取Poly能力组件 
	/// @return 
	virtual UPolyAbilitySysComp* GetPolyAbilitySysComp() const override;
	virtual UPolyAttributeSet*   GetAttributeSet() override { return PolyAs; };
	//~ End IAbilitySystem Interface

protected:
	virtual void BeginPlay() override;
	void         InitAbilityInfo();
	virtual void OnRep_PlayerState() override;

	/// 角色的战斗组件
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Poly|Comp|Combat")
	TObjectPtr<UEnemyCombatComp> EnemyCombatComp;

	/// 角色的武器组件
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Poly|Comp|Weapon")
	TObjectPtr<UEnemyWeaponComp> EnemyWeaponComp;

	/// 角色与UI通信的组件
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Poly|Comp|UI")
	TObjectPtr<UEnemyUiComp> EnemyUiComp;

	/// 敌人名字牌
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(AllowPrivateAccess="true"), Category="Poly|Comp|UI")
	TObjectPtr<UWidgetComponent> NameplateWidgetComp;

	/// 翅膀1
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Attach_Wing1{};

	/// 翅膀2
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Attach_Wing2{};

	/// 胡子
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Attach_Beard{};

	/// 头部
	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> Attach_Head{};

	/// 初始化Asc信息
	virtual void InitializeAscInfo() override;
	void InitEnemyUI();

private:
	void InitSubMesh(
		FAttachmentTransformRules Rules = {EAttachmentRule::KeepRelative, false});
};
