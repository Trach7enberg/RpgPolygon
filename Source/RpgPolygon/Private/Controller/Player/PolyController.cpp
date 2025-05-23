// Garrett Gan All Right Reserved


#include "Controller/Player/PolyController.h"

APolyController::APolyController()
{
	// 启用复制
	bReplicates      = true;
	bShowMouseCursor = true;

	// 设置鼠标的样式
	DefaultMouseCursor = EMouseCursor::Type::Default;
	
}

void APolyController::BeginPlay()
{
	Super::BeginPlay();
	SetGenericTeamId(0);
}

void APolyController::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	if (TeamID != NewTeamID) { TeamID = NewTeamID; }
}

FGenericTeamId APolyController::GetGenericTeamId() const { return TeamID; }

ETeamAttitude::Type APolyController::GetTeamAttitudeTowards(const AActor& Other) const
{
	// ID不同则视为敌对
	if (const auto ToCheckActor = Cast<IGenericTeamAgentInterface>(&Other);
		ToCheckActor && ToCheckActor->GetGenericTeamId() != GetGenericTeamId()) { return ETeamAttitude::Hostile; }

	return ETeamAttitude::Friendly;
}

int32 APolyController::GetMappingContextCurrentPriorityCnt(const bool bAutoIncrease)
{
	if (bAutoIncrease) { return MappingContextCurrentPriorityCnt++; }

	return MappingContextCurrentPriorityCnt;
}
