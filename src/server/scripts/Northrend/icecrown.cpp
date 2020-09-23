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

/* ScriptData
SDName: Icecrown
SD%Complete: 100
SDComment: Quest support: 12807
SDCategory: Icecrown
EndScriptData */

/* ContentData
npc_arete
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "SpellAuras.h"

/*######
## npc_arete
######*/

#define GOSSIP_ARETE_ITEM1 "Lord-Commander, I would hear your tale."
#define GOSSIP_ARETE_ITEM2 "<You nod slightly but do not complete the motion as the Lord-Commander narrows his eyes before he continues.>"
#define GOSSIP_ARETE_ITEM3 "I thought that they now called themselves the Scarlet Onslaught?"
#define GOSSIP_ARETE_ITEM4 "Where did the grand admiral go?"
#define GOSSIP_ARETE_ITEM5 "That's fine. When do I start?"
#define GOSSIP_ARETE_ITEM6 "Let's finish this!"
#define GOSSIP_ARETE_ITEM7 "That's quite a tale, Lord-Commander."

enum eArete
{
    GOSSIP_TEXTID_ARETE1        = 13525,
    GOSSIP_TEXTID_ARETE2        = 13526,
    GOSSIP_TEXTID_ARETE3        = 13527,
    GOSSIP_TEXTID_ARETE4        = 13528,
    GOSSIP_TEXTID_ARETE5        = 13529,
    GOSSIP_TEXTID_ARETE6        = 13530,
    GOSSIP_TEXTID_ARETE7        = 13531,

    QUEST_THE_STORY_THUS_FAR    = 12807
};

class npc_arete : public CreatureScript
{
public:
    npc_arete() : CreatureScript("npc_arete") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->isQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_THE_STORY_THUS_FAR) == QUEST_STATUS_INCOMPLETE)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE1, creature->GetGUID());
            return true;
        }

        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF+1:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE2, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+2:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE3, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+3:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE4, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+4:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE5, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+5:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE6, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+6:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ARETE_ITEM7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ARETE7, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF+7:
                player->CLOSE_GOSSIP_MENU();
                player->AreaExploredOrEventHappens(QUEST_THE_STORY_THUS_FAR);
                break;
        }

        return true;
    }
};

/*######
## npc_squire_david
######*/

enum eSquireDavid
{
    QUEST_THE_ASPIRANT_S_CHALLENGE_H                    = 13680,
    QUEST_THE_ASPIRANT_S_CHALLENGE_A                    = 13679,

    NPC_ARGENT_VALIANT                                  = 33448,

    GOSSIP_TEXTID_SQUIRE                                = 14407
};

#define GOSSIP_SQUIRE_ITEM_1 "I am ready to fight!"
#define GOSSIP_SQUIRE_ITEM_2 "How do the Argent Crusader raiders fight?"

class npc_squire_david : public CreatureScript
{
public:
    npc_squire_david() : CreatureScript("npc_squire_david") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (player->GetQuestStatus(QUEST_THE_ASPIRANT_S_CHALLENGE_H) == QUEST_STATUS_INCOMPLETE ||
            player->GetQuestStatus(QUEST_THE_ASPIRANT_S_CHALLENGE_A) == QUEST_STATUS_INCOMPLETE)//We need more info about it.
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SQUIRE_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_SQUIRE_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
        }

        player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_SQUIRE, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF+1)
        {
            player->CLOSE_GOSSIP_MENU();
            creature->SummonCreature(NPC_ARGENT_VALIANT, 8575.451f, 952.472f, 547.554f, 0.38f);
        }
        return true;
    }
};

/*######
## npc_argent_valiant
######*/

enum eArgentValiant
{
    SPELL_CHARGE                = 63010,
    SPELL_SHIELD_BREAKER        = 65147,
    SPELL_KILL_CREDIT           = 63049
};

class npc_argent_valiant : public CreatureScript
{
public:
    npc_argent_valiant() : CreatureScript("npc_argent_valiant") { }

