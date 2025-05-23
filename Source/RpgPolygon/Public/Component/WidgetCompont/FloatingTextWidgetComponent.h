// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "FloatingTextWidgetComponent.generated.h"

/**
 * 浮动文字
 */
UCLASS()
class RPGPOLYGON_API UFloatingTextWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFloatingTextWidgetComponent();

	virtual void InitializeComponent() override;
	/// 开始浮动
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="FloatingText")
	void BeginFloating();

	/// 设置主文本(如伤害数字)
	/// @param DamageText 
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="FloatingText")
	void SetFloatingStr(const FString& DamageText);

	/// 设置额外的消息文本(比如暴击、格挡)
	/// @param MessageText 
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="FloatingText")
	void SetExtraStr(const FString& MessageText);

	/// 设置主文本的颜色
	/// @param NewColor 
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="FloatingText")
	void SetFloatingStrColor(FLinearColor NewColor);

	/// 设置额外消息的文本颜色
	/// @param NewColor 
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category="FloatingText")
	void SetExtraStrColor(FLinearColor NewColor);
};
