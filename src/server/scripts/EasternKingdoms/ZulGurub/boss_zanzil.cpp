#include "ScriptPCH.h"
#include "zulgurub.h"

enum ScriptTexts
{
    SAY_AGGRO   = 0,
    SAY_DEATH   = 1,
    SAY_GAS     = 2,
    SAY_KILL    = 3,
    SAY_BERSERK = 4,
    SAY_TROLLS  = 5,
};

enum eTexts
{
	EMOTE_ZANZIL_GRAVEYARD_GAS = 3,
	SAY_ZANZIL_GRAVEYARD_GAS = 4,
};

enum Spells
{
    SPELL_VOODOO_BOLT                            = 96346,
    SPELL_VOODOO_BOLT_H                          = 96347,
    SPELL_ZANZIL_FIRE							 = 96914,
    SPELL_ZANZIL_FIRE1							 = 96916,
    SPELL_ZANZIL_RES1							 = 96319, // zombie
    SPELL_ZANZIL_RES2							 = 96316, // berserker
	SPELL_ZANZILS_GRAVEYARD_GAS					 = 96338,
	SPELL_DRAIN_BLUE_CAULDRON					 = 96488,
	SPELL_DRAIN_RED_CAULDRON					 = 96486,
	SPELL_DRAIN_GREEN_CAULDRON					 = 96487,
	SPELL_GREEN_GAS							     = 97180,
	SPELL_TERRIBLE_TONIC						 = 96348,
	SPELL_TOXIC_GAS								 = 96500,

    SPELL_PURSUIT								 = 96342,
    SPELL_THUNDERCLAP							 = 96340,
    SPELL_KNOCK_AWAY							 = 96341,
};

enum Events
{
	// intro events
	EVENT_DRAIN_BLUE_CAULDRON = 1,
	EVENT_DRAIN_RED_CAULDRON = 2,
	EVENT_DRAIN_GREEN_CAULDRON = 3,
	EVENT_RITUAL_DANCE = 4,
	// Zanzil
    EVENT_ZANZIL_FIRE   = 1,
    EVENT_VOODOO_BOLT   = 2,
    EVENT_CAST_ZOMBIE   = 3,
    EVENT_CAST_BERSERK  = 4,
    EVENT_RES_ZOMBIE    = 5,
    EVENT_RES_BERSERK   = 6,
	EVENT_REMOVE_GAS = 7,
	EVENT_GRAVEYARD_GAS = 8,
	EVENT_TERRIBLE_TONIC = 9,
	EVENT_RESPAWN_ZOMBIE = 10,
	EVENT_RESPAWN_BERSERKER = 11,
};

enum Adds
{
    NPC_ZANZIL_ZOMBIE       = 52055,
    NPC_ZANZIL_BERSERKER    = 52054,
    NPC_ZANZIL_TOXIC_GAS    = 52062,
};

enum eDefine
{
	ACTION_FILL_GAS = 1,
	ID_GREEN_CAULDRON = 18,
	ID_RED_CAULDRON = 19,
	ID_BLUE_CAULDRON = 20,
	ID_GREEN_GAS = 21,
};

enum eMisc
{
	POINT_BLUE_CAULDRON = 1,
	POINT_RED_CAULDRON = 2,
	POINT_GREEN_CAULDRON = 3,
};

const float CauldronWP[3][3] =
{
	{ -11599.7f, -1292.10f, 77.5160f },
	{ -11581.7f, -1305.00f, 78.2143f },
	{ -11570.5f, -1271.27f, 77.5758f },
};

const Position berserkerPos[3] = 
{
    {-11603.59f, -1233.59f, 81.40f, 5.20f},
    {-11545.00f, -1240.56f, 81.55f, 3.92f},
    {-11541.40f, -1298.15f, 85.25f, 2.33f}
};

const Position zombiePos[4] =
{
    {-11590.67f, -1255.56f, 78.15f, 0.0f},
    {-11539.32f, -1259.71f, 78.98f, 0.0f},
    {-11586.93f, -1331.94f, 79.50f, 0.0f},
    {-11617.71f, -1315.54f, 79.40f, 0.0f}
};

