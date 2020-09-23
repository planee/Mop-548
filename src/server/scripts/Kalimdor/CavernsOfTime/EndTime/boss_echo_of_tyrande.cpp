#include "ScriptPCH.h"
#include "end_time.h"

enum Yells
{
    SAY_AGGRO       = 0,
    SAY_80          = 1,
    SAY_80_EMOTE    = 2,
    SAY_55          = 3,
    SAY_30          = 4,
    SAY_30_EMOTE    = 5,
    SAY_DEATH       = 6,
    SAY_INTRO_1     = 7,
    SAY_INTRO_2     = 8,
    SAY_INTRO_3     = 9,
    SAY_INTRO_4     = 10,
    SAY_INTRO_5     = 11,
    SAY_KILL        = 12,
    SAY_EYES        = 13,
    SAY_MOONLANCE   = 14,
    SAY_LIGHT_1     = 15,
    SAY_LIGHT_2     = 16,
    SAY_LIGHT_3     = 17,
    SAY_LIGHT_4     = 18,
    SAY_LIGHT_5     = 19,
    SAY_LIGHT_6     = 20,
    SAY_LIGHT_LEFT  = 21,
};

enum Spells
{
    SPELL_MOONBOLT                      = 102193,
    SPELL_DARK_MOONLIGHT                = 102414,
    SPELL_MOONLIGHT_COSMETIC            = 108642,
    SPELL_STARDUST                      = 102173,
    
	SPELL_MOONLANCE_AURA                = 102150,
    SPELL_MOONLANCE_DMG                 = 102149,
    SPELL_MOONLANCE_SUMMON_1            = 102151,
    SPELL_MOONLANCE_SUMMON_2            = 102152,
	SPELL_MOONLANCE_STUN                = 102248,
   
	SPELL_LUNAR_GUIDANCE                = 102472,
    	
	SPELL_TEARS_OF_ELUNE                = 102241,
    SPELL_TEARS_OF_ELUNE_SCRIPT         = 102242,
    SPELL_TEARS_OF_ELUNE_MISSILE        = 102243,
    SPELL_TEARS_OF_ELUNE_DMG            = 102244,
    
	
	SPELL_EYES_OF_GODDESS               = 102181,
	SPELL_PIERCING_GAZE_OF_ELUNE_AURA   = 102182,
    SPELL_PIERCING_GAZE_OF_ELUNE_DMG    = 102183,

    // event
    SPELL_IN_SHADOW                     = 101841,
	SPELL_CANCEL_SHADOW                 = 101842,
    SPELL_MOONLIGHT                     = 101946,
    SPELL_SHRINK                        = 102002,

    SPELL_ACHIEVEMENT_CHECK             = 102491,
    SPELL_ACHIEVEMENT_FAIL              = 102539,
    SPELL_ACHIEVEMENT                   = 102542,
};

enum Events
{
    EVENT_MOONBOLT          = 1,
    EVENT_MOONLANCE         = 2,
    EVENT_STARDUST          = 3,
    EVENT_EYES_OF_GODDESS   = 4,

    EVENT_START_EVENT       = 5,
    EVENT_CHECK_PLAYERS     = 6,
    EVENT_SUMMON_ADDS       = 7,
    EVENT_SUMMON_POOL       = 8,
    EVENT_STOP_EVENT        = 9,
    EVENT_STOP_EVENT_1      = 10,

	EVENT_FALL,
};

enum Adds
{
    NPC_MOONLANCE_1                 = 54574,
    NPC_MOONLANCE_2_1               = 54580,
    NPC_MOONLANCE_2_2               = 54581,
    NPC_MOONLANCE_2_3               = 54582,
    NPC_EYE_OF_ELUNE_1              = 54939,
    NPC_EYE_OF_ELUNE_2              = 54940,
    NPC_EYE_OF_ELUNE_3              = 54941,
    NPC_EYE_OF_ELUNE_4              = 54942,
	NPC_EYE_OF_ELUNE_5              = 54594,

    // for aura
    NPC_STALKER                     = 45979,

