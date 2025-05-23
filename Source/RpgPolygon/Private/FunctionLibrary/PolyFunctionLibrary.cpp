// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary/PolyFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySys/Core/PolyAbilitySysComp.h"
#include "Controller/Player/PolyController.h"
#include "CoreTypes/PolyCoreStruct.h"
#include "CoreTypes/PolyGameplayTags.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "RpgPolygon/RpgPolygon.h"

#define HIT_REACT_TAG(Team, Direction) ((Team == 0) ? \
		PolyGameplayTags::RpgPoly_Player_Ability_Action_HitReact_##Direction : PolyGameplayTags::RpgPoly_Enemy_Ability_Action_HitReact_##Direction)
class UEnhancedInputLocalPlayerSubsystem;
DEFINE_LOG_CATEGORY_STATIC(PolyFunctionLibraryLog, All, All);

UPolyAbilitySysComp* UPolyFunctionLibrary::GetPolyAsc(AActor* Context)
{
	if (!ensureMsgf(Context, TEXT("the context for ASC cannot be nullptr"))) { return nullptr; }
	if (!Context)
	{
		UE_LOG(PolyFunctionLibraryLog, Error, TEXT("the context for ASC cannot be nullptr"));
		return nullptr;
	}

	return Cast<UPolyAbilitySysComp>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Context));
}

void UPolyFunctionLibrary::AddGameplayTagToActor(AActor* InActor, FGameplayTag TagToAdd)
{
	const auto Asc = GetPolyAsc(InActor);
	if (!Asc) { return; }

	if (!Asc->HasMatchingGameplayTag(TagToAdd)) { Asc->AddLooseGameplayTag(TagToAdd); }
}

void UPolyFunctionLibrary::AddGameplayTagToActorReplicated(AActor* InActor, FGameplayTag TagToAdd)
{
	const auto Asc = GetPolyAsc(InActor);
	if (!Asc) { return; }
	if (!Asc->HasMatchingGameplayTag(TagToAdd)) { Asc->AddReplicatedLooseGameplayTag(TagToAdd); }
}

void UPolyFunctionLibrary::RemoveGameplayTagFromActor(AActor* InActor, FGameplayTag TagToRemove)
{
	const auto Asc = GetPolyAsc(InActor);
	if (!Asc) { return; }
	if (Asc->HasMatchingGameplayTag(TagToRemove)) { Asc->RemoveLooseGameplayTag(TagToRemove); }
}

void UPolyFunctionLibrary::RemoveGameplayTagFromActorReplicated(AActor* InActor, FGameplayTag TagToRemove)
{
	const auto Asc = GetPolyAsc(InActor);
	if (!Asc) { return; }
	if (Asc->HasMatchingGameplayTag(TagToRemove)) { Asc->RemoveReplicatedLooseGameplayTag(TagToRemove); }
}

bool UPolyFunctionLibrary::DoseActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	const auto Asc = GetPolyAsc(InActor);
	if (!Asc) { return false; }

	return Asc->HasMatchingGameplayTag(TagToCheck);
}

void UPolyFunctionLibrary::BP_DoseActorHaveTag(AActor*           InActor,
                                               FGameplayTag      TagToCheck,
                                               EPolyConfirmType& OutConfirm)
{
	OutConfirm = DoseActorHaveTag(InActor, TagToCheck) ? EPolyConfirmType::Successful : EPolyConfirmType::Failed;
}

FActiveGameplayEffectHandle UPolyFunctionLibrary::
ApplyDamageGameplayEffectByProjectileParams(const FPolyProjectileDamageEffectParam& InParam)
{
	if (!InParam.IsParamsValid())
	{
		UE_LOG(PolyFunctionLibraryLog, Warning, TEXT("Params无效,无法应用伤害GE!"));
		return FActiveGameplayEffectHandle();
	}
	const auto SourceAvatar = InParam.SourceAbilitySystemComponent->GetAvatarActor();
	if (!SourceAvatar) { return FActiveGameplayEffectHandle(); }

	auto       EffectContextHandle = InParam.SourceAbilitySystemComponent->MakeEffectContext();
	const auto GeSpecHandle        = InParam.SourceAbilitySystemComponent->MakeOutgoingSpec(
	 InParam.DamageGameplayEffectClass,
	 InParam.AbilityLevel,
	 EffectContextHandle);
	EffectContextHandle.AddSourceObject(SourceAvatar);

	/// 传输设置冲击点的前向向量、以及范围衰减伤害系数(如果有)

	return InParam.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GeSpecHandle.Data);
}

bool UPolyFunctionLibrary::AreActorsFriendly(const AActor* A, const AActor* B)
{
	if (!A || !B) { return false; }
	if (!A->IsA(ACharacter::StaticClass()) || !B->IsA(ACharacter::StaticClass())) { return false; }

	const auto InA = Cast<IGenericTeamAgentInterface>(Cast<ACharacter>(A)->GetController());
	const auto InB = Cast<IGenericTeamAgentInterface>(Cast<ACharacter>(B)->GetController());

	if (!InA || !InB) { return false; }

	const auto Id  = InA->GetGenericTeamId();
	const auto Ids = InB->GetGenericTeamId();
	return InA->GetGenericTeamId() == InB->GetGenericTeamId();
}

