// Garrett Gan All Right Reserved


#include "SubSystem/ObjectPoolSubsystem.h"

DEFINE_LOG_CATEGORY_STATIC(ObjectPoolSubsystemLog, All, All);

void UObjectPoolSubsystem::PostInitialize()
{
	Super::PostInitialize();
	WidgetComponentPool.InitializePool(GetWorld());
}

UWidgetComponent* UObjectPoolSubsystem::CreateOrGetPoolElem(const TSubclassOf<UWidgetComponent>& InWidgetCompClass,
                                                            UObject*                             NewOwner)
{
	if (!InWidgetCompClass) return nullptr;
	const auto ResultWidgetComp = WidgetComponentPool.GetOrCreateWidgetComp(InWidgetCompClass);
	WidgetComponentPool.SetWidgetCompEnable(ResultWidgetComp, true, NewOwner);
	return ResultWidgetComp;
}

void UObjectPoolSubsystem::ReleasePoolElem(UWidgetComponent* InWidgetComp)
{
	if (!InWidgetComp) return;
	WidgetComponentPool.ReleaseWidgetComp(InWidgetComp);
}

void UObjectPoolSubsystem::ReleasePoolElems(TArray<UWidgetComponent*> InWidgetComps)
{
	WidgetComponentPool.ReleaseWidgetComp(InWidgetComps);
}

void UObjectPoolSubsystem::ResetPool(TSubclassOf<UWidgetComponent> InWidgetCompClass)
{
	UE_LOG(ObjectPoolSubsystemLog,
	       Log,
	       TEXT("Starting ResetPool %s , Current Active Elems (%d)"),
	       *InWidgetCompClass->GetName(),
	       WidgetComponentPool.GetActiveWidgetCompsNum());
	WidgetComponentPool.ResetPool();
	UE_LOG(ObjectPoolSubsystemLog,
	       Log,
	       TEXT("End ResetPool %s , Current Active Elems (%d)"),
	       *InWidgetCompClass->GetName(),
	       WidgetComponentPool.GetActiveWidgetCompsNum());
}
