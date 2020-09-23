#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "SpellScript.h"
#include "GameObjectAI.h"
#include "Group.h"

/*######
## mob_master_shang_xi - 53566
######*/

enum MasterShangXiMisc
{
	ACTION_TALK = 1,
	NPC_MASTER_SHANG_XI__                   = 53566,

	SPELL_SNATCH_MASTERS_FLAME              = 114746,
	SPELL_CREATE_THE_MASTERS_FLAME          = 114611,
	SPELL_THE_MASTERS_FLAME                 = 114610,
	QUEST_THE_LESSON_OF_THE_BURNING_SCROLL_ = 29408
};

class mob_master_shang_xi : public CreatureScript
{
public:
	mob_master_shang_xi() : CreatureScript("mob_master_shang_xi") { }

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

	bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
	{
		//if (quest->GetQuestId() == 29408) // La lecon du parchemin brulant
		//{
		//	//creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
		//	//creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);

		//}
		return true;
	}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_master_shang_xi_AI(creature);
	}

	struct mob_master_shang_xi_AI : public ScriptedAI
	{
		mob_master_shang_xi_AI(Creature* creature) : ScriptedAI(creature) {	}

		//uint32 checkPlayersTime;

		void Reset()
		{
			//checkPlayersTime = 2000;
		}

		//void SpellHit(Unit* caster, const SpellInfo* pSpell)
		//{
		//	if (pSpell->Id == 114746) // Attraper la flamme
		//	{
		//		if (caster->GetTypeId() == TYPEID_PLAYER)
		//		{
		//			if (caster->ToPlayer()->GetQuestStatus(29408) == QUEST_STATUS_INCOMPLETE)
		//			{
		//				//me->CastSpell(caster, SPELL_CREATE_THE_MASTERS_FLAME, true);
		//				me->AddAura(SPELL_THE_MASTERS_FLAME, caster);// quest creadit
		//				me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
		//				//me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
		//				Talk(0);
		//			}
		//		}
		//	}
		//}

		void TalkToPlayer()
		{
			Talk(0);
		}

		void UpdateAI(const uint32 diff)
		{
			//if (checkPlayersTime <= diff)
			//{
			//	std::list<Player*> playerList;
			//	GetPlayerListInGrid(playerList, me, 5.0f);

			//	bool playerWithQuestNear = false;
			//	for (auto player : playerList)
			//	{
			//		if (player->GetQuestStatus(29408) == QUEST_STATUS_INCOMPLETE)
			//			if (!player->HasItemCount(80212))
			//				playerWithQuestNear = true;
			//	}

			//	//if (playerWithQuestNear && !me->HasAura(114610))
			//	//{
			//	//	me->CastSpell(me, 114600);
			//	//	me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
			//	//	me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
			//	//}
			//	//else if (!playerWithQuestNear && me->HasAura(114610))
			//	//{
			//	//	me->RemoveAurasDueToSpell(114610);
			//	//	me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
			//	//	me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
			//	//}

			//	checkPlayersTime = 2000;
			//}
			//else
			//	checkPlayersTime -= diff;
		}
	};
};

/*######
## npc_the_masters_flame - 59591
######*/

class npc_the_masters_flame : public CreatureScript
{
public:

	npc_the_masters_flame()
		: CreatureScript("npc_the_masters_flame")
	{
	}

	struct npc_the_masters_flameAI : public ScriptedAI
	{
		npc_the_masters_flameAI(Creature* creature) : ScriptedAI(creature) {}

		//uint32 updateTimer;

		void Reset()
		{
			//updateTimer = 2500;
		}

		void UpdateAI(const uint32 uiDiff)
		{
			//if (updateTimer <= uiDiff)
			//{
			//	updateTimer = 2500;
			//}
			//else
			//	updateTimer -= uiDiff;
		}
	};

	bool OnGossipHello(Player* player, Creature* creature)
	{
		if (player->GetQuestStatus(QUEST_THE_LESSON_OF_THE_BURNING_SCROLL_) == QUEST_STATUS_INCOMPLETE && !player->HasAura(SPELL_THE_MASTERS_FLAME))
		{
			// Cast Snatch Master's Flame
			player->CastSpell(player, SPELL_SNATCH_MASTERS_FLAME, true);
			// Create required item and cast aura
			player->CastSpell(player, SPELL_CREATE_THE_MASTERS_FLAME, true);
			// Look for master 
			std::list<Creature*> master;
			GetCreatureListWithEntryInGrid(master, creature, NPC_MASTER_SHANG_XI__, 10.0f);
			for (std::list<Creature*>::iterator iter = master.begin(); iter != master.end(); ++iter)
				CAST_AI(mob_master_shang_xi::mob_master_shang_xi_AI, (*iter)->AI())->TalkToPlayer();
		}

		return true;
	}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_the_masters_flameAI(creature);
	}
};

/*######
## go_wandering_weapon_rack - 210005
######*/

enum WeaponRackMisc
{
	GO_WANDERING_WEAPON_RACK = 210005,

	QUEST_THE_LESSON_OF_THE_IRON_BOUGH_1 = 30027,
	QUEST_THE_LESSON_OF_THE_IRON_BOUGH_2 = 30033,
	QUEST_THE_LESSON_OF_THE_IRON_BOUGH_3 = 30034,
	QUEST_THE_LESSON_OF_THE_IRON_BOUGH_4 = 30035,
	QUEST_THE_LESSON_OF_THE_IRON_BOUGH_5 = 30036,
	QUEST_THE_LESSON_OF_THE_IRON_BOUGH_6 = 30037,
	QUEST_THE_LESSON_OF_THE_IRON_BOUGH_7 = 30038,

	ITEM_TRAINEES_STAFF = 73209,
	ITEM_TRAINEES_HAND_FAN = 76392,
	ITEM_TRAINEES_SPELLBLADE = 76390,
	ITEM_TRAINEES_CROSSBOW = 73211,
	ITEM_TRAINEES_BOOK_OF_PRAYERS = 76393,
	ITEM_TRAINEES_MACE = 73207,
	ITEM_TRAINEES_DAGGER_1 = 73212,
	ITEM_TRAINEES_DAGGER_2 = 73208,
	ITEM_TRAINEES_SHIELD = 73213,
	ITEM_TRAINEES_AXE = 76391,
	ITEM_TRAINEES_SWORD = 73210,
};

class go_wandering_weapon_rack : public GameObjectScript
{
public:
	go_wandering_weapon_rack() : GameObjectScript("go_wandering_weapon_rack") { }

	bool sendLoot;

	bool OnGossipHello(Player* player, GameObject* go)
	{
		if (player->GetQuestStatus(QUEST_THE_LESSON_OF_THE_IRON_BOUGH_1) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(ITEM_TRAINEES_STAFF))
		{
			sendLoot = true;
		}
		else if (player->GetQuestStatus(QUEST_THE_LESSON_OF_THE_IRON_BOUGH_2) == QUEST_STATUS_INCOMPLETE && (!player->HasItemCount(ITEM_TRAINEES_HAND_FAN) || !player->HasItemCount(ITEM_TRAINEES_SPELLBLADE)))
		{
			sendLoot = true;
		}
		else if (player->GetQuestStatus(QUEST_THE_LESSON_OF_THE_IRON_BOUGH_3) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(ITEM_TRAINEES_CROSSBOW))
		{
			sendLoot = true;
		}
		else if (player->GetQuestStatus(QUEST_THE_LESSON_OF_THE_IRON_BOUGH_4) == QUEST_STATUS_INCOMPLETE && (!player->HasItemCount(ITEM_TRAINEES_BOOK_OF_PRAYERS) || !player->HasItemCount(ITEM_TRAINEES_MACE)))
		{
			sendLoot = true;
		}
		else if (player->GetQuestStatus(QUEST_THE_LESSON_OF_THE_IRON_BOUGH_5) == QUEST_STATUS_INCOMPLETE && (!player->HasItemCount(ITEM_TRAINEES_DAGGER_1) || !player->HasItemCount(ITEM_TRAINEES_DAGGER_2)))
		{
			sendLoot = true;
		}
		else if (player->GetQuestStatus(QUEST_THE_LESSON_OF_THE_IRON_BOUGH_6) == QUEST_STATUS_INCOMPLETE && (!player->HasItemCount(ITEM_TRAINEES_SHIELD) || !player->HasItemCount(ITEM_TRAINEES_AXE)))
		{
			sendLoot = true;
		}
		else if (player->GetQuestStatus(QUEST_THE_LESSON_OF_THE_IRON_BOUGH_7) == QUEST_STATUS_INCOMPLETE && !player->HasItemCount(ITEM_TRAINEES_SWORD))
		{
			sendLoot = true;
		}
		else
		{
			sendLoot = false;
		}

		if (sendLoot)
		{
			Loot* loot = 0;
			loot = &go->loot;
			loot->clear();
			loot->FillLoot(GO_WANDERING_WEAPON_RACK, LootTemplates_Gameobject, player, true, false, go->GetLootMode());
			player->SendLoot(go->GetGUID(), LOOT_CORPSE);
			sendLoot = false;
		}
		return true;
	}
};

/*######
## mob_training_target - 53714, 57873
######*/

enum TrainingTargetMisc
{
	NPC_ASPIRING_TRAINEE_MALE = 53565,
};

class mob_training_target : public CreatureScript
{
public:
	mob_training_target() : CreatureScript("mob_training_target") { }
	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_training_targetAI(creature);
	}

	struct mob_training_targetAI : public ScriptedAI
	{
		mob_training_targetAI(Creature* creature) : ScriptedAI(creature) {}

		uint32 emoteTimer;
		uint32 checkTimer;
		uint32 nextEmote;

		void Reset()
		{
			me->SetReactState(REACT_PASSIVE);
			emoteTimer = 1000;
			checkTimer = 1500;
			nextEmote = 0;
		}

		void EnterCombat()
		{
			return;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!me->isInCombat())
			{
				//Cosmetic, Aspiring Trainee emotes.
				if (emoteTimer <= diff)
				{
					switch (irand(0, 3))
					{
					case 0:
						nextEmote = EMOTE_ONESHOT_PALMSTRIKE;
						break;
					case 1:
						nextEmote = EMOTE_ONESHOT_MONKOFFENSE_PARRYUNARMED;
						break;
					case 2:
						nextEmote = EMOTE_ONESHOT_MONKOFFENSE_ATTACKUNARMED;
						break;
					case 3:
						nextEmote = EMOTE_ONESHOT_MONKOFFENSE_ATTACKUNARMEDOFF;
						break;
					}
					if (Creature* trainee = me->FindNearestCreature(NPC_ASPIRING_TRAINEE_MALE, 1.85f, true))
					{
						me->HandleEmoteCommand(EMOTE_ONESHOT_WOUND);
						trainee->HandleEmoteCommand(nextEmote);
					}
					emoteTimer = irand(3640, 4970);
				}
				else
				{
					emoteTimer -= diff;
				}
			}
			else
			{
				//Stop punshing the target.
				if (checkTimer <= diff)
				{
					if (Creature* trainee = me->FindNearestCreature(NPC_ASPIRING_TRAINEE_MALE, 1.85f, true))
					{
						trainee->HandleEmoteCommand(EMOTE_STATE_STAND);
					}
					checkTimer = 1500;
				}
				else
				{
					checkTimer -= diff;
				}
			}
		}
	};
};

/*######
## mob_instructor_qun - 57748
## Support for Quest: [The Lesson of the Iron Bough]
######*/

enum InstructorQunMiscEvents
{
	EVENT_PLAY_EMOTE = 1,
};

enum InstructorQunMisc
{
	NPC_ASPIRING_TRAINEE_FEMALE = 65469,
};

class mob_instructor_qun : public CreatureScript
{
public:
	mob_instructor_qun() : CreatureScript("mob_instructor_qun") { }
	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_instructor_qunAI(creature);
	}

	struct mob_instructor_qunAI : public ScriptedAI
	{
		mob_instructor_qunAI(Creature* creature) : ScriptedAI(creature) {}

		uint32 updateTimer;
		uint32 ownEmoteTimer;
		uint32 nextEmote;

		void Reset()
		{
			updateTimer = 300;
			ownEmoteTimer = 1000;
			nextEmote = 0;
		}

		void UpdateAI(const uint32 diff)
		{
			events.Update(diff);
			//Support for Quest: [The Lesson of the Iron Bough] visual effects for players.
			if (updateTimer <= diff)
			{
				//Allways keep spawned the weapon rack, becouse Chest despawn after loot.
				std::list<GameObject*> rackList;
				GetGameObjectListWithEntryInGrid(rackList, me, GO_WANDERING_WEAPON_RACK, 100.0f);
				for (std::list<GameObject*>::const_iterator itr = rackList.begin(); itr != rackList.end(); ++itr)
				{
					if (!(*itr)->isSpawned())
						(*itr)->Respawn();
				}
				//Update the visibility for all near players.
				std::list<Player*> playerList;
				GetPlayerListInGrid(playerList, me, 100.0f);
				for (auto player : playerList)
				{
					if (player->GetPhaseMask() == 8)
						player->UpdateTriggerVisibility();
				}
				updateTimer = 300;
			}
			else
			{
				updateTimer -= diff;
			}
			//Cosmetic, Instructor Qun emotes.
			if (ownEmoteTimer <= diff)
			{
				switch (irand(0, 3))
				{
				case 0:
					nextEmote = EMOTE_ONESHOT_MONKOFFENSE_ATTACKUNARMED;
					break;
				case 1:
					nextEmote = EMOTE_ONESHOT_MONKOFFENSE_SPECIALUNARMED;
					break;
				case 2:
					nextEmote = EMOTE_ONESHOT_MONKOFFENSE_PARRYUNARMED;
					break;
				case 3:
					nextEmote = EMOTE_ONESHOT_PALMSTRIKE;
					break;
				}
				me->HandleEmoteCommand(nextEmote);
				events.ScheduleEvent(EVENT_PLAY_EMOTE, 1120);
				ownEmoteTimer = irand(3700, 6040);
			}
			else
			{
				ownEmoteTimer -= diff;
			}
			//Cosmetic, Trainee playing emotes at the same time.
			if (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_PLAY_EMOTE:
				{
					//Aspiring Trainee Emotes
					std::list<Creature*> traineeList;
					GetCreatureListWithEntryInGrid(traineeList, me, NPC_ASPIRING_TRAINEE_MALE, 10.0f);
					GetCreatureListWithEntryInGrid(traineeList, me, NPC_ASPIRING_TRAINEE_FEMALE, 10.0f);
					for (std::list<Creature*>::iterator iter = traineeList.begin(); iter != traineeList.end(); ++iter)
						(*iter)->HandleEmoteCommand(nextEmote);

					events.CancelEvent(EVENT_PLAY_EMOTE);
				} break;
				}
			}
		}
	private:
		EventMap events;
	};
};

/*######
## mob_instructor_zhi - 61411
######*/

enum InstructorZhiEvents
{
	EVENT_PLAY_EMOTE_ZIN = 1,
};

enum InstructorZhiMisc
{
	NPC_TUSHUI_TRAINEE_MALE = 65471,
	NPC_TUSHUI_TRAINEE_FEMALE = 54587,
};

class mob_instructor_zhi : public CreatureScript
{
public:
	mob_instructor_zhi() : CreatureScript("mob_instructor_zhi") { }
	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_instructor_zhiAI(creature);
	}

	struct mob_instructor_zhiAI : public ScriptedAI
	{
		mob_instructor_zhiAI(Creature* creature) : ScriptedAI(creature) {}

		uint32 ownEmoteTimer;
		uint32 nextEmote;

		void Reset()
		{
			ownEmoteTimer = 1000;
			nextEmote = 0;
		}

		void UpdateAI(const uint32 diff)
		{
			events.Update(diff);
			//Cosmetic, Instructor Zhi emotes.
			if (ownEmoteTimer <= diff)
			{
				switch (irand(0, 3))
				{
				case 0:
					nextEmote = EMOTE_ONESHOT_MONKOFFENSE_ATTACKUNARMED;
					break;
				case 1:
					nextEmote = EMOTE_ONESHOT_MONKOFFENSE_SPECIALUNARMED;
					break;
				case 2:
					nextEmote = EMOTE_ONESHOT_MONKOFFENSE_PARRYUNARMED;
					break;
				case 3:
					nextEmote = EMOTE_ONESHOT_PALMSTRIKE;
					break;
				}
				me->HandleEmoteCommand(nextEmote);
				events.ScheduleEvent(EVENT_PLAY_EMOTE_ZIN, 1118);
				ownEmoteTimer = irand(3700, 6040);
			}
			else
			{
				ownEmoteTimer -= diff;
			}

			//Cosmetic, Tushui Trainee playing emotes at the same time.
			if (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_PLAY_EMOTE_ZIN:
				{
					//Tushui Trainee Emotes
					std::list<Creature*> traineeList;
					GetCreatureListWithEntryInGrid(traineeList, me, NPC_TUSHUI_TRAINEE_MALE, 7.0f);
					GetCreatureListWithEntryInGrid(traineeList, me, NPC_TUSHUI_TRAINEE_FEMALE, 7.0f);
					for (std::list<Creature*>::iterator iter = traineeList.begin(); iter != traineeList.end(); ++iter)
					{
						if (!(*iter)->isInCombat())
							(*iter)->HandleEmoteCommand(nextEmote);
					}
					events.CancelEvent(EVENT_PLAY_EMOTE_ZIN);
				} break;
				}
			}
		}
	private:
		EventMap events;
	};
};

