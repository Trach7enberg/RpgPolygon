// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "PlayerStateBase.generated.h"

class UAttributeSet;
class UPolyGiSubSystem;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API APlayerStateBase : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	APlayerStateBase();
	// ~ IAbilitySystemInterface Begin
	virtual UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// ~ IAbilitySystemInterface End

		/// 设置要进行网络复制的属性
	/// @param OutLifetimeProps 
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	/// GAS的能力组件
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	/// GAS的属性集
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;

private:

	UPROPERTY()
	TObjectPtr<UPolyGiSubSystem> PolyGiSubSystem = nullptr;

	UPolyGiSubSystem* GetGiSubSystem();
};
