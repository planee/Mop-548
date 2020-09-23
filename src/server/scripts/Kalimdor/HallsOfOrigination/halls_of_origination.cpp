#include "ScriptPCH.h"
#include "halls_of_origination.h"

enum ScriptTexts
{
    // Brann Bronzebeard
    SAY_0   = 0,
    SAY_1   = 1,
    SAY_2   = 2,
    SAY_3   = 3,
    SAY_4   = 4,
    SAY_5   = 5,
    SAY_6   = 6,
    SAY_7   = 7,
    SAY_8   = 8,
    SAY_9   = 9,
    SAY_10  = 10,
};
/*
BRANN_SAY_DOOR_INTRO = 0,  // Right, let's go! Just need to input the final entry sequence into the door mechanism... and...
BRANN_SAY_UNLOCK_DOOR = 1,  // That did the trick! The control room should be right behind this... oh... wow...
BRANN_SAY_TROGGS = 2,  //
What ? This isn't the control room! There's another entire defense
mechanism in place, and the blasted Rock Troggs broke into here somehow.
Troggs.Why did it have to be Troggs!
BRANN_SAY_THINK = 3,  // Ok, let me think a moment.
BRANN_SAY_MIRRORS = 4,  // Mirrors pointing all over the place.
BRANN_SAY_ELEMENTALS = 5,  // Four platforms with huge elementals.
BRANN_SAY_GET_IT = 6,  //
I got it!I saw a tablet that mentioned this chamber.This is the Vault
of Lights!Ok, simple enough.I need you adventurers to take out each
of the four elementals to trigger the opening sequence for the far door!
BRANN_1_ELEMENTAL_DEAD = 7,  // One down!
BRANN_2_ELEMENTAL_DEAD = 8,  // Another one down! Just look at those light beams! They seem to be connecting to the far door!
BRANN_3_ELEMENTAL_DEAD = 9,  // One more elemental to go! The door is almost open!
BRANN_4_ELEMENTAL_DEAD = 10, // That''s it, you''ve done it! The vault door is opening! Now we can... oh, no!
BRANN_SAY_ANRAPHET_DIED = 11, // We''ve done it! The control room is breached!
BRANN_SAY_MOMENT = 12 // Here we go! Now this should only take a moment...
*/
/*
Position const BrannIntroWaypoint[MAX_BRANN_WAYPOINTS_INTRO] =
{
	{ -429.583f, 367.019f, 89.79282f, 0.0f },
	{ -409.9531f, 367.0469f, 89.81111f, 0.0f },
	{ -397.8246f, 366.967f, 86.37722f, 0.0f },
	{ -383.7813f, 366.8229f, 82.07919f, 0.0f },
	{ -368.2604f, 366.7448f, 77.0984f, 0.0f },
	{ -353.6458f, 366.4896f, 75.92504f, 0.0f },
	{ -309.0608f, 366.7205f, 75.91345f, 0.0f },
	{ -276.3303f, 367.0f, 75.92413f, 0.0f },
	{ -246.5104f, 366.6389f, 75.87791f, 0.0f },
	{ -202.0417f, 366.7517f, 75.92508f, 0.0f },
	{ -187.6024f, 366.7656f, 76.23077f, 0.0f },
	{ -155.0938f, 366.783f, 86.45834f, 0.0f },
	{ -143.5694f, 366.8177f, 89.73354f, 0.0f },
	{ -128.5608f, 366.8629f, 89.74199f, 0.0f },
	{ -103.559f, 366.5938f, 89.79725f, 0.0f },
	{ -71.58507f, 367.0278f, 89.77069f, 0.0f },
	{ -35.04861f, 366.6563f, 89.77447f, 0.0f },
};
*/
enum Spells
{
    // Air Warden
    SPELL_WIND_SNEAR              = 77334,

    // Flame Warden
    SPELL_RAGING_INFERNO          = 77241,
    SPELL_RAGING_INFERNO_DMG      = 77262,
    SPELL_RAGING_INFERNO_DMG_H    = 91159,
    SPELL_LAVA_ERUPTION           = 77273,
    SPELL_LAVA_ERUPTION_H         = 91161,

