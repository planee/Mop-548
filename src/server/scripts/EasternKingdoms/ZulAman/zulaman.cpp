

#include "ScriptPCH.h"
#include "zulaman.h"

/*######
## npc_zulaman_voljin
######*/

enum VolJinYells
{
	SAY_FOLLOW = 0,
	SAY_GONG = 1,
	SAY_OPEN = 2,
	SAY_RESET = 3,
	ANN_GONG = 4
};

enum HostageYells
{
	SAY_BOSS_DEAD = 0,
	SAY_CHEST = 1,
	SAY_THANKS = 2,
};

enum Points
{
	POINT_TURN = 1,
	POINT_DOWN = 2,
};

Position const wayPos[3] =
{
	{ 120.234f, 1656.628f, 42.021f },
	{ 129.312f, 1645.332f, 42.021f },
	{ 120.660f, 1638.805f, 42.358f },
};

const Position posTurnPoint = { 232.83f, 1367.78f, 48.58f, 1.79f };
const Position posDownPoint = { 227.75f, 1460.83f, 25.98f, 4.75f };
const Position posUpPoint = { 280.12f, 1380.63f, 49.35f, 3.46f };

enum HierophantYells
{
	/*
	// Dialogue:
	Zandalari Hierophant says: Dis shattered world not done breakin, mon.
	Zandalari Hierophant says: De tides of darkness gonna take over. All da trolls be in danger.
	Zandalari Hierophant says: Zul has seen tha' future. We gotta come together, or we all fall to de darkness.
	Zandalari Hierophant says: De Zandalari got powers you never seen. Wisdom of de most ancient of trolls, wisdom dat's rightfully yours.
	Zandalari Hierophant says: Dis land was taken from us in a tide of blood.
	Zandalari Hierophant says: De Darkspear be foolish. No one gonna stand in our way.
	Zandalari Hierophant says: De green fist of de troll empire gonna crush dis land and make it our own again.
	Zandalari Hierophant says: 'Dis be de only way, bruddahs.
	*/
	YELL_HIEROPHANT_DIALOGUE_1 = 0,
	YELL_HIEROPHANT_DIALOGUE_2 = 1,
	YELL_HIEROPHANT_DIALOGUE_3 = 2,
	YELL_HIEROPHANT_DIALOGUE_4 = 3,
	YELL_HIEROPHANT_DIALOGUE_5 = 4,
	YELL_HIEROPHANT_DIALOGUE_6 = 5,
	YELL_HIEROPHANT_DIALOGUE_7 = 6,
	YELL_HIEROPHANT_DIALOGUE_8 = 7,

	YELL_HIEROPHANT_GLORY = 8
};

enum Events
{
	// Amani'shi Tempest
	EVENT_SUMMON_EAGLES = 1,
	EVENT_SUMMON_MOBS = 2,
	EVENT_THUNDERCLAP = 3,
	EVENT_CHAIN_LIGHTNING = 4,

	// Amani'shi Warrior
	EVENT_CHARGE1 = 5,
	EVENT_KICK = 6,

	// Amani'shi Guardian
	EVENT_GUARDIAN_ENRAGE,
	EVENT_GUARDIAN_SLEEP,

	// Amani'shi Savage
	EVENT_SAVAGE_REND,
	EVENT_SAVAGE_HAMSTRING,
	EVENT_SAVAGE_SUNDER_ARMOR,

	// Voljin
	EVENT_MOVE_0 = 1,
	EVENT_MOVE_1,
	EVENT_MOVE_2,
	EVENT_STOP_MOVE,
	EVENT_GONG_START,
	EVENT_GONG_RESET,
	EVENT_SAY_OPEN,
	EVENT_OPEN_GATES,

	// Amani Eagle
	EVENT_TALON1,

	// Mobs
	EVENT_DIALOGUE_1,
	EVENT_DIALOGUE_2,
	EVENT_DIALOGUE_3,
	EVENT_DIALOGUE_4,
	EVENT_DIALOGUE_5,
	EVENT_DIALOGUE_6,
	EVENT_DIALOGUE_7,
	EVENT_DIALOGUE_8,