    // event
    NPC_POOL_OF_MOONLIGHT           = 54508,
    NPC_TIME_TWISTED_SENTINEL       = 54512,
    NPC_TIME_TWISTED_HUNTRESS       = 54701,
    NPC_TIME_TWISTED_NIGHTSABER_1   = 54688,
    NPC_TIME_TWISTED_NIGHTSABER_2   = 54699,
    NPC_TIME_TWISTED_NIGHTSABER_3   = 54700,
};

enum Other
{
    POINT_MOONLANCE     = 1,
    ACTION_START_EVENT  = 2,
};

enum Actions
{
	ACTION_TEAR = 1,
};

const Position poolPos[5] = 
{
    {2903.26f, 63.1788f, 3.2449f, 0.0f},
    {2862.83f, 131.462f, 3.18436f, 0.0f},
    {2756.57f, 129.971f, 5.58215f, 0.0f},
    {2695.44f, 28.7969f, 1.2324f, 0.0f},
    {2792.82f, 1.93924f, 2.46328f, 0.0f}
};

Position const EluneEyes[6] =
{
	{ 2849.759f, 56.774f, 0.324f },
	{ 2845.864f, 28.631f, 0.855f },
	{ 2821.864f, 19.929f, 0.560f },
	{ 2784.864f, 46.805f, 0.975f },
	{ 2797.864f, 78.631f, 1.064f },
	{ 2820.173f, 86.631f, 0.280f },
};

