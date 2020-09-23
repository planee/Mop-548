#include "ScriptPCH.h"
#include "bastion_of_twilight.h"

enum ValionaScriptTexts
{
    SAY_VALIONA_INTRO_1        = 0,
    SAY_VALIONA_INTRO_2        = 1,
    SAY_VALIONA_KILL        = 2,
    SAY_VALIONA_DEATH        = 3,
    SAY_VALIONA_DEEP        = 4,
    SAY_VALIONA_BLACKOUT    = 5,
};
enum TheralionScriptTexts
{
    SAY_THERALION_INTRO_1    = 0,
    SAY_THERALION_INTRO_2    = 1,
    SAY_THERALION_KILL        = 2,
    SAY_THERALION_DEATH        = 3,
    SAY_THERALION_DAZ1        = 4,
    SAY_THERALION_DAZ2        = 5,
    SAY_THERALION_MAGIC1    = 6,
    SAY_THERALION_MAGIC2    = 7,
};

enum Spells
{
    //valiona
    SPELL_BLACKOUT                    = 86788,
    SPELL_BLACKOUT_DMG                = 86825,
	SPELL_DEVOURING_FLAMES            = 86840,
	SPELL_DEVOURING_FLAMES_DMG        = 86844,
	SPELL_DEVOURING_FLAMES_SUMMON     = 90945,
	SPELL_TWILIGHT_METEORITE          = 86013,
    SPELL_TWILIGHT_METEORITE_DMG      = 86014,
    SPELL_TWILIGHT_METEORITE_MARK     = 88518,
    SPELL_DEEP_BREATH                 = 86059,
    SPELL_TWILIGHT_FLAMES_TRIGGER     = 86194,
    SPELL_TWILIGHT_FLAME_DMG_1        = 86199, //бьет по обычному миру
    SPELL_TWILIGHT_FLAME_DMG_2        = 86228, //бьет по сумеречному миру
    SPELL_COSMETIC_TWILIGHT_BREATH    = 78954, //возможно неверный

    //theralion
    SPELL_ENGULFING_MAGIC                             = 86607,
    SPELL_ENGULFING_MAGIC_AURA                        = 86622,
    SPELL_ENGULFING_MAGIC_DMG                         = 86631,
    SPELL_FABOLOUS_FLAMES                             = 86497,
    SPELL_FABOLUOS_FLAMES_SUM                         = 86503,
    SPELL_FABOLOUS_FLAMES_AURA                        = 86506,
    SPELL_FABOLOUS_FLAMES_DMG                         = 86505,
    SPELL_TWILIGHT_BLAST                              = 86369,
    SPELL_TWILIGHT_BLAST_DMG                          = 86371,
    SPELL_DAZZLING_DESTRUCTION                        = 86408,
    SPELL_DAZZLING_DESTRUCTION_STALKER_VISUAL         = 86383,
    SPELL_DAZZLING_DESTRUCTION_SUMMON_MISSILE         = 86380,
	SPELL_DAZZLING_DESTRUCTION_SUMMON                 = 86385,
    SPELL_DAZZLING_DESTRUCTION_MISSILE                = 86386,
    SPELL_DAZZLING_DESTRUCTION_DMG                    = 86406,
	SPELL_DAZZLING_DESTRUCTION_TWILIGHT_DMG           = 93063,

    //twilight ream & mobs spells
    SPELL_TWILIGHT_PROTECTION_BUFF                     = 86415,
    SPELL_TWILIGHT_SHIFT_AURA_1                        = 86202, 
    SPELL_TWILIGHT_SHIFT_AURA_2                        = 88436, 
    SPELL_COLLAPSING_TWILIGHT_PORTAL_VISUAL            = 86291,
    SPELL_UNSTABLE_TWILIGHT_VISUAL                     = 86302,
    SPELL_UNSTABLE_TWILIGHT_DMG                        = 86305,
    SPELL_TWILIGHT_ZONE                                = 86210,
    SPELL_TWILIGHT_ZONE_DMG                            = 86214,
    SPELL_TWILIGHT_RIFT_CHANNEL                        = 93017,
    SPELL_TWILIGHT_RIFT_10H                            = 93010,
    SPELL_RIFT_BLAST_10H                               = 93019,
    SPELL_SHIFTING_REALITY                             = 93055,
    SPELL_TWILIGHT_SHIFT_TRIGGER                       = 93053,
    SPELL_TWILIGHT_SHIFT_STACK                         = 93051,
	SPELL_TWILIGHT_REALM                               = 74807, // Actual shift aura - Phase 32.

    //shared
    SPELL_TWILIGHT_SHIFT_BUFF                        = 86360,
    SPELL_BERSERK                                    = 47008,
};

enum Adds
{
    NPC_DAZZLING_DESTRUCTION_STALKER        = 46374,
    NPC_FABOLOUS_FLAMES                     = 46448,
    NPC_THERALION_FLIGHT_TARGET_STALKER     = 46364,
    NPC_CONVECTIVE_FLAMES                   = 46588,
    NPC_TWILIGHT_FLAMES                     = 40718,
    NPC_UNSTABLE_TWILIGHT                   = 46304, 
    NPC_COLLAPSING_TWILIGHT_PORTAL          = 46301,
    NPC_DEVOURING_FLAMES                    = 48798,
    NPC_TWILIGHT_SENTRY                     = 50008,
    NPC_TWILIGHT_RIFT                       = 50014,
    NPC_VALIONA_STALKER                     = 46147, // ?
    NPC_FLAME_BREATH_TARGET_STALKER         = 46296, 
	NPC_TWILIGHT_FIEND                      = 49864,
};

enum Action
{
    ACTION_THERALION_FLY_START    = 1,
    ACTION_VALIONA_FLY_START    = 2,
    ACTION_VALIONA_FLY_STOP        = 3,
    ACTION_THERALION_FLY_STOP    = 4,
    ACTION_DAZZLING_DESTRUCTION    = 5,
};

enum Points
{
    POINT_LAND        = 1,
    POINT_FLY        = 2,
    POINT_VALIONA_1    = 3,
    POINT_VALIONA_2    = 4,
    POINT_VALIONA_3    = 5,
    POINT_VALIONA_4    = 6,
    POINT_VALIONA_5    = 7,
    POINT_VALIONA_6    = 8,
    POINT_RESET        = 9,
};

enum Events
{
    EVENT_TWILIGHT_BLAST                = 1,
	EVENT_DAZZLING_DESTRUCTION          = 2,
    EVENT_THERALION_ON                    = 8,
    EVENT_BLACKOUT                        = 9,
    EVENT_DEVOURING_FLAMES                = 10,
    EVENT_ENGULFING_MAGIC                = 11,
    EVENT_FABOLOUS_FLAMES                = 12,
    EVENT_DEEP_BREATH                    = 13,
    EVENT_VALIONA_ON                    = 14,
    EVENT_TWILIGHT_METEORITE            = 15,
    EVENT_VALIONA_1                        = 16, 
    EVENT_VALIONA_2                        = 17,
    EVENT_VALIONA_3                        = 18,
    EVENT_VALIONA_4                        = 19,
    EVENT_VALIONA_5                        = 20,
    EVENT_VALIONA_6                            = 21,
    EVENT_TWILIGHT_FLAME_SPAWN                 = 22,
    EVENT_UNSTABLE_TWILIGHT                    = 23,
    EVENT_UNSTABLE_TWILIGHT_DESPAWN            = 24,
    EVENT_COLLAPSING_TWILIGHT_PORTAL           = 25,
    EVENT_TWILIGHT_SENTRY                      = 26,
    EVENT_TWILIGHT_SHIFT_STACK                 = 27,
    EVENT_BERSERK                              = 28,
	EVENT_SUMMON_COLLAPSING_TWILIGHT_PORTAL    = 29,
	EVENT_SUMMON_TWILIGHT_FIEND                = 30,
	EVENT_SUMMON_UNSTABLE_TWILIGHT             = 31,
	EVENT_SUMMON_TWILIGHT_FIEND_DESPAWN        = 32,
	EVENT_DAZZLING_DESTRUCTION_TWILIGHT_DPS    = 33,
	EVENT_TWILIGHT_RIFT_SUMMON                 = 34,
	EVENT_TWILIGHT_ZONE                        = 35,
};

const Position valionatheralionlandPos = {-740.86f, -681.37f, 831.89f};
const Position valionatheralionflightPos = {-740.86f, -681.37f, 861.89f};

const Position valionaOriginalPos = {-741.595f, -633.372f, 836.699f, 4.75136f};
const Position theralionOriginalPos = { -741.556f, -736.176f, 836.698f, 1.5862f};

const Position valionadeepbreathPos[2][3] = 
{
    {
        {-760.49f, -770.87f, 866.68f, 6.17f},
        {-746.55f, -772.22f, 866.68f, 6.17f},
        {-726.25f, -774.00f, 866.68f, 6.17f},
    },
    {
        {-759.03f, -597.33f, 866.68f, 4.65f},
        {-737.71f, -597.60f, 866.68f, 4.65f},
        {-721.66f, -598.78f, 866.68f, 4.65f},
    },
};