const Position GasSP[22] =
{
	{ -11609.9f, -1222.70f, 87.9190f, 5.20108f },
	{ -11623.7f, -1355.40f, 82.2363f, 0.94247f },
	{ -11627.2f, -1354.40f, 86.6990f, 0.87266f },
	{ -11526.5f, -1256.37f, 87.4362f, 3.87463f },
	{ -11623.1f, -1276.96f, 83.8367f, 6.05629f },
	{ -11624.9f, -1275.04f, 87.3894f, 6.03884f },
	{ -11531.4f, -1292.22f, 83.7441f, 2.32129f },
	{ -11625.2f, -1278.44f, 87.4016f, 6.09120f },
	{ -11607.4f, -1223.03f, 84.6856f, 5.20108f },
	{ -11607.4f, -1220.11f, 87.6618f, 5.18363f },
	{ -11534.7f, -1225.67f, 85.6265f, 3.78736f },
	{ -11529.4f, -1292.84f, 87.3956f, 2.39110f },
	{ -11529.3f, -1254.09f, 87.5675f, 3.94444f },
	{ -11529.5f, -1256.81f, 83.3696f, 3.76991f },
	{ -11532.1f, -1294.95f, 87.5052f, 2.32129f },
	{ -11626.5f, -1357.79f, 86.3576f, 0.90757f },
	{ -11536.6f, -1225.10f, 81.7799f, 4.18879f },
	{ -11537.2f, -1223.78f, 85.8028f, 4.22370f },
	{ -11564.2f, -1258.80f, 78.7486f, 0.00000f },
	{ -11570.5f, -1313.09f, 79.3255f, 0.00000f },
	{ -11612.7f, -1283.43f, 78.4788f, 0.00000f },
	{ -11580.9f, -1287.01f, 77.3751f, 0.00000f },
};


class boss_zanzil : public CreatureScript
{
	class GasEvent : public BasicEvent
	{
	public:
		GasEvent(Creature* creature) : me(creature) {}

	private:
		bool Execute(uint64 /*time*/, uint32 /*diff*/)
		{
			me->AI()->DoAction(ACTION_FILL_GAS);
			return true;
		}

	private:
		Creature* me;
	};

    public:
        boss_zanzil() : CreatureScript("boss_zanzil") { }

        struct boss_zanzilAI : public BossAI
        {
            boss_zanzilAI(Creature* creature) : BossAI(creature, DATA_ZANZIL)
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
			uint64 GasGUID[22];
			uint64 ZombieGUID[56];
			uint64 BerserkerGUID[3];
			uint8 ResurrectionId;

			void InitializeAI()
			{
				for (int i = 0; i < ID_GREEN_CAULDRON; ++i)
				if (Creature* gas = me->SummonCreature(NPC_ZANZIL_TOXIC_GAS, GasSP[i]))
					GasGUID[i] = gas->GetGUID();

				static uint32 GasSpell[4] =
				{
					96868,
					96869,
					96867,
					SPELL_GREEN_GAS,
				};

				for (int i = ID_GREEN_CAULDRON; i <= ID_GREEN_GAS; ++i)
				if (Creature* gas = me->SummonCreature(NPC_ZANZIL_TOXIC_GAS, GasSP[i]))
				{
					GasGUID[i] = gas->GetGUID();
					gas->CastSpell(gas, GasSpell[i - ID_GREEN_CAULDRON], false);
				}

				memset(&ZombieGUID, 0, sizeof(ZombieGUID));
				memset(&BerserkerGUID, 0, sizeof(BerserkerGUID));
				Reset();
			}

            void Reset()
            {
                _Reset();
				RemoveGas();
				ResurrectionId = 0;
				me->SetWalk(true);
				me->SetReactState(REACT_AGGRESSIVE);
				events.ScheduleEvent(EVENT_DRAIN_BLUE_CAULDRON, 1000);
				instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

				/*for (int i = 0; i < 56; ++i)
				if (!ZombieGUID[i])
				if (Creature* zombie = me->SummonCreature(NPC_ZANZIL_ZOMBIE, zombiePos[i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
					ZombieGUID[i] = zombie->GetGUID();

				for (int i = 0; i < 3; ++i)
				if (!BerserkerGUID[i])
				if (Creature* berserker = me->SummonCreature(NPC_ZANZIL_BERSERKER, berserkerPos[i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
					BerserkerGUID[i] = berserker->GetGUID();*/
            }

