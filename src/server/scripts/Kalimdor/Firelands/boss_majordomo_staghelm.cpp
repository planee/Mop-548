/*
* Copyright (C) 2014-2017 RoG_WoW Source  <http://wow.rog.snet/>
*
* Dont Share The SourceCode
*
*/

#include "ScriptPCH.h"
#include "firelands.h"

enum Spells
{
    // Majordormo Staghelm
    SPELL_BERSERK                   = 26662, // Increases the caster's attack and movement speeds by 150% and all damage it deals by 500%. Also grants immunity to Taunt effects
    SPELL_CAT_FORM                  = 98374, // Fandral transforms into a cat when his enemies are spread out.
    SPELL_SCORPION_FORM             = 98379, // Fandral transforms into a scorpion when 7 or more of his enemies are clustered together in 10 player raids, and 18 or more in 25 player raids.
    SPELL_FURY                      = 97235, // Fandral's fury fuels his flames, increasing the damage he inflicts with Leaping Flames and Flame Scythe by 8% per application. Stacks.
    SPELL_ADRENALINE                = 97238, // Increases the caster's energy regeneration rate by 20% per application. Stacks.
    SPELL_FIERY_CYCLONE             = 98443, // Tosses all enemy targets into the air, preventing all action but making them invulnerable for 3 sec.
    SPELL_SEARING_SEEDS             = 98450, // Implants fiery seeds in the caster's enemies. Each seed grows at a different rate. When fully grown the seeds explode, inflicting 63750 Fire damage to targets within 12 yards.
    SPELL_SEARING_SEEDS_EXPLOSION   = 98620, // should be triggered when Searing Seeds removes
    SPELL_BURNING_ORBS              = 98451, // Summons Burning Orbs to attack the caster's enemies.
    SPELL_BURNING_ORBS_SUMMON       = 98565, // 10man - 2, 25man - 5
    SPELL_FLAME_SCYTHE              = 98474, // Inflicts Fire damage in front of the caster. Damage is split equally among targets hit.


	SPELL_FLAME_SCYTE_10N = 98474,
	SPELL_FLAME_SCYTE_25N = 100212,
	SPELL_FLAME_SCYTE_10H = 100213,
	SPELL_FLAME_SCYTE_25H = 100214,

    SPELL_LEAPING_FLAMES            = 98476, // Leaps at an enemy, inflicting 26036 to 29213 Fire damage in a small area and creating a Spirit of the Flame.
    SPELL_LEAPING_FLAMES_SUMMON     = 101222, // Summon Spirit of the Flame
    SPELL_LEAPING_FLAMES_PERSISTENT = 98535, // Fandral lands in a blaze of glory, igniting the ground at his destination and causing it to burn enemy enemy units for 26036 to 29213 Fire damage every 0.5 sec

	SPELL_LEAP_FLAMES_DMG_10N = 98535,
	SPELL_LEAP_FLAMES_DMG_25N = 100206,
	SPELL_LEAP_FLAMES_DMG_10H = 100207,
	SPELL_LEAP_FLAMES_DMG_25H = 100208,

    // Burning Orb
    SPELL_BURNING_ORB_PERIODIC      = 98583, // Visual. Inflicts 7650 Fire damage every 2 sec. Stacks.

    SPELL_CONCENTRATION             = 98256,
    SPELL_CONCENTRATION_AURA        = 98229,
    SPELL_LEGENDARY_CONCENTRATION   = 98245,
    SPELL_EPIC_CONCENTRATION        = 98252,
    SPELL_RARE_CONCENTRATION        = 98253,
    SPELL_UNCOMMON_CONCENTRATION    = 98254,

	SPELL_ZERO_POWER = 72242,
};

enum Events
{
	EVENT_BERSERK = 1,
	EVENT_INTRO_1 = 2,
	EVENT_INTRO_2 = 3,
	EVENT_INTRO_3 = 4,
	EVENT_SUMMON_ORBS = 5,
	EVENT_CHECK_FORM = 6,
	EVENT_ENERGY_REGEN = 7,

	// Spirit of the Flame
	EVENT_JUMP_TARGET = 8,

