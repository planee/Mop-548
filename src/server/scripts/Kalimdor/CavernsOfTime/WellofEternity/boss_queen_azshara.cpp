#include "ScriptPCH.h"
#include "well_of_eternity.h"
#include "Unit.h"

enum ScriptedTexts
{
    SAY_AGGRO       = 0,
    SAY_INTERRUPT   = 1,
    SAY_END_1       = 2,
    SAY_END_2       = 3,
    SAY_END_3       = 4,
    SAY_WIPE        = 5,
    SAY_KILL        = 6,
    SAY_PUPPET      = 7,
    SAY_ALL         = 8,
    SAY_ADDS_1      = 9,
    SAY_ADDS_2      = 10,
    SAY_ADDS_3      = 11,
};

enum Spells
{
    SPELL_SERVANT_OF_THE_QUEEN      = 102334,
    SPELL_TOTAL_OBEDIENCE           = 103241,
    SPELL_TOTAL_OBEDIENCE_1         = 110096, // Aura Mod Stun.

    // Enchanted Magus
    SPELL_ARCANE_SHOCK              = 102463,
    SPELL_HAMMER_OF_DIVINITY_1      = 102454,
    SPELL_HAMMER_OF_DIVINITY_2      = 102454,
    SPELL_HAMMER_OF_DIVINITY_DUMMY  = 102460,
    SPELL_ARCANE_BOMB               = 102455,
    SPELL_ARCANE_BOMB_DUMMY         = 109122,
    SPELL_FIREBALL                  = 102265,
    SPELL_FIREBOMB                  = 102482,
    SPELL_BLASTWAVE                 = 102483,
    SPELL_BLADES_OF_ICE             = 102467,
    SPELL_BLADES_OF_ICE_DMG         = 102468,
    SPELL_ICE_FLING                 = 102478,
    SPELL_COLDFLAME                 = 102465,
    SPELL_COLDFLAME_DMG             = 102466,

    SPELL_PUPPET_CROSS              = 102310,
    SPELL_PUPPET_STRING_HOVER       = 102312,
    SPELL_PUPPET_STRING_DUMMY_1     = 102315,
    SPELL_PUPPET_STRING_DUMMY_2     = 102318,
    SPELL_PUPPET_STRING_DUMMY_3     = 102319,
    SPELL_PUPPET_STRING_SCRIPT_1    = 102333,
    SPELL_PUPPET_STRING_SCRIPT_2    = 102345,
};

enum Adds
{
    NPC_HAND_OF_QUEEN           = 54728,
    NPC_ENCHANTED_MAGUS_ARCANE  = 54884,
    NPC_ENCHANTED_MAGUS_FIRE    = 54882,
    NPC_ENCHANTED_MAGUS_FROST   = 54883,
    NPC_HAMMER_OF_DIVINITY_1    = 54864,
    NPC_HAMMER_OF_DIVINITY_2    = 54865,
};

enum Events
{   
    EVENT_ADDS_1                = 1,
    EVENT_ADDS_2                = 2,
    EVENT_ADDS_3                = 3,
    EVENT_SERVANT_OF_THE_QUEEN  = 4,
    EVENT_TOTAL_OBEDIENCE       = 5,
    EVENT_END                   = 6,
    EVENT_ARCANE_SHOCK          = 7,
    EVENT_ARCANE_BOMB           = 8,
    EVENT_FIREBALL              = 9,
    EVENT_FIREBOMB              = 10,
    EVENT_BLASTWAVE             = 11,
    EVENT_BLADES_OF_ICE         = 12,
    EVENT_COLDFLAME             = 13,
    EVENT_ICE_FLING             = 14,
};

enum Actions
{
    ACTION_ATTACK   = 1,
};

const Position addsPos[6] = 
{
    {3453.030029f, -5282.740234f, 230.04f, 4.45f}, // fire 1
    {3443.540039f, -5280.370117f, 230.04f, 4.66f}, // frost 1
    {3461.139893f, -5283.169922f, 230.04f, 4.31f}, // arcane 1
    {3435.590088f, -5278.350098f, 230.04f, 4.50f}, // fire 2
    {3469.729980f, -5282.430176f, 230.04f, 4.53f}, // frost 2
    {3428.43f,     -5274.59f,     230.04f, 4.20f}  // arcane 2
};

