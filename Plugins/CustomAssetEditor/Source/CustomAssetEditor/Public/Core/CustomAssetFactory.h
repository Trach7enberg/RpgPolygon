// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "CustomAssetFactory.generated.h"

/**
 * "内容浏览器中新建某种类型资源时,用来定义该资源怎么创建、能否导入、怎么导入"的一套机制
 * 这里用于定义我们自定义资产类的@see UCustomAsset 创建、导入的逻辑
 */
UCLASS()
class CUSTOMASSETEDITOR_API UCustomAssetFactory : public UFactory
{
	GENERATED_BODY()
public:
	UCustomAssetFactory(const FObjectInitializer & ObjectInitializer);

	virtual bool     CanCreateNew() const override;

	/// 在内容浏览器中“右键 → 新建”一个资产Asset时真正创建资产的逻辑
	/// @param InClass 
	/// @param InParent 
	/// @param InName 
	/// @param Flags 
	/// @param Context 
	/// @param Warn 
	/// @return 
	virtual UObject* FactoryCreateNew(UClass* InClass,
	                                  UObject* InParent,
	                                  FName InName,
	                                  EObjectFlags Flags,
	                                  UObject* Context,
	                                  FFeedbackContext* Warn) override;
};
