// Garrett Gan All Right Reserved


#include "Controller/AI/PolyAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Character/PolyCharacterBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interface/Provider/CombatProvider.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

APolyAIController::APolyAIController(const FObjectInitializer& ObjectInitializer):
	Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("AIPerceptionComponent");
	AISenseConfig_Sight   = CreateDefaultSubobject<UAISenseConfig_Sight>("AISenseConfig_Sight");

	// 控制 AI (感知)视觉对不同阵营(Affiliation)的检测
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies    = true;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals   = false;

	// AI 最大视野
	AISenseConfig_Sight->SightRadius = 5000.f;
	// AI 在看到目标后 失去目标的最大距离
	AISenseConfig_Sight->LoseSightRadius = 0.f;
	// AI视野角度
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;


	AIPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	// AI 优先使用哪种感知方式 来检测目标
	AIPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
	// 当 AI 发现、丢失或更新目标的感知状态时会触发的回调
	AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);

	// TODO 蓝图配置 
	// 在基类的构造过程中,当前(子)类的部分还未构造完成,虚拟函数调用会绑定到基类的函数,而不是派生类的函数,无所谓这里就是要调用基类的函数
	SetGenericTeamId(1);

	CrowdFollowingComponentRef = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent());
}

ETeamAttitude::Type APolyAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const auto ToCheckActor = Cast<APolyCharacterBase>(&Other);
	if (!ToCheckActor) { return ETeamAttitude::Friendly; }

	// ID不同则视为敌对
	if (const auto ToCheckController = Cast<IGenericTeamAgentInterface>(ToCheckActor->GetController());
		ToCheckController && ToCheckController->GetGenericTeamId() != GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;
	}

	return ETeamAttitude::Friendly;
	
}

void APolyAIController::BeginPlay()
{
	Super::BeginPlay();
	if (CrowdFollowingComponentRef.IsValid())
	{
		// 启用 Crowd Simulation群体模拟 AI 角色会使用智能避障,自动调整位置,避免碰撞
		CrowdFollowingComponentRef->SetCrowdSimulationState(bEnableDetourCrowAvoidance
																? ECrowdSimulationState::Enabled
																: ECrowdSimulationState::Disabled);
		switch (DetourCrowedAvoidanceQuality)
		{
			case 1:
				CrowdFollowingComponentRef->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
			break;
			case 2:
				CrowdFollowingComponentRef->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
			break;
			case 3:
				CrowdFollowingComponentRef->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
			break;
			case 4:
				CrowdFollowingComponentRef->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
			break;

			default:
				break;;
		}

		// 设置当前 AI 角色的避障分组,只有属于相同 GroupFlags 的 AI 之间才会互相避让
		CrowdFollowingComponentRef->SetAvoidanceGroup(1);
		// 设置当前 AI 角色需要避让的分组,AI 角色会避让 GroupFlags 所指定的组
		CrowdFollowingComponentRef->SetGroupsToAvoid(1);
		// 设置当前 AI 检测其他 AI 角色的范围,用于控制 AI 角色多远距离内会检测到其他 AI 并进行避让
		CrowdFollowingComponentRef->SetCrowdCollisionQueryRange(CollisionQueryRange);
	}
}
void APolyAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	ensureMsgf(BehaviorTree, TEXT("BehaviorTree Cant Be Null!"));

	// 运行并初始化行为树黑板
	if (!BehaviorTree) { return; }
	RunBehaviorTree(BehaviorTree);

	if (!GetBlackboardComponent()) { return; }
	// 初始化黑板键部分静态的不变值变量
	GetBlackboardComponent()->SetValueAsFloat(FName("EnemyDefaultMaxWalkSpeed"),
											  GetCharacter()
												  ? GetCharacter()->GetCharacterMovement()->MaxWalkSpeed
												  : 0.f);
}
void APolyAIController::OnTargetPerceptionUpdated(AActor* Actor,  FAIStimulus Stimulus)
{
	if (!Stimulus.WasSuccessfullySensed()) { return; }
	
	const auto InCombatProvider = Cast<ICombatProvider>(Actor);
	if (!InCombatProvider) { return; }

	// if (InCombatInterface->IsDead()) { return; }
	
	if (const auto BlackBoard = GetBlackboardComponent();
		BlackBoard && Actor)
	{
		// 不需要每次都设置黑板键
		if (BlackBoard->GetValueAsObject(FName("TargetActor"))) { return; }
	
		// if (!Cast<AWarriorCharacterBase>(Actor)) { return; }
		BlackBoard->SetValueAsObject(FName("TargetActor"), Actor);
	}
}