/*######
## mob_quiet_lam - 57752
######*/

enum QuietLamEvents
{
	EVENT_PLAY_EMOTE_IRONFIST = 1,
};

enum QuietLamMisc
{
	NPC_ASPIRING_TRAINEE_MALE_ = 53565,
	NPC_IRONFIST_ZHOU = 57753
};

class mob_quiet_lam : public CreatureScript
{
public:
	mob_quiet_lam() : CreatureScript("mob_quiet_lam") { }
	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_quiet_lamAI(creature);
	}

	struct mob_quiet_lamAI : public ScriptedAI
	{
		mob_quiet_lamAI(Creature* creature) : ScriptedAI(creature) {}

		uint32 emoteTimer;
		uint32 nextEmote;

		void Reset()
		{
			emoteTimer = 1000;
			nextEmote = 0;
		}

		void UpdateAI(const uint32 diff)
		{
			events.Update(diff);
			//Cosmetic, QuietLam emotes.
			if (emoteTimer <= diff)
			{
				switch (irand(0, 3))
				{
				case 0:
					nextEmote = EMOTE_ONESHOT_MONKOFFENSE_ATTACKUNARMED;
					break;
				case 1:
					nextEmote = EMOTE_ONESHOT_MONKOFFENSE_SPECIALUNARMED;
					break;
				case 2:
					nextEmote = EMOTE_ONESHOT_MONKOFFENSE_PARRYUNARMED;
					break;
				case 3:
					nextEmote = EMOTE_ONESHOT_PALMSTRIKE;
					break;
				}
				me->HandleEmoteCommand(nextEmote);
				events.ScheduleEvent(EVENT_PLAY_EMOTE_IRONFIST, 1100);
				emoteTimer = irand(3700, 6040);
			}
			else
			{
				emoteTimer -= diff;
			}

			//Cosmetic, IronFist Zhou playing emotes.
			if (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_PLAY_EMOTE_IRONFIST:
				{
					if (Creature *iron = me->FindNearestCreature(NPC_IRONFIST_ZHOU, 1.5f))
					{
						iron->HandleEmoteCommand(nextEmote);
					}
					events.CancelEvent(EVENT_PLAY_EMOTE_IRONFIST);
				} break;
				}
			}
		}
	private:
		EventMap events;
	};
};

/*######
## mob_tushui_trainee - 54587, 65471
######*/

enum TushuiTraineeMisc
{
	NPC_MASTER_SHANG_XI_ = 53566,
	SPELL_BLACKOUT_KICK_ = 100784,
	AREA_THE_DAWNING_VALLEY = 5825,
};

enum TushuiTraineeEvents
{
	EVENT_TUSHUI_TALK = 1,
	EVENT_TUSHUI_RUN = 2,
	EVENT_TUSHUI_BLACKOUT_KICK = 3,
	EVENT_TUSHUI_GOHOME = 4,
	EVENT_TUSHUI_RESET = 5
};

class mob_tushui_trainee : public CreatureScript
{
public:
	mob_tushui_trainee() : CreatureScript("mob_tushui_trainee") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_tushui_trainee_AI(creature);
	}

	struct mob_tushui_trainee_AI : public ScriptedAI
	{
		mob_tushui_trainee_AI(Creature* creature) : ScriptedAI(creature) { }

		uint32 checkTimer;
		bool masterShangXiFound;

		void Reset()
		{
			checkTimer = 2500;
			masterShangXiFound = false;
			me->SetReactState(REACT_DEFENSIVE);
			me->setFaction(7);
			events.Reset();
		}

		void JustRespawned()
		{
			Reset();
		}

		void EnterCombat(Unit* unit)
		{
			events.ScheduleEvent(EVENT_TUSHUI_BLACKOUT_KICK, 2000);
		}

		void DamageTaken(Unit* attacker, uint32& damage)
		{
			if (me->HealthBelowPctDamaged(16.67f, damage))
			{
				damage = 0;
				me->CombatStop();
				me->setFaction(11);
				me->HandleEmoteCommand(EMOTE_STATE_STAND);
				// Clear in combat
				attacker->ClearInCombat();
				//
				events.ScheduleEvent(EVENT_TUSHUI_TALK, 300);
				events.ScheduleEvent(EVENT_TUSHUI_RUN, 2500);
				events.CancelEvent(EVENT_TUSHUI_BLACKOUT_KICK);

				if (attacker && attacker->GetTypeId() == TYPEID_PLAYER)
					attacker->ToPlayer()->KilledMonsterCredit(54586, 0);
			}
		}

		void UpdateAI(const uint32 diff)
		{
			events.Update(diff);

			if (me->isInCombat())
			{
				DoMeleeAttackIfReady();
				me->HandleEmoteCommand(EMOTE_STATE_READYUNARMED);
			}
			else
			{
				if (checkTimer <= diff)
				{
					if (me->FindNearestCreature(NPC_MASTER_SHANG_XI_, 1.5f) && !me->isInCombat() && !masterShangXiFound)
					{
						// Since this creature don't ever die, is't require to be despawned, 
						// but this secuence is "visualy" equal to despawn and respawn.
						masterShangXiFound = true;
						events.ScheduleEvent(EVENT_TUSHUI_GOHOME, 3000 + me->GetRespawnTime());
						events.ScheduleEvent(EVENT_TUSHUI_RESET, 6000 + me->GetRespawnTime());
						me->SetVisible(false);
						return;
					}
					checkTimer = 2000;
				}
				else
				{
					checkTimer -= diff;
				}
			}

			if (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_TUSHUI_TALK:
					Talk(irand(0, 7));
					events.CancelEvent(EVENT_TUSHUI_TALK);
					break;
				case EVENT_TUSHUI_RUN:
					if (me->GetAreaId() != AREA_THE_DAWNING_VALLEY)
						me->GetMotionMaster()->MovePoint(0, 1446.322876f, 3389.027588f, 173.782471f);
					events.CancelEvent(EVENT_TUSHUI_RUN);
					break;
				case EVENT_TUSHUI_BLACKOUT_KICK:
					if (me->getVictim())
						me->CastSpell(me->getVictim(), SPELL_BLACKOUT_KICK_, true);
					events.ScheduleEvent(EVENT_TUSHUI_BLACKOUT_KICK, irand(6000, 8000));
					break;
				case EVENT_TUSHUI_GOHOME:
					me->GetMotionMaster()->MoveTargetedHome();
					events.CancelEvent(EVENT_TUSHUI_GOHOME);
					break;
				case EVENT_TUSHUI_RESET:
					Reset();
					me->SetVisible(true);
					events.CancelEvent(EVENT_TUSHUI_RESET);
					break;
				default:
					break;
				}
			}
		}
	private:
		EventMap events;
	};
};

/*######
## boss_jaomin_ro - 54611
######*/

enum eJaominRoMisc
{
	SPELL_BABY_ELEPHANT_TAKES_A_BATH_STUND = 108937,
	SPELL_BABY_ELEPHANT_TAKES_A_BATH_JUMP  = 108938,
	SPELL_RECKLESS_ROUNDHOUSE              = 119301,
	SPELL_HAWK_DIVING_EARTH                = 108935,

	QUEST_THE_DISCIPLE_CHALLENGE           = 29409,
};

enum eJaominRoEvents
{
	EVENT_CHECK_FOR_OPONENTS = 1,
	EVENT_JAOMIN_JUMP        = 2,
	EVENT_HIT_CIRCLE         = 3,
	EVENT_FALCON             = 4,
	EVENT_STUND_GROUND       = 5,
	EVENT_SALUTE_1           = 6,
	EVENT_RESET              = 7,
	EVENT_SIT                = 8
};

const Position JaominRoHomePosition = { 1379.91f, 3169.6f, 137.018f, 1.00893f };

class boss_jaomin_ro : public CreatureScript
{
public:
	boss_jaomin_ro() : CreatureScript("boss_jaomin_ro") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_jaomin_roAI(creature);
	}

	struct boss_jaomin_roAI : public ScriptedAI
	{
		boss_jaomin_roAI(Creature* creature) : ScriptedAI(creature) { }

		std::set<uint64> _atakers;

		bool isInFalcon;
		
		void EnterCombat(Unit* unit)
		{
			events.ScheduleEvent(EVENT_JAOMIN_JUMP, 1000);
			events.ScheduleEvent(EVENT_HIT_CIRCLE, 8000);
		}
	
		void Reset()
		{
			// Cancel old events
			events.CancelEvent(EVENT_JAOMIN_JUMP);
			events.CancelEvent(EVENT_STUND_GROUND);
			events.CancelEvent(EVENT_HIT_CIRCLE);
			events.CancelEvent(EVENT_FALCON);
			//
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			//
			me->HandleEmoteCommand(EMOTE_STATE_STAND);
			//
			me->SetReactState(REACT_DEFENSIVE);
			me->RemoveAllAttackers();
			me->SetDisplayId(39755);
			me->setFaction(2357);
			me->CombatStop(true);
			// Clear attakers list
			_atakers.clear();
			// Set falcon stage false
			isInFalcon = false;
			// Go home
			if (me->GetDistance(JaominRoHomePosition) >= 3.0f)
				me->GetMotionMaster()->MoveTargetedHome();
			else
				me->NearTeleportTo(JaominRoHomePosition.m_positionX, JaominRoHomePosition.m_positionY, JaominRoHomePosition.m_positionZ, JaominRoHomePosition.m_orientation, true);
			//
			events.ScheduleEvent(EVENT_SIT, 4000);
			// Start Looking for oponents
			events.ScheduleEvent(EVENT_CHECK_FOR_OPONENTS, 700);
		}

		void KilledUnit(Unit* /*victim*/) 
		{
			if (!me->getVictim() || me->getVictim() == NULL)
				Reset();
		}

		void DamageTaken(Unit* attacker, uint32& damage)
		{
			if (Player* _player = attacker->ToPlayer())
			{
				_atakers.insert(_player->GetGUID());
			}

			if (me->HealthBelowPctDamaged(30, damage) && !isInFalcon)
			{
				me->SetDisplayId(39796); // Falcon
				events.ScheduleEvent(EVENT_FALCON, 1000);
				//
				events.CancelEvent(EVENT_JAOMIN_JUMP);
				events.CancelEvent(EVENT_STUND_GROUND);
				events.CancelEvent(EVENT_HIT_CIRCLE);
				//
				isInFalcon = true;
			}

			if (me->HealthBelowPctDamaged(5, damage))
			{
				// Clear in combat
				attacker->ClearInCombat();
				me->CombatStop();
				// 
				me->SetDisplayId(39755);
				me->SetFullHealth();
				me->setFaction(35);
				//
				std::list<Player*> playerList;
				GetPlayerListInGrid(playerList, me, 30.0f);
				for (auto player : playerList)
				{
					if (_atakers.find(player->GetGUID()) != _atakers.end())
					{
						if (player->GetQuestStatus(QUEST_THE_DISCIPLE_CHALLENGE) == QUEST_STATUS_INCOMPLETE)
						{
							player->KilledMonsterCredit(me->GetEntry(), 0);
						}
					}
				}
				// Cancel old events
				events.CancelEvent(EVENT_JAOMIN_JUMP);
				events.CancelEvent(EVENT_STUND_GROUND);
				events.CancelEvent(EVENT_HIT_CIRCLE);
				events.CancelEvent(EVENT_FALCON);
				// Start reset
				events.ScheduleEvent(EVENT_SALUTE_1, 1000);
				events.ScheduleEvent(EVENT_RESET, 5000);
				//
				damage = 0;
			}

			if (damage > me->GetHealth())
				damage = 0;
		}

		void CheckAreaForOponents()
		{
			std::list<Player*> playerList;
			GetPlayerListInGrid(playerList, me, 25.0f);
			for (auto player : playerList)
			{
				if (player->GetQuestStatus(QUEST_THE_DISCIPLE_CHALLENGE) == QUEST_STATUS_INCOMPLETE)
				{
					me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
					me->MonsterSay("A challenger approach", LANG_UNIVERSAL, 0); // Replace with Talk(0)
					me->HandleEmoteCommand(EMOTE_STATE_READY1H);
					me->SetStandState(UNIT_STAND_STATE_STAND);
					me->SetReactState(REACT_AGGRESSIVE);
					events.CancelEvent(EVENT_CHECK_FOR_OPONENTS);
					return;
				}
			}

			events.ScheduleEvent(EVENT_CHECK_FOR_OPONENTS, 700);
		}

		void UpdateAI(const uint32 diff)
		{
			// Enter on evade mode if is too far
			if (me->GetDistance(JaominRoHomePosition) >= 15.0f)
			{
				events.ScheduleEvent(EVENT_RESET, 2000);
				Reset();
				return;
			}

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_CHECK_FOR_OPONENTS:
					CheckAreaForOponents();
					break;
				case EVENT_JAOMIN_JUMP:
					if (Unit* victim = me->getVictim())
					{
						me->CastSpell(victim, SPELL_BABY_ELEPHANT_TAKES_A_BATH_JUMP, true);
						events.ScheduleEvent(EVENT_STUND_GROUND, 2000); 
					}
					events.ScheduleEvent(EVENT_JAOMIN_JUMP, 20000);
					break;
				case EVENT_STUND_GROUND:
					if (Unit* victim = me->getVictim())
						me->CastSpell(victim, SPELL_BABY_ELEPHANT_TAKES_A_BATH_STUND, true);
					events.CancelEvent(EVENT_STUND_GROUND);
					break;
				case EVENT_HIT_CIRCLE:
					if (Unit* victim = me->getVictim())
						me->CastSpell(victim, SPELL_RECKLESS_ROUNDHOUSE, true);
					events.ScheduleEvent(EVENT_HIT_CIRCLE, 15000);
					break;
				case EVENT_FALCON:
					if (me->getVictim())
						me->CastSpell(me->getVictim(), SPELL_HAWK_DIVING_EARTH, true);
					events.ScheduleEvent(EVENT_FALCON, 4000);
					break;
				case EVENT_SALUTE_1:
					me->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
					events.CancelEvent(EVENT_SALUTE_1);
					break;
				case EVENT_RESET:
					Reset();
				case EVENT_SIT:
					me->SetStandState(UNIT_STAND_STATE_SIT);
					events.CancelEvent(EVENT_SIT);
					break;
				default:
					break;
				}
			}

			DoMeleeAttackIfReady();
		}
	private:
		EventMap events;
	};
};

/*######
## mob_min_dimwind_final - 54785
######*/

enum eMinDimwindFinalEvents
{
	EVENT_SUMMON_SCAMP_1 = 1,
	EVENT_KEG_CARRY_1 = 2,
	EVENT_RUNAWAY_1 = 3,
	EVENT_SUMMON_SCAMP_2 = 4,
	EVENT_KEG_CARRY_2 = 5,
	EVENT_RUNAWAY_2 = 6,
	EVENT_SUMMON_SCAMP_3 = 7,
	EVENT_KEG_CARRY_3 = 8,
	EVENT_RUNAWAY_3 = 9
};

enum eMiscMinDimwindFinal
{
	NPC_AMBERLEAF_SCAMP_ = 54130,
	SPELL_KEG_CARRY = 109137,
	QUEST_THE_MISSING_DRIVER_ = 29419
};

// Thift Amberleaf Scamp positions this are near.
Position const ThiftScampPoints[] =
{
	{ 1293.51f, 3528.53f, 98.0433f, 4.67748f }, // Thift Amberleaf Scamp 1
	{ 1294.22f, 3519.09f, 100.127f, 2.02458f }, // Thift Amberleaf Scamp 2 
	{ 1288.38f, 3528.15f, 96.9992f, 5.27089f }, // Thift Amberleaf Scamp 3
};

// Positions were the Amberleaf Scamp Thift will run away.
Position const ThiftEscapePoints[] =
{
	{ 1342.825928f, 3514.124268f, 101.61726f }, // Amberleaf Scamp Thift 1 
	{ 1325.679932f, 3471.875244f, 112.65136f }, // Amberleaf Scamp Thift 2 
	{ 1251.993408f, 3560.332275f, 101.59293f }  // Amberleaf Scamp Thift 3
};

