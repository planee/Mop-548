
#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "mechanar.h"



enum Says
{
	SAY_AGGRO = 0,
	SAY_HAMMER = 1,
	SAY_SLAY = 2,
	SAY_DEATH = 3,
	EMOTE_HAMMER = 4
};

enum Spellss
{
	SPELL_SHADOW_POWER = 35322,
	H_SPELL_SHADOW_POWER = 39193,
	SPELL_HAMMER_PUNCH = 35326,
	SPELL_JACKHAMMER = 35327,
	H_SPELL_JACKHAMMER = 39194,
	SPELL_STREAM_OF_MACHINE_FLUID = 35311
};

enum Events
{
	EVENT_STREAM_OF_MACHINE_FLUID = 1,
	EVENT_JACKHAMMER = 2,
	EVENT_SHADOW_POWER = 3
};


enum mob_eventns
{
	EVENT_DMAAGEBAJO,
	EVENT_DMAGEMEDIO,
	EVENT_DAMAGEALTO,
	EVENT_RESET,
	DATA_BETHTILAC = 1
};
enum Spells
{
	SPELL_DMAAGEBAJO = 35049,
	SPELL_MEDIO = 35056, //Normal dugeon 
	SPELL_ALTO = 38923 // Heroic

};

class mob_merchande : public CreatureScript
{
public:
	mob_merchande() : CreatureScript("mob_merchande") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_merchandeAI(creature);
	}

	struct mob_merchandeAI : public BossAI
	{
		mob_merchandeAI(Creature* pCreature) : BossAI(pCreature, DATA_BETHTILAC)
		{
			pInstance = (InstanceScript*)pCreature->GetInstanceScript();
		}


		InstanceScript* pInstance;
		std::set<uint64> _atakers;

		void Reset()
		{

			events.CancelEvent(EVENT_DMAAGEBAJO);
			events.CancelEvent(EVENT_DMAGEMEDIO);
			events.CancelEvent(EVENT_DAMAGEALTO);
			_atakers.clear();

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

			if (me->HealthBelowPctDamaged(70, damage))
				events.ScheduleEvent(EVENT_DMAAGEBAJO, 1000);

			if (me->HealthBelowPctDamaged(50, damage))
				events.ScheduleEvent(EVENT_DMAGEMEDIO, irand(4000, 6000));


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
				case EVENT_DMAAGEBAJO:
					if (Unit* victim = me->getVictim())
						me->CastSpell(victim, SPELL_DMAAGEBAJO, true);
					break;
				case EVENT_DMAGEMEDIO:
					if (Unit* victim = me->getVictim())
					{
						if (pInstance)
						{
							if (IsHeroic())
								me->CastSpell(victim, SPELL_ALTO, true);

							else
								me->CastSpell(victim, SPELL_MEDIO, true);

						}
					}
					break;
				default:
					break;
				}

			}

			DoMeleeAttackIfReady();
		}
	private: EventMap events;
	};

};

void AddSC_mechanar()
{
	new mob_merchande();    
}