const Position valionatwilightflamePos[3][25] = 
{
    {
        {-759.53f, -603.89f, 836.68f, 0.0f},
        {-759.53f, -608.89f, 836.68f, 0.0f},
        {-759.62f, -614.39f, 836.69f, 0.0f},
        {-759.62f, -621.39f, 836.69f, 0.0f},
        {-759.01f, -628.38f, 836.69f, 0.0f},
        {-759.01f, -635.38f, 836.69f, 0.0f},
        {-759.70f, -642.37f, 835.07f, 0.0f},
        {-759.70f, -647.37f, 835.07f, 0.0f},
        {-759.18f, -652.85f, 832.16f, 0.0f},
        {-759.18f, -656.85f, 832.16f, 0.0f},
        {-759.64f, -663.34f, 831.89f, 0.0f},
        {-759.64f, -670.34f, 831.89f, 0.0f},
        {-759.18f, -677.33f, 831.89f, 0.0f},
        {-759.18f, -685.33f, 831.89f, 0.0f},
        {-759.72f, -691.32f, 831.89f, 0.0f},
        {-759.72f, -695.32f, 831.89f, 0.0f},
        {-759.94f, -701.82f, 831.89f, 0.0f},
        {-759.94f, -706.82f, 831.89f, 0.0f},
        {-759.93f, -712.30f, 831.89f, 0.0f},
        {-759.93f, -717.30f, 831.89f, 0.0f},
        {-759.92f, -722.80f, 833.96f, 0.0f},
        {-759.92f, -728.80f, 833.96f, 0.0f},
        {-759.91f, -736.80f, 836.69f, 0.0f},
        {-759.91f, -742.80f, 836.69f, 0.0f},
        {-759.90f, -750.80f, 836.69f, 0.0f},
    },
    {
        {-742.53f, -603.89f, 836.68f, 0.0f},
        {-742.53f, -608.89f, 836.68f, 0.0f},
        {-742.62f, -614.39f, 836.69f, 0.0f},
        {-742.62f, -621.39f, 836.69f, 0.0f},
        {-742.01f, -628.38f, 836.69f, 0.0f},
        {-742.01f, -635.38f, 836.69f, 0.0f},
        {-742.70f, -642.37f, 835.07f, 0.0f},
        {-742.70f, -647.37f, 835.07f, 0.0f},
        {-742.18f, -652.85f, 832.16f, 0.0f},
        {-742.18f, -656.85f, 832.16f, 0.0f},
        {-742.64f, -663.34f, 831.89f, 0.0f},
        {-742.64f, -670.34f, 831.89f, 0.0f},
        {-742.18f, -677.33f, 831.89f, 0.0f},
        {-742.18f, -685.33f, 831.89f, 0.0f},
        {-742.72f, -691.32f, 831.89f, 0.0f},
        {-742.72f, -695.32f, 831.89f, 0.0f},
        {-742.94f, -701.82f, 831.89f, 0.0f},
        {-742.94f, -706.82f, 831.89f, 0.0f},
        {-742.93f, -712.30f, 831.89f, 0.0f},
        {-742.93f, -717.30f, 831.89f, 0.0f},
        {-742.92f, -722.80f, 833.96f, 0.0f},
        {-742.92f, -728.80f, 833.96f, 0.0f},
        {-742.91f, -736.80f, 836.69f, 0.0f},
        {-742.91f, -742.80f, 836.69f, 0.0f},
        {-742.90f, -750.80f, 836.69f, 0.0f},
    },
    {
        {-724.53f, -603.89f, 836.68f, 0.0f},
        {-724.53f, -608.89f, 836.68f, 0.0f},
        {-724.62f, -614.39f, 836.69f, 0.0f},
        {-724.62f, -621.39f, 836.69f, 0.0f},
        {-724.01f, -628.38f, 836.69f, 0.0f},
        {-724.01f, -635.38f, 836.69f, 0.0f},
        {-724.70f, -642.37f, 835.07f, 0.0f},
        {-724.70f, -647.37f, 835.07f, 0.0f},
        {-724.18f, -652.85f, 832.16f, 0.0f},
        {-724.18f, -656.85f, 832.16f, 0.0f},
        {-724.64f, -663.34f, 831.89f, 0.0f},
        {-724.64f, -670.34f, 831.89f, 0.0f},
        {-724.18f, -677.33f, 831.89f, 0.0f},
        {-724.18f, -685.33f, 831.89f, 0.0f},
        {-724.72f, -691.32f, 831.89f, 0.0f},
        {-724.72f, -695.32f, 831.89f, 0.0f},
        {-724.94f, -701.82f, 831.89f, 0.0f},
        {-724.94f, -706.82f, 831.89f, 0.0f},
        {-724.93f, -712.30f, 831.89f, 0.0f},
        {-724.93f, -717.30f, 831.89f, 0.0f},
        {-724.92f, -722.80f, 833.96f, 0.0f},
        {-724.92f, -728.80f, 833.96f, 0.0f},
        {-724.91f, -736.80f, 836.69f, 0.0f},
        {-724.91f, -742.80f, 836.69f, 0.0f},
        {-724.90f, -750.80f, 836.69f, 0.0f},
    },
};

const Position twilightportalPos[1] =
{
{ -745.01f, -688.87f, 831.89f, 0.0f},
};

const Position unstabletwilightPos[10] = 
{
    {-721.71f, -683.42f, 835.89f, 4.64f},
    {-720.54f, -664.70f, 835.89f, 4.64f},
    {-719.21f, -643.19f, 839.32f, 4.64f},
    {-764.23f, -709.56f, 835.90f, 1.44f},
    {-762.20f, -678.75f, 835.89f, 1.44f},
    {-729.50f, -742.50f, 840.69f, 4.64f},
    {-757.44f, -740.75f, 840.69f, 4.64f},
    {-723.40f, -710.33f, 835.89f, 4.64f},
    {-739.04f, -725.81f, 837.82f, 4.64f},
    {-758.30f, -646.80f, 837.87f, 1.44f},
};

const Position collapsingtwilightportalPos [4] = 
{
{ -741.16f, -689.19f, 831.89f, 1.47f },
{ -741.443f, -740.062f, 836.697f, 1.53221f},
{ -742.081f, -631.441f, 836.698f, 4.69689f},
{ -740.7f, -684.502f, 831.889f, 4.68902f},
};

const Position TwilightFiendPos[6] =
{
	{ -719.122f, -764.787f, 836.685f, 2.37939f },
	{ -748.021f, -685.938f, 832.056f, 4.56856f },
	{ -766.021f, -737.965f, 836.778f, 1.35695f },
	{ -742.273f, -625.814f, 836.698f, 1.47548f },
	{ -723.421f, -728.161f, 835.452f, 1.83508f },
	{ -723.421f, -625.814f, 835.452f, 1.83508f },
};

const Position twilightsentryPos [2] = 
{
{-764.286f, -690.384f, 831.891f, 0.40168f},
{-716.943f, -691.795f, 831.893f, 2.94112f},
};

