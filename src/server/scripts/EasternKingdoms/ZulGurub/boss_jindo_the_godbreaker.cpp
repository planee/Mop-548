#include "ScriptPCH.h"
#include "zulgurub.h"

enum JindoScriptTexts
{
    SAY_AGGRO                   = 0,
    SAY_DEATH                   = 1,
    SAY_KILL_1                  = 2,
    SAY_KILL_2                  = 3,
    SAY_PHASE_2                 = 5,
    SAY_SPAWN                   = 6,
    SOUND_HAKKAR_BREAK_CHAINS   = 24245,
};

enum eTexts
{
	JINDO_YELL_START = 0,
	JINDO_EMOTE_SHADOWS_OF_HAKKAR = 1,
	JINDO_YELL_SPIRIT_REALM = 2,
	JINDO_KILL_PLAYER = 3,
	JINDO_SPIRIT_YELL_KILL_PLAYER = 0,
	JINDO_SPIRIT_YELL_DIED = 1,
	HAKKAR_YELL_SPIT = 0,
	HAKKAR_YELL_OVERSTEPPED = 1,
	HAKKAR_SPIRIT_YELL_INSECTS = 0,
};

enum HakkarScriptTexts
{
    SAY_PHASE   = 2,
    SAY_END_2   = 0,
    SAY_END_1   = 1,
};

enum Spells
{
    SPELL_DRAIN_SPIRIT_ESSENCE  = 97321,
    SPELL_DEADZONE              = 97170,
    SPELL_SHADOWS_OF_HAKKAR     = 97172,
    SPELL_SHADOW_SPIKE_TARGET   = 97158,
    SPELL_SHADOW_SPIKE          = 97160,
	SPELL_SHADOW_SPIKE_L        = 97208,
    SPELL_HAKKAR_CHAINS         = 97022,
    SPELL_HAKKAR_CHAINS_VISUAL  = 97091,
    SPELL_SPIRIT_WORLD          = 98861,
    SPELL_SPIRIT_WORLD_AURA     = 96689,
    SPELL_SPIRIT_FORM           = 96568,
    SPELL_SPIRIT_FORM_CHAIN     = 96642,
    SPELL_SUMMON_SPIRIT_TARGET  = 97152,
    SPELL_SUMMON_SPIRIT         = 97123,
    SPELL_BODY_SLAM             = 97198,
    SPELL_SPIRIT_WARRIOR_GAZE   = 97597,
    SPELL_FRENZY                = 97088,
    SPELL_SUNDER_RIFT           = 96970,
    SPELL_SUNDER_RIFT_AURA      = 97320,
    SPELL_BRITTLE_BARRIER       = 97417,
	SPELL_ADD_PLAYERS_THREAD    = 100401,
	SPELL_VANISH                = 97002,
	SPELL_TRANSFORM             = 96716,
	SPELL_HAKKAR_BREAKS_FREE    = 97209,
};

enum Events
{
    EVENT_DEADZONE          = 1,
    EVENT_SHADOWS_OF_HAKKAR = 2,
    EVENT_SUMMON_SPIRIT     = 3,
    EVENT_BODY_SLAM         = 4,
    EVENT_SHADOW_SPIKE      = 5,
    EVENT_FRENZY            = 6,
    EVENT_SUMMON_GURUBASHI  = 7,
	EVENT_DRAIN_SPIRIT_ESSENCE_COSMETIC_INTRO = 8,
	EVENT_SET_FACING        = 9,
	EVENT_SPIRIT_WORLD      = 10,
	EVENT_SPIRIT_WORLD_SUMMON = 11,
	EVENT_HAKKAR_SET_FACING = 12,
	EVENT_HAKKAR_KILL_JINDO = 13,
	EVENT_HAKKAR_YELL_BYE = 14,
	EVENT_JINDO_KILL_SELF = 15,

};

