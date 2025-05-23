// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreTypes/PolyCoreStruct.h"

#include "AbilitySys/Abilities/PolyGameplayAbility.h"
#include "Anim/LinkedLayer/PolyLinkedLayerAnimIns.h"

DEFINE_LOG_CATEGORY_STATIC(PolyCoreStruct, All, All);

DEFINE_LOG_CATEGORY_STATIC(PolyCoreStructLog, All, All);

bool FPolyAbilityStruct::IsValid() const { return InputTag.IsValid() && Ability; }

bool FPolyWeaponData::IsValid() const
{
	return WeaponAnimLayerToLink && WeaponInputMappingContext && !WeaponIcon.IsNull();
}

FName FPolyWeaponData::FindSocketNameByTag(const FGameplayTag& InSocketTypeTag) const
{
	const auto Result = TagToSocket.Find(InSocketTypeTag);

	return Result ? *Result : NAME_None;
}

#pragma region FWidgetComponentPool
UWidgetComponent* FWidgetComponentPool::GetWidgetComp(const TSubclassOf<UWidgetComponent>& WidgetComponentClass)
{
	const auto Result = GetOrCreateWidgetComp(WidgetComponentClass);
	UE_LOG(PolyCoreStructLog, Log, TEXT("CreateOrGetPoolElem : %s"), (Result)? *FString("Null"):*Result->GetName());
	return Result;
}

void FWidgetComponentPool::ReleaseWidgetComp(UWidgetComponent* InWidgetComp)
{
	if (!InWidgetComp) { return; }

	// 找到了则释放掉Active,移入InActive
	if (const auto Index = ActiveWidgetComponents.Find(InWidgetComp); Index != INDEX_NONE)
	{
		ActiveWidgetComponents.RemoveAt(Index);
		InActiveWidgetComponents.Push(InWidgetComp);
		SetWidgetCompEnable(InWidgetComp, false);
		UE_LOG(PolyCoreStructLog, Log, TEXT("Release WidgetComp %s"), *InWidgetComp->GetName());
	}
}

void FWidgetComponentPool::ReleaseWidgetComp(const TArray<UWidgetComponent*>& InWidgetComps)
{
	for (const auto& InWidgetComp : InWidgetComps) { ReleaseWidgetComp(InWidgetComp); }
}

void FWidgetComponentPool::SetWidgetCompEnable(UWidgetComponent* InWidgetComp, bool Enable, UObject* NewOuter) const
{
	if (!InWidgetComp)
		return;

	// 1.根据enable 设置新的组件Outer
	InWidgetComp->Rename(nullptr, NewOuter ? NewOuter : OwningWorld.Get());


	// 2.启用的话则挂载到新Owner的身上,并且注册组件
	if (Enable)
	{
		const auto OuterTmp = Cast<AActor>(NewOuter);
		ensureMsgf(OuterTmp, TEXT("%hs WidgetComp Attach Failure"), __FUNCTION__);
		InWidgetComp->AttachToComponent(OuterTmp ? OuterTmp->GetRootComponent() : nullptr,
		                                FAttachmentTransformRules::KeepRelativeTransform);

		InWidgetComp->RegisterComponent();
	}
	else
	{
		InWidgetComp->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
		InWidgetComp->UnregisterComponent();
	}

	// 3.注意SetActive的顺序放到最后
	InWidgetComp->SetVisibility(Enable);
	InWidgetComp->SetHiddenInGame(!Enable);
	InWidgetComp->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	InWidgetComp->SetTickMode(ETickMode::Disabled);
	InWidgetComp->SetComponentTickEnabled(false);
	InWidgetComp->SetActive(Enable);
}


void FWidgetComponentPool::ReleaseAll()
{
	for (auto& Component : ActiveWidgetComponents) { SetWidgetCompEnable(Component, false); }
	InActiveWidgetComponents.Append(ActiveWidgetComponents);
	ActiveWidgetComponents.Empty();
}

void FWidgetComponentPool::ResetPool()
{
	InActiveWidgetComponents.Reset();
	ActiveWidgetComponents.Reset();
}


#pragma endregion

bool FPolyGeContext::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	return FGameplayEffectContext::NetSerialize(Ar, Map, bOutSuccess);
}