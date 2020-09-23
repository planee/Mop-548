/*
* Copyright (C) 2014-2017 RoG_WoW Source  <http://wow.rog.snet
*
* Dont Share The SourceCode
*
*/

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "CreatureTextMgr.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "Player.h"
#include "Vehicle.h"

#include "stormstout_brewery.h"

enum Yells
{
    SAY_INTRO                    = 0, // Who crashing Ook party!? Ook ook ook...
    SAY_AGGRO                    = 1, // Me gonna ook you in the ooker!
    SAY_KILL                     = 2, // In the ooker!
    SAY_BANANAS                  = 3, // 0 - Get Ooking party started! ; 1 - Come on and get your Ook on! ; 2 - We're gonna Ook all night!
    SAY_DEATH                    = 4  // Ook ! Oooook !
};

#define ANN_BANANAS "Ook-Ook is Going Bananas! More barrels are coming!"

enum Spells
{
    // Boss
    SPELL_GROUND_POUND              = 106807, // Aura.
    SPELL_GOING_BANANAS             = 106651, // Aura.
    SPELL_GOING_BANANAS_DUMMY       = 115978, // Throws bananas around :).

    // NPCs
    SPELL_BARREL_EXPLOSION_PLR      = 107016, ///< Explosion on players. Triggered by 115868 periodic aura.
    SPELL_SMALL_DUST_PUFF           = 116169,

    SPELL_BARREL_RIDE               = 106614, ///< Vehicle ride spell, triggers 106768, triggering 106769.
    SPELL_FORCECAST_BARREL_DROP     = 122385, ///< Triggers SPELL_BARREL_DROP.
    SPELL_BARREL_DROP               = 122376, ///< Jump spell for Barrel NPC.
    SPELL_BARREL_TOSS_MISSILE       = 106847,
    SPELL_BARREL_TOSS_SUMMON        = 106848,

    // 56682 - Rolling Barrel
    SPELL_BREW_BARREL_PER_A         = 115868,
    SPELL_BREW_BARREL_PER_B         = 106768,
    SPELL_BREW_BARREL_PER_C         = 115907,
    SPELL_BARREL_COSMETIC           = 106647, ///< Visual spell, triggers 106672 dummy each 300 ms.
    SPELL_BREW_EXPLOSION_HOZEN      = 107351, ///< Explosion on Hozens
    SPELL_BREW_EXPLOSION_BOSS       = 106784, ///< Explosion on Ook-Ook
    SPELL_BREW_EXPLOSION_BASIC      = 106648, ///< Basic explosion on players, walls, other barrels...
};

enum Events
{
    // Boss
    EVENT_GROUND_POUND           = 1,
    EVENT_GOING_BANANAS,

    // NPCs
    EVENT_EXPLODE,
    EVENT_BARREL_TOSS,
};

enum GoingBananasStates
{
    DONE_NONE              = 0, // No casts done.
    DONE_90                = 1, // First cast done.
    DONE_60                = 2, // Second cast done.
    DONE_30                = 3  // All casts done.
};

enum eTypes
{
    TYPE_SUMMONED_BARREL = 1,
};

const Position g_BarrelPos = { -766.802f, 1391.21f, 146.739f, 0.236796f };
const Position g_OokOokFightPos = { -755.653f, 1351.396f, 146.923f, 1.832596f };
const Position g_HozenFleeingPos = { -771.666f, 1412.337f, 139.579f, 1.832596f };

class boss_ook_ook : public CreatureScript
{
    public:
        boss_ook_ook() : CreatureScript("boss_ook_ook") { }

        struct boss_ook_ook_AI : public BossAI
        {
            boss_ook_ook_AI(Creature* creature) : BossAI(creature, DATA_OOKOOK_EVENT), summons(me)
            {
                instance = creature->GetInstanceScript();
                m_IntroDone = false;
            }

            InstanceScript* instance;
            EventMap events;
            SummonList summons;            
            uint8 goingBananasDone;
            uint64 m_BarrelGuid;
            bool m_InCombat;
            bool m_IntroDone;
            bool summonedBarrels; // For Going Bananas phases.
            bool achievement;