enum Adds
{
    NPC_TWISTED_SPIRIT      = 52624,
    NPC_SPIRIT_PORTAL       = 52532,
    NPC_HAKKAR_CHAINS       = 52430,
    NPC_SUNDERED_RIFT       = 52400,
    NPC_BROKEN_GROUND       = 52407,
    NPC_JINDO_THE_BROKEN    = 52154,
    NPC_SPIRIT_OF_HAKKAR    = 52222,
    NPC_GURUBASHI_SPIRIT    = 52730,
};

enum Points
{
    POINT_JINDO = 1,
};

enum eDefault
{
	POINT_SPIRIT_WORLD = 1,

	ACTION_HAKKAR_FREE = 1,
	ACTION_DESPAWN = 2,
	ACTION_CHAIN_DIED = 3,

	TYPE_SPAWN_POSITION_ID = 1,
	TYPE_KILLED_TROLL_ID = 1,
};

const Position HakkarChainSP[2][3] =
{
	{
		{ -11814.56f, -1652.120f, 52.96632f, 0.0f },
		{ -11778.60f, -1659.418f, 53.06332f, 0.0f },
		{ -11801.36f, -1678.391f, 53.04712f, 0.0f },
	},
	{
		{ -11761.55f, -1649.866f, 52.96572f, 0.0f },
		{ -11772.65f, -1676.898f, 53.04771f, 0.0f },
		{ -11796.30f, -1659.990f, 53.09364f, 0.0f },
	}
};

const Position hakkarPos = {-11786.5f, -1690.92f, 53.0195f, 1.6057f};
const Position jindoPos = {-11787.84f, -1698.48f, 52.9600f, 1.539f};

const Position enterPos = {-11917.0f, -1230.14f, 92.29f, 4.78f};

const Position SpiritPortalSP[15] =
{
	{ -11811.90f, -1637.995f, 52.99569f, 0.0f },
	{ -11793.88f, -1646.389f, 54.62890f, 0.0f },
	{ -11782.06f, -1646.380f, 54.56368f, 0.0f },
	{ -11769.54f, -1663.590f, 53.06438f, 0.0f },
	{ -11788.62f, -1628.262f, 54.86021f, 0.0f },
	{ -11751.88f, -1662.833f, 53.08055f, 0.0f },
	{ -11764.74f, -1636.479f, 52.98969f, 0.0f },
	{ -11752.42f, -1645.153f, 52.87562f, 0.0f },
	{ -11756.94f, -1680.793f, 53.07720f, 0.0f },
	{ -11749.95f, -1631.240f, 52.89489f, 0.0f },
	{ -11823.27f, -1665.200f, 53.08056f, 0.0f },
	{ -11823.57f, -1647.462f, 52.87725f, 0.0f },
	{ -11816.96f, -1682.873f, 53.07767f, 0.0f },
	{ -11805.72f, -1664.719f, 53.06411f, 0.0f },
	{ -11827.62f, -1634.120f, 52.93477f, 0.0f },
};

const Position SpiritWarriorSP[4] =
{
	{ -11837.85f, -1698.944f, 40.88818f, 0.0f },
	{ -11735.52f, -1695.576f, 40.88869f, 0.0f },
	{ -11737.58f, -1592.231f, 40.88970f, 0.0f },
	{ -11842.00f, -1595.804f, 40.88970f, 0.0f },
};

