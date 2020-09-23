/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Scripts for spells with SPELLFAMILY_MONK and SPELLFAMILY_GENERIC spells used by monk players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_monk_".
 */

#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "GridNotifiers.h"

enum MonkSpells
{
    SPELL_MONK_LEGACY_OF_THE_EMPEROR            = 117667,
    SPELL_MONK_FORTIFYING_BREW                  = 120954,
    SPELL_MONK_PROVOKE                          = 118635,
    SPELL_MONK_BLACKOUT_KICK_DOT                = 128531,
    SPELL_MONK_BLACKOUT_KICK_HEAL               = 128591,
    SPELL_MONK_SHUFFLE                          = 115307,
    SPELL_MONK_ZEN_PILGRIMAGE                   = 126892,
    SPELL_MONK_ZEN_PILGRIMAGE_RETURN            = 126895,
    SPELL_MONK_DISABLE_ROOT                     = 116706,
    SPELL_MONK_DISABLE                          = 116095,
	SPELL_MONK_EMINENCE_HEAL_STATUE             = 117895,
	SPELL_MONK_ZEN_SPHERE_HEAL                  = 124081,
    SPELL_MONK_SOOTHING_MIST_VISUAL             = 125955,
    SPELL_MONK_SOOTHING_MIST_ENERGIZE           = 116335,
    SPELL_MONK_BREATH_OF_FIRE_DOT               = 123725,
    SPELL_MONK_BREATH_OF_FIRE_CONFUSED          = 123393,
    SPELL_MONK_ELUSIVE_BREW_STACKS              = 128939,
    SPELL_MONK_ELUSIVE_BREW                     = 115308,
    SPELL_MONK_KEG_SMASH_VISUAL                 = 123662,
    SPELL_MONK_KEG_SMASH_ENERGIZE               = 127796,
    SPELL_MONK_WEAKENED_BLOWS                   = 115798,
    SPELL_MONK_DIZZYING_HAZE                    = 116330,
    SPELL_MONK_CLASH_CHARGE                     = 126452,
    SPELL_MONK_LIGHT_STAGGER                    = 124275,
    SPELL_MONK_MODERATE_STAGGER                 = 124274,
    SPELL_MONK_HEAVY_STAGGER                    = 124273,
    SPELL_MONK_ROLL                             = 109132,
    SPELL_MONK_ROLL_TRIGGER                     = 107427,
    SPELL_MONK_CHI_TORPEDO_HEAL                 = 124040,
    SPELL_MONK_CHI_TORPEDO_DAMAGE               = 117993,
    SPELL_MONK_FLYING_SERPENT_KICK              = 101545,
    SPELL_MONK_FLYING_SERPENT_KICK_NEW          = 115057,
    SPELL_MONK_FLYING_SERPENT_KICK_AOE          = 123586,
    SPELL_MONK_GLYPH_OF_FLYING_SERPENT_KICK     = 123403,
    SPELL_MONK_TIGEREYE_BREW                    = 116740,
    SPELL_MONK_TIGEREYE_BREW_STACKS             = 125195,
    SPELL_MONK_TIGEREYE_BREW_VISUAL             = 137591,
    SPELL_MONK_SPEAR_HAND_STRIKE_SILENCE        = 116709,
    SPELL_MONK_CHI_BURST_VISUAL                 = 125817,
    SPELL_MONK_ZEN_SPHERE_DAMAGE                = 124098,
    SPELL_MONK_ZEN_SPHERE_DETONATE_HEAL         = 124101,
    SPELL_MONK_ZEN_SPHERE_DETONATE_DAMAGE       = 125033,
    SPELL_MONK_HEALING_ELIXIRS_AURA             = 122280,
    SPELL_MONK_HEALING_ELIXIRS_RESTORE_HEALTH   = 122281,
    SPELL_MONK_RENEWING_MIST_HOT                = 119611,
    SPELL_MONK_RENEWING_MIST_JUMP_AURA          = 119607,
    SPELL_MONK_GLYPH_OF_RENEWING_MIST           = 123334,
    SPELL_MONK_SURGING_MIST_HEAL                = 116995,
    SPELL_MONK_ENVELOPING_MIST_HEAL             = 132120,
    SPELL_MONK_INTERNAL_MEDICINE                = 115451,
    SPELL_MONK_PLUS_ONE_MANA_TEA                = 123760,
    SPELL_MONK_MANA_TEA_STACKS                  = 115867,
    SPELL_MONK_MANA_TEA_REGEN                   = 115294,
    SPELL_MONK_SPINNING_CRANE_KICK_HEAL         = 117640,
    MONK_NPC_JADE_SERPENT_STATUE                = 60849,
    SPELL_MONK_UPLIFT_ALLOWING_CAST             = 123757,
    SPELL_MONK_THUNDER_FOCUS_TEA                = 116680,
    SPELL_MONK_PATH_OF_BLOSSOM_AREATRIGGER      = 122035,
    SPELL_MONK_SPINNING_FIRE_BLOSSOM_DAMAGE     = 123408,
    SPELL_MONK_SPINNING_FIRE_BLOSSOM_MISSILE    = 118852,
    SPELL_MONK_SPINNING_FIRE_BLOSSOM_ROOT       = 123407,
    SPELL_MONK_GLYPH_OF_SPINNING_FIRE_BLOSSOM   = 123405,
    SPELL_MONK_TOUCH_OF_KARMA_REDIRECT_DAMAGE   = 124280,
    SPELL_MONK_JADE_LIGHTNING_ENERGIZE          = 123333,
    SPELL_MONK_CRACKLING_JADE_SHOCK_BUMP        = 117962,
    SPELL_MONK_POWER_STRIKES_TALENT             = 121817,
    SPELL_MONK_POWER_STRIKES_TALENT_EFFECT      = 129914,
    SPELL_MONK_CREATE_CHI_SPHERE                = 121286,
    SPELL_MONK_GLYPH_OF_ZEN_FLIGHT              = 125893,
    SPELL_MONK_ZEN_FLIGHT                       = 125883,
    SPELL_MONK_BEAR_HUG                         = 127361,
    ITEM_MONK_T14_TANK_4P                       = 123159,
    MONK_NPC_BLACK_OX_STATUE                    = 61146,
    SPELL_MONK_GUARD                            = 115295,
    SPELL_MONK_ITEM_2_S12_MISTWEAVER            = 131561,
    SPELL_MONK_ITEM_4_S12_MISTWEAVER            = 124487,
    SPELL_MONK_ZEN_FOCUS                        = 124488,
    SPELL_MONK_EMINENCE_HEAL                    = 126890,
    SPELL_MONK_GRAPPLE_WEAPON_DPS_UPGRADE       = 123231,
    SPELL_MONK_GRAPPLE_WEAPON_TANK_UPGRADE      = 123232,
    SPELL_MONK_GRAPPLE_WEAPON_HEAL_UPGRADE      = 123234,
    SPELL_MONK_GLYPH_OF_BLACKOUT_KICK           = 132005,
    SPELL_MONK_CHI_WAVE_HEAL                    = 132463,
    SPELL_MONK_CHI_WAVE_DAMAGE                  = 132467,
    SPELL_MONK_CHI_WAVE_HEALING_BOLT            = 132464,
    SPELL_MONK_CHI_WAVE_TALENT_AURA             = 115098,
    SPELL_MONK_ITEM_PVP_GLOVES_BONUS            = 124489,
    SPELL_MONK_MUSCLE_MEMORY                    = 139598,
    SPELL_MONK_MUSCLE_MEMORY_EFFECT             = 139597,
    SPELL_MONK_CHI_BREW                         = 115399,
    SPELL_MONK_GLYPH_OF_MANA_TEA                = 123763,
    SPELL_MONK_GLYPH_OF_MANA_TEA_EFFECT         = 123761,
    SPELL_MONK_COMBO_BREAKER_TIGER_PALM         = 118864,
    SPELL_MONK_COMBO_BREAKER_BLACKOUT_KICK      = 116768,
    SPELL_MONK_LEER_OF_THE_OX                   = 115543,
    SPELL_MONK_LEER_OF_THE_OX_GLYPH             = 125967,
    SPELL_MONK_GLYPH_OF_LIFE_COCOON             = 124989,
    SPELL_MONK_MASTERY_BOTTLED_FURY             = 115636,
    SPELL_MONK_STORM_EARTH_AND_FIRE             = 137639,
    SPELL_MONK_RING_OF_PEACE_AURA               = 140023,
    SPELL_MONK_RING_OF_PEACE_DISARM             = 137461,
    SPELL_MONK_RING_OF_PEACE_SILENCE            = 137460,
	SPELL_MONK_COMBO_BREAKER                    = 137384,
	SPELL_MONK_SPARRING                         = 116033,
	SPELL_MONK_SPARRING_COOLDOWN_MARKER         = 116087,
	SPELL_MONK_FORTIFYING_BREW_A                = 115203,
	SPELL_MONK_PURIFYING_BREW                   = 119582,
	SPELL_MONK_ENERGIZING_BREW                  = 115288,
	SPELL_MONK_NIMBLE_BREW                      = 137562,
	SPELL_MONK_TOUCH_OF_KARMA                   = 122470
};

// Ring of Peace (dummy) - 140023
class spell_monk_ring_of_peace_dummy : public SpellScriptLoader
{
    public:
        spell_monk_ring_of_peace_dummy() : SpellScriptLoader("spell_monk_ring_of_peace_dummy") {}

        class spell_monk_ring_of_peace_dummy_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_ring_of_peace_dummy_AuraScript);

            void HandleDummyProc(constAuraEffectPtr /*aurEff*/, ProcEventInfo& /*eventInfo*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetTarget())
                    {
                        caster->CastSpell(target, SPELL_MONK_RING_OF_PEACE_SILENCE, true);
                        caster->CastSpell(target, SPELL_MONK_RING_OF_PEACE_DISARM, true);
                    }
                }
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_monk_ring_of_peace_dummy_AuraScript::HandleDummyProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_ring_of_peace_dummy_AuraScript();
        }
};

// Ring of Peace - 116844
class spell_monk_ring_of_peace : public SpellScriptLoader
{
    public:
        spell_monk_ring_of_peace() : SpellScriptLoader("spell_monk_ring_of_peace") { }

        class spell_monk_ring_of_peace_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_ring_of_peace_AuraScript);

            void OnUpdate(uint32 diff)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetUnitOwner())
                    {
                        std::list<Unit*> targetList;
                        float radius = 8.0f;

                        WoWSource::NearestAttackableUnitInObjectRangeCheck u_check(target, caster, radius);
                        WoWSource::UnitListSearcher<WoWSource::NearestAttackableUnitInObjectRangeCheck> searcher(target, targetList, u_check);
                        target->VisitNearbyObject(radius, searcher);

                        for (auto itr : targetList)
                            caster->CastSpell(itr, SPELL_MONK_RING_OF_PEACE_AURA, true);
                    }
                }
            }

            void Register()
            {
                OnAuraUpdate += AuraUpdateFn(spell_monk_ring_of_peace_AuraScript::OnUpdate);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_ring_of_peace_AuraScript();
        }
};

const uint32 spiritEntry[3] = { 69680,  69792,  69791  }; // Storm, Earth and Fire
const uint32 summonsMonk[3] = { 138122, 138121, 138123 }; // Storm, Earth and Fire
const uint32 visualMorph[3] = { 138080, 138083, 138081 }; // Storm, Earth and Fire

// Storm, Earth and Fire - 138130
class spell_monk_storm_earth_and_fire_stats : public SpellScriptLoader
{
    public:
        spell_monk_storm_earth_and_fire_stats() : SpellScriptLoader("spell_monk_storm_earth_and_fire_stats") { }

        class spell_monk_storm_earth_and_fire_stats_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_storm_earth_and_fire_stats_AuraScript);

            void OnUpdate(uint32 /*diff*/, AuraEffectPtr aurEff)
            {
                if (!GetCaster())
                    return;

                if (Unit* caster = GetCaster()->GetOwner())
                {
                    if (AuraEffectPtr stormAura = caster->GetAuraEffect(SPELL_MONK_STORM_EARTH_AND_FIRE, EFFECT_1))
                    {
                        if (aurEff->GetAmount() != stormAura->GetAmount())
                            aurEff->ChangeAmount(stormAura->GetAmount());
                    }
                }
            }

            void CalculateReducedDamage(constAuraEffectPtr /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (!GetCaster() || !GetCaster()->GetOwner())
                    return;

                if (Unit* owner = GetCaster()->GetOwner())
                    if (AuraEffectPtr stormAura = owner->GetAuraEffect(SPELL_MONK_STORM_EARTH_AND_FIRE, EFFECT_1))
                        amount = stormAura->GetAmount();
            }

            void CalculateHealing(constAuraEffectPtr /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (!GetCaster() || !GetCaster()->GetOwner())
                    return;

                if (Unit* owner = GetCaster()->GetOwner())
                    amount = owner->GetTotalAuraModifier(SPELL_AURA_MOD_HEALING_DONE_PERCENT);
            }

            void CalculateAttackPower(constAuraEffectPtr /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (!GetCaster() || !GetCaster()->GetOwner())
                    return;

                if (Unit* owner = GetCaster()->GetOwner())
                    amount = owner->GetTotalAttackPowerValue(BASE_ATTACK);
            }

            void CalculateHaste(constAuraEffectPtr /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (!GetCaster() || !GetCaster()->GetOwner())
                    return;

                if (Player* owner = GetCaster()->GetOwner()->ToPlayer())
                {
                    if (Unit* caster = GetCaster())
                    {
                        // Convert Owner's haste into the Spirit haste
                        float ownerHaste = owner->GetMeleeHastePct(false) / 10.f;

                        caster->ApplyPercentModFloatValue(UNIT_MOD_CAST_SPEED, ownerHaste, false);
                        caster->ApplyPercentModFloatValue(UNIT_MOD_CAST_HASTE, ownerHaste, false);
                        caster->ApplyPercentModFloatValue(UNIT_MOD_HASTE, ownerHaste, false);
                    }
                }
            }

            void Register()
            {
                OnEffectUpdate += AuraEffectUpdateFn(spell_monk_storm_earth_and_fire_stats_AuraScript::OnUpdate, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_storm_earth_and_fire_stats_AuraScript::CalculateReducedDamage, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_storm_earth_and_fire_stats_AuraScript::CalculateHealing, EFFECT_3, SPELL_AURA_MOD_HEALING_DONE_PERCENT);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_storm_earth_and_fire_stats_AuraScript::CalculateAttackPower, EFFECT_4, SPELL_AURA_MOD_ATTACK_POWER);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_storm_earth_and_fire_stats_AuraScript::CalculateHaste, EFFECT_5, SPELL_AURA_MOD_MELEE_HASTE_3);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_storm_earth_and_fire_stats_AuraScript();
        }
};

// Storm, Earth and Fire - 137639
class spell_monk_storm_earth_and_fire : public SpellScriptLoader
{
    public:
        spell_monk_storm_earth_and_fire() : SpellScriptLoader("spell_monk_storm_earth_and_fire") { }

