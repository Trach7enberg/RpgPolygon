// Garrett Gan All Right Reserved


#include "AbilitySys/Core/PolyAbilitySystemGlobals.h"

#include "CoreTypes/PolyCoreStruct.h"

FGameplayEffectContext* UPolyAbilitySystemGlobals::AllocGameplayEffectContext() const { return new FPolyGeContext(); }

FPolyGeContext* UPolyAbilitySystemGlobals::GetCustomGeContext(FGameplayEffectContext* GeContextHandle)
{
	return static_cast<FPolyGeContext*>(GeContextHandle);
}
