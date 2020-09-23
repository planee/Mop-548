/*
* Copyright (C) 2014-2017 RoG_WoW Source  <http://wow.rog.snet
*
* Dont Share The SourceCode
*
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "CreatureTextMgr.h"
#include "temple_of_jade_serpent.h"

#define TYPE_LOREWALKTER_STONESTEP 0
#define TIMER_INTENSITY 2000
#define TIMER_DISSIPATION TIMER_INTENSITY 

enum eBoss
{
    BOSS_SUN = 2,
    BOSS_ZAO_SUNSEEKER = 3,

    BOSS_STRIFE = 4,
    BOSS_PERIL = 5,
};
//Todo: Miss Spell Purple Floor when Haunting Sha is invoke and text when the event is complete
enum eSpells
{
    SPELL_MEDITATION            = 122715,
    SPELL_LOREWALKER_ALACRITY   = 122714, //To cast on players when event complete
    SPELL_SCROLL_FLOOR          = 107350, //On spawn
    SPELL_JADE_ENERGY           = 107384,
    SPELL_JADE_ENERGY_2         = 111452, //On spawn
    SPELL_ROOT_SELF             = 106822,
    SPELL_BLISTERING_VORTEX     = 67422,
    SPELL_EFFECT_CAST           = 42808,

    SPELL_SUNFIRE_RAYS          = 107223, //09 26 28 - 09 46 29 - 10 06 46
    SPELL_SUNFIRE_EXPLOSION     = 111737,
    SPELL_SUN                   = 107349,
    SPELL_GROW_LOW              = 104921,
    SPELL_EXTRACT_SHA           = 111764,
    SPELL_EXTRACT_SHA_2         = 111806,
    SPELL_EXTRACT_SHA_3         = 111807,
    SPELL_EXTRACT_SHA_4         = 111768,
    SPELL_SHOOT                 = 3018,
    SPELL_SHOOT_SUN             = 112084, //10 52 00 - 11 26 50 - 11 52 35
    SPELL_HELLFIRE_ARROW        = 113017,
    SPELL_SHA_CORRUPTION_2      = 120000,
    SPELL_STRIFER_CORRUPTION    = 115086, 
    SPELL_STRIFER_CORRUPTION_2  = 111237,
    SPELL_SHA_EXPLOSION_2       = 111812,  //Use when Haunting Sha Die, before Zao turn Evil

        //SCROLL SPELLS
    SPELL_DRAW_SHA_2            = 111393,
    SPELL_DRAW_SHA_3            = 111431,
    SPELL_SHA_BURNING           = 111588, //OnDied
    SPELL_SHA_EXPLOSION         = 111579, //OnDied and ussing by Haunting Sha when join with Zao
    SPELL_DEATH                 = 98391,  //OnDied

    SPELL_AGONY                 = 114571,
    SPELL_DISSIPATION           = 113379,
    SPELL_INTENSITY             = 113315,
    SPELL_ULTIMATE_POWER        = 113309,    

    //Mob Trash
    SPELL_BUBBLE_SPRAY          = 114811,
    SPELL_SONGBIRD_SERENADE     = 114826,
    SPELL_AERIALIST_KICK        = 114805,
    SPELL_THROWN_TORCH          = 114803,
    SPELL_SERRATED_SLASH        = 128051,
    SPELL_SHROUD_OF_GOLD        = 88023,
    SPELL_SLOW                  = 31589,
    SPELL_CLAW                  = 31289,
    SPELL_HAUNTING_GAZE         = 114646,
};

enum eEvents
{
    EVENT_INTRO_0 = 1,
    EVENT_INTRO_1 = 2,
    EVENT_INTRO_2 = 3,
    EVENT_INTRO_3 = 4,

    EVENT_SUN_0 = 5,
    EVENT_SUN_1 = 6,
    EVENT_SUN_2 = 7,
    EVENT_SUN_3 = 8,
    EVENT_SUN_4 = 9,
    EVENT_SUN_5 = 10,

    EVENT_ZAO_ENTER_COMBAT_1 = 11,
    EVENT_ZAO_ENTER_COMBAT_2 = 12,
    EVENT_ZAO_ATTACK         = 13,

    EVENT_STRIFE_0 = 14,
    EVENT_STRIFE_1 = 15,
    EVENT_STRIFE_2 = 16,
    EVENT_STRIFE_3 = 17,
    EVENT_STRIFE_4 = 18,

    EVENT_HAUNTING_GAZE = 19,
};

enum lAction
{
    ACTION_EVENT_COMPLETE               = 3,
    ACTION_ZAO_START_COMBAT             = 4,   
    ACTION_ZAO_ATTACK                   = 5,
    ACTION_START_BLUSTERING             = 6,
    ACTION_SUNFIRE_EXPLOSION            = 7,
    ACTION_SUN_ACTIVATE                 = 8,
    ACTION_SHA_DESTROYED                = 9,
    ACTION_ZAO_ENTER_COMBAT_CORRUPTED   = 10,
    ACTION_HAUNTING_ATTACK_ZAO          = 11,
};

enum Points
{
    POINT_SUN = 10,
};

enum eTexts
{
    EVENT_TALK_INTRO_0 = 0,
    EVENT_TALK_INTRO_1 = 1,
    EVENT_TALK_INTRO_2 = 2,
    EVENT_TALK_INTRO_3 = 3,

    EVENT_TALK_ZAO_APPEARS_0 = 4,
    EVENT_TALK_ZAO_APPEARS_1 = 5,
    EVENT_TALK_ZAO_APPEARS_2 = 6,
    EVENT_TALK_ZAO_APPEARS_3 = 7,
    EVENT_TALK_ZAO_APPEARS_4 = 8,

    EVENT_TALK_ZAO_ENTERS_COMBAT_0 = 9,

    EVENT_TALK_STRIFE_0 = 10,
    EVENT_TALK_STRIFE_1 = 11,
    EVENT_TALK_STRIFE_2 = 12,
    EVENT_TALK_STRIFE_3 = 13,
    EVENT_TALK_STRIFE_4 = 14,
};

enum eCreatures
{
    CREATURE_HAUNTING_SHA_1         = 58865,
    CREATURE_HAUNTING_SHA_2         = 58856,
};

static const float sunPos[5][3] =
{
    { 830.067f, -2466.660f, 179.240f }, // 1
    { 836.632f, -2467.159f, 178.139f }, // 2
    { 839.659f, -2469.159f, 182.496f }, // 3
    { 845.263f, -2469.179f, 178.209f }, // 4
    { 850.361f, -2474.320f, 178.196f }, // 5
};

static const float sunTriggerPos[5][3] =
{
    { 830.067f, -2466.660f, 176.320f }, // 1
    { 836.632f, -2467.159f, 176.320f }, // 2
    { 839.659f, -2469.159f, 176.320f }, // 3
    { 845.263f, -2469.179f, 176.320f }, // 4
    { 850.361f, -2474.320f, 176.320f }, // 5
};


class boss_lorewalker_stonestep : public CreatureScript
{
    public:
        boss_lorewalker_stonestep() : CreatureScript("boss_lorewalker_stonestep") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_lorewalker_stonestep_AI(creature);
        }

        struct boss_lorewalker_stonestep_AI : public BossAI
        {
            boss_lorewalker_stonestep_AI(Creature* creature) : BossAI(creature, BOSS_LOREWALKER_STONESTEP_DATA)
            {
                event_go = false;
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }

            bool event_go;
            bool osongSummoned;
            uint64 scrollGUID;
            uint8 shaDefeatCount;
            Creature* Strife;
            Creature* Peril;
            Creature* Osong;

            void Reset()
            {
                events.Reset();
                summons.DespawnAll();
                me->HandleEmoteCommand(EMOTE_STATE_NONE);
                event_go = false;
                osongSummoned = false;
                me->GetMotionMaster()->MoveTargetedHome();
                me->RemoveAura(SPELL_MEDITATION);
                instance->SetBossState(BOSS_LOREWALKER_STONESTEP_DATA, NOT_STARTED);
                if (!me->FindNearestCreature(NPC_SCROLL, 50.0f, true))
                    ForceReset(NPC_SCROLL);    

                me->SetWalk(false);

                ForceReset(NPC_OSONG);
                ForceReset(NPC_WISE_DRAGON);
                ForceReset(NPC_WELL);
                ForceReset(NPC_STRIFE_INI);
                ForceReset(NPC_HEROINE);
                ForceReset(NPC_MOON);
                ForceReset(NPC_SWIRLING_SUNFIRE);                

                DespawnCreatures(CREATURE_HAUNTING_SHA_1);
                DespawnCreatures(CREATURE_HAUNTING_SHA_2);
                DespawnCreatures(NPC_SUN);
                DespawnCreatures(NPC_SUN_TRIGGER);

                CleanAura(NPC_SWIRLING_SUNFIRE);                

                shaDefeatCount = 0;

                _Reset();
            }

            void DoAction(const int32 action)
            {
                switch (action)
                {
                case ACTION_SPAWN_STRIFE_AND_PERIL:
                    events.ScheduleEvent(EVENT_STRIFE_0, 500);
                    break;
                case ACTION_SPAWN_SUNS:
                    events.ScheduleEvent(EVENT_SUN_0, 500);
                    break;
                case ACTION_ZAO_START_COMBAT:
                    Talk(EVENT_TALK_ZAO_ENTERS_COMBAT_0);
                    break;
                case ACTION_SHA_DESTROYED:
                    {
                        if(++shaDefeatCount >= 5)
                        {
                            DoActionCreatureEntry(CREATURE_HAUNTING_SHA_1, ACTION_HAUNTING_ATTACK_ZAO);
                        }
                    break;
                    }
                case ACTION_EVENT_COMPLETE:
                    {
                        if (instance)
                        {
                            instance->SetBossState(BOSS_LOREWALKER_STONESTEP_DATA, DONE);
                            instance->SetData(DATA_LOREWALKER_STONESTEP_EVENT, DONE);

                            if (Creature* bossWise = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_WISE_MARI)))
                            {
                                if (bossWise->isDead())
                                {
                                    if (GameObject* go = me->FindNearestGameObject(GO_DOOR_LOREWALKER_STONSTEP, 100.0f))
                                        go->SetGoState(GO_STATE_ACTIVE);

                                    if (GameObject* gowise = ObjectAccessor::GetGameObject(*me, instance->GetData64(DATA_DOOR_WISE_MARI)))
                                        gowise->SetGoState(GO_STATE_ACTIVE);
                                }
                            }                            
                        }
                        Map::PlayerList const& PlayerList = me->GetMap()->GetPlayers();
                        if (!PlayerList.isEmpty())
                        {
                            for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                            {
                                if(Player* plr = i->getSource())
                                plr->CastSpell(plr, SPELL_LOREWALKER_ALACRITY, false);
                            }
                        }

                        DespawnCreatures(NPC_OSONG);
                        DespawnCreatures(NPC_SUN);
                        DespawnCreatures(NPC_SWIRLING_SUNFIRE);
                        DespawnCreatures(NPC_SUN_TRIGGER);

                        me->HandleEmoteCommand(EMOTE_STATE_NONE);
                        me->SetWalk(true);
                        me->GetMotionMaster()->MoveTargetedHome();
                        me->CastWithDelay(5000, (Unit*)NULL, SPELL_MEDITATION); 
                        me->DespawnOrUnsummon(20000);
                    }
                    break;
                }
            }

            void MoveInLineOfSight(Unit* who)
            {
                // If Lorewalker stonestep sees a player, launch the speech.
                if (!event_go && who->GetTypeId() == TYPEID_PLAYER)
                {
                    event_go = true;
                    events.ScheduleEvent(EVENT_INTRO_0, 500);
                    instance->SetData(TYPE_LOREWALKTER_STONESTEP, 1);
                }
            }

            void ForceReset(uint32 entry)
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);

                if (creatures.empty())
                    return;

                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                {
                    (*iter)->Respawn();
                    (*iter)->CastStop();
                    (*iter)->GetMotionMaster()->MoveTargetedHome();
                    (*iter)->RemoveAura(SPELL_DRAW_SHA_3);
                    (*iter)->RemoveAura(SPELL_DRAW_SHA_2); 
                }                    
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

            void DoActionCreatureEntry(uint32 entry, int32 action)
            {
                std::list<Creature*> creature;
                GetCreatureListWithEntryInGrid(creature, me, entry, 200.0f);
                if (!creature.empty())
                for (std::list<Creature*>::iterator iter = creature.begin(); iter != creature.end(); ++iter)
                if ((*iter)->AI())
                    (*iter)->AI()->DoAction(action);
            }

            void MovementInform(uint32 type, uint32 id)
            {
                if (type == POINT_MOTION_TYPE)
                {
                    switch (id)
                    {
                    case POINT_SUN:
                        me->SetFacingTo(1.239f);
                        me->HandleEmoteCommand(EMOTE_STATE_COWER);
                        break;  
                    }
                }
            }

            void SpellHit(Unit* /*who*/, const SpellInfo* spellInfo)
            {
                if (spellInfo->Id == SPELL_SUNFIRE_EXPLOSION)
                {
                    events.ScheduleEvent(EVENT_SUN_4, 2000);
                    if (Creature* Zao = me->FindNearestCreature(NPC_ZAO_SUNSEEKER, 50.0f, true))
                        Zao->AI()->DoAction(ACTION_ZAO_ATTACK);
                }
            }

            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);

                if (instance->IsWipe())
                    Reset();

                if (osongSummoned && Osong && Osong->isDead())
                    Reset();

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        // This is the first speech when Lorewalker stonestep sees you for the first time.
                        case EVENT_INTRO_0:
                            Talk(EVENT_TALK_INTRO_0); 
                            events.ScheduleEvent(EVENT_INTRO_1, 8019);
                            break;
                        case EVENT_INTRO_1:
                            Talk(EVENT_TALK_INTRO_1); 
                            events.ScheduleEvent(EVENT_INTRO_2, 16162);
                            break;
                        case EVENT_INTRO_2:
                            Talk(EVENT_TALK_INTRO_2); 
                            events.ScheduleEvent(EVENT_INTRO_3, 9578);
                            break;
                        case EVENT_INTRO_3:
                            Talk(EVENT_TALK_INTRO_3); 
                            break;
                        // End of the first speech.

                        // TRIAL: Speech when the scroll is destroyed.
                        case EVENT_SUN_0:
                            events.Reset();
                            me->RemoveAura(SPELL_ROOT_SELF);
                            instance->SetBossState(BOSS_LOREWALKER_STONESTEP_DATA, IN_PROGRESS);
                            me->HandleEmoteCommand(EMOTE_STATE_TALK);
                            Talk(EVENT_TALK_ZAO_APPEARS_0); 
                            
                            //Suns
                            for (int i = 0; i < 5; i++)
                                me->SummonCreature(NPC_SUN, sunPos[i][0], sunPos[i][1], sunPos[i][2], TEMPSUMMON_MANUAL_DESPAWN);
                            //Trigger of the suns
                            for (int i = 0; i < 5; i++)
                                me->SummonCreature(NPC_SUN_TRIGGER, sunTriggerPos[i][0], sunTriggerPos[i][1], sunTriggerPos[i][2], TEMPSUMMON_MANUAL_DESPAWN);
                            //Summon Zao.
                            if (Creature* sum = me->SummonCreature(NPC_ZAO_SUNSEEKER, 846.877f, -2449.110f, 175.044f, TEMPSUMMON_MANUAL_DESPAWN))
                            sum->SetFacingTo(4.450f);

                            DoActionCreatureEntry(NPC_SWIRLING_SUNFIRE, ACTION_START_BLUSTERING);

                            events.ScheduleEvent(EVENT_SUN_1, 5000);
                            break;
                        case EVENT_SUN_1:
                            Talk(EVENT_TALK_ZAO_APPEARS_1); 
                            events.ScheduleEvent(EVENT_SUN_2, 10000);
                            break;
                        case EVENT_SUN_2:
                            Talk(EVENT_TALK_ZAO_APPEARS_2); 
                            events.ScheduleEvent(EVENT_SUN_3, 9000);
                            break;
                        case EVENT_SUN_3:                        
                            DoActionCreatureEntry(NPC_SUN, ACTION_SUN_ACTIVATE);
                            DoActionCreatureEntry(NPC_SWIRLING_SUNFIRE, ACTION_SUNFIRE_EXPLOSION);

                            break;
                        case EVENT_SUN_4:
                            events.Reset();
                            me->HandleEmoteCommand(EMOTE_STATE_NONE);
                            Talk(EVENT_TALK_ZAO_APPEARS_4);
                            events.ScheduleEvent(EVENT_SUN_5, 1000);
                            break;
                        case EVENT_SUN_5:
                            me->SetWalk(false);
                            me->GetMotionMaster()->MovePoint(POINT_SUN, 833.457f, -2493.01f, 179.901f);
                            break;
                        // TRIAL: End of speech for destroyed scroll.

                        // ZAO: Speech when the scroll is destroyed.
                        case EVENT_STRIFE_0:
                        {
                            me->RemoveAura(SPELL_ROOT_SELF);
                            instance->SetBossState(BOSS_LOREWALKER_STONESTEP_DATA, IN_PROGRESS);
                            me->HandleEmoteCommand(EMOTE_STATE_TALK);
                            Talk(EVENT_TALK_STRIFE_0); 
                           
                            if (Strife = me->SummonCreature(NPC_STRIFE, 847.530f, -2469.184f, 174.960f, TEMPSUMMON_MANUAL_DESPAWN))
                                Strife->SetFacingTo(1.525f);
                            if (Peril = me->SummonCreature(NPC_PERIL, 836.906f, -2465.859f, 174.960f, TEMPSUMMON_MANUAL_DESPAWN))
                                Peril->SetFacingTo(1.014f);
                            
                            if (Osong = me->SummonCreature(NPC_OSONG, 847.414f, -2451.13f, 174.961f, TEMPSUMMON_MANUAL_DESPAWN))
                            {
                                Osong->AddAura(SPELL_ROOT_SELF, Osong);
                                Osong->SetFacingTo(4.39f);             
                                osongSummoned = true;
                            }
                            events.ScheduleEvent(EVENT_STRIFE_1, 9641);
                         }
                            break;
                        case EVENT_STRIFE_1:
                            me->HandleEmoteCommand(EMOTE_STATE_TALK);
                            Talk(EVENT_TALK_STRIFE_1); 
                            me->SetWalk(true);
                            me->GetMotionMaster()->MovePoint(0, 826.744f, -2451.49f, 176.303f);
                            events.ScheduleEvent(EVENT_STRIFE_2, 8011);
                            break;
                        case EVENT_STRIFE_2:
                            Talk(EVENT_TALK_STRIFE_2); 
                            events.ScheduleEvent(EVENT_STRIFE_3, 5092);
                            break;
                        case EVENT_STRIFE_3:
                            {
                                Talk(EVENT_TALK_STRIFE_3); 
                                me->SetFacingTo(5.91f);
                                events.ScheduleEvent(EVENT_STRIFE_4, 6014);
                            }
                            break;
                        case EVENT_STRIFE_4:                            
                            Talk(EVENT_TALK_STRIFE_4); 
                            if (Player* player = me->FindNearestPlayer(200.0f, true))
                                Osong->setFaction(player->getFaction());
                            
                            Osong->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            Strife->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            Peril->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            Osong->RemoveAura(SPELL_ROOT_SELF);
                            Strife->RemoveAura(SPELL_ROOT_SELF);
                            Peril->RemoveAura(SPELL_ROOT_SELF);
                            Strife->SetReactState(REACT_AGGRESSIVE);
                            Peril->SetReactState(REACT_AGGRESSIVE);
                            sCreatureTextMgr->SendChat(Osong, 0, 0);
                            if (Peril)
                                Osong->AI()->AttackStart(Peril);
                            me->HandleEmoteCommand(EMOTE_STATE_NONE);
                            break;
                        // ZAO: End of speech for destroyed scroll.
                    }
                }

            }
        };
};