class boss_echo_of_tyrande : public CreatureScript
{
    public:
        boss_echo_of_tyrande() : CreatureScript("boss_echo_of_tyrande") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_echo_of_tyrandeAI(pCreature);
        }

        struct boss_echo_of_tyrandeAI : public BossAI
        {
            boss_echo_of_tyrandeAI(Creature* creature) : BossAI(creature, DATA_ECHO_OF_TYRANDE)
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
                phase = 0;
                eventphase = 0;
                curPool = NULL;
                me->SetUInt32Value(UNIT_FIELD_BYTES_1, 8);
                me->AddAura(SPELL_IN_SHADOW, me);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            }

            void InitializeAI()
            {
                if (!instance || static_cast<InstanceMap*>(me->GetMap())->GetScriptId() != sObjectMgr->GetScriptId(ETScriptName))
                    me->IsAIEnabled = false;
                else if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                _Reset();

                moonlanceGUID = 0LL;
                phase = 0;
				eventphase = 0;
				curPool = NULL;
				me->RemoveAllAuras();
				me->AddAura(SPELL_IN_SHADOW, me);
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
				DespawnCreatures(NPC_TIME_TWISTED_NIGHTSABER_1);
				DespawnCreatures(NPC_TIME_TWISTED_NIGHTSABER_2);
				DespawnCreatures(NPC_TIME_TWISTED_NIGHTSABER_3);
				DespawnCreatures(NPC_TIME_TWISTED_HUNTRESS);
				DespawnCreatures(NPC_TIME_TWISTED_SENTINEL);
				DespawnCreatures(NPC_STALKER);
				if (instance)
				{
				    instance->SetBossState(EVENT_START_EVENT, NOT_STARTED); 
				    instance->SetBossState(EVENT_SUMMON_POOL, NOT_STARTED);
				    instance->SetBossState(EVENT_SUMMON_ADDS, NOT_STARTED);
				    instance->SetData(DATA_ECHO_OF_TYRANDE, NOT_STARTED);
				    instance->SetData(DATA_TYRANDE_EVENT, NOT_STARTED);
				}
				events.Reset();
            }

            void JustDied(Unit* killer)
            {
                _JustDied();
                Talk(SAY_DEATH);
				if (Creature * pool = me->FindNearestCreature(NPC_STALKER, 20.0f))
					pool->DespawnOrUnsummon();
				if (Creature * pool = me->FindNearestCreature(NPC_POOL_OF_MOONLIGHT, 20.0f))
					pool->DespawnOrUnsummon();

				if (instance)
					instance->SetData(DATA_ECHO_OF_TYRANDE, DONE);
				if (instance->GetData(DATA_TYRANDE_EVENT) == DONE)
				{
					me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
					me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
					me->RemoveAura(SPELL_IN_SHADOW);
					if (Creature* pStalker = me->SummonCreature(NPC_STALKER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f))
					{
					pStalker->RemoveAllAuras();
					pStalker->CastSpell(pStalker, SPELL_MOONLIGHT_COSMETIC, true);
					}
				}
                // Quest
                Map::PlayerList const &PlayerList = instance->instance->GetPlayers();
                if (!PlayerList.isEmpty())
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        if (Player* pPlayer = i->getSource())
                            if (me->GetDistance2d(pPlayer) <= 50.0f && pPlayer->GetQuestStatus(30097) == QUEST_STATUS_INCOMPLETE)
                                DoCast(pPlayer, SPELL_ARCHIVED_TYRANDE, true);
            }

            void JustSummoned(Creature* summon)
            {
                if (summon->GetEntry() != NPC_STALKER)
                    BossAI::JustSummoned(summon);

                if (summon->GetEntry() == NPC_MOONLANCE_1)
                {
                    Player* target = ObjectAccessor::GetPlayer(*me, moonlanceGUID);
                    if (!target)
                        summon->DespawnOrUnsummon();

                    summon->SetOrientation(me->GetAngle(target));
                    Position pos;
                    summon->GetNearPosition(pos, 15.0f, 0.0f);
                    summon->GetMotionMaster()->MovePoint(POINT_MOONLANCE, pos);
                }
            }

            void SpellHit(Unit* caster, SpellInfo const* spell)
            {
                if (spell->HasEffect(SPELL_EFFECT_INTERRUPT_CAST))
                    if (me->GetCurrentSpell(CURRENT_GENERIC_SPELL))
                        if (me->GetCurrentSpell(CURRENT_GENERIC_SPELL)->m_spellInfo->Id == SPELL_MOONBOLT)
                            me->InterruptSpell(CURRENT_GENERIC_SPELL);
            }

            void EnterCombat(Unit* /*who*/)
            {
                Talk(SAY_AGGRO);
                
                phase = 0;

                //DoCast(me, SPELL_DARK_MOONLIGHT, true);

                events.ScheduleEvent(EVENT_MOONBOLT, 1000);
                events.ScheduleEvent(EVENT_MOONLANCE, urand(12500, 13000));
                events.ScheduleEvent(EVENT_STARDUST, urand(7000, 8000));
                events.ScheduleEvent(EVENT_EYES_OF_GODDESS, urand(31000, 33000));

                instance->SetBossState(DATA_ECHO_OF_TYRANDE, IN_PROGRESS);
                DoZoneInCombat();

            }

            void SummonedCreatureDespawn(Creature* summon)
            {
                BossAI::SummonedCreatureDespawn(summon);
                if (summon->GetEntry() == NPC_POOL_OF_MOONLIGHT)
                    Talk(SAY_LIGHT_LEFT);
            }

            void AttackStart(Unit* who)
            {
                if (who)
                    me->Attack(who, false);
            }

            void DoAction(const int32 action)
            {
                if (action == ACTION_START_EVENT)
                {
                    eventphase = 1;
                    summons.DespawnAll();
                    events.ScheduleEvent(EVENT_START_EVENT, 10000);
                }
				switch (action)
				{
				case ACTION_TEAR:
					events.ScheduleEvent(EVENT_FALL, 1000);
					break;
				default:
					break;
				}
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim() && !eventphase)
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (phase == 0 && me->HealthBelowPct(80))
                {
                    phase = 1;
                    Talk(SAY_80);
                    DoCast(me, SPELL_LUNAR_GUIDANCE);
                    return;
                }
                else if (phase == 1 && me->HealthBelowPct(55))
                {
                    phase = 2;
                    Talk(SAY_55);
                    DoCast(me, SPELL_LUNAR_GUIDANCE);
                    return;
                }
                else if (phase == 2 && me->HealthBelowPct(30))
                {
                    phase = 3;
                    Talk(SAY_30);
                    DoCast(me, SPELL_TEARS_OF_ELUNE);
                    return;
                }

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_START_EVENT:
                            events.ScheduleEvent(EVENT_SUMMON_POOL, 2000);
                            events.ScheduleEvent(EVENT_SUMMON_ADDS, 5000);
                            events.ScheduleEvent(EVENT_CHECK_PLAYERS, 5000);
                            break;
                        case EVENT_SUMMON_POOL:
                            switch (eventphase)
                            {
                                case 1: Talk(SAY_LIGHT_1); break;
                                case 2: Talk(SAY_LIGHT_2); break;
                                case 3: Talk(SAY_LIGHT_3); break;
                                case 4: Talk(SAY_LIGHT_4); break;
                                case 5: Talk(SAY_LIGHT_5); break;
                                default: break;
                            }
                            curPool = NULL;
                            curPool = me->SummonCreature(NPC_POOL_OF_MOONLIGHT, poolPos[eventphase - 1], TEMPSUMMON_TIMED_DESPAWN, 40000);
                            if (eventphase < 5)
                            {
                                switch (eventphase)
                                {
                                    case 2: Talk(SAY_INTRO_2); break;
                                    case 3: Talk(SAY_INTRO_3); break;
                                    case 4: Talk(SAY_INTRO_4); break;
                                    default: break;
                                }
                                eventphase++;
                                events.ScheduleEvent(EVENT_SUMMON_POOL, 45000);
                            }
                            else
                            {
                                Talk(SAY_INTRO_5);
                                events.ScheduleEvent(EVENT_STOP_EVENT, 30000);
                                events.ScheduleEvent(EVENT_STOP_EVENT_1, 40000);
                            }
                            break;
                        case EVENT_SUMMON_ADDS:
                        {
                            if (Player* pPlayer = me->FindNearestPlayer(500.0f))
                            {
                                Position pos;
                                pPlayer->GetRandomNearPosition(pos, frand(15.0f, 20.0f));
                                uint32 entry = NPC_TIME_TWISTED_NIGHTSABER_1;
                                switch (urand(1, eventphase))
                                {
                                    case 1: entry = NPC_TIME_TWISTED_NIGHTSABER_1; break;
                                    case 2: entry = NPC_TIME_TWISTED_NIGHTSABER_2; break;
                                    case 3: entry = NPC_TIME_TWISTED_NIGHTSABER_3; break;
                                    case 4: entry = NPC_TIME_TWISTED_SENTINEL; break;
                                    case 5: entry = NPC_TIME_TWISTED_HUNTRESS; break;
                                }
                                if (Creature* pCreature = me->SummonCreature(entry, pos))
                                    pCreature->AI()->AttackStart(pPlayer);
                            }
                            
                            events.ScheduleEvent(EVENT_SUMMON_ADDS, urand(5000, 10000));
                            break;
                        }
                        case EVENT_CHECK_PLAYERS:
                        {
                            uint8 num = 0;
                            Map::PlayerList const &playerList = instance->instance->GetPlayers();
                            if (!playerList.isEmpty())
                                for (Map::PlayerList::const_iterator itr = playerList.begin(); itr != playerList.end(); ++itr)
                                    if (Player* pPlayer = itr->getSource())
                                        if (pPlayer->GetAreaId() == AREA_EMERALD && pPlayer->isAlive())
                                            num++;
                            
                            if (!num)
                            {
                                summons.DespawnAll();
                                events.CancelEvent(EVENT_SUMMON_ADDS);
                                events.CancelEvent(EVENT_SUMMON_POOL);
                                events.CancelEvent(EVENT_CHECK_PLAYERS);
                                events.CancelEvent(EVENT_STOP_EVENT);
                                events.CancelEvent(EVENT_STOP_EVENT_1);
                                eventphase = 0;
                                instance->SetData(DATA_TYRANDE_EVENT, NOT_STARTED);
								Reset();
                            }
                            else
                                events.ScheduleEvent(EVENT_CHECK_PLAYERS, 5000);
                            break;
                        }
                        case EVENT_STOP_EVENT:
                            events.CancelEvent(EVENT_SUMMON_ADDS);
                            events.CancelEvent(EVENT_SUMMON_POOL);
                            break;
                        case EVENT_STOP_EVENT_1:
                            Talk(SAY_LIGHT_6);
                            DoCastAOE(SPELL_ACHIEVEMENT);
                            events.CancelEvent(EVENT_CHECK_PLAYERS);
                            me->SetUInt32Value(UNIT_FIELD_BYTES_1, 0);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
                            me->RemoveAura(SPELL_IN_SHADOW);
							DespawnCreatures(NPC_TIME_TWISTED_NIGHTSABER_1);
							DespawnCreatures(NPC_TIME_TWISTED_NIGHTSABER_2);
							DespawnCreatures(NPC_TIME_TWISTED_NIGHTSABER_3);
							DespawnCreatures(NPC_TIME_TWISTED_HUNTRESS);
							DespawnCreatures(NPC_TIME_TWISTED_SENTINEL);
                            if (Creature* pStalker = me->SummonCreature(NPC_STALKER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f))
                            {
                                pStalker->RemoveAllAuras();
                                pStalker->CastSpell(pStalker, SPELL_MOONLIGHT_COSMETIC, true);
								//pStalker->CastSpell(pStalker, SPELL_DARK_MOONLIGHT, true);
                            }
							/*if (Player* pPlayer = me->FindNearestPlayer(25.0f))
							{
								pPlayer->CastSpell(pPlayer, SPELL_DARK_MOONLIGHT, true);
							}
							else
							{
								pPlayer->RemoveAura(SPELL_DARK_MOONLIGHT);
							}*/
                            instance->SetData(DATA_TYRANDE_EVENT, DONE);
                            break;
                        case EVENT_MOONBOLT:
                            DoCastVictim(SPELL_MOONBOLT);
							/*if (Player* pPlayer = me->FindNearestPlayer(25.0f))
							{
								pPlayer->CastSpell(pPlayer, SPELL_DARK_MOONLIGHT, true);
							}
							else
							{
								pPlayer->RemoveAura(SPELL_DARK_MOONLIGHT);
							}*/
                            events.ScheduleEvent(EVENT_MOONBOLT, 3000);
                            break;
                        case EVENT_MOONLANCE:
                        {
                            Unit* pTarget;
                            pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, -10.0f, true);
                            if (!pTarget)
                                pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true);
                            if (pTarget)
                            {
                                if (roll_chance_i(20))
                                    Talk(SAY_MOONLANCE);
                                moonlanceGUID = pTarget->GetGUID();
                                DoCast(pTarget, SPELL_MOONLANCE_SUMMON_1);
                            }
                            events.ScheduleEvent(EVENT_MOONLANCE, urand(12500, 13000));
                            break;
                        }
                        case EVENT_STARDUST:
                            DoCastAOE(SPELL_STARDUST);
                            events.ScheduleEvent(EVENT_STARDUST, urand(7000, 8000));
                            break;
                        case EVENT_EYES_OF_GODDESS:
                            //Talk(SAY_EYES); //Repeat many time because de timer set, change in the future
							DoCast(me, SPELL_EYES_OF_GODDESS);
							events.ScheduleEvent(EVENT_EYES_OF_GODDESS, 3000);
                            break;
						case EVENT_FALL:
							DoCast(me, SPELL_TEARS_OF_ELUNE_MISSILE);
							events.ScheduleEvent(EVENT_FALL, 1000);
							break;
                        default:
                            break;
                    }
                }
            }
			void DespawnCreatures(uint32 entry)
			{
				std::list<Creature*> creatures;
				GetCreatureListWithEntryInGrid(creatures, me, entry, 1000.0f);

				if (creatures.empty())
					return;

				for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
					(*iter)->DespawnOrUnsummon();
			}
        private:
            uint8 phase; 
            uint64 moonlanceGUID;
            uint8 eventphase;
            Unit* curPool;
        };
};

