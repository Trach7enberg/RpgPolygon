// Garrett Gan All Right Reserved


#include "UI/Widgets/Enemy/EnemyHealthBarWidget.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Component/UI/EnemyUiComp.h"

void UEnemyHealthBarWidget::InitializePolyWidget()
{
	auto OwnerUiComp = GetOwningEnemyUIComponent();

	if (!OwnerUiComp) { return; }

	OnPolyWidgetInitialize();
}