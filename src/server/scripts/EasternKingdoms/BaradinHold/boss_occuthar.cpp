#include "ScriptPCH.h"
#include "baradin_hold.h"

enum Spells
{
    SPELL_BERSERK                   = 47008, 
    SPELL_SEARING_SHADOW            = 96913, 

    SPELL_FOCUSED_FIRE              = 96872,
    SPELL_FOCUSED_FIRE_DUMMY        = 96886,
    SPELL_FOCUSED_FIRE_1            = 96884,

    SPELL_EYE_OF_OCCUTHAR           = 96920, 
    SPELL_EYE_OF_OCCUTHAR_25        = 101006,
    SPELL_EYE_OF_OCCUTHAR_VEHICLE   = 96932,

    SPELL_EYE_OF_OCCUTHAR_DMG       = 96942,
	SPELL_GAZE_OF_OCCUTHAR          = 97028,
    SPELL_OCCUTHARS_DESTRUCTION     = 96968,
    
};

enum Events
{
    EVENT_BERSERK           = 1,
    EVENT_SEARING_SHADOWS   = 2,
    EVENT_EYE_OF_OCCUTHAR   = 3,
    EVENT_FOCUSED_FIRE      = 4,
	EVENT_GAZE_OF_OCCUTHAR  = 5,
	EVENT_AOE               = 6,
	EVENT_OCCU_DESTRUCT     = 7,
	EVENT_EYE_REMOVE        = 8,
};

enum Adds
{
    NPC_EYE_OF_OCCUTHAR = 52389,
    NPC_EYESTALK        = 52369,
};

class boss_occuthar : public CreatureScript
{
    public:
        boss_occuthar() : CreatureScript("boss_occuthar") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_occutharAI(pCreature);
        }

        struct boss_occutharAI : public BossAI
        {
            boss_occutharAI(Creature* pCreature) : BossAI(pCreature, DATA_OCCUTHAR) 
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

            void InitializeAI()
            {
                if (!instance || static_cast<InstanceMap*>(me->GetMap())->GetScriptId() != sObjectMgr->GetScriptId(BHScriptName))
                    me->IsAIEnabled = false;
                else if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                _Reset();
                
                events.Reset();
				instance->HandleGameObject(instance->GetData64(GO_OCCUTHAR_DOOR), true); // set me to true, when we release step by step
            }

            void JustReachedHome()
            {
                _JustReachedHome();
            }

            void EnterCombat(Unit* attacker)
            {
                events.ScheduleEvent(EVENT_BERSERK, 300000);
                events.ScheduleEvent(EVENT_EYE_OF_OCCUTHAR, 59000);
                events.ScheduleEvent(EVENT_FOCUSED_FIRE, 26000);
                events.ScheduleEvent(EVENT_SEARING_SHADOWS, 24000); 
                instance->SetBossState(DATA_OCCUTHAR, IN_PROGRESS);
				instance->HandleGameObject(instance->GetData64(GO_OCCUTHAR_DOOR), false);
            }

            void JustDied(Unit* killer)
            {
                _JustDied();
				if (instance)
				{
					Map* map = me->GetMap();
					if (!map)
						return;

					if (!map->IsDungeon())
						return;

					//75 Justices Points for players level 85
					instance->DoModifyPlayerCurrenciesIfLevel(395, 7500, 85);
				}
				instance->HandleGameObject(instance->GetData64(GO_OCCUTHAR_DOOR), true);
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
                        case EVENT_BERSERK:
                            DoCast(me, SPELL_BERSERK, true);
                            break;
                        case EVENT_SEARING_SHADOWS:
                            DoCast(me->getVictim(), SPELL_SEARING_SHADOW);
                            events.ScheduleEvent(EVENT_SEARING_SHADOWS, 24000);
                            break;
                        case EVENT_FOCUSED_FIRE:
							if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0/*, NonTankTargetSelector(me)*/))
							{
								DoCastAOE(SPELL_FOCUSED_FIRE);
								me->SummonCreature(NPC_FOCUSED_FIRE_DUMMY, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ());
							}
                            events.ScheduleEvent(EVENT_FOCUSED_FIRE, 14000);
                            break;
                        case EVENT_EYE_OF_OCCUTHAR:
                            DoCastAOE(SPELL_EYE_OF_OCCUTHAR);
                            events.RescheduleEvent(EVENT_FOCUSED_FIRE, 26000);
                            events.ScheduleEvent(EVENT_EYE_OF_OCCUTHAR, 59000);
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class spell_occuthar_eye_of_occuthar : public SpellScriptLoader
{
    public:
        spell_occuthar_eye_of_occuthar() : SpellScriptLoader("spell_occuthar_eye_of_occuthar") { }

        class spell_occuthar_eye_of_occuthar_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_occuthar_eye_of_occuthar_SpellScript);

            void HandleScript(SpellEffIndex /*effIndex*/)
			{
                if (!GetCaster() || !GetHitUnit())
                    return;

                GetCaster()->CastSpell(GetCaster(), SPELL_EYE_OF_OCCUTHAR_VEHICLE, true);
                
                if (Creature* pEye = GetCaster()->SummonCreature(NPC_EYE_OF_OCCUTHAR, GetCaster()->GetPositionX(), GetCaster()->GetPositionY(), GetCaster()->GetPositionZ(), GetCaster()->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 11000))
                    pEye->CastSpell(GetCaster(), SPELL_EYE_OF_OCCUTHAR_DMG, true); 
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_occuthar_eye_of_occuthar_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_occuthar_eye_of_occuthar_SpellScript();
        }
};

