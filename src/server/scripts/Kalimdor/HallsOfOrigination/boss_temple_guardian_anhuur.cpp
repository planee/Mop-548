#include "ScriptPCH.h"
#include "Spell.h"
#include "halls_of_origination.h"

enum ScriptTexts
{
    SAY_DEATH       = 0,
    SAY_AGGRO       = 1,
    SAY_EVENT       = 2,
    SAY_KILL        = 3, 
};

enum Quotes
{
	SAY_SHIELD,
	EMOTE_SHIELD,
	EMOTE_SHIELD_REMOVED
};

enum Spells
{
    SPELL_DIVINE_RECKONING       = 75592,
	SPELL_DIVINE_RECKONING_LEECH = 75591,
    SPELL_REVERBERATING_HYMN     = 75322,
    SPELL_SEARING_FLAME          = 75115,
    SPELL_SEARING_FLAME_SUM      = 75114,
    SPELL_SEARING_FLAME_DMG      = 75116,
    SPELL_SHIELD_OF_LIGHT        = 74938,
	SPELL_SHIELD_VISUAL          = 74930,
	SPELL_BEAM_LEFT              = 83697, 
	SPELL_BEAM_RIGHT             = 83698, 
    SPELL_POISON_TIPPED_FANGS    = 74538,
	SPELL_TELEPORT               = 74969, // Teleport on phase switch
	SPELL_SEARING_FLAME_2        = 75194,
};

enum Events
{
    EVENT_SEARING_FLAME         = 1,
    EVENT_DIVINE_RECKONING      = 2,
    EVENT_POISON_TIPPED_FANGS   = 3,
    EVENT_ACHIEVEMENT           = 4,
    EVENT_SHIELD_OF_LIGHT       = 5,
    EVENT_REVERBERATING_HYMN    = 6,
};

enum Actions
{
    ACTION_ACTIVATE = 1,
};

enum Points
{
    POINT_CENTER = 1,
};

enum Phases
{
	PHASE_NORMAL = 1,
	PHASE_SHIELDED = 2,
};

enum MiscData
{
	DATA_SHIELD = 1,
};

enum Adds
{
    NPC_CAVE_IN         = 40183,
    NPC_PIT_SNAKE       = 39444,
    NPC_SEARING_FLAME   = 40283,

    GO_BEACON_LEFT      = 203133,
    GO_BEACON_RIGHT     = 203136,
};

const Position SpawnPosition[] =
{
    {-654.277f, 361.118f, 52.9508f, 5.86241f},
    {-670.102f, 350.896f, 54.1803f, 2.53073f},
    {-668.896f, 326.048f, 53.2267f, 3.36574f},
    {-618.875f, 344.237f, 52.95f, 0.194356f},
    {-661.667f, 338.78f, 53.0333f, 2.53073f},
    {-607.836f, 348.586f, 53.4939f, 1.0558f},
    {-656.452f, 376.388f, 53.9709f, 1.4525f},
    {-652.762f, 370.634f, 52.9503f, 2.5221f},
    {-682.656f, 343.953f, 53.7329f, 2.53073f},
    {-658.877f, 309.077f, 53.6711f, 0.595064f},
    {-619.399f, 309.049f, 53.4247f, 4.63496f},
    {-612.648f, 318.365f, 53.777f, 3.53434f},
    {-616.398f, 345.109f, 53.0165f, 2.53073f},
    {-681.394f, 342.813f, 53.8955f, 6.24987f},
    {-668.843f, 351.407f, 54.1813f, 5.5293f},
    {-672.797f, 317.175f, 52.9636f, 5.51166f},
    {-631.834f, 375.502f, 55.7079f, 0.738231f},
    {-617.027f, 360.071f, 52.9816f, 2.00725f},
    {-623.891f, 361.178f, 52.9334f, 5.61183f},
    {-614.988f, 331.613f, 52.9533f, 2.91186f},
    {-662.902f, 341.463f, 52.9502f, 2.84307f}
};

const Position bosspos = {-640.527f, 334.855f, 78.345f, 1.54f};

