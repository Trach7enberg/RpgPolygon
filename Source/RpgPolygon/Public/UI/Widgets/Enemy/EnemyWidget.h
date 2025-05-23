// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/PolyBaseWidget.h"
#include "EnemyWidget.generated.h"

class UEnemyUiComp;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UEnemyWidget : public UPolyBaseWidget
{
	GENERATED_BODY()

public:
	
	/// 初始化widget
	virtual void InitializePolyWidget() override;

	virtual void InitializePolyWidget(UEnemyUiComp* InEnemyUiComp);


	UFUNCTION(BlueprintCallable, BlueprintPure, Category="PolyWidget|Enemy")
	UEnemyUiComp* GetOwningEnemyUIComponent();

private:
	UPROPERTY()
	TSoftObjectPtr<UEnemyUiComp> EnemyUiComp;

};
