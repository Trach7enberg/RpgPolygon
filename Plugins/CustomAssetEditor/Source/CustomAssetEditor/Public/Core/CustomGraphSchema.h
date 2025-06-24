// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "CustomGraphSchema.generated.h"

/// 定义和管理“右键菜单中的行为条目”
USTRUCT()
struct FNewNodeAction : public FEdGraphSchemaAction
{
public:
	GENERATED_BODY()
	FNewNodeAction() = default;

	FNewNodeAction(const FText& InNodeCategory,
	               const FText& InMenuDesc,
	               const FText& InToolTip,
	               int32        InGrouping,
	               const FText& InKeywords,
	               int32        InSectionID)
	: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping, InKeywords, InSectionID) {}

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph,
	                                    UEdGraphPin*    FromPin,
	                                    const FVector2D Location,
	                                    bool            bSelectNewNode = true) override;
};

/**
 * 定义图表Graph中的节点、连线和其他元素的规则和行为
 */
UCLASS()
class CUSTOMASSETEDITOR_API UCustomGraphSchema : public UEdGraphSchema
{
	GENERATED_BODY()

public:
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
};
