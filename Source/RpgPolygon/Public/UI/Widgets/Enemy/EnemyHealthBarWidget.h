// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Enemy/EnemyWidget.h"
#include "EnemyHealthBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UEnemyHealthBarWidget : public UEnemyWidget
{
	GENERATED_BODY()

public:
	virtual void InitializePolyWidget() override;

};
