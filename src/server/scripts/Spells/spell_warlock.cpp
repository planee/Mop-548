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
 * Scripts for spells with SPELLFAMILY_WARLOCK and SPELLFAMILY_GENERIC spells used by warlock players.
 * Ordered alphabetically using scriptname.
 * Scriptnames of files in this file should be prefixed with "spell_warl_".
 */

#include "Creature.h"
#include "ScriptMgr.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"

enum WarlockSpells
{
    WARLOCK_DEMONIC_EMPOWERMENT_SUCCUBUS    = 54435,
    WARLOCK_DEMONIC_EMPOWERMENT_VOIDWALKER  = 54443,
    WARLOCK_DEMONIC_EMPOWERMENT_FELGUARD    = 54508,
    WARLOCK_DEMONIC_EMPOWERMENT_FELHUNTER   = 54509,
    WARLOCK_DEMONIC_EMPOWERMENT_IMP         = 54444,
    WARLOCK_DEMONIC_CIRCLE_SUMMON           = 48018,
    WARLOCK_DEMONIC_CIRCLE_TELEPORT         = 48020,
    WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST       = 62388,
    WARLOCK_UNSTABLE_AFFLICTION_DISPEL      = 31117,
    WARLOCK_GLYPH_OF_FEAR                   = 56244,
    WARLOCK_FEAR_EFFECT                     = 118699,
    WARLOCK_GLYPH_OF_FEAR_EFFECT            = 130616,
    WARLOCK_CREATE_HEALTHSTONE              = 23517,
    WARLOCK_HARVEST_LIFE_HEAL               = 125314,
    WARLOCK_DRAIN_LIFE_HEAL                 = 89653,
    WARLOCK_SOULBURN_AURA                   = 74434,
    WARLOCK_CORRUPTION                      = 172,
    WARLOCK_AGONY                           = 980,
    WARLOCK_DOOM                            = 603,
    WARLOCK_UNSTABLE_AFFLICTION             = 30108,
    WARLOCK_IMMOLATE                        = 348,
    WARLOCK_SHADOWBURN_ENERGIZE             = 125882,
    WARLOCK_CONFLAGRATE                     = 17962,
    WARLOCK_CONFLAGRATE_FIRE_AND_BRIMSTONE  = 108685,
    WARLOCK_IMMOLATE_FIRE_AND_BRIMSTONE     = 108686,
    WARLOCK_FIRE_AND_BRIMSTONE              = 108683,
    WARLOCK_GLYPH_OF_DEMON_TRAINING         = 56249,
    WARLOCK_BACKDRAFT                       = 117828,
    WARLOCK_PYROCLASM                       = 123686,
    WARLOCK_MANNOROTHS_FURY                 = 108508, 
    WARLOCK_RAIN_OF_FIRE                    = 5740,
    WARLOCK_RAIN_OF_FIRE_DAMAGE             = 42223,
    WARLOCK_RAIN_OF_FIRE_AFTERMATH          = 104232,
    WARLOCK_RAIN_OF_FIRE_DAMAGE_AFTERMATH   = 104233,
    WARLOCK_SPAWN_PURPLE_DEMONIC_GATEWAY    = 113890,
    WARLOCK_DEMONIC_GATEWAY_TELEPORT_GREEN  = 113896,
    WARLOCK_DEMONIC_GATEWAY_TELEPORT_PURPLE = 120729,
    WARLOCK_DEMONIC_GATEWAY_PERIODIC_CHARGE = 113901,
    WARLOCK_NIGHTFALL                       = 108558,
    WARLOCK_SOUL_SWAP_AURA                  = 86211,
    WARLOCK_SOUL_SWAP_VISUAL                = 92795,
	WARLOCK_GLYPH_OF_SOUL_SWAP				= 56226,
    WARLOCK_GRIMOIRE_OF_SACRIFICE           = 108503,
    WARLOCK_METAMORPHOSIS                   = 103958,
    WARLOCK_DEMONIC_LEAP_JUMP               = 54785,
    WARLOCK_ITEM_S12_TIER_4                 = 131632,
    WARLOCK_TWILIGHT_WARD_S12               = 131623,
    WARLOCK_TWILIGHT_WARD_METAMORPHOSIS_S12 = 131624,
    WARLOCK_SHADOWFLAME                     = 47960,
    WARLOCK_SOUL_LEECH_HEAL                 = 108366,
    WARLOCK_DARK_REGENERATION               = 108359,
    WARLOCK_DARK_BARGAIN_DOT                = 110914,
    WARLOCK_MOLTEN_CORE                     = 122355,
    WARLOCK_MOLTEN_CORE_AURA                = 122351,
    WARLOCK_MOLTEN_CORE_VISUAL              = 126090,
    WARLOCK_WILD_IMP_SUMMON                 = 104317,
    WARLOCK_DEMONIC_CALL                    = 114925,
    WARLOCK_DECIMATE_AURA                   = 108869,
    WARLOCK_SOUL_LEECH_AURA                 = 108370,
    WARLOCK_ARCHIMONDES_VENGEANCE_COOLDOWN  = 116405,
    WARLOCK_ARCHIMONDES_VENGEANCE_DAMAGE    = 124051,
    WARLOCK_ARCHIMONDES_VENGEANCE_PASSIVE   = 116403,
    WARLOCK_SOUL_LINK_DUMMY_AURA            = 108446,
    WARLOCK_GLYPH_OF_CONFLAGRATE            = 56235,
    WARLOCK_SHIELD_OF_SHADOW                = 115232,
    WARLOCK_THREATENING_PRESENCE            = 112042,
    WARLOCK_SUPPLANT_DEMONIC_COMMAND        = 119904,
    WARLOCK_KIL_JAEDENS_CUNNING_PASSIVE     = 108507,
    WARLOCK_AFTERMATH_STUN                  = 85387,
    WARLOCK_IMP_SWARM                       = 104316,
    WARLOCK_DISRUPTED_NETHER                = 114736,
    WARLOCK_GLYPH_OF_SIPHON_LIFE            = 56218,
    WARLOCK_GLYPH_OF_SOULWELL               = 58094,
    WARLOCK_GLYPH_OF_SOULWELL_VISUAL        = 34145,
    WARLOCK_SOULBURN_OVERRIDE_1             = 93312,
    WARLOCK_SOULBURN_OVERRIDE_2             = 93313,
    WARLOCK_SOULBURN_OVERRIDE_3             = 104245,
    WARLOCK_SOULBURN_OVERRIDE_4             = 104249,
    WARLOCK_SOULBURN_OVERRIDE_5             = 104250,
    WARLOCK_SOULBURN_OVERRIDE_6             = 104251,
    WARLOCK_SOULBURN_OVERRIDE_7             = 114787,
    WARLOCK_SEED_OF_CORRUPTION_DUMMY        = 86664,
    WARLOCK_SOULBURN_DEMONIC_CIRCLE_TELE    = 114794,
    WARLOCK_GRIMOIRE_OF_SUPREMACY_TALENT    = 108499,
    WARLOCK_SUMMON_FEL_IMP                  = 112866,
    WARLOCK_SUMMON_VOIDLORD                 = 112867,
    WARLOCK_SUMMON_SHIVARRA                 = 112868,
    WARLOCK_SUMMON_OBSERVER                 = 112869,
    WARLOCK_SUMMON_WRATHGUARD               = 112870,
    WARLOCK_SUMMON_ABYSSAL                  = 112921,
    WARLOCK_SUMMON_TERRORGUARD              = 112927,
    WARLOCK_SUMMON_GRIMOIRE_IMP             = 111859,
    WARLOCK_SUMMON_GRIMOIRE_VOIDWALKER      = 111895,
    WARLOCK_SUMMON_GRIMOIRE_SUCCUBUS        = 111896,
    WARLOCK_SUMMON_GRIMOIRE_FELHUNTER       = 111897,
    WARLOCK_SUMMON_GRIMOIRE_FELGUARD        = 111898,
    WARLOCK_HARVEST_LIFE                    = 108371,
    WARLOCK_IMMOLATION_AURA                 = 104025,
    WARLOCK_DARK_APOTHEOSIS                 = 114168,
    WARLOCK_METAMORPHOSIS_OVERRIDER         = 103965,
    WARLOCK_METAMORPHOSIS_RESISTANCE        = 54817,
    WARLOCK_METAMORPHOSIS_MODIFIERS         = 54879,
    WARLOCK_DEMONIC_FURY_PASSIVE            = 109145,
    WARLOCK_LIFE_TAP                        = 1454,
    WARLOCK_GLYPH_OF_LIFE_TAP               = 63320,
    WARLOCK_BACKLASH_AURA                   = 34936,
    WARLOCK_SOUL_SWAP                       = 86121,
    WARLOCK_SOUL_SWAP_EXHALE                = 86213,
    WARLOCK_TWILIGHT_WARD_METAMORPHOSIS     = 104048,
    WARLOCK_ENSLAVE_DEMON_METAMORPHOSIS     = 104043,
	WARLOCK_HAVOC_AURA						= 80240,
	WARLOCK_CAUTERIZE_MASTER				= 119905,
	WARLOCK_CAUTERIZE_MASTER_EFFECT			= 119899,
	WARLOCK_DISARM							= 119907,
	WARLOCK_FELLASH							= 119913,
	WARLOCK_FELSTORM						= 119914,
	WARLOCK_FELSTORM_EFFECT					= 89751,
	WARLOCK_OPTICAL_BLAST					= 119911,
	WARLOCK_SPELL_LOCK						= 119910,
	WARLOCK_SPELL_LOCK2						= 132409,
	WARLOCK_SPELL_LOCK2_EFFECT				= 24259,
	WARLOCK_WHIPLASH						= 119909,
	WARLOCK_WRATHSTORM						= 119915,
	WARLOCK_WRATHSTORM_EFFECT				= 115831,
	WARLOCK_DEMON_SINGLE_MAGIC				= 89808,
	WARLOCK_DEMON_SUFFERING					= 17735,
	WARLOCK_DEMON_SEDUCE					= 6358,
	WARLOCK_DEMON_SPELL_LOCK				= 19647,
	WARLOCK_DEMON_AXE_TOSS					= 89766,
	WARLOCK_BLOODY_FEAR_EFFECT				= 137143,
	WARLOCK_SIPHON_LIFE_HEAL				= 63106,
    WARLOCK_MASTERY_EMBERSTORM              = 77220,
    WARLOCK_MASTERY_POTENT_AFFLICTIONS      = 77215,
    WARLOCK_MASTERY_MASTER_DEMONOLOGIST     = 77219
};

// Demonic Slash - 114175
class spell_warl_demonic_slash : public SpellScriptLoader
{
    public:
        spell_warl_demonic_slash() : SpellScriptLoader("spell_warl_demonic_slash") { }

        class spell_warl_demonic_slash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_demonic_slash_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    int32 demonicFury = 60;
                    caster->CastCustomSpell(caster, 104314, NULL, &demonicFury, NULL, true);
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_demonic_slash_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_demonic_slash_SpellScript();
        }
};

// Fury Ward - 119839
class spell_warl_fury_ward : public SpellScriptLoader
{
    public:
        spell_warl_fury_ward() : SpellScriptLoader("spell_warl_fury_ward") { }

        class spell_warl_fury_ward_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_fury_ward_AuraScript);

            void CalculateAbsorb(constAuraEffectPtr /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                if (Unit* caster = GetCaster())
                    amount += (caster->SpellBaseDamageBonusDone(GetSpellInfo()->GetSchoolMask()) * 3.0f);
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_fury_ward_AuraScript::CalculateAbsorb, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_fury_ward_AuraScript();
        }
};

// Dark Apotheosis - 114168
class spell_warl_dark_apotheosis : public SpellScriptLoader
{
    public:
        spell_warl_dark_apotheosis() : SpellScriptLoader("spell_warl_dark_apotheosis") { }

        class spell_warl_dark_apotheosis_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_dark_apotheosis_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    caster->RemoveAura(WARLOCK_METAMORPHOSIS);

                    if (AuraPtr overrider = caster->AddAura(WARLOCK_METAMORPHOSIS_OVERRIDER, caster))
                    {
                        overrider->GetEffect(EFFECT_0)->ChangeAmount(114175);
                        overrider->GetEffect(EFFECT_1)->ChangeAmount(0);
                        overrider->GetEffect(EFFECT_3)->ChangeAmount(0);
                    }

                    caster->CastSpell(caster, WARLOCK_METAMORPHOSIS_RESISTANCE, true);
                    caster->CastSpell(caster, WARLOCK_METAMORPHOSIS_MODIFIERS, true);
                    caster->CastSpell(caster, WARLOCK_DEMONIC_FURY_PASSIVE, true);
                }
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    caster->RemoveAura(WARLOCK_METAMORPHOSIS_OVERRIDER);
                    caster->RemoveAura(WARLOCK_METAMORPHOSIS_RESISTANCE);
                    caster->RemoveAura(WARLOCK_METAMORPHOSIS_MODIFIERS);
                    caster->RemoveAura(WARLOCK_DEMONIC_FURY_PASSIVE);
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_dark_apotheosis_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_IGNORE_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warl_dark_apotheosis_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_IGNORE_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_dark_apotheosis_AuraScript();
        }
};

// Glyph of Demon Hunting - 63303
class spell_warl_glyph_of_demon_hunting : public SpellScriptLoader
{
    public:
        spell_warl_glyph_of_demon_hunting() : SpellScriptLoader("spell_warl_glyph_of_demon_hunting") { }

        class spell_warl_glyph_of_demon_hunting_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_glyph_of_demon_hunting_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->learnSpell(WARLOCK_DARK_APOTHEOSIS, false);
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    if (_player->HasSpell(WARLOCK_DARK_APOTHEOSIS))
                        _player->removeSpell(WARLOCK_DARK_APOTHEOSIS, false, false);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_glyph_of_demon_hunting_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warl_glyph_of_demon_hunting_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_glyph_of_demon_hunting_AuraScript();
        }
};

// Grimoire of Supremacy - 108499
class spell_warl_grimoire_of_supremacy : public SpellScriptLoader
{
    public:
        spell_warl_grimoire_of_supremacy() : SpellScriptLoader("spell_warl_grimoire_of_supremacy") { }

        class spell_warl_grimoire_of_supremacy_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_grimoire_of_supremacy_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                {
                    _player->learnSpell(WARLOCK_SUMMON_FEL_IMP, false);
                    _player->learnSpell(WARLOCK_SUMMON_VOIDLORD, false);
                    _player->learnSpell(WARLOCK_SUMMON_SHIVARRA, false);
                    _player->learnSpell(WARLOCK_SUMMON_OBSERVER, false);
                    _player->learnSpell(WARLOCK_SUMMON_ABYSSAL, false);
                    _player->learnSpell(WARLOCK_SUMMON_TERRORGUARD, false);

                    if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_WARLOCK_DEMONOLOGY)
                        _player->learnSpell(WARLOCK_SUMMON_WRATHGUARD, false);
                }
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                {
					if (Pet* pet = _player->GetPet())
					{
						switch (pet->GetEntry())
						{
							case ENTRY_FEL_IMP:
							case ENTRY_VOIDLORD:
							case ENTRY_SHIVARRA:
							case ENTRY_OBSERVER:
							case ENTRY_WRATHGUARD:
								pet->DespawnOrUnsummon();
								break;
						}
					}

                    if (_player->HasSpell(WARLOCK_SUMMON_FEL_IMP))
                        _player->removeSpell(WARLOCK_SUMMON_FEL_IMP, false, false);

                    if (_player->HasSpell(WARLOCK_SUMMON_VOIDLORD))
                        _player->removeSpell(WARLOCK_SUMMON_VOIDLORD, false, false);

                    if (_player->HasSpell(WARLOCK_SUMMON_SHIVARRA))
                        _player->removeSpell(WARLOCK_SUMMON_SHIVARRA, false, false);

                    if (_player->HasSpell(WARLOCK_SUMMON_OBSERVER))
                        _player->removeSpell(WARLOCK_SUMMON_OBSERVER, false, false);

                    if (_player->HasSpell(WARLOCK_SUMMON_WRATHGUARD))
                        _player->removeSpell(WARLOCK_SUMMON_WRATHGUARD, false, false);

                    if (_player->HasSpell(WARLOCK_SUMMON_ABYSSAL))
                        _player->removeSpell(WARLOCK_SUMMON_ABYSSAL, false, false);

                    if (_player->HasSpell(WARLOCK_SUMMON_TERRORGUARD))
                        _player->removeSpell(WARLOCK_SUMMON_TERRORGUARD, false, false);
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_grimoire_of_supremacy_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warl_grimoire_of_supremacy_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_grimoire_of_supremacy_AuraScript();
        }
};

// Soulburn : Drain Life - 89420
class spell_warl_soulburn_drain_life : public SpellScriptLoader
{
    public:
        spell_warl_soulburn_drain_life() : SpellScriptLoader("spell_warl_soulburn_drain_life") { }

