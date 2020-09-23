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
    SAY_AGGRO          = 0, // Oh yeah!
    SAY_KILL           = 1, // You die!
    SAY_DEATH          = 2, // You have...turnip...for a head...
    SAY_FURLWIND       = 3, // Gonna spins around !
    SAY_CARROT_BREATH  = 4  // Urp...eats too many carrots...
};

#define ANN_BUNNIES "Hoptallus lets out a loud screech! The virmen are coming!"

enum Spells
{
    // Boss
    SPELL_CARROT_BREATH          = 112944, // Aura. Triggers 112945 dmg.
    SPELL_FURLWIND               = 112992, // Aura. Triggers 112993 dmg.
    SPELL_COSMETIC_EARTHQUAKE    = 114928,
    SPELL_HOPTALLUS_KEG_SCENE    = 114366,

    // NPCs
    SPELL_KEG_CARRY              = 131820, // Hopper carry keg.
    SPELL_BLINKING_EXPL_COSM     = 114287,
    SPELL_BLINKING_EXPL_FUSE     = 114290,
    SPELL_EXPLOSIVE_BREW         = 114291, // When Hopper reaches target.
    SPELL_HOPPER_ANIM_REPLACE    = 114284,
    SPELL_CARROT_DOOR            = 116005,

    SPELL_HAMMER_VISUAL          = 114530, // Bopper carry hammer + hammer ground visual.
    SPELL_HAMMER_FALLING         = 114531,
    SPELL_HAMMER_ARROW           = 114533,
    SPELL_SMASH_AURA             = 111662, // Hammer aura.
    SPELL_SMASH                  = 111666,  // Player cast spell on button click.
    SPELL_NIBBLER_VISUAL         = 128188
};

enum Events
{
    // Boss
    EVENT_CARROT_BREATH          = 1,
    EVENT_FURLWIND,
    EVENT_SUMMON_NPCS,
    EVENT_SET_COMBAT,
    EVENT_FURLWIND_ENDCAST,

    // NPCs
    EVENT_EXPLOSIVE_BREW,
    EVENT_CHECK_PLAYERS
};

Position const bunnySummonPosition     = { -713.955f, 1254.574f, 164.790f }; // Bunny adds summon position.
Position const hoptallusMovePosition   = { -692.524f, 1247.556f, 162.793f }; // Hoptallus move position after summoned.

uint32 const g_TrashEntries[3] = { NPC_HOPPLING, NPC_HOPPER, NPC_BOPPER };

/// Check if all trashes are done, so Hoptallus can appear
bool CheckTrashDone(Creature* p_Dead)
{
    for (uint8 l_Idx = 0; l_Idx < 3; ++l_Idx)
    {
        if (g_TrashEntries[l_Idx] == p_Dead->GetEntry())
        {
            std::list<Creature*> l_TrashList;
            GetCreatureListWithEntryInGrid(l_TrashList, p_Dead, g_TrashEntries[l_Idx], 50.0f);

            if (!l_TrashList.empty())
            {
                for (Creature* l_Trash : l_TrashList)
                {
                    // Found another trash with the same entry which is alive
                    if (l_Trash != p_Dead && l_Trash->isAlive())
                        return false;
                }
            }
        }
        else
        {
            // Found another trash alive
            if (GetClosestCreatureWithEntry(p_Dead, g_TrashEntries[l_Idx], 50.0f))
                return false;
        }
    }

    // No trash found
    return true;
}

class boss_hoptallus : public CreatureScript
{
    public :
        boss_hoptallus() : CreatureScript("boss_hoptallus") { }

        struct boss_hoptallus_AI : public BossAI
        {
            boss_hoptallus_AI(Creature* creature) : BossAI(creature, DATA_HOPTALLUS_EVENT), summons(me)
            {
                pInstance = creature->GetInstanceScript();
                creature->ApplySpellImmune(0, IMMUNITY_ID, 111666, true); // Immune to Smash.
                introStarted = false;
                introDone    = false;
            }

            EventMap events;
            InstanceScript* pInstance;
            SummonList summons;
            bool introStarted, introDone, IsCastingCarrotBreath, furlwind;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                summons.DespawnAll();