class mob_sun : public CreatureScript
{
    public:
        mob_sun() : CreatureScript("mob_sun") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_sun_AI(creature);
        }

        struct mob_sun_AI : public BossAI
        {
            mob_sun_AI(Creature* creature) : BossAI(creature, BOSS_SUN)
            {
                me->CastSpell(me, SPELL_SUN, false);
                me->CastSpell(me, SPELL_GROW_LOW, false);
                me->AddUnitState(UNIT_STATE_ROOT);
                me->SetDisableGravity(true);
                me->SetOrientation(1.239f);
                creature->SetReactState(REACT_PASSIVE);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }

            void DoAction(const int32 action)
            {
                switch (action)
                {
                case ACTION_SUN_ACTIVATE:
                    me->SetInCombatWithZone();
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    events.ScheduleEvent(1, 2000);
                    break;
                }
            }

            void JustDied(Unit* killer)
            {
                //summon one haunting sha.
                me->CastSpell(me->GetPositionX(), me->GetPositionY(), 174.95f, SPELL_EXTRACT_SHA_2, true);
            }

            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case 1:
                        Unit* target = SelectTarget(SELECT_TARGET_RANDOM);
                        if (target != nullptr)
                            me->CastSpell(target, SPELL_SUNFIRE_RAYS, true);
                        events.ScheduleEvent(1, 5000);
                        break;
                    }
                }
            }
        };
};