        class spell_monk_storm_earth_and_fire_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_storm_earth_and_fire_SpellScript);

            uint8 summonsCount;
            uint8 firstSpirit;

            bool Load()
            {
                summonsCount = 0;
                firstSpirit  = 3;
                return true;
            }

            void HandleDummy(SpellEffIndex effIndex)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        for (uint8 i = 0; i < 3; ++i)
                        {
                            if (!caster->m_Controlled.empty())
                            {
                                for (Unit::ControlList::const_iterator itr = caster->m_Controlled.begin(); itr != caster->m_Controlled.end(); ++itr)
                                {
                                    if (!(*itr))
                                        continue;

                                    if ((*itr)->GetEntry() == spiritEntry[i])
                                    {
                                        ++summonsCount;

                                        if (firstSpirit == 3)
                                            firstSpirit = i;
                                    }
                                }
                            }
                        }

                        if (!summonsCount)
                            caster->CastSpell(caster, visualMorph[urand(0, 2)], true);

                        ++summonsCount;

                        // Find summonned spirit
                        if (!caster->m_Controlled.empty())
                        {
                            for (Unit::ControlList::const_iterator itr = caster->m_Controlled.begin(); itr != caster->m_Controlled.end(); ++itr)
                            {
                                if (!(*itr))
                                    continue;

                                if (Creature* spirit = (*itr)->ToCreature())
                                {
                                    if (spirit->AI() && spirit->AI()->GetGUID() == target->GetGUID())
                                    {
                                        spirit->AI()->DoAction(0);
                                        return;
                                    }
                                }
                            }
                        }

                        Unit* spiritRemoved = NULL;
                        if (summonsCount > 2)
                        {
                            if (!caster->m_Controlled.empty())
                            {
                                for (Unit::ControlList::const_iterator itr = caster->m_Controlled.begin(); itr != caster->m_Controlled.end(); ++itr)
                                {
                                    if (!(*itr))
                                        continue;

                                    if ((*itr)->GetEntry() == spiritEntry[firstSpirit])
                                    {
                                        if (Creature* spirit = (*itr)->ToCreature())
                                        {
                                            if (Unit* owner = spirit->GetOwner())
                                            {
                                                spirit->GetMotionMaster()->MovementExpired();
                                                spirit->GetMotionMaster()->MoveJump(owner->GetPositionX(), owner->GetPositionY(), owner->GetPositionZ(), 15.0f, 10.0f, spirit->GetOrientation(), 1);
                                                spiritRemoved = spirit->ToUnit();
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        Unit* pPet = NULL;
                        if (spiritRemoved)
                        {
                            for (uint8 i = 0; i < 3; ++i)
                            {
                                if (spiritEntry[i] == spiritRemoved->GetEntry())
                                {
                                    caster->CastSpell(caster, summonsMonk[i], true);

                                    // Find summoned spirit
                                    if (!caster->m_Controlled.empty())
                                    {
                                        for (Unit::ControlList::const_iterator itr = caster->m_Controlled.begin(); itr != caster->m_Controlled.end(); ++itr)
                                        {
                                            if (!(*itr))
                                                continue;

                                            if ((*itr)->GetEntry() == spiritEntry[i] && (*itr) != spiritRemoved)
                                            {
                                                pPet = *itr;
                                                break;
                                            }
                                        }
                                    }

                                    if (pPet && pPet->GetAI())
                                        pPet->GetAI()->SetGUID(target->GetGUID());

                                    if (firstSpirit == 3)
                                        firstSpirit = i;

                                    return;
                                }
                            }
                        }

                        for (uint8 i = 0; i < 3; ++i)
                        {
                            if (caster->HasAura(visualMorph[i]))
                                continue;

                            if (firstSpirit < 3 && firstSpirit == i)
                                continue;

                            caster->CastSpell(caster, summonsMonk[i], true);

                            // Find summoned spirit
                            if (!caster->m_Controlled.empty())
                            {
                                for (Unit::ControlList::const_iterator itr = caster->m_Controlled.begin(); itr != caster->m_Controlled.end(); ++itr)
                                {
                                    if (!(*itr))
                                        continue;

                                    if ((*itr)->GetEntry() == spiritEntry[i] && (*itr) != spiritRemoved)
                                    {
                                        pPet = *itr;
                                        break;
                                    }
                                }
                            }

                            if (pPet && pPet->GetAI())
                                pPet->GetAI()->SetGUID(target->GetGUID());

                            if (firstSpirit == 3)
                                firstSpirit = i;

                            break;
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_monk_storm_earth_and_fire_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_storm_earth_and_fire_SpellScript();
        }

        class spell_monk_storm_earth_and_fire_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_storm_earth_and_fire_AuraScript);

            void CalculateAmount(constAuraEffectPtr aurEff, int32& amount, bool & /*canBeRecalculated*/)
            {
                amount = (aurEff->GetBase()->GetStackAmount() > 1) ? -45 : -30;
            }

            void OnUpdate(uint32 /*diff*/, AuraEffectPtr /*aurEff*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Player* player = caster->ToPlayer())
                    {
                        uint8 count = 0;

                        if (!player->m_Controlled.empty())
                        for (Unit::ControlList::const_iterator itr = player->m_Controlled.begin(); itr != player->m_Controlled.end(); ++itr)
                        if ((*itr)->GetEntry() == 69680 || (*itr)->GetEntry() == 69792 || (*itr)->GetEntry() == 69791)
                            ++count;

                        if (!count)
                        {
                            player->RemoveAura(GetSpellInfo()->Id);
                            return;
                        }

                        if (AuraPtr stormAura = player->GetAura(GetSpellInfo()->Id))
                        {
                            if (count != stormAura->GetStackAmount())
                                stormAura->SetStackAmount(count);
                        }
                    }
                }
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    for (uint8 i = 0; i < 3; ++i)
                        caster->RemoveAura(visualMorph[i]);

                    if (!caster->m_Controlled.empty())
                    {
                        for (Unit::ControlList::const_iterator itr = caster->m_Controlled.begin(); itr != caster->m_Controlled.end(); ++itr)
                        {
                            if ((*itr)->GetEntry() == 69680 || (*itr)->GetEntry() == 69792 || (*itr)->GetEntry() == 69791)
                            {
                                if (Creature* spirit = (*itr)->ToCreature())
                                {
                                    spirit->GetMotionMaster()->Clear();
                                    spirit->GetMotionMaster()->MoveJump(caster->GetPositionX(), caster->GetPositionY(), caster->GetPositionZ(), 15.0f, 10.0f, spirit->GetOrientation(), 1);
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_storm_earth_and_fire_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_storm_earth_and_fire_AuraScript::CalculateAmount, EFFECT_2, SPELL_AURA_DUMMY);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_storm_earth_and_fire_AuraScript::CalculateAmount, EFFECT_3, SPELL_AURA_ADD_PCT_MODIFIER);
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_storm_earth_and_fire_AuraScript::CalculateAmount, EFFECT_4, SPELL_AURA_ADD_PCT_MODIFIER);
                OnEffectUpdate += AuraEffectUpdateFn(spell_monk_storm_earth_and_fire_AuraScript::OnUpdate, EFFECT_2, SPELL_AURA_DUMMY);
                AfterEffectRemove += AuraEffectRemoveFn(spell_monk_storm_earth_and_fire_AuraScript::OnRemove, EFFECT_2, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_storm_earth_and_fire_AuraScript();
        }
};

// Fists of Fury (stun effect) - 120086
class spell_monk_fists_of_fury_stun : public SpellScriptLoader
{
    public:
        spell_monk_fists_of_fury_stun() : SpellScriptLoader("spell_monk_fists_of_fury_stun") { }

        class spell_monk_fists_of_fury_stun_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_fists_of_fury_stun_SpellScript);

            void RemoveInvalidTargets(std::list<WorldObject*>& targets)
            {
                targets.remove_if(WoWSource::UnitAuraCheck(true, GetSpellInfo()->Id));
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_monk_fists_of_fury_stun_SpellScript::RemoveInvalidTargets, EFFECT_0, TARGET_UNIT_CONE_ENEMY_24);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_fists_of_fury_stun_SpellScript();
        }
};

// Expel Harm - 115072
class spell_monk_expel_harm : public SpellScriptLoader
{
    public:
        spell_monk_expel_harm() : SpellScriptLoader("spell_monk_expel_harm") { }

        class spell_monk_expel_harm_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_expel_harm_SpellScript);

            void HandleOnHit()
            {
                if (!GetCaster())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    std::list<Unit*> targetList;
                    float radius = 10.0f;

                    WoWSource::NearestAttackableUnitInObjectRangeCheck u_check(_player, _player, radius);
                    WoWSource::UnitListSearcher<WoWSource::NearestAttackableUnitInObjectRangeCheck> searcher(_player, targetList, u_check);
                    _player->VisitNearbyObject(radius, searcher);

                    for (auto itr : targetList)
                    {
                        if (_player->IsValidAttackTarget(itr))
                        {
                            int32 bp = CalculatePct((-GetHitDamage()), 50);
                            _player->CastCustomSpell(itr, 115129, &bp, NULL, NULL, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_expel_harm_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_expel_harm_SpellScript();
        }
};

// Chi Wave (damage bolt) - 132464
class spell_monk_chi_wave_healing_bolt : public SpellScriptLoader
{
    public:
        spell_monk_chi_wave_healing_bolt() : SpellScriptLoader("spell_monk_chi_wave_healing_bolt") { }

        class spell_monk_chi_wave_healing_bolt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_chi_wave_healing_bolt_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetOriginalCaster())
                {
                    if (Player* player = caster->ToPlayer())
                    {
                        if (Unit* target = GetHitUnit())
                        {
                            if (GetSpellInfo()->Id == SPELL_MONK_CHI_WAVE_HEALING_BOLT)
                                player->CastSpell(target, SPELL_MONK_CHI_WAVE_HEAL, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_chi_wave_healing_bolt_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_chi_wave_healing_bolt_SpellScript();
        }
};

// Chi Wave (damage) - 132467 and Chi Wave (heal) - 132463
class spell_monk_chi_wave_bolt : public SpellScriptLoader
{
    public:
        spell_monk_chi_wave_bolt() : SpellScriptLoader("spell_monk_chi_wave_bolt") { }

        class spell_monk_chi_wave_bolt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_chi_wave_bolt_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetOriginalCaster())
                {
                    if (Player* player = caster->ToPlayer())
                    {
                        if (Unit* target = GetHitUnit())
                        {
                            uint8 count = 0;

                            if (AuraEffectPtr chiWave = player->GetAuraEffect(SPELL_MONK_CHI_WAVE_TALENT_AURA, EFFECT_1))
                            {
                                count = chiWave->GetAmount();

                                if (count >= 7)
                                {
                                    player->RemoveAura(SPELL_MONK_CHI_WAVE_TALENT_AURA);
                                    return;
                                }

                                count++;
                                chiWave->SetAmount(count);
                            }
                            else
                                return;

                            std::list<Unit*> positiveTargetList;
                            std::list<Unit*> negativeTargetList;

                            player->FilterTargets(positiveTargetList, 25.f, (EXCLUDE_ENEMIES | ONLY_LOS), 1, target, HealthPctOrderPred);
                            player->FilterTargets(negativeTargetList, 25.f, (EXCLUDE_ALLIES | ONLY_LOS), 1, target, DistanceOrderPred);

                            if (positiveTargetList.empty() && negativeTargetList.empty())
                                player->RemoveAurasDueToSpell(SPELL_MONK_CHI_WAVE_TALENT_AURA);
                            else
                            {
                                if (roll_chance_i(50) && !positiveTargetList.empty())
                                {
                                    for (auto itr : positiveTargetList)
                                        target->CastSpell(itr, SPELL_MONK_CHI_WAVE_HEALING_BOLT, true, NULL, NULLAURA_EFFECT, player->GetGUID());
                                }
                                else if (!negativeTargetList.empty())
                                {
                                    for (auto itr : negativeTargetList)
                                        target->CastSpell(itr, SPELL_MONK_CHI_WAVE_DAMAGE, true, NULL, NULLAURA_EFFECT, player->GetGUID());
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_chi_wave_bolt_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_chi_wave_bolt_SpellScript();
        }
};

// Chi Wave (talent) - 115098
class spell_monk_chi_wave : public SpellScriptLoader
{
    public:
        spell_monk_chi_wave() : SpellScriptLoader("spell_monk_chi_wave") { }

        class spell_monk_chi_wave_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_chi_wave_SpellScript);

            uint64 targetGUID;
            bool done;

            SpellCastResult CheckTarget()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Player* player = caster->ToPlayer())
                    {
                        if (Unit* target = GetExplTargetUnit())
                        {
                            if (!player->IsValidAttackTarget(target) && !player->IsValidAssistTarget(target))
                                return SPELL_FAILED_BAD_TARGETS;
                        }
                    }
                }

                return SPELL_CAST_OK;
            }

            bool Load()
            {
                targetGUID = 0;
                done = false;
                return true;
            }

            void HandleDummy(SpellEffIndex effIndex)
            {
                if (Unit* target = GetHitUnit())
                    targetGUID = target->GetGUID();
            }

            void HandleApplyAura()
            {
                if (!targetGUID || done)
                    return;

                if (Unit* caster = GetCaster())
                {
                    if (Player* player = caster->ToPlayer())
                    {
                        if (Unit* target = sObjectAccessor->FindUnit(targetGUID))
                        {
                            int32 spellId = NULL;

                            if (player->IsValidAttackTarget(target))
                                spellId = SPELL_MONK_CHI_WAVE_DAMAGE;
                            else if (player->IsValidAssistTarget(target))
                                spellId = SPELL_MONK_CHI_WAVE_HEALING_BOLT;

                            if (spellId)
                            {
                                player->CastSpell(target, spellId, true);
                                done = true;
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_monk_chi_wave_SpellScript::CheckTarget);
                OnEffectHitTarget += SpellEffectFn(spell_monk_chi_wave_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
                AfterHit += SpellHitFn(spell_monk_chi_wave_SpellScript::HandleApplyAura);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_chi_wave_SpellScript();
        }
};

// Grapple Weapon - 117368
class spell_monk_grapple_weapon : public SpellScriptLoader
{
    public:
        spell_monk_grapple_weapon() : SpellScriptLoader("spell_monk_grapple_weapon") { }

        class spell_monk_grapple_weapon_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_grapple_weapon_SpellScript)

            void HandleBeforeHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (target->ToPlayer())
                        {
                            Item* mainItem = _player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                            Item* targetMainItem = target->ToPlayer()->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

                            if (mainItem && targetMainItem)
                            {
                                if (targetMainItem->GetTemplate()->ItemLevel > mainItem->GetTemplate()->ItemLevel)
                                {
                                    switch (_player->GetSpecializationId(_player->GetActiveSpec()))
                                    {
                                        case SPEC_MONK_BREWMASTER:
                                            _player->CastSpell(_player, SPELL_MONK_GRAPPLE_WEAPON_TANK_UPGRADE, true);
                                            break;
                                        case SPEC_MONK_MISTWEAVER:
                                            _player->CastSpell(_player, SPELL_MONK_GRAPPLE_WEAPON_HEAL_UPGRADE, true);
                                            break;
                                        case SPEC_MONK_WINDWALKER:
                                            _player->CastSpell(_player, SPELL_MONK_GRAPPLE_WEAPON_DPS_UPGRADE, true);
                                            break;
                                        default:
                                            break;
                                    }
                                }
                            }
                        }
                        else if (target->GetTypeId() == TYPEID_UNIT)
                        {
                            if (target->getLevel() > _player->getLevel())
                            {
                                switch (_player->GetSpecializationId(_player->GetActiveSpec()))
                                {
                                    case SPEC_MONK_BREWMASTER:
                                        _player->CastSpell(_player, SPELL_MONK_GRAPPLE_WEAPON_TANK_UPGRADE, true);
                                        break;
                                    case SPEC_MONK_MISTWEAVER:
                                        _player->CastSpell(_player, SPELL_MONK_GRAPPLE_WEAPON_HEAL_UPGRADE, true);
                                        break;
                                    case SPEC_MONK_WINDWALKER:
                                        _player->CastSpell(_player, SPELL_MONK_GRAPPLE_WEAPON_DPS_UPGRADE, true);
                                        break;
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                BeforeHit += SpellHitFn(spell_monk_grapple_weapon_SpellScript::HandleBeforeHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_grapple_weapon_SpellScript();
        }
};

// Transcendence : Transfer - 119996
class spell_monk_transcendence_transfer : public SpellScriptLoader
{
    public:
        spell_monk_transcendence_transfer() : SpellScriptLoader("spell_monk_transcendence_transfer") { }

        class spell_monk_transcendence_transfer_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_transcendence_transfer_SpellScript);

            Creature* spirit = NULL;

            SpellCastResult CheckTarget()
            {
                if (GetCaster())
                {
                    if (Player* _player = GetCaster()->ToPlayer())
                    {
                        float distance = 40.0f;

                        std::list<Creature*> npcs;
                        GetCreatureListWithEntryInGrid(npcs, _player, 54569, distance);
                        for (auto creature : npcs)
                        {
                            if (creature->ToTempSummon())
                            {
                                if (creature->ToTempSummon()->GetOwner() == _player)
                                {
                                    spirit = creature;
                                    return SPELL_CAST_OK;
                                }
                            }
                        }

                        return SPELL_FAILED_OUT_OF_RANGE;
                    }
                }

                return SPELL_FAILED_DONT_REPORT;
            }

            void HandleOnCast()
            {
                if (GetCaster())
                {
                    if (Player* _player = GetCaster()->ToPlayer())
                    {
                        if (!spirit)
                            return;

                        Position tpos;
                        spirit->GetPosition(&tpos);

                        Position ppos;
                        _player->GetPosition(&ppos);

                        spirit->NearTeleportTo(ppos.GetPositionX(), ppos.GetPositionY(), ppos.GetPositionZ(), ppos.GetOrientation());
                        _player->TeleportTo(spirit->GetMapId(), tpos.GetPositionX(), tpos.GetPositionY(), tpos.GetPositionZ(), tpos.GetOrientation(), TELE_TO_NOT_LEAVE_COMBAT);
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_monk_transcendence_transfer_SpellScript::CheckTarget);
                OnCast += SpellCastFn(spell_monk_transcendence_transfer_SpellScript::HandleOnCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_transcendence_transfer_SpellScript();
        }
};

// Transcendence : remove old spirit - 101643
class spell_monk_transcendence_remove_spirit : public SpellScriptLoader
{
    public:
        spell_monk_transcendence_remove_spirit() : SpellScriptLoader("spell_monk_transcendence_remove_spirit") { }

        class spell_monk_transcendence_remove_spirit_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_transcendence_remove_spirit_SpellScript);

            void HandleBeforeCast()
            {
                if (GetCaster())
                {
                    if (Player* _player = GetCaster()->ToPlayer())
                    {
                        // Summon Effect Visual
                        _player->SendPlaySpellVisual(24497, _player, 0.0f);

                        // Despawn if find old spirit
                        std::list<Creature*> transcendence;
                        _player->GetCreatureListWithEntryInGrid(transcendence, 54569, 100.0f);
                        if (!transcendence.empty())
                            for (auto itr : transcendence)
                                if (itr->GetOwnerGUID() == _player->GetGUID())
                                    itr->ToTempSummon()->UnSummon();
                    }
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_monk_transcendence_remove_spirit_SpellScript::HandleBeforeCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_transcendence_remove_spirit_SpellScript();
        }
};

// Serpent's Zeal - 127722
class spell_monk_serpents_zeal : public SpellScriptLoader
{
    public:
        spell_monk_serpents_zeal() : SpellScriptLoader("spell_monk_serpents_zeal") { }

        class spell_monk_serpents_zeal_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_serpents_zeal_AuraScript);

            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                if (!GetCaster())
                    return;

                if (eventInfo.GetActor()->GetGUID() != GetTarget()->GetGUID())
                    return;

                if (eventInfo.GetDamageInfo()->GetSpellInfo())
                    return;

                if (!(eventInfo.GetDamageInfo()->GetDamage()))
                    return;

                if (eventInfo.GetDamageInfo()->GetAttackType() != BASE_ATTACK && eventInfo.GetDamageInfo()->GetAttackType() != OFF_ATTACK)
                    return;

                int32 bp = eventInfo.GetDamageInfo()->GetDamage();

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    std::list<Creature*> tempList;
                    std::list<Creature*> statueList;
                    Creature* statue = NULL;

                    if (AuraPtr serpentsZeal = _player->GetAura(aurEff->GetSpellInfo()->Id))
                    {
                        if (serpentsZeal->GetStackAmount() < 2)
                            bp /= 4;
                        else
                            bp /= 2;
                    }

                    _player->GetCreatureListWithEntryInGrid(tempList, MONK_NPC_JADE_SERPENT_STATUE, 100.0f);
                    _player->GetCreatureListWithEntryInGrid(statueList, MONK_NPC_JADE_SERPENT_STATUE, 100.0f);

                    // Remove other players jade statue
                    for (std::list<Creature*>::iterator i = tempList.begin(); i != tempList.end(); ++i)
                    {
                        Unit* owner = (*i)->GetOwner();
                        if (owner && owner == _player && (*i)->isSummon())
                            continue;

                        statueList.remove((*i));
                    }

                    // you gain Serpent's Zeal causing you to heal nearby injured targets equal to 25% of your auto-attack damage. Stacks up to 2 times.
                    _player->CastCustomSpell(_player, SPELL_MONK_EMINENCE_HEAL, &bp, NULL, NULL, true);

                    if (statueList.size() == 1)
                    {
                        for (auto itrBis : statueList)
                            statue = itrBis;

                        if (statue && (statue->isPet() || statue->isGuardian()))
                            if (statue->GetOwner() && statue->GetOwner()->GetGUID() == _player->GetGUID())
                                statue->CastCustomSpell(statue, SPELL_MONK_EMINENCE_HEAL, &bp, NULL, NULL, true, 0, NULLAURA_EFFECT, _player->GetGUID()); // Eminence - statue
                    }
                }
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_monk_serpents_zeal_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_serpents_zeal_AuraScript();
        }
};

// Dampen Harm - 122278
class spell_monk_dampen_harm : public SpellScriptLoader
{
    public:
        spell_monk_dampen_harm() : SpellScriptLoader("spell_monk_dampen_harm") { }

        class spell_monk_dampen_harm_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_dampen_harm_AuraScript);

            uint32 healthPct;

            bool Load()
            {
                healthPct = GetSpellInfo()->Effects[EFFECT_0].CalcValue(GetCaster());
                return GetUnitOwner()->ToPlayer();
            }

            void CalculateAmount(constAuraEffectPtr /*auraEffect*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                amount = -1;
            }

            void Absorb(AuraEffectPtr auraEffect, DamageInfo& dmgInfo, uint32& absorbAmount)
            {
                Unit* target = GetTarget();

                uint32 health = target->CountPctFromMaxHealth(healthPct);

                if (dmgInfo.GetDamage() < health)
                {
                    PreventDefaultAction();
                    return;
                }

                // The next 3 attacks within 45 sec that deal damage equal to 10% or more of your total health are reduced by half
                absorbAmount = dmgInfo.GetDamage() / 2;
                auraEffect->GetBase()->DropCharge();
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_dampen_harm_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_monk_dampen_harm_AuraScript::Absorb, EFFECT_0);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_dampen_harm_AuraScript();
        }
};

// Called by Thunder Focus Tea - 116680
// Item S12 4P - Mistweaver - 124487
class spell_monk_item_s12_4p_mistweaver : public SpellScriptLoader
{
    public:
        spell_monk_item_s12_4p_mistweaver() : SpellScriptLoader("spell_monk_item_s12_4p_mistweaver") { }

        class spell_monk_item_s12_4p_mistweaver_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_item_s12_4p_mistweaver_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (_player->HasAura(SPELL_MONK_ITEM_4_S12_MISTWEAVER))
                        _player->CastSpell(_player, SPELL_MONK_ZEN_FOCUS, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_item_s12_4p_mistweaver_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_item_s12_4p_mistweaver_SpellScript();
        }
};

struct auraData
{
    auraData(uint32 id, uint64 casterGUID) : m_id(id), m_casterGuid(casterGUID) {}
    uint32 m_id;
    uint64 m_casterGuid;
};

// Diffuse Magic - 122783
class spell_monk_diffuse_magic : public SpellScriptLoader
{
    public:
        spell_monk_diffuse_magic() : SpellScriptLoader("spell_monk_diffuse_magic") { }

        class spell_monk_diffuse_magic_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_diffuse_magic_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    std::set<auraData*> auraListToRemove;
                    Unit::AuraApplicationMap AuraList = _player->GetAppliedAuras();
                    for (Unit::AuraApplicationMap::iterator iter = AuraList.begin(); iter != AuraList.end(); ++iter)
                    {
                        AuraPtr aura = iter->second->GetBase();
                        if (!aura)
                            continue;

                        Unit* caster = aura->GetCaster();
                        if (!caster || caster->GetGUID() == _player->GetGUID())
                            continue;

                        if (!caster->IsWithinDist(_player, 40.0f))
                            continue;

                        if (aura->GetSpellInfo()->IsPositive())
                            continue;

                        if (!(aura->GetSpellInfo()->GetSchoolMask() & SPELL_SCHOOL_MASK_MAGIC))
                            continue;

                        _player->AddAura(aura->GetSpellInfo()->Id, caster);

                        if (AuraPtr targetAura = caster->GetAura(aura->GetSpellInfo()->Id, _player->GetGUID()))
                        {
                            targetAura->SetDuration(aura->GetDuration());
                            targetAura->SetMaxDuration(aura->GetMaxDuration());
                            targetAura->SetCharges(aura->GetCharges());
                            targetAura->SetStackAmount(aura->GetStackAmount());
                            targetAura->SetNeedClientUpdateForTargets();

                            for (int i = 0; i < MAX_SPELL_EFFECTS; ++i)
                            {
                                if (targetAura->GetEffect(i) && aura->GetEffect(i))
                                {
                                    if (AuraEffectPtr targetAuraEffect = caster->GetAuraEffect(aura->GetSpellInfo()->Id, i, _player->GetGUID()))
                                    {
                                        if (AuraEffectPtr playerAuraEffect = _player->GetAuraEffect(aura->GetSpellInfo()->Id, i, caster->GetGUID()))
                                        {
                                            targetAuraEffect->GetFixedDamageInfo().SetFixedDamage(playerAuraEffect->GetFixedDamageInfo().GetFixedDamage());
                                            targetAuraEffect->GetFixedDamageInfo().SetFixedTotalDamage(playerAuraEffect->GetFixedDamageInfo().GetFixedTotalDamage());
                                            targetAuraEffect->GetFixedDamageInfo().SetCriticalChance(playerAuraEffect->GetFixedDamageInfo().GetCriticalChance());

                                            targetAuraEffect->SetAmount(playerAuraEffect->GetAmount());
                                            targetAuraEffect->SetAmplitude(playerAuraEffect->GetAmplitude());
                                        }
                                    }
                                }
                            }
                        }

                        auraListToRemove.insert(new auraData(aura->GetSpellInfo()->Id, caster->GetGUID()));
                    }

                    for (std::set<auraData*>::iterator itr = auraListToRemove.begin(); itr != auraListToRemove.end(); ++itr)
                    {
                        _player->RemoveAura((*itr)->m_id, (*itr)->m_casterGuid);
                        delete (*itr);
                    }

                    auraListToRemove.clear();
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_diffuse_magic_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_diffuse_magic_SpellScript();
        }
};

// Summon Black Ox Statue - 115315
class spell_monk_black_ox_statue : public SpellScriptLoader
{
    public:
        spell_monk_black_ox_statue() : SpellScriptLoader("spell_monk_black_ox_statue") { }

        class spell_monk_black_ox_statue_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_black_ox_statue_SpellScript)

            void HandleSummon(SpellEffIndex effIndex)
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    PreventHitDefaultEffect(effIndex);

                    const SpellInfo* spell = GetSpellInfo();
                    std::list<Creature*> tempList;
                    std::list<Creature*> blackOxList;

                    player->GetCreatureListWithEntryInGrid(tempList, MONK_NPC_BLACK_OX_STATUE, 500.0f);

                    for (auto itr : tempList)
                        blackOxList.push_back(itr);

                    // Remove other players jade statue
                    for (std::list<Creature*>::iterator i = tempList.begin(); i != tempList.end(); ++i)
                    {
                        Unit* owner = (*i)->GetOwner();
                        if (owner && owner == player && (*i)->isSummon())
                            continue;

                        blackOxList.remove((*i));
                    }

                    // 1 statue max
                    if ((int32)blackOxList.size() >= spell->Effects[effIndex].BasePoints)
                        blackOxList.back()->ToTempSummon()->UnSummon();

                    Position pos;
                    GetExplTargetDest()->GetPosition(&pos);
                    const SummonPropertiesEntry* properties = sSummonPropertiesStore.LookupEntry(spell->Effects[effIndex].MiscValueB);
                    TempSummon* summon = player->SummonCreature(spell->Effects[effIndex].MiscValue, pos, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, spell->GetDuration());
                    if (!summon)
                        return;

                    summon->SetUInt64Value(UNIT_FIELD_SUMMONEDBY, player->GetGUID());
                    summon->setFaction(player->getFaction());
                    summon->SetUInt32Value(UNIT_CREATED_BY_SPELL, GetSpellInfo()->Id);
                    summon->SetMaxHealth(player->CountPctFromMaxHealth(50));
                    summon->SetHealth(summon->GetMaxHealth());
                    summon->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_HEAL, true);
                    summon->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_PERIODIC_HEAL, true);
                    summon->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_HEAL_PCT, true);
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_monk_black_ox_statue_SpellScript::HandleSummon, EFFECT_0, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_black_ox_statue_SpellScript();
        }

        class spell_monk_black_ox_statue_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_black_ox_statue_AuraScript);

            uint32 damageDealed;

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                damageDealed = 0;
            }

            void SetData(uint32 type, uint32 data)
            {
                if (!GetCaster())
                    return;

                if (Player* _plr = GetCaster()->ToPlayer())
                {
                    uint32 value = _plr->GetTotalAttackPowerValue(BASE_ATTACK) * 16;

                    damageDealed += data;

                    if (damageDealed >= value)
                    {
                        damageDealed = 0;

                        std::list<Creature*> tempList;
                        std::list<Creature*> statueList;
                        Creature* statue;

                        _plr->GetCreatureListWithEntryInGrid(tempList, MONK_NPC_BLACK_OX_STATUE, 100.0f);
                        _plr->GetCreatureListWithEntryInGrid(statueList, MONK_NPC_BLACK_OX_STATUE, 100.0f);

                        // Remove other players jade statue
                        for (std::list<Creature*>::iterator i = tempList.begin(); i != tempList.end(); ++i)
                        {
                            Unit* owner = (*i)->GetOwner();
                            if (owner && owner->GetGUID() == _plr->GetGUID() && (*i)->isSummon())
                                continue;

                            statueList.remove((*i));
                        }

                        if (!statueList.empty() && statueList.size() == 1)
                        {
                            for (auto itr : statueList)
                                statue = itr;

                            if (statue && (statue->isPet() || statue->isGuardian()))
                            {
                                if (statue->GetOwner() && statue->GetOwner()->GetGUID() == _plr->GetGUID())
                                {
                                    std::list<Unit*> targets;
                                    std::list<Unit*> tempTargets;

                                    _plr->GetPartyMembers(tempTargets);

                                    for (auto itr : tempTargets)
                                    {
                                        if (itr->GetGUID() == statue->GetGUID() ||
                                            itr->GetGUID() == _plr->GetGUID())
                                            continue;

                                        targets.push_back(itr);
                                    }

                                    WoWSource::Containers::RandomResizeList(targets, 1);

                                    for (auto itr : targets)
                                        statue->CastSpell(itr, SPELL_MONK_GUARD, true);
                                }
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_monk_black_ox_statue_AuraScript::OnApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_black_ox_statue_AuraScript();
        }
};

// Guard - 115295
class spell_monk_guard : public SpellScriptLoader
{
    public:
        spell_monk_guard() : SpellScriptLoader("spell_monk_guard") { }

        class spell_monk_guard_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_guard_AuraScript);

            void CalculateAmount(constAuraEffectPtr /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (!GetCaster())
                    return;

                if (Player* _plr = GetCaster()->ToPlayer())
                {
                    amount += int32(_plr->GetTotalAttackPowerValue(BASE_ATTACK) * 1.971f);

                    if (_plr->HasAura(ITEM_MONK_T14_TANK_4P))
                        amount = int32(amount * 1.2f);
                }
                // For Black Ox Statue
                else if (GetCaster()->GetOwner())
                {
                    if (Player* _plr = GetCaster()->GetOwner()->ToPlayer())
                    {
                        amount += int32(_plr->GetTotalAttackPowerValue(BASE_ATTACK) * 1.971f);

                        if (_plr->HasAura(ITEM_MONK_T14_TANK_4P))
                            amount = int32(amount * 1.2f);
                        if (_plr->HasAura(145049))
                            _plr->CastCustomSpell(145051, SPELLVALUE_BASE_POINT0, CalculatePct(amount, 8), _plr, true);
                    }
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_guard_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_guard_AuraScript();
        }
};

// Bear Hug - 127361
class spell_monk_bear_hug : public SpellScriptLoader
{
    public:
        spell_monk_bear_hug() : SpellScriptLoader("spell_monk_bear_hug") { }

        class spell_monk_bear_hug_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_bear_hug_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (AuraPtr bearHug = target->GetAura(SPELL_MONK_BEAR_HUG, _player->GetGUID()))
                            if (bearHug->GetEffect(1))
                                bearHug->GetEffect(1)->SetAmount(_player->CountPctFromMaxHealth(2));
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_bear_hug_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_bear_hug_SpellScript();
        }
};

// Zen Flight - 125883
class spell_monk_zen_flight_check : public SpellScriptLoader
{
    public:
        spell_monk_zen_flight_check() : SpellScriptLoader("spell_monk_zen_flight_check") { }

        class spell_monk_zen_flight_check_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_zen_flight_check_SpellScript);

            SpellCastResult CheckTarget()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->GetMap()->IsRaidOrHeroicDungeon())
                        return SPELL_FAILED_NOT_IN_RAID_INSTANCE;

                    if (_player->GetMap()->IsBattlegroundOrArena())
                        return SPELL_FAILED_NOT_IN_BATTLEGROUND;

                    // In Kalimdor or Eastern Kingdom with Flight Master's License
                    if (!_player->HasSpell(90267) && (_player->GetMapId() == 1 || _player->GetMapId() == 0))
                        return SPELL_FAILED_NOT_HERE;

                    // In Pandaria with Wisdom of the Four Winds
                    if (!_player->HasSpell(115913) && (_player->GetMapId() == 870))
                        return SPELL_FAILED_NOT_HERE;
                }

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_monk_zen_flight_check_SpellScript::CheckTarget);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_zen_flight_check_SpellScript();
        }

        class spell_monk_zen_flight_check_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_zen_flight_check_AuraScript);

            bool Load()
            {
                return GetCaster() && GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            void CalculateAmount(constAuraEffectPtr /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (!GetCaster())
                    return;

                if (Player* caster = GetCaster()->ToPlayer())
                    if (caster->GetSkillValue(SKILL_RIDING) >= 375)
                        amount = 310;
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_zen_flight_check_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_MOD_INCREASE_VEHICLE_FLIGHT_SPEED);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_zen_flight_check_AuraScript();
        }
};

// Glyph of Zen Flight - 125893
class spell_monk_glyph_of_zen_flight : public SpellScriptLoader
{
    public:
        spell_monk_glyph_of_zen_flight() : SpellScriptLoader("spell_monk_glyph_of_zen_flight") { }

        class spell_monk_glyph_of_zen_flight_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_glyph_of_zen_flight_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->learnSpell(SPELL_MONK_ZEN_FLIGHT, false);
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    if (_player->HasSpell(SPELL_MONK_ZEN_FLIGHT))
                        _player->removeSpell(SPELL_MONK_ZEN_FLIGHT, false, false);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_monk_glyph_of_zen_flight_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_monk_glyph_of_zen_flight_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_glyph_of_zen_flight_AuraScript();
        }
};

// Called by Jab - 100780
// Power Strikes - 121817
class spell_monk_power_strikes : public SpellScriptLoader
{
    public:
        spell_monk_power_strikes() : SpellScriptLoader("spell_monk_power_strikes") { }

        class spell_monk_power_strikes_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_power_strikes_SpellScript)

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (_player->HasAura(SPELL_MONK_POWER_STRIKES_TALENT))
                        {
                            if (!_player->HasSpellCooldown(SPELL_MONK_POWER_STRIKES_TALENT))
                            {
                                if (_player->GetPower(POWER_CHI) < _player->GetMaxPower(POWER_CHI))
                                {
                                    _player->EnergizeBySpell(_player, GetSpellInfo()->Id, 1, POWER_CHI);
                                    _player->AddSpellCooldown(SPELL_MONK_POWER_STRIKES_TALENT, 0, time(NULL) + 20);
                                    _player->RemoveAura(SPELL_MONK_POWER_STRIKES_TALENT_EFFECT);
                                    _player->AddSpellCooldown(SPELL_MONK_POWER_STRIKES_TALENT_EFFECT, 0, time(NULL) + 20);
                                }
                                else
                                    _player->CastSpell(_player, SPELL_MONK_CREATE_CHI_SPHERE, true);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_power_strikes_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_power_strikes_SpellScript();
        }
};

// Crackling Jade Lightning - 117952
class spell_monk_crackling_jade_lightning : public SpellScriptLoader
{
    public:
        spell_monk_crackling_jade_lightning() : SpellScriptLoader("spell_monk_crackling_jade_lightning") { }

        class spell_monk_crackling_jade_lightning_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_crackling_jade_lightning_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (Unit* caster = GetCaster())
                {
                    if (roll_chance_i(30))
                        caster->CastSpell(caster, SPELL_MONK_JADE_LIGHTNING_ENERGIZE, true);
                    if (caster->HasAura(103985) || caster->HasAura(115069))
                        if (caster->GetPower(POWER_ENERGY) > 20)
                            caster->EnergizeBySpell(caster, GetSpellInfo()->Id, -20, POWER_ENERGY);
                        else
                            caster->CastStop();
                }
            }

            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                if (!GetCaster())
                    return;

                if (eventInfo.GetActor()->GetGUID() != GetTarget()->GetGUID())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (GetTarget()->HasAura(aurEff->GetSpellInfo()->Id, _player->GetGUID()))
                    {
                        if (!_player->HasSpellCooldown(SPELL_MONK_CRACKLING_JADE_SHOCK_BUMP))
                        {
                            _player->CastSpell(GetTarget(), SPELL_MONK_CRACKLING_JADE_SHOCK_BUMP, true);
                            _player->AddSpellCooldown(SPELL_MONK_CRACKLING_JADE_SHOCK_BUMP, 0, time(NULL) + 8);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_crackling_jade_lightning_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
                OnEffectProc += AuraEffectProcFn(spell_monk_crackling_jade_lightning_AuraScript::OnProc, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_crackling_jade_lightning_AuraScript();
        }
};

// Touch of Karma - 122470
class spell_monk_touch_of_karma : public SpellScriptLoader
{
    public:
        spell_monk_touch_of_karma() : SpellScriptLoader("spell_monk_touch_of_karma") { }

        class spell_monk_touch_of_karma_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_touch_of_karma_AuraScript);

            uint32 totalAbsorbAmount;

            bool Load()
            {
                totalAbsorbAmount = 0;
                return true;
            }

            void CalculateAmount(constAuraEffectPtr /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (GetCaster())
                    amount = GetCaster()->GetMaxHealth();
            }

            void OnAbsorb(AuraEffectPtr aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
            {
                if (Unit* caster = dmgInfo.getVictim())
                {
                    if (Unit* attacker = dmgInfo.GetAttacker())
                    {
                        totalAbsorbAmount += dmgInfo.GetDamage();

                        if (attacker->HasAura(aurEff->GetSpellInfo()->Id, caster->GetGUID()))
                            caster->CastCustomSpell(SPELL_MONK_TOUCH_OF_KARMA_REDIRECT_DAMAGE, SPELLVALUE_BASE_POINT0, (totalAbsorbAmount / 6), attacker);
                    }
                }
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
				if (Unit* caster =  GetCaster())
					if (caster->HasAura(SPELL_MONK_TOUCH_OF_KARMA))
						caster->RemoveAura(SPELL_MONK_TOUCH_OF_KARMA);
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_monk_touch_of_karma_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_monk_touch_of_karma_AuraScript::OnAbsorb, EFFECT_1);
                OnEffectRemove += AuraEffectRemoveFn(spell_monk_touch_of_karma_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_touch_of_karma_AuraScript();
        }
};

// Spinning Fire Blossom - 123408
class spell_monk_spinning_fire_blossom_damage : public SpellScriptLoader
{
    public:
        spell_monk_spinning_fire_blossom_damage() : SpellScriptLoader("spell_monk_spinning_fire_blossom_damage") { }

        class spell_monk_spinning_fire_blossom_damage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_spinning_fire_blossom_damage_SpellScript);

            SpellCastResult CheckTarget()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetExplTargetUnit())
                        if (_player->IsFriendlyTo(target))
                            return SPELL_FAILED_BAD_TARGETS;

                return SPELL_CAST_OK;
            }

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (target->GetDistance(_player) > 10.0f)
                        {
                            SetHitDamage(int32(GetHitDamage() * 1.5f));

                            if (!_player->HasAura(SPELL_MONK_GLYPH_OF_SPINNING_FIRE_BLOSSOM))
                                _player->CastSpell(target, SPELL_MONK_SPINNING_FIRE_BLOSSOM_ROOT, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_monk_spinning_fire_blossom_damage_SpellScript::CheckTarget);
                OnHit += SpellHitFn(spell_monk_spinning_fire_blossom_damage_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_spinning_fire_blossom_damage_SpellScript();
        }
};

// Spinning Fire Blossom - 115073
class spell_monk_spinning_fire_blossom : public SpellScriptLoader
{
    public:
        spell_monk_spinning_fire_blossom() : SpellScriptLoader("spell_monk_spinning_fire_blossom") { }

        class spell_monk_spinning_fire_blossom_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_spinning_fire_blossom_SpellScript)

            void HandleAfterCast()
            {
                if (!GetCaster())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    std::list<Unit*> targetList;
                    float range = 50.f;
                    uint32 filterMask = 0;

                    filterMask |= EXCLUDE_ALLIES;
                    filterMask |= ONLY_ARC;
                    filterMask |= ONLY_LOS;

                    _player->FilterTargets(targetList, range, filterMask, 1, NULL, DistanceOrderPred);

                    if (!targetList.empty())
                    {
                        for (auto itr : targetList)
                            _player->CastSpell(itr, SPELL_MONK_SPINNING_FIRE_BLOSSOM_DAMAGE, true);
                    }
                    else
                        _player->CastSpell(_player, SPELL_MONK_SPINNING_FIRE_BLOSSOM_MISSILE, true);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_monk_spinning_fire_blossom_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_spinning_fire_blossom_SpellScript();
        }
};

// Path of Blossom - 124336
class spell_monk_path_of_blossom : public SpellScriptLoader
{
    public:
        spell_monk_path_of_blossom() : SpellScriptLoader("spell_monk_path_of_blossom") { }

        class spell_monk_path_of_blossom_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_path_of_blossom_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (GetCaster())
                    GetCaster()->CastSpell(GetCaster(), SPELL_MONK_PATH_OF_BLOSSOM_AREATRIGGER, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_path_of_blossom_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_path_of_blossom_AuraScript();
        }
};

// Called by Uplift - 116670 and Uplift - 130316
// Thunder Focus Tea - 116680
class spell_monk_thunder_focus_tea : public SpellScriptLoader
{
    public:
        spell_monk_thunder_focus_tea() : SpellScriptLoader("spell_monk_thunder_focus_tea") { }

        class spell_monk_thunder_focus_tea_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_thunder_focus_tea_SpellScript)

            bool hasTea;

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                hasTea = false;
                if (AuraPtr aur = GetCaster()->GetAura(SPELL_MONK_THUNDER_FOCUS_TEA))
                {
                    hasTea = true;
                    aur->Remove();
                }

                unitList.remove_if(WoWSource::UnitAuraCheck(false, SPELL_MONK_RENEWING_MIST_HOT, GetCaster()->GetGUID()));
            }

            void HandleOnHit(SpellEffIndex effIndex)
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (hasTea)
                        {
                            if (AuraPtr renewingMist = target->GetAura(SPELL_MONK_RENEWING_MIST_HOT, _player->GetGUID()))
                                renewingMist->RefreshDuration();
                        }
                    }
                }
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_monk_thunder_focus_tea_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
                OnEffectHitTarget += SpellEffectFn(spell_monk_thunder_focus_tea_SpellScript::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_thunder_focus_tea_SpellScript();
        }
};

// Summon Jade Serpent Statue - 115313
class spell_monk_jade_serpent_statue : public SpellScriptLoader
{
    public:
        spell_monk_jade_serpent_statue() : SpellScriptLoader("spell_monk_jade_serpent_statue") { }

        class spell_monk_jade_serpent_statue_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_jade_serpent_statue_SpellScript)

            void HandleSummon(SpellEffIndex effIndex)
            {
                if (!GetCaster())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    PreventHitDefaultEffect(effIndex);

                    const SpellInfo* spell = GetSpellInfo();
                    std::list<Creature*> tempList;
                    std::list<Creature*> jadeSerpentlist;

                    if (_player)
                    {
                        _player->GetCreatureListWithEntryInGrid(tempList, MONK_NPC_JADE_SERPENT_STATUE, 500.0f);
                        _player->GetCreatureListWithEntryInGrid(jadeSerpentlist, MONK_NPC_JADE_SERPENT_STATUE, 500.0f);
                    }

                    // Remove other players jade statue
                    for (std::list<Creature*>::iterator i = tempList.begin(); i != tempList.end(); ++i)
                    {
                        Unit* owner = (*i)->GetOwner();
                        if (owner && owner == _player && (*i)->isSummon())
                            continue;

                        jadeSerpentlist.remove((*i));
                    }

                    // 1 statue max
                    if ((int32)jadeSerpentlist.size() >= spell->Effects[effIndex].BasePoints)
                        jadeSerpentlist.back()->ToTempSummon()->UnSummon();

                    Position pos;
                    GetExplTargetDest()->GetPosition(&pos);
                    const SummonPropertiesEntry* properties = sSummonPropertiesStore.LookupEntry(spell->Effects[effIndex].MiscValueB);
                    TempSummon* summon = _player->SummonCreature(spell->Effects[effIndex].MiscValue, pos, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, spell->GetDuration());
                    if (!summon)
                        return;

                    summon->SetUInt64Value(UNIT_FIELD_SUMMONEDBY, _player->GetGUID());
                    summon->setFaction(_player->getFaction());
                    summon->SetUInt32Value(UNIT_CREATED_BY_SPELL, GetSpellInfo()->Id);
                    summon->SetMaxHealth(_player->CountPctFromMaxHealth(50));
                    summon->SetHealth(summon->GetMaxHealth());
                    summon->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_HEAL, true);
                    summon->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_PERIODIC_HEAL, true);
                    summon->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_HEAL_PCT, true);
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_monk_jade_serpent_statue_SpellScript::HandleSummon, EFFECT_0, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_jade_serpent_statue_SpellScript();
        }
};

// Called by Spinning Crane Kick - 107270 and Rushing Jade Wind - 148187
// Teachings of the Monastery - 116645
class spell_monk_teachings_of_the_monastery : public SpellScriptLoader
{
    public:
        spell_monk_teachings_of_the_monastery() : SpellScriptLoader("spell_monk_teachings_of_the_monastery") { }

        class spell_monk_teachings_of_the_monastery_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_teachings_of_the_monastery_SpellScript);

            void HandleAfterCast()
            {
                if (GetCaster())
                    if (GetCaster()->HasAura(118672))
                        GetCaster()->CastSpell(GetCaster(), SPELL_MONK_SPINNING_CRANE_KICK_HEAL, true);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_monk_teachings_of_the_monastery_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_teachings_of_the_monastery_SpellScript();
        }
};

// Mana Tea - 115294
class spell_monk_mana_tea : public SpellScriptLoader
{
    public:
        spell_monk_mana_tea() : SpellScriptLoader("spell_monk_mana_tea") { }

        class spell_monk_mana_tea_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_mana_tea_SpellScript);

            SpellModifier* spellMod;

            void HandleBeforeCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    int32 stacks = 0;

                    if (AuraPtr manaTeaStacks = _player->GetAura(SPELL_MONK_MANA_TEA_STACKS))
                        stacks = manaTeaStacks->GetStackAmount();

                    int32 newDuration = (stacks * IN_MILLISECONDS) / 2;

                    spellMod = new SpellModifier();
                    spellMod->op = SPELLMOD_DURATION;
                    spellMod->type = SPELLMOD_FLAT;
                    spellMod->spellId = SPELL_MONK_MANA_TEA_REGEN;
                    spellMod->value = newDuration;
                    spellMod->mask[1] = 0x200000;
                    spellMod->mask[2] = 0x1;

                    _player->AddSpellMod(spellMod, true);
                }
            }

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    _player->AddSpellMod(spellMod, false);
                    if (AuraApplication* aura = _player->GetAuraApplication(SPELL_MONK_MANA_TEA_REGEN))
                    {
                        AuraPtr manaTea = aura->GetBase();
                        int32 newDuration = manaTea->GetDuration() - 1000;
                        manaTea->SetDuration(newDuration);
                    }
                }
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_monk_mana_tea_SpellScript::HandleBeforeCast);
                AfterCast += SpellCastFn(spell_monk_mana_tea_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_mana_tea_SpellScript();
        }

        class spell_monk_mana_tea_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_mana_tea_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (GetCaster())
                {
                    // remove one charge per tick instead of remove aura on cast
                    // "Cancelling the channel will not waste stacks"
                    if (AuraPtr manaTea = GetCaster()->GetAura(SPELL_MONK_MANA_TEA_STACKS))
                    {
                        if (manaTea->GetStackAmount() > 1)
                            manaTea->SetStackAmount(manaTea->GetStackAmount() - 1);
                        else
                            GetCaster()->RemoveAura(SPELL_MONK_MANA_TEA_STACKS);
                    }
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_mana_tea_AuraScript::OnTick, EFFECT_0, SPELL_AURA_OBS_MOD_POWER);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_mana_tea_AuraScript();
        }
};

// Brewing : Mana Tea - 123766
class spell_monk_mana_tea_stacks : public SpellScriptLoader
{
    public:
        spell_monk_mana_tea_stacks() : SpellScriptLoader("spell_monk_mana_tea_stacks") { }

        class spell_monk_mana_tea_stacks_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_mana_tea_stacks_AuraScript);

            uint32 chiConsumed;

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                chiConsumed = 0;
            }

            void SetData(uint32 type, uint32 data)
            {
                while ((chiConsumed += data) >= 4)
                {
                    chiConsumed = 0;
                    data = data > 4 ? data - 4: 0;

                    if (GetCaster())
                    {
                        GetCaster()->CastSpell(GetCaster(), SPELL_MONK_MANA_TEA_STACKS, true);
                        GetCaster()->CastSpell(GetCaster(), SPELL_MONK_PLUS_ONE_MANA_TEA, true);
                    }
                }
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_monk_mana_tea_stacks_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_mana_tea_stacks_AuraScript();
        }
};

/*######
## spell_monk_detox - 115450
######*/

class spell_monk_detox : public SpellScriptLoader
{
public:
    spell_monk_detox() : SpellScriptLoader("spell_monk_detox") { }

    class spell_monk_detox_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_detox_SpellScript);

        SpellCastResult CheckCleansing()
        {
            if (Unit* caster = GetCaster())
            {
                if (Unit* target = GetExplTargetUnit())
                {
                    DispelChargesList dispelList[MAX_SPELL_EFFECTS];

                    // Create dispel mask by dispel type
                    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
                    {
                        uint32 dispel_type = GetSpellInfo()->Effects[i].MiscValue;
                        uint32 dispelMask = GetSpellInfo()->GetDispelMask(DispelType(dispel_type));

                        // Detox can dispell all Curse and poison, and if has Internal Medicine, also dispell all Magic
                        if (caster->HasAura(SPELL_MONK_INTERNAL_MEDICINE))
                            dispelMask = ((1 << DISPEL_MAGIC) | (1 << DISPEL_POISON) | (1 << DISPEL_DISEASE));
                        else
                            dispelMask = ((1 << DISPEL_POISON) | (1 << DISPEL_DISEASE));

                        target->GetDispellableAuraList(caster, dispelMask, dispelList[i]);
                    }

                    bool empty = true;
                    for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
                    {
                        if (dispelList[i].empty())
                            continue;

                        empty = false;
                        break;
                    }

                    if (empty)
                        return SPELL_FAILED_NOTHING_TO_DISPEL;

                    return SPELL_CAST_OK;
                }
            }

            return SPELL_CAST_OK;
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_monk_detox_SpellScript::CheckCleansing);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_monk_detox_SpellScript();
    }
};

// Enveloping Mist - 124682
class spell_monk_enveloping_mist : public SpellScriptLoader
{
    public:
        spell_monk_enveloping_mist() : SpellScriptLoader("spell_monk_enveloping_mist") { }

        class spell_monk_enveloping_mist_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_enveloping_mist_SpellScript);

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetExplTargetUnit())
                        _player->CastSpell(target, SPELL_MONK_ENVELOPING_MIST_HEAL, true);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_monk_enveloping_mist_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_enveloping_mist_SpellScript();
        }
};

// Surging Mist - 116694
class spell_monk_surging_mist : public SpellScriptLoader
{
    public:
        spell_monk_surging_mist() : SpellScriptLoader("spell_monk_surging_mist") { }

        class spell_monk_surging_mist_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_surging_mist_SpellScript);

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetExplTargetUnit())
                        _player->CastSpell(target, SPELL_MONK_SURGING_MIST_HEAL, true);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_monk_surging_mist_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_surging_mist_SpellScript();
        }
};

