/*
* Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
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

/* ScriptData
SDName: Stormwind_City
SD%Complete: 25%
SDComment:
SDCategory: Stormwind City
EndScriptData */

/* ContentData
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"





enum eSpells
{
	SPELL_MIND_BLAST = 13860,
	SPELL_PENITENCE = 54518,
	SPELL_DIAGONAL_SLIDE = 83991,
	SPELL_DIAGONAL_SLIDE_EFFECT = 83995,
	SPELL_POWER_SHIELSD = 11974,
	SPELL_INNER_FIRE = 48168,
	SPELL_ALTSHIELD = 84018
};

enum eEvents
{
	EVENT_MINDBLAST = 1,
	EVENT_PENITENCE = 2,
	EVENT_COMBAT = 3,
	EVENT_MOVE_DIAGONALLY = 4,
	EVENT_TELEPORTDELAY = 5
};

enum Quests
{
	QUEST_MISSING_PART		   = 27038,
	QUEST_RALLE_THE_FLEET      = 26975,
	QUEST_THE_UNUSUAL_SOSPECTS = 26997,
	QUEST_HOLDING_ON_US        = 27064,
	QUEST_PEASAN_PROBLEM       = 27044,
    QUEST_TWLIGHT_SHORES       = 28238
};

enum Spells
{
	SPELL_SUMMON_ANDUIN_THRONE_ROOM = 82823
};

enum ePrince
{
	ANDUIN_WRYNN_THRONE   = 44293, //NPC ID
	//Prince Mounts
	ARMORED_SNOWY_GRYPHON = 27913,
	SWIFT_WHITE_STEED     = 14338,
	//Quests
	MY_SON_THE_PRINCE     = 26960,
	RALLYING_THE_FLEET    = 26975
};

enum KingSpells
{
    // King - Varian Wrynn
    SPELL_HEROIC_LEAP           = 59688,
    SPELL_WHIRLWIND             = 41056,  
    SPELL_STRENGTH_OF_WRYNN     = 60509,

    //King - Genn Graymane
    SPELL_HORRIFYING_HOWL       = 84813,
    SPELL_INTIMIDATING_ROAR     = 51467,
    SPELL_JUMP_ATTACK           = 84815,
    SPELL_SHATTERING_THROW      = 84817,
};

enum KingEvents
{
    // King - Varian Wrynn
    EVENT_HEROIC_LEAP           = 1,
    EVENT_WHIRLWIND             = 2,
    EVENT_GUARDS                = 3,

    //King - Genn Graymane
    EVENT_HORRIFYING_HOWL       = 4,
    EVENT_INTIMIDATING_ROAR     = 5,
    EVENT_JUMP_ATTACK           = 6,
    EVENT_SHATTERING_THROW      = 7,
};

enum KingTexts
{
    SAY_WRYNN_AGGRO = 0, // @ DB 50% chance for two yells
    SAY_WRYNN_GUARDS = 1,

    //    SAY_TYRANDE_AGGRO       = 0 // Does she yell?
};

Position const PosWrynnGuards[2] =
{
    { -8363.64f, 254.42f, 155.34f, 3.76f }, // Wrynn Guards
    { -8384.68f, 237.71f, 155.34f, 0.63f },
};

enum KingCreas
{
    NPC_WRYNN_GUARDS = 1756
};

class npc_king_varian_wrynn_quest : public CreatureScript
{
public:
	npc_king_varian_wrynn_quest() : CreatureScript("npc_king_varian_wrynn_quest") { }

	bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
	{
		if (quest->GetQuestId() == 30988) // The Alliance Way
		{
			if (Creature* master = player->SummonCreature(61796, creature->GetPositionX(), creature->GetPositionY(), creature->GetPositionZ(), creature->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 300000))
			{
				master->setExplicitSeerGuid(player->GetGUID());
				master->AI()->SetGUID(player->GetGUID());
			}
		}

		return true;
	}

    struct npc_king_varian_wrynn_questAI : public ScriptedAI
    {
        npc_king_varian_wrynn_questAI(Creature* creature) : ScriptedAI(creature), summons(creature) { }

        SummonList summons;

        void Reset()
        {
            summons.DespawnAll();
            events.Reset();
        }

        void EnterCombat(Unit* /*who*/)
        {
            Talk(SAY_WRYNN_AGGRO);
            DoCastAOE(SPELL_STRENGTH_OF_WRYNN);
            events.ScheduleEvent(EVENT_HEROIC_LEAP, 10000);
            events.ScheduleEvent(EVENT_WHIRLWIND, 25000);
            events.ScheduleEvent(EVENT_GUARDS, 30000);
        }

        void JustSummoned(Creature* summon)
        {
            if (summon->GetEntry() == NPC_WRYNN_GUARDS)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    summon->AI()->AttackStart(target);
                summon->SetInCombatWithZone();

                summons.Summon(summon);
            }
        }

        void JustDied(Unit* /*killer*/)
        {
            summons.DespawnAll();
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_HEROIC_LEAP:
                    DoCast(SelectTarget(SELECT_TARGET_TOPAGGRO, 0), SPELL_HEROIC_LEAP);
                    events.ScheduleEvent(EVENT_HEROIC_LEAP, urand(20 * IN_MILLISECONDS, 35 * IN_MILLISECONDS));
                    break;
                case EVENT_WHIRLWIND:
                    DoCastVictim(SPELL_WHIRLWIND);
                    events.ScheduleEvent(EVENT_WHIRLWIND, urand(35 * IN_MILLISECONDS, 45 * IN_MILLISECONDS));
                    break;
                case EVENT_GUARDS:
                    Talk(SAY_WRYNN_GUARDS);
                    for (uint8 i = 0; i < 2; ++i)
                        me->SummonCreature(NPC_WRYNN_GUARDS, PosWrynnGuards[i], TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 5000);
                    events.ScheduleEvent(EVENT_GUARDS, urand(30 * IN_MILLISECONDS, 40 * IN_MILLISECONDS));
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }
    private:
        EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_king_varian_wrynn_questAI(creature);
    }
};

class npc_genn_greymane : public CreatureScript
{
public:
    npc_genn_greymane() : CreatureScript("npc_genn_greymane") { }

