// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Player/PlayerWidget.h"
#include "PlayerMovableWidget.generated.h"

class UCanvasPanelSlot;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UPlayerMovableWidget : public UPlayerWidget
{
	GENERATED_BODY()

public:
	UPlayerMovableWidget();
	virtual void InitializePolyWidget() override;
	
	UFUNCTION(BlueprintCallable, Category="PolyWidget|PlayerMovableWidget")
	virtual void InitMovableCanvasPaneSlotIfValid(UCanvasPanelSlot* InCanvasPanelSlot = nullptr);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PolyWidget|PlayerMovableWidget|Timer")
	float MovingWidget_LoopTime{};

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
	virtual void MovingWidget();

private:
	TWeakObjectPtr<UCanvasPanelSlot> CanvasPanelSlot{};
	FTimerHandle                     TimerHandleMoving;
	FVector2D                        PivotOffset{};
};