	// Burning Orb
	EVENT_ORB_DAMAGE = 9,

	EVENT_SAY = 10
};

enum MajordomoPhase
{
	PHASE_NONE = 0, PHASE_DRUID = 1, PHASE_CAT = 2, PHASE_SCORPION = 3
};

enum Yells
{

	SAY_INTRO_1 = 0,
	SAY_INTRO_2 = 1,
	SAY_INTRO_3 = 2,
	SAY_AGGRO = 3,
	SAY_ON_DEAD = 4,
	SAY_ON_KILL = 5,
	SAY_SCORPION = 6,
	SAY_CAT = 7,
	SAY_DRUID = 8,
	SAY_SEEDS = 9,
	SAY_ORBS = 10,
	SAY_SCYTE = 11,
	SAY_LEAP = 12

};

enum CreatureEncounterIds
{
    NPC_BURNING_ORB     = 53216,
};

const Position orbsPos[5] = 
{
    {468.600f, -20.167f, 78.950f, 0.0f},
    {434.693f, -14.543f, 79.000f, 0.0f},
    {384.831f, -64.045f, 79.000f, 0.0f},
    {411.289f, -101.455f, 79.00f, 0.0f},
    {451.879f, -104.702f, 79.00f, 0.0f}
};

/**** Majordomo Staghelm ****/