    struct npc_genn_greymaneAI : public ScriptedAI
    {
        npc_genn_greymaneAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() { events.Reset(); }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_INTIMIDATING_ROAR, 20000);
            events.ScheduleEvent(EVENT_HORRIFYING_HOWL, 5000);
            events.ScheduleEvent(EVENT_JUMP_ATTACK, 10000);
            events.ScheduleEvent(EVENT_SHATTERING_THROW, 40000);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_JUMP_ATTACK:
                    DoCast(SelectTarget(SELECT_TARGET_FARTHEST, 0, 40.0f, true), SPELL_JUMP_ATTACK);
                    events.ScheduleEvent(EVENT_JUMP_ATTACK, urand(20 * IN_MILLISECONDS, 30 * IN_MILLISECONDS));
                    break;
                case EVENT_SHATTERING_THROW:
                    DoCast(SelectTarget(SELECT_TARGET_FARTHEST, 0, 40.0f, true), SPELL_SHATTERING_THROW);
                    events.ScheduleEvent(EVENT_SHATTERING_THROW, urand(20 * IN_MILLISECONDS, 30 * IN_MILLISECONDS));
                    break;
                case EVENT_HORRIFYING_HOWL:
                    DoCastVictim(SPELL_HORRIFYING_HOWL);
                    events.ScheduleEvent(EVENT_HORRIFYING_HOWL, urand(40 * IN_MILLISECONDS, 50 * IN_MILLISECONDS));
                    break;
                case EVENT_INTIMIDATING_ROAR:
                    DoCastVictim(SPELL_INTIMIDATING_ROAR);
                    events.ScheduleEvent(EVENT_WHIRLWIND, urand(1 * MINUTE*IN_MILLISECONDS, 2 * MINUTE*IN_MILLISECONDS));
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }
    private:
        EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_genn_greymaneAI(creature);
    }
};


class npc_king_varian_wrynn_the_alliance_way : public CreatureScript
{
public:
	npc_king_varian_wrynn_the_alliance_way() : CreatureScript("npc_king_varian_wrynn_the_alliance_way") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_king_varian_wrynn_the_alliance_wayAI(creature);
	}

	bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
	{
		if (quest->GetQuestId() == 30989) // The Alliance Way
		{
			creature->AI()->SetGUID(player->GetGUID());
			creature->AI()->DoAction(1);
		}
		return true;
	}

	struct npc_king_varian_wrynn_the_alliance_wayAI : public ScriptedAI
	{
		npc_king_varian_wrynn_the_alliance_wayAI(Creature* creature) : ScriptedAI(creature) {}

		bool isPitFighter;
		uint32 phaseId;
		uint32 phaseTimer;
		uint64 playerGUID;

		void Reset()
		{
			isPitFighter = false;
			playerGUID = 0;
			phaseId = 0;
			phaseTimer = 2000;
		}

		void DoAction(int32 const action)
		{
			if (action == 1)
			{
				me->CastSpell(me, 120411, true);
				isPitFighter = true;
				phaseTimer = 10000;
				phaseId = 16;
				Talk(15);
			}
		}

		void SetGUID(uint64 guid, int32 /* = 0 */)
		{
			playerGUID = guid;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!playerGUID)
				return;

			if (isPitFighter)
			{
				if (phaseTimer < diff)
				{
					Talk(phaseId, playerGUID);
					if (phaseId == 16)
					{
						me->setFaction(7);
						if (Player * player = Unit::GetPlayer(*me, playerGUID))
							AttackStart(player);
					}
					if (phaseId == 20)
					{
						me->HandleEmoteCommand(EMOTE_ONESHOT_KNOCKDOWN);
						me->setFaction(35);
						if (Player * player = Unit::GetPlayer(*me, playerGUID))
							player->KilledMonsterCredit(61824);

						playerGUID = 0;
						me->ForcedDespawn(3000);
					}
					++phaseId;
					phaseTimer = 5000;
				}
				else
					phaseTimer -= diff;
				return;
			}
			else
			{
				if (phaseTimer < diff)
				{
					if (phaseId > 14)
					{
						if (Player * player = Unit::GetPlayer(*me, playerGUID))
							player->KilledMonsterCredit(61798);
						playerGUID = 0;
						return;
					}

					Talk(phaseId, playerGUID);

					phaseTimer = 6500;

					if (phaseId == 0 || phaseId == 1 || phaseId == 13)
						phaseTimer = 3000;
					else if (phaseId == 7 || phaseId == 9)
						phaseTimer = 5000;
					else if (phaseId == 6 || phaseId == 3)
						phaseTimer = 6000;
					else if (phaseId == 11)
						phaseTimer = 9000;
					else if (phaseId == 2)
						phaseTimer = 7000;
					else if (phaseId == 5)
						phaseTimer = 10000;
					else if (phaseId == 12)
						phaseTimer = 13000;

					++phaseId;
				}
				else
					phaseTimer -= diff;
			}
		}
	};
};

/*######
## npc_anduin_wrynn_throne
######*/


#define GOSSIP_ITEM		"Come whit me, your highness"
#define GOSSIP_ITEM_2	"Greetings Young Prince, Your Father Has Instructed me to make Your Aqueintance"

Position const  pricePosi[] =
{
	{ -8361.29f, 233.745f, 156.991f, 2.3328f },
	
};

class npc_anduin_wrynn_throne : public CreatureScript
{
public:

	npc_anduin_wrynn_throne()
		: CreatureScript("npc_anduin_wrynn_throne")
	{
	}

	struct npc_anduin_wrynn_throneAI : public ScriptedAI
	{

		npc_anduin_wrynn_throneAI(Creature* creature) : ScriptedAI(creature) {}

		Player* player;

		void Reset()
		{
		}

		void UpdateAI(const uint32 uiDiff)
		{
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_anduin_wrynn_throneAI(creature);
	}

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (creature->isQuestGiver())
			player->PrepareQuestMenu(creature->GetGUID());

		if (player->GetQuestStatus(RALLYING_THE_FLEET) == QUEST_STATUS_INCOMPLETE 
			|| (QUEST_THE_UNUSUAL_SOSPECTS) == QUEST_STATUS_INCOMPLETE
			|| (QUEST_HOLDING_ON_US) == QUEST_STATUS_INCOMPLETE)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

		if (player->GetQuestStatus(MY_SON_THE_PRINCE) == QUEST_STATUS_INCOMPLETE)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