            void Reset()
            {
                events.Reset();
                summons.DespawnAll();
                summonedBarrels = false;                
                m_InCombat = false;
                achievement = false;
                m_BarrelGuid = 0;

                if (!m_IntroDone)
                {
                    me->SetReactState(REACT_PASSIVE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                }

                if (instance)
                {
                    instance->SetData(DATA_OOKOOK_EVENT, NOT_STARTED);
                    instance->SetBossState(DATA_OOKOOK, NOT_STARTED);
                }
                    

                goingBananasDone = DONE_NONE;

                _Reset();
            }

            void MovementInform(uint32 p_Type, uint32 p_Id)
            {
                if (p_Type != EFFECT_MOTION_TYPE || p_Id != 1)
                    return;

                if (!m_IntroDone)
                {
                    Talk(SAY_INTRO);
                    m_IntroDone = true;
                }

                me->SetReactState(REACT_DEFENSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);

                if (GameObject* l_Barrel = me->SummonGameObject(GAMEOBJECT_OOK_OOK_DOOR, g_BarrelPos.m_positionX, g_BarrelPos.m_positionY, g_BarrelPos.m_positionZ, g_BarrelPos.m_orientation, 0, 0, 0, 0, 0))
                {
                    l_Barrel->SetGoState(GO_STATE_READY);
                    m_BarrelGuid = l_Barrel->GetGUID();                    

                    if (Creature* l_Dummy = GetClosestCreatureWithEntry(me, NPC_GENERAL_PURPOSE_BUNNY_B, 50.0f))
                        l_Dummy->CastSpell(l_Dummy, SPELL_DUSTY_EXPLOSION, true);
                }
                me->SetHomePosition(g_OokOokFightPos);
            }

            void EnterCombat(Unit* /*who*/)
            {
                if (!m_InCombat)
                {
                    Talk(SAY_AGGRO);
                    m_InCombat = true;
                }

                if (instance)
                {
                    instance->SetData(DATA_OOKOOK_EVENT, IN_PROGRESS);
                    instance->SetBossState(DATA_OOKOOK, IN_PROGRESS);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
                }

                if (!me->FindNearestGameObject(GAMEOBJECT_OOK_OOK_DOOR, 50.0f))
                if (GameObject* l_Barrel = me->SummonGameObject(GAMEOBJECT_OOK_OOK_DOOR, g_BarrelPos.m_positionX, g_BarrelPos.m_positionY, g_BarrelPos.m_positionZ, g_BarrelPos.m_orientation, 0, 0, 0, 0, 0))
                {
                    l_Barrel->SetGoState(GO_STATE_READY);
                    m_BarrelGuid = l_Barrel->GetGUID();

                    if (Creature* l_Dummy = GetClosestCreatureWithEntry(me, NPC_GENERAL_PURPOSE_BUNNY_B, 50.0f))
                        l_Dummy->CastSpell(l_Dummy, SPELL_DUSTY_EXPLOSION, true);
                }

                events.ScheduleEvent(EVENT_GROUND_POUND, 10000);

                _EnterCombat();
            }

            void KilledUnit(Unit* victim)
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    Talk(SAY_KILL);
            }