	EVENT_BLESSING_ZAND_HIERO,
	EVENT_BLESSING_ZAND_ARCHON,
	EVENT_BLESSING_ZAND_JUGGER,

	EVENT_GLORY_HIERO,  //  Ancients of Zandalar, grant dis one da power ta' mock death itself!
	EVENT_GLORY_ARCHON, //  Ancients of Zandalar, mark 'dem for de black road!
	EVENT_GLORY_JUGGER, //  Ancestors be beside me, let 'dem hear yo' voice!

	// Hierophant
	EVENT_GUARDIAN,
	EVENT_POWER,
	EVENT_SANCTIFY,
	EVENT_HYPOTHERMIA,

	// Archon
	EVENT_SIGIL_OF_DEATH,
	EVENT_SIGIL_OF_FLAME,
	EVENT_SIGIL_OF_FROST,
	EVENT_SIGIL_SHATTER,

	// Juggernaut
	EVENT_ANCESTRAL_CALL


};

enum Spells
{
	// Glory
	SPELL_GLORY_HIEROPHANT = 97969,
	SPELL_GLORY_ARCHON = 97971,
	SPELL_GLORY_JUGGERNAUT = 97970,

	SPELL_BLESSING_OF_ZAND = 97977, // Before Glory.

	// Hierophant
	SPELL_ANCIENT_GUARDIAN = 97978, // - Glory.
	SPELL_ANCIENT_POWER = 23979,
	SPELL_SANCTIFY = 97974, // - Sanctify Aura.
	SPELL_HYPOTHERMIA = 96332,

	// Juggernaut
	SPELL_ANCESTRAL_CALL = 98000, // - Glory.
	SPELL_EARTHQUAKE_AURA = 97987,

	// Archon
	SPELL_SIGIL_OF_DEATH = 98018,
	SPELL_SIGIL_OF_FLAME = 98006,
	SPELL_SIGIL_OF_FROST = 98015,
	SPELL_SIGIL_SHATTER = 98024, // - Glory.

	SPELL_REMOVE_AMANI_CURSE = 43732,
	SPELL_PUSH_MOJO = 43923,
	SPELL_SUMMON_MONEY_BAG = 43774,
	SPELL_SUMMON_AMANI_CHARM_CHEST1 = 43835,
	SPELL_SUMMON_AMANI_CHARM_CHEST2 = 43756,

	// Amani Eagle
	SPELL_TALON = 43517,



	// Achievement Hex Mix
	SPELL_MELISSA_ACHIEVEMENT = 97905,
	SPELL_MAWAGO_ACHIEVEMENT = 97906,
	SPELL_TYLLAN_ACHIEVEMENT = 97907,
	SPELL_MICAH_ACHIEVEMENT = 97908,
	SPELL_ARINOTH_ACHIEVEMENT = 97909,
	SPELL_KALDRICK_ACHIEVEMENT = 97910,
	SPELL_LENZO_ACHIEVEMENT = 97911,
	SPELL_MELASONG_ACHIEVEMENT = 97912,
	SPELL_HARALD_ACHIEVEMENT = 97913,
	SPELL_RELISSA_ACHIEVEMENT = 97914,
	SPELL_EULINDA_ACHIEVEMENT = 97915,
	SPELL_ROSA_ACHIEVEMENT = 97916,
};


enum Action
{
	ACTION_EVENTS_START = 1,
	ACTION_GONG_COMPLETE,
};



class npc_zulaman_voljin : public CreatureScript
{
public:
	npc_zulaman_voljin() : CreatureScript("npc_zulaman_voljin") { }

