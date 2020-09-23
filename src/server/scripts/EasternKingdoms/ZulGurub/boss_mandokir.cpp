#include "ScriptPCH.h"
#include "zulgurub.h"

enum ScriptTexts
{
    SAY_AGGRO    = 0,
    SAY_DEATH    = 1,
    SAY_KILL     = 2,
    SAY_LEVEL    = 3,
    SAY_OHGAN    = 4,
    SAY_RES      = 5,
	EMOTE_FRENZY = 6,
	SAY_FRENZY   = 7,
};

enum Spells
{
    SPELL_DECAPITATE               = 96684,
    SPELL_LEVEL_UP                 = 96662,
    SPELL_DEVASTATING_SLAM         = 96740,
	SPELL_DEVASTATING_SLAM_TRIGGER = 96761,
	SPELL_DEVASTATING_SLAM_DAMAGE  = 97385,
    SPELL_BLOODLETTING_DUMMY       = 96776,
    SPELL_BLOODLETTING_DMG         = 96777,
    SPELL_BLOODLETTING_HEAL        = 96778,
    SPELL_REANIMATE_OHGAN          = 96724,
    SPELL_FRENZY                   = 96800,
    SPELL_OHGAN_ORGERS             = 96721,
    SPELL_OHGAN_ORDERS_DMG         = 96722,
	SPELL_PERMANENT_FEIGN_DEATH    = 96733,
	SPELL_CLEAR_ALL                = 28471,
	SPELL_BLOODLORD_AURA           = 96480,
	SPELL_SUMMON_OHGAN             = 96717,
	SPELL_SPIRIT_VENGEANCE_CANCEL  = 96821,

    SPELL_OHGAN_HEART              = 96727,

    SPELL_SPIRIT_FORM1             = 96568,
    SPELL_SPIRIT_FORM2             = 96642,
    SPELL_RESSURECT                = 96484,

};

enum Events
{
    EVENT_DECAPITATE        = 1,
    EVENT_DISMOUNT          = 2,
    EVENT_BLOODLETTING      = 3,
    EVENT_RESSURECT         = 4,
    EVENT_OHGAN_ORDERS      = 5,
    EVENT_DEVASTATING_SLAM  = 6,
    EVENT_OHGAN_RES         = 7,
    EVENT_LEVEL_UP          = 8,
	EVENT_SUMMON_OHGAN      = 9,
	EVENT_RETURN_TO_FIGHT   = 10,
	EVENT_BLOODLORD_AURA    = 11,
	EVENT_REANIMATE_OHGAN_COOLDOWN = 12,
};

enum Adds
{
    NPC_OHGAN               = 52157,
    NPC_DEVASTATING_SLAM    = 52324,
    NPC_CHAINED_SPIRIT      = 52156,
};

enum Points
{
    POINT_RES,
};
enum Other
{
    DATA_RES    = 1,
};

enum Action
{
	// Bloodlord Mandokir
	ACTION_OHGAN_IS_DEATH = 1,
	ACTION_START_REVIVE = 2,
	ACTION_EVADE = 3,

	// Chained Spirit
	ACTION_REVIVE = 1,
	ACTION_CHANGE_FACTION = 2,
	ACTION_REANIMATE_OHGAN = 3,
	ACTION_CLEAR_ALL = 4,
};

enum Misc
{
	POINT_START_REVIVE = 1,
	TYPE_PLAYER_REVIVE = 1,
	FACTION_NONE = 1665,
	DATA_OHGANOT_SO_FAST = 5762,
};

const Position chainedspiritPos[8] = 
{
    {-12378.6f, -1861.22f, 127.542f, 5.34071f},
    {-12391.2f, -1905.27f, 127.32f, 0.610865f},
    {-12351.9f, -1861.51f, 127.481f, 4.67748f},
    {-12326.7f, -1904.33f, 127.411f, 2.75762f},
    {-12347.4f, -1917.54f, 127.32f, 1.55334f},
    {-12397.8f, -1887.73f, 127.545f, 0.0349066f},
    {-12372.4f, -1918.84f, 127.343f, 1.15192f},
    {-12330.3f, -1878.41f, 127.32f, 3.89208f}
};
struct DiedPlayer
{
	uint64 playerGUID;
	uint32 resetTimer;
};
class boss_mandokir : public CreatureScript
{
    public:

