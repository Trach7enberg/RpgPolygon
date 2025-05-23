// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PolyAIController.generated.h"

class UCrowdFollowingComponent;
struct FAIStimulus;
class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API APolyAIController : public AAIController
{
	GENERATED_BODY()

public:
	APolyAIController(const FObjectInitializer& ObjectInitializer);
	//~ Begin GenericTeamAgentInterface
	/// 判断 AI 对某个 AActor 的态度（友好、敌对、中立）
	/// AI Perception 和 AI 行为逻辑通常会依赖它来决定如何与目标交互,比如配置中的对不同阵营的检测
	/// @param Other 
	/// @return 
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	//~ End GenericTeamAgentInterface

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAI")
	TObjectPtr<UAIPerceptionComponent> AIPerceptionComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAI")
	TObjectPtr<UAISenseConfig_Sight> AISenseConfig_Sight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="PolyAI|Config")
	bool bEnableDetourCrowAvoidance = true;

	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		meta=(EditCondition="bEnableDetourCrowAvoidance", ClampMin="1", ClampMax="4"),
		Category="PolyAI|Config")
	int32 DetourCrowedAvoidanceQuality = 4;

	UPROPERTY(EditDefaultsOnly,
		BlueprintReadOnly,
		meta=(EditCondition="bEnableDetourCrowAvoidance"),
		Category="PolyAI|Config")
	float CollisionQueryRange = 600.f;

	virtual void OnPossess(APawn* InPawn) override;

private:
	/// 根据感知到的目标更新 BT 黑板中的目标键
	/// @param Actor 
	/// @param Stimulus 
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	UPROPERTY()
	TSoftObjectPtr<UCrowdFollowingComponent> CrowdFollowingComponentRef{};
};
