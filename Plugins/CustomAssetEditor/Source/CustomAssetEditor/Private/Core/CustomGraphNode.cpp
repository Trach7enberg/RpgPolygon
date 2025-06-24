// Garrett Gan All Right Reserved


#include "Core/CustomGraphNode.h"

#include "CustomAssetEditor.h"
#include "ToolMenu.h"
#include "ToolMenuSection.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphPin.h"
#include "Graph/CustomGraphicPin.h"

#define LOCTEXT_NAMESPACE "CustomGraphNode"

FText UCustomGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const { return Super::GetNodeTitle(TitleType); }
FLinearColor UCustomGraphNode::GetNodeTitleColor() const { return FLinearColor::Red; }
bool UCustomGraphNode::CanUserDeleteNode() const { return true; }

void UCustomGraphNode::GetNodeContextMenuActions(class UToolMenu*                    Menu,
                                                 class UGraphNodeContextMenuContext* Context) const
{
	Super::GetNodeContextMenuActions(Menu, Context);
	// 由于当前函数是const,(this就是const this,而createPin不是const,const this 不能调用非const函数)
	const auto InThis = const_cast<UCustomGraphNode*>(this);
	if (!InThis) { return; }


	// 创建结点右键时候的菜单选项
	FToolMenuSection& Section = Menu->AddSection("CustomGraphNode", LOCTEXT("SectionName", "Custom Node"));

	// 结点右键时候的菜单选项
	Section.AddMenuEntry(
	                     "AddPinEntry",
	                     LOCTEXT("AddPinEntry", "Add Pin Entry"),
	                     LOCTEXT("CreateANewPin", "Create a new pin"),
	                     FSlateIcon(FCustomAssetEditorModule::SlateStyleSet_Name,
	                                FCustomAssetEditorModule::
	                                SlateStyleSet_PropertyName_CustomAssetEditor_NodeAddPinIcon),
	                     FUIAction(FExecuteAction::CreateLambda([InThis, this]()
	                     {
		                     InThis->CreatePin(EGPD_Output,
		                                       "Inputs",
		                                       "SomeInput");
		                     InThis->GetGraph()->NotifyGraphChanged();
		                     InThis->Modify();
	                     }))
	                    );
	// 删除pin脚
	Section.AddMenuEntry(
	                     "DeletePinEntry",
	                     LOCTEXT("DeletePinEntry", "Delete Pin Entry"),
	                     LOCTEXT("DeleteANewPin", "Delete a Old pin"),
	                     FSlateIcon(FCustomAssetEditorModule::SlateStyleSet_Name,
	                                FCustomAssetEditorModule::
	                                SlateStyleSet_PropertyName_CustomAssetEditor_NodeDeletePinIcon),
	                     FUIAction(FExecuteAction::CreateLambda([InThis, this]()
	                     {
		                     UEdGraphPin* InPin = InThis->GetPinAt(InThis->Pins.Num() - 1);
		                     if (InPin->Direction != EGPD_Output) { return; }

		                     InThis->RemovePin(InPin);
		                     GetGraph()->NotifyGraphChanged();
		                     InThis->GetGraph()->NotifyGraphChanged();
		                     InThis->Modify();
	                     }))
	                    );
	// 删除结点
	Section.AddMenuEntry(
	                     "DeleteEntry",
	                     LOCTEXT("DeleteNode", "Delete Node"),
	                     LOCTEXT("DeleteTheNode", "Deletes the node"),
	                     FSlateIcon(FCustomAssetEditorModule::SlateStyleSet_Name,
	                                FCustomAssetEditorModule::
	                                SlateStyleSet_PropertyName_CustomAssetEditor_NodeDeleteNodeIcon),
	                     FUIAction(FExecuteAction::CreateLambda([InThis, this]()
	                     {
		                     InThis->GetGraph()->RemoveNode(InThis);
	                     }))
	                    );
}

UEdGraphPin* UCustomGraphNode::CreateCustomGraphPin(EEdGraphPinDirection InDir, FName InPinName)
{
	const auto   CategoryName      = InDir == EGPD_Input ? "Inputs" : "Outputs";
	UEdGraphPin* Result            = CreatePin(InDir, CategoryName, InPinName);
	Result->PinType.PinSubCategory = SCustomGraphicPin::CustomGraphicPinType.PinSubCategory;

	return Result;
}

#undef LOCTEXT_NAMESPACE