    // Water Warden
    SPELL_BUBBLE_BOUND            = 77336,
    SPELL_BUBBLE_BOUND_H          = 91158,

    // Earth Warden
    SPELL_IMPALE                  = 77235,
    SPELL_ROCKWAVE                = 77234,    

	//Temple Runecaster
	SPELL_CURSE_OF_THE_RUNECASTER = 89551,
	SPELL_RUNIC_CLEAVE            = 89554,

	//Temple Shadowlancer
	SPELL_PACT_OF_DARKNESS        = 89560,
	SPELL_SHADOWLANCE             = 89555,

	//Blistering Scarab
	SPELL_CORROSIVE_SPRAY         = 74122,
	SPELL_SERRATED_SLASH          = 74542,

	//Temple Fireshaper
	SPELL_MOLTEN_BARRIER          = 89542,
	SPELL_FIREBALL                = 89538,
	SPELL_BLAZING_ERUPTION        = 89547,
	SPELL_METEOR                  = 84032,

	//Temple Swiftstalker
	SPELL_CHARGE                  = 94971,
	SPELL_MULTI_SHOOT             = 84836,
	SPELL_SHOOT                   = 83877,

	//Dustbone Horror
	SPELL_SMASH                   = 75453,

	//Dustbone Tormentor
	SPELL_SHADOW_BOLT             = 77570,
	SPELL_CURSE_OF_EXHAUSTION     = 77357,
};

enum Events
{
    // Air Warden
    EVENT_WIND_SNEAR        = 1,

    // Flame Warden
    EVENT_LAVA_ERUPTION     = 2,
    EVENT_RAGING_INFERNO    = 3,

    // Water Warden         
    EVENT_BUBBLE_BOUND      = 4,

    // Earth Warden
    EVENT_IMPALE            = 5,
    EVENT_ROCKWAVE          = 6,

    // Brann Bronzebeard
    EVENT_TALK_0            = 7,
    EVENT_TALK_1            = 8,
    EVENT_TALK_2            = 9,
    EVENT_TALK_3            = 10,
    EVENT_TALK_4            = 11,
    EVENT_TALK_5            = 12,
    EVENT_TALK_6            = 13,
    EVENT_TALK_7            = 14,
    EVENT_TALK_8            = 15,
    EVENT_TALK_9            = 16,
    EVENT_TALK_10           = 17,
    EVENT_TALK_11           = 18,    
};

enum Adds
{
    NPC_WHIRLING_WINDS  = 41245, // 77321
};

enum Actions
{
    ACTION_TALK_1       = 1,
    ACTION_TALK_2       = 2,
    ACTION_TALK_3       = 3,
    ACTION_TALK_4       = 4,
    ACTION_START_EVENT  = 5,
};

#define GOSSIP_BRANN_START_EVENT "Let's go"