class boss_temple_guardian_anhuur : public CreatureScript
{
    public:
        boss_temple_guardian_anhuur() : CreatureScript("boss_temple_guardian_anhuur") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_temple_guardian_anhuurAI(pCreature);
        }

        struct boss_temple_guardian_anhuurAI : public BossAI
        {
            boss_temple_guardian_anhuurAI(Creature* pCreature) : BossAI(pCreature, DATA_TEMPLE_GUARDIAN_ANHUUR)
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
            uint8 beacons;
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

                me->SetReactState(REACT_AGGRESSIVE);
                phase = 0;
                beacons = 0;
                achieve = false;
				RemoveSummons();
				shielded = false;
				stage = 0;
				targetGUID = 0;
				SetLevers(false);
            }

            void KilledUnit(Unit* /*Killed*/)
            {
                Talk(SAY_KILL);
            }

            void JustDied(Unit* /*Kill*/)
            {
                _JustDied();
				RemoveSummons();
                Talk(SAY_DEATH);
				//Achievement I Hate That Song, THAT IS A HACK, FIX THE LINE OF ACHIVEMENT CRITERIA IN THE FUTURE
				Map* map = me->GetMap();
				if (!map)
					return;
				if (achieve = true && map->GetDifficulty() == DUNGEON_DIFFICULTY_HEROIC)
					instance->DoCompleteAchievement(5293);
            }

            void EnterCombat(Unit* /*Ent*/)
            {
                events.ScheduleEvent(EVENT_DIVINE_RECKONING, urand(3000, 10000));
                events.ScheduleEvent(EVENT_SEARING_FLAME, urand(2000, 7000));
                Talk(SAY_AGGRO);
                DoZoneInCombat();
                instance->SetBossState(DATA_TEMPLE_GUARDIAN_ANHUUR, IN_PROGRESS);
            }

            void JustReachedHome()
		    {
			    _JustReachedHome();
		    }

            bool HasAchieved()
            {
                return achieve;
            }

           void DoAction(const int32 action)
            {
                if (action == ACTION_ACTIVATE)
                {
                    beacons++;
                    if (beacons == 2)
                    {
                        me->RemoveAurasDueToSpell(SPELL_SHIELD_OF_LIGHT);
						me->SetReactState(REACT_AGGRESSIVE);
						me->CastStop(SPELL_REVERBERATING_HYMN);
						events.ScheduleEvent(EVENT_DIVINE_RECKONING, urand(3000, 10000));
						events.ScheduleEvent(EVENT_SEARING_FLAME, urand(2000, 7000));
                        beacons = 0;
						DespawnSnake(NPC_PIT_SNAKE);
						SetLevers(false);
                    }
                }
            }
			
		   void DespawnSnake(uint32 entry)

		   {
			   std::list<Creature*> creatures;
			   GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);
			   if (creatures.empty())
				   return;
			   for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
				   (*iter)->DespawnOrUnsummon();
		   }

			void SetLevers(bool active)
			{
				if (GameObject * lever1 = me->FindNearestGameObject(GO_BEACON_LEFT, 100.0f))
				{
					if (active)
						lever1->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
					else
						lever1->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
				}

				if (GameObject * lever2 = me->FindNearestGameObject(GO_BEACON_RIGHT, 100.0f))
				{
					if (active)
						lever2->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
					else
						lever2->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
				}
			}

			void DamageTaken(Unit * done_by, uint32 &damage)
			{
				if (shielded) // to prevent possible exploits
				{
					if (me->HasAura(SPELL_SHIELD_OF_LIGHT))
						damage = 0;
					else
					{
						events.SetPhase(PHASE_NORMAL);
						me->CastStop(SPELL_REVERBERATING_HYMN);
						me->GetMotionMaster()->MoveChase(me->getVictim() ? me->getVictim() : done_by);
						shielded = false;
					}
				}
				
				if (stage >= 2)
					return;

				if (me->GetHealthPct() <= (stage ? 33.0f : 66.0f))
				{
					++stage;

					Talk(SAY_SHIELD);
					Talk(EMOTE_SHIELD);
					events.Reset();
					me->SetReactState(REACT_PASSIVE);
					me->GetMotionMaster()->Clear();
					me->GetMotionMaster()->MoveIdle();
					me->AttackStop();
					DoCast(me, SPELL_TELEPORT, true);
					events.SetPhase(PHASE_SHIELDED);
					events.CancelEvent(EVENT_DIVINE_RECKONING);
					events.CancelEvent(EVENT_SEARING_FLAME);
					events.ScheduleEvent(EVENT_SHIELD_OF_LIGHT, 1000);
					for (uint32 i = 0; i < 21; ++i)
						me->SummonCreature(NPC_PIT_SNAKE, SpawnPosition[i], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
					if (!achieve)
					{
						achieve = true;
						events.ScheduleEvent(EVENT_ACHIEVEMENT, 15000);
					}
					SetLevers(true);

					GameObject * lever2 = me->FindNearestGameObject(GO_BEACON_RIGHT, 100.0f);
						lever2->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
					    lever2->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
						lever2->setActive(true);
					GameObject * lever1 = me->FindNearestGameObject(GO_BEACON_LEFT, 100.0f);
					    lever1->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
					    lever1->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
						lever1->setActive(true);
					shielded = true;

					if (Creature *light1 = me->SummonCreature(NPC_CAVE_IN, -603.465f, 334.38f, 65.4f, 3.12f, TEMPSUMMON_CORPSE_DESPAWN, 1000))
						light1->CastSpell(me, SPELL_BEAM_LEFT, false);

					if (Creature *light2 = me->SummonCreature(NPC_CAVE_IN, -678.132f, 334.212f, 64.9f, 0.24f, TEMPSUMMON_CORPSE_DESPAWN, 1000))
						light2->CastSpell(me, SPELL_BEAM_RIGHT, false);
				}
			}

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                if (summon->GetEntry() != NPC_PIT_SNAKE)
                    if (me->isInCombat())
                        DoZoneInCombat(summon);
					if (Player * player = me->GetPlayer(*me, targetGUID))
					{
						if (Creature * stalker = player->FindNearestCreature(NPC_SEARING_FLAME, 100.0f))
							stalker->CastSpell(stalker, SPELL_SEARING_FLAME, true, NULL, NULL, me->GetGUID());
						summon->setFaction(14);
						targetGUID = 0;
					}
            }

			void RemoveSummons()
			{
				if (SummonList.empty())
					return;

				for (std::list<uint64>::const_iterator itr = SummonList.begin(); itr != SummonList.end(); ++itr)
				{
					if (Creature* pTemp = Unit::GetCreature(*me, *itr))
					if (pTemp)
						pTemp->DisappearAndDie();
				}
				SummonList.clear();
			}

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;
                events.Update(diff);

			    while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SHIELD_OF_LIGHT:
							DoCast(me, SPELL_SHIELD_VISUAL, true);
                            DoCast(me, SPELL_SHIELD_OF_LIGHT, true);
                            events.ScheduleEvent(EVENT_REVERBERATING_HYMN, 1000);
                            break;
                       case EVENT_REVERBERATING_HYMN:
						   me->SetReactState(REACT_PASSIVE);
						   DoCast(me, SPELL_REVERBERATING_HYMN);
						   break;
                        case EVENT_ACHIEVEMENT:
							if (me->HasAura(SPELL_REVERBERATING_HYMN))
                            achieve = false;
                            break;
                        case EVENT_DIVINE_RECKONING:
							if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                DoCast(pTarget, SPELL_DIVINE_RECKONING);
                            events.ScheduleEvent(EVENT_DIVINE_RECKONING, urand(15000, 17000));
                            break;
                        case EVENT_SEARING_FLAME:
						{
							Unit * target = SelectTarget(SELECT_TARGET_RANDOM, 1, 50.0f, true);
							if (!target)
							target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true);
							if (target)
							   {
								targetGUID = target->GetGUID();
								DoCast(target, SPELL_SEARING_FLAME, true);
							   }
							events.ScheduleEvent(EVENT_SEARING_FLAME, urand(10000, 15000));
						}
							break;
                    }
                }

                DoMeleeAttackIfReady();
            }
			private:
			uint64 targetGUID;
			bool shielded;
			int8 stage;
			std::list<uint64> SummonList;
	
        };
};

