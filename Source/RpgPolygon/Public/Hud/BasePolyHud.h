// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BasePolyHud.generated.h"


class UPolyGiSubSystem;
class UPolyBaseWidget;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API ABasePolyHud : public AHUD
{
	GENERATED_BODY()

public:
	/// 初始化HUD的主要widget
	void InitHudMainWidget();


protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PolyHud")
	TSubclassOf<UPolyBaseWidget> MainPolyWidgetClass;



private:
	TWeakObjectPtr<UPolyBaseWidget> CurrentMainWidget{};
	TWeakObjectPtr<UPolyGiSubSystem> PolyGiSubSystem{};
};