            void DoAction(int32 const p_Action)
            {
                if (p_Action == ACTION_OOK_OOK_FIGHT)
                {
                    if (m_InCombat)
                        return;

                    me->GetMotionMaster()->MoveJump(g_OokOokFightPos.GetPositionX(), g_OokOokFightPos.GetPositionY(),
                        g_OokOokFightPos.GetPositionZ(), 45.0f, 10.f, g_OokOokFightPos.GetOrientation(), 1);

                    // Making all hozen party animals flee
                    std::list<Creature*> l_HozenList;
                    std::list<Creature*> HozenListParty;
                    GetCreatureListWithEntryInGrid(l_HozenList, me, NPC_HOZEN_PARTY_ANIMAL, 200.0f); // TODO: adjuste searche range
                    GetCreatureListWithEntryInGrid(HozenListParty, me, NPC_HOZEN_PARTY_ANIMAL_1, 200.0f); // TODO: adjuste searche range
                    if (!l_HozenList.empty())
                    {
                        for (Creature* l_Hozen : l_HozenList)
                        {
                            if (!l_Hozen->isAlive() || l_Hozen->GetPositionZ() < 146.0f)
                                continue;

                            l_Hozen->CombatStop(true);
                            l_Hozen->DeleteThreatList();
                            l_Hozen->SetReactState(REACT_PASSIVE);
                            l_Hozen->GetMotionMaster()->MoveCharge(g_HozenFleeingPos.GetPositionX(), g_HozenFleeingPos.GetPositionY(),
                                g_HozenFleeingPos.GetPositionZ(), 42.0f, 2);
                            l_Hozen->DespawnOrUnsummon(4000);
                        }
                    }
                    if (!HozenListParty.empty())
                    {
                        for (Creature* l_Hozen : HozenListParty)
                        {
                            if (!l_Hozen->isAlive() || l_Hozen->GetPositionZ() < 146.0f)
                                continue;

                            l_Hozen->CombatStop(true);
                            l_Hozen->DeleteThreatList();
                            l_Hozen->SetReactState(REACT_PASSIVE);
                            l_Hozen->GetMotionMaster()->MoveCharge(g_HozenFleeingPos.GetPositionX(), g_HozenFleeingPos.GetPositionY(),
                                g_HozenFleeingPos.GetPositionZ(), 42.0f, 2);
                            l_Hozen->DespawnOrUnsummon(4000);
                        }
                    }
                }
            }

            void DamageTaken(Unit* p_Attacker, uint32& p_Damage)
            {
                if (m_InCombat)
                    return;

                EnterCombat(p_Attacker);
            }

            void EnterEvadeMode()
            {

                if (GameObject* l_Barrel = GameObject::GetGameObject(*me, m_BarrelGuid))
                    l_Barrel->RemoveFromWorld();

                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();

                if (instance)
                {
                    instance->SetData(DATA_OOKOOK_EVENT, FAIL);
                    instance->SetBossState(DATA_OOKOOK, FAIL);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
                }

                _EnterEvadeMode();
            }

            void JustDied(Unit* /*killer*/)
            {
                if (instance)
                {
                    instance->SetData(DATA_OOKOOK_EVENT, DONE);
                    instance->SetBossState(DATA_OOKOOK, DONE);
                    instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                    if (achievement)
                    instance->DoCompleteAchievement(6089); // Keep Rollin' Rollin' Rollin' Achievement
                }

                Talk(SAY_DEATH);
                summons.DespawnAll();

                if (GameObject* l_Barrel = GameObject::GetGameObject(*me, m_BarrelGuid))
                    l_Barrel->RemoveFromWorld();

                std::list<Creature*> l_AddList;
                GetCreatureListWithEntryInGrid(l_AddList, me, NPC_HOZEN_BOUNCER, 200.0f); // TODO: adjuste searche range

                for (std::list<Creature*>::iterator l_Itr = l_AddList.begin(); l_Itr != l_AddList.end(); ++l_Itr)
                {
                    if (*l_Itr = l_AddList.front())
                        (*l_Itr)->AI()->DoAction(ACTION_OOK_OOK_TALK);
                    (*l_Itr)->AI()->DoAction(ACTION_OOK_OOK_DEAD);
                }

                // Deactivate Hollorer (launch of barrels)
                l_AddList.clear();
                GetCreatureListWithEntryInGrid(l_AddList, me, NPC_HOZEN_HOLLERER, 200.0f); // TODO: adjuste searche range
                for (Creature* l_Hollerer : l_AddList)
                    l_Hollerer->AI()->DoAction(ACTION_OOK_OOK_DEAD);

                _JustDied();
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);

		        if (me->isInCombat())
                    summon->SetInCombatWithZone();
            }

            uint32 GetData(uint32 p_Type)
            {
                if (p_Type == TYPE_SUMMONED_BARREL)
                    return summonedBarrels == true ? 1 : 0;
                return 0;
            }

            void SetData(uint32 p_Type, uint32 p_Value)
            {
                if (p_Type == TYPE_SUMMONED_BARREL)
                    summonedBarrels = p_Value = 0 ? false : true;
            }
           
