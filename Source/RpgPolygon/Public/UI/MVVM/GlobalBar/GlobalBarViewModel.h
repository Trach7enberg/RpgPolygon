// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "UI/MVVM/PolyMvvmBase.h"
#include "GlobalBarViewModel.generated.h"

/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UGlobalBarViewModel : public UPolyMvvmBase
{
	GENERATED_BODY()

public:
	float GetCurrentLiquidValue() const { return CurrentLiquidValue; }
	float GetMaxLiquidValue() const { return MaxLiquidValue; }


	void SetMaxLiquidValue(const float InMaxLiquidValue)
	{
		UE_MVVM_SET_PROPERTY_VALUE(MaxLiquidValue, InMaxLiquidValue);
	}

	void SetCurrentLiquidValue(const float InCurrentLiquidValue)
	{
		UE_MVVM_SET_PROPERTY_VALUE(CurrentLiquidValue, InCurrentLiquidValue);
	}

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(Allowprivateaccess="true"))
	float CurrentLiquidValue{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta=(Allowprivateaccess="true"))
	float MaxLiquidValue{};
};
