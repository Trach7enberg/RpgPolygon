// Garrett Gan All Right Reserved


#include "RpgPolygon/Public/AbilitySys/Abilities/Offensive/Spell/SpellProjectileGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "FunctionLibrary/PolyFunctionLibrary.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interface/Provider/CombatProvider.h"
#include "Item/Projectile/PolyProjectileBase.h"

DEFINE_LOG_CATEGORY_STATIC(SpellProjectileGameplayAbilityLog, All, All);

USpellProjectileGameplayAbility::USpellProjectileGameplayAbility()
{
	NonHomingTarget = CreateDefaultSubobject<USceneComponent>("NonHomingTarget");
}

void USpellProjectileGameplayAbility::SpawnProjectile(const FHitResult& HitResult,
                                                      FVector           InAttackSocketLoc)
{
	// 飞弹能力(投射物)仅在服务器上生成 , 世界正在摧毁也不能生成
	if (!GetAvatarActorFromActorInfo() || !GetAvatarActorFromActorInfo()->HasAuthority() || !GetWorld()) { return; }

	if (!GetOwningActorFromActorInfo() || !GetAbilitySystemComponentFromActorInfo())
	{
		UE_LOG(SpellProjectileGameplayAbilityLog, Error, TEXT("%hs Actor信息获取失败!"), __FUNCTION__);
		return;
	}

	// Instigator : 引发者就是引发我们正在进行的事情的角色 , 必须是Pawn
	const auto Instigator = Cast<APawn>(GetAvatarActorFromActorInfo());
	if (!Instigator) { return; }


	FTransform Transform;
	const auto AttackSocketLoc = InAttackSocketLoc;
	Transform.SetLocation(AttackSocketLoc);

	// 射弹朝向
	const FRotator Rotation = (HitResult.ImpactPoint - AttackSocketLoc).Rotation();

	// 飞弹的倾斜度是与地面平行
	// Rotation.Pitch = 0.f;
	Transform.SetRotation(Rotation.Quaternion());


	// 完成飞弹生成
	if (const auto Projectile = CreateProjectile(Transform, Instigator)) { Projectile->FinishSpawning(Transform); }
}

void USpellProjectileGameplayAbility::SpawnProjectiles(const FHitResult& HitResult,
                                                       FVector           InAttackSocketLoc,
                                                       AActor*           HomingActor,
                                                       bool              bOverridePitch,
                                                       float             OverridePitch)
{
	// 飞弹能力(投射物)仅在服务器上生成,世界正在摧毁也不能生成
	if (!GetAvatarActorFromActorInfo() || !GetAvatarActorFromActorInfo()->HasAuthority() || !GetWorld()) { return; }

	if (!GetOwningActorFromActorInfo() || !GetAvatarActorFromActorInfo() || !GetAbilitySystemComponentFromActorInfo())
	{
		UE_LOG(SpellProjectileGameplayAbilityLog, Error, TEXT("%hs Actor信息获取失败!"), __FUNCTION__);
		return;
	}

	// Instigate : 引发者就是引发我们正在进行的事情的角色 , 必须是Pawn
	const auto Instigator = Cast<APawn>(GetAvatarActorFromActorInfo());
	if (!Instigator) { return; }

	if (const auto CombatInterProvider = Cast<ICombatProvider>(GetAvatarActorFromActorInfo()); !CombatInterProvider)
	{
		UE_LOG(SpellProjectileGameplayAbilityLog, Error, TEXT("%hs 转换失败!"), __FUNCTION__);
		return;
	}

	FTransform Transform;
	const auto AttackSocketLoc = InAttackSocketLoc;
	Transform.SetLocation(AttackSocketLoc);

	// 计算射弹朝向
	FRotator Rotation = (HitResult.ImpactPoint - AttackSocketLoc).Rotation();
	if (bOverridePitch) { Rotation.Pitch = OverridePitch; }

	const auto      ForwardVector = Rotation.Vector();
	const auto      ProjNum       = FMath::Max(1, GetAbilityLevel());
	TArray<FVector> Directions;
	UPolyFunctionLibrary::GetVectorBySpread(SpawnSpread, ProjNum, ForwardVector, Directions);
	auto Random = FMath::RandRange(1, Directions.Num());
	for (auto& Dire : Directions)
	{
		--Random;
		FTransform SpawnTrans;
		SpawnTrans.SetLocation(AttackSocketLoc);

		auto Rot = Dire.Rotation();
		SpawnTrans.SetRotation(Rot.Quaternion());

		const auto Projectile = CreateProjectile(SpawnTrans, Instigator);
		if (!Projectile) { continue; }

		const auto ProjComp = Projectile->GetProjectileMovementComponent();
		if (!ProjComp) { continue; }
		ProjComp->ProjectileGravityScale = ProjectileGravity;
		if (bIsHomingProjectile && HomingActor && HomingActor->Implements<UCombatProvider>())
		{
			ProjComp->HomingTargetComponent = HomingActor->GetRootComponent();
			Projectile->RegisterHomingActorOnMissingEvent();
		}
		else
		{
			NonHomingTarget->SetWorldLocation(HitResult.ImpactPoint);
			ProjComp->HomingTargetComponent = NonHomingTarget;
		}
		ProjComp->HomingAccelerationMagnitude = FMath::RandRange(HomingMinAcceleration, HomingMaxAcceleration);
		ProjComp->bIsHomingProjectile         = bIsHomingProjectile;

		// 完成飞弹生成
		Projectile->FinishSpawning(SpawnTrans);
	}
}

void USpellProjectileGameplayAbility::MakeProjectileDamageEffectParamsFromAbilityDefaults(
	FPolyProjectileDamageEffectParam& OutParam,
	AActor*                           Target) const
{
	// OutParam.BaseDamage = OutParam.RadiusDamageFallOffFactor * GetEstimatedDamageFromDamageTypesMap(GetAbilityLevel());

	OutParam.AbilityLevel                 = GetAbilityLevel();
	OutParam.WorldContextObject           = GetAvatarActorFromActorInfo();
	OutParam.DamageGameplayEffectClass    = DamageEffectClass;
	OutParam.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	OutParam.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
}

void USpellProjectileGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle     Handle,
                                                      const FGameplayAbilityActorInfo*     ActorInfo,
                                                      const FGameplayAbilityActivationInfo ActivationInfo,
                                                      const FGameplayEventData*            TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

APolyProjectileBase* USpellProjectileGameplayAbility::CreateProjectile(const FTransform& Transform,
                                                                       APawn*            Instigator) const
{
	if (!ProjectileClass.Get() || !DamageEffectClass)
	{
		UE_LOG(SpellProjectileGameplayAbilityLog, Error, TEXT("GE Class不能为nullptr!"));
		return nullptr;
	}
	// 生成一个延迟调用BeginPlay的飞弹
	const auto Projectile = GetWorld()->SpawnActorDeferred<APolyProjectileBase>(
	                                                                            ProjectileClass.Get(),
	                                                                            Transform,
	                                                                            GetAvatarActorFromActorInfo(),
	                                                                            Instigator,
	                                                                            ESpawnActorCollisionHandlingMethod::AlwaysSpawn);


	if (IsValid(Projectile))
	{
		MakeProjectileDamageEffectParamsFromAbilityDefaults(Projectile->DamageEffectParam, nullptr);
	}
	else { UE_LOG(SpellProjectileGameplayAbilityLog, Error, TEXT("[%s]生成飞弹失败!"), *GetName()); }
	return Projectile;
}