	bool OnGossipHello(Player* player, Creature* pCreature)
	{
		if (pCreature->isQuestGiver())
			player->PrepareQuestMenu(pCreature->GetGUID());

		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "We're ready to open the gates.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		player->SEND_GOSSIP_MENU(66672, pCreature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
	{
		if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
		{
			pPlayer->PlayerTalkClass->ClearMenus();
			pPlayer->CLOSE_GOSSIP_MENU();
			pCreature->GetAI()->DoAction(ACTION_EVENTS_START);
		}

		return true;
	}

	struct npc_zulaman_voljinAI : public ScriptedAI
	{
		npc_zulaman_voljinAI(Creature* pCreature) : ScriptedAI(pCreature)
		{
			instance = pCreature->GetInstanceScript();
			activated = false;
			Starting = false;
		}

		InstanceScript* instance;
		bool activated, Starting;
		EventMap events;

		void UpdateAI(const uint32 diff)
		{
			if (!activated)
				return;

			if (activated && !Starting)
			{
				events.ScheduleEvent(EVENT_MOVE_0, 1000);
				Starting = true;
			}

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_MOVE_0:
					Talk(SAY_FOLLOW);
					me->GetMotionMaster()->MovePoint(0, wayPos[0]);
					events.ScheduleEvent(EVENT_MOVE_1, 2500);
					break;
				case EVENT_MOVE_1:
					me->GetMotionMaster()->MovePoint(0, wayPos[1]);
					events.ScheduleEvent(EVENT_STOP_MOVE, 2500);
					break;
				case EVENT_STOP_MOVE:
					Talk(SAY_GONG);
					Talk(ANN_GONG);
					events.ScheduleEvent(EVENT_GONG_START, 2000);
					break;
				case EVENT_GONG_START:
					if (GameObject * gong = me->FindNearestGameObject(187359, 30.0f))
					{
						gong->SetGoState(GO_STATE_ACTIVE);
						gong->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
						DoCast(104012);
					}
					events.ScheduleEvent(EVENT_GONG_RESET, 2000);
					break;
				case EVENT_GONG_RESET:
					if (GameObject * gong = me->FindNearestGameObject(187359, 30.0f))
						gong->SetGoState(GO_STATE_READY);
					events.ScheduleEvent(EVENT_MOVE_2, 2000);
					break;
				case EVENT_MOVE_2:
					me->GetMotionMaster()->MovePoint(0, wayPos[2]);
					events.ScheduleEvent(EVENT_SAY_OPEN, 2500);
					break;
				case EVENT_SAY_OPEN:
					Talk(SAY_OPEN);
					events.ScheduleEvent(EVENT_OPEN_GATES, 5000);
					break;
				case EVENT_OPEN_GATES:
					if (GameObject * gate = me->FindNearestGameObject(186728, 50.0f))
						gate->UseDoorOrButton();
					if (Creature* Guardian = me->FindNearestCreature(52938, 50.0f, true))
						Guardian->AI()->Talk(1);
					break;

				default:
					break;
				}
			}
		}

		void DoAction(const int32 action)
		{
			switch (action)
			{
			case ACTION_EVENTS_START:
				me->Dismount();
				me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
				activated = true;
				break;
			case ACTION_GONG_COMPLETE:
				events.CancelEvent(EVENT_GONG_RESET);
				events.CancelEvent(EVENT_GONG_START);
				if (GameObject * gong = me->FindNearestGameObject(187359, 10.0f))
					gong->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
				break;
			}
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_zulaman_voljinAI(pCreature);
	}
};

/*######
## npc_forest_frog
######*/


#define NPC_FOREST_FROG           24396

class npc_zulaman_forest_frog : public CreatureScript
{
public:
	npc_zulaman_forest_frog() : CreatureScript("npc_zulaman_forest_frog") { }

	struct npc_zulaman_forest_frogAI : public ScriptedAI
	{
		npc_zulaman_forest_frogAI(Creature* pCreature) : ScriptedAI(pCreature)
		{
			pInstance = pCreature->GetInstanceScript();
			reward = 0;
		}

		InstanceScript* pInstance;
		uint8 reward;

		void Reset() {}