class npc_echo_of_tyrande_moonlance : public CreatureScript
{
    public:
        npc_echo_of_tyrande_moonlance() : CreatureScript("npc_echo_of_tyrande_moonlance") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_echo_of_tyrande_moonlanceAI(pCreature);
        }

        struct npc_echo_of_tyrande_moonlanceAI : public Scripted_NoMovementAI
        {
            npc_echo_of_tyrande_moonlanceAI(Creature*  pCreature) : Scripted_NoMovementAI(pCreature)
            {
				instance = me->GetInstanceScript();
                me->SetReactState(REACT_PASSIVE);
                me->SetSpeed(MOVE_RUN, (me->GetEntry() == NPC_MOONLANCE_1 ? 0.6f : 0.9f), true);
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
				DoCast(me, SPELL_MOONLANCE_AURA);
				/*DoCast(me, SPELL_MOONLANCE_DMG);
				DoCast(me, SPELL_MOONLANCE_STUN);*/
				timer = 3500;
				Despawn = false;
            }
			void Reset()
			{
				DoCast(me, SPELL_MOONLANCE_DMG);
				DoCast(me, SPELL_MOONLANCE_STUN);
			}
            //void AttackStart(Unit* /*who*/) { return; }

            /*void MovementInform(uint32 type, uint32 data)
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                if (data == POINT_MOONLANCE)
                {
                    if (me->GetEntry() == NPC_MOONLANCE_1)
                    {
                        Position pos1_1, pos1_2, pos2_1, pos2_2, pos3_1, pos3_2;
                        me->GetNearPosition(pos1_1, 3.0f, -(M_PI / 4.0f));
                        me->GetNearPosition(pos1_2, 30.0f, -(M_PI / 4.0f)); 
                        me->GetNearPosition(pos2_1, 3.0f, 0.0f); 
                        me->GetNearPosition(pos2_2, 30.0f, 0.0f); 
                        me->GetNearPosition(pos3_1, 3.0f, (M_PI / 4.0f)); 
                        me->GetNearPosition(pos3_2, 30.0f, (M_PI / 4.0f));
                        if (Creature* pLance1 = me->SummonCreature(NPC_MOONLANCE_2_1, pos1_1, TEMPSUMMON_TIMED_DESPAWN, 30000))
                            pLance1->GetMotionMaster()->MovePoint(POINT_MOONLANCE, pos1_2);
                        if (Creature* pLance2 = me->SummonCreature(NPC_MOONLANCE_2_2, pos2_1, TEMPSUMMON_TIMED_DESPAWN, 30000))
                            pLance2->GetMotionMaster()->MovePoint(POINT_MOONLANCE, pos2_2);
                        if (Creature* pLance3 = me->SummonCreature(NPC_MOONLANCE_2_3, pos3_1, TEMPSUMMON_TIMED_DESPAWN, 30000))
                            pLance3->GetMotionMaster()->MovePoint(POINT_MOONLANCE, pos3_2);
                    }

                    me->DespawnOrUnsummon(500);
                }
            }*/
InstanceScript* instance;
uint32 timer;
bool Despawn;

void UpdateAI(uint32 const diff)
{
	if (timer <= diff && !Despawn)
	{
		Despawn = true;
		if (me->GetEntry() == NPC_MOONLANCE_1)
		{
			me->SummonCreature(NPC_MOONLANCE_2_1, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation() - 0.7f);
			me->SummonCreature(NPC_MOONLANCE_2_2, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
			me->SummonCreature(NPC_MOONLANCE_2_3, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation() + 0.7f);
		}
		me->DespawnOrUnsummon(600);
	}
	else timer -= diff;

	float x, y, z;
	me->GetClosePoint(x, y, z, me->GetObjectSize() / 3);
	me->GetMotionMaster()->MovePoint(0, x, y, z);
}
        };
};