        class spell_warl_soulburn_drain_life_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_soulburn_drain_life_AuraScript);

            void HandleApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (GetCaster())
                    if (GetCaster()->HasAura(WARLOCK_SOULBURN_AURA))
                        GetCaster()->RemoveAura(WARLOCK_SOULBURN_AURA);
            }

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (Unit* caster = GetCaster())
                {
                    Player* _player = GetCaster()->ToPlayer();
                    if (!_player)
                        return;

                    // Restoring 3% of the caster's total health every 1s
                    int32 basepoints = _player->CountPctFromMaxHealth(3);

                    // In Demonology spec : Generates 10 Demonic Fury per second
                    if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_WARLOCK_DEMONOLOGY)
                    {
                        int32 demonicFury = 10;
                        _player->CastCustomSpell(_player, 104314, NULL, &demonicFury, NULL, true);
                    }

                    if (_player->HasAura(WARLOCK_HARVEST_LIFE))
                        basepoints *= 2.5;

                    // Glyph of Drain Life
                    if (_player->HasAura(63302))
                        basepoints *= 1.3f;

                    // PvP Power affects on drain life heal
                    float PvPPower = 1 + (_player->GetFloatValue(PLAYER_FIELD_PVP_POWER_HEALING) / 100);
                    basepoints *= PvPPower;

                    _player->CastCustomSpell(_player, WARLOCK_DRAIN_LIFE_HEAL, &basepoints, NULL, NULL, true);
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_soulburn_drain_life_AuraScript::HandleApply, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_soulburn_drain_life_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_soulburn_drain_life_AuraScript();
        }
};

// Soulburn : Health Funnel - 104220
class spell_warl_soulburn_health_funnel : public SpellScriptLoader
{
    public:
        spell_warl_soulburn_health_funnel() : SpellScriptLoader("spell_warl_soulburn_health_funnel") { }

        class spell_warl_soulburn_health_funnel_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soulburn_health_funnel_SpellScript);

            void HandleOnHit()
            {
                if (Player* player = GetCaster()->ToPlayer())
                    player->CastSpell(player, 755, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_soulburn_health_funnel_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soulburn_health_funnel_SpellScript();
        }
};

// Soulburn : Seed of Corruption - Damage - 87385
class spell_warl_soulburn_seed_of_corruption_damage : public SpellScriptLoader
{
    public:
        spell_warl_soulburn_seed_of_corruption_damage() : SpellScriptLoader("spell_warl_soulburn_seed_of_corruption_damage") { }

        class spell_warl_soulburn_seed_of_corruption_damage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soulburn_seed_of_corruption_damage_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (GetExplTargetUnit())
                    targets.remove(GetExplTargetUnit());
            }

            void HandleScript()
            {
                if (!GetCaster())
                    return;

                // Remove Soul Burn aura
                if (GetCaster()->HasAura(WARLOCK_SEED_OF_CORRUPTION_DUMMY))
                    GetCaster()->RemoveAurasDueToSpell(WARLOCK_SEED_OF_CORRUPTION_DUMMY);
                // Add Corruption aura
                if (Unit* target = GetHitUnit())
                    GetCaster()->AddAura(146739, target);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warl_soulburn_seed_of_corruption_damage_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
                AfterHit += SpellHitFn(spell_warl_soulburn_seed_of_corruption_damage_SpellScript::HandleScript);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soulburn_seed_of_corruption_damage_SpellScript();
        }
};

// Called by Soulburn : Seed of Corruption - 114790
class spell_warl_soulburn_seed_of_corruption : public SpellScriptLoader
{
    public:
        spell_warl_soulburn_seed_of_corruption() : SpellScriptLoader("spell_warl_soulburn_seed_of_corruption") { }

        class spell_warl_soulburn_seed_of_corruption_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soulburn_seed_of_corruption_SpellScript);

            void HandleOnHit()
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    player->CastSpell(player, WARLOCK_SEED_OF_CORRUPTION_DUMMY, true);

                    if (player->HasAura(WARLOCK_SOULBURN_AURA))
                        player->RemoveAurasDueToSpell(WARLOCK_SOULBURN_AURA);
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_soulburn_seed_of_corruption_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soulburn_seed_of_corruption_SpellScript();
        }
};

// Called by Soulburn : Curse of Enfeeblement - 109468, Soulburn : Curse of Elements - 104225 and Soulburn : Curse of Exhaustion - 104223
// Soulburn aura - Remove - 74434
class spell_warl_soulburn_remove : public SpellScriptLoader
{
    public:
        spell_warl_soulburn_remove() : SpellScriptLoader("spell_warl_soulburn_remove") { }

        class spell_warl_soulburn_remove_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soulburn_remove_SpellScript);

            void HandleOnHit()
            {
                if (Player* player = GetCaster()->ToPlayer())
                    if (player->HasAura(WARLOCK_SOULBURN_AURA))
                        player->RemoveAurasDueToSpell(WARLOCK_SOULBURN_AURA);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_soulburn_remove_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soulburn_remove_SpellScript();
        }
};

// Soulburn - 74434
class spell_warl_soulburn_override : public SpellScriptLoader
{
    public:
        spell_warl_soulburn_override() : SpellScriptLoader("spell_warl_soulburn_override") { }

        class spell_warl_soulburn_override_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_soulburn_override_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster())
                    return;

                if (Player* player = GetCaster()->ToPlayer())
                {
                    // Overrides Drain Life, Undending Breath and Harvest Life
                    player->CastSpell(player, WARLOCK_SOULBURN_OVERRIDE_1, true);
                    // Overrides Seed of Corruption
                    player->CastSpell(player, WARLOCK_SOULBURN_OVERRIDE_2, true);
                    // Overrides Curse of Enfeeblement and Curse of Elements
                    player->CastSpell(player, WARLOCK_SOULBURN_OVERRIDE_3, true);
                    // Overrides Demonic Circle : Teleport
                    player->CastSpell(player, WARLOCK_SOULBURN_OVERRIDE_4, true);
                    // Overrides Curse of Exhaustion
                    player->CastSpell(player, WARLOCK_SOULBURN_OVERRIDE_5, true);
                    // Overrides Soul Swap
                    player->CastSpell(player, WARLOCK_SOULBURN_OVERRIDE_6, true);
                    // Overrides Health Funnel
                    player->CastSpell(player, WARLOCK_SOULBURN_OVERRIDE_7, true);
                }
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster())
                    return;

                if (Player* player = GetCaster()->ToPlayer())
                {
                    // Overrides Drain Life, Undending Breath and Harvest Life
                    player->RemoveAura(WARLOCK_SOULBURN_OVERRIDE_1);
                    // Overrides Seed of Corruption
                    player->RemoveAura(WARLOCK_SOULBURN_OVERRIDE_2);
                    // Overrides Curse of Enfeeblement and Curse of Elements
                    player->RemoveAura(WARLOCK_SOULBURN_OVERRIDE_3);
                    // Overrides Demonic Circle : Teleport
                    player->RemoveAura(WARLOCK_SOULBURN_OVERRIDE_4);
                    // Overrides Curse of Exhaustion
                    player->RemoveAura(WARLOCK_SOULBURN_OVERRIDE_5);
                    // Overrides Soul Swap
                    player->RemoveAura(WARLOCK_SOULBURN_OVERRIDE_6);
                    // Overrides Health Funnel
                    player->RemoveAura(WARLOCK_SOULBURN_OVERRIDE_7);
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_soulburn_override_AuraScript::OnApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warl_soulburn_override_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_soulburn_override_AuraScript();
        }
};

// Called by Create Soulwell - 29893
// Glyph of Soulwell - 58094
class spell_warl_glyph_of_soulwell : public SpellScriptLoader
{
    public:
        spell_warl_glyph_of_soulwell() : SpellScriptLoader("spell_warl_glyph_of_soulwell") { }

        class spell_warl_glyph_of_soulwell_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_glyph_of_soulwell_SpellScript);

            void HandleAfterCast()
            {
                if (!GetCaster())
                    return;

                if (!GetExplTargetDest())
                    return;

                if (!GetCaster()->HasAura(WARLOCK_GLYPH_OF_SOULWELL))
                    return;

                GetCaster()->CastSpell(GetExplTargetDest()->GetPositionX(), GetExplTargetDest()->GetPositionY(), GetExplTargetDest()->GetPositionZ(), WARLOCK_GLYPH_OF_SOULWELL_VISUAL, true);
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_warl_glyph_of_soulwell_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_glyph_of_soulwell_SpellScript();
        }
};

// Imp Swarm - 104316
class spell_warl_imp_swarm : public SpellScriptLoader
{
    public:
        spell_warl_imp_swarm() : SpellScriptLoader("spell_warl_imp_swarm") { }

        class spell_warl_imp_swarm_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_imp_swarm_SpellScript);

            SpellCastResult CheckSpec()
            {
                if (!GetCaster())
                    return SPELL_FAILED_DONT_REPORT;

                if (GetCaster()->GetTypeId() != TYPEID_PLAYER)
                    return SPELL_FAILED_DONT_REPORT;

                Player* _plr = GetCaster()->ToPlayer();
                if (_plr->GetSpecializationId(_plr->GetActiveSpec()) != SPEC_WARLOCK_DEMONOLOGY)
                    return SPELL_FAILED_DONT_REPORT;

                return SPELL_CAST_OK;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (Player* _plr = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        _plr->AddAura(WARLOCK_DEMONIC_CALL, _plr);
                        _plr->CastSpell(target, WARLOCK_WILD_IMP_SUMMON, true);
                        _plr->AddAura(WARLOCK_DEMONIC_CALL, _plr);
                        _plr->CastSpell(target, WARLOCK_WILD_IMP_SUMMON, true);
                        _plr->AddAura(WARLOCK_DEMONIC_CALL, _plr);
                        _plr->CastSpell(target, WARLOCK_WILD_IMP_SUMMON, true);
                        _plr->AddAura(WARLOCK_DEMONIC_CALL, _plr);
                        _plr->CastSpell(target, WARLOCK_WILD_IMP_SUMMON, true);
                        _plr->RemoveAura(WARLOCK_DEMONIC_CALL);
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warl_imp_swarm_SpellScript::CheckSpec);
                OnEffectHitTarget += SpellEffectFn(spell_warl_imp_swarm_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_imp_swarm_SpellScript();
        }
};

// Glyph of Imp Swarm - 56242
class spell_warl_glyph_of_imp_swarm : public SpellScriptLoader
{
    public:
        spell_warl_glyph_of_imp_swarm() : SpellScriptLoader("spell_warl_glyph_of_imp_swarm") { }

        class spell_warl_glyph_of_imp_swarm_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_glyph_of_imp_swarm_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    _player->learnSpell(WARLOCK_IMP_SWARM, false);
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Player* _player = GetTarget()->ToPlayer())
                    if (_player->HasSpell(WARLOCK_IMP_SWARM))
                        _player->removeSpell(WARLOCK_IMP_SWARM, false, false);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_glyph_of_imp_swarm_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warl_glyph_of_imp_swarm_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_glyph_of_imp_swarm_AuraScript();
        }
};

// Unbound Will - 108482
class spell_warl_unbound_will : public SpellScriptLoader
{
    public:
        spell_warl_unbound_will() : SpellScriptLoader("spell_warl_unbound_will") { }

        class spell_warl_unbound_will_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_unbound_will_SpellScript);

            SpellCastResult CheckHealth()
            {
                if (Unit* caster = GetCaster())
                {
                    if (caster->GetHealthPct() <= 20.0f)
                    {
                        SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_NOT_ENOUGH_HEALTH);
                        return SPELL_FAILED_CUSTOM_ERROR;
                    }
                    else
                        return SPELL_CAST_OK;
                }
                else
                    return SPELL_FAILED_DONT_REPORT;

                return SPELL_CAST_OK;
            }

            void HandleOnHit()
            {
				if (Player* player = GetCaster()->ToPlayer())
				{
					player->ModifyHealth(-int32(player->CountPctFromMaxHealth(20)));
					player->RemoveAurasWithMechanic((1 << MECHANIC_SNARE) | (1 << MECHANIC_ROOT) | (1 << MECHANIC_FREEZE));
					player->RemoveAurasByType(SPELL_AURA_MOD_CONFUSE);
					player->RemoveAurasByType(SPELL_AURA_MOD_FEAR);
					player->RemoveAurasByType(SPELL_AURA_MOD_FEAR_2);
					player->RemoveAurasByType(SPELL_AURA_MOD_STUN);
					player->RemoveAurasByType(SPELL_AURA_MOD_ROOT);
					player->RemoveAurasByType(SPELL_AURA_TRANSFORM);
					player->RemoveAurasByType(SPELL_AURA_STRANGULATE);
				}
				if (Guardian* pet = GetCaster()->GetGuardianPet())
				{
					pet->RemoveAurasWithMechanic((1 << MECHANIC_SNARE) | (1 << MECHANIC_ROOT) | (1 << MECHANIC_FREEZE));
					pet->RemoveAurasByType(SPELL_AURA_MOD_CONFUSE);
					pet->RemoveAurasByType(SPELL_AURA_MOD_FEAR);
					pet->RemoveAurasByType(SPELL_AURA_MOD_FEAR_2);
					pet->RemoveAurasByType(SPELL_AURA_MOD_STUN);
					pet->RemoveAurasByType(SPELL_AURA_MOD_ROOT);
					pet->RemoveAurasByType(SPELL_AURA_TRANSFORM);
					pet->RemoveAurasByType(SPELL_AURA_STRANGULATE);
				}
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warl_unbound_will_SpellScript::CheckHealth);
                OnHit += SpellHitFn(spell_warl_unbound_will_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_unbound_will_SpellScript();
        }
};

bool FirstTickBug = true;
// Rain of Fire (Destruction) - 104232
class spell_warl_rain_of_fire : public SpellScriptLoader
{
public:
    spell_warl_rain_of_fire() : SpellScriptLoader("spell_warl_rain_of_fire") { }

    class spell_warl_rain_of_fire_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_rain_of_fire_AuraScript);

        void OnTick(constAuraEffectPtr aurEff)
        {
            if (Unit* caster = GetCaster())
            {
                if (caster != GetTarget())
                    return;

                int32 count = caster->CountDynObject(WARLOCK_RAIN_OF_FIRE_AFTERMATH);
                int32 Range = caster->HasAura(WARLOCK_MANNOROTHS_FURY) ? 50 : 10;

                if (count > 1)
                {
                    std::list<DynamicObject*> RainOfFireList;
                    std::list<DynamicObject*> LastRain;

                    caster->GetDynObjectList(RainOfFireList, WARLOCK_RAIN_OF_FIRE_AFTERMATH);
                    caster->GetDynObjectList(LastRain, WARLOCK_RAIN_OF_FIRE_AFTERMATH);

                    if (!RainOfFireList.empty() || !LastRain.empty())
                    {
                        LastRain.sort(WoWSource::DynamicObjectsDurationPctOrderPred());

                        LastRain.reverse();
                        LastRain.resize(1);

                        for (auto itr1 : LastRain)
                        {
                            for (auto itr2 : RainOfFireList)
                            {
                                if (itr1->GetDistance(itr2) < Range)
                                {
                                    DynamicObject* RainOfFire = itr2;
                                    RainOfFire->SetDuration(0);
                                    FirstTickBug = false;
                                }
                                break;
                            }
                        }
                    }
                }

                caster->ForEachDynObject([=](DynamicObject* p_Object)
                {
                    caster->CastSpell(*p_Object, WARLOCK_RAIN_OF_FIRE_DAMAGE_AFTERMATH, true);
                    return true;
                });
            }
        }

        void Register() override
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_rain_of_fire_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_rain_of_fire_AuraScript();
    }
};

// Rain of Fire damage (destruction) - 104233
class spell_warl_rain_of_fire_damage : public SpellScriptLoader
{
public:
    spell_warl_rain_of_fire_damage() : SpellScriptLoader("spell_warl_rain_of_fire_damage") { }

    class spell_warl_rain_of_fire_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_rain_of_fire_damage_SpellScript);

        void HandleOnHit()
        {
            if (Player* player = GetCaster()->ToPlayer())
            {
                if (Unit* Target = GetHitUnit())
                {
                    if (Target->HasAura(WARLOCK_IMMOLATE) || Target->HasAura(WARLOCK_IMMOLATE_FIRE_AND_BRIMSTONE))
                        SetHitDamage(CalculatePct(GetHitDamage(), 150)); // +50%

                    if (roll_chance_i(10))
                        player->ModifyPower(POWER_BURNING_EMBERS, 2);

                    if (FirstTickBug == false)
                    {
                        SetHitDamage(0);
                        FirstTickBug = true;
                    }
                }
            }
        }

        void Register() override
        {
            OnHit += SpellHitFn(spell_warl_rain_of_fire_damage_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_rain_of_fire_damage_SpellScript();
    }
};

// Kil'Jaeden's Cunning (passive with cooldown) - 119048
class spell_warl_kil_jaedens_cunning : public SpellScriptLoader
{
    public:
        spell_warl_kil_jaedens_cunning() : SpellScriptLoader("spell_warl_kil_jaedens_cunning") { }

        class spell_warl_kil_jaedens_cunning_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_kil_jaedens_cunning_AuraScript);

            void HandleApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (GetCaster())
                    GetCaster()->RemoveAura(WARLOCK_KIL_JAEDENS_CUNNING_PASSIVE);
            }

            void HandleRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (GetCaster())
                    GetCaster()->CastSpell(GetCaster(), WARLOCK_KIL_JAEDENS_CUNNING_PASSIVE, true);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_kil_jaedens_cunning_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                OnEffectRemove += AuraEffectRemoveFn(spell_warl_kil_jaedens_cunning_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_kil_jaedens_cunning_AuraScript();
        }
};

// Voidwalker : Shield of Shadow - 103130
class spell_warl_shield_of_shadow : public SpellScriptLoader
{
    public:
        spell_warl_shield_of_shadow() : SpellScriptLoader("spell_warl_shield_of_shadow") { }

        class spell_warl_shield_of_shadow_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_shield_of_shadow_AuraScript);

            void OnUpdate(uint32 diff, AuraEffectPtr aurEff)
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Pet* pet = _player->GetPet())
                        if (pet->GetEntry() == ENTRY_VOIDWALKER) // Voidwalker
                            if (!pet->HasSpell(WARLOCK_SHIELD_OF_SHADOW))
                                pet->addSpell(WARLOCK_SHIELD_OF_SHADOW);
            }

            void Register()
            {
                OnEffectUpdate += AuraEffectUpdateFn(spell_warl_shield_of_shadow_AuraScript::OnUpdate, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_shield_of_shadow_AuraScript();
        }
};