		void EnterCombat(Unit* /*who*/) {}

		void DoSpawnRandom()
		{
			if (pInstance)
			{
				uint32 cEntry = 0;
				uint32 spellId = 0; // For Achievement
				switch (urand(0, 11))
				{
				case 0: cEntry = NPC_HARALD; spellId = SPELL_HARALD_ACHIEVEMENT; break;
				case 1: cEntry = NPC_EULINDA; spellId = SPELL_EULINDA_ACHIEVEMENT; break;
				case 2: cEntry = NPC_ARINOTH; reward = 1; spellId = SPELL_ARINOTH_ACHIEVEMENT; break;
				case 3: cEntry = NPC_LENZO; reward = 1; spellId = SPELL_LENZO_ACHIEVEMENT; break;
				case 4: cEntry = NPC_MELISSA; reward = 2; spellId = SPELL_MELISSA_ACHIEVEMENT; break;
				case 5: cEntry = NPC_MAWAGO; reward = 2; spellId = SPELL_MAWAGO_ACHIEVEMENT; break;
				case 6: cEntry = NPC_MELASONG; reward = 2; spellId = SPELL_MELASONG_ACHIEVEMENT;; break;
				case 7: cEntry = NPC_ROSA; reward = 2; spellId = SPELL_ROSA_ACHIEVEMENT; break;
				case 8: cEntry = NPC_RELISSA; reward = 2; spellId = SPELL_RELISSA_ACHIEVEMENT; break;
				case 9: cEntry = NPC_TYLLAN; reward = 2; spellId = SPELL_TYLLAN_ACHIEVEMENT; break;
				case 10: cEntry = NPC_KALDRICK; reward = 2; spellId = SPELL_KALDRICK_ACHIEVEMENT; break;
				case 11: cEntry = NPC_MICAH; reward = 2; spellId = SPELL_MICAH_ACHIEVEMENT; break;
				}

				if (cEntry == NPC_HARALD && pInstance->GetData(DATA_VENDOR_1))
					cEntry = NPC_TYLLAN;
				if (cEntry == NPC_EULINDA && pInstance->GetData(DATA_VENDOR_2))
					cEntry = NPC_ARINOTH;

				if (cEntry) me->UpdateEntry(cEntry);

				if (spellId)
					DoCastAOE(spellId, true);

				// There must be only one vendor per instance
				if (cEntry == NPC_HARALD)
					pInstance->SetData(DATA_VENDOR_1, DONE);
				else if (cEntry == NPC_EULINDA)
					pInstance->SetData(DATA_VENDOR_2, DONE);
				else
				{
					if (reward == 1)
						me->CastSpell(me, SPELL_SUMMON_MONEY_BAG, true);
					else if (reward == 2)
						me->CastSpell(me, urand(0, 1) ? SPELL_SUMMON_AMANI_CHARM_CHEST1 : SPELL_SUMMON_AMANI_CHARM_CHEST2, true);

					me->DespawnOrUnsummon(5000);
				}
			}
		}

		void SpellHit(Unit* caster, const SpellInfo* spell)
		{
			if (spell->Id == SPELL_REMOVE_AMANI_CURSE && caster->GetTypeId() == TYPEID_PLAYER && me->GetEntry() == NPC_FOREST_FROG)
			{
				if (roll_chance_i(6))
				{
					if (!caster->ToPlayer()->HasItemCount(33993) && !caster->HasSpell(43918))
					{
						DoCast(caster, SPELL_PUSH_MOJO, true);
						me->DespawnOrUnsummon();
					}
					else
						DoSpawnRandom();
				}
				else
					DoSpawnRandom();
			}
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_zulaman_forest_frogAI(pCreature);
	}
};


/*######
## npc_zulaman_hostage
######*/



//  Hazlek, Bakkalzu, Norkani, Kasha
static uint32 HostageEntry[] = { 52939, 52941, 52943, 52945 };
static uint32 ChestEntry[] = { 186648, 187021, 186667, 186672 };
uint32 CageEntry[] = { 187377, 187378, 187379, 187380 };

class npc_zulaman_hostage : public CreatureScript
{
public:
	npc_zulaman_hostage() : CreatureScript("npc_zulaman_hostage") { }