        boss_mandokir() : CreatureScript("boss_mandokir") { }
        
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_mandokirAI(pCreature);
        }
            
        struct boss_mandokirAI : public BossAI
        {
			boss_mandokirAI(Creature* pCreature) : BossAI(pCreature, DATA_MANDOKIR), SummonedSpirit(pCreature)
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

			bool Frenzy;
			SummonList SummonedSpirit;
			std::list<DiedPlayer> players;
			bool OhganotSoFast;

            void Reset()
            {
                _Reset();
				Frenzy = false;
				me->CastSpell((Unit*)NULL, SPELL_SPIRIT_VENGEANCE_CANCEL, false);
				SummonedSpirit.DespawnAll();
				players.clear();
                for (uint8 i = 0; i < 8; ++i)
                    me->SummonCreature(NPC_CHAINED_SPIRIT, chainedspiritPos[i]);
				me->SetReactState(REACT_AGGRESSIVE);
				instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                bAchieve = true;
            }

            void KilledUnit(Unit* victim)
            {
                if (victim->GetTypeId() != TYPEID_PLAYER)
                    return;

                Talk(SAY_KILL);

                if (Creature* spirit = me->FindNearestCreature(NPC_CHAINED_SPIRIT, 200.0f))
                    spirit->AI()->SetGUID(victim->GetGUID(), DATA_RES);
				me->CastSpell((Unit*)NULL, SPELL_LEVEL_UP, true);
            }

			void JustSummoned(Creature* summoned)
			{
				switch (summoned->GetEntry())
				{
				case NPC_CHAINED_SPIRIT:
					SummonedSpirit.Summon(summoned);
					return;
				case NPC_DEVASTATING_SLAM:
				{
							  me->SetReactState(REACT_PASSIVE);
							  me->AttackStop();
							  me->CastStop();
							  me->StopMoving();
							  me->SetFacingTo(me->GetAngle(summoned));

							  for (uint8 i = 0; i <= 50; ++i)
							  {
								  float x, y;
								  me->GetNearPoint2D(x, y, frand(-2.5f, 50.0f), me->GetOrientation() + frand(-M_PI / 6, M_PI / 6));
								  me->CastSpell(x, y, me->GetPositionZ(), SPELL_DEVASTATING_SLAM_DAMAGE, true);
							  }

							  me->CastSpell(me, SPELL_DEVASTATING_SLAM, false);
							  events.ScheduleEvent(EVENT_RETURN_TO_FIGHT, 4000);
				}
					break;
				}

				summons.Summon(summoned);

				if (me->isInCombat())
					summoned->SetInCombatWithZone();
			}

            void EnterCombat(Unit* /*who*/)
            {
                Talk(SAY_AGGRO);
				EntryCheckPredicate pred(NPC_CHAINED_SPIRIT);
                events.ScheduleEvent(EVENT_DECAPITATE, 7000);
                events.ScheduleEvent(EVENT_BLOODLETTING, 10000);
                events.ScheduleEvent(EVENT_DISMOUNT, 15000);
				events.ScheduleEvent(EVENT_DEVASTATING_SLAM, 25000);
				events.ScheduleEvent(EVENT_BLOODLORD_AURA, 1000);
				SummonedSpirit.DoAction(ACTION_CHANGE_FACTION, pred);
                DoZoneInCombat();
                instance->SetBossState(DATA_MANDOKIR, IN_PROGRESS);
            }

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
                Talk(SAY_DEATH);
				players.clear();
				SummonedSpirit.DespawnAll();
				PlayersRemoveSpiritVengeance();
            }

			void PlayersRemoveSpiritVengeance()
			{
				Map* map = me->GetMap();
				Map::PlayerList const& players = map->GetPlayers();
				if (!players.isEmpty())
				for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
				if (Player* player = i->getSource())
				{
					if (player->HasAura(96493))//Remove Spirit Vengeance
						player->RemoveAura(96493);
				}
			}

			void DamageTaken(Unit* /*attacker*/, uint32& damage)
			{
				if (me->HealthBelowPctDamaged(20, damage) && !Frenzy)
				{
					Frenzy = true;
					Talk(SAY_FRENZY);
					Talk(EMOTE_FRENZY);
					me->CastSpell(me, SPELL_FRENZY, true);
				}
			}

            bool AllowAchieve()
            {
                return bAchieve;
            }
            
            void SummonedCreatureDies(Creature* summon, Unit* killer)
            {
                if (summon->GetEntry() == NPC_OHGAN)
                {
                    bAchieve = false;
                    events.ScheduleEvent(EVENT_OHGAN_RES, 10000);
                }
            }

			void DoAction(int32 const action)
			{
				switch (action)
				{
				case ACTION_OHGAN_IS_DEATH:
				{
											  OhganotSoFast = false;
											  uint32 LeftTime = 0;

											  if (events.GetNextEventTime(EVENT_REANIMATE_OHGAN_COOLDOWN))
											  {
												  LeftTime = events.GetNextEventTime(EVENT_REANIMATE_OHGAN_COOLDOWN) - events.GetTimer();
												  events.CancelEvent(EVENT_REANIMATE_OHGAN_COOLDOWN);
											  }

											  events.ScheduleEvent(EVENT_OHGAN_RES, LeftTime + urand(3000, 7000));
				}
					break;
				}
			}

			uint32 GetData(uint32 type) const
			{
				if (type == DATA_OHGANOT_SO_FAST)
					return uint32(OhganotSoFast);

				return 0;
			}

			void RevivePlayer(Player* player)
			{
				if (!SummonedSpirit.empty())
				{
					if (Creature* chainedSpirit = ObjectAccessor::GetCreature(*me, WoWSource::Containers::SelectRandomContainerElement(SummonedSpirit)))
					{
						DiedPlayer _player;
						_player.playerGUID = player->GetGUID();
						_player.resetTimer = 15000;
						players.push_back(_player);
						SummonedSpirit.Despawn(chainedSpirit);
						me->CombatStart(chainedSpirit);
						me->AddThreat(chainedSpirit, 100.0f);
						chainedSpirit->AI()->SetGUID(player->GetGUID(), TYPE_PLAYER_REVIVE);
					}
				}
								
			}

            void UpdateAI(uint32 const diff)
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
                        case EVENT_DECAPITATE:
                        {
							 me->CastSpell((Unit*)NULL, SPELL_DECAPITATE, false);
							 events.ScheduleEvent(EVENT_DECAPITATE, Frenzy ? 17500 : 35000);
							 //events.ScheduleEvent(EVENT_LEVEL_UP, 1000);
							 break;
                        }
                        case EVENT_LEVEL_UP:
                            Talk(SAY_LEVEL);
                            DoCast(me, SPELL_LEVEL_UP);
                            break;
                        case EVENT_BLOODLETTING:
                        {
                            Unit* pTarget = NULL;
                            pTarget = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true);
                            if (!pTarget)
                                pTarget = pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true);
                            if (pTarget)
                            {
                                DoCast(pTarget, SPELL_BLOODLETTING_DUMMY);
                                me->ClearUnitState(UNIT_STATE_CASTING);
                            }
                            events.ScheduleEvent(EVENT_BLOODLETTING, urand(20000, 30000));
                            break;
                        }
                        case EVENT_OHGAN_RES:
                            Talk(SAY_RES);
							me->SummonCreature(NPC_OHGAN, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());//Add Ohgan when he is died, that is a hack to fix problem with reanimate spell
							//me->CastSpell((Unit*)NULL, SPELL_REANIMATE_OHGAN, false);
							//events.ScheduleEvent(EVENT_REANIMATE_OHGAN_COOLDOWN, 25000);
                            break;
                       /* case EVENT_OHGAN_ORDERS:
                            break;*/
                        case EVENT_DISMOUNT:
                            Talk(SAY_OHGAN);
                            me->Dismount();
                            me->SummonCreature(NPC_OHGAN, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
                            break;
						case EVENT_BLOODLORD_AURA:
							me->CastSpell((Unit*)NULL, SPELL_BLOODLORD_AURA, false);
							events.ScheduleEvent(EVENT_BLOODLORD_AURA, 1000);
							break;
						case EVENT_DEVASTATING_SLAM:
							me->CastSpell(me, 96739, false);
							me->CastSpell((Unit*)NULL, SPELL_DEVASTATING_SLAM_TRIGGER, false);
							events.ScheduleEvent(EVENT_DEVASTATING_SLAM, 30000);
							break;
						case EVENT_RETURN_TO_FIGHT:
							me->SetReactState(REACT_AGGRESSIVE);
							break;
                    }
                }
                DoMeleeAttackIfReady();
            }
        private:
            bool bAchieve;

        };
};