// Agony - 980
class spell_warl_agony : public SpellScriptLoader
{
    public:
        spell_warl_agony() : SpellScriptLoader("spell_warl_agony") { }

        class spell_warl_agony_AuraScript : public AuraScript
        {
            /*PrepareAuraScript(spell_warl_agony_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (GetCaster())
                    if (GetTarget())
                        if (AuraPtr agony = GetTarget()->GetAura(aurEff->GetSpellInfo()->Id, GetCaster()->GetGUID()))
                            agony->ModStackAmount(1);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_agony_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }*/
			PrepareAuraScript(spell_warl_agony_AuraScript);

			bool m_PreventRecalculation;
			
			bool Load() override
			{
				m_PreventRecalculation = false;	
				
				return true;
			}

			void CalculateAmount(constAuraEffectPtr auraEffect, int32& amount, bool& /*canBeRecalculated*/)
			{
				//return m_PreventRecalculation; ///< Only when refreshed
				if (!m_PreventRecalculation)
					amount = 0;			
											
			}

			void SetData(uint32 type, uint32 data) override
			{
				if (type == 0){					
					m_PreventRecalculation = (data != 0);
				}					
			}

			void OnTick(constAuraEffectPtr aurEff)
			{
				if (GetCaster())
				{
					if (GetTarget())
					{
						if (AuraPtr agony = GetTarget()->GetAura(aurEff->GetSpellInfo()->Id, GetCaster()->GetGUID()))
						{
							m_PreventRecalculation = true;
							agony->ModStackAmount(1);
							m_PreventRecalculation = false;							
						}
					}
				}
			}

			void Register() override
			{
				DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_agony_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);				
				OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_agony_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
			}
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_agony_AuraScript();
        }
};

// Grimoire of Sacrifice - 108503
class spell_warl_grimoire_of_sacrifice : public SpellScriptLoader
{
    public:
        spell_warl_grimoire_of_sacrifice() : SpellScriptLoader("spell_warl_grimoire_of_sacrifice") { }

        class spell_warl_grimoire_of_sacrifice_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_grimoire_of_sacrifice_SpellScript);

            void HandleAfterCast()
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    if (Pet* pet = player->GetPet())
                    {
                        // Supplant Command Demon
                        if (player->getLevel() >= 56)
                        {
                            int32 bp = 0;

                            player->RemoveAura(WARLOCK_SUPPLANT_DEMONIC_COMMAND);

                            switch (pet->GetEntry())
                            {
                                case ENTRY_IMP:
                                    bp = 132411;// Single Magic
                                    break;
                                case ENTRY_VOIDWALKER:
                                    bp = 132413;// Shadow Bulwark
                                    break;
                                case ENTRY_SUCCUBUS:
                                    bp = 137706;// Whiplash
                                    break;
                                case ENTRY_FELHUNTER:
                                    bp = 132409;// Spell Lock
                                    break;
                                case ENTRY_FELGUARD:
                                    bp = 132410;// Pursuit
                                    break;
                                default:
                                    break;
                            }

                            if (bp)
                                player->CastCustomSpell(player, WARLOCK_SUPPLANT_DEMONIC_COMMAND, &bp, NULL, NULL, true);
                        }
                    }
                }
            }

            void HandleOnHit()
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    // EFFECT_0 : Instakill
                    // EFFECT_1 : 2% health every 5s
                    // EFFECT_2 : +20% DOT damage for Malefic Grasp, Drain Soul
                    // EFFECT_3 : +25% damage for Shadow Bolt, Hand of Gul'Dan, Soul Fire, Wild Imps and Fel Flame
                    // EFFECT_4 : +15% damage for Incinerate, Conflagrate, Shadowburn and Fel Flame
                    // EFFECT_5 : +20% damage for Fel Flame, Haunt
                    // EFFECT_6 : +20% Health if Soul Link talent is also chosen
                    // EFFECT_7 : +20% Malefic Grasp - DISABLE
                    // EFFECT_8 : +20% on Drain Soul - DISABLE
                    // EFFECT_9 : +25% drain life
                    // EFFECT_10 : +15% drain life
                    // EFFECT_11 : +3 sec to chaos bolt
                    if (AuraPtr grimoireOfSacrifice = player->GetAura(WARLOCK_GRIMOIRE_OF_SACRIFICE))
                    {  
						switch (player->GetSpecializationId(player->GetActiveSpec()))
						{
							case SPEC_WARLOCK_AFFLICTION:
								if (grimoireOfSacrifice->GetEffect(EFFECT_3))
									grimoireOfSacrifice->GetEffect(EFFECT_3)->SetAmount(0);
								if (grimoireOfSacrifice->GetEffect(EFFECT_4))
									grimoireOfSacrifice->GetEffect(EFFECT_4)->SetAmount(0);
								if (grimoireOfSacrifice->GetEffect(EFFECT_11))
									grimoireOfSacrifice->GetEffect(EFFECT_11)->SetAmount(0);
								break;
							case SPEC_WARLOCK_DEMONOLOGY:
								
								if (grimoireOfSacrifice->GetEffect(EFFECT_2))
									grimoireOfSacrifice->GetEffect(EFFECT_2)->SetAmount(0);
								if (grimoireOfSacrifice->GetEffect(EFFECT_4))
									grimoireOfSacrifice->GetEffect(EFFECT_4)->SetAmount(0);
								if (grimoireOfSacrifice->GetEffect(EFFECT_5))
									grimoireOfSacrifice->GetEffect(EFFECT_5)->SetAmount(0);
								if (grimoireOfSacrifice->GetEffect(EFFECT_7))
									grimoireOfSacrifice->GetEffect(EFFECT_7)->SetAmount(0);							
								if (grimoireOfSacrifice->GetEffect(EFFECT_11))
									grimoireOfSacrifice->GetEffect(EFFECT_11)->SetAmount(0);

								break;
							case SPEC_WARLOCK_DESTRUCTION:
								if (grimoireOfSacrifice->GetEffect(EFFECT_2))
									grimoireOfSacrifice->GetEffect(EFFECT_2)->SetAmount(0);
								if (grimoireOfSacrifice->GetEffect(EFFECT_3))
									grimoireOfSacrifice->GetEffect(EFFECT_3)->SetAmount(0);
								if (grimoireOfSacrifice->GetEffect(EFFECT_5))
									grimoireOfSacrifice->GetEffect(EFFECT_5)->SetAmount(0);
								if (grimoireOfSacrifice->GetEffect(EFFECT_7))
									grimoireOfSacrifice->GetEffect(EFFECT_7)->SetAmount(0);
								break;
							case SPEC_NONE:
								if (grimoireOfSacrifice->GetEffect(EFFECT_2))
									grimoireOfSacrifice->GetEffect(EFFECT_2)->SetAmount(0);
								if (grimoireOfSacrifice->GetEffect(EFFECT_3))
									grimoireOfSacrifice->GetEffect(EFFECT_3)->SetAmount(0);
								if (grimoireOfSacrifice->GetEffect(EFFECT_4))
									grimoireOfSacrifice->GetEffect(EFFECT_4)->SetAmount(0);
								if (grimoireOfSacrifice->GetEffect(EFFECT_7))
									grimoireOfSacrifice->GetEffect(EFFECT_7)->SetAmount(0);
							default:
								break;
						}
                    }
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_warl_grimoire_of_sacrifice_SpellScript::HandleAfterCast);
                OnHit += SpellHitFn(spell_warl_grimoire_of_sacrifice_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_grimoire_of_sacrifice_SpellScript();
        }

        class spell_warl_grimoire_of_sacrifice_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_grimoire_of_sacrifice_AuraScript);

            void HandleRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (!GetTarget())
                    return;

				if (Player* _player = GetTarget()->ToPlayer()){
					if (_player->HasAura(WARLOCK_SUPPLANT_DEMONIC_COMMAND))
						_player->RemoveAura(WARLOCK_SUPPLANT_DEMONIC_COMMAND);
				}
            }

            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_warl_grimoire_of_sacrifice_AuraScript::HandleRemove, EFFECT_1, SPELL_AURA_OBS_MOD_HEALTH, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_grimoire_of_sacrifice_AuraScript();
        }
};

// Flames of Xoroth - 120451
class spell_warl_flames_of_xoroth : public SpellScriptLoader
{
    public:
        spell_warl_flames_of_xoroth() : SpellScriptLoader("spell_warl_flames_of_xoroth") { }

        class spell_warl_flames_of_xoroth_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_flames_of_xoroth_SpellScript);

            bool Load()
            {
                return GetCaster()->GetTypeId() == TYPEID_PLAYER;
            }

            SpellCastResult CheckPet()
            {
                if (!GetCaster())
                    return SPELL_FAILED_DONT_REPORT;

                Player* _plr = GetCaster()->ToPlayer();
                if (!_plr)
                    return SPELL_FAILED_DONT_REPORT;

                if (Pet* pet = _plr->GetPet())
                    return SPELL_FAILED_ALREADY_HAVE_PET;

                return SPELL_CAST_OK;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (!GetCaster())
                    return;

                Player* player = GetCaster()->ToPlayer();
                if (player->GetLastPetNumber())
                {
                    PetType newPetType = (player->getClass() == CLASS_HUNTER) ? HUNTER_PET : SUMMON_PET;
                    if (Pet* newPet = new Pet(player, newPetType))
                    {
                        if (newPet->LoadPetFromDB(player, 0, player->GetLastPetNumber(), true))
                        {
                            // revive the pet if it is dead
                            if (newPet->getDeathState() == DEAD || newPet->getDeathState() == CORPSE)
                                newPet->setDeathState(ALIVE);

                            newPet->ClearUnitState(uint32(UNIT_STATE_ALL_STATE));
                            newPet->SetFullHealth();
                            newPet->SetPower(newPet->getPowerType(), newPet->GetMaxPower(newPet->getPowerType()));

                            switch (newPet->GetEntry())
                            {
                                case 11859: // Doomguard
                                case 89:    // Inferno
                                    newPet->SetEntry(416);
                                    break;
                                default:
                                    break;
                            }
                        }
                        else
                            delete newPet;
                    }
                }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warl_flames_of_xoroth_SpellScript::CheckPet);
                OnEffectHitTarget += SpellEffectFn(spell_warl_flames_of_xoroth_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_flames_of_xoroth_SpellScript();
        }
};

// Soul Link - 108446
class spell_warl_soul_link_dummy : public SpellScriptLoader
{
public:
    spell_warl_soul_link_dummy() : SpellScriptLoader("spell_warl_soul_link_dummy") { }

    class spell_warl_soul_link_dummy_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_soul_link_dummy_AuraScript);

        void HandleRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
        {
            if (!GetCaster() || !GetTarget())
                return;

            if (Player* _player = GetCaster()->ToPlayer())
            {
                if (GetTarget()->GetGUID() == _player->GetGUID())
                    if (Pet* pet = _player->GetPet())
                        if (pet->HasAura(WARLOCK_SOUL_LINK_DUMMY_AURA))
                            pet->RemoveAura(WARLOCK_SOUL_LINK_DUMMY_AURA);

                if (_player->HasAura(WARLOCK_SOUL_LINK_DUMMY_AURA))
                    _player->RemoveAura(WARLOCK_SOUL_LINK_DUMMY_AURA);

                if (AuraPtr grimoireOfSacrifice = _player->GetAura(WARLOCK_GRIMOIRE_OF_SACRIFICE))
                    if (grimoireOfSacrifice->GetEffect(EFFECT_6))
                        grimoireOfSacrifice->GetEffect(EFFECT_6)->SetAmount(0);
            }
        }

        void Register()
        {
            OnEffectRemove += AuraEffectApplyFn(spell_warl_soul_link_dummy_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_soul_link_dummy_AuraScript();
    }
};

// Archimonde's Vengeance (Cooldown marker) - 108505
class spell_warl_archimondes_vengeance_cooldown : public SpellScriptLoader
{
    public:
        spell_warl_archimondes_vengeance_cooldown() : SpellScriptLoader("spell_warl_archimondes_vengeance_cooldown") { }

        class spell_warl_archimondes_vengeance_cooldown_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_archimondes_vengeance_cooldown_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (!_player->HasSpellCooldown(WARLOCK_ARCHIMONDES_VENGEANCE_PASSIVE))
                            _player->AddSpellCooldown(WARLOCK_ARCHIMONDES_VENGEANCE_PASSIVE, 0, time(NULL) + 120);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_archimondes_vengeance_cooldown_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_archimondes_vengeance_cooldown_SpellScript();
        }
};

// Archimonde's Vengeance - 108505
class spell_warl_archimondes_vengance : public SpellScriptLoader
{
    public:
        spell_warl_archimondes_vengance() : SpellScriptLoader("spell_warl_archimondes_vengance") { }

        class spell_warl_archimondes_vengance_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_archimondes_vengance_AuraScript);

            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                if (!GetCaster())
                    return;

                if (!GetTarget())
                    return;

                std::list<Unit*> tempList;
                std::list<Unit*> targetList;
                Unit* target = NULL;

                GetCaster()->GetAttackableUnitListInRange(tempList, 100.0f);

                if (tempList.empty())
                    return;

                for (auto itr : tempList)
                {
                    if (itr->GetGUID() == GetCaster()->GetGUID())
                        continue;

                    if (itr->HasAura(aurEff->GetSpellInfo()->Id, GetCaster()->GetGUID()))
                        targetList.push_back(itr);
                }

                if (targetList.empty())
                    return;

                if (targetList.size() > 1)
                    return;

                for (auto itr : targetList)
                    target = itr;

                if (!target)
                    return;

                if (eventInfo.GetActor()->GetGUID() == GetTarget()->GetGUID())
                    return;

                if (!eventInfo.GetDamageInfo()->GetDamage())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (target->HasAura(aurEff->GetSpellInfo()->Id, _player->GetGUID()))
                    {
                        int32 bp = int32(eventInfo.GetDamageInfo()->GetDamage() / 4);

                        if (!bp)
                            return;

                        _player->CastCustomSpell(target, WARLOCK_ARCHIMONDES_VENGEANCE_DAMAGE, &bp, NULL, NULL, true);
                    }
                }

                tempList.clear();
                targetList.clear();
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_warl_archimondes_vengance_AuraScript::OnProc, EFFECT_1, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_archimondes_vengance_AuraScript();
        }
};

// Called by Firebolt - 3110, Felbolt - 115746, Seduction - 6358, Mesmerize - 115268
// Glyph of Demon Training - 56249
class spell_warl_glyph_of_demon_training : public SpellScriptLoader
{
public:
    spell_warl_glyph_of_demon_training() : SpellScriptLoader("spell_warl_glyph_of_demon_training") { }

    class spell_warl_glyph_of_demon_training_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_glyph_of_demon_training_SpellScript);

        enum
        {
            Firebolt         = 3110,
            Felbolt          = 115746,
            Seduction        = 6358,
            Mesmerize        = 115268,
            RedFireVisual    = 23402,
            GreenFireVisual  = 25762,
        };

        void HandleOnCast()
        {
            if (Pet* pet = GetCaster()->ToPet())
            {
                if (Unit* target = pet->getVictim())
                {
                    if (Player* owner = pet->GetOwner())
                    {
                        if (owner->HasAura(WARLOCK_GLYPH_OF_DEMON_TRAINING))
                        {
                            if (GetSpellInfo()->Id == Firebolt || GetSpellInfo()->Id == Felbolt)
                            {
                                if (pet->GetEntry() == ENTRY_IMP)
                                    pet->SendPlaySpellVisual(RedFireVisual, target, 15.f);
                                else if (pet->GetEntry() == ENTRY_FEL_IMP)
                                    pet->SendPlaySpellVisual(GreenFireVisual, target, 15.f);
                            }
                        }
                    }
                }
            }
        }

        void HandleOnHit()
        {
            if (Pet* pet = GetCaster()->ToPet())
            {
                if (Unit* target = pet->getVictim())
                {
                    if (Player* owner = pet->GetOwner())
                    {
                        if (owner->HasAura(WARLOCK_GLYPH_OF_DEMON_TRAINING))
                        {
                            if (GetSpellInfo()->Id == Firebolt || GetSpellInfo()->Id == Felbolt)
                            {
                                int32 Damage = GetHitDamage();
                                int32 NewDamage = Damage / 3;
                                int32 FinalDamage = NewDamage;

                                FinalDamage -= target->GetDamageReduction(uint32(FinalDamage));

                                bool isCrit = false;

                                if (GetSpell()->IsCritForTarget(target))
                                {
                                    isCrit = true;
                                    FinalDamage *= 2;
                                }

                                SetHitDamage(NewDamage);

                                pet->DealDamage(target, FinalDamage, NULL, SPELL_DIRECT_DAMAGE, SPELL_SCHOOL_MASK_FIRE, NULL, isCrit);
                                pet->DealDamage(target, FinalDamage, NULL, SPELL_DIRECT_DAMAGE, SPELL_SCHOOL_MASK_FIRE, NULL, isCrit);

                                pet->SendSpellNonMeleeDamageLog(target, GetSpellInfo()->Id, FinalDamage, SPELL_SCHOOL_MASK_FIRE, 0, 0, false, 0, isCrit);
                                pet->SendSpellNonMeleeDamageLog(target, GetSpellInfo()->Id, FinalDamage, SPELL_SCHOOL_MASK_FIRE, 0, 0, false, 0, isCrit);
                            }
                            else if (GetSpellInfo()->Id == Seduction || GetSpellInfo()->Id == Mesmerize)
                            {
                                target->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE, 0, target->GetAura(32409)); // Shawow Word : Death Self Damage not be removed.
                                target->RemoveAurasByType(SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
                                target->RemoveAurasByType(SPELL_AURA_PERIODIC_LEECH);
                            }
                        }
                    }
                }
            }
        }


        void Register()
        {
            OnCast += SpellCastFn(spell_warl_glyph_of_demon_training_SpellScript::HandleOnCast);
            OnHit += SpellHitFn(spell_warl_glyph_of_demon_training_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_glyph_of_demon_training_SpellScript();
    }
};

