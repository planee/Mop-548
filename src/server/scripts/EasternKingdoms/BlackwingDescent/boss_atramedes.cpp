#include "ScriptPCH.h"
#include "Spell.h"
#include "blackwing_descent.h"


/* 
43404 - maloriak
43396 - nefarian
43407 - atramedes
43402 - flames
43400 - memory fog

69676 - aura like ghost *all
81271 - potion in hand  *maloriak
81184 - fire aura
81178 - memory fog


INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (334803, 43396, 669, 15, 1, 32440, 0, 150.781, -231.196, 75.5367, 2.21657, 7200, 0, 0, 9877580, 947000, 0, 0, 0, 0);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (334805, 43402, 669, 15, 1, 11686, 0, 166.764, -229.984, 74.9906, 3.12414, 7200, 0, 0, 697410, 62356, 0, 0, 0, 0);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (334806, 43402, 669, 15, 1, 11686, 0, 149.431, -245.88, 74.9906, 0.593412, 7200, 0, 0, 697410, 62356, 0, 0, 0, 0);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (334804, 43404, 669, 15, 1, 33186, 0, 149.757, -207.628, 75.5367, 4.04916, 7200, 0, 0, 30062200, 0, 0, 0, 0, 0);
INSERT INTO `creature` (`guid`, `id`, `map`, `spawnMask`, `phaseMask`, `modelid`, `equipment_id`, `position_x`, `position_y`, `position_z`, `orientation`, `spawntimesecs`, `spawndist`, `currentwaypoint`, `curhealth`, `curmana`, `MovementType`, `npcflag`, `unit_flags`, `dynamicflags`) VALUES (334802, 43407, 669, 15, 1, 399, 0, 136.076, -207.644, 75.5367, 4.76475, 7200, 0, 0, 42, 0, 0, 0, 0, 0);
*/

enum ScriptTexts
{
    SAY_AGGRO    = 0,
    SAY_KILL    = 1,
    SAY_DEATH    = 2,
    SAY_FLAME    = 5,
    SAY_FLY        = 6,
};

enum Spells
{
	// Pre Event
	SPELL_GLOW_ORANGE			= 80857,
	SPELL_BLIND_WHELP			= 81214,
	SPELL_GHOST_VISUAL			= 91218,

    SPELL_MODULATION            = 77612,
    SPELL_MODULATION_25            = 92451,
    SPELL_MODULATION_10H        = 92452,
    SPELL_MODULATION_25H        = 92453,
    SPELL_SONAR_PULSE_AURA        = 77674,
    SPELL_SONAR_PULSE_DMG        = 77675,
    SPELL_SONAR_PULSE_DMG_25    = 92417,
    SPELL_SONAR_PULSE_DMG_10H    = 92418,
    SPELL_SONAR_PULSE_DMG_25H    = 92419,
    SPELL_TRACKING                = 78092,
	SPELL_SONIC_BREATH_SUMMON     = 78091,
    SPELL_SONIC_BREATH            = 78098,
	SPELL_SONIC_BREATH_DPS        = 78100,
    SPELL_SEARING_FLAME_MISSILE    = 77966,
    SPELL_SEARING_FLAME            = 77840,
    SPELL_SEARING_FLAME_1        = 77974,
    SPELL_SEARING_FLAME_DMG        = 77982,
    SPELL_SEARING_FLAME_DMG_25    = 92421,
    SPELL_SEARING_FLAME_DMG_10H    = 92422,
    SPELL_SEARING_FLAME_DMG_25H    = 92423,
    SPELL_DEVASTATION            = 78875,
    SPELL_DEVASTATION_DMG        = 78868,
    SPELL_RESONATING_CLASH        = 77611,
    SPELL_RESONATING_CLASH_1    = 77709,
    SPELL_RESONATING_CLASH_2    = 78168,
    SPELL_VERTIGO                = 77717,
    SPELL_SONIC_FLAMES            = 78864,
    SPELL_SONIC_FLAMES_DMG        = 77782,
    SPELL_SONAR_BOMB            = 92557,
    SPELL_SONAR_BOMB_DMG        = 92553,
    SPELL_SONAR_BOMB_DMG_25        = 92554,
    SPELL_SONAR_BOMB_DMG_10H    = 92555,
    SPELL_SONAR_BOMB_DMG_25H    = 92556,
    SPELL_SONAR_FIREBALL_T        = 78030,
    SPELL_SONAR_FIREBALL        = 78115,
    SPELL_NOISY                    = 78897,
    SPELL_ROARING_FLAME            = 78221,
    SPELL_ROARING_FLAME_DMG        = 78353,
    SPELL_ROARING_FLAME_DMG_25    = 92445,
    SPELL_ROARING_FLAME_DMG_10H    = 92446,
    SPELL_ROARING_FLAME_DMG_25H    = 92447,
    SPELL_ROARING_FLAME_AURA    = 78018,
    SPELL_ROARING_FLAME_AURA_DMG        = 78023,
    SPELL_ROARING_FLAME_AURA_DMG_25        = 92483,
    SPELL_ROARING_FLAME_AURA_DMG_10H    = 92484,
    SPELL_ROARING_FLAME_AURA_DMG_25H    = 92485,
	SPELL_SOUND_AURA                    = 88824,
	SPELL_OBNOXIOUS                     = 92677,
	SPELL_PHASESHIFT                    = 92681,
};

enum Adds
{
    NPC_SONAR_PULSE                = 41546,
    NPC_TRACKING_FLAMES            = 41879,
    NPC_ROARING_FLAME            = 41807,
    NPC_ROARING_FLAME_TARGET    = 42121,
    NPC_ABNOXIOUS_FIEND            = 49740,
    NPC_LORD_VICTOR_NEFARIUS_A    = 43396, // не уверен