                if (pInstance)
                    pInstance->SetData(DATA_HOPTALLUS_EVENT, NOT_STARTED);

                if (Creature* l_Bunny = GetClosestCreatureWithEntry(me, NPC_GENERAL_PURPOSE_BUNNY_B, 50.0f))
                    l_Bunny->AddAura(SPELL_CARROT_DOOR, l_Bunny);

                _Reset();

                me->SetReactState(REACT_DEFENSIVE);

                if (!introDone)
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            }

            void MovementInform(uint32 type, uint32 id)
            {
                if (!me->isAlive() || type != POINT_MOTION_TYPE || id != 1)
                    return;
                
                me->SetFacingTo(hoptallusMovePosition.GetOrientation());
                me->SetOrientation(hoptallusMovePosition.GetOrientation());                
            }

            void EnterCombat(Unit* /*who*/)
            {
                Talk(SAY_AGGRO);
                IsCastingCarrotBreath = false;
                furlwind = false;

                if (pInstance)
                {
                    pInstance->SetData(DATA_HOPTALLUS_EVENT, IN_PROGRESS);
                    pInstance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
                }

                // Carrot Breath handled through EVENT_FURLWIND and the other way around.
                events.ScheduleEvent(EVENT_FURLWIND, urand(13000, 16000));
                events.ScheduleEvent(EVENT_SUMMON_NPCS, urand(48000, 52000));

                _EnterCombat();
            }

            void DoAction(int32 const p_Action)
            {
                if (p_Action == ACTION_HOPTALLUS_APPEARS)
                {
                    introDone = true;

                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);

                    if (Creature* l_Bunny = GetClosestCreatureWithEntry(me, NPC_GENERAL_PURPOSE_BUNNY_B, 50.0f))
                        l_Bunny->AddAura(SPELL_CARROT_DOOR, l_Bunny);

                    if (pInstance)
                    {
                        if (GameObject* l_Keg = pInstance->instance->GetGameObject(pInstance->GetData64(GAMEOBJECT_GIANT_BARREL)))
                            l_Keg->SetGoState(GO_STATE_ACTIVE);

                        me->GetMotionMaster()->MoveJump(hoptallusMovePosition.GetPositionX(), hoptallusMovePosition.GetPositionY(),
                            hoptallusMovePosition.GetPositionZ(), 20.0f, 5.0f, 10.0f, 1);
                    }

                    // Keg scene; should be played by spell 114366 but, doesn't work...
                    Map::PlayerList const &l_PlayerList = me->GetMap()->GetPlayers();
                    for (Map::PlayerList::const_iterator l_Itr = l_PlayerList.begin(); l_Itr != l_PlayerList.end(); ++l_Itr)
                        l_Itr->getSource()->PlayScene(SCENE_HOPTALLUS_KEG, l_Itr->getSource());

                    me->SetHomePosition(hoptallusMovePosition);
                }
            }

            void KilledUnit(Unit* victim)
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    Talk(SAY_KILL);
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();

                if (pInstance)
                {
                    pInstance->SetData(DATA_HOPTALLUS_EVENT, FAIL);
                    pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                }

                _EnterEvadeMode();
            }

            void JustDied(Unit* /*killer*/)
            {
                Talk(SAY_DEATH);
                summons.DespawnAll();

                if (pInstance)
                {
                    pInstance->SetData(DATA_HOPTALLUS_EVENT, DONE);
                    pInstance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove

                    if (GameObject* door = pInstance->instance->GetGameObject(pInstance->GetData64(GAMEOBJECT_GIANT_CARROT)))
                        door->SetGoState(GO_STATE_ACTIVE);

                    if (Creature* l_Dummy = GetClosestCreatureWithEntry(me, NPC_GENERAL_PURPOSE_BUNNY_B, 50.0f))
                        l_Dummy->RemoveAura(SPELL_CARROT_DOOR);
                }

                _JustDied();
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);

		        if (me->isInCombat())
                    summon->SetInCombatWithZone();
            }

            void UpdateAI(const uint32 diff)
            {
                if (furlwind && !me->HasAura(SPELL_FURLWIND))
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    furlwind = false;
                }

                if (!UpdateVictim() && introDone)
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_FURLWIND:
                            Talk(SAY_FURLWIND);                            
                           
                            me->SetReactState(REACT_PASSIVE); 
                            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                            DoCast(me, SPELL_FURLWIND);
                            me->AttackStop();
                            me->ClearUnitState(UNIT_STATE_CASTING);                            
                            furlwind = true;                                                   
                            events.ScheduleEvent(EVENT_CARROT_BREATH, 18000); 
                            events.ScheduleEvent(EVENT_FURLWIND_ENDCAST, 2500);
                            break;

                        case EVENT_FURLWIND_ENDCAST:
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                            me->GetMotionMaster()->MoveChase(me->getVictim());                           
                            break;

                        case EVENT_CARROT_BREATH:
                            Talk(SAY_CARROT_BREATH);
                            me->SetReactState(REACT_PASSIVE);                           
                            DoCast(me, SPELL_CARROT_BREATH);
                            events.ScheduleEvent(EVENT_FURLWIND, 25000); 
                            events.ScheduleEvent(EVENT_SET_COMBAT, 18000); 
                            break;

                        case EVENT_SET_COMBAT:                           
                            me->SetReactState(REACT_AGGRESSIVE);
                            
                            break;
                            
                        case EVENT_SUMMON_NPCS:
                            me->MonsterTextEmote(ANN_BUNNIES, NULL, true);
                            CallNPCS();
                            events.ScheduleEvent(EVENT_SUMMON_NPCS, urand(48000, 52000)); // Constant.
                            break;

                        default: break;
                    }
                }

                if (introDone && me->isInCombat())
                    DoMeleeAttackIfReady();
            }

        // Special functions here.
        private:
            void CallNPCS()
            {
                // 15 Hoppling, 7 Hopper, 5 Bopper.
                for (uint8 i = 0; i < 8; i++)
                    if (Creature* hoppling = me->SummonCreature(NPC_HOPPLING, bunnySummonPosition, TEMPSUMMON_MANUAL_DESPAWN))
                        hoppling->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 5.0f, 10.0f);

                for (uint8 i = 0; i < 4; i++)
                if (Creature* hopper = me->SummonCreature(NPC_HOPPER, bunnySummonPosition, TEMPSUMMON_MANUAL_DESPAWN))
                {
                    hopper->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 5.0f, 10.0f);
                    hopper->AI()->EnterCombat(hopper);
                }                        

                for (uint8 i = 0; i < 2; i++)
                    if (Creature* bopper = me->SummonCreature(NPC_BOPPER, bunnySummonPosition, TEMPSUMMON_MANUAL_DESPAWN))
                        bopper->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 5.0f, 10.0f);
            }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_hoptallus_AI(creature);
    }
};