// Archimonde's Vengeance (5% passive) - 116403
class spell_warl_archimondes_vengance_passive : public SpellScriptLoader
{
    public:
        spell_warl_archimondes_vengance_passive() : SpellScriptLoader("spell_warl_archimondes_vengance_passive") { }

        class spell_warl_archimondes_vengance_passive_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_archimondes_vengance_passive_AuraScript);

            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                if (!GetCaster())
                    return;

                if (eventInfo.GetActor()->GetGUID() == GetTarget()->GetGUID())
                    return;

                if (!eventInfo.GetDamageInfo()->GetDamage())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasSpellCooldown(WARLOCK_ARCHIMONDES_VENGEANCE_PASSIVE))
                        return;

                    if (GetTarget()->HasAura(aurEff->GetSpellInfo()->Id, _player->GetGUID()))
                    {
                        int32 bp = int32(eventInfo.GetDamageInfo()->GetDamage() / 20);

                        if (!bp)
                            return;

                        _player->CastCustomSpell(eventInfo.GetActor(), WARLOCK_ARCHIMONDES_VENGEANCE_DAMAGE, &bp, NULL, NULL, true);
                    }
                }
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_warl_archimondes_vengance_passive_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_archimondes_vengance_passive_AuraScript();
        }
};

// Called by Shadowflame - 47960
// Molten Core - 122351
class spell_warl_molten_core_dot : public SpellScriptLoader
{
    public:
        spell_warl_molten_core_dot() : SpellScriptLoader("spell_warl_molten_core_dot") { }

        class spell_warl_molten_core_dot_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_molten_core_dot_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (GetCaster())
                {
                    if (GetCaster()->HasAura(WARLOCK_MOLTEN_CORE_AURA) && GetCaster()->getLevel() >= 69)
                        if (roll_chance_i(8))
                        {
                            GetCaster()->CastSpell(GetCaster(), WARLOCK_MOLTEN_CORE, true);
                            
                            if (AuraPtr MoltenCore = GetCaster()->GetAura(WARLOCK_MOLTEN_CORE))
                            {
                                int32 stacks = MoltenCore->GetStackAmount();

                                if (stacks > 1)
                                    GetCaster()->CastSpell(GetCaster(), WARLOCK_MOLTEN_CORE_VISUAL, true);
                            }
                        }

                    int32 demonicFury = 2;
                    GetCaster()->CastCustomSpell(GetCaster(), 104314, NULL, &demonicFury, NULL, true);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_molten_core_dot_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_molten_core_dot_AuraScript();
        }
};

// Called by Shadow Bolt - 686 and Soul Fire - 6353
// Decimate - 108869
class spell_warl_decimate : public SpellScriptLoader
{
    public:
        spell_warl_decimate() : SpellScriptLoader("spell_warl_decimate") { }

        class spell_warl_decimate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_decimate_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    Unit* target = GetHitUnit();
                    if (target)
                        if (_player->HasAura(WARLOCK_DECIMATE_AURA) && _player->getLevel() >= 73)
                            if (target->GetHealthPct() < 25.0f)
                            {
                               _player->CastSpell(_player, WARLOCK_MOLTEN_CORE, true);

                               if (AuraPtr MoltenCore = GetCaster()->GetAura(WARLOCK_MOLTEN_CORE))
                               {
                                   int32 stacks = MoltenCore->GetStackAmount();

                                   if (stacks > 1)
                                       GetCaster()->CastSpell(GetCaster(), WARLOCK_MOLTEN_CORE_VISUAL, true);
                               }
                            }        

                    if (_player->HasAura(145072))
                    {
                        if (m_scriptSpellId == 6353 && roll_chance_i(20))
                        {
                            _player->CastSpell(_player, 145085, true);
                        }
                    }
                    if (_player->HasAura(145091))
                    {
                        if (m_scriptSpellId == 686 && roll_chance_i(8) && target)
                            _player->CastSpell(target, 105174, true);
                    }                    
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_decimate_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_decimate_SpellScript();
        }
};

// Called by Shadow Bolt - 686, Shadow Bolt (with glyph) - 112092, Soul Fire - 6353, Touch of Chaos - 103964 and Demonic Slash - 114175
// Soul Fire (metamorphosis) - 104027
// Demonic Call - 114925
class spell_warl_demonic_call : public SpellScriptLoader
{
    public:
        spell_warl_demonic_call() : SpellScriptLoader("spell_warl_demonic_call") { }

        class spell_warl_demonic_call_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_demonic_call_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (_player->HasAura(WARLOCK_DEMONIC_CALL) && !_player->HasAura(WARLOCK_DISRUPTED_NETHER))
                        {
                            _player->CastSpell(_player, WARLOCK_WILD_IMP_SUMMON, true);
                            _player->RemoveAura(WARLOCK_DEMONIC_CALL);
                        }
                    }                   
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_demonic_call_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_demonic_call_SpellScript();
        }
};

// Chaos Wave - 124916
class spell_warl_chaos_wave : public SpellScriptLoader
{
    public:
        spell_warl_chaos_wave() : SpellScriptLoader("spell_warl_chaos_wave") { }

        class spell_warl_chaos_wave_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_chaos_wave_SpellScript);

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (_player->HasAura(WARLOCK_MOLTEN_CORE_AURA) && _player->getLevel() >= 69)
                    {
                        _player->CastSpell(_player, WARLOCK_MOLTEN_CORE, true);

                        if (AuraPtr MoltenCore = GetCaster()->GetAura(WARLOCK_MOLTEN_CORE))
                        {
                            int32 stacks = MoltenCore->GetStackAmount();

                            if (stacks > 1)
                                GetCaster()->CastSpell(GetCaster(), WARLOCK_MOLTEN_CORE_VISUAL, true);
                        }
                    }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_warl_chaos_wave_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_chaos_wave_SpellScript();
        }
};

// Metamorphosis - 103958
class spell_warl_metamorphosis_cost : public SpellScriptLoader
{
    public:
        spell_warl_metamorphosis_cost() : SpellScriptLoader("spell_warl_metamorphosis_cost") { }

        class spell_warl_metamorphosis_cost_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_metamorphosis_cost_AuraScript);

            enum PasiveOverrideAuras
            {
                Metamorphosis_Immolation_Aura   = 109797,
                Metamorphosis_Touch_of_Chaos    = 112089,
                Metamorphosis_Cursed_Auras      = 116208,
                Metamorphosis_Doom              = 124913,
                Metamorphosis_Chaos_Wave        = 124917,
                Metamorphosis_Void_Ray          = 129343
            };

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Player* player = caster->ToPlayer())
                    {
                        if (player->HasAura(WARLOCK_DARK_APOTHEOSIS))
                            player->RemoveAura(WARLOCK_DARK_APOTHEOSIS);

                        if (AuraPtr overrider = player->AddAura(WARLOCK_METAMORPHOSIS_OVERRIDER, player))
                        {
                            overrider->GetEffect(EFFECT_7)->ChangeAmount(0); // This is only for Dark Apotheosis

                            if (!player->HasSpell(Metamorphosis_Immolation_Aura))
                                overrider->GetEffect(EFFECT_2)->ChangeAmount(0);

                            if (!player->HasSpell(Metamorphosis_Touch_of_Chaos))
                                overrider->GetEffect(EFFECT_0)->ChangeAmount(0);

                            if (!player->HasSpell(Metamorphosis_Cursed_Auras))
                            {
                                overrider->GetEffect(EFFECT_5)->ChangeAmount(0);
                                overrider->GetEffect(EFFECT_6)->ChangeAmount(0);
                            }

                            if (!player->HasSpell(Metamorphosis_Doom))
                                overrider->GetEffect(EFFECT_1)->ChangeAmount(0);

                            if (!player->HasSpell(Metamorphosis_Chaos_Wave))
                                overrider->GetEffect(EFFECT_3)->ChangeAmount(0);

                            if (!player->HasSpell(Metamorphosis_Void_Ray))
                                overrider->GetEffect(EFFECT_4)->ChangeAmount(0);
                        }
                    }
                }
            }

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Player* player = caster->ToPlayer())
                    {
                        int32 demonicFury = -6;
                        player->CastCustomSpell(player, 104314, NULL, &demonicFury, NULL, true);
                    }
                }
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Player* player = caster->ToPlayer())
                    {
                        if (player->HasAura(WARLOCK_METAMORPHOSIS_OVERRIDER))
                            player->RemoveAura(WARLOCK_METAMORPHOSIS_OVERRIDER);
                    }
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_metamorphosis_cost_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_metamorphosis_cost_AuraScript::OnTick, EFFECT_2, SPELL_AURA_PERIODIC_DUMMY);
                OnEffectRemove += AuraEffectApplyFn(spell_warl_metamorphosis_cost_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_SHAPESHIFT, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_metamorphosis_cost_AuraScript();
        }
};

// Immolation Aura - 104025
class spell_warl_immolation_aura : public SpellScriptLoader
{
    public:
        spell_warl_immolation_aura() : SpellScriptLoader("spell_warl_immolation_aura") { }

        class spell_warl_immolation_aura_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_immolation_aura_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (GetCaster())
                {
                    int32 demonicFury = -25;
                    GetCaster()->CastCustomSpell(GetCaster(), 104314, NULL, &demonicFury, NULL, true);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_immolation_aura_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_immolation_aura_AuraScript();
        }
};

// Dark Bargain - 110013
class spell_warl_dark_bargain_on_absorb : public SpellScriptLoader
{
    public:
        spell_warl_dark_bargain_on_absorb() : SpellScriptLoader("spell_warl_dark_bargain_on_absorb") { }

        class spell_warl_dark_bargain_on_absorb_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_dark_bargain_on_absorb_AuraScript);

            uint32 totalAbsorbAmount;

            bool Load()
            {
                totalAbsorbAmount = 0;
                return true;
            }

            void CalculateAmount(constAuraEffectPtr /*aurEff*/, int32 & amount, bool & /*canBeRecalculated*/)
            {
                amount = int32(100000000);
            }

            void OnAbsorb(AuraEffectPtr aurEff, DamageInfo& dmgInfo, uint32& absorbAmount)
            {
                totalAbsorbAmount += dmgInfo.GetDamage();
            }

            void OnRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                // (totalAbsorbAmount / 16) it's for totalAbsorbAmount 50% & totalAbsorbAmount / 8 (for each tick of custom spell)
                if (Unit* caster = GetCaster())
                    caster->CastCustomSpell(WARLOCK_DARK_BARGAIN_DOT, SPELLVALUE_BASE_POINT0, (totalAbsorbAmount / 16) , caster, true);
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_dark_bargain_on_absorb_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
                OnEffectAbsorb += AuraEffectAbsorbFn(spell_warl_dark_bargain_on_absorb_AuraScript::OnAbsorb, EFFECT_0);
                AfterEffectRemove += AuraEffectRemoveFn(spell_warl_dark_bargain_on_absorb_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_dark_bargain_on_absorb_AuraScript();
        }
};

// Dark Regeneration - 108359
class spell_warl_dark_regeneration : public SpellScriptLoader
{
    public:
        spell_warl_dark_regeneration() : SpellScriptLoader("spell_warl_dark_regeneration") { }

        class spell_warl_dark_regeneration_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_dark_regeneration_AuraScript);

            void HandleApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (GetTarget())
                    if (Guardian* pet = GetTarget()->GetGuardianPet())
                        pet->CastSpell(pet, WARLOCK_DARK_REGENERATION, true);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_dark_regeneration_AuraScript::HandleApply, EFFECT_0, SPELL_AURA_OBS_MOD_HEALTH, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_dark_regeneration_AuraScript();
        }
};

// Called by Haunt - 48181, Fel Flame - 77799, Shadow Bolt - 686, Incinerate - 29722, Chaos Bolt - 116858
// Touch of Chaos - 103964, Demonic Slash - 114175, Soul Fire - 6353, Soul Fire (Metamorphosis) - 104027
// Void Ray - 115422 and Shadow Burn - 17877
// Soul Leech - 108370
class spell_warl_soul_leech : public SpellScriptLoader
{
    public:
        spell_warl_soul_leech() : SpellScriptLoader("spell_warl_soul_leech") { }

        class spell_warl_soul_leech_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soul_leech_SpellScript);

            void HandleAfterHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (_player->HasAura(WARLOCK_SOUL_LEECH_AURA))
                        {
                            int32 bp = int32(GetHitDamage() / 10);

                            _player->CastCustomSpell(_player, WARLOCK_SOUL_LEECH_HEAL, &bp, NULL, NULL, true);

                            if (Pet* pet = _player->GetPet())
                                _player->CastCustomSpell(pet, WARLOCK_SOUL_LEECH_HEAL, &bp, NULL, NULL, true);
                        }
                    }
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_warl_soul_leech_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soul_leech_SpellScript();
        }
};

// Sacrificial Pact - 108416
class spell_warl_sacrificial_pact : public SpellScriptLoader
{
    public:
        spell_warl_sacrificial_pact() : SpellScriptLoader("spell_warl_sacrificial_pact") { }

        class spell_warl_sacrificial_pact_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_sacrificial_pact_AuraScript);

            void CalculateAmount(constAuraEffectPtr , int32 & amount, bool & )
            {
                if (Unit* caster = GetCaster())
                {
                    if (!GetCaster()->GetGuardianPet())
                    {
                        int32 sacrifiedHealth = GetCaster()->CountPctFromCurHealth(25);
                        GetCaster()->ModifyHealth(-sacrifiedHealth);
                        amount = sacrifiedHealth * 4;
                    }
                    else if (GetCaster()->GetGuardianPet())
                    {
                        int32 sacrifiedHealth = GetCaster()->GetGuardianPet()->CountPctFromCurHealth(25);
                        GetCaster()->GetGuardianPet()->ModifyHealth(-sacrifiedHealth);
                        amount = sacrifiedHealth * 4;
                    }
                }
            }
            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_sacrificial_pact_AuraScript::CalculateAmount, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_sacrificial_pact_AuraScript();
        }
};

// Hand of Gul'Dan - 86040
class spell_warl_hand_of_guldan : public SpellScriptLoader
{
    public:
        spell_warl_hand_of_guldan() : SpellScriptLoader("spell_warl_hand_of_guldan") { }

        class spell_warl_hand_of_guldan_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_hand_of_guldan_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        _player->CastSpell(target, WARLOCK_SHADOWFLAME, true);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_hand_of_guldan_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_hand_of_guldan_SpellScript();
        }
};

// Twilight Ward - 6229 and Twilight Ward (Metamorphosis) - 104048
class spell_warl_twilight_ward_s12 : public SpellScriptLoader
{
    public:
        spell_warl_twilight_ward_s12() : SpellScriptLoader("spell_warl_twilight_ward_s12") { }

        class spell_warl_twilight_ward_s12_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_twilight_ward_s12_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasAura(WARLOCK_ITEM_S12_TIER_4))
                    {
                        if (GetSpellInfo()->Id == 6229)
                        {
                            if (_player->HasAura(GetSpellInfo()->Id))
                                _player->RemoveAura(GetSpellInfo()->Id);

                            _player->CastSpell(_player, WARLOCK_TWILIGHT_WARD_S12, true);
                        }
                        else if (GetSpellInfo()->Id == 104048)
                        {
                            if (_player->HasAura(GetSpellInfo()->Id))
                                _player->RemoveAura(GetSpellInfo()->Id);

                            _player->CastSpell(_player, WARLOCK_TWILIGHT_WARD_METAMORPHOSIS_S12, true);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_twilight_ward_s12_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_twilight_ward_s12_SpellScript();
        }
};

// Hellfire - 5857
class spell_warl_hellfire : public SpellScriptLoader
{
public:
    spell_warl_hellfire() : SpellScriptLoader("spell_warl_hellfire") { }

    class spell_warl_hellfire_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_hellfire_SpellScript);

        void HandleOnHit()
        {
            if (Player* player = GetCaster()->ToPlayer())
            if (GetHitUnit())
                player->EnergizeBySpell(player, GetSpellInfo()->Id, 4, POWER_DEMONIC_FURY);
        }

        void Register()
        {
            OnHit += SpellHitFn(spell_warl_hellfire_SpellScript::HandleOnHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_hellfire_SpellScript();
    }
};


// Hellfire - 1949
class spell_warl_hellfire_aura : public SpellScriptLoader
{
    public:
        spell_warl_hellfire_aura() : SpellScriptLoader("spell_warl_hellfire_aura") { }

        class spell_warl_hellfire_aura_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_hellfire_aura_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (Unit* caster = GetCaster())
                {
                    int32 demonicFury = 10;
                    caster->CastCustomSpell(caster, 104314, NULL, &demonicFury, NULL, true);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_hellfire_aura_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_hellfire_aura_AuraScript();
        }
};

// Demonic Leap - 109151
class spell_warl_demonic_leap : public SpellScriptLoader
{
    public:
        spell_warl_demonic_leap() : SpellScriptLoader("spell_warl_demonic_leap") { }