class npc_pit_snake : public CreatureScript
{
    public:
        npc_pit_snake() : CreatureScript("npc_pit_snake") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_pit_snakeAI(pCreature);
        }

        struct npc_pit_snakeAI : public ScriptedAI
        {
            npc_pit_snakeAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* who)
            {
                events.ScheduleEvent(EVENT_POISON_TIPPED_FANGS, urand(2000, 8000));
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

			    while (uint32 eventId = events.ExecuteEvent())
                {
					switch (eventId)
					{
					case EVENT_POISON_TIPPED_FANGS:
						switch (eventId)
						{
						case EVENT_POISON_TIPPED_FANGS:
							if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
							{
								if (AuraPtr aur = pTarget->GetAura(SPELL_POISON_TIPPED_FANGS))
									aur->ModStackAmount(1);
								else
									DoCast(pTarget, SPELL_POISON_TIPPED_FANGS);
							}
							events.ScheduleEvent(EVENT_POISON_TIPPED_FANGS, urand(5000, 10000));
							break;
						}
					}
                }

                DoMeleeAttackIfReady();
            }
        };
};

class go_beacon_of_light : public GameObjectScript
{
public:
    go_beacon_of_light() : GameObjectScript("go_beacon_of_light") { }

    bool OnGossipHello(Player* pPlayer, GameObject* pGO)
    {
        if (Creature* pAnhuur = pGO->FindNearestCreature(NPC_TEMPLE_GUARDIAN_ANHUUR, 100.0f))
            pAnhuur->GetAI()->DoAction(ACTION_ACTIVATE);
        pGO->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
        return false;
    }
};

