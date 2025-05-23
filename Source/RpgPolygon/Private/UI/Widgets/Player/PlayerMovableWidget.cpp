// Garrett Gan All Right Reserved


#include "UI/Widgets/Player/PlayerMovableWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(PlayerMovableWidgeLog, All, All);

UPlayerMovableWidget::UPlayerMovableWidget() { MovingWidget_LoopTime = .02f; }

void UPlayerMovableWidget::InitializePolyWidget()
{
	if (GetWorld())
	{
		FTimerDynamicDelegate Delegate{};
		Delegate.BindDynamic(this, &ThisClass::MovingWidget);
		TimerHandleMoving = UKismetSystemLibrary::K2_SetTimerDelegate(Delegate,
		                                                              MovingWidget_LoopTime,
		                                                              true,
		                                                              true);
		UKismetSystemLibrary::K2_PauseTimerHandle(GetWorld(), TimerHandleMoving);
	}
	Super::InitializePolyWidget();
}

void UPlayerMovableWidget::InitMovableCanvasPaneSlotIfValid(UCanvasPanelSlot* InCanvasPanelSlot)
{
	if (InCanvasPanelSlot) { CanvasPanelSlot = InCanvasPanelSlot; }
}

FReply UPlayerMovableWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	//TODO 待完善,目前只能用左键响应拖拽 widget 
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		const auto InMousePositionOnViewport = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
		// 如果不是被canvas包裹,则Moving修改的是render,否则修改的是widget的位置
		PivotOffset = CanvasPanelSlot.IsValid()
			              ? InMousePositionOnViewport - CanvasPanelSlot->GetPosition()
			              : InMousePositionOnViewport - GetRenderTransform().Translation;

		UKismetSystemLibrary::K2_UnPauseTimerHandle(GetWorld(), TimerHandleMoving);
		UE_LOG(PlayerMovableWidgeLog, Log, TEXT("UnPause TimerHandleMoving"));
	}
	return Super::NativeOnMouseButtonDown(InGeometry,  InMouseEvent);
}

FReply UPlayerMovableWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		UKismetSystemLibrary::K2_PauseTimerHandle(GetWorld(), TimerHandleMoving);
		UE_LOG(PlayerMovableWidgeLog, Log, TEXT("Pause TimerHandleMoving"));
	}
	return Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
}

void UPlayerMovableWidget::MovingWidget()
{
	const auto MovingLoc = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld()) - PivotOffset;

	if (CanvasPanelSlot.IsValid()) { CanvasPanelSlot->SetPosition(MovingLoc); }
	else { SetRenderTranslation(MovingLoc); }
}
