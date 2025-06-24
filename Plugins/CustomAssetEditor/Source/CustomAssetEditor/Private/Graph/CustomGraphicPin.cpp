// Garrett Gan All Right Reserved


#include "Graph/CustomGraphicPin.h"

const FEdGraphPinType SCustomGraphicPin::CustomGraphicPinType
		= {
			"",
			"CustomPin",
			nullptr,
			{},
			false,
			{}
		};

FSlateColor SCustomGraphicPin::GetPinColor() const { return {FLinearColor::White}; }