            void EnterCombat(Unit* /*who*/)
            {
                Talk(SAY_AGGRO);
				events.Reset();
				events.ScheduleEvent(EVENT_VOODOO_BOLT, urand(5000, 15000));
				events.ScheduleEvent(EVENT_ZANZIL_FIRE, urand(5000, 15000));
				events.ScheduleEvent(EVENT_TERRIBLE_TONIC, urand(5000, 15000));
				events.ScheduleEvent(RAND(EVENT_CAST_BERSERK, EVENT_GRAVEYARD_GAS, EVENT_CAST_ZOMBIE), urand(15000, 30000));
			    DoZoneInCombat();
                instance->SetBossState(DATA_ZANZIL, IN_PROGRESS); 
            }
			void MovementInform(uint32 type, uint32 id)
			{
				if (type != POINT_MOTION_TYPE)
					return;

				switch (id)
				{
				case POINT_BLUE_CAULDRON:
				{
											if (GameObject* cauldron = me->FindNearestGameObject(208314, 20.0f))
												me->SetFacingTo(me->GetAngle(cauldron));

											me->CastSpell((Unit*)NULL, SPELL_DRAIN_BLUE_CAULDRON, false);
											events.ScheduleEvent(EVENT_RITUAL_DANCE, 4000);
											events.ScheduleEvent(RAND(EVENT_DRAIN_RED_CAULDRON, EVENT_DRAIN_GREEN_CAULDRON), urand(20000, 30000));
				}
					break;
				case POINT_RED_CAULDRON:
				{
										   if (GameObject* cauldron = me->FindNearestGameObject(208313, 20.0f))
											   me->SetFacingTo(me->GetAngle(cauldron));

										   me->CastSpell((Unit*)NULL, SPELL_DRAIN_RED_CAULDRON, false);
										   events.ScheduleEvent(EVENT_RITUAL_DANCE, 4000);
										   events.ScheduleEvent(RAND(EVENT_DRAIN_BLUE_CAULDRON, EVENT_DRAIN_GREEN_CAULDRON), urand(20000, 30000));
				}
					break;
				case POINT_GREEN_CAULDRON:
				{
											 if (GameObject* cauldron = me->FindNearestGameObject(208315, 20.0f))
												 me->SetFacingTo(me->GetAngle(cauldron));

											 me->CastSpell((Unit*)NULL, SPELL_DRAIN_GREEN_CAULDRON, false);
											 events.ScheduleEvent(EVENT_RITUAL_DANCE, 4000);
											 events.ScheduleEvent(RAND(EVENT_DRAIN_BLUE_CAULDRON, EVENT_DRAIN_RED_CAULDRON), urand(20000, 30000));
				}
					break;
				}
			}

			void RemoveGas()
			{
				if (Creature* gas = ObjectAccessor::GetCreature(*me, GasGUID[ID_GREEN_GAS]))
					gas->RemoveAllAuras();

				for (int i = 0; i < ID_GREEN_CAULDRON; ++i)
				if (Creature* gas = ObjectAccessor::GetCreature(*me, GasGUID[i]))
					gas->RemoveAllAuras();

				instance->DoRemoveAurasDueToSpellOnPlayers(96434);
			}

			void DoAction(int32 const action)
			{
				if (action == ACTION_FILL_GAS)
				{
					Talk(SAY_ZANZIL_GRAVEYARD_GAS);
					events.ScheduleEvent(EVENT_REMOVE_GAS, 15000);
					events.ScheduleEvent(RAND(EVENT_CAST_BERSERK, EVENT_CAST_ZOMBIE), 30000);

					if (Creature* gas = ObjectAccessor::GetCreature(*me, GasGUID[ID_GREEN_GAS]))
						gas->CastSpell(gas, SPELL_GREEN_GAS, false);

					Map::PlayerList const &players = me->GetMap()->GetPlayers();

					for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
					if (Player* player = itr->getSource())
						player->CastSpell(player, 96434, true, NULL, NULL, me->GetGUID());
				}
			}

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
                Talk(SAY_DEATH);
				RemoveGas();
				instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
            }   
            
            void KilledUnit(Unit* victim)
            {
                Talk(SAY_KILL);
            }
            
