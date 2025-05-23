// Garrett Gan All Right Reserved


#include "AbilitySys/Abilities/Action/ClickToMoveGameplayAbility.h"

#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySys/AbilityTask/AbilityTask_GetHitUnderCursor.h"
#include "Character/PolyCharacter.h"
#include "Components/SplineComponent.h"
#include "Controller/Player/PolyController.h"
#include "Net/UnrealNetwork.h"
#include "RpgPolygon/RpgPolygon.h"

DEFINE_LOG_CATEGORY_STATIC(ClickToMoveGameplayAbilityLog, All, All);

UClickToMoveGameplayAbility::UClickToMoveGameplayAbility()
{
	SplineComponent = CreateDefaultSubobject<USplineComponent>("SplineComponent");
}

void UClickToMoveGameplayAbility::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UClickToMoveGameplayAbility, CachedDestination);
}

void UClickToMoveGameplayAbility::GetReachableNavPath(FHitResult& TargetLoc, FVector& OutPathEndPoint)
{
	if (!GetPolyController() || !GetPolyCharacter())
	{
		UE_LOG(ClickToMoveGameplayAbilityLog, Log, TEXT("Invalid Loc"));
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, true);
	}

	const FHitResult HitResult = TargetLoc;

	if (!HitResult.bBlockingHit)
	{
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, true);
	}

	CachedDestination = HitResult.Location;

	// 创建导航路径,根据导航路径走
	UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(
	 GetWorld(),
	 GetPolyCharacter()->GetActorLocation(),
	 CachedDestination);

	if (NavPath)
	{
		SplineComponent->ClearSplinePoints();
		for (const auto& PathPoint : NavPath->PathPoints)
		{
			// 向样条曲线添加点
			SplineComponent->AddSplinePoint(PathPoint, ESplineCoordinateSpace::World);
			// DrawDebugSphere(GetWorld(), PathPoint, 25, 10, FColor::Red, false, 1.f);
		}

		// 设置目标点为导航路径数组的最后一个点,防止无法到达某个位置或则跑出世界
		if (NavPath->PathPoints.Num() > 0) { CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1]; }
	}

	OutPathEndPoint = CachedDestination;
}

FVector UClickToMoveGameplayAbility::GetClosetDirectionFromPath()
{
	if (!GetPolyCharacter()) { return FVector::Zero(); }
	const auto Loc = SplineComponent->FindLocationClosestToWorldLocation(
	                                                                     GetPolyCharacter()->GetActorLocation(),
	                                                                     ESplineCoordinateSpace::World);
	// GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Red, *Loc.ToString());
	// 从样条曲线中寻找离Loc最近的方向
	const auto Dir = SplineComponent->FindDirectionClosestToWorldLocation(Loc, ESplineCoordinateSpace::World);

	const auto DisToDes = (Loc - CachedDestination).Length();
	if (DisToDes <= StopDistance) { return FVector::Zero(); }

	return Dir;
}

void UClickToMoveGameplayAbility::Moving(FVector InMoveDirection)
{
	const auto InOwnerCharacter = GetPolyController()->GetPawn();

	if (!InOwnerCharacter || !GetPolyController() || InMoveDirection.IsNearlyZero())
	{
		EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, true);
	}

	const auto DisToDes = (InOwnerCharacter->GetActorLocation() - CachedDestination).Length();


	if (!InOwnerCharacter) { return; }
	InOwnerCharacter->AddMovementInput(InMoveDirection); //TODO 在角色里创建调用client移动函数 不在这里进行移动 
}
