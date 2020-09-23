#include "CreatureAI.h"
#include "ScriptPCH.h"
#include "zulaman.h"

enum Yells
{
	YELL_INTRO = 0,
	YELL_AGGRO = 1,
	YELL_KILL_ONE = 5,
	YELL_KILL_TWO = 2,
	YELL_DEATH = 6,
	YELL_BERSERK = 3,

	YELL_BEAR = 4,
	YELL_LYNX = 7,
	YELL_EAGLE = 8,
	YELL_DRAGONHAWK = 9,

	YELL_FIRE_BREATH = 10,

	ANN_BEAR = 11,
	ANN_LYNX = 12,
	ANN_EAGLE = 13,
	ANN_DRAGONHAWK = 14,
};

enum PhaseDaakara
{
	PHASE_NONE = 0,
	PHASE_TROLL = 1,
	// At 80%.
	PHASE_BEAR = 2,
	PHASE_EAGLE = 3,
	// At 40%.
	PHASE_LYNX = 4,
	PHASE_DRAGONHAWK = 5
};

enum Spells
{
	//====== Troll Form
	SPELL_WHIRLWIND = 17207,
	SPELL_GRIEVOUS_THROW = 43093,

	//====== Bear Form
	SPELL_CREEPING_PARALYSIS = 43095,   // should cast on the whole raid
	SPELL_OVERPOWER = 43456,
	SPELL_SURGE = 42402,

	//====== Eagle Form
	SPELL_ENERGY_STORM = 43983,   // enemy area aura, trigger 42577
	SPELL_ZAP_INFORM = 42577,
	SPELL_ZAP_DAMAGE = 43137,   // 1250 damage
	SPELL_SUMMON_CYCLONE = 43112,   // summon four feather vortex
	SPELL_CYCLONE_VISUAL = 97835,
	SPELL_CYCLONE_PASSIVE = 43120,   // trigger 43121 (4y aoe) every second
	SPELL_SUMMON_LIGHT_TOTEM = 43302, // Lightning Totem
	SPELL_SWEEPING_WINDS = 97647,
	SPELL_SUM_VORTEX = 97648,
	FEATHER_VISUAL = 43147,
	SPELL_STORM = 43121,


	//====== Lynx Form
	SPELL_CLAW_RAGE_CHARGE = 42583, // charge
	SPELL_CLAW_RAGE_DAMAGE = 43150, // damage - 10 on target.
	SPELL_LYNX_RUSH = 43153, // run and damage.
	SPELL_SUMMON_LYNX = 97686,

	//====== Dragonhawk Form
	SPELL_FLAME_WHIRL = 43213,   // trigger two spells
	SPELL_FLAME_BREATH = 43140,
	SPELL_SUMMON_BREATH_LINE = 97497,
	SPELL_SUMMON_PILLAR = 43216,   // summon 24187
	CREATURE_COLUMN_OF_FIRE = 24187,
	SPELL_PILLAR_TRIGGER = 43218,   // trigger 43217
	SPELL_PILLAR_OF_FLAME_VISUAL = 43541,  // Visual Column of Fire
	SPELL_PILLAR_OF_FLAME_AURA = 43218, // Aura on da' Move!

	//====== Transforms:
	SPELL_SHAPE_OF_THE_BEAR = 42594,   // 15% dmg
	SPELL_SHAPE_OF_THE_EAGLE = 42606,

	SPELL_SHAPE_OF_THE_LYNX = 42607,   // haste melee 30%
	SPELL_SHAPE_OF_DRAGONHAWK = 42608,

	SPELL_BERSERK = 45078
};

enum Npc
{
	CREATURE_FEATHER_VORTEX = 24136
};

enum Events
{
	//====== Troll Form
	EVENT_WHIRLWIND = 1,
	EVENT_GRIEVOUS_THROW,
	//====== Bear Form
	EVENT_SURGE,
	EVENT_OVERPOWER,
	EVENT_CREEPING_PARALYSIS,
	//====== Lynx Form
	EVENT_SUMMON_LYNX,
	EVENT_CLAW_RAGE,
	EVENT_LYNX_RUSH,
	//====== Eagle Form
	EVENT_LIGHTNING_TOTEM,
	EVENT_SWEEPING_WINDS,
	EVENT_TORNADO_MOVE, // After Sweeping Winds.
	EVENT_TORNADO_STOP,

