// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Item/Projectile/PolyProjectileBase.h"
#include "SpellProjectile.generated.h"

/**
 * 基础法术飞弹类
 */
UCLASS()
class RPGPOLYGON_API ASpellProjectile : public APolyProjectileBase
{
	GENERATED_BODY()

public:
	ASpellProjectile();

protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void LifeSpanExpired() override;

	/// 当前投射物有没有Overlap
	bool BIsHit = false;

	virtual void SpawnVfxAndSound() const override;

private:
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                                  AActor*              OtherActor,
	                                  UPrimitiveComponent* OtherComp,
	                                  int32                OtherBodyIndex,
	                                  bool                 bFromSweep,
	                                  const FHitResult&    SweepResult) override;
};