// 60208 - Hopling
class npc_hopling : public CreatureScript
{
public:
    npc_hopling() : CreatureScript("npc_hopling") { }

    struct npc_hoplingAI : public ScriptedAI
    {
        npc_hoplingAI(Creature* p_Creature) : ScriptedAI(p_Creature)
        {
            m_Instance = p_Creature->GetInstanceScript();
        }

        InstanceScript* m_Instance;

        void EnterEvadeMode()
        {
            me->GetMotionMaster()->MoveTargetedHome();
        }
        
        void JustDied(Unit* p_Killer)
        {
            if (CheckTrashDone(me))
            {
                if (m_Instance)
                {
                    if (Creature* m_Hoptallus = m_Instance->instance->GetCreature(m_Instance->GetData64(DATA_HOPTALLUS)))
                        m_Hoptallus->AI()->DoAction(ACTION_HOPTALLUS_APPEARS);
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* p_Creature) const
    {
        return new npc_hoplingAI(p_Creature);
    }
};

class npc_hopper : public CreatureScript
{
    public :
        npc_hopper() : CreatureScript("npc_hopper") { }

        struct npc_hopper_AI : public ScriptedAI
        {
            npc_hopper_AI(Creature* creature) : ScriptedAI(creature), m_Vehicle(creature->GetVehicleKit())
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript* pInstance;
            EventMap events;
            Vehicle* m_Vehicle;
            bool explode;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                Reset();
            }

            void Reset()
            {
                explode = false;
                me->AddAura(SPELL_KEG_CARRY, me);
                events.Reset();

                if (m_Vehicle)
                {
                    if (!m_Vehicle->IsVehicleInUse())
                    {
                        if (Creature* l_Barrel = me->SummonCreature(NPC_EXPLOSIVE_BREW_BARREL, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()))
                        { 
                            l_Barrel->EnterVehicle(me, 0);
                            l_Barrel->ClearUnitState(UNIT_STATE_ONVEHICLE);
                            l_Barrel->CastSpell(l_Barrel, SPELL_BLINKING_EXPL_COSM, true);
                            l_Barrel->CastSpell(l_Barrel, SPELL_BLINKING_EXPL_FUSE, true);
                            l_Barrel->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                        }
                    }
                }
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_CHECK_PLAYERS, 1000);
            }

            void EnterEvadeMode()
            {                
                events.Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->DespawnOrUnsummon();
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void JustDied(Unit* p_Killer)
            {
                if (CheckTrashDone(me))
                {
                    if (pInstance)
                    {
                        if (Creature* m_Hoptallus = pInstance->instance->GetCreature(pInstance->GetData64(DATA_HOPTALLUS)))
                            m_Hoptallus->AI()->DoAction(ACTION_HOPTALLUS_APPEARS);
                    }
                }
                me->DespawnOrUnsummon(4000);
                DespawnExplosive();
            }

            void DespawnExplosive()
            {
                std::list<Creature*> explosive;
                GetCreatureListWithEntryInGrid(explosive, me, NPC_EXPLOSIVE_BREW_BARREL, 50.0f);

                if (explosive.empty())
                    return;

                for (std::list<Creature*>::iterator iter = explosive.begin(); iter != explosive.end(); ++iter)
                    if(!(*iter)->IsOnVehicle())
                        (*iter)->DespawnOrUnsummon(4000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (explode)
                if (Creature* clinger = me->FindNearestCreature(NPC_HOZEN_CLINGER, 5.0f, true))
                {
                    if (me->GetDistance(clinger) < 3.0f)
                    {
                        clinger->AI()->DoAction(ACTION_CLINGER);
                        return;
                    }                        
                }                   

                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_CHECK_PLAYERS:
                            if (Player* nearPlayer = me->FindNearestPlayer(1.0f, true))
                            {
                                if (nearPlayer->IsWithinDistInMap(me, 1.0f, true))
                                {
                                    DoCast(SPELL_EXPLOSIVE_BREW);
                                    explode = true;
                                }
                                else
                                    events.ScheduleEvent(EVENT_CHECK_PLAYERS, 1000);
                            }
                            else
                                events.ScheduleEvent(EVENT_CHECK_PLAYERS, 1000);
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_hopper_AI(creature);
        }
};

class npc_bopper : public CreatureScript
{
    public :
        npc_bopper() : CreatureScript("npc_bopper") { }

        struct npc_bopper_AI : public ScriptedAI
        {
            npc_bopper_AI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
            }

            InstanceScript* pInstance;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                Reset();
            }

            void Reset()
            {
                me->AddAura(SPELL_HAMMER_VISUAL, me);
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->DespawnOrUnsummon();
            }

            void JustDied(Unit* /*killer*/)
            {
                me->RemoveAura(SPELL_HAMMER_VISUAL);
                me->CastSpell(me, SPELL_HAMMER_FALLING, true);

                if (Unit* hammer = me->SummonCreature(NPC_BOPPER_HAMMER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 30000))
                {
                    hammer->ToCreature()->SetReactState(REACT_PASSIVE);
                    hammer->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                    hammer->AddAura(SPELL_HAMMER_VISUAL, hammer);
                    hammer->AddAura(SPELL_HAMMER_ARROW, hammer);
                }

                if (CheckTrashDone(me))
                {
                    if (pInstance)
                    {
                        if (Creature* m_Hoptallus = pInstance->instance->GetCreature(pInstance->GetData64(DATA_HOPTALLUS)))
                            m_Hoptallus->AI()->DoAction(ACTION_HOPTALLUS_APPEARS);
                    }
                }
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_bopper_AI(creature);
        }
};

class npc_hozen_clinger : public CreatureScript
{
public:
    npc_hozen_clinger() : CreatureScript("npc_hozen_clinger") { }

    struct npc_hozen_clinger_AI : public ScriptedAI
    {
        npc_hozen_clinger_AI(Creature* creature) : ScriptedAI(creature)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;

        void Reset()
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);
        }

        void DoAction(int32 const p_Action)
        {
            if (p_Action == ACTION_CLINGER)
            {
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_DISABLE_GRAVITY);
                me->GetMotionMaster()->MoveJump(me->GetPositionX(), me->GetPositionY(), 162.715f, 20.0f, 5.0f, 10.0f);
                me->CastWithDelay(1000, (Unit*)NULL, SPELL_DUSTY_EXPLOSION);
                me->DespawnOrUnsummon(10000);
                pInstance->DoCompleteAchievement(6400); //Achievement How Did He Get Up There?
            }
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hozen_clinger_AI(creature);
    }
};

class npc_hoptallus_bopper_hammer : public CreatureScript
{
    public:
        npc_hoptallus_bopper_hammer() : CreatureScript("npc_hoptallus_bopper_hammer") { }

