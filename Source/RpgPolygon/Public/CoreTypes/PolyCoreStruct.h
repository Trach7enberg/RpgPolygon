// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "Components/WidgetComponent.h"
#include "PolyCorestruct.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;
class UGameplayAbilityBase;
class APolyWeaponBase;
class UInputMappingContext;
class UPolyLinkedLayerAnimIns;

/// 角色职业
UENUM(BlueprintType)
enum class ERoleType :uint8
{
	Default UMETA(DisplayName = "无"),
	Elementalist UMETA(DisplayName = "法术师"),
	Warrior UMETA(DisplayName = "战士"),
	Range UMETA(DisplayName = "游侠"),
	Assassin UMETA(DisplayName = "刺客")
};

/// 装备的位置
UENUM(BlueprintType)
enum class EEquippedState : uint8
{
	Current,
	Left,
	Right
};

/// 能力启用时候的触发策略
UENUM(BlueprintType)
enum class EPolyAbilityActivationPolicy :uint8
{
	/// 给予能力时不会触发,触发后结束还存在ASC中
	OnTriggered,
	///给予能力时会触发,触发后结束不存在ASC中
	OnGiven,
};

/// 蓝图输出引脚
UENUM(Blueprintable)
enum class EPolyConfirmType:uint8
{
	Successful UMETA(DisplayName="Successful"),
	Failed UMETA(DisplayName="Failed"),
};

/**
 *  玩家人物技能结构体输入标签对应一个能力
 */
USTRUCT(BlueprintType)
struct FPolyAbilityStruct
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories="RpgPoly.InputTag"))
	FGameplayTag InputTag{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayAbilityBase> Ability{};

	bool IsValid() const;
};

/// 每把武器所携带的数据
USTRUCT(BlueprintType)
struct FPolyWeaponData
{
	GENERATED_BODY()

	/// 要链接到主人物蓝图的当前武器(装备时的)动画
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UPolyLinkedLayerAnimIns> WeaponAnimLayerToLink{};

	/// 当前武器装备时对应的一套输入映射
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* WeaponInputMappingContext{};

	/// 当前武器装备时所能拥有的能力
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FPolyAbilityStruct> WeaponDefaultAbilities{};

	/// 武器基础伤害
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat WeaponBaseDamage{};

	/// 武器图标
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> WeaponIcon{};

	/// 手持类型标签对应插槽名字
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FGameplayTag/*SocketTypeTag*/, FName /*Socket Name*/> TagToSocket{};

	///判断数据中的动画、输入映射、武器图标是否有效
	/// @return 
	bool IsValid() const;

	/// 根据标签返回查找的对应的插槽名字
	/// @param InSocketTypeTag 
	/// @return 
	FName FindSocketNameByTag(const FGameplayTag& InSocketTypeTag) const;
};

/// 基础飞弹携带的数据
USTRUCT(BlueprintType)
struct FPolyProjectileDamageEffectParam
{
	GENERATED_BODY()

	FPolyProjectileDamageEffectParam() {}

	UPROPERTY()
	float BaseDamage = 0.f;

	// 如果伤害是带有半径的衰减伤害(1.0f为没有)
	UPROPERTY()
	float RadiusDamageFallOffFactor = 1.f;

	UPROPERTY()
	int32 AbilityLevel = 1;

	/// 角色被击杀死亡时候的冲击点方向(一般为归一化)
	UPROPERTY()
	FVector ImpulseVector = FVector::Zero();

	/// 默认为发起GE的Asc的化身
	UPROPERTY()
	TObjectPtr<UObject> WorldContextObject = nullptr;

	UPROPERTY()
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr;

	/// 发起GE的Actor的ASC
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent = nullptr;

	/// 被应用GE的Actor的ASC
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent = nullptr;

	/// 该Params的(部分重要)参数是否有效
	/// @return 
	bool IsParamsValid() const
	{
		return SourceAbilitySystemComponent && TargetAbilitySystemComponent && DamageGameplayEffectClass;
	}
};

/// 表示单把武器的结构体
USTRUCT(BlueprintType)
struct FWeaponInstance
{
	GENERATED_BODY()

	UPROPERTY()
	FGameplayTag WeaponTag{};

	UPROPERTY()
	TObjectPtr<APolyWeaponBase> Weapon{};

	FWeaponInstance() {}

	FWeaponInstance(const FGameplayTag& InGt, const TObjectPtr<APolyWeaponBase>& InWeapon)
	{
		WeaponTag = InGt;
		Weapon    = InWeapon;
	}

	friend bool operator==(const FWeaponInstance& Lhs, const FWeaponInstance& RHS)
	{
		return Lhs.WeaponTag == RHS.WeaponTag;
	}

	friend bool operator!=(const FWeaponInstance& Lhs, const FWeaponInstance& RHS)
	{
		return Lhs.WeaponTag != RHS.WeaponTag;
	}
};

/// 用于基础武器碰撞时候的委托<br/>
/// @ref APolyWeaponBase::OnWeaponBeginOverlapDelegate,APolyWeaponBase::OnWeaponEndOverlapDelegate
DECLARE_DELEGATE_TwoParams(FOnWeaponOverlapDelegate, AActor*, const FHitResult*);

