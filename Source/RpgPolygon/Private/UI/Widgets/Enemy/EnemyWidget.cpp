// Garrett Gan All Right Reserved


#include "UI/Widgets/Enemy/EnemyWidget.h"

#include "Component/UI/EnemyUiComp.h"

void UEnemyWidget::InitializePolyWidget() { OnPolyWidgetInitialize(); }

void UEnemyWidget::InitializePolyWidget(UEnemyUiComp* InEnemyUiComp)
{
	this->EnemyUiComp = InEnemyUiComp;
	InitializePolyWidget();
}


UEnemyUiComp* UEnemyWidget::GetOwningEnemyUIComponent() { return EnemyUiComp.Get(); }