            void SpellHit(Unit* caster, SpellInfo const* spell)
            {
                if (me->GetCurrentSpell(CURRENT_GENERIC_SPELL))
                    if (me->GetCurrentSpell(CURRENT_GENERIC_SPELL)->m_spellInfo->Id == SPELL_VOODOO_BOLT ||
                        me->GetCurrentSpell(CURRENT_GENERIC_SPELL)->m_spellInfo->Id == SPELL_VOODOO_BOLT_H)
                        for (uint8 i = 0; i < 3; ++i)
                            if (spell->Effects[i].Effect == SPELL_EFFECT_INTERRUPT_CAST)
                                me->InterruptSpell(CURRENT_GENERIC_SPELL);
            }

            void UpdateAI(uint32 const diff)
            {
				if (!UpdateVictim())
				{
					if (uint32 eventId = events.ExecuteEvent())
					{
						switch (eventId)
						{
						case EVENT_DRAIN_BLUE_CAULDRON:
							me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
							me->GetMotionMaster()->MovePoint(POINT_BLUE_CAULDRON, CauldronWP[0][0], CauldronWP[0][1], CauldronWP[0][2]);
							break;
						case EVENT_DRAIN_RED_CAULDRON:
							me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
							me->GetMotionMaster()->MovePoint(POINT_RED_CAULDRON, CauldronWP[1][0], CauldronWP[1][1], CauldronWP[1][2]);
							break;
						case EVENT_DRAIN_GREEN_CAULDRON:
							me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_NONE);
							me->GetMotionMaster()->MovePoint(POINT_GREEN_CAULDRON, CauldronWP[2][0], CauldronWP[2][1], CauldronWP[2][2]);
							break;
						case EVENT_RITUAL_DANCE:
							me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_DANCE);
							break;
						}
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
                        case EVENT_VOODOO_BOLT:
                            DoCastVictim(SPELL_VOODOO_BOLT);
                            events.ScheduleEvent(EVENT_VOODOO_BOLT, urand(7000, 10000));
                            break;
                        case EVENT_ZANZIL_FIRE:
                            DoCastVictim(SPELL_ZANZIL_FIRE);
							events.ScheduleEvent(EVENT_ZANZIL_FIRE, urand(5000, 15000));
                            break;
						case EVENT_GRAVEYARD_GAS:
							Talk(EMOTE_ZANZIL_GRAVEYARD_GAS);
							me->CastSpell(me, SPELL_ZANZILS_GRAVEYARD_GAS, false);
							me->m_Events.AddEvent(new GasEvent(me), me->m_Events.CalculateTime(2 * IN_MILLISECONDS));
							break;
						case EVENT_REMOVE_GAS:
							RemoveGas();
							break;
                        case EVENT_CAST_ZOMBIE:
                            Talk(SAY_TROLLS);
                            DoCast(me, SPELL_ZANZIL_RES1);
							events.ScheduleEvent(EVENT_RES_ZOMBIE, 7000);
							events.ScheduleEvent(EVENT_RESPAWN_ZOMBIE, 15000);
                            break;
                        case EVENT_RES_ZOMBIE:
                        {
					        Talk(SAY_TROLLS);
							events.ScheduleEvent(RAND(EVENT_GRAVEYARD_GAS, EVENT_CAST_BERSERK), 30000);
                            uint8 pos = urand(0, 3);
                            for (uint8 i = 0; i < 15; ++i)
                                me->SummonCreature(NPC_ZANZIL_ZOMBIE, zombiePos[pos]);
                            break;
                        }
						case EVENT_RESPAWN_ZOMBIE:
						{
													 for (int i = ResurrectionId * 14; i < ResurrectionId * 14 + 14; ++i)
													 if (Creature* zombie = me->SummonCreature(NPC_ZANZIL_ZOMBIE, zombiePos[i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
														 ZombieGUID[i] = zombie->GetGUID();
						}

                        case EVENT_CAST_BERSERK:
                            Talk(SAY_BERSERK);
                            DoCast(me, SPELL_ZANZIL_RES2);
                            events.ScheduleEvent(EVENT_RES_BERSERK, 7000);
							events.ScheduleEvent(EVENT_RESPAWN_BERSERKER, 15000);
                            break;
                        case EVENT_RES_BERSERK:
							Talk(SAY_BERSERK);
							me->SummonCreature(NPC_ZANZIL_BERSERKER, berserkerPos[urand(0,2)]);
							me->SetReactState(REACT_AGGRESSIVE);
							events.ScheduleEvent(RAND(EVENT_GRAVEYARD_GAS, EVENT_CAST_ZOMBIE), 30000);

							if (Creature* berserker = ObjectAccessor::GetCreature(*me, BerserkerGUID[ResurrectionId]))
							{
								BerserkerGUID[ResurrectionId] = 0;
								berserker->GetMotionMaster()->MoveFall();
								berserker->SetReactState(REACT_AGGRESSIVE);
								berserker->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
								berserker->SetInCombatWithZone();
							}
                            break;
						case EVENT_RESPAWN_BERSERKER:
						{
														if (Creature* berserker = me->SummonCreature(NPC_ZANZIL_BERSERKER, berserkerPos[ResurrectionId], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
															BerserkerGUID[ResurrectionId] = berserker->GetGUID();
						}
							break;
						case EVENT_TERRIBLE_TONIC:
						{
													 if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
														 me->CastSpell(target, SPELL_TERRIBLE_TONIC, false);

													 events.ScheduleEvent(EVENT_TERRIBLE_TONIC, urand(5000, 15000));
						}
							break;
                    }
                }
                

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_zanzilAI(creature);
        }
};

class npc_zanzil_berserker : public CreatureScript
{
    public:

        npc_zanzil_berserker() : CreatureScript("npc_zanzil_berserker") {}
        
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_zanzil_berserkerAI(pCreature);
        }

        struct npc_zanzil_berserkerAI : public ScriptedAI
        {
            npc_zanzil_berserkerAI(Creature* pCreature) : ScriptedAI(pCreature) 
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
                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
                me->SetSpeed(MOVE_RUN, 0.5f);
            }
            
            bool bSpell;
            uint32 spellTimer;
            uint32 pursuitTimer;

            void Reset()
            {
                bSpell = true;
                spellTimer = 0;
                pursuitTimer = 3000;
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_IMMUNE_TO_PC);
            }
            
            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (!bSpell)
                {
                    if (spellTimer <= diff)
                    {
                        bSpell = true;
                        spellTimer = 12000;
                    }
                    else
                        spellTimer -= diff;
                }

                if (bSpell)
                    if (Unit* pTarget = me->SelectNearbyTarget())
                    {
                        bSpell = false;
                        DoCast(pTarget, urand(0, 1)? SPELL_KNOCK_AWAY: SPELL_THUNDERCLAP);
                    }

                if (pursuitTimer <= diff)
                {
                    pursuitTimer = 20000;
                    if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        DoCast(pTarget, SPELL_PURSUIT);
                }
                else
                    pursuitTimer -= diff;

                DoMeleeAttackIfReady();
            }

        };
};

