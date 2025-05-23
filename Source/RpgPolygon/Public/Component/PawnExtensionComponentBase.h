// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPGPOLYGON_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UPawnExtensionComponentBase();

	/// 初始化组件
	virtual void InitializePawnComponent();

protected:
	template <class T = APawn>
	T* GetOwningPawn() const
	{
		// 编译时静态断言T必须是APawn的子类,即From(T)必须可以转换为To(APawn)
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "T must inherit from APawn");
		return Cast<T>(GetOwner());
	}

	template <class T=AController>
	T* GetOwningController() const
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "T must inherit from AController");

		const auto InCon = GetOwningPawn();
		auto       Res   = InCon ? InCon->GetController<T>() : nullptr;

		return Res;
	}

	APawn* GetOwningPawn()
	{
		if (!OwningPawn.Get()) { OwningPawn = GetOwningPawn<APawn>(); }
		return OwningPawn.Get();
	}

	AController* GetOwningController()
	{
		if (!OwningController.Get()) { OwningController = GetOwningController<AController>(); }
		return OwningController.Get();
	}

private:
	TWeakObjectPtr<AController> OwningController;
	TWeakObjectPtr<APawn>       OwningPawn;
};
