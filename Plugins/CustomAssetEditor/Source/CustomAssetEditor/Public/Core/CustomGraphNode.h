// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "CustomGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMASSETEDITOR_API UCustomGraphNode : public UEdGraphNode
{
	GENERATED_BODY()

public:
	virtual FText        GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual bool         CanUserDeleteNode() const override;
	virtual void
	GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	/// 创建自定义图形结点的引脚
	/// @param InDir 引脚的方向
	/// @param InPinName 引脚的名字
	/// @return 
	UEdGraphPin* CreateCustomGraphPin(EEdGraphPinDirection InDir, FName InPinName);
};
