// Garrett Gan All Right Reserved


#include "AbilitySys/AbilityTask/AbilityTask_ExecuteTickTask.h"


UAbilityTask_ExecuteTickTask::UAbilityTask_ExecuteTickTask() { bTickingTask = true; }

UAbilityTask_ExecuteTickTask* UAbilityTask_ExecuteTickTask::ExecuteTickTask(UGameplayAbility* OwningAbility)
{
	return NewAbilityTask<UAbilityTask_ExecuteTickTask>(OwningAbility);
}

void UAbilityTask_ExecuteTickTask::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnTaskTick.Broadcast(DeltaTime);
	}else
	{
		EndTask();
	}
	
	
}
