// Garrett Gan All Right Reserved


#include "PlayerStates/PlayerStateBase.h"

#include "AbilitySystemComponent.h"
#include "AbilitySys/Core/PolyAbilitySysComp.h"
#include "AbilitySys/Core/PolyAttributeSet.h"
#include "SubSystem/PolyGiSubSystem.h"

APlayerStateBase::APlayerStateBase()
{
	// 当玩家状态在服务器上发生变化时,服务器就会发送更新到所有客户端 这个值就是设置服务器发送更新到所有客户端的频率
	// 但是当玩家状态有GAS系统的组件时,这个值要设置高(慢)一点
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UPolyAbilitySysComp>("PolyAsc");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UPolyAttributeSet>("PolyAs");
}

UAbilitySystemComponent* APlayerStateBase::GetAbilitySystemComponent() const { return AbilitySystemComponent; }

void APlayerStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

UPolyGiSubSystem* APlayerStateBase::GetGiSubSystem()
{
	if (!PolyGiSubSystem)
	{
		if (!GetGameInstance()) { return nullptr; }
		PolyGiSubSystem = Cast<UPolyGiSubSystem>(
		                                         GetGameInstance()->GetSubsystem<UPolyGiSubSystem>());
	}
	return PolyGiSubSystem;
}