const uint32 addsEntry[6] =
{
    NPC_ENCHANTED_MAGUS_FIRE,
    NPC_ENCHANTED_MAGUS_FROST,
    NPC_ENCHANTED_MAGUS_ARCANE,
    NPC_ENCHANTED_MAGUS_FIRE,
    NPC_ENCHANTED_MAGUS_FROST,
    NPC_ENCHANTED_MAGUS_ARCANE
};


class boss_queen_azshara : public CreatureScript
{
    public:
        boss_queen_azshara() : CreatureScript("boss_queen_azshara") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_queen_azsharaAI(pCreature);
        }

        struct boss_queen_azsharaAI : public BossAI
        {
            boss_queen_azsharaAI(Creature* pCreature) : BossAI(pCreature, DATA_AZSHARA)
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
                me->setActive(true);

				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
				
			}

		
            void InitializeAI()
            {
                if (!instance || static_cast<InstanceMap*>(me->GetMap())->GetScriptId() != sObjectMgr->GetScriptId(WoEScriptName))
                    me->IsAIEnabled = false;
                else if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                _Reset();
				
                memset(addsGUIDs, 0, sizeof(addsGUIDs));

                for (uint8 i = 0; i < 6; ++i)
                    if (Creature* pAdd = me->SummonCreature(addsEntry[i], addsPos[i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
                        addsGUIDs[i] = pAdd->GetGUID();

                addsCount = 0;
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
				events.CancelEvent(EVENT_TOTAL_OBEDIENCE);
				events.CancelEvent(EVENT_SERVANT_OF_THE_QUEEN);
				
			}

            void EnterCombat(Unit* attacker)
            {
                Talk(SAY_AGGRO);
				addsCount = 0;
				events.RescheduleEvent(EVENT_ADDS_1, 10000);
				DoZoneInCombat();
                instance->SetBossState(DATA_AZSHARA, IN_PROGRESS);
			}
			
            void JustReachedHome()
            {
                Talk(SAY_WIPE);
                addsCount = 0;
            }
			
			void AttackStart(Unit* who)
            {
				if (who)
					me->Attack(who, false);
            }

            void KilledUnit(Unit* who)
            {
                if (who && who->GetTypeId() == TYPEID_PLAYER)
                    Talk(SAY_KILL);
            }
			
            void SpellHit(Unit* /*who*/, const SpellInfo* spellInfo)
            {
                if (Spell* spell = me->GetCurrentSpell(CURRENT_GENERIC_SPELL))
                    if (spellInfo->HasEffect(SPELL_EFFECT_INTERRUPT_CAST))
                    {
                        me->InterruptSpell(CURRENT_GENERIC_SPELL);
                        Talk(SAY_INTERRUPT);
                    }
            }
			
            void SummonedCreatureDies(Creature* summon, Unit* /*killer*/)
            {
                if (!me->isInCombat())
                    return;

                if (summon->GetEntry() == NPC_ENCHANTED_MAGUS_FIRE ||
                    summon->GetEntry() == NPC_ENCHANTED_MAGUS_ARCANE ||
                    summon->GetEntry() == NPC_ENCHANTED_MAGUS_FROST)
                    addsCount++;
                
				if ((addsCount == 1) || (addsCount == 3) || (addsCount == 5))
					events.ScheduleEvent(EVENT_ADDS_1, 6000);

				else if (addsCount == 6)
                {
                    events.Reset();
                    me->InterruptNonMeleeSpells(false);
                    Talk(SAY_END_1);
                    events.ScheduleEvent(EVENT_END, 6000);
                }
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
					    case EVENT_SERVANT_OF_THE_QUEEN: // SERVANT OF THE QUEEN (Scripted)
							me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
							Talk(SAY_PUPPET);
							if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
							
								DoCast(pTarget, SPELL_SERVANT_OF_THE_QUEEN);
								events.RescheduleEvent(EVENT_TOTAL_OBEDIENCE, urand(25000, 30000));
							break;
						case EVENT_TOTAL_OBEDIENCE: // TOTAL OBEDIENCE (Scripted)
							me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
							Talk(SAY_ALL);
							DoCastAOE(SPELL_TOTAL_OBEDIENCE);
							events.RescheduleEvent(EVENT_SERVANT_OF_THE_QUEEN, urand(40000, 50000));
							break;
                        case EVENT_ADDS_1:
							Talk((addsCount / 2) + 9);
							events.RescheduleEvent(EVENT_ADDS_2, 7000);
							events.ScheduleEvent(EVENT_TOTAL_OBEDIENCE, 38000);
							events.ScheduleEvent(EVENT_SERVANT_OF_THE_QUEEN, 20000);
							break;
                        case EVENT_ADDS_2:
							if (Creature* pAdd = ObjectAccessor::GetCreature(*me, addsGUIDs[addsCount]))
                            pAdd->AI()->Talk(addsCount / 2);
                            events.RescheduleEvent(EVENT_ADDS_3, 6000);
							events.ScheduleEvent(EVENT_TOTAL_OBEDIENCE, 38000);
							events.ScheduleEvent(EVENT_SERVANT_OF_THE_QUEEN, 20000);
                            break;
                        case EVENT_ADDS_3:
							me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
                            for (uint8 i = addsCount; i < (addsCount + 2); ++i)
                            {
                                if (Creature* pAdd = ObjectAccessor::GetCreature(*me, addsGUIDs[i]))
                                {
                                    pAdd->SetReactState(REACT_AGGRESSIVE);
								    DoZoneInCombat(pAdd);
                                    pAdd->AI()->DoAction(ACTION_ATTACK);
                                }
                            }
							events.ScheduleEvent(EVENT_SERVANT_OF_THE_QUEEN, 20000);
							events.ScheduleEvent(EVENT_TOTAL_OBEDIENCE, 35000);
                            break;
                        case EVENT_END:
							events.CancelEvent(EVENT_SERVANT_OF_THE_QUEEN);
							events.CancelEvent(EVENT_TOTAL_OBEDIENCE);
						    me->SummonGameObject(210025, 3465.447f, -5238.09f, 230.575f, 4.54f, 4.54f, 4.54f, 4.54f, 4.54f, 20000);
                            instance->DoKilledMonsterKredit(QUEST_THE_VAINGLORIOUS, 54853, 0);
							instance->SetBossState(DATA_AZSHARA, DONE);
                            instance->DoRespawnGameObject(instance->GetData64(GO_ROYAL_CACHE), DAY);
							me->DespawnOrUnsummon();
                            break;
                        
                        default:
                            break;
                    }
                }
            }
        private:
            EventMap events;
            uint8 phase;
            uint64 addsGUIDs[6];
            uint8 addsCount;

     };
};

