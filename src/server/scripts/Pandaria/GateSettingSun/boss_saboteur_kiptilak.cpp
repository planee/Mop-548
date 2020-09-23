/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "gate_setting_sun.h"
#include "CreatureTextMgr.h"

/*######
## boss_saboteur_kiptilak - 56906
######*/

const Position path[5] =
{
    { 734.726f, 2317.41f, 391.639f, 6.28011f },
    { 734.882f, 2291.8f, 391.639f, 4.6536f },
    { 709.097f, 2291.51f, 391.639f, 3.10095f },
    { 708.845f, 2317.5f, 391.639f, 1.60476f },
    { 721.513f, 2321.89f, 390.851f, 5.0559f } // Spawn position
};

enum eSay
{
    SAY_SABOTEUR_KIPTILAK_1 = 0, // Gate?! I'm going to bring this whole wall down!
    SAY_SABOTEUR_KIPTILAK_2 = 1, // I... blew it...
    SAY_SABOTEUR_KIPTILAK_3 = 2, // ...
    SAY_SABOTEUR_KIPTILAK_4 = 3, // ...
    SAY_SABOTEUR_KIPTILAK_5 = 4, // You've been |cFFFF0000|Hspell:107268|h[Sabotaged]|h|r!
    SAY_SABOTEUR_KIPTILAK_6 = 5, // |TInterface\Icons\inv_misc_bomb_05.blp:20|t%s casts |cFFFF0000|Hspell:107268|h[Sabotage]|h|r on |cFFFF0000$n|r!
    SAY_SABOTEUR_KIPTILAK_7 = 6, // Saboteur Kip'tilak sets off a series of explosions!
};

enum eSpells
{
    SPELL_PLANT_EXPLOSIVE               = 107187,

    SPELL_SABOTAGE                      = 107268,
    SPELL_SABOTAGE_EXPLOSION            = 113645,
    
    SPELL_PLAYER_EXPLOSION              = 113654,

    SPELL_MUNITION_STABLE               = 109987,
    SPELL_MUNITION_EXPLOSION            = 107153,
    SPELL_MUNITION_EXPLOSION_AURA       = 120551,
};

enum eEvents
{
    EVENT_EXPLOSIVES        = 1,
    EVENT_SABOTAGE          = 2,
    EVENT_PATH_POINT_1      = 3,
    EVENT_PATH_POINT_2      = 4,
    EVENT_PATH_POINT_3      = 5,
    EVENT_PATH_POINT_4      = 6,
    EVENT_WORLD_IN_FLAMES   = 7
};

class boss_saboteur_kiptilak : public CreatureScript
{
public:
    boss_saboteur_kiptilak() : CreatureScript("boss_saboteur_kiptilak") {}

    struct boss_saboteur_kiptilakAI : public BossAI
    {
        boss_saboteur_kiptilakAI(Creature* creature) : BossAI(creature, DATA_KIPTILAK)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;

        uint32 originalMovenetFlags;

        // Used to indicate if World In Flames has ben done at 70 % of HP
        bool hasDoneWorldInFlamesAt70Pct;
        // Used to indicate if World In Flames has ben done at 30 % of HP
        bool hasDoneWorldInFlamesAt30Pct;
        // Used to indicate if has Talk at 50 % of HP
        bool hasTalkAt50Pct;
        // Has started to fight
        bool isOnCombat;

        void Reset()
        {
            // Call the reset
            _Reset();
            // Stop the explosive events
            events.CancelEvent(EVENT_EXPLOSIVES);
            // Stop the sabotage events
            events.CancelEvent(EVENT_SABOTAGE);
            // Stop the path events
            events.CancelEvent(EVENT_PATH_POINT_1);
            events.CancelEvent(EVENT_PATH_POINT_2);
            events.CancelEvent(EVENT_PATH_POINT_3);
            events.CancelEvent(EVENT_PATH_POINT_4);
            // Stop World In Flames
            events.CancelEvent(EVENT_WORLD_IN_FLAMES);
            // Reset World In Flames at 70 %
            hasDoneWorldInFlamesAt70Pct = false;
            // Reset World In Flames at 30 %
            hasDoneWorldInFlamesAt30Pct = false;
            // Reset Talk at 50 %
            hasTalkAt50Pct = false;
            // Set is not in combat
            isOnCombat = false;
            // Requirements to the boss can fly
            me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
            me->SetSpeed(MOVE_RUN, 0.5f, true);
            me->SetDisableGravity(true);
            me->CanFly();
            // Take off
            me->GetMotionMaster()->MoveTakeoff(0, path[4]);
            // Start the path
            events.ScheduleEvent(EVENT_PATH_POINT_1, 14000);
        }

