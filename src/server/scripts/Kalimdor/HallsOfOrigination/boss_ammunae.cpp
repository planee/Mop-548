#include "ScriptPCH.h"
#include "halls_of_origination.h"
#include "Vehicle.h"

enum ScriptTexts
{
    SAY_DEATH                = 0,
    SAY_AGGRO                = 1,
    SAY_GROWTH               = 2,
    SAY_KILL                 = 3,
};

enum Spells
{
    //Ammunae
    SPELL_WITHER                            = 76043,
    SPELL_CONSUME_LIFE_MANA                 = 75718,
    SPELL_CONSUME_LIFE_FOCUS                = 80968,
    SPELL_CONSUME_LIFE_FOCUS_H              = 94958,
    SPELL_CONSUME_LIFE_ENERGY               = 79766,
    SPELL_CONSUME_LIFE_ENERGY_H             = 94961,
    SPELL_CONSUME_LIFE_RUNIC                = 79768,
    SPELL_CONSUME_LIFE_RUNIC_H              = 94959,
    SPELL_CONSUME_LIFE_RAGE                 = 79767,
    SPELL_CONSUME_LIFE_RAGE_H               = 94960,
    SPELL_CONSUME_LIFE_SELF                 = 75665,
    SPELL_ZERO_POWER						= 72242,
    SPELL_RAMPANT_GROWTH                    = 75790,

    // Seedling Pod
    SPELL_ENERGIZE                          = 75657,
    SPELL_ENERGIZING_GROWTH                 = 75624,   
    SPELL_SEEDLING_POD                      = 96278,

    // Bloodpetal
    SPELL_THORN_SLASH                       = 76044,

    // Spore
    SPELL_SPORE_CLOUD                       = 75701,
    SPELL_NOXIOUS_SPORE                     = 75702,

	//Living Vine
	SPELL_SPORE_BLAST                       = 75153,

	//Lifewarden Nymph
	SPELL_SHOOT                             = 75958,
	SPELL_TRANQUILITY                       = 75940,
	SPELL_ENTANGLING_SHOOT                  = 75961,
};

enum Events
{
    EVENT_WITHER                = 1,
    EVENT_CONSUME_LIFE          = 2,
    EVENT_RAMPANT_GROWTH        = 3,
    EVENT_SUMMON_POD            = 4,
    EVENT_SUMMON_SPORE          = 5,
    EVENT_ENERGIZE              = 6,
	EVENT_SPORE_BLAST           = 7,
};

enum Adds
{
    NPC_SEEDLING_POD            = 40550, // 75624
    NPC_BLOODPETAL_BLOSSOM      = 40620, // 75770
    NPC_BLOODPETAL_BLOSSOM_2    = 40622,
    NPC_SPORE                   = 40585,
    NPC_SEEDLING_POD_2          = 40716, // 96278
    NPC_BUDDING_SPORE           = 40669, // 75867
    NPC_BLOODPETAL_SPROUT       = 40630, // 76486
    NPC_SEEDLING_POD_3          = 40592, // 75687
};

enum Misc
{
	DATA_RAMPANT_GROWTH = 1
};

