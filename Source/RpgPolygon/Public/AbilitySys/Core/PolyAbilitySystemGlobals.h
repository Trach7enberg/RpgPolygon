// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "PolyAbilitySystemGlobals.generated.h"

struct FPolyGeContext;
/**
 * 当前项目控制AbilitySys的数据类
 */
UCLASS()
class RPGPOLYGON_API UPolyAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()

public:
	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;

	static FPolyGeContext* GetCustomGeContext(FGameplayEffectContext* GeContextHandle);
};