        class spell_warl_demonic_leap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_demonic_leap_SpellScript);

			SpellCastResult CheckCast()
			{
				Unit* caster = GetCaster();
				if (!caster)
					return SPELL_FAILED_DONT_REPORT;

				if (caster->HasAuraType(SPELL_AURA_MOD_ROOT))
				{
					caster->RemoveAura(WARLOCK_METAMORPHOSIS);
					return SPELL_FAILED_ROOTED;
				}

				return SPELL_CAST_OK;
			}

            void HandleAfterCast()
            {
                if (Unit* caster = GetCaster())
                {
					if (Player* _player = GetCaster()->ToPlayer())
					{
						if (!caster->HasAura(WARLOCK_DARK_APOTHEOSIS))
							caster->CastSpell(caster, WARLOCK_METAMORPHOSIS, true);

						if (_player->HasAura(56247) && _player->IsFalling())
							_player->CastSpell(_player, 124315, true); // Meteor Slam
						else
							caster->CastSpell(caster, WARLOCK_DEMONIC_LEAP_JUMP, true);	
					}
                }
            }

            void Register()
            {
				OnCheckCast += SpellCheckCastFn(spell_warl_demonic_leap_SpellScript::CheckCast);
                AfterCast += SpellCastFn(spell_warl_demonic_leap_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_demonic_leap_SpellScript();
        }
};

// Burning Rush - 111400
class spell_warl_burning_rush : public SpellScriptLoader
{
    public:
        spell_warl_burning_rush() : SpellScriptLoader("spell_warl_burning_rush") { }

        class spell_warl_burning_rush_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_burning_rush_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (GetCaster())
                {
                    // Drain 4% of health every second
                    int32 basepoints = GetCaster()->CountPctFromMaxHealth(4);

                    GetCaster()->DealDamage(GetCaster(), basepoints, NULL, NODAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_burning_rush_AuraScript::OnTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_burning_rush_AuraScript();
        }
};

// Soul Swap : Soulburn - 119678
class spell_warl_soul_swap_soulburn : public SpellScriptLoader
{
    public:
        spell_warl_soul_swap_soulburn() : SpellScriptLoader("spell_warl_soul_swap_soulburn") { }

        class spell_warl_soul_swap_soulburn_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soul_swap_soulburn_SpellScript);

            void HandleOnHit()
            {
                if (Unit* caster = GetCaster())
                {
                    if (Player* player = caster->ToPlayer())
                    {
                        if (Unit* target = GetHitUnit())
                        {
                            player->CastSpell(target, WARLOCK_CORRUPTION, true);
                            player->CastSpell(target, WARLOCK_UNSTABLE_AFFLICTION, true);
                            player->CastSpell(target, WARLOCK_AGONY, true);
                            player->RemoveAura(WARLOCK_SOULBURN_AURA);
                            player->CastSpell(player, WARLOCK_SOUL_SWAP_VISUAL, true);
                        }
                    }
                }		
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_soul_swap_soulburn_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soul_swap_soulburn_SpellScript();
        }
};

// Soul Swap - 86121 or Soul Swap : Exhale - 86213
class spell_warl_soul_swap : public SpellScriptLoader
{
    public:
        spell_warl_soul_swap() : SpellScriptLoader("spell_warl_soul_swap") { }

        class spell_warl_soul_swap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soul_swap_SpellScript);

            SpellCastResult CheckCast()
            {                
				Unit* l_Caster = GetCaster();
				Unit* l_Target = GetExplTargetUnit();
				if (l_Target)
				{
					if (!l_Caster->CanExhaleTarget(l_Target))
						return SpellCastResult::SPELL_FAILED_BAD_TARGETS;

					if (GetSpellInfo()->Id == WarlockSpells::WARLOCK_SOUL_SWAP)
					{
						if (!l_Target->HasAuraTypeWithCaster(SPELL_AURA_PERIODIC_DAMAGE, l_Caster->GetGUID()))
							return SpellCastResult::SPELL_FAILED_BAD_TARGETS;
					}
				}
				else
					return SpellCastResult::SPELL_FAILED_BAD_TARGETS;

				return SpellCastResult::SPELL_CAST_OK;
            }

            void HandleOnHit()
            {   
				Unit* l_Caster = GetCaster();
				if(l_Caster)
				{
					Unit* l_Target = GetHitUnit();
					if(l_Target)
					{
						if (GetSpellInfo()->Id == WarlockSpells::WARLOCK_SOUL_SWAP)
						{
							// Soul Swap override spell
							l_Caster->CastSpell(l_Caster, WarlockSpells::WARLOCK_SOUL_SWAP_AURA, true);
							l_Target->CastSpell(l_Caster, WarlockSpells::WARLOCK_SOUL_SWAP_VISUAL, true);							
							l_Caster->RemoveSoulSwapDOT(l_Target);
						}
						else if (GetSpellInfo()->Id == WarlockSpells::WARLOCK_SOUL_SWAP_EXHALE)
						{
							l_Caster->ApplySoulSwapDOT(l_Caster, l_Target);
							l_Caster->RemoveAurasDueToSpell(WarlockSpells::WARLOCK_SOUL_SWAP_AURA);

							if (l_Caster->HasAura(WarlockSpells::WARLOCK_GLYPH_OF_SOUL_SWAP) && l_Caster->ToPlayer())
								l_Caster->ToPlayer()->AddSpellCooldown(86121, 0, 30 * IN_MILLISECONDS);
						}
					}
				}
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warl_soul_swap_SpellScript::CheckCast);
                OnHit += SpellHitFn(spell_warl_soul_swap_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soul_swap_SpellScript();
        }
};

class spell_warl_soul_swap_aura_removal : public SpellScriptLoader
{
public:
	spell_warl_soul_swap_aura_removal() : SpellScriptLoader("spell_warl_soul_swap_aura_removal") { }

	class spell_warl_soul_swap_aura_removal_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_warl_soul_swap_aura_removal_AuraScript);

		void HandleRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
		{
			Unit* caster = GetCaster();
			if(caster)
				caster->ResetExhaleTarget();
		}

		void Register()
		{
			OnEffectRemove += AuraEffectApplyFn(spell_warl_soul_swap_aura_removal_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_OVERRIDE_ACTIONBAR_SPELLS, AURA_EFFECT_HANDLE_REAL);
		}
	};

	AuraScript* GetAuraScript() const
	{
		return new spell_warl_soul_swap_aura_removal_AuraScript();
	}
};

// Called by Corruption - 172, 146739
// Nightfall - 108558
class spell_warl_nightfall : public SpellScriptLoader
{
    public:
        spell_warl_nightfall() : SpellScriptLoader("spell_warl_nightfall") { }

        class spell_warl_nightfall_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_nightfall_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (!GetCaster())
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasAura(WARLOCK_NIGHTFALL))
                        if (roll_chance_i(10))
                            _player->CastSpell(_player, 17941, true); // Shadow Trance (+ 1 Soul shard and visual effect)
                            //_player->SetPower(POWER_SOUL_SHARDS, _player->GetPower(POWER_SOUL_SHARDS) + 100);                   
                }
				
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_nightfall_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_nightfall_AuraScript();
        }
};

// Called by Immolate - 348, Immolate (Fire and Brimstone) - 108686, Corruption - 146739
// Glyph of Siphon Life - 56218
class spell_warl_siphon_life : public SpellScriptLoader
{
public:
	spell_warl_siphon_life() : SpellScriptLoader("spell_warl_siphon_life") { }

	class spell_warl_siphon_life_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_warl_siphon_life_AuraScript);

		void OnTick(constAuraEffectPtr aurEff)
		{
			Unit* caster = GetCaster();
			if (caster)
			{
				if (caster->isAlive())
				{
					AuraEffectPtr siphonLifeEffect = caster->GetAuraEffect(WARLOCK_GLYPH_OF_SIPHON_LIFE, EFFECT_0);
					if(siphonLifeEffect)
					{
						int32 l_BP = CalculatePct(caster->GetMaxHealth(), siphonLifeEffect->GetAmount() / 1000.f);
						caster->CastCustomSpell(caster, WARLOCK_SIPHON_LIFE_HEAL, &l_BP, NULL, NULL, true);
					}
				}
			}
		}

		void Register()
		{
			OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_siphon_life_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
		}
	};

	AuraScript* GetAuraScript() const
	{
		return new spell_warl_siphon_life_AuraScript();
	}
};

// Drain Soul - 1120
class spell_warl_drain_soul : public SpellScriptLoader
{
    public:
        spell_warl_drain_soul() : SpellScriptLoader("spell_warl_drain_soul") { }

        class spell_warl_drain_soul_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_drain_soul_AuraScript);

            void HandleRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (GetCaster())
                {
                    AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                    if (removeMode == AURA_REMOVE_BY_DEATH)
                        GetCaster()->SetPower(POWER_SOUL_SHARDS, GetCaster()->GetPower(POWER_SOUL_SHARDS) + 300);
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_warl_drain_soul_AuraScript::HandleRemove, EFFECT_4, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_drain_soul_AuraScript();
        }
};

const int32 greenAuras[6] = { 113930, 113903, 113911, 113912, 113913, 113914 };
const int32 purpleAuras[6] = { 113931, 113915, 113916, 113917, 113918, 113919 };

// Demonic Gateway (charges periodic) - 113901
class spell_warl_demonic_gateway_charges : public SpellScriptLoader
{
    public:
        spell_warl_demonic_gateway_charges() : SpellScriptLoader("spell_warl_demonic_gateway_charges") { }

        class spell_warl_demonic_gateway_charges_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_demonic_gateway_charges_AuraScript);

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (Unit* caster = GetCaster())
                {
                    int32 charges = aurEff->GetAmount();
                    if (charges > 4)
                        return;
                    else
                        aurEff->GetBase()->GetEffect(0)->SetAmount(++charges);

                    switch (caster->GetEntry())
                    {
                        case 59262: // Green
                        {
                            for (int i = 0; i < 6; ++i)
                            {
                                if (i <= charges)
                                    caster->CastSpell(caster, greenAuras[i], true);
                                else
                                    caster->RemoveAura(greenAuras[i]);
                            }

                            break;
                        }
                        case 59271: // Purple
                        {
                            for (int i = 0; i < 6; ++i)
                            {
                                if (i <= charges)
                                    caster->CastSpell(caster, purpleAuras[i], true);
                                else
                                    caster->RemoveAura(purpleAuras[i]);
                            }

                            break;
                        }
                    }
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_demonic_gateway_charges_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_demonic_gateway_charges_AuraScript();
        }
};

// Demonic Gateway - 111771
class spell_warl_demonic_gateway : public SpellScriptLoader
{
    public:
        spell_warl_demonic_gateway() : SpellScriptLoader("spell_warl_demonic_gateway") { }

        class spell_warl_demonic_gateway_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_demonic_gateway_SpellScript);

            std::list<Unit*> targetList;

            SpellCastResult CheckElevation()
            {
                Unit* caster = GetCaster();
                if (!caster || !caster->ToPlayer())
                    return SPELL_FAILED_DONT_REPORT;

                Player* player = caster->ToPlayer();

                WorldLocation* dest = const_cast<WorldLocation*>(GetExplTargetDest());
                if (!dest)
                    return SPELL_FAILED_DONT_REPORT;

                if (dest->GetPositionZ() > player->GetPositionZ() + 5.0f)
                    return SPELL_FAILED_NOPATH;
                else if (player->HasAuraType(SPELL_AURA_MOD_ROOT))
                    return SPELL_FAILED_ROOTED;
                else if (player->GetMap()->IsBattlegroundOrArena())
                {
                    if (Battleground* bg = player->GetBattleground())
                    {
                        if (bg->GetStatus() != STATUS_IN_PROGRESS)
                            return SPELL_FAILED_NOT_READY;
                    }
                }

                return SPELL_CAST_OK;
            }

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    _player->CastSpell(_player, WARLOCK_SPAWN_PURPLE_DEMONIC_GATEWAY, true);
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warl_demonic_gateway_SpellScript::CheckElevation);
                AfterCast += SpellCastFn(spell_warl_demonic_gateway_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_demonic_gateway_SpellScript();
        }
};

// Chaos Bolt - 116858
class spell_warl_chaos_bolt : public SpellScriptLoader
{
    public:
        spell_warl_chaos_bolt() : SpellScriptLoader("spell_warl_chaos_bolt") { }

        class spell_warl_chaos_bolt_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_chaos_bolt_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (target->GetTypeId() == TYPEID_PLAYER)
                            SetHitDamage(int32(CalculatePct(GetHitDamage(), 75)));
                    }
                }
            }

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (_player->HasAura(WARLOCK_PYROCLASM))
                        if(AuraPtr backdraft = _player->GetAura(WARLOCK_BACKDRAFT))
                            backdraft->ModCharges(-3);
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_chaos_bolt_SpellScript::HandleOnHit);
                AfterCast += SpellCastFn(spell_warl_chaos_bolt_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_chaos_bolt_SpellScript();
        }
};

// Ember Tap - 114635
class spell_warl_ember_tap : public SpellScriptLoader
{
    public:
        spell_warl_ember_tap() : SpellScriptLoader("spell_warl_ember_tap") { }

        class spell_warl_ember_tap_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_ember_tap_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        int32 healAmount;
                        float pct;
                        float Mastery;

                        Mastery = 3.0f * _player->GetFloatValue(PLAYER_MASTERY) / 100.0f;

                        pct = 0.15f * (1 + Mastery);

                        healAmount = int32(_player->GetMaxHealth() * pct);
                        healAmount = _player->SpellHealingBonusDone(_player, GetSpellInfo(), healAmount, HEAL);
                        healAmount = _player->SpellHealingBonusTaken(_player, GetSpellInfo(), healAmount, HEAL);

                        float PvPPower = 1 + (_player->GetFloatValue(PLAYER_FIELD_PVP_POWER_HEALING) / 100);
                        healAmount *= PvPPower;

                        if (_player->HasAura(63304))
                            healAmount = 0;

                        SetHitHeal(healAmount);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_ember_tap_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_ember_tap_SpellScript();
        }
};

// Called By : Incinerate (Fire and Brimstone) - 114654, Conflagrate (Fire and Brimstone) - 108685
// Curse of the Elements (Fire and Brimstone) - 104225, Curse of Enfeeblement (Fire and Brimstone) - 109468
// Immolate (Fire and Brimstone) - 108686
// Fire and Brimstone - 108683
class spell_warl_fire_and_brimstone : public SpellScriptLoader
{
    public:
        spell_warl_fire_and_brimstone() : SpellScriptLoader("spell_warl_fire_and_brimstone") { }

        class spell_warl_fire_and_brimstone_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_fire_and_brimstone_SpellScript);

            SpellCastResult CheckCast()
            {
                if (!GetCaster())
                    return SPELL_FAILED_DONT_REPORT;

                if (GetSpellInfo()->Id == 114654 || GetSpellInfo()->Id == 108685 || GetSpellInfo()->Id == 108686)
                    if (GetCaster()->GetPower(POWER_BURNING_EMBERS)<10)
                        return SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW;

                return SPELL_CAST_OK;
            }

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                    if (Unit* target = GetHitUnit())
                        if (_player->HasAura(WARLOCK_FIRE_AND_BRIMSTONE))
                        {
                            _player->SetPower(POWER_BURNING_EMBERS, _player->GetPower(POWER_BURNING_EMBERS) - 10); // Take 1 burning ember
                            _player->RemoveAura(WARLOCK_FIRE_AND_BRIMSTONE);
                        }
            }

            void Register()
            {
                OnCheckCast += SpellCheckCastFn(spell_warl_fire_and_brimstone_SpellScript::CheckCast);
                OnHit += SpellHitFn(spell_warl_fire_and_brimstone_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_fire_and_brimstone_SpellScript();
        }
};

// Conflagrate - 17962 and Conflagrate (Fire and Brimstone) - 108685
class spell_warl_conflagrate_aura : public SpellScriptLoader
{
    public:
        spell_warl_conflagrate_aura() : SpellScriptLoader("spell_warl_conflagrate_aura") { }

        class spell_warl_conflagrate_aura_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_conflagrate_aura_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (!target->HasAura(WARLOCK_IMMOLATE) && !_player->HasAura(WARLOCK_GLYPH_OF_CONFLAGRATE))
                            if (AuraPtr conflagrate = target->GetAura(WARLOCK_CONFLAGRATE))
                                target->RemoveAura(WARLOCK_CONFLAGRATE);
                        if (!target->HasAura(WARLOCK_IMMOLATE_FIRE_AND_BRIMSTONE))
                            if (AuraPtr conflagrate = target->GetAura(WARLOCK_CONFLAGRATE_FIRE_AND_BRIMSTONE))
                                target->RemoveAura(WARLOCK_CONFLAGRATE_FIRE_AND_BRIMSTONE);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_conflagrate_aura_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_conflagrate_aura_SpellScript();
        }
};

// Shadowburn - 29341
class spell_warl_shadowburn : public SpellScriptLoader
{
    public:
        spell_warl_shadowburn() : SpellScriptLoader("spell_warl_shadowburn") { }

        class spell_warl_shadowburn_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_shadowburn_AuraScript);

            void HandleRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes mode)
            {
                if (GetCaster())
                {
                    AuraRemoveMode removeMode = GetTargetApplication()->GetRemoveMode();
                    if (removeMode == AURA_REMOVE_BY_DEATH)
                        GetCaster()->SetPower(POWER_BURNING_EMBERS, GetCaster()->GetPower(POWER_BURNING_EMBERS) + 20); // Give 2 Burning Embers
                    else if (removeMode == AURA_REMOVE_BY_EXPIRE)
                        GetCaster()->CastSpell(GetCaster(), WARLOCK_SHADOWBURN_ENERGIZE, true);
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_warl_shadowburn_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_shadowburn_AuraScript();
        }
};