		player->SEND_GOSSIP_MENU(907, creature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		switch (action)
		{
		case GOSSIP_ACTION_INFO_DEF + 1:
			Creature *summon;			
			player->CLOSE_GOSSIP_MENU();			
			creature->SummonCreature(ANDUIN_WRYNN_THRONE, pricePosi[0], TEMPSUMMON_DEAD_DESPAWN, 0, 0, player->GetGUID());			
			summon = creature->FindNearestCreature(ANDUIN_WRYNN_THRONE, 1.0f, true);
			summon->GetMotionMaster()->MoveFollow(player, 0.0f, 0.0f);
			summon->SetOwnerGUID(player->GetGUID());			
			creature->DestroyForPlayer(player, false);
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			player->CLOSE_GOSSIP_MENU();		
			player->KilledMonsterCredit(44692);
			break;
		}
		return true;
	}
};


/*######
## npc_anduin_wrynn_summon
######*/

Position const  points[3] =
{
	{ -8049.27f, 957.033f, 79.4188f, 0.226921f },
	{ -8048.63f, 966.344f, 79.9703f, 0.226921f },
	{ -8048.63f, 966.344f, 79.9703f, 4.77595f }
};

class npc_anduin_wrynn_summon : public CreatureScript
{
public:

	npc_anduin_wrynn_summon()
		: CreatureScript("npc_anduin_wrynn_summon")
	{
	}

	struct npc_anduin_wrynn_summonAI : public ScriptedAI
	{

		npc_anduin_wrynn_summonAI(Creature* creature) : ScriptedAI(creature) {}

		Player* player;

		uint64 checkTimer;
		uint64 eventTimer;
		uint32 area;
		uint8 Phase;

		bool follow;
		bool stage;
		bool say;
		bool Data_prince;

		void Reset()
		{
			checkTimer = 0;
			eventTimer = 0;

			area = 0;
			Phase = 0;

			follow = true;
			stage = false;
			say = true;
			Data_prince = false;
		}	

		void UpdateAI(const uint32 uiDiff)
		{
			if (Data_prince == true)
			{
				if (Creature* SargentGraves = me->FindNearestCreature(44293, 30.0f, true))
				{
					me->MonsterSay("Are you often sent to gather things for people ? I suppose a hero's work is never done", 0, 0);
					Data_prince = false;
				}
				
			}
			
			if (me->HasUnitState(UNIT_STATE_CASTING))
				return;

			if (checkTimer <= uiDiff)
			{
				area = me->GetAreaId();					
				checkTimer = 2500;
			}
			else
			{
				checkTimer -= uiDiff;
			}

			if (area == 5398)
			{
				if (me->FindNearestGameObject(205164, 12.0f))
				{
					stage = true;
				}

				//Star Stage 1
				if (stage)
				{
					if (eventTimer < uiDiff)
					{
						switch (Phase)
						{
						case 0:
							follow = false;
							me->GetMotionMaster()->Clear(true);
							me->SetWalk(true);
							Phase++;
							break;
						case 1:
							if (me->GetPositionX() != points[0].GetPositionX() && me->GetPositionY() != points[0].GetPositionY())
							{
								me->GetMotionMaster()->MovePoint(0, points[0]);
								eventTimer = 2000;
							}
							else
							{
								me->NearTeleportTo(-8049.27f, 957.033f, 79.4188f, 0.226921f); //I use teleport because some reason the NPC don't goes to the correct orientation.
								eventTimer = 2000;
								Phase++;
							}
							break;
						case 2:
							if (say)
							{
								say = false;
								me->MonsterSay("What IS this place? Ugh, and that smell...", LANG_UNIVERSAL, 0);
							}

							if (me->GetPositionX() != points[1].GetPositionX() && me->GetPositionY() != points[1].GetPositionY())
							{
								me->GetMotionMaster()->MovePoint(0, points[1]);
								eventTimer = 2000;
							}
							else
							{
								eventTimer = 300;
								Phase++;
							}
							break;
						case 3:
							me->HandleEmoteCommand(EMOTE_ONESHOT_KNEEL);
							eventTimer = 1500;
							Phase++;
							break;
						case 4:
							me->MonsterSay("Some sort of rituals were performed at this altar. It looks like a kind of pagan initiation ritual that Valen once tolme about. Bloody. Disgusting.", LANG_UNIVERSAL, 0);
							eventTimer = 3300;
							Phase++;
							break;
						case 5:
							me->NearTeleportTo(-8048.63f, 966.344f, 79.9703f, 4.77595f);
							eventTimer = 2300;
							Phase++;
							break;
						case 6:
						{
							std::string sText = ("Who do you think - wait - " + std::string(me->GetOwner()->GetName()) + ", Look out behind you!");
							me->MonsterSay(sText.c_str(), LANG_UNIVERSAL, 0);
							eventTimer = 1;
							Phase++;
							break;
						}
						case 7:
							float x, y, z;
							me->GetPosition(x, y, z);
							me->GetMotionMaster()->MovePoint(0, points[1].GetPositionX(), points[1].GetPositionY(), points[1].GetPositionZ() + 8.0f);
							me->UpdateGroundPositionZ(x, y, z);
							eventTimer = 3000;
							Phase++;
							break;
						case 8:
							eventTimer = 3000;
							Phase++;
							break;
						case 9:
							break;
						}
					}
					else
					{
						eventTimer -= uiDiff;
					}
				}
			}

			//Prince Following behavior Part
			if (follow)
			{
				Unit* player = me->GetOwner();
				if (player)
				{
					if (player->IsFlying())
					{
						me->Mount(ARMORED_SNOWY_GRYPHON);
						me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
						me->AddUnitMovementFlag(MOVEMENTFLAG_FLYING);
						float flyspeed = player->GetSpeedRate(MOVE_FLIGHT);
						me->SetSpeed(MOVE_FLIGHT, flyspeed, true);
					}

					if (!player->IsFlying())
					{
						me->RemoveUnitMovementFlag(MOVEMENTFLAG_FLYING);
						float speed = player->GetSpeedRate(MOVE_RUN);
						me->SetSpeed(MOVE_RUN, speed);
						if (player->IsMounted() || player->IsInFlyForm())
							me->Mount(SWIFT_WHITE_STEED);

						if (!player->IsMounted() && !player->IsInFlyForm())
							me->Dismount();
					}
				}
			}
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_anduin_wrynn_summonAI(creature);
	}

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (creature->isQuestGiver())
			player->PrepareQuestMenu(creature->GetGUID());
		player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
		return true;
	}
};


/*######
## npc_supply_sargent_graves
######*/

class npc_supply_sargent_graves : public CreatureScript
{
public:
	npc_supply_sargent_graves() : CreatureScript("npc_supply_sargent_graves") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (creature->isQuestGiver())
			player->PrepareQuestMenu(creature->GetGUID());