class npc_air_warden : public CreatureScript
{
    public:
        npc_air_warden() : CreatureScript("npc_air_warden") {}
 
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_air_wardenAI(creature);
        }

        struct npc_air_wardenAI : public ScriptedAI
        {
            npc_air_wardenAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
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
 
            InstanceScript* pInstance;
            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit * who)
            {
                events.ScheduleEvent(EVENT_WIND_SNEAR, urand(2000, 6000));
                DoZoneInCombat();
            }

            void JustDied(Unit* /*killer*/)
            {
                if (pInstance)
                    pInstance->SetData(DATA_WARDENS, 1);
            }
        
            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;
                                       
                events.Update(diff);
 
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                    case EVENT_WIND_SNEAR:
                        if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(pTarget, SPELL_WIND_SNEAR);
                        events.ScheduleEvent(EVENT_WIND_SNEAR, urand(7000, 10000));
                        break;                                                 
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_flame_warden : public CreatureScript
{
    public:
        npc_flame_warden() : CreatureScript("npc_flame_warden") {}
 
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_flame_wardenAI(creature);
        }

        struct npc_flame_wardenAI : public ScriptedAI
        {
            npc_flame_wardenAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
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
 
            InstanceScript* pInstance;
            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit * who)
            {
                events.ScheduleEvent(EVENT_LAVA_ERUPTION, urand(4000, 7000));
                events.ScheduleEvent(EVENT_RAGING_INFERNO, urand(10000, 12000));
                DoZoneInCombat();
            }

            void JustDied(Unit* /*killer*/)
            {
                if (pInstance)
                    pInstance->SetData(DATA_WARDENS, 1);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;
                                       
                events.Update(diff);
 
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_LAVA_ERUPTION:
                            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                DoCast(pTarget, SPELL_LAVA_ERUPTION);
                            events.ScheduleEvent(EVENT_LAVA_ERUPTION, urand(8000, 12000));
                            break;
                        case EVENT_RAGING_INFERNO:
                            DoCastAOE(SPELL_RAGING_INFERNO);
                            events.ScheduleEvent(EVENT_RAGING_INFERNO, urand(20000, 25000));
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_water_warden : public CreatureScript
{
    public:
        npc_water_warden() : CreatureScript("npc_water_warden") {}
 
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_water_wardenAI(creature);
        }

        struct npc_water_wardenAI : public ScriptedAI
        {
            npc_water_wardenAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
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
 
            InstanceScript* pInstance;
            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit * who)
            {
                events.ScheduleEvent(EVENT_BUBBLE_BOUND, urand(10000, 15000));
                DoZoneInCombat();
            }

            void JustDied(Unit* /*killer*/)
            {
                if (pInstance)
                    pInstance->SetData(DATA_WARDENS, 1);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;
                                       
                events.Update(diff);
 
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_BUBBLE_BOUND:
                            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                DoCast(pTarget, SPELL_BUBBLE_BOUND);
                            events.ScheduleEvent(EVENT_BUBBLE_BOUND, urand(10000, 15000));
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_earth_warden : public CreatureScript
{
    public:
        npc_earth_warden() : CreatureScript("npc_earth_warden") {}
 
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_earth_wardenAI(creature);
        }

        struct npc_earth_wardenAI : public ScriptedAI
        {
            npc_earth_wardenAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
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
 
            InstanceScript* pInstance;
            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit * who)
            {
                events.ScheduleEvent(EVENT_IMPALE, urand(6000, 10000));
                events.ScheduleEvent(EVENT_ROCKWAVE, urand(12000, 15000));
                DoZoneInCombat();
            }

            void JustDied(Unit* /*killer*/)
            {
                if (pInstance)
                    pInstance->SetData(DATA_WARDENS, 1);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;
                                       
                events.Update(diff);
 
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_IMPALE:
                            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                DoCast(pTarget, SPELL_IMPALE);
                            events.ScheduleEvent(EVENT_IMPALE, urand(10000, 15000));
                            break;
                        case EVENT_ROCKWAVE:
                            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                DoCast(pTarget, SPELL_ROCKWAVE);
                            events.ScheduleEvent(EVENT_ROCKWAVE, urand(15000, 20000));
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_water_warden_water_bubble : public CreatureScript
{
    public:
        npc_water_warden_water_bubble() : CreatureScript("npc_water_warden_water_bubble") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_water_warden_water_bubbleAI(creature);
        }

        struct npc_water_warden_water_bubbleAI : public Scripted_NoMovementAI
        {
            npc_water_warden_water_bubbleAI(Creature* creature) : Scripted_NoMovementAI(creature)
            {
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
			    me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            }

            void Reset()
            {
                me->SetReactState(REACT_PASSIVE);
            }

            void JustDied(Unit* /*killer*/)
            {
                if (Unit* pOwner = me->GetOwner())
                {
                    pOwner->RemoveAurasDueToSpell(SPELL_BUBBLE_BOUND);
                    pOwner->RemoveAurasDueToSpell(SPELL_BUBBLE_BOUND_H);
                }
                me->DespawnOrUnsummon();
            }

            void UpdateAI(const uint32 diff)
            {
                if (!me->GetOwner())
                    me->DespawnOrUnsummon();

                if (me->GetOwner()->isAlive())
                    me->DespawnOrUnsummon();

                if (!me->GetOwner()->HasAura(SPELL_BUBBLE_BOUND) &&
                    !me->GetOwner()->HasAura(SPELL_BUBBLE_BOUND_H))
                    me->DespawnOrUnsummon();
            }
        };
};

class npc_halls_of_origination_brann_bronzebeard : public CreatureScript
{
    public:
        npc_halls_of_origination_brann_bronzebeard() : CreatureScript("npc_halls_of_origination_brann_bronzebeard") {}
 
        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_halls_of_origination_brann_bronzebeardAI(creature);
        }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            if (pCreature->isQuestGiver())
                pPlayer->PrepareQuestMenu(pCreature->GetGUID());

            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BRANN_START_EVENT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();

            if (uiAction == (GOSSIP_ACTION_INFO_DEF + 1))
            {
                pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                pCreature->AI()->DoAction(ACTION_START_EVENT);
            }

            return true;
        }

        struct npc_halls_of_origination_brann_bronzebeardAI : public ScriptedAI
        {
            npc_halls_of_origination_brann_bronzebeardAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
                pCreature->setActive(true);
            }
 
            InstanceScript* pInstance;
            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void DoAction(const int32 action)
            {
                switch (action)
                {
                    case ACTION_TALK_1:
                        Talk(SAY_7);
                        break;
                    case ACTION_TALK_2:
                        Talk(SAY_8);
                        break;
                    case ACTION_TALK_3:
                        Talk(SAY_9);
                        break;
                    case ACTION_TALK_4:
                        Talk(SAY_10);
                        break;
                    case ACTION_START_EVENT:
                        events.ScheduleEvent(EVENT_TALK_0, 1000);
                        break;
                }
            }

            void UpdateAI(const uint32 diff)
            {        
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_TALK_0:
                            Talk(SAY_0);
                            events.ScheduleEvent(EVENT_TALK_1, 8000);
                            break;
                        case EVENT_TALK_1:
                            if (pInstance)
                            {
                                pInstance->HandleGameObject(pInstance->GetData64(DATA_ANRAPHET_ENTRANCE_DOOR), true);
                                pInstance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, EVENT_FASTER_THAN_LIGHT);
                            }
                            Talk(SAY_1);
                            events.ScheduleEvent(EVENT_TALK_2, 4000);
                            break;
                        case EVENT_TALK_2:
                            Talk(SAY_2);
                            events.ScheduleEvent(EVENT_TALK_3, 8000);
                            break;
                        case EVENT_TALK_3:
                            Talk(SAY_3);
                            events.ScheduleEvent(EVENT_TALK_4, 4000);
                            break;
                        case EVENT_TALK_4:
                            Talk(SAY_4);
                            events.ScheduleEvent(EVENT_TALK_5, 4000);
                            break;
                        case EVENT_TALK_5:
                            Talk(SAY_5);
                            events.ScheduleEvent(EVENT_TALK_6, 4000);
                            break;
                        case EVENT_TALK_6:
                            Talk(SAY_6);
                            break;
                    }
                }
            }
        };
};

