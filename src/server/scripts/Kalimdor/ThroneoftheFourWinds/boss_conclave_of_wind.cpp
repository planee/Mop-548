#include "ScriptPCH.h"
#include "throne_of_the_four_winds.h"
#include "MoveSplineInit.h"

enum ScriptTextAnshal
{
    SAY_ANSHAL_AGGRO        = 0,  
    SAY_ANSHAL_KILL         = 1,
    SAY_ANSHAL_ENRAGE       = 2,
    SAY_CONCLAVE_ULTIMATE   = 3,
    SAY_ANSHAL_LOW          = 4,
};

enum ScriptTextNezir
{
    SAY_NEZIR_AGGRO         = 0,  
    SAY_NEZIR_KILL          = 1,
    SAY_NEZIR_ENRAGE        = 2,
    SAY_NEZIR_LOW           = 4,
};

enum ScriptTextRohash
{
    SAY_ROHASH_AGGRO        = 0,  
    SAY_ROHASH_KILL         = 1,
    SAY_ROHASH_ENRAGE       = 2,
    SAY_ROHASH_LOW          = 4,
};

enum Spells
{
    SPELL_NO_REGEN                  = 96301,

    // Anshal
    SPELL_PREFIGHT_VISUAL_WEST      = 85537,
    SPELL_SOOTHING_BREEZE           = 86205,
    SPELL_SOOTHING_BREEZE_SUMMON    = 86204,
    SPELL_SOOTHING_BREEZE_AURA_1    = 86206,
    SPELL_SOOTHING_BREEZE_AURA_2    = 86207,
    SPELL_SOOTHING_BREEZE_VISUAL    = 86208,
    SPELL_NURTURE                   = 85422,
    SPELL_NURTURE_SUMMON_TRIGGER    = 85425,
    SPELL_NURTURE_DUMMY             = 85428,
    SPELL_NURTURE_SUMMON            = 85429,
    SPELL_TOXIC_SPORES_FORCE        = 86290,
    SPELL_TOXIC_SPORES              = 86281,
    SPELL_TOXIC_SPORES_DMG          = 86282,
    SPELL_ZEPHYR                    = 84638,
	SPELL_ZEPHYR_BUFF               = 84651,
    SPELL_DUMMY_FOR_NURTURE         = 89813,
    SPELL_WITHERING_WINDS           = 85576,
    SPELL_WITHERING_WINDS_DAMAGE    = 93168,

    // Nezir
    SPELL_PREFIGHT_VISUAL_NORTH     = 85532,
    SPELL_ICE_PATCH                 = 86122,
    SPELL_ICE_PATCH_VISUAL          = 86107, 
    SPELL_ICE_PATCH_AURA            = 86111,
    SPELL_PERMAFROST                = 86082,
    SPELL_WIND_CHILL                = 84645,
    SPELL_SLEET_STORM               = 84644,
    SPELL_SLEET_STORM_DMG           = 86367,
    SPELL_CHILLING_WINDS            = 85578,
    SPELL_CHILLING_WINDS_DAMAGE     = 93163,

    // Rohash
    SPELL_PREFIGHT_VISUAL_EAST      = 85538,
    SPELL_SLICING_GALE              = 86182,
	SPELL_WIND_BLAST_CAST           = 85480,
    SPELL_WIND_BLAST                = 86193, //casts the other spell...
    SPELL_WIND_BLAST_EFFECT         = 85483, //casted by this 85480
    SPELL_TORNADO_AURA              = 86134, 
    SPELL_TORNADO_SUMMON            = 86192,
    SPELL_SLOW_SPIN                 = 99380,  //For Spinning and Wind Blast
    SPELL_STORM_SHIELD              = 93059,
    SPELL_DEAFENING_WINDS           = 85573,
    SPELL_DEAFENING_WINDS_DAMAGE    = 93166,
    SPELL_HURRICANE_ULTIMATE        = 84643,  
    SPELL_HURRICANE_DUMMY           = 86498, // triggered from main spell
    SPELL_HURRICANE_VEHICLE         = 86492, // casted by player
    SPELL_HURRICANE_DAMAGE          = 86487,

    // All
    SPELL_GATHER_STRENGHT           = 86307,
    SPELL_DEAD                      = 81238, // Dead look.
    //SPELL_CANNOT_TURN               = 95544,
    SPELL_TELEPORT_VISUAL           = 83369,

    // Instance
    SPELL_WINDDRAFT                 = 84576,
    SPELL_JETSTREAM_PREVENT         = 89771,
    SPELL_BERSERK                   = 82395,
    SPELL_WIND_PRE_EFFECT_WARNING   = 96508,

    // Achievements
    SPELL_ACHIEVEMENT_CONCLAVE      = 88835,
};

enum GameobjectIds
{
    GOB_WIND_DRAFTEFFECT_CENTER     = 207922,
    GOB_RAIDPLATFORM                = 207737,

    GOB_WIND_DRAFTEFFECT_1          = 207923,
    GOB_WIND_DRAFTEFFECT_2          = 207924,
    GOB_WIND_DRAFTEFFECT_3          = 207925,
    GOB_WIND_DRAFTEFFECT_4          = 207926,
    GOB_WIND_DRAFTEFFECT_5          = 207929,
    GOB_WIND_DRAFTEFFECT_6          = 207930,
    GOB_WIND_DRAFTEFFECT_7          = 207927,
    GOB_WIND_DRAFTEFFECT_8          = 207928,

    GOB_DEIJING_HEALING             = 206699,
    GOB_DEIJING_FROST               = 206700,
    GOB_DEIJING_TORNADO             = 206701
};

enum Adds
{
    NPC_TORNADO                     = 46207,
    NPC_HURRICANE                   = 46419,
    NPC_RAVENOUS_TRIGGER            = 45813,
    NPC_RAVENOUS_CREEPER            = 45812,
    NPC_SOOTHING_BREEZE             = 46246,
	NPC_ICE_PATCH                   = 46186,
	NPC_BURST_TARGET                = 34211,
};

enum Events
{
    // Anshal
    EVENT_SOOTHING_BREEZE           = 1,
    EVENT_NURTURE,
	EVENT_STOP_NURTURE,
    EVENT_ULTIMATE_ANSHAL,
    EVENT_TOXIC_SPORES,
    EVENT_ZEPHYR_1,
    EVENT_ZEPHYR_2,

    // Nezir
    EVENT_ICE_PATCH,
    EVENT_PERMAFROST,
    EVENT_WIND_CHILL,
    EVENT_SLEET_STORM_1,
    EVENT_SLEET_STORM_2,

    // Rohash
    EVENT_SLICING_GALE,
    EVENT_WIND_BLAST,
	EVENT_WIND_BLAST_END,
    EVENT_TORNADO,
    EVENT_STORM_SHIELD,
    EVENT_HURRICANE,
    EVENT_HURRICANE_1,
    EVENT_HURRICANE_2,
    