class mob_zao : public CreatureScript
{
    public:
        mob_zao() : CreatureScript("mob_zao") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_zao_AI(creature);
        }

        struct mob_zao_AI : public BossAI
        {
            mob_zao_AI(Creature* creature) : BossAI(creature, BOSS_ZAO_SUNSEEKER)
            {
                isCorrupted = false;
                CountShaExplotion = 0;
                me->AddUnitState(UNIT_STATE_ROOT);

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
            std::list<Creature*> suns;

            bool isCorrupted;
            uint8 CountShaExplotion;

            void DamageTaken(Unit* attacker, uint32&)
            {
                if (attacker->ToCreature()
                    && (attacker->ToCreature()->GetEntry() == CREATURE_HAUNTING_SHA_1
                    || attacker->ToCreature()->GetEntry() == CREATURE_HAUNTING_SHA_2))
                {
                    me->CastSpell(me, SPELL_SHA_EXPLOSION, false);
                    ++CountShaExplotion;
                    attacker->ToCreature()->ForcedDespawn();
                }
            }

            void JustDied(Unit* killer)
            {
                if (!instance)
                    return;

                if (Creature* loreWalker = me->GetMap()->GetCreature(me->GetInstanceScript()->GetData64(BOSS_LOREWALKER_STONESTEP)))
                if (loreWalker->GetAI())
                    loreWalker->GetAI()->DoAction(ACTION_EVENT_COMPLETE);
            }

            void DoAction(const int32 action)
            {
                switch (action)
                {
                case ACTION_ZAO_ATTACK:
                    me->SetInCombatWithZone();
                    events.ScheduleEvent(EVENT_ZAO_ENTER_COMBAT_1, 1000);
                    events.ScheduleEvent(EVENT_ZAO_ATTACK, 1000);
                    break;
                case ACTION_ZAO_ENTER_COMBAT_CORRUPTED:
                    {
                        events.Reset();
                        me->setFaction(14);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        me->CastSpell(me, SPELL_SHA_CORRUPTION_2, false);
                        me->SetFullHealth();
                        events.ScheduleEvent(EVENT_ZAO_ENTER_COMBAT_2, 1000);
                     break;
                    }
                }
            }

            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);

                if (!isCorrupted && CountShaExplotion >= 5)
                {
                    isCorrupted = true;
                    DoAction(ACTION_ZAO_ENTER_COMBAT_CORRUPTED);
                    return;
                }

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    // Speech of Zao entering combat
                    case EVENT_ZAO_ENTER_COMBAT_1: 
                        events.CancelEvent(EVENT_ZAO_ENTER_COMBAT_1);
                        me->MonsterYell("I can allow this no longer!",0,0);
                        break;
                    case EVENT_ZAO_ENTER_COMBAT_2: 
                        Talk(EVENT_TALK_INTRO_0);
                        events.ScheduleEvent(EVENT_ZAO_ATTACK, 1000);
                        break;
                    // End of speech of Zao entering combat
                    case EVENT_ZAO_ATTACK:
                        if (isCorrupted)
                        {
                            Unit* target = SelectTarget(SELECT_TARGET_RANDOM);
                            if (target != nullptr)
                            {
                                me->CastSpell(target, SPELL_SHOOT, true);
                                me->CastSpell(target, SPELL_HELLFIRE_ARROW, true);
                            }
                               
                            events.ScheduleEvent(EVENT_ZAO_ATTACK, 3000);
                        }
                        else
                        {
                            suns.clear();
                            GetCreatureListWithEntryInGrid(suns, me, NPC_SUN, 50.0f);
                            if (!suns.empty())
                            {
                                uint32 rand = urand(0, suns.size());
                                Creature* target = NULL;
                                for (auto sun : suns)
                                {
                                    if (rand == 0)
                                    {
                                        target = sun;
                                        break;
                                    }
                                    --rand;
                                }
                                if (target)
                                    me->CastSpell(target, SPELL_SHOOT_SUN, false);
                            }
                                events.ScheduleEvent(EVENT_ZAO_ATTACK, 3000);
                        }                        
                        break;
                    }
                }
            }
        };
};

