// Garrett Gan All Right Reserved


#include "Core/CustomGraphSchema.h"

#include "Core/CustomGraphNode.h"
#include "EdGraph/EdGraph.h"

#define LOCTEXT_NAMESPACE "NewNodeAction"

UEdGraphNode* FNewNodeAction::PerformAction(UEdGraph*       ParentGraph,
                                            UEdGraphPin*    FromPin,
                                            const FVector2D Location,
                                            bool            bSelectNewNode)
{
	auto ResultGraphNode = NewObject<UCustomGraphNode>(ParentGraph);
	ResultGraphNode->CreateNewGuid();
	ResultGraphNode->NodePosX = Location.X;
	ResultGraphNode->NodePosY = Location.Y;

	auto InputPin = ResultGraphNode->CreateCustomGraphPin(EGPD_Input, "SomeInput");
	ResultGraphNode->CreateCustomGraphPin(EGPD_Output, "Output1");
	ResultGraphNode->CreateCustomGraphPin(EGPD_Output, "Output2");

	if (FromPin != nullptr) { ResultGraphNode->GetSchema()->TryCreateConnection(FromPin, InputPin); }

	ParentGraph->Modify();
	ParentGraph->AddNode(ResultGraphNode, true, true);

	return ResultGraphNode;
}

void UCustomGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	const TSharedPtr<FNewNodeAction> InNewNodeAction(new FNewNodeAction(LOCTEXT("Nodes", "Nodes"),
	                                                                    LOCTEXT("NewNode", "NewNode"),
	                                                                    LOCTEXT("Makes a new node", "Makes a new node"),
	                                                                    0,
	                                                                    LOCTEXT("KNewNode", "New"),
	                                                                    0));
	ContextMenuBuilder.AddAction(InNewNodeAction);
}

const FPinConnectionResponse UCustomGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const

{
	if (!A || !B) { return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, "Need 2 pins"); }
	if (A->GetOwningNode() == B->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW,
		                              "Cannot connect input and output pins of the same node");
	}

	const auto             bCanConnect = (A->Direction != B->Direction);
	FPinConnectionResponse ResultResponse{};
	ResultResponse.Response = bCanConnect ? CONNECT_RESPONSE_BREAK_OTHERS_AB : CONNECT_RESPONSE_DISALLOW;
	ResultResponse.Message  = bCanConnect
		                          ? LOCTEXT("OTHERS_AB Message", "Inputs and outputs can connect to each other")
		                          : LOCTEXT("DISALLOW Message", "Inputs can only connect to outputs");


	return ResultResponse;
}

#undef LOCTEXT_NAMESPACE