// Glyph of Surging Mist
// Called by Surging Mist - 123273
class spell_monk_glyph_of_surging_mist : public SpellScriptLoader
{
public:
    spell_monk_glyph_of_surging_mist() : SpellScriptLoader("spell_monk_glyph_of_surging_mist") { }

    class spell_monk_glyph_of_surging_mist_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_glyph_of_surging_mist_SpellScript);

        void HandleOnCast()
        {
            if (GetCaster())
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    std::list<Unit*> targetList;
                    float range = 40.0f;
                    uint32 filterMask = 0;

                    filterMask |= EXCLUDE_ENEMIES;
                    filterMask |= ONLY_LOS;
                    filterMask |= ONLY_RAID_MEMBERS;

                    _player->FilterTargets(targetList, range, filterMask, 1, NULL, HealthPctOrderPred);

                    for (auto itr : targetList)
                        _player->CastSpell(itr, SPELL_MONK_SURGING_MIST_HEAL, true);
                }
            }
        }

        void Register()
        {
            OnCast += SpellCastFn(spell_monk_glyph_of_surging_mist_SpellScript::HandleOnCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_monk_glyph_of_surging_mist_SpellScript();
    }
};

// Renewing Mist - 119611
class spell_monk_renewing_mist : public SpellScriptLoader
{
public:
    spell_monk_renewing_mist() : SpellScriptLoader("spell_monk_renewing_mist") { }