class boss_theralion : public CreatureScript
{
    public:
        boss_theralion() : CreatureScript("boss_theralion") {}

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_theralionAI(pCreature);
        }

        struct boss_theralionAI : public BossAI
        {
            boss_theralionAI(Creature * pCreature) : BossAI(pCreature, DATA_VALIONA_THERALION), summons(me)
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
                _fly = false;
            }

            uint8 _currentWaypoint;
            EventMap events;
            SummonList summons;
			uint32 uiDazzlingDestructionCount;
			uint32 missilecount;
            bool doReset;
            uint32 resetTimer;
            bool _fly;

            void InitializeAI()
            {
                if (!instance || static_cast<InstanceMap*>(me->GetMap())->GetScriptId() != sObjectMgr->GetScriptId(BTScriptName))
                    me->IsAIEnabled = false;
                else if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                if (_fly)
                {
                    me->GetMotionMaster()->MovementExpired();
                    me->GetMotionMaster()->Clear();
                    me->StopMoving();
                    me->GetMotionMaster()->MovePoint(POINT_RESET, theralionOriginalPos);
                    _fly = false;
                    return;
                }
				instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_PROTECTION_BUFF);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_SHIFT_AURA_1);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_SHIFT_AURA_2);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_ZONE_DMG);
				instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_REALM);
                summons.DespawnAll();
                events.Reset();
				uiDazzlingDestructionCount = 0;
				missilecount = 0;
                resetTimer = 500;
                doReset = true;
                me->SetSpeed(MOVE_FLIGHT, 1.5f);
                me->SetCanFly(false);
                me->SetFloatValue(UNIT_FIELD_BOUNDING_RADIUS, 10.0f);
                me->SetFloatValue(UNIT_FIELD_COMBAT_REACH, 10.0f);
                me->SetReactState(REACT_PASSIVE);
				me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
				me->RemoveUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetHealth(me->GetMaxHealth());
                instance->SetData(DATA_HEALTH_VALIONA_THERALION, me->GetMaxHealth());
				me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_TWILIGHT_ZONE, true);
				me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_TWILIGHT_REALM, true);
				SendPhase(1);
                _Reset();
                if (Creature* pValiona = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_VALIONA)))
                    pValiona->AI()->Reset();
            }

            void DamageTaken(Unit* attacker, uint32& damage)
            {
                if (!me || !me->isAlive())
                    return;
                if (attacker->GetGUID() == me->GetGUID())
                    return;
                me->LowerPlayerDamageReq(damage);
                instance->SetData(DATA_HEALTH_VALIONA_THERALION, me->GetHealth() > damage ? me->GetHealth() - damage : 0);
            }

            void KilledUnit(Unit* /*victim*/)
            {
                Talk(SAY_THERALION_KILL);
            }
            
            void DoAction(int32 const action)
            {
                switch(action)
                {
                case ACTION_THERALION_FLY_START:
                    me->SetReactState(REACT_PASSIVE);
                    events.CancelEvent(EVENT_FABOLOUS_FLAMES);
                    events.CancelEvent(EVENT_ENGULFING_MAGIC);
					me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
					me->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
                    _fly = true;
                    me->SetCanFly(true);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
					me->CastStop();
					me->AttackStop();
                    me->GetMotionMaster()->MovePoint(POINT_FLY, valionatheralionflightPos);
                    break;
                case ACTION_THERALION_FLY_STOP:
                    if(Creature* pValiona = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_VALIONA)))
                        pValiona->AI()->DoAction(ACTION_VALIONA_FLY_START);
					me->GetMotionMaster()->MovePoint(POINT_LAND, valionatheralionlandPos);
                    break;
                case ACTION_DAZZLING_DESTRUCTION:
					if (missilecount < 1)
					{
							std::list<Creature*> creatures;
							GetCreatureListWithEntryInGrid(creatures, me, NPC_DAZZLING_DESTRUCTION_STALKER, 1000.0f);
							if (creatures.empty())
								return;
							for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
								me->CastSpell(*iter, SPELL_DAZZLING_DESTRUCTION_MISSILE, true);
							missilecount++;
					}						
                    break;
                }
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                if (me->isInCombat())
                    summon->SetInCombatWithZone();
            }

            void SummmonedCreatureDespawn(Creature* summon)
            {
                summons.Despawn(summon);
            }
            
            void EnterCombat(Unit* who)
            {
				instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                instance->SetData(DATA_HEALTH_VALIONA_THERALION, me->GetMaxHealth());				
				if (IsHeroic())
				{
					me->SummonCreature(NPC_THERALION_FLIGHT_TARGET_STALKER,	-743.81f, -675.18f, 831.90f, 0.0f);
					if (Creature* _zone = me->SummonCreature(NPC_THERALION_FLIGHT_TARGET_STALKER, -743.81f, -675.18f, 831.90f, 0.0f))
					{
						_zone->SetPhaseMask(32, true);
						_zone->CastSpell(_zone, SPELL_TWILIGHT_ZONE, false);
					}
					events.ScheduleEvent(EVENT_TWILIGHT_SENTRY, urand(3000, 7000));					
				}
				events.ScheduleEvent(EVENT_SUMMON_COLLAPSING_TWILIGHT_PORTAL, 10000);
				events.ScheduleEvent(EVENT_SUMMON_TWILIGHT_FIEND, 10000);
				events.ScheduleEvent(EVENT_SUMMON_UNSTABLE_TWILIGHT, 10000);
                events.ScheduleEvent(EVENT_BERSERK, IsHeroic()? 10*MINUTE*IN_MILLISECONDS: 6*MINUTE*IN_MILLISECONDS);
                DoAction(ACTION_THERALION_FLY_START);			
				uiDazzlingDestructionCount = 0;
                if (Creature* pValiona = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_VALIONA)))
                    if (!pValiona->isInCombat())
                        pValiona->SetInCombatWithZone();
                instance->SetBossState(DATA_VALIONA_THERALION, IN_PROGRESS);
				SetUnstableInCombat();
				SetFiendInCombat();
				if (me->GetMap()->IsHeroic())
					SetSentriesInCombat();
            }

            void JustReachedHome()
            {
                _JustReachedHome();
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                instance->SetBossState(DATA_VALIONA_THERALION, FAIL);
            }

            void JustDied(Unit* Killer)
            {
                _JustDied();
				instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_PROTECTION_BUFF);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_SHIFT_AURA_1);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_SHIFT_AURA_2);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_ZONE_DMG);
				instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_REALM);
                me->SetCanFly(false);
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_FLYING);
                summons.DespawnAll();
                Talk(SAY_THERALION_DEATH);
                instance->SetData(DATA_HEALTH_VALIONA_THERALION, 0);
				SendPhase(1);
				instance->SetBossState(DATA_VALIONA_THERALION, DONE);
                if (Creature* pValiona = Unit::GetCreature(*me, instance->GetData64(DATA_VALIONA)))
                    me->Kill(pValiona);
            }

			void SetSentriesInCombat()
			{
				std::list<Creature*> creatures;
				me->GetCreatureListWithEntryInGrid(creatures, NPC_TWILIGHT_SENTRY, 1000.0f);

				if (creatures.empty())
					return;

				for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
					(*iter)->SetInCombatWithZone(); // Set Twilight Realm sentries in combat.
			}

			void SetUnstableInCombat()
			{
				std::list<Creature*> creatures;
				me->GetCreatureListWithEntryInGrid(creatures, NPC_UNSTABLE_TWILIGHT, 1000.0f);

				if (creatures.empty())
					return;

				for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
					(*iter)->SetInCombatWithZone(); // Set Unstable Twilight orbs in combat.
			}

			void SetFiendInCombat()
			{
				std::list<Creature*> creatures;
				me->GetCreatureListWithEntryInGrid(creatures, NPC_TWILIGHT_FIEND, 1000.0f);

				if (creatures.empty())
					return;

				for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
					(*iter)->SetInCombatWithZone(); // Set Twilight Fiend orbs in combat.
			}

			void SendPhase(uint32 newPhaseMask)
			{
				Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
				if (!PlayerList.isEmpty())
				{
					for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
					{
						Player *player = i->getSource();
						player->SetPhaseMask(newPhaseMask, true);
					}
				}
			}
            
            void MovementInform(uint32 type, uint32 id)
            {
                if (type == POINT_MOTION_TYPE)
                {
                    switch (id)
                    {
                        case POINT_LAND:
                            _fly = false;
                            me->SetCanFly(false);
                            me->SetReactState(REACT_AGGRESSIVE);
							me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
							me->RemoveUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
							me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            events.ScheduleEvent(EVENT_FABOLOUS_FLAMES, urand(5000, 8000));
                            events.ScheduleEvent(EVENT_ENGULFING_MAGIC, urand(14000, 16000));
                            if (IsHeroic())
                            {                               
                                events.ScheduleEvent(EVENT_TWILIGHT_SHIFT_STACK, urand(15000, 20000));
                            }
                            AttackStart(me->getVictim());
                            break;
                        case POINT_FLY:                            
                            events.ScheduleEvent(EVENT_TWILIGHT_BLAST, urand(3000, 4000));
							events.ScheduleEvent(EVENT_DAZZLING_DESTRUCTION, 132000);
                            break;
                        case POINT_RESET:
                            events.Reset();
                            me->CastStop();
                            me->AttackStop();
                            Reset();
                            break;
                    }
                }
            }
            
            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (instance->GetData(DATA_HEALTH_VALIONA_THERALION) != 0)
                    me->SetHealth(instance->GetData(DATA_HEALTH_VALIONA_THERALION));
                else
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                if (Creature* pValiona = me->FindNearestCreature(NPC_VALIONA, 500.0f, true))
                {
                    if (me->isInCombat() && !pValiona->isInCombat())
                        pValiona->SetInCombatWithZone();
                    if (!me->HasAura(SPELL_BERSERK) && pValiona->HasAura(SPELL_BERSERK))
                        pValiona->AI()->Reset();
                }

                if (resetTimer <= diff)
                {
                    Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                    if (!PlayerList.isEmpty())
                    {
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        {
                            Player *player = i->getSource();
                            if (player->isAlive())
                            {
                                doReset = false;
                                break;
                            }
                        }
                    }
                    if (doReset)
                    {
                        Reset();
                    }                      

                    resetTimer = 2000;
                }
                else
                    resetTimer -= diff;
                
                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_BERSERK:
                        DoCast(me, SPELL_BERSERK);
                        break;
                    case EVENT_TWILIGHT_SENTRY:
						for (uint8 i = 0; i < 2; i++)
                        if (Creature* _sentry = me->SummonCreature(NPC_TWILIGHT_SENTRY, twilightsentryPos[i]))
                            _sentry->SetPhaseMask(32, true);
						events.ScheduleEvent(EVENT_TWILIGHT_SENTRY, 60000);
                        break;
                    case EVENT_TWILIGHT_SHIFT_STACK:
                        DoCast(me->getVictim(), SPELL_TWILIGHT_SHIFT_STACK);
                        events.ScheduleEvent(EVENT_TWILIGHT_SHIFT_STACK, urand(19000, 20000));
                        break;
                    case EVENT_FABOLOUS_FLAMES:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                            DoCast(target, SPELL_FABOLOUS_FLAMES);
                        events.ScheduleEvent(EVENT_FABOLOUS_FLAMES, urand(14000, 16000));
                        break;
                    case EVENT_ENGULFING_MAGIC:
						me->CastCustomSpell(SPELL_ENGULFING_MAGIC, SPELLVALUE_MAX_TARGETS, RAID_MODE(1, 3, 1, 3), 0, false);
                        events.ScheduleEvent(EVENT_ENGULFING_MAGIC, urand(30000, 40000));
                        break;
                    case EVENT_TWILIGHT_BLAST:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                            DoCast(target, SPELL_TWILIGHT_BLAST);
                        events.ScheduleEvent(EVENT_TWILIGHT_BLAST, urand(3000, 4000));
                        break;
					case EVENT_SUMMON_COLLAPSING_TWILIGHT_PORTAL:
					    {
						uint32 i = urand(0, 3);
						if (Creature* pTwilightPortal = me->SummonCreature(NPC_COLLAPSING_TWILIGHT_PORTAL, collapsingtwilightportalPos[i]))
						{
							pTwilightPortal->SetPhaseMask(32, true);
							pTwilightPortal->setActive(true);
						}							
						events.ScheduleEvent(EVENT_SUMMON_COLLAPSING_TWILIGHT_PORTAL, 60000);
						break;
					    }
					case EVENT_SUMMON_TWILIGHT_FIEND:					
						for (uint8 i = 0; i < 6; i++)
						if (Creature* TwilightFiend = me->SummonCreature(NPC_TWILIGHT_FIEND, TwilightFiendPos[i]))
							TwilightFiend->SetPhaseMask(32, true);
						events.ScheduleEvent(EVENT_SUMMON_TWILIGHT_FIEND, 60000);
						break;		
					case EVENT_SUMMON_UNSTABLE_TWILIGHT:
						for (uint8 i = 0; i < 10; i++)
						if (Creature* pUnstableTwilight = me->SummonCreature(NPC_UNSTABLE_TWILIGHT, unstabletwilightPos[i]))
							pUnstableTwilight->SetPhaseMask(32, true);
						events.ScheduleEvent(EVENT_SUMMON_UNSTABLE_TWILIGHT, 60000);
						break;
                     case EVENT_DAZZLING_DESTRUCTION:
                        events.CancelEvent(EVENT_TWILIGHT_BLAST);
						missilecount = 0;
						if (uiDazzlingDestructionCount < 3)
						{
							if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
							{
								me->CastSpell(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), SPELL_DAZZLING_DESTRUCTION_SUMMON_MISSILE, true);
								if(Creature* _stalker1 = me->SummonCreature(NPC_DAZZLING_DESTRUCTION_STALKER, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
									_stalker1->SetPhaseMask(32, true);
							}
							if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
							{
								me->CastSpell(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), SPELL_DAZZLING_DESTRUCTION_SUMMON_MISSILE, true);
								if (Creature* _stalker2 = me->SummonCreature(NPC_DAZZLING_DESTRUCTION_STALKER, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0, TEMPSUMMON_MANUAL_DESPAWN))
									_stalker2->SetPhaseMask(32, true);
							}
							DoCast(me, SPELL_DAZZLING_DESTRUCTION);							
							uiDazzlingDestructionCount++;
							events.ScheduleEvent(EVENT_DAZZLING_DESTRUCTION, 6000);
						}
						else
						{
							Talk(SAY_THERALION_DAZ1);
							events.CancelEvent(EVENT_DAZZLING_DESTRUCTION);
							uiDazzlingDestructionCount = 0; // Revert to initial count for next phase.							
							events.ScheduleEvent(EVENT_THERALION_ON, 100);
						}				              
                        break;
                     case EVENT_THERALION_ON:      
                        me->AI()->DoAction(ACTION_THERALION_FLY_STOP);
                        break;
                    }
                }            
                DoMeleeAttackIfReady();
            }
        };
};

