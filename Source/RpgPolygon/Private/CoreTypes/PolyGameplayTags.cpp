// Fill out your copyright notice in the Description page of Project Settings.


#include "CoreTypes/PolyGameplayTags.h"

namespace PolyGameplayTags
{
#pragma region InputTag
	/// RPGWARRIOR_API宏意思是允许这个标签可以被其他模块使用
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_InputTag_Move, "RpgPoly.InputTag.Move", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_InputTag_Look, "RpgPoly.InputTag.Look", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_InputTag_Equip, "RpgPoly.InputTag.Equip", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_InputTag_UnEquip, "RpgPoly.InputTag.UnEquip", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_InputTag_LightAttack, "RpgPoly.InputTag.LightAttack", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_InputTag_HeavyAttack, "RpgPoly.InputTag.HeavyAttack", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_InputTag_Roll, "RpgPoly.InputTag.Roll", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_InputTag_Block, "RpgPoly.InputTag.Block", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_InputTag_TargetLock, "RpgPoly.InputTag.TargetLock", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_InputTag_SwitchTarget_Left, "RpgPoly.InputTag.SwitchTarget.Left", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_InputTag_SwitchTarget_Right, "RpgPoly.InputTag.SwitchTarget.Right", "");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_InputTag_Click_Interact, "RpgPoly.InputTag.Click.Interact", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_InputTag_Click_Character, "RpgPoly.InputTag.Click.Character", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_InputTag_Click_Environment, "RpgPoly.InputTag.Click.Environment", "");
#pragma endregion

#pragma region WeaponTag
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Weapon_KnightRuin_Staff_01,
	                               "RpgPoly.Player.Weapon.KnightRuin.Staff.01",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Weapon_KnightRuin_Sword_GreatSwordRound,
	                               "RpgPoly.Player.Weapon.KnightRuin.Sword.GreatSwordRound",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Weapon_KnightRuin_Spear,
	                               "RpgPoly.Player.Weapon.KnightRuin.Spear",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Weapon_KnightRuin_Bow,
	                               "RpgPoly.Player.Weapon.KnightRuin.Bow",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Weapon_KnightRuin_Staff_01,
	                               "RpgPoly.Enemy.Weapon.KnightRuin.Staff.01",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Weapon_KnightRuin_Sword_GreatSwordRound,
	                               "RpgPoly.Enemy.Weapon.KnightRuin.Sword.GreatSwordRound",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Weapon_KnightRuin_Spear,
	                               "RpgPoly.Enemy.Weapon.KnightRuin.Spear",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Weapon_KnightRuin_Bow,
	                               "RpgPoly.Enemy.Weapon.KnightRuin.Bow",
	                               "");
#pragma endregion

#pragma region EvenTag


	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_EventTag_Offensive_MeleeHit,
	                               "RpgPoly.Player.EventTag.Offensive.MeleeHit",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_EventTag_Offensive_Spell_Projectile,
	                               "RpgPoly.Player.EventTag.Offensive.Spell.Projectile",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_EventTag_Action_Equip_Axe,
	                               "RpgPoly.Player.EventTag.Action.Equip.Axe",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_EventTag_Action_UnEquip_Axe,
	                               "RpgPoly.Player.EventTag.Action.UnEquip.Axe",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_EventTag_Action_HitPause,
	                               "RpgPoly.Player.EventTag.Action.HitPause",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_EventTag_Action_HitReact,
	                               "RpgPoly.Player.EventTag.Action.HitReact",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_EventTag_Action_Death, "RpgPoly.Player.EventTag.Action.Death", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_EventTag_Action_SuccessfulBlock,
	                               "RpgPoly.Player.EventTag.Action.SuccessfulBlock",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_EventTag_Action_SwitchLockTarget_Left,
	                               "RpgPoly.Player.EventTag.Action.SwitchLockTarget.Left",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_EventTag_Action_SwitchLockTarget_Right,
	                               "RpgPoly.Player.EventTag.Action.SwitchLockTarget.Right",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_EventTag_Action_Bow_Aiming,
	                               "RpgPoly.Player.EventTag.Action.Bow.Aiming",
	                               "");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_EventTag_Action_Bow_Release,
	                               "RpgPoly.Player.EventTag.Action.Bow.Release",
	                               "");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_EventTag_Action_HitReact,
	                               "RpgPoly.Enemy.EventTag.Action.HitReact",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_EventTag_Action_Death, "RpgPoly.Enemy.EventTag.Action.Death", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_EventTag_Action_Strafing,
	                               "RpgPoly.Enemy.EventTag.Action.Strafing",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_EventTag_Offensive_MeleeHit,
	                               "RpgPoly.Enemy.EventTag.Offensive.MeleeHit",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_EventTag_Action_Bow_Aiming,
	                               "RpgPoly.Enemy.EventTag.Action.Bow.Aiming",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_EventTag_Action_Bow_Release,
	                               "RpgPoly.Enemy.EventTag.Action.Bow.Release",
	                               "");