    class spell_monk_renewing_mist_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_renewing_mist_AuraScript);

        void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Unit* caster = GetCaster())
            {
                if (Player* player = caster->ToPlayer())
                    player->AddAura(SPELL_MONK_UPLIFT_ALLOWING_CAST, player);
            }
        }

        void OnTick(constAuraEffectPtr aurEff)
        {
            if (Unit* caster = GetCaster())
            {
                if (Player* player = caster->ToPlayer())
                {
                    if (Unit* target = GetTarget())
                    {
                        player->AddAura(SPELL_MONK_UPLIFT_ALLOWING_CAST, player);

                        if (player->HasAura(145449))
                        {
                            if (roll_chance_i(4))
                                player->CastSpell(target, 149112, true);
                        }

                        std::list<Unit*> nextTarget;
                        int32 range = player->HasAura(SPELL_MONK_GLYPH_OF_RENEWING_MIST) ? 40 : 20;
uint32 filterMask = (EXCLUDE_ENEMIES | ONLY_LOS | ONLY_RAID_MEMBERS | HAS_NOT_SPECIFIC_AURA);

                        target->FilterTargets(nextTarget, range, filterMask, 1, target, HealthPctOrderPred, 0.f, SPELL_MONK_RENEWING_MIST_HOT, player->GetGUID());

                        if (AuraPtr renewingMistHot = target->GetAura(SPELL_MONK_RENEWING_MIST_HOT, player->GetGUID()))
                        {
                            if (!nextTarget.empty())
                            {
                                for (auto itr : nextTarget)
                                {
                                    int32 charges = renewingMistHot->GetCharges();

                                    if (charges > 1)
                                    {
                                        renewingMistHot->SetCharges(1);

                                        player->AddAura(SPELL_MONK_RENEWING_MIST_HOT, itr);
                                        target->SendPlaySpellVisual(23997, itr, 30.0f); // Renewing Mist Visual

                                        if (AuraPtr aoeRenewingMistHot = itr->GetAura(SPELL_MONK_RENEWING_MIST_HOT, player->GetGUID()))
                                            aoeRenewingMistHot->SetCharges(charges - 1);
                                    }
                                }
                            }
                            else
                                renewingMistHot->SetCharges(1);                    
                        }
                    }
                }
            }
        }

        void HandleDispel(DispelInfo* dispelInfo)
        {
            if (Unit* caster = GetCaster())
            {
                if (Player* player = caster->ToPlayer())
                {
                    if (player->HasAura(SPELL_MONK_ITEM_2_S12_MISTWEAVER))
                    {
                        player->CastSpell(player, SPELL_MONK_MANA_TEA_STACKS, true);
                        player->CastSpell(player, SPELL_MONK_PLUS_ONE_MANA_TEA, true);
                    }
                }
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_monk_renewing_mist_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_renewing_mist_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
            AfterDispel += AuraDispelFn(spell_monk_renewing_mist_AuraScript::HandleDispel);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_monk_renewing_mist_AuraScript();
    }
};