    //All
    EVENT_UPDATE_VICTIM,
    EVENT_REVIVE,
    EVENT_GATHER_STRENGHT,
    EVENT_START_MOVE,
    EVENT_UPDATE_ENERGY,
	EVENT_BERSERK,
	EVENT_AGGRO,
};

enum Others
{
    DATA_DEAD       = 1,
    DATA_ULTIMATE   = 2,
	DATA_SHIELD     = 3,
};

class CouncilGameObject
{
    public:
        CouncilGameObject() { }

        bool operator()(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GOB_WIND_DRAFTEFFECT_CENTER:
                    go->SetGoState(GO_STATE_READY);
                    break;
                case GOB_DEIJING_HEALING:
                case GOB_DEIJING_FROST:
                case GOB_DEIJING_TORNADO:
                    go->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GOB_RAIDPLATFORM:
                    go->SetGoState(GO_STATE_READY);
                    break;
                case GOB_WIND_DRAFTEFFECT_1:
                case GOB_WIND_DRAFTEFFECT_2:
                case GOB_WIND_DRAFTEFFECT_3:
                case GOB_WIND_DRAFTEFFECT_4:
                case GOB_WIND_DRAFTEFFECT_5:
                case GOB_WIND_DRAFTEFFECT_6:
                case GOB_WIND_DRAFTEFFECT_7:
                case GOB_WIND_DRAFTEFFECT_8:
                    go->SetGoState(GO_STATE_READY);
                    break;
                default:
                    break;
            }

            return false;
        }
};

Position const TornadoWaypoints[] =
{
	{ -4.0624f, 604.63f, 198.49f, 0 },
	{ -16.88f, 614.48f, 199.49f, 0 },
	{ -31.12f, 620.74f, 197.69f, 0 },
	{ -19.41f, 599.69f, 199.49f, 0 },
	{ -26.89f, 605.23f, 199.49f, 0 },
	{ -40.16f, 609.25f, 199.48f, 0 },
	{ -22.98f, 587.98f, 199.49f, 0 },
	{ -44.01f, 600.01f, 199.49f, 0 },
	{ -53.95f, 608.68f, 199.48f, 0 },
	{ -67.92f, 619.45f, 197.06f, 0 },
	{ -77.55f, 618.57f, 199.49f, 0 },
	{ -85.30f, 607.88f, 199.49f, 0 },
	{ -68.97f, 602.52f, 199.48f, 0 },
	{ -74.77f, 592.49f, 199.48f, 0 },
	{ -76.74f, 578.68f, 199.48f, 0 },
	{ -62.66f, 590.42f, 199.48f, 0 },
	{ -47.44f, 590.97f, 199.46f, 0 },
	{ -75.72f, 564.73f, 199.48f, 0 },
	{ -64.95f, 554.41f, 199.48f, 0 },
	{ -68.06f, 547.86f, 199.48f, 0 },
	{ -49.25f, 552.65f, 199.48f, 0 },
	{ -26.08f, 558.72f, 199.48f, 0 },
	{ -42.69f, 545.89f, 199.48f, 0 },
	{ -37.36f, 558.31f, 199.48f, 0 },
	{ -24.81f, 572.06f, 199.48f, 0 },
};