class boss_ammunae : public CreatureScript
{
    public:
        boss_ammunae() : CreatureScript("boss_ammunae") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_ammunaeAI(pCreature);
        }

        struct boss_ammunaeAI : public BossAI
        {
            boss_ammunaeAI(Creature* pCreature) : BossAI(pCreature, DATA_AMMUNAE)
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
				me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_SPORE_CLOUD, true); // Noxious Spores
				me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_NOXIOUS_SPORE, true); // Noxious Spores
            }

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

                DoCast(me, SPELL_ZERO_POWER);
                me->setPowerType(POWER_ENERGY);
                me->SetMaxPower(POWER_ENERGY, 100);
                me->SetPower(POWER_ENERGY, 0);
            }

            void KilledUnit(Unit* /*Killed*/)
            {
                Talk(SAY_KILL);
            }

            void JustDied(Unit* /*Kill*/)
            {
                _JustDied();
                Talk(SAY_DEATH);
            }

            void EnterCombat(Unit* /*Ent*/)
            {
                Talk(SAY_AGGRO);

                events.ScheduleEvent(EVENT_WITHER, urand(3000, 6000));
                events.ScheduleEvent(EVENT_CONSUME_LIFE, urand(8000, 12000));
                events.ScheduleEvent(EVENT_SUMMON_POD, urand(7000, 14000));
                events.ScheduleEvent(EVENT_SUMMON_SPORE, urand(14000, 16000));

                DoZoneInCombat();
                instance->SetBossState(DATA_AMMUNAE, IN_PROGRESS);
            }

            void JustReachedHome()
		    {
			    _JustReachedHome();
		    }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
				    return;

                 if (me->GetPower(POWER_ENERGY) > 99)
                 {
                     Talk(SAY_GROWTH);
                     DoCastAOE(SPELL_RAMPANT_GROWTH);
					 std::list<Creature*> cList;
					 me->GetCreatureListWithEntryInGrid(cList, NPC_BLOODPETAL_BLOSSOM, 100.0f);
					 if (!cList.empty())
					 for (std::list<Creature *>::const_iterator itr = cList.begin(); itr != cList.end(); ++itr)
						 (*itr)->AI()->SetData(DATA_RAMPANT_GROWTH, 1);
                     return;
                 }

			    while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_WITHER:
                            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                DoCast(pTarget, SPELL_WITHER);
                            events.ScheduleEvent(EVENT_WITHER, urand(15000, 20000));
                            break;
                        case EVENT_SUMMON_SPORE:
                            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                me->SummonCreature(NPC_SPORE, pTarget->GetPositionX() + rand()%10, pTarget->GetPositionY() + rand()%10, pTarget->GetPositionZ(), 0.0f);
                            events.ScheduleEvent(EVENT_SUMMON_SPORE, urand(20000, 23000));
                            break;
                        case EVENT_SUMMON_POD:
							me->SummonCreature(NPC_BLOODPETAL_BLOSSOM, me->GetPositionX() + rand() % 10, me->GetPositionY() + rand() % 10, me->GetPositionZ(), 0.0f);
                            events.ScheduleEvent(EVENT_SUMMON_POD, urand(15000, 23000));
                            break;
                        case EVENT_CONSUME_LIFE:
                            DoCast(me, SPELL_CONSUME_LIFE_SELF, true);
                            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                            {
                                switch (pTarget->getPowerType())
                                {
                                    case POWER_FOCUS:
                                        DoCast(pTarget, SPELL_CONSUME_LIFE_FOCUS);
                                        break;
                                    case POWER_ENERGY:
                                        DoCast(pTarget, SPELL_CONSUME_LIFE_ENERGY);
                                        break;
                                    case POWER_RUNIC_POWER:
                                        DoCast(pTarget, SPELL_CONSUME_LIFE_RUNIC);
                                        break;
                                    case POWER_RAGE:
                                        DoCast(pTarget, SPELL_CONSUME_LIFE_RAGE);
                                        break;
                                    default:
                                        DoCast(pTarget, SPELL_CONSUME_LIFE_MANA);
                                        break;
                                }
                            }
                            events.ScheduleEvent(EVENT_CONSUME_LIFE, urand(18000, 20000));
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_ammunae_seedling_pod : public CreatureScript
{
    public:
        npc_ammunae_seedling_pod() : CreatureScript("npc_ammunae_seedling_pod") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_ammunae_seedling_podAI(pCreature);
        }

        struct npc_ammunae_seedling_podAI : public Scripted_NoMovementAI
        {
            npc_ammunae_seedling_podAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
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

            void Reset()
            {
                me->SetReactState(REACT_PASSIVE);
                DoCast(me, SPELL_SEEDLING_POD, true);
                if (Creature* pAmmunae = me->FindNearestCreature(NPC_AMMUNAE, 100.0f, true))
                    DoCast(pAmmunae, SPELL_ENERGIZE);
            }

            void UpdateAI(uint32 const diff)
            {
            }

            void JustDied(Unit* /*killer*/)
            {
                me->DespawnOrUnsummon();
            }
        };

};

class npc_ammunae_spore : public CreatureScript
{
    public:
        npc_ammunae_spore() : CreatureScript("npc_ammunae_spore") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_ammunae_sporeAI(pCreature);
        }

        struct npc_ammunae_sporeAI : public ScriptedAI
        {
            npc_ammunae_sporeAI(Creature* pCreature) : ScriptedAI(pCreature)
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
                me->SetReactState(REACT_PASSIVE);
            }

            void Reset()
            {
				/*if (me->GetMaxHealth())
                    me->GetMotionMaster()->MoveRandom(15.0f);
				else
					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);*/
            }
            
            void DamageTaken(Unit* /*who*/, uint32& damage)
            {
                if (damage >= me->GetHealth())
                {
					damage = 0;
					me->GetMotionMaster()->Clear();
                    me->SetStandState(UNIT_STAND_STATE_DEAD);
                    me->SetHealth(me->GetMaxHealth());
                    me->RemoveAllAuras();
					me->StopMoving();
					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
					DoCast(me, SPELL_SPORE_CLOUD); 
                }
            }

            void UpdateAI(uint32 const diff)
            {
            }
        };
};

class npc_living_vine : public CreatureScript
{
public:
	npc_living_vine() : CreatureScript("npc_living_vine") { }

	struct npc_living_vineAI : public ScriptedAI
	{
		npc_living_vineAI(Creature* creature) : ScriptedAI(creature)
		{
			SetCombatMovement(false);
			me->ApplySpellImmune(0, IMMUNITY_ID, 75701, true); // Noxious Spores
		}

		void Reset()
		{
			events.Reset();

			if (Unit* passenger = me->GetVehicleKit()->GetPassenger(1))
				passenger->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_SPORE_BLAST, 2000);
		}