// Called by : Fortifying Brew - 115203, Chi Brew - 115399, Elusive Brew - 115308, Tigereye Brew - 116740
// Purifying Brew - 119582, Mana Tea - 115294, Thunder Focus Tea - 116680 and Energizing Brew - 115288
// Healing Elixirs - 122280
class spell_monk_healing_elixirs : public SpellScriptLoader
{
    public:
        spell_monk_healing_elixirs() : SpellScriptLoader("spell_monk_healing_elixirs") { }

        class spell_monk_healing_elixirs_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_healing_elixirs_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasAura(SPELL_MONK_HEALING_ELIXIRS_AURA))
                    {
                        int32 bp = 10;

                        if (!_player->HasSpellCooldown(SPELL_MONK_HEALING_ELIXIRS_RESTORE_HEALTH))
                        {
                            _player->CastCustomSpell(_player, SPELL_MONK_HEALING_ELIXIRS_RESTORE_HEALTH, &bp, NULL, NULL, true);
                            // This effect cannot occur more than once per 18s
                            _player->AddSpellCooldown(SPELL_MONK_HEALING_ELIXIRS_RESTORE_HEALTH, 0, time(NULL) + 18);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_healing_elixirs_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_healing_elixirs_SpellScript();
        }
};

// Zen Sphere - 124081
class spell_monk_zen_sphere : public SpellScriptLoader
{
public:
	spell_monk_zen_sphere() : SpellScriptLoader("spell_monk_zen_sphere") { }

	class spell_monk_zen_sphere_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_monk_zen_sphere_AuraScript);

		void OnTick(constAuraEffectPtr aurEff)
		{
			if (!GetCaster())
				return;

			if (Player* _player = GetCaster()->ToPlayer())
				_player->CastSpell(_player, SPELL_MONK_ZEN_SPHERE_DAMAGE, true);
		}


		void HandleRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
		{
			if (GetCaster() && GetTarget())
			{
				AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
				if (removeMode == AURA_REMOVE_BY_EXPIRE)
				{
					GetCaster()->CastSpell(GetCaster(), SPELL_MONK_ZEN_SPHERE_DETONATE_HEAL, true);
					GetCaster()->CastSpell(GetCaster(), SPELL_MONK_ZEN_SPHERE_DETONATE_DAMAGE, true);
				}
			}
		}

		void HandleDispel(DispelInfo* dispelInfo)
		{
			if (GetCaster() && GetTarget())
			{
				GetCaster()->CastSpell(GetCaster(), SPELL_MONK_ZEN_SPHERE_DETONATE_HEAL, true);
				GetCaster()->CastSpell(GetCaster(), SPELL_MONK_ZEN_SPHERE_DETONATE_HEAL, true);
			}
		}

		void Register()
		{
			OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_zen_sphere_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
			OnEffectRemove += AuraEffectApplyFn(spell_monk_zen_sphere_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
			AfterDispel += AuraDispelFn(spell_monk_zen_sphere_AuraScript::HandleDispel);
		}
	};

	AuraScript* GetAuraScript() const
	{
		return new spell_monk_zen_sphere_AuraScript();
	}
};

// Chi Burst - 123986
class spell_monk_chi_burst : public SpellScriptLoader
{
    public:
        spell_monk_chi_burst() : SpellScriptLoader("spell_monk_chi_burst") { }

        class spell_monk_chi_burst_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_chi_burst_SpellScript);

            void HandleOnCast()
            {
                if (!GetCaster())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    float x, y;

                    _player->GetNearPoint2D(x, y, GetSpellInfo()->Effects[0].CalcRadius(_player) * GetSpellValue()->RadiusMod, _player->GetOrientation());

                    if (Creature* pointOfReference = _player->SummonCreature(WORLD_TRIGGER, x, y, _player->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 100))
                        _player->CastSpell(pointOfReference, SPELL_MONK_CHI_BURST_VISUAL, true);
                }
            }
            void Register()
            {
                OnCast += SpellCastFn(spell_monk_chi_burst_SpellScript::HandleOnCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_chi_burst_SpellScript();
        }
};

// Energizing Brew - 115288
class spell_monk_energizing_brew : public SpellScriptLoader
{
    public:
        spell_monk_energizing_brew() : SpellScriptLoader("spell_monk_energizing_brew") { }

        class spell_monk_energizing_brew_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_energizing_brew_SpellScript);

            SpellCastResult CheckFight()
            {
                if (!GetCaster()->isInCombat())
                    return SPELL_FAILED_CASTER_AURASTATE;
                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_monk_energizing_brew_SpellScript::CheckFight);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_energizing_brew_SpellScript();
        }
};

// Spear Hand Strike - 116705
class spell_monk_spear_hand_strike : public SpellScriptLoader
{
    public:
        spell_monk_spear_hand_strike() : SpellScriptLoader("spell_monk_spear_hand_strike") { }

        class spell_monk_spear_hand_strike_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_spear_hand_strike_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (target->isInFront(_player))
                        {
                            _player->CastSpell(target, SPELL_MONK_SPEAR_HAND_STRIKE_SILENCE, true);
                            _player->AddSpellCooldown(116705, 0, time(NULL) + 15);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_spear_hand_strike_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_spear_hand_strike_SpellScript();
        }
};

// Tigereye Brew - 116740
class spell_monk_tigereye_brew : public SpellScriptLoader
{
    public:
        spell_monk_tigereye_brew() : SpellScriptLoader("spell_monk_tigereye_brew") { }

        class spell_monk_tigereye_brew_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_tigereye_brew_SpellScript);

            bool Validate()
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MONK_TIGEREYE_BREW))
                    return false;
                return true;
            }

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        int32 stacks = 0;
                        //if (AuraApplication* aura = _player->GetAuraApplication(SPELL_MONK_TIGEREYE_BREW_STACKS, _player->GetGUID()))
                        if (AuraPtr tigereyeBrewStacks = _player->GetAura(SPELL_MONK_TIGEREYE_BREW_STACKS))
                        {
                            int32 effectAmount = tigereyeBrewStacks->GetStackAmount() * 6;
                            stacks = tigereyeBrewStacks->GetStackAmount();

                            if (stacks >= 10)
                                effectAmount = 60;

                            if (_player->HasAura(138315))
                            {
                                if (stacks > 10)
                                    effectAmount += 5;
                                else
                                    effectAmount += CalculatePct(stacks, 50);
                            }
 
                            AuraApplication* tigereyeBrew = _player->GetAuraApplication(SPELL_MONK_TIGEREYE_BREW, _player->GetGUID());
                            if (tigereyeBrew)
                            {
                                tigereyeBrew->GetBase()->GetEffect(0)->ChangeAmount(effectAmount);
                                tigereyeBrew->GetBase()->GetEffect(1)->ChangeAmount(effectAmount);
                            }
                            if (_player->HasAura(145022))
                            {
                                int32 amount = 0;
                                if (stacks >= 10)
                                    amount = 10;
                                else
                                    amount = stacks;
                                _player->CastCustomSpell(145024, SPELLVALUE_BASE_POINT0, amount, _player, true);
                            }

                            if (stacks >= 10)
                            {
                                tigereyeBrewStacks->SetStackAmount(stacks - 10);

                                if (stacks != 20)
                                {
                                    if (_player->HasAura(SPELL_MONK_TIGEREYE_BREW_VISUAL))
                                        _player->RemoveAura(SPELL_MONK_TIGEREYE_BREW_VISUAL);
                                }
                            }
                            else
                                _player->RemoveAura(SPELL_MONK_TIGEREYE_BREW_STACKS);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_tigereye_brew_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_tigereye_brew_SpellScript();
        }
};

// Tiger's Lust - 116841
class spell_monk_tigers_lust : public SpellScriptLoader
{
    public:
        spell_monk_tigers_lust() : SpellScriptLoader("spell_monk_tigers_lust") { }