    struct npc_argent_valiantAI : public ScriptedAI
    {
        npc_argent_valiantAI(Creature* creature) : ScriptedAI(creature)
        {
            creature->GetMotionMaster()->MovePoint(0, 8599.258f, 963.951f, 547.553f);
            creature->setFaction(35); //wrong faction in db?
        }

        uint32 uiChargeTimer;
        uint32 uiShieldBreakerTimer;

        void Reset()
        {
            uiChargeTimer = 7000;
            uiShieldBreakerTimer = 10000;
        }

        void MovementInform(uint32 uiType, uint32 /*uiId*/)
        {
            if (uiType != POINT_MOTION_TYPE)
                return;

            me->setFaction(14);
        }

        void DamageTaken(Unit* pDoneBy, uint32& uiDamage)
        {
            if (uiDamage > me->GetHealth() && pDoneBy->GetTypeId() == TYPEID_PLAYER)
            {
                uiDamage = 0;
                pDoneBy->CastSpell(pDoneBy, SPELL_KILL_CREDIT, true);
                me->setFaction(35);
                me->DespawnOrUnsummon(5000);
                me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
                EnterEvadeMode();
            }
        }

        void UpdateAI(const uint32 uiDiff)
        {
            if (!UpdateVictim())
                return;

            if (uiChargeTimer <= uiDiff)
            {
                DoCastVictim(SPELL_CHARGE);
                uiChargeTimer = 7000;
            } else uiChargeTimer -= uiDiff;

            if (uiShieldBreakerTimer <= uiDiff)
            {
                DoCastVictim(SPELL_SHIELD_BREAKER);
                uiShieldBreakerTimer = 10000;
            } else uiShieldBreakerTimer -= uiDiff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_argent_valiantAI(creature);
    }
};

/*######
## npc_guardian_pavilion
######*/

enum eGuardianPavilion
{
    SPELL_TRESPASSER_H                            = 63987,
    AREA_SUNREAVER_PAVILION                       = 4676,

    AREA_SILVER_COVENANT_PAVILION                 = 4677,
    SPELL_TRESPASSER_A                            = 63986,
};

class npc_guardian_pavilion : public CreatureScript
{
public:
    npc_guardian_pavilion() : CreatureScript("npc_guardian_pavilion") { }

    struct npc_guardian_pavilionAI : public Scripted_NoMovementAI
    {
        npc_guardian_pavilionAI(Creature* creature) : Scripted_NoMovementAI(creature) {}

        void MoveInLineOfSight(Unit* who)
        {
            if (me->GetAreaId() != AREA_SUNREAVER_PAVILION && me->GetAreaId() != AREA_SILVER_COVENANT_PAVILION)
                return;

            if (!who || who->GetTypeId() != TYPEID_PLAYER || !me->IsHostileTo(who) || !me->isInBackInMap(who, 5.0f))
                return;

            if (who->HasAura(SPELL_TRESPASSER_H) || who->HasAura(SPELL_TRESPASSER_A))
                return;

            if (who->ToPlayer()->GetTeamId() == TEAM_ALLIANCE)
                who->CastSpell(who, SPELL_TRESPASSER_H, true);
            else
                who->CastSpell(who, SPELL_TRESPASSER_A, true);

        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_guardian_pavilionAI(creature);
    }
};

/*######
## npc_vereth_the_cunning
######*/

enum eVerethTheCunning
{
    NPC_GEIST_RETURN_BUNNY_KC   = 31049,
    NPC_LITHE_STALKER           = 30894,
    SPELL_SUBDUED_LITHE_STALKER = 58151,
};

class npc_vereth_the_cunning : public CreatureScript
{
public:
    npc_vereth_the_cunning() : CreatureScript("npc_vereth_the_cunning") { }

    struct npc_vereth_the_cunningAI : public ScriptedAI
    {
        npc_vereth_the_cunningAI(Creature* creature) : ScriptedAI(creature) {}