class boss_valiona : public CreatureScript
{
    public:
        boss_valiona() : CreatureScript("boss_valiona") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_valionaAI(pCreature);
        }

        struct boss_valionaAI : public BossAI
        {
            boss_valionaAI(Creature* pCreature) :BossAI(pCreature, DATA_VALIONA_THERALION), summons(me)
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
                _fly = false;
            }

            EventMap events;
            SummonList summons;
            uint8 _currside, _currway;
            uint8 _flamescount;
            bool doReset;
            uint32 resetTimer;
            bool _fly;

            void InitializeAI()
            {
                if (!instance || static_cast<InstanceMap*>(me->GetMap())->GetScriptId() != sObjectMgr->GetScriptId(BTScriptName))
                    me->IsAIEnabled = false;
                else if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                if (_fly)
                {
                    me->GetMotionMaster()->MovementExpired();
                    me->GetMotionMaster()->Clear();
                    me->StopMoving();
                    me->GetMotionMaster()->MovePoint(POINT_RESET, valionaOriginalPos);
                    _fly = false;
                    return;
                }
				instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_PROTECTION_BUFF);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_SHIFT_AURA_1);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_SHIFT_AURA_2);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_ZONE_DMG);
				instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_REALM);
				instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_ZONE);
                summons.DespawnAll();
                events.Reset();
                me->SetSpeed(MOVE_FLIGHT, 1.5f);
                me->SetCanFly(false);
                me->SetFloatValue(UNIT_FIELD_BOUNDING_RADIUS, 10.0f);
                me->SetFloatValue(UNIT_FIELD_COMBAT_REACH, 10.0f);
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                _currside = 0;
                _currway = 0;
                _flamescount = 0;
                resetTimer = 500;
                doReset = true;
                me->SetHealth(me->GetMaxHealth());
                instance->SetData(DATA_HEALTH_VALIONA_THERALION, me->GetMaxHealth());
                instance->SetBossState(DATA_VALIONA_THERALION, NOT_STARTED);
				me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
				me->RemoveUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
				me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_TWILIGHT_ZONE, true);
				me->ApplySpellImmune(0, IMMUNITY_ID, SPELL_TWILIGHT_REALM, true);
                _Reset();
            }

            void DamageTaken(Unit* attacker, uint32& damage)
            {
                if (!me || !me->isAlive())
                    return;
                if (attacker->GetGUID() == me->GetGUID())
                    return;
                me->LowerPlayerDamageReq(damage);
                instance->SetData(DATA_HEALTH_VALIONA_THERALION, me->GetHealth() > damage ? me->GetHealth() - damage : 0);
            }
            
            void KilledUnit(Unit* /*victim*/)
            {
                Talk(SAY_VALIONA_KILL);
            }
            
            void JustReachedHome()
            {
                _JustReachedHome();
                instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                instance->SetBossState(DATA_VALIONA_THERALION, FAIL);
            }

            void JustDied(Unit* Killer)
            {
                _JustDied();
				instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_PROTECTION_BUFF);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_SHIFT_AURA_1);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_SHIFT_AURA_2);
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_ZONE_DMG);
				instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_ZONE);
				instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_TWILIGHT_REALM);
				instance->DoModifyPlayerCurrenciesIfLevel(395, 7500, 85);
                me->SetCanFly(false);
                me->RemoveUnitMovementFlag(MOVEMENTFLAG_FLYING);
                summons.DespawnAll();
                Talk(SAY_VALIONA_DEATH);
                instance->SetData(DATA_HEALTH_VALIONA_THERALION, 0);
                if (Creature* pTheralion = me->Unit::GetCreature(*me, instance->GetData64(DATA_THERALION)))
                    me->Kill(pTheralion);
            }
            
            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                if (me->isInCombat())
                    summon->SetInCombatWithZone();
            }

            void SummonedCreatureDespawn(Creature* summon)
            {
                summons.Despawn(summon);
            }

            void DoAction(int32 const action)
            {
                switch(action)
                {
                case ACTION_VALIONA_FLY_START:
					me->SetReactState(REACT_PASSIVE);
                    events.CancelEvent(EVENT_DEVOURING_FLAMES);
                    events.CancelEvent(EVENT_BLACKOUT);                   
                    events.CancelEvent(EVENT_TWILIGHT_SHIFT_STACK);
                    me->CastStop();
                    me->AttackStop();                    
					me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
					me->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
                    me->SetCanFly(true);
                    _fly = true;
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->GetMotionMaster()->MovePoint(POINT_FLY, valionatheralionflightPos);
                    break;
                case ACTION_VALIONA_FLY_STOP:					
                    if(Creature* pTheralion = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THERALION)))
                        pTheralion->AI()->DoAction(ACTION_THERALION_FLY_START);
                    me->GetMotionMaster()->MovePoint(POINT_LAND, valionatheralionlandPos);
                    break;
                }
            }

            void EnterCombat(Unit* who)
            {
				instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
                events.ScheduleEvent(EVENT_BERSERK, IsHeroic()? 10*MINUTE*IN_MILLISECONDS: 6*MINUTE*IN_MILLISECONDS);
                if (Creature* pTheralion = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_THERALION)))
                    pTheralion->SetInCombatWithZone();
                instance->SetData(DATA_HEALTH_VALIONA_THERALION, me->GetMaxHealth());
                instance->SetBossState(DATA_VALIONA_THERALION, IN_PROGRESS);
				events.ScheduleEvent(EVENT_BLACKOUT, urand(10000, 13000));
				events.ScheduleEvent(EVENT_DEVOURING_FLAMES, urand(26000, 29000));
				 if (IsHeroic())
				 {                            
				   events.ScheduleEvent(EVENT_TWILIGHT_SHIFT_STACK, urand(10000, 20000));
				 }
                DoZoneInCombat();
            }
             
             
            void MovementInform(uint32 type, uint32 id)
            {
                if (type == POINT_MOTION_TYPE)
                {
                    switch (id)
                    {
                    case POINT_LAND:
						me->SetSpeed(MOVE_FLIGHT, 1.5f, true);
                        me->SetCanFly(false);
                        _fly = false;
                        me->SetReactState(REACT_AGGRESSIVE);
						me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
						me->RemoveUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
						me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        events.ScheduleEvent(EVENT_BLACKOUT, urand(10000, 13000));
                        events.ScheduleEvent(EVENT_DEVOURING_FLAMES, urand(26000, 29000));
                        if (IsHeroic())
                        {                            
                            events.ScheduleEvent(EVENT_TWILIGHT_SHIFT_STACK, urand(10000, 20000));
                        }
                        AttackStart(me->getVictim());
                        break;
                    case POINT_FLY:
                        events.ScheduleEvent(EVENT_TWILIGHT_METEORITE, urand(6000, 8000)); 
                        events.ScheduleEvent(EVENT_DEEP_BREATH, 98000);
                        break;
                    case POINT_VALIONA_1:
                        events.ScheduleEvent(EVENT_VALIONA_1, 2000);
                        break;
                    case POINT_VALIONA_2:
                        events.ScheduleEvent(EVENT_VALIONA_2, 1000);
                        break;
                    case POINT_VALIONA_3:
                        events.ScheduleEvent(EVENT_VALIONA_3, 2000);
                        break;
                    case POINT_VALIONA_4:
                        events.ScheduleEvent(EVENT_VALIONA_4, 1000);
                        break;
                    case POINT_VALIONA_5:
                        events.ScheduleEvent(EVENT_VALIONA_5, 1000);
                        break;
                    case POINT_VALIONA_6:
                        events.ScheduleEvent(EVENT_VALIONA_6, 1000);
                        break;
                    case POINT_RESET:
                        events.Reset();
                        me->CastStop();
                        me->AttackStop();
                        Reset();
                        break;
                    }
                }
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if (instance->GetData(DATA_HEALTH_VALIONA_THERALION) != 0)
                    me->SetHealth(instance->GetData(DATA_HEALTH_VALIONA_THERALION));
                else
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

                if (Creature* pTheralion = me->FindNearestCreature(NPC_THERALION, 500.0f, true))
                {
                    if (me->isInCombat() && !pTheralion->isInCombat())
                        pTheralion->SetInCombatWithZone();
                    if (!me->HasAura(SPELL_BERSERK) && pTheralion->HasAura(SPELL_BERSERK))
                        pTheralion->AI()->Reset();
                }


                if (resetTimer <= diff)
                {
                    Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                    if (!PlayerList.isEmpty())
                    {
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        {
                            Player *player = i->getSource();
							if (player->isAlive() || player->isInCombat())
                            {
                                doReset = false;
                                break;
                            }
							else
								doReset = true;
                        }
                    }
                    if (doReset)
                    {
                        Reset();
                    }

                    resetTimer = 2000;
                }
                else
                    resetTimer -= diff;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_BERSERK:
                        DoCast(me, SPELL_BERSERK);
                        break;
                    case EVENT_TWILIGHT_SHIFT_STACK:
                        DoCast(me->getVictim(), SPELL_TWILIGHT_SHIFT_STACK);
                        events.ScheduleEvent(EVENT_TWILIGHT_SHIFT_STACK, urand(19000, 20000));
                        break;
                    case EVENT_BLACKOUT:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                            DoCast(target, SPELL_BLACKOUT);
                        events.ScheduleEvent(EVENT_BLACKOUT, urand(28000, 31000));
                        break;
                    case EVENT_DEVOURING_FLAMES:
						if (Unit* target = me->getVictim())
						{
							me->CastSpell(target, SPELL_DEVOURING_FLAMES_SUMMON, true);
							if (Creature* spTarget = me->FindNearestCreature(NPC_DEVOURING_FLAMES, 100.0f))							
							{
								me->SetReactState(REACT_PASSIVE);
								spTarget->setFaction(target->getFaction());
								spTarget->SetReactState(REACT_AGGRESSIVE);
								me->Attack(spTarget, true);
								spTarget->Attack(me, true);
								me->AddThreat(spTarget, 50000.0f, SPELL_SCHOOL_MASK_NORMAL);
								spTarget->AddThreat(me, 50000.0f, SPELL_SCHOOL_MASK_NORMAL);
								me->SetFacingToObject(spTarget);
								me->CastSpell(spTarget, SPELL_DEVOURING_FLAMES, true);
							}
						}
						me->SetReactState(REACT_AGGRESSIVE);
                        events.ScheduleEvent(EVENT_DEVOURING_FLAMES, urand(38000, 41000));
                        break;
                    case EVENT_TWILIGHT_METEORITE:
                        me->CastCustomSpell(SPELL_TWILIGHT_METEORITE_MARK, SPELLVALUE_MAX_TARGETS, 1, 0, false);
                        events.ScheduleEvent(EVENT_TWILIGHT_METEORITE, urand(9000, 14000));
                        break;
                    case EVENT_DEEP_BREATH:
                        events.CancelEvent(EVENT_TWILIGHT_METEORITE);
						me->SetSpeed(MOVE_FLIGHT, 2.7f, true);
                        Talk(SAY_VALIONA_DEEP);
                        _currside = urand(0, 1);
                        _currway = urand(0, 2);
                        me->GetMotionMaster()->MovePoint(POINT_VALIONA_1, valionadeepbreathPos[_currside][_currway]);
                        break;
                    case EVENT_VALIONA_1:
                        _flamescount = 0;
                        DoCast(me, SPELL_COSMETIC_TWILIGHT_BREATH);
                        events.ScheduleEvent(EVENT_TWILIGHT_FLAME_SPAWN, 500);
                        me->GetMotionMaster()->MovePoint(POINT_VALIONA_2, valionadeepbreathPos[_currside > 0? 0: 1][_currway]);
                        break;
                    case EVENT_VALIONA_2:
                        _currside = _currside > 0? 0: 1;
                        _currway = urand(0, 2);
                        me->GetMotionMaster()->MovePoint(POINT_VALIONA_3, valionadeepbreathPos[_currside][_currway]);
                        break;
                    case EVENT_VALIONA_3:
                        _flamescount = 0;
                        DoCast(me, SPELL_COSMETIC_TWILIGHT_BREATH);
                        events.ScheduleEvent(EVENT_TWILIGHT_FLAME_SPAWN, 500);
                        me->GetMotionMaster()->MovePoint(POINT_VALIONA_4, valionadeepbreathPos[_currside > 0? 0: 1][_currway]);
                        break;
                    case EVENT_VALIONA_4:
                        _currside = _currside > 0? 0: 1;
                        _currway = urand(0, 2);
                        me->GetMotionMaster()->MovePoint(POINT_VALIONA_5, valionadeepbreathPos[_currside][_currway]);
                        break;
                    case EVENT_VALIONA_5:
                        _flamescount = 0;
                        DoCast(me, SPELL_COSMETIC_TWILIGHT_BREATH);
                        events.ScheduleEvent(EVENT_TWILIGHT_FLAME_SPAWN, 500);
                        me->GetMotionMaster()->MovePoint(POINT_VALIONA_6, valionadeepbreathPos[_currside > 0? 0: 1][_currway]);
                        break;
                    case EVENT_VALIONA_6:
                        DoAction(ACTION_VALIONA_FLY_STOP);
                        break;
                    case EVENT_TWILIGHT_FLAME_SPAWN:
                        if (_flamescount < 25)
                        {
							if (_currside == 1)
							{
								if (Creature* flame1 = me->SummonCreature(NPC_TWILIGHT_FLAMES, valionatwilightflamePos[_currway][_flamescount], TEMPSUMMON_MANUAL_DESPAWN, 10000))
									flame1->SetPhaseMask(32, true);
								me->SummonCreature(NPC_TWILIGHT_FLAMES, valionatwilightflamePos[_currway][_flamescount], TEMPSUMMON_TIMED_DESPAWN, 10000);
							}
							else
							{
								if (Creature* flame2 = me->SummonCreature(NPC_TWILIGHT_FLAMES, valionatwilightflamePos[_currway][24 - _flamescount], TEMPSUMMON_MANUAL_DESPAWN, 10000))
									flame2->SetPhaseMask(32, true);
								me->SummonCreature(NPC_TWILIGHT_FLAMES, valionatwilightflamePos[_currway][24 - _flamescount], TEMPSUMMON_TIMED_DESPAWN, 10000);
							}                                
                            _flamescount++;
                            events.ScheduleEvent(EVENT_TWILIGHT_FLAME_SPAWN, 200);
                        }
                        break;
                    default:
                        break;
                    }
                }
                DoMeleeAttackIfReady();      
            }
        };
};

