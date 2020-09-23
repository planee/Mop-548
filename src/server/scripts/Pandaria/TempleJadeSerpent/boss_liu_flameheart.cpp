/*
* Copyright (C) 2014-2017 RoG_WoW Source  <http://wow.rog.snet
*
* Dont Share The SourceCode
*
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "temple_of_jade_serpent.h"

#define TYPE_LIU_FLAMEHEART_STATUS 6
#define TYPE_IS_WIPE 7

enum eBosses
{
    BOSS_YU_LON,
    BOSS_TRIGGER,
};

enum eSpells
{
    //LIU FLAMEHEART Event:
    SPELL_POSSESSED_BY_SHA                  = 110164, //On Spawn
    SPELL_DUST_VISUAL                       = 110518, //On Spawn
    SPELL_SERPENT_DANCE_TRIGGER             = 106878,
    SPELL_SERPENT_STRIKE                    = 106823, 
    SPELL_SERPENT_WAVE_SUMMON_CONTROLLER    = 106982, 
    SPELL_SERPENT_KICK                      = 106856, 
    SPELL_JADE_ESSENCE                      = 106797, //AddAura on phase 2
    SPELL_JADE_SERPENT_DANCE_TRIGGER        = 106882,
    SPELL_JADE_SERPENT_STRIKE               = 106841,
    SPELL_JADE_SERPENT_WAVE_SUMMON_CONTROLLER=106995,
    SPELL_JADE_SERPENT_KICK                 = 106864,
    SPELL_DEATH_SIPHON                      = 116783,
    SPELL_SUMMON_JADE_SERPENT               = 106895,
    SPELL_JADE_SOUL                         = 106909,

    SPELL_JADE_SERPENT_HEALTH               = 106924,
    SPELL_SHARED_HEALTH                     = 114711,
    SPELL_TRANSFORM_VISUAL                  = 74620, //When the dragon is dead, cast this and remove the possess aura.
    SPELL_JADE_FIRE                         = 107045,
    SPELL_JADE_FIRE_MISSILE                 = 107098,
    SPELL_JADE_FIRE_SUMMON                  = 107103,
    SPELL_CLEANSING_BREATH                  = 132387,

    SPELL_JADE_SERPENT_WAVE_DMG             = 118540,

    SPELL_SERPENT_WAVE_SUMMON               = 118551,
    SPELL_SERPENT_WAVE_SUMMON_N             = 118549,
    SPELL_SERPENT_WAVE_SUMMON_E             = 106930,
    SPELL_SERPENT_WAVE_SUMMON_S             = 106928,
    SPELL_SERPENT_WAVE_SUMMON_W             = 106931,

    SPELL_JADE_SERPENT_WAVE_VISUAL          = 107002,
    SPELL_SERPENT_WAVE_VISUAL               = 106939,
    SPELL_SERPENT_WAVE_PERIODIC             = 106959,
    SPELL_JADE_SERPENT_WAVE_PERIODIC        = 107054,
    SPELL_JADE_SERPENT_WAVE_STALKER_PERIODIC= 106879,
    SPELL_JADE_SERPENT_WAVE                 = 119508,
    SPELL_SERPENT_WAVE                      = 106938,

    SPELL_JADE_FIRE_PERIODIC                = 107108,
    
    //Trash Mob
    SPELL_SHA_SCREECH                       = 122527,
    SPELL_SHADOWS_OF_DOUBT                  = 110099, 
    SPELL_SHATTERED_RESOLVE                 = 110125,
};

enum eStatus
{
    PHASE_1,
    PHASE_2,
    PHASE_3,
};

enum eAction
{
    ACTION_YU_LON_DONE      = 2,
    ACTION_START_COMBAT     = 3,
    ACTION_START_FLEE       = 4,
    ACTION_FINISH_FLEE      = 5,
    ACTION_INCREASE_COUNT   = 6,
};

enum eEvents
{
    EVENT_SERPENT_STRIKE        = 1,
    EVENT_SERPENT_KICK          = 2,
    EVENT_SERPENT_WAVE          = 3,

    EVENT_JADE_SERPENT_STRIKE   = 4,
    EVENT_JADE_SERPENT_KICK     = 5,
    EVENT_JADE_SERPENT_WAVE     = 6,

    EVENT_SUMMON_YULON          = 7,
    EVENT_JADE_FIRE             = 8,

    EVENT_LIU_FALL              = 9,
};

enum eTexts
{
    TALK_AGGRO_01,
    TALK_DEATH_01,
    TALK_EVENT_01,
    TALK_EVENT_02,
    TALK_INTRO_01,
    TALK_KILL_01,
    TALK_KILL_02,
};

enum eTextsWarriorDragons
{
    TALK_RUN_01 = 1,
    TALK_SHA_01 = 2,
};

enum eCreatures
{
    CREATURE_TRIGGER_WAVE    = 56789,
    CREATURE_SERPENT_WARRIOR = 62171,
};

class boss_liu_flameheart : public CreatureScript
{
    public:
        boss_liu_flameheart() : CreatureScript("boss_liu_flameheart") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_liu_flameheart_AI(creature);
        }

        struct boss_liu_flameheart_AI : public BossAI
        {
            boss_liu_flameheart_AI(Creature* creature) : BossAI(creature, BOSS_LIU_FLAMEHEART_DATA)
            {
                me->CastSpell(me, SPELL_POSSESSED_BY_SHA, false);
                status = PHASE_1;           

                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_STUN, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FEAR, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_ROOT, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FREEZE, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_POLYMORPH, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_HORROR, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SAPPED, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_CHARM, true);
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DISORIENTED, true);
                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_CONFUSE, true);
            }
            eStatus status;
            Creature* firstWave;
            Creature* secondWave;
            Creature* thirdWave;
            Creature* fourthWave;
            uint8 phase;            

            void Reset()
            {                
                status = PHASE_1;
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                me->SetReactState(REACT_DEFENSIVE);
                instance->SetBossState(DATA_LIU_FLAMEHEART_EVENT, NOT_STARTED);
                _Reset();
                me->RemoveAura(SPELL_JADE_SOUL);

                DespawnCreatures(NPC_JADE_FIRE);
                DespawnCreatures(NPC_YU_LON);
            }

            void DoAction(const int32 action)
            {
                switch (action)
                {
                case ACTION_JUMP_START:
                    me->CastWithDelay(3900, (Unit*)NULL, SPELL_DUST_VISUAL);
                    Talk(TALK_INTRO_01);                    
                    me->GetMotionMaster()->MoveJump(929.68f, -2560.80f, 180.06f, 20, 40);
                    me->SetHomePosition(929.68f, -2560.80f, 180.06f, me->GetOrientation());
                    break;
                case ACTION_YU_LON_DONE:
                    me->LowerPlayerDamageReq(me->GetHealth());
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->CastSpell(me, SPELL_TRANSFORM_VISUAL, false);

                    if (GameObject* doorLiu = me->FindNearestGameObject(GO_DOOR_LIU_FLAMEHEART, 100.0f))
                        doorLiu->SetGoState(GO_STATE_ACTIVE);
                    if (GameObject* doorLiu2 = me->FindNearestGameObject(GO_DOOR_LIU_FLAMEHEART_2, 100.0f))
                        doorLiu2->SetGoState(GO_STATE_ACTIVE);

                    if (Creature* bossSha = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_SHA_OF_DOUBT)))
                        bossSha->AI()->DoAction(ACTION_START_SHA_OF_DOUBT);

                    me->Kill(me);
                    if (instance)
                    {
                        instance->SetBossState(BOSS_LIU_FLAMEHEART_DATA, DONE);
                        instance->SetData(DATA_LIU_FLAMEHEART_EVENT, DONE);
                    }
                    break;
                }

            }

            void JustSummoned(Creature* summon)
            {
                if (summon->GetEntry() == CREATURE_TRIGGER_WAVE)
                {
                    if (phase == 0)
                    {
                        summon->CastSpell(summon, SPELL_SERPENT_WAVE_VISUAL, false);
                        summon->CastSpell(summon, SPELL_SERPENT_WAVE_PERIODIC, false);
                    }
                    if (phase == 1)
                    {
                        summon->CastSpell(summon, SPELL_JADE_SERPENT_WAVE_VISUAL, false);
                        summon->CastSpell(summon, SPELL_JADE_SERPENT_WAVE_PERIODIC, false);
                    }
                }
            }

            void KilledUnit(Unit* victim)
            {
                if (victim && victim->GetTypeId() == TYPEID_PLAYER)
                {
                    uint8 i = urand(0, 1);
                    if (i = 0)
                        Talk(TALK_KILL_01);
                    else
                        Talk(TALK_KILL_02);
                }
            }

            void EnterCombat(Unit* unit)
            {
                if (Creature* bossLorewalker = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_LOREWALKER_STONESTEP)))
                {
                    if (Creature* bossWise = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_WISE_MARI)))
                    {
                        if (bossWise->isAlive() && bossLorewalker->isAlive())
                        {
                            Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                            if (!PlayerList.isEmpty())
                            {
                                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                                {
                                    Player *player = i->getSource();
                                    if (player)                                    
                                        player->TeleportTo(870, 961.419f, -2463.21f, 180.582f, 4.81154f); //Teleport to the exit
                                    Reset();
                                }
                            }
                        }
                    }
                }

                Talk(TALK_AGGRO_01);
                phase = 0;
                events.ScheduleEvent(EVENT_SERPENT_STRIKE, 3000);
                events.ScheduleEvent(EVENT_SERPENT_KICK, 5000);
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

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);
                
                if (me->GetHealthPct() < 70.f && status == PHASE_1)
                {
                    me->AddAura(SPELL_JADE_ESSENCE, me);
                    phase = 1;
                    events.Reset();
                    events.ScheduleEvent(EVENT_JADE_SERPENT_STRIKE, 5000);
                    events.ScheduleEvent(EVENT_JADE_SERPENT_KICK, 10000);
                    Talk(TALK_EVENT_01);
                    status = PHASE_2;
                }
                if (me->GetHealthPct() < 30.f && status == PHASE_2)
                {
                    events.Reset();
                    phase = 2;
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->ApplySpellImmune(SPELL_JADE_SOUL, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, true);
                    me->ApplySpellImmune(SPELL_JADE_SOUL, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_MAGIC, true);
                    me->SetReactState(REACT_PASSIVE);
                    me->GetMotionMaster()->MoveTargetedHome();
                    events.ScheduleEvent(EVENT_SUMMON_YULON, 3000);
                    Talk(TALK_EVENT_02);
                    status = PHASE_3;
                }

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_SERPENT_STRIKE:
                        {
                            me->CastSpell(me->getVictim(), SPELL_SERPENT_STRIKE, false);
                            events.ScheduleEvent(EVENT_SERPENT_STRIKE, 10000);                           
                        }
                        break;
                    case EVENT_SERPENT_KICK:
                        me->CastSpell(me->getVictim(), SPELL_SERPENT_KICK, false);
                        events.ScheduleEvent(EVENT_SERPENT_KICK, 10000);
                        events.ScheduleEvent(EVENT_SERPENT_WAVE, 4000);
                        break;
                    case EVENT_SERPENT_WAVE:
                        {
                             float x = me->GetPositionX();
                             float y = me->GetPositionY();
                             float z = 179.821503f; // To prevent undermap           

                             if (firstWave = me->SummonCreature(CREATURE_TRIGGER_WAVE, x + 5.0f, y, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10 * IN_MILLISECONDS))
                                 firstWave->GetMotionMaster()->MovePoint(0, x + 100.0f, y, z);                                                                                        
                             if (secondWave = me->SummonCreature(CREATURE_TRIGGER_WAVE, x, y + 5.0f, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10 * IN_MILLISECONDS))
                                 secondWave->GetMotionMaster()->MovePoint(0, x, y + 100.0f, z);                                                                                         
                             if (thirdWave = me->SummonCreature(CREATURE_TRIGGER_WAVE, x - 5.0f, y, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10 * IN_MILLISECONDS))
                                 thirdWave->GetMotionMaster()->MovePoint(0, x - 100.0f, y, z);                                                                                      
                             if (fourthWave = me->SummonCreature(CREATURE_TRIGGER_WAVE, x, y - 5.0f, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10 * IN_MILLISECONDS))
                                 fourthWave->GetMotionMaster()->MovePoint(0, x, y - 100.0f, z);
                                                             
                        }
                        break;
                    case EVENT_JADE_SERPENT_STRIKE:
                        {
                            me->CastSpell(me->getVictim(), SPELL_JADE_SERPENT_STRIKE, false);

                            Map::PlayerList const& PlayerList = me->GetInstanceScript()->instance->GetPlayers();

                            if (!PlayerList.isEmpty())
                            {
                                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                                {
                                    Player* plr = i->getSource();
                                    if( !plr)
                                        continue;
                                    if (plr->GetDistance2d(me) < 10.f)
                                        plr->KnockbackFrom(me->GetPositionX(), me->GetPositionY(), 10, 10);
                                }
                            }
                            events.ScheduleEvent(EVENT_JADE_SERPENT_STRIKE, 10000);                            
                        }
                        break;
                    case EVENT_JADE_SERPENT_KICK:
                        me->CastSpell(me->getVictim(), SPELL_JADE_SERPENT_KICK, false);
                        events.ScheduleEvent(EVENT_JADE_SERPENT_KICK, 10000);
                        events.ScheduleEvent(EVENT_JADE_SERPENT_WAVE, 4000);
                        break;
                    case EVENT_JADE_SERPENT_WAVE:
                        {
                             float x = me->GetPositionX();
                             float y = me->GetPositionY();
                             float z = 179.821503f; // To prevent undermap    

                             if (firstWave = me->SummonCreature(CREATURE_TRIGGER_WAVE, x + 5.0f, y, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10 * IN_MILLISECONDS))
                                 firstWave->GetMotionMaster()->MovePoint(0, x + 100.0f, y, z);                                                                                       
                             if (secondWave = me->SummonCreature(CREATURE_TRIGGER_WAVE, x, y + 5.0f, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10 * IN_MILLISECONDS))
                                 secondWave->GetMotionMaster()->MovePoint(0, x, y + 100.0f, z);                                                                                         
                             if (thirdWave = me->SummonCreature(CREATURE_TRIGGER_WAVE, x - 5.0f, y, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10 * IN_MILLISECONDS))
                                 thirdWave->GetMotionMaster()->MovePoint(0, x - 100.0f, y, z);                                                                                      
                             if (fourthWave = me->SummonCreature(CREATURE_TRIGGER_WAVE, x, y - 5.0f, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 10 * IN_MILLISECONDS))
                                 fourthWave->GetMotionMaster()->MovePoint(0, x, y - 100.0f, z);
                                    
                        }
                        break;
                    case EVENT_SUMMON_YULON:
                        me->CastSpell(me, SPELL_SUMMON_JADE_SERPENT, false);
                        if (Creature* Yulon = me->FindNearestCreature(NPC_YU_LON, 50.0f, true))
                            me->CastSpell(Yulon, SPELL_JADE_SOUL, false);
                        me->AddUnitState(UNIT_STATE_ROOT);
                        break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class boss_yu_lon_tojs : public CreatureScript
{
    public:
        boss_yu_lon_tojs() : CreatureScript("boss_yu_lon_tojs") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_yu_lon_tojs_AI(creature);
        }

        struct boss_yu_lon_tojs_AI : public BossAI
        {
            boss_yu_lon_tojs_AI(Creature* creature) : BossAI(creature, BOSS_YU_LON)
            {
            }

            bool healthApplied;

            void IsSummonedBy(Unit* summoner)
            {
                events.Reset();
                healthApplied = false;
                if (instance)
                {
                    if (Creature* liu = me->FindNearestCreature(BOSS_LIU_FLAMEHEART, 500, true))
                    if (!healthApplied)
                    {
                        me->SetHealth(liu->GetMaxHealth() * 0.3f);
                        healthApplied = true;
                    }
                    me->SetObjectScale(0.1f);                                
                    me->SetInCombatWithZone();
                }
            }
            void EnterCombat(Unit* unit)
            {
                me->SetObjectScale(1.0f); // Spawn animation        
                events.ScheduleEvent(EVENT_JADE_FIRE, 100);
            }

            void JustDied(Unit* died)
            {
                summons.DespawnAll();
                me->CastSpell(me, SPELL_CLEANSING_BREATH, false);
                Creature* liu = me->FindNearestCreature(NPC_LIU_FLAMEHEART, 100.0f, true);
                if (liu && liu->GetAI())
                    liu->GetAI()->DoAction(ACTION_YU_LON_DONE);
                me->CastWithDelay(900, (Unit*)NULL, SPELL_TRANSFORM_VISUAL);
                me->DespawnOrUnsummon(500);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_JADE_FIRE:
                        me->CastSpell(SelectTarget(SELECT_TARGET_RANDOM), SPELL_JADE_FIRE_MISSILE, false);
                        events.ScheduleEvent(EVENT_JADE_FIRE, 1700);
                        break;
                    }
                }
                
                DoMeleeAttackIfReady();
            }
        };
};

class mob_trigger_liu_flameheart: public CreatureScript
{
    public:
        mob_trigger_liu_flameheart() : CreatureScript("mob_trigger_liu_flameheart") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_trigger_liu_flameheart_AI(creature);
        }

        struct mob_trigger_liu_flameheart_AI : public ScriptedAI
        {
            mob_trigger_liu_flameheart_AI(Creature* creature) : ScriptedAI(creature)
            {
                if (me->GetInstanceScript() && me->GetInstanceScript()->GetData(TYPE_LIU_FLAMEHEART_STATUS))
                    timer = 500;
                else
                    timer = 0;
            }
            uint32 timer;

            void UpdateAI(const uint32 diff)
            {
                if (timer <= diff)
                {
                    if (me->GetInstanceScript() && me->GetInstanceScript()->GetData(TYPE_LIU_FLAMEHEART_STATUS))
                    {
                        me->CastSpell(me, SPELL_JADE_FIRE_SUMMON, false);
                        timer = 1000;
                    }
                }
                else
                    timer -= diff;
            }
        };
};

class mob_minion_of_doubt: public CreatureScript
{
    public:
        mob_minion_of_doubt() : CreatureScript("mob_minion_of_doubt") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_minion_of_doubt_AI(creature);
        }

        struct mob_minion_of_doubt_AI : public ScriptedAI
        {
            mob_minion_of_doubt_AI(Creature* creature) : ScriptedAI(creature)
            {
            }
            EventMap events;

            void EnterCombat(Unit* unit)
            {
                events.ScheduleEvent(1, 2000);
                events.ScheduleEvent(2, 4000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case 1:
                        me->CastSpell(me->getVictim(), SPELL_SHADOWS_OF_DOUBT, false);
                        events.ScheduleEvent(1, 5000);
                        break;
                    case 2:
                        me->CastSpell(me->getVictim(), SPELL_SHATTERED_RESOLVE, false);
                        events.ScheduleEvent(2, 5000);
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };
};

class mob_lesser_sha: public CreatureScript
{
    public:
        mob_lesser_sha() : CreatureScript("mob_lesser_sha") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_lesser_sha_AI(creature);
        }

        struct mob_lesser_sha_AI : public ScriptedAI
        {
            mob_lesser_sha_AI(Creature* creature) : ScriptedAI(creature)
            {
            }
            EventMap events;

            void EnterCombat(Unit* unit)
            {
                events.ScheduleEvent(1, 2000);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case 1:
                        me->CastSpell(me->getVictim(), SPELL_SHA_SCREECH, false);
                        events.ScheduleEvent(1, 5000);
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };
};

//62171 Serpent Warrior
class mob_dragon_warriors : public CreatureScript
{
public:
    mob_dragon_warriors() : CreatureScript("mob_dragon_warriors") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_dragon_warriors_AI(creature);
    }

    struct mob_dragon_warriors_AI : public ScriptedAI
    {
        mob_dragon_warriors_AI(Creature* creature) : ScriptedAI(creature)
        {
            event_go = false;
        }
        EventMap events;
        bool event_go, inMove;
        uint8 fleeCount;

        void Reset()
        {
            if (me->FindNearestCreature(NPC_MINION_OF_DOUBT, 5.0f, false) && me->isAlive() && !inMove && fleeCount < 5 && !me->isInCombat())            
                DoAction(ACTION_START_FLEE);          
            else if (me->FindNearestCreature(NPC_MINION_OF_DOUBT, 5.0f, false) && me->isAlive() && !inMove && fleeCount >= 5 && !me->isInCombat())
                DoAction(ACTION_FINISH_FLEE);
        }
        
        void DoAction(const int32 action)
        {
            switch (action)
            {
            case ACTION_START_COMBAT:
                fleeCount = 0;
                event_go = true;
                inMove = false;
                if (Creature* sha = me->FindNearestCreature(NPC_MINION_OF_DOUBT, 10.0f, true))
                    AttackStart(sha);
                break;
            case ACTION_INCREASE_COUNT:
                ++fleeCount;
                break;
            case ACTION_START_FLEE:
                ExecuteAction(ACTION_INCREASE_COUNT);
                inMove = true;
                Talk(TALK_RUN_01);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                me->GetMotionMaster()->MovePoint(0, 950.975f, -2596.15f, 181.322f);
                break;
            case ACTION_FINISH_FLEE:
                Talk(TALK_SHA_01);
                if (GameObject* doorLiu2 = me->FindNearestGameObject(GO_DOOR_LIU_FLAMEHEART_2, 100.0f))
                {
                    inMove = true;
                    doorLiu2->SetGoState(GO_STATE_ACTIVE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                    me->GetMotionMaster()->MovePoint(1, 952.23f, -2491.77f, 180.372f);                    
                }
            }
        }

        void ExecuteAction(int32 action)
        {
            std::list<Creature*> creatures;
            GetCreatureListWithEntryInGrid(creatures, me, CREATURE_SERPENT_WARRIOR, 100.0f);
            if (creatures.empty())
                return;
            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                (*iter)->AI()->DoAction(action);
        }


        void MovementInform(uint32 type, uint32 id)
        {
            if (type == POINT_MOTION_TYPE)
            {
                switch (id)
                {
                case 0:
                    me->DespawnOrUnsummon();
                    break;
                case 1:
                    if (GameObject* doorLiu2 = me->FindNearestGameObject(GO_DOOR_LIU_FLAMEHEART_2, 100.0f))
                    {
                        doorLiu2->SetGoState(GO_STATE_READY);
                        me->DespawnOrUnsummon();
                    }
                    break;
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            
            if (!event_go)
            if(Player* player = me->FindNearestPlayer(15.0f, true)) 
            if (me->IsWithinLOSInMap(player) && me->FindNearestCreature(NPC_MINION_OF_DOUBT, 5.0f, true))                   
                ExecuteAction(ACTION_START_COMBAT);

            if (!UpdateVictim())
                return;
            
            events.Update(diff);

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_liu_flameheat()
{
    new boss_liu_flameheart();
    new boss_yu_lon_tojs();
    new mob_trigger_liu_flameheart();
    //Trashes
    new mob_minion_of_doubt();
    new mob_lesser_sha();
    new mob_dragon_warriors();
}