class mob_min_dimwind_final : public CreatureScript
{
public:
	mob_min_dimwind_final() : CreatureScript("mob_min_dimwind_final") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_min_dimwind_finalAI(creature);
	}

	struct mob_min_dimwind_finalAI : public ScriptedAI
	{
		mob_min_dimwind_finalAI(Creature* creature) : ScriptedAI(creature) {}

		Creature* thiftScamp1;
		Creature* thiftScamp2;
		Creature* thiftScamp3;

		uint64 m_checkTimer;

		void Reset()
		{
			m_checkTimer = 2000;

			events.ScheduleEvent(EVENT_SUMMON_SCAMP_1, 4000);
		}

		void UpdateAI(const uint32 diff)
		{
			events.Update(diff);

			if (m_checkTimer <= diff)
			{
				std::list<Player*> PlayerList;
				GetPlayerListInGrid(PlayerList, me, 200.0f);
				for (auto cPlayer : PlayerList)
				{
					if (cPlayer->GetQuestStatus(QUEST_THE_MISSING_DRIVER_) != QUEST_STATUS_REWARDED)
					{
						me->DestroyForPlayer(cPlayer);
					}

					if (cPlayer->GetQuestStatus(QUEST_THE_MISSING_DRIVER_) == QUEST_STATUS_REWARDED)
					{
						me->ToUnit()->UpdateObjectVisibility(true);
					}
				}
				m_checkTimer = 2500;
			}
			else
			{
				m_checkTimer -= diff;
			}

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_SUMMON_SCAMP_1:
					if (thiftScamp1 = me->SummonCreature(NPC_AMBERLEAF_SCAMP_, ThiftScampPoints[0], TEMPSUMMON_TIMED_DESPAWN, 15000))
						thiftScamp1->SetPhaseMask(65504, true);
					events.ScheduleEvent(EVENT_KEG_CARRY_1, irand(2000, 4000));
					events.CancelEvent(EVENT_SUMMON_SCAMP_1);
					break;
				case EVENT_KEG_CARRY_1:
					if (thiftScamp1)
						thiftScamp1->CastSpell(thiftScamp1, SPELL_KEG_CARRY, true);
					events.ScheduleEvent(EVENT_RUNAWAY_1, irand(4000, 6000));
					events.CancelEvent(EVENT_KEG_CARRY_1);
					break;
				case EVENT_RUNAWAY_1:
					if (thiftScamp1)
						thiftScamp1->GetMotionMaster()->MovePoint(0, ThiftEscapePoints[0]);
					events.ScheduleEvent(EVENT_SUMMON_SCAMP_2, irand(2000, 6000));
					events.CancelEvent(EVENT_RUNAWAY_1);
					break;
				case EVENT_SUMMON_SCAMP_2:
					if (thiftScamp2 = me->SummonCreature(NPC_AMBERLEAF_SCAMP_, ThiftScampPoints[1], TEMPSUMMON_TIMED_DESPAWN, 15000))
						thiftScamp2->SetPhaseMask(65504, true);
					events.ScheduleEvent(EVENT_KEG_CARRY_2, irand(2000, 4000));
					events.CancelEvent(EVENT_SUMMON_SCAMP_2);
					break;
				case EVENT_KEG_CARRY_2:
					if (thiftScamp2)
						thiftScamp2->CastSpell(thiftScamp2, SPELL_KEG_CARRY, true);
					events.ScheduleEvent(EVENT_RUNAWAY_2, irand(4000, 6000));
					events.CancelEvent(EVENT_KEG_CARRY_2);
					break;
				case EVENT_RUNAWAY_2:
					if (thiftScamp2)
						thiftScamp2->GetMotionMaster()->MovePoint(0, ThiftEscapePoints[1]);
					events.ScheduleEvent(EVENT_SUMMON_SCAMP_3, irand(2000, 6000));
					events.CancelEvent(EVENT_RUNAWAY_2);
					break;
				case EVENT_SUMMON_SCAMP_3:
					if (thiftScamp3 = me->SummonCreature(NPC_AMBERLEAF_SCAMP_, ThiftScampPoints[2], TEMPSUMMON_TIMED_DESPAWN, 15000))
						thiftScamp3->SetPhaseMask(65504, true);
					events.ScheduleEvent(EVENT_KEG_CARRY_3, irand(2000, 4000));
					events.CancelEvent(EVENT_SUMMON_SCAMP_3);
					break;
				case EVENT_KEG_CARRY_3:
					if (thiftScamp3)
						thiftScamp3->CastSpell(thiftScamp3, SPELL_KEG_CARRY, true);
					events.ScheduleEvent(EVENT_RUNAWAY_3, irand(4000, 6000));
					events.CancelEvent(EVENT_KEG_CARRY_3);
					break;
				case EVENT_RUNAWAY_3:
					if (thiftScamp3)
						thiftScamp3->GetMotionMaster()->MovePoint(0, ThiftEscapePoints[2]);
					events.ScheduleEvent(EVENT_SUMMON_SCAMP_1, irand(2000, 6000));
					events.CancelEvent(EVENT_RUNAWAY_3);
					break;
				default:
					break;
				}
			}
		}
	private:
		EventMap events;
	};
};

/*######
## mob_min_dimwind_summon - 56503
######*/

enum eMiscMinDimwindSummon
{
	NPC_MIN_DIMWIND = 54855,
};

enum eSayMinDimwindSummon
{
	SAY_AMBERLEAF_1 = 0, // Look out! Its friendses are coming!
	SAY_AMBERLEAF_2 = 1, // Run away!

	SAY_MIN_DIMWIND_1 = 0, // Master Shang has trained you well. Thank you, Friend!
	SAY_MIN_DIMWIND_2 = 1, // I couldn't have fougth off alone. Now, if you'll excuse me, I shoul go find my cart.
	SAY_MIN_DIMWIND_3 = 2, // Cart!
	SAY_MIN_DIMWIND_4 = 3, // Hello, cart. Still upside-downed, I see.
};

enum eEventsMinDimwind
{
	EVENT_AMBERLEAF_RUN_AWAY_1 = 1,
	EVENT_AMBERLEAF_RUN_AWAY_2 = 2,
	EVENT_DIMWIND_SAY_1 = 3,
	EVENT_DIMWIND_SAY_2 = 4,
	EVENT_DIMWIND_RUN_1 = 5,
	EVENT_DIMWIND_SAY_3 = 6,
	EVENT_DIMWIND_RUN_2 = 7,
	EVENT_DIMWIND_SAY_4 = 8,
	EVENT_DIMWIND_RUN_3 = 9,
	EVENT_DIMWIND_RUN_4 = 10,
	EVENT_DIMWIND_RUN_5 = 11,
	EVENT_DIMWIND_SAY_5 = 12,
	EVENT_DIMWIND_RUN_6 = 13,
	EVENT_DIMWIND_RUN_7 = 14,
	EVENT_DIMWIND_END = 15,
};

// Positions were the Amberleaf Scamp will run away.
Position const EscapePoints[] =
{
	{ 1462.280762f, 3571.749268f, 87.852112f }, // Amberleaf Scamp 1
	{ 1412.113770f, 3581.308594f, 89.331223f }, // Amberleaf Scamp 2 
	{ 1390.180664f, 3581.708008f, 91.498085f }, // Amberleaf Scamp 3
	{ 1371.005249f, 3575.204102f, 91.947105f }, // Amberleaf Scamp 4 
	{ 1374.989258f, 3539.136230f, 93.007309f }, // Amberleaf Scamp 5 
};

// Min Dimwind summon WayPoints
Position const MinDimiwindRunPoints[] =
{
	{ 1397.118652f, 3548.915283f, 90.728721f },
	{ 1373.306885f, 3581.243896f, 91.602699f },
	{ 1354.650513f, 3583.795898f, 89.320351f },
	{ 1323.678467f, 3538.115967f, 98.475006f },
	{ 1299.884277f, 3527.468018f, 98.938644f },
	{ 1295.715942f, 3520.725098f, 99.892564f },
	{ 1286.92f, 3521.41f, 97.880f }
};

class mob_min_dimwind_summon : public CreatureScript
{
public:
	mob_min_dimwind_summon() : CreatureScript("mob_min_dimwind_summon") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_min_dimwind_summonAI(creature);
	}

	struct mob_min_dimwind_summonAI : public ScriptedAI
	{
		mob_min_dimwind_summonAI(Creature* creature) : ScriptedAI(creature) { }

		uint64 playerOwnerGUID;

		uint64 scamp1;
		uint64 scamp2;
		uint64 scamp3;
		uint64 scamp4;
		uint64 scamp5;
		uint64 dimwind;

		uint64 m_checkTimer;

		bool startEvent;

		void Reset()
		{
			me->SetVisible(false);
			playerOwnerGUID = 0;
			m_checkTimer = 1000;
			startEvent = false;
		}

		void UpdateAI(const uint32 diff)
		{
			events.Update(diff);

			if (m_checkTimer <= diff)
			{
				std::list<Player*> PlayerList;
				GetPlayerListInGrid(PlayerList, me, 25.0f);
				for (auto _cPlayer : PlayerList)
				{
					if (_cPlayer->GetGUID() == playerOwnerGUID)
					{
						if (!startEvent)
						{
							events.ScheduleEvent(EVENT_AMBERLEAF_RUN_AWAY_1, 2500);
							startEvent = true;
						}
					}
				}
				//Despawn after owner get rewarded
				if (Unit* _cPlayerOwner = ObjectAccessor::FindUnit(playerOwnerGUID))
				{
					if (_cPlayerOwner->ToPlayer()->GetQuestStatus(QUEST_THE_MISSING_DRIVER_) == QUEST_STATUS_REWARDED)
						me->DespawnOrUnsummon(1000);
				}
				m_checkTimer = 1000;
			}
			else
			{
				m_checkTimer -= diff;
			}

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_AMBERLEAF_RUN_AWAY_1:
				{
					// Make the Scamps 1 run away.
					if (Unit* aScamp1 = ObjectAccessor::FindUnit(scamp1))
					{
						aScamp1->GetMotionMaster()->MovePoint(0, EscapePoints[0]);
						aScamp1->ToCreature()->DespawnOrUnsummon(15000);
					}
					// Make the Scamps 2 run away.
					if (Unit* aScamp2 = ObjectAccessor::FindUnit(scamp2))
					{
						aScamp2->ToCreature()->AI()->Talk(SAY_AMBERLEAF_1);
						aScamp2->GetMotionMaster()->MovePoint(0, EscapePoints[1]);
						aScamp2->ToCreature()->DespawnOrUnsummon(15000);
					}
					// Make the Scamps 3 run away.
					if (Unit* aScamp3 = ObjectAccessor::FindUnit(scamp3))
					{
						aScamp3->GetMotionMaster()->MovePoint(0, EscapePoints[2]);
						aScamp3->ToCreature()->DespawnOrUnsummon(15000);
					}
					// Make the Scamps 4 run away.
					if (Unit* aScamp4 = ObjectAccessor::FindUnit(scamp4))
					{
						aScamp4->GetMotionMaster()->MovePoint(0, EscapePoints[3]);
						aScamp4->ToCreature()->DespawnOrUnsummon(15000);
					}
					// Complete Quest by giving kill monster credit
					if (Unit* cPlayerOwner = ObjectAccessor::FindUnit(playerOwnerGUID))
					{
						cPlayerOwner->ToPlayer()->KilledMonsterCredit(NPC_MIN_DIMWIND, 0);
						if (Unit* aDimwind = ObjectAccessor::FindUnit(dimwind))
						{
							aDimwind->DestroyForPlayer(cPlayerOwner->ToPlayer());
						}
					}
					// End
					me->HandleEmoteCommand(EMOTE_STATE_STAND);
					me->SetVisible(true);
					events.ScheduleEvent(EVENT_AMBERLEAF_RUN_AWAY_2, 2000);
					events.CancelEvent(EVENT_AMBERLEAF_RUN_AWAY_1);
				} break;
				case EVENT_AMBERLEAF_RUN_AWAY_2:
					if (Unit* aScamp5 = ObjectAccessor::FindUnit(scamp5))
					{
						aScamp5->ToCreature()->AI()->Talk(SAY_AMBERLEAF_2);
						aScamp5->GetMotionMaster()->MovePoint(0, EscapePoints[4]);
						aScamp5->ToCreature()->DespawnOrUnsummon(15000);
					}
					events.ScheduleEvent(EVENT_DIMWIND_SAY_1, 2200);
					events.CancelEvent(EVENT_AMBERLEAF_RUN_AWAY_2);
					break;
				case EVENT_DIMWIND_SAY_1:
					Talk(SAY_MIN_DIMWIND_1);
					events.ScheduleEvent(EVENT_DIMWIND_SAY_2, 4000);
					events.CancelEvent(EVENT_DIMWIND_SAY_1);
					break;
				case EVENT_DIMWIND_SAY_2:
					Talk(SAY_MIN_DIMWIND_2);
					events.ScheduleEvent(EVENT_DIMWIND_RUN_1, 3200);
					events.CancelEvent(EVENT_DIMWIND_SAY_2);
					break;
				case EVENT_DIMWIND_RUN_1:
					me->GetMotionMaster()->MovePoint(0, MinDimiwindRunPoints[0]);
					events.ScheduleEvent(EVENT_DIMWIND_SAY_3, 3000);
					events.CancelEvent(EVENT_DIMWIND_RUN_1);
					break;
				case EVENT_DIMWIND_SAY_3:
					Talk(SAY_MIN_DIMWIND_3);
					events.ScheduleEvent(EVENT_DIMWIND_RUN_2, 2000);
					events.CancelEvent(EVENT_DIMWIND_SAY_3);
					break;
				case EVENT_DIMWIND_RUN_2:
					me->GetMotionMaster()->MovePoint(0, MinDimiwindRunPoints[1]);
					events.ScheduleEvent(EVENT_DIMWIND_SAY_4, 5200);
					events.CancelEvent(EVENT_DIMWIND_RUN_2);
					break;
				case EVENT_DIMWIND_SAY_4:
					Talk(SAY_MIN_DIMWIND_3);
					events.ScheduleEvent(EVENT_DIMWIND_RUN_3, 2000);
					events.CancelEvent(EVENT_DIMWIND_SAY_4);
					break;
				case EVENT_DIMWIND_RUN_3:
					me->GetMotionMaster()->MovePoint(0, MinDimiwindRunPoints[2]);
					events.ScheduleEvent(EVENT_DIMWIND_RUN_4, 2300);
					events.CancelEvent(EVENT_DIMWIND_RUN_3);
					break;
				case EVENT_DIMWIND_RUN_4:
					me->GetMotionMaster()->MovePoint(0, MinDimiwindRunPoints[3]);
					events.ScheduleEvent(EVENT_DIMWIND_RUN_5, 6600);
					events.CancelEvent(EVENT_DIMWIND_RUN_4);
					break;
				case EVENT_DIMWIND_RUN_5:
					me->GetMotionMaster()->MovePoint(0, MinDimiwindRunPoints[4]);
					events.ScheduleEvent(EVENT_DIMWIND_SAY_5, 4000);
					events.CancelEvent(EVENT_DIMWIND_RUN_5);
					break;
				case EVENT_DIMWIND_SAY_5:
					Talk(SAY_MIN_DIMWIND_4);
					events.ScheduleEvent(EVENT_DIMWIND_RUN_6, 1500);
					events.CancelEvent(EVENT_DIMWIND_SAY_5);
					break;
				case EVENT_DIMWIND_RUN_6:
					me->GetMotionMaster()->MovePoint(0, MinDimiwindRunPoints[5]);
					me->SetSpeed(MOVE_RUN, 0.5f);
					events.ScheduleEvent(EVENT_DIMWIND_RUN_7, 3300);
					events.CancelEvent(EVENT_DIMWIND_RUN_6);
					break;
				case EVENT_DIMWIND_RUN_7:
					me->GetMotionMaster()->MovePoint(0, MinDimiwindRunPoints[6]);
					events.ScheduleEvent(EVENT_DIMWIND_END, 3000);
					events.CancelEvent(EVENT_DIMWIND_RUN_7);
					break;
				case EVENT_DIMWIND_END:
					me->SetFacingTo(0.869715f);
					events.CancelEvent(EVENT_DIMWIND_END);
					break;
				default:
					break;
				}
			}
		}
	private:
		EventMap events;
	};
};

// @ToDo - Delete
class mob_attacker_dimwind : public CreatureScript
{
public:
    mob_attacker_dimwind() : CreatureScript("mob_attacker_dimwind") { }
    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_attacker_dimwindAI(creature);
    }
    
    struct mob_attacker_dimwindAI : public ScriptedAI
    {
    	mob_attacker_dimwindAI(Creature* creature) : ScriptedAI(creature) {}
    	
        void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
        {
            if(me->GetHealthPct() < 90 && pDoneBy && pDoneBy->ToCreature() && pDoneBy->ToCreature()->GetEntry() == 54785)
                uiDamage = 0;
        }

        void UpdateAI(const uint32 diff)
        {
            if (me->GetPositionX() == 1403.440430f && me->GetPositionY() == 3566.382568f)
                me->DespawnOrUnsummon();
        }
    };
};

