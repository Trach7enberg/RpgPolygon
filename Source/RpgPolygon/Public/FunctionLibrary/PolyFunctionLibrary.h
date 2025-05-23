// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RpgPolygon/Public/AbilitySys/Abilities/Offensive/Spell/SpellProjectileGameplayAbility.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PolyFunctionLibrary.generated.h"

struct FPolyProjectileDamageEffectParam;
class UInputMappingContext;
class APolyController;
struct FGameplayTag;
enum class EPolyConfirmType : uint8;
class UPolyAbilitySysComp;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UPolyFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
#pragma region AbilitySystem
	UFUNCTION(BlueprintCallable, Category="PolyFunctionLibrary")
	static UPolyAbilitySysComp* GetPolyAsc(AActor* Context);

	/// 通过InActor的ASC给其添加GT(注意该方法不是replicated的)
	/// @param InActor 
	/// @param TagToAdd 
	UFUNCTION(BlueprintCallable, Category="PolyFunctionLibrary")
	static void AddGameplayTagToActor(AActor* InActor, FGameplayTag TagToAdd);

	/// 通过InActor的ASC给其添加GT(该方法是replicated的)
	/// @param InActor 
	/// @param TagToAdd 
	UFUNCTION(BlueprintCallable, Category="PolyFunctionLibrary")
	static void AddGameplayTagToActorReplicated(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category="PolyFunctionLibrary")
	static void RemoveGameplayTagFromActor(AActor* InActor, FGameplayTag TagToRemove);

	UFUNCTION(BlueprintCallable, Category="PolyFunctionLibrary")
	static void RemoveGameplayTagFromActorReplicated(AActor* InActor, FGameplayTag TagToRemove);

	static bool DoseActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	/// 检查Actor是否包含指定的标签
	/// @param InActor 
	/// @param TagToCheck 
	/// @param OutConfirm 
	UFUNCTION(BlueprintCallable,
		meta=(DisplayName="Dose Actor Have Tag", ExpandEnumAsExecs="OutConfirm"),
		Category="PolyFunctionLibrary")
	static void BP_DoseActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EPolyConfirmType& OutConfirm);


	static FActiveGameplayEffectHandle ApplyDamageGameplayEffectByProjectileParams(
		const FPolyProjectileDamageEffectParam& InParam);

#pragma endregion


#pragma region Misc
	/// 检查Actor是否是同一个阵营
	/// @param A 
	/// @param B 
	/// @return 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyFunctionLibrary")
	static bool AreActorsFriendly(const AActor* A, const AActor* B);


	/// 根据输入角度,返回朝向这个角度的受击标签
	/// @param TeamId 默认为0,为玩家,1为AI
	/// @param Angle 
	/// @return
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyFunctionLibrary")
	static FGameplayTag GetHitReactDirectionTagByAngle(int32 TeamId, float Angle);

	/// 获取Actor Suffer 到 Actor Instigator之间的夹角
	/// 负值表示Instigator在Suffer左边,正值表示Instigator在Suffer右边
	/// @param Instigator 
	/// @param Suffer 
	/// @return 负值表示Instigator在Suffer左边,反之为右边
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyFunctionLibrary")
	static float AngleBetweenActors(const AActor* Instigator,
	                                const AActor* Suffer);

	/// 判断2个actor的方向是否互为相反
	/// @param Attacker 
	/// @param Defender
	/// @param Tolerance 精度
	/// @return 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyFunctionLibrary")
	static bool DirectionOpposite(const AActor* Attacker, const AActor* Defender, float Tolerance = 0.7f);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyFunctionLibrary")
	static FRotator FindLookAtRotation(const AActor* Start, const AActor* Target);

	static void AddInputMappingContextOverride(APolyController*            PolyController,
	                                           const UInputMappingContext* InputMappingContext);

	static void RemoveInputMappingContext(APolyController*            PolyController,
	                                      const UInputMappingContext* InputMappingContext);

	/// 根据散射角度按照给定轴旋转轴生成(均衡的)归一化方向向量数组
	/// @param BaseSpread 
	/// @param NumVector 
	/// @param ForwardVector 起始点的(前向)方向
	/// @param OutArray 
	/// @param RotateAxis 
	static void GetVectorBySpread(const float      BaseSpread,
	                              const float      NumVector,
	                              const FVector&   ForwardVector,
	                              TArray<FVector>& OutArray,
	                              const FVector&   RotateAxis = FVector::UpVector);

	/// 中文字体转换,避免乱码
	/// @param InString
	/// @return 
	static FString GetStringFromUTF16(const FString& InString);

#pragma endregion

	
};