class npc_mandokir_chained_spirit : public CreatureScript
{
    public:

        npc_mandokir_chained_spirit() : CreatureScript("npc_mandokir_chained_spirit") {}
        
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_mandokir_chained_spiritAI(pCreature);
        }

        struct npc_mandokir_chained_spiritAI : public ScriptedAI
        {
            npc_mandokir_chained_spiritAI(Creature* pCreature) : ScriptedAI(pCreature) 
            {
                me->SetSpeed(MOVE_RUN, 0.9f);
                me->SetReactState(REACT_PASSIVE);
                DoCast(me, SPELL_SPIRIT_FORM1, true);
                DoCast(me, SPELL_SPIRIT_FORM2, true);
            }
            
  
			uint64 _revivePlayerGUID;
			EventMap events;

			void InitializeAI()
			{
				Reset();
			}

			void Reset()
			{
				_revivePlayerGUID = 0;
			}

			void DamageTaken(Unit* /*killer*/, uint32 &damage)
			{
				if (_revivePlayerGUID && damage > me->GetHealth())
				{
					me->SetHealth(1);
					damage = 0;
				}
			}

			void SetGUID(uint64 guid, int32 type)
			{
				if (type == TYPE_PLAYER_REVIVE)
				{
					_revivePlayerGUID = guid;

					if (Player* player = ObjectAccessor::GetPlayer(*me, _revivePlayerGUID))
					{
						float x, y;
						player->GetNearPoint2D(x, y, 5.0f, player->GetAngle(me));
						me->GetMotionMaster()->MovePoint(POINT_START_REVIVE, x, y, player->m_positionZ);
					}
				}
			}

			void DoAction(int32 const action)
			{
				if (action == ACTION_CHANGE_FACTION)
				{
					me->setFaction(FACTION_NONE);
					me->SetInCombatState(false, me->ToTempSummon()->GetSummoner());
					me->getThreatManager().addThreat(me->ToTempSummon()->GetSummoner(), std::numeric_limits<float>::max());
					me->SetReactState(REACT_PASSIVE);
				}
			}

			void MovementInform(uint32 type, uint32 point)
			{
				if (type != POINT_MOTION_TYPE)
					return;

				if (point == POINT_START_REVIVE)
				{
					if (Player* player = ObjectAccessor::GetPlayer(*me, _revivePlayerGUID))
					{
						Talk(0, _revivePlayerGUID);
						player->RemoveAura(SPELL_BLOODLORD_AURA);
						me->CastSpell(player, SPELL_RESSURECT, false, NULL, NULL, player->GetGUID());
					}

					if (AuraPtr aura = me->GetAura(SPELL_OHGAN_ORDERS_DMG))
					if (Unit* caster = aura->GetCaster())
						caster->CastSpell((Unit*)NULL, SPELL_OHGAN_ORGERS, true);

					me->DespawnOrUnsummon(3000);
				}
			}
        };
};