class boss_jindo_the_godbreaker : public CreatureScript
{
    public:
        boss_jindo_the_godbreaker() : CreatureScript("boss_jindo_the_godbreaker") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_jindo_the_godbreakerAI(pCreature);
        }

        struct boss_jindo_the_godbreakerAI : public BossAI
        {
            boss_jindo_the_godbreakerAI(Creature* pCreature) : BossAI(pCreature, DATA_JINDO)
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
                me->setActive(true);
            }

            bool bTwoPhase;
            uint8 chains;
			uint8 SpiritTrollSpawMask;
			uint64 HakkarGUID;
			uint64 JindoSpiritGUID;
			uint64 HakkarSpiritGUID;

			void InitializeAI()
			{
				/*for (int i = 0; i < 4; ++i)
				if (Creature* warrior = me->SummonCreature(52167, SpiritWarriorSP[i]))
					warrior->AI()->SetData(TYPE_SPAWN_POSITION_ID, i);*/

				if (me->isAlive())
					me->SummonCreature(52650, hakkarPos);

				SpiritTrollSpawMask = 0;
				Reset();
			}

            void Reset()
            {
				EntryCheckPredicate pred(52430);
				summons.DoAction(ACTION_DESPAWN, pred);
                _Reset();
                bTwoPhase = false;
				HakkarGUID = 0;
				JindoSpiritGUID = 0;
				HakkarSpiritGUID = 0;
                chains = 0;
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
				events.ScheduleEvent(EVENT_DRAIN_SPIRIT_ESSENCE_COSMETIC_INTRO, urand(5000, 15000));
				//me->LowerPlayerDamageReq(me->GetHealth());
				instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            }

			void SetData(uint32 type, uint32 data)
			{
				if (type == TYPE_KILLED_TROLL_ID)
					SpiritTrollSpawMask |= 1 << data;
			}

            void EnterCombat(Unit* /*who*/)
            {
                if (instance->GetData(DATA_BOSSES) < 2)
                {
                    EnterEvadeMode();
                    instance->DoNearTeleportPlayers(enterPos);
                    return;
                }

                Talk(SAY_AGGRO);
                bTwoPhase = false;
                chains = 0;
                events.ScheduleEvent(EVENT_DEADZONE, 12000);
                events.ScheduleEvent(EVENT_SHADOWS_OF_HAKKAR, 19000);
                instance->SetBossState(DATA_JINDO, IN_PROGRESS);
            }

            void JustDied(Unit* /*killer*/)
            {
				EntryCheckPredicate pred(52430);
				summons.DoAction(ACTION_DESPAWN, pred);
				instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                _JustDied();
				if (instance)
				{
					Map* map = me->GetMap();
					if (!map)
						return;

					if (!map->IsDungeon())
						return;

					//50 Justices Points for players level 85
					instance->DoModifyPlayerCurrenciesIfLevel(395, 5000, 85);
				}
            }

			void JustSummoned(Creature* summoned)
			{
				switch (summoned->GetEntry())
				{
				case 52167:
					summoned->SetPhaseMask(1, true);
					return;
				case NPC_SHADOW_OF_HAKKAR:
					HakkarSpiritGUID = summoned->GetGUID();
					summoned->SetPhaseMask(1, true);
					return;
				case NPC_GURUBASHI_SPIRIT:
				case 52732:
					summoned->SetPhaseMask(2, true);
					summons.Summon(summoned);
					return;
				case NPC_SPIRIT_OF_HAKKAR:
					HakkarGUID = summoned->GetGUID();
					summoned->SetReactState(REACT_PASSIVE);
					summoned->SetPhaseMask(2, true);
					break;
				case NPC_JINDO_TRIGGER:
					JindoSpiritGUID = summoned->GetGUID();
					summoned->SetPhaseMask(2, true);
					break;
				case NPC_HAKKAR_CHAINS:
					summoned->SetPhaseMask(2, true);
					summoned->CastSpell((Unit*)NULL, SPELL_HAKKAR_CHAINS, false);
					break;
				}

				summons.Summon(summoned);

				if (me->isInCombat())
					summoned->SetInCombatWithZone();
			}

			void DoAction(int32 const action)
			{
				if (action == ACTION_CHAIN_DIED)
				{
					++chains;

					if (chains == 3)
					{
						summons.DespawnEntry(52624);
						summons.DespawnEntry(52532);

						if (Creature* jindo = ObjectAccessor::GetCreature(*me, JindoSpiritGUID))
							jindo->AI()->DoAction(ACTION_HAKKAR_FREE);

						if (Creature* hakkar = ObjectAccessor::GetCreature(*me, HakkarGUID))
						{
							hakkar->AI()->Talk(HAKKAR_YELL_OVERSTEPPED);
							hakkar->CastSpell(hakkar, SPELL_HAKKAR_BREAKS_FREE, false);
							events.ScheduleEvent(EVENT_HAKKAR_SET_FACING, 1000);
						}
					}
				}
			}

			//void DamageTaken(Unit* /*done_by*/, uint32 & /*damage*/)
			/*{
				if (!bTwoPhase && me->GetHealthPct() <= 70)
				{
					bTwoPhase = true;
					Talk(SAY_PHASE_2);
					me->SetReactState(REACT_PASSIVE);
					me->AttackStop();
					me->CastStop();
					me->GetMotionMaster()->MovePoint(0, -11787.0f, -1695.73f, 52.98806f);
					events.Reset();
					events.ScheduleEvent(EVENT_SET_FACING, 5000);
				}
			}*/
            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
				{
					if (events.ExecuteEvent() == EVENT_DRAIN_SPIRIT_ESSENCE_COSMETIC_INTRO)
					{
						me->CastSpell(me, SPELL_DRAIN_SPIRIT_ESSENCE, false);
						events.ScheduleEvent(EVENT_DRAIN_SPIRIT_ESSENCE_COSMETIC_INTRO, urand(10000, 20000));
					}

					return;
				}

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_DEADZONE:
                            DoCast(me, SPELL_DEADZONE);
                            events.ScheduleEvent(EVENT_DEADZONE, 19000);
							events.ScheduleEvent(EVENT_SHADOWS_OF_HAKKAR, urand(5000, 10000));
                            break;
                        case EVENT_SHADOWS_OF_HAKKAR:
							me->CastSpell(me, SPELL_SHADOWS_OF_HAKKAR, false);
                            //events.ScheduleEvent(EVENT_SHADOWS_OF_HAKKAR, 18000);
                            break;
						case EVENT_SET_FACING:
							me->SetFacingTo(1.570796f);
							events.ScheduleEvent(EVENT_SPIRIT_WORLD, 500);
							break;
						case EVENT_SPIRIT_WORLD:
							me->CastSpell(me, SPELL_ADD_PLAYERS_THREAD, false);
							me->CastSpell(me, SPELL_SPIRIT_WORLD, false);
							me->CastSpell(me, SPELL_VANISH, false);
							events.ScheduleEvent(EVENT_SPIRIT_WORLD_SUMMON, 3000);
							instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
							break;
						case EVENT_SPIRIT_WORLD_SUMMON:
						{
														  me->SummonCreature(52150, jindoPos);
														  uint8 id = urand(0, 1);

														  for (int i = 0; i < 3; ++i)
															  me->SummonCreature(52430, HakkarChainSP[id][i]);

														  for (int i = 0; i < 15; ++i)
															  me->SummonCreature(52532, SpiritPortalSP[i]);

														  for (int i = 0; i < 4; ++i)
															  me->SummonCreature(SpiritTrollSpawMask & 1 << i ? 52730 : 52732, SpiritWarriorSP[i]);

														  if (Creature* hakkar = me->SummonCreature(52222, hakkarPos))
															  hakkar->AI()->Talk(SAY_PHASE);
						}
							break;

						case EVENT_HAKKAR_SET_FACING:
						{
														if (Creature* hakkar = ObjectAccessor::GetCreature(*me, HakkarGUID))
															hakkar->SetFacingTo(4.712389f);

														events.ScheduleEvent(EVENT_HAKKAR_KILL_JINDO, 17000);
						}
							break;
						case EVENT_HAKKAR_KILL_JINDO:
						{
														if (Creature* hakkar = ObjectAccessor::GetCreature(*me, HakkarGUID))
															hakkar->HandleEmoteCommand(EMOTE_ONESHOT_ATTACK1H);

														me->RemoveAura(SPELL_SPIRIT_WORLD);
														events.ScheduleEvent(EVENT_HAKKAR_YELL_BYE, 2500);
						}
							break;
						case EVENT_HAKKAR_YELL_BYE:
						{
													  if (Creature* hakkar = ObjectAccessor::GetCreature(*me, HakkarSpiritGUID))
													  {
														  hakkar->AI()->Talk(SAY_END_1);
														  hakkar->DespawnOrUnsummon(5000);
													  }

													  events.ScheduleEvent(EVENT_JINDO_KILL_SELF, 5000);
						}
							break;
						case EVENT_JINDO_KILL_SELF:
						{
													  me->RemoveAllAuras();
													  me->CastSpell(me, SPELL_TRANSFORM, false);

													  if (!me->getThreatManager().getThreatList().empty())
													  if (Unit* killer = ObjectAccessor::GetUnit(*me, (*me->getThreatManager().getThreatList().begin())->getUnitGuid()))
														  killer->DealDamage(me, me->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
						}
							break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_jindo_gurubashi_spirit : public CreatureScript
{
    public:

        npc_jindo_gurubashi_spirit() : CreatureScript("npc_jindo_gurubashi_spirit") {}

    private:
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_jindo_gurubashi_spiritAI(pCreature);
        }

        struct npc_jindo_gurubashi_spiritAI : public ScriptedAI
        {
            npc_jindo_gurubashi_spiritAI(Creature* pCreature) : ScriptedAI(pCreature) 
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
            }

            EventMap events;
			void InitializeAI()
			{
				JustReachedHome();
			}

			void JustReachedHome()
			{
				me->GetMotionMaster()->MoveRandom(3.0f);
			}
            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* who)
            {
                events.ScheduleEvent(EVENT_BODY_SLAM, 12000);
                events.ScheduleEvent(EVENT_FRENZY, 7000);
                DoZoneInCombat(me, 100.0f);
            }

            void JustSummoned(Creature* summon)
            {
                if (Creature* pJindo = me->FindNearestCreature(NPC_JINDO, 100.0f))
                    static_cast<boss_jindo_the_godbreaker::boss_jindo_the_godbreakerAI*>(pJindo->GetAI())->JustSummoned(summon);
            }

            void MovementInform(uint32 type, uint32 id)
            {
                if (id == EVENT_JUMP)
                    if (Creature* pChain = me->FindNearestCreature(NPC_HAKKAR_CHAINS, 5.0f))
                        pChain->RemoveAurasDueToSpell(SPELL_BRITTLE_BARRIER);
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
                    switch (eventId)
                    {
                        case EVENT_FRENZY:
                            DoCast(me, SPELL_FRENZY);
                            events.ScheduleEvent(EVENT_FRENZY, 10000);
                            break;
                        case EVENT_BODY_SLAM:
                            DoCast(me, SPELL_SPIRIT_WARRIOR_GAZE);
                            events.ScheduleEvent(EVENT_BODY_SLAM, 25000);
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_jindo_spirit_of_hakkar : public CreatureScript
{
    public:

        npc_jindo_spirit_of_hakkar() : CreatureScript("npc_jindo_spirit_of_hakkar") {}
        
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_jindo_spirit_of_hakkarAI(pCreature);
        }

        struct npc_jindo_spirit_of_hakkarAI : public Scripted_NoMovementAI
        {
            npc_jindo_spirit_of_hakkarAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature) 
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
                me->SetReactState(REACT_PASSIVE);
            }

            void DamageTaken(Unit* attacker, uint32 &damage)
            {
                damage = 0;
            }
        };
};

