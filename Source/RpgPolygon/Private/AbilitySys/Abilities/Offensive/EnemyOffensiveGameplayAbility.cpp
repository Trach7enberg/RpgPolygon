// Garrett Gan All Right Reserved


#include "RpgPolygon/Public/AbilitySys/Abilities/Offensive/EnemyOffensiveGameplayAbility.h"

UAnimMontage* UEnemyOffensiveGameplayAbility::GetCurrentAttackMontage() const
{
	if (AttackMontage.IsEmpty()) { return nullptr; }

	if (AttackMontage.Num() == 1) { return AttackMontage[0]; }

	const auto Result = AttackMontage.Find(FMath::RandRange(0, AttackMontage.Num() - 1));
	ensureMsgf(Result, TEXT("Cant Find AttackMontage"));
	if (!Result || *Result == nullptr) { return nullptr; }

	return *Result;
}