// Called By : Incinerate - 29722 and Incinerate (Fire and Brimstone) - 114654
// Conflagrate - 17962 and Conflagrate (Fire and Brimstone) - 108685
// Burning Embers generate
class spell_warl_burning_embers : public SpellScriptLoader
{
    public:
        spell_warl_burning_embers() : SpellScriptLoader("spell_warl_burning_embers") { }

        class spell_warl_burning_embers_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_burning_embers_SpellScript);

            void HandleOnHit()
            {
                if (GetSpellInfo()->Id == 114654 || GetSpellInfo()->Id == 108685)
                    return;

                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (GetSpell()->IsCritForTarget(target))
                            _player->SetPower(POWER_BURNING_EMBERS, _player->GetPower(POWER_BURNING_EMBERS) + 2);
                        else
                            _player->SetPower(POWER_BURNING_EMBERS, _player->GetPower(POWER_BURNING_EMBERS) + 1);

                        // hotfix 5.4 - this spells can generate additional burning ember with 15% chance
                        if (roll_chance_i(15))
                            _player->SetPower(POWER_BURNING_EMBERS, _player->GetPower(POWER_BURNING_EMBERS) + 1);

                        if (GetSpellInfo()->Id == 29722)
                            if (_player->HasAura(138134))
                                if (roll_chance_i(8))
                                    _player->SetPower(POWER_BURNING_EMBERS, _player->GetPower(POWER_BURNING_EMBERS) + 1);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_burning_embers_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_burning_embers_SpellScript();
        }
};

// Fel Flame - 77799
class spell_warl_fel_flame : public SpellScriptLoader
{
    public:
        spell_warl_fel_flame() : SpellScriptLoader("spell_warl_fel_flame") { }

        class spell_warl_fel_flame_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_fel_flame_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_WARLOCK_DESTRUCTION)
                        {
                            if (GetSpell()->IsCritForTarget(target))
                                _player->SetPower(POWER_BURNING_EMBERS, _player->GetPower(POWER_BURNING_EMBERS) + 2);
                            else
                                _player->SetPower(POWER_BURNING_EMBERS, _player->GetPower(POWER_BURNING_EMBERS) + 1);
                        }

                        int32 hitDamage = GetHitDamage();
                        if (AuraPtr grimoireOfSacrifice = _player->GetAura(WARLOCK_GRIMOIRE_OF_SACRIFICE))
                        {
                            switch (_player->GetSpecializationId(_player->GetActiveSpec()))
                            {
                                case SPEC_WARLOCK_AFFLICTION:
                                    hitDamage = int32((hitDamage / 1.6f) * 1.2f);
                                    break;
                                case SPEC_WARLOCK_DEMONOLOGY:
                                    hitDamage = int32((hitDamage / 1.65f) * 1.25f);
                                    break;
                                case SPEC_WARLOCK_DESTRUCTION:
                                    hitDamage = int32((hitDamage / 1.6f) * 1.15f);
                                    break;
                                default:
                                    break;
                            }
                        }
                        SetHitDamage(hitDamage);
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_fel_flame_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_fel_flame_SpellScript();
        }
};

// Drain Life - 689 , Drain Life (Demonic) - 103990
class spell_warl_drain_life : public SpellScriptLoader
{
    public:
        spell_warl_drain_life() : SpellScriptLoader("spell_warl_drain_life") { }

        class spell_warl_drain_life_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_drain_life_AuraScript);

            void CalculateAmount(constAuraEffectPtr /*auraEffect*/, int32& amount, bool& /*canBeRecalculated*/)
            {
                if (!GetCaster())
                    return;
                if (Unit* caster = GetCaster())
                {
                    if (caster->HasAura(WARLOCK_HARVEST_LIFE))
                        amount *= 1.5;
                }
            }

            void OnTick(constAuraEffectPtr aurEff)
            {
                if (Unit* caster = GetCaster())
                {
                    Player* _player = GetCaster()->ToPlayer();
                    if (!_player)
                        return;

                    // Restoring 2% of the caster's total health every 1s
                    int32 basepoints = _player->GetMaxHealth() / 50;

                    if (_player->HasAura(WARLOCK_HARVEST_LIFE))
                        basepoints *= 2.5;

                    // In Demonology spec : Generates 10 Demonic Fury per second
                    if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_WARLOCK_DEMONOLOGY)
                    {
                       int32 demonicFury = 10;
                       _player->CastCustomSpell(_player, 104314, NULL, &demonicFury, NULL, true);
                    }

                    // Glyph of Drain Life
                    if (_player->HasAura(63302))
                        basepoints *= 1.3f;

                    // PvP Power affects on drain life heal
                    float PvPPower = 1 + (_player->GetFloatValue(PLAYER_FIELD_PVP_POWER_HEALING) / 100);
                    basepoints *= PvPPower;

                    _player->CastCustomSpell(_player, WARLOCK_DRAIN_LIFE_HEAL, &basepoints, NULL, NULL, true);
                }
            }

            void Register()
            {
                DoEffectCalcAmount += AuraEffectCalcAmountFn(spell_warl_drain_life_AuraScript::CalculateAmount, EFFECT_1, SPELL_AURA_PERIODIC_DAMAGE);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_drain_life_AuraScript::OnTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_drain_life_AuraScript();
        }
};

// Soul Harvest - 101976
class spell_warl_soul_harverst : public SpellScriptLoader
{
    public:
        spell_warl_soul_harverst() : SpellScriptLoader("spell_warl_soul_harverst") { }

        class spell_warl_soul_harverst_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_soul_harverst_AuraScript);

            uint32 update;

            bool Validate(SpellInfo const* /*spell*/)
            {
                update = 0;

                if (!sSpellMgr->GetSpellInfo(101976))
                    return false;
                return true;
            }

            void OnUpdate(uint32 diff)
            {
                update += diff;

                if (update >= 1000)
                {
                    if (Player* _player = GetCaster()->ToPlayer())
                    {
                        if (!_player->isInCombat() && !_player->InArena() && _player->isAlive())
                        {
                            _player->SetHealth(_player->GetHealth() + int32(_player->GetMaxHealth() / 50));

                            if (Pet* pet = _player->GetPet())
                                pet->SetHealth(pet->GetHealth() + int32(pet->GetMaxHealth() / 50));
                        }
                    }

                    update = 0;
                }
            }

            void Register()
            {
                OnAuraUpdate += AuraUpdateFn(spell_warl_soul_harverst_AuraScript::OnUpdate);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_soul_harverst_AuraScript();
        }
};

// Life Tap - 1454
class spell_warl_life_tap : public SpellScriptLoader
{
public:
    spell_warl_life_tap() : SpellScriptLoader("spell_warl_life_tap") { }

    class spell_warl_life_tap_SpellScript : public SpellScript
    {
        int32 m_amount;

    public:
        spell_warl_life_tap_SpellScript()
            : m_amount(0) {}

        PrepareSpellScript(spell_warl_life_tap_SpellScript);

        SpellCastResult CheckLife()
        {
            if (GetCaster()->GetHealthPct() > 15.0f)
                return SPELL_CAST_OK;

            return SPELL_FAILED_FIZZLE;
        }

        void HandleBeforeHit()
        {
            if (Unit* caster = GetCaster())
            {
                if (AuraEffectPtr lifeTap = caster->GetAuraEffect(WARLOCK_LIFE_TAP, EFFECT_2))
                    m_amount = lifeTap->GetAmount();
                else
                    m_amount = 0;
            }
        }

        void HandleAfterHit()
        {
            if (Unit* caster = GetCaster())
            {
                int32 amount = caster->CountPctFromMaxHealth(15);

                if (caster->HasAura(WARLOCK_GLYPH_OF_LIFE_TAP))
                {
                    int32 amount = m_amount + caster->CountPctFromMaxHealth(15);
                    if (AuraEffectPtr lifeTap = caster->GetAuraEffect(WARLOCK_LIFE_TAP, EFFECT_2))
                        lifeTap->ChangeAmount(amount);
                }
                else
                {
                    caster->SetHealth(caster->GetHealth() - amount);
                }
                caster->EnergizeBySpell(caster, WARLOCK_LIFE_TAP, amount, POWER_MANA);
            }
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_warl_life_tap_SpellScript::CheckLife);
            BeforeHit += SpellHitFn(spell_warl_life_tap_SpellScript::HandleBeforeHit);
            AfterHit += SpellHitFn(spell_warl_life_tap_SpellScript::HandleAfterHit);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_life_tap_SpellScript();
    }
};

// Soulburn : Harvest Life - 115707
class spell_warl_soulburn_harvest_life : public SpellScriptLoader
{
public:
    spell_warl_soulburn_harvest_life() : SpellScriptLoader("spell_warl_soulburn_harvest_life") { }

    class spell_warl_soulburn_harvest_life_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_soulburn_harvest_life_AuraScript);

        void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (!GetCaster())
                return;

            if (Player* player = GetCaster()->ToPlayer())
                if (player->HasAura(WARLOCK_SOULBURN_AURA))
                    player->RemoveAurasDueToSpell(WARLOCK_SOULBURN_AURA);
        }

        void OnTick(constAuraEffectPtr aurEff)
        {
            if (!GetCaster())
                return;

            if (Player* _player = GetCaster()->ToPlayer())
            {
                // Restoring 3-4.5% of the caster's total health every 1s - With 33% bonus
                int32 basepoints = int32(frand(0.03f, 0.045f) * _player->GetMaxHealth());

                AddPct(basepoints, 33);

                if (!_player->HasSpellCooldown(WARLOCK_HARVEST_LIFE_HEAL))
                {
                    _player->CastCustomSpell(_player, WARLOCK_HARVEST_LIFE_HEAL, &basepoints, NULL, NULL, true);
                    // prevent the heal to proc off for each targets
                    _player->AddSpellCooldown(WARLOCK_HARVEST_LIFE_HEAL, 0, time(NULL) + 1);
                }

                _player->EnergizeBySpell(_player, aurEff->GetSpellInfo()->Id, 4, POWER_DEMONIC_FURY);
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_warl_soulburn_harvest_life_AuraScript::OnApply, EFFECT_2, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_soulburn_harvest_life_AuraScript::OnTick, EFFECT_2, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_soulburn_harvest_life_AuraScript();
    }
};

// Fear - 5782
class spell_warl_fear : public SpellScriptLoader
{
    public:
        spell_warl_fear() : SpellScriptLoader("spell_warl_fear") { }

        class spell_warl_fear_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_fear_SpellScript);

            void HandleAfterHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (_player->HasAura(WARLOCK_GLYPH_OF_FEAR))
                        {
                            _player->CastSpell(target, WARLOCK_GLYPH_OF_FEAR_EFFECT, true);
                        }
                        else
                            _player->CastSpell(target, WARLOCK_FEAR_EFFECT, true);
                    }
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_warl_fear_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_fear_SpellScript();
        }
};

// Bloody Fear - 111397
class spell_warl_bloody_fear : public SpellScriptLoader
{
public:
    spell_warl_bloody_fear() : SpellScriptLoader("spell_warl_bloody_fear") { }

    class spell_warl_bloody_fear_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_bloody_fear_AuraScript);

        void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            if (Player* Caster = GetCaster()->ToPlayer())
            {
                Caster->DealDamage(Caster, Caster->CountPctFromMaxHealth(5), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
            }
        }

        void OnProc(constAuraEffectPtr p_AurEff, ProcEventInfo& p_EventInfo)
        {
            PreventDefaultAction();

            if (Unit* Caster = GetUnitOwner())
            {
                if (Unit* Target = p_EventInfo.GetDamageInfo()->GetAttacker())
                {
                    // Blood horror doesn't proc on pets/guardians and such
                    if (Target->IsPetGuardianStuff())
                        return;

                    Caster->CastSpell(Target, WARLOCK_BLOODY_FEAR_EFFECT, true);
                    p_AurEff->GetBase()->DropCharge();
                }
            }
        }

        void Register() override
        {
            OnEffectApply += AuraEffectApplyFn(spell_warl_bloody_fear_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectProc += AuraEffectProcFn(spell_warl_bloody_fear_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const override
    {
        return new spell_warl_bloody_fear_AuraScript();
    }
};

// Updated 4.3.4
class spell_warl_banish : public SpellScriptLoader
{
    public:
        spell_warl_banish() : SpellScriptLoader("spell_warl_banish") { }

        class spell_warl_banish_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_banish_SpellScript);

            bool Load()
            {
                _removed = false;
                return true;
            }

            void HandleBanish()
            {
                // Casting Banish on a banished target will cancel the effect
                // Check if the target already has Banish, if so, do nothing.

                if (Unit* target = GetHitUnit())
                {
                    if (target->GetAuraEffect(SPELL_AURA_SCHOOL_IMMUNITY, SPELLFAMILY_WARLOCK, 0, 0x08000000, 0))
                    {
                        // No need to remove old aura since its removed due to not stack by current Banish aura
                        PreventHitDefaultEffect(EFFECT_0);
                        PreventHitDefaultEffect(EFFECT_1);
                        PreventHitDefaultEffect(EFFECT_2);
                        _removed = true;
                    }
                }
            }

            void RemoveAura()
            {
                if (_removed)
                    PreventHitAura();
            }

            void Register()
            {
                BeforeHit += SpellHitFn(spell_warl_banish_SpellScript::HandleBanish);
                AfterHit += SpellHitFn(spell_warl_banish_SpellScript::RemoveAura);
            }

            bool _removed;
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_banish_SpellScript();
        }
};

// Create Healthstone - 6201
class spell_warl_create_healthstone : public SpellScriptLoader
{
    public:
        spell_warl_create_healthstone() : SpellScriptLoader("spell_warl_create_healthstone") { }

        class spell_warl_create_healthstone_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_create_healthstone_SpellScript);

            void HandleAfterCast()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->HasItemCount(5512, 1))
                        _player->DestroyItemCount(5512, 1, true);

                    _player->CastSpell(_player, WARLOCK_CREATE_HEALTHSTONE, true);
                }
            }

            void Register()
            {
                AfterCast += SpellCastFn(spell_warl_create_healthstone_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_create_healthstone_SpellScript();
        }
};

class spell_warl_seed_of_corruption : public SpellScriptLoader
{
    public:
        spell_warl_seed_of_corruption() : SpellScriptLoader("spell_warl_seed_of_corruption") { }

        class spell_warl_seed_of_corruption_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_seed_of_corruption_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (GetExplTargetUnit())
                    targets.remove(GetExplTargetUnit());
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_warl_seed_of_corruption_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_seed_of_corruption_SpellScript();
        }
};

enum Soulshatter
{
    SPELL_SOULSHATTER   = 32835,
};

class spell_warl_soulshatter : public SpellScriptLoader
{
    public:
        spell_warl_soulshatter() : SpellScriptLoader("spell_warl_soulshatter") { }

        class spell_warl_soulshatter_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_soulshatter_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_SOULSHATTER))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                {
                    if (target->CanHaveThreatList() && target->getThreatManager().getThreat(caster) > 0.0f)
                        caster->CastSpell(target, SPELL_SOULSHATTER, true);
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_warl_soulshatter_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_soulshatter_SpellScript();
        }
};

// Demonic Circle : Summon - 48018
class spell_warl_demonic_circle_summon : public SpellScriptLoader
{
    public:
        spell_warl_demonic_circle_summon() : SpellScriptLoader("spell_warl_demonic_circle_summon") { }

        class spell_warl_demonic_circle_summon_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_demonic_circle_summon_AuraScript);

            void HandleRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes mode)
            {
                if (GetTarget())
                {
                    // If effect is removed by expire remove the summoned demonic circle too.
                    if (!(mode & AURA_EFFECT_HANDLE_REAPPLY))
                        GetTarget()->RemoveGameObject(GetId(), true);

                    if (GetTarget()->GetAuraApplication(aurEff->GetSpellInfo()->Id, GetTarget()->GetGUID()))
                        GetTarget()->GetAuraApplication(aurEff->GetSpellInfo()->Id, GetTarget()->GetGUID())->SendFakeAuraUpdate(WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST, true);
                }
            }

            void HandleDummyTick(constAuraEffectPtr aurEff)
            {
                if (GetTarget())
                {
                    if (GameObject* circle = GetTarget()->GetGameObject(GetId()))
                    {
                        // Here we check if player is in demonic circle teleport range, if so add
                        // WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST; allowing him to cast the WARLOCK_DEMONIC_CIRCLE_TELEPORT.
                        // If not in range remove the WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST.

                        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(WARLOCK_DEMONIC_CIRCLE_TELEPORT);

                        if (GetTarget()->IsWithinDist(circle, spellInfo->GetMaxRange(true)))
                            GetTarget()->GetAuraApplication(aurEff->GetSpellInfo()->Id, GetTarget()->GetGUID())->SendFakeAuraUpdate(WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST, false);
                        else
                            GetTarget()->GetAuraApplication(aurEff->GetSpellInfo()->Id, GetTarget()->GetGUID())->SendFakeAuraUpdate(WARLOCK_DEMONIC_CIRCLE_ALLOW_CAST, true);
                    }
                }
            }

            void Register()
            {
                OnEffectRemove += AuraEffectApplyFn(spell_warl_demonic_circle_summon_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_warl_demonic_circle_summon_AuraScript::HandleDummyTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_demonic_circle_summon_AuraScript();
        }
};