        struct npc_hoptallus_bopper_hammerAI : public PassiveAI
        {
            npc_hoptallus_bopper_hammerAI(Creature* creature) : PassiveAI(creature) { }

            void OnSpellClick(Unit* clicker)
            {
                if (AuraPtr smash = clicker->AddAura(SPELL_SMASH_AURA, clicker))
                    smash->SetStackAmount(3);
                me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                me->DespawnOrUnsummon();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_hoptallus_bopper_hammerAI(creature);
        }
};

class PlayerCheck : public std::unary_function<Unit*, bool>
{
    public:
        explicit PlayerCheck(Unit* _caster) : caster(_caster) { }
        bool operator()(WorldObject* object)
        {
            return object->GetTypeId() != TYPEID_PLAYER;
        }

    private:
        Unit* caster;
};

class VerminCheck : public std::unary_function<Unit*, bool>
{
    public:
        explicit VerminCheck(Unit* _caster) : caster(_caster) { }
        bool operator()(WorldObject* object)
        {
            return (object->GetTypeId() == TYPEID_UNIT && 
                   (object->GetEntry() == NPC_BOPPER || object->GetEntry() == NPC_HOPPER || object->GetEntry() == NPC_HOPPLING)) ? true : false;
        }

    private:
        Unit* caster;
};

// Carrot Breath 112944
class spell_hoptallus_carrot_breath : public SpellScriptLoader
{
public:
    spell_hoptallus_carrot_breath() : SpellScriptLoader("spell_hoptallus_carrot_breath") { }