        void JustReachedHome() { }

        void EnterCombat(Unit* /*who*/)
        {
            // Enter on combat
            _EnterCombat();
            // Yell on enter on combat
            Talk(SAY_SABOTEUR_KIPTILAK_1);
            // Stop the path events
            events.CancelEvent(EVENT_PATH_POINT_1);
            events.CancelEvent(EVENT_PATH_POINT_2);
            events.CancelEvent(EVENT_PATH_POINT_3);
            events.CancelEvent(EVENT_PATH_POINT_4);
            // Start the throw of exploives
            events.ScheduleEvent(EVENT_EXPLOSIVES, urand(7500, 12500));
            // Start the sabotage timer event
            events.ScheduleEvent(EVENT_SABOTAGE, 15000);
            // Land
            me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
            me->SetSpeed(MOVE_RUN, 0.992063f);
            me->SetDisableGravity(false);
            me->SetCanFly(false);
            me->GetMotionMaster()->MoveFall();
            // Set on combat
            isOnCombat = true;
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            switch (attacker->GetEntry())
            {
            case NPC_EXPLOSION_BUNNY_N_M:
            case NPC_EXPLOSION_BUNNY_S_M:
            case NPC_EXPLOSION_BUNNY_E_M:
            case NPC_EXPLOSION_BUNNY_W_M:
            case NPC_EXPLOSION_BUNNY_N_P:
            case NPC_EXPLOSION_BUNNY_S_P:
            case NPC_EXPLOSION_BUNNY_E_P:
            case NPC_EXPLOSION_BUNNY_W_P:
                damage = 0;
                return;
            }
            // Check if the damage takes the HP to 70% or 30%
            if (me->HealthBelowPctDamaged(50, damage) && !hasTalkAt50Pct)
            {
                // Talk
                Talk(SAY_SABOTEUR_KIPTILAK_3);
                // Set that the say ben done at 50 %
                hasTalkAt50Pct = true;
            }
            // Check if the damage takes the HP to 70% or 30%
            if (me->HealthBelowPctDamaged(70, damage) && !hasDoneWorldInFlamesAt70Pct ||
                me->HealthBelowPctDamaged(30, damage) && !hasDoneWorldInFlamesAt30Pct)
            {
                //
                events.ScheduleEvent(EVENT_WORLD_IN_FLAMES, 1000);
                // Talk
                Talk(SAY_SABOTEUR_KIPTILAK_4);
                Talk(SAY_SABOTEUR_KIPTILAK_7);
                // Set that World in Flames has ben done at 70 % of HP and return
                if (!hasDoneWorldInFlamesAt70Pct)
                {
                    hasDoneWorldInFlamesAt70Pct = true;
                    return;
                }
                // Set that World in Flames has ben done at 30 %
                hasDoneWorldInFlamesAt30Pct = true;
            }
        }

        void JustSummoned(Creature* summoned)
        {
            //
            if (summoned->GetEntry() == NPC_STABLE_MUNITION)
                summoned->AddAura(SPELL_MUNITION_STABLE, summoned);
            // 
            summons.Summon(summoned);
        }

        Player* SelectRandomPlayer(float range = 0.0f)
        {
            Map* map = me->GetMap();
            if (!map->IsDungeon())
                return NULL;

            Map::PlayerList const &PlayerList = map->GetPlayers();
            if (PlayerList.isEmpty())
                return NULL;

            std::list<Player*> temp;
            for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                if (me->IsWithinDistInMap(i->getSource(), range) && i->getSource()->isAlive())
                    temp.push_back(i->getSource());

            if (!temp.empty())
            {
                std::list<Player*>::const_iterator j = temp.begin();
                advance(j, rand() % temp.size());
                return (*j);
            }
            return NULL;
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim() && isOnCombat)
            {
                // Players has fail to kill the boss
                instance->SetBossState(DATA_KIPTILAK, FAIL);
                // Despawn all summoned things
                summons.DespawnAll();
            }
            
            events.Update(diff);