        void MoveInLineOfSight(Unit* who)
        {
            ScriptedAI::MoveInLineOfSight(who);

            if (who->GetEntry() == NPC_LITHE_STALKER && me->IsWithinDistInMap(who, 10.0f))
            {
                if (Unit* owner = who->GetCharmer())
                {
                    if (who->HasAura(SPELL_SUBDUED_LITHE_STALKER))
                        {
                            owner->ToPlayer()->KilledMonsterCredit(NPC_GEIST_RETURN_BUNNY_KC, 0);
                            who->ToCreature()->DisappearAndDie();

                    }
                }
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_vereth_the_cunningAI(creature);
    }
};

/*######
* npc_tournament_training_dummy
######*/
enum TournamentDummy
{
    NPC_CHARGE_TARGET         = 33272,
    NPC_MELEE_TARGET          = 33229,
    NPC_RANGED_TARGET         = 33243,

    SPELL_CHARGE_CREDIT       = 62658,
    SPELL_MELEE_CREDIT        = 62672,
    SPELL_RANGED_CREDIT       = 62673,

    SPELL_PLAYER_THRUST       = 62544,
    SPELL_PLAYER_BREAK_SHIELD = 62626,
    SPELL_PLAYER_CHARGE       = 62874,

    SPELL_RANGED_DEFEND       = 62719,
    SPELL_CHARGE_DEFEND       = 64100,
    SPELL_VULNERABLE          = 62665,

    SPELL_COUNTERATTACK       = 62709,

    EVENT_DUMMY_RECAST_DEFEND = 1,
    EVENT_DUMMY_RESET         = 2,
};

class npc_tournament_training_dummy : public CreatureScript
{
    public:
        npc_tournament_training_dummy(): CreatureScript("npc_tournament_training_dummy"){}

        struct npc_tournament_training_dummyAI : Scripted_NoMovementAI
        {
            npc_tournament_training_dummyAI(Creature* creature) : Scripted_NoMovementAI(creature) {}

            EventMap events;
            bool isVulnerable;

            void Reset()
            {
                me->SetControlled(true, UNIT_STATE_STUNNED);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                isVulnerable = false;

                // Cast Defend spells to max stack size
                switch (me->GetEntry())
                {
                    case NPC_CHARGE_TARGET:
                        DoCast(SPELL_CHARGE_DEFEND);
                        break;
                    case NPC_RANGED_TARGET:
                        me->CastCustomSpell(SPELL_RANGED_DEFEND, SPELLVALUE_AURA_STACK, 3, me);
                        break;
                }

                events.Reset();
                events.ScheduleEvent(EVENT_DUMMY_RECAST_DEFEND, 5000);
            }

            void EnterEvadeMode()
            {
                if (!_EnterEvadeMode())
                    return;

                Reset();
            }

            void DamageTaken(Unit* /*attacker*/, uint32& damage)
            {
                damage = 0;
                events.RescheduleEvent(EVENT_DUMMY_RESET, 10000);
            }