    class spell_hoptallus_carrot_breath_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_hoptallus_carrot_breath_AuraScript);

        void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
        {
            PreventDefaultAction(); // Don't apply stupid dummy aura.
        }

        void Rotate(constAuraEffectPtr aurEff)
        {
            if (Unit* l_Caster = GetCaster())
            {
                float l_Ori = l_Caster->GetOrientation() + M_PI / 12.0f;
                l_Caster->SetOrientation(l_Ori);
                l_Caster->SetFacingTo(l_Ori);
                float x, y, z;
                z = l_Caster->GetPositionZ();
                l_Caster->GetNearPoint2D(x, y, 5.0f, l_Caster->GetOrientation());
                if (Creature* temp = l_Caster->SummonCreature(NPC_BURST_TARGET, x, y, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 500))
                {
                    l_Caster->SetTarget(temp->GetGUID());                    
                    l_Caster->ToCreature()->AI()->AttackStart(temp);
                    l_Caster->StopMoving();
                }
            }
        }

        void Register()
        {
            OnEffectApply += AuraEffectApplyFn(spell_hoptallus_carrot_breath_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_hoptallus_carrot_breath_AuraScript::Rotate, EFFECT_1, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_hoptallus_carrot_breath_AuraScript();
    }
};

// Hoptallus Carrot breath damage 112945.
class spell_hoptallus_carrot_breath_damage : public SpellScriptLoader
{
public:
    spell_hoptallus_carrot_breath_damage() : SpellScriptLoader("spell_hoptallus_carrot_breath_damage") { }