        class spell_monk_tigers_lust_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_tigers_lust_SpellScript);

            bool Validate()
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MONK_FLYING_SERPENT_KICK_NEW))
                    return false;
                return true;
            }

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        target->RemoveMovementImpairingAuras();
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_tigers_lust_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_tigers_lust_SpellScript();
        }
};

// Flying Serpent Kick - 101545
class spell_monk_flying_serpent_kick_travel : public SpellScriptLoader
{
public:
    spell_monk_flying_serpent_kick_travel() : SpellScriptLoader("spell_monk_flying_serpent_kick_travel") { }

    class spell_monk_flying_serpent_kick_travel_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_flying_serpent_kick_travel_AuraScript);

        void OnTick(constAuraEffectPtr aurEff)
        {
            if (GetCaster())
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (!_player->HasAura(SPELL_MONK_GLYPH_OF_FLYING_SERPENT_KICK))
                        return;

                    if (aurEff->GetTickNumber() > 2)
                    {
                        std::list<Unit*> targetList;
                        float range = 5.0f;

                        _player->FilterTargets(targetList, range, EXCLUDE_ALLIES);

                        for (auto itr : targetList)
                            _player->CastSpell(_player, SPELL_MONK_FLYING_SERPENT_KICK_NEW, true);
                    }
                }
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_flying_serpent_kick_travel_AuraScript::OnTick, EFFECT_6, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_monk_flying_serpent_kick_travel_AuraScript();
    }
};

// Flying Serpent Kick - 115057
class spell_monk_flying_serpent_kick : public SpellScriptLoader
{
    public:
        spell_monk_flying_serpent_kick() : SpellScriptLoader("spell_monk_flying_serpent_kick") { }

        class spell_monk_flying_serpent_kick_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_flying_serpent_kick_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MONK_FLYING_SERPENT_KICK_NEW))
                    return false;
                return true;
            }

            void HandleOnCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Player* _player = caster->ToPlayer())
                    {
                        if (_player->HasAura(SPELL_MONK_FLYING_SERPENT_KICK))
                            _player->RemoveAura(SPELL_MONK_FLYING_SERPENT_KICK);

                        if (caster->HasAura(SPELL_MONK_ITEM_PVP_GLOVES_BONUS))
                            caster->RemoveAurasByType(SPELL_AURA_MOD_DECREASE_SPEED);

                        _player->CastSpell(_player, SPELL_MONK_FLYING_SERPENT_KICK_AOE, true);
                    }
                }
            }

            void Register()
            {
                OnCast += SpellCastFn(spell_monk_flying_serpent_kick_SpellScript::HandleOnCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_flying_serpent_kick_SpellScript();
        }
};

// Chi Torpedo - 115008 or Chi Torpedo (3 charges) - 121828
class spell_monk_chi_torpedo : public SpellScriptLoader
{
    public:
        spell_monk_chi_torpedo() : SpellScriptLoader("spell_monk_chi_torpedo") { }

        class spell_monk_chi_torpedo_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_chi_torpedo_SpellScript);

            void HandleAfterCast()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Player* _player = caster->ToPlayer())
                    {
                        if (caster->HasAura(SPELL_MONK_ITEM_PVP_GLOVES_BONUS))
                            caster->RemoveAurasByType(SPELL_AURA_MOD_DECREASE_SPEED);
                    }
                }
            }

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Player* player = caster->ToPlayer())
                    {
                        if (Unit* target = GetHitUnit())
                        {
                            float distance = player->GetDistance(target) / 20;
                            int32 maxTime = 1100;
                            maxTime *= distance;

                            uint32 spell = player->IsValidAttackTarget(target) ? SPELL_MONK_CHI_TORPEDO_DAMAGE : SPELL_MONK_CHI_TORPEDO_HEAL;
                            player->CastWithDelay(maxTime, target, spell, true);
                        }
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_monk_chi_torpedo_SpellScript::HandleAfterCast);
                OnHit += SpellHitFn(spell_monk_chi_torpedo_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_chi_torpedo_SpellScript();
        }
};

// Purifying Brew - 119582
class spell_monk_purifying_brew : public SpellScriptLoader
{
    public:
        spell_monk_purifying_brew() : SpellScriptLoader("spell_monk_purifying_brew") { }

        class spell_monk_purifying_brew_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_purifying_brew_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Player* _player = caster->ToPlayer())
                    {
                        AuraApplication* staggerAmount = _player->GetAuraApplication(SPELL_MONK_LIGHT_STAGGER);

                        if (!staggerAmount)
                            staggerAmount = _player->GetAuraApplication(SPELL_MONK_MODERATE_STAGGER);
                        if (!staggerAmount)
                            staggerAmount = _player->GetAuraApplication(SPELL_MONK_HEAVY_STAGGER);
                        if (_player->HasAura(145055))
                        {
                            int32 amount = 0;
                            if (staggerAmount)
                            {
                                amount = staggerAmount->GetBase()->GetEffect(0)->GetAmount() * (10 - staggerAmount->GetBase()->GetEffect(0)->GetTickNumber());
                                ApplyPct(amount, 15);
                            }
                            _player->CastCustomSpell(145056, SPELLVALUE_BASE_POINT0, amount, _player, true);
                        }

                        if (staggerAmount)
                            _player->RemoveAura(staggerAmount->GetBase()->GetId());
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_purifying_brew_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_purifying_brew_SpellScript();
        }
};

// Clash - 122057 and Clash - 126449
class spell_monk_clash : public SpellScriptLoader
{
    public:
        spell_monk_clash() : SpellScriptLoader("spell_monk_clash") { }

        class spell_monk_clash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_clash_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Player* _player = caster->ToPlayer())
                    {
                        if (Unit* target = GetHitUnit())
                        {
                            int32 basePoint = 2;
                            _player->CastCustomSpell(target, SPELL_MONK_CLASH_CHARGE, &basePoint, NULL, NULL, true);
                            target->CastSpell(_player, SPELL_MONK_CLASH_CHARGE, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_clash_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_clash_SpellScript();
        }
};

// Keg Smash - 121253
class spell_monk_keg_smash : public SpellScriptLoader
{
    public:
        spell_monk_keg_smash() : SpellScriptLoader("spell_monk_keg_smash") { }

        class spell_monk_keg_smash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_keg_smash_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Player* _player = caster->ToPlayer())
                    {
                        if (Unit* target = GetHitUnit())
                        {
                            _player->CastSpell(target, SPELL_MONK_KEG_SMASH_VISUAL, true);
                            _player->CastSpell(target, SPELL_MONK_WEAKENED_BLOWS, true);
                            _player->CastSpell(_player, SPELL_MONK_KEG_SMASH_ENERGIZE, true);
                            // Prevent to receive 2 CHI more than once time per cast
                            _player->AddSpellCooldown(SPELL_MONK_KEG_SMASH_ENERGIZE, 0, time(NULL) + 1);
                            _player->CastSpell(target, SPELL_MONK_DIZZYING_HAZE, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_keg_smash_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_keg_smash_SpellScript();
        }
};

// Elusive Brew - 115308
class spell_monk_elusive_brew : public SpellScriptLoader
{
    public:
        spell_monk_elusive_brew() : SpellScriptLoader("spell_monk_elusive_brew") { }

        class spell_monk_elusive_brew_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_elusive_brew_SpellScript);

            void HandleOnHit()
            {
                int32 stackAmount = 0;

                if (Unit* caster = GetCaster())
                {
                    if (Player* _player = caster->ToPlayer())
                    {
                        if (AuraApplication* brewStacks = _player->GetAuraApplication(SPELL_MONK_ELUSIVE_BREW_STACKS))
                            stackAmount = brewStacks->GetBase()->GetStackAmount();

                        _player->AddAura(SPELL_MONK_ELUSIVE_BREW, _player);

                        if (_player->HasAura(138231))
                        {
                            if (AuraPtr aura = _player->AddAura(138233, _player))
                                aura->SetDuration(stackAmount * 1000);
                        }

                        if (AuraApplication* aura = _player->GetAuraApplication(SPELL_MONK_ELUSIVE_BREW))
                        {
                            AuraPtr elusiveBrew = aura->GetBase();
                            int32 maxDuration = elusiveBrew->GetMaxDuration();
                            int32 newDuration = stackAmount * 1000;
                            elusiveBrew->SetDuration(newDuration);

                            if (newDuration > maxDuration)
                                elusiveBrew->SetMaxDuration(newDuration);

                            _player->RemoveAura(SPELL_MONK_ELUSIVE_BREW_STACKS);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_elusive_brew_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_elusive_brew_SpellScript();
        }
};

// Breath of Fire - 115181
class spell_monk_breath_of_fire : public SpellScriptLoader
{
    public:
        spell_monk_breath_of_fire() : SpellScriptLoader("spell_monk_breath_of_fire") { }

        class spell_monk_breath_of_fire_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_breath_of_fire_SpellScript);

            void HandleAfterHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Player* _player = caster->ToPlayer())
                    {
                        if (Unit* target = GetHitUnit())
                        {
                            // if Dizzying Haze is on the target, they will burn for an additionnal damage over 8s
                            if (target->HasAura(SPELL_MONK_DIZZYING_HAZE))
                            {
                                _player->CastSpell(target, SPELL_MONK_BREATH_OF_FIRE_DOT, true);

                                // Glyph of Breath of Fire
                                if (_player->HasAura(123394))
                                    _player->CastSpell(target, SPELL_MONK_BREATH_OF_FIRE_CONFUSED, true);
                            }
                        }
                    }
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_monk_breath_of_fire_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_breath_of_fire_SpellScript();
        }
};

// Soothing Mist - 115175
class spell_monk_soothing_mist : public SpellScriptLoader
{
    public:
        spell_monk_soothing_mist() : SpellScriptLoader("spell_monk_soothing_mist") { }

        class spell_monk_soothing_mist_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_soothing_mist_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster())
                    return;

                if (Unit* target = GetTarget())
                    target->CastSpell(target, SPELL_MONK_SOOTHING_MIST_VISUAL, true);

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetTarget())
                    {
                        std::list<Unit*> playerList;
                        std::list<Creature*> statueList;

                        _player->GetPartyMembers(playerList);

                        if (playerList.size() > 1)
                        {
                            playerList.remove(target);
                            playerList.sort(WoWSource::HealthPctOrderPred());
                            playerList.resize(1);
                        }

                        _player->GetCreatureListWithEntryInGrid(statueList, 60849, 100.0f);

                        // Remove other players jade statue
                        for (std::list<Creature*>::iterator i = statueList.begin(); i != statueList.end();)
                        {
                            Unit* owner = (*i)->GetOwner();
                            if (owner && owner == _player && (*i)->isSummon())
                            {
                                ++i;
                                continue;
                            }

                            i = statueList.erase(i);
                        }

                        Creature* statue = nullptr;
                        if (statueList.size() == 1)
                            statue = *statueList.begin();

                        if (statue)
                        {
                            std::list<Unit*> l_PartyMembers;
                            _player->GetPartyMembers(l_PartyMembers);

                            if (!l_PartyMembers.empty())
                            {
                                l_PartyMembers.sort(WoWSource::HealthPctOrderPred());

                                statue->CastSpell(l_PartyMembers.front(), GetSpellInfo()->Id, true);
                            }
                        }
                    }
                }
            }

            void HandleEffectPeriodic(constAuraEffectPtr /*aurEff*/)
            {
                if (Unit* caster = GetCaster())
                    if (Unit* target = GetTarget())
                        // 30% to give 1 chi per tick
                        if (roll_chance_i(30))
                            caster->CastSpell(caster, SPELL_MONK_SOOTHING_MIST_ENERGIZE, true);
            }

            void OnRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetTarget())
                    {
                        if (Player* _player = GetCaster()->ToPlayer())
                        {
                            std::list<Unit*> playerList;
                            std::list<Creature*> tempList;
                            std::list<Creature*> statueList;
                            Creature* statue;

                            _player->GetPartyMembers(playerList);

                            if (playerList.size() > 1)
                            {
                                playerList.sort(WoWSource::HealthPctOrderPred());
                                playerList.resize(1);
                            }

                            _player->GetCreatureListWithEntryInGrid(tempList, 60849, 100.0f);
                            _player->GetCreatureListWithEntryInGrid(statueList, 60849, 100.0f);

                            // Remove other players jade statue
                            for (std::list<Creature*>::iterator i = tempList.begin(); i != tempList.end(); ++i)
                            {
                                Unit* owner = (*i)->GetOwner();
                                if (owner && owner == _player && (*i)->isSummon())
                                    continue;

                                statueList.remove((*i));
                            }

                            for (auto itr : playerList)
                            {
                                if (statueList.size() == 1)
                                {
                                    for (auto itrBis : statueList)
                                        statue = itrBis;

                                    if (statue && (statue->isPet() || statue->isGuardian()))
                                    {
                                        if (statue->GetOwner() && statue->GetOwner()->GetGUID() == _player->GetGUID())
                                        {
                                            statue->CastStop();
                                        }
                                    }
                                }
                            }

                            if (target->HasAura(SPELL_MONK_SOOTHING_MIST_VISUAL))
                                target->RemoveAura(SPELL_MONK_SOOTHING_MIST_VISUAL);
                        }
                    }
                }
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_monk_soothing_mist_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_soothing_mist_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_HEAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_monk_soothing_mist_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_soothing_mist_AuraScript();
        }
};

// Disable - 116095
class spell_monk_disable : public SpellScriptLoader
{
    public:
        spell_monk_disable() : SpellScriptLoader("spell_monk_disable") { }

        class spell_monk_disable_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_disable_SpellScript);

            bool snaredOnHit;

            SpellCastResult CheckCast()
            {
                snaredOnHit = false;

                if (GetCaster())
                    if (Unit* target = GetCaster()->getVictim())
                        if (target->HasAuraType(SPELL_AURA_MOD_DECREASE_SPEED))
                            snaredOnHit = true;

                return SPELL_CAST_OK;
            }

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                    if (Player* _player = caster->ToPlayer())
                        if (Unit* target = GetHitUnit())
                            if (snaredOnHit)
                                _player->CastSpell(target, SPELL_MONK_DISABLE_ROOT, true);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_monk_disable_SpellScript::CheckCast);
                OnHit += SpellHitFn(spell_monk_disable_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_disable_SpellScript();
        }

        class spell_monk_disable_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_disable_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (!GetCaster())
                    return;

                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetTarget())
                    {
                        if (target->GetDistance(caster) < 10.0f)
                        {
                            if (AuraPtr disable = target->GetAura(SPELL_MONK_DISABLE, caster->GetGUID()))
                            {
                                if (disable->GetDuration() <= 500)
                                    aurEff->GetBase()->RefreshDuration();
                            }
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_monk_disable_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_disable_AuraScript();
        }
};

// Zen Pilgrimage - 126892 and Zen Pilgrimage : Return - 126895
class spell_monk_zen_pilgrimage : public SpellScriptLoader
{
    public:
        spell_monk_zen_pilgrimage() : SpellScriptLoader("spell_monk_zen_pilgrimage") { }

        class spell_monk_zen_pilgrimage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_zen_pilgrimage_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MONK_ZEN_PILGRIMAGE) || !sSpellMgr->GetSpellInfo(SPELL_MONK_ZEN_PILGRIMAGE_RETURN))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Player* _player = caster->ToPlayer())
                    {
                        if (GetSpellInfo()->Id == SPELL_MONK_ZEN_PILGRIMAGE)
                        {
                            _player->SaveRecallPosition();
                            _player->TeleportTo(870, 3818.55f, 1793.18f, 950.35f, _player->GetOrientation());
                        }
                        else if (GetSpellInfo()->Id == SPELL_MONK_ZEN_PILGRIMAGE_RETURN)
                        {
                            _player->TeleportTo(_player->m_recallMap, _player->m_recallX, _player->m_recallY, _player->m_recallZ, _player->m_recallO);
                            _player->RemoveAura(126896);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_monk_zen_pilgrimage_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_zen_pilgrimage_SpellScript();
        }
};

// Blackout Kick - 100784
class spell_monk_blackout_kick : public SpellScriptLoader
{
    public:
        spell_monk_blackout_kick() : SpellScriptLoader("spell_monk_blackout_kick") { }