// Demonic Circle : Teleport - 48020 and Soulburn : Demonic Circle : Teleport - 114794
class spell_warl_demonic_circle_teleport : public SpellScriptLoader
{
    public:
        spell_warl_demonic_circle_teleport() : SpellScriptLoader("spell_warl_demonic_circle_teleport") { }

        class spell_warl_demonic_circle_teleport_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_demonic_circle_teleport_AuraScript);

            void HandleTeleport(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Player* player = GetTarget()->ToPlayer())
                {
                    for (uint8 i = 0; i <= 1; ++i)
                    if (GameObject* circle = player->GetGameObject(i == 0 ? WARLOCK_DEMONIC_CIRCLE_SUMMON : 104135))
                    {
                        player->CastSpell(player, 104163, true); // Demonic Circle: Teleport Visual
                        
                        player->NearTeleportTo(circle->GetPositionX(), circle->GetPositionY(), circle->GetPositionZ(), circle->GetOrientation());
                        player->RemoveSnareAuras();
                        player->Relocate(circle->GetPositionX(), circle->GetPositionY(), circle->GetPositionZ(), circle->GetOrientation());

                        if (aurEff->GetSpellInfo()->Id == WARLOCK_SOULBURN_DEMONIC_CIRCLE_TELE)
                            if (player->HasAura(WARLOCK_SOULBURN_AURA))
                                player->RemoveAurasDueToSpell(WARLOCK_SOULBURN_AURA);

                        WorldPacket data(SMSG_MOVE_UPDATE);
                        player->m_movementInfo.pos.m_positionX = player->GetPositionX();
                        player->m_movementInfo.pos.m_positionY = player->GetPositionY();
                        player->m_movementInfo.pos.m_positionZ = player->GetPositionZ();
                        player->m_movementInfo.pos.m_orientation = player->GetOrientation();
                        player->WriteMovementInfo(data);
                        player->SendMessageToSet(&data, player);
                    }
                }
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_warl_demonic_circle_teleport_AuraScript::HandleTeleport, EFFECT_0, SPELL_AURA_MECHANIC_IMMUNITY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_demonic_circle_teleport_AuraScript();
        }
};

// Unstable Affliction - 30108
class spell_warl_unstable_affliction : public SpellScriptLoader
{
    public:
        spell_warl_unstable_affliction() : SpellScriptLoader("spell_warl_unstable_affliction") { }

        class spell_warl_unstable_affliction_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_unstable_affliction_AuraScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(WARLOCK_UNSTABLE_AFFLICTION_DISPEL))
                    return false;
                return true;
            }

            void HandleDispel(DispelInfo* dispelInfo)
            {
                if (Unit* caster = GetCaster())
                {
                    if (constAuraEffectPtr aurEff = GetEffect(EFFECT_0))
                    {
                        int32 damage = aurEff->GetAmount() * 8;

                        // Backfire damage and silence.
                        caster->CastCustomSpell(dispelInfo->GetDispeller(), WARLOCK_UNSTABLE_AFFLICTION_DISPEL, &damage, NULL, NULL, true, NULL, aurEff);
                        if (!dispelInfo->GetDispeller()->HasAura(WARLOCK_UNSTABLE_AFFLICTION_DISPEL))
                            caster->AddAura(WARLOCK_UNSTABLE_AFFLICTION_DISPEL, dispelInfo->GetDispeller());
                    }
                }
            }

            void Register()
            {
                AfterDispel += AuraDispelFn(spell_warl_unstable_affliction_AuraScript::HandleDispel);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_unstable_affliction_AuraScript();
        }
};

// Called by Corruption - 146739, Agony - 980, Unstable Affliction - 30108, Immolate - 348, Doom - 603
// Pandemic - 131973
class spell_warl_pandemic : public SpellScriptLoader
{
    public:
        spell_warl_pandemic() : SpellScriptLoader("spell_warl_pandemic") { }

        class spell_warl_pandemic_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_pandemic_SpellScript);

            int32 duration;

            void HandlePandemic()
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        if (AuraPtr aura = target->GetAura(GetSpellInfo()->Id, GetCaster()->GetGUID()))
                            duration = aura->GetDuration();
                        else
                            duration = 0;
                    }
                }
            }

            void HandleOnHit()
            {
                if (Player* player = GetCaster()->ToPlayer())
                {
                    if (player->getLevel() < 90)
                        return;

                    if (Unit* target = GetHitUnit())
                    {
                        if (AuraPtr aura = target->GetAura(GetSpellInfo()->Id, GetCaster()->GetGUID()))
                        {
                            int32 newDuration;
                            int32 maxDuration = aura->GetMaxDuration();
                            int32 newMaxDuration = aura->GetMaxDuration() * 1.5f;
                            if (duration == 0)
                                newDuration = maxDuration;
                            else
                                newDuration = duration+maxDuration < newMaxDuration ? duration+maxDuration : newMaxDuration;
                            
                            aura->SetMaxDuration(newDuration);
                            aura->SetDuration(newDuration);
                        }
                    }
                }
            }

            void Register()
            {
                BeforeHit += SpellHitFn(spell_warl_pandemic_SpellScript::HandlePandemic);
                OnHit += SpellHitFn(spell_warl_pandemic_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_pandemic_SpellScript();
        }
};

// Called by Legion Strike - 30213, Shadow Bite - 54049, Lash of Pain - 7814, Torment - 3716, Firebolt - 3110
// Demonic Fury - 104315
// Demonic regenerate - 104314
class spell_warl_demonic_fury : public SpellScriptLoader
{
    public:
        spell_warl_demonic_fury() : SpellScriptLoader("spell_warl_demonic_fury") { }

        class spell_warl_demonic_fury_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_demonic_fury_SpellScript);

            void HandleOnHit()
            {
                if (Pet* pet = GetCaster()->ToPet())
				{
                    if (Player* _player = pet->GetOwner())
                    {
                        int32 demonicFury;
                        if (_player->GetSpecializationId(_player->GetActiveSpec()) == SPEC_WARLOCK_DEMONOLOGY)
                        {
                            switch (GetSpellInfo()->Id)
                            {
                                case 30213: // Legion Strike
                                case 54049: // Shadow Bite
                                case 7814:  // Lash of Pain
                                case 115625: // Mortal strike
                                case 115778: // Tongue lash
                                case 115748: // Bladedance
                                    demonicFury = 12;
                                    break;
                                case 3716: // Torment
                                    demonicFury = 10;
                                    break;
                                case 3110: // Firebolt
                                case 115746: // Felbolt
                                    demonicFury = 8;
                                    break;

                                default: break;
                            }

                            if (demonicFury)
                                _player->CastCustomSpell(_player, 104314, NULL, &demonicFury, NULL, true);
                        }
					}
				}
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_demonic_fury_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_demonic_fury_SpellScript();
        }
};

// Ritual of Summoning - 698
class spell_warl_ritual_of_summoning : public SpellScriptLoader
{
public:
    spell_warl_ritual_of_summoning() : SpellScriptLoader("spell_warl_ritual_of_summoning") { }

    class spell_warl_ritual_of_summoning_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_warl_ritual_of_summoning_SpellScript);

        SpellCastResult CheckBattleground()
        {
            if (GetCaster())
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (_player->GetMap()->IsBattleground())
                    {
                        return SPELL_FAILED_NOT_IN_BATTLEGROUND;
                    }
                }
            }
            return SPELL_CAST_OK;
        }

        void Register()
        {
            OnCheckCast += SpellCheckCastFn(spell_warl_ritual_of_summoning_SpellScript::CheckBattleground);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_warl_ritual_of_summoning_SpellScript();
    }
};

// Touch of Chaos - 103964
class spell_warl_touch_of_chaos : public SpellScriptLoader
{
    public:
        spell_warl_touch_of_chaos() : SpellScriptLoader("spell_warl_touch_of_chaos") { }

        class spell_warl_touch_of_chaos_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_touch_of_chaos_SpellScript);

            void HandleOnHit()
            {
                if (Player* _player = GetCaster()->ToPlayer())
                {
                    if (Unit* target = GetHitUnit())
                    {
                        target->SendPlaySpellVisual(21819, _player, 80.f);
                        
                        if (_player->HasAura(145091))
                        {
                            if (roll_chance_i(8))
                                _player->CastSpell(target, 105174, true);
                        }

                        if (AuraPtr aura = target->GetAura(146739, GetCaster()->GetGUID()))
                        {
                            int32 maxDuration = aura->GetMaxDuration();
                            aura->SetDuration(maxDuration);
                        }
                    }
                }
            }

            void Register()
            {
                OnHit += SpellHitFn(spell_warl_touch_of_chaos_SpellScript::HandleOnHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_touch_of_chaos_SpellScript();
        }
};

// Glyph of Soul Consumption - 58070
class spell_warl_glyph_of_soul_consumption : public SpellScriptLoader
{
    public:
        spell_warl_glyph_of_soul_consumption() : SpellScriptLoader("spell_warl_glyph_of_soul_consumption") { }

        class spell_warl_glyph_of_soul_consumption_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_warl_glyph_of_soul_consumption_AuraScript);

            void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
            {
                PreventDefaultAction();

                if (!GetCaster() || !eventInfo.GetDamageInfo()->getVictim())
                    return;

                if (GetCaster()->ToPlayer()->InArena())
                    return;

                if (GetCaster()->ToPlayer()->HasSpellCooldown(58068))
                    return;

                if (eventInfo.GetDamageInfo()->GetSpellInfo() && (eventInfo.GetDamageInfo()->GetSpellInfo()->Id != 116858 &&
                        eventInfo.GetDamageInfo()->GetSpellInfo()->Id != 1120 &&
                        !GetCaster()->HasAura(103958)))
                    return;

                int32 final = eventInfo.GetDamageInfo()->getVictim()->GetHealth() - eventInfo.GetDamageInfo()->GetDamage();

                if (final >= 0)
                    return;

                GetCaster()->CastSpell(GetCaster(), 58068, true);

                GetCaster()->ToPlayer()->AddSpellCooldown(58068, 0, time(NULL) + 10);
            }

            void Register()
            {
                OnEffectProc += AuraEffectProcFn(spell_warl_glyph_of_soul_consumption_AuraScript::OnProc, EFFECT_0, SPELL_AURA_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_warl_glyph_of_soul_consumption_AuraScript();
        }
};

// Called by Incinerate - 29722
// Backlash - 108563
class spell_warl_incinerate : public SpellScriptLoader
{
    public:
        spell_warl_incinerate() : SpellScriptLoader("spell_warl_incinerate") { }

        class spell_warl_incinerate_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_incinerate_SpellScript);

			bool hasAuraPrepareCast;
			bool hasAuraOnCast;

			void HandleAfterCast()
			{
				if (Player* _player = GetCaster()->ToPlayer())
				{
					if (hasAuraPrepareCast && !hasAuraOnCast)
						_player->RemoveAura(WARLOCK_BACKLASH_AURA);
				}
			}

			void HandleOnCast(){
				if (Player* _player = GetCaster()->ToPlayer())
				{
					if (_player->HasAura(WARLOCK_BACKLASH_AURA) && !hasAuraPrepareCast)
						hasAuraOnCast = true;

				}
			}

			void HandleOnPrepareCast() {
				if (Player* _player = GetCaster()->ToPlayer())
				{

					if (_player->HasAura(WARLOCK_BACKLASH_AURA)) {
						hasAuraPrepareCast = true;
						hasAuraOnCast = false;
					}
					else
						hasAuraPrepareCast = false;

				}
			}

			void Register()
			{
				OnPrepareCast += SpellCastFn(spell_warl_incinerate_SpellScript::HandleOnPrepareCast);
				AfterCast += SpellCastFn(spell_warl_incinerate_SpellScript::HandleAfterCast);
				OnCast += SpellCastFn(spell_warl_incinerate_SpellScript::HandleOnCast);
			}
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_incinerate_SpellScript();
        }
};

// Called by Legion Strike - 30213, Mortal Cleave - 115625
class spell_warl_reduce_heal : public SpellScriptLoader
{
    public:
        spell_warl_reduce_heal() : SpellScriptLoader("spell_warl_reduce_heal") { }

        class spell_warl_reduce_heal_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_warl_reduce_heal_SpellScript);

            void HandleAfterHit()
            {
                if (Unit* target = GetHitUnit())
                {
                    if (target->HasAura(82654) || target->HasAura(54680) || target->HasAura(115804) || target->HasAura(8680))
                    {
                        if (AuraPtr reduceHealAura = target->GetAura(GetSpellInfo()->Id))
                        {
                            if (AuraEffectPtr reduceHealEffect = reduceHealAura->GetEffect(3))
                                reduceHealEffect->SetAmount(0);
                        }
                    }
                }
            }

            void Register()
            {
                AfterHit += SpellHitFn(spell_warl_reduce_heal_SpellScript::HandleAfterHit);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_warl_reduce_heal_SpellScript();
        }
};

class spell_warl_glyph_of_siphon_life : public SpellScriptLoader
{
public:
    spell_warl_glyph_of_siphon_life() : SpellScriptLoader("spell_warl_glyph_of_siphon_life") {}

    class spell_impl : public SpellScript
    {
        PrepareSpellScript(spell_impl);

        void HandleDummy(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);

            if (Unit * caster = GetCaster())
            {
                // 0.5% (5.4.0 17399)

                int32 healing = caster->CountPctFromMaxHealth(1) * 0.5f;
                SetHitHeal(healing);
                SetHitDamage(0);
            }
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_impl::HandleDummy, EFFECT_0, SPELL_EFFECT_HEAL_PCT);
        }
    };

    SpellScript* GetSpellScript() const

    {

        return new spell_impl();

    }
};

// WARLOCK_HAVOC_AURA : 80240 Es llamado por Caos Bolt-116858 / Conflagrate-17962 / Immolate-348 / Incinerate-29722 / Fel Flame-77799 / Shadowburn-17877 / Espiral Mortal-6789
class spell_warl_havoc : public SpellScriptLoader
{
	public:
		spell_warl_havoc() : SpellScriptLoader("spell_warl_havoc") { }

		class spell_warl_havoc_SpellScript : public SpellScript
		{
			PrepareSpellScript(spell_warl_havoc_SpellScript);

			bool triggerSpellHavoc;

			void HandleAfterOnCast()
			{
				if (Player* _caster = GetCaster()->ToPlayer())
				{
					if (Unit* _target = _caster->ToPlayer()->GetSelectedUnit())
					{
						SpellInfo const* spellInf = GetSpellInfo();
						if (spellInf && !spellInf->GetTriggeredByHavoc() && _caster && _caster->HasAura(WARLOCK_HAVOC_AURA) && _target){
							std::list<Unit*> targets;
							_caster->GetAttackableUnitListInRange(targets, 40.0f);

							targets.remove(_target);
							targets.remove(_caster);

							Unit* l_SecondTarget = nullptr;
							for (auto itr : targets)
							{
								if (!itr)
									continue;

								if (itr->IsWithinLOSInMap(_caster) && itr->IsWithinDist(_caster, 40.0f) && itr->HasAura(WARLOCK_HAVOC_AURA, _caster->GetGUID()))
								{
									l_SecondTarget = itr;
									break;
								}
							}

							if (l_SecondTarget)
							{
								triggerSpellHavoc = true;
								AuraPtr havoc = _caster->GetAura(WARLOCK_HAVOC_AURA);
								AuraPtr targetaura = l_SecondTarget->GetAura(WARLOCK_HAVOC_AURA);
								int leftcharge = 0;

								if (havoc)
								{
									switch (spellInf->Id)
									{
									case 17877:
									{
										int life = l_SecondTarget->GetMaxHealth() * 0.20;
										int healt = l_SecondTarget->GetHealth();
										if (healt && life && healt <= life)
										{
											havoc->ModStackAmount(-1);
											targetaura->ModStackAmount(-1);
											leftcharge = havoc->GetStackAmount();
											if (leftcharge > 0)
											{
												spellInf->SetTriggeredByHavoc(true);
												_caster->RemoveSpellCooldown(spellInf->Id, true);
												_caster->CastSpell(l_SecondTarget, spellInf, true);
											}
										}
										break;
									}
									default:
									{
										havoc->ModStackAmount(spellInf->Id == 116858 ? -3 : -1);
										targetaura->ModStackAmount(spellInf->Id == 116858 ? -3 : -1);
										leftcharge = havoc->GetStackAmount();
										if (leftcharge > 0)
										{
											spellInf->SetTriggeredByHavoc(true);
											_caster->RemoveSpellCooldown(spellInf->Id, true);
											_caster->CastSpell(l_SecondTarget, spellInf, true);
										}
										break;
									}
									}
								}
								if (leftcharge == 0)
								{
									_caster->RemoveAura(WARLOCK_HAVOC_AURA);
									_target->RemoveAura(WARLOCK_HAVOC_AURA);
								}
							}
							else if (_caster->HasAura(WARLOCK_HAVOC_AURA))
							{
								_caster->RemoveAura(WARLOCK_HAVOC_AURA);
							}
						}
						else
						{
							spellInf->SetTriggeredByHavoc(false);
						}
					}
				}
			}
		
			void Register()
			{
				AfterCast += SpellCastFn(spell_warl_havoc_SpellScript::HandleAfterOnCast);
			}
		};

	SpellScript* GetSpellScript() const
	{
		return new spell_warl_havoc_SpellScript();
	}
};

/// Called by Cauterize Master - 119905, Disarm - 119907, Whiplash - 119909, 
///           Spell Lock - 119910, Optical Blast - 119911, Fellash - 119913, 
///           Felstorm - 119914, Wrathstorm - 119915, Spell Lock - 132409
/// Command Demon - 119898
class spell_warl_command_demon : public SpellScriptLoader
{
public:
	spell_warl_command_demon() : SpellScriptLoader("spell_warl_command_demon") { }

