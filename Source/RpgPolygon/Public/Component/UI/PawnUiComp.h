// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponentBase.h"
#include "PawnUiComp.generated.h"

class APolyCharacterBase;
class UPolyAbilitySysComp;
/**
 * 
 */
UCLASS()
class RPGPOLYGON_API UPawnUiComp : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	/// 初始化当前UI组件
	virtual void InitialUiComponent();

protected:
	UPolyAbilitySysComp*        GetPolyAbilitySysComp();
	virtual APolyCharacterBase* GetOwnerCharacter();

private:
	TWeakObjectPtr<UPolyAbilitySysComp> PolyAsc{};
	TWeakObjectPtr<APolyCharacterBase>  OwnerCharacter{};
};