    NPC_IMP_PORTAL_STALKER  = 49801,
    NPC_BLIND_DRAGON_TAIL   = 42356,
    NPC_ROARING_FLAME_CASTER = 42345,

    NPC_ATRAMEDES_WHELP            = 43407,
    NPC_MALORIAK_1                = 43404,
    NPC_LORD_VICTOR_NEFARIUS_1    = 49580,
};

enum Actions
{
    ACTION_SHIELD				= 1,
    ACTION_FLAME				= 2,
    ACTION_SHIELD_KILL			= 3,
    ACTION_NEFARIUS_SHIELD		= 4,
    ACTION_ABNOXIOUS_FIEND		= 5,
	ACTION_ACTIVATE_EVENTS		= 6,
};

enum Points
{
	POINT_LAND = 1,
	POINT_FLY = 2,
};

enum Events
{
    EVENT_MODULATION				= 1,
    EVENT_GROUND					= 4,
    EVENT_FLY						= 5,
    EVENT_NEXT_SPELL				= 6,
    EVENT_SONAR_PULSE_MOVE			= 7,
    EVENT_SONAR_FIREBALL			= 8,
    EVENT_SONAR_BOMB				= 9,
    EVENT_ROARING_FLAME				= 10,
    EVENT_ROARING_FLAME_SPD			= 11,
    EVENT_DEVASTATION				= 12,
    EVENT_TRACKING_FLAMES_MOVE		= 13,
    EVENT_ABNOXIOUS_FIEND			= 14,
    EVENT_NEFARIUS_SUMMON_1			= 15,
    EVENT_NEFARIUS_SUMMON_2			= 16,
    EVENT_NEFARIUS_SHIELD			= 17,
	EVENT_KILL_SOUND				= 18,
	EVENT_CHECKSOUND				= 19
};

const Position flyPos = {127.94f, -225.10f, 110.45f, 0.0f};
const Position groundPos = {127.94f, -225.10f, 75.45f, 0.0f};
const uint32 dwarvenshieldsEntry[8] = 
{
    41445,
    42958,
    42947,
    42960,
    42949,
    42951,
    42954,
    42956,
};
const Position dwarvenshieldsPos[8] = 
{
    {169.57f, -262.49f, 76.72f, 2.42f},
    {154.70f, -273.64f, 76.64f, 2.18f},
    {130.48f, -282.24f, 76.72f, 1.46f},
    {106.28f, -276.95f, 76.72f, 1.01f},
    {169.69f, -186.16f, 76.72f, 3.89f},
    {152.00f, -173.88f, 76.72f, 4.29f},
    {129.58f, -167.68f, 76.72f, 4.83f},
    {108.62f, -171.25f, 76.72f, 5.02f}
};

const Position atramedesnefariusspawnPos = {96.54f, -220.32f, 94.90f, 0.06f};

Unit* atramedesTarget; 
Creature* atramedesShield;
//Creature* roaringsummon;
Creature* _shields[8];

