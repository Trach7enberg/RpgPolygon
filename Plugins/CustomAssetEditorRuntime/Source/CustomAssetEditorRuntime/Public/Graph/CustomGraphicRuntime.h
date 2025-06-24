// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "CustomGraphicRuntime.generated.h"

/**
 * 运行时自定义图pin脚数据
 */
UCLASS()
class CUSTOMASSETEDITORRUNTIME_API UCustomGraphicPinRuntime : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName PinName{};

	UPROPERTY()
	FGuid PinId{};

	/// 当前引脚所连接的引脚
	UPROPERTY()
	TObjectPtr<UCustomGraphicPinRuntime> ConnectionPin{};
};

/**
 * 运行时自定义图结点数据
 */
UCLASS()
class CUSTOMASSETEDITORRUNTIME_API UCustomGraphicNodeRuntime : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	TObjectPtr<UCustomGraphicPinRuntime> InputPin{};

	UPROPERTY()
	TArray<UCustomGraphicPinRuntime*> OutputPins{};

	UPROPERTY()
	FVector2D NodePosition{};
};

/**
 * 运行时自定义图的数据(多个)
 */
UCLASS()
class CUSTOMASSETEDITORRUNTIME_API UCustomGraphicRuntime : public UObject
{
	GENERATED_BODY()

public:
	/// 图结点数组
	UPROPERTY()
	TArray<UCustomGraphicNodeRuntime*> Nodes{};
};