// 58815 
class mob_sunfire : public CreatureScript
{
public:
    mob_sunfire() : CreatureScript("mob_sunfire") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_sunfire_AI(creature);
    }

    struct mob_sunfire_AI : public ScriptedAI
    {
        mob_sunfire_AI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
            me->AddUnitState(UNIT_STATE_ROOT);
        }

        void DoAction(const int32 action)
        {
            if (action == ACTION_START_BLUSTERING)
                me->CastSpell(me, SPELL_BLISTERING_VORTEX, false); //Blistering Vortex, Fire vortex display

            if (action == ACTION_SUNFIRE_EXPLOSION)
                me->CastSpell(me, SPELL_SUNFIRE_EXPLOSION, true);
        }
    };
};

// 58865 - haunting sha pursuing zao
class mob_haunting_sha : public CreatureScript
{
public:
    mob_haunting_sha() : CreatureScript("mob_haunting_sha") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_haunting_sha_AI(creature);
    }

    struct mob_haunting_sha_AI : public ScriptedAI
    {
        mob_haunting_sha_AI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            me->setFaction(14);
            events.Reset();
        }

        void EnterCombat(Unit* unit)
        {
            events.ScheduleEvent(EVENT_HAUNTING_GAZE, 1000);
        }

        void DoAction(const int32 action)
        {
            if (!instance)
                return;

            if (action == ACTION_HAUNTING_ATTACK_ZAO)
            {
                me->Respawn();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                if (Creature* zao = me->GetMap()->GetCreature(me->GetInstanceScript()->GetData64(NPC_ZAO_SUNSEEKER)))
                {
                    me->getThreatManager().addThreat(zao, 1000000.f);
                    me->AI()->AttackStart(zao);
                }
            }
        }

        void JustDied(Unit* killer)
        {
            if (Creature* loreWalker = me->GetMap()->GetCreature(me->GetInstanceScript()->GetData64(BOSS_LOREWALKER_STONESTEP)))
            if (loreWalker->GetAI())
                loreWalker->GetAI()->DoAction(ACTION_SHA_DESTROYED);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!me->getVictim())
            {
                Map::PlayerList const& PlayerList = me->GetInstanceScript()->instance->GetPlayers();

                if (!PlayerList.isEmpty())
                {
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        Player* plr = i->getSource();
                        if (!plr)
                            continue;
                        me->getThreatManager().addThreat(plr, 1.0f);
                    }
                }
                me->AI()->AttackStart(SelectTarget(SELECT_TARGET_RANDOM));
            }

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_HAUNTING_GAZE:
                    if (me->getVictim() && me->getVictim()->GetTypeId() == TYPEID_PLAYER)
                        me->CastSpell(me->getVictim(), SPELL_HAUNTING_GAZE, false);
                    events.ScheduleEvent(EVENT_HAUNTING_GAZE, 2000);
                    break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