class boss_atramedes : public CreatureScript
{
public:
    boss_atramedes() : CreatureScript("boss_atramedes") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_atramedesAI (pCreature);
    }

    struct boss_atramedesAI : public BossAI
    {
        boss_atramedesAI(Creature *pCreature) : BossAI(pCreature, DATA_ATRAMEDES), summons(me) 
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
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			canEnterInCombat = false;
			SetCombatMovement(false);
			me->SetReactState(REACT_PASSIVE);
        }
        
        EventMap events;
        uint8 stage;    //0 - ground, 1 - fly
        uint8 nextspell; // from 0 to 7
        SummonList summons;
		bool canEnterInCombat;	
		bool devastation;
		bool vertigo;
		std::list<Unit*> targets;
		uint32 checkauratimer;

        void InitializeAI()
        {
            if (!instance || static_cast<InstanceMap*>(me->GetMap())->GetScriptId() != sObjectMgr->GetScriptId(BDScriptName))
                me->IsAIEnabled = false;
            else if (!me->isDead())
                Reset();
        }

        void Reset()
        {
            _Reset();
			summons.DespawnAll();
			DespawnCreatures(NPC_ROARING_FLAME);
            for (uint8 i = 0; i < 8; i++)
                _shields[i] = me->SummonCreature(42949, dwarvenshieldsPos[i]);
			
			if (!me->FindNearestCreature(NPC_EVENTFIRE, 1000.f, true)){
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				canEnterInCombat = true;
				SetCombatMovement(true);
				me->SetReactState(REACT_AGGRESSIVE);
			}
			me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
			me->RemoveUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
            me->SetFloatValue(UNIT_FIELD_BOUNDING_RADIUS, 15.0f);
            me->SetFloatValue(UNIT_FIELD_COMBAT_REACH, 15.0f);
			checkauratimer = 1000;
            stage = 0;
            nextspell = 0;
            events.Reset();
            me->SetCanFly(false); 
			devastation = false;
			vertigo = false;
			removeSoundaura();
			
        }

        void DoAction(const int32 action)
        {
            switch (action)
            {
                case ACTION_SHIELD:
                    if (stage == 0)
                    {
                        me->RemoveAurasDueToSpell(SPELL_SEARING_FLAME_1);
                        me->CastStop();
                        DoCast(me, SPELL_VERTIGO);
						Map::PlayerList const &pList = me->GetMap()->GetPlayers();
						for (Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr)
						{
							Player* pPlayer = itr->getSource();
							pPlayer->SetPower(POWER_ALTERNATE_POWER, 0);
							
						}
                    }
					if (stage == 1)
					{
						vertigo = true;
						me->RemoveAurasDueToSpell(SPELL_SEARING_FLAME_1);
						summons.DespawnEntry(NPC_ROARING_FLAME_CASTER);
						summons.DespawnEntry(NPC_ROARING_FLAME_TARGET);
						events.CancelEvent(EVENT_ROARING_FLAME);
						me->CastStop();
						DoCast(me, SPELL_VERTIGO);
						Map::PlayerList const &pList = me->GetMap()->GetPlayers();
						for (Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr)
						{
							Player* pPlayer = itr->getSource();
							pPlayer->SetPower(POWER_ALTERNATE_POWER, 0);

						}
					}
                    break;
                case ACTION_FLAME:
                    events.ScheduleEvent(EVENT_ROARING_FLAME, 5000);
                    break;
                case ACTION_SHIELD_KILL:
                    if (atramedesShield)
                        DoCast(atramedesShield, SPELL_SONIC_FLAMES, true);
                    break;
				case ACTION_ACTIVATE_EVENTS:
					me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
					me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
					canEnterInCombat = true;
					SetCombatMovement(true);
					me->SetReactState(REACT_AGGRESSIVE);					
					break;
            }
        }

        void SummonedCreatureDespawn(Creature* summon)
        {
            summons.Despawn(summon);
        }

        void JustDied(Unit* who)
        {
			removeSoundaura();
            _JustDied();
            summons.DespawnAll();
			DespawnCreatures(NPC_ROARING_FLAME);
            Talk(SAY_DEATH);
			instance->SetBossState(DATA_ATRAMEDES, DONE);
			me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
			me->RemoveUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
			me->SetCanFly(false);
			instance->DoModifyPlayerCurrenciesIfLevel(395, 7500, 85);
        }

        void KilledUnit(Unit* victim)
        {
            Talk(SAY_KILL);
        }

        void JustSummoned(Creature* summon)
        {
            summons.Summon(summon);
            if (me->isInCombat())
                summon->SetInCombatWithZone();
            switch (summon->GetEntry())
            {
            case NPC_ROARING_FLAME_TARGET:
                if (atramedesTarget)
                {
                    summon->GetMotionMaster()->MoveFollow(atramedesTarget, 0.01f, 0.0f);
                }
                break;
			case NPC_ABNOXIOUS_FIEND:
					if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
						summon->AI()->AttackStart(target);
				break;
				
            }
        }

        void EnterCombat(Unit* who)
        {
			if (canEnterInCombat){
				events.ScheduleEvent(EVENT_MODULATION, urand(7000, 10000));
				events.ScheduleEvent(EVENT_NEXT_SPELL, 5000);
				events.ScheduleEvent(EVENT_FLY, 80000);
				events.ScheduleEvent(EVENT_KILL_SOUND, 2000);
				events.ScheduleEvent(EVENT_CHECKSOUND, 3000);
				if (me->GetMap()->IsHeroic())
					events.ScheduleEvent(EVENT_ABNOXIOUS_FIEND, 38500);
				Talk(SAY_AGGRO);
				DoZoneInCombat();
				instance->SetBossState(DATA_ATRAMEDES, IN_PROGRESS);
				addSoundAura();
			}            
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type == POINT_MOTION_TYPE)
            {
                switch (id)
                {
				case POINT_FLY:
                    stage = 1;
					me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    Talk(SAY_FLY);
                    DoCast(me, SPELL_SONAR_FIREBALL_T);
                    events.ScheduleEvent(EVENT_SONAR_BOMB, 4000);
                    events.ScheduleEvent(EVENT_ROARING_FLAME, 2000);	
					events.ScheduleEvent(EVENT_GROUND, 40000);
					events.ScheduleEvent(EVENT_KILL_SOUND, 2000);
                    //me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, false);
                    //me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, false);
                    break;
				case POINT_LAND:					
					me->SetReactState(REACT_AGGRESSIVE);
                    me->SetCanFly(false);
					me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
					me->RemoveUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
                    SetCombatMovement(true);
                    stage = 0;
                    nextspell = 0;
                    events.ScheduleEvent(EVENT_MODULATION, 8000);
                    events.ScheduleEvent(EVENT_NEXT_SPELL, 5000);
                    events.ScheduleEvent(EVENT_FLY, 80000);
					events.ScheduleEvent(EVENT_KILL_SOUND, 2000);
					if (me->GetMap()->IsHeroic())
						events.ScheduleEvent(EVENT_ABNOXIOUS_FIEND, 38500);
                    me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, false);
                    me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, false);
                    me->GetMotionMaster()->MoveChase(me->getVictim());
                    break;
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
			if (!UpdateVictim() || devastation || me->HasUnitState(UNIT_STATE_CASTING))
                return;

			if (checkauratimer <= diff)
			{
				if (me->isInCombat())
				{
					addSoundAura();
					ActiveShield(42949);
				}
			}
			else checkauratimer -= diff;

            events.Update(diff);

			if (me->HasAura(SPELL_VERTIGO) && stage == 1 && vertigo == true)
			{
				events.ScheduleEvent(EVENT_ROARING_FLAME, 8000);
				vertigo = false;
			}
				

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_MODULATION:
                    DoCast(me, SPELL_MODULATION);
                    events.ScheduleEvent(EVENT_MODULATION, urand(18000, 22000));
                    break;
                case EVENT_FLY:
					me->SetReactState(REACT_PASSIVE);
					me->SetByteFlag(UNIT_FIELD_BYTES_1, 3, 0x02);
					me->AddUnitMovementFlag(MOVEMENTFLAG_CAN_FLY | MOVEMENTFLAG_FLYING);
                    me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                    me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
					events.CancelEvent(EVENT_MODULATION);
					events.CancelEvent(EVENT_NEXT_SPELL);
					events.CancelEvent(EVENT_KILL_SOUND);
					if (me->GetMap()->IsHeroic())
						events.CancelEvent(EVENT_ABNOXIOUS_FIEND);
					me->CastStop();
					me->AttackStop();
                    events.Reset();
                    SetCombatMovement(false);
                    me->SetCanFly(true);
					me->GetMotionMaster()->MovePoint(POINT_FLY, flyPos);
                    break;
                case EVENT_GROUND:
					me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
                    me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                    me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
                    me->CastStop();
					me->AttackStop();
					me->SetReactState(REACT_PASSIVE);
					summons.DespawnEntry(NPC_ROARING_FLAME_CASTER);
                    summons.DespawnEntry(NPC_ROARING_FLAME_TARGET);
                    me->RemoveAurasDueToSpell(SPELL_SONAR_FIREBALL_T);
                    events.Reset();
					events.CancelEvent(EVENT_SONAR_BOMB);
					events.CancelEvent(EVENT_ROARING_FLAME);
					events.CancelEvent(EVENT_KILL_SOUND);
					me->GetMotionMaster()->MovePoint(POINT_LAND, groundPos);
                    break;
                case EVENT_NEXT_SPELL:                    
                    if (nextspell > 7)
                        break;
                    switch (nextspell)
                    {
                    case 0:
                    case 2:
                    case 5:
                    case 7:
                        for (uint8 i = 0; i < 3; i++)
                            me->SummonCreature(NPC_SONAR_PULSE,
                                me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f);
                        break;
                    case 1:
                    case 3:
                    case 6:
						if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
						{							
							me->CastSpell(target, SPELL_SONIC_BREATH_SUMMON, true);
							if (Creature* spTarget = me->FindNearestCreature(NPC_TRACKING_FLAMES, 100.0f))
							{
								me->SetReactState(REACT_PASSIVE);
								spTarget->setFaction(target->getFaction());
								spTarget->SetReactState(REACT_AGGRESSIVE);
								me->Attack(spTarget, true);
								spTarget->Attack(me, true);
								me->AddThreat(spTarget, 50000.0f, SPELL_SCHOOL_MASK_NORMAL);
								spTarget->AddThreat(me, 50000.0f, SPELL_SCHOOL_MASK_NORMAL);
								me->SetFacingToObject(spTarget);
								me->CastSpell(spTarget, SPELL_SONIC_BREATH, true);
							}
						}
                        break;
                    case 4:
                        Talk(SAY_FLAME);
                        DoCast(SPELL_SEARING_FLAME_1);
                        DoCast(SPELL_SEARING_FLAME);
                        break;
                    }
                    nextspell++;
                    events.ScheduleEvent(EVENT_NEXT_SPELL, 10000);
                    break;
                case EVENT_SONAR_FIREBALL:
                    me->CastSpell(me, SPELL_SONAR_FIREBALL, true);
                    events.ScheduleEvent(EVENT_SONAR_FIREBALL, 10000);
                    break;
                case EVENT_SONAR_BOMB:
					SelectTargetList(targets, RAID_MODE(3, 6), SELECT_TARGET_RANDOM, 100.0f, true);
					if (!targets.empty())
					for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
						me->CastSpell(*itr, SPELL_SONAR_BOMB, true);						
					events.ScheduleEvent(EVENT_SONAR_BOMB, 18000);
                    break;
                case EVENT_ROARING_FLAME:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                    {
                        atramedesTarget = target;
						Unit* caster = me->SummonCreature(NPC_ROARING_FLAME_CASTER, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 40000);
						if (Unit* roaring = me->SummonCreature(NPC_ROARING_FLAME_TARGET, target->GetPositionX() + urand(5, 9), target->GetPositionY() + urand(5, 9), target->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 40000))
						{
							caster->CastSpell(roaring, SPELL_ROARING_FLAME, true);
							me->SetFacingToObject(roaring);
						}
                    }
                    break;							
				case EVENT_KILL_SOUND:
					checkSounAura();					
					events.ScheduleEvent(EVENT_KILL_SOUND, 2000);
					break;
				case EVENT_CHECKSOUND:
					addSoundAura();
					break;
				case EVENT_ABNOXIOUS_FIEND:
					me->SummonCreature(NPC_ABNOXIOUS_FIEND, 93.767f, -224.105f, 74.911f, 6.26f, TEMPSUMMON_CORPSE_DESPAWN, 30000);
					events.ScheduleEvent(EVENT_ABNOXIOUS_FIEND, 38500);
					break;
                }
            }			
            DoMeleeAttackIfReady();
        }

		private:
			void addSoundAura() {
				std::list<Unit*> targets;
				me->GetAttackableUnitListInRange(targets, 100.f);
				for (Unit* itr : targets) {
					if (!itr)
						continue;
					Player* target = itr->ToPlayer();
					if (target && !target->HasAura(SPELL_SOUND_AURA)) {
						me->AddAura(SPELL_SOUND_AURA, target);
					}
				}
			}

			void removeSoundaura() {
				std::list<Unit*> targets;
				me->GetAttackableUnitListInRange(targets, 100.f);
				for (Unit* itr : targets) {
					if (!itr)
						continue;
					Player* target = itr->ToPlayer();
					if (target) {
						target->RemoveAura(SPELL_SOUND_AURA);
					}
				}
			}

			void checkSounAura(){				
				std::list<Unit*> targets;
				me->GetAttackableUnitListInRange(targets, 100.f);
				for (Unit* itr : targets) {
					if (!itr)
						continue;
					Player* target = itr->ToPlayer();
					if (target && !devastation) {
						if (AuraPtr soundAura = target->GetAura(SPELL_SOUND_AURA)){							
							if (target->GetPower(POWER_ALTERNATE_POWER) >= 100){								
								devastation = true;	
								me->CastSpell(target, SPELL_DEVASTATION, true);
								break;
							}
								
						}
					}
				}
				me->SetReactState(REACT_AGGRESSIVE);
				devastation = false;
			}
			void DespawnCreatures(uint32 entry)
			{
				std::list<Creature*> creatures;
				GetCreatureListWithEntryInGrid(creatures, me, entry, 100.0f);

				if (creatures.empty())
					return;

				for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
					(*iter)->DespawnOrUnsummon();
			}
			void ActiveShield(uint32 entry)
			{
				std::list<Creature*> creatures;
				GetCreatureListWithEntryInGrid(creatures, me, entry, 100.0f);
				if (creatures.empty())
					return;
				for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
				if ((*iter)->isAlive())					
					(*iter)->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
			}		
    };
};