class go_halls_of_origination_transit_device : public GameObjectScript
{
    public:
        go_halls_of_origination_transit_device() : GameObjectScript("go_halls_of_origination_transit_device"){ }

        bool OnGossipHello(Player* pPlayer, GameObject* pGo)
        {
            if (pPlayer->isInCombat())
                return true;
            return false;
        }
};

/***************************
**Temple Runecaster
****************************/

class npc_temple_runecaster : public CreatureScript
{
public:
	npc_temple_runecaster() : CreatureScript("npc_temple_runecaster") {}

	struct npc_temple_runecasterAI : public ScriptedAI
	{
		npc_temple_runecasterAI(Creature *c) : ScriptedAI(c) {}

		uint32 cleave;
		uint32 curse;

		void Reset()
		{
			cleave = 10000;
			curse = 15000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (cleave <= diff)
			{
				DoCast(me->getVictim(), SPELL_RUNIC_CLEAVE);
				cleave = 10000;
			}
			else cleave -= diff;

			if (curse <= diff)
			{
				DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true), SPELL_CURSE_OF_THE_RUNECASTER);
				curse = 15000;
			}
			else curse -= diff;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_temple_runecasterAI(pCreature);
	}
};

/**********************
**Temple Shadowlancer
***********************/

class npc_temple_shadowlancer : public CreatureScript
{
public:
	npc_temple_shadowlancer() : CreatureScript("npc_temple_shadowlancer") {}