/*######
## mob_min_dimwind - 54855
######*/

enum eMiscMinDimwind
{
	NPC_MIN_DIMWIND_SUMMON = 56503,
	NPC_AMBERLEAF_SCAMP = 54130,
	QUEST_THE_MISSING_DRIVER = 29419
};

// Amberleaf Scamp temporaly summoned positions, this positions are constants, not randomly created.
Position const AmberleafScampPoints[] =
{
	{ 1418.814941f, 3538.107422f, 85.971985f, 4.17430f }, // Amberleaf Scamp 1 
	{ 1413.725342f, 3542.623047f, 87.532526f, 4.92588f }, // Amberleaf Scamp 2  
	{ 1411.864380f, 3540.173340f, 87.579727f, 5.02405f }, // Amberleaf Scamp 3 
	{ 1408.024048f, 3539.550049f, 87.931252f, 6.01367f }, // Amberleaf Scamp 4 
	{ 1408.695435f, 3534.402100f, 86.883087f, 5.99031f }, // Amberleaf Scamp 5  
};

class mob_min_dimwind : public CreatureScript
{
public:
	mob_min_dimwind() : CreatureScript("mob_min_dimwind") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_min_dimwindAI(creature);
	}

	struct mob_min_dimwindAI : public ScriptedAI
	{
		mob_min_dimwindAI(Creature* creature) : ScriptedAI(creature) { }

		std::list<uint64> _playerDataList;

		Creature* Scamp1;
		Creature* Scamp2;
		Creature* Scamp3;
		Creature* Scamp4;
		Creature* Scamp5;
		Creature* Dimwind;

		uint32 m_checkTimer;

		void Reset()
		{
			m_checkTimer = 2000;
		}

		bool IsPlayerOnlist(Player* player, std::list<uint64> &list)
		{
			for (auto _cPlayer : list)
			{
				if (_cPlayer == player->GetGUID())
				{
					return true;
					break;
				}
			}

			return false;
		}

		void SetStageFor(Player* player)
		{
			_playerDataList.push_back(player->GetGUID());

			Scamp1 = me->SummonCreature(NPC_AMBERLEAF_SCAMP, AmberleafScampPoints[0], TEMPSUMMON_MANUAL_DESPAWN, 0, 0, player->GetGUID());
			Scamp2 = me->SummonCreature(NPC_AMBERLEAF_SCAMP, AmberleafScampPoints[1], TEMPSUMMON_MANUAL_DESPAWN, 0, 0, player->GetGUID());
			Scamp3 = me->SummonCreature(NPC_AMBERLEAF_SCAMP, AmberleafScampPoints[2], TEMPSUMMON_MANUAL_DESPAWN, 0, 0, player->GetGUID());
			Scamp4 = me->SummonCreature(NPC_AMBERLEAF_SCAMP, AmberleafScampPoints[3], TEMPSUMMON_MANUAL_DESPAWN, 0, 0, player->GetGUID());
			Scamp5 = me->SummonCreature(NPC_AMBERLEAF_SCAMP, AmberleafScampPoints[4], TEMPSUMMON_MANUAL_DESPAWN, 0, 0, player->GetGUID());
			Dimwind = me->SummonCreature(NPC_MIN_DIMWIND_SUMMON, me->GetHomePosition(), TEMPSUMMON_MANUAL_DESPAWN, 0, 0, player->GetGUID());

			Scamp1->SetPhaseMask(63, true);
			Scamp2->SetPhaseMask(63, true);
			Scamp3->SetPhaseMask(63, true);
			Scamp4->SetPhaseMask(63, true);
			Scamp5->SetPhaseMask(63, true);
			Dimwind->SetPhaseMask(63, true);

			Dimwind->HandleEmoteCommand(EMOTE_STATE_CRANE);

			std::list<Creature*> DimwindList;
			GetCreatureListWithEntryInGrid(DimwindList, me, NPC_MIN_DIMWIND_SUMMON, 5.0f);
			for (auto _cDimwind : DimwindList)
			{
				if (_cDimwind->GetGUID() == Dimwind->GetGUID())
				{
					// Set owner GUID
					CAST_AI(mob_min_dimwind_summon::mob_min_dimwind_summonAI, _cDimwind->AI())->playerOwnerGUID = player->GetGUID();
					// Set Scamps GUIDs
					CAST_AI(mob_min_dimwind_summon::mob_min_dimwind_summonAI, _cDimwind->AI())->scamp1 = Scamp1->GetGUID();
					CAST_AI(mob_min_dimwind_summon::mob_min_dimwind_summonAI, _cDimwind->AI())->scamp2 = Scamp2->GetGUID();
					CAST_AI(mob_min_dimwind_summon::mob_min_dimwind_summonAI, _cDimwind->AI())->scamp3 = Scamp3->GetGUID();
					CAST_AI(mob_min_dimwind_summon::mob_min_dimwind_summonAI, _cDimwind->AI())->scamp4 = Scamp4->GetGUID();
					CAST_AI(mob_min_dimwind_summon::mob_min_dimwind_summonAI, _cDimwind->AI())->scamp5 = Scamp5->GetGUID();
					CAST_AI(mob_min_dimwind_summon::mob_min_dimwind_summonAI, _cDimwind->AI())->dimwind = me->GetGUID();
				}
			}
		}

		void UpdateAI(const uint32 diff)
		{
			if (m_checkTimer <= diff)
			{
				std::list<Player*> PlayerList;
				GetPlayerListInGrid(PlayerList, me, 80.0f);
				for (auto _cPlayer : PlayerList)
				{
					if (_cPlayer->GetQuestStatus(QUEST_THE_MISSING_DRIVER) == QUEST_STATUS_INCOMPLETE)
					{
						if (!IsPlayerOnlist(_cPlayer, _playerDataList))
							SetStageFor(_cPlayer);
					}
				}
				m_checkTimer = 2000;
			}
			else
			{
				m_checkTimer -= diff;
			}
		}
	};
};

/*######
## mob_aysa_meditating - 54975
######*/

enum eMiscAysaMeditating
{
	NPC_MASTER_LI_FEI = 54856,
	NPC_TUSHUI_MONK = 65051,
	NPC_AMBERLEAF_TROUBLEMAKER = 59637,
	NPC_TUSHUI_MONK_PERMANENT = 59649,

	SPELL_GHOST_VISUAL = 91218,
	SPEL_MEDITATION_TIMER_BAR = 116421,
};

enum eSayAysaMeditating
{
	SOUND_AYSA_MEDITATING_1 = 27398,
	SOUND_AYSA_MEDITATING_2 = 27399,

	SAY_AYSA_MEDITATING_1 = 0, // I can't meditate!
	SAY_AYSA_MEDITATING_2 = 1, // Keep those creatures at bay while I meditate. We'll soon have the answers we seek.
	SAY_AYSA_MEDITATING_3 = 2, // And so our path lays before us. Speak to Master Shang Xi, he will tell you what comes next.

	SAY_MASTER_LI_FEI_1 = 0, // The way of the Tushui... enlightenment through patience and mediation... the principled life
	SAY_MASTER_LI_FEI_2 = 1, // It is good to see you again, Aysa. You've come with respect, and so I shall give you the answers you seek.
	SAY_MASTER_LI_FEI_3 = 2, // Huo, the spirit of fire, is known for his hunger.
	SAY_MASTER_LI_FEI_4 = 3, // If you find these things and bring them to his cave, on the far side of Wu-Song Village, you will face a challenge within.
	SAY_MASTER_LI_FEI_5 = 4, // Overcome that challenge, and you shall be graced by Huo's presence. Rekindle his flame, and if your spirit is pure, he shall follow you.
	SAY_MASTER_LI_FEI_6 = 5, // Go, children. We shall meet again very soon.
};

enum eEventsAysaMeditating
{
	EVENT_AYSA_MEDITATING_1 = 1,
	EVENT_AYSA_MEDITATING_2 = 2,
	EVENT_AYSA_MEDITATING_3 = 3,
	EVENT_AYSA_MEDITATING_4 = 4,
	EVENT_AYSA_MEDITATING_5 = 5,
	EVENT_AYSA_MEDITATING_6 = 6,
};

Position const TushuiMonkPositions[] =
{
	{ 1141.85f, 3431.46f, 105.472f, 0.496668f },
	{ 1139.73f, 3437.20f, 105.378f, 0.099515f },
	{ 1131.07f, 3437.02f, 105.472f, 5.802540f }
};

class mob_aysa_meditating : public CreatureScript
{
public:
	mob_aysa_meditating() : CreatureScript("mob_aysa_meditating") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_aysa_meditatingAI(creature);
	}

	struct mob_aysa_meditatingAI : public ScriptedAI
	{
		mob_aysa_meditatingAI(Creature* creature) : ScriptedAI(creature) { }

		Creature* MonkL;
		Creature* MonkR;
		Creature* LiFei;

		uint64 m_ownerGUID;
		uint32 timer;

		void Reset()
		{

		}

		void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
		{
			if (me->HealthBelowPctDamaged(5, uiDamage))
			{
				uiDamage = 0;
				Talk(SAY_AYSA_MEDITATING_1);
				me->SetReactState(REACT_DEFENSIVE);
				me->SetFullHealth();

				std::list<Creature*> unitlist;
				GetCreatureListWithEntryInGrid(unitlist, me, NPC_AMBERLEAF_TROUBLEMAKER, 25.0f);
				for (auto creature : unitlist)
					me->Kill(creature);

				// Update progress bar.
				if (Player* playerOwner = ObjectAccessor::FindUnit(m_ownerGUID)->ToPlayer())
				{
					playerOwner->ModifyPower(POWER_ALTERNATE_POWER, 0);
					playerOwner->SetMaxPower(POWER_ALTERNATE_POWER, 90);
				}

				events.ScheduleEvent(EVENT_AYSA_MEDITATING_1, 20000);
				events.CancelEvent(EVENT_AYSA_MEDITATING_4);
				events.CancelEvent(EVENT_AYSA_MEDITATING_5);
				events.CancelEvent(EVENT_AYSA_MEDITATING_6);
			}
		}

		void SetVisible()
		{
			me->SetVisible(true);
			events.ScheduleEvent(EVENT_AYSA_MEDITATING_1, 500);
		}

		void SetStageFor(Player* player)
		{
			// Remove Default Tushui Monk from player vision.
			events.ScheduleEvent(EVENT_AYSA_MEDITATING_2, 1500);
			// Start Event
			events.ScheduleEvent(EVENT_AYSA_MEDITATING_3, 2000);

			// Spawn Event related creatures.
			MonkL = me->SummonCreature(NPC_TUSHUI_MONK, TushuiMonkPositions[0], TEMPSUMMON_DEAD_DESPAWN, 0, 0, player->GetGUID());
			MonkR = me->SummonCreature(NPC_TUSHUI_MONK, TushuiMonkPositions[1], TEMPSUMMON_DEAD_DESPAWN, 0, 0, player->GetGUID());
			LiFei = me->SummonCreature(NPC_MASTER_LI_FEI, TushuiMonkPositions[2], TEMPSUMMON_MANUAL_DESPAWN, 0, 0, player->GetGUID());

			// Set faction to Tushui Monks
			MonkL->setFaction(2263);
			MonkR->setFaction(2263);

			// Apply required spells
			LiFei->CastSpell(LiFei, SPELL_GHOST_VISUAL);
			player->CastSpell(player, SPEL_MEDITATION_TIMER_BAR);

			// Modify React State.
			me->SetReactState(REACT_PASSIVE);
			MonkL->SetReactState(REACT_AGGRESSIVE);
			MonkR->SetReactState(REACT_AGGRESSIVE);

			// Set variables.
			timer = 1;
		}

		void SetMyOwner(uint64 _aGUID)
		{
			me->ToUnit()->SetOwnerGUID(_aGUID);
		}

		bool isOwnerInWorld()
		{
			if (me->ToUnit()->GetOwner() || me->ToUnit()->GetOwner() != nullptr)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

		void UpdateAI(const uint32 diff)
		{
			if (!isOwnerInWorld())
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_AYSA_MEDITATING_1: // Check for player
					if (Player* playerOwner = ObjectAccessor::FindUnit(m_ownerGUID)->ToPlayer())
					{
						if (me->GetDistance2d(playerOwner) <= 35.0f)
						{
							SetStageFor(playerOwner);
							events.CancelEvent(EVENT_AYSA_MEDITATING_1);
						}
						else
						{
							events.ScheduleEvent(EVENT_AYSA_MEDITATING_1, 500);
						}
					}
					break;
				case EVENT_AYSA_MEDITATING_2: // Remove Default Tushui Monk from player vision.
					if (Player* playerOwner = ObjectAccessor::FindUnit(m_ownerGUID)->ToPlayer())
					{
						// Remove Default Tushui Monk from vision.
						std::list<Creature*> TushuiMonkList;
						GetCreatureListWithEntryInGrid(TushuiMonkList, me, NPC_TUSHUI_MONK_PERMANENT, 10.0f);
						for (auto _cMonk : TushuiMonkList)
						{
							if (_cMonk->GetPhaseMask() == 63)
							{
								_cMonk->DestroyForPlayer(playerOwner);
								_cMonk->SetReactState(REACT_DEFENSIVE);
							}
						}
						events.ScheduleEvent(EVENT_AYSA_MEDITATING_2, 1500);
					}
					break;
				case EVENT_AYSA_MEDITATING_3: // Start Event
				{
					Talk(SAY_AYSA_MEDITATING_2);
					if (Player* playerOwner = ObjectAccessor::FindUnit(m_ownerGUID)->ToPlayer())
						me->PlayDirectSound(SOUND_AYSA_MEDITATING_1, playerOwner);
					events.ScheduleEvent(EVENT_AYSA_MEDITATING_4, 5000); //spawn mobs
					events.ScheduleEvent(EVENT_AYSA_MEDITATING_5, 1000); //update time
				} break;
				case EVENT_AYSA_MEDITATING_4: //spawn mobs
				{
					for (int i = 0; i < irand(3, 4); i++)
					{
						if (TempSummon* temp = me->SummonCreature(NPC_AMBERLEAF_TROUBLEMAKER, 1144.55f, 3435.65f, 104.97f, 3.3f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000))
						{
							if (temp->AI())
								temp->AI()->AttackStart(me);

							temp->AddThreat(me, 550.0f);
							temp->GetMotionMaster()->Clear();
							temp->GetMotionMaster()->MoveChase(me);
						}
					}
					events.ScheduleEvent(EVENT_AYSA_MEDITATING_4, 20000); // Spawn mobs
				} break;
				case EVENT_AYSA_MEDITATING_5: // Update time
				{
					timer++;

					if (timer == 25 && LiFei)
						LiFei->AI()->Talk(SAY_MASTER_LI_FEI_1);

					if (timer == 30 && LiFei)
						LiFei->AI()->Talk(SAY_MASTER_LI_FEI_2);

					if (timer == 42 && LiFei)
						LiFei->AI()->Talk(SAY_MASTER_LI_FEI_3);

					if (timer == 54 && LiFei)
						LiFei->AI()->Talk(SAY_MASTER_LI_FEI_4);

					if (timer == 66 && LiFei)
						LiFei->AI()->Talk(SAY_MASTER_LI_FEI_5);

					if (timer == 78 && LiFei)
						LiFei->AI()->Talk(SAY_MASTER_LI_FEI_6);

					if (timer == 85 && LiFei)
						LiFei->DespawnOrUnsummon(2000);

					// Update progress bar.
					if (Player* playerOwner = ObjectAccessor::FindUnit(m_ownerGUID)->ToPlayer())
					{
						playerOwner->ModifyPower(POWER_ALTERNATE_POWER, timer / (timer ^ 1 / 2));
						playerOwner->SetMaxPower(POWER_ALTERNATE_POWER, 90);
					}

					// Event control.
					if (timer >= 90)
					{
						events.ScheduleEvent(EVENT_AYSA_MEDITATING_6, 2000); // End quest
						events.CancelEvent(EVENT_AYSA_MEDITATING_4);
						events.CancelEvent(EVENT_AYSA_MEDITATING_5);
					}
					else
					{
						events.ScheduleEvent(EVENT_AYSA_MEDITATING_5, irand(500, 1500));
					}
				} break;
				case EVENT_AYSA_MEDITATING_6: // End event.
				{
					Talk(SAY_AYSA_MEDITATING_3);
					if (Player* playerOwner = ObjectAccessor::FindUnit(m_ownerGUID)->ToPlayer())
					{
						playerOwner->KilledMonsterCredit(NPC_MASTER_LI_FEI, 0);
						playerOwner->RemoveAura(SPEL_MEDITATION_TIMER_BAR/*Meditation Timer Bar*/);
						me->PlayDirectSound(SOUND_AYSA_MEDITATING_2, playerOwner);
						// Despawn temporal creatures.
						if (MonkL && MonkR && MonkL->isAlive() && MonkR->isAlive())
						{
							MonkL->DespawnOrUnsummon(300);
							MonkR->DespawnOrUnsummon(300);
						}
					}
					me->DespawnOrUnsummon(2000);
				} break;
				default:
					break;
				}
			}
		}
	private:
		EventMap events;
	};
};