	//====== Dragonhawk Form
	EVENT_FLAME_BREATH,
	EVENT_FLAME_WHIRL,
	EVENT_PILLAR_OF_FIRE,

	EVENT_BERSERK,

	//====== Achievement "Ring Out"
	EVENT_CHECK_PLAYERS,
};

#define MAX_X 136.199707f
#define MIN_X 104.217331f
#define MAX_Y 715.623901f
#define MIN_Y 697.285217f

class boss_daakara : public CreatureScript
{
public:
	boss_daakara() : CreatureScript("boss_daakara") { }

	struct boss_daakaraAI : public ScriptedAI
	{
		boss_daakaraAI(Creature* creature) : ScriptedAI(creature), summons(me)
		{
			instance = creature->GetInstanceScript();
			introDone = false;
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
			bAchieve = true;
		}

		InstanceScript* instance;
		SummonList summons;
		EventMap events;

		bool introDone, firstSelection, secondSelection, hasclawTarget, isFlameBreathing, canCastClaw, canCastRush, bAchieve;
		PhaseDaakara Phase;
		uint32 clawRageTicks;
		uint32 lynxRushes;
		Unit* clawTarget;

		void Reset()
		{
			events.Reset();
			summons.DespawnAll();

			if (instance)
				instance->SetData(DATA_DAAKARAEVENT, NOT_STARTED);

			Phase = PHASE_NONE;
			firstSelection = false;
			secondSelection = false;
			bAchieve = true;
			clawRageTicks = 0;
			lynxRushes = 0;
			hasclawTarget = false;
			canCastClaw = false;
			canCastRush = false;
			bAchieve = true;
			isFlameBreathing = false;

			SetEquipmentSlots(false, 69916, 0, 0);
		}

		void MoveInLineOfSight(Unit* who)
		{
			if (!introDone && me->IsWithinDistInMap(who, 40) && who->GetTypeId() == TYPEID_PLAYER)
			{
				Talk(YELL_INTRO);
				introDone = true;
			}
		}

		void EnterCombat(Unit* /*who*/)
		{
			Talk(YELL_AGGRO);
			bAchieve = true;
			if (instance)
			{
				instance->SetData(DATA_DAAKARAEVENT, IN_PROGRESS);
				instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
			}

			if (GameObject* door = me->FindNearestGameObject(186859, 80.0f))
				door->SetGoState(GO_STATE_READY);

			EnterPhase(PHASE_TROLL);
			events.ScheduleEvent(EVENT_BERSERK, 10 * MINUTE * IN_MILLISECONDS);
			events.ScheduleEvent(EVENT_CHECK_PLAYERS, 5000);
		}

		void JustSummoned(Creature* summon)
		{
			summons.Summon(summon);
			summon->setActive(true);

			if (me->isInCombat())
				summon->AI()->DoZoneInCombat();
		}

