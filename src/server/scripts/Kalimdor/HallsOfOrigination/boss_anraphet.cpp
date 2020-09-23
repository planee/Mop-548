#include "ScriptPCH.h"
#include "halls_of_origination.h"

enum ScriptTexts
{
    SAY_DEATH                  = 0,
    SAY_INTRO                  = 1,
    SAY_KILL                   = 2,
    SAY_ALPHA                  = 3,
    SAY_OMEGA                  = 4,
    SAY_AGGRO                  = 5,
};

enum Spells
{
	SPELL_ALPHA_BEAMS           = 76184,
    SPELL_ALPHA_BEAMS_AOE       = 76904, 
    SPELL_ALPHA_BEAM            = 76912,
	SPELL_ALPHA_BEAM_H          = 91205,
    SPELL_ALPHA_BEAM_DMG        = 76956, 
	SPELL_CRUMBLING_RUIN        = 75609, 
    SPELL_CRUMBLING_RUIN_H      = 91206, 
    SPELL_DESTRUCTION_PROTOCOL  = 77437,
    SPELL_NEMESIS_STRIKE        = 75604,
    SPELL_OMEGA_STANCE          = 75622,
};

enum Events
{
    EVENT_ALPHA_BEAMS          = 1,
    EVENT_CRUMBLING_RUIN       = 2,
    EVENT_DESTRUCTION_PROTOCOL = 3,
    EVENT_NEMESIS_STRIKE       = 4,
    EVENT_INTRO                = 5,
	EVENT_ALPHA_BEAMS_END      = 6,  
	EVENT_OMEGA_STANCE         = 7, 
};

enum Phases
{
	PHASE_NORMAL = 1,
	PHASE_ALPHA_BEAMS,
	PHASE_OMEGA_STANCE
};

enum Adds
{
    NPC_ALPHA_BEAM      = 41144,
    NPC_OMEGA_STANCE    = 41194, // 77137 77117 
};