            void SpellHit(Unit* caster, SpellInfo const* spell)
            {
                switch (me->GetEntry())
                {
                    case NPC_CHARGE_TARGET:
                        if (spell->Id == SPELL_PLAYER_CHARGE)
                            if (isVulnerable)
                                DoCast(caster, SPELL_CHARGE_CREDIT, true);
                        break;
                    case NPC_MELEE_TARGET:
                        if (spell->Id == SPELL_PLAYER_THRUST)
                        {
                            DoCast(caster, SPELL_MELEE_CREDIT, true);

                            if (Unit* target = caster->GetVehicleBase())
                                DoCast(target, SPELL_COUNTERATTACK, true);
                        }
                        break;
                    case NPC_RANGED_TARGET:
                        if (spell->Id == SPELL_PLAYER_BREAK_SHIELD)
                            if (isVulnerable)
                                DoCast(caster, SPELL_RANGED_CREDIT, true);
                        break;
                }

                if (spell->Id == SPELL_PLAYER_BREAK_SHIELD)
                    if (!me->HasAura(SPELL_CHARGE_DEFEND) && !me->HasAura(SPELL_RANGED_DEFEND))
                        isVulnerable = true;
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                switch (events.ExecuteEvent())
                {
                    case EVENT_DUMMY_RECAST_DEFEND:
                        switch (me->GetEntry())
                        {
                            case NPC_CHARGE_TARGET:
                            {
                                if (!me->HasAura(SPELL_CHARGE_DEFEND))
                                    DoCast(SPELL_CHARGE_DEFEND);
                                break;
                            }
                            case NPC_RANGED_TARGET:
                            {
                                AuraPtr defend = me->GetAura(SPELL_RANGED_DEFEND);
                                if (!defend || defend->GetStackAmount() < 3 || defend->GetDuration() <= 8000)
                                    DoCast(SPELL_RANGED_DEFEND);
                                break;
                            }
                        }
                        isVulnerable = false;
                        events.ScheduleEvent(EVENT_DUMMY_RECAST_DEFEND, 5000);
                        break;
                    case EVENT_DUMMY_RESET:
                        if (UpdateVictim())
                        {
                            EnterEvadeMode();
                            events.ScheduleEvent(EVENT_DUMMY_RESET, 10000);
                        }
                        break;
                }

                if (!UpdateVictim())
                    return;

                if (!me->HasUnitState(UNIT_STATE_STUNNED))
                    me->SetControlled(true, UNIT_STATE_STUNNED);
            }

            void MoveInLineOfSight(Unit* /*who*/){}
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_tournament_training_dummyAI(creature);
        }

};

class npc_hakmund_of_argus : public CreatureScript
{
    public:
        npc_hakmund_of_argus() : CreatureScript("npc_hakmund_of_argus")
        {
        }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_hakmund_of_argusAI(creature);
        }

        struct npc_hakmund_of_argusAI : public ScriptedAI
        {
            npc_hakmund_of_argusAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void UpdateAI(const uint32 diff)
            {
            }
        };
};

enum QUEST_RESCUE_CRUSADERS
{
	QUEST_INTO_THE_WILD_GREEN_YOUNDER = 13045, /*Into The Wild Green Yonder*/
	SPELL_NERUBIAN_WEB_PRISION = 56726,
	SPELL_RIDE_VEHICLE = 56687,
	NPC_CUZADER_CAPTURED = 30907,
	ACTION_START_EVENT = 1,
	EVENT_SAY_TEXT  = 1,  /*Let's get out of here! Quickly!*//*Faster, hero! We must get back to the Argent Vanguard and warn them of the impending attack!*/
	EVENT_SAY_TEX_2 = 2, /*There are hundreds of them! Maybe thousands! They will attack at any moment! I'm sure of it!*/
	EVENT_SAY_TEX_3 = 3, /*Had you not come along I would have died for sure!*/
	EVENT_SAY_TEX_4 = 4, /*They're planning a huge attack! We need to warn Highlord Fordring!*/
	EVENT_SAY_TEX_5 = 5, /*Thank you, hero.*/ /*Thank you, friend, but we're not out of trouble yet!*/	
	EVENT_DESPAWN   = 6 

};

class npc_crusader_captured : public CreatureScript
{
	
public:
	npc_crusader_captured() : CreatureScript("npc_crusader_captured")
	{
	}

	bool OnGossipHello(Player* player, Creature* _Creature)
	{
		if (player->GetQuestStatus(QUEST_INTO_THE_WILD_GREEN_YOUNDER) == QUEST_STATUS_INCOMPLETE)
		{
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Liberar Cruzado Capturado", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
			player->SEND_GOSSIP_MENU(907, _Creature->GetGUID());
		}		
		return true;
	}