            switch (events.ExecuteEvent())
            {
            case EVENT_EXPLOSIVES:
            {
                if (isOnCombat)
                {
                    // Throw 1 to 3 explosives
                    for (uint8 i = 0; i < urand(1, 3); ++i)
                        me->CastSpell(frand(702, 740), frand(2292, 2320), 388.5f, SPELL_PLANT_EXPLOSIVE, true);
                    // ReSchedule this evetnt
                    events.ScheduleEvent(EVENT_EXPLOSIVES, urand(7500, 12500));
                }
            }   break;
            case EVENT_SABOTAGE:
            {
                if (isOnCombat)
                {
                    // Create a null pointer for a random target
                    Player* randomPlayer = nullptr;
                    // Get A random player on the map
                    randomPlayer = SelectRandomPlayer(100.0f);
                    // Check the random player and cast sabotage over the player
                    if (randomPlayer)
                    {
                        // Announce that a sabotage has ben casted
                        Talk(SAY_SABOTEUR_KIPTILAK_6, randomPlayer->GetGUID());
                        // Cast Sabotage to the player
                        me->CastSpell(randomPlayer, SPELL_SABOTAGE, true);
                    }
                    // ReSchedule this evetnt
                    events.ScheduleEvent(EVENT_SABOTAGE, 15000);
                }
            }   break;
            case EVENT_PATH_POINT_1:
            {
                if (!isOnCombat)
                {
                    me->GetMotionMaster()->MovePoint(0, path[0]);
                    me->GetMotionMaster()->Initialize();
                    events.ScheduleEvent(EVENT_PATH_POINT_2, 7000);
                }
            } break;
            case EVENT_PATH_POINT_2:
            {
                if (!isOnCombat)
                {
                    me->GetMotionMaster()->MovePoint(0, path[1]);
                    me->GetMotionMaster()->Initialize();
                    events.ScheduleEvent(EVENT_PATH_POINT_3, 7000);
                }
            } break;
            case EVENT_PATH_POINT_3:
            {
                if (!isOnCombat)
                {
                    me->GetMotionMaster()->MovePoint(0, path[2]);
                    me->GetMotionMaster()->Initialize();
                    events.ScheduleEvent(EVENT_PATH_POINT_4, 7000);
                }
            } break;
            case EVENT_PATH_POINT_4:
            {
                if (!isOnCombat)
                {
                    me->GetMotionMaster()->MovePoint(0, path[3]);
                    me->GetMotionMaster()->Initialize();
                    events.ScheduleEvent(EVENT_PATH_POINT_1, 7000);
                }
            } break;
            case EVENT_WORLD_IN_FLAMES:
            {
                if (isOnCombat)
                {
                    // Get all the Stable Munittions around
                    std::list<Creature*> munitionList;
                    GetCreatureListWithEntryInGrid(munitionList, me, NPC_STABLE_MUNITION, 100.0f);
                    // Detonate each one of them
                    for (auto itr : munitionList)
                    {
                        itr->RemoveAurasDueToSpell(SPELL_MUNITION_STABLE);
                        itr->CastSpell(itr, SPELL_MUNITION_EXPLOSION, true);
                        itr->DespawnOrUnsummon(2000);
                    }
                }
            }   break;
            default:
                break;
            }

            DoMeleeAttackIfReady();
        }

        void JustDied(Unit* /*killer*/)
        {
            Talk(SAY_SABOTEUR_KIPTILAK_2);
            _JustDied();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_saboteur_kiptilakAI(creature);
    }
};

/*######
## spell_kiptilak_munitions_explosion - 120552
######*/

class npc_munition_explosion_bunny : public CreatureScript
{
public:
    npc_munition_explosion_bunny() : CreatureScript("npc_munition_explosion_bunny") { }

    struct npc_munition_explosion_bunnyAI : public ScriptedAI
    {
        npc_munition_explosion_bunnyAI(Creature* creature) : ScriptedAI(creature) {}

        float orientation;
        uint32 checkTimer;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            orientation = 0.0f;
            checkTimer = 1000;

            switch (me->GetEntry())
            {
                case NPC_EXPLOSION_BUNNY_N_M:
                case NPC_EXPLOSION_BUNNY_N_P:
                    orientation = 0.0f;
                    break;
                case NPC_EXPLOSION_BUNNY_S_M:
                case NPC_EXPLOSION_BUNNY_S_P:
                    orientation = M_PI;
                    break;
                case NPC_EXPLOSION_BUNNY_E_M:
                case NPC_EXPLOSION_BUNNY_E_P:
                    orientation = 4.71f;
                    break;
                case NPC_EXPLOSION_BUNNY_W_M:
                case NPC_EXPLOSION_BUNNY_W_P:
                    orientation = 1.57f;
                    break;
            }

