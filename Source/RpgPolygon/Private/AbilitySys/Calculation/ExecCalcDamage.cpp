// Garrett Gan All Right Reserved


#include "AbilitySys/Calculation/ExecCalcDamage.h"

#include "AbilitySys/Core/PolyAttributeSet.h"

struct FAttributeCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Intelligence)

	DECLARE_ATTRIBUTE_CAPTUREDEF(FireResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(LightingResistance)
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArcaneResistance)

	FAttributeCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPolyAttributeSet, Armor, Target, false);                 // 捕获目标的护甲属性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPolyAttributeSet, BlockChance, Target, false);           // 捕获目标的格挡属性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPolyAttributeSet, ArmorPenetration, Target, false);      // 捕获目标的护甲穿透属性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPolyAttributeSet, CriticalHitChance, Source, false);     // 捕获源 的暴击率
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPolyAttributeSet, CriticalHitDamage, Source, false);     // 捕获源 的暴击伤害
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPolyAttributeSet, CriticalHitResistance, Target, false); // 捕获 目标的暴击抵抗率
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPolyAttributeSet, Intelligence, Source, false);          // 捕获 源的智力值

		DEFINE_ATTRIBUTE_CAPTUREDEF(UPolyAttributeSet, FireResistance, Target, false);     // 捕获目标的火焰抗性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPolyAttributeSet, PhysicalResistance, Target, false); // 捕获目标的物理抗性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPolyAttributeSet, LightingResistance, Target, false); // 捕获目标的雷电抗性
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPolyAttributeSet, ArcaneResistance, Target, false);   // 捕获目标的奥术 抗性
	}
};

static const FAttributeCapture& GetAttributeCapture()
{
	static FAttributeCapture AttributeCapture;
	return AttributeCapture;
}

UExecCalcDamage::UExecCalcDamage()
{
	RelevantAttributesToCapture.Add(GetAttributeCapture().ArmorDef);
	RelevantAttributesToCapture.Add(GetAttributeCapture().BlockChanceDef);
	RelevantAttributesToCapture.Add(GetAttributeCapture().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(GetAttributeCapture().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(GetAttributeCapture().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(GetAttributeCapture().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(GetAttributeCapture().IntelligenceDef);

	RelevantAttributesToCapture.Add(GetAttributeCapture().FireResistanceDef);
	RelevantAttributesToCapture.Add(GetAttributeCapture().PhysicalResistanceDef);
	RelevantAttributesToCapture.Add(GetAttributeCapture().LightingResistanceDef);
	RelevantAttributesToCapture.Add(GetAttributeCapture().ArcaneResistanceDef);
}

void UExecCalcDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                             FGameplayEffectCustomExecutionOutput&           OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	if (!ExecutionParams.GetSourceAbilitySystemComponent() || !ExecutionParams.GetTargetAbilitySystemComponent())
	{
		return;
	}
	const auto GeSpec            = ExecutionParams.GetOwningSpec();
	const auto CaptureAttributes = GetAttributeCapture();

	// 从GE里获取源、目标的CombineTags
	const auto SourceTags = GeSpec.CapturedSourceTags.GetAggregatedTags();
	const auto TargetTags = GeSpec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;

	const auto SourceAvatar = ExecutionParams.GetSourceAbilitySystemComponent()->GetAvatarActor();
	const auto TargetAvatar = ExecutionParams.GetTargetAbilitySystemComponent()->GetAvatarActor();


	auto GeContextHandle = GeSpec.GetContext();
}
