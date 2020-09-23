#include "ScriptPCH.h"
#include "halls_of_origination.h"

enum Spells
{
    //Rajh
    SPELL_SUN_STRIKE                    = 73872, 
    SPELL_SUN_STRIKE_H                  = 89887,
    SPELL_SUN_STRIKE_DMG                = 73874,
    SPELL_SUN_STRIKE_DMG_H              = 90009,
    SPELL_SUMMON_SUN_ORB                = 80352,
    SPELL_BLESSING_OF_THE_SUN           = 76352,
    SPELL_BLESSING_OF_THE_SUN_AURA      = 76355,
    SPELL_BLESSING_OF_THE_SUN_AURA_H    = 89879,
    SPELL_ZERO_POWER                    = 72242,
	SPELL_SUMMON_SOLAR_WINDS            = 74104,
    SPELL_SOLAR_FIRE                    = 89131,
    SPELL_SOLAR_FIRE_DMG                = 89133,
    SPELL_SOLAR_FIRE_DMG_H              = 89878,
	SPELL_INFERNO_JUMP                  = 87653,
	SPELL_INFERNO_JUMP_EXPLOSION        = 87647,
	SPELL_INFERNO_JUMP_VISUAL           = 87645,
	SPELL_INFERNO_JUMP_TRIGGER          = 87650,

	//Sun Orb
	SPELL_SUN = 73658,
	SPELL_CHARGE = 82856,

	//Sun-Touched Speaker
	SPELL_STOMP = 75241,
	SPELL_FIRE_STORM = 73861,

	//Sun-Touched Servant
	SPELL_DISPERSE = 88097,
	SPELL_DISPERSE_FINAL = 88100,
	SPELL_FLAME_DISPERSION = 77160,
	SPELL_SEARING_FLAMES = 74101,
	SPELL_PYROGENICS = 76158,

	//Solar Wind
	SPELL_FIRE_VORTEX = 74109,
	SPELL_SOLAR_FIRE_AURA = 74107,
	SPELL_SUMMON_SOLAR_FIRE = 74104,
};

enum Texts
{
    SAY_DEATH    = 0,
    SAY_AGGRO    = 1,
    SAY_ENERGIZE = 2,
    SAY_KILL     = 3, 
};

Position const pointcenter = { -319.68f, 193.42f, 343.94f, 4.76f };
Position const SunPoint = { -317.685f, 192.550f, 379.702f, 0.0f };

enum Events
{
    EVENT_SUN_STRIKE           = 1,
    EVENT_SUMMON_SOLAR_WINDS   = 2,
	EVENT_INFERNO_JUMP         = 3,
	EVENT_SUMMON_SUN_ORB       = 4,

	//Suntouched Speaker
	EVENT_FIRE_STORM           = 5,
	EVENT_STOMP                = 6,

	// Fire Elementars
	EVENT_SUMMON_2             = 7,
	EVENT_KILL_2               = 8,
	EVENT_FLAME_WAVE           = 9,
	EVENT_SEARING_FLAME        = 10,

	// Sun Orb
	EVENT_MOVE_UP              = 11,
	EVENT_MOVE_DOWN            = 12,
	EVENT_DESPAWN              = 13,

	// Solar Wind
	EVENT_MOVE_ARROUND         = 14,
	EVENT_SUMMON_FIRE          = 15,

};

enum Points
{
	POINT_CENTER = 1,
	POINT_UP = 2,
	POINT_SUN_EXP = 3
};

enum Adds
{
    //NPC_SOLAR_WINDS1            = 39634,
    NPC_SOLAR_WINDS2            = 39635, // 74109
    NPC_SOLAR_WINDS3            = 47922,
	NPC_SUN_TOUCHED_SERVANT     = 39366, // 76159
	NPC_SUN_TOUCHED_SPEAKR      = 39373, // 76158,
    NPC_ORB_OF_SUN              = 40835, // 73658
    NPC_INFERNO_LEAP            = 47040,
    NPC_BLAZING_INFERNO         = 40927,
};