class npc_fabolous_flames : public CreatureScript
{
    public:
        npc_fabolous_flames() : CreatureScript("npc_fabolous_flames") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fabolous_flamesAI(creature);
        }

        struct npc_fabolous_flamesAI : public Scripted_NoMovementAI
        {
            npc_fabolous_flamesAI(Creature* creature) : Scripted_NoMovementAI(creature)
            {
				creature->SetReactState(REACT_PASSIVE);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				creature->DespawnOrUnsummon(45000);
            }

            void IsSummonedBy(Unit* who)
            {
                DoCast(me, SPELL_FABOLOUS_FLAMES_AURA);
            }

            void Reset()
            {                
            }

            void UpdateAI(const uint32 diff)
            {
                if (Creature* valiona = me->FindNearestCreature(NPC_VALIONA, 200.0f, true))
                if (!valiona || !valiona->isInCombat()) // Is dead / evaded.
                    me->DespawnOrUnsummon();

                events.Update(diff);
            }
        };
};

class npc_valiona_twilight_flames : public CreatureScript
{
    public:
        npc_valiona_twilight_flames() : CreatureScript("npc_valiona_twilight_flames") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_valiona_twilight_flamesAI(creature);
        }

        struct npc_valiona_twilight_flamesAI : public Scripted_NoMovementAI
        {
            npc_valiona_twilight_flamesAI(Creature* creature) : Scripted_NoMovementAI(creature)
            {
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				creature->SetReactState(REACT_PASSIVE);
            }

            void Reset()
            {
				DoCast(me, SPELL_TWILIGHT_FLAMES_TRIGGER);
            }

            void UpdateAI(const uint32 diff)
            {
                if (Creature* valiona = me->FindNearestCreature(NPC_VALIONA, 200.0f, true))
                if (!valiona || !valiona->isInCombat()) // Is dead / evaded.
                    me->DespawnOrUnsummon();

                events.Update(diff);
            }
        };
};