class npc_echo_of_tyrande_pool_of_moonlight : public CreatureScript
{
    public:
        npc_echo_of_tyrande_pool_of_moonlight() : CreatureScript("npc_echo_of_tyrande_pool_of_moonlight") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_echo_of_tyrande_pool_of_moonlightAI(pCreature);
        }

        struct npc_echo_of_tyrande_pool_of_moonlightAI : public Scripted_NoMovementAI
        {
            npc_echo_of_tyrande_pool_of_moonlightAI(Creature*  pCreature) : Scripted_NoMovementAI(pCreature)
            {
                me->SetReactState(REACT_PASSIVE);
				me->AddAura(SPELL_MOONLIGHT, me);
            }

            uint32 uiShrinkTimer;
            uint32 uiDespawnTimer;

            void Reset()
            {
                uiShrinkTimer = 5000;
                uiDespawnTimer = 60000;
            }

            void UpdateAI(const uint32 diff)
            {
                if (uiDespawnTimer <= diff)
                {
                    uiDespawnTimer = 60000;
                    me->DespawnOrUnsummon(500);
                }
                else
                    uiDespawnTimer -= diff;

                if (uiShrinkTimer <= diff)
                {
                    uiShrinkTimer = 2000;
                    DoCast(me, SPELL_SHRINK, true);
                }
                else
                    uiShrinkTimer -= diff;
            }
        };
};