class npc_tracking_flames : public CreatureScript
{
public:
    npc_tracking_flames() : CreatureScript("npc_tracking_flames") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_tracking_flamesAI (pCreature);
    }

    struct npc_tracking_flamesAI : public ScriptedAI
    {
        npc_tracking_flamesAI(Creature* creature) : ScriptedAI(creature) 
        {
        }

        EventMap events;

        void Reset()
        {
        }
        
        void UpdateAI(const uint32 diff)
        {
        }
    };
};

class npc_roaring_flame : public CreatureScript
{
public:
    npc_roaring_flame() : CreatureScript("npc_roaring_flame") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_roaring_flameAI (pCreature);
    }

    struct npc_roaring_flameAI : public ScriptedAI
    {
        npc_roaring_flameAI(Creature* creature) : ScriptedAI(creature) 
        {        
        }

        EventMap events;

        void Reset()
        {
            DoCast(me, SPELL_ROARING_FLAME_AURA);
        }
    };
};

class npc_sonar_pulse : public CreatureScript
{
public:
    npc_sonar_pulse() : CreatureScript("npc_sonar_pulse") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_sonar_pulseAI (pCreature);
    }

    struct npc_sonar_pulseAI : public ScriptedAI
    {
        npc_sonar_pulseAI(Creature* creature) : ScriptedAI(creature) 
        {
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        }

        EventMap events;
        Unit* target;

        void Reset()
        {
            events.ScheduleEvent(EVENT_SONAR_PULSE_MOVE, 1500);
            DoCast(SPELL_SONAR_PULSE_AURA);
        }
        
        void IsSummonedBy(Unit* owner)
        {
            if (owner)
                target = owner->ToCreature()->GetAI()->SelectTarget(SELECT_TARGET_RANDOM);
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type == POINT_MOTION_TYPE)
            {
                if (id == 1)
                {
                    me->DespawnOrUnsummon();
                }
            }            
        }

        void UpdateAI(const uint32 diff)
        {
            Position pos;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_SONAR_PULSE_MOVE:
                    if (target)
                        me->GetNearPosition(pos, 50.0f, me->GetAngle(target->GetPositionX(), target->GetPositionY()));
                    me->GetMotionMaster()->MovePoint(1, pos);
                    break;
                }
            }
        }
    };
};