class spell_zanzil_pursuit : public SpellScriptLoader
{
    public:
        spell_zanzil_pursuit() : SpellScriptLoader("spell_zanzil_pursuit") { }

        class spell_zanzil_pursuit_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_zanzil_pursuit_SpellScript);
            

            void HandleScript(SpellEffIndex effIndex)
            {
                if (!GetCaster() || !GetHitUnit())
                    return;

                if (GetCaster()->GetEntry() == NPC_ZANZIL_BERSERKER)
                {
                    static_cast<npc_zanzil_berserker::npc_zanzil_berserkerAI*>(GetCaster()->GetAI())->DoResetThreat();
                    GetCaster()->AddThreat(GetHitUnit(), 5000000.0f);
                    GetCaster()->GetAI()->AttackStart(GetHitUnit());
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_zanzil_pursuit_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_zanzil_pursuit_SpellScript();
        }
};

class spell_zanzil_fire : public SpellScriptLoader
{
    public:
        spell_zanzil_fire() : SpellScriptLoader("spell_zanzil_fire") { }

        class spell_zanzil_fire_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_zanzil_fire_AuraScript);
            
            bool Load()
            {
                count = 0;
                return true;
            }

            void PeriodicTick(constAuraEffectPtr aurEff)
            {
                if (!GetCaster())
                    return;

                count++;

                if (count > 6)
                {
                    GetCaster()->RemoveAurasDueToSpell(SPELL_ZANZIL_FIRE);
                    return;
                }

                Position pos;
                GetCaster()->GetNearPosition(pos, 4.0f * count, 0.0f);
                GetCaster()->CastSpell(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), SPELL_ZANZIL_FIRE1, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_zanzil_fire_AuraScript::PeriodicTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }

        private:
            uint8 count;
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_zanzil_fire_AuraScript();
        }
};