            void UpdateAI(const uint32 diff)
            {

                if (instance)
                {
                    if (instance->IsWipe() && !me->IsInEvadeMode())
                    {
                        EnterEvadeMode();
                        return;
                    }
                }

                if (me->isInCombat() && !instance->IsWipe())
                {
                    Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                    if (!PlayerList.isEmpty())
                    {
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        {
                            if (Player *player = i->getSource())
                            if (player->HasUnitState(UNIT_STATE_ONVEHICLE))
                            {
                                player->ClearUnitState(UNIT_STATE_ONVEHICLE);
                                return;
                            }
                        }
                    }
                }


                if (IsHeroic() && !achievement && me->HasAura(SPELL_BREW_EXPLOSION_BOSS))
                { 
                    if(AuraPtr aur = me->GetAura(SPELL_BREW_EXPLOSION_BOSS))                 
                    if (aur->GetStackAmount() >= 20)
                    {
                        achievement = true;
                        return;
                    }
                }
                else  if (IsHeroic() && !achievement && me->HasAura(SPELL_BREW_EXPLOSION_HOZEN))
                {
                    if(AuraPtr aur = me->GetAura(SPELL_BREW_EXPLOSION_HOZEN))
                    if (aur->GetStackAmount() >= 20)
                    {
                        achievement = true;
                        return;
                    }                        
                }


                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                // Set Going Bananas phases execution.
                if (me->HealthBelowPct(91) && goingBananasDone == DONE_NONE || me->HealthBelowPct(61) && goingBananasDone == DONE_90 || me->HealthBelowPct(31) && goingBananasDone == DONE_60)
                {
                    events.ScheduleEvent(EVENT_GOING_BANANAS, 1000);
                    goingBananasDone++;
                }

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_GROUND_POUND:
                            DoCast(me, SPELL_GROUND_POUND);                            
                            events.ScheduleEvent(EVENT_GROUND_POUND, DUNGEON_MODE(10000, 7000));
                            break;

                        case EVENT_GOING_BANANAS:
                            me->MonsterTextEmote(ANN_BANANAS, NULL, true);
                            Talk(SAY_BANANAS);
                            summonedBarrels = false;
                            DoCast(me, SPELL_GOING_BANANAS);
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_ook_ook_AI(creature);
        }
};

// 56783 - Hozen Hollerer
class npc_ook_hozen_hollerer : public CreatureScript
{
public:
    npc_ook_hozen_hollerer() : CreatureScript("npc_ook_hozen_hollerer") { }

    struct npc_ook_hozen_hollererAI : public ScriptedAI
    {
        npc_ook_hozen_hollererAI(Creature* p_Creature) : ScriptedAI(p_Creature)
        {
            m_Instance = p_Creature->GetInstanceScript();
        }

        InstanceScript* m_Instance;
        EventMap m_Events;
        bool m_Active;  // Is able to toss barrels (but could be not tossing if no player around)
        bool m_Tossing; // Is actually tossing barrels

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            if (m_Instance)
                m_Active = m_Instance->GetBossState(DATA_OOKOOK) != DONE;

            m_Tossing = false;
        }

        void MoveInLineOfSight(Unit* p_Who)
        {
            if (!m_Active || m_Tossing || p_Who->GetTypeId() != TYPEID_PLAYER || !me->IsWithinDist3d(p_Who, 40.0f))
                return;

            m_Tossing = true;
            m_Events.ScheduleEvent(EVENT_BARREL_TOSS, urand(1000, 5000));
        }

        void DoAction(int32 const p_Action)
        {
            if (p_Action == ACTION_OOK_OOK_DEAD)
            {
                m_Events.Reset();
                m_Active = false;
                m_Tossing = false;
            }
        }

        void UpdateAI(uint32 const p_Diff)
        {
            if (!m_Active || !m_Tossing)
                return;

            m_Events.Update(p_Diff);
            if (m_Events.ExecuteEvent() == EVENT_BARREL_TOSS)
            {
                // To cast on invisible NPC...
                if (Unit* l_Target = GetClosestCreatureWithEntry(me, NPC_BARREL_TOSS_TARGET, 20.0f))
                    me->CastSpell(l_Target, SPELL_BARREL_TOSS_MISSILE, false);

                m_Events.ScheduleEvent(EVENT_BARREL_TOSS, urand(7000, 10000));
            }
        }
    };

    CreatureAI* GetAI(Creature* p_Creature) const
    {
        return new npc_ook_hozen_hollererAI(p_Creature);
    }
};

