// Garrett Gan All Right Reserved


#include "Graph/CustomGraphicPinFactory.h"

#include "Graph/CustomGraphicPin.h"

TSharedPtr<SGraphPin> FCustomGraphicPinFactory::CreatePin(UEdGraphPin* Pin) const
{
	if (SCustomGraphicPin::CustomGraphicPinType.PinSubCategory == Pin->PinType.PinSubCategory) { return SNew(SCustomGraphicPin, Pin); }
	return FGraphPanelPinFactory::CreatePin(Pin);
}