class boss_rajh : public CreatureScript
{
    public:
        boss_rajh() : CreatureScript("boss_rajh") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_rajhAI(pCreature);
        }

        struct boss_rajhAI : public BossAI
        {
            boss_rajhAI(Creature* pCreature) : BossAI(pCreature, DATA_RAJH)
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
            }

            uint8 phase;
            bool achieve;

            void InitializeAI()
            {
                if (!instance || static_cast<InstanceMap*>(me->GetMap())->GetScriptId() != sObjectMgr->GetScriptId(HOScriptName))
                    me->IsAIEnabled = false;
                else if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                _Reset();

                bool achieve = false;

                phase = 0;

                SetEquipmentSlots(false, 1728, 0, 0);

                DoCast(me, SPELL_ZERO_POWER, true);
                me->setPowerType(POWER_ENERGY);
                me->SetMaxPower(POWER_ENERGY, 100);
                me->SetPower(POWER_ENERGY, 100);
				DespawnFire(NPC_SOLAR_WINDS3);
            }

			void DespawnFire(uint32 entry)
			{
				std::list<Creature*> creatures;
				GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);
				if (creatures.empty())
					return;
				for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
					(*iter)->DespawnOrUnsummon();
			}

            void KilledUnit(Unit* /*Killed*/)
            {
                Talk(SAY_KILL);
            }

            void JustDied(Unit* /*Kill*/)
            {
                _JustDied();
                Talk(SAY_DEATH);
				DespawnFire(NPC_SOLAR_WINDS3);
				//50 Justices Points for players level 85
				Map* map = me->GetMap();
				if (!map)
					return;
				if (!map->IsDungeon())
					return;
				if (map->GetDifficulty() == DUNGEON_DIFFICULTY_HEROIC)
					instance->DoModifyPlayerCurrenciesIfLevel(395, 5000, 85);
            }

            bool HasAchieved()
            {
                return achieve;
            }

            void EnterCombat(Unit* /*Ent*/)
            {
                Talk(SAY_AGGRO);
                
                events.ScheduleEvent(EVENT_SUN_STRIKE, urand(5000, 10000));
			    events.ScheduleEvent(EVENT_SUMMON_SOLAR_WINDS, 5800);
				events.ScheduleEvent(EVENT_INFERNO_JUMP, 15000);
				events.ScheduleEvent(EVENT_SUMMON_SUN_ORB, 9800);

                achieve = true;
                DoZoneInCombat();
                instance->SetBossState(DATA_RAJH, IN_PROGRESS);
            }

            void JustReachedHome()
		    {
			    _JustReachedHome();
		    }

			void JustSummoned(Creature* summon)
			{
				BossAI::JustSummoned(summon);

				switch (summon->GetEntry())
				{
				case NPC_INFERNO_LEAP:
					summon->setFaction(16);
					summon->SetDisplayId(me->GetCreatureTemplate()->Modelid1);
					//summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
					summon->AI()->DoCastAOE(SPELL_INFERNO_JUMP_VISUAL);
					summon->CastWithDelay(7000, (Unit*)NULL, SPELL_INFERNO_JUMP_EXPLOSION);
					summon->DespawnOrUnsummon(7500);
					break;
				case NPC_SOLAR_WINDS3:
					me->SetDisplayId(me->GetCreatureTemplate()->Modelid1);
					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
					DoCastAOE(SPELL_SOLAR_FIRE);
					break;
				}
			}

            void MovementInform(uint32 type, uint32 id)
		    {
			    if (type == POINT_MOTION_TYPE)
			    {
				    switch (id)
				    {
					case POINT_CENTER:
                            Talk(SAY_ENERGIZE);
							me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                            DoCastAOE(SPELL_BLESSING_OF_THE_SUN);
					        break;
				    }
			    }
		    }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
				    return;

                if (me->GetPower(POWER_ENERGY) < 1 && phase == 0)
                {
                    phase = 1;
                    events.Reset();
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
					me->GetMotionMaster()->MovePoint(POINT_CENTER, pointcenter);
                    return;
                }
                else if (me->GetPower(POWER_ENERGY) > 99 && phase == 1)
                {
                    phase = 0;
                    achieve = false;
					me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    me->SetReactState(REACT_AGGRESSIVE);
                    events.ScheduleEvent(EVENT_SUN_STRIKE, 20000);
					events.ScheduleEvent(EVENT_SUMMON_SOLAR_WINDS, 5800);
					events.ScheduleEvent(EVENT_INFERNO_JUMP, 15000);
					events.ScheduleEvent(EVENT_SUMMON_SUN_ORB, 9800);
                    me->GetMotionMaster()->MoveChase(me->getVictim());
                    return;
                }

			    while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SUN_STRIKE:
                            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                DoCast(pTarget, SPELL_SUN_STRIKE);
                            events.ScheduleEvent(EVENT_SUN_STRIKE, urand(15000, 20000));
                            break;
                        case EVENT_SUMMON_SOLAR_WINDS:
							if (me->SummonCreature(NPC_SOLAR_WINDS2, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()))
                            events.ScheduleEvent(EVENT_SUMMON_SOLAR_WINDS, urand(21000, 25000));
                            break;
						case EVENT_INFERNO_JUMP:
							DoCastRandom(SPELL_INFERNO_JUMP_TRIGGER, 100.0f);
							DoCastAOE(SPELL_INFERNO_JUMP);
							events.ScheduleEvent(EVENT_INFERNO_JUMP, 35000);
							break;
						case EVENT_SUMMON_SUN_ORB:
							DoCast(SPELL_SUMMON_SUN_ORB);
							events.ScheduleEvent(EVENT_SUMMON_SUN_ORB, 25000);
							break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