	bool OnGossipSelect(Player *player, Creature* creature, uint32 sender, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();
		switch (action)
		{
		case GOSSIP_ACTION_INFO_DEF + 1:
		  {
			creature->RemoveAura(SPELL_NERUBIAN_WEB_PRISION);
			player->CastSpell(creature, 56683);
			player->PlayerTalkClass->SendCloseGossip();
		  }
		break;		
		}
		return true;
	}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_crusader_capturedAI(creature);
	}

	struct npc_crusader_capturedAI : public ScriptedAI
	{
		npc_crusader_capturedAI(Creature* creature) : ScriptedAI(creature)
		{
		}	

		Player* owner;
		EventMap events;
		uint32 emoteTimmer;
		uint32 EventStarted;
		uint32 emoteinterval;				
		bool emoteStartFlag;
		bool sayEvent_text;

		void Reset()
		{
			me->AddAura(SPELL_NERUBIAN_WEB_PRISION, me);	
			emoteTimmer = 1000;				
			emoteStartFlag = true;
			EventStarted = 2000;
			sayEvent_text = false;
			
		}

		void SpellHit(Unit* /*target*/, SpellInfo const* spell)
		{
			if (spell->Id == 56683)
			{					
				owner = me->FindNearestPlayer(10.0f, true);
				me->SetFacingToObject(owner);
				emoteStartFlag = false;
				sayEvent_text = true;
				DoAction(ACTION_START_EVENT);
			}
		}

		void DoAction(int32 const action)
		{
			switch (action)
			{
			case ACTION_START_EVENT:
				events.ScheduleEvent(EVENT_SAY_TEXT, 2500);
				events.ScheduleEvent(EVENT_SAY_TEX_3, 12000);
				events.ScheduleEvent(EVENT_SAY_TEX_4, 16000);
				events.ScheduleEvent(EVENT_SAY_TEX_5, 23000);
				events.ScheduleEvent(EVENT_DESPAWN, 280000);
				break;
			}
		}

		void UpdateAI(const uint32 diff)
		{		

			if (emoteTimmer <= diff)
			{
				if (emoteStartFlag)
				{
					switch (urand(0, 1))
					{
					case 0:
						me->HandleEmote(70);
						break;
					case 1:
						me->HandleEmote(22);
						break;
					}
					emoteTimmer = irand(1000, 3000);
				}
			}
			else
			{
				emoteTimmer -= diff;
			}

			if (sayEvent_text)
			{
				events.Update(diff);
				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
					case EVENT_SAY_TEXT:
						switch (urand(0, 3))
						{
							case 0:
							{
								me->MonsterSay("Let's get out of here! Quickly!", 0, NULL);
								me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
								break;
							}
							case 1:
							{
								me->MonsterSay("Faster, hero! We must get back to the Argent Vanguard and warn them of the impending attack!", 0, NULL);
								me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
								break;
							}
							default:
								break;
						}
						events.ScheduleEvent(EVENT_SAY_TEX_2, 9500);

					case EVENT_SAY_TEX_2:
					{
						me->MonsterSay("There are hundreds of them! Maybe thousands! They will attack at any moment! I'm sure of it!", 0, NULL);
						me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
						break;
					}

					case EVENT_SAY_TEX_3:
					{
						me->MonsterSay("Had you not come along I would have died for sure!", 0, NULL);	
						me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
						break;
					}
					case EVENT_SAY_TEX_4:
					{
						me->MonsterSay("They're planning a huge attack! We need to warn Highlord Fordring!", 0, NULL);
						me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
						break;
					}

					case EVENT_SAY_TEX_5:
					{
						switch (urand(0, 1))
						{
							case 0:
							{
								me->MonsterSay("Thank you, hero.", 0, NULL);
								me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
								break;
							}
							case 1:
							{
								me->MonsterSay("Thank you, friend, but we're not out of trouble yet!", 0, NULL);
								me->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
								break;
							}
						}

					}
					case EVENT_DESPAWN:
						me->ForcedDespawn();
						sayEvent_text = false;
						owner->KilledMonsterCredit(30407);
						break;
					default:
						break;
					}

				}
			}

		}
	};
};