	struct npc_temple_shadowlancerAI : public ScriptedAI
	{
		npc_temple_shadowlancerAI(Creature *c) : ScriptedAI(c) {}

		uint32 shadowlance;
		uint32 pact;

		void Reset()
		{
			shadowlance = 20000;
			pact = 25000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (shadowlance <= diff)
			{
				DoCast(me, SPELL_SHADOWLANCE);
				shadowlance = 20000;
			}
			else shadowlance -= diff;

			if (pact <= diff)
			{
				DoCast(me, SPELL_PACT_OF_DARKNESS);
				pact = 25000;
			}
			else pact -= diff;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_temple_shadowlancerAI(pCreature);
	}
};

/*******************
**Blistering Scarab
********************/

class npc_blistering_scarab : public CreatureScript
{
public:
	npc_blistering_scarab() : CreatureScript("npc_blistering_scarab") {}

	struct npc_blistering_scarabAI : public ScriptedAI
	{
		npc_blistering_scarabAI(Creature *c) : ScriptedAI(c) {}

		uint32 slash;
		uint32 corrosive;

		void Reset()
		{
			slash = 15000;
			corrosive = 10000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (slash <= diff)
			{
				DoCast(me->getVictim(), SPELL_SERRATED_SLASH);
				slash = 15000;
			}
			else slash -= diff;

			if (corrosive <= diff)
			{
				DoCast(me, SPELL_CORROSIVE_SPRAY);
				corrosive = 10000;
			}
			else corrosive -= diff;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_blistering_scarabAI(pCreature);
	}

};

/*********************
**Temple Fireshaper
**********************/


class npc_temple_fireshaper : public CreatureScript
{
public:
	npc_temple_fireshaper() : CreatureScript("npc_temple_fireshaper") {}

	struct npc_temple_fireshaperAI : public ScriptedAI
	{
		npc_temple_fireshaperAI(Creature *c) : ScriptedAI(c) {}

		uint32 barrier;
		uint32 fireball;
		uint32 eruption;
		uint32 meteor;

		void Reset()
		{
			barrier = 45000;
			fireball = 4000;
			eruption = 60000;
			meteor = 30000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (barrier <= diff)
			{
				DoCast(me, SPELL_MOLTEN_BARRIER);
				barrier = 45000;
			}
			else barrier -= diff;

			if (fireball <= diff)
			{
				DoCast(me->getVictim(), SPELL_FIREBALL);
				fireball = 4000;
			}
			else fireball -= diff;

			if (eruption <= diff)
			{
				DoCast(me, SPELL_BLAZING_ERUPTION);
				eruption = 60000;
			}
			else eruption -= diff;

			if (meteor <= diff)
			{
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 10.0f, true))
					DoCast(target, SPELL_METEOR);
				meteor = 30000;
			}
			else meteor -= diff;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_temple_fireshaperAI(pCreature);
	}

};

/**************************
**Temple Swiftstalker
***************************/

class npc_temple_swiftstalker : public CreatureScript
{
public:
	npc_temple_swiftstalker() : CreatureScript("npc_temple_swiftstalker") {}