		void EnterEvadeMode()
		{
			Reset();
			me->GetMotionMaster()->MoveTargetedHome();
			me->RemoveAllAuras();
			me->SetHealth(me->GetMaxHealth());

			if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE))
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);

			if (GameObject* door = me->FindNearestGameObject(186859, 80.0f))
				door->SetGoState(GO_STATE_ACTIVE);

			if (instance)
			{
				instance->SetData(DATA_DAAKARAEVENT, FAIL);
				instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
			}
		}

		void KilledUnit(Unit* /*victim*/)
		{
			Talk(RAND(YELL_KILL_ONE, YELL_KILL_TWO));
		}

		void JustDied(Unit* /*killer*/)
		{
			Talk(YELL_DEATH);
			summons.DespawnAll();

			if (GameObject* door = me->FindNearestGameObject(186859, 80.0f))
				door->SetGoState(GO_STATE_ACTIVE);

			if (instance)
			{
				instance->SetData(DATA_DAAKARAEVENT, DONE);
				instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
				instance->DoModifyPlayerCurrenciesIfLevel(395, 5000, 85);
			}
		}

		bool AllowAchieve()
		{
			return bAchieve;
		}

		void EnterPhase(PhaseDaakara NextPhase)
		{
			switch (NextPhase)
			{
			case PHASE_TROLL:
				events.ScheduleEvent(EVENT_WHIRLWIND, 7000);
				events.ScheduleEvent(EVENT_GRIEVOUS_THROW, 9500);
				break;

			case PHASE_BEAR:
				SetEquipmentSlots(false, 0, 0, 0);
				Talk(YELL_BEAR);
				Talk(ANN_BEAR);
				DoCast(me, SPELL_SHAPE_OF_THE_BEAR);

				events.ScheduleEvent(EVENT_SURGE, 6000);
				events.ScheduleEvent(EVENT_OVERPOWER, 15000);
				events.ScheduleEvent(EVENT_CREEPING_PARALYSIS, 9000);

				me->AI()->AttackStart(me->getVictim());
				break;

			case PHASE_LYNX:
				SetEquipmentSlots(false, 0, 0, 0);
				Talk(YELL_LYNX);
				Talk(ANN_LYNX);
				DoCast(me, SPELL_SHAPE_OF_THE_LYNX);

				canCastClaw = true;
				events.ScheduleEvent(EVENT_CLAW_RAGE, 5000);
				events.ScheduleEvent(EVENT_LYNX_RUSH, 14000);
				events.ScheduleEvent(EVENT_SUMMON_LYNX, 2000);

				me->AI()->AttackStart(me->getVictim());
				break;

			case PHASE_EAGLE:
			{
								SetEquipmentSlots(false, 0, 0, 0);
								Talk(YELL_EAGLE);
								Talk(ANN_EAGLE);
								me->RemoveAurasDueToSpell(me->HasAura(SPELL_SHAPE_OF_THE_BEAR ? SPELL_SHAPE_OF_THE_BEAR : SPELL_SHAPE_OF_THE_LYNX));

								Map::PlayerList const& players = me->GetMap()->GetPlayers();
								for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
								if (Player* player = itr->getSource())
								{
									Creature* Cyclone = me->SummonCreature(CREATURE_FEATHER_VORTEX, player->GetPositionX(), player->GetPositionY(), player->GetPositionZ(), player->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
									if (Cyclone)
									{
										Cyclone->SetSpeed(MOVE_RUN, 1.0f);
										Cyclone->AddAura(43120, Cyclone);
										Cyclone->AddAura(97835, Cyclone);
										Cyclone->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
										Cyclone->SetFlag(UNIT_FIELD_FLAGS, MOVEMENTFLAG_DISABLE_GRAVITY);
									}
								}


								DoCast(me, SPELL_SHAPE_OF_THE_EAGLE);
								me->AddAura(SPELL_ENERGY_STORM, me); // enemy aura

								events.ScheduleEvent(EVENT_LIGHTNING_TOTEM, 1000);
								events.ScheduleEvent(EVENT_SWEEPING_WINDS, 2000);

								me->GetMotionMaster()->Clear();
								me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
			}
				break;

			case PHASE_DRAGONHAWK:
				SetEquipmentSlots(false, 0, 0, 0);
				Talk(YELL_DRAGONHAWK);
				Talk(ANN_DRAGONHAWK);
				me->RemoveAurasDueToSpell(me->HasAura(SPELL_SHAPE_OF_THE_BEAR ? SPELL_SHAPE_OF_THE_BEAR : SPELL_SHAPE_OF_THE_LYNX));
				DoCast(me, SPELL_SHAPE_OF_DRAGONHAWK);
				events.ScheduleEvent(EVENT_FLAME_BREATH, urand(5000, 12000));
				events.ScheduleEvent(EVENT_FLAME_WHIRL, urand(3000, 5000));
				events.ScheduleEvent(EVENT_PILLAR_OF_FIRE, urand(12000, 17000));

				me->AI()->AttackStart(me->getVictim());
				break;

			default:
				break;
			}
			Phase = NextPhase;
		}

		void DamageDealt(Unit* target, uint32 &damage, DamageEffectType /*damagetype*/)
		{
			if (isFlameBreathing)
			{
				if (!me->HasInArc(M_PI / 6, target))
					damage = 0;
			}
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
				return;

			if (me->HealthBelowPct(81) && !firstSelection)
			{
				events.CancelEvent(EVENT_WHIRLWIND);
				events.CancelEvent(EVENT_GRIEVOUS_THROW);
				EnterPhase(RAND(PHASE_BEAR, PHASE_LYNX));
				firstSelection = true;
			}

			if (me->HealthBelowPct(41) && !secondSelection)
			{
				if (Phase == PHASE_BEAR)
				{
					events.CancelEvent(EVENT_SURGE);
					events.CancelEvent(EVENT_OVERPOWER);
					events.CancelEvent(EVENT_CREEPING_PARALYSIS);
				}
				else if (Phase == PHASE_LYNX)
				{
					events.CancelEvent(EVENT_CLAW_RAGE);
					events.CancelEvent(EVENT_LYNX_RUSH);
				}

				EnterPhase(RAND(PHASE_EAGLE, PHASE_DRAGONHAWK));
				secondSelection = true;
			}

			if (isFlameBreathing)
			{
				if (!me->IsNonMeleeSpellCasted(false))
					isFlameBreathing = false;
				else
					return;
			}

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
					//========= Achievement 'Ring Out'
				case EVENT_CHECK_PLAYERS:
				{
											Map::PlayerList const &plrList = instance->instance->GetPlayers();
											if (!plrList.isEmpty())
											{
												for (Map::PlayerList::const_iterator itr = plrList.begin(); itr != plrList.end(); ++itr)
												if (Player* pPlayer = itr->getSource())
												if (pPlayer->GetPositionX() < MIN_X ||
													pPlayer->GetPositionX() > MAX_X ||
													pPlayer->GetPositionY() < MIN_Y ||
													pPlayer->GetPositionY() > MAX_Y)
												{
													bAchieve = false;
													break;
												}
											}
											if (bAchieve)
												events.ScheduleEvent(EVENT_CHECK_PLAYERS, 5000);
											break;
				}
					//====== Troll Form
				case EVENT_WHIRLWIND:
					DoCast(me, SPELL_WHIRLWIND);
					events.ScheduleEvent(EVENT_WHIRLWIND, urand(15000, 20000));
					break;

				case EVENT_GRIEVOUS_THROW:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
						DoCast(target, SPELL_GRIEVOUS_THROW, false);
					events.ScheduleEvent(EVENT_GRIEVOUS_THROW, urand(10000, 11000));
					break;

					//====== Bear Form
				case EVENT_SURGE:
					if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 80.0f, true)) // Try to select farthest target.
						DoCast(target, SPELL_SURGE);
					events.ScheduleEvent(EVENT_SURGE, urand(15000, 20000));
					break;

				case EVENT_OVERPOWER:
					DoCastVictim(SPELL_OVERPOWER);
					events.ScheduleEvent(EVENT_OVERPOWER, urand(11000, 15000));
					break;

				case EVENT_CREEPING_PARALYSIS:
				{
												 Map::PlayerList const& players = me->GetMap()->GetPlayers();
												 for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
												 if (Player* player = itr->getSource())
													 DoCast(player, SPELL_CREEPING_PARALYSIS);

												 events.ScheduleEvent(EVENT_CREEPING_PARALYSIS, urand(19000, 21000));
				}
					break;

					//====== Lynx Form
				case EVENT_SUMMON_LYNX:
					DoCast(me, SPELL_SUMMON_LYNX);
					break;

				case EVENT_CLAW_RAGE:
					if (canCastClaw && clawRageTicks < 10)
					{
						if (!hasclawTarget)
						{
							if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
							{
								DoCast(target, SPELL_CLAW_RAGE_CHARGE, false);
								DoCast(target, SPELL_CLAW_RAGE_DAMAGE, false);
								clawTarget = target;
								hasclawTarget = true;
							}
						}
						else
						{
							DoCast(clawTarget, SPELL_CLAW_RAGE_DAMAGE, false);
						}

						clawRageTicks++;
						events.ScheduleEvent(EVENT_CLAW_RAGE, 500);
					}
					else
					{
						canCastClaw = false;
						clawRageTicks = 0;
						hasclawTarget = false;
						canCastRush = true;
						events.ScheduleEvent(EVENT_CLAW_RAGE, urand(15000, 20000));
					}
					break;

				case EVENT_LYNX_RUSH:
					if (canCastRush && lynxRushes < 4)
					{
						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
							DoCast(target, SPELL_LYNX_RUSH);

						lynxRushes++;
						events.ScheduleEvent(EVENT_LYNX_RUSH, 1000);
					}
					else
					{
						canCastRush = false;
						lynxRushes = 0;
						events.ScheduleEvent(EVENT_LYNX_RUSH, urand(15000, 20000));
						canCastClaw = true;
					}
					break;

					//====== Eagle Form
				case EVENT_LIGHTNING_TOTEM:
					DoCast(me, SPELL_SUMMON_LIGHT_TOTEM);
					events.ScheduleEvent(EVENT_LIGHTNING_TOTEM, urand(5000, 9000));
					break;

				case EVENT_SWEEPING_WINDS:
					DoCast(me, SPELL_SWEEPING_WINDS);
					events.ScheduleEvent(EVENT_TORNADO_MOVE, 1000);
					events.ScheduleEvent(EVENT_SWEEPING_WINDS, urand(19000, 21000));
					break;

				case EVENT_TORNADO_MOVE:
				{
										   std::list<Creature*> creatures;
										   GetCreatureListWithEntryInGrid(creatures, me, 24136, 1000.0f);

										   if (creatures.empty())
											   return;

										   for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
										   {
											   (*iter)->SetWalk(false);
											   (*iter)->SetSpeed(MOVE_RUN, 2.5f);
											   (*iter)->GetMotionMaster()->MoveRandom(15.0f);
											   (*iter)->SetFlag(UNIT_FIELD_FLAGS, MOVEMENTFLAG_DISABLE_GRAVITY);
										   }

										   events.ScheduleEvent(EVENT_TORNADO_MOVE, urand(11000, 12000));
				}
					break;

				case EVENT_TORNADO_STOP:
				{
										   std::list<Creature*> creatures;
										   GetCreatureListWithEntryInGrid(creatures, me, 24136, 1000.0f);

										   if (creatures.empty())
											   return;

										   for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
										   {
											   (*iter)->GetMotionMaster()->MovementExpired();
											   (*iter)->GetMotionMaster()->Clear();
											   (*iter)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
										   }
										   events.ScheduleEvent(EVENT_TORNADO_STOP, urand(8000, 9000));
				}
					break;

					//====== Dragonhawk Form
				case EVENT_FLAME_BREATH:
					Talk(YELL_FIRE_BREATH);
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
					{
						me->AttackStop();
						me->GetMotionMaster()->Clear();

						for (uint8 i = 0; i < 7; i++)
						{
							float x, y, z;
							me->GetClosePoint(x, y, z, me->GetObjectSize() / 3, 1.0f + (4 * i));
							me->CastSpell(x, y, z, SPELL_SUMMON_BREATH_LINE, true);
						}

						DoCast(target, SPELL_FLAME_BREATH);
						me->StopMoving();
						isFlameBreathing = true;
					}

					events.ScheduleEvent(EVENT_FLAME_BREATH, urand(10000, 15000));
					break;

				case EVENT_FLAME_WHIRL:
					DoCast(me, SPELL_FLAME_WHIRL);
					events.ScheduleEvent(EVENT_FLAME_WHIRL, urand(10000, 12000));
					break;

				case EVENT_PILLAR_OF_FIRE:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
						DoCast(target, SPELL_SUMMON_PILLAR);
					events.ScheduleEvent(EVENT_PILLAR_OF_FIRE, urand(12000, 18000));
					break;

				case EVENT_BERSERK:
					Talk(YELL_BERSERK);
					DoCast(me, SPELL_BERSERK);
					break;
				}
			}

			if (Phase != PHASE_EAGLE)
				DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_daakaraAI(creature);
	}
};

