// Garrett Gan All Right Reserved


#include "UI/Widgets/Player/PlayerWidget.h"

#include "Component/UI/PolyUiComp.h"

UPolyUiComp* UPlayerWidget::GetOwningPlayerUIComponent()
{
	if (!PlayerUiComp.Get())
	{
		const auto TmpComp = GetOwningPlayerPawn()->FindComponentByClass(UPolyUiComp::StaticClass());
		PlayerUiComp        = Cast<UPolyUiComp>(TmpComp);
	}
	return PlayerUiComp.Get();
}