class npc_roaring_flame_target : public CreatureScript
{
public:
    npc_roaring_flame_target() : CreatureScript("npc_roaring_flame_target") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_roaring_flame_targetAI (pCreature);
    }

    struct npc_roaring_flame_targetAI : public ScriptedAI
    {
        npc_roaring_flame_targetAI(Creature* creature) : ScriptedAI(creature) 
        {
			if (me->GetMap()->IsHeroic())
			{
				me->SetSpeed(MOVE_WALK, 0.95f, true);
				me->SetSpeed(MOVE_RUN, 0.95f, true);
			}
			else
			{
				me->SetSpeed(MOVE_WALK, 0.87f, true);
				me->SetSpeed(MOVE_RUN, 0.87f, true);
			}
            pInstance = creature->GetInstanceScript();
        }
        
        InstanceScript* pInstance;

        void Reset()
        {
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type == POINT_MOTION_TYPE)
            {
                switch (id)
                {
                case 1:
                    if (Creature* atramedes = me->FindNearestCreature(NPC_ATRAMEDES, 100.0f))
                         atramedes->AI()->DoAction(ACTION_FLAME);
                    if (atramedesShield)
                        atramedesShield->DespawnOrUnsummon();
                     me->DespawnOrUnsummon();
                }
            }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!pInstance)
                return;

            if (!me->FindNearestCreature(NPC_ROARING_FLAME, 4.0f))
                me->SummonCreature(NPC_ROARING_FLAME,
                    me->GetPositionX(),
                    me->GetPositionY(),
                    me->GetPositionZ(),
                    0.0f, TEMPSUMMON_TIMED_DESPAWN, 45000);
        }
    };
};

class npc_roaring_flame_caster : public CreatureScript
{
public:
	npc_roaring_flame_caster() : CreatureScript("npc_roaring_flame_caster") { }

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_roaring_flame_casterAI(pCreature);
	}

	struct npc_roaring_flame_casterAI : public ScriptedAI
	{
		npc_roaring_flame_casterAI(Creature* creature) : ScriptedAI(creature)
		{
			me->SetUnitMovementFlags(MOVEMENTFLAG_HOVER);
			me->SetUnitMovementFlags(MOVEMENTFLAG_DISABLE_GRAVITY);
			me->SetReactState(REACT_PASSIVE);
			pInstance = creature->GetInstanceScript();
		}

		InstanceScript* pInstance;

		void Reset()
		{
		}	
	};
};

class npc_atramedes_gong : public CreatureScript
{
public:
    npc_atramedes_gong() : CreatureScript("npc_atramedes_gong") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        InstanceScript* pInstance = pCreature->GetInstanceScript();
        if (!pInstance)
            return false;
        if (pInstance->GetBossState(DATA_ATRAMEDES) != IN_PROGRESS)
            return true;
        if(Creature* atramedes = pCreature->FindNearestCreature(NPC_ATRAMEDES, 200.0f))
        {
            pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            atramedesShield = pCreature;
            atramedesTarget = pPlayer;
            atramedes->AI()->DoAction(ACTION_SHIELD);
        }
        return true;
    }
};