class npc_unstable_twilight : public CreatureScript
{
    public:
        npc_unstable_twilight() : CreatureScript("npc_unstable_twilight") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_unstable_twilightAI(creature);
        }

        struct npc_unstable_twilightAI : public ScriptedAI
        {
            npc_unstable_twilightAI(Creature* creature) : ScriptedAI(creature)
            {
				creature->SetReactState(REACT_PASSIVE);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				creature->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
				creature->GetMotionMaster()->MoveRandom(50.0f);	
				creature->SetSpeed(MOVE_WALK, 1.3f);
			}

            EventMap events;

            void Reset()
            {				
                DoCast(me, SPELL_UNSTABLE_TWILIGHT_VISUAL);
                events.ScheduleEvent(EVENT_UNSTABLE_TWILIGHT, 1000);
				events.ScheduleEvent(EVENT_UNSTABLE_TWILIGHT_DESPAWN, 60000);
            }

            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_UNSTABLE_TWILIGHT:
                        if (Unit* target = me->SelectNearestTarget(3.0f))
                        {
                            if (target->GetTypeId() == TYPEID_PLAYER && !target->HasAura(SPELL_TWILIGHT_PROTECTION_BUFF))
                            {
                                DoCast(me, SPELL_UNSTABLE_TWILIGHT_DMG);
                                events.ScheduleEvent(EVENT_UNSTABLE_TWILIGHT_DESPAWN, 800);
                            }
                        }
                        events.ScheduleEvent(EVENT_UNSTABLE_TWILIGHT, 1000);
                        break;
                    case EVENT_UNSTABLE_TWILIGHT_DESPAWN:
                        me->DespawnOrUnsummon();
                        break;
                    }
                }
            }
        };
};

class npc_twilight_sentry : public CreatureScript
{
    public:
        npc_twilight_sentry() : CreatureScript("npc_twilight_sentry") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_twilight_sentryAI(creature);
        }

		struct npc_twilight_sentryAI : public ScriptedAI
        {
			npc_twilight_sentryAI(Creature* creature) : ScriptedAI(creature), summons(me)
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

            SummonList summons;

            void Reset()
            {
				me->SetReactState(REACT_PASSIVE);
				events.ScheduleEvent(EVENT_TWILIGHT_RIFT_SUMMON, 1000);
            }

            void JustDied(Unit* killer)
            {
                summons.DespawnAll();
                me->DespawnOrUnsummon();
            }

			void EnterCombat(Unit* who)
			{
				DoZoneInCombat();
			}

			void UpdateAI(const uint32 diff)
			{
				events.Update(diff);

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
					case EVENT_TWILIGHT_RIFT_SUMMON:						   
							if (!me->HasAura(SPELL_TWILIGHT_RIFT_CHANNEL))
								me->AddAura(SPELL_TWILIGHT_RIFT_CHANNEL, me);
							me->SummonCreature(NPC_TWILIGHT_RIFT, me->GetPositionX() + frand(1.0f, 20.0f), me->GetPositionY() + frand(1.0f, 20.0f), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN);
							if (Creature* rift = me->SummonCreature(NPC_TWILIGHT_RIFT, me->GetPositionX() + frand(1.0f, 20.0f), me->GetPositionY() + frand(1.0f, 20.0f), me->GetPositionZ(), 0, TEMPSUMMON_CORPSE_DESPAWN))
								rift->SetPhaseMask(1, true);
							me->SetReactState(REACT_AGGRESSIVE);
						events.ScheduleEvent(EVENT_TWILIGHT_RIFT_SUMMON, 15100);
						break;
					}
				}
				DoMeleeAttackIfReady();
			}
        };
};

class npc_twilight_rift : public CreatureScript
{
    public:
        npc_twilight_rift() : CreatureScript("npc_twilight_rift") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_twilight_riftAI(creature);
        }

        struct npc_twilight_riftAI : public Scripted_NoMovementAI
        {
            npc_twilight_riftAI(Creature* creature) : Scripted_NoMovementAI(creature)
            {
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
                me->SetCanFly(true);
                pInstance = creature->GetInstanceScript();
				creature->GetMotionMaster()->MoveRandom(50.0f);
				creature->DespawnOrUnsummon(15000);
            }

            InstanceScript* pInstance;
            Unit* sentry;

            void IsSummonedBy(Unit* owner)
            {
                me->SetPosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()+5.0f, me->GetOrientation());
                DoCast(me, SPELL_TWILIGHT_RIFT_10H);
            }

            void JustDied(Unit* killer)
            {
                me->DespawnOrUnsummon();
            }

            void UpdateAI(const uint32 diff)
            {
                if (!pInstance)
                    return;
                if (pInstance->GetBossState(DATA_VALIONA_THERALION) != IN_PROGRESS)
                    me->DespawnOrUnsummon();
            }
            
        };
};

class npc_collapsing_twilight_portal : public CreatureScript
{
    public:
        npc_collapsing_twilight_portal() : CreatureScript("npc_collapsing_twilight_portal") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_collapsing_twilight_portalAI(creature);
			creature->DespawnOrUnsummon(60000);
        }

        bool OnGossipHello(Player* pPlayer, Creature* creature)
        {
            pPlayer->RemoveAurasDueToSpell(SPELL_TWILIGHT_PROTECTION_BUFF);
            pPlayer->RemoveAurasDueToSpell(SPELL_TWILIGHT_SHIFT_AURA_1);
            pPlayer->RemoveAurasDueToSpell(SPELL_TWILIGHT_SHIFT_AURA_2);
            pPlayer->RemoveAurasDueToSpell(SPELL_TWILIGHT_ZONE_DMG);
			pPlayer->SetPhaseMask(1, true);
            return true;
        }

        struct npc_collapsing_twilight_portalAI : public Scripted_NoMovementAI
        {
            npc_collapsing_twilight_portalAI(Creature* creature) : Scripted_NoMovementAI(creature)
            {
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
            }

            EventMap events;

            void Reset()
            {
				me->SetPhaseMask(32, true);
                DoCast(me, SPELL_COLLAPSING_TWILIGHT_PORTAL_VISUAL);
                events.ScheduleEvent(EVENT_COLLAPSING_TWILIGHT_PORTAL, 55000);
            }

            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_COLLAPSING_TWILIGHT_PORTAL:
						me->DespawnOrUnsummon();                                           
                        break;
                    }
                }
            }
        };
};

