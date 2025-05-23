// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Widgets/PolyBaseWidget.h"
#include "SubSystem/PolyGiSubSystem.h"

UPolyGiSubSystem* UPolyBaseWidget::GetPolyGiSubSystem()
{
	if (!PolyGiSubSystem.IsValid())
	{
		const auto LocalOwingPlayer = GetOwningPlayer();
		if (!LocalOwingPlayer) { return nullptr; }

		const auto Gi = LocalOwingPlayer->GetGameInstance();
		if (!Gi) { return nullptr; }
		PolyGiSubSystem = Gi->GetSubsystem<UPolyGiSubSystem>();
	}

	return PolyGiSubSystem.Get();
}

float UPolyBaseWidget::CalculateHorizontalOffset(float ParentRootRenderAngle)
{
	const auto Sign = ParentRootRenderAngle > 0.f ? 1 : -1;
	return 360.f - FMath::Abs(ParentRootRenderAngle) * Sign;
}

void UPolyBaseWidget::InitializePolyWidget() { OnPolyWidgetInitialize(); }