		player->SEND_GOSSIP_MENU(907, creature->GetGUID());
		return true;
	}

	bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
	{
		if (quest->GetQuestId() == QUEST_MISSING_PART)
		{
			if (Creature* Prince = creature->FindNearestCreature(44293, 90.0f, true))
				CAST_AI(npc_anduin_wrynn_summon::npc_anduin_wrynn_summonAI, Prince->AI())->Data_prince = true;
		}
		return true;
	}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_supply_sargent_gravesAI(creature);
	}


	struct npc_supply_sargent_gravesAI : public ScriptedAI
	{
		uint64 PlayerGUID;


		npc_supply_sargent_gravesAI(Creature* creature) : ScriptedAI(creature) { }

		uint32 checktimmer;

		void Reset()
		{
			checktimmer = 2 * IN_MILLISECONDS;
		}

		void UpdateAI(const uint32 diff)
		{
			if (checktimmer <= diff)
			{
				std::list<Player*> Players;
				GetPlayerListInGrid(Players, me, 15.0f);

				for (auto _Players : Players)
				{
					if (_Players->GetQuestStatus(26975) == (QUEST_STATUS_INCOMPLETE))
					{
						if (Creature* Anduyn = me->FindNearestCreature(44293, 15.0f, true))
						{
							if (Anduyn->GetOwnerGUID() == _Players->GetGUID())
								_Players->CompleteQuest(26975, false);
						}
					}
				}

			}
			else
			{
				checktimmer -= diff;
			}
		}

	};

};



/*######
## npc_the_black_bishop
######*/


//Bunnys teleport GUIDs, read the description.
uint64 BunnyGUID[4] =
{
	4414239, //1	| 1            4 | This is the most important part of the script. You most
	4413278, //2    |			     | enter correctly  the bunnys GUIDs in orther to teleport
	4414237, //3    |       ▲▲		 | Bishop in the right sequence, that  other is shown on 
	4414238	 //4    | 2     IN     3 | the description. "In" means the room entrance. Enjoy
};

enum eMisc
{
	NPC_BLACK_BISHOP = 44816,
	NPC_BLACK_BISHOP_TELEPORT_BUNNY = 44957
};

class npc_the_black_bishop : public CreatureScript
{
public:
	npc_the_black_bishop() : CreatureScript("npc_the_black_bishop") { }

	struct npc_the_black_bishopAI : public ScriptedAI
	{
		npc_the_black_bishopAI(Creature* creature) : ScriptedAI(creature) {	}

		int b_position;

		uint32 m_uidiagonalslide_timer;
		uint32 m_uidcast_timer;

		Creature* tele_b;

		bool can_cast;
		bool bSay;
		bool bSay2;
		bool bSay3;
		bool bSay4;
		bool bSay5;

		void Reset()
		{
			events.Reset();
			me->SetReactState(REACT_AGGRESSIVE);

			b_position = 0;

			can_cast = false;
			bSay = false;
			bSay2 = false;
			bSay3 = false;
			bSay4 = false;
			bSay5 = false;
		}

		void EnterEvadeMode()
		{
			Unit* target = me->getVictim();

			if (target && target->isAlive() && target->GetTypeId() == TYPEID_PLAYER)
				return;
			else
				ScriptedAI::EnterEvadeMode();
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_MINDBLAST, 1000);
			me->MonsterSay("The game is afoot! But you are mere pawn, I am ...  THE BLACK BISHOP!", LANG_UNIVERSAL, 0);
			m_uidiagonalslide_timer = 1;
			m_uidcast_timer = 1;
		}

		int NextCorner(int b_position)
		{
			if (b_position == 1 || b_position == 2)
			{
				b_position += 2;
				return b_position;
			}
			else if (b_position == 3 || b_position == 4)
			{
				b_position -= 2;
				return b_position;
			}
			else
				return b_position = irand(1, 4);
		}

		//To find my bunnys :)
		Creature* FindCreatureNear(WorldObject* searchObject, uint32 guid) const
		{
			Creature* creature = NULL;
			CellCoord p(WoWSource::ComputeCellCoord(searchObject->GetPositionX(), searchObject->GetPositionY()));
			Cell cell(p);

			WoWSource::CreatureWithDbGUIDCheck target_check(searchObject, guid);
			WoWSource::CreatureSearcher<WoWSource::CreatureWithDbGUIDCheck> checker(searchObject, creature, target_check);

			TypeContainerVisitor<WoWSource::CreatureSearcher <WoWSource::CreatureWithDbGUIDCheck>, GridTypeMapContainer > unit_checker(checker);
			cell.Visit(p, unit_checker, *searchObject->GetMap(), *searchObject, searchObject->GetGridActivationRange());

			return creature;
		}

