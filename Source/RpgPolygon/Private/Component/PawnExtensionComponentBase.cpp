 // Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PawnExtensionComponentBase.h"

UPawnExtensionComponentBase::UPawnExtensionComponentBase()
{
	PrimaryComponentTick.bCanEverTick = false;

}

 void UPawnExtensionComponentBase::InitializePawnComponent()
{
	// 子类实现
}