class mob_strife : public CreatureScript
{
    public:
        mob_strife() : CreatureScript("mob_strife") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_strife_AI(creature);
        }

        struct mob_strife_AI : public BossAI
        {
            mob_strife_AI(Creature* creature) : BossAI(creature, BOSS_STRIFE)
            {
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

                me->setFaction(14);
                timer_intensity = TIMER_INTENSITY;
                timer_dissipation = TIMER_DISSIPATION;
                countIntensity = 0;
                hasBeenHit = false;
                creature->AddAura(SPELL_STRIFER_CORRUPTION, creature);
                creature->AddAura(SPELL_STRIFER_CORRUPTION_2, creature);
                creature->AddAura(SPELL_ROOT_SELF, creature);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                creature->SetReactState(REACT_PASSIVE);
            }
            uint32 timer_dissipation;
            uint32 timer_intensity;
            int32 countIntensity;
            bool hasBeenHit;

            void DamageTaken(Unit* unit, uint32&)
            {
                timer_dissipation = TIMER_DISSIPATION;
                hasBeenHit = true;
            }

            void EnterCombat(Unit* unit)
            {
                events.ScheduleEvent(1, 1000);
            }

            void KilledUnit(Unit* victim)
            {
                if (victim->GetEntry() == NPC_OSONG)
                if (Creature* lorewalker = me->FindNearestCreature(BOSS_LOREWALKER_STONESTEP, 100.0f, true))
                    lorewalker->AI()->Reset();
            }

            void JustDied(Unit* /*killer*/)
            {
                if (Creature* Peril = me->FindNearestCreature(NPC_PERIL, 100.0f, false))
                if (Creature* lorewalker = me->FindNearestCreature(BOSS_LOREWALKER_STONESTEP, 100.0f, true))
                    lorewalker->AI()->DoAction(ACTION_EVENT_COMPLETE);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (timer_dissipation <= diff)
                {
                    me->RemoveAuraFromStack(SPELL_INTENSITY);
                    if (!me->HasAura(SPELL_INTENSITY))
                        me->AddAura(SPELL_DISSIPATION, me);
                    timer_dissipation = TIMER_DISSIPATION;
                    --countIntensity;
                    if (countIntensity == -10)
                        countIntensity = -10;
                }
                else
                    timer_dissipation -= diff;

                if (timer_intensity <= diff)
                {
                    if (hasBeenHit)
                    {
                        me->RemoveAuraFromStack(SPELL_DISSIPATION);
                        if (!me->HasAura(SPELL_DISSIPATION))
                            me->AddAura(SPELL_INTENSITY, me);
                        ++countIntensity;

                        if (countIntensity == 10)
                        {
                            me->CastSpell(me, SPELL_ULTIMATE_POWER, false);
                            me->RemoveAura(SPELL_INTENSITY);
                        }
                        if (countIntensity > 10)
                            countIntensity = 10;
                    }
                    hasBeenHit = false;
                    timer_intensity = TIMER_INTENSITY;
                }
                else
                    timer_intensity -= diff;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case 1:
                        if (!me->getVictim())
                            return;
                        me->CastSpell(me->getVictim(), SPELL_AGONY, false);
                        events.ScheduleEvent(1, 2000);
                        break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class mob_peril : public CreatureScript
{
    public:
        mob_peril() : CreatureScript("mob_peril") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_peril_AI(creature);
        }

        struct mob_peril_AI : public BossAI
        {
            mob_peril_AI(Creature* creature) : BossAI(creature, BOSS_PERIL)
            {
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

                me->setFaction(14);
                timer_intensity = TIMER_INTENSITY;
                timer_dissipation = TIMER_DISSIPATION;
                countIntensity = 0;
                hasBeenHit = false; 
                creature->AddAura(SPELL_STRIFER_CORRUPTION, creature);
                creature->AddAura(SPELL_STRIFER_CORRUPTION_2, creature);
                creature->AddAura(SPELL_ROOT_SELF, creature);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                creature->SetReactState(REACT_PASSIVE);
            }
            uint32 timer_dissipation;
            uint32 timer_intensity;
            int32 countIntensity;
            bool hasBeenHit;

            void DamageTaken(Unit* unit, uint32&)
            {
                timer_dissipation = TIMER_DISSIPATION;
                hasBeenHit = true;
            }

            void EnterCombat(Unit* unit)
            {
                events.ScheduleEvent(1, 1000);
            }

            void KilledUnit(Unit* victim)
            {
                if (victim->GetEntry() == NPC_OSONG)
                if (Creature* lorewalker = me->FindNearestCreature(BOSS_LOREWALKER_STONESTEP, 100.0f, true))
                    lorewalker->AI()->Reset();                    
            }

            void JustDied(Unit* /*killer*/)
            {
                if (Creature* Strife = me->FindNearestCreature(NPC_STRIFE, 100.0f, false))
                if (Creature* lorewalker = me->FindNearestCreature(BOSS_LOREWALKER_STONESTEP, 100.0f, true))
                    lorewalker->AI()->DoAction(ACTION_EVENT_COMPLETE);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (timer_dissipation <= diff)
                {
                    me->RemoveAuraFromStack(SPELL_INTENSITY);
                    if (!me->HasAura(SPELL_INTENSITY))
                        me->AddAura(SPELL_DISSIPATION, me);
                    timer_dissipation = TIMER_DISSIPATION;
                    --countIntensity;
                    if (countIntensity == -10)
                        countIntensity = -10;
                }
                else
                    timer_dissipation -= diff;

                if (timer_intensity <= diff)
                {
                    if (hasBeenHit)
                    {
                        me->RemoveAuraFromStack(SPELL_DISSIPATION);
                        if (!me->HasAura(SPELL_DISSIPATION))
                            me->AddAura(SPELL_INTENSITY, me);
                        ++countIntensity;

                        if (countIntensity == 10)
                        {
                            me->CastSpell(me, SPELL_ULTIMATE_POWER, false);
                            me->RemoveAura(SPELL_INTENSITY);
                        }
                        if (countIntensity > 10)
                            countIntensity = 10;
                    }
                    hasBeenHit = false;
                    timer_intensity = TIMER_INTENSITY;
                }
                else
                    timer_intensity -= diff;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case 1:
                        if (!me->getVictim())
                            return;
                        me->CastSpell(me->getVictim(), SPELL_AGONY, false);
                        events.ScheduleEvent(1, 2000);
                        break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_scroll : public CreatureScript
{
public:
    npc_scroll() : CreatureScript("npc_scroll") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_scrollAI(creature);
    }

    struct npc_scrollAI : public Scripted_NoMovementAI
    {
        npc_scrollAI(Creature* creature) : Scripted_NoMovementAI(creature)
        {
            creature->SetReactState(REACT_PASSIVE);
        }

        void Reset()
        {
            me->CastSpell(me, SPELL_SCROLL_FLOOR, false);
            me->CastSpell(me, SPELL_JADE_ENERGY_2, false);
            me->CastSpell(me, SPELL_GROW_LOW, false);
        }

        void JustDied(Unit* /*killer*/)
        {
            me->RemoveAura(SPELL_JADE_ENERGY_2);
            me->RemoveAura(SPELL_SCROLL_FLOOR);
            me->RemoveAura(SPELL_GROW_LOW);
            me->CastSpell(me, SPELL_SHA_BURNING, false);
            me->CastSpell(me, SPELL_SHA_EXPLOSION, false);
            me->CastSpell(me, SPELL_DEATH, false);
        }
    };
};

class mob_nodding_tiger: public CreatureScript
{
    public:
        mob_nodding_tiger() : CreatureScript("mob_nodding_tiger") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_nodding_tiger_AI(creature);
        }

        struct mob_nodding_tiger_AI : public ScriptedAI
        {
            mob_nodding_tiger_AI(Creature* creature) : ScriptedAI(creature)
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
                        me->CastSpell(me->getVictim(), SPELL_CLAW, false);
                        events.ScheduleEvent(1, 3000);
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };
};

class mob_golden_beetle: public CreatureScript
{
    public:
        mob_golden_beetle() : CreatureScript("mob_golden_beetle") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_golden_beetle_AI(creature);
        }

        struct mob_golden_beetle_AI : public ScriptedAI
        {
            mob_golden_beetle_AI(Creature* creature) : ScriptedAI(creature)
            {
            }
            EventMap events;

            void EnterCombat(Unit* unit)
            {
                events.ScheduleEvent(1, 2000);
                events.ScheduleEvent(2, 4000);
                events.ScheduleEvent(3, 6000);
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
                        me->CastSpell(me->getVictim(), SPELL_SERRATED_SLASH, false);
                        events.ScheduleEvent(1, 10000);
                        break;
                    case 2:
                        me->CastSpell(me->getVictim(), SPELL_SHROUD_OF_GOLD, false);
                        events.ScheduleEvent(2, 5000);
                        break;
                    case 3:
                        me->CastSpell(me->getVictim(), SPELL_SLOW, false);
                        events.ScheduleEvent(3, 15000);
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };
};

// 59547 - 65317 - the two junglers (trash)
class mob_jiang_xiang : public CreatureScript
{
public:
    mob_jiang_xiang() : CreatureScript("mob_jiang_xiang") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_jiang_xiang_AI(creature);
    }

    struct mob_jiang_xiang_AI : public ScriptedAI
    {
        mob_jiang_xiang_AI(Creature* creature) : ScriptedAI(creature) { }
        EventMap events;

        enum eEventsJiangXiang
        {
            EVENT_AERIALIST_KICK = 1,
            EVENT_THROW_TORCH = 2,
        };

        enum eSpellsJiangXiang
        {
            SPELL_JUGGLER_JIANG = 114745,
            SPELL_JUGGLER_XIANG = 114718,

            SPELL_AERIALIST_KICK = 114805,
            SPELL_THROW_TORCH = 114803,
        };

        void Reset()
        {
            if (me->GetEntry() == NPC_JIANG)
                me->CastSpell(me, SPELL_JUGGLER_JIANG, false);
            else if (me->GetEntry() == NPC_XIANG)
                me->CastSpell(me, SPELL_JUGGLER_XIANG, false);

            me->CastSpell(me, SPELL_SHA_CORRUPTION_2, false);
            events.Reset();
        }

        void EnterCombat(Unit* unit)
        {
            events.ScheduleEvent(EVENT_AERIALIST_KICK, 2000);
            events.ScheduleEvent(EVENT_THROW_TORCH, 4000);
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
                case EVENT_AERIALIST_KICK:
                    me->CastSpell(me->getVictim(), SPELL_AERIALIST_KICK, false);
                    events.ScheduleEvent(EVENT_AERIALIST_KICK, 10000);
                    break;
                case EVENT_THROW_TORCH:
                    me->CastSpell(me->getVictim(), SPELL_THROW_TORCH, false);
                    events.ScheduleEvent(EVENT_THROW_TORCH, 5000);
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }
    };
};

class mob_songbird_queen: public CreatureScript
{
    public:
        mob_songbird_queen() : CreatureScript("mob_songbird_queen") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_songbird_queen_AI(creature);
        }

        struct mob_songbird_queen_AI : public ScriptedAI
        {
            mob_songbird_queen_AI(Creature* creature) : ScriptedAI(creature)
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
                        me->CastSpell(me->getVictim(), SPELL_SONGBIRD_SERENADE, false);
                        events.ScheduleEvent(1, 10000);
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };
};