class spell_echo_of_tyrande_tears_of_elune_script : public SpellScriptLoader
{
    public:
        spell_echo_of_tyrande_tears_of_elune_script() : SpellScriptLoader("spell_echo_of_tyrande_tears_of_elune_script") { }

        class spell_echo_of_tyrande_tears_of_elune_script_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_echo_of_tyrande_tears_of_elune_script_SpellScript);

            void HandleDummy(SpellEffIndex /*effIndex*/)
			{
				if(!GetCaster() || !GetHitUnit())
					return;

                if (roll_chance_i(50))
                    GetCaster()->CastSpell(GetHitUnit(), SPELL_TEARS_OF_ELUNE_MISSILE, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_echo_of_tyrande_tears_of_elune_script_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_echo_of_tyrande_tears_of_elune_script_SpellScript();
        }
};

class at_et_tyrande : public AreaTriggerScript
{
    public:
        at_et_tyrande() : AreaTriggerScript("at_et_tyrande") { }

        bool OnTrigger(Player* pPlayer, const AreaTriggerEntry* /*pAt*/)
        {
            if (!pPlayer)
                return true;

            if (pPlayer->IsBeingTeleported() || pPlayer->isBeingLoaded())
                return true;

            if (InstanceScript* pInstance = pPlayer->GetInstanceScript())
            {
                if (pInstance->GetData(DATA_TYRANDE_EVENT) != IN_PROGRESS && 
                    pInstance->GetData(DATA_TYRANDE_EVENT) != DONE)
                {
                    if (Creature* pTyrande = ObjectAccessor::GetCreature(*pPlayer, pInstance->GetData64(DATA_ECHO_OF_TYRANDE)))
                    {
                        pTyrande->AI()->Talk(SAY_INTRO_1);
                        pTyrande->AI()->DoAction(ACTION_START_EVENT);
                        pInstance->SetData(DATA_TYRANDE_EVENT, IN_PROGRESS);
                    }
                }
            }

            return true;
        }
};