class npc_jindo_chains_of_hakkar : public CreatureScript
{
    public:

        npc_jindo_chains_of_hakkar() : CreatureScript("npc_jindo_chains_of_hakkar") {}
        
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_jindo_chains_of_hakkarAI(pCreature);
        }

        struct npc_jindo_chains_of_hakkarAI : public Scripted_NoMovementAI
        {
            npc_jindo_chains_of_hakkarAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature) 
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
                me->SetReactState(REACT_PASSIVE);
            }

            void EnterCombat(Unit* who)
            {
                DoZoneInCombat(me, 300.0f);
            }

			InstanceScript* instance;

			void InitializeAI()
			{
				ASSERT(instance);
				me->SetReactState(REACT_PASSIVE);
				me->AddAura(SPELL_HAKKAR_CHAINS_VISUAL, me);
				me->AddAura(SPELL_BRITTLE_BARRIER, me);
			}

			void DoAction(int32 const action)
			{
				if (action == ACTION_DESPAWN)
					instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
			}

			void JustDied(Unit* /*killer*/)
			{
				if (Creature* jindo = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_JINDO)))
					jindo->AI()->DoAction(ACTION_CHAIN_DIED);

				instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
			}
		};
};


class npc_jindo_spirit_portal : public CreatureScript
{
    public:

