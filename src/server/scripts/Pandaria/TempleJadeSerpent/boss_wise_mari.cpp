/*
* Copyright (C) 2014-2017 RoG_WoW Source  <http://wow.rog.snet
*
* Dont Share The SourceCode
*
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "temple_of_jade_serpent.h"

enum eBoss
{
    BOSS_WASE_MARI = 1,
};

enum eSpells
{
    SPELL_BUBBLE_BURST              = 106612,
    SPELL_WATER_BUBBLE              = 106062,
    SPELL_WATER_BUBBLE_KNOCK_BACK   = 106079,
    SPELL_CALL_WATER                = 106526,
    SPELL_CORRUPTED_FOUTAIN         = 106518,
    SPELL_SHA_RESIDUE               = 106653,
    SPELL_HYDROLANCE_PRECAST        = 115220,
    SPELL_HYDROLANCE_PRE_DMG_BOTTOM = 106319,
    SPELL_HYDROLANCE_DMG_BOTTOM     = 106267,
    SPELL_HYDROLANCE_VISUAL         = 106055,
    SPELL_HYDROLANCE_PRE_DMG        = 106104,
    SPELL_HYDROLANCE_DMG            = 106105,
    SPELL_WASH_AWAY_CAST            = 106329,
    SPELL_WASH_AWAY_TRIGGER         = 106331,
    SPELL_WASH_AWAY_DUMMY           = 115575, //Used in table Spell_Linked_Spell with 106329
    SPELL_WASH_AWAY_DMG             = 106334,

    SPELL_ROOT                      = 42716,  // Self root forever, used when WATER BUBBLE is up.

    //Trigger Corrupted Waters NPC ID 65393
    SPELL_CORRUPTED_WATERS_TRIGGER  = 115165,
    SPELL_CORRUPTED_WATERS_DPS      = 115167,
};

enum eTexts
{
    TEXT_INTRO            = 0,
    TEXT_AGGRO            = 1,
    TEXT_BOSS_EMOTE_AGGRO = 2,
    TEXT_CALL_WATER       = 3,
    TEXT_PHASE_SWITCH     = 4,
    TEXT_DEATH            = 5,
    TEXT_KILL_PLAYER      = 6,
};

enum eEvents
{
    EVENT_CALL_WATER        = 1,
    EVENT_HYDROLANCE        = 2,
    EVENT_PRE_HYDROLANCE    = 3,
    EVENT_HYDROLANCE_START  = 4,
    EVENT_SWITCH_PHASE_TWO  = 5,
    EVENT_WASH_AWAY         = 6,
};

enum eCreatures
{
    MOB_TRASH_CORRUPTING_LIVING_WATER   = 59873,

    //BOSS
    CREATURE_CORRUPTEDS_WATERS          = 65393,
    CREATURE_CORRUPTING_LIVING_WATER    = 56511,
    CREATURE_FOUTAIN_TRIGGER            = 56586,
    CREATURE_CORRUPT_DROPLET            = 62358,
    CREATURE_HYDROLANCE_BOTTOM_TRIGGER  = 56542,
};

enum eTimers
{
    TIMER_CALL_WATTER           = 29000,
    TIMER_HYDROLANCE_START      = 10000,
    TIMER_PRE_HYDROLANCE        =  4300,
    TIMER_HYDROLANCE            =  5500,
    TIMER_SWITCH_PHASE_TWO      = 15000,
    TIMER_WASH_AWAY             =   125,
};

enum eAction
{
    ACTION_START_INTRO          = 1,
    ACTION_WATER_DEAD           = 2,
    ACTION_PHASE_2              = 3,
    ACTION_CORRUPTED_WATER      = 4,
};

enum hydrolancePhase
{
    HYDROLANCE_BOTTOM   = 1,
    HYDROLANCE_LEFT     = 2,
    HYDROLANCE_RIGHT    = 3,
};

enum Achievements
{
    // Defeat Wise Mari without being hit by Corrupted Water, Hydrolance, or Wash Away in Temple of the Jade Serpent on Heroic Difficulty.
    ACHI_HYDROPHOBIA = 6460,
};

static const float fountainTriggerPos[4][3] = 
{
    {1022.743f, -2544.295f, 173.7757f},
    {1023.314f, -2569.695f, 176.0339f},
    {1059.943f, -2581.648f, 176.1427f},
    {1075.231f, -2561.335f, 173.8758f},
};

static const float hydrolanceLeftTrigger[5][3] =
{
    {1061.411f, -2570.721f, 174.2403f},
    {1058.921f, -2573.487f, 174.2403f},
    {1055.910f, -2575.674f, 174.2403f},
    {1052.511f, -2577.188f, 174.2403f},
    {1048.871f, -2577.961f, 174.2403f},
};

static const float hydrolanceRightTrigger[5][3] =
{
    {1035.333f, -2573.693f, 174.2403f},
    {1032.795f, -2570.971f, 174.2403f},
    {1030.878f, -2567.781f, 174.2403f},
    {1029.667f, -2564.263f, 174.2403f},
    {1029.213f, -2560.569f, 174.2403f},
};

static const float preHydrolanceRightTrigger[3][3] =
{
    { 1039.41f, -2563.54f, 174.157f },
    { 1035.94f, -2564.91f, 174.157f },
    { 1033.03f, -2566.10f, 174.157f },
};

static const float preHydrolanceLeftTrigger[3][3] =
{
    { 1051.54f, -2567.76f, 174.157f },
    { 1052.83f, -2570.14f, 174.157f },
    { 1054.33f, -2572.46f, 174.162f },
};

static const float preHydrolanceBottomTrigger[6][3] =
{
    { 1049.31f, -2552.60f, 174.158f },
    { 1050.27f, -2549.91f, 174.158f },
    { 1051.25f, -2547.20f, 174.158f },
    { 1051.97f, -2544.24f, 170.194f },
    { 1052.73f, -2542.44f, 170.197f },
    { 1053.36f, -2540.13f, 170.204f },
};

const Position roomCenter = { 1046.941f, -2560.606f, 174.9552f, 4.33f };

bool giveAchievement;

class boss_wase_mari : public CreatureScript
{
    public:
        boss_wase_mari() : CreatureScript("boss_wase_mari") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_wise_mari_AI(creature);
        }

        struct boss_wise_mari_AI : public BossAI
        {
            boss_wise_mari_AI(Creature* creature) : BossAI(creature, BOSS_WASE_MARI)
            {
                intro = false;

                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_STUN, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FEAR, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FREEZE, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_POLYMORPH, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_HORROR, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SAPPED, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_CHARM, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DISORIENTED, true);
                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_CONFUSE, true);
            }

            bool intro;
            bool IsCastingWashAway;
            bool firstCastWashAway;
            uint8 phase;
            uint8 foutainCount;
            uint8 fountainActive;
            uint32 hydrolancePhase;
            uint32 uiTurnTimer;

            void Reset()
            {
                events.Reset();

                hydrolancePhase = 0;
                foutainCount = 0;
                fountainActive = 0;
                phase = 0;     
                uiTurnTimer = 0;

                IsCastingWashAway = false;
                firstCastWashAway = true;
                giveAchievement = true;

                me->RemoveAurasDueToSpell(SPELL_WATER_BUBBLE);
                me->RemoveAurasDueToSpell(SPELL_ROOT); 
                me->RemoveAurasDueToSpell(SPELL_WASH_AWAY_DUMMY);

                CleanAura(CREATURE_FOUTAIN_TRIGGER);
                CleanAura(CREATURE_CORRUPTEDS_WATERS);

                DespawnCreatures(CREATURE_CORRUPT_DROPLET);
                DespawnCreatures(CREATURE_CORRUPTING_LIVING_WATER);

                if (instance)
                    instance->SetBossState(BOSS_WISE_MARI_DATA, NOT_STARTED);
                _Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {
                me->AddAura(SPELL_ROOT, me);
                me->CastSpell(me, SPELL_WATER_BUBBLE, true);
                me->ClearUnitState(UNIT_STATE_CASTING);

                if (Creature* trigger = me->FindNearestCreature(CREATURE_CORRUPTEDS_WATERS, 200.0f, true))
                    trigger->AI()->DoAction(ACTION_CORRUPTED_WATER);

                Talk(TEXT_AGGRO);
                Talk(TEXT_BOSS_EMOTE_AGGRO);                
                phase = 1;
                hydrolancePhase = HYDROLANCE_BOTTOM; 
                events.ScheduleEvent(EVENT_CALL_WATER, 8000);
                events.ScheduleEvent(EVENT_HYDROLANCE_START, TIMER_HYDROLANCE_START);

                if (instance)
                    instance->SetBossState(BOSS_WISE_MARI_DATA, IN_PROGRESS);

                _EnterCombat();
            }

            void DoAction(const int32 action)
            {
                switch (action)
                {
                    // Intro
                case ACTION_START_INTRO:
                {
                    intro = true;
                    Talk(TEXT_INTRO);
                    me->SetInCombatWithZone();
                    break;
                }
                    
                case ACTION_WATER_DEAD:
                    if (foutainCount < 4)
                        foutainCount++;

                    if (phase < 2 && foutainCount == 4)
                        DoAction(ACTION_PHASE_2);
                    break;

                    // Evade
                case ACTION_PHASE_2:
                    phase = 2;
                    events.ScheduleEvent(EVENT_SWITCH_PHASE_TWO, TIMER_SWITCH_PHASE_TWO);
                    break;

                default: break;
                }
            }

            void EnterEvadeMode()
            {
                Reset();
                _EnterEvadeMode();
            }

            void KilledUnit(Unit* victim)
            {
                if (victim && victim->GetTypeId() == TYPEID_PLAYER)
                Talk(TEXT_KILL_PLAYER);
            }

            void SpellHitTarget(Unit* target, SpellInfo const* spell)
            {
                if (IsHeroic())
                {
                    if (target->GetTypeId() == TYPEID_PLAYER)
                    {
                        if (giveAchievement)
                            switch (spell->Id)
                        {
                            case SPELL_HYDROLANCE_PRE_DMG_BOTTOM:
                            case SPELL_HYDROLANCE_DMG_BOTTOM:
                            case SPELL_HYDROLANCE_PRE_DMG:
                            case SPELL_HYDROLANCE_DMG:
                            case SPELL_WASH_AWAY_DMG:
                                giveAchievement = false;
                                break;
                        }
                    }
                }
            }

            void JustDied(Unit* /*killer*/)
            {
                Talk(TEXT_DEATH);

                CleanAura(CREATURE_FOUTAIN_TRIGGER);
                CleanAura(CREATURE_CORRUPTEDS_WATERS);

                DespawnCreatures(CREATURE_CORRUPT_DROPLET);
                DespawnCreatures(CREATURE_CORRUPTING_LIVING_WATER);

                if (instance)
                {
                    instance->SetBossState(BOSS_WISE_MARI_DATA, DONE);
                    instance->SetData(DATA_WISE_MARI_EVENT, DONE);

                    if (Creature* bossLorewalker = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_LOREWALKER_STONESTEP)))
                    {
                        if (bossLorewalker->isDead())
                        {
                            if (GameObject* go = me->FindNearestGameObject(GO_DOOR_WISE_MARI, 100.0f))
                                go->SetGoState(GO_STATE_ACTIVE);

                            if (GameObject* goLore = ObjectAccessor::GetGameObject(*me, instance->GetData64(DATA_DOOR_LOREWALKER_STONSTEP)))
                                goLore->SetGoState(GO_STATE_ACTIVE);
                        }
                    }
                    if (giveAchievement && IsHeroic())
                        instance->DoCompleteAchievement(ACHI_HYDROPHOBIA);

                }

                if (IsHeroic())
                    DoCast(me, SPELL_PURIFIED_WATER);

                _JustDied();
            }

            void DespawnCreatures(uint32 entry)
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, entry, 50.0f);

                if (creatures.empty())
                    return;

                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    (*iter)->DespawnOrUnsummon();
            }

            void CleanAura(uint32 entry)
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, entry, 50.0f);

                if (creatures.empty())
                    return;

                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    (*iter)->RemoveAllAuras();
            }

            void UpdateOrientation()
            {
                float l_Ori = me->GetOrientation() - M_PI / 75.0f;
                me->SetOrientation(l_Ori);
                me->SetFacingTo(l_Ori);
                if (firstCastWashAway)
                {
                    firstCastWashAway = false;
                    me->SetFacingTo(3.520f);                    
                }
                float x, y, z;
                z = me->GetPositionZ();
                me->GetNearPoint2D(x, y, 15.0f, me->GetOrientation());
                if (Creature* temp = me->SummonCreature(NPC_BURST_TARGET, x, y, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 75))
                {
                    me->SetTarget(temp->GetGUID());
                    me->ToCreature()->AI()->AttackStart(temp);
                }
            }

            void UpdateAI(const uint32 diff)
            {

                if (!intro && me->FindNearestPlayer(25.0f, true))
                    DoAction(ACTION_START_INTRO);

                if (!intro)
                    return;

                if (instance && instance->IsWipe())
                {
                    EnterEvadeMode();
                    return;
                }
                if (IsCastingWashAway)
                {                    
                    if (uiTurnTimer <= diff)
                    {                       
                        UpdateOrientation();
                        uiTurnTimer = 70;
                    }
                    else uiTurnTimer -= diff;
                }

                if (!UpdateVictim())
                    return;

                events.Update(diff);

                // Wise Mari don't search target
                if (me->GetUInt32Value(UNIT_FIELD_TARGET)  && phase !=2)
                    me->SetUInt32Value(UNIT_FIELD_TARGET, 0);

                if (me->HasUnitState(UNIT_STATE_CASTING) && phase != 2)
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CALL_WATER:
                        {
                            if (phase != 1)
                                break;

                            Talk(TEXT_CALL_WATER);

                            if (fountainActive < 4)
                            {
                                std::list<Creature*> fountain;
                                GetCreatureListWithEntryInGrid(fountain, me, CREATURE_FOUTAIN_TRIGGER, 50.0f);

                                if (fountain.empty())
                                    return;

                                fountain.remove_if((AuraCheck(SPELL_CORRUPTED_FOUTAIN)));

                                WoWSource::Containers::RandomResizeList(fountain, 1);
                                if (Creature* target = fountain.front())
                                {
                                    me->CastSpell(target, SPELL_CALL_WATER, true);
                                    target->AddAura(SPELL_CORRUPTED_FOUTAIN, target);
                                    fountainActive++;
                                }                                    
                                
                            }
                            events.ScheduleEvent(EVENT_CALL_WATER, TIMER_CALL_WATTER + rand() % 6000);
                            break;
                        }

                        case EVENT_HYDROLANCE_START:
                        {
                            if (phase != 1)
                                break;

                            float facing = 0.00f;
                            events.ScheduleEvent(EVENT_PRE_HYDROLANCE, TIMER_PRE_HYDROLANCE);
                            events.ScheduleEvent(EVENT_HYDROLANCE, TIMER_HYDROLANCE);
                            switch (hydrolancePhase)
                            {
                                case HYDROLANCE_BOTTOM:
                                    {
                                        std::list<Creature*> trigger;
                                        me->GetCreatureListWithEntryInGrid(trigger,CREATURE_HYDROLANCE_BOTTOM_TRIGGER, 50.0f);
                                        for (auto itr : trigger)
                                            itr->CastSpell(itr, SPELL_HYDROLANCE_PRECAST, true);
                                        facing = 1.23f;
                                        break;
                                    }
                                case HYDROLANCE_RIGHT:
                                    for (int i = 0; i < 5; i++)
                                        me->CastSpell(hydrolanceRightTrigger[i][0], hydrolanceRightTrigger[i][1], hydrolanceRightTrigger[i][2], SPELL_HYDROLANCE_PRECAST, true);
                                    facing = 3.55f;
                                    break;
                                case HYDROLANCE_LEFT:
                                    for (int i = 0; i < 5; i++)
                                        me->CastSpell(hydrolanceLeftTrigger[i][0], hydrolanceLeftTrigger[i][1], hydrolanceLeftTrigger[i][2], SPELL_HYDROLANCE_PRECAST, true);
                                    facing = 5.25f;
                                    break;
                            }
                            me->CastSpell(me, SPELL_HYDROLANCE_VISUAL, false);
                            me->UpdatePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), facing);
                            me->SetFacingTo(facing);
                            break;
                        }

                        case EVENT_PRE_HYDROLANCE:
                        {
                            if (phase != 1)
                                break;
                            switch (hydrolancePhase)
                            {
                            case HYDROLANCE_BOTTOM:                            
                                for (int i = 0; i < 6; i++)
                                    me->CastWithDelayPos(preHydrolanceBottomTrigger[i][0], preHydrolanceBottomTrigger[i][1], preHydrolanceBottomTrigger[i][2], 200 * i, SPELL_HYDROLANCE_PRE_DMG_BOTTOM, true, false);
                                break;                            
                            case HYDROLANCE_RIGHT:
                                for (int i = 0; i < 3; i++)                                  
                                    me->CastWithDelayPos(preHydrolanceRightTrigger[i][0], preHydrolanceRightTrigger[i][1], preHydrolanceRightTrigger[i][2], 400 * i, SPELL_HYDROLANCE_PRE_DMG, true, false);                                
                                break;
                            case HYDROLANCE_LEFT:
                                for (int i = 0; i < 3; i++)
                                    me->CastWithDelayPos(preHydrolanceLeftTrigger[i][0], preHydrolanceLeftTrigger[i][1], preHydrolanceLeftTrigger[i][2], 400 * i, SPELL_HYDROLANCE_PRE_DMG, true, false);
                                break;
                            }                            
                            break;
                        }

                        case EVENT_HYDROLANCE:
                        {
                            if (phase != 1)
                                break;
                            switch (hydrolancePhase)
                            {
                                case HYDROLANCE_BOTTOM:
                                {
                                    std::list<Creature*> trigger;
                                    me->GetCreatureListWithEntryInGrid(trigger,CREATURE_HYDROLANCE_BOTTOM_TRIGGER, 50.0f);
                                    for (auto itr : trigger)
                                        itr->CastSpell(itr->GetPositionX(), itr->GetPositionY(), itr->GetPositionZ(), SPELL_HYDROLANCE_DMG_BOTTOM, true);
                                    break;
                                }
                                case HYDROLANCE_RIGHT:
                                    for (int i = 0; i < 5; i++)
                                        me->CastSpell(hydrolanceRightTrigger[i][0], hydrolanceRightTrigger[i][1], hydrolanceRightTrigger[i][2], SPELL_HYDROLANCE_DMG, true);
                                    break;
                                case HYDROLANCE_LEFT:
                                    for (int i = 0; i < 5; i++)
                                        me->CastSpell(hydrolanceLeftTrigger[i][0], hydrolanceLeftTrigger[i][1], hydrolanceLeftTrigger[i][2], SPELL_HYDROLANCE_DMG, true);
                                    break;
                            }

                            if( hydrolancePhase == HYDROLANCE_RIGHT)
                                hydrolancePhase = HYDROLANCE_BOTTOM;
                            else
                                hydrolancePhase++;

                            events.ScheduleEvent(EVENT_HYDROLANCE_START, TIMER_HYDROLANCE_START);
                            break;

                        }

                        case EVENT_SWITCH_PHASE_TWO:
                        {
                            if (phase !=2)
                                break;

                            Talk(TEXT_PHASE_SWITCH);

                            DoCast(me, SPELL_BUBBLE_BURST);
                            events.ScheduleEvent(EVENT_WASH_AWAY, 4000);
                            break;
                        }

                        case EVENT_WASH_AWAY:
                        {
                            if (phase !=2)
                                break;
                            me->SetReactState(REACT_PASSIVE);
                            me->RemoveAurasDueToSpell(SPELL_WATER_BUBBLE); 
                            me->SetInCombatWithZone();
                            UpdateOrientation();
                            me->CastSpell(me, SPELL_WASH_AWAY_CAST, true);
                            IsCastingWashAway = true;
                            uiTurnTimer = 250;                            
                            break;
                        }
                    }
                }

            }
        };

        private:
            class AuraCheck
            {
            public:
                AuraCheck(uint32 spellId) : _spellId(spellId) {}

                bool operator()(WorldObject* unit)
                {
                    return (!unit->ToCreature() || unit->ToCreature()->HasAura(_spellId));
                }

            private:
                uint32 _spellId;
            };
};