    class spell_hoptallus_carrot_breath_damageSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hoptallus_carrot_breath_damageSpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {            
            if (Unit* l_Caster = GetCaster())
                targets.remove_if(PlayerCheck(l_Caster));
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hoptallus_carrot_breath_damageSpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CONE_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hoptallus_carrot_breath_damageSpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_CONE_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hoptallus_carrot_breath_damageSpellScript::FilterTargets, EFFECT_2, TARGET_UNIT_CONE_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hoptallus_carrot_breath_damageSpellScript();
    }
};

// Hoptallus Furlwind damage 112993.
class spell_hoptallus_furlwind_damage : public SpellScriptLoader
{
public:
    spell_hoptallus_furlwind_damage() : SpellScriptLoader("spell_hoptallus_furlwind_damage") { }

    class spell_hoptallus_furlwind_damageSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hoptallus_furlwind_damageSpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(PlayerCheck(GetCaster()));
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hoptallus_furlwind_damageSpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hoptallus_furlwind_damageSpellScript();
    }
};

// Hoptallus Hammer: Smash! 111666.
class spell_hoptallus_hammer_smash : public SpellScriptLoader
{
public:
    spell_hoptallus_hammer_smash() : SpellScriptLoader("spell_hoptallus_hammer_smash") { }

    class spell_hoptallus_hammer_smashSpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hoptallus_hammer_smashSpellScript);

        bool achievement = false;

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(VerminCheck(GetCaster()));
        }

        void HandleScript(SpellEffIndex /*effIndex*/)
        {
            Unit* caster = GetCaster();
            Unit* target = GetHitUnit();

            if (!caster || !target)
                return;

            if (AuraPtr smash = caster->GetAura(SPELL_SMASH_AURA))
            {
                int32 stacks = smash->GetStackAmount();
                if (stacks)
                {
                    if (stacks > 1)
                        smash->SetStackAmount(stacks - 1);
                    else
                        caster->RemoveAurasDueToSpell(SPELL_SMASH_AURA);
                }
            }

            const SpellInfo* SmashSpell = sSpellMgr->GetSpellInfo(SPELL_SMASH, caster->GetMap()->GetDifficulty());
            if (SmashSpell)
            {
                std::list<Creature*> verminList;
                GetCreatureListWithEntryInGrid(verminList, caster, NPC_BOPPER,   6.0f);
                GetCreatureListWithEntryInGrid(verminList, caster, NPC_HOPPER,   6.0f);
                GetCreatureListWithEntryInGrid(verminList, caster, NPC_HOPPLING, 6.0f);

                if (!verminList.empty())
                {
                    if (verminList.size() >= 100)
                        achievement = true;

                    for (auto vermin : verminList)
                    {
                        vermin->GetMotionMaster()->MoveJump(vermin->GetPositionX(), vermin->GetPositionY(),
                            vermin->GetPositionZ() + 20.0f, 20.0f, 5.0f, 10.0f);
                        
                        caster->DealDamage(vermin, vermin->GetHealth() - 1, NULL, SPELL_DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, SmashSpell);
                        vermin->SetReactState(REACT_PASSIVE);
                        vermin->ClearUnitState(UNIT_STATE_CASTING);
                        vermin->DespawnOrUnsummon(3000);
                    }                        
                }

            }
        }

        void Achievement()
        {
            if (achievement && GetCaster()->GetMap()->IsHeroic())
            if (InstanceScript* pInstance = GetCaster()->GetInstanceScript())
                pInstance->DoCompleteAchievement(6420); //Achievement Hopocalypse Now!
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hoptallus_hammer_smashSpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hoptallus_hammer_smashSpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
            OnEffectHitTarget += SpellEffectFn(spell_hoptallus_hammer_smashSpellScript::HandleScript, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
            AfterHit += SpellHitFn(spell_hoptallus_hammer_smashSpellScript::Achievement);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hoptallus_hammer_smashSpellScript();
    }
};

void AddSC_boss_hoptallus()
{
	new boss_hoptallus();
	new npc_hopper();
	new npc_bopper();
    new npc_hoptallus_bopper_hammer();
    new npc_hopling();                          // 60208
    new npc_hozen_clinger();                    //60276
    new spell_hoptallus_carrot_breath();
    new spell_hoptallus_carrot_breath_damage();
    new spell_hoptallus_furlwind_damage();
    new spell_hoptallus_hammer_smash();
}