        npc_jindo_spirit_portal() : CreatureScript("npc_jindo_spirit_portal") {}
        
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_jindo_spirit_portalAI(pCreature);
        }

        struct npc_jindo_spirit_portalAI : public Scripted_NoMovementAI
        {
            npc_jindo_spirit_portalAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature) 
            {
            }

            void JustSummoned(Creature* summon)
            {
                if (Creature* pJindo = me->FindNearestCreature(NPC_JINDO, 300.0f))
                    static_cast<boss_jindo_the_godbreaker::boss_jindo_the_godbreakerAI*>(pJindo->GetAI())->JustSummoned(summon);
            }
        };
};

class spell_jindo_shadow_spike_target : public SpellScriptLoader
{
    public:
        spell_jindo_shadow_spike_target() : SpellScriptLoader("spell_jindo_shadow_spike_target") { }


        class spell_jindo_shadow_spike_target_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_jindo_shadow_spike_target_SpellScript);

            void HandleDummy(SpellEffIndex effIndex)
            {
                if (!GetCaster() || !GetHitUnit())
                    return;

                GetCaster()->CastSpell(GetHitUnit(), SPELL_SHADOW_SPIKE, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_jindo_shadow_spike_target_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_jindo_shadow_spike_target_SpellScript();
        }
};