            float x = 0.0f;
            float y = 0.0f;
            GetPositionWithDistInOrientation(me, 40.0f, orientation, x, y);
            me->GetMotionMaster()->MovePoint(1, x, y, me->GetPositionZ());

            me->AddAura(SPELL_MUNITION_EXPLOSION_AURA, me);
        }

        void DamageTaken(Unit* attacker, uint32& damage)
        {
            damage = 0;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (id == 1)
                me->DespawnOrUnsummon();
        }

        void EnterCombat(Unit* /*who*/)
        {
            return;
        }
        
        void UpdateAI(const uint32 diff)
        {
            if (checkTimer <= diff)
            {
                checkTimer = 500;
                if (Creature* munition = GetClosestCreatureWithEntry(me, NPC_STABLE_MUNITION, 2.0f, true))
                {
                    if (munition->HasAura(SPELL_MUNITION_STABLE))
                    {
                        munition->RemoveAurasDueToSpell(SPELL_MUNITION_STABLE);
                        munition->CastSpell(munition, SPELL_MUNITION_EXPLOSION, true);
                        munition->DespawnOrUnsummon(2000);
                    }
                }
            }
            else checkTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_munition_explosion_bunnyAI (creature);
    }
};

/*######
## spell_kiptilak_munitions_explosion - 120552
######*/

class CheckMunitionExplosionPredicate
{
    public:
        CheckMunitionExplosionPredicate(Unit* caster) : _caster(caster) {}

        bool operator()(WorldObject* target)
        {
            if (!_caster || !target)
                return true;

            if (!_caster->ToTempSummon())
                return true;

            Unit* creator = _caster->ToTempSummon()->GetSummoner();

            if (!creator || creator == target)
                return true;

            return false;
        }

    private:
        Unit* _caster;
};

class spell_kiptilak_munitions_explosion : public SpellScriptLoader
{
    public:
        spell_kiptilak_munitions_explosion() : SpellScriptLoader("spell_kiptilak_munitions_explosion") { }

        class spell_kiptilak_munitions_explosion_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_kiptilak_munitions_explosion_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                if (Unit* caster = GetCaster())
                    unitList.remove_if(CheckMunitionExplosionPredicate(caster));
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_kiptilak_munitions_explosion_SpellScript::FilterTargets, EFFECT_0, TARGET_SRC_CASTER);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_kiptilak_munitions_explosion_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_kiptilak_munitions_explosion_SpellScript();
        }
};

/*######
## spell_kiptilak_sabotage - 107268
######*/

class spell_kiptilak_sabotage : public SpellScriptLoader
{
    public:
        spell_kiptilak_sabotage() :  SpellScriptLoader("spell_kiptilak_sabotage") { }

        class spell_kiptilak_sabotage_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_kiptilak_sabotage_AuraScript);

            void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* caster = GetCaster())
                {
                    if (Unit* target = GetTarget())
                    {
                        if (Player* player = target->ToPlayer())
                        {
                              // Talk
                            LocaleConstant local = player->GetSession()->GetSessionDbcLocale();
                            std::string text = sCreatureTextMgr->GetLocalizedChatString(caster->GetEntry(), SAY_SABOTEUR_KIPTILAK_5, 0, local);
                            WorldPacket data;
                            player->BuildPlayerChat(&data, CHAT_MSG_RAID_BOSS_EMOTE, text, LANG_UNIVERSAL);
                            player->GetSession()->SendPacket(&data);
                        }
                    }
                }
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                Unit* target = GetTarget();

                if (!target)
                    return;

                target->CastSpell(target, SPELL_PLAYER_EXPLOSION, true);
                target->CastSpell(target, SPELL_SABOTAGE_EXPLOSION, true);
            }

            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_kiptilak_sabotage_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_kiptilak_sabotage_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_kiptilak_sabotage_AuraScript();
        }
};

/* @TODO NOTES
This boos should loot 5 Timewarped Badge[1166]
*/

void AddSC_boss_saboteur_kiptilak()
{
    new boss_saboteur_kiptilak();
    new npc_munition_explosion_bunny();
    new spell_kiptilak_munitions_explosion();
    new spell_kiptilak_sabotage();
}
