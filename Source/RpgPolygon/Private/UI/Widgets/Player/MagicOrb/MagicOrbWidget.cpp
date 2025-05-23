// Garrett Gan All Right Reserved


#include "UI/Widgets/Player/MagicOrb/MagicOrbWidget.h"

#include "Component/UI/PolyUiComp.h"
#include "Components/ProgressBar.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RpgPolygon/RpgPolygon.h"

DEFINE_LOG_CATEGORY_STATIC(MagicOrbWidgetLog, All, All);

void UMagicOrbWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (PBar_Fill_Main)
	{
		// bar的填充比需要填满,我们是通过材质来设置填充比例,因此无关紧要
		PBar_Fill_Main->SetPercent(1.f);
		auto MainBarStyle = PBar_Fill_Main->GetWidgetStyle();
 
		UObject* FillImageBrush = MainBarStyle.FillImage.GetResourceObject();

		if (const auto Mi = Cast<UMaterialInterface>(FillImageBrush))
		{
			MainBarFillPercentMid = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), Mi);
			MainBarStyle.FillImage.SetResourceObject(MainBarFillPercentMid);
			PBar_Fill_Main->SetWidgetStyle(MainBarStyle);
		}
	}

	if (GetWorld())
	{
		FTimerDynamicDelegate DelegateMainBarFillPercent{};
		FTimerDynamicDelegate DelegateMainBarFillPercentAmptitude{};
		DelegateMainBarFillPercent.BindDynamic(this, &ThisClass::UpdateMainBarFillPercent);
		DelegateMainBarFillPercentAmptitude.BindDynamic(this, &ThisClass::UpdateMainBarFillPercentAmptitude);
		TimerBarMain = UKismetSystemLibrary::K2_SetTimerDelegate(DelegateMainBarFillPercent,
		                                                         Timer_MainBar_FillPercent_LoopTime,
		                                                         true,
		                                                         true);
		TimerBarMainAmptitude =
				UKismetSystemLibrary::K2_SetTimerDelegate(DelegateMainBarFillPercentAmptitude,
				                                          Timer_MainBar_FillPercent_LoopTime,
				                                          true,
				                                          true);
		UKismetSystemLibrary::K2_PauseTimerHandle(GetWorld(), TimerBarMain);
		UKismetSystemLibrary::K2_PauseTimerHandle(GetWorld(), TimerBarMainAmptitude);
	}
}

void UMagicOrbWidget::InitializePolyWidget()
{
	if (!GetOwningPlayerUIComponent())
	{
		UE_LOG(MagicOrbWidgetLog, Error, TEXT("Initialize MagicOrb Failed"));
		return;
	}
	GetOwningPlayerUIComponent()->OnMovingChangeDelegateDelegate.AddLambda([this](bool bIsMoving)
	{
		CurrentFillPercentAmptitude = bIsMoving
			                              ? FillPercentAmptitudeWhenNotIdle
			                              : FillPercentAmptitudeWhenIdle;
		UKismetSystemLibrary::K2_UnPauseTimerHandle(GetWorld(), TimerBarMainAmptitude);
	});
	Super::InitializePolyWidget();
}

float UMagicOrbWidget::GetMainBarCurrentFillPercentMidValue(const FName InParamName) const
{
	if (!PBar_Fill_Main || InParamName.IsNone()) { return 0.f; }
	return MainBarFillPercentMid->K2_GetScalarParameterValue(InParamName);
}

void UMagicOrbWidget::SetMainBarCurrentFillPercentMidValue(const FName InParamName, const float InValue) const
{
	if (!PBar_Fill_Main || InParamName.IsNone()) { return; }
	MainBarFillPercentMid->SetScalarParameterValue(InParamName, InValue);
}

void UMagicOrbWidget::IncrementMainFillBarGradually(const float InPercentTarget)
{
	MainFillPercentToCatchUp = InPercentTarget;
	UKismetSystemLibrary::K2_UnPauseTimerHandle(GetWorld(), TimerBarMain);
}

void UMagicOrbWidget::UpdateMainBarFillPercent()
{
	const auto CurrentFillPercent = GetMainBarCurrentFillPercentMidValue(Dim_MainBar_FillPercent_ParamName);
	if (FMath::IsNearlyEqual(CurrentFillPercent, MainFillPercentToCatchUp, 0.01f))
	{
		UKismetSystemLibrary::K2_PauseTimerHandle(GetWorld(), TimerBarMain);
		UE_LOG(MagicOrbWidgetLog, Log, TEXT("%hs %s Update Fill Percent Done."), __FUNCTION__, *GetNameSafe(this));
	}

	const float Result = FMath::FInterpTo(CurrentFillPercent,
	                                      MainFillPercentToCatchUp,
	                                      IncreaseDeltaTime,
	                                      IncreaseInterpSpeed);
	SetMainBarCurrentFillPercentMidValue(Dim_MainBar_FillPercent_ParamName, Result);
}

void UMagicOrbWidget::UpdateMainBarFillPercentAmptitude()
{
	const auto CurrentAmptitudeValue = GetMainBarCurrentFillPercentMidValue(Dim_MainBar_Amptitude_ParamName);

	if (FMath::IsNearlyEqual(CurrentAmptitudeValue, CurrentFillPercentAmptitude, 0.001f))
	{
		UKismetSystemLibrary::K2_PauseTimerHandle(GetWorld(), TimerBarMainAmptitude);
		UE_LOG(MagicOrbWidgetLog, Log, TEXT("%hs %s Update Amptitude Done."), __FUNCTION__, *GetNameSafe(this));
	}
	const float Result = FMath::FInterpTo(CurrentAmptitudeValue,
	                                      CurrentFillPercentAmptitude,
	                                      IncreaseDeltaTime,
	                                      IncreaseInterpSpeed);
	MainBarFillPercentMid->SetScalarParameterValue(Dim_MainBar_Amptitude_ParamName, Result);
}