typedef boss_rajh::boss_rajhAI RajhAI;

class achievement_sun_of_a : public AchievementCriteriaScript
{
    public:
        achievement_sun_of_a() : AchievementCriteriaScript("achievement_sun_of_a") { }

        bool OnCheck(Player* source, Unit* target)
        {
            if (!target)
                return false;
            if (RajhAI* rajhAI = CAST_AI(RajhAI, target->GetAI()))
                return rajhAI->HasAchieved();

            return false;
        }
};

class npc_suntouched_speaker : public CreatureScript
{
public:
	npc_suntouched_speaker() : CreatureScript("npc_suntouched_speaker") { }

	struct npc_suntouched_speakerAI : public ScriptedAI
	{
		npc_suntouched_speakerAI(Creature* creature) : ScriptedAI(creature) { }

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_FIRE_STORM, 10000);
			events.ScheduleEvent(EVENT_STOMP, 6000);
		}

		void Reset()
		{
			events.Reset();
		}

		void UpdateAI(uint32 const diff)
		{
			events.Update(diff);

			if (!UpdateVictim())
				return;

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_FIRE_STORM:
					DoCastVictim(SPELL_FIRE_STORM);
					events.ScheduleEvent(SPELL_FIRE_STORM, 15000);
					break;
				case EVENT_STOMP:
					DoCastVictim(SPELL_STOMP);
					events.ScheduleEvent(EVENT_STOMP, 9000);
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
	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_suntouched_speakerAI(creature);
	}
};

class npc_elementar_1 : public CreatureScript
{
public:
	npc_elementar_1() : CreatureScript("npc_elementar_1") { }

	struct npc_elementar_1AI : public ScriptedAI
	{
		npc_elementar_1AI(Creature* creature) : ScriptedAI(creature) { }

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_FLAME_WAVE, 9000);
			events.ScheduleEvent(EVENT_SEARING_FLAME, 6000);
		}

		void Reset()
		{
			events.Reset();
		}

		void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/)
		{
			if (!me->IsNonMeleeSpellCasted(false) && HealthBelowPct(3))
			{
				DoCast(SPELL_DISPERSE);
				me->DespawnOrUnsummon(3100);
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				me->RemoveAllAuras();
			}
		}

		void UpdateAI(uint32 const diff)
		{
			events.Update(diff);

			if (!UpdateVictim())
				return;

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_FLAME_WAVE:
						DoCastAOE(SPELL_FLAME_DISPERSION);
						events.ScheduleEvent(EVENT_FLAME_WAVE, 9000);
					break;
				case EVENT_SEARING_FLAME:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
						DoCast(target, SPELL_SEARING_FLAMES);
						events.ScheduleEvent(EVENT_SEARING_FLAME, 6000);
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

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_elementar_1AI(creature);
	}
};

class npc_elementar_2 : public CreatureScript
{
public:
	npc_elementar_2() : CreatureScript("npc_elementar_2") { }