class npc_mandokir_ohgan : public CreatureScript
{
    public:

        npc_mandokir_ohgan() : CreatureScript("npc_mandokir_ohgan") {}
        
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_mandokir_ohganAI(pCreature);
        }

        struct npc_mandokir_ohganAI : public ScriptedAI
        {
            npc_mandokir_ohganAI(Creature* pCreature) : ScriptedAI(pCreature) 
            {
                me->SetSpeed(MOVE_RUN, 0.8f);
                //me->SetReactState(REACT_PASSIVE);
				me->SetReactState(REACT_AGGRESSIVE);
                DoCast(me, SPELL_OHGAN_HEART);
            }
			InstanceScript* instance;
			void SpellHitTarget(Unit* victim, const SpellInfo * spell)
			{
				if (spell->Id == SPELL_OHGAN_ORGERS)
					AttackStart(victim);
			}

			void EnterCombat(Unit* /*who*/)
			{
				me->SetReactState(REACT_AGGRESSIVE);
				//me->CastSpell((Unit*)NULL, SPELL_OHGAN_ORGERS, true);
				//instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
				DoZoneInCombat();
			}

			void JustDied(Unit* /*killer*/)
			{
				me->DespawnOrUnsummon(3000);
			}

			void DoAction(int32 const action)
			{
				switch (action)
				{
				case ACTION_REANIMATE_OHGAN:
					me->RemoveAura(SPELL_PERMANENT_FEIGN_DEATH);
					me->CastSpell(me, SPELL_OHGAN_HEART, true);
					//me->CastSpell((Unit*)NULL, SPELL_OHGAN_ORGERS, true);
					//instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
					DoZoneInCombat();
					break;
				case ACTION_CLEAR_ALL:
					me->AttackStop();
					me->StopMoving();
					me->SetTarget(0);
					me->ClearInCombat();
					me->RemoveAllAuras();
					me->getThreatManager().resetAllAggro();
					break;
				}
			}

			//void DamageTaken(Unit* /*attacker*/, uint32& damage)
			/*{
				if (damage >= me->GetHealth())
				{
					damage = 0;
					me->CastSpell(me, SPELL_CLEAR_ALL, true);
					me->CastSpell(me, SPELL_PERMANENT_FEIGN_DEATH);
					instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);

					if (Creature* summoner = me->ToTempSummon()->GetSummonerCreatureBase())
						summoner->AI()->DoAction(ACTION_OHGAN_IS_DEATH);
				}
			}*/

			void KilledUnit(Unit* victim)
			{
				if (Creature* spirit = me->FindNearestCreature(NPC_CHAINED_SPIRIT, 200.0f))
					spirit->AI()->SetGUID(victim->GetGUID(), DATA_RES);
				if (victim->GetEntry() == NPC_CHAINED_SPIRIT)
					me->CastSpell((Unit*)NULL, SPELL_OHGAN_ORGERS, true);
				if (Creature* creature = me->FindNearestCreature(NPC_MANDOKIR, 500.0f, true))
					creature->CastSpell((Unit*)NULL, SPELL_LEVEL_UP, true);
			}

			void UpdateAI(uint32 const /*diff*/)
			{
				if (!UpdateVictim())
					return;

				DoMeleeAttackIfReady();
			}

        };
};

