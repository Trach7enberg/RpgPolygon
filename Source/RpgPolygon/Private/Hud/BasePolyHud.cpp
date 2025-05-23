// Fill out your copyright notice in the Description page of Project Settings.


#include "Hud/BasePolyHud.h"

#include "SubSystem/PolyGiSubSystem.h"
#include "UI/Widgets/PolyBaseWidget.h"


DEFINE_LOG_CATEGORY_STATIC(BasePolyHudLog, All, All);

void ABasePolyHud::InitHudMainWidget()
{
	if (!MainPolyWidgetClass || !GetOwningPlayerController())
	{
		UE_LOG(BasePolyHudLog, Warning, TEXT("Main Hud widget class cant be null!"));
		return;
	}
	const auto TmpOwner = GetOwningPlayerController()->GetPawn();

	if (!TmpOwner) { return; }
	const auto Gi = TmpOwner->GetGameInstance();
	if (!Gi) { return; }

	PolyGiSubSystem = Gi->GetSubsystem<UPolyGiSubSystem>();
	if (!PolyGiSubSystem.IsValid())
	{
		UE_LOG(BasePolyHudLog, Error, TEXT("Cant Init Hud !"));
		return;
	}
	CurrentMainWidget = CreateWidget<UPolyBaseWidget>(GetOwningPlayerController(), MainPolyWidgetClass);
	CurrentMainWidget.Get()->InitializePolyWidget();
	CurrentMainWidget->AddToViewport();
}

void ABasePolyHud::BeginPlay() { Super::BeginPlay(); }