class boss_majordomo_staghelm : public CreatureScript
{
    public:
        boss_majordomo_staghelm() : CreatureScript("boss_majordomo_staghelm") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_majordomo_staghelmAI(creature);
        }

		struct boss_majordomo_staghelmAI : public BossAI
		{
			boss_majordomo_staghelmAI(Creature* c) :
				BossAI(c, DATA_STAGHELM)
			{
				instance = me->GetInstanceScript();
				introDone = false;
				me->SetSpeed(MOVE_RUN, 1.5f, true);
			}

			InstanceScript* instance;

			MajordomoPhase phase;
			bool introDone;
			uint32 transformcount;

			void Reset()
			{
				if (instance)
				{
					instance->SetBossState(DATA_STAGHELM, NOT_STARTED);
					instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
				}

				events.Reset();

				summons.DespawnAll();
				me->RemoveAllAuras();
				TransformToNormal();
				transformcount = 0;
			}

			void MoveInLineOfSight(Unit* who)
			{
				if (introDone || !me->IsWithinDistInMap(who, 35.0f, false))
					return;

				introDone = true;
				// events.SetPhase(1);

				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
				me->SetReactState(REACT_PASSIVE);

				events.ScheduleEvent(EVENT_INTRO_1, 5000);
				events.ScheduleEvent(EVENT_INTRO_2, 17000);
				events.ScheduleEvent(EVENT_INTRO_3, 22500);
			}

			void EnterEvadeMode()
			{
				Reset();

				me->GetMotionMaster()->MoveTargetedHome();

				if (instance)
					instance->SetBossState(DATA_STAGHELM, FAIL);

				_EnterEvadeMode();
			}

			void KilledUnit(Unit * /*victim*/)
			{
				Talk(SAY_ON_KILL);
			}

			void JustSummoned(Creature* summon)
			{
				summons.Summon(summon);
				summon->setActive(true);

				if (me->isInCombat())
					summon->AI()->DoZoneInCombat();
			}

			void DespawnObjects(uint32 entry, float distance)
			{
				std::list<GameObject*> firedoor;
				me->GetGameObjectListWithEntryInGrid(firedoor, 208873, 5000.0f);

				if (!firedoor.empty())
					for (std::list<GameObject*>::const_iterator itr = firedoor.begin(); itr != firedoor.end(); ++itr)
						(*itr)->Delete();
			}

			void JustDied(Unit * /*victim*/)
			{
				if (instance)
				{
					instance->SetBossState(DATA_STAGHELM, DONE);
					instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
				}

				if (GameObject* firewall = me->FindNearestGameObject(208906, 5000.0f))
					firewall->DestroyForNearbyPlayers();

				DespawnObjects(208873, 50000.0f);

				Talk(SAY_ON_DEAD);
				summons.DespawnAll();
				_JustDied();
			}

			void EnterCombat(Unit* who)
			{
				if (instance)
				{
					instance->SetBossState(DATA_STAGHELM, IN_PROGRESS);
					instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me); // Add
				}

				Talk(SAY_AGGRO);
				events.ScheduleEvent(EVENT_CHECK_FORM, 10000);
				events.ScheduleEvent(EVENT_ENERGY_REGEN, 12000);
				events.ScheduleEvent(EVENT_BERSERK, 10 * MINUTE * IN_MILLISECONDS);

				_EnterCombat();
			}

			void UpdateAI(const uint32 diff)
			{
				if (!UpdateVictim() && phase != PHASE_NONE || me->HasUnitState(UNIT_STATE_CASTING))
					return;

				if (phase == PHASE_SCORPION && me->GetPower(POWER_ENERGY) == 100)
				{
					DoCast(me, RAID_MODE(SPELL_FLAME_SCYTE_10N, SPELL_FLAME_SCYTE_25N, SPELL_FLAME_SCYTE_10H, SPELL_FLAME_SCYTE_25H));

					Talk(SAY_SCYTE);
				}

				if (phase == PHASE_CAT && me->GetPower(POWER_ENERGY) == 100)
				{
					DoCast(me, SPELL_LEAPING_FLAMES_SUMMON);
					if (Unit* tempTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 500.0f, true))
					{
						DoCast(tempTarget, SPELL_LEAPING_FLAMES);
						DoCast(tempTarget,
							RAID_MODE(SPELL_LEAP_FLAMES_DMG_10N, SPELL_LEAP_FLAMES_DMG_25N,
							SPELL_LEAP_FLAMES_DMG_10H, SPELL_LEAP_FLAMES_DMG_25H));
					}

					Talk(SAY_LEAP);
				}

				events.Update(diff);

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
					case EVENT_CHECK_FORM:
					{
						uint8 numb = 0;
						Map::PlayerList const& players = me->GetMap()->GetPlayers();
						for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
							if (Player* player = itr->getSource())
								if (me->GetDistance(player) <= 7.0f)
									++numb;

						if ((numb >= (Is25ManRaid() ? 18 : 7)) && phase != PHASE_SCORPION
							&& phase != PHASE_DRUID)
						{
							if (transformcount == 3)
							{
								transformcount = 0;
								TransformToDruid();
							}
							else
							{
								transformcount += 1;
								TransformToScorpion();
							}
						}
						else if ((numb < (Is25ManRaid() ? 18 : 7)) && phase != PHASE_CAT
							&& phase != PHASE_DRUID)
						{
							if (transformcount == 3)
							{
								transformcount = 0;
								TransformToDruid();
							}
							else
							{
								transformcount += 1;
								TransformToCat();
							}
						}

						events.ScheduleEvent(EVENT_CHECK_FORM, 1000);
						break;
					}
					case EVENT_ENERGY_REGEN:
					{
						if (phase == PHASE_CAT || phase == PHASE_SCORPION)
						{
							int32 power = 5;
							if (me->HasAura(SPELL_ADRENALINE))
								power += power * (me->GetAura(SPELL_ADRENALINE)->GetStackAmount() * 20) / 100;
							me->SetPower(POWER_ENERGY, me->GetPower(POWER_ENERGY) + power);
						}
						events.ScheduleEvent(EVENT_ENERGY_REGEN, 1000);
						break;
					}

					case EVENT_INTRO_1:
						Talk(SAY_INTRO_1);
						break;

					case EVENT_INTRO_2:
						Talk(SAY_INTRO_2);
						break;

					case EVENT_INTRO_3:
						Talk(SAY_INTRO_3);
						me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
						me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
						me->SetReactState(REACT_DEFENSIVE);
						break;

					case EVENT_BERSERK:
						DoCast(me, SPELL_BERSERK);
						break;

					case EVENT_SUMMON_ORBS:
					{
						std::list<Unit*> targets;
						SelectTargetList(targets, RAID_MODE(2, 3, 2, 3), SELECT_TARGET_RANDOM, 200.0f, true);
						if (!targets.empty())
							for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
								DoCast(*itr, SPELL_BURNING_ORBS_SUMMON);
						break;
					}
					}
				}

				DoMeleeAttackIfReady();
			}

		private:
			void TransformToCat()
			{
				me->RemoveAura(SPELL_ADRENALINE);
				me->RemoveAura(SPELL_SCORPION_FORM);

				DoCast(me, SPELL_CAT_FORM);

				me->SetByteValue(UNIT_FIELD_BYTES_0, 1, 4);
				me->SetByteValue(UNIT_FIELD_BYTES_0, 3, POWER_ENERGY);
				me->SetMaxPower(POWER_ENERGY, 100);
				me->SetPower(POWER_ENERGY, 0);
				DoCast(me, SPELL_ZERO_POWER);

				DoCast(me, SPELL_FURY);

				phase = PHASE_CAT;

				Talk(SAY_CAT);
			}

			void TransformToScorpion()
			{
				me->RemoveAura(SPELL_ADRENALINE);
				me->RemoveAura(SPELL_CAT_FORM);

				DoCast(me, SPELL_SCORPION_FORM);

				me->SetByteValue(UNIT_FIELD_BYTES_0, 1, 4);
				me->SetByteValue(UNIT_FIELD_BYTES_0, 3, POWER_ENERGY);
				me->SetMaxPower(POWER_ENERGY, 100);
				me->SetPower(POWER_ENERGY, 0);
				DoCast(me, SPELL_ZERO_POWER);

				DoCast(me, SPELL_FURY);

				phase = PHASE_SCORPION;

				Talk(SAY_SCORPION);
			}

			void TransformToDruid()
			{
				me->RemoveAura(SPELL_ADRENALINE);

				DoCast(me, SPELL_FIERY_CYCLONE);

				//When switching from Cat form to Scorpion form, Fandral unleashes Searing Seeds.When switching from Scorpion form to Cat form, Fandral unleashes Burning Orbs.
				if (me->HasAura(SPELL_CAT_FORM)) // Here is the check for previous form for seering seeds.
				{
					me->RemoveAura(SPELL_CAT_FORM);
					Talk(SAY_SEEDS);
					DoCast(me, SPELL_SEARING_SEEDS);
				}

				if (me->HasAura(SPELL_SCORPION_FORM)) // Here is the check for previous form for burning orbs.
				{
					me->RemoveAura(SPELL_SCORPION_FORM);
					Talk(SAY_ORBS);
					DoCast(me, SPELL_BURNING_ORBS);
					events.ScheduleEvent(EVENT_SUMMON_ORBS, 500);
				}

				me->SetByteValue(UNIT_FIELD_BYTES_0, 1, 2);
				me->SetByteValue(UNIT_FIELD_BYTES_0, 3, POWER_MANA);
				me->SetMaxPower(POWER_MANA, 179200);
				me->SetPower(POWER_MANA, 179200);
				phase = PHASE_DRUID;
				Talk(SAY_DRUID);
			}

			void TransformToNormal()
			{
				me->SetByteValue(UNIT_FIELD_BYTES_0, 1, 2);
				me->SetByteValue(UNIT_FIELD_BYTES_0, 3, POWER_MANA);
				me->SetMaxPower(POWER_MANA, 179200);
				me->SetPower(POWER_MANA, 179200);
				phase = PHASE_NONE;
			}
		};
};