class spell_mandokir_decapitate : public SpellScriptLoader
{
public:
	spell_mandokir_decapitate() : SpellScriptLoader("spell_mandokir_decapitate") { }

private:
	class spell_mandokir_decapitate_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_mandokir_decapitate_SpellScript);

		void HandleScript(SpellEffIndex /*effIndex*/)
		{
			GetCaster()->CastSpell(GetHitUnit(), uint32(GetEffectValue()), true);
		}

		void Register()
		{
			OnEffectHitTarget += SpellEffectFn(spell_mandokir_decapitate_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_mandokir_decapitate_SpellScript();
	}
};

class spell_mandokir_bloodletting : public SpellScriptLoader
{
    public:
        spell_mandokir_bloodletting() : SpellScriptLoader("spell_mandokir_bloodletting") { }

        class spell_mandokir_bloodletting_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_mandokir_bloodletting_AuraScript);

            void PeriodicTick(constAuraEffectPtr aurEff)
            {
                if (!GetCaster() || !GetTarget())
                    return;

                int32 damage = int32(0.5f * GetTarget()->GetHealth());
                int32 heal = int32(0.5f * damage);
                GetCaster()->CastCustomSpell(GetTarget(), SPELL_BLOODLETTING_DMG, &damage, 0, 0, true);
                GetCaster()->CastCustomSpell(GetCaster(), SPELL_BLOODLETTING_HEAL, &heal, 0, 0, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_mandokir_bloodletting_AuraScript::PeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_mandokir_bloodletting_AuraScript();
        }
};

