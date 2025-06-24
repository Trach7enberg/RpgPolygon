// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "EdGraphUtilities.h"

/**
 * 自定义Graph Pin工厂类
 */
struct CUSTOMASSETEDITOR_API FCustomGraphicPinFactory : public FGraphPanelPinFactory
{
public:
	virtual ~FCustomGraphicPinFactory() override {};

	virtual TSharedPtr<class SGraphPin> CreatePin(class UEdGraphPin* Pin) const override;
};