	struct npc_zulaman_hostageAI : public ScriptedAI
	{
		npc_zulaman_hostageAI(Creature* pCreature) : ScriptedAI(pCreature) {}

		uint64 PlayerGUID;

		void Reset() {}

		void EnterCombat(Unit* /*who*/) {}

		void IsSummonedBy(Unit* /*summoner*/)

		{
			Talk(SAY_BOSS_DEAD);
		}

		void UpdateAI(const uint32 /*diff*/) {}

	};

	bool OnGossipHello(Player* player, Creature* pCreature)
	{
		player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "I came to save you.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
		player->SEND_GOSSIP_MENU(player->GetGossipTextId(pCreature), pCreature->GetGUID());
		return true;
	}

	bool OnGossipSelect(Player* player, Creature* pCreature, uint32 /*sender*/, uint32 action)
	{
		player->PlayerTalkClass->ClearMenus();

		if (action == GOSSIP_ACTION_INFO_DEF + 1)
			player->CLOSE_GOSSIP_MENU();

		if (!pCreature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP))
			return true;

		pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

		InstanceScript* instance = pCreature->GetInstanceScript();
		if (instance)
		{
			pCreature->AI()->Talk(SAY_CHEST);
			uint8 progress = instance->GetData(DATA_CHESTLOOTED);
			instance->SetData(DATA_CHESTLOOTED, 0);
			float x, y, z;
			pCreature->GetClosePoint(x, y, z, pCreature->GetObjectSize() / 3, 5.0f);
			uint32 entry = pCreature->GetEntry();
			for (uint8 i = 0; i < 4; ++i)

			{
				if (HostageEntry[i] == entry)
				{
					if (GameObject* cage = pCreature->FindNearestGameObject(CageEntry[i], 50.0f))

					if (cage->GetEntry() == CageEntry[i])
						cage->UseDoorOrButton();
					pCreature->SummonGameObject(ChestEntry[i], x, y, z, 0, 0, 0, 0, 0, 0);
					instance->DoKilledMonsterKredit(29217, HostageEntry[i], 0);
					pCreature->ForcedDespawn(5000);
					break;
				}


			}
		}
		return true;
	}

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_zulaman_hostageAI(pCreature);
	}
};


class npc_zulaman_juggernaut : public CreatureScript
{
public:
	npc_zulaman_juggernaut() : CreatureScript("npc_zulaman_juggernaut") { }

	struct npc_zulaman_juggernautAI : public ScriptedAI
	{
		npc_zulaman_juggernautAI(Creature* pCreature) : ScriptedAI(pCreature)
		{
			instance = pCreature->GetInstanceScript();
			pCreature->AddAura(SPELL_EARTHQUAKE_AURA, pCreature);
		}

		InstanceScript* instance;
		EventMap events;
		bool gloryCasted;

		void Reset()
		{
			gloryCasted = false;
		}

		void EnterEvadeMode()
		{
			if (me->HasAura(SPELL_GLORY_JUGGERNAUT))
				me->RemoveAura(SPELL_GLORY_JUGGERNAUT);

			me->GetMotionMaster()->MoveTargetedHome();
			Reset();

			me->SetHealth(me->GetMaxHealth());
		}

		void EnterCombat(Unit* /*who*/) { }