class spell_mandokir_spirit_vengeance_cancel : public SpellScriptLoader
{
public:
	spell_mandokir_spirit_vengeance_cancel() : SpellScriptLoader("spell_mandokir_spirit_vengeance_cancel") { }

private:
	class spell_mandokir_spirit_vengeance_cancel_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_mandokir_spirit_vengeance_cancel_SpellScript);

		void HandleScript(SpellEffIndex /*effIndex*/)
		{
			GetHitUnit()->RemoveAura(uint32(GetEffectValue()));
		}

		void Register()
		{
			OnEffectHitTarget += SpellEffectFn(spell_mandokir_spirit_vengeance_cancel_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
			OnEffectHitTarget += SpellEffectFn(spell_mandokir_spirit_vengeance_cancel_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_DUMMY);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_mandokir_spirit_vengeance_cancel_SpellScript();
	}
};

class spell_mandokir_ohgan_orders : public SpellScriptLoader
{
public:
	spell_mandokir_ohgan_orders() : SpellScriptLoader("spell_mandokir_ohgan_orders") { }

private:
	class spell_mandokir_ohgan_orders_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_mandokir_ohgan_orders_SpellScript);

		void HandleScript(SpellEffIndex /*effIndex*/)
		{
			GetCaster()->CastSpell(GetHitUnit(), uint32(GetEffectValue()), true);
		}

		void Register()
		{
			OnEffectHitTarget += SpellEffectFn(spell_mandokir_ohgan_orders_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_mandokir_ohgan_orders_SpellScript();
	}
};

class spell_mandokir_ohgan_orders_trigger : public SpellScriptLoader
{
public:
	spell_mandokir_ohgan_orders_trigger() : SpellScriptLoader("spell_mandokir_ohgan_orders_trigger") { }

private:
	class spell_mandokir_ohgan_orders_trigger_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_mandokir_ohgan_orders_trigger_SpellScript);

		void HandleScript(SpellEffIndex effIndex)
		{
			GetHitUnit()->CastSpell(GetCaster(), GetSpellInfo()->Effects[effIndex].BasePoints, true);
		}

		void Register()
		{
			OnEffectHitTarget += SpellEffectFn(spell_mandokir_ohgan_orders_trigger_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_mandokir_ohgan_orders_trigger_SpellScript();
	}
};

class spell_ohgan_permanent_feign_death : public SpellScriptLoader
{
public:
	spell_ohgan_permanent_feign_death() : SpellScriptLoader("spell_ohgan_permanent_feign_death") { }

private:
	class spell_ohgan_permanent_feign_deathAuraScript : public AuraScript
	{
		PrepareAuraScript(spell_ohgan_permanent_feign_deathAuraScript)

		void EffectDeath(constAuraEffectPtr aurEff, AuraEffectHandleModes mode)
		{
			GetTarget()->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
			//GetTarget()->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
			GetTarget()->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

			if (GetTarget()->ToCreature())
				GetTarget()->ToCreature()->SetReactState(REACT_PASSIVE);
		}

		void EffectRevive(constAuraEffectPtr aurEff, AuraEffectHandleModes mode)
		{
			GetTarget()->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
			//GetTarget()->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
			GetTarget()->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

			if (GetTarget()->ToCreature())
				GetTarget()->ToCreature()->SetReactState(REACT_AGGRESSIVE);
		}

		void Register()
		{
			OnEffectApply += AuraEffectApplyFn(spell_ohgan_permanent_feign_deathAuraScript::EffectDeath, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
			OnEffectRemove += AuraEffectRemoveFn(spell_ohgan_permanent_feign_deathAuraScript::EffectRevive, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
		}
	};

	AuraScript *GetAuraScript() const
	{
		return new spell_ohgan_permanent_feign_deathAuraScript();
	}
};

class DevastatingSlamTargetSelector : public std::unary_function<Unit *, bool>
{
public:
	DevastatingSlamTargetSelector(Creature* me, const Unit* victim) : _me(me), _victim(victim) {}

	bool operator() (WorldObject* target)
	{
		if (target == _victim && _me->getThreatManager().getThreatList().size() > 1)
			return true;

		if (target->GetTypeId() != TYPEID_PLAYER)
			return true;

		return false;
	}