/*######
## mob_aysa_lake_escort - 56661
######*/

enum eEventsAysaLakeEscort
{
	EVENT_AYSA_LAKE_ESCORT_1 = 1,
	EVENT_AYSA_LAKE_ESCORT_2 = 2,
	EVENT_AYSA_LAKE_ESCORT_3 = 3,
	EVENT_AYSA_LAKE_ESCORT_4 = 4,
	EVENT_AYSA_LAKE_ESCORT_5 = 5,
	EVENT_AYSA_LAKE_ESCORT_6 = 6,
};

enum eSayAysaLakeEscort
{
	SOUND_AYSA_LAKE_ESCORT_1 = 27397,

	SAY_AYSA_LAKE_ESCORT_1 = 0, // Meet me up in the cave if you would, friend.
};

class mob_aysa_lake_escort : public CreatureScript
{
public:
	mob_aysa_lake_escort() : CreatureScript("mob_aysa_lake_escort") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_aysa_lake_escortAI(creature);
	}

	struct mob_aysa_lake_escortAI : public ScriptedAI
	{
		mob_aysa_lake_escortAI(Creature* creature) : ScriptedAI(creature) {}

		uint64 m_ownerGUID;
		uint64 m_AysaCaveGUID;

		void Reset()
		{
			events.ScheduleEvent(EVENT_AYSA_LAKE_ESCORT_1, 1500);
		}

		void UpdateAI(const uint32 diff)
		{
			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_AYSA_LAKE_ESCORT_1:
					Talk(SAY_AYSA_LAKE_ESCORT_1);
					if (Player* _playerOwner = ObjectAccessor::FindUnit(m_ownerGUID)->ToPlayer())
						me->PlayDirectSound(SOUND_AYSA_LAKE_ESCORT_1, _playerOwner);
					events.ScheduleEvent(EVENT_AYSA_LAKE_ESCORT_2, 3000);
					events.CancelEvent(EVENT_AYSA_LAKE_ESCORT_1);
					break;
				case EVENT_AYSA_LAKE_ESCORT_2:
					me->GetMotionMaster()->MoveJump(1197.98f, 3492.69f, 90.77f, 10, 20);
					events.ScheduleEvent(EVENT_AYSA_LAKE_ESCORT_3, 2000);
					events.CancelEvent(EVENT_AYSA_LAKE_ESCORT_2);
					break;
				case EVENT_AYSA_LAKE_ESCORT_3:
					me->GetMotionMaster()->MoveJump(1195.66f, 3478.06f, 107.82f, 10, 20);
					events.ScheduleEvent(EVENT_AYSA_LAKE_ESCORT_4, 2500);
					events.CancelEvent(EVENT_AYSA_LAKE_ESCORT_3);
					break;
				case EVENT_AYSA_LAKE_ESCORT_4:
					me->GetMotionMaster()->MoveJump(1182.59f, 3445.28f, 102.41f, 25, 20);
					events.ScheduleEvent(EVENT_AYSA_LAKE_ESCORT_5, 2500);
					events.CancelEvent(EVENT_AYSA_LAKE_ESCORT_4);
					break;
				case EVENT_AYSA_LAKE_ESCORT_5:
					me->GetMotionMaster()->MovePoint(0, 1155.14f, 3439.11f, 104.97f);
					events.ScheduleEvent(EVENT_AYSA_LAKE_ESCORT_6, 4000);
					events.CancelEvent(EVENT_AYSA_LAKE_ESCORT_5);
					break;
				case EVENT_AYSA_LAKE_ESCORT_6:
					if (Unit* _AysaCave = ObjectAccessor::FindUnit(m_AysaCaveGUID))
					{
						CAST_AI(mob_aysa_meditating::mob_aysa_meditatingAI, _AysaCave->ToCreature()->AI())->SetVisible();
						me->DespawnOrUnsummon(300);
					}
					events.CancelEvent(EVENT_AYSA_LAKE_ESCORT_6);
					break;
				default:
					break;
				}
			}
		}
	private:
		EventMap events;
	};
};

/*######
## mob_aysa - 54567
######*/

enum eMiscAysaCloudsinger
{
	NPC_AYSA_CLOUDSINGER_EXCORT = 56661,
	NPC_AYSA_CLOUDSINGER_MEDITATING = 54975,

	QUEST_THE_WAY_OF_THE_TUSHUI = 29414,
};

Position const MobAysaPositions[] =
{
	{ 1206.31f, 3507.46f, 85.9069f, 6.19783f },
	{ 1135.16f, 3432.99f, 105.532f, 3.38994f },
};

class mob_aysa : public CreatureScript
{
public:
	mob_aysa() : CreatureScript("mob_aysa") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_aysaAI(creature);
	}

	struct mob_aysaAI : public ScriptedAI
	{
		mob_aysaAI(Creature* creature) : ScriptedAI(creature) { }

		std::list<uint64> _playerDataList;

		Creature* AysaExcort;
		Creature* AysaCave;

		uint64 m_checkTimer;

		void Reset()
		{
			if (me->GetPhaseMask() == 16)
				me->SetDisableGravity(true);
			m_checkTimer = 1500;
		}

		bool IsPlayerOnlist(Player* player, std::list<uint64> &list)
		{
			for (auto _cPlayer : list)
			{
				if (_cPlayer == player->GetGUID())
				{
					return true;
					break;
				}
			}

			list.push_back(player->GetGUID());
			return false;
		}

		void SetStageFor(Player* player)
		{
			if (!IsPlayerOnlist(player, _playerDataList))
			{
				AysaExcort = me->SummonCreature(NPC_AYSA_CLOUDSINGER_EXCORT, MobAysaPositions[0], TEMPSUMMON_MANUAL_DESPAWN, 0, 0, player->GetGUID());
				AysaCave = me->SummonCreature(NPC_AYSA_CLOUDSINGER_MEDITATING, MobAysaPositions[1], TEMPSUMMON_MANUAL_DESPAWN, 0, 0, player->GetGUID());

				if (AysaCave && AysaExcort)
				{
					CAST_AI(mob_aysa_lake_escort::mob_aysa_lake_escortAI, AysaExcort->AI())->m_AysaCaveGUID = AysaCave->GetGUID();
					CAST_AI(mob_aysa_lake_escort::mob_aysa_lake_escortAI, AysaExcort->AI())->m_ownerGUID = player->GetGUID();
					CAST_AI(mob_aysa_meditating::mob_aysa_meditatingAI, AysaCave->AI())->m_ownerGUID = player->GetGUID();
					//
					CAST_AI(mob_aysa_meditating::mob_aysa_meditatingAI, AysaCave->AI())->SetMyOwner(player->GetGUID());
					AysaCave->SetVisible(false);
				}
				me->DestroyForPlayer(player);
			}
		}

		void UpdateAI(const uint32 diff)
		{
			if (m_checkTimer <= diff)
			{
				for (auto _cPlayer : _playerDataList)
				{
					if (Player* _cpPlayer = ObjectAccessor::GetPlayer(*me, _cPlayer))
					{
						if (_cpPlayer->GetQuestStatus(QUEST_THE_WAY_OF_THE_TUSHUI) == QUEST_STATUS_REWARDED)
						{
							_playerDataList.remove(_cPlayer);
							continue;
						}

						me->DestroyForPlayer(_cpPlayer);
					}
				}
				m_checkTimer = 1500;
			}
			else { m_checkTimer -= diff; }
		}
	};

	bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
	{
		if (quest->GetQuestId() == QUEST_THE_WAY_OF_THE_TUSHUI)
			CAST_AI(mob_aysa::mob_aysaAI, creature->AI())->SetStageFor(player);
		return true;
	}
};

/*######
## boss_living_air - 54631
######*/

enum eLivingAir
{
	SPELL_LIGHTNING_CLOUD = 108693,
	SPELL_LIGHTNING_BOLT = 73212
};

class boss_living_air : public CreatureScript
{
public:
	boss_living_air() : CreatureScript("boss_living_air") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_living_airAI(creature);
	}

	struct boss_living_airAI : public ScriptedAI
	{
		boss_living_airAI(Creature* creature) : ScriptedAI(creature) { }

		void Reset()
		{
			me->SetReactState(REACT_AGGRESSIVE);
			me->setFaction(14);
		}

		void EnterCombat(Unit* unit)
		{
			events.ScheduleEvent(1, 3000);
			events.ScheduleEvent(2, 5000);
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
					me->CastSpell(me->getVictim(), SPELL_LIGHTNING_CLOUD);
					break;
				case 2:
					me->CastSpell(me->getVictim(), SPELL_LIGHTNING_BOLT);
					events.ScheduleEvent(2, 5000);
					break;
				}
			}

			DoMeleeAttackIfReady();
		}
	private:
		EventMap events;
	};
};

/*######
## boss_li_fei_fight - 54734
######*/

enum eLiFeiMsic
{
	QUEST_ONLY_THE_WORTHY_SHALL_PASS = 29421,

	SPELL_FEET_OF_FURY = 108958,
	SPELL_FLYING_SHADOW_KICK = 108936,
	SPELL_FLYING_SHADOW_KICK_STUN = 108944,
};

enum eLiFeiEvents
{
	EVENT_LI_FEI_CHECK_PLAYER = 1,
	EVENT_LI_FEI_FEET_OF_FURY = 2,
	EVENT_LI_FEI_SHADOW_KICK = 3,
	EVENT_LI_FEI_SHADOW_KICK_STUN = 4,
	EVENT_LI_FEI_END_FIGTH = 5
};

class boss_li_fei_fight : public CreatureScript
{
public:
	boss_li_fei_fight() : CreatureScript("boss_li_fei_fight") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_li_fei_fightAI(creature);
	}

	struct boss_li_fei_fightAI : public ScriptedAI
	{
		boss_li_fei_fightAI(Creature* creature) : ScriptedAI(creature)
		{
		}

		uint64 playerGuid;
		bool allowAttack;

		void Reset()
		{
			playerGuid = 0;
			allowAttack = false;
		}

		void DamageTaken(Unit* attacker, uint32& damage)
		{
			if (me->HealthBelowPctDamaged(10, damage))
			{
				damage = 0;
				allowAttack = false;
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
				me->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
				me->setFaction(35);
				me->CombatStop();

				if (attacker->GetTypeId() == TYPEID_PLAYER)
				{
					if (Player* player = attacker->ToPlayer())
					{
						player->KilledMonsterCredit(54734, 0);
					}
				}

				me->DespawnOrUnsummon(2000);
			}
		}

		void KilledUnit(Unit* victim)
		{
			if (victim->GetTypeId() == TYPEID_PLAYER)
			{
				victim->ToPlayer()->SetQuestStatus(QUEST_ONLY_THE_WORTHY_SHALL_PASS, QUEST_STATUS_FAILED);

				if (victim->GetGUID() == playerGuid)
					me->DespawnOrUnsummon(3000);
			}
		}

		void TimedAttackStart(uint64 guid, uint32 time)
		{
			events.ScheduleEvent(EVENT_LI_FEI_CHECK_PLAYER, time);
			playerGuid = guid;
		}

		void UpdateAI(const uint32 diff)
		{
			if (playerGuid == 0)
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_LI_FEI_CHECK_PLAYER:
					if (Unit* cPlayer = ObjectAccessor::FindUnit(playerGuid))
					{
						events.ScheduleEvent(EVENT_LI_FEI_FEET_OF_FURY, 5000);
						events.ScheduleEvent(EVENT_LI_FEI_SHADOW_KICK, 1000);

						me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC);
						me->SetReactState(REACT_AGGRESSIVE);
						me->AI()->AttackStart(cPlayer);
						me->setFaction(7);
						allowAttack = true;
					}
					else
					{
						me->DespawnOrUnsummon(1000);
					}
					break;
				case EVENT_LI_FEI_FEET_OF_FURY:
					if (Unit* cPlayer = ObjectAccessor::FindUnit(playerGuid))
						me->CastSpell(cPlayer, SPELL_FEET_OF_FURY);
					events.ScheduleEvent(EVENT_LI_FEI_FEET_OF_FURY, 10000);
					break;
				case EVENT_LI_FEI_SHADOW_KICK:
					if (Unit* cPlayer = ObjectAccessor::FindUnit(playerGuid))
						me->CastSpell(cPlayer, SPELL_FLYING_SHADOW_KICK);
					events.ScheduleEvent(EVENT_LI_FEI_SHADOW_KICK_STUN, 300);
					events.ScheduleEvent(EVENT_LI_FEI_SHADOW_KICK, 30000);
					break;
				case EVENT_LI_FEI_SHADOW_KICK_STUN:
					if (Unit* cPlayer = ObjectAccessor::FindUnit(playerGuid))
						cPlayer->CastSpell(me, SPELL_FLYING_SHADOW_KICK_STUN);
					break;
				default:
					break;
				}
			}

			if (allowAttack)
				DoMeleeAttackIfReady();
		}
	private:
		EventMap events;
	};
};

/*######
## spell_huo_benediction - 102630
######*/

enum eSpellHuoBendition
{
	NPC_ANCIENT_SPIRIT_OF_FIRE = 54958
};

class spell_huo_benediction : public SpellScriptLoader
{
public:
	spell_huo_benediction() : SpellScriptLoader("spell_huo_benediction") { }