class mob_talking_fish: public CreatureScript
{
    public:
        mob_talking_fish() : CreatureScript("mob_talking_fish") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_talking_fish_AI(creature);
        }

        enum eTalks
        {
            TALK_0,
            TALK_1,
            TALK_2,
            TALK_3,
        };

        struct mob_talking_fish_AI : public ScriptedAI
        {
            mob_talking_fish_AI(Creature* creature) : ScriptedAI(creature)
            {
            }
            EventMap events;

            void EnterCombat(Unit* unit)
            {
                Talk(TALK_0 + urand(0, 3));
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
                        me->CastSpell(me->getVictim(), SPELL_BUBBLE_SPRAY, false);
                        events.ScheduleEvent(1, 10000);
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };
};

//59555 - hunting sha (trash)
class mob_sha_corrupted_generic : public CreatureScript
{
public:
    mob_sha_corrupted_generic() : CreatureScript("mob_sha_corrupted_generic") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_sha_corrupted_generic_AI(creature);
    }

    enum eSpellsHuntingSha
    {
        SPELL_HAUNTING_GAZE = 114650,
    };

    struct mob_sha_corrupted_generic_AI : public ScriptedAI
    {
        mob_sha_corrupted_generic_AI(Creature* creature) : ScriptedAI(creature)
        {
        }

        void Reset()
        {
            me->CastSpell(me, SPELL_HAUNTING_GAZE, false);            
        }
    };
};

