#include "ScriptPCH.h"
#include "baradin_hold.h"

enum Spells
{
    SPELL_FEL_FIRESTORM       = 88972,
    SPELL_CONSUMING_DARKNESS  = 88954,
    SPELL_METEOR_SLASH        = 88942,
	SPELL_METEOR_SLASH_VISUAL = 88949,
    SPELL_BERSERK             = 47008,
};

enum ePhases
{
    PHASE_1,
    PHASE_2,
};

class boss_argaloth : public CreatureScript
{
    public:
        boss_argaloth() : CreatureScript("boss_argaloth") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_argalothAI(pCreature);
        }

        struct boss_argalothAI : public BossAI
        {
            boss_argalothAI(Creature* pCreature) : BossAI(pCreature, DATA_ARGALOTH) 
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

            uint8 Phase, PhaseCount;

            uint32 SlashTimer;
            uint32 ConsumingDarknessTimer;
            uint32 BerserkTimer;
            uint32 ResetPhaseTimer;

            void Reset()
            {
                _Reset();
				me->RemoveAurasDueToSpell(SPELL_BERSERK);
                PhaseCount = 0;
                SlashTimer = 10000;
                ConsumingDarknessTimer = 15000;
                BerserkTimer = 360000;
                Phase = PHASE_1;
				instance->HandleGameObject(instance->GetData64(GO_ARGALOTH_DOOR), true);
            }

            void EnterCombat(Unit* attacker)
            {
				_EnterCombat();
                instance->SetBossState(DATA_ARGALOTH, IN_PROGRESS);
				instance->HandleGameObject(instance->GetData64(GO_ARGALOTH_DOOR), false);
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

				instance->HandleGameObject(instance->GetData64(GO_ARGALOTH_DOOR), true);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if(SlashTimer <= diff && Phase == PHASE_1)
                {
                    DoCastVictim(SPELL_METEOR_SLASH);
					me->CastSpell(me, SPELL_METEOR_SLASH_VISUAL, true);
                    SlashTimer = 15000;
                } else SlashTimer -= diff;

                if(ConsumingDarknessTimer <= diff && Phase == PHASE_1)
                {
					me->CastCustomSpell(SPELL_CONSUMING_DARKNESS, SPELLVALUE_MAX_TARGETS, RAID_MODE(3, 8, 3, 8), me);
                    ConsumingDarknessTimer = 15000;
                } else ConsumingDarknessTimer -= diff;

                if(BerserkTimer <= diff && Phase == PHASE_1)
                {
                    DoCast(me, SPELL_BERSERK);
                    BerserkTimer = 360000;
                } else BerserkTimer -= diff;

                if (HealthBelowPct(67) && Phase == PHASE_1 && PhaseCount == 0)
                {
                    PhaseCount++;
                    Phase = PHASE_2;
                    me->SetReactState(REACT_PASSIVE);
                    me->AttackStop();
                    DoCastAOE(SPELL_FEL_FIRESTORM);
                    ResetPhaseTimer = 16500;
                }

                if (HealthBelowPct(34) && Phase == PHASE_1 && PhaseCount == 1)
                {
                    PhaseCount++;
                    Phase = PHASE_2;
                    me->SetReactState(REACT_PASSIVE);
                    me->AttackStop();
                    DoCastAOE(SPELL_FEL_FIRESTORM);
                    ResetPhaseTimer = 16500;
                }

                if(ResetPhaseTimer <= diff)
                {
                    Phase = PHASE_1;
                    me->SetReactState(REACT_AGGRESSIVE);
                    SlashTimer = 10000;
                    ConsumingDarknessTimer = 15000;
                    ResetPhaseTimer = 360000;
                } else ResetPhaseTimer -= diff;

                DoMeleeAttackIfReady();
            }
        };
};

// Fel Firestorm 88972

class spell_argaloth_fel_firestorm : public SpellScriptLoader
{
	class script_impl : public AuraScript
	{
		PrepareAuraScript(script_impl);

		void OnRemove(constAuraEffectPtr, AuraEffectHandleModes)
		{
			Unit* const caster = GetCaster();
			if (!caster || !caster->ToCreature())
				return;

			std::list<Creature*> triggerList;
			caster->GetCreatureListWithEntryInGrid(triggerList, NPC_FEL_FIRESTORM_TRIGGER, 100.0f);
			for (std::list<Creature*>::iterator itr = triggerList.begin(); itr != triggerList.end(); ++itr)
			if (Creature* const trigger = *itr)
				trigger->DespawnOrUnsummon(1000);
			caster->ToCreature()->SetReactState(REACT_AGGRESSIVE);
		}

		void Register()
		{
			OnEffectRemove += AuraEffectRemoveFn(script_impl::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL, AURA_EFFECT_HANDLE_REAL);
		}
	};

public:
	spell_argaloth_fel_firestorm()
		: SpellScriptLoader("spell_argaloth_fel_firestorm")
	{
	}

	AuraScript* GetAuraScript() const
	{
		return new script_impl;
	}
};

// Consuming Darkness 88954
class spell_consuming_darkness : public SpellScriptLoader
{
public:
	spell_consuming_darkness() : SpellScriptLoader("spell_consuming_darkness") { }

	AuraScript* GetAuraScript() const
	{
		return new spell_consuming_darkness_AuraScript();
	}

	class spell_consuming_darkness_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_consuming_darkness_AuraScript)

		void OnUpdate(AuraEffectPtr aurEff)
		{
			uint32 dmg = urand(103950, 106050);
			aurEff->SetAmount(dmg / (18 - (aurEff->GetTickNumber() / 2)));
		}

		void Register()
		{
			OnEffectUpdatePeriodic += AuraEffectUpdatePeriodicFn(spell_consuming_darkness_AuraScript::OnUpdate, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
		}
	};
};

void AddSC_boss_argaloth()
{
    new boss_argaloth();
	new spell_argaloth_fel_firestorm();
	//new spell_consuming_darkness(); Fix this when the hook work again
}