class spell_frostburn_formula : public SpellScriptLoader
{
    public:
        spell_frostburn_formula() : SpellScriptLoader("spell_frostburn_formula") { }

        class spell_frostburn_formula_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_frostburn_formula_SpellScript);
            

            void HandleScript(SpellEffIndex effIndex)
            {
                if (!GetCaster() || !GetHitUnit())
                    return;

                SetHitDamage(CalculatePct(GetHitUnit()->GetMaxHealth(), 65));
                GetHitUnit()->CastSpell(GetHitUnit(), SPELL_HYPPOTHERMIA, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_frostburn_formula_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_frostburn_formula_SpellScript();
        }
};

class AuraCheck : public std::unary_function<Unit*, bool>
{
public:
	explicit AuraCheck() {}

	bool operator()(WorldObject* object)
	{
		return object->ToUnit()->HasAuraType(SPELL_AURA_DUMMY);
	}
};

class spell_zanzils_graveyard_gas : public SpellScriptLoader
{
public:
	spell_zanzils_graveyard_gas() : SpellScriptLoader("spell_zanzils_graveyard_gas") { }

private:
	class spell_zanzils_graveyard_gas_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_zanzils_graveyard_gas_SpellScript);

		void FilterTargets(std::list<WorldObject*>& unitList)
		{
			unitList.remove_if(AuraCheck());

			if (unitList.size() > 3)
				unitList.resize(3);
		}

		void HandleScript(SpellEffIndex /*eff*/)
		{
			GetHitUnit()->CastSpell(GetHitUnit(), SPELL_TOXIC_GAS, false);
		}

		void Register()
		{
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_zanzils_graveyard_gas_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
			OnEffectHitTarget += SpellEffectFn(spell_zanzils_graveyard_gas_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_zanzils_graveyard_gas_SpellScript();
	}
};

class spell_zanzils_graveyard_gas_damage : public SpellScriptLoader
{
public:
	spell_zanzils_graveyard_gas_damage() : SpellScriptLoader("spell_zanzils_graveyard_gas_damage") { }

private:
	class spell_zanzils_graveyard_gas_damage_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_zanzils_graveyard_gas_damage_AuraScript)

		void HandleTick(constAuraEffectPtr aurEff)
		{
			PreventDefaultAction();

			if (!GetCaster())
				return;

			float damage = GetTarget()->GetMaxHealth() * GetSpellInfo()->Effects[EFFECT_0].BasePoints / 100;
			//damage = GetTarget()->SpellDamageBonusTaken(GetSpellInfo(), damage, DOT, 1, GetCasterGUID());

			int32 overkill = damage - GetTarget()->GetHealth();
			if (overkill < 0)
				overkill = 0;

			SpellPeriodicAuraLogInfo info(aurEff, damage, overkill, 0.0f, 0.0f, 0.0f, 0.0f);
			GetTarget()->SendPeriodicAuraLog(&info);

			GetCaster()->DealDamage(GetTarget(), damage, 0, DOT, GetSpellInfo()->GetSchoolMask(), GetSpellInfo(), true);
		}

		void Register()
		{
			OnEffectPeriodic += AuraEffectPeriodicFn(spell_zanzils_graveyard_gas_damage_AuraScript::HandleTick, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
		}
	};

	AuraScript *GetAuraScript() const
	{
		return new spell_zanzils_graveyard_gas_damage_AuraScript();
	}
};

void AddSC_boss_zanzil()
{
    new boss_zanzil();
    new npc_zanzil_berserker();
    new spell_zanzil_pursuit();
    new spell_zanzil_fire();
    new spell_frostburn_formula();
	new spell_zanzils_graveyard_gas_damage();
	new spell_zanzils_graveyard_gas();
}
