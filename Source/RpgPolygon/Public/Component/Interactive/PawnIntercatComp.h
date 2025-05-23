// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/PawnExtensionComponentBase.h"
#include "PawnIntercatComp.generated.h"

/**
 * 交互逻辑,物品拾取、开关操作、对话触发等,基本上就是分析左键,只交互和分析,因此可能需要引用装备组件进行装备
 */
UCLASS()
class RPGPOLYGON_API UPawnInteractComp : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
	
};
