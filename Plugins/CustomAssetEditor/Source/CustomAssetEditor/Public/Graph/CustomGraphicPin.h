// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "SGraphPin.h"

using SSuper = SGraphPin;

/**
 * 自定义图形结点引脚
 */
class CUSTOMASSETEDITOR_API SCustomGraphicPin : public SGraphPin
{
public:
	SLATE_BEGIN_ARGS(SCustomGraphicPin){};
	SLATE_END_ARGS();
	const static FEdGraphPinType CustomGraphicPinType;
	void Construct(const FArguments& InArgs, UEdGraphPin* InGraphPinObj)
	{
		SSuper::Construct(SSuper::FArguments(), InGraphPinObj);
	}

	
protected:
	virtual FSlateColor GetPinColor() const override;
};