class boss_anshal : public CreatureScript
{
    public:
        boss_anshal() : CreatureScript("boss_anshal") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_anshalAI (creature);
        }

        struct boss_anshalAI : public ScriptedAI
        {
            boss_anshalAI(Creature* pCreature) : ScriptedAI(pCreature), summons(me)
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

				me->SetUnitMovementFlags(MOVEMENTFLAG_HOVER);
				me->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);

                me->setActive(true);
                me->SetFloatValue(UNIT_FIELD_COMBAT_REACH, 5.0f);

                pInstance = pCreature->GetInstanceScript();

                m_isDead = false;
                hasNoTarget = false;
            }

            void Reset()
            {
                events.Reset();
                summons.DespawnAll();
                DespawnCreatures(NPC_SOOTHING_BREEZE);
				DespawnCreatures(NPC_RAVENOUS_CREEPER);
				DespawnCreatures(NPC_SLIPSTREAM_ALAKIR_1);
                me->RemoveAura(SPELL_DEAD); // Dead Look
				me->RemoveAura(SPELL_BERSERK);

                DoCast(me, SPELL_NO_REGEN, true);
                
                me->SetMaxPower(POWER_MANA, 90);
                me->SetPower(POWER_MANA, 0);

                me->SetReactState(REACT_AGGRESSIVE);
                m_isDead = false;
                hasNoTarget = false;

				if (pInstance)
				{
					pInstance->SetBossState(DATA_CONCLAVE_OF_WIND, NOT_STARTED);
					pInstance->SetData(DATA_CONCLAVE_OF_WIND, NOT_STARTED);
				}
            }

            void EnterCombat(Unit* who)
            {
				Map* map = me->GetMap();
                me->RemoveAura(SPELL_PREFIGHT_VISUAL_WEST);

                events.ScheduleEvent(EVENT_NURTURE, 30000);
                events.ScheduleEvent(EVENT_SOOTHING_BREEZE, 16000);
                events.ScheduleEvent(EVENT_UPDATE_ENERGY, 1000);
                events.ScheduleEvent(EVENT_UPDATE_VICTIM, 10000);
				if (map->GetDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL || map->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC)
					events.ScheduleEvent(EVENT_BERSERK, 480000);
                Talk(SAY_ANSHAL_AGGRO);

                me->SetMaxPower(POWER_MANA, 90);
                me->SetPower(POWER_MANA, 0);

                m_isDead = false;
                hasNoTarget = false;

                if (pInstance)
                {
                    if (Creature* pNezir = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_NEZIR)))
                        if (!pNezir->isInCombat())
                            DoZoneInCombat(pNezir, 600.0f);

                    if (Creature* pRohash = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_ROHASH)))
                        if (!pRohash->isInCombat())
                            DoZoneInCombat(pRohash, 600.0f);

                    pInstance->SetData(DATA_CONCLAVE_OF_WIND, IN_PROGRESS);
					pInstance->SetBossState(DATA_CONCLAVE_OF_WIND, IN_PROGRESS);					
                }
            }

            void DamageTaken(Unit* dealer, uint32 &damage)
            {
                if (dealer->GetGUID() == me->GetGUID())
                    return;
                
                if (me->GetHealth() < damage)
                {
                    damage = me->GetHealth() - 1;

                    if (!m_isDead)
                    {
                        m_isDead = true;
                        if (pInstance)
                        {
                            Creature* pNezir = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_NEZIR));
                            Creature* pRohash = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_ROHASH));
                            if (pNezir->AI()->GetData(DATA_DEAD) > 0 && pRohash->AI()->GetData(DATA_DEAD) > 0)
                            {
                                pNezir->Kill(pNezir);
                                pRohash->Kill(pRohash);
                                me->Kill(me);
								
                            }
                            else
                            {
                                events.Reset();
                                me->SetReactState(REACT_PASSIVE);
                                me->AttackStop();
                                DoCast(me, SPELL_GATHER_STRENGHT);
                                Talk(SAY_ANSHAL_LOW);
                            }
                        }
                    }
                }
            }

            void JustSummoned(Creature *summon)
            {
                summons.Summon(summon);
                if (me->isInCombat())
                    DoZoneInCombat(summon);
            }

            void SummonedCreatureDespawn(Creature* summon)
            {
                summons.Despawn(summon);
            }

            void JustDied(Unit* killer)
            {
				
                events.Reset();
                summons.DespawnAll();
                pInstance->SetBossState(DATA_CONCLAVE_OF_WIND, DONE);
				pInstance->SetData(DATA_CONCLAVE_OF_WIND, DONE);
				if(Creature *alakir = me->FindNearestCreature(NPC_ALAKIR, 500.0f))
					alakir->MonsterYell("The Conclave of Wind has dissipated. Your honorable conduct and determination have earned you the right to face me in battle, mortals. I await your assault on my platform! Come!", 0, NULL);
				if (pInstance)
				{
					Map* map = me->GetMap();
					if (!map)
						return;

					if (!map->IsDungeon())
						return;

					//75 Justices Points for players level 85
					//pInstance->DoModifyPlayerCurrenciesIfLevel(395, 7500, 85); Add this when the boss save in the BD

					//Achievement Conclave of Wind Heroic kills (Throne of the Four Winds) 10H, 25H
					if (map->GetDifficulty() == RAID_DIFFICULTY_10MAN_HEROIC)
					{
						pInstance->DoCompleteAchievement(5574);
					}
					else if (map->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC)
					{
						pInstance->DoCompleteAchievement(5574);
					}
					//Fix this achievement in the future, comment to prevent crash
					/*Map::PlayerList const& players = instance->GetPlayers();
					if (!players.isEmpty())
					{
						for (Map::PlayerList::const_iterator i = players.begin(); i != players.end(); ++i)
						{
							if (Player* player = i->getSource())
							{
								if (AuraPtr aur = player->GetAura(SPELL_WIND_CHILL))
								{
									if (aur->GetStackAmount() > 7)
										pInstance->DoCompleteAchievement(5304);
								}
							}
						}
					}*/
				}
			}
            
            void KilledUnit(Unit* victim)
            {
                Talk(SAY_ANSHAL_KILL);
            }

            uint32 GetData(uint32 type)
            {
                if (type == DATA_DEAD)
                    return (m_isDead ? 1 : 0);

                return 0;
            }
            
            void UpdateAI(const uint32 diff)
            {                    
                if (!UpdateVictim() || !pInstance)
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
                
                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_UPDATE_VICTIM:
                            if (Unit* victim = me->getVictim())
                            {
                                if (me->GetHomePosition().GetExactDist2d(victim) > 60.0f)
                                {
                                    Unit* pTarget = NULL;
                                    pTarget = SelectTarget(SELECT_TARGET_NEAREST, 0, 55.0f, true);
                                    if (pTarget && me->GetHomePosition().GetExactDist2d(pTarget) <= 60.0f)
                                    {
                                        AttackStart(pTarget);
                                    }
                                    else if (!hasNoTarget)
                                    {
                                        hasNoTarget = true;
                                        Talk(SAY_ANSHAL_ENRAGE);
                                        DoCast(me, SPELL_WITHERING_WINDS, true);
                                    }
                                }
                            }

                            events.ScheduleEvent(EVENT_UPDATE_VICTIM, 5000);
                            break;
                        case EVENT_SOOTHING_BREEZE:
                            if (Creature* creeper = me->FindNearestCreature(NPC_RAVENOUS_CREEPER, 90.0f, true))
                                DoCast(creeper, SPELL_SOOTHING_BREEZE);
                            else
                                DoCast(me, SPELL_SOOTHING_BREEZE);
							events.ScheduleEvent(EVENT_SOOTHING_BREEZE, urand(25000, 35000));
                            break;
                        case EVENT_NURTURE:
							me->SetReactState(REACT_PASSIVE);
							me->AttackStop();
							me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                            DoCast(me, SPELL_NURTURE, true);
							events.ScheduleEvent(EVENT_STOP_NURTURE, 5000);                           
                            break;
						case EVENT_STOP_NURTURE:
							me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
							me->SetReactState(REACT_AGGRESSIVE);
							me->RemoveAurasDueToSpell(SPELL_NURTURE_DUMMY);
							me->RemoveAurasDueToSpell(SPELL_NURTURE);
							me->RemoveAurasDueToSpell(SPELL_NURTURE_SUMMON);
							break;
                        case EVENT_UPDATE_ENERGY:
                            if (me->GetPower(POWER_MANA) < 90)
                            {
                                int32 power = me->GetPower(POWER_MANA);
                                power++;
                                me->SetPower(POWER_MANA, power);
                                if (Creature* pNezir = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_NEZIR)))
                                    pNezir->SetPower(POWER_MANA, power);
                                if (Creature* pRohash = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_ROHASH)))
                                    pRohash->SetPower(POWER_MANA, power);

                                events.ScheduleEvent(EVENT_UPDATE_ENERGY, 1000);
                            }
                            else
                            {
                                events.CancelEvent(EVENT_SOOTHING_BREEZE);
                                events.CancelEvent(EVENT_NURTURE);
                                events.CancelEvent(EVENT_TOXIC_SPORES);
                                events.CancelEvent(EVENT_UPDATE_VICTIM);

                                summons.DespawnEntry(NPC_SOOTHING_BREEZE);

                                me->NearTeleportTo(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY(), me->GetHomePosition().GetPositionZ(), me->GetHomePosition().GetOrientation());
                                me->UpdateObjectVisibility(true);

								me->SetReactState(REACT_PASSIVE);
								me->AttackStop();
								me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);

                                if (Creature* pNezir = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_NEZIR)))
                                    pNezir->AI()->DoAction(DATA_ULTIMATE);
								if (Creature* pRohash = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_ROHASH)))
                                    pRohash->AI()->DoAction(DATA_ULTIMATE);

                                Talk(SAY_CONCLAVE_ULTIMATE);

                                events.ScheduleEvent(EVENT_ZEPHYR_1, 1000);                                
                            }
							if (me->GetPower(POWER_MANA) == 29 && IsHeroic())
							if (Creature* pRohash = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_ROHASH)))
								pRohash->AI()->DoAction(DATA_SHIELD);
                            break;
                        case EVENT_ZEPHYR_1:
                            DoCast(SPELL_ZEPHYR);
                            events.ScheduleEvent(EVENT_ZEPHYR_2, 16000);
                            break;
                        case EVENT_ZEPHYR_2:
                            me->SetPower(POWER_MANA, 0);							
							me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
							me->SetReactState(REACT_AGGRESSIVE);
							me->RemoveAura(SPELL_ZEPHYR_BUFF);

                            events.ScheduleEvent(EVENT_SOOTHING_BREEZE, 16000);
                            events.ScheduleEvent(EVENT_NURTURE, 35000);
                            events.ScheduleEvent(EVENT_UPDATE_ENERGY, 1000);
                            events.ScheduleEvent(EVENT_UPDATE_VICTIM, 10000);

                            me->SetReactState(REACT_AGGRESSIVE);
                            break;
						case EVENT_BERSERK:
							me->CastSpell(me, SPELL_BERSERK, true);
							events.CancelEvent(EVENT_BERSERK);
							break;
                        default:
                            break;
                    }
                }        

                DoMeleeAttackIfReady();
            }

        private:
            InstanceScript* pInstance;
            EventMap events;
            SummonList summons;
            bool m_isDead;
            bool hasNoTarget;
			InstanceMap* instance;

            void DespawnCreatures(uint32 entry)
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);

                if (creatures.empty())
                   return;

                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                     (*iter)->DespawnOrUnsummon(2000);
            }
        };
};