		void UpdateAI(uint32 const diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
				return;

			if (me->HealthBelowPct(36) && !gloryCasted)
			{
				events.ScheduleEvent(EVENT_BLESSING_ZAND_JUGGER, 100);
				events.ScheduleEvent(EVENT_GLORY_JUGGER, 200);
				events.ScheduleEvent(EVENT_ANCESTRAL_CALL, 5000);
				gloryCasted = true;
			}

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_BLESSING_ZAND_JUGGER:
					Talk(0);
					DoCast(me, SPELL_BLESSING_OF_ZAND);
					break;

				case EVENT_GLORY_JUGGER:
					DoCast(me, SPELL_GLORY_JUGGERNAUT);
					break;

				case EVENT_ANCESTRAL_CALL:
					DoCast(me, SPELL_ANCESTRAL_CALL);
					events.ScheduleEvent(EVENT_ANCESTRAL_CALL, urand(20000, 30000));
					break;
				}
			}

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_zulaman_juggernautAI(pCreature);
	}
};

class npc_zulaman_hierophant : public CreatureScript
{
public:
	npc_zulaman_hierophant() : CreatureScript("npc_zulaman_hierophant") { }

	struct npc_zulaman_hierophantAI : public ScriptedAI
	{
		npc_zulaman_hierophantAI(Creature* pCreature) : ScriptedAI(pCreature)
		{
			instance = pCreature->GetInstanceScript();

		}

		InstanceScript* instance;
		EventMap events;
		bool gloryCasted;

		void Reset()
		{
			gloryCasted = false;
		}

		void EnterEvadeMode()
		{
			if (me->HasAura(SPELL_GLORY_HIEROPHANT))
				me->RemoveAura(SPELL_GLORY_HIEROPHANT);

			me->GetMotionMaster()->MoveTargetedHome();
			Reset();

			me->SetHealth(me->GetMaxHealth());
		}

		void EnterCombat(Unit* who)
		{
			events.CancelEvent(EVENT_DIALOGUE_2);
			events.ScheduleEvent(EVENT_POWER, urand(3000, 8000));
			events.ScheduleEvent(EVENT_HYPOTHERMIA, urand(5000, 12000));

			std::list<Creature*> creatures;
			GetCreatureListWithEntryInGrid(creatures, me, 53021, 80.0f);

			if (creatures.empty())
				return;

			for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
			{
				(*iter)->SetWalk(false);
				(*iter)->SetSpeed(MOVE_RUN, 2.0f);
				(*iter)->AI()->AttackStart(who);
			}
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (me->HealthBelowPct(36) && !gloryCasted)
			{
				events.ScheduleEvent(EVENT_GLORY_HIERO, 200);
				events.ScheduleEvent(EVENT_BLESSING_ZAND_HIERO, 100);
				events.ScheduleEvent(EVENT_GUARDIAN, 5000);
				gloryCasted = true;
			}
			events.Update(diff);

			if (me->HasUnitState(UNIT_STATE_CASTING))
				return;

			if (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_DIALOGUE_2:
					Talk(YELL_HIEROPHANT_DIALOGUE_2);
					break;

				case EVENT_GLORY_HIERO:
					Talk(YELL_HIEROPHANT_GLORY);
					DoCast(me, SPELL_GLORY_HIEROPHANT);
					break;

				case EVENT_BLESSING_ZAND_HIERO:
					DoCast(me, SPELL_BLESSING_OF_ZAND);
					break;

				case EVENT_GUARDIAN:
					DoCast(me, SPELL_ANCIENT_GUARDIAN);
					break;

				case EVENT_POWER:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
						DoCast(target, SPELL_ANCIENT_POWER, true);
					events.ScheduleEvent(EVENT_POWER, urand(9000, 17000));
					break;

				case EVENT_HYPOTHERMIA:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
						me->AddAura(SPELL_HYPOTHERMIA, target);
					events.ScheduleEvent(EVENT_HYPOTHERMIA, urand(15000, 20000));
					break;
				}
			}

			DoMeleeAttackIfReady();
		}


	};


	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_zulaman_hierophantAI(pCreature);
	}

};


void AddSC_zulaman()
{
	new npc_zulaman_voljin();
	new npc_zulaman_forest_frog();
	new npc_zulaman_hostage();
	new npc_zulaman_juggernaut();
	new npc_zulaman_hierophant();
}