// Brew Barrel 56682.
class npc_ook_barrel : public CreatureScript
{
public:
    npc_ook_barrel() : CreatureScript("npc_ook_barrel") { }

    struct npc_ook_barrel_AI : public ScriptedAI
    {
        npc_ook_barrel_AI(Creature* p_Creature) : ScriptedAI(p_Creature), m_Vehicle(p_Creature->GetVehicleKit())
        {
            ASSERT(m_Vehicle);
            m_Instance = p_Creature->GetInstanceScript();
        }

        Vehicle* m_Vehicle;
        InstanceScript* m_Instance;

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->AddAura(SPELL_BARREL_COSMETIC, me);
            me->AddAura(SPELL_BREW_BARREL_PER_B, me);
            me->SetSpeed(MOVE_WALK, 0.7f);
            me->SetSpeed(MOVE_RUN, 0.7f);
            me->SetUnitMovementFlags(MOVEMENTFLAG_LEFT);
            me->SetUnitMovementFlags(MOVEMENTFLAG_RIGHT);                
        }

        void IsSummonedBy(Unit* p_Summoner)
        {
            me->CastSpell(me, SPELL_SMALL_DUST_PUFF, true);

            float l_Ori = 0.0f;

            if (m_Instance)
            {
                /// If in combat against Ook Ook, barrel targets either Ook Ook or players
                if (m_Instance->GetBossState(DATA_OOKOOK) == IN_PROGRESS)
                {
                    std::list<Unit*> l_TargetList;
                    // Adding Ook-Ook to the targets list
                    if (Creature* l_OokOok = m_Instance->instance->GetCreature(m_Instance->GetData64(BOSS_OOKOOK)))
                        l_TargetList.push_back(l_OokOok);

                    // Adding players to the targets list
                    std::list<Player*> l_PlayerList;
                    GetPlayerListInGrid(l_PlayerList, me, 100.0f);

                    for (Player* l_Plr : l_PlayerList)
                    {
                        // Not targetting riding players
                        if (l_Plr->HasAura(SPELL_BARREL_RIDE))
                            continue;

                        l_TargetList.push_back(l_Plr);
                    }

                    // Selecting a target
                    if (!l_TargetList.empty())
                    {
                        WoWSource::RandomResizeList(l_TargetList, 1);
                        Unit* l_Target = l_TargetList.front();
                        l_Ori = me->GetAngle(l_Target->GetPositionX(), l_Target->GetPositionY());
                    }
                }
            }

            // Random way: if l_Ori is still at 0.0f, we're not targeting an unit, else, we're going in a random direction
            l_Ori = l_Ori != 0.0 ? l_Ori : p_Summoner->GetOrientation() + frand(-1.0f, 1.0f);
            float l_X = me->GetPositionX() + 40.0f * cos(l_Ori);
            float l_Y = me->GetPositionY() + 40.0f * sin(l_Ori);
            me->GetMotionMaster()->MovePoint(1, l_X, l_Y, me->GetPositionZ());
        }

        void MovementInform(uint32 p_Type, uint32 p_Id)
        {
            if (!me->isAlive() || p_Type != POINT_MOTION_TYPE || p_Id != 1)
                return;

            if (!me->FindNearestCreature(BOSS_OOKOOK, 5.0f, true))
            me->CastSpell(me, SPELL_BREW_EXPLOSION_HOZEN, true);
            me->DespawnOrUnsummon(500);
        }

        void OnSpellClick(Unit* p_Player)
        {
            me->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ());
            p_Player->CastSpell(me, SPELL_BARREL_RIDE, true);

        }

        void UpdateAI(uint32 const /*diff*/) { } ///< Override UpdateAI to avoid melee attacks
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ook_barrel_AI(creature);
    }
};

// Going Bananas 115978.
class spell_ook_ook_going_bananas_summon : public SpellScriptLoader
{
public:
    spell_ook_ook_going_bananas_summon() : SpellScriptLoader("spell_ook_ook_going_bananas_summon") { }