typedef boss_temple_guardian_anhuur::boss_temple_guardian_anhuurAI AnhuurAI;

class achievement_i_hate_that_song : public AchievementCriteriaScript
{
    public:
        achievement_i_hate_that_song() : AchievementCriteriaScript("achievement_i_hate_that_song") { }

        bool OnCheck(Player* source, Unit* target)
        {
            if (!target)
                return false;

            if (AnhuurAI* anhuurAI = CAST_AI(AnhuurAI, target->GetAI()))
                return anhuurAI->HasAchieved();

            return false;
        }
};

class spell_disable_beacon_beams : public SpellScriptLoader
{
public:
	spell_disable_beacon_beams() : SpellScriptLoader("spell_disable_beacon_beams") {}

	class spell_disable_beacon_beams_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_disable_beacon_beams_SpellScript)
		void HandleScript(SpellEffIndex /*effIndex*/)
		{
			if (Unit * caster = GetCaster())
			{
				if (Creature * boss = caster->FindNearestCreature(NPC_TEMPLE_GUARDIAN_ANHUUR, 100.0f))
					boss->AI()->SetData(DATA_SHIELD, GetSpellInfo()->Id);
			}
		}

		void Register()
		{
			OnEffectHitTarget += SpellEffectFn(spell_disable_beacon_beams_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_disable_beacon_beams_SpellScript();
	}
};

class spell_anhuur_divine_reckoning : public SpellScriptLoader
{
public:
	spell_anhuur_divine_reckoning() : SpellScriptLoader("spell_anhuur_divine_reckoning") { }

	class spell_anhuur_divine_reckoning_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_anhuur_divine_reckoning_AuraScript);

		void OnPeriodic(constAuraEffectPtr aurEff)
		{
				if (Unit* caster = GetCaster())
			{
				Unit* target = GetTarget();
				CustomSpellValues values;
				values.AddSpellMod(SPELLVALUE_BASE_POINT0, aurEff->GetAmount());
				if (GetId() == SPELL_DIVINE_RECKONING && GetDuration() == 0)
					caster->CastCustomSpell(SPELL_DIVINE_RECKONING_LEECH, values, target);
			}
		}

		void Register() override
		{
			OnEffectPeriodic += AuraEffectPeriodicFn(spell_anhuur_divine_reckoning_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
		}
	};

	AuraScript* GetAuraScript() const override
	{
		return new spell_anhuur_divine_reckoning_AuraScript();
	}
};

void AddSC_boss_temple_guardian_anhuur()
{
    new boss_temple_guardian_anhuur();
    new npc_pit_snake();
    new go_beacon_of_light();
    new achievement_i_hate_that_song();
	new spell_disable_beacon_beams();
	new spell_anhuur_divine_reckoning();
}
