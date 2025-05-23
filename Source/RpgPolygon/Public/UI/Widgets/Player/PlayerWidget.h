// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/PolyBaseWidget.h"
#include "PlayerWidget.generated.h"

class UPolyUiComp;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UPlayerWidget : public UPolyBaseWidget
{
	GENERATED_BODY()


public:
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="PolyWidget|Player")
	UPolyUiComp* GetOwningPlayerUIComponent();

private:
	UPROPERTY()
	TSoftObjectPtr<UPolyUiComp> PlayerUiComp;
};