class npc_abnoxious_fiend : public CreatureScript
{
    public:
        npc_abnoxious_fiend() : CreatureScript("npc_abnoxious_fiend") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_abnoxious_fiendAI(creature);
        }

        struct npc_abnoxious_fiendAI : public ScriptedAI
        {
            npc_abnoxious_fiendAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
            }
            
            InstanceScript* pInstance;
			uint32 timerRemoveAura;
			uint32 timerCast;
            void Reset()
            {
				me->AddAura(SPELL_PHASESHIFT, me);
				timerCast = 10000;
				timerRemoveAura = 7000;
            }

            void UpdateAI(const uint32 diff)
            {
                if (!pInstance)
                    return;

				if (timerCast <= diff)
				{
					DoCast(me->getVictim(), SPELL_OBNOXIOUS);
					timerCast = 3000;
				}
				else timerCast -= diff;

				if (timerRemoveAura <= diff && me->HasAura(SPELL_PHASESHIFT))
				{
					me->RemoveAura(SPELL_PHASESHIFT);
				}
				else timerRemoveAura -= diff;

                DoMeleeAttackIfReady();
            }
        };
};

class spell_atramedes_resonating_clash : public SpellScriptLoader
{
    public:
        spell_atramedes_resonating_clash() : SpellScriptLoader("spell_atramedes_resonating_clash") { }

        class spell_atramedes_resonating_clash_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_atramedes_resonating_clash_SpellScript);

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (!GetHitUnit())
                    return;
                GetHitUnit()->CastSpell(GetHitUnit(), SPELL_RESONATING_CLASH, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_atramedes_resonating_clash_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_atramedes_resonating_clash_SpellScript();
        }
};

class spell_atramedes_resonating_clash_1 : public SpellScriptLoader
{
    public:
        spell_atramedes_resonating_clash_1() : SpellScriptLoader("spell_atramedes_resonating_clash_1") { }

        class spell_atramedes_resonating_clash_1_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_atramedes_resonating_clash_1_SpellScript);

            void HandleScript(SpellEffIndex /*effIndex*/)
            {
                if (!GetHitUnit())
                    return;
                GetHitUnit()->RemoveAurasDueToSpell(SPELL_NOISY);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_atramedes_resonating_clash_1_SpellScript::HandleScript, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_atramedes_resonating_clash_1_SpellScript();
        }
};

class spell_atramedes_vertigo : public SpellScriptLoader
{
    public:
        spell_atramedes_vertigo() : SpellScriptLoader("spell_atramedes_vertigo") { }

        class spell_atramedes_vertigo_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_atramedes_vertigo_AuraScript);

            void OnRemove(constAuraEffectPtr aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (!GetTarget())
                    return;

                GetTarget()->ToCreature()->AI()->DoAction(ACTION_SHIELD_KILL);
            }
            
            void Register()
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_atramedes_vertigo_AuraScript::OnRemove, EFFECT_1, SPELL_AURA_MOD_STUN, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_atramedes_vertigo_AuraScript();
        }
};

class spell_atramedes_roaring_flame : public SpellScriptLoader
{
    public:
        spell_atramedes_roaring_flame() : SpellScriptLoader("spell_atramedes_roaring_flame") { }

        class spell_atramedes_roaring_flame_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_atramedes_roaring_flame_SpellScript);

            void RecalculateDamage(SpellEffIndex /*effIndex*/)
            {
                uint32 power = GetHitUnit()->GetPower(POWER_ALTERNATE_POWER);
                GetHitUnit()->SetPower(POWER_ALTERNATE_POWER, power + 3);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_atramedes_roaring_flame_SpellScript::RecalculateDamage, EFFECT_1, SPELL_EFFECT_ENERGIZE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_atramedes_roaring_flame_SpellScript();
        }
};

class spell_atramedes_roaring_flame_aura : public SpellScriptLoader
{
    public:
        spell_atramedes_roaring_flame_aura() : SpellScriptLoader("spell_atramedes_roaring_flame_aura") { }

        class spell_atramedes_roaring_flame_aura_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_atramedes_roaring_flame_aura_SpellScript);

            void RecalculateDamage(SpellEffIndex /*effIndex*/)
            {
                uint32 power = GetHitUnit()->GetPower(POWER_ALTERNATE_POWER);
                GetHitUnit()->SetPower(POWER_ALTERNATE_POWER, power + 5);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_atramedes_roaring_flame_aura_SpellScript::RecalculateDamage, EFFECT_2, SPELL_EFFECT_ENERGIZE);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_atramedes_roaring_flame_aura_SpellScript();
        }
};


class spell_atramedes_sonic_breath : public SpellScriptLoader
{
public:
	spell_atramedes_sonic_breath() : SpellScriptLoader("spell_atramedes_sonic_breath") { }

	class spell_atramedes_sonic_breath_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_atramedes_sonic_breath_AuraScript);

		void OnPeriodic(constAuraEffectPtr aurEff)
		{
			if (Unit* caster = GetCaster())
			{
				caster->CastSpell(caster, SPELL_SONIC_BREATH_DPS, true);
			}
		}

		void Register()
		{
			OnEffectPeriodic += AuraEffectPeriodicFn(spell_atramedes_sonic_breath_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
		}
	};

	AuraScript* GetAuraScript() const
	{
		return new spell_atramedes_sonic_breath_AuraScript();
	}
};

class spell_atramedes_sonic_breath_dps : public SpellScriptLoader
{
    public:
		spell_atramedes_sonic_breath_dps() : SpellScriptLoader("spell_atramedes_sonic_breath_dps") { }