class thrash_tyrande : public CreatureScript
{
public:
	thrash_tyrande() : CreatureScript("thrash_tyrande") { }

	struct thrash_tyrandeAI : public ScriptedAI
	{
		thrash_tyrandeAI(Creature* creature) : ScriptedAI(creature)
		{
			instance = me->GetInstanceScript();
			me->AddAura(SPELL_IN_SHADOW, me);
		}

		InstanceScript* instance;


		void UpdateAI(uint32 const diff)
		{
			if (Creature * pool = me->FindNearestCreature(NPC_POOL_OF_MOONLIGHT, 5.0f))
			{
				if (me->HasAura(SPELL_IN_SHADOW))
					me->RemoveAura(SPELL_IN_SHADOW);
			}
			else
			{
				if (!me->HasAura(SPELL_IN_SHADOW))
					me->AddAura(SPELL_IN_SHADOW, me);
				if (!me->HasAura(SPELL_CANCEL_SHADOW))
					me->RemoveAura(SPELL_CANCEL_SHADOW);
			}
			DoMeleeAttackIfReady();
		}

		/*void JustDied(Unit* killer)
		{
			if (Creature * pool = me->FindNearestCreature(54508, 10.0f))
			{
				pool->SetObjectScale(pool->GetFloatValue(OBJECT_FIELD_SCALE_X) - 0.05);
				Creature * NewCreature = me->FindNearestCreature(RAND(54688, 54699, 54700, 54701, 54512), 40.0f);
				for (uint8 i = 0; i<4; ++i)
					NewCreature = me->FindNearestCreature(RAND(54688, 54699, 54700, 54701, 54512), 40.0f);

				if (!NewCreature)
					me->SummonCreature(RAND(54688, 54699, 54700, 54701, 54512), me->GetPositionX() + urand(0, 20), me->GetPositionY() + urand(0, 20), me->GetPositionZ());
				else
					NewCreature->AI()->AttackStart(killer);
			}

		}*/
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new thrash_tyrandeAI(creature);
	}
};