class npc_dazzling_destruction_stalker : public CreatureScript
{
    public:
        npc_dazzling_destruction_stalker() : CreatureScript("npc_dazzling_destruction_stalker") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_dazzling_destruction_stalkerAI(creature);
        }

        struct npc_dazzling_destruction_stalkerAI : public Scripted_NoMovementAI
        {
            npc_dazzling_destruction_stalkerAI(Creature* creature) : Scripted_NoMovementAI(creature)
            {
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->SetReactState(REACT_PASSIVE);
            }

            void Reset()
            {
                DoCast(me, SPELL_DAZZLING_DESTRUCTION_STALKER_VISUAL);
				events.ScheduleEvent(EVENT_DAZZLING_DESTRUCTION_TWILIGHT_DPS, 6000);
            }

            void SpellHit(Unit* caster, SpellEntry const* spell)
            {
				if (spell->Id == SPELL_DAZZLING_DESTRUCTION_DMG)
				{					
					me->DespawnOrUnsummon();
				}
            }

			void UpdateAI(const uint32 diff)
			{
                    if (Creature* theralion = me->FindNearestCreature(NPC_THERALION, 200.0f, true))
                    if (!theralion || !theralion->isInCombat()) // Is dead / evaded.
                        me->DespawnOrUnsummon();
                
				events.Update(diff);

				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
					case EVENT_DAZZLING_DESTRUCTION_TWILIGHT_DPS:
						if (me->GetPhaseMask() == 32)
						{
							DoCastAOE(SPELL_DAZZLING_DESTRUCTION_TWILIGHT_DMG);
							me->DespawnOrUnsummon();
						}					
						break;
					}
				}
			}
        };
};

class npc_theralion_flight_target_stalker : public CreatureScript
{
    public:
        npc_theralion_flight_target_stalker() : CreatureScript("npc_theralion_flight_target_stalker") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_theralion_flight_target_stalkerAI(creature);
        }

        struct npc_theralion_flight_target_stalkerAI : public Scripted_NoMovementAI
        {
            npc_theralion_flight_target_stalkerAI(Creature* creature) : Scripted_NoMovementAI(creature)
            {
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            }

            void IsSummonedBy(Unit* who)
            {
				events.ScheduleEvent(EVENT_TWILIGHT_ZONE, 1000);
            }

            void Reset()
            {   				
            }

			void UpdateAI(const uint32 diff)
			{

				events.Update(diff);


				while (uint32 eventId = events.ExecuteEvent())
				{
					switch (eventId)
					{
					case EVENT_TWILIGHT_ZONE:
						Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
						if (!PlayerList.isEmpty())
						{
							for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
							{
								Player *player = i->getSource();
								if (player->GetPhaseMask() == 1 && player->HasAura(SPELL_TWILIGHT_ZONE_DMG))
								{
									player->RemoveAura(SPELL_TWILIGHT_ZONE);
									player->RemoveAura(SPELL_TWILIGHT_ZONE_DMG);
								}

							}
						}
						events.ScheduleEvent(EVENT_TWILIGHT_ZONE, 2000);
						break;
					}
				}				
			}
        };
};

class npc_twilight_fiend : CreatureScript
{
public:
	npc_twilight_fiend() : CreatureScript("npc_twilight_fiend") { }

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_twilight_fiendAI(creature);
	}

	struct npc_twilight_fiendAI : public ScriptedAI
	{
		npc_twilight_fiendAI(Creature* creature) : ScriptedAI(creature)
		{			
			creature->GetMotionMaster()->MoveRandom(50.0f);
		}
		
		void Reset()
		{
			me->SetReactState(REACT_PASSIVE);
			events.ScheduleEvent(EVENT_SUMMON_TWILIGHT_FIEND_DESPAWN, 60000);
		}

		void EnterCombat(Unit* who)
		{
			DoZoneInCombat();
		}

		void JustDied(Unit* killer)
		{
			me->DespawnOrUnsummon();
		}

		void IsSummonedBy(Unit* /*summoner*/)
		{
			if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
			{
				me->AI()->AttackStart(target);
			}
		}

		void UpdateAI(const uint32 diff)
		{

			if (me->GetPhaseMask() == 32 && me->GetReactState() == REACT_PASSIVE)
				me->SetReactState(REACT_AGGRESSIVE);

			events.Update(diff);


			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{
				case EVENT_SUMMON_TWILIGHT_FIEND_DESPAWN:
					me->DespawnOrUnsummon();
					break;
				}
			}
			DoMeleeAttackIfReady();
		}
	};
};


class spell_valiona_blackout : public SpellScriptLoader
{
    public:
        spell_valiona_blackout() : SpellScriptLoader("spell_valiona_blackout") { }

        class spell_valiona_blackout_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_valiona_blackout_AuraScript);

            void OnRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (!GetTarget())
                    return;
                if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL ||
                    GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE)
                    GetTarget()->CastSpell(GetTarget(), SPELL_BLACKOUT_DMG, true);
            }
            
            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_valiona_blackout_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_HEAL_ABSORB, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_valiona_blackout_AuraScript();
        }
};

class spell_valiona_twilight_meteorite : public SpellScriptLoader
{
    public:
        spell_valiona_twilight_meteorite() : SpellScriptLoader("spell_valiona_twilight_meteorite") { }

        class spell_valiona_twilight_meteorite_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_valiona_twilight_meteorite_AuraScript);

            void OnApply(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (!GetCaster() || !GetTarget())
                    return;

                GetCaster()->CastSpell(GetTarget(), SPELL_TWILIGHT_METEORITE, false);
            }
            
            void Register()
            {
                OnEffectApply += AuraEffectApplyFn(spell_valiona_twilight_meteorite_AuraScript::OnApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_valiona_twilight_meteorite_AuraScript();
        }
};

class spell_valiona_twilight_flame_dmg_1 : public SpellScriptLoader
{
    public:
        spell_valiona_twilight_flame_dmg_1() : SpellScriptLoader("spell_valiona_twilight_flame_dmg_1") { }


        class spell_valiona_twilight_flame_dmg_1_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_valiona_twilight_flame_dmg_1_SpellScript);

			void HandleDps(SpellEffIndex effIndex)
			{
				if (!GetCaster() || !GetHitUnit())
					return;
				if (GetHitUnit()->GetTypeId() == TYPEID_PLAYER)
				{
					if (GetHitUnit()->HasAura(SPELL_TWILIGHT_REALM) && GetHitUnit()->GetPhaseMask() == 32)
					{
						PreventHitDefaultEffect(EFFECT_0);						
					}
				}
			}

            void HandleScript(SpellEffIndex effIndex)
            {
                if (!GetCaster() || !GetHitUnit())
                    return;

                if (GetHitUnit()->GetTypeId() == TYPEID_PLAYER)
                {					
					if (GetHitUnit()->GetPhaseMask() == 1)
					{
						GetHitUnit()->AddAura(SPELL_TWILIGHT_PROTECTION_BUFF, GetHitUnit());
						GetHitUnit()->AddAura(SPELL_TWILIGHT_REALM, GetHitUnit());
					}
                }
            }



            void Register()
            {
				OnEffectHitTarget += SpellEffectFn(spell_valiona_twilight_flame_dmg_1_SpellScript::HandleDps, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
                OnEffectHitTarget += SpellEffectFn(spell_valiona_twilight_flame_dmg_1_SpellScript::HandleScript, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
				
				
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_valiona_twilight_flame_dmg_1_SpellScript();
        }
};

class spell_valiona_twilight_flame_dmg_2 : public SpellScriptLoader
{
    public:
        spell_valiona_twilight_flame_dmg_2() : SpellScriptLoader("spell_valiona_twilight_flame_dmg_2") { }


        class spell_valiona_twilight_flame_dmg_2_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_valiona_twilight_flame_dmg_2_SpellScript);


            void HandleScript(SpellEffIndex effIndex)
            {
                if (!GetHitUnit())
                    return;

				if (!GetHitUnit()->HasAura(SPELL_TWILIGHT_REALM))
                    PreventHitDefaultEffect(EFFECT_0);
				if (GetHitUnit()->HasAura(SPELL_TWILIGHT_PROTECTION_BUFF))
					SetHitDamage(0);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_valiona_twilight_flame_dmg_2_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_valiona_twilight_flame_dmg_2_SpellScript();
        }
};

class spell_theralion_dazzling_destruction : public SpellScriptLoader
{
    public:
        spell_theralion_dazzling_destruction() : SpellScriptLoader("spell_theralion_dazzling_destruction") { }


        class spell_theralion_dazzling_destruction_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_theralion_dazzling_destruction_SpellScript);


            void HandleScript(SpellEffIndex effIndex)
            {
                if (!GetCaster() || !GetHitUnit() || !GetCaster()->GetAI())
                    return;

                GetCaster()->GetAI()->DoAction(ACTION_DAZZLING_DESTRUCTION);                
            }			

            void Register()
            {
				OnEffectHitTarget += SpellEffectFn(spell_theralion_dazzling_destruction_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_theralion_dazzling_destruction_SpellScript();
        }
};

class spell_theralion_dazzling_destruction_dmg : public SpellScriptLoader
{
    public:
        spell_theralion_dazzling_destruction_dmg() : SpellScriptLoader("spell_theralion_dazzling_destruction_dmg") { }