#pragma endregion

#pragma region AbilityTag
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_SpawnWeapon_Type_Staff,
	                               "RpgPoly.Player.Ability.SpawnWeapon.Type.Staff",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_SpawnWeapon_Type_Sword,
	                               "RpgPoly.Player.Ability.SpawnWeapon.Type.Sword",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_SpawnWeapon_Type_Shield,
	                               "RpgPoly.Player.Ability.SpawnWeapon.Type.Shield",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Ability_SpawnWeapon_Type_Staff,
	                               "RpgPoly.Enemy.Ability.SpawnWeapon.Type.Staff",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Ability_SpawnWeapon_Type_Sword,
	                               "RpgPoly.Enemy.Ability.SpawnWeapon.Type.Sword",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Ability_SpawnWeapon_Type_Shield,
	                               "RpgPoly.Enemy.Ability.SpawnWeapon.Type.Shield",
	                               "");


	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_Action_Equip_Axe, "RpgPoly.Player.Ability.Action.Equip", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_Action_UnEquip_Axe,
	                               "RpgPoly.Player.Ability.Action.UnEquip",
	                               "");
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_Offensive_Spell_Fire_FireBolt,
	                               "RpgPoly.Player.Ability.Offensive.Spell.Fire.FireBolt",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_Defend_Block_Shield,
	                               "RpgPoly.Player.Ability.Defend.Block.Shield",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_Action_HitPause,
	                               "RpgPoly.Player.Ability.Action.HitPause",
	                               "");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_Action_HitReact_Front,
	                               "RpgPoly.Player.Ability.Action.HitReact.Front",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_Action_HitReact_Left,
	                               "RpgPoly.Player.Ability.Action.HitReact.Left",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_Action_HitReact_Right,
	                               "RpgPoly.Player.Ability.Action.HitReact.Right",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_Action_HitReact_Back,
	                               "RpgPoly.Player.Ability.Action.HitReact.Back",
	                               "");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_Action_Death, "RpgPoly.Player.Ability.Action.Death", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_Action_Roll, "RpgPoly.Player.Ability.Action.Roll", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_Action_TargetLock,
	                               "RpgPoly.Player.Ability.Action.TargetLock",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Ability_Action_ClickMove,
	                               "RpgPoly.Player.Ability.Action.ClickMove",
	                               "");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Ability_Offensive_Melee, "RpgPoly.Enemy.Ability.Offensive.Melee", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Ability_Offensive_Ranged,
	                               "RpgPoly.Enemy.Ability.Offensive.Ranged",
	                               "");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Ability_Action_HitReact, "RpgPoly.Enemy.Ability.Action.HitReact", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Ability_Action_HitReact_Front,
	                               "RpgPoly.Enemy.Ability.Action.HitReact.Front",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Ability_Action_HitReact_Left,
	                               "RpgPoly.Enemy.Ability.Action.HitReact.Left",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Ability_Action_HitReact_Right,
	                               "RpgPoly.Enemy.Ability.Action.HitReact.Right",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Ability_Action_HitReact_Back,
	                               "RpgPoly.Enemy.Ability.Action.HitReact.Back",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Ability_Action_Death, "RpgPoly.Enemy.Ability.Action.Death", "");
#pragma endregion

#pragma region AbilityStatusTag
	
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Status_Action_Rolling,
	                               "RpgPoly.Player.Status.Action.Rolling",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Status_Action_Blocking,
	                               "RpgPoly.Player.Status.Action.Blocking",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Status_Action_TargetLocking,
	                               "RpgPoly.Player.Status.Action.TargetLocking",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Status_Action_Move_ManualMoving,
	                               "RpgPoly.Player.Status.Action.Move.ManualMoving",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Status_Action_Move_AutoMoving,
	                               "RpgPoly.Player.Status.Action.Move.AutoMoving",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Player_Status_Action_Bow_Aiming,
	                               "RpgPoly.Player.Status.Action.Bow.Aiming",
	                               "");

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Status_Action_UnderAttack,
	                               "RpgPoly.Enemy.Status.Action.UnderAttack",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Enemy_Status_Action_Bow_Aiming,
	                               "RpgPoly.Enemy.Status.Action.Bow.Aiming",
	                               "");


