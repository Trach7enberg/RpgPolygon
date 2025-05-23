// Garrett Gan All Right Reserved


#include "Component/WidgetCompont/FloatingTextWidgetComponent.h"

UFloatingTextWidgetComponent::UFloatingTextWidgetComponent()
{
	
}

void UFloatingTextWidgetComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetIsReplicated(true);
}