		void UpdateAI(const uint32 diff)
		{

			if (!UpdateVictim())
				return;

			events.Update(diff);

			if (me->HasUnitState(UNIT_STATE_CASTING))
				return;

			if (me->HealthAbovePct(61))
			{
				if (m_uidcast_timer <= diff)
				{
					events.ScheduleEvent(EVENT_COMBAT, 25);
					m_uidcast_timer = 2000;
				}
				else
				{
					m_uidcast_timer -= diff;
				}
			}

			if (me->HealthBelowPct(60) && me->HealthAbovePct(20))
			{
				if (!bSay)
				{
					bSay = true;
					me->MonsterSay("The bishop moves diagonally!", LANG_UNIVERSAL, 0);
				}

				me->StopMoving();

				if (m_uidiagonalslide_timer <= diff)
				{
					events.ScheduleEvent(EVENT_MOVE_DIAGONALLY, 1000);
					m_uidiagonalslide_timer = 3000;
				}
				else
				{
					m_uidiagonalslide_timer -= diff;
				}

				if (can_cast == true)
				{
					can_cast = false;
					events.ScheduleEvent(EVENT_COMBAT, 25);
				}

				if (me->HealthBelowPct(50))
				{
					if (!bSay2)
					{
						bSay2 = true;
						DoCast(me, SPELL_POWER_SHIELSD);
						me->MonsterSay("Bishop threatens pawn...", LANG_UNIVERSAL, 0);
					}
				}

				if (me->HealthBelowPct(25))
				{
					if (!bSay3)
					{
						bSay3 = true;
						DoCast(me, SPELL_POWER_SHIELSD);
						me->MonsterSay("Check!", LANG_UNIVERSAL, 0);
					}
				}
			}

			if (me->HealthBelowPct(20))
			{
				if (m_uidcast_timer <= diff)
				{
					events.ScheduleEvent(EVENT_COMBAT, 25);
					m_uidcast_timer = 2000;
				}
				else
				{
					m_uidcast_timer -= diff;
				}

				if (!bSay4)
				{
					bSay4 = true;
					me->MonsterSay("Bishop threatens pawn...", LANG_UNIVERSAL, 0);
				}

				if (me->HealthBelowPct(10))
				{
					if (!bSay5)
					{
						bSay5 = true;
						me->MonsterSay("The games isn't over yet...", LANG_UNIVERSAL, 0);
					}
				}
			}

			if (uint32 eventId = events.ExecuteEvent())
			{
				Unit* target = me->getVictim();
				switch (eventId)
				{
				case EVENT_MINDBLAST:
					DoCast(SPELL_MIND_BLAST);
					break;
				case EVENT_PENITENCE:
					me->CastSpell(target, SPELL_PENITENCE, true);
					break;
				case EVENT_COMBAT:
				{
					int rand = irand(1, 2);

					switch (rand)
					{
					case 1:
						events.ScheduleEvent(EVENT_MINDBLAST, 300);
						break;
					case 2:
						events.ScheduleEvent(EVENT_PENITENCE, 300);
						break;
					}
				} break;
				case EVENT_MOVE_DIAGONALLY:
				{
					tele_b = me->FindNearestCreature(NPC_BLACK_BISHOP_TELEPORT_BUNNY, 4.0f, true);
					if (!tele_b)
					{
						b_position = irand(1, 4);
					}
					else
					{
						b_position = NextCorner(b_position);
					}
					tele_b = FindCreatureNear(me, BunnyGUID[b_position - 1]);
					me->CastSpell(tele_b, SPELL_DIAGONAL_SLIDE, true);
					events.ScheduleEvent(EVENT_TELEPORTDELAY, 250);
				} break;
				case EVENT_TELEPORTDELAY:
					me->NearTeleportTo(tele_b->GetPositionX(), tele_b->GetPositionY(), tele_b->GetPositionZ() - 1.5f, tele_b->GetOrientation());
					break;
				}
			}
			DoMeleeAttackIfReady();
		}

		void JustDied(Unit* killer/*killer*/)
		{
			me->MonsterSay("Pawn ... takes ... bishop ... ", LANG_UNIVERSAL, 0);
		}

	private:
		EventMap events;
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_the_black_bishopAI(creature);
	}
};


/*######
## npc_the_black_bishop_teleport_bunny
######*/

class npc_the_black_bishop_teleport_bunny : public CreatureScript
{
public:

	npc_the_black_bishop_teleport_bunny()
		: CreatureScript("npc_the_black_bishop_teleport_bunny")
	{
	}

	struct npc_the_black_bishop_teleport_bunnyAI : public ScriptedAI
	{

		npc_the_black_bishop_teleport_bunnyAI(Creature* creature) : ScriptedAI(creature) {}

		void SpellHit(Unit* caster, const SpellInfo* spell)
		{
			if (spell->Id == SPELL_DIAGONAL_SLIDE)
			{
				Creature *bishop = me->FindNearestCreature(NPC_BLACK_BISHOP, 50.0f, true);
				me->CastSpell(bishop, SPELL_DIAGONAL_SLIDE_EFFECT, true);
				bishop->RemoveUnitMovementFlag(MOVEMENTFLAG_FALLING);
				CAST_AI(npc_the_black_bishop::npc_the_black_bishopAI, bishop->AI())->can_cast = true;
			}
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_the_black_bishop_teleport_bunnyAI(creature);
	}

};


/*######
## npc_bunny_samuelson ****************----------->>>>> NOT FINISH TODO::: 
######*/

enum Misc
{
	SAY_UNMASKET = 0,
	SAY_VARIANATTAC = 1,
	SAY_TRANSFORM = 2,
	SAYON_DEAD = 3

};

enum Events
{
	EVENT_SHADOW_CRASH = 1,
	EVENT_SHAOS_SLAM,	
	EVENT_SPIT,
	EVENT_SAMUELSON_UNMASKET
};

enum eEnd
{

	SPELL_SAMUELSON_UNMASKET = 84033,// SAmuleson
	SPELL_SPIT = 75903,// SAmuleson
	SPELL_SHADOW_CRASH = 75903,// SAmuleson
	SPELL_SHAOS_SLAM = 84108,// SAmuleson
	SPELL_SHIELD_PRINCE = 20706,// PRINCIPE
	SPELL_BLESSING_OF_KINGS = 56525,// PRINCIPE
	SPELL_TRANSITUS_SHIELD_BEAM = 48310, // SPELL BARRERA
	SPELL_IMPUNITY = 82548,
	SPELL_FREEZ = 52656,

	NPC_BUNNY1 = 144951,
	NPC_BUNNY2 = 42750,
	NPC_BUNNY3 = 42635,
	NPC_BUNNY4 = 42745,
	NPC_QUEST_BUNNY = 44979,
	NPC_PRINCIPE = 1747,
	NPC_VARIAN = 29611,
	NPC_SAMULSON_UNMASKED = 45014,
	NPC_SAMUELSON_NORMAL = 2439,
	NPC_GENN = 45253,
	EQUIP_ID_AXE = 33542,

	QUEST_SAMUELSON_UNMASK = 27106
};
//89299	Twilight Spit
//96126 Samuelson Killed

class npc_bunny_samuelson : public CreatureScript
{
public:
	npc_bunny_samuelson() : CreatureScript("npc_bunny_samuelson") { }

	struct npc_bunny_samuelsonAI : public Scripted_NoMovementAI
	{
		npc_bunny_samuelsonAI(Creature* creature) : Scripted_NoMovementAI(creature){}
		
		Player* player;
		bool can_cast;
		uint32 Can_cast;

		void Reset()
		{
			can_cast = false;
			Can_cast = 15000;
		}

