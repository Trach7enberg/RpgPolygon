// Garrett Gan All Right Reserved


#include "AbilitySys/AbilityTask/AbilityTask_GetHitUnderCursor.h"

#include "AbilitySystemComponent.h"

UAbilityTask_GetHitUnderCursor* UAbilityTask_GetHitUnderCursor::ExecuteAbilityTask_GetHitUnderCursor(
	UGameplayAbility* OwningAbility)
{
	const auto Result = NewAbilityTask<UAbilityTask_GetHitUnderCursor>(OwningAbility);
	return Result;
}

void UAbilityTask_GetHitUnderCursor::Activate()
{
	Super::Activate();
	// 当前不在服务器控制的话就发送(HitResult)数据给服务器
	if (Ability && Ability->GetActorInfo().IsLocallyControlled()) { SendTargetDataToServer(); }
	else
	{
		// 当前已经在服务器,只需要监听发送过来的数据,当服务接受数据会广播一个委托,因此我们获取这个委托即可
		AbilitySystemComponent.Get()->
		                       AbilityTargetDataSetDelegate(GetAbilitySpecHandle(), GetActivationPredictionKey()).
		                       AddUObject(this, &UAbilityTask_GetHitUnderCursor::OnTargetDataReplicatedCallBack);

		// 当服务器广播委托先于我们还没有绑定那个接受数据的委托时,导致我们没有执行回调函数,就用下面这个函数,返回值为true说明数据已经成功到达,并且我们的委托已经被绑定
		const bool BIsCalledDelegate = AbilitySystemComponent->CallReplicatedTargetDataDelegatesIfSet(
		 GetAbilitySpecHandle(),
		 GetActivationPredictionKey());

		// 委托成功绑定但是客户端的数据还没送过来,我们需要等待那个数据
		if (!BIsCalledDelegate) { SetWaitingOnRemotePlayerData(); }
	}
}

void UAbilityTask_GetHitUnderCursor::SendTargetDataToServer()
{
	const auto ActorInfo = Ability->GetCurrentActorInfo();
	const auto PController = ActorInfo->PlayerController.Get();
	if (!ActorInfo ||  !PController) { return; }


	// 告诉ASC,接下来要执行一段客户端预测操作(Prediction) 请为我开启 Prediction ID 并同步给服务器,服务端稍后判定
	FScopedPredictionWindow ScopedPredictionWindow(ActorInfo->AbilitySystemComponent.Get());

	FHitResult HitResult{};
	PController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	// 创建一个要发送给服务器FHitResult数据的结构体
	const auto HitData = new FGameplayAbilityTargetData_SingleTargetHit();
	HitData->HitResult = HitResult;

	// 包裹FHitResult数据的一个Handle
	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(HitData);

	// 发送FHitResult数据到服务器(该函数内部有一个委托会进行广播)
	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(),
	                                                      GetActivationPredictionKey(),
	                                                      DataHandle,
	                                                      FGameplayTag(),
	                                                      AbilitySystemComponent->ScopedPredictionKey);


	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnGetTargetDataUnderCursor.Broadcast(DataHandle);
	}
}

void UAbilityTask_GetHitUnderCursor::OnTargetDataReplicatedCallBack(
	const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag                            ActivationTag)
{
	// 数据只会从服务器复制到客户端,但我们也可以将复制的数据通过RPC从客户端发送到服务器,所以有时候也可以叫"Replicated Data"
	// 接收数据的时候还要通知能力系统组件,因为这个数据存储在一个特定的结构里,因此我们需要通知Asc你不需要存储它，也不需要再缓存它
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());

	if (ShouldBroadcastAbilityTaskDelegates()) { OnGetTargetDataUnderCursor.Broadcast(DataHandle); }

}
