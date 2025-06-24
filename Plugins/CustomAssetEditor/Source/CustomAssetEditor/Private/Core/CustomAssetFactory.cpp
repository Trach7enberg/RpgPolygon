// Garrett Gan All Right Reserved


#include "Core/CustomAssetFactory.h"

#include "Core/CustomAsset.h"

UCustomAssetFactory::UCustomAssetFactory(const FObjectInitializer & ObjectInitializer):Super(ObjectInitializer)
{
	SupportedClass = UCustomAsset::StaticClass();
}

bool UCustomAssetFactory::CanCreateNew() const { return true; }

UObject* UCustomAssetFactory::FactoryCreateNew(UClass*           InClass,
                                               UObject*          InParent,
                                               FName             InName,
                                               EObjectFlags      Flags,
                                               UObject*          Context,
                                               FFeedbackContext* Warn)
{
	return NewObject<UCustomAsset>(InParent, InName, Flags);
}