class boss_nezir : public CreatureScript
{
    public:
        boss_nezir() : CreatureScript("boss_nezir") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_nezirAI (creature);
        }

        struct boss_nezirAI : public ScriptedAI
        {
            boss_nezirAI(Creature* pCreature) : ScriptedAI(pCreature), summons(me)
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

				me->SetUnitMovementFlags(MOVEMENTFLAG_HOVER);
				me->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);

                me->setActive(true);
                me->SetFloatValue(UNIT_FIELD_COMBAT_REACH, 5.0f);

                pInstance = pCreature->GetInstanceScript();

                m_isDead = false;
                hasNoTarget = false;
            }

            void Reset()
            {
                events.Reset();
                summons.DespawnAll();
				DespawnCreatures(NPC_SLIPSTREAM_ALAKIR_1);
                me->RemoveAura(SPELL_DEAD); // Dead Look
				me->RemoveAura(SPELL_BERSERK);

                DoCast(me, SPELL_NO_REGEN, true);
                
                me->SetMaxPower(POWER_MANA, 90);
                me->SetPower(POWER_MANA, 0);

                me->SetReactState(REACT_AGGRESSIVE);

                m_isDead = false;
                hasNoTarget = false;

				if (pInstance)
				{
					pInstance->SetBossState(DATA_CONCLAVE_OF_WIND, NOT_STARTED);
					pInstance->SetData(DATA_CONCLAVE_OF_WIND, NOT_STARTED);
				}
            }

            void EnterCombat(Unit* who)
            {
				Map* map = me->GetMap();
                me->RemoveAura(SPELL_PREFIGHT_VISUAL_NORTH);

                me->SetMaxPower(POWER_MANA, 90);
                me->SetPower(POWER_MANA, 0);

				events.ScheduleEvent(EVENT_ICE_PATCH, urand(10000, 12000));
                events.ScheduleEvent(EVENT_WIND_CHILL, urand(5000, 10500));
                events.ScheduleEvent(EVENT_PERMAFROST, 10000);
                events.ScheduleEvent(EVENT_UPDATE_VICTIM, 10000);
				if (map->GetDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL || map->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC)
					events.ScheduleEvent(EVENT_BERSERK, 480000);

                m_isDead = false;
                hasNoTarget = false;

                if (pInstance)
                {
                    if (Creature* pAnshal = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_ANSHAL)))
                        if (!pAnshal->isInCombat())
                            DoZoneInCombat(pAnshal, 600.0f);

                    if (Creature* pRohash = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_ROHASH)))
                        if (!pRohash->isInCombat())
                            DoZoneInCombat(pRohash, 600.0f);

                    pInstance->SetBossState(DATA_CONCLAVE_OF_WIND, IN_PROGRESS);
					pInstance->SetData(DATA_CONCLAVE_OF_WIND, IN_PROGRESS);
                }
            }

            void DoAction(const int32 action)
            {
                if (action == DATA_ULTIMATE)
                {
                    events.CancelEvent(EVENT_WIND_CHILL);
                    events.CancelEvent(EVENT_PERMAFROST);
					events.CancelEvent(EVENT_ICE_PATCH);
                    events.CancelEvent(EVENT_UPDATE_VICTIM);

                    me->NearTeleportTo(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY(), me->GetHomePosition().GetPositionZ(), me->GetHomePosition().GetOrientation());
                    me->UpdateObjectVisibility(true);
					me->SetReactState(REACT_PASSIVE);
					me->AttackStop();
					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);

                    Talk(SAY_CONCLAVE_ULTIMATE);

                    events.ScheduleEvent(EVENT_SLEET_STORM_1, 1000);
					//That is a hack, because sleet storm, present problems, in the future is necesary fix
					events.ScheduleEvent(EVENT_SLEET_STORM_2, 16000);
                }
            }

            void DamageTaken(Unit* dealer, uint32 &damage)
            {
                if (dealer->GetGUID() == me->GetGUID())
                    return;
                
                if (me->GetHealth() < damage)
                {
                    damage = me->GetHealth() - 1;

                    if (!m_isDead)
                    {
                        m_isDead = true;
                        if (pInstance)
                        {
                            Creature* pAnshal = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_ANSHAL));
                            Creature* pRohash = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_ROHASH));
                            if (pAnshal->AI()->GetData(DATA_DEAD) > 0 && pRohash->AI()->GetData(DATA_DEAD) > 0)
                            {
                                pAnshal->Kill(pAnshal);
                                pRohash->Kill(pRohash);
                                me->Kill(me);
						     }
                            else
                            {
                                events.Reset();
                                me->SetReactState(REACT_PASSIVE);
                                me->AttackStop();
                                DoCast(me, SPELL_GATHER_STRENGHT);
                            }
                        }
                    }
                }
            }

            void JustSummoned(Creature *summon)
            {
                summons.Summon(summon);
                if (me->isInCombat())
                    DoZoneInCombat(summon);
            }

            void SummonedCreatureDespawn(Creature* summon)
            {
                summons.Despawn(summon);
            }

            void JustDied(Unit* killer)
            {
                events.Reset();
                summons.DespawnAll();
				pInstance->SetData(DATA_CONCLAVE_OF_WIND, DONE);
                pInstance->SetBossState(DATA_CONCLAVE_OF_WIND, DONE);				
            }
            
            void KilledUnit(Unit* victim)
            {

            }

            uint32 GetData(uint32 type)
            {
                if (type == DATA_DEAD)
                    return (m_isDead ? 1 : 0);

                return 0;
            }
            
            void UpdateAI(const uint32 diff)
            {                    
                if (!UpdateVictim() || !pInstance)
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
                
                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_UPDATE_VICTIM:
                            if (Unit* victim = me->getVictim())
                            {
                                if (me->GetHomePosition().GetExactDist2d(victim) > 60.0f)
                                {
                                    Unit* pTarget = NULL;
                                    pTarget = SelectTarget(SELECT_TARGET_NEAREST, 0, 55.0f, true);
                                    if (pTarget && me->GetHomePosition().GetExactDist2d(pTarget) <= 60.0f)
                                    {
                                        AttackStart(pTarget);
                                    }
                                    else if (!hasNoTarget)
                                    {
                                        hasNoTarget = true;
                                        Talk(SAY_NEZIR_ENRAGE);
                                        DoCast(me, SPELL_CHILLING_WINDS, true);
                                    }
                                }
                            }

                            events.ScheduleEvent(EVENT_UPDATE_VICTIM, 10000);
                            break;
						case EVENT_ICE_PATCH:
							if (Unit * target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
								DoCast(target, SPELL_ICE_PATCH);
							events.ScheduleEvent(EVENT_ICE_PATCH, urand(17000, 22000));
							break;
                        case EVENT_WIND_CHILL:
                            DoCastAOE(SPELL_WIND_CHILL);
                            events.ScheduleEvent(EVENT_WIND_CHILL, 10500);
                            break;
                        case EVENT_PERMAFROST:
                            DoCastVictim(SPELL_PERMAFROST);
                            events.ScheduleEvent(EVENT_PERMAFROST, 15000);
                            break;
                        case EVENT_SLEET_STORM_1:
							//That is a hack, because sleet storm, present problems, in the future is necesary fix
							DoCast(me, SPELL_SLEET_STORM_DMG);
                            events.ScheduleEvent(EVENT_SLEET_STORM_1, 1000/*16000*/);
							//events.ScheduleEvent(EVENT_SLEET_STORM_2, 16000);
                            break;
                        case EVENT_SLEET_STORM_2:
							me->SetPower(POWER_MANA, 0);                            
							me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
							me->SetReactState(REACT_AGGRESSIVE);
                            events.ScheduleEvent(EVENT_WIND_CHILL, urand(7000, 10500));
                            events.ScheduleEvent(EVENT_PERMAFROST, 3000);
                            events.ScheduleEvent(EVENT_UPDATE_VICTIM, 10000);
							events.ScheduleEvent(EVENT_ICE_PATCH, urand(10000, 12000));
							events.CancelEvent(EVENT_SLEET_STORM_1);
							break;
						case EVENT_BERSERK:
							me->CastSpell(me, SPELL_BERSERK, true);
							events.CancelEvent(EVENT_BERSERK);
							break;
                        default:
                            break;
                    }
                }        

                DoMeleeAttackIfReady();
            }

        private:
            InstanceScript* pInstance;
            EventMap events;
            SummonList summons;
            bool m_isDead;
            bool hasNoTarget;
			InstanceMap* instance;

            void DespawnCreatures(uint32 entry)
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);

                if (creatures.empty())
                   return;

                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                     (*iter)->DespawnOrUnsummon(2000);
            }
        };
};

