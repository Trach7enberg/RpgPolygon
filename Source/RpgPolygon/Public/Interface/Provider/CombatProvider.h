// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatProvider.generated.h"

class ICombatInterface;

UINTERFACE(MinimalAPI, meta=(CannotImplementInterfaceInBlueprint))
class UCombatProvider : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPGPOLYGON_API ICombatProvider
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="CombatProvider")
	virtual  TScriptInterface<ICombatInterface> GetCombatInterface() = 0;
};
