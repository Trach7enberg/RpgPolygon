// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "PolyController.generated.h"

/**
 * 
 */
UCLASS()
class RPGPOLYGON_API APolyController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	APolyController();
	
	virtual void BeginPlay() override;
	
	//~ Begin GenericTeamAgentInterface
	/// 设置阵营ID
	/// @param NewTeamID 
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;

	/// 获取控制器的阵营ID
	/// @return 
	virtual FGenericTeamId GetGenericTeamId() const override;

	/// 判断 AI 对某个 AActor 的态度（友好、敌对、中立）
	/// AI Perception 和 AI 行为逻辑通常会依赖它来决定如何与目标交互,比如配置中的对不同阵营的检测
	/// @param Other 
	/// @return 
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	//~ End GenericTeamAgentInterface

	/// 获取当前按键映射上下文当前的优先级
	/// @param bAutoIncrease 
	/// @return 
	int32        GetMappingContextCurrentPriorityCnt(bool bAutoIncrease = false);
	/// 设置当前按键映射上下文当前的优先级
	/// @param InPriority 
	void SetMappingContextCurrentPriorityCnt(const int32 InPriority)
	{
		this->MappingContextCurrentPriorityCnt = FMath::Max(0, InPriority);
	}

private:
	FGenericTeamId TeamID{};

	/// 按键映射上下文当前的优先级
	UPROPERTY()
	int32 MappingContextCurrentPriorityCnt = 0;
};