class npc_daakara_vortex : public CreatureScript
{
public:
	npc_daakara_vortex() : CreatureScript("npc_daakara_vortex") { }

	struct npc_daakara_vortexAI : public ScriptedAI
	{
		npc_daakara_vortexAI(Creature* creature) : ScriptedAI(creature) { }

		void Reset() {}

		void EnterCombat(Unit* /*target*/) {}

		void SpellHit(Unit* caster, const SpellInfo* spell)
		{
			if (spell->Id == SPELL_ZAP_INFORM)
				DoCast(caster, SPELL_ZAP_DAMAGE, true);
		}

		void UpdateAI(const uint32 /*diff*/)
		{
			// if the vortex reach the target, it change his target to another player (not used, they move on sweeping winds!).
			// if (me->IsWithinMeleeRange(me->getVictim()))
			//    AttackStart(SelectTarget(SELECT_TARGET_RANDOM, 0));
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_daakara_vortexAI(creature);
	}
};

class spell_summon_vortex : public SpellScriptLoader
{
public:
	spell_summon_vortex() : SpellScriptLoader("spell_summon_vortex") { }

	class spell_summon_vortex_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_summon_vortex_SpellScript);

		bool Validate(SpellInfo const* /*spellEntry*/)
		{
			if (!sSpellMgr->GetSpellInfo(SPELL_SWEEPING_WINDS))
				return false;
			return true;
		}