    class spell_ook_ook_going_bananas_summon_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ook_ook_going_bananas_summon_SpellScript)

        bool Validate(const SpellInfo* spellInfo)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_GOING_BANANAS_DUMMY))
                return false;

            return true;
        }

        void HandleDummy(SpellEffIndex effIndex) // This comes periodic, so only do it once per phase.
        {
            if (GetCaster() && GetCaster()->GetEntry() == BOSS_OOKOOK)
            {
                if (Creature* l_OokOok = GetCaster()->ToCreature())
                {
                    if (l_OokOok->AI()->GetData(TYPE_SUMMONED_BARREL) == 0)
                    {
                        for (uint8 l_Idx = 0; l_Idx < 6; ++l_Idx)
                            l_OokOok->SummonCreature(NPC_OOK_BARREL, l_OokOok->GetPositionX() + frand(-30.0f, 30.0f), l_OokOok->GetPositionY() + frand(-30.0f, 30.0f), l_OokOok->GetPositionZ(), frand(0.0f, 2 * M_PI));

                        l_OokOok->AI()->SetData(TYPE_SUMMONED_BARREL, 1);
                    }
                }
            }
        }

        void Register()
        {
            OnEffectLaunch += SpellEffectFn(spell_ook_ook_going_bananas_summon_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ook_ook_going_bananas_summon_SpellScript();
    }
};

class PositionCheck : public std::unary_function<Unit*, bool>
{
public:
    explicit PositionCheck(Unit* _caster) : caster(_caster) { }
    bool operator()(WorldObject* object)
    {
        return !caster->HasInArc(M_PI / 6, object);
    }

private:
    Unit* caster;
};

// Ground Pound triggered spell 106808.
class spell_ook_ook_ground_pound_dmg : public SpellScriptLoader
{
public:
    spell_ook_ook_ground_pound_dmg() : SpellScriptLoader("spell_ook_ook_ground_pound_dmg") { }

    class spell_ook_ook_ground_pound_dmgSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_ook_ook_ground_pound_dmgSpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (Unit* l_Caster = GetCaster())
                targets.remove_if(PositionCheck(l_Caster));
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ook_ook_ground_pound_dmgSpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CONE_ENEMY_104);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_ook_ook_ground_pound_dmgSpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_CONE_ENEMY_104);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_ook_ook_ground_pound_dmgSpellScript();
    }
};

// 106847 - Barrel Toss (missile) - cast 106848
class spell_barrel_toss_missile : public SpellScriptLoader
{
public:
    spell_barrel_toss_missile() : SpellScriptLoader("spell_barrel_toss_missile") { }

    class spell_barrel_toss_missile_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_barrel_toss_missile_SpellScript);

        void Trigger(SpellEffIndex /*p_EffIndex*/)
        {
            if (Unit* l_Caster = GetCaster())
            {
                if (Unit* l_Target = GetExplTargetUnit())
                    l_Caster->CastSpell(l_Target, SPELL_BARREL_TOSS_SUMMON, true);
            }
        }

        void Register()
        {
            OnEffectHit += SpellEffectFn(spell_barrel_toss_missile_SpellScript::Trigger, EFFECT_0, SPELL_EFFECT_TRIGGER_MISSILE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_barrel_toss_missile_SpellScript();
    }
};

// 106768 - Brew Barrel Periodic Trigger
class spell_brew_barrel : public SpellScriptLoader
{
public:
    spell_brew_barrel() : SpellScriptLoader("spell_brew_barrel") { }

