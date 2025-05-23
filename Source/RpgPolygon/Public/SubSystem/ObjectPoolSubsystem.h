// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes/PolyCoreStruct.h"
#include "Subsystems/WorldSubsystem.h"
#include "ObjectPoolSubsystem.generated.h"

class UWidgetComponent;
struct FWidgetComponentPool;
struct FActorPool;


/**
 * 池管理子系统
 */
UCLASS()
class RPGPOLYGON_API UObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	/// 创建 WidgetComp
	/// @param InWidgetCompClass 
	/// @return 
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="WorldSubSys|WidgetCompPool")
	UWidgetComponent* CreateOrGetPoolElem(const TSubclassOf<UWidgetComponent>& InWidgetCompClass, UObject* NewOwner);

	/// 释放 InWidgetComp 到对象池
	/// @param InWidgetComp 
	UFUNCTION(BlueprintCallable, Category="WorldSubSys|WidgetCompPool")
	void ReleasePoolElem(UWidgetComponent* InWidgetComp);

	/// 释放 给定的 InWidgetComps 到对象池
	/// @param InWidgetComps 
	UFUNCTION(BlueprintCallable, Category="WorldSubSys|WidgetComPool")
	void ReleasePoolElems(TArray<UWidgetComponent*> InWidgetComps);

	/// 重置池
	/// @param InWidgetCompClass 
	UFUNCTION(BlueprintCallable, Category="WorldSubSys|WidgetCompPool")
	void ResetPool(TSubclassOf<UWidgetComponent> InWidgetCompClass);

protected:
	virtual void PostInitialize() override;

private:
	UPROPERTY()
	FWidgetComponentPool WidgetComponentPool{};
};
