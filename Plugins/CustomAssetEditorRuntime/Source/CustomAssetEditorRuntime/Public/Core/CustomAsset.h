// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "CustomAsset.generated.h"

class UCustomGraphicRuntime;
/**
 * 自定义资产类的数据
 */
UCLASS(BlueprintType)
class CUSTOMASSETEDITORRUNTIME_API UCustomAsset : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FString SomeData{};

	UPROPERTY(EditAnywhere)
	int32 SomeNumber{};

	UPROPERTY(EditAnywhere)
	bool SomeBool{};

	/// 保存编辑器打开图表后的自定义资产图表数据
	UPROPERTY()
	TObjectPtr<UCustomGraphicRuntime> Graph{};

	virtual FString ToString();
};
