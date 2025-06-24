// Garrett Gan All Right Reserved


#include "Core/CustomAssetEditorApp.h"

#include "Core/CustomAsset.h"
#include "Core/CustomAsset.h"
#include "Core/CustomGraphNode.h"
#include "Core/CustomGraphSchema.h"
#include "Core/AppMode/CustomAssetAppMode.h"
#include "Graph/CustomGraphicRuntime.h"
#include "Kismet2/BlueprintEditorUtils.h"

const FName FCustomAssetEditorApp::AppID     = FName("CustomAssetEditor");
const FName FCustomAssetEditorApp::GraphName = FName("CustomAssetGraph");

void FCustomAssetEditorApp::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}

void FCustomAssetEditorApp::InitEditor(const EToolkitMode::Type        InMode,
                                       const TSharedPtr<IToolkitHost>& InitToolkitHost,
                                       UObject*                        InObj)
{
	TArray<UObject*> ObjectsToEdit{};
	ObjectsToEdit.Add(InObj);
	CurrentCustomAsset = Cast<UCustomAsset>(InObj);

	// 初始化自定义图表
	CurrentGraph = FBlueprintEditorUtils::CreateNewGraph(CurrentCustomAsset,
	                                                     GraphName,
	                                                     UEdGraph::StaticClass(),
	                                                     UCustomGraphSchema::StaticClass());
	InitAssetEditor(InMode,
	                InitToolkitHost,
	                AppID,
	                FTabManager::FLayout::NullLayout,
	                true,
	                true,
	                ObjectsToEdit);
	AddApplicationMode(FCustomAssetAppMode::ModID, MakeShareable(new FCustomAssetAppMode(SharedThis(this))));
	SetCurrentMode(FCustomAssetAppMode::ModID);
}

void FCustomAssetEditorApp::UpdateAssetFromGraph()
{
	if (!CurrentGraph || !CurrentCustomAsset) { return; }

	UCustomGraphicRuntime* RuntimeGraph = NewObject<UCustomGraphicRuntime>(CurrentGraph);
	CurrentCustomAsset->Graph           = RuntimeGraph;

	// 当前Graph里每个结点的输出pin所对应的链接的引脚
	TArray<TPair<FGuid, FGuid>> OutputPinConnections{};
	
	// 当前Graph中的每一个结点所对应的运行时引脚
	TMap<FGuid, UCustomGraphicPinRuntime*> IdToRuntimePinMap{};

	// 1.遍历图中的每一个结点
	// 2.创建一个运行时资产结点
	//	2.1 遍历结点的所有引脚
	//		2.1.0 创建一个运行时资产引脚
	//		2.1.1 将输出引脚与其链接的引脚Guid保存到OutputPinConnections
	//		2.1.2 根据当前引脚的ID创建运行时资产引脚放入IdToRuntimePinMap
	//		2.1.3 根据当前引脚是输入还是输出类型来设置 运行时资产结点的InputPin/OutputPins成员
	//	2.2 遍历结束将 运行时资产结点 放入当前资产CurrentCustomAsset->Graph里
	// 3.遍历OutputPinConnections,根据IdToRuntimePinMap里存储的映射关系为运行时资产输出引脚建立和其他引脚的链接关系

	// 遍历编辑器图中的每一个结点
	for (const auto GraphNode : CurrentGraph->Nodes)
	{
		// 当前结点
		auto RuntimeNode          = NewObject<UCustomGraphicNodeRuntime>(CurrentGraph);
		RuntimeNode->NodePosition = FVector2D(GraphNode->NodePosX, GraphNode->NodePosY);

		// 遍历当前结点的所有引脚
		for (const auto GraphPin : GraphNode->Pins)
		{
			auto RuntimePin     = NewObject<UCustomGraphicPinRuntime>(RuntimeNode);
			RuntimePin->PinId   = GraphPin->PinId;
			RuntimePin->PinName = GraphPin->PinName;

			// 当前的输出引脚有链接并且是输出引脚时
			if (GraphPin->HasAnyConnections() && GraphPin->Direction == EGPD_Output)
			{
				// 这里我们的一个输出引脚只会对应链接到一个linked引脚所以是[O] (项目就是这么设置的)
				OutputPinConnections.Emplace(GraphPin->PinId, GraphPin->LinkedTo[0]->PinId);
			}

			// 把每一个引脚和它对应的运行时数据引脚保存起来
			IdToRuntimePinMap.Emplace(GraphPin->PinId, RuntimePin);

			// 当前引脚是输入引脚,当前的[结点]的输入引脚就设置为这个,项目设置一个Node只有一个输入
			if (GraphPin->Direction == EGPD_Input) { RuntimeNode->InputPin = RuntimePin; }
			else
			{
				// 否则当前引脚是输出引脚,则保存入运行时结点的输出引脚
				RuntimeNode->OutputPins.Add(RuntimePin);
			}
		}

		// 保存图结点
		RuntimeGraph->Nodes.Emplace(RuntimeNode);
	}

	// 遍历所有输出引脚的链Map,保存每一个输出引脚的连接关系
	for (auto& Pair : OutputPinConnections)
	{
		// 找到当前为输出引脚的对象
		UCustomGraphicPinRuntime** Pin1 = IdToRuntimePinMap.Find(Pair.Key);
		if (!Pin1) { continue; }

		// 找到输出引脚所连接的引脚的对象
		UCustomGraphicPinRuntime* Pin2 = IdToRuntimePinMap[Pair.Value];
		// 输出引脚真正保存链接的引脚
		(*Pin1)->ConnectionPin         = Pin2;
	}
}

