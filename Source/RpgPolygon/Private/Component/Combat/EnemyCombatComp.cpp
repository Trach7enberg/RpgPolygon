// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Combat/EnemyCombatComp.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "MotionWarpingComponent.h"
#include "Component/Weapon/EnemyWeaponComp.h"
#include "Component/WidgetCompont/FloatingTextWidgetComponent.h"
#include "CoreTypes/PolyGameplayTags.h"
#include "FunctionLibrary/PolyFunctionLibrary.h"
#include "SubSystem/ObjectPoolSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(EnemyCombatCompLog, All, All);

UEnemyCombatComp::UEnemyCombatComp() {}

void UEnemyCombatComp::InitDependencies(UPawnWeaponComp* InPawnWeaponComp, UMotionWarpingComponent* InMotionWarpingComp)
{
	Super::InitDependencies(InPawnWeaponComp, InMotionWarpingComp);
	OwningEnemyWeaponComp = Cast<UEnemyWeaponComp>(GetOwningPawnWeaponComp());
}

void UEnemyCombatComp::EnableWeaponCombatDetect(bool bShouldEnable)
{
	if (!GetOwningEnemyWeaponComp()) { return; }
	GetOwningEnemyWeaponComp()->EnableWeaponCollision(bShouldEnable);
}

FOnPreDeathSignature& UEnemyCombatComp::GetCharacterPreOnDeathDelegate() { return OnPreDeathDelegate; }

FVector UEnemyCombatComp::GetCombatSocketLocationByTag(FGameplayTag InSocketTypeTag)
{
	if (!GetOwningEnemyWeaponComp()) { return FVector::Zero(); }
	return GetOwningEnemyWeaponComp()->GetWeaponSocketLocationByTag(InSocketTypeTag);
}

void UEnemyCombatComp::UpdateMotionWarpingTarget(FTransform InTrans, FName WarpTargetName)
{
	if (!GetOwningMotionWarpingComponent()) { return; }

	GetOwningMotionWarpingComponent()->AddOrUpdateWarpTargetFromTransform(WarpTargetName, InTrans);
}

void UEnemyCombatComp::ShowFloatingDamageText(const float Damage, bool bBlockedHit, bool bCriticalHit)
{
	if (!DamageTextWidgetClass)
	{
		UE_LOG(EnemyCombatCompLog, Warning, TEXT("%hs show Floating Damage Failed"), __FUNCTION__);
		return;
	}
	if (!GetOwner()) { return; }
	const auto WidgetCompPool = GetObjectPoolSubsystem();
	if (!WidgetCompPool) { return; }

	const auto DamageTextComponent = Cast<
		UFloatingTextWidgetComponent>(WidgetCompPool->CreateOrGetPoolElem(DamageTextWidgetClass, GetOwner()));
	if (!DamageTextComponent) { return; }


	const auto HitMessage_Critical = UPolyFunctionLibrary::GetStringFromUTF16(TEXT("暴击"));
	const auto HitMessage_Blocked  = UPolyFunctionLibrary::GetStringFromUTF16(TEXT("格挡"));

	DamageTextComponent->SetRelativeLocation(FVector(FMath::RandRange(10, 50),
	                                                 FMath::RandRange(10, 50),
	                                                 FMath::RandRange(10, 50)));

	const auto DamageStr = FString::Printf(TEXT("%.0f"), Damage);

	FString HitMessageText{};
	if (bCriticalHit && bBlockedHit)
	{
		DamageTextComponent->SetFloatingStrColor(FLinearColor::Yellow);
		DamageTextComponent->SetExtraStrColor(FLinearColor::Yellow);
		HitMessageText = HitMessage_Critical + HitMessage_Blocked + "!";
	}
	else if (bCriticalHit)
	{
		DamageTextComponent->SetFloatingStrColor(FLinearColor::Red);
		DamageTextComponent->SetExtraStrColor(FLinearColor::Red);
		HitMessageText = HitMessage_Critical + "!";
	}
	else if (bBlockedHit)
	{
		DamageTextComponent->SetFloatingStrColor(FLinearColor::Gray);
		DamageTextComponent->SetExtraStrColor(FLinearColor::Gray);
		HitMessageText = HitMessage_Blocked + "!";
	}
	DamageTextComponent->SetFloatingStr(DamageStr);
	DamageTextComponent->SetExtraStr(HitMessageText);
	DamageTextComponent->BeginFloating();
}

void UEnemyCombatComp::ExecuteHitReact(AActor* Instigator)
{
	if (!Instigator || !GetOwner()) { return; }
	FGameplayEventData Payload{};
	Payload.Instigator = Instigator;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(),
	                                                         PolyGameplayTags::RpgPoly_Enemy_EventTag_Action_HitReact,
	                                                         Payload);
}

UEnemyWeaponComp* UEnemyCombatComp::GetOwningEnemyWeaponComp()
{
	if (!OwningEnemyWeaponComp.IsValid()) { OwningEnemyWeaponComp = Cast<UEnemyWeaponComp>(GetOwningPawnWeaponComp()); }
	return OwningEnemyWeaponComp.Get();
}