class npc_queen_azshara_enchanted_magus : public CreatureScript
{
    public:

        npc_queen_azshara_enchanted_magus() : CreatureScript("npc_queen_azshara_enchanted_magus") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_queen_azshara_enchanted_magusAI(pCreature);
        }

        struct npc_queen_azshara_enchanted_magusAI : public ScriptedAI
        {
            npc_queen_azshara_enchanted_magusAI(Creature* pCreature) : ScriptedAI(pCreature) { }

			bool isIcying;
            
			void Reset()
            {
                events.Reset();
                me->SetReactState(REACT_PASSIVE);
			}

			void DamageDealt(Unit* target, uint32 damage, DamageEffectType /*damagetype*/)
			{
				if (isIcying)
				{
					if (!me->HasInArc(M_PI / 6, target))
						damage = 0;
				}
			}

            void DoAction(const int32 action)
            {
                if (action == ACTION_ATTACK)
                {
                    if (me->GetEntry() == NPC_ENCHANTED_MAGUS_FIRE)
                    {
                        events.ScheduleEvent(EVENT_FIREBALL, 1000);
                        events.ScheduleEvent(EVENT_FIREBOMB, urand(10000, 15000));
                        events.ScheduleEvent(EVENT_BLASTWAVE, urand(10000, 20000));
                    }
                    else if (me->GetEntry() == NPC_ENCHANTED_MAGUS_FROST)
                    {
						
                        events.ScheduleEvent(EVENT_BLADES_OF_ICE, urand(5000, 10000));
                        events.ScheduleEvent(EVENT_COLDFLAME, urand(12000, 20000));
                        events.ScheduleEvent(EVENT_ICE_FLING, urand(2000, 15000));
                    }
                    else if (me->GetEntry() == NPC_ENCHANTED_MAGUS_ARCANE)
                    {
                        events.ScheduleEvent(EVENT_ARCANE_SHOCK, urand(10000, 15000));
                        events.ScheduleEvent(EVENT_ARCANE_BOMB, urand(5000, 10000));
                    }
                }
            }
        
          void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;
				
				if (isIcying)
				{
					if (!me->IsNonMeleeSpellCasted(false))
						isIcying = false;
					else
						return;
				}


                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_FIREBALL:
                            DoCastVictim(SPELL_FIREBALL);
                            events.ScheduleEvent(EVENT_FIREBALL, 3000);
                            break;
                        case EVENT_FIREBOMB:
                            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                                DoCast(pTarget, SPELL_FIREBOMB);
                            events.ScheduleEvent(EVENT_FIREBOMB, urand(15000, 20000));
                            break;
                        case EVENT_BLASTWAVE:
                            DoCastAOE(SPELL_BLASTWAVE);
                            events.ScheduleEvent(EVENT_BLASTWAVE, urand(15000, 20000));
                            break;
                        case EVENT_ICE_FLING:
                            DoCastAOE(SPELL_ICE_FLING);
                            events.ScheduleEvent(EVENT_ICE_FLING, urand(10000, 20000));
                            break;
                        case EVENT_BLADES_OF_ICE:
							if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
							DoCast(pTarget, SPELL_BLADES_OF_ICE);
                            events.ScheduleEvent(EVENT_BLADES_OF_ICE, urand(12000, 20000));
                            break;
                        case EVENT_COLDFLAME:
							if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
							{
								for (uint8 i = 0; i < 7; i++)
								{
									float x, y, z;
									me->GetClosePoint(x, y, z, me->GetObjectSize() / 3, 1.0f + (4 * i));
								}
								DoCast(target, SPELL_COLDFLAME);
								DoCast(target, SPELL_COLDFLAME_DMG, true);
								isIcying = true;
							}
							events.ScheduleEvent(EVENT_COLDFLAME, urand(19000, 23000));
							break;
                        case EVENT_ARCANE_SHOCK:
                            me->StopMoving();
                            DoCast(me, SPELL_ARCANE_SHOCK);
                            events.ScheduleEvent(EVENT_ARCANE_SHOCK, urand(12000, 20000));
                            break;
                        case EVENT_ARCANE_BOMB:
                        {
                            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                            {
                              DoCastAOE(SPELL_ARCANE_BOMB, true);
                            }
                            events.ScheduleEvent(EVENT_ARCANE_BOMB, urand(15000, 20000));
                            break;
                        }
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

        private:
            EventMap events;
        };
};