	class spell_huo_benediction_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_huo_benediction_AuraScript);

		void OnApply(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
		{
			Unit* target = GetTarget();

			if (!target)
				return;

			std::list<Creature*> huoList;
			GetCreatureListWithEntryInGrid(huoList, target, NPC_ANCIENT_SPIRIT_OF_FIRE, 20.0f);

			for (auto huo : huoList)
			{
				if (huo->ToTempSummon())
					if (huo->ToTempSummon()->GetOwnerGUID() == target->GetGUID())
						return;
			}

			// A partir d'ici on sait que le joueur n'a pas encore de Huo
			if (TempSummon* tempHuo = target->SummonCreature(NPC_ANCIENT_SPIRIT_OF_FIRE, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0.0f, TEMPSUMMON_MANUAL_DESPAWN, 0, target->GetGUID()))
			{
				tempHuo->SetOwnerGUID(target->GetGUID());
				tempHuo->GetMotionMaster()->MoveFollow(target, PET_FOLLOW_DIST, PET_FOLLOW_ANGLE);
			}
		}

		void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
		{
			Unit* target = GetTarget();

			if (!target)
				return;

			std::list<Creature*> huoList;
			GetCreatureListWithEntryInGrid(huoList, target, NPC_ANCIENT_SPIRIT_OF_FIRE, 20.0f);

			for (auto huo : huoList)
			{
				if (huo->ToTempSummon())
					if (huo->ToTempSummon()->GetOwnerGUID() == target->GetGUID())
						huo->DespawnOrUnsummon();
			}
		}

		void Register()
		{
			OnEffectApply += AuraEffectApplyFn(spell_huo_benediction_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_INCREASE_SPEED, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
			OnEffectRemove += AuraEffectRemoveFn(spell_huo_benediction_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_INCREASE_SPEED, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
		}
	};

	AuraScript* GetAuraScript() const
	{
		return new spell_huo_benediction_AuraScript();
	}
};

// @TODO
class AreaTrigger_at_temple_entrance : public AreaTriggerScript
{
    public:
        AreaTrigger_at_temple_entrance() : AreaTriggerScript("AreaTrigger_at_temple_entrance")
        {}

        bool OnTrigger(Player* player, AreaTriggerEntry const* trigger)
        {
            if (player->GetQuestStatus(29423) == QUEST_STATUS_INCOMPLETE)
            {
                player->KilledMonsterCredit(61128, 0);

                std::list<Creature*> huoList;
                GetCreatureListWithEntryInGrid(huoList, player, 54958, 20.0f);

                for (auto huo: huoList)
                {
                    if (huo->ToTempSummon())
                    {
                        if (huo->ToTempSummon()->GetOwnerGUID() == player->GetGUID())
                        {
                            huo->GetMotionMaster()->Clear();
                            huo->GetMotionMaster()->MovePoint(1, 950.0f, 3601.0f, 203.0f);
                            huo->DespawnOrUnsummon(5000);
                        }
                    }
                }
            }

            return true;
        }
};

/*######
## mob_trainee_nim - 60183
######*/

enum traineeNimMisc
{
	QUEST_THE_DISCIPLES_CHALLENGE = 29409,
	NPC_TUSHUI_TRAINEE_MALE_ = 65471,
	NPC_TUSHUI_TRAINEE_FEMALE_ = 54587,
};

class mob_trainee_nim : public CreatureScript
{
public:
	mob_trainee_nim() : CreatureScript("mob_trainee_nim") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_trainee_nimAI(creature);
	}

	struct mob_trainee_nimAI : public ScriptedAI
	{
		std::list<uint64> salutePlayerList;

		uint32 checkTimer;
		uint32 emoteTimer;
		uint32 nextEmote;

		mob_trainee_nimAI(Creature* creature) : ScriptedAI(creature)
		{
			checkTimer = 1000;
			emoteTimer = 1000;
			nextEmote = 0;
		}

		bool HasSaluteTo(Player* player)
		{
			for (auto splayer : salutePlayerList)
			{
				if (splayer == player->GetGUID())
				{
					return true;
					break;
				}
			}

			salutePlayerList.push_back(player->GetGUID());
			return false;
		}

		void UpdateAI(const uint32 diff)
		{
			if (checkTimer <= diff)
			{
				std::list<Player*> playerList;
				GetPlayerListInGrid(playerList, me, 25.0f);

				for (auto player : playerList)
				{
					if (player->GetQuestStatus(QUEST_THE_DISCIPLES_CHALLENGE) == QUEST_STATUS_INCOMPLETE && !HasSaluteTo(player))
					{
						std::string sText = ("I hope you are ready, " + std::string(player->GetName()) + ". Jaomin Ro is waiting for you, next to the bridge.");
						me->MonsterSay(sText.c_str(), LANG_UNIVERSAL, 0);
						me->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);

						me->SummonGameObject(197333, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), 0, 0, 0, 0, TEMPSUMMON_MANUAL_DESPAWN);
					}
				}
				checkTimer = 1000;
			}
			else
			{
				checkTimer -= diff;
			}

			//Tushui trainee - 65471, 54587 play emotes
			if (emoteTimer <= diff)
			{
				switch (irand(0, 3))
				{
				case 0:
					nextEmote = EMOTE_ONESHOT_MONKOFFENSE_ATTACKUNARMED;
					break;
				case 1:
					nextEmote = EMOTE_ONESHOT_MONKOFFENSE_SPECIALUNARMED;
					break;
				case 2:
					nextEmote = EMOTE_ONESHOT_MONKOFFENSE_PARRYUNARMED;
					break;
				case 3:
					nextEmote = EMOTE_ONESHOT_PALMSTRIKE;
					break;
				}
				//Play emotes
				std::list<Creature*> traineeList;
				GetCreatureListWithEntryInGrid(traineeList, me, NPC_TUSHUI_TRAINEE_MALE_, 90.0f);
				GetCreatureListWithEntryInGrid(traineeList, me, NPC_TUSHUI_TRAINEE_FEMALE_, 90.0f);
				for (std::list<Creature*>::iterator iter = traineeList.begin(); iter != traineeList.end(); ++iter)
				{
					if (!(*iter)->isInCombat())
						(*iter)->HandleEmoteCommand(nextEmote);
				}
				emoteTimer = irand(3700, 6040);
			}
			else
			{
				emoteTimer -= diff;
			}
		}
	};
};

// @TODO - DELETE
enum eEvents
{
    EVENT_PUNCH     = 1,
    EVENT_COPY_ANIM = 2
};

#define TRAINEE 65469

enum eActions
{
    ACTION_PUNCH = 0
};

class mob_instructors : public CreatureScript
{
public:
    mob_instructors() : CreatureScript("mob_instructors") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_instructorsAI(creature);
    }

    struct mob_instructorsAI : public ScriptedAI
    {
        EventMap events;
        uint8 rand;

        mob_instructorsAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        uint32 punch1;
        uint32 punch2;
        uint32 punch3;

        void Reset()
        {
            punch1 = 300;
            punch2 = 2800;
            punch3 = 5300;
        }

        void UpdateAI(const uint32 diff)
        {
            if (punch1 <= diff)
            {
                me->HandleEmote(35);
                punch1 = 7500;
            }
            else
                punch1 -= diff;

            if (punch2 <= diff)
            {
                me->HandleEmote(36);
                punch2 = 7500;
            }
            else
                punch2 -= diff;

            if (punch3 <= diff)
            {
                me->HandleEmote(37);
                punch3 = 7500;
            }
            else
                punch3 -= diff;
        }
    };
};

// @TODO - DELETE
class mob_aspiring_trainee : public CreatureScript
{
public:
    mob_aspiring_trainee() : CreatureScript("mob_aspiring_trainee") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_aspiring_traineeAI(creature);
    }

    struct mob_aspiring_traineeAI : public ScriptedAI
    {
        mob_aspiring_traineeAI(Creature* creature) : ScriptedAI(creature)
        {
        }

        uint32 punch1;
        uint32 punch2;
        uint32 punch3;

        void Reset()
        {
            punch1 = 1000;
            punch2 = 3500;
            punch3 = 6000;
        }

        void UpdateAI(const uint32 diff)
        {
            if (punch1 <= diff)
            {
                me->HandleEmote(35);
                punch1 = 7500;
            }
            else
                punch1 -= diff;

            if (punch2 <= diff)
            {
                me->HandleEmote(36);
                punch2 = 7500;
            }
            else
                punch2 -= diff;

            if (punch3 <= diff)
            {
                me->HandleEmote(37);
                punch3 = 7500;
            }
            else
                punch3 -= diff;
        }
    };
};

/*######
## mob_huojin_trainee - 54586, 65470
######*/

enum HuojinTraineeMisc
{
	NPC_HUOJIN_TRAINEE_MALE = 54586,
	NPC_HUOJIN_TRAINEE_FEMALE = 65470,
	NPC_MASTER_SHANG_XI = 53566,
	SPELL_BLACKOUT_KICK = 100784
};

enum HuojinTraineeEvents
{
	EVENT_HUOJIN_STATE_STAND = 1,
	EVENT_HUOJIN_ONESHOT_SALUTE = 2,
	EVENT_HUOJIN_TALK = 3,
	EVENT_HUOJIN_RUN = 4,
	EVENT_HUOJIN_BLACKOUT_KICK = 5,
	EVENT_HUOJIN_GOHOME = 6,
	EVENT_HUOJIN_RESET = 7

};

class mob_huojin_trainee : public CreatureScript
{
public:
	mob_huojin_trainee() : CreatureScript("mob_huojin_trainee") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_huojin_trainee_AI(creature);
	}

	struct mob_huojin_trainee_AI : public ScriptedAI
	{
		mob_huojin_trainee_AI(Creature* creature) : ScriptedAI(creature) { }

		Creature* partner;

		uint32 checkTimer;
		uint32 emoteTimer;

		bool masterShangXiFound;
		bool partnerBusy;
		bool salute;
		bool running;

		void Reset()
		{
			checkTimer = 1500;
			emoteTimer = 1000;

			masterShangXiFound = false;
			partnerBusy = false;
			salute = false;
			running = false;
			me->SetReactState(REACT_DEFENSIVE);
			me->setFaction(7);
			events.Reset();
		}

		void JustRespawned()
		{
			Reset();
		}

		void EnterCombat(Unit* unit)
		{
			events.ScheduleEvent(EVENT_HUOJIN_BLACKOUT_KICK, 2000);
		}

		void DamageTaken(Unit* attacker, uint32& damage)
		{
			if (me->HealthBelowPctDamaged(16.67f, damage))
			{
				// Clear in combat
				attacker->ClearInCombat();
				//
				damage = 0;
				running = true;
				me->CombatStop();
				me->setFaction(11);
				me->HandleEmoteCommand(EMOTE_STATE_STAND);

				events.ScheduleEvent(EVENT_HUOJIN_TALK, 800);
				events.ScheduleEvent(EVENT_HUOJIN_RUN, 3500);
				events.CancelEvent(EVENT_HUOJIN_BLACKOUT_KICK);

				if (attacker && attacker->GetTypeId() == TYPEID_PLAYER)
					attacker->ToPlayer()->KilledMonsterCredit(54586, 0);
			}
		}

		void UpdateAI(const uint32 diff)
		{
			events.Update(diff);

			if (me->isInCombat())
			{
				DoMeleeAttackIfReady();
				me->HandleEmoteCommand(EMOTE_STATE_READYUNARMED);
				events.CancelEvent(EVENT_HUOJIN_STATE_STAND);
			}
			else
			{
				if (checkTimer <= diff)
				{
					if (me->FindNearestCreature(NPC_MASTER_SHANG_XI_, 1.5f) && !me->isInCombat() && !masterShangXiFound)
					{
						// Since this creature don't ever die, is't require to be despawned, 
						// but this secuence is "visualy" equal to despawn and respawn.
						masterShangXiFound = true;
						events.ScheduleEvent(EVENT_HUOJIN_GOHOME, 3000/* + me->GetRespawnTime()*/);
						events.ScheduleEvent(EVENT_HUOJIN_RESET, 6000/* + me->GetRespawnTime()*/);
						me->SetVisible(false);
						return;
					}

					/* Check Huojin trainee. */
					std::list<Creature*> huojinList;
					GetCreatureListWithEntryInGrid(huojinList, me, NPC_HUOJIN_TRAINEE_FEMALE, 1.0f);
					GetCreatureListWithEntryInGrid(huojinList, me, NPC_HUOJIN_TRAINEE_MALE, 1.0f);

					for (std::list<Creature*>::iterator iter = huojinList.begin(); iter != huojinList.end(); ++iter)
						if ((*iter)->GetGUID() != me->GetGUID())
							partner = (*iter);

					/* Is my partner busy? */
					if (partner->isInCombat() || !partner || !partner->isAlive() || (partner->GetDistance2d(me)) >  1.0f)
						partnerBusy = true;
					else
						partnerBusy = false;

					checkTimer = 1500;
				}
				else
				{
					checkTimer -= diff;
				}
				/*  */
				if (partnerBusy)
				{
					if (!salute)
					{
						salute = true;
						events.ScheduleEvent(EVENT_HUOJIN_ONESHOT_SALUTE, 1500);
						events.ScheduleEvent(EVENT_HUOJIN_STATE_STAND, 4000);
					}
				}
				else
				{
					if (salute)
					{
						salute = false;
						events.CancelEvent(EVENT_HUOJIN_STATE_STAND);
					}

					if (!running)
					{
						if (emoteTimer <= diff)
						{
							switch (irand(0, 4))
							{
							case 0:
								me->HandleEmoteCommand(EMOTE_ONESHOT_MONKOFFENSE_ATTACKUNARMED);
								break;
							case 1:
								me->HandleEmoteCommand(EMOTE_ONESHOT_MONKOFFENSE_SPECIALUNARMED);
								break;
							case 2:
								me->HandleEmoteCommand(EMOTE_ONESHOT_MONKOFFENSE_PARRYUNARMED);
								break;
							case 3:
								me->HandleEmoteCommand(EMOTE_ONESHOT_PALMSTRIKE);
								break;
							case 4:
								me->HandleEmoteCommand(EMOTE_ONESHOT_MONKOFFENSE_ATTACKUNARMEDOFF);
								break;
							}
							emoteTimer = irand(3500, 5000);
						}
						else
						{
							emoteTimer -= diff;
						}
					}
				}
			}

			if (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_HUOJIN_STATE_STAND:
					me->HandleEmoteCommand(EMOTE_STATE_STAND);
					break;
				case EVENT_HUOJIN_ONESHOT_SALUTE:
					me->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
					events.CancelEvent(EVENT_HUOJIN_ONESHOT_SALUTE);
					break;
				case EVENT_HUOJIN_TALK:
					Talk(irand(0, 7));
					events.CancelEvent(EVENT_HUOJIN_TALK);
					break;
				case EVENT_HUOJIN_RUN:
					if (me->GetAreaId() != 5825)
						me->GetMotionMaster()->MovePoint(0, 1446.322876f, 3389.027588f, 173.782471f);
					events.CancelEvent(EVENT_HUOJIN_RUN);
					break;
				case EVENT_HUOJIN_BLACKOUT_KICK:
					if (me->getVictim())
						me->CastSpell(me->getVictim(), SPELL_BLACKOUT_KICK, true);
					events.ScheduleEvent(EVENT_HUOJIN_BLACKOUT_KICK, irand(6000, 8000));
					break;
				case EVENT_HUOJIN_GOHOME:
					me->GetMotionMaster()->MoveTargetedHome();
					events.CancelEvent(EVENT_HUOJIN_GOHOME);
					break;
				case EVENT_HUOJIN_RESET:
					Reset();
					me->SetVisible(true);
					events.CancelEvent(EVENT_HUOJIN_RESET);
					break;
				default:
					break;
				}
			}
		}
	private:
		EventMap events;
	};
};

/*######
## npc_merchant_lorvo - 54943
######*/

enum merchantLorvoMisc
{
	QUEST_AYSA_OF_THE_TUSHUI = 29410,
	SAY_MERCHANT_LORVO_1 = 0, // Shhhh! Come quietly. She's practicing. Shhhh! Acercate en silencio. Se esta entrenando.
};

class npc_merchant_lorvo : public CreatureScript
{
public:
	npc_merchant_lorvo() : CreatureScript("npc_merchant_lorvo") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_merchant_lorvoAI(creature);
	}

	struct npc_merchant_lorvoAI : public ScriptedAI
	{
		npc_merchant_lorvoAI(Creature* creature) : ScriptedAI(creature)
		{
		}

		std::list<uint64> salutePlayerList;

		uint32 checkTimer;

		void Reset()
		{
			checkTimer = 1000;
		}

		bool HasSaluteTo(Player* player)
		{
			for (auto splayer : salutePlayerList)
			{
				if (splayer == player->GetGUID())
				{
					return true;
					break;
				}
			}

			salutePlayerList.push_back(player->GetGUID());
			return false;
		}

		void UpdateAI(const uint32 diff)
		{
			if (checkTimer <= diff)
			{
				std::list<Player*> playerList;
				GetPlayerListInGrid(playerList, me, 10.0f);

				for (auto player : playerList)
				{
					if (player->GetQuestStatus(QUEST_AYSA_OF_THE_TUSHUI) == QUEST_STATUS_COMPLETE && !HasSaluteTo(player))
					{
						Talk(SAY_MERCHANT_LORVO_1);
					}
				}
				checkTimer = 1000;
			}
			else
			{
				checkTimer -= diff;
			}
		}
	};
};

/*######
## mob_ji_firepaw - 54568
######*/

enum eMiscJiFirepaw
{
	QUEST_JI_OF_THE_HUOJIN = 29522,
	SOUND_JI_OF_THE_HUOJIN_1 = 27344,
	SAY_JI_OF_THE_HUOJIN_1 = 0,
};

class mob_ji_firepaw : public CreatureScript
{
public:
	mob_ji_firepaw() : CreatureScript("mob_ji_firepaw") { }

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

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_ji_firepawAI(creature);
	}

	struct mob_ji_firepawAI : public ScriptedAI
	{
		mob_ji_firepawAI(Creature* creature) : ScriptedAI(creature)
		{
		}

		std::list<uint64> salutePlayerList;

		uint32 checkTimer;

		void Reset()
		{
			checkTimer = 1000;
		}

		bool HasSalutedTo(Player* player)
		{
			for (auto splayer : salutePlayerList)
			{
				if (splayer == player->GetGUID())
				{
					return true;
					break;
				}
			}

			salutePlayerList.push_back(player->GetGUID());
			return false;
		}

		void UpdateAI(const uint32 diff)
		{
			if (checkTimer <= diff)
			{
				std::list<Player*> playerList;
				GetPlayerListInGrid(playerList, me, 10.0f);

				for (auto cPlayer : playerList)
				{
					if (cPlayer->GetQuestStatus(QUEST_JI_OF_THE_HUOJIN) == QUEST_STATUS_COMPLETE && !HasSalutedTo(cPlayer))
					{
						Talk(SAY_JI_OF_THE_HUOJIN_1);
						me->PlayDirectSound(SOUND_JI_OF_THE_HUOJIN_1, cPlayer);
					}
				}
				checkTimer = 1000;
			}
			else
			{
				checkTimer -= diff;
			}
			DoMeleeAttackIfReady();
		}
	};
};

/*######
## mob_huojin_monk - 60176
######*/

enum eMiscHuojiMonk
{
	QUEST_THE_SPIRITS_GUARDIAN = 29420,
	SAY_HUOJIN_MONK_1 = 0, // The fire spirit is upset. It's dangerous to enter the Shrine now....
};