	struct npc_elementar_2AI : public ScriptedAI
	{
		npc_elementar_2AI(Creature* creature) : ScriptedAI(creature) { }

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_FLAME_WAVE, 9000);
			events.ScheduleEvent(EVENT_SEARING_FLAME, 6000);
			DoCastAOE(SPELL_PYROGENICS);
		}

		void Reset()
		{
			events.Reset();
		}

		void DamageTaken(Unit* /*attacker*/, uint32& /*damage*/)
		{
			if (!me->IsNonMeleeSpellCasted(false) && HealthBelowPct(3))
			{
				DoCast(SPELL_DISPERSE_FINAL);
				me->DespawnOrUnsummon(3100);
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				me->RemoveAllAuras();
			}
		}
		void UpdateAI(uint32 const diff)
		{
			events.Update(diff);

			if (!UpdateVictim())
				return;

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_FLAME_WAVE:
						DoCastAOE(SPELL_FLAME_DISPERSION);
						events.ScheduleEvent(EVENT_FLAME_WAVE, 9000);
					break;
				case EVENT_SEARING_FLAME:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
						DoCast(target, SPELL_SEARING_FLAMES);
						events.ScheduleEvent(EVENT_SEARING_FLAME, 6000);
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

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_elementar_2AI(creature);
	}
};

class npc_sunball : public CreatureScript
{
public:
	npc_sunball() : CreatureScript("npc_sunball") {}

	struct npc_sunballAI : public ScriptedAI
	{
		npc_sunballAI(Creature* creature) : ScriptedAI(creature) { }

		void IsSummonedBy(Unit* /*summoner*/)
		{
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
			DoCast(me, SPELL_SUN);
			me->SetCanFly(true);
			me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
			me->setFaction(16);
			events.ScheduleEvent(EVENT_MOVE_UP, 100);
			me->SetReactState(REACT_PASSIVE);
		}

		void MovementInform(uint32 type, uint32 pointId)
		{
			switch (pointId)
			{
			case POINT_UP:
				events.ScheduleEvent(EVENT_MOVE_DOWN, 7000);
				break;
			case POINT_SUN_EXP:
				events.ScheduleEvent(EVENT_DESPAWN, 12000);
				break;
			default:
				break;
			}
		}

		void UpdateAI(uint32 const diff)
		{
			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_MOVE_UP:
				{
									  float posX = me->GetPositionX();
									  float posY = me->GetPositionY();
									  me->GetMotionMaster()->MovePoint(POINT_UP, posX, posY, 369.702f);
				}
					break;
				case EVENT_MOVE_DOWN:
				{
										float posX = me->GetPositionX();
										float posY = me->GetPositionY();
										me->GetMotionMaster()->MovePoint(POINT_SUN_EXP, posX, posY, 343.94f);					
				}
					break;
				case EVENT_DESPAWN:
					DoCastAOE(SPELL_CHARGE);
					me->DespawnOrUnsummon(1000);
					break;
				default:
					break;
				}
			}
		}
	private:
		EventMap events;
	};
	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_sunballAI(creature);
	}
};

class npc_solar_wind_vortex : public CreatureScript
{
public:
	npc_solar_wind_vortex() : CreatureScript("npc_solar_wind_vortex") {}

	struct npc_solar_wind_vortexAI : public ScriptedAI
	{
		npc_solar_wind_vortexAI(Creature* creature) : ScriptedAI(creature)
		{
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
			me->SetReactState(REACT_PASSIVE);
		}

		void IsSummonedBy(Unit* /*summoner*/)
		{
			me->SetDisplayId(me->GetCreatureTemplate()->Modelid1);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_NPC);
			me->SetReactState(REACT_PASSIVE);
			DoCastAOE(SPELL_FIRE_VORTEX);
			DoCast(me, SPELL_SOLAR_FIRE_AURA, true);
			events.ScheduleEvent(EVENT_MOVE_ARROUND, 100);
			events.ScheduleEvent(EVENT_SUMMON_FIRE, 3000);
			me->SetSpeed(MOVE_RUN, 0.5f, false);
			me->GetMotionMaster()->MoveRandom(50.0f);
		}

		void UpdateAI(const uint32 diff)
		{
			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_MOVE_ARROUND:
					me->GetMotionMaster()->MoveRandom(50.0f);
					events.ScheduleEvent(EVENT_MOVE_ARROUND, 10000);
					break;
				case EVENT_SUMMON_FIRE:
					DoCastAOE(SPELL_SUMMON_SOLAR_FIRE);
					events.ScheduleEvent(EVENT_SUMMON_FIRE, 3000);
					break;
				default:
					break;
				}
			}
		}
	private:
		EventMap events;
	};
	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_solar_wind_vortexAI(creature);
	}
};

void AddSC_boss_rajh()
{
    new boss_rajh();
    new achievement_sun_of_a();
	new npc_suntouched_speaker;
	new npc_elementar_1;
	new npc_elementar_2;
	new npc_sunball;
	new npc_solar_wind_vortex;
}