		class spell_atramedes_sonic_breath_dps_SpellScript : public SpellScript
        {
			PrepareSpellScript(spell_atramedes_sonic_breath_dps_SpellScript);

			void FilterTargets(std::list<WorldObject*>& targets)
			{

				if (targets.empty())
					return;
				Unit* owner = GetCaster();
				if (owner){					
					targets.remove(owner);
					float arc = M_PI/3 ; // Cast in 60 grade
					for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); ++itr){
						if (!*itr)
							continue;
						if (!owner->isInFront(*itr, arc)){
							targets.remove((*itr));
						}
					}
				}
			}

            void Register()
            {
				OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_atramedes_sonic_breath_dps_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_CONE_ENEMY_24);
            }
        };

        SpellScript* GetSpellScript() const
        {
			return new spell_atramedes_sonic_breath_dps_SpellScript();
        }
};

uint16 const times[16] =
{
	500, 10000, 10000, 5000, 5000, 10000, 5000, 7500,
	5000, 8000, 5000, 7500, 3000, 8000, 9000, 5000
};

uint32 guards[8] = {	NPC_SPIRIT_OF_ANGERFORGE,	NPC_SPIRIT_OF_THAURISSAN,	NPC_SPIRIT_OF_IRONSTAR,	NPC_SPIRIT_OF_BURNINGEYE,	NPC_SPIRIT_OF_COREHAMMER,	NPC_SPIRIT_OF_ANVILRAGE,	NPC_SPIRIT_OF_MOLTENFIST,	NPC_SPIRIT_OF_SHADOWFORGE };


/*
Atramedes pre-event
20091 - Ah, Maloriak! How gracious of you to finally appear from that quarantine you call a laboratory. What have you got this time?
19860 - My sincerest apologies for the disturbance, my liege. But I believe I have something you may be very interested in!
20092 - By all means, enlighten me.
19861 - Yes, yes!
19862 - By extracting agents from the blood of various dragonflights I have created a salve that bestow the wearer sight beyond sight!
19863 - Sense beyond this realm of mortality!
19864 - Atramedes! Your master beckons.
19865 - I present to you experiment number 25463-D!
20093 - It appears as though your experiment has failed. That whelp has gone completely blind! Look at him.
20156 - LOOK AT HIM!
19866 - How could this be!? I will dispose of him immediately!
20094 - No, not yet.
20095 - This object of your chagrin may still prove... valuable... to me.
20096 - Leave now, pathetic alchemist. I anxiously await your next failure.
19867 - Yes, my lord...

dissappear all three plus throne, players fight the 8 gnomes, then bang the big bell (401937 id) and atramedes flies in, melting it (activate).

Atramedes Heroic Nefarian yells
23357 - You should have been disposed of long time ago. // Death
23358 - These shields are proving quite the nuissance. // Shield
23359 - Atramedes! The heroes are right there! // Air phase
23360 - Atramedes... Are you going deaf aswell as blind? hurry up and kill them all! // Intro
*/


class mob_maloriak_atramedes_event : public CreatureScript
{
	public:
		mob_maloriak_atramedes_event() : CreatureScript("mob_maloriak_atramedes_event") { }

		struct mob_maloriak_atramedes_eventAI : public BossAI
		{
			mob_maloriak_atramedes_eventAI(Creature* creature) : BossAI(creature, DATA_EVENTFIRE)
			{
				instance = creature->GetInstanceScript();
			}

			InstanceScript* instance;
			uint32 timer;
			uint8 eventStep;

			Creature* nefarian;
			Creature* atramedes;
			Creature* maloriak;
			bool beginEvent;
			bool eventProcessed;

			void Reset()
			{				
				eventStep = 0;
				eventProcessed = false;
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				DespawnCreatures(NPC_PRE_NEFARIAN);
				DespawnCreatures(NPC_PRE_MALORIAK);
				DespawnCreatures(NPC_PRE_ATRAMEDES);				
				beginEvent = false;
				events.ScheduleEvent(1, 1000);
			};

			void DespawnCreatures(uint32 entry)
			{
				std::list<Creature*> creatures;
				GetCreatureListWithEntryInGrid(creatures, me, entry, 100.0f);

				if (creatures.empty())
					return;

				for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
					(*iter)->DespawnOrUnsummon();
			}

			void DoAction(const int32 action)
			{
				if (action == 1){
					me->SummonCreature(NPC_PRE_NEFARIAN, 127.802f, -234.484f, 75.453453f, 2.046f, TEMPSUMMON_CORPSE_DESPAWN, 3000);
					me->SummonCreature(NPC_PRE_MALORIAK, 122.799f, -216.601f, 75.453453f, 5.011f, TEMPSUMMON_CORPSE_DESPAWN, 3000);
					me->SummonGameObject(GOB_NEFARIANS_THRONE, 129.937f, -236.88f, 75.4534f, 2.274f, 0, 0, 0, 0, 0);
					nefarian = me->FindNearestCreature(NPC_PRE_NEFARIAN, 100.0f, true);
					nefarian->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
					nefarian->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
					maloriak = me->FindNearestCreature(NPC_PRE_MALORIAK, 100.0f, true);
					maloriak->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
					maloriak->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
					// Ghost visual.							
					nefarian->AddAura(SPELL_GHOST_VISUAL, nefarian);
					maloriak->AddAura(SPELL_GHOST_VISUAL, maloriak);
					maloriak->SetReactState(REACT_PASSIVE);
					nefarian->SetReactState(REACT_PASSIVE); 
					events.ScheduleEvent(2, 10);
					beginEvent = true;					
				}
			}

