// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PolyBaseGameMode.h"

#include "Character/PolyCharacterBase.h"
#include "Controller/Player/PolyController.h"

APolyBaseGameMode::APolyBaseGameMode()
{
	DefaultPawnClass      = APolyCharacterBase::StaticClass();
	PlayerControllerClass = APolyController::StaticClass();
}
