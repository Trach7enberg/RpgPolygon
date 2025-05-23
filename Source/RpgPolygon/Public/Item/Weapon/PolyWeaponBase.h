// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreTypes/PolyCoreStruct.h"
#include "GameFramework/Actor.h"
#include "PolyWeaponBase.generated.h"

class USkeletalMeshComponent;
class UTimelineComponent;
class UPolyAbilitySysComp;
class UBoxComponent;

UCLASS()
class RPGPOLYGON_API APolyWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	APolyWeaponBase();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	FOnWeaponOverlapDelegate OnWeaponBeginOverlapDelegate;
	FOnWeaponOverlapDelegate OnWeaponEndOverlapDelegate;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Replicated, ReplicatedUsing=OnRep_WeaponMesh, Category="Weapons")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh{};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapons")
	TObjectPtr<UBoxComponent> WeaponCollisionBox{};


	void EnableCollision(bool Enabled) const;

	void DestroyWeapon();

	/// 获取武器信息
	/// @return 
	FORCEINLINE FPolyWeaponData GetWeaponData() const { return WeaponData; }

	FORCEINLINE float GetWeaponDataBaseDamage(float InAbilityLevel = 1) const;

	/// 返回武器碰撞盒
	/// @return 
	FORCEINLINE TObjectPtr<UBoxComponent> GetWeaponCollisionBox() const { return WeaponCollisionBox; }

	/// 获取武器插槽
	/// @param InSocketTypeTag 
	/// @return 
	FVector GetWeaponSocketLocByTag(const FGameplayTag& InSocketTypeTag);

protected:
	virtual void BeginPlay() override;

	/// 武器信息
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapons")
	FPolyWeaponData WeaponData;

	/// 
	/// @return 
	TObjectPtr<UPolyAbilitySysComp> GetOwnerAsc();


	void InitialDissolveTimeline();
	void StartDissolveTimeline();

private:
	UPROPERTY()
	bool bIsOverlap = false;


	UPROPERTY()
	TObjectPtr<UPolyAbilitySysComp> OwnerAsc{};

	UPROPERTY()
	TObjectPtr<UTimelineComponent> DissolveTimeLineComp;

	UFUNCTION()
	void OnDissolveTimelineUpdate(float Value);

	UFUNCTION()
	void OnDissolveTimelineFinished();

	UFUNCTION()
	virtual void OnWeaponBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                                  AActor*              OtherActor,
	                                  UPrimitiveComponent* OtherComp,
	                                  int32                OtherBodyIndex,
	                                  bool                 bFromSweep,
	                                  const FHitResult&    SweepResult);

	UFUNCTION()
	virtual void OnEndWeaponOverlap(UPrimitiveComponent* OverlappedComponent,
	                                AActor*              OtherActor,
	                                UPrimitiveComponent* OtherComp,
	                                int32                OtherBodyIndex);


	UFUNCTION()
	virtual void OnRep_WeaponMesh(USkeletalMeshComponent* OldValue);
};