	Creature* _me;
	Unit const* _victim;
};

class spell_mandokir_devastating_slam : public SpellScriptLoader
{
public:
	spell_mandokir_devastating_slam() : SpellScriptLoader("spell_mandokir_devastating_slam") { }

	class spell_mandokir_devastating_slam_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_mandokir_devastating_slam_SpellScript);

		void FilterTargets(std::list<WorldObject*>& targets)
		{
			targets.remove_if(DevastatingSlamTargetSelector(GetCaster()->ToCreature(), GetCaster()->getVictim()));
			if (targets.empty())
				return;

			WorldObject* target =WoWSource::Containers::SelectRandomContainerElement(targets);
			targets.clear();
			targets.push_back(target);
		}

		void HandleScript(SpellEffIndex /*effIndex*/)
		{
			Unit* caster = GetCaster();
			float angle = 0.0f;
			float x, y, z;

			if (Player* target = GetHitPlayer())
			{
				caster->AttackStop();
				caster->SetOrientation(caster->GetAngle(target));
				caster->SetFacingTo(caster->GetAngle(target));

				caster->CastSpell(caster, SPELL_DEVASTATING_SLAM, false);

				// HACK: Need better way for pos calculation
				for (uint8 i = 0; i <= 50; ++i)
				{
					angle = float(rand_norm()) * static_cast<float>(M_PI * 35.0f / 180.0f) - static_cast<float>(M_PI * 17.5f / 180.0f);
					caster->GetClosePoint(x, y, z, 4.0f, frand(-2.5f, 50.0f), angle);

					caster->CastSpell(x, y, z, SPELL_DEVASTATING_SLAM_DAMAGE, true);
				}
			}
		}

		void Register()
		{
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mandokir_devastating_slam_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
			OnEffectHitTarget += SpellEffectFn(spell_mandokir_devastating_slam_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_FORCE_CAST);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_mandokir_devastating_slam_SpellScript();
	}
};
typedef boss_mandokir::boss_mandokirAI MandokirAI;

class achievement_ohganot_so_fast : public AchievementCriteriaScript
{
    public:
        achievement_ohganot_so_fast() : AchievementCriteriaScript("achievement_ohganot_so_fast") { }

        bool OnCheck(Player* source, Unit* target)
        {
            if (!target)
                return false;

            if (MandokirAI* mandokirAI = CAST_AI(MandokirAI, target->GetAI()))
                return mandokirAI->AllowAchieve();

            return false;
        }
};

class spell_mandokir_reanimate_ohgan : public SpellScriptLoader
{
public:
	spell_mandokir_reanimate_ohgan() : SpellScriptLoader("spell_mandokir_reanimate_ohgan") { }

private:
	class spell_mandokir_reanimate_ohgan_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_mandokir_reanimate_ohgan_SpellScript);

		void HandleScript(SpellEffIndex /*effIndex*/)
		{
			GetHitUnit()->GetAI()->DoAction(ACTION_REANIMATE_OHGAN);
		}

		void Register()
		{
			OnEffectHitTarget += SpellEffectFn(spell_mandokir_reanimate_ohgan_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_mandokir_reanimate_ohgan_SpellScript();
	}
};

class spell_clear_all : public SpellScriptLoader
{
public:
	spell_clear_all() : SpellScriptLoader("spell_clear_all") { }

private:
	class spell_clear_all_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_clear_all_SpellScript);

		void HandleScript(SpellEffIndex /*effIndex*/)
		{
			GetCaster()->GetAI()->DoAction(ACTION_CLEAR_ALL);
		}

		void Register()
		{
			OnEffectHitTarget += SpellEffectFn(spell_clear_all_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_clear_all_SpellScript();
	}
};


void AddSC_boss_mandokir()
{
    new boss_mandokir();
    new npc_mandokir_chained_spirit();
    new npc_mandokir_ohgan();
    new spell_mandokir_bloodletting();
    new achievement_ohganot_so_fast();
	new spell_mandokir_decapitate();
	new spell_mandokir_spirit_vengeance_cancel();
	new spell_mandokir_ohgan_orders();
	new spell_mandokir_ohgan_orders_trigger();
	new spell_ohgan_permanent_feign_death();
	new spell_mandokir_reanimate_ohgan();
	new spell_clear_all();
}