			void UpdateAI(uint32 const diff)
			{								
				
				events.Update(diff);

				while (uint32 eventId = events.ExecuteEvent()){
					switch (eventId)
					{
						case 1:	
							if (!FindCreatures() && me->SelectNearestPlayer(40.0f)){								
								DoAction(1);
							}								
							else
								events.ScheduleEvent(1, 1000);
							
							break;
						case 2:
							
								if (eventStep == 0)
								{
									timer = times[eventStep];

									if (Player* target = me->FindNearestPlayer(40.0f, true))
										if (target && target->GetDistance(me) < 35.0f  && !eventProcessed)
										{
											eventStep = 1;
											eventProcessed = true;
										}
								}
								else
								{
									switch (eventStep)
									{
										// Nefarian
									case 1:
										nefarian->AI()->Talk(0);
										nefarian->MonsterSay("Ah, Maloriak! How gracious of you to finally appear from that quarantine you call a laboratory. What have you got this time?", 0, 0);
										break;
									case 3:
										nefarian->AI()->Talk(1);
										nefarian->MonsterSay("By all means, enlighten me.", 0, 0);
										break;
									case 9:
										nefarian->AI()->Talk(2);
										nefarian->MonsterSay("It appears as though your experiment has failed. That whelp has gone completely blind! Look at him.", 0, 0);
										break;
									case 10:
										nefarian->AI()->Talk(3);
										nefarian->MonsterSay("LOOK AT HIM!", 0, 0);
										break;
									case 12:
										nefarian->AI()->Talk(4);
										nefarian->MonsterSay("No, not yet.", 0, 0);
										break;
									case 13:
										nefarian->AI()->Talk(5);
										nefarian->MonsterSay("This object of your chagrin may still prove... valuable... to me.", 0, 0);
										break;
									case 14:
										nefarian->AI()->Talk(6);
										nefarian->MonsterSay("Leave now, pathetic alchemist. I anxiously await your next failure.", 0, 0);
										break;

										// Maloriak
									case 2:
										maloriak->AI()->Talk(0);
										maloriak->MonsterSay("My sincerest apologies for the disturbance, my liege. But I believe I have something you may be very interested in!", 0, 0);
										break;
									case 4:
										maloriak->AI()->Talk(1);
										maloriak->MonsterSay("Yes, yes!", 0, 0);
										break;
									case 5:
										maloriak->AI()->Talk(2);
										maloriak->MonsterSay("By extracting agents from the blood of various dragonflights I have created a salve that bestow the wearer sight beyond sight!", 0, 0);
										break;
									case 6:
										maloriak->AI()->Talk(3);
										maloriak->MonsterSay("Sense beyond this realm of mortality!", 0, 0);
										break;
									case 7:
										maloriak->AI()->Talk(4);
										maloriak->MonsterSay("Atramedes! Your master beckons.", 0, 0);
										me->SummonCreature(NPC_PRE_ATRAMEDES, 117.386f, -219.943f, 75.453453f, 5.305f, TEMPSUMMON_CORPSE_DESPAWN, 3000);
										atramedes = me->FindNearestCreature(NPC_PRE_ATRAMEDES, 100.0f, true);
										atramedes->AddAura(SPELL_GHOST_VISUAL, atramedes);
										atramedes->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
										atramedes->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
										atramedes->SetReactState(REACT_PASSIVE);
										break;

									case 8:
										atramedes->AddAura(SPELL_GLOW_ORANGE, atramedes);
										atramedes->AddAura(SPELL_BLIND_WHELP, atramedes);
										atramedes->GetMotionMaster()->MovePoint(0, 121.493f, -225.428f, 75.4535f);
										maloriak->AI()->Talk(5);
										maloriak->MonsterSay("I present to you experiment number 25463-D!", 0, 0);
										break;
									case 11:
										maloriak->AI()->Talk(6);
										maloriak->MonsterSay("How could this be!? I will dispose of him immediately!", 0, 0);
										break;
									case 15:
										atramedes->RemoveAura(SPELL_GLOW_ORANGE);
										atramedes->RemoveAura(SPELL_BLIND_WHELP);
										maloriak->AI()->Talk(7);
										maloriak->MonsterSay("Yes, my lord...", 0, 0);
										break;

										// Both
									case 16:
										atramedes->DespawnOrUnsummon();
										nefarian->DespawnOrUnsummon();
										maloriak->DespawnOrUnsummon();

										if (GameObject* throne = me->FindNearestGameObject(GOB_NEFARIANS_THRONE, 100.0f))
											throne->Delete();

										me->DespawnOrUnsummon(100);
										instance->SetData(DATA_ATRAMEDES_READY, 0);
										break;
									}

									timer = times[eventStep];

									if (eventStep<16)
										eventStep++;
								

								}							
							events.ScheduleEvent(2, timer);
							break;
					}
				}

							
			}


			bool FindCreatures(){			
				for (uint32 entry : guards){
					if (me->FindNearestCreature(entry, 100.0f, true)){
						return true;
					}
				}
				return false;
			}
		};

		CreatureAI* GetAI(Creature* creature) const
		{
			return new mob_maloriak_atramedes_eventAI(creature);
		}
};

void AddSC_boss_atramedes()
{
    new boss_atramedes();
    new npc_sonar_pulse();
    new npc_tracking_flames();
    new npc_roaring_flame_target();
    new npc_roaring_flame();
	new npc_roaring_flame_caster();
    new npc_atramedes_gong();
    new npc_abnoxious_fiend();
    new spell_atramedes_resonating_clash();
    new spell_atramedes_resonating_clash_1();
    new spell_atramedes_vertigo();
	new mob_maloriak_atramedes_event();	    
    new spell_atramedes_roaring_flame();
    new spell_atramedes_roaring_flame_aura();
	new spell_atramedes_sonic_breath();
	new spell_atramedes_sonic_breath_dps();
}