class mob_corrupt_living_water : public CreatureScript
{
    public:
        mob_corrupt_living_water() : CreatureScript("mob_corrupt_living_water") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_corrupt_living_water_AI(creature);
        }

        struct mob_corrupt_living_water_AI : public ScriptedAI
        {
            mob_corrupt_living_water_AI(Creature* creature) : ScriptedAI(creature)  {}

            bool died;

            void IsSummonedBy(Unit* summoner)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0f, true))
                    AttackStart(target);                
                died = false;
            }

            void DamageTaken(Unit* attacker, uint32 &damage)
            {
                if (me->GetEntry() == CREATURE_CORRUPTING_LIVING_WATER)
                {
                    if (damage >= me->GetHealth() && !died)
                    {
                        died = true;
                        damage = 0;
                        me->SetReactState(REACT_PASSIVE);
                        me->AttackStop();
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_DISABLE_MOVE);
                        me->SetStandState(UNIT_STAND_STATE_DEAD);
                        me->RemoveAllAuras();

                        for (int i = 0; i < 3; i++)
                        {
                            Position pos;
                            me->GetRandomNearPosition(pos, 4.0f);
                            me->SummonCreature(CREATURE_CORRUPT_DROPLET, pos, TEMPSUMMON_CORPSE_DESPAWN);
                        }

                        if (Creature* wise = me->FindNearestCreature(BOSS_WISE_MARI, 100.0f, true))
                            wise->AI()->DoAction(ACTION_WATER_DEAD);

                        me->CastSpell(me, SPELL_SHA_RESIDUE, true);
                        me->DespawnOrUnsummon(25000);
                    }
                }
            }

            void JustSummoned(Creature* summon)
            {
                if (summon->GetEntry() == CREATURE_CORRUPT_DROPLET)
                {
                    summon->SetReactState(REACT_AGGRESSIVE);
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.0f, true))                    
                        summon->AI()->AttackStart(target);                                    
                }
            }

            void JustDied(Unit* killer)
            {
                if (me->GetEntry() == MOB_TRASH_CORRUPTING_LIVING_WATER)
                {
                    for (int i = 0; i < 4; i++)
                    {
                        Position pos;
                        me->GetRandomNearPosition(pos, 4.0f);
                        Creature* droplet = me->SummonCreature(CREATURE_CORRUPT_DROPLET, pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60000);
                        if (!droplet)
                            continue;

                        if (Unit* unit = SelectTarget(SELECT_TARGET_RANDOM))
                            droplet->Attack(unit, true);
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
};

class npc_corrupted_waters : public CreatureScript
{
public:
    npc_corrupted_waters() : CreatureScript("npc_corrupted_waters") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_corrupted_watersAI(creature);
    }

    struct npc_corrupted_watersAI : public Scripted_NoMovementAI
    {
        npc_corrupted_watersAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);            
        }
        
        void DoAction(const int32 action)
        {
            if (action == ACTION_CORRUPTED_WATER)
            {
                if (Creature* wise = me->FindNearestCreature(BOSS_WISE_MARI, 200.0f, true))
                if (wise && wise->isAlive() && wise->isInCombat()) // Is dead / evaded.                
                    me->AddAura(SPELL_CORRUPTED_WATERS_TRIGGER, me);
                
                else if (me->HasAura(SPELL_CORRUPTED_WATERS_TRIGGER))
                    me->RemoveAura(SPELL_CORRUPTED_WATERS_TRIGGER);
            }
        }

        void SpellHitTarget(Unit* target, SpellInfo const* spell)
        {
            if (IsHeroic())
            {
                if (target->GetTypeId() == TYPEID_PLAYER)
                {
                    if (giveAchievement)
                        switch (spell->Id)
                    {
                        case SPELL_CORRUPTED_WATERS_DPS:
                            giveAchievement = false;
                            break;
                    }
                }
            }
        }
    };
};