		void UpdateAI(const uint32 uiDiff)
		{
			if (can_cast == true)
			{
				if (Creature* samuelson = me->FindNearestCreature(NPC_SAMUELSON_NORMAL, 90.0f, true))
					me->CastSpell(samuelson, SPELL_TRANSITUS_SHIELD_BEAM, true);
			}
		}

	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_bunny_samuelsonAI(creature);
	}
};

#define GOSSIP_ITEM_SAMUELSON "It's over.Samuelson we know who you are, and I put a stop to your little cathedral scheme. "

class npc_major_samuelson : public CreatureScript
{
public:
	npc_major_samuelson() : CreatureScript("npc_major_samuelson") {}

	CreatureAI* GetAI(Creature* Creature) const
	{
		return new npc_major_samuelsonAI(Creature);
	}

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (creature->isQuestGiver())
			player->PrepareQuestMenu(creature->GetGUID());

		if (player->GetQuestStatus(QUEST_SAMUELSON_UNMASK) == QUEST_STATUS_INCOMPLETE)
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SAMUELSON, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

		player->SEND_GOSSIP_MENU(907, creature->GetGUID());
		return true;

	}
	bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		if (action == GOSSIP_ACTION_INFO_DEF + 1)
		{
			player->CLOSE_GOSSIP_MENU();
			creature->CastSpell(creature, 96126, true);

			CAST_AI(npc_major_samuelson::npc_major_samuelsonAI, creature->AI())->PlayerGUID = player->GetGUID();

			if (!(CAST_AI(npc_major_samuelson::npc_major_samuelsonAI, creature->AI())->EventStarted))
			{
				CAST_AI(npc_major_samuelson::npc_major_samuelsonAI, creature->AI())->EventStarted = true;
			}
		}
		return true;
	}

	struct npc_major_samuelsonAI : public ScriptedAI
	{
		npc_major_samuelsonAI(Creature* creature) : ScriptedAI(creature)
		{
			me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_SHAOS_SLAM, true);
		}

		uint64 PlayerGUID;
		uint32 EventTimer;
		uint8 Phase;
		bool EventStarted;
		bool Move;
		bool EventInProgress;
		uint64 SamuelsonGUID;
		EventMap events;


		void Reset()
		{
			EventInProgress = false;
			events.Reset();
			Phase = 0;
			SamuelsonGUID = 0;
			PlayerGUID = 0;
			EventTimer = 1000;
			EventStarted = false;
			bool Move = false;
			me->RemoveAllAuras();
			me->SetReactState(REACT_PASSIVE);
			me->GetEquipmentId();
			if (me->GetEntry() == NPC_SAMULSON_UNMASKED)
				me->UpdateEntry(NPC_SAMUELSON_NORMAL);
		}


		void EnterEvadeMode()
		{
			Unit* target = me->getVictim();
			if (target && target->isAlive() && target->GetTypeId() == TYPEID_PLAYER)
				return;

			ScriptedAI::EnterEvadeMode();
		}


		void JustDied(Unit* killer/*killer*/)
		{
			me->MonsterSay("Al'golath mal shal'nel...Darkness consumes...", LANG_UNIVERSAL, 0);
			if (Player* target = me->FindNearestPlayer(25.0f))
			{
				if (Creature* varian = me->FindNearestCreature(NPC_VARIAN, 50.0f, true))
				{
					if (Creature* Genn = me->FindNearestCreature(NPC_GENN, 50.0f, true))
					{
						if (Creature* principe = me->FindNearestCreature(NPC_PRINCIPE, 50.0f, true))
						{
							target->ToPlayer()->KilledMonsterCredit(NPC_SAMUELSON_NORMAL);
							varian->RemoveAurasDueToSpell(SPELL_FREEZ);
							Genn->RemoveAurasDueToSpell(SPELL_FREEZ);
							principe->RemoveAurasDueToSpell(SPELL_FREEZ);
						}
					}
				}
			}
		}

		void EnterCombat(Unit* Target)
		{
			events.ScheduleEvent(EVENT_SHADOW_CRASH, 10000);
			events.ScheduleEvent(EVENT_SHAOS_SLAM, 15000);
			events.ScheduleEvent(EVENT_SPIT, 5000);

			if (Creature *Samuelson = Unit::GetCreature(*me, SamuelsonGUID))
			{
				if (Samuelson->isAlive() && !Samuelson->isInCombat())
					Samuelson->AI()->AttackStart(Target);

			}

		}

		void DamageTaken(Unit* attacker, uint32 &/*damage*/)
		{
			if (attacker->GetTypeId() != TYPEID_PLAYER)
				return;

			Unit* victim = NULL;
			if (victim)
				me->getThreatManager().modifyThreatPercent(victim, -100);

			AttackStart(attacker);
			me->AddThreat(attacker, 10005000);
		}

		void DoFreez()
		{
			if (Creature* varian = me->FindNearestCreature(NPC_VARIAN, 50.0f, true))
			{
				if (Creature* Genn = me->FindNearestCreature(NPC_GENN, 50.0f, true))
				{
					if (Creature* principe = me->FindNearestCreature(NPC_PRINCIPE, 50.0f, true))
					{
						varian->CastSpell(varian, SPELL_FREEZ, true); //FREEZ
						Genn->CastSpell(Genn, SPELL_FREEZ, true); //FREEZ
						principe->CastSpell(principe, SPELL_FREEZ, true); //FREEZ
					}
				}
			}
		}

		void RemoveFreez()
		{
			if (Creature* varian = me->FindNearestCreature(NPC_VARIAN, 50.0f, true))
				if (Creature* Genn = me->FindNearestCreature(NPC_GENN, 50.0f, true))
					if (Creature* principe = me->FindNearestCreature(NPC_PRINCIPE, 50.0f, true))
					{
						varian->RemoveAurasDueToSpell(SPELL_FREEZ);
						Genn->RemoveAurasDueToSpell(SPELL_FREEZ);
						principe->RemoveAurasDueToSpell(SPELL_FREEZ);

					}
		}

		void EnterAir() // EN DESARROLLO, SIGUE NADANDO HACIA ARRIBA
		{
			me->HandleEmoteCommand(EMOTE_ONESHOT_LIFTOFF); // nuevo
			me->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
			me->SetDisableGravity(true);
			me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
			me->SetHover(true);

		}

		void UpdateAI(const uint32 diff)
		{
			if (EventStarted)
			{
				if (EventTimer < diff)
				{
					if (Player* player = me->GetPlayer(*me, PlayerGUID))
						if (Creature* principe = me->FindNearestCreature(NPC_PRINCIPE, 50.0f, true))
							if (Creature* varian = me->FindNearestCreature(NPC_VARIAN, 50.0f, true))
								if (Creature* Genn = me->FindNearestCreature(NPC_GENN, 90.0f, true))
								{
									switch (Phase)
									{
									case 0:
									{

										me->MonsterSay("Yes... yes It's all true. I am not ashamed. The power I submit to make mortal Kings to look like insects.!", 0, 0);
										player->KilledMonsterCredit(NPC_QUEST_BUNNY);
										me->SetStandState(UNIT_STAND_STATE_KNEEL);
										EventTimer = 8000;
										Phase++;
										break;
									}
									case 1:
									{
										SetEquipmentSlots(false, EQUIP_ID_AXE, EQUIP_NO_CHANGE, EQUIP_NO_CHANGE);
										me->HandleEmoteCommand(EMOTE_STATE_READY1H);
										EventTimer = 400;
										Phase++;
										break;
									}
									case 2:
									{
										me->MonsterSay("But I am not yet finished. Death to the king.", 0, 0);
										EventTimer = 4000;
										Phase++;
										break;
									}
									case 3:// Salto para Varian
									{
										me->GetMotionMaster()->MoveJump(-8364.65f, 234.359f, 156.991f, 15.0f, 13.0f);
										principe->MonsterSay("Father, watch out,", 0, 0);
										EventTimer = 1000;
										Phase++;
										break;
									}
									case 4:
									{
										me->SetFacingToObject(varian);
										EventTimer = 300;//
										Phase++;
										break;
									}
									case 5:
									{
										varian->HandleEmoteCommand(EMOTE_STATE_READY2HL);
										principe->CastSpell(varian, SPELL_SHIELD_PRINCE, true);
										varian->CastSpell(varian, SPELL_BLESSING_OF_KINGS, true);
										EventTimer = 700;
										Phase++;
										break;
									}
									case 6:
									{
										me->AddAura(SPELL_IMPUNITY, me);
										me->SetStandState(UNIT_STAND_STATE_STAND);
										me->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK2HTIGHT);
										EventTimer = 500;
										Phase++;
										break;
									}
									case 7:
									{
										me->SetStandState(UNIT_STAND_STATE_STAND);
										varian->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK2HTIGHT);
										EventTimer = 300;
										Phase++;
										break;
									}
									case 8:// Salto hacia atras
									{
										uint64 SamuelsonGUID = me->GetGUID();
										varian->RemoveAura(SPELL_SHIELD_PRINCE);
										me->GetMotionMaster()->MoveKnockbackFrom(-8371.04f, 242.061f, 155.348f, 15.0f);
										EventTimer = 2000;
										Phase++;
										break;
									}
									case 9:
									{
										Position const MovePosition = { -8375.73f, 248.51f, 155.346f, 5.37001f };
										me->GetMotionMaster()->MovePoint(0, MovePosition);
										EventTimer = 1500;
										Phase++;
										break;
									}
									case 10:
									{
										me->SetFacingToObject(varian);
										if (Creature* bunny1 = me->FindNearestCreature(NPC_BUNNY1, 90.0f, true))
											CAST_AI(npc_bunny_samuelson::npc_bunny_samuelsonAI, bunny1->AI())->can_cast = true;
										EventTimer = 1000;
										Phase++;
										break;
									}
									case 11:
									{
										// VARIANTE # 1 

										/*Position const fly = {-8375.73f, 248.51f, 155.346f, 5.37001f};
										me->AddAura(16245, me);
										me->HandleEmoteCommand(EMOTE_ONESHOT_LIFTOFF);
										me->AddUnitMovementFlag(MOVEMENTFLAG_DISABLE_GRAVITY | MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
										me->SetSpeed(MOVE_FLIGHT, 0.5f, true);
										me->SetSpeed(MOVE_RUN, 0.5f, true);
										me->SetSpeed(MOVE_WALK, 0.5f, true);
										me->SetSpeed(MOVE_SWIM, 0.5f, true);
										EnterAir();
										Position pos;
										me->GetPosition(&pos);
										pos.m_positionZ += 10.f;
										me->GetMotionMaster()->MovePoint(1, pos.GetPositionX(),pos.GetPositionY(),pos.GetPositionZ(), false);
										*/
										// Variante 2
										me->MonsterYell("Gods of the Shadow, lords of the twilight... give me strength!", 0, 0);
										me->HandleEmoteCommand(ANIM_FLY);
										me->AddUnitMovementFlag(MOVEMENTFLAG_FLYING);
										me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
										Position pos;
										me->GetPosition(&pos);
										pos.m_positionZ += 8.f;
										me->GetMotionMaster()->MoveJump(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), 1, 1);
										EventTimer = 10000;
										Phase++;
										break;
									}
									case 12:
									{
										DoFreez();
										me->RemoveAurasDueToSpell(SPELL_IMPUNITY);
										me->GetEquipmentId();
										me->UpdateEntry(NPC_SAMULSON_UNMASKED);
										me->SetReactState(REACT_AGGRESSIVE);
										EventTimer = 500;
										Phase++;
										break;
									}
									case 13:
									{
										me->setFaction(125);
										me->SetStandState(UNIT_STAND_STATE_STAND);// nuevo
										me->RemoveUnitMovementFlag(MOVEMENTFLAG_FLYING);
										me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
										Position pos;
										me->GetPosition(&pos);
										pos.m_positionZ -= 8.f;
										me->GetMotionMaster()->MoveJump(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), 8, 8);
										EventTimer = 500;
										Phase++;
										break;
									}

									break;
									default:
										break;
									}
								}

				}
				else EventTimer -= diff;
				DoMeleeAttackIfReady();
			}


			if (!UpdateVictim())
				return;
			events.Update(diff);

			if (me->HasUnitState(UNIT_STATE_CASTING))
				return;
			if (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_SHAOS_SLAM:

					DoCast(SPELL_SHAOS_SLAM);
					events.ScheduleEvent(EVENT_SHAOS_SLAM, 15000);
					break;
				case EVENT_SHADOW_CRASH:

					DoCast(SPELL_SHADOW_CRASH);
					events.ScheduleEvent(EVENT_SHADOW_CRASH, 12000);
					break;
				case EVENT_SPIT:

					DoCastRandom(SPELL_SPIT, 50);
					events.RescheduleEvent(EVENT_SPIT, 3000);
					break;
				default:
					break;
				}

			}

		}

	};
};