        class spell_theralion_dazzling_destruction_dmg_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_theralion_dazzling_destruction_dmg_SpellScript);


            void HandleScript(SpellEffIndex effIndex)
            {
                if (!GetCaster() || !GetHitUnit())
                    return;
                if (GetHitUnit()->GetTypeId() == TYPEID_PLAYER)
                {
					GetHitUnit()->AddAura(SPELL_TWILIGHT_REALM, GetHitUnit());
                    GetHitUnit()->AddAura(SPELL_TWILIGHT_PROTECTION_BUFF, GetHitUnit());
                }
				if (GetHitUnit()->GetTypeId() == TYPEID_PLAYER && GetHitUnit()->HasAura(SPELL_TWILIGHT_REALM))
					GetCaster()->CastSpell(GetHitUnit(), SPELL_DAZZLING_DESTRUCTION_TWILIGHT_DMG, true);
            }

            void Register()
            {
				OnEffectHitTarget += SpellEffectFn(spell_theralion_dazzling_destruction_dmg_SpellScript::HandleScript, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_theralion_dazzling_destruction_dmg_SpellScript();
        }
};

class spell_valiona_devouring_flames_dmg : public SpellScriptLoader
{
    public:
        spell_valiona_devouring_flames_dmg() : SpellScriptLoader("spell_valiona_devouring_flames_dmg") { }


        class spell_valiona_devouring_flames_dmg_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_valiona_devouring_flames_dmg_SpellScript);

			void FilterTargets(std::list<WorldObject*>& targets)
			{									
						
		   	   if (targets.empty())
					return;
			   Unit* owner = GetCaster();
			   if (owner)
               {
				   Creature * cValiona = owner->FindNearestCreature(NPC_DEVOURING_FLAMES, 100.0f);
					targets.remove(owner);
					float arc = M_PI; // Cast in 180 grade
					for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    {
                        if (*itr)
                        {
                            if (cValiona->isInFront(*itr, arc))
                                targets.remove((*itr));
                        }						
					}
				}
			}
			void CalculateDamage(SpellEffIndex /*effIndex*/)
			{
				if (!GetHitUnit())
					return;

				float distance = GetCaster()->GetDistance2d(GetHitUnit());

				if (distance > 1.0f)
					SetHitDamage(int32(GetHitDamage() - (2000 * distance))); // Drops by 2000 for every yard the player is away.

				if (GetHitDamage() < 0) // Don't let it go lower then 0.
					SetHitDamage(0);
			}

            void Register()
			{              
				OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_valiona_devouring_flames_dmg_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CONE_ENEMY_24);
				OnEffectHitTarget += SpellEffectFn(spell_valiona_devouring_flames_dmg_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
			}
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_valiona_devouring_flames_dmg_SpellScript();
        }
};

class spell_valiona_devouring_flames : public SpellScriptLoader
{
public:
	spell_valiona_devouring_flames() : SpellScriptLoader("spell_valiona_devouring_flames") { }

	class spell_valiona_devouring_flames_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_valiona_devouring_flames_AuraScript);
		
		void OnPeriodic(constAuraEffectPtr aurEff)
		{
			if (Unit* caster = GetCaster())
			{
				caster->CastSpell(caster, SPELL_DEVOURING_FLAMES_DMG, true);
			}
		}

		void Register()
		{			
			OnEffectPeriodic += AuraEffectPeriodicFn(spell_valiona_devouring_flames_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
		}
	};

	AuraScript* GetAuraScript() const
	{
		return new spell_valiona_devouring_flames_AuraScript();
	}
};

class spell_twilight_shift_stack : public SpellScriptLoader
{
    public:
        spell_twilight_shift_stack() : SpellScriptLoader("spell_twilight_shift_stack") { }


        class spell_twilight_shift_stack_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_twilight_shift_stack_SpellScript);


            void HandleScript(SpellEffIndex effIndex)
            {
                if (!GetCaster() || !GetHitUnit())
                    return;

                uint8 stacks;

                if (AuraPtr aura = GetHitUnit()->GetAura(SPELL_TWILIGHT_SHIFT_STACK))
                {
                    stacks = aura->GetStackAmount();
                    if (stacks > 4)
                    {
                        GetHitUnit()->RemoveAurasDueToSpell(SPELL_TWILIGHT_SHIFT_STACK);
                        GetHitUnit()->CastSpell(GetHitUnit(), SPELL_SHIFTING_REALITY, true);
                    }
                }
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_twilight_shift_stack_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_twilight_shift_stack_SpellScript();
        }
};

class spell_shifting_reality : public SpellScriptLoader
{
    public:
        spell_shifting_reality() : SpellScriptLoader("spell_shifting_reality") { }


        class spell_shifting_reality_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_shifting_reality_SpellScript);


            void HandleScript(SpellEffIndex effIndex)
            {
                if (!GetCaster() || !GetHitUnit())
                    return;
                
				GetHitUnit()->AddAura(SPELL_TWILIGHT_REALM, GetHitUnit());
                GetHitUnit()->AddAura(SPELL_TWILIGHT_PROTECTION_BUFF, GetHitUnit());
				uint32 Damage = GetSpellInfo()->Effects[0].BasePoints;
				if (!Damage)
					return;
				SetHitDamage(Damage);
			}

            void Register()
            {
				OnEffectHitTarget += SpellEffectFn(spell_shifting_reality_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_shifting_reality_SpellScript();
        }
};

//Engulfing Magic 86622
class spell_theralion_engulfing_magic : public SpellScriptLoader
{
public:
	spell_theralion_engulfing_magic() : SpellScriptLoader("spell_theralion_engulfing_magic") { }

	class spell_theralion_engulfing_magic_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_theralion_engulfing_magic_AuraScript);

		void OnProc(constAuraEffectPtr aurEff, ProcEventInfo& eventInfo)
		{

			if (!GetCaster())
				return;

			if (!eventInfo.GetDamageInfo()->GetSpellInfo())
				return;

			if (eventInfo.GetDamageInfo()->GetSpellInfo()->Id == SPELL_ENGULFING_MAGIC_DMG)
				return;

			if (!(eventInfo.GetDamageInfo()->GetDamage()) && !(eventInfo.GetHealInfo()->GetHeal()))
				return;

			if (!(eventInfo.GetDamageInfo()->GetDamageType() == SPELL_DIRECT_DAMAGE) && !(eventInfo.GetDamageInfo()->GetDamageType() == HEAL))
				return;
			
			int32 bp = 0;

				if (!eventInfo.GetDamageInfo()->GetSpellInfo()->IsPositive())
				{
					bp = eventInfo.GetDamageInfo()->GetDamage();
				}
				else
				{
					bp = eventInfo.GetHealInfo()->GetHeal();
				}
			

			if (!bp)
				return;			

			GetCaster()->CastCustomSpell(GetCaster(), SPELL_ENGULFING_MAGIC_DMG, &bp, NULL, NULL, true);

		}

		void Register()
		{
			OnEffectProc += AuraEffectProcFn(spell_theralion_engulfing_magic_AuraScript::OnProc, EFFECT_2, SPELL_AURA_DUMMY);
		}
	};

	AuraScript* GetAuraScript() const
	{
		return new spell_theralion_engulfing_magic_AuraScript();
	}
};

//Called Rift Blast 93019
class spell_twilight_rift_dps : public SpellScriptLoader
{
public:
    spell_twilight_rift_dps() : SpellScriptLoader("spell_twilight_rift_dps") { }


    class spell_twilight_rift_dps_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_twilight_rift_dps_SpellScript);


        void HandleScript(SpellEffIndex effIndex)
        {
            if (!GetCaster() || !GetHitUnit())
                return;

            uint32 Damage = urand(14625, 15375);
            if (!Damage)
                return;
            SetHitDamage(Damage);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_twilight_rift_dps_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_twilight_rift_dps_SpellScript();
    }
};

//Called Unstable Twilight Dmg 86305
class spell_unstable_twilight_dps : public SpellScriptLoader
{
public:
    spell_unstable_twilight_dps() : SpellScriptLoader("spell_unstable_twilight_dps") { }


    class spell_unstable_twilight_dps_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_unstable_twilight_dps_SpellScript);


        void HandleScript(SpellEffIndex effIndex)
        {
            if (!GetCaster() || !GetHitUnit())
                return;

            uint32 Damage = GetSpellInfo()->Effects[0].BasePoints;
            if (!Damage)
                return;
            SetHitDamage(Damage);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_unstable_twilight_dps_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_unstable_twilight_dps_SpellScript();
    }
};

void AddSC_boss_theralion_and_valiona()
{
    new boss_theralion();
    new boss_valiona();
    new npc_dazzling_destruction_stalker();
    new npc_fabolous_flames();
    new npc_valiona_twilight_flames();
    new npc_unstable_twilight();
    new npc_collapsing_twilight_portal();
    new npc_theralion_flight_target_stalker();
    new npc_twilight_sentry();
    new npc_twilight_rift();
	new npc_twilight_fiend();
    new spell_valiona_blackout();	
    new spell_valiona_twilight_meteorite();
    new spell_valiona_twilight_flame_dmg_1();
    new spell_valiona_twilight_flame_dmg_2();
	new spell_valiona_devouring_flames();
	new spell_valiona_devouring_flames_dmg();
    new spell_theralion_dazzling_destruction();
    new spell_theralion_dazzling_destruction_dmg();
	new spell_theralion_engulfing_magic();
    new spell_twilight_shift_stack();
    new spell_shifting_reality();	
    new spell_twilight_rift_dps();
    new spell_unstable_twilight_dps();
}