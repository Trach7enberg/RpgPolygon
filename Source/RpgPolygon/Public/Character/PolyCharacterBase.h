// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySys/Core/PolyAbilitySysComp.h"
#include "GameFramework/Character.h"
#include "PolyCharacterBase.generated.h"

enum class ERoleType : uint8;
class UDataAssetStartUp;
class UPolyAttributeSet;
class UPolyAbilitySysComp;
class UPolyGiSubSystem;
class UWidgetComponent;
class UMotionWarpingComponent;
class UAttributeSet;

UCLASS()
class RPGPOLYGON_API APolyCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APolyCharacterBase();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	//~ Begin APawn Interface
	/// 只在服务器端调用 这里用于初始化服务器端的Asc
	/// @param NewController 
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	//~ Begin IAbilitySystem Interface
	/// 获取默认的Asc
	/// @return 
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/// 获取Poly能力组件
	/// @return 
	FORCEINLINE virtual UPolyAbilitySysComp*       GetPolyAbilitySysComp() const;
	FORCEINLINE virtual UPolyAttributeSet* GetAttributeSet() { return PolyAs; };
	//~ End IAbilitySystem Interface

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Poly|Var")
	ERoleType CharacterRoleType{};
	

#pragma region Component
	/// 运动扭曲
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Poly|Comp|MotionWarping")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComp{};

	/// 当前角色指示器Widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Poly|Comp|Widget")
	TObjectPtr<UWidgetComponent> LockIndicatorComp{};


	/// GAS的能力组件
	UPROPERTY()
	TObjectPtr<UPolyAbilitySysComp> PolyAsc{};

	/// GAS的属性集
	UPROPERTY()
	TObjectPtr<UPolyAttributeSet> PolyAs{};

#pragma endregion

#pragma region Func

	virtual void BeginPlay() override;

	/// 初始化Asc信息
	virtual void InitializeAscInfo();

	/// 获取游戏实例子系统
	/// @return 
	UPolyGiSubSystem* GetGiSubSystem();


#pragma region OnRep


#pragma endregion

#pragma endregion

#pragma region DataAsset

	/// 角色初始能力资产
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Poly|DataAsset")
	TObjectPtr<UDataAssetStartUp> DataAssetStarUpAbilities;

#pragma endregion

private:
	UPROPERTY()
	TSoftObjectPtr<UPolyGiSubSystem> PolyGiSubSystem{};
};