/// 用于绑定角色的属性值(血量、蓝量)变化时候的委托
/// @ref UPolyUiComp,UEnemyUiComp
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnFloatValueChangeDelegate, float, Value, bool, bIsIncrease);

/// 用于绑定角色的移动速率变化时的UI委托(获得对应GameplayTag时候会广播)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMovingChangeDelegate, bool bIsMoving);

/// 场景中UI生成的池管理
/// @ref UObjectPoolSubsystem
USTRUCT(BlueprintType)
struct FWidgetComponentPool
{
	GENERATED_BODY()

public:
	FWidgetComponentPool() {};

	/// 初始化池系统
	/// @param World 
	void InitializePool(UWorld* World) { if (World) { OwningWorld = World; } }

	/// 是否初始化了？
	/// @return 
	bool IsInitialized() const { return OwningWorld.IsValid(); }

	UWidgetComponent* GetWidgetComp(const TSubclassOf<UWidgetComponent>& WidgetComponentClass);

	/// 从池中获取,没有则创建
	/// @tparam WidgetComponentT 
	/// @param WidgetCompClass 
	/// @return 
	template <typename WidgetComponentT = UWidgetComponent>
	UWidgetComponent* GetOrCreateWidgetComp(TSubclassOf<WidgetComponentT> WidgetCompClass)
	{
		if (!WidgetCompClass || !ensure(IsInitialized())) { return nullptr; }

		WidgetComponentT* WidgetComp = nullptr;
		for (UWidgetComponent* InactiveWidgetComponent : InActiveWidgetComponents)
		{
			if (InactiveWidgetComponent->IsA(WidgetCompClass))
			{
				WidgetComp = InactiveWidgetComponent;
				InActiveWidgetComponents.RemoveSingleSwap(InactiveWidgetComponent);
				break;
			}
		}
		if (!WidgetComp)
		{
			WidgetComp = NewObject<WidgetComponentT>(OwningWorld.Get(), WidgetCompClass);
			if (!WidgetComp) { return nullptr; }
		}
		ActiveWidgetComponents.Add(WidgetComp);

		return WidgetComp;
	}

	/// 将actor释放回对象池
	void ReleaseWidgetComp(UWidgetComponent* InWidgetComp);

	void ReleaseWidgetComp(const TArray<UWidgetComponent*>& InWidgetComps);

	/// 释放所有小部件组件对象
	void ReleaseAll();

	/// 重置Active、InActive对象池
	void ResetPool();

	/// 启用、关闭Actor
	/// @param InWidgetComp 
	/// @param Enable 
	/// @param NewOuter 
	void SetWidgetCompEnable(UWidgetComponent* InWidgetComp, bool Enable, UObject* NewOuter = nullptr) const;

	int32 GetActiveWidgetCompsNum() const { return ActiveWidgetComponents.Num(); }

private:
	/// 已经启用的池中对象,只在游戏运行的时候有效,不序列化
	UPROPERTY(Transient)
	TArray<TObjectPtr<UWidgetComponent>> ActiveWidgetComponents;

	/// 空闲的的池中对象,只在游戏运行的时候有效,不序列化
	UPROPERTY(Transient)
	TArray<TObjectPtr<UWidgetComponent>> InActiveWidgetComponents;

	/// 上下文
	TWeakObjectPtr<UWorld> OwningWorld;
};

/// 角色死亡的委托(死亡动画之前)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPreDeathSignature, AActor* PreparingToDieCharacter);

#pragma region CustomGameplayEffect Context

/// 自定义GE上下文类
USTRUCT(BlueprintType)
struct FPolyGeContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	virtual UScriptStruct* GetScriptStruct() const override { return StaticStruct(); }

	/// 序列化,将当前结构变成0和1组成的数据然后通过网络传输
	/// @param Ar 存储序列化数据或者序列化事物的工具,把数据序列化为一系列的位,内部重载了<<运算符用于序列化或者反序列化
	/// (字节序是多字节数据在计算机内存中存储或者网络传输时各字节的存储顺序 , 这里采用(Byte order neutral = Big Endian)大端字节序)
	/// @param Map 将对象映射到索引的工具,在序列化所有对象时,结构体的所有变量都被转换为字符串(由零和一组成的字符串数组),当序列开始的时候,一堆东西并排放在一起时,知道一个对象是从哪里开始的索引非常有用
	/// @param bOutSuccess 如果序列化成功,会返回true
	/// @return 
	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;

	/// 创建此上下文的副本，以便以后修改
	/// @return 当前GE上下文的副本
	virtual FPolyGeContext* Duplicate() const override
	{
		FPolyGeContext* NewContext = new FPolyGeContext();
		*NewContext                = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}
};

/// 结构体特征选项结构
template <>
struct TStructOpsTypeTraits<FPolyGeContext> : public TStructOpsTypeTraitsBase2<FPolyGeContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy          = true
	};
};

#pragma endregion

// USTRUCT(BlueprintType)
// struct F