		void JustDied(Unit* /*killer*/)
		{
			if (Unit* passenger = me->GetVehicleKit()->GetPassenger(1))
				passenger->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
			me->DespawnOrUnsummon(100);
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
				case EVENT_SPORE_BLAST:
					DoCastRandom(SPELL_SPORE_BLAST, 40.0f);
					events.ScheduleEvent(EVENT_SPORE_BLAST, 5000);
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
		return new npc_living_vineAI(creature);
	}
};

class npc_bloodpetal_blossom : public CreatureScript
{
	enum
	{
		SPELL_BLOSSOM_VISUAL = 75768,
	};

	struct npc_bloodpetal_blossomAI : public ScriptedAI
	{
		npc_bloodpetal_blossomAI(Creature * creature) : ScriptedAI(creature)
		{
			done = false;
			me->UpdateEntry(NPC_SEEDLING_POD);
			me->SetReactState(REACT_PASSIVE);
		}

		void Reset()
		{
			DoCast(me, SPELL_SEEDLING_POD, true);
			Map* map = me->GetMap();
			if (!map)
				return;
			if (!map->IsDungeon())
				return;
			if (map->GetDifficulty() == DUNGEON_DIFFICULTY_HEROIC)
			{
				if (Creature* pAmmunae = me->FindNearestCreature(NPC_AMMUNAE, 100.0f, true))
					me->CastSpell(pAmmunae, SPELL_ENERGIZING_GROWTH, true);
					//DoCast(pAmmunae, SPELL_ENERGIZING_GROWTH);
			}
			actionTimer = urand(15000, 18000);
		}

		void IsSummonedBy(Unit * summoner)
		{
			if (AuraPtr aur= summoner->GetAura(SPELL_ENERGIZE))
				aur->ModStackAmount(1);
			else
				summoner->AddAura(SPELL_ENERGIZE, summoner);
		}

		void JustDied(Unit* /*killer*/)
		{
			if (TempSummon* summon = me->ToTempSummon())
			if (Unit* summoner = summon->GetSummoner())
				summoner->RemoveAuraFromStack(SPELL_ENERGIZE);
		}

		void SetData(uint32 type, uint32)
		{
			if (!done && type == DATA_RAMPANT_GROWTH)
				actionTimer = 100;
		}

		void UpdateAI(uint32 const diff)
		{
			if (!done)
			{
				if (actionTimer <= diff)
				{
					done = true;
					me->RemoveAurasDueToSpell(SPELL_SEEDLING_POD);
					me->RemoveAurasDueToSpell(SPELL_ENERGIZE);
					me->RemoveAurasDueToSpell(SPELL_ENERGIZING_GROWTH);
					me->UpdateEntry(NPC_BLOODPETAL_BLOSSOM);
					DoCast(SPELL_BLOSSOM_VISUAL);
					me->SetHealth(me->GetMaxHealth());
					me->SetReactState(REACT_AGGRESSIVE);
					DoZoneInCombat();
					actionTimer = urand(5000, 8000);
				}
				else actionTimer -= diff;
			}
			else
			{
				if (!UpdateVictim())
					return;

				if (actionTimer <= diff)
				{
					DoCastVictim(SPELL_THORN_SLASH);
					actionTimer = urand(5000, 7500);
				}
				else actionTimer -= diff;
			}
		}
	private:
		bool done;
		uint32 actionTimer;
	};

public:
	npc_bloodpetal_blossom() : CreatureScript("npc_bloodpetal_blossom") {}

	CreatureAI * GetAI(Creature * creature) const
	{
		return new npc_bloodpetal_blossomAI(creature);
	}
};

/***************************
**Lifewarden Nymph
****************************/

class npc_lifewarden_nymph : public CreatureScript
{
public:
	npc_lifewarden_nymph() : CreatureScript("npc_lifewarden_nymph") {}

	struct npc_lifewarden_nymphAI : public ScriptedAI
	{
		npc_lifewarden_nymphAI(Creature *c) : ScriptedAI(c) {}

		uint32 shoot;
		uint32 entangling;
		uint32 tranqulility;

		void Reset()
		{
			shoot = 4000;
			entangling = 22000;
			tranqulility = 35000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			/*if (shoot <= diff)
			{
				DoCast(me->getVictim(), SPELL_SHOOT);
				shoot = 4000;
			}
			else shoot -= diff;*/

			if (entangling <= diff)
			{
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 10.0f, true))
					DoCast(target, SPELL_ENTANGLING_SHOOT);
				entangling = 22000;
			}
			else entangling -= diff;

			if (tranqulility <= diff)
			{
				DoCast(me, SPELL_TRANQUILITY);
				tranqulility = 35000;
			}
			else tranqulility -= diff;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_lifewarden_nymphAI(pCreature);
	}

};

void AddSC_boss_ammunae()
{
    new boss_ammunae();
    new npc_ammunae_seedling_pod();
    new npc_ammunae_spore();
	new npc_living_vine();
	new npc_bloodpetal_blossom();
	new npc_lifewarden_nymph();
}
