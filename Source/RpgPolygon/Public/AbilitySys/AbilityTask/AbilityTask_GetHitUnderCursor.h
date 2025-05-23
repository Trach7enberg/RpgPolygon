// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_GetHitUnderCursor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMouseTargetDataSignature, const FGameplayAbilityTargetDataHandle&, Data);


/**
 * 获取鼠标下的HitResult TargetData
 */
UCLASS()
class RPGPOLYGON_API UAbilityTask_GetHitUnderCursor : public UAbilityTask
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FMouseTargetDataSignature OnGetTargetDataUnderCursor;

	/// 获取鼠标击中的HitResult TargetData
	/// @param OwningAbility 
	/// @return 
	UFUNCTION(BlueprintCallable,
		Category="PolyTask",
		meta = (DisplayName="GetTargetDataUnderCursor",
			HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UAbilityTask_GetHitUnderCursor* ExecuteAbilityTask_GetHitUnderCursor(UGameplayAbility* OwningAbility);
protected:
	
	virtual void Activate() override;

	/// 发送FHitResult类型的数据给服务器
	void SendTargetDataToServer();

	/// 当复制的数据被接收时，这个函数将在服务器上被调用
	/// @param DataHandle 包装有复制数据的一个Handle
	/// @param ActivationTag 传过来的游戏标签
	UFUNCTION()
	void OnTargetDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& DataHandle, FGameplayTag ActivationTag);
};