FGameplayTag UPolyFunctionLibrary::GetHitReactDirectionTagByAngle(int32 TeamId, float Angle)
{
	FGameplayTag BaseTag;
	if (Angle <= -45.0f && Angle >= -135.0f) { return HIT_REACT_TAG(TeamId, Left); }

	if (Angle > 45.0f && Angle < 135.0f) { return HIT_REACT_TAG(TeamId, Right); }
	if (Angle >= 135.0f || Angle <= -135.0f) { return HIT_REACT_TAG(TeamId, Back); }

	// Angle >= -45.0f && Angle <= 45.0f
	return HIT_REACT_TAG(TeamId, Front);;
}

float UPolyFunctionLibrary::AngleBetweenActors(const AActor* Instigator, const AActor* Suffer)
{
	if (!Instigator || !Suffer) { return 0; }

	// 两个向量得归一化
	const auto SufferForwardVec      = Suffer->GetActorForwardVector();
	const auto SufferToInstigatorVec = (Instigator->GetActorLocation() - Suffer->GetActorLocation()).GetSafeNormal();

	const auto Dot   = FVector::DotProduct(SufferForwardVec, SufferToInstigatorVec);
	const auto Angle = UKismetMathLibrary::DegAcos(Dot);

	// 叉乘返回一个与另外两个向量都垂直的另一个向量,Z轴为负,则Suffer在Instigator左边,否则为右边
	const auto Cross = FVector::CrossProduct(SufferForwardVec, SufferToInstigatorVec);
	return Angle * (Cross.Z > 0 ? 1.f : -1.f);
}

bool UPolyFunctionLibrary::DirectionOpposite(const AActor* Attacker, const AActor* Defender, float Tolerance)
{
	if (!Attacker || !Defender) { return false; }

	// 向量不垂直(0)、方向不相同(1),即面对面的情况时(向量方向相反)才是有效格挡
	return FVector::DotProduct(Attacker->GetActorForwardVector(), Defender->GetActorForwardVector()) < 0.f - Tolerance;
}

FRotator UPolyFunctionLibrary::FindLookAtRotation(const AActor* Start, const AActor* Target)
{
	if (!Start || !Target) { return {}; }

	return UKismetMathLibrary::FindLookAtRotation(Start->GetActorLocation(), Target->GetActorLocation());
}

void UPolyFunctionLibrary::AddInputMappingContextOverride(APolyController*            PolyController,
                                                          const UInputMappingContext* InputMappingContext)
{
	if (!PolyController || !InputMappingContext)
	{
		UE_LOG(PolyFunctionLibraryLog,
		       Error,
		       TEXT("[%hs]PolyController and InputMappingContext cannot be nullptr"),
		       __FUNCTION__);
		return;
	}

	const auto InputSubSystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(PolyController->GetLocalPlayer());
	if (!InputSubSystem)
	{
		UE_LOG(PolyFunctionLibraryLog, Error, TEXT("[%hs]Failed to Add InputMappingContext Override"), __FUNCTION__);
		return;
	}

	InputSubSystem->AddMappingContext(InputMappingContext,
	                                  PolyController->GetMappingContextCurrentPriorityCnt(true));
}

void UPolyFunctionLibrary::RemoveInputMappingContext(APolyController*            PolyController,
                                                     const UInputMappingContext* InputMappingContext)
{
	if (!PolyController || !InputMappingContext)
	{
		UE_LOG(PolyFunctionLibraryLog,
		       Error,
		       TEXT("[%hs]PolyController and InputMappingContext cannot be nullptr"),
		       __FUNCTION__);
		return;
	}

	const auto InputSubSystem = ULocalPlayer::GetSubsystem<
		UEnhancedInputLocalPlayerSubsystem>(PolyController->GetLocalPlayer());
	if (!InputSubSystem)
	{
		UE_LOG(PolyFunctionLibraryLog, Error, TEXT("[%hs]Failed to Remove InputMappingContext"), __FUNCTION__);
		return;
	}

	InputSubSystem->RemoveMappingContext(InputMappingContext);
	PolyController->
			SetMappingContextCurrentPriorityCnt(PolyController->GetMappingContextCurrentPriorityCnt() - 1);
}

void UPolyFunctionLibrary::GetVectorBySpread(const float      BaseSpread,
                                             const float      NumVector,
                                             const FVector&   ForwardVector,
                                             TArray<FVector>& OutArray,
                                             const FVector&   RotateAxis)
{
	if (NumVector <= 0) { return; }

	// 细分分子数
	const auto DeltaFactor = (FMath::IsNearlyZero((FMath::Fmod(BaseSpread, 360.f)))) ? 0 : 1;
	// 细分角度
	const auto DeltaSpread = (NumVector > 1) ? BaseSpread / (NumVector - DeltaFactor) : 0;
	// 初始向量的角度(以UpVector为轴)
	const auto InitSpread = (NumVector > 1) ? -((BaseSpread / 2.f)) : 0;
	// 左分散的向量
	const auto LeftOfSpread = ForwardVector.RotateAngleAxis(InitSpread, RotateAxis);

	for (int i = 0; i < NumVector; ++i)
	{
		const auto Dir = LeftOfSpread.RotateAngleAxis((DeltaSpread) * i,
		                                              RotateAxis);
		OutArray.Add(Dir);
	}
}

FString UPolyFunctionLibrary::GetStringFromUTF16(const FString& InString)
{
	return FString(UTF16_TO_TCHAR(TCHAR_TO_UTF16(*InString)));
}
