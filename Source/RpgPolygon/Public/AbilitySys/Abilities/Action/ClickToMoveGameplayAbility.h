// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySys/Abilities/PolyGameplayAbility.h"
#include "ClickToMoveGameplayAbility.generated.h"

class USplineComponent;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UClickToMoveGameplayAbility : public UPolyGameplayAbility
{
	GENERATED_BODY()

public:
	UClickToMoveGameplayAbility();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/// 到达目标点多近时停止
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PolyAbility|ClickMove")
	float StopDistance = 10.f;

	/// 获取通向目标点可行走的导航路径
	/// @param TargetLoc
	/// @param OutPathEndPoint 
	UFUNCTION(BlueprintCallable, Category="PolyAbility|ClickMove")
	void GetReachableNavPath(UPARAM(ref)FHitResult& TargetLoc, FVector& OutPathEndPoint);

	/// 从可导航的路径中获取离当前角色最近的点
	/// @return 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyAbility|ClickMove")
	FVector GetClosetDirectionFromPath();


	/// 开始移动
	/// @param InMoveDirection 
	UFUNCTION(BlueprintCallable, Category="PolyAbility|ClickMove|ClickMove")
	void Moving(FVector InMoveDirection);

private:
	/// 样条线组件,用于平滑路径
	UPROPERTY()
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(Replicated)
	FVector CachedDestination{};
};