class boss_rohash : public CreatureScript
{
    public:
        boss_rohash() : CreatureScript("boss_rohash") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_rohashAI (creature);
        }

        struct boss_rohashAI : public ScriptedAI
        {
            boss_rohashAI(Creature* pCreature) : ScriptedAI(pCreature), summons(me)
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
				me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_WIND_BLAST_EFFECT, true);

				me->SetUnitMovementFlags(MOVEMENTFLAG_HOVER);
				me->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);

                me->setActive(true);
                me->SetFloatValue(UNIT_FIELD_COMBAT_REACH, 5.0f);

                pInstance = pCreature->GetInstanceScript();

                m_isDead = false;
                hasNoTarget = false;
				IsCastingWindBlast = false;
            }

            void Reset()
            {
                events.Reset();
                summons.DespawnAll();
				DespawnCreatures(NPC_SLIPSTREAM_ALAKIR_1);
                me->RemoveAura(SPELL_DEAD); // Dead Look
				me->RemoveAura(SPELL_BERSERK);

                DoCast(me, SPELL_NO_REGEN, true);
                
                me->SetMaxPower(POWER_MANA, 90);
                me->SetPower(POWER_MANA, 0);

                me->SetReactState(REACT_AGGRESSIVE);

                m_isDead = false;
                hasNoTarget = false;
				IsCastingWindBlast = false;

				uiTurnTimer = 45000;

				if (pInstance)
				{
					pInstance->SetBossState(DATA_CONCLAVE_OF_WIND, NOT_STARTED);
					pInstance->SetData(DATA_CONCLAVE_OF_WIND, NOT_STARTED);
				}
            }

            void EnterCombat(Unit* who)
            {
				Map* map = me->GetMap();
                me->RemoveAura(SPELL_PREFIGHT_VISUAL_EAST);

                me->SetMaxPower(POWER_MANA, 90);
                me->SetPower(POWER_MANA, 0);

                m_isDead = false;
                hasNoTarget = false;
				IsCastingWindBlast = false;
				if (map->GetDifficulty() == RAID_DIFFICULTY_25MAN_NORMAL || map->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC)
				events.ScheduleEvent(EVENT_BERSERK, 480000);
                events.ScheduleEvent(EVENT_SLICING_GALE, 2000);
				events.ScheduleEvent(EVENT_WIND_BLAST, 10000);
                events.ScheduleEvent(EVENT_TORNADO, 7000);
                events.ScheduleEvent(EVENT_UPDATE_VICTIM, 10000);				

                Talk(SAY_ROHASH_AGGRO);

                if (pInstance)
                {
                    if (Creature* pAnshal = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_ANSHAL)))
                        if (!pAnshal->isInCombat())
                            DoZoneInCombat(pAnshal, 600.0f);

                    if (Creature* pNezir = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_NEZIR)))
                        if (!pNezir->isInCombat())
                            DoZoneInCombat(pNezir, 600.0f);

                    pInstance->SetBossState(DATA_CONCLAVE_OF_WIND, IN_PROGRESS);
					pInstance->SetData(DATA_CONCLAVE_OF_WIND, IN_PROGRESS);
                }
            }

            void AttackStart(Unit* who)
            {
                if (!who)
                    return;

                if (me->Attack(who, false))
                    DoStartNoMovement(who);
            }

            void DoAction(const int32 action)
            {
                if (action == DATA_ULTIMATE)
                {
                    events.CancelEvent(EVENT_SLICING_GALE);
                    events.CancelEvent(EVENT_UPDATE_VICTIM);
					events.CancelEvent(EVENT_SLICING_GALE);
					events.CancelEvent(EVENT_WIND_BLAST);
					DespawnCreatures(NPC_TORNADO);

                    me->NearTeleportTo(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY(), me->GetHomePosition().GetPositionZ(), me->GetHomePosition().GetOrientation());
                    me->UpdateObjectVisibility(true);

                    Talk(SAY_CONCLAVE_ULTIMATE);

                    events.ScheduleEvent(EVENT_HURRICANE_1, 1000);
                }
				if (action == DATA_SHIELD)
				{
					events.ScheduleEvent(EVENT_STORM_SHIELD, 1000);
				}
            }

            void DamageTaken(Unit* dealer, uint32 &damage)
            {
                if (dealer->GetGUID() == me->GetGUID())
                    return;
                
                if (me->GetHealth() < damage)
                {
                    damage = me->GetHealth() - 1;

                    if (!m_isDead)
                    {
                        m_isDead = true;
                        if (pInstance)
                        {
                            Creature* pAnshal = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_ANSHAL));
							Creature* pNezir = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_NEZIR));
                            if (pAnshal->AI()->GetData(DATA_DEAD) > 0 && pNezir->AI()->GetData(DATA_DEAD) > 0)
                            {
                                pAnshal->Kill(pAnshal);
                                pNezir->Kill(pNezir);
                                me->Kill(me);
                            }
                            else
                            {
                                events.Reset();
                                me->SetReactState(REACT_PASSIVE);
                                me->AttackStop();
                                DoCast(me, SPELL_GATHER_STRENGHT);
                            }
                        }
                    }
                }
            }

			void SummonThreatController()
			{
				if (Creature* hurricane = me->SummonCreature(NPC_HURRICANE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 25, 3.32963f, TEMPSUMMON_TIMED_DESPAWN, 16000))
				{
					hurricane->SetCanFly(true);
					hurricane->SetDisableGravity(true);
					hurricane->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);
					hurricane->GetMotionMaster()->MoveRotate(15000, urand(0, 1) ? ROTATE_DIRECTION_LEFT : ROTATE_DIRECTION_RIGHT);
				}

				me->SetInCombatWithZone();
			}

			void UpdateOrientation()
			{
				float orient = me->GetOrientation();
				me->SetFacingTo(orient - M_PI / 75);
				float x, y, z;
				z = me->GetPositionZ();
				me->GetNearPoint2D(x, y, 10.0f, me->GetOrientation());
				if (Creature* temp = me->SummonCreature(NPC_BURST_TARGET, x, y, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 100))
					me->SetTarget(temp->GetGUID());
			}

            void JustSummoned(Creature *summon)
            {
                summons.Summon(summon);
                if (me->isInCombat())
                    DoZoneInCombat(summon);
            }

            void SummonedCreatureDespawn(Creature* summon)
            {
                summons.Despawn(summon);
            }

            void JustDied(Unit* killer)
            {
                events.Reset();
                summons.DespawnAll();
				pInstance->SetBossState(DATA_CONCLAVE_OF_WIND, DONE);
				pInstance->SetData(DATA_CONCLAVE_OF_WIND, DONE);
            }
            
            void KilledUnit(Unit* victim)
            {

            }

            uint32 GetData(uint32 type)
            {
                if (type == DATA_DEAD)
                    return (m_isDead ? 1 : 0);

                return 0;
            }
            
            void UpdateAI(const uint32 diff)
            {          

				if (uiTurnTimer <= diff)
				{
					if (IsCastingWindBlast)
					{
						me->SetFacingTo(irand(0, 4));
						UpdateOrientation();
					}
					uiTurnTimer = 70;
				}
				else uiTurnTimer -= diff;

                if (!UpdateVictim() || !pInstance)
                    return;								

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
                
                if (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_UPDATE_VICTIM:
                            if (Unit* victim = me->getVictim())
                            {
                                if (me->GetHomePosition().GetExactDist2d(victim) > 60.0f)
                                {
                                    Unit* pTarget = NULL;
                                    pTarget = SelectTarget(SELECT_TARGET_NEAREST, 0, 55.0f, true);
                                    if (pTarget && me->GetHomePosition().GetExactDist2d(pTarget) <= 60.0f)
                                    {
                                        AttackStart(pTarget);
                                    }
                                    else if (!hasNoTarget)
                                    {
                                        hasNoTarget = true;
                                        Talk(SAY_ROHASH_ENRAGE);
                                        DoCast(me, SPELL_DEAFENING_WINDS, true);
                                    }
                                }
                            }

                            events.ScheduleEvent(EVENT_UPDATE_VICTIM, 10000);
                            break;
						case EVENT_WIND_BLAST:
							events.CancelEvent(EVENT_SLICING_GALE);
							me->SetReactState(REACT_PASSIVE);
							UpdateOrientation();
							DoCast(SPELL_WIND_BLAST);
							IsCastingWindBlast = true;
							uiTurnTimer = 2000;
							events.CancelEvent(EVENT_WIND_BLAST);
							events.ScheduleEvent(EVENT_WIND_BLAST_END, 10000);							
							break;

						case EVENT_WIND_BLAST_END:							
							me->SetReactState(REACT_AGGRESSIVE);
							uiTurnTimer = 0xFFFFFF;
							IsCastingWindBlast = false;
							events.ScheduleEvent(EVENT_SLICING_GALE, 2500);
							events.ScheduleEvent(EVENT_WIND_BLAST, 50000);
							break;
                        case EVENT_SLICING_GALE:
							if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 90.0f, true))
							{
								DoCast(target, SPELL_SLICING_GALE);
							}
							else
								DoCastVictim(SPELL_SLICING_GALE);
                            events.ScheduleEvent(EVENT_SLICING_GALE, 2500);
                            break;
						case EVENT_STORM_SHIELD:
							DoCast(me, SPELL_STORM_SHIELD);
							break;
                        case EVENT_HURRICANE_1:
                            events.ScheduleEvent(EVENT_HURRICANE_2, 16000);
							SummonThreatController();
                            DoCast(me, SPELL_HURRICANE_ULTIMATE);
                            break;
                        case EVENT_HURRICANE_2:
                            me->SetReactState(REACT_AGGRESSIVE);
							me->SetPower(POWER_MANA, 0);
                            events.ScheduleEvent(EVENT_SLICING_GALE, 3000);
                            events.ScheduleEvent(EVENT_UPDATE_VICTIM, 10000);
							events.ScheduleEvent(EVENT_TORNADO, 7000);
							events.ScheduleEvent(EVENT_WIND_BLAST, 10000);
                            break;
                        case EVENT_TORNADO:
                            DoCast(me, SPELL_TORNADO_SUMMON);
                            break;
						case EVENT_BERSERK:
							if (Creature *alakir = me->FindNearestCreature(NPC_ALAKIR, 500.0f))
								alakir->MonsterYell("This confrontation no longer serves any purpose. I shall end it.", 0, NULL);
							me->CastSpell(me, SPELL_BERSERK, true);
							events.CancelEvent(EVENT_BERSERK);
							break;
                        default:
                            break;
                    }
                }        
            }

        private:
            InstanceScript* pInstance;
            EventMap events;
            SummonList summons;
            bool m_isDead;
            bool hasNoTarget;
			bool IsCastingWindBlast;
			uint32 uiTurnTimer;
			uint32 uiCheckAgroo;
			InstanceMap* instance;

            void DespawnCreatures(uint32 entry)
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);

                if (creatures.empty())
                   return;

                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                     (*iter)->DespawnOrUnsummon(2000);
            }
        };
};