/*Siegemaster Fezzik*/
/*Misión: [78] A Cold Front Approaches ID: 13070*/

enum IceCrowQuest
{
	QUEST_A_COLD_FROTN_APPROACHES = 13070,
	QUEST_THE_LAST_LINE_OF_THEFENCE = 13086
};
class npc_siegemaster_fezzik : public CreatureScript
{
public:
	npc_siegemaster_fezzik() : CreatureScript("npc_siegemaster_fezzik")	{ }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (creature->isQuestGiver())
		{
			player->PrepareQuestMenu(creature->GetGUID());
			player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
			creature->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
		}
		return true;

	}

	bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
	{
		if (quest->GetQuestId() == QUEST_A_COLD_FROTN_APPROACHES)
		{			
			player->SetPhaseMask(66, true);
		}
		
		if (quest->GetPrevQuestId() == QUEST_THE_LAST_LINE_OF_THEFENCE)
		{			
			player->SetPhaseMask(1, true);
		}
		return false;
	}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_siegemaster_fezzikAI(creature);
	}

	struct npc_siegemaster_fezzikAI : public ScriptedAI
	{
		npc_siegemaster_fezzikAI(Creature* creature) : ScriptedAI(creature)	{ }
		
		std::list<uint64> quest_playerList;
		// Timet
		uint32 checkTimer;

		void Reset()
		{
			checkTimer = 2000;
		}

		bool HasQuestComplete(Player* player)
		{
			for (auto splayer : quest_playerList)
			{
				if (splayer == player->GetGUID())
				{
					return true;
					break;
				}
			}

			quest_playerList.push_back(player->GetGUID());
			return false;
		}

		void UpdateAI(const uint32 diff)
		{
			if (checkTimer <= diff)
			{
				// Get nears players, by 10 yards
				std::list<Player*> playerList;
				GetPlayerListInGrid(playerList, me, 10.0f);
				//
				for (auto cPlayer : playerList)
				{
					if (cPlayer->GetQuestStatus(QUEST_A_COLD_FROTN_APPROACHES) == QUEST_STATUS_INCOMPLETE)
					{
						cPlayer->CompleteQuest(QUEST_A_COLD_FROTN_APPROACHES);						
					}

					if (cPlayer->GetPhaseMask() == 1 && cPlayer->getLevel() <= 70)
						return;

					if (!HasQuestComplete(cPlayer))
					{
						if (cPlayer->GetQuestStatus(QUEST_THE_LAST_LINE_OF_THEFENCE) == QUEST_STATUS_REWARDED && cPlayer->GetQuestStatus(13070) == QUEST_STATUS_REWARDED)
						{							
							cPlayer->SetPhaseMask(1, true);
						}
					}
				}
				checkTimer = 2000;
			}
			else
			{
				checkTimer -= diff;
			}
		}
	};
};

class npc_mobs_icecrow : public CreatureScript
{
public:
	npc_mobs_icecrow() : CreatureScript("npc_mobs_icecrow")
	{
	}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_mobs_icecrowAI(creature);
	}

	struct npc_mobs_icecrowAI : public ScriptedAI
	{
		npc_mobs_icecrowAI(Creature* creature) : ScriptedAI(creature)
		{
		}	

		void Reset()
		{
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
		}

		void UpdateAI(const uint32 diff)
		{
		}
	};
};


/*Misión: [80] [Destroying the Altars] ID: 13119*/

