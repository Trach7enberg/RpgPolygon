// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim/PolyAnimInstBase.h"

#include "GameplayTagContainer.h"
#include "KismetAnimationLibrary.h"
#include "Character/PolyCharacterBase.h"
#include "FunctionLibrary/PolyFunctionLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"

void UPolyAnimInstBase::NativeInitializeAnimation()
{
	OwningCharacter = Cast<APolyCharacterBase>(TryGetPawnOwner());
	if (!OwningCharacter) { return; }
	OwningMovementComp = OwningCharacter->GetCharacterMovement();
}

void UPolyAnimInstBase::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComp) { return; }

	GroundSpeed      = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComp->Velocity.Size2D() > 0.f;

	// 清除空闲计时
	if (bHasAcceleration)
	{
		IdleElapsedTime        = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		// 开始空闲计时
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = (IdleElapsedTime >= EnterRelaxStateThreshold);
	}


	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(),
	                                                                  OwningCharacter->GetActorRotation());
	bIsFalling = OwningMovementComp->IsFalling();
}	

bool UPolyAnimInstBase::DoesOwnerHasTag(FGameplayTag TagToCheck) const
{
	if (!GetOwningActor() || !TagToCheck.IsValid()) { return false; }
	return UPolyFunctionLibrary::DoseActorHaveTag(GetOwningActor(), TagToCheck);
}