class spell_servant_of_the_queen : public SpellScriptLoader
{
public:
	spell_servant_of_the_queen() : SpellScriptLoader("spell_servant_of_the_queen") { }

	class spell_servant_of_the_queen_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_servant_of_the_queen_SpellScript);

		void HandleAfterHit()
		{
			if (GetCaster() && GetHitUnit())
			{
				// no real reason to create another spellscript for this purpose
				GetCaster()->AddAura(SPELL_PUPPET_STRING_HOVER, GetHitPlayer());
				GetCaster()->AddAura(SPELL_PUPPET_CROSS, GetHitPlayer());
				GetCaster()->AddAura(SPELL_PUPPET_STRING_DUMMY_3, GetHitPlayer());
			}
		}

		void Register()
		{
			AfterHit += SpellHitFn(spell_servant_of_the_queen_SpellScript::HandleAfterHit);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_servant_of_the_queen_SpellScript();
	}
};

class spell_total_obedience : public SpellScriptLoader
{
public:
	spell_total_obedience() : SpellScriptLoader("spell_total_obedience") { }

	class spell_total_obedience_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_total_obedience_SpellScript);

		void HandleAfterHit()
		{
			if (GetCaster() && GetHitUnit())
			{
				// no real reason to create another spellscript for this purpose
				GetCaster()->AddAura(SPELL_PUPPET_STRING_HOVER, GetHitPlayer());
				GetCaster()->AddAura(SPELL_PUPPET_CROSS, GetHitPlayer());
				GetCaster()->AddAura(SPELL_PUPPET_STRING_DUMMY_3, GetHitPlayer());
			}
		}

		void Register()
		{
			AfterHit += SpellHitFn(spell_total_obedience_SpellScript::HandleAfterHit);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_total_obedience_SpellScript();
	}
};
void AddSC_boss_queen_azshara()
{
    new boss_queen_azshara();
    new npc_queen_azshara_enchanted_magus();
	new spell_servant_of_the_queen();
	new spell_total_obedience();
}