void FCustomAssetEditorApp::UpdateEditorGraphFromAsset()
{
	if (!CurrentGraph || !CurrentCustomAsset) { return; }

	// 当前Graph里每个node引脚的链接,以Guid为唯一标识
	TArray<TPair<FGuid, FGuid>> Connections{};
	
	// Guid对应的[编辑器]引脚数据
	TMap<FGuid, UEdGraphPin*> IdToRuntimePinMap{};

	// 遍历当前保存的资产中图的所有结点
	for (const UCustomGraphicNodeRuntime* AssetRuntimeNode : CurrentCustomAsset->Graph->Nodes)
	{
		if (!AssetRuntimeNode->InputPin ) {continue;}

		// 创建一个新的GraphNode
		const auto RealGraphNode = NewObject<UCustomGraphNode>(CurrentGraph);
		RealGraphNode->CreateNewGuid();
		RealGraphNode->NodePosX = AssetRuntimeNode->NodePosition.X;
		RealGraphNode->NodePosY = AssetRuntimeNode->NodePosition.Y;

		// 创建Node的输入引脚
		const UCustomGraphicPinRuntime* InputPin = AssetRuntimeNode->InputPin;
		UEdGraphPin* RealGraphInputPin = RealGraphNode->CreateCustomGraphPin( EGPD_Input, InputPin->PinName);
		RealGraphInputPin->PinId = InputPin->PinId;

		// 如果输入引脚有连接，则把每一个输入引脚和它链接的引脚保存起来
		if (InputPin->ConnectionPin)
		{
			Connections.Emplace(InputPin->PinId, InputPin->ConnectionPin->PinId);
		}
		IdToRuntimePinMap.Add(InputPin->PinId,RealGraphInputPin);

		// 遍历所有输出引脚
		for (UCustomGraphicPinRuntime* OutputPin : AssetRuntimeNode->OutputPins)
		{
			UEdGraphPin* RealGraphOutputNode = RealGraphNode->CreateCustomGraphPin( EGPD_Output, OutputPin->PinName);
			RealGraphOutputNode->PinId = OutputPin->PinId;
		}
	}
}
