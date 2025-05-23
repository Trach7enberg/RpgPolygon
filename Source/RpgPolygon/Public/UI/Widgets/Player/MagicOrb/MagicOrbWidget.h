// Garrett Gan All Right Reserved

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/Player/PlayerWidget.h"
#include "MagicOrbWidget.generated.h"

class UProgressBar;
/**
 * 魔法球基类
 */
UCLASS()
class RPGPOLYGON_API UMagicOrbWidget : public UPlayerWidget
{
	GENERATED_BODY()

public:
	virtual void InitializePolyWidget() override;

	/// 
	/// @param InParamName 
	/// @return 
	UFUNCTION(BlueprintCallable, Category="PolyWidget|MagicOrb")
	float GetMainBarCurrentFillPercentMidValue(const FName InParamName) const;

	/// 
	/// @param InParamName
	/// @param InValue 
	/// @return 
	UFUNCTION(BlueprintCallable, Category="PolyWidget|MagicOrb")
	void SetMainBarCurrentFillPercentMidValue(const FName InParamName, float InValue) const;

	/// @brief 增加主进度条
	/// @param InPercentTarget 
	UFUNCTION(BlueprintCallable, Category="PolyWidget")
	void IncrementMainFillBarGradually(float InPercentTarget);

protected:
	virtual void NativeConstruct() override;
	
	/// MainBar填充材质FillPercent
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PolyWidget|MagicOrb")
	FName Dim_MainBar_FillPercent_ParamName = "_Height";

	/// MainBar填充材质的振幅幅度
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PolyWidget|MagicOrb")
	FName Dim_MainBar_Amptitude_ParamName = "_Amptitude";

	/// 计时器运行的间隔
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PolyWidget|MagicOrb|Timer")
	float Timer_MainBar_FillPercent_LoopTime = .02f;

	/// MainBar填充材质的变化时间间隔
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PolyWidget|MagicOrb|Timer")
	float IncreaseDeltaTime = .1f;

	/// MainBar填充材质的增加速度
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PolyWidget|MagicOrb|Timer")
	float IncreaseInterpSpeed = .5f;

	/// 当角色idle时orb液体的振幅幅度
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PolyWidget|MagicOrb|Timer")
	float FillPercentAmptitudeWhenIdle = .01f;

	/// 当角色没有idle时orb液体的振幅幅度
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="PolyWidget|MagicOrb|Timer")
	float FillPercentAmptitudeWhenNotIdle = .03f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta=(BindWidget))
	TObjectPtr<UProgressBar> PBar_Fill_Main{};

	/// 升级orb中的液体填充值
	UFUNCTION()
	virtual void UpdateMainBarFillPercent();

	/// 平滑orb液体中的振幅幅度
	UFUNCTION()
	virtual void UpdateMainBarFillPercentAmptitude();

private:
	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> MainBarFillPercentMid{nullptr};

	FTimerHandle TimerBarMain{};
	FTimerHandle TimerBarMainAmptitude{};

	float MainFillPercentToCatchUp    = 0.f;
	float CurrentFillPercentAmptitude = .01f;
};