class mob_huojin_monk : public CreatureScript
{
public:
	mob_huojin_monk() : CreatureScript("mob_huojin_monk") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_huojin_monkAI(creature);
	}

	struct mob_huojin_monkAI : public ScriptedAI
	{
		mob_huojin_monkAI(Creature* creature) : ScriptedAI(creature)
		{
		}

		std::list<uint64> salutePlayerList;

		uint32 checkTimer;

		void Reset()
		{
			checkTimer = 1000;
		}

		bool HasSaluteTo(Player* player)
		{
			for (auto cPlayer : salutePlayerList)
			{
				if (cPlayer == player->GetGUID())
				{
					return true;
					break;
				}
			}

			salutePlayerList.push_back(player->GetGUID());
			return false;
		}

		void UpdateAI(const uint32 diff)
		{
			if (checkTimer <= diff)
			{
				std::list<Player*> playerList;
				GetPlayerListInGrid(playerList, me, 15.0f);

				for (auto cPlayer : playerList)
				{
					if (cPlayer->GetQuestStatus(QUEST_THE_SPIRITS_GUARDIAN) == QUEST_STATUS_COMPLETE && !HasSaluteTo(cPlayer))
					{
						Talk(SAY_HUOJIN_MONK_1);
					}
				}
				checkTimer = 1000;
			}
			else
			{
				checkTimer -= diff;
			}
		}
	};
};

/*######
## mob_flame_spout - 59626
######*/

enum eFlameSpoutMisc
{
	SPELL_FLAME_SPOUT_1 = 114686,
	SPELL_FLAME_SPOUT_2 = 114684
};

enum eFlameSpoutEvents
{
	EVENT_FLAME_SPOUT_1 = 1,
	EVENT_FLAME_SPOUT_2 = 2,
	EVENT_FLAME_SPOUT_3 = 3
};

class mob_flame_spout : public CreatureScript
{
public:
	mob_flame_spout() : CreatureScript("mob_flame_spout") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_flame_spoutAI(creature);
	}

	struct mob_flame_spoutAI : public ScriptedAI
	{
		mob_flame_spoutAI(Creature* creature) : ScriptedAI(creature)
		{
		}

		void Reset()
		{
			events.ScheduleEvent(EVENT_FLAME_SPOUT_1, 1000);
		}

		void UpdateAI(const uint32 diff)
		{
			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_FLAME_SPOUT_1:
					if (irand(1, 100) <= 35)
					{
						me->CastSpell(me, SPELL_FLAME_SPOUT_1, false);
						events.ScheduleEvent(EVENT_FLAME_SPOUT_2, 2000);
					}
					else
					{
						events.ScheduleEvent(EVENT_FLAME_SPOUT_1, 7000);
					}
					break;
				case EVENT_FLAME_SPOUT_2:
					me->CastSpell(me, SPELL_FLAME_SPOUT_2, false);
					events.ScheduleEvent(EVENT_FLAME_SPOUT_3, 4000);
					break;
				case EVENT_FLAME_SPOUT_3:
					me->RemoveAurasDueToSpell(SPELL_FLAME_SPOUT_1);
					events.ScheduleEvent(EVENT_FLAME_SPOUT_1, 1000);
					break;
				default:
					break;
				}
			}
		}
	private:
		EventMap events;
	};
};

/*######
## go_brazier_of_the_flame - 209369, 209372, 209373, 209374
######*/

enum eBrazierMisc
{
	ITEM_TORCH_OF_PRISMATIC_FLAME = 75000,
	ITEM_UNLIT_CHALLENGERS_TORCH = 75008,

	SPELL_LIGHT_CHALLENGERS_TORCH = 105151,
	SPELL_QUEST_CREDIT_RED = 105156,
	SPELL_QUEST_CREDIT_BLUE = 105157,
	SPELL_QUEST_CREDIT_VIOLET = 105158,

	GO_BRAZIER_OF_THE_FLICKERING_FLAME = 209369,
	GO_BRAZIER_OF_THE_VIOLET_FLAME_0 = 209372,
	GO_BRAZIER_OF_THE_VIOLET_FLAME_1 = 209803,
	GO_BRAZIER_OF_THE_BLUE_FLAME_0 = 209373,
	GO_BRAZIER_OF_THE_BLUE_FLAME_1 = 209802,
	GO_BRAZIER_OF_THE_RED_FLAME_0 = 209374,
	GO_BRAZIER_OF_THE_RED_FLAME_1 = 209801
};

Position const braziersPositions[] =
{
	{ 1333.55f, 3945.18f, 110.544f, 0.0f }, // Brazier of the Flickering Flame
	{ 1367.34f, 3937.73f, 110.267f, 0.0f }, // Brazier of the Red Flame
	{ 1333.31f, 3932.52f, 110.387f, 0.0f }, // Brazier of the Blue Flame
	{ 1343.03f, 3957.44f, 110.398f, 0.0f }  // Brazier of the Violet Flame
};

class go_brazier_of_the_flame : public GameObjectScript
{
public:
	go_brazier_of_the_flame() : GameObjectScript("go_brazier_of_the_flame") { }

	// Spawn current brazier and give player credit.
	void SpawnLigtedBrazier(Player* aPlayer, uint32 aGoID, uint32 aCreditSpell, uint32 aPosIndex)
	{
		GameObject* summonGo = aPlayer->SummonGameObject(aGoID, braziersPositions[aPosIndex].GetPositionX(), braziersPositions[aPosIndex].GetPositionY(), braziersPositions[aPosIndex].GetPositionZ(), 0, 0, 0, 0, 0, 0, aPlayer->GetGUID());
		summonGo->SetByteValue(GAMEOBJECT_BYTES_1, 1, 0);
		summonGo->SetGoState(GO_STATE_ACTIVE);
		summonGo->CastSpell(aPlayer, aCreditSpell);
		aPlayer->RemoveAurasDueToSpell(aCreditSpell);
	}

	void SpawnUnliteBraziers(Player* aPlayer)
	{
		aPlayer->SummonGameObject(GO_BRAZIER_OF_THE_RED_FLAME_1, braziersPositions[1].GetPositionX(), braziersPositions[1].GetPositionY(), braziersPositions[1].GetPositionZ(), 0, 0, 0, 0, 0, 0, aPlayer->GetGUID());
		aPlayer->SummonGameObject(GO_BRAZIER_OF_THE_BLUE_FLAME_1, braziersPositions[2].GetPositionX(), braziersPositions[2].GetPositionY(), braziersPositions[2].GetPositionZ(), 0, 0, 0, 0, 0, 0, aPlayer->GetGUID());
		aPlayer->SummonGameObject(GO_BRAZIER_OF_THE_VIOLET_FLAME_1, braziersPositions[3].GetPositionX(), braziersPositions[3].GetPositionY(), braziersPositions[3].GetPositionZ(), 0, 0, 0, 0, 0, 0, aPlayer->GetGUID());
	}

	bool OnGossipHello(Player* Player, GameObject* go)
	{
		switch (go->GetEntry())
		{
		case GO_BRAZIER_OF_THE_FLICKERING_FLAME:
			if (Player->HasItemCount(ITEM_UNLIT_CHALLENGERS_TORCH))
			{
				SpawnLigtedBrazier(Player, GO_BRAZIER_OF_THE_FLICKERING_FLAME, SPELL_LIGHT_CHALLENGERS_TORCH, 0);
				Player->DestroyItemCount(ITEM_UNLIT_CHALLENGERS_TORCH, -1, true, false);
				go->DestroyForPlayer(Player);
				SpawnUnliteBraziers(Player);
			}
			break;
		case GO_BRAZIER_OF_THE_RED_FLAME_1:
			SpawnLigtedBrazier(Player, GO_BRAZIER_OF_THE_RED_FLAME_0, SPELL_QUEST_CREDIT_RED, 1);
			go->DestroyForPlayer(Player);
			break;
		case GO_BRAZIER_OF_THE_BLUE_FLAME_1:
			SpawnLigtedBrazier(Player, GO_BRAZIER_OF_THE_BLUE_FLAME_0, SPELL_QUEST_CREDIT_BLUE, 2);
			go->DestroyForPlayer(Player);
			break;
		case GO_BRAZIER_OF_THE_VIOLET_FLAME_1:
			SpawnLigtedBrazier(Player, GO_BRAZIER_OF_THE_VIOLET_FLAME_0, SPELL_QUEST_CREDIT_VIOLET, 3);
			go->DestroyForPlayer(Player);
			break;
		default:
			break;
		}
		return true;
	}
};

/*######
## mob_master_li_fei - 54135
######*/

enum eMasterLifeiMisc
{
	QUEST_THE_CHALLENGERS_FIRES    = 29664,
	SPELL_CANCEL_CHALLENGERS_TORCH = 119304,
	NPC_MASTER_LI_FEI_BOSS         = 54734
};

class mob_master_li_fei : public CreatureScript
{
public:
	mob_master_li_fei() : CreatureScript("mob_master_li_fei") {}

	bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
	{
		if (quest->GetQuestId() == QUEST_ONLY_THE_WORTHY_SHALL_PASS)
		{
			// ToDO: Get correct emote.
			creature->HandleEmoteCommand(EMOTE_ONESHOT_KICK);
			// ToDO: Get the spell that leap back the player, casted by master li fei, this is used by now.
			float vcos = std::cos(6.10f);
			float vsin = std::sin(6.10f);
			player->SendMoveKnockBack(player, 16.0f, -10.0f, vcos, vsin);
			// Spawn Master Li Fei Boss.
			if (Creature* masterLiFei = creature->SummonCreature(NPC_MASTER_LI_FEI_BOSS, 1347.237f, 3940.618f, 109.2756f, 5.930672f, TEMPSUMMON_MANUAL_DESPAWN, 0, 0/*player->GetGUID()*//*, &list*/))
			{
				CAST_AI(boss_li_fei_fight::boss_li_fei_fightAI, masterLiFei->AI())->TimedAttackStart(player->GetGUID(), 2000);
			}
		}
		return true;
	}

	bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 /*opt*/)
	{ 
		if (quest->GetQuestId() == QUEST_THE_CHALLENGERS_FIRES)
			creature->CastSpell(player, SPELL_CANCEL_CHALLENGERS_TORCH, true);
		return false;
	}
};

/*######
# spell_fan_the_flames_effects - 109090, 109095, 109105, 109109
#######*/

enum eSpellFanTHeFlames
{
	NPC_HUO = 57779,
};

class spell_fan_the_flames_effects : public SpellScriptLoader
{
public:
	spell_fan_the_flames_effects() : SpellScriptLoader("spell_fan_the_flames_effects") { }

	class spell_fan_the_flames_effects_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_fan_the_flames_effects_SpellScript);

		void CheckTarget(std::list<WorldObject*>& unitList)
		{
			std::list<WorldObject*> tempList;

			for (auto itr : unitList)
			{
				if (itr->GetEntry() == NPC_HUO)
					tempList.push_back(itr);
			}

			unitList.clear();

			for (auto itr : tempList)
				unitList.push_back(itr);
		}

		void Register()
		{
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fan_the_flames_effects_SpellScript::CheckTarget, EFFECT_0, TARGET_UNIT_CONE_ENTRY);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_fan_the_flames_effects_SpellScript();
	}
};

/*######
# spell_fan_the_flames - 102522
#######*/

class spell_fan_the_flames : public SpellScriptLoader
{
public:
	spell_fan_the_flames() : SpellScriptLoader("spell_fan_the_flames") { }

	class spell_fan_the_flames_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_fan_the_flames_SpellScript);

		SpellCastResult CheckCast()
		{
			bool isHuoNear;
			// Check if Huo is Near as required by Spells Fan the Flames
			if (GetCaster()->FindNearestCreature(NPC_HUO, 10.0f, true))
				isHuoNear = true;
			else
				isHuoNear = false;
			// Check for Shrine of the Inner-Ligth
			if (GetCaster()->GetAreaId() != 5849 || !isHuoNear)
				return SPELL_FAILED_INCORRECT_AREA;
			else
				return SPELL_CAST_OK;
		};

		void Register()
		{
			OnCheckCast += SpellCheckCastFn(spell_fan_the_flames_SpellScript::CheckCast);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_fan_the_flames_SpellScript();
	}
};

/*######
# mob_chia_hui_autumnleaf - 60248
#######*/

enum eChiaHuiAutumnleaf
{
	QUEST_THE_PASSION_OF_SHEN_ZIN_SU = 29423
};

class mob_chia_hui_autumnleaf : public CreatureScript
{
public:
	mob_chia_hui_autumnleaf() : CreatureScript("mob_chia_hui_autumnleaf") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_chia_hui_autumnleafAI(creature);
	}

	struct mob_chia_hui_autumnleafAI : public ScriptedAI
	{
		mob_chia_hui_autumnleafAI(Creature* creature) : ScriptedAI(creature)
		{
		}

		bool hasSaid1;

		void Reset()
		{
			hasSaid1 = false;
		}

		void DoAction(uint8 action)
		{
			switch (action)
			{
			case ACTION_TALK:
				if (!hasSaid1)
				{
					Talk(0);
					hasSaid1 = true;
				}
				break;
			}
		}

		void UpdateAI(const uint32 diff)
		{
			std::list<Player*> playerList;
			GetPlayerListInGrid(playerList, me, 12.0f);
			for (auto player : playerList)
			{
				if (player->GetQuestStatus(QUEST_THE_PASSION_OF_SHEN_ZIN_SU) == QUEST_STATUS_INCOMPLETE)
				{
					DoAction(ACTION_TALK);
				}
			}

			DoMeleeAttackIfReady();
		}
	};
};