class SpiritPortalCheck
{
    public:
        SpiritPortalCheck(uint32 entry) {i_entry = entry;}
        bool operator()(WorldObject* obj) const
        {
            if (!obj->ToCreature())
                return true;
            return ((obj->ToCreature()->HasUnitState(UNIT_STATE_CASTING)) || (obj->ToCreature()->GetEntry() != i_entry) || !obj->ToCreature()->isAlive());
        }
        uint32 i_entry;
};

class spell_jindo_summon_spirit_target : public SpellScriptLoader
{
    public:
        spell_jindo_summon_spirit_target() : SpellScriptLoader("spell_jindo_summon_spirit_target") { }


        class spell_jindo_summon_spirit_target_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_jindo_summon_spirit_target_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            { 
                targets.remove_if(SpiritPortalCheck(NPC_SPIRIT_PORTAL));
                if (targets.size() > 1)
                    WoWSource::RandomResizeList(targets, 1);
            }

            void HandleDummy(SpellEffIndex effIndex)
            {
                if (!GetCaster() || !GetHitUnit())
                    return;

                GetHitUnit()->CastSpell(GetHitUnit(), SPELL_SUMMON_SPIRIT);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_jindo_summon_spirit_target_SpellScript::FilterTargets, EFFECT_0,TARGET_UNIT_SRC_AREA_ENTRY);
                OnEffectHitTarget += SpellEffectFn(spell_jindo_summon_spirit_target_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_jindo_summon_spirit_target_SpellScript();
        }
};

class spell_jindo_spirit_warrior_gaze_target : public SpellScriptLoader
{
    public:
        spell_jindo_spirit_warrior_gaze_target() : SpellScriptLoader("spell_jindo_spirit_warrior_gaze_target") { }

        class spell_jindo_spirit_warrior_gaze_target_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_jindo_spirit_warrior_gaze_target_SpellScript);

            void HandleApplyAura(SpellEffIndex effIndex)
            {
                if (!GetCaster() || !GetHitUnit())
                    return;

                GetCaster()->CastSpell(GetHitUnit(), SPELL_BODY_SLAM);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_jindo_spirit_warrior_gaze_target_SpellScript::HandleApplyAura, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_jindo_spirit_warrior_gaze_target_SpellScript();
        }
};

