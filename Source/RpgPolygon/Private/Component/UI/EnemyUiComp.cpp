// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/EnemyUiComp.h"

#include "AbilitySys/Core/PolyAbilitySysComp.h"
#include "AbilitySys/Core/PolyAttributeSet.h"
#include "Kismet/KismetMathLibrary.h"
#include "RpgPolygon/RpgPolygon.h"

void UEnemyUiComp::InitializePawnComponent()
{
	const auto Asc = GetPolyAbilitySysComp();
	if (!Asc) { return; }
	const auto As = Asc->GetAttributeSet(UPolyAttributeSet::StaticClass());
	Asc->GetGameplayAttributeValueChangeDelegate(UPolyAttributeSet::GetCurrentHealthAttribute()).AddLambda([this, Asc
	 ](const FOnAttributeChangeData& Data)
	 {
		 Client_BroadcastOnEnemyHealthChanged(Data.NewValue, Data.OldValue);
	 });
}

void UEnemyUiComp::BroadcastHealthManaInitValue()
{
	const auto Asc = GetPolyAbilitySysComp();
	if (!Asc) { return; }
	if (OnEnemyHealthChanged.IsBound())
	{
		Client_BroadcastOnEnemyHealthChanged(Asc->GetNumericAttribute(UPolyAttributeSet::GetCurrentHealthAttribute()));
	}
}

void UEnemyUiComp::Client_BroadcastOnEnemyHealthChanged_Implementation(float New, float Old)
{
	const auto Asc = GetPolyAbilitySysComp();
	if (!Asc) { return; }
	const auto Max = Asc->GetNumericAttribute(UPolyAttributeSet::GetMaxHealthAttribute());
	OnEnemyHealthChanged.Broadcast(Max > 0 ? New / Max : 0,
	                               New > Old);
}