enum MyEadasdnum
{
	spell_Kill_credit = 57852,
	spell_item_cast = 57853
};
class npc_altar_bunny : public CreatureScript
{
public:
	npc_altar_bunny() : CreatureScript("npc_altar_bunny")
	{
	}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_altar_bunnyAI(creature);
	}

	struct npc_altar_bunnyAI : public ScriptedAI
	{
		npc_altar_bunnyAI(Creature* creature) : ScriptedAI(creature)
		{
		}
		
		uint32 killcreadit;
		bool is_spell_hit;
		uint32 ChekTimmer;

		void Reset()
		{
			ChekTimmer = 2000;
			killcreadit = me->GetEntry();
			is_spell_hit = false;
		}

		void SpellHit(Unit* _player, const SpellInfo* spell)
		{
			if (spell->Id == spell_item_cast)
			{							
				is_spell_hit = true;
			}
		}

		void UpdateAI(const uint32 diff)
		{
			if (ChekTimmer <= diff)
			{
				if (is_spell_hit)
				{
					if (Player* Caster = me->FindNearestPlayer(10.0f, true))
					{
						Caster->KilledMonsterCredit(me->GetEntry(), 0);
						is_spell_hit = false;
					}
				}
				ChekTimmer = 2000;
			}
			else
			{
				ChekTimmer -= diff;
			}
		}
	};
};

/*######
# spell_master_summoner_staff - 57853
#######*/

enum Npc_Destroy_Altars
{
	NPC_ALTAR_BUNNY_1 = 30742,
	NPC_ALTAR_BUNNY_2 = 30744,
	NPC_ALTAR_BUNNY_3 = 30745,
	NPC_ALTAR_BUNNY_4 = 30950
};



class spell_drake_arpon : public SpellScriptLoader
{
public:
	spell_drake_arpon() : SpellScriptLoader("spell_drake_arpon") { }

	class spell_drake_arpon_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_drake_arpon_SpellScript);

		uint32 basepoints = 0;

		void HandleAfterHit()
		{

			if (Unit* Player = GetCaster()->ToPlayer()) /*damage done to the target*/
			{				
				if (Unit* target = GetHitUnit())
				{
					basepoints = GetHitDamage() * 30; /*Formula  30% healing */					
					int32 bp0 = -(sSpellMgr->GetSpellInfo(56570)->Effects[0].BasePoints) + basepoints;
					Player->CastCustomSpell(target, 56570, &bp0, NULL, NULL, true);

				}
			}
		}

		
		void Register()
		{
			AfterHit += SpellHitFn(spell_drake_arpon_SpellScript::HandleAfterHit);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_drake_arpon_SpellScript();
	}
};

/*######
# spell_master_summoner_staff - 57853
#######*/

class npc_vil_bunny : public CreatureScript
{
public:
	npc_vil_bunny() : CreatureScript("npc_vil_bunny")
	{
	}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_vil_bunnyAI(creature);
	}

	struct npc_vil_bunnyAI : public ScriptedAI
	{
		npc_vil_bunnyAI(Creature* creature) : ScriptedAI(creature)
		{
		}

		uint32 killcreadit;
		bool isQuestComplete;
		uint32 ChekTimmer;

		void Reset()
		{
			ChekTimmer = 2000;
			killcreadit = me->GetEntry();
			isQuestComplete = false;
		}

		

		void UpdateAI(const uint32 diff)
		{
			if (ChekTimmer <= diff)
			{
				std::list<Player*> playerList;
				GetPlayerListInGrid(playerList, me, 25.0f);
				if (!isQuestComplete)
				{
					for (auto player : playerList)
					{
						if (player->GetQuestStatus(13145) == QUEST_STATUS_INCOMPLETE)
						{
							player->KilledMonsterCredit(me->GetEntry());
							isQuestComplete = true;
						}
					}
				}
				ChekTimmer = 2000;
			}
			else
			{
				ChekTimmer -= diff;
			}
		}
	};
};


void AddSC_icecrown()
{
	new npc_vil_bunny();
	new npc_altar_bunny();
	new npc_mobs_icecrow();
	new npc_siegemaster_fezzik();
	new npc_crusader_captured();
    new npc_hakmund_of_argus();
    new npc_arete;
    new npc_squire_david;
    new npc_argent_valiant;
    new npc_guardian_pavilion;
    new npc_vereth_the_cunning;
    new npc_tournament_training_dummy;
}