		void AfterCast(SpellEffIndex /*effIndex*/)
		{
			Unit* caster = GetCaster();
			caster->CastSpell(caster, 43121);
		}

		void Register()
		{
			OnEffectHitTarget += SpellEffectFn(spell_summon_vortex_SpellScript::AfterCast, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_summon_vortex_SpellScript();
	}
};

class npc_daakara_pillar_of_flame : public CreatureScript
{
public:

	npc_daakara_pillar_of_flame() : CreatureScript("npc_daakara_pillar_of_flame") {}

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_daakara_pillar_of_flameAI(pCreature);
	}

	struct npc_daakara_pillar_of_flameAI : public Scripted_NoMovementAI
	{
		npc_daakara_pillar_of_flameAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
		{
			me->SetReactState(REACT_PASSIVE);
			DoCast(me, SPELL_PILLAR_OF_FLAME_VISUAL, true);
			bExplode = false;
			explodeTimer = 2000;
		}

		bool bExplode;
		uint32 explodeTimer;

		void Reset()
		{
		}

		void UpdateAI(const uint32 diff)
		{
			if (explodeTimer <= diff && !bExplode)
			{
				bExplode = true;
				me->RemoveAllAuras();
				DoCast(me, SPELL_PILLAR_OF_FLAME_AURA, true);
			}
			else
				explodeTimer -= diff;
		}
	};
};


typedef boss_daakara::boss_daakaraAI DaakaraAI;

class achievement_ring_out : public AchievementCriteriaScript
{
public:
	achievement_ring_out() : AchievementCriteriaScript("achievement_ring_out") { }

	bool OnCheck(Player* source, Unit* target)
	{
		if (!target)
			return false;

		if (DaakaraAI* daakaraAI = CAST_AI(DaakaraAI, target->GetAI()))
			return daakaraAI->AllowAchieve();

		return false;
	}
};

void AddSC_boss_daakara()
{
	new boss_daakara();
	new npc_daakara_vortex();
	new spell_summon_vortex();
	new achievement_ring_out();
	new npc_daakara_pillar_of_flame();

}