/*######
## npc_avion ****************----------->>>>> NOT FINISH TODO::: 
######*/
enum avion
{
	NPC_AVION = 50266,
	NPC_AVION_FIJO = 50262
};


class npc_avion : public CreatureScript
{
public:
	npc_avion() : CreatureScript("npc_avion") { }



	CreatureAI* GetAI(Creature* creature) const override
	{
		return new npc_avionAI(creature);
	}


	struct npc_avionAI : public npc_escortAI
	{
		uint64 PlayerGUID;


		npc_avionAI(Creature* creature) : npc_escortAI(creature) { }

		bool isBoarded;
		Player* taxi;

		void Reset() override
		{
			PlayerGUID = 0;
			isBoarded = false;

		}

		void PassengerBoarded(Unit* who, int8 /*seatId*/, bool apply)
		{

			if (apply && who->GetTypeId() == TYPEID_PLAYER)

			{
				me->SetCanFly(true);
				me->AddUnitMovementFlag(MOVEMENTFLAG_DISABLE_GRAVITY);
				isBoarded = true;
				Start(false, true, who->GetGUID(), NULL, false, true);
			}
		}

		void WaypointReached(uint32 waypointId) override
		{
			switch (waypointId)
			{
			case 0:
				me->MonsterSay("estoy en el 0", 0, 0);
				me->CastSpell(me, 68499, true); //OOX Lift Off
				me->SetSpeed(MOVE_FLIGHT, 9.0f, true);

			case 1:
				me->MonsterSay("estoy en el 1", 0, 0);
				break;

			case 2:
				me->MonsterSay("estoy en el 2", 0, 0);
				break;
			}

		}