class spell_staghelm_searing_seeds_aura : public SpellScriptLoader
{
    public:
        spell_staghelm_searing_seeds_aura() : SpellScriptLoader("spell_staghelm_searing_seeds_aura") { }

        class spell_staghelm_searing_seeds_aura_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_staghelm_searing_seeds_aura_AuraScript);

            void OnApply(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                AuraPtr aura = aurEff->GetBase();
                uint32 duration = urand(3000, 45000);
                aura->SetDuration(duration);
                aura->SetMaxDuration(duration);
            }

            void OnRemove(constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
            {
                GetTarget()->CastSpell(GetTarget(), SPELL_SEARING_SEEDS_EXPLOSION, true);
            }

            void Register()
            {
                AfterEffectApply += AuraEffectApplyFn(spell_staghelm_searing_seeds_aura_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
                AfterEffectRemove += AuraEffectRemoveFn(spell_staghelm_searing_seeds_aura_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_staghelm_searing_seeds_aura_AuraScript();
        }
};

class spell_staghelm_burning_orbs : public SpellScriptLoader
{
    public:
        spell_staghelm_burning_orbs() : SpellScriptLoader("spell_staghelm_burning_orbs") { }

        class spell_staghelm_burning_orbs_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_staghelm_burning_orbs_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                Unit* caster = GetCaster();
                uint8 const orbsCount = (GetCaster()->GetMap()->GetSpawnMode() & 1) ? 5 : 2;
                for (uint8 i = 0; i < orbsCount; ++i)
                    caster->CastSpell(orbsPos[i].GetPositionX(), orbsPos[i].GetPositionY(), orbsPos[i].GetPositionZ(), SPELL_BURNING_ORBS_SUMMON, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_staghelm_burning_orbs_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_staghelm_burning_orbs_SpellScript();
        }
};

class spell_staghelm_concentration_aura : public SpellScriptLoader
{
    public:
        spell_staghelm_concentration_aura() : SpellScriptLoader("spell_staghelm_concentration_aura") { }

        class spell_staghelm_concentration_aura_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_staghelm_concentration_aura_AuraScript);

            void HandlePeriodicTick(constAuraEffectPtr /*aurEff*/)
            {
                if (!GetUnitOwner())
                    return;

                if (AuraEffectPtr aurEff = GetAura()->GetEffect(EFFECT_0))
                {
                    int32 oldamount = GetUnitOwner()->GetPower(POWER_ALTERNATE_POWER);
                    int32 newamount = oldamount + 5;
                    if (newamount > 100)
                        newamount = 100;
                    if (newamount == oldamount)
                        return;

                    if (oldamount < 100 && newamount == 100)
                    {
                        GetUnitOwner()->RemoveAura(SPELL_EPIC_CONCENTRATION);
                        GetUnitOwner()->CastSpell(GetUnitOwner(), SPELL_LEGENDARY_CONCENTRATION, true);
                    }
                    else if (oldamount < 75 && newamount >= 75)
                    {
                        GetUnitOwner()->RemoveAura(SPELL_RARE_CONCENTRATION);
                        GetUnitOwner()->CastSpell(GetUnitOwner(), SPELL_EPIC_CONCENTRATION, true);
                    }
                    else if (oldamount < 50 && newamount >= 50)
                    {
                        GetUnitOwner()->RemoveAura(SPELL_UNCOMMON_CONCENTRATION);
                        GetUnitOwner()->CastSpell(GetUnitOwner(), SPELL_RARE_CONCENTRATION, true);
                    }
                    else if (oldamount < 25 && newamount >= 25)
                    {
                        GetUnitOwner()->CastSpell(GetUnitOwner(), SPELL_UNCOMMON_CONCENTRATION, true);
                    }
                    else if (newamount < 25)
                    {
                        GetUnitOwner()->RemoveAura(SPELL_LEGENDARY_CONCENTRATION);
                        GetUnitOwner()->RemoveAura(SPELL_EPIC_CONCENTRATION);
                        GetUnitOwner()->RemoveAura(SPELL_RARE_CONCENTRATION);
                        GetUnitOwner()->RemoveAura(SPELL_UNCOMMON_CONCENTRATION);
                    }
                    GetUnitOwner()->SetPower(POWER_ALTERNATE_POWER, newamount);
                }
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_staghelm_concentration_aura_AuraScript::HandlePeriodicTick, EFFECT_1, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_staghelm_concentration_aura_AuraScript();
        }
};

void AddSC_boss_majordomo_staghelm()
{
    new boss_majordomo_staghelm();
    new spell_staghelm_searing_seeds_aura();
    new spell_staghelm_burning_orbs();
    new spell_staghelm_concentration_aura();
}