class npc_anshal_ravenous_trigger : public CreatureScript
{
    public:
        npc_anshal_ravenous_trigger() : CreatureScript("npc_anshal_ravenous_trigger") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_anshal_ravenous_triggerAI(pCreature);
        }

        struct npc_anshal_ravenous_triggerAI : public Scripted_NoMovementAI
        {
            npc_anshal_ravenous_triggerAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                me->SetReactState(REACT_PASSIVE);
            }

            void IsSummonedBy(Unit* /*owner*/)
            {
                
                DoCast(me, SPELL_NURTURE_SUMMON, true);
                DoCast(me, SPELL_NURTURE_DUMMY, true);
            }
        };
};

class npc_anshal_ravenous_creeper : public CreatureScript
{
    public:
        npc_anshal_ravenous_creeper() : CreatureScript("npc_anshal_ravenous_creeper") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_anshal_ravenous_creeperAI(pCreature);
        }

        struct npc_anshal_ravenous_creeperAI : public ScriptedAI
        {
            npc_anshal_ravenous_creeperAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                me->SetReactState(REACT_PASSIVE);
            }

            void IsSummonedBy(Unit* /*owner*/)
            {
                events.ScheduleEvent(EVENT_START_MOVE, 2000);
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
                        case EVENT_START_MOVE:
                            me->SetReactState(REACT_AGGRESSIVE);
							events.ScheduleEvent(EVENT_TOXIC_SPORES, 10000);
							events.ScheduleEvent(EVENT_AGGRO, 5000);
                            break;
						case EVENT_TOXIC_SPORES:
							DoCastAOE(SPELL_TOXIC_SPORES_FORCE, true);
							events.ScheduleEvent(EVENT_TOXIC_SPORES, 21000);
							break;
						case EVENT_AGGRO:
							if (me->GetDistance2d(me->getVictim()) > 90)
							{
								if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
								{
									me->getThreatManager().resetAllAggro();
									me->AddThreat(target, 10);
								}
							}
							events.ScheduleEvent(EVENT_TOXIC_SPORES, 5000);
							break;
                    }
                }

                DoMeleeAttackIfReady();
            }

        private:
            EventMap events;
        };
};

