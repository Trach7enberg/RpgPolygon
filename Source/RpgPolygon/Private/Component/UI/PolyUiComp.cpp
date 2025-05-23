// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/UI/PolyUiComp.h"

#include "AbilitySys/Core/PolyAbilitySysComp.h"
#include "AbilitySys/Core/PolyAttributeSet.h"
#include "Character/PolyCharacterBase.h"
#include "CoreTypes/PolyGameplayTags.h"
#include "RpgPolygon/RpgPolygon.h"

void UPolyUiComp::InitialUiComponent()
{
	const auto Asc = GetPolyAbilitySysComp();
	if (!Asc) { return; }

	Asc->GetGameplayAttributeValueChangeDelegate(UPolyAttributeSet::GetCurrentHealthAttribute()).AddLambda([this, Asc
	 ](const FOnAttributeChangeData& Data)
	 {
		 OnHealthChanged.Broadcast(Data.NewValue / Asc
		                           ->GetNumericAttribute(UPolyAttributeSet::GetMaxHealthAttribute()),
		                           Data.NewValue > Data.OldValue);
	 });

	Asc->GetGameplayAttributeValueChangeDelegate(UPolyAttributeSet::GetCurrentManaAttribute()).AddLambda([this, Asc
	 ](const FOnAttributeChangeData& Data)
	 {
		 OnManaChanged.Broadcast(Data.NewValue / Asc
		                         ->GetNumericAttribute(UPolyAttributeSet::GetMaxManaAttribute()),
		                         Data.NewValue > Data.OldValue);
	 });

	Asc->RegisterGameplayTagEvent(PolyGameplayTags::RpgPoly_Player_Status_Action_Move_ManualMoving).AddLambda(
	 [this](const FGameplayTag Tag, int32 NewCount)
	 {
		 if (NewCount == 0) { OnMovingChangeDelegateDelegate.Broadcast(false); }
		 else { OnMovingChangeDelegateDelegate.Broadcast(true); }
	 });
	Asc->RegisterGameplayTagEvent(PolyGameplayTags::RpgPoly_Player_Status_Action_Move_AutoMoving).AddLambda(
	 [this](const FGameplayTag Tag, int32 NewCount)
	 {
		 if (NewCount == 0) { OnMovingChangeDelegateDelegate.Broadcast(false); }
		 else { OnMovingChangeDelegateDelegate.Broadcast(true); }
	 });
}

void UPolyUiComp::BroadcastHealthManaInitValue()
{
	const auto Asc = GetPolyAbilitySysComp();
	if (!Asc) { return; }
	if (OnHealthChanged.IsBound())
	{
		OnHealthChanged.Broadcast(Asc->GetNumericAttribute(UPolyAttributeSet::GetCurrentHealthAttribute()) / Asc
		                          ->GetNumericAttribute(UPolyAttributeSet::GetMaxHealthAttribute()),
		                          false);
	}

	if (OnManaChanged.IsBound())
	{
		OnManaChanged.Broadcast(Asc->GetNumericAttribute(UPolyAttributeSet::GetCurrentManaAttribute()) / Asc
		                        ->GetNumericAttribute(UPolyAttributeSet::GetMaxManaAttribute()),
		                        false);
	}
}

void UPolyUiComp::BeginDestroy() { Super::BeginDestroy(); }