class SunCheck
{
public:
    bool operator()(const WorldObject* target)
    {
        if (target->ToCreature())
        {
            if (target->GetEntry() == BOSS_LOREWALKER_STONESTEP)
                return false;
        }
        return true;
    }
};

//Called Sunfire Explosion 111737
class spell_mob_sun_sunfire_explotion : public SpellScriptLoader
{
public:
    spell_mob_sun_sunfire_explotion() : SpellScriptLoader("spell_mob_sun_sunfire_explotion") { }

    class spell_mob_sun_sunfire_explotion_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_mob_sun_sunfire_explotion_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (!GetCaster())
                return;

            targets.remove_if(SunCheck());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mob_sun_sunfire_explotion_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mob_sun_sunfire_explotion_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_mob_sun_sunfire_explotion_SpellScript();
    }
};

void AddSC_boss_lorewalker_stonestep()
{
    new boss_lorewalker_stonestep();
    new mob_sun();
    new mob_zao();
    new mob_haunting_sha();
    new mob_peril();
    new mob_strife();
    new npc_scroll();
    new mob_sunfire();
    //Trashes
    new mob_nodding_tiger();
    new mob_golden_beetle();
    new mob_jiang_xiang();
    new mob_songbird_queen();
    new mob_talking_fish();
    new mob_sha_corrupted_generic();
    //Spell
    new spell_mob_sun_sunfire_explotion();
}