class npc_soothing_breeze : public CreatureScript
{
public:
	npc_soothing_breeze() : CreatureScript("npc_soothing_breeze") {}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_soothing_breezeAI(creature);
	}

	struct npc_soothing_breezeAI : public Scripted_NoMovementAI
	{
		npc_soothing_breezeAI(Creature* creature) : Scripted_NoMovementAI(creature)
		{
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED);
			me->SetReactState(REACT_PASSIVE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
		}

		uint32 DespawnTimer;

		void Reset()
		{
			DespawnTimer = 30000;

		}

		void UpdateAI(uint32 const diff)
		{
			if (DespawnTimer <= diff)
			{
				me->DespawnOrUnsummon();

			}
			else DespawnTimer -= diff;
		}
	};
};

class npc_rohash_hurricane : public CreatureScript
{
    public:
        npc_rohash_hurricane() : CreatureScript("npc_rohash_hurricane") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_rohash_hurricaneAI(pCreature);
        }

        struct npc_rohash_hurricaneAI : public Scripted_NoMovementAI
        {
            npc_rohash_hurricaneAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
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

                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                me->SetReactState(REACT_PASSIVE);
            }
        };
};

class npc_rohash_tornado : public CreatureScript
{
    public:
        npc_rohash_tornado() : CreatureScript("npc_rohash_tornado") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_rohash_tornadoAI(pCreature);
        }

        struct npc_rohash_tornadoAI : public Scripted_NoMovementAI
        {
            npc_rohash_tornadoAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                me->SetReactState(REACT_PASSIVE);

                moveTimer = 2000;
                isMoving = false;
            }

            void UpdateAI(const uint32 diff)
            {
                if (!isMoving)
                    if (moveTimer <= diff)
                    {
                        me->SetSpeed(MOVE_RUN, 1.0f, true);
						me->GetMotionMaster()->MovePoint(0, TornadoWaypoints[urand(0, 24)]);
						moveTimer = 5000;
                    }
                    else
                        moveTimer -= diff;

            }

        private:

            uint32 moveTimer;
            bool isMoving;        
        };
};

class npc_nezir_ice_patch : public CreatureScript
{
public:
	npc_nezir_ice_patch() : CreatureScript("npc_nezir_ice_patch") {}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_nezir_ice_patchAI(creature);
	}

	struct npc_nezir_ice_patchAI : public Scripted_NoMovementAI
	{
		npc_nezir_ice_patchAI(Creature* creature) : Scripted_NoMovementAI(creature)
		{
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PACIFIED);
			me->SetReactState(REACT_PASSIVE);
		}

		uint32 DespawnTimer;

		void Reset()
		{
			DespawnTimer = 3000;
			DoCast(me, SPELL_ICE_PATCH_VISUAL, true); 
		}

		void UpdateAI(uint32 const diff)
		{
			if (DespawnTimer <= diff)
			{
				me->DespawnOrUnsummon();

			}
			else DespawnTimer -= diff;
		}
	};
};

class spell_anshal_nurture_summon_trigger : public SpellScriptLoader
{
    public:
        spell_anshal_nurture_summon_trigger() : SpellScriptLoader("spell_anshal_nurture_summon_trigger") { }

        class spell_anshal_nurture_summon_trigger_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_anshal_nurture_summon_trigger_SpellScript);

            void ChangeSummonPos(SpellEffIndex effIndex)
            {
                if (!GetCaster() || !GetCaster()->ToCreature())
                    return;

                PreventHitDefaultEffect(effIndex);
                PreventHitEffect(effIndex);

                Position pos = GetCaster()->ToCreature()->GetHomePosition();
                pos.Relocate(pos.GetPositionX() + frand(-5.0f, 5.0f), pos.GetPositionY() + frand(-5.0f, 5.0f), pos.GetPositionZ() + 1.0f);
                GetCaster()->SummonCreature(NPC_RAVENOUS_CREEPER, pos);

                WorldLocation loc;
                loc.Relocate(pos);
                SetExplTargetDest(loc);
                GetHitDest()->Relocate(pos);
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_anshal_nurture_summon_trigger_SpellScript::ChangeSummonPos, EFFECT_0, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_anshal_nurture_summon_trigger_SpellScript();
        }
};