        class spell_monk_blackout_kick_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_blackout_kick_SpellScript);

            void HandleOnHit(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        // Combo Breaker: Blackout Kick
                        if (caster->HasAura(SPELL_MONK_COMBO_BREAKER_BLACKOUT_KICK))
                            caster->RemoveAura(SPELL_MONK_COMBO_BREAKER_BLACKOUT_KICK);

                        // Second effect by spec : Instant heal or DoT
                        if (caster->GetTypeId() == TYPEID_PLAYER && caster->ToPlayer()->GetSpecializationId(caster->ToPlayer()->GetActiveSpec()) == SPEC_MONK_WINDWALKER
                            && caster->ToPlayer()->HasAura(128595))
                        {
                            // Your Blackout Kick always deals 20% additional damage over 4 sec regardless of positioning but you're unable to trigger the healing effect.
                            if (caster->HasAura(SPELL_MONK_GLYPH_OF_BLACKOUT_KICK))
                            {
                                int32 bp = int32(GetHitDamage() * 0.2f) / 4;
                                caster->CastCustomSpell(target, SPELL_MONK_BLACKOUT_KICK_DOT, &bp, NULL, NULL, true);
                            }
                            else
                            {
                                // If behind : 20% damage on DoT
                                if (target->isInBack(caster))
                                {
                                    int32 bp = int32(GetHitDamage() * 0.2f) / 4;
                                    caster->CastCustomSpell(target, SPELL_MONK_BLACKOUT_KICK_DOT, &bp, NULL, NULL, true);
                                }
                                // else : 20% damage on instant heal
                                else
                                {
                                    int32 bp = int32(GetHitDamage() * 0.2f);
                                    caster->CastCustomSpell(caster, SPELL_MONK_BLACKOUT_KICK_HEAL, &bp, NULL, NULL, true);
                                }
                            }
                        }
                        // Brewmaster : Training - you gain Shuffle, increasing parry chance and stagger amount by 20%
                        else if (caster->GetTypeId() == TYPEID_PLAYER && caster->ToPlayer()->GetSpecializationId(caster->ToPlayer()->GetActiveSpec()) == SPEC_MONK_BREWMASTER)
                            caster->CastSpell(caster, SPELL_MONK_SHUFFLE, true);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_monk_blackout_kick_SpellScript::HandleOnHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_blackout_kick_SpellScript();
        }
};

// Rising Sun Kick - 107428
class spell_monk_rising_sun_kick : public SpellScriptLoader
{
public:
    spell_monk_rising_sun_kick() : SpellScriptLoader("spell_monk_rising_sun_kick") { }

    class spell_monk_rising_sun_kick_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_monk_rising_sun_kick_SpellScript);

        void HandleAfterHit()
        {
            Player* player = GetCaster()->ToPlayer();
            if (!player)
                return;

            Unit* target = GetHitUnit();
            if (!target)
                return;

            player->CastSpell(target, 130320, true);
        }

        void Register()
        {
            AfterHit += SpellHitFn(spell_monk_rising_sun_kick_SpellScript::HandleAfterHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_monk_rising_sun_kick_SpellScript();
    }
};

// Provoke - 115546
class spell_monk_provoke : public SpellScriptLoader
{
    public:
        spell_monk_provoke() : SpellScriptLoader("spell_monk_provoke") { }

        class spell_monk_provoke_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_provoke_SpellScript);

            SpellCastResult CheckCast()
            {
                Unit* target = GetExplTargetUnit();
                if (!target)
                    return SPELL_FAILED_NO_VALID_TARGETS;
                else if (target->GetTypeId() == TYPEID_PLAYER)
                    return SPELL_FAILED_BAD_TARGETS;
                else if (!target->IsWithinLOSInMap(GetCaster()))
                    return SPELL_FAILED_LINE_OF_SIGHT;
                return SPELL_CAST_OK;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Unit* caster = GetCaster())
                    if (caster->getClass() == CLASS_MONK && caster->GetTypeId() == TYPEID_PLAYER)
                        if (Unit* target = GetHitUnit())
                            caster->CastSpell(target, SPELL_MONK_PROVOKE, true);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_monk_provoke_SpellScript::CheckCast);
                OnEffectHitTarget += SpellEffectFn(spell_monk_provoke_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_provoke_SpellScript();
        }
};

// Paralysis - 115078
class spell_monk_paralysis : public SpellScriptLoader
{
    public:
        spell_monk_paralysis() : SpellScriptLoader("spell_monk_paralysis") { }

        class spell_monk_paralysis_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_paralysis_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (caster->HasAura(125755)) // Glyph of Paralysis
                        {
                            target->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE, 0, target->GetAura(32409)); // Shawow Word : Death Self Damage not be removed.
                            target->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
                            target->RemoveAurasByType(SPELL_AURA_PERIODIC_LEECH);
                        }

                        if (target->isInBack(caster))
                        {
                            if (AuraApplication* aura = target->GetAuraApplication(115078))
                            {
                                AuraPtr Paralysis = aura->GetBase();
                                int32 maxDuration = Paralysis->GetMaxDuration();
                                int32 newDuration = maxDuration * float(1.5f);
                                Paralysis->SetDuration(newDuration);

                                if (newDuration > maxDuration)
                                    Paralysis->SetMaxDuration(newDuration);
                            }
                        }
                        
                        if (target->ToPlayer())
                        {
                            if (AuraApplication* aura = target->GetAuraApplication(115078))
                            {
                                AuraPtr Paralysis = aura->GetBase();
                                int32 maxDuration = Paralysis->GetMaxDuration();
                                int32 newDuration = maxDuration / 2;
                                Paralysis->SetDuration(newDuration);
                                Paralysis->SetMaxDuration(newDuration);
                            }                            
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_paralysis_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_paralysis_SpellScript();
        }
};

// Touch of Death - 115080
class spell_monk_touch_of_death : public SpellScriptLoader
{
    public:
        spell_monk_touch_of_death() : SpellScriptLoader("spell_monk_touch_of_death") { }

        class spell_monk_touch_of_death_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_touch_of_death_SpellScript);

            SpellCastResult CheckCast()
            {
                if (GetCaster() && GetExplTargetUnit())
                {
                    if (GetCaster()->HasAura(124490))
                    {
                        if (GetExplTargetUnit()->GetTypeId() == TYPEID_UNIT && GetExplTargetUnit()->ToCreature()->IsDungeonBoss())
                            return SPELL_FAILED_BAD_TARGETS;
                        else if (GetExplTargetUnit()->GetTypeId() == TYPEID_UNIT && (GetExplTargetUnit()->GetHealth() > GetCaster()->GetHealth()))
                            return SPELL_FAILED_BAD_TARGETS;
                        else if (GetExplTargetUnit()->GetTypeId() == TYPEID_PLAYER && (GetExplTargetUnit()->GetHealthPct() > 10.0f))
                            return SPELL_FAILED_BAD_TARGETS;
                    }
                    else
                    {
                        if (GetExplTargetUnit()->GetTypeId() == TYPEID_UNIT && GetExplTargetUnit()->ToCreature()->IsDungeonBoss())
                            return SPELL_FAILED_BAD_TARGETS;
                        else if (GetExplTargetUnit()->GetTypeId() == TYPEID_PLAYER)
                            return SPELL_FAILED_BAD_TARGETS;
                        else if (GetExplTargetUnit()->GetTypeId() == TYPEID_UNIT && (GetExplTargetUnit()->GetHealth() > GetCaster()->GetHealth()))
                            return SPELL_FAILED_BAD_TARGETS;
                    }
                    return SPELL_CAST_OK;
                }
                return SPELL_FAILED_NO_VALID_TARGETS;
            }

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasAura(125732)) // Glyph of Honor
                        _player->SendPlaySpellVisual(26117, _player, NULL); // Honorable Bow Animation
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_monk_touch_of_death_SpellScript::CheckCast);
                OnHit += SpellHitFn(spell_monk_touch_of_death_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_touch_of_death_SpellScript();
        }
};

// Fortifying brew - 115203
class spell_monk_fortifying_brew : public SpellScriptLoader
{
    public:
        spell_monk_fortifying_brew() : SpellScriptLoader("spell_monk_fortifying_brew") { }

        class spell_monk_fortifying_brew_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_fortifying_brew_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (caster && caster->GetTypeId() == TYPEID_PLAYER)
                    caster->CastSpell(caster, SPELL_MONK_FORTIFYING_BREW, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_monk_fortifying_brew_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_fortifying_brew_SpellScript();
        }
};

// Legacy of the Emperor - 115921
class spell_monk_legacy_of_the_emperor : public SpellScriptLoader
{
    public:
        spell_monk_legacy_of_the_emperor() : SpellScriptLoader("spell_monk_legacy_of_the_emperor") { }

        class spell_monk_legacy_of_the_emperor_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_legacy_of_the_emperor_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Player* plr = GetCaster()->ToPlayer())
                {
                    std::list<Unit*> groupList;

                    plr->GetPartyMembers(groupList);

                    if (!groupList.empty())
                    {
                        for (auto itr : groupList)
                        {
                            if (!plr)
                                continue;

                            if (!itr)
                                continue;

                            plr->CastSpell(itr, SPELL_MONK_LEGACY_OF_THE_EMPEROR, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_monk_legacy_of_the_emperor_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_legacy_of_the_emperor_SpellScript();
        }
};

// Roll - 109132 or Roll (3 charges) - 121827
class spell_monk_roll : public SpellScriptLoader
{
    public:
        spell_monk_roll() : SpellScriptLoader("spell_monk_roll") { }

        class spell_monk_roll_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_roll_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_MONK_ROLL))
                    return false;
                return true;
            }

            void HandleBeforeCast()
            {
                AuraPtr aur = GetCaster()->AddAura(SPELL_MONK_ROLL_TRIGGER, GetCaster());
                if (!aur)
                    return;

                AuraApplication* app =  aur->GetApplicationOfTarget(GetCaster()->GetGUID());
                if (!app)
                    return;

                app->ClientUpdate();
            }

            void HandleAfterCast()
            {
                Unit* caster = GetCaster();
                if (!caster || caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                caster->CastSpell(caster, SPELL_MONK_ROLL_TRIGGER, true);

                if (caster->HasAura(SPELL_MONK_ITEM_PVP_GLOVES_BONUS))
                    caster->RemoveAurasByType(SPELL_AURA_MOD_DECREASE_SPEED);
            }

            void Register()
            {
                BeforeCast += SpellCastFn(spell_monk_roll_SpellScript::HandleBeforeCast);
                AfterCast += SpellCastFn(spell_monk_roll_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_roll_SpellScript();
        }
};

// Brewing : Tigereye Brew - 123980
class spell_monk_tigereye_brew_stacks : public SpellScriptLoader
{
    public:
        spell_monk_tigereye_brew_stacks() : SpellScriptLoader("spell_monk_tigereye_brew_stacks") { }

        class spell_monk_tigereye_brew_stacks_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_tigereye_brew_stacks_AuraScript);

            uint32 chiConsumed;

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                chiConsumed = 0;
            }

            void SetData(uint32 type, uint32 data)
            {
                while ((chiConsumed += data) >= 4)
                {
                    chiConsumed = 0;
                    data = data > 4 ? data - 4: 0;

                    if (GetCaster())
                        GetCaster()->CastSpell(GetCaster(), SPELL_MONK_TIGEREYE_BREW_STACKS, true);
                }
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_monk_tigereye_brew_stacks_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_tigereye_brew_stacks_AuraScript();
        }
};

// Called by Jab - 100780 and Spinning crane kick - 107270 and Rushing Jade Wind - 116847
// Muscle Memory - 139598
class spell_monk_muscle_memory : public SpellScriptLoader
{
    public:
        spell_monk_muscle_memory() : SpellScriptLoader("spell_monk_muscle_memory") { }

        class spell_monk_muscle_memory_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_muscle_memory_SpellScript)

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (_player->HasSpell(139598))
                        if (Unit* target = GetHitUnit())
                            if (GetSpellInfo()->Id != 107270)
                                if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_MONK_MISTWEAVER)
                                    _player->AddAura(SPELL_MONK_MUSCLE_MEMORY_EFFECT,_player);
            }

            void SelectTarget(std::list<WorldObject*>& targets)
            {
                if (targets.size() >= 3)
                    if (Player* _player = GetCaster()->ToPlayer())
                        if (_player->HasSpell(139598))
						    if (GetSpellInfo()->Id == 107270 || GetSpellInfo()->Id == 116847)
                                if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_MONK_MISTWEAVER)
                                    _player->AddAura(SPELL_MONK_MUSCLE_MEMORY_EFFECT,_player);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_muscle_memory_SpellScript::HandleOnHit);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_monk_muscle_memory_SpellScript::SelectTarget, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_muscle_memory_SpellScript();
        }
};

int32 chiBrewCount = 0;
// Chi Brew - 115399
class spell_monk_chi_brew : public SpellScriptLoader
{
    public:
        spell_monk_chi_brew() : SpellScriptLoader("spell_monk_chi_brew") { }

        class spell_monk_chi_brew_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_chi_brew_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    int32 stacks = 0;

                    chiBrewCount++;

                    _player->AddAura(125473, _player); // Delay aura for chiBrewCount reset

                    if (chiBrewCount > 2)
                    {
                        chiBrewCount = 0;
                        _player->AddSpellCooldown(115399, 0, time(NULL) + 1);
                        return;
                    }

                    switch (_player->GetSpecializationId(_player->GetActiveSpec()))
                    {
                        case SPEC_MONK_BREWMASTER:
                            if (AuraPtr elusiveBrewStacks = _player->GetAura(SPELL_MONK_ELUSIVE_BREW_STACKS))
                                if (elusiveBrewStacks->GetStackAmount() >= 15)
                                    return;

                            for (int i = 1; i <= 5; i++)
                                _player->CastSpell(_player, SPELL_MONK_ELUSIVE_BREW_STACKS, true);
                            break;
                        case SPEC_MONK_MISTWEAVER:
                            if (AuraPtr manaTeaStacks = _player->GetAura(SPELL_MONK_MANA_TEA_STACKS))
                                if (manaTeaStacks->GetStackAmount() >= 20)
                                    return;

                            if (!_player->HasAura(115070)) // allow to add mana tea stacks only in Stance of the Wise Serpent
                                return;

                            for (int i = 1; i <= 2; i++)
                                _player->CastSpell(_player, SPELL_MONK_MANA_TEA_STACKS, true);
                            break;
                        case SPEC_MONK_WINDWALKER:
                            if (AuraPtr tigerEyeStacks = _player->GetAura(SPELL_MONK_TIGEREYE_BREW_STACKS))
                                if (tigerEyeStacks->GetStackAmount() >= 20)
                                    return;

                            for (int i = 1; i <= 2; i++)
                                _player->CastSpell(_player, SPELL_MONK_TIGEREYE_BREW_STACKS, true);
                            break;
                        default:
                            break;
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_chi_brew_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_chi_brew_SpellScript();
        }
};

// Delay Aura - 125473
class spell_monk_delay_aura : public SpellScriptLoader
{
public:
    spell_monk_delay_aura() : SpellScriptLoader("spell_monk_delay_aura") { }

    class spell_monk_delay_aura_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_monk_delay_aura_AuraScript);

        void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            chiBrewCount = 0;
        }

        void Register()
        {
            OnEffectRemove += AuraEffectRemoveFn(spell_monk_delay_aura_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_monk_delay_aura_AuraScript();
    }
};

// Called by Brewing: Tigereye Brew - 125195
// Mastery: Bottled Fury - 115636
class spell_monk_mastery_bottled_fury : public SpellScriptLoader
{
    public:
        spell_monk_mastery_bottled_fury() : SpellScriptLoader("spell_monk_mastery_bottled_fury") { }

        class spell_monk_mastery_bottled_fury_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_mastery_bottled_fury_SpellScript)

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (GetCaster())
                {
    				if (Player* player = GetCaster()->ToPlayer())
                    {
                        // Fix for Tooltip Amount
                        if (AuraPtr tigerEyeStacks = player->GetAura(SPELL_MONK_TIGEREYE_BREW_STACKS))
                        {
                            if (tigerEyeStacks->GetEffect(EFFECT_2)->GetAmount() > 60)
                                tigerEyeStacks->GetEffect(EFFECT_2)->SetAmount(60);

                            if (tigerEyeStacks->GetStackAmount() >= 10)
                                player->AddAura(SPELL_MONK_TIGEREYE_BREW_VISUAL, player);
                        }

                        // Mastery: Bottled Fury
                        float Mastery = player->GetFloatValue(PLAYER_MASTERY) * 2.5f;

                        if (player->HasAura(115636) && roll_chance_i(Mastery))
                            player->CastSpell(player, SPELL_MONK_TIGEREYE_BREW_STACKS, true);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_monk_mastery_bottled_fury_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_mastery_bottled_fury_SpellScript();
        }
};