//Called By Corrupted Waters Dps 115167
class spell_wise_mari_corrupted_waters_dmg : public SpellScriptLoader
{
public:
    spell_wise_mari_corrupted_waters_dmg() : SpellScriptLoader("spell_wise_mari_corrupted_waters_dmg") { }


    class spell_wise_mari_corrupted_waters_dmg_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_wise_mari_corrupted_waters_dmg_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (!GetCaster())
                return;

            if (targets.empty())
                return;

            std::list<Player*> PlayerList;
            GetCaster()->GetPlayerListInGrid(PlayerList, 30.0f);

            if (PlayerList.empty())
                return;

            targets.remove_if(PositionCheck(GetCaster(), PlayerList));

        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_wise_mari_corrupted_waters_dmg_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_wise_mari_corrupted_waters_dmg_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
        }

    private:
        class PositionCheck
        {
        public:
            PositionCheck(Unit* caster, std::list<Player*> plist) : _caster(caster), _PlayerList(plist) {}

            bool operator()(WorldObject* unit)
            {
                for (std::list<Player*>::const_iterator itr = _PlayerList.begin(); itr != _PlayerList.end(); ++itr)
                {                   
                    (*itr)->GetPosition(&pos);
                    if (((*itr)->GetDistance(roomCenter) < 20.00f && roomCenter.HasInArc(M_PI, &pos))
                        || (!roomCenter.HasInArc(M_PI, &pos) && (*itr)->GetDistance(roomCenter) < 14.00f))
                    {
                        if ((*itr)->GetPositionZ() > 174.05f && (*itr)->GetPositionZ() < 174.23f)
                            return false;
                    }

                    if ((*itr)->GetDistance(roomCenter) < 30.00f && (*itr)->GetPositionZ() > 170.19f && (*itr)->GetPositionZ() < 170.215f)
                        return false;
                }
                return true;
            }

        private:
            Unit* _caster;
            std::list<Player*> _PlayerList;
            Position pos;
        };
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_wise_mari_corrupted_waters_dmg_SpellScript();
    }
};

void AddSC_boss_wise_mari()
{
    new boss_wase_mari();
    new mob_corrupt_living_water();
    new npc_corrupted_waters(); //65393
    new spell_wise_mari_corrupted_waters_dmg(); //115167
}