    class spell_brew_barrel_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_brew_barrel_AuraScript);

        void DespawnBarrel(uint32 p_SpellId, Unit* p_Interact = nullptr, bool p_BarrelIsCaster = true)
        {
            if (!GetUnitOwner())
                return;

            Creature* l_Barrel = GetUnitOwner()->ToCreature();
            if (!l_Barrel)
                return;

            if (!p_Interact)
                p_Interact = l_Barrel;

            if (Vehicle* l_Vehicle = l_Barrel->GetVehicleKit())
                l_Vehicle->RemoveAllPassengers(true);

            if (p_SpellId)
            {
                if (p_BarrelIsCaster)
                    l_Barrel->CastSpell(p_Interact, p_SpellId, true);
                else
                    p_Interact->CastSpell(l_Barrel, p_SpellId, true);
            }

            l_Barrel->RemoveAura(SPELL_BARREL_COSMETIC);
            l_Barrel->DespawnOrUnsummon(500);

            if (p_Interact->GetEntry() == NPC_OOK_BARREL)
            {
                if (Vehicle* l_Vehicle = p_Interact->GetVehicleKit())
                    l_Vehicle->RemoveAllPassengers(true);

                l_Barrel->RemoveAura(SPELL_BARREL_COSMETIC);
                p_Interact->ToCreature()->DespawnOrUnsummon(500);
            }
        }

        void TriggerSpells(constAuraEffectPtr aurEff)
        {
            PreventDefaultAction();

            Creature* l_Barrel = nullptr;
            if (GetUnitOwner())
                l_Barrel = GetUnitOwner()->ToCreature();

            if (l_Barrel)
            {
                // Ook-Ook
                if (Vehicle* l_Vehicle = l_Barrel->GetVehicleKit())
                if (l_Vehicle->IsVehicleInUse())
                {                    
                    Creature* l_OokOok = GetClosestCreatureWithEntry(l_Barrel, BOSS_OOKOOK, 1.0f);
                    if (l_OokOok)
                    {
                        if (AuraPtr aur = l_OokOok->GetAura(SPELL_BREW_EXPLOSION_BOSS))
                            aur->ModStackAmount(1);
                        else
                            DespawnBarrel(SPELL_BREW_EXPLOSION_BOSS, l_OokOok);
                    }
                }                   

                // Hozens
                Creature* l_Hozen = GetClosestCreatureWithEntry(l_Barrel, NPC_HOZEN_PARTY_ANIMAL, 1.0f);
                if (l_Hozen && l_Hozen->isAlive())
                {
                    if (AuraPtr aur = l_Hozen->GetAura(SPELL_BREW_EXPLOSION_HOZEN))
                        aur->ModStackAmount(1);
                    else
                        DespawnBarrel(SPELL_BREW_EXPLOSION_HOZEN, l_Hozen, false);
                }

                // Players
                std::list<Player*> l_PlayerList;
                GetPlayerListInGrid(l_PlayerList, l_Barrel, 1.0f);
                if (!l_PlayerList.empty())
                {
                    for (Player* l_Plr : l_PlayerList)
                    {
                        if (l_Plr->HasAura(SPELL_BARREL_RIDE) || !l_Plr->isAlive())
                            continue;
                        
                        if (AuraPtr aur = l_Plr->GetAura(SPELL_BREW_EXPLOSION_HOZEN))
                            aur->ModStackAmount(1);
                        else
                            DespawnBarrel(SPELL_BREW_EXPLOSION_HOZEN, l_Plr, false);
                        
                        break;
                    }
                }

                // Others Barrels
                std::list<Creature*> l_BarrelList;
                GetCreatureListWithEntryInGrid(l_BarrelList, l_Barrel, NPC_OOK_BARREL, 1.0f);
                if (!l_BarrelList.empty())
                {
                    for (Creature* l_OtherBarrel : l_BarrelList)
                    {
                        if (l_OtherBarrel != l_Barrel && l_OtherBarrel->HasAura(SPELL_BARREL_COSMETIC))
                            DespawnBarrel(SPELL_BREW_EXPLOSION_HOZEN);
                    }
                }

                // Walls
                float l_PosX = l_Barrel->GetPositionX() + 1.0f * cos(l_Barrel->GetOrientation());
                float l_PosY = l_Barrel->GetPositionY() + 1.0f * sin(l_Barrel->GetOrientation());

                if (!l_Barrel->IsWithinLOS(l_PosX, l_PosY, l_Barrel->GetPositionZ()))
                    DespawnBarrel(SPELL_BREW_EXPLOSION_HOZEN);
            }
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_brew_barrel_AuraScript::TriggerSpells, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_brew_barrel_AuraScript();
    }
};