		void UpdateAI(const uint32 diff)
		{
			npc_escortAI::UpdateAI(diff);
		}
		void UpdateEscortAI(const uint32 diff)
		{
		}

	};

};


/*######
## npc_stormwind_duck_worker 
######*/


#define SPEED_RUN               (1.0f)

class npc_stormwind_duck_worker : public CreatureScript
{
public:
	npc_stormwind_duck_worker()	: CreatureScript("npc_stormwind_duck_worker"){}
	
	struct npc_stormwind_duck_workerAI : public ScriptedAI
	{

		npc_stormwind_duck_workerAI(Creature* creature) : ScriptedAI(creature)
		{
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
		}

		Player* player;
		uint32 checktimmer;
		uint64 playerGUID;
		uint64 PrinceGUID;
		bool runaway;
		bool KillMonster;
		bool emotefear;

		void Reset()
		{
			checktimmer = 2 * IN_MILLISECONDS;	
			playerGUID = 0;
			PrinceGUID = 0;
			emotefear = false;
			runaway = false;
			KillMonster = false;
		}

		bool CheckIfPrinceIsNear(Creature* prince)
		{
			if (prince->GetEntry() == ANDUIN_WRYNN_THRONE)
			{
				std::list<Player*> Players;
				GetPlayerListInGrid(Players, me, 15.0f);
				for (auto _Players : Players)
				{
					if (prince->GetOwnerGUID() == _Players->GetGUID())
						return true;
				}
				
			}
			return false;
		}

		void OnSpellClick(Unit* clicker)
		{
			Creature* Prince = me->FindNearestCreature(ANDUIN_WRYNN_THRONE, 15.0f, true);
			if (!Prince)
				return;
			if (!CheckIfPrinceIsNear(Prince))
				return;
			me->HandleEmote(EMOTE_STATE_COWER);
			me->CastSpell(me, SPELL_FREEZ);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			emotefear = true;
		}

		void SpellHit(Unit* caster, const SpellInfo* spell)
		{
			Creature* Prince = me->FindNearestCreature(ANDUIN_WRYNN_THRONE, 15.0f, true);
			if (!Prince)
				return;
			if (spell->Id == 83577)
			{
				me->RemoveAura(SPELL_FREEZ);
				me->HandleEmote(0);
				switch (urand(0, 3))
				{
				case 0:
					me->MonsterSay("I haven't heard a thing. !I swear!", 0, 0);
					runaway = true;
					break;
				case 1:
					me->MonsterSay("Twilight's Hammers? I don't know anything! Why are you asking me ?", 0, 0);
					runaway = true;
					break;
				case 2:
					me->MonsterSay("! I don't know anything about a cult.! Please let me get back to work...", 0, 0);
					runaway = true;
					break;
				case 3:
					me->MonsterSay("What, that crazy end-of-the-world cult? !if I heard anything you will be the first to know!", 0, 0);
					runaway = true;
					break;
				default:
					break;
				}
			}
		}

		void UpdateAI(const uint32 uiDiff)
		{
			if (checktimmer <= uiDiff)
			{
				if (emotefear)
				{
					me->CastSpell(me, SPELL_FREEZ);
					me->SetSpeed(MOVE_RUN, 0.5f);					
					emotefear = false;
				}
				if (runaway)
				{	
					me->SetSpeed(MOVE_RUN, 0.5f);
					me->GetMotionMaster()->MoveRandom(40.0f);
					me->ForcedDespawn(6 * IN_MILLISECONDS);
					runaway = false;
					KillMonster = true;
				}
				if (KillMonster)
				{
					if (Player* player = me->FindNearestPlayer(15.0f, true))
					{
						player->KilledMonsterCredit(44827, 0);
						me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
						KillMonster = false;
					}
				}
			}
			else
			{
				checktimmer -= uiDiff;
			}
		}
		
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_stormwind_duck_workerAI(creature);
	}	
	
};


void AddSC_stormwind_city()
{
	new npc_stormwind_duck_worker();
	new npc_supply_sargent_graves();
	new npc_avion();
	new npc_major_samuelson();
	new npc_the_black_bishop();
	new npc_the_black_bishop_teleport_bunny();
	new npc_anduin_wrynn_throne();
	new npc_anduin_wrynn_summon();
	new npc_king_varian_wrynn_quest();
	new npc_king_varian_wrynn_the_alliance_way();
    new npc_genn_greymane();
}