class dark_moonlight : public CreatureScript
{
public:
	dark_moonlight() : CreatureScript("dark_moonlight") { }

	struct dark_moonlightAI : public ScriptedAI
	{
		dark_moonlightAI(Creature* creature) : ScriptedAI(creature)
		{
			instance = me->GetInstanceScript();
			me->SetReactState(REACT_PASSIVE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
			//DoCastAOE(SPELL_DARK_MOONLIGHT);
		}

		void DoAction(int32 const action)
		{
			switch (action)
			{
			case ACTION_TEAR:
				events.ScheduleEvent(EVENT_FALL, 1000);
				break;
			default:
				break;
			}
		}

		void UpdateAI(uint32 const diff)
		{
			if (!UpdateVictim())
				return;

			events.Update(diff);
			/*if (Player * pPlayer = me->FindNearestPlayer(NPC_STALKER, 25.0f))
			{
				if (!me->HasAura(SPELL_DARK_MOONLIGHT))
					me->AddAura(SPELL_DARK_MOONLIGHT, pPlayer);
			}
			else
			{
				if (me->HasAura(SPELL_DARK_MOONLIGHT))
					me->RemoveAura(SPELL_DARK_MOONLIGHT);			
			}*/
			
			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_FALL:
					DoCast(me, SPELL_TEARS_OF_ELUNE_MISSILE);
					events.ScheduleEvent(EVENT_FALL, 1000);
					break;

				default:
					break;
				}
			}
		}


		InstanceScript* instance;

	private:
		EventMap events;

	};



	CreatureAI* GetAI(Creature* creature) const
	{
		return new dark_moonlightAI(creature);
	}
};

class eyes_of_elune : public CreatureScript
{
public:
	eyes_of_elune() : CreatureScript("eyes_of_elune") { }

	struct eyes_of_eluneAI : public ScriptedAI
	{
		eyes_of_eluneAI(Creature* creature) : ScriptedAI(creature)
		{
			instance = me->GetInstanceScript();
			me->SetReactState(REACT_PASSIVE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
			DoCast(me, SPELL_PIERCING_GAZE_OF_ELUNE_AURA);
			timer = 100;
			if (me->GetEntry() == NPC_EYE_OF_ELUNE_5)
				num = 3;
			else
				num = 0;
		}

		InstanceScript* instance;
		uint32 timer, num;

		void UpdateAI(uint32 const diff)
		{
			if (timer <= diff)
			{
				me->GetMotionMaster()->MovePoint(0, EluneEyes[num]);
				if (num == 5)
					num = 0;
				else
					++num;
				timer = 3000;
			}
			else timer -= diff;
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new eyes_of_eluneAI(creature);
	}
};

void AddSC_boss_echo_of_tyrande()
{
    new boss_echo_of_tyrande();
    new npc_echo_of_tyrande_moonlance();
    new npc_echo_of_tyrande_pool_of_moonlight();
    new spell_echo_of_tyrande_tears_of_elune_script();
    new at_et_tyrande();
	new thrash_tyrande();
	new eyes_of_elune();
}