class CheckBrewBarrelTargets
{
public:
    bool operator()(WorldObject* target) const
    {
        if (target->ToCreature())
        {
            if (target->GetEntry() == NPC_GENERAL_PURPOSE_BUNNY_JMF)
                return true;
            if (target->GetEntry() == NPC_GENERAL_PURPOSE_BUNNY_B)
                return true;
        }

        if (Player* player = target->ToPlayer())
        {
            if (player->IsFalling())
                return true;
        }
        return false;
    }
};

class AuraCheck
{
public:
    AuraCheck(uint32 spellId) : _spellId(spellId) {}

    bool operator()(WorldObject* unit)
    {
        return (!unit->ToUnit() || unit->ToUnit()->HasAura(_spellId));
    }

private:
    uint32 _spellId;
};

// 107351 - Brew Explosion on Hozen
class spell_brew_explosion_hozen : public SpellScriptLoader
{
public:
    spell_brew_explosion_hozen() : SpellScriptLoader("spell_brew_explosion_hozen") { }

    class spell_brew_explosion_hozen_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_brew_explosion_hozen_SpellScript);

        void FilterTargets(std::list<WorldObject*>& p_Targets)
        {
            p_Targets.remove_if(AuraCheck(SPELL_BARREL_RIDE));
            p_Targets.remove_if(CheckBrewBarrelTargets());

            if (Unit* caster = GetCaster())
            if (Creature* Ook = caster->FindNearestCreature(BOSS_OOKOOK, 3.0f, true))
            if (Vehicle* l_Vehicle = caster->GetVehicleKit())
            if (!l_Vehicle->IsVehicleInUse())             
                p_Targets.remove(Ook);
        }

        void HandleCast(SpellEffIndex effIndex)
        {
            if (!GetHitUnit())
                return;

            if (GetHitUnit()->GetEntry() == BOSS_OOKOOK)
            if (Unit* caster = GetCaster())            
            if (Vehicle* l_Vehicle = caster->GetVehicleKit())
            if (!l_Vehicle->IsVehicleInUse())
            PreventHitEffect(effIndex);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_brew_explosion_hozen_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_brew_explosion_hozen_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_brew_explosion_hozen_SpellScript::FilterTargets, EFFECT_2, TARGET_UNIT_SRC_AREA_ENTRY);
            OnEffectHitTarget += SpellEffectFn(spell_brew_explosion_hozen_SpellScript::HandleCast, EFFECT_2, SPELL_EFFECT_APPLY_AURA);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_brew_explosion_hozen_SpellScript();
    }
};

// 106784 - Brew Explosion on Ook Ook
class spell_brew_explosion_ookook : public SpellScriptLoader
{
public:
    spell_brew_explosion_ookook() : SpellScriptLoader("spell_brew_explosion_ookook") { }

    class spell_brew_explosion_ookook_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_brew_explosion_ookook_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.clear();
            if (Unit* caster = GetCaster())
            if (Creature* Ook = caster->FindNearestCreature(BOSS_OOKOOK, 3.0f, true))
            if (Vehicle* l_Vehicle = caster->GetVehicleKit())
            if (l_Vehicle->IsVehicleInUse())            
                targets.push_back(Ook);                           
        }

        void HandleCast(SpellEffIndex effIndex)
        {
            if (!GetHitUnit())
                return;

            if (GetHitUnit()->GetEntry() == BOSS_OOKOOK)
            if (Unit* caster = GetCaster())
            if (Vehicle* l_Vehicle = caster->GetVehicleKit())
            if (!l_Vehicle->IsVehicleInUse())
                PreventHitEffect(effIndex);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_brew_explosion_ookook_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_brew_explosion_ookook_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
            OnEffectHitTarget += SpellEffectFn(spell_brew_explosion_ookook_SpellScript::HandleCast, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_brew_explosion_ookook_SpellScript();
    }
};

void AddSC_boss_ook_ook()
{
	new boss_ook_ook();
    new npc_ook_hozen_hollerer();
    new npc_ook_barrel();
    new spell_ook_ook_going_bananas_summon();
    new spell_ook_ook_ground_pound_dmg();    
    new spell_barrel_toss_missile();            // 106847
    new spell_brew_barrel();                    // 106768
    new spell_brew_explosion_hozen();           // 107351
    new spell_brew_explosion_ookook();          // 106784
}