	class spell_warl_command_demon_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_warl_command_demon_SpellScript);

		uint32 GetTargetSpellId()
		{
			SpellInfo const* spellInfo = GetSpellInfo();

			// Because all spells are not working the same way, ty Blizz
			switch (spellInfo->Id)
			{
			case WarlockSpells::WARLOCK_CAUTERIZE_MASTER:
				return WarlockSpells::WARLOCK_CAUTERIZE_MASTER_EFFECT;

			case WarlockSpells::WARLOCK_FELSTORM:
				return WarlockSpells::WARLOCK_FELSTORM_EFFECT;

			case WarlockSpells::WARLOCK_SPELL_LOCK2:
				return WarlockSpells::WARLOCK_SPELL_LOCK2_EFFECT;

			case WarlockSpells::WARLOCK_WRATHSTORM:
				return WarlockSpells::WARLOCK_WRATHSTORM_EFFECT;

			default:
				return spellInfo->Effects[EFFECT_0].BasePoints;
			}
		}

		SpellCastResult CheckCooldown()
		{
			if (Unit* l_Caster = GetCaster())
			{
				if (l_Caster->GetTypeId() != TypeID::TYPEID_PLAYER)
					return SpellCastResult::SPELL_CAST_OK;

				switch (m_scriptSpellId)
				{
				case WarlockSpells::WARLOCK_SPELL_LOCK:
				case WarlockSpells::WARLOCK_SPELL_LOCK2:
				case WarlockSpells::WARLOCK_DISARM:
					return CheckPlayerCooldown(l_Caster->ToPlayer());
				default:
					return CheckPetCooldown(l_Caster->ToPlayer());
				}
			}

			return SpellCastResult::SPELL_CAST_OK;
		}

        SpellCastResult CheckLoS()
        {
            if (Player* l_Player = GetCaster()->ToPlayer())
            {
                if (Pet* l_Pet = l_Player->GetPet())
                {
                    if (Unit* l_Target = GetExplTargetUnit())
                    {
                        if (!l_Pet->IsWithinLOS(l_Target->GetPositionX(), l_Target->GetPositionY(), l_Target->GetPositionZ()))
                        {
                            return SpellCastResult::SPELL_FAILED_LINE_OF_SIGHT;
                        }
                    }
                }
            }
            return SpellCastResult::SPELL_CAST_OK;
        }

		SpellCastResult CheckPetCooldown(Player const* l_Player)
		{
			if (Pet* l_Pet = l_Player->GetPet())
			{
				uint32 l_TargetSpellId = GetTargetSpellId();
				if (l_Pet->HasSpellCooldown(l_TargetSpellId))
					return SpellCastResult::SPELL_FAILED_NOT_READY;
			}
			else
				return SpellCastResult::SPELL_FAILED_NO_PET;

			return SpellCastResult::SPELL_CAST_OK;
		}

		SpellCastResult CheckPlayerCooldown(Player const* l_Player)
		{
			uint32 l_TargetSpellId = GetTargetSpellId();
			if (l_Player->HasSpellCooldown(l_TargetSpellId))
				return SpellCastResult::SPELL_FAILED_NOT_READY;

			return SpellCastResult::SPELL_CAST_OK;
		}

		SpellCastResult CheckValidAttackTarget()
		{
			if (Unit* l_Caster = GetCaster())
			{
				if (Unit* l_Target = GetExplTargetUnit())
				{
					if (!l_Caster->_IsValidAttackTarget(l_Target, sSpellMgr->GetSpellInfo(GetTargetSpellId())))
						return SpellCastResult::SPELL_FAILED_BAD_TARGETS;
				}
			}

			return SpellCastResult::SPELL_CAST_OK;
		}

		void FixCooldown()
		{
			if (Unit* l_Caster = GetCaster())
			{
				if (l_Caster->GetTypeId() != TypeID::TYPEID_PLAYER)
					return;

				Player* l_Player = l_Caster->ToPlayer();
				if (Pet* l_Pet = l_Player->GetPet())
					l_Pet->AddCreatureSpellCooldown(GetTargetSpellId());
			}
		}

		void HandleHitTarget(SpellEffIndex p_EffIndex)
		{
			if (Unit* l_Caster = GetCaster())
			{
				if (l_Caster->GetTypeId() != TypeID::TYPEID_PLAYER)
					return;

				Player* l_Player = l_Caster->ToPlayer();
				if (Unit* l_Target = GetHitUnit())
				{
					uint32 l_TargetSpellId = GetTargetSpellId();
					switch (m_scriptSpellId)
					{
						case WarlockSpells::WARLOCK_SPELL_LOCK:
						case WarlockSpells::WARLOCK_SPELL_LOCK2:
						case WarlockSpells::WARLOCK_DISARM:
						{
							l_Player->CastSpell(l_Target, l_TargetSpellId, true);
							l_Player->AddSpellAndCategoryCooldowns(sSpellMgr->GetSpellInfo(l_TargetSpellId), 0);
							break;
						}
						default:
						{
							if (Pet* l_Pet = l_Player->GetPet())
							{
								l_Pet->CastSpell(l_Target, l_TargetSpellId, false);
								l_Pet->AddCreatureSpellCooldown(l_TargetSpellId);
							}
							break;
						}
					}
				}
			}
		}

		void HandleHitDest(SpellEffIndex p_EffIndex)
		{
			if (Unit* l_Caster = GetCaster())
			{
				if (l_Caster->GetTypeId() != TypeID::TYPEID_PLAYER)
					return;

				Player* l_Player = l_Caster->ToPlayer();
				if (WorldLocation* l_Dest = GetHitDest())
				{
					if (Pet* l_Pet = l_Player->GetPet())
					{
						uint32 l_TargetSpellId = GetTargetSpellId();

						l_Pet->CastSpell(*l_Dest, l_TargetSpellId, false);
						l_Pet->AddCreatureSpellCooldown(l_TargetSpellId);
					}
				}
			}
		}

		void Register() override
		{
			OnCheckCast += SpellCheckCastFn(spell_warl_command_demon_SpellScript::CheckCooldown);
            OnCheckCast += SpellCheckCastFn(spell_warl_command_demon_SpellScript::CheckLoS);

			switch (m_scriptSpellId)
			{
			case WarlockSpells::WARLOCK_DISARM:
			case WarlockSpells::WARLOCK_SPELL_LOCK:
			case WarlockSpells::WARLOCK_OPTICAL_BLAST:
				OnCheckCast += SpellCheckCastFn(spell_warl_command_demon_SpellScript::CheckValidAttackTarget);
				// No break intended
			case WarlockSpells::WARLOCK_CAUTERIZE_MASTER:
				OnEffectHitTarget += SpellEffectFn(spell_warl_command_demon_SpellScript::HandleHitTarget, SpellEffIndex::EFFECT_0, SpellEffects::SPELL_EFFECT_DUMMY);
				break;

			case WarlockSpells::WARLOCK_FELLASH:
			case WarlockSpells::WARLOCK_WHIPLASH:
				OnEffectLaunch += SpellEffectFn(spell_warl_command_demon_SpellScript::HandleHitDest, SpellEffIndex::EFFECT_0, SpellEffects::SPELL_EFFECT_DUMMY);
				break;

			case WarlockSpells::WARLOCK_FELSTORM:
			case WarlockSpells::WARLOCK_WRATHSTORM:
				AfterCast += SpellCastFn(spell_warl_command_demon_SpellScript::FixCooldown);
				break;

			case WarlockSpells::WARLOCK_SPELL_LOCK2:
				OnCheckCast += SpellCheckCastFn(spell_warl_command_demon_SpellScript::CheckValidAttackTarget);
				OnEffectHitTarget += SpellEffectFn(spell_warl_command_demon_SpellScript::HandleHitTarget, SpellEffIndex::EFFECT_1, SpellEffects::SPELL_EFFECT_DUMMY);
				break;

			default:
				break;
			}
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_warl_command_demon_SpellScript();
	}
};

//////////////////////////////////////////////////////////////
/// 122355 - Molten Core Effect								//
//////////////////////////////////////////////////////////////

class spell_warl_moltencore : public SpellScriptLoader
{
public:
	spell_warl_moltencore() : SpellScriptLoader("spell_warl_moltencore") { }

	class spell_warl_moltencore_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_warl_moltencore_AuraScript);

		void OnApply(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
		{
			if (!GetCaster())
				return;

			if (aurEff->GetEffIndex() == EFFECT_0){
				if (AuraPtr aur = GetAura())
				{
					if (AuraEffectPtr realAuraEff = aur->GetEffect(EFFECT_0))
					{
						if (aur->GetStackAmount() > 1){							
							realAuraEff->SetAmount(0);
						}

					}
				}
			}			
		}

		void Register()
		{
			OnEffectApply += AuraEffectApplyFn(spell_warl_moltencore_AuraScript::OnApply, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
		}
	};

	AuraScript* GetAuraScript() const
	{
		return new spell_warl_moltencore_AuraScript();
	}
};

//////////////////////////////////////////////////////////////
/// Llamado por 6353 - Soulfire / 104027 - Demonic SoulFire //
//////////////////////////////////////////////////////////////

class spell_soulfire_moltencore : public SpellScriptLoader
{
public:
	spell_soulfire_moltencore() : SpellScriptLoader("spell_soulfire_moltencore") { }
	class spell_soulfire_moltencore_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_soulfire_moltencore_SpellScript);

		bool hasAuraPrepareCast;
		bool hasAuraOnCast;

		void HandleAfterCast()
		{
			if (Player* _player = GetCaster()->ToPlayer())
			{
				if (hasAuraPrepareCast && !hasAuraOnCast)
				{
					if (AuraPtr l_MoltenCore = _player->GetAura(WARLOCK_MOLTEN_CORE)){
						if (l_MoltenCore->GetStackAmount() < 1){
							_player->RemoveAura(WARLOCK_MOLTEN_CORE_VISUAL);
						}
						l_MoltenCore->DropCharge(AURA_REMOVE_BY_EXPIRE);
					}
				}
			}
		}

		void HandleOnCast()
		{
			if (Unit* l_Caster = GetCaster())
			{
				if (l_Caster->HasAura(WARLOCK_MOLTEN_CORE) && !hasAuraPrepareCast)
					hasAuraOnCast = true;
					
			}
		}

		void HandleOnPrepareCast() {
			if (Player* _player = GetCaster()->ToPlayer())
			{

				if (_player->HasAura(WARLOCK_MOLTEN_CORE)) {
					hasAuraPrepareCast = true;
					hasAuraOnCast = false;
				}
				else
					hasAuraPrepareCast = false;

			}
		}

		void Register()
		{
			OnPrepareCast += SpellCastFn(spell_soulfire_moltencore_SpellScript::HandleOnPrepareCast);
			AfterCast += SpellCastFn(spell_soulfire_moltencore_SpellScript::HandleAfterCast);
			OnCast += SpellCastFn(spell_soulfire_moltencore_SpellScript::HandleOnCast);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_soulfire_moltencore_SpellScript();
	}
};



/*######
## ID - 77220 Mastery: Emberstorm
## ID - 77215 Mastery: Potent Afflictions
## ID - 77219 Mastery: Master Demonologist
######*/
class spell_warl_mastery : public SpellScriptLoader
{
public:
    spell_warl_mastery() : SpellScriptLoader("spell_warl_mastery") { }

    class spell_warl_mastery_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_warl_mastery_AuraScript);

        void HandleEffectMasteryUpdate(AuraEffectPtr aurEff)
        {
            if (Unit* caster = GetCaster())
            {
                if (Player* player = caster->ToPlayer())
                {
                    float Mastery = 0;

                    switch (GetSpellInfo()->Id)
                    {
                        case WARLOCK_MASTERY_EMBERSTORM:
                            Mastery = player->GetFloatValue(PLAYER_MASTERY) + 1;
                            if (aurEff->GetEffIndex() == EFFECT_4)
                                Mastery = player->GetFloatValue(PLAYER_MASTERY) * 3;
                            break;
                        case WARLOCK_MASTERY_MASTER_DEMONOLOGIST:
                            Mastery = player->GetFloatValue(PLAYER_MASTERY) * 3;
                            if (AuraPtr metamorphosis = player->GetAura(WARLOCK_METAMORPHOSIS))
                                metamorphosis->GetEffect(EFFECT_1)->ChangeAmount(Mastery, true, true);
                            break;
                        case WARLOCK_MASTERY_POTENT_AFFLICTIONS:
                            Mastery = player->GetFloatValue(PLAYER_MASTERY) * 3.1f;
                            break;
                        default: break;
                    }

                    if (AuraPtr masteryAura = player->GetAura(GetSpellInfo()->Id))
                        masteryAura->GetEffect(aurEff->GetEffIndex())->ChangeAmount(Mastery, true, true);
                }
            }
        }

        void Register()
        {
            OnEffectMasteryUpdate += AuraEffectMasteryUpdateFn(spell_warl_mastery_AuraScript::HandleEffectMasteryUpdate, EFFECT_0, SPELL_AURA_ADD_FLAT_MODIFIER);
            OnEffectMasteryUpdate += AuraEffectMasteryUpdateFn(spell_warl_mastery_AuraScript::HandleEffectMasteryUpdate, EFFECT_0, SPELL_AURA_ADD_PCT_MODIFIER);
            OnEffectMasteryUpdate += AuraEffectMasteryUpdateFn(spell_warl_mastery_AuraScript::HandleEffectMasteryUpdate, EFFECT_2, SPELL_AURA_ADD_PCT_MODIFIER);
            OnEffectMasteryUpdate += AuraEffectMasteryUpdateFn(spell_warl_mastery_AuraScript::HandleEffectMasteryUpdate, EFFECT_3, SPELL_AURA_ADD_PCT_MODIFIER);
            OnEffectMasteryUpdate += AuraEffectMasteryUpdateFn(spell_warl_mastery_AuraScript::HandleEffectMasteryUpdate, EFFECT_4, SPELL_AURA_ADD_PCT_MODIFIER);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_warl_mastery_AuraScript();
    }
};

void AddSC_warlock_spell_scripts()
{
    new spell_warl_demonic_slash();
    new spell_warl_fury_ward();
    new spell_warl_dark_apotheosis();
    new spell_warl_glyph_of_demon_hunting();
    new spell_warl_grimoire_of_supremacy();
    new spell_warl_soulburn_drain_life();
    new spell_warl_soulburn_health_funnel();
    new spell_warl_soulburn_seed_of_corruption_damage();
    new spell_warl_soulburn_seed_of_corruption();
    new spell_warl_soulburn_remove();
    new spell_warl_soulburn_override();
    new spell_warl_glyph_of_soulwell();
    new spell_warl_imp_swarm();
    new spell_warl_glyph_of_imp_swarm();
    new spell_warl_unbound_will();
    new spell_warl_rain_of_fire_damage();
    new spell_warl_kil_jaedens_cunning();
    new spell_warl_shield_of_shadow();
    new spell_warl_agony();
    new spell_warl_grimoire_of_sacrifice();
    new spell_warl_flames_of_xoroth();
    new spell_warl_soul_link_dummy();
  //  new spell_warl_archimondes_vengeance_cooldown();
  //  new spell_warl_archimondes_vengance();
  //  new spell_warl_archimondes_vengance_passive();
    new spell_warl_molten_core_dot();
    new spell_warl_decimate();
    new spell_warl_demonic_call();
    new spell_warl_chaos_wave();
    new spell_warl_metamorphosis_cost();
    new spell_warl_immolation_aura();
    new spell_warl_dark_bargain_on_absorb();
    new spell_warl_dark_regeneration();
    new spell_warl_soul_leech();
    new spell_warl_sacrificial_pact();
    new spell_warl_hand_of_guldan();
    new spell_warl_twilight_ward_s12();
    new spell_warl_hellfire();
    new spell_warl_hellfire_aura();
    new spell_warl_demonic_leap();
    new spell_warl_burning_rush();
    new spell_warl_soul_swap_soulburn();
    new spell_warl_soul_swap();
	new spell_warl_soul_swap_aura_removal();
    new spell_warl_nightfall();
    new spell_warl_drain_soul();
    new spell_warl_demonic_gateway_charges();
    new spell_warl_demonic_gateway();
    new spell_warl_chaos_bolt();
    new spell_warl_ember_tap();
   // new spell_warl_glyph_of_demon_training();
    new spell_warl_fire_and_brimstone();
    new spell_warl_conflagrate_aura();
    new spell_warl_shadowburn();
    new spell_warl_burning_embers();
    new spell_warl_fel_flame();
    new spell_warl_drain_life();
    new spell_warl_soul_harverst();
    new spell_warl_life_tap();
    new spell_warl_soulburn_harvest_life();
    new spell_warl_fear();
    new spell_warl_banish();
    new spell_warl_create_healthstone();
    new spell_warl_seed_of_corruption();
    new spell_warl_soulshatter();
    new spell_warl_demonic_circle_summon();
    new spell_warl_demonic_circle_teleport();
    new spell_warl_unstable_affliction();
    new spell_warl_bloody_fear();
    new spell_warl_pandemic();
    new spell_warl_demonic_fury();
    new spell_warl_ritual_of_summoning();
    new spell_warl_touch_of_chaos();
    new spell_warl_rain_of_fire();
    new spell_warl_glyph_of_soul_consumption();
    new spell_warl_incinerate();
    new spell_warl_reduce_heal();
    new spell_warl_glyph_of_siphon_life();
	new spell_warl_havoc();	
	new spell_warl_command_demon();
	new spell_warl_siphon_life();
	new spell_soulfire_moltencore();
	new spell_warl_moltencore();
    new spell_warl_mastery();
}