// @TODO
class mob_brewer_lin : public CreatureScript
{
    public:
        mob_brewer_lin() : CreatureScript("mob_brewer_lin") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_brewer_linAI(creature);
        }

        struct mob_brewer_linAI : public ScriptedAI
        {
            mob_brewer_linAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            bool hasSaid1;

            void Reset()
            {
                hasSaid1 = false;
            }

            void DoAction (uint8 action)
            {
                switch (action)
                {
                case ACTION_TALK:
                    if (!hasSaid1)
                    {
                        Talk(0);
                        hasSaid1 = true;
                    }
                    break;
                }
            }

            void UpdateAI(const uint32 diff)
            {
                std::list<Player*> playerList;
                GetPlayerListInGrid(playerList, me, 4.0f);
                for (auto player: playerList)
                {
                    if (player->GetQuestStatus(29423) == QUEST_STATUS_INCOMPLETE)
                    {
                        DoAction(ACTION_TALK);
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

// TODO@
class mob_jaomin_ro : public CreatureScript
{
    public:
        mob_jaomin_ro() : CreatureScript("mob_jaomin_ro") { }

        bool OnGossipHello(Player*player , Creature*creature)
        {
            if (Creature* vehicle = player->SummonCreature(55685, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation()))
            {
                creature->GetAI()->Reset();
            }

            return true;
        }
};

/*######
## npc_monke_brewthief - 56730
######*/

enum eMiscmonkeBrewthief
{
	NPC_BREWTHIEF_MONKEY     = 56730,
	NPC_PANDA_FEMALE		 = 65472,
	NPC_PANDA_MALE	         = 57132,
	NPC_MONKEY_RED			 = 57205,
};

class npc_monke_brewthief : public CreatureScript
{
public:
	npc_monke_brewthief() : CreatureScript("npc_monke_brewthief") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_monke_brewthiefAI(creature);
	}

	struct npc_monke_brewthiefAI : public ScriptedAI
	{
		npc_monke_brewthiefAI(Creature* creature) : ScriptedAI(creature){}

		uint32 checkTimmer;
		bool HasATarget;

		void Reset()
		{
			checkTimmer = 1000;
			HasATarget = false;
		}
		void DamageTaken(Unit* who, uint32& damage)
		{
			if (who->GetEntry() == NPC_PANDA_MALE /*&& damage >= me->GetHealth() || */ || who->GetEntry() == NPC_PANDA_FEMALE/* && damage >= me->GetHealth()*/)
				damage = 0;
				//me->SetHealth(me->GetMaxHealth());

			if (who->GetTypeId() == TYPEID_PLAYER || who->isPet())
			{
				if (Creature* male = me->FindNearestCreature(NPC_PANDA_MALE, 6.0f, true))
				{
					male->getThreatManager().resetAllAggro();
					male->CombatStop(true);
				}
				
				if (Creature* Fmale = me->FindNearestCreature(NPC_PANDA_FEMALE, 6.0f, true))
				{
					Fmale->getThreatManager().resetAllAggro();
					Fmale->CombatStop(true);
				}

				me->getThreatManager().resetAllAggro();
				me->GetMotionMaster()->MoveChase(who);
				me->AI()->AttackStart(who);
			}
		}
		void UpdateAI(const uint32 diff)
		{
			if (checkTimmer <= diff)
			{
				if (!UpdateVictim())
				{
					if (Creature* Male = me->FindNearestCreature(NPC_PANDA_MALE, 6.0f, true))
					{
						me->SetReactState(REACT_AGGRESSIVE);
						me->AI()->AttackStart(Male);
					}
					else if (Creature* Fmale = me->FindNearestCreature(NPC_PANDA_FEMALE, 6.0f, true))
					{
						me->SetReactState(REACT_AGGRESSIVE);
						me->AI()->AttackStart(Fmale);
					}
				}
				checkTimmer = 1000;
			}
			DoMeleeAttackIfReady();
		}
	};
};

/*######
## npc_wosong_villager - 57132, 65472
######*/

class npc_wosong_villager : public CreatureScript
{
public:
	npc_wosong_villager() : CreatureScript("npc_wosong_villager") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_wosong_villagerAI(creature);
	}

	struct npc_wosong_villagerAI : public ScriptedAI
	{
		npc_wosong_villagerAI(Creature* creature) : ScriptedAI(creature)
		{
		}

		uint32 monkeyAttackTimmer;
		uint32 checkTimmer;
		bool HasATarget;

		void Reset()
		{
			me->GetMotionMaster()->MoveTargetedHome();
			checkTimmer = 1000;
			HasATarget = false;
		}

		void DamageTaken(Unit* doneBy, uint32& damage)
		{
			if (doneBy->ToCreature())
				if (me->GetHealth() <= damage || me->GetHealthPct() <= 80.0f)
					damage = 0;
		}

		void DamageDealt(Unit* target, uint32& damage, DamageEffectType damageType)
		{
			if (target->ToCreature())
				if (target->GetHealth() <= damage || target->GetHealthPct() <= 70.0f)
					damage = 0;
		}

		void MoveInLineOfSight(Unit* who)
		{
			if (who && !HasATarget)
				if (me->GetDistance(who) < 5.0f)
					if (Creature* creature = who->ToCreature())
						if (creature->GetEntry() == NPC_BREWTHIEF_MONKEY || creature->GetEntry() == NPC_MONKEY_RED)
							AttackStart(who);
		}

		void EnterEvadeMode()
		{
			Reset();
		}

		void UpdateAI(const uint32 diff)
		{
			if (checkTimmer <= diff)
			{
				if (!UpdateVictim())
				{
					if (Creature* Monkey = me->FindNearestCreature(NPC_BREWTHIEF_MONKEY, 6.0f, true))
					{
						me->SetReactState(REACT_AGGRESSIVE);
						me->AI()->AttackStart(Monkey);
					}
					else if (Creature* Monkey_red = me->FindNearestCreature(NPC_MONKEY_RED, 6.0f, true))
					{
						me->SetReactState(REACT_AGGRESSIVE);
						me->AI()->AttackStart(Monkey_red);
					}
				}
				checkTimmer = 1000;
			}
			else
				checkTimmer -= diff;

			if (!me->isInCombat())
			{
				Reset();
			}
			DoMeleeAttackIfReady();
		}
	};
};

/*######
## npc_hozu_hanging_bunny - 56739
######*/

enum eHangingBunny
{
	SPELL_RIDE_VEHICLE_HARDCODED = 46598,
	NPC_HOZU_HANGING_MONKEY = 54131,
};

class npc_hozu_hanging_bunny : public CreatureScript
{
public:
	npc_hozu_hanging_bunny() : CreatureScript("npc_hozu_hanging_bunny") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_hozu_hanging_bunnyAI(creature);
	}

	struct npc_hozu_hanging_bunnyAI : public ScriptedAI
	{
		npc_hozu_hanging_bunnyAI(Creature* creature) : ScriptedAI(creature)
		{
		}

		uint64 m_myHozuGuid;
		uint32 m_checkTimer;
		bool hasHozu;

		void Reset()
		{
			me->SetDisableGravity(true);
			m_checkTimer = 300;
			hasHozu = false;

			// For some reason is needed to relocate the bunny
			float x, y, z, o;
			me->GetPosition(x, y, z);
			o = me->GetOrientation();
			me->SetPosition(x, y, z - 1.5f, o);
		}

		void ProcesHozu(Creature* aHozu)
		{
			aHozu->CastSpell(me, SPELL_RIDE_VEHICLE_HARDCODED, true);

			float x, y, z, o;
			aHozu->GetPosition(x, y, z);
			o = aHozu->GetOrientation();
			aHozu->SetPosition(x, y, z - 1.5f, 0.0f);
		}

		void UpdateAI(const uint32 diff)
		{
			if (m_checkTimer <= diff)
			{
				if (hasHozu)
				{
					if (Unit* _Hozu = ObjectAccessor::FindUnit(m_myHozuGuid))
					{
						if (_Hozu && !_Hozu->isInCombat() && _Hozu->isAlive() && !_Hozu->HasAura(SPELL_RIDE_VEHICLE_HARDCODED))
						{
							ProcesHozu(_Hozu->ToCreature());
						}
					}
					m_checkTimer = 10 * IN_MILLISECONDS;
				}
				else
				{
					Creature* monkey = me->FindNearestCreature(NPC_HOZU_HANGING_MONKEY, 25.0f);
					if (monkey && !monkey->isInCombat() && monkey->isAlive())
					{
						m_myHozuGuid = monkey->GetGUID();
						ProcesHozu(monkey);
						hasHozu = true;
					}
					m_checkTimer = 3 * IN_MILLISECONDS;
				}
			}
			else
			{
				m_checkTimer -= diff;
			}
		}
	};
};

/*######
## npc_hozu_hanging_monkey - 54131
######*/

enum eHozuMisk
{
	NPC_HOZU_HANGING_BUNNY = 56739,
	SPELL_PERMANENT_FEIGN_DEATH_STUN = 96733,
};

class npc_hozu_hanging_monkey : public CreatureScript
{
public:
	npc_hozu_hanging_monkey() : CreatureScript("npc_hozu_hanging_monkey") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_hozu_hanging_monkeyAI(creature);
	}

	struct npc_hozu_hanging_monkeyAI : public ScriptedAI
	{
		npc_hozu_hanging_monkeyAI(Creature* creature) : ScriptedAI(creature)
		{
		}

		void Reset()
		{
			me->SetReactState(REACT_DEFENSIVE);

			if (me->HasAura(SPELL_PERMANENT_FEIGN_DEATH_STUN))
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
		}

		void DamageTaken(Unit* doneBy, uint32& damage)
		{
			if (me->HasAura(SPELL_RIDE_VEHICLE_HARDCODED))
			{
				std::list<Creature*> bunnyList;
				GetCreatureListWithEntryInGrid(bunnyList, me, NPC_HOZU_HANGING_BUNNY, 2.0f);
				for (auto _cBunny : bunnyList)
					_cBunny->RemoveAurasDueToSpell(SPELL_RIDE_VEHICLE_HARDCODED);
			}
		}

		void UpdateAI(const uint32 diff)
		{
			if (me->isInCombat())
			{
				DoMeleeAttackIfReady();
			}
		}
	};
};

/*######
## npc_stone_ritual_bunny - 69900
######*/

enum eStoneRitualBunnyMisc
{
	NPC_LIVING_AIR                           = 54631,
	
	SPELL_SUMMON_LIVING_AIR                  = 106299,
	SPEL_RUNE_RUINATION_TWILIGHT_RUNE_OF_AIR = 86946,
	SPELL_LIGHTNING_STRIKE_COSMETIC          = 140857,
};

enum eStoneRitualBunnyEvents
{
	EVENT_SUMMON_LIVING_AIR = 1,
};

// This are the positions where the Air Spirit shout be spawned.
Position const AirSpiritSpawnPositions[] =
{
	{ 1232.79f, 3698.32f, 93.4866f, 1.62512f },
	{ 1241.17f, 3725.63f, 94.1434f, 3.38439f },
	{ 1225.95f, 3734.42f, 91.3392f, 4.86236f }
};

class npc_stone_ritual_bunny : public CreatureScript
{

public:
	npc_stone_ritual_bunny() : CreatureScript("npc_stone_ritual_bunny") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_stone_ritual_bunnyAI(creature);
	}

	struct npc_stone_ritual_bunnyAI : public ScriptedAI
	{
		npc_stone_ritual_bunnyAI(Creature* creature) : ScriptedAI(creature) { }

		Creature* livingAir;

		float m_timesCorrection;
		uint8 m_pos;
		
		void Reset()
		{
			me->SetDisableGravity(true);
			m_timesCorrection = 1.0f;
			m_pos = 0;
		}

		void SpellHit(Unit* caster, const SpellInfo* spell)
		{
			if (spell->Id == SPELL_SUMMON_LIVING_AIR)
			{
				m_timesCorrection = me->GetDistance(caster) / 14.0f;
				events.ScheduleEvent(1, (2500 * m_timesCorrection));
			}
		}

		void UpdateAI(const uint32 diff)
		{
			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_SUMMON_LIVING_AIR:
				{
					m_pos = irand(0, 2);
					me->CastSpell(me, SPEL_RUNE_RUINATION_TWILIGHT_RUNE_OF_AIR, true);
					if (livingAir = me->SummonCreature(NPC_LIVING_AIR, AirSpiritSpawnPositions[m_pos].GetPositionX(), AirSpiritSpawnPositions[m_pos].GetPositionY(), AirSpiritSpawnPositions[m_pos].GetPositionZ(), AirSpiritSpawnPositions[m_pos].GetOrientation(), TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000))
						me->CastSpell(livingAir, SPELL_LIGHTNING_STRIKE_COSMETIC, true);
				}break;
				default:
					break;
				}
			}
		}
	private:
		EventMap events;
	};
};

/*######
# spell_summon_living_air - 106299
#######*/

enum SpellSummonLivingAir
{
	NPC_STONE_RITUAL_BUNNY = 69900,
};

class spell_summon_living_air : public SpellScriptLoader
{
public:
	spell_summon_living_air() : SpellScriptLoader("spell_summon_living_air") { }

	class spell_summon_living_air_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_summon_living_air_SpellScript);

		void FilterTargets(std::list<WorldObject*>& unitList)
		{
			Unit* unit_to_add = NULL;
			for (std::list<WorldObject*>::iterator itr = unitList.begin(); itr != unitList.end(); ++itr)
			{
				if (Unit* unit = (*itr)->ToUnit())
				{
					if (unit->GetEntry() == NPC_STONE_RITUAL_BUNNY)
					{
						unit_to_add = unit;
						break;
					}
				}
			}

			unitList.clear();
			if (unit_to_add)
				unitList.push_back(unit_to_add);
		}

		void Register()
		{
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_summon_living_air_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_summon_living_air_SpellScript();
	}
};

// @ToDo - DELETE
class npc_master_shangshi_intown : public CreatureScript
{

public:
	npc_master_shangshi_intown() : CreatureScript("npc_master_shangshi_intown") { }

	bool OnGossipHello(Player* player, Creature* creature)
	{
		creature->HandleEmoteCommand(EMOTE_ONESHOT_TALK);

		if (creature->isQuestGiver())
		{
			//player->PrepareQuestMenu(creature->GetGUID());
			//player->SEND_GOSSIP_MENU(907, creature->GetGUID());
		}
		return true;
	}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_master_shangshi_intownAI(creature);
	}

	struct npc_master_shangshi_intownAI : public ScriptedAI
	{

		npc_master_shangshi_intownAI(Creature* creature) : ScriptedAI(creature)
		{
		}
		//uint64 PlayerGUID;
		//uint32 Check_Visivility;

		void Reset()
		{
			//PlayerGUID = 0;
			//Check_Visivility = urand(1000, 2000);
			me->AddAura(126160, me);
		}

		void UpdateAI(const uint32 diff)
		{
			//if (Check_Visivility <= diff)
			//{
			//	if (Player* player = me->FindNearestPlayer(15.0f, true))
			//	if (player->GetQuestStatus(29523) == QUEST_STATUS_INCOMPLETE || player->GetQuestStatus(29523) == !QUEST_STATUS_REWARDED)
			//		me->SetVisible(false);
			//	else
			//		me->SetVisible(true);

			//	Check_Visivility = urand(1000, 2000);// Cpu optimizer
			//}
			//else
			//{
			//	Check_Visivility -= diff;
			//}
		}
	};
};

/*######
## npc_trainee_guang - 60244
######*/

enum traineeGuangMisc
{
	SAY_TRAINEE_GUANG_1 = 0, // You're departing so soom? I am envious of your prowess, $C. Good luck to to you.
};

class npc_trainee_guang : public CreatureScript
{
public:
	npc_trainee_guang() : CreatureScript("npc_trainee_guang") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_trainee_guangAI(creature);
	}

	struct npc_trainee_guangAI : public ScriptedAI
	{
		npc_trainee_guangAI(Creature* creature) : ScriptedAI(creature) { }

		std::list<uint64> salutePlayerList;

		uint32 m_checkTimer;

		void Reset()
		{
			m_checkTimer = 1000;
		}

		bool HasSalutedTo(Player* player)
		{
			for (auto splayer : salutePlayerList)
			{
				if (splayer == player->GetGUID())
				{
					return true;
					break;
				}
			}

			salutePlayerList.push_back(player->GetGUID());
			return false;
		}

		void UpdateAI(const uint32 diff)
		{
			if (m_checkTimer <= diff)
			{
				std::list<Player*> playerList;
				GetPlayerListInGrid(playerList, me, 15.0f);

				for (auto player : playerList)
				{
					if (!HasSalutedTo(player))
					{
						std::string sPclass = ((sChrClassesStore.LookupEntry(player->getClass()))->name);
						std::string sText = ("You're departing so soom? I am envious of your prowess, " + sPclass + ". Good luck to you.");
						me->MonsterSay(sText.c_str(), LANG_UNIVERSAL, 0);
						me->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
					}
				}
				m_checkTimer = 1000;
			}
			else
			{
				m_checkTimer -= diff;
			}
		}
	};
};

/*######
## go_scroll_post - 210987
######*/

enum eScrollPost
{
	GAMEOBJECT_EDICT_OF_TEMPERANCE         = 210986,
	QUEST_THE_LESSON_OF_THE_BURNING_SCROLL = 29408
};

class go_scroll_post : public GameObjectScript
{
public:
	go_scroll_post() : GameObjectScript("go_scroll_post") {}

	GameObjectAI* GetAI(GameObject* go) const
	{
		return new go_scroll_postAI(go);
	}

	struct go_scroll_postAI : public GameObjectAI
	{
		go_scroll_postAI(GameObject* go) : GameObjectAI(go)	{ }

		uint32 checkElderTimer;

		void Reset()
		{
			checkElderTimer = 4000;
		};

		void UpdateAI(uint32 diff)
		{
			if (checkElderTimer <= diff)
			{
				std::list<Player*> playersNear;
				GetPlayerListInGrid(playersNear, go, 5.0f);

				if (GameObject* edict = go->FindNearestGameObject(GAMEOBJECT_EDICT_OF_TEMPERANCE, 5.0f))
				{
					edict->SetGoState(GO_STATE_READY);
					edict->Respawn();

					for (auto player : playersNear)
					{
						if (player->GetQuestStatus(QUEST_THE_LESSON_OF_THE_BURNING_SCROLL) == QUEST_STATUS_REWARDED)
						{
							edict->DestroyForPlayer(player);
						}
						else
						{
							edict->SendUpdateToPlayer(player);
							player->UpdateTriggerVisibility();
						}
					}
				}
				checkElderTimer = 4000;
			}
			else
			{
				checkElderTimer -= diff;
			}
		}
	};
};

void AddSC_WanderingIsland_North()
{
    new mob_master_shang_xi();
    new go_wandering_weapon_rack();
    new mob_training_target();
    new mob_tushui_trainee();
    new mob_huojin_trainee();
    new mob_jaomin_ro();
    new boss_jaomin_ro();
   // new mob_attacker_dimwind();
    new mob_min_dimwind();
    new mob_aysa_lake_escort();
    new mob_aysa();
    new mob_trainee_nim();
    //new mob_instructors();
    //new mob_aspiring_trainee();
    new mob_ji_firepaw();
    new npc_merchant_lorvo();
    new mob_huojin_monk();
    new boss_living_air();
    new boss_li_fei_fight();
    new mob_chia_hui_autumnleaf();
    new mob_brewer_lin();
    new spell_huo_benediction();
    new AreaTrigger_at_temple_entrance();
	new mob_instructor_qun();
	new mob_quiet_lam();
	new mob_instructor_zhi();
	new mob_min_dimwind_final();
	new mob_min_dimwind_summon();
	new mob_aysa_meditating();
	new mob_flame_spout();
	new go_brazier_of_the_flame();
	new mob_master_li_fei();
	new spell_fan_the_flames_effects();
	new spell_fan_the_flames();
	new npc_monke_brewthief();
	new npc_wosong_villager();
	new npc_hozu_hanging_bunny();
	new npc_hozu_hanging_monkey();
	new npc_stone_ritual_bunny();
	new spell_summon_living_air();
	//new npc_master_shangshi_intown();
	new npc_trainee_guang();
	new go_scroll_post();
	new npc_the_masters_flame();
}
