// Garrett Gan All Right Reserved


#include "Item/Projectile/SpellProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/AudioComponent.h"
#include "FunctionLibrary/PolyFunctionLibrary.h"
#include "Interface/CombatInterface.h"
#include "Interface/Provider/CombatProvider.h"

ASpellProjectile::ASpellProjectile() {}
void ASpellProjectile::BeginPlay() { Super::BeginPlay(); }


void ASpellProjectile::SpawnVfxAndSound() const { Super::SpawnVfxAndSound(); }

void ASpellProjectile::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                            AActor*              OtherActor,
                                            UPrimitiveComponent* OtherComp,
                                            int32                OtherBodyIndex,
                                            bool                 bFromSweep,
                                            const FHitResult&    SweepResult)
{
	if (!OtherActor || !Cast<ICombatProvider>(OtherActor)) { return; }

	DamageEffectParam.TargetAbilitySystemComponent =
			UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor);
	if (OtherActor->GetOwner() && OtherActor->GetOwner() == GetOwner()) { return; }

	if (bIgnoreFriend && UPolyFunctionLibrary::AreActorsFriendly(GetOwner(), OtherActor)) { return; }
	if (!BIsHit) { SpawnVfxAndSound(); }


	if (HasAuthority())
	{
		UPolyFunctionLibrary::ApplyDamageGameplayEffectByProjectileParams(DamageEffectParam);
		
		Destroy();
	}
	else
	{
		// 投射物有可能在还没有生成特效和声音的时候就被销毁了(重叠在服务器上发生,销毁的行为会复制到客户端会导致客户端还没有重叠的时候就销毁了飞弹)
		// 因此我们标记一下当前客户端的投射物已经击中了,然后重写Destroy函数,在被销毁前播放特效和声音
		BIsHit = true;
	}
	
}

void ASpellProjectile::Destroyed()
{
	// 在客户端情况下,快销毁且没有被击中时,播放爆炸特效和声音
	if (!BIsHit && !HasAuthority()) { SpawnVfxAndSound(); }

	if (IsValid(LoopSoundAudioComponent.Get())) { LoopSoundAudioComponent->Stop(); }
	Super::Destroyed();
}

void ASpellProjectile::LifeSpanExpired()
{
	// 生命周期过期时,如果还没有被击中(则播放爆炸特效和声音)
	if (!BIsHit) { SpawnVfxAndSound(); }
	if (IsValid(LoopSoundAudioComponent.Get())) { LoopSoundAudioComponent->Stop(); }
	Super::LifeSpanExpired();
}