class boss_anraphet : public CreatureScript
{
    public:
        boss_anraphet() : CreatureScript("boss_anraphet") {}
 
        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_anraphetAI(pCreature);
        }

        struct boss_anraphetAI : public BossAI
        {
            boss_anraphetAI(Creature* pCreature) : BossAI(pCreature, DATA_EARTHRAGER_PTAH)
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
                //me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
            }

            uint8 spells;

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
                spells = 0;
				Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
				if (!PlayerList.isEmpty())
				{
					for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
					{
						Player *player = i->getSource();
						if (player->HasAura(SPELL_CRUMBLING_RUIN) || (SPELL_CRUMBLING_RUIN_H))
						{
							player->RemoveAura(SPELL_CRUMBLING_RUIN);
							player->RemoveAura(SPELL_CRUMBLING_RUIN_H);
						}
					}
				}
            }

            void EnterCombat(Unit * who)
            {
                Talk(SAY_AGGRO);

                events.ScheduleEvent(EVENT_ALPHA_BEAMS, 10000);
                events.ScheduleEvent(EVENT_NEMESIS_STRIKE, urand(3000, 7000));
				events.ScheduleEvent(EVENT_OMEGA_STANCE, 15000);
               
                DoZoneInCombat();
                instance->SetBossState(DATA_ANRAPHET, IN_PROGRESS);
            }

            void JustDied(Unit* /*killer*/)
            {
                _JustDied();
                Talk(SAY_DEATH);
				Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
				if (!PlayerList.isEmpty())
				{
					for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
					{
						Player *player = i->getSource();
						if (player->HasAura(SPELL_CRUMBLING_RUIN) || (SPELL_CRUMBLING_RUIN_H))
						{
							player->RemoveAura(SPELL_CRUMBLING_RUIN);
							player->RemoveAura(SPELL_CRUMBLING_RUIN_H);
						}
					}
				}
            }
            
            void KilledUnit(Unit* who)
            {
                Talk(SAY_KILL);
            }

            void DoAction(const int32 action)
            {
                if (action == 1)
                {
                    Talk(SAY_INTRO);
                    me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
                    me->SetHomePosition(-203.93f, 368.71f, 75.92f, me->GetOrientation());
                    me->GetMotionMaster()->MovePoint(0, -203.93f, 368.71f, 75.92f);
                }
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
                    switch(eventId)
                    {
                    		case EVENT_ALPHA_BEAMS:
							Talk(SAY_ALPHA);
							events.SetPhase(PHASE_ALPHA_BEAMS);
							me->SetReactState(REACT_PASSIVE);
							me->SetUInt64Value(UNIT_FIELD_TARGET, 0);
							me->GetMotionMaster()->Clear();
							me->GetMotionMaster()->MoveIdle();
							DoCast(SPELL_ALPHA_BEAMS);
							events.DelayEvents(13000, 1);
							events.ScheduleEvent(EVENT_ALPHA_BEAMS_END, 13000, 0, PHASE_ALPHA_BEAMS);
							events.ScheduleEvent(EVENT_CRUMBLING_RUIN, 1000);
							break;
						case EVENT_ALPHA_BEAMS_END:
							events.SetPhase(PHASE_NORMAL);
							me->SetReactState(REACT_AGGRESSIVE);
							if (Unit * victim = me->getVictim())
							{
								me->SetUInt64Value(UNIT_FIELD_TARGET, victim->GetGUID());
								DoStartMovement(victim);
							}
							events.ScheduleEvent(EVENT_ALPHA_BEAMS, urand(15000, 25000), 1);
							break;
						case EVENT_CRUMBLING_RUIN:
							DoCast(me, SPELL_CRUMBLING_RUIN, true);
							break;
						case EVENT_NEMESIS_STRIKE:
							DoCastVictim(SPELL_NEMESIS_STRIKE, true);
							events.ScheduleEvent(EVENT_NEMESIS_STRIKE, urand(12000, 15000), 1);
							break;
						case EVENT_OMEGA_STANCE:
							Talk(SAY_OMEGA);
							DoCast(me, SPELL_OMEGA_STANCE);
							events.ScheduleEvent(EVENT_OMEGA_STANCE, urand(25000, 30000), 1);
							events.ScheduleEvent(EVENT_CRUMBLING_RUIN, 1000);
							break;
						default:
							break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class npc_alpha_beam : public CreatureScript
{
    public:
        npc_alpha_beam() : CreatureScript("npc_alpha_beam") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_alpha_beamAI(creature);
        }

        struct npc_alpha_beamAI : public Scripted_NoMovementAI
        {
            npc_alpha_beamAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
            {
				pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			}

			void Reset()
			{
				if (IsHeroic())
					DoCast(me, SPELL_ALPHA_BEAM_H);
				else
					DoCast(me, SPELL_ALPHA_BEAM);
			}
			
			void UpdateAI(const uint32 diff)
			{				
			}
        };
};

class spell_anraphet_alpha_beams : public SpellScriptLoader
{
public:
	spell_anraphet_alpha_beams() : SpellScriptLoader("spell_anraphet_alpha_beams") { }

	class spell_anraphet_alpha_beams_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_anraphet_alpha_beams_SpellScript);

		void FilterTargets(std::list<WorldObject*>& targets)
		{
			if (targets.empty())
				return;

			WorldObject* target = WoWSource::Containers::SelectRandomContainerElement(targets);
			targets.clear();
			targets.push_back(target);
		}

		void Register() override
		{
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_anraphet_alpha_beams_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
		}
	};

	SpellScript* GetSpellScript() const override
	{
		return new spell_anraphet_alpha_beams_SpellScript();
	}
};

void AddSC_boss_anraphet()
{
    new boss_anraphet();
    new npc_alpha_beam();
	new spell_anraphet_alpha_beams();
}