// Brewing: Mana Tea passiv bonus - 115867
class spell_monk_brewing_mana_tea_passiv : public SpellScriptLoader
{
    public:
        spell_monk_brewing_mana_tea_passiv() : SpellScriptLoader("spell_monk_brewing_mana_tea_passiv") { }

        class spell_monk_brewing_mana_tea_passiv_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_brewing_mana_tea_passiv_SpellScript)

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (!GetCaster())
                    return;

                if (Player* plr = GetCaster()->ToPlayer())
                {
                    // Brewing: Mana Tea passiv bonus
                    float crit_chance = 0.0f;
                    crit_chance += GetCaster()->GetFloatValue(PLAYER_SPELL_CRIT_PERCENTAGE1 + SPELL_SCHOOL_MASK_NORMAL);

                    // To prevent a crash
                    if (AuraPtr manaTeaStacks = plr->GetAura(SPELL_MONK_MANA_TEA_STACKS))
                        if (manaTeaStacks->GetStackAmount() >= 20)
                            return;

                    if (roll_chance_i(crit_chance))
                    {
                        if (plr)
                        {
                            plr->CastSpell(plr, SPELL_MONK_MANA_TEA_STACKS, true);
                            plr->CastSpell(plr, SPELL_MONK_PLUS_ONE_MANA_TEA, true);
                        }
                    }  
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_monk_brewing_mana_tea_passiv_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_brewing_mana_tea_passiv_SpellScript();
        }
};

// Called by Mana Tea (instant) - 123761
// Glyph of Mana Tea - 123763
class spell_monk_glyph_of_mana_tea : public SpellScriptLoader
{
    public:
        spell_monk_glyph_of_mana_tea() : SpellScriptLoader("spell_monk_glyph_of_mana_tea") { }

        class spell_monk_glyph_of_mana_tea_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_glyph_of_mana_tea_SpellScript)

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                        if (_player->HasAura(SPELL_MONK_GLYPH_OF_MANA_TEA))
                        {
                            if (AuraPtr manaTeaStacks = _player->GetAura(SPELL_MONK_MANA_TEA_STACKS))
                                {
                                    int32 maxDuration = manaTeaStacks->GetMaxDuration();
                                    int32 stacks = manaTeaStacks->GetStackAmount();
                                    if (stacks > 2)
                                    {
                                        manaTeaStacks->SetStackAmount(stacks - 2);
                                        manaTeaStacks->SetDuration(maxDuration);
                                    }
                                    else
                                        _player->RemoveAura(manaTeaStacks);
                                }
                        }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_monk_glyph_of_mana_tea_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_glyph_of_mana_tea_SpellScript();
        }
};

// Called by 100780 / 108557 / 115698 / 115687 / 115693 / 115695 - Jab (and overrides)
// 137384 - Combo Breaker
class spell_monk_combo_breaker : public SpellScriptLoader
{
    public:
		spell_monk_combo_breaker() : SpellScriptLoader("spell_monk_combo_breaker") { }

		class spell_monk_combo_breaker_SpellScript : public SpellScript
        {
			PrepareSpellScript(spell_monk_combo_breaker_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetHitUnit())
                    {
						if (caster->GetTypeId() == TYPEID_PLAYER && caster->HasAura(SPELL_MONK_COMBO_BREAKER))
                        {
                            if (roll_chance_i(12))
                            {
                                if (roll_chance_i(50))
									caster->CastSpell(caster, SPELL_MONK_COMBO_BREAKER_TIGER_PALM, true);
                                else
									caster->CastSpell(caster, SPELL_MONK_COMBO_BREAKER_BLACKOUT_KICK, true);
                            }
                        }
                    }
                }
            }

            void Register()
            {
				OnHit += SpellHitFn(spell_monk_combo_breaker_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
			return new spell_monk_combo_breaker_SpellScript();
        }
};

class spell_monk_sanctuary_of_the_ox : public SpellScriptLoader
{
	class script_impl : public AuraScript
	{
		PrepareAuraScript(script_impl)

		enum
		{
			BLACK_OX_GUARD_AOE_SELECTOR = 118605
		};

		uint32 totalDamageDone_;

	public:
		script_impl()
			: totalDamageDone_()
		{ }

	public:
		void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
		{
			PreventDefaultAction();

			totalDamageDone_ += eventInfo.GetDamageInfo()->GetDamage();

			auto const monk = eventInfo.GetActor();

			uint32 const threshold = monk->GetTotalAttackPowerValue(BASE_ATTACK) * 16;
			if (totalDamageDone_ < threshold)
				return;

			totalDamageDone_ -= threshold;

			auto const statue = Unit::GetUnit(*monk, monk->m_SummonSlot[SUMMON_SLOT_TOTEM]);
			if (!statue)
				return;

			statue->CastSpell(statue, BLACK_OX_GUARD_AOE_SELECTOR, true, nullptr, nullptr, monk->GetGUID());
		}

		void Register()
		{
			OnEffectProc += AuraEffectProcFn(script_impl::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
		}
	};

public:
	spell_monk_sanctuary_of_the_ox()
		: SpellScriptLoader("spell_monk_sanctuary_of_the_ox")
	{ }

	AuraScript * GetAuraScript() const
	{
		return new script_impl;
	}
};

class spell_monk_black_ox_guard_aoe_selector : public SpellScriptLoader
{
	class script_impl : public SpellScript
	{
		PrepareSpellScript(script_impl)

		enum
		{
			BLACK_OX_GUARD = 118604
		};

		void filterTargets(std::list<WorldObject*> &targets)
		{
			auto const monk = GetOriginalCaster();
			Unit *mostInjured = nullptr;

			for (auto &obj : targets)
			{
				if (obj->GetTypeId() != TYPEID_PLAYER || obj == monk)
					continue;

				auto const unitTarget = obj->ToUnit();
				if (!monk->IsInRaidWith(unitTarget))
					continue;

				if (!mostInjured || mostInjured->GetHealthPct() > unitTarget->GetHealthPct())
					mostInjured = unitTarget;
			};

			targets.clear();

			if (mostInjured)
				targets.emplace_back(mostInjured);
		}

		void scriptEffect(SpellEffIndex effIndex)
		{
			PreventHitDefaultEffect(effIndex);

			auto const monk = GetOriginalCaster();
			auto const target = GetHitUnit();

			monk->CastSpell(target, BLACK_OX_GUARD, true);
		}

		void Register()
		{
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(script_impl::filterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
			OnEffectHitTarget += SpellEffectFn(script_impl::scriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
		}
	};

public:
	spell_monk_black_ox_guard_aoe_selector()
		: SpellScriptLoader("spell_monk_black_ox_guard_aoe_selector")
	{ }

	SpellScript * GetSpellScript() const
	{
		return new script_impl;
	}
};

// Glyph: Leer of the Ox
class spell_monk_leer_of_the_ox : public SpellScriptLoader
{
    public:
        spell_monk_leer_of_the_ox() : SpellScriptLoader("spell_monk_leer_of_the_ox") { }

        class spell_monk_leer_of_the_ox_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_monk_leer_of_the_ox_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->learnSpell(SPELL_MONK_LEER_OF_THE_OX, false);
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    if (_player->HasSpell(SPELL_MONK_LEER_OF_THE_OX))
                        _player->removeSpell(SPELL_MONK_LEER_OF_THE_OX, false, false);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_monk_leer_of_the_ox_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_monk_leer_of_the_ox_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_monk_leer_of_the_ox_AuraScript();
        }
};

// Life Cocoon - 116849
// Glyph of Life Cocoon - 124989
class spell_monk_life_cocoon : public SpellScriptLoader
{
    public:
        spell_monk_life_cocoon() : SpellScriptLoader("spell_monk_life_cocoon") { }

        class spell_monk_life_cocoon_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_monk_life_cocoon_SpellScript);

            SpellCastResult CheckTarget()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (_player->HasAuraType(SPELL_AURA_MOD_STUN) && !_player->HasAura(SPELL_MONK_GLYPH_OF_LIFE_COCOON))
                        return SPELL_FAILED_STUNNED;

                return SPELL_CAST_OK;
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_monk_life_cocoon_SpellScript::CheckTarget);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_monk_life_cocoon_SpellScript();
        }
};

/*######
## spell_monk_sparring - 116023
######*/

class spell_monk_sparring : public SpellScriptLoader
{
public:
	spell_monk_sparring() : SpellScriptLoader("spell_monk_sparring") { }

	class spell_monk_sparring_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_monk_sparring_AuraScript);

		// Is required to apply sparring cooldown marker
		bool applySparringCooldownMarker;

		bool OnCheckProc(ProcEventInfo& eventInfo)
		{
			applySparringCooldownMarker = false;
			if (Unit* caster = GetCaster())
			{
				if (Unit* actor = eventInfo.GetActor())
				{
					if (caster != actor)
					{
						if (!caster->HasAura(SPELL_MONK_SPARRING_COOLDOWN_MARKER))
						{
							if (caster->isInFrontInMap(actor, 3.0f))
							{
								applySparringCooldownMarker = true;
								return true;
							}
						}
					}
					else
					{
						if (caster->HasAura(SPELL_MONK_SPARRING))
						{
							if (AuraPtr cooldown_aura = caster->GetAura(SPELL_MONK_SPARRING_COOLDOWN_MARKER))
							{
								if (Unit* targuet = eventInfo.GetActionTarget())
								{
									if (cooldown_aura->GetCasterGUID() == targuet->GetGUID())
									{
										return true;
									}
								}
							}
						}
					}
				}
			}
			return false;
		}

		void OnProc(constAuraEffectPtr /*aurEff*/, ProcEventInfo& eventInfo)
		{
			if (applySparringCooldownMarker)
			{
				if (Unit* caster = GetCaster())
				{
					if (Unit* actor = eventInfo.GetActor())
					{
						caster->CastSpell(caster, SPELL_MONK_SPARRING_COOLDOWN_MARKER, true, NULL, NULLAURA_EFFECT, actor->GetGUID());
					}
				}
			}
		}

		void Register()
		{
			DoCheckProc += AuraCheckProcFn(spell_monk_sparring_AuraScript::OnCheckProc);
			OnEffectProc += AuraEffectProcFn(spell_monk_sparring_AuraScript::OnProc, EFFECT_0, SPELL_AURA_PROC_TRIGGER_SPELL);

		}
	};

	AuraScript* GetAuraScript() const
	{
		return new spell_monk_sparring_AuraScript();
	}
};

/*######
## spell_monk_healing_elixirs_proc - 134563 procFlags (0x000A22A8 | 0x00004400 = 0x000A66A8), proEx (3)
######*/

class spell_monk_healing_elixirs_proc : public SpellScriptLoader
{
public:
	spell_monk_healing_elixirs_proc() : SpellScriptLoader("spell_monk_healing_elixirs_proc") { }

	class spell_monk_healing_elixirs_proc_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_monk_healing_elixirs_proc_AuraScript);

		bool OnCheckProc(ProcEventInfo& eventInfo)
		{
			if (Unit* caster = GetCaster())
			{
				if (Unit* actor = eventInfo.GetActor())
				{
					if (DamageInfo* damage = eventInfo.GetDamageInfo())
					{
						if (caster != actor)
						{
							if (caster->HealthBelowPctDamaged(35.0f, damage->GetDamage()))
							{
								return true;
							}
						}
						else
						{
							if (!caster->IsFullHealth())
							{
								if (SpellInfo const* spellInf = damage->GetSpellInfo())
								{
									uint32 spellID = spellInf->Id;
									if (spellID == SPELL_MONK_FORTIFYING_BREW_A || // 115203
										spellID == SPELL_MONK_CHI_BREW ||          // 115399
										spellID == SPELL_MONK_ELUSIVE_BREW ||      // 115308
										spellID == SPELL_MONK_TIGEREYE_BREW ||     // 116740
										spellID == SPELL_MONK_PURIFYING_BREW ||    // 119582
										spellID == SPELL_MONK_ENERGIZING_BREW ||   // 115288
										spellID == SPELL_MONK_NIMBLE_BREW ||       // 137562
										spellID == SPELL_MONK_MANA_TEA_REGEN ||    // 115294
										spellID == SPELL_MONK_THUNDER_FOCUS_TEA)   // 116680
									{
										return true;
									}
								}
							}
						}
					}
				}
			}
			return false;
		}

		void Register()
		{
			DoCheckProc += AuraCheckProcFn(spell_monk_healing_elixirs_proc_AuraScript::OnCheckProc);
		}
	};

	AuraScript* GetAuraScript() const
	{
		return new spell_monk_healing_elixirs_proc_AuraScript();
	}
};

void AddSC_monk_spell_scripts()
{
    new spell_monk_ring_of_peace_dummy();
    new spell_monk_ring_of_peace();
    new spell_monk_storm_earth_and_fire_stats();
    new spell_monk_storm_earth_and_fire();
    new spell_monk_fists_of_fury_stun();
    new spell_monk_expel_harm();
    new spell_monk_chi_wave_healing_bolt();
    new spell_monk_chi_wave_bolt();
    new spell_monk_chi_wave();
    new spell_monk_grapple_weapon();
    new spell_monk_transcendence_transfer();
    new spell_monk_transcendence_remove_spirit();
    new spell_monk_serpents_zeal();
    new spell_monk_dampen_harm();
    new spell_monk_item_s12_4p_mistweaver();
    new spell_monk_diffuse_magic();
    new spell_monk_black_ox_statue();
    new spell_monk_guard();
    new spell_monk_bear_hug();
    new spell_monk_rising_sun_kick();
    new spell_monk_zen_flight_check();
    new spell_monk_power_strikes();
    new spell_monk_crackling_jade_lightning();
    new spell_monk_touch_of_karma();
    new spell_monk_spinning_fire_blossom_damage();
    new spell_monk_spinning_fire_blossom();
    new spell_monk_delay_aura();
    new spell_monk_path_of_blossom();
    new spell_monk_thunder_focus_tea();
    new spell_monk_jade_serpent_statue();
    new spell_monk_teachings_of_the_monastery();
    new spell_monk_mana_tea();
    new spell_monk_mana_tea_stacks();
    new spell_monk_detox();
    new spell_monk_enveloping_mist();
    new spell_monk_surging_mist();
    new spell_monk_glyph_of_surging_mist();
    new spell_monk_renewing_mist();
    //new spell_monk_healing_elixirs(); // no longer required, now handled by spell_monk_healing_elixirs_proc
    new spell_monk_zen_sphere();
    new spell_monk_chi_burst();
    new spell_monk_energizing_brew();
    new spell_monk_spear_hand_strike();
    new spell_monk_tigereye_brew();
    new spell_monk_tigers_lust();
    new spell_monk_flying_serpent_kick_travel();
    new spell_monk_flying_serpent_kick();
    new spell_monk_chi_torpedo();
    new spell_monk_purifying_brew();
    new spell_monk_clash();
    new spell_monk_keg_smash();
    new spell_monk_elusive_brew();
    new spell_monk_breath_of_fire();
    new spell_monk_soothing_mist();
    new spell_monk_disable();
    new spell_monk_zen_pilgrimage();
    new spell_monk_blackout_kick();
    new spell_monk_legacy_of_the_emperor();
    new spell_monk_fortifying_brew();
    new spell_monk_touch_of_death();
    new spell_monk_paralysis();
    new spell_monk_provoke();
    new spell_monk_roll();
    new spell_monk_tigereye_brew_stacks();
    new spell_monk_muscle_memory();
    new spell_monk_chi_brew();
    new spell_monk_mastery_bottled_fury();
    new spell_monk_brewing_mana_tea_passiv();
    new spell_monk_glyph_of_mana_tea();
    new spell_monk_combo_breaker();
	new spell_monk_sanctuary_of_the_ox();
	new spell_monk_black_ox_guard_aoe_selector();
    new spell_monk_leer_of_the_ox();
    new spell_monk_life_cocoon();
	new spell_monk_sparring();
	new spell_monk_healing_elixirs_proc();
}