#pragma endregion

#pragma region SetByCallerTag

	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Shared_SetByCaller_BaseDamage, "RpgPoly.Shared.SetByCaller.BaseDamage", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Shared_SetByCaller_AttackType_Light,
	                               "RpgPoly.Shared.SetByCaller.AttackType.Light",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_Shared_SetByCaller_AttackType_Heavy,
	                               "RpgPoly.Shared.SetByCaller.AttackType.Heavy",
	                               "");

#pragma endregion

#pragma region EquippedTypeTag
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_EquippedTag_Current,
	                               "RpgPoly.EquippedTag.Current",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_EquippedTag_Right,
	                               "RpgPoly.EquippedTag.Right",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_EquippedTag_Left,
	                               "RpgPoly.EquippedTag.Left",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_EquippedTag_Back,
	                               "RpgPoly.EquippedTag.Back",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_EquippedTag_Head,
	                               "RpgPoly.EquippedTag.Head",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_EquippedTag_Bread,
	                               "RpgPoly.EquippedTag.Bread",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_EquippedTag_Wing1,
	                               "RpgPoly.EquippedTag.Wing1",
	                               "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_EquippedTag_Wing2,
	                               "RpgPoly.EquippedTag.Wing2",
	                               "");
#pragma endregion

#pragma region MageSkillKeywords
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_AttackSpeed, "RpgPoly.SkillKeywords.AttackSpeed", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Barrier, "RpgPoly.SkillKeywords.Barrier", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Basic, "RpgPoly.SkillKeywords.Basic", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Burn, "RpgPoly.SkillKeywords.Burn", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Chain, "RpgPoly.SkillKeywords.Chain", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Channeled, "RpgPoly.SkillKeywords.Channeled", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Chill, "RpgPoly.SkillKeywords.Chill", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Cold, "RpgPoly.SkillKeywords.Cold", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Conjuration, "RpgPoly.SkillKeywords.Conjuration", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Cooldown, "RpgPoly.SkillKeywords.Cooldown", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Core, "RpgPoly.SkillKeywords.Core", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_CracklingEnergy, "RpgPoly.SkillKeywords.CracklingEnergy", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_CriticalStrikes, "RpgPoly.SkillKeywords.CriticalStrikes", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_CrowdControl, "RpgPoly.SkillKeywords.CrowdControl", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Damage, "RpgPoly.SkillKeywords.Damage", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_DamageReduction, "RpgPoly.SkillKeywords.DamageReduction", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Defensive, "RpgPoly.SkillKeywords.Defensive", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Dodge, "RpgPoly.SkillKeywords.Dodge", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_EliteMonsters, "RpgPoly.SkillKeywords.EliteMonsters", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Fire, "RpgPoly.SkillKeywords.Fire", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Frost, "RpgPoly.SkillKeywords.Frost", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Frozen, "RpgPoly.SkillKeywords.Frozen", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Healing, "RpgPoly.SkillKeywords.Healing", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Healthy, "RpgPoly.SkillKeywords.Healthy", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Immune, "RpgPoly.SkillKeywords.Immune", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_KeyPassive, "RpgPoly.SkillKeywords.KeyPassive", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Life, "RpgPoly.SkillKeywords.Life", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Lightning, "RpgPoly.SkillKeywords.Lightning", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_LuckyHit, "RpgPoly.SkillKeywords.LuckyHit", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Mana, "RpgPoly.SkillKeywords.Mana", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Mastery, "RpgPoly.SkillKeywords.Mastery", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Mobility, "RpgPoly.SkillKeywords.Mobility", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Movement, "RpgPoly.SkillKeywords.Movement", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_NonPhysical, "RpgPoly.SkillKeywords.NonPhysical", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Pyromancy, "RpgPoly.SkillKeywords.Pyromancy", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Resistance, "RpgPoly.SkillKeywords.Resistance", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Shock, "RpgPoly.SkillKeywords.Shock", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Summon, "RpgPoly.SkillKeywords.Summon", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Ultimate, "RpgPoly.SkillKeywords.Ultimate", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Unstoppable, "RpgPoly.SkillKeywords.Unstoppable", "");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(RpgPoly_SkillKeywords_Vulnerable, "RpgPoly.SkillKeywords.Vulnerable", "");

#pragma endregion
}