	struct npc_temple_swiftstalkerAI : public ScriptedAI
	{
		npc_temple_swiftstalkerAI(Creature *c) : ScriptedAI(c) {}

		uint32 multiples;
		uint32 tir;
		uint32 tir_charge;

		void Reset()
		{
			multiples = 12000;
			tir = 2500;
			tir_charge = 19000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (multiples <= diff)
			{
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 10.0f, true))
					DoCast(target, SPELL_MULTI_SHOOT);
				multiples = 12000;
			}
			else multiples -= diff;

			/*if (tir <= diff)
			{
				DoCast(me->getVictim(), SPELL_SHOOT);
				tir = 2500;
			}
			else tir -= diff;*/

			if (tir_charge <= diff)
			{
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
					DoCast(pTarget, SPELL_CHARGE);
				tir_charge = 19000;
			}
			else tir_charge -= diff;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_temple_swiftstalkerAI(pCreature);
	}
};

/******************
**Venomous Skitterer
*******************/

#define spell_afflux 83233 // Afflux
#define spell_toxine RAND(73963,74121) // Toxine

class npc_venomous_skitterer : public CreatureScript
{
public:
	npc_venomous_skitterer() : CreatureScript("npc_venomous_skitterer") {}

	struct npc_venomous_skittererAI : public ScriptedAI
	{
		npc_venomous_skittererAI(Creature *c) : ScriptedAI(c) {}

		uint32 afflux;
		uint32 toxine;

		void Reset()
		{
			afflux = 15000;
			toxine = 10000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (afflux <= diff)
			{
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 10.0f, true))
					DoCast(target, spell_afflux);
				afflux = 15000;
			}
			else afflux -= diff;

			if (toxine <= diff)
			{
				DoCast(me->getVictim(), spell_toxine);
				toxine = 10000;
			}
			else toxine -= diff;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_venomous_skittererAI(pCreature);
	}

};

/*********************
**Dustbone Horror
**********************/

class npc_dustbone_horror : public CreatureScript
{
public:
	npc_dustbone_horror() : CreatureScript("npc_dustbone_horror") {}

	struct npc_dustbone_horrorAI : public ScriptedAI
	{
		npc_dustbone_horrorAI(Creature *c) : ScriptedAI(c) {}

		uint32 smash;

		void Reset()
		{
			smash = 5000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (smash <= diff)
			{
				DoCast(me->getVictim(), SPELL_SMASH);
				smash = 5000;
			}
			else smash -= diff;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_dustbone_horrorAI(pCreature);
	}

};

/*************************
**Dustbone Tormentor
**************************/

class npc_dustbone_tormentor : public CreatureScript
{
public:
	npc_dustbone_tormentor() : CreatureScript("npc_dustbone_tormentor") {}

	struct npc_dustbone_tormentorAI : public ScriptedAI
	{
		npc_dustbone_tormentorAI(Creature *c) : ScriptedAI(c) {}

		uint32 bolt;
		uint32 curse;

		void Reset()
		{
			bolt = 6000;
			curse = 10000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (bolt <= diff)
			{
				DoCast(me->getVictim(), SPELL_SHADOW_BOLT);
				bolt = 6000;
			}
			else bolt -= diff;

			if (curse <= diff)
			{
				if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
					DoCast(pTarget, SPELL_CURSE_OF_EXHAUSTION);
				curse = 10000;
			}
			else curse -= diff;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_dustbone_tormentorAI(pCreature);
	}

};


void AddSC_halls_of_origination()
{
    new npc_air_warden();
    new npc_flame_warden();
    new npc_water_warden();
    new npc_earth_warden();
    new npc_water_warden_water_bubble();
    new npc_halls_of_origination_brann_bronzebeard();
    new go_halls_of_origination_transit_device();
	new npc_temple_runecaster();
	new npc_temple_shadowlancer();
	new npc_blistering_scarab();
	new npc_temple_fireshaper();
	new npc_temple_swiftstalker();
	new npc_venomous_skitterer();
	new npc_dustbone_horror();
	new npc_dustbone_tormentor();
}