class npc_focused_fire_dummy : public CreatureScript
{
public:
	npc_focused_fire_dummy() : CreatureScript("npc_focused_fire_dummy") { }

	struct npc_focused_fire_dummyAI : public BossAI
	{
		npc_focused_fire_dummyAI(Creature* creature) : BossAI(creature, DATA_FOCUSED_FIRE_DUMMY)
		{
		}

		void EnterCombat(Unit* who)
		{
			events.ScheduleEvent(EVENT_AOE, 1000);
		}

		void UpdateAI(uint32 const diff)
		{
			if (!UpdateVictim() || !CheckInRoom())
				return;

			events.Update(diff);

			if (me->HasUnitState(UNIT_STATE_CASTING))
				return;

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_AOE:
					DoCast(SPELL_FOCUSED_FIRE_1);
					break;
				}
			}
		}

	protected:
		EventMap Events;
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_focused_fire_dummyAI(creature);
	}
};

class npc_eye_of_occuthar : public CreatureScript
{
public:
	npc_eye_of_occuthar() : CreatureScript("npc_eye_of_occuthar") { }

	struct npc_eye_of_occutharAI : public BossAI
	{
		npc_eye_of_occutharAI(Creature* creature) : BossAI(creature, DATA_EYE_OF_OCCUTHAR)
		{
		}

		void reset()
		{
			events.ScheduleEvent(EVENT_GAZE_OF_OCCUTHAR, 8000);
		}

		void EnterCombat(Unit* /*who*/)
		{
			events.ScheduleEvent(EVENT_GAZE_OF_OCCUTHAR, 1000);
		}

		void UpdateAI(uint32 const diff)
		{
			if (!UpdateVictim() || !CheckInRoom())
				return;

			events.Update(diff);

			if (me->HasUnitState(UNIT_STATE_CASTING) && !me->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
				return;

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_GAZE_OF_OCCUTHAR:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
						DoCast(target, SPELL_GAZE_OF_OCCUTHAR);
					events.ScheduleEvent(EVENT_OCCU_DESTRUCT, 10000);
					break;
				case EVENT_OCCU_DESTRUCT:
					//DoCast(me, SPELL_OCCUTHARS_DESTRUCTION, false);
					DoCastAOE(SPELL_OCCUTHARS_DESTRUCTION, true);
					events.ScheduleEvent(EVENT_EYE_REMOVE, 1500);
					break;
				case EVENT_EYE_REMOVE:
					me->DisappearAndDie();
					break;
				}
			}
		}

	protected:
		EventMap Events;
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_eye_of_occutharAI(creature);
	}
};

void AddSC_boss_occuthar()
{
    new boss_occuthar();
    new spell_occuthar_eye_of_occuthar();
	new npc_focused_fire_dummy();
	new npc_eye_of_occuthar();
}