class boss_jindo_the_godbreaker_spirit_world : public CreatureScript
{
public:
	boss_jindo_the_godbreaker_spirit_world() : CreatureScript("boss_jindo_the_godbreaker_spirit_world") { }

private:
	CreatureAI* GetAI(Creature* creature) const
	{
		return new boss_jindo_the_godbreaker_spirit_worldAI(creature);
	}

	struct boss_jindo_the_godbreaker_spirit_worldAI : public ScriptedAI
	{
		boss_jindo_the_godbreaker_spirit_worldAI(Creature* creature) : ScriptedAI(creature) { }

		EventMap events;
		bool RightArm;

		void InitializeAI()
		{
			RightArm = true;
			me->SetReactState(REACT_PASSIVE);
		}

		void KilledUnit(Unit* victim)
		{
			if (victim->GetTypeId() == TYPEID_PLAYER)
				Talk(SAY_KILL_1);
		}

		void DoAction(int32 const action)
		{
			if (action == ACTION_HAKKAR_FREE)
			{
				Talk(SAY_DEATH);
				events.Reset();
			}
		}

		void SpellHitTarget(Unit* target, const SpellInfo* spell)
		{
			switch (spell->Id)
			{
			case SPELL_SHADOW_SPIKE:
				me->CastSpell(target, RightArm ? SPELL_SHADOW_SPIKE : SPELL_SHADOW_SPIKE_L, true);
				RightArm = !RightArm;
				break;
			case SPELL_SUMMON_SPIRIT_TARGET:
				target->CastSpell(target, SPELL_SUMMON_SPIRIT, false, NULL, NULL, me->ToTempSummon()->GetSummonerGUID());
				break;
			}
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_SHADOW_SPIKE, 1000);
			events.ScheduleEvent(EVENT_SUMMON_SPIRIT, 1000);
		}

		void UpdateAI(uint32 const diff)
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);

			if (events.ExecuteEvent() == EVENT_SHADOW_SPIKE)
			{
				me->CastSpell((Unit*)NULL, SPELL_SHADOW_SPIKE, false);
				events.ScheduleEvent(EVENT_SHADOW_SPIKE, 3100);
			}

			if (events.ExecuteEvent() == EVENT_SUMMON_SPIRIT)
			{
				me->CastSpell((Unit*)NULL, SPELL_SUMMON_SPIRIT_TARGET, false);
				events.ScheduleEvent(EVENT_SUMMON_SPIRIT, 3100);
			}

			DoMeleeAttackIfReady();
		}
	};
};

class spell_sunder_rift_visual : public SpellScriptLoader
{
public:
	spell_sunder_rift_visual() : SpellScriptLoader("spell_sunder_rift_visual") { }

private:
	class spell_sunder_rift_visual_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_sunder_rift_visual_SpellScript);

		void ModDestHeight(SpellEffIndex /*effIndex*/)
		{
			Position offset = { 0.0f, 0.0f, 10.0f, 0.0f };
			const_cast<WorldLocation*>(GetExplTargetDest())->RelocateOffset(offset);
			GetHitDest()->RelocateOffset(offset);
		}

		void Register()
		{
			OnEffectLaunch += SpellEffectFn(spell_sunder_rift_visual_SpellScript::ModDestHeight, EFFECT_0, SPELL_EFFECT_DUMMY);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_sunder_rift_visual_SpellScript();
	}
};

void AddSC_boss_jindo_the_godbreaker()
{
    new boss_jindo_the_godbreaker();
    new npc_jindo_gurubashi_spirit();
    new npc_jindo_spirit_of_hakkar();
    new npc_jindo_chains_of_hakkar();
    new npc_jindo_spirit_portal();
    new spell_jindo_shadow_spike_target();
    new spell_jindo_summon_spirit_target();
    new spell_jindo_spirit_warrior_gaze_target();
	new boss_jindo_the_godbreaker_spirit_world();
	new spell_sunder_rift_visual();

}
