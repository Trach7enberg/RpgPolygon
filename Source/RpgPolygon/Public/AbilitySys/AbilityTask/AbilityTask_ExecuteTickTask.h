// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_ExecuteTickTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityTaskTickDelegate, float, DeltaTime);

/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UAbilityTask_ExecuteTickTask : public UAbilityTask
{
	GENERATED_BODY()

public:
	UAbilityTask_ExecuteTickTask();

	/// 执行带有输出deltaTime的能力任务
	/// @param OwningAbility
	/// @return 
	UFUNCTION(BlueprintCallable,
		Category="PolyTask|TickTask",
		meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "true"))
	static UAbilityTask_ExecuteTickTask* ExecuteTickTask(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FOnAbilityTaskTickDelegate OnTaskTick;

	virtual void TickTask(float DeltaTime) override;

};
