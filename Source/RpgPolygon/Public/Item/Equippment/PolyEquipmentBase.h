// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PolyEquipmentBase.generated.h"

/**
 * 
 */
UCLASS()
class RPGPOLYGON_API APolyEquipmentBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APolyEquipmentBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
