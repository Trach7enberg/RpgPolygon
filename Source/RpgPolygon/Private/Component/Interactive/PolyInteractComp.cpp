// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/Interactive/PolyInteractComp.h"

#include "NavigationSystem.h"
#include "AI/NavigationSystemBase.h"
#include "Character/PolyCharacterBase.h"
#include "CoreTypes/PolyGameplayTags.h"
#include "FunctionLibrary/PolyFunctionLibrary.h"
#include "RpgPolygon/RpgPolygon.h"

DEFINE_LOG_CATEGORY_STATIC(PolyInteractCompLog, All, All);

FGameplayTag UPolyInteractComp::AnalyzeAbilityClickInputTag(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) { return InInputTag; }
	
	// 非鼠标左键直接返回
 	if (InInputTag != PolyGameplayTags::RpgPoly_InputTag_Click_Interact) { return InInputTag; }

	FHitResult HitResult{};
	GetOwningPlayerController()->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
	if (!HitResult.bBlockingHit) { return InInputTag; }

	const auto IsCharacter = Cast<APolyCharacterBase>(HitResult.GetActor());

	if (IsCharacter == GetOwner()) { return FGameplayTag{}; }

	// 点击到的是角色(敌人或者玩家)
	if (IsCharacter) { return PolyGameplayTags::RpgPoly_InputTag_Click_Character; }

	UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	if (!NavSys)
	{
		UE_LOG(PolyInteractCompLog, Warning, TEXT("The Navigation System Cannot Be Found"));
		return {};
	}
	FNavLocation ProjectedNavLocation;
	if (const auto OnNav = NavSys->ProjectPointToNavigation(HitResult.Location, ProjectedNavLocation, FVector::Zero());
		!OnNav)
	{
		UE_LOG(PolyInteractCompLog, Log, TEXT("Cant Reachable."));
		return {};
	}


	// todo 待判断是可互动物体之类的东西 


	return PolyGameplayTags::RpgPoly_InputTag_Click_Environment;
}

void UPolyInteractComp::SendAbilityStatusTag(const FGameplayTag& InGt) const
{
	if (!GetOwner() || !InGt.IsValid()) { return; }
	UPolyFunctionLibrary::AddGameplayTagToActor(GetOwner(), InGt);
}

void UPolyInteractComp::RemoveAbilityStatusTag(const FGameplayTag& InGt) const
{
	if (!GetOwner() || !InGt.IsValid()) { return; }
	UPolyFunctionLibrary::RemoveGameplayTagFromActor(GetOwner(), InGt);
}

APlayerController* UPolyInteractComp::GetOwningPlayerController()
{
	if (!OwningPlayerController.Get()) { OwningPlayerController = GetOwningController<APlayerController>(); }

	return OwningPlayerController.Get();
}