class spell_anshal_withering_winds : public SpellScriptLoader
{
    public:
        spell_anshal_withering_winds() : SpellScriptLoader("spell_anshal_withering_winds") { }

        class spell_anshal_withering_winds_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_anshal_withering_winds_AuraScript);

            void HandlePeriodic(constAuraEffectPtr aurEff)
            {
                if (!GetTarget())
                    return;

                int32 bp0 = aurEff->GetAmount() * aurEff->GetTickNumber();
                GetTarget()->CastCustomSpell(GetTarget(), SPELL_WITHERING_WINDS_DAMAGE, &bp0, NULL, NULL, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_anshal_withering_winds_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY); 
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_anshal_withering_winds_AuraScript();
        }
};

class spell_nezir_chilling_winds : public SpellScriptLoader
{
    public:
        spell_nezir_chilling_winds() : SpellScriptLoader("spell_nezir_chilling_winds") { }

        class spell_nezir_chilling_winds_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_nezir_chilling_winds_AuraScript);

            void HandlePeriodic(constAuraEffectPtr aurEff)
            {
                if (!GetTarget())
                    return;

                int32 bp0 = aurEff->GetAmount() * aurEff->GetTickNumber();
                GetTarget()->CastCustomSpell(GetTarget(), SPELL_CHILLING_WINDS_DAMAGE, &bp0, NULL, NULL, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_nezir_chilling_winds_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY); 
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_nezir_chilling_winds_AuraScript();
        }
};

class spell_rohash_deafening_winds : public SpellScriptLoader
{
    public:
        spell_rohash_deafening_winds() : SpellScriptLoader("spell_rohash_deafening_winds") { }

        class spell_rohash_deafening_winds_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_rohash_deafening_winds_AuraScript);

            void HandlePeriodic(constAuraEffectPtr aurEff)
            {
                if (!GetTarget())
                    return;

                int32 bp0 = aurEff->GetAmount() * aurEff->GetTickNumber();
                GetTarget()->CastCustomSpell(GetTarget(), SPELL_DEAFENING_WINDS_DAMAGE, &bp0, NULL, NULL, true);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_rohash_deafening_winds_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY); 
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_rohash_deafening_winds_AuraScript();
        }
};

class spell_rohash_hurricane_dummy : public SpellScriptLoader
{
    public:
        spell_rohash_hurricane_dummy() : SpellScriptLoader("spell_rohash_hurricane_dummy") { }

        class spell_rohash_hurricane_dummy_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_rohash_hurricane_dummy_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
            {
                if (!GetCaster() || !GetHitUnit())
                    return;

                GetHitUnit()->CastSpell(GetHitUnit(), SPELL_HURRICANE_VEHICLE, true);

            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_rohash_hurricane_dummy_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_rohash_hurricane_dummy_SpellScript();
        }
};

class PlayerInRangeCheck
{
public:
	explicit PlayerInRangeCheck(Unit* _caster) : caster(_caster) { }

	bool operator() (WorldObject* unit)
	{
		if (caster->HasInArc(M_PI * 104 / 180, unit))
			return false;

		return true;
	}

	Unit* caster;
};

class spell_wind_blast : public SpellScriptLoader
{
public:
	spell_wind_blast() : SpellScriptLoader("spell_wind_blast") { }

	class spell_wind_blast_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_wind_blast_SpellScript);

		void FilterTargets(std::list<WorldObject*>& unitList)
		{
			unitList.remove_if(PlayerInRangeCheck(GetCaster()));
		}

		void Register()
		{
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_wind_blast_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CONE_ENEMY_104);
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_wind_blast_SpellScript::FilterTargets, EFFECT_1, TARGET_DEST_UNK_110);
		}

	protected:
		uint32 targetCount;
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_wind_blast_SpellScript();
	}
};

class spell_nezir_sleet_storm : public SpellScriptLoader
{
public:
	spell_nezir_sleet_storm() : SpellScriptLoader("spell_nezir_sleet_storm") { }

	class spell_nezir_sleet_storm_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_nezir_sleet_storm_SpellScript);

		void FilterTargets(std::list<WorldObject*>& unitList)
		{
			targetCount = unitList.size();
		}

		void CalcDamage()
		{
			SetHitDamage(int32(GetHitDamage() / targetCount));
		}

		void Register()
		{
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_nezir_sleet_storm_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
			OnHit += SpellHitFn(spell_nezir_sleet_storm_SpellScript::CalcDamage);
		}

	protected:
		uint32 targetCount;
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_nezir_sleet_storm_SpellScript();
	}
};

class spell_nurture_aura : public SpellScriptLoader
{
public:
	spell_nurture_aura() : SpellScriptLoader("spell_nurture_aura") {}

	class spell_nurture_aura_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_nurture_aura_AuraScript);

		void HandleEffectCalcPeriodic(constAuraEffectPtr aurEff, bool& isPeriodic, int32& amplitude)
		{
			isPeriodic = true;
		}

		void HandlePeriodic(constAuraEffectPtr aurEff)
		{
			if (Unit* caster = GetCaster())
				caster->CastSpell(caster, SPELL_NURTURE_SUMMON, true);
		}

		void Register()
		{
			DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_nurture_aura_AuraScript::HandleEffectCalcPeriodic, EFFECT_0, SPELL_AURA_DUMMY);
			OnEffectPeriodic += AuraEffectPeriodicFn(spell_nurture_aura_AuraScript::HandlePeriodic, EFFECT_0, SPELL_AURA_DUMMY);
		}
	};

	AuraScript* GetAuraScript() const
	{
		return new spell_nurture_aura_AuraScript();
	}
};

void AddSC_boss_conclave_of_wind()
{
    new boss_anshal();
    new boss_nezir();
    new boss_rohash();
    new npc_anshal_ravenous_trigger();
    new npc_anshal_ravenous_creeper();
	new npc_soothing_breeze();
    new npc_rohash_hurricane();
    new npc_rohash_tornado();
	new npc_nezir_ice_patch();
    new spell_anshal_nurture_summon_trigger();
    new spell_anshal_withering_winds();
    new spell_nezir_chilling_winds();
    new spell_rohash_deafening_winds();
    new spell_rohash_hurricane_dummy();
	new spell_wind_blast();
	new spell_nezir_sleet_storm();
	new spell_nurture_aura();
}
