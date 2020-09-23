/*
 *    Dungeon : Mogu'shan palace 87-89
 *    Xin the weaponmaster
 *    Jade servers
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "mogu_shan_palace.h"
#include "Log.h"
#include "Pet.h"

enum Spells : uint32
{
    SPELL_BLADES_1           = 124531,
    SPELL_BLADES_2           = 124534,

    SPELL_TURN_OFF_BLADES    = 124540,
    SPELL_BLADE_TRAP_VISUAL  = 119388,

    SPELL_SUMMON_STAFF       = 120109,
    SPELL_SUMMON_AXES        = 120083,

    SPELL_STAFF_FIREBALL     = 119528,

    SPELL_SUMMON_FIRE_RING   = 119541,
    SPELL_FIRE_RING_AURA     = 119544,
    SPELL_FIRE_RING_VISUAL   = 119549,
    SPELL_EXPLODE_FIRE_RING  = 119590,

    SPELL_GROUND_SLAM       = 119684,

    SPELL_INCITING_ROAR     = 122959,

    SPELL_DART_AURA         = 120143,
    SPELL_DART_DAMAGE       = 120142
};

enum Creatures : uint32
{
    CREATURE_SWORD_LAUNCHER  = 59481,
};

// Constants to define which world triggers can be chosen as blade launchers

static const float m_fLessThanYPos = -2647.7f;
static const float m_fMoreThanYPos = -2578.6f;

static const Position m_fCenterPos = { -4632.8f, -2615.f, 21.8f, 0.0f };

class CorrectLauncherCheck
{
public:
    bool operator()(WorldObject* target) const
    {
        return (target->GetPositionY() > m_fLessThanYPos && target->GetPositionY() < m_fMoreThanYPos);
    }
};

class ActiveLauncherCheck
{
public:
    bool operator()(WorldObject* target) const
    {
        return (target->ToUnit() && target->ToUnit()->HasAura(SPELL_BLADES_1));
    }
};

static const uint32 aBladeSpells[2] =
{
    SPELL_BLADES_1,
    SPELL_BLADES_2
};

class boss_xin_the_weaponmaster : public CreatureScript
{
public:
    boss_xin_the_weaponmaster() : CreatureScript("boss_xin_the_weaponmaster") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_xin_the_weaponmaster_AI(creature);
    }

    enum eEvents
    {
        EVENT_RING_OF_FIRE          = 1,
        EVENT_GROUND_SLAM           = 2,
        EVENT_INCITING_ROAR         = 3,
        EVENT_AXES_ACTIVATE         = 4,
        EVENT_CHECK_SWORDS          = 5,
        EVENT_CHECK_CROSSBOW        = 6
    };

    enum eTalks
    {
        TALK_INTRO,
        TALK_AGGRO,
        TALK_AXES,
        EMOTE_AXES,
        EMOTE_BLADES,
        TALK_BLADES,
        TALK_CROSSBOW,
        EMOTE_CROSSBOW,
        TALK_DEATH,
        EMOTE_DEATH,
        TALK_SLAY,
        TALK_RESET
    };

    struct boss_xin_the_weaponmaster_AI : public BossAI
    {
        boss_xin_the_weaponmaster_AI(Creature* creature) : BossAI(creature, DATA_XIN_THE_WEAPONMASTER)
        {
            pInstance = creature->GetInstanceScript();
        }

        InstanceScript* pInstance;
        bool m_bHasYelled;

        void InitializeAI() final
        {
            Reset();
            SetImmuneToPullPushEffects(true);
        }

        void Reset()
        {
            events.Reset();
        }

        void MoveInLineOfSight(Unit* pWho)
        {
            if (!m_bHasYelled && pWho && pWho->GetTypeId() == TYPEID_PLAYER)
            {
                m_bHasYelled = true;
                Talk(TALK_INTRO);
            }

            ScriptedAI::MoveInLineOfSight(pWho);
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();

            if (me->HasUnitState(UNIT_STATE_CANNOT_TURN))
                me->ClearUnitState(UNIT_STATE_CANNOT_TURN);

            me->GetMotionMaster()->MoveTargetedHome();

            DeactivateWeapons();
            Talk(TALK_RESET);

            if (auto const script = me->GetInstanceScript())
                script->HandleGameObject(0, true, ObjectAccessor::GetGameObject(*me, script->GetData64(GO_DOOR_BEFORE_KING)));
        }

        void KilledUnit(Unit* /*pVictim*/)
        {
            Talk(TALK_SLAY);
        }

        void DeactivateWeapons()
        {
            DeactivateAxes();
            DeactivateStaves();
            DeactivateCrossbows();
            DeactivateSwordLaunchers();
        }

        void DeactivateAxes()
        {
            if (pInstance)
                pInstance->SetData(TYPE_ACTIVATE_ANIMATED_AXE, 0);
        }

        void DeactivateStaves()
        {
            std::list<Creature*> m_lStaveList;

            GetCreatureListWithEntryInGrid(m_lStaveList, me, CREATURE_ANIMATED_STAFF, 200.0f);

            for (auto pCreature : m_lStaveList)
            {
                pCreature->CombatStop(true);

                if (pCreature->AI())
                    pCreature->AI()->EnterEvadeMode();
            }
        }


        bool DoActivateSwordLaunchers()
        {
            if (me->GetHealthPct() > 66.5f)
                return false;

            std::list<Creature*>m_lLaunchersList;

            GetCreatureListWithEntryInGrid(m_lLaunchersList, me, CREATURE_SWORD_LAUNCHER, 200.0f);
            m_lLaunchersList.remove_if(CorrectLauncherCheck());

            if (m_lLaunchersList.empty())
            {
//                TC_LOG_ERROR("scripts", "Xin the Weaponmaster found no world triggers for blade launcher in instance %u", me->GetInstanceId());
                return true;
            }

            for (int n = 0; n < 2 && !m_lLaunchersList.empty(); ++n)
            {
                if (Creature* pTrap = WoWSource::Containers::SelectRandomContainerElement(m_lLaunchersList))
                {
                    me->AddAura(aBladeSpells[n], pTrap);
                    me->AddAura(SPELL_BLADE_TRAP_VISUAL, pTrap);
                }

                m_lLaunchersList.remove_if(ActiveLauncherCheck());
            }

            Talk(EMOTE_BLADES);
            Talk(TALK_BLADES);

            return true;
        }

        void DeactivateSwordLaunchers()
        {
            std::list<Creature*>m_lLaunchersList;

            GetCreatureListWithEntryInGrid(m_lLaunchersList, me, CREATURE_SWORD_LAUNCHER, 200.0f);

            for (auto pCreature : m_lLaunchersList)
            {
                pCreature->RemoveAllAuras();
            }
        }

        bool DoActivateCrossbows()
        {
            if (me->GetHealthPct() > 35.5f)
                return false;

            std::list<Creature*>m_lCrossbowList;

            GetCreatureListWithEntryInGrid(m_lCrossbowList, me, CREATURE_CROSSBOW, 200.0f);

            for (auto pCrossbow : m_lCrossbowList)
            {
                pCrossbow->CastSpell(pCrossbow, SPELL_DART_AURA, true);
                pCrossbow->RemoveAurasDueToSpell(SPELL_PERMANENT_FEIGN_DEATH);
            }

            Talk(EMOTE_CROSSBOW);
            Talk(TALK_CROSSBOW);

            return true;
        }

        void DeactivateCrossbows()
        {
            std::list<Creature*>m_lCrossbowList;

            GetCreatureListWithEntryInGrid(m_lCrossbowList, me, CREATURE_CROSSBOW, 200.0f);

            for (auto pCrossbow : m_lCrossbowList)
            {
                pCrossbow->RemoveAurasDueToSpell(SPELL_DART_AURA);
                pCrossbow->CastSpell(pCrossbow, SPELL_PERMANENT_FEIGN_DEATH, true);
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_RING_OF_FIRE, 15000);
            events.ScheduleEvent(EVENT_GROUND_SLAM, urand(10000, 15000));
            events.ScheduleEvent(EVENT_INCITING_ROAR, urand(15000, 25000));
            events.ScheduleEvent(EVENT_AXES_ACTIVATE, urand(15000, 25000));
            events.ScheduleEvent(EVENT_CHECK_SWORDS, 1000);
            events.ScheduleEvent(EVENT_CHECK_CROSSBOW, 1000);

            Talk(TALK_AGGRO);

            if (auto const script = me->GetInstanceScript())
                script->HandleGameObject(0, false, ObjectAccessor::GetGameObject(*me, script->GetData64(GO_DOOR_BEFORE_KING)));
        }

		void JustDied(Unit* /*pKiller*/)
		{
			Talk(TALK_DEATH);
			Talk(EMOTE_DEATH);

			DeactivateWeapons();

			if (auto const script = me->GetInstanceScript())
				script->HandleGameObject(0, true, ObjectAccessor::GetGameObject(*me, script->GetData64(GO_DOOR_BEFORE_KING)));

			if (GetDifficulty() == DUNGEON_DIFFICULTY_HEROIC)
			{
				instance->SetData(DATA_XIN_THE_WEAPONMASTER, DONE);
				instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
				instance->DoModifyPlayerCurrenciesIfLevel(396, 1500, 90);
				instance->DoCompleteAchievement(ACHIEVEMENTS_DEFEAT_XIN_HEROIC);
				instance->DoCompleteAchievement(ACHIEVEMENTS_DEFEAT_XIN_NORMAL);
				Map::PlayerList const &pList = me->GetMap()->GetPlayers();

				if (!pList.isEmpty())

					for (Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr)
					{
						Player* pPlayer = itr->getSource();
						pPlayer->SummonCreature(NPC_QUILEN_SUMMONER, -4509.71f, -2746.09f, 31.9666f, 0.0f, TEMPSUMMON_MANUAL_DESPAWN);
						pPlayer->SummonCreature(NPC_QUILEN_SUMMONER, -4458.32f, -2609.35f, -26.3518f, 0.0f, TEMPSUMMON_MANUAL_DESPAWN);
						pPlayer->SummonCreature(NPC_QUILEN_SUMMONER, -4237.60f, -2508.57f, -28.0529f, 5.11377f, TEMPSUMMON_MANUAL_DESPAWN);
						pPlayer->SummonCreature(NPC_QUILEN_SUMMONER, -4237.06f, -2609.72f, 16.4804f, 0.0f, TEMPSUMMON_MANUAL_DESPAWN);
						pPlayer->SummonCreature(NPC_QUILEN_SUMMONER, -3960.71f, -2702.11f, 26.7736f, 0.0f, TEMPSUMMON_MANUAL_DESPAWN);
					}

			}
			else
				instance->DoCompleteAchievement(ACHIEVEMENTS_DEFEAT_XIN_NORMAL);
			
		}
		
		void UpdateAI(const uint32 diff)
        {
			if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
				return;
		
			if (me->HealthBelowPct(34))
			{
				if (GetDifficulty() == DUNGEON_DIFFICULTY_HEROIC)
				{
					Map::PlayerList const &pList = me->GetMap()->GetPlayers();

					if (!pList.isEmpty())

						for (Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr)
					{
						if (Player* pPlayer = itr->getSource())
						{
							me->SummonCreature(CRYSTAL_SUMMONER, -4609.11f, -2613.86f, 21.8994f, 0, TEMPSUMMON_TIMED_DESPAWN, 6000);
							me->SummonCreature(CRYSTAL_SUMMONER, -4659.91f, -2613.89f, 21.8994f, 0, TEMPSUMMON_TIMED_DESPAWN, 6000);
						}
					}
				}
				else return;
			}
		
		
			events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RING_OF_FIRE:
                        if (pInstance)
                            pInstance->SetData(TYPE_ACTIVATE_ANIMATED_STAFF, 0);
                        events.ScheduleEvent(EVENT_RING_OF_FIRE, 35000);
                        break;
                    case EVENT_GROUND_SLAM:
                        me->CastSpell(me, SPELL_GROUND_SLAM, false);
                        events.ScheduleEvent(EVENT_GROUND_SLAM, urand(10000, 15000));
                        break;
                    case EVENT_INCITING_ROAR:
                        DoCast(SPELL_INCITING_ROAR);
                        events.ScheduleEvent(EVENT_INCITING_ROAR, 30000);
                        break;
                    case EVENT_AXES_ACTIVATE:
                        if (pInstance)
                            pInstance->SetData(TYPE_ACTIVATE_ANIMATED_AXE, 1);
                        Talk(EMOTE_AXES);
                        Talk(TALK_AXES);
                        break;
                    case EVENT_CHECK_SWORDS:
                        if (!DoActivateSwordLaunchers())
                            events.ScheduleEvent(EVENT_CHECK_SWORDS, 1000);
                        break;
                    case EVENT_CHECK_CROSSBOW:
                        if (!DoActivateCrossbows())
                            events.ScheduleEvent(EVENT_CHECK_CROSSBOW, 1000);
                        break;
                }
            }

            DoMeleeAttackIfReady();
        }
    };
};

class mob_animated_staff : public CreatureScript
{
public:
    mob_animated_staff() : CreatureScript("mob_animated_staff") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_animated_staff_AI(creature);
    }

    enum eActions
    {
        ACTION_ACTIVATE,
    };

    enum eEvents
    {
        EVENT_SUMMON_RING_OF_FIRE = 1,
        EVENT_FIREBALL = 2,
        EVENT_MOVE = 3,
        EVENT_FIRE_RING_VISUAL = 4
    };

    enum eCreatures
    {
        CREATURE_RING_OF_FIRE = 61499,
    };

    struct mob_animated_staff_AI : public ScriptedAI
    {
        mob_animated_staff_AI(Creature* creature) : ScriptedAI(creature)
        {
            DoCast(SPELL_PERMANENT_FEIGN_DEATH);
            me->SetDisplayId(42195);
            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 76364);
            me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
            SetCombatMovement(false);
        }

        void MovementInform(uint32 uiType, uint32 /*uiPointId*/)
        {
            if (uiType != POINT_MOTION_TYPE)
                return;

            me->SetVisible(true);
        }

        void EnterCombat(Unit* /*unit*/)
        {
        }

        void DoAction(const int32 action)
        {
            switch (action)
            {
                case ACTION_ACTIVATE:
                    me->RemoveAurasDueToSpell(SPELL_PERMANENT_FEIGN_DEATH);
                    events.ScheduleEvent(EVENT_SUMMON_RING_OF_FIRE, urand(9000, 14000));
                    events.ScheduleEvent(EVENT_FIREBALL, urand(2000, 3000));
                    events.ScheduleEvent(EVENT_MOVE, 200);
                    me->GetMotionMaster()->MovePoint(1, m_fCenterPos);
                    DoZoneInCombat();
                    break;
            }
        }

        void Move()
        {
            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
            {
                float x, y;
                GetPositionWithDistInOrientation(me, frand(3.f, me->GetDistance(pTarget)), me->GetAngle(pTarget), x, y);
                me->GetMotionMaster()->MovePoint(0, x, y, me->GetPositionZ());
            }

            events.ScheduleEvent(EVENT_MOVE, urand(4000, 7000));
        }

        void EnterEvadeMode()
        {
            _EnterEvadeMode();

            me->SetVisible(false);
            me->SetReactState(REACT_PASSIVE);
            me->CombatStop(true);
            //Add aura here to prevent our function cancelling movement
            me->AddAura(SPELL_PERMANENT_FEIGN_DEATH, me);

            me->GetMotionMaster()->MovePoint(0, me->GetHomePosition());
        }

        void HandleRing()
        {
            Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0);

            if (!pTarget)
                return;

            me->GetMotionMaster()->MovePoint(0, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());
            me->CastSpell(pTarget, SPELL_SUMMON_FIRE_RING, false);
            events.ScheduleEvent(EVENT_FIRE_RING_VISUAL, 600);
            events.ScheduleEvent(EVENT_SUMMON_RING_OF_FIRE, urand(16000, 22000));
        }

        void HandleFireball()
        {
            Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0);

            if (pTarget)
                DoCast(pTarget, SPELL_STAFF_FIREBALL);
            events.ScheduleEvent(EVENT_FIREBALL, urand(4000, 8000));
            events.RescheduleEvent(EVENT_MOVE, urand(1000, 2000));
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
                return;

            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SUMMON_RING_OF_FIRE:
                        HandleRing();
                        break;
                    case EVENT_FIREBALL:
                        HandleFireball();
                        break;
                    case EVENT_MOVE:
                        Move();
                        break;
                    case EVENT_FIRE_RING_VISUAL:
                        DoCast(SPELL_FIRE_RING_VISUAL);
                        break;
                }
            }
        }
    };
};


class npc_fire_ring_trigger : public CreatureScript
{
public:
    npc_fire_ring_trigger() : CreatureScript("npc_fire_ring_trigger"){ }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_fire_ring_triggerAI(pCreature);
    }

    enum eEvents
    {
        EVENT_UNSUMMON = 1,
        EVENT_MOVE     = 2,
        EVENT_MOVE_MID = 3
    };

    struct npc_fire_ring_triggerAI : public ScriptedAI
    {
        npc_fire_ring_triggerAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            Initialize();
        }

        float x, y;
        float m_fArcPoint;
        bool m_bCounterClockwise;
        bool m_bFirstPoint;

        void Initialize()
        {
            me->SetReactState(REACT_PASSIVE);
            me->GetMotionMaster()->Clear();

            events.ScheduleEvent(EVENT_MOVE, 500);
            x = me->GetPositionX();
            y = me->GetPositionY();
            m_fArcPoint = 0.0f;

            m_bCounterClockwise = urand(0, 1);

            m_bFirstPoint = true;
        }

        void MovementInform(uint32 uiType, uint32 uiPointId)
        {
            if (uiType != POINT_MOTION_TYPE)
                return;

            if (uiPointId == 0)
            {
                if (m_fArcPoint < 11)
                    events.ScheduleEvent(EVENT_MOVE, 200);
                else
                {
                    events.CancelEvent(EVENT_MOVE);
                    events.ScheduleEvent(EVENT_MOVE_MID, 200);
                }
            }
            else
            {
                DoCast(SPELL_EXPLODE_FIRE_RING);
                events.ScheduleEvent(EVENT_UNSUMMON, 2500);
            }
        }

        void Move()
        {
            if (!me->HasAura(SPELL_FIRE_RING_AURA) && !m_bFirstPoint)
                DoCast(me, SPELL_FIRE_RING_AURA, true);

            float newX = x + 5.0f * cos(m_fArcPoint * M_PI / 5);
            float newY = m_bCounterClockwise ? y - 5.0f * sin(m_fArcPoint * M_PI / 5) : y + 5.0f * sin(m_fArcPoint * M_PI / 5);
            me->GetMotionMaster()->MovePoint(0, newX, newY, me->GetPositionZ());

            ++m_fArcPoint;

            m_bFirstPoint = false;
        }

        void MoveMiddle()
        {
            me->RemoveAllAuras();
            me->GetMotionMaster()->MovePoint(1, x, y, me->GetPositionZ());
        }

        void UpdateAI(const uint32 uiDiff)
        {
            events.Update(uiDiff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MOVE:
                        Move();
                        break;
                    case EVENT_UNSUMMON:
						if (Creature* pStaff = me->FindNearestCreature(61433, 25.0f, true))
                        pStaff->DespawnOrUnsummon();
                        break;
                    case EVENT_MOVE_MID:
                        MoveMiddle();
                        break;
                }
            }
        }
    };

};

class npc_animated_axe : public CreatureScript
{
public:
    npc_animated_axe() : CreatureScript("npc_animated_axe") { }

    enum eActions : int32
    {
        ACTION_START_COMBAT,
        ACTION_STOP_COMBAT
    };

    struct npc_animated_axeAI : public ScriptedAI
    {
        npc_animated_axeAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            Initialize();
        }

        void Initialize()
        {
            me->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, 30316);
            DoCast(SPELL_PERMANENT_FEIGN_DEATH);
            me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());

            me->SetReactState(REACT_PASSIVE);
        }

        void DoAction(const int32 uiAction)
        {
            if (uiAction == ACTION_START_COMBAT)
            {
                me->RemoveAurasDueToSpell(SPELL_PERMANENT_FEIGN_DEATH);
                DoCast(SPELL_WHIRLWIND);

                // could possibly be written in a better way
                // will recheck
                me->GetMotionMaster()->MoveRandom(50.f);
            }
            else
                if (uiAction == ACTION_STOP_COMBAT)
                {
                    DeactivateAxe();
                }
        }

        void MovementInform(uint32 uiType, uint32 /*uiPointId*/)
        {
            if (uiType != POINT_MOTION_TYPE)
                return;

            me->SetVisible(true);
        }

        void DeactivateAxe()
        {
            me->SetVisible(false);
            me->CombatStop(true);
            me->RemoveAurasDueToSpell(SPELL_WHIRLWIND);
            DoCast(SPELL_PERMANENT_FEIGN_DEATH);
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MovePoint(0, me->GetHomePosition());
        }

        void EnterEvadeMode()
        {
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_animated_axeAI(pCreature);
    }
};

class OnlyTriggerInFrontPredicate
{
public:
    OnlyTriggerInFrontPredicate(Unit* caster) : _caster(caster) {}

    bool operator()(WorldObject* target) const
    {
        return !_caster->isInFront(target, M_PI / 5) || target->GetGUID() == _caster->GetGUID() || target->GetDistance2d(_caster) > 80.f;
    }

private:
    Unit* _caster;
};

struct CheckIfValidTarget
{
    bool operator ()(WorldObject const *target) const
    {
        return target->GetEntry() != 59481;
    }
};

class InBetweenCheck
{
public:
    InBetweenCheck(Unit* caster, WorldObject* trigger)
        : _caster(caster)
        , _trigger(trigger)
    { }

    bool operator ()(WorldObject const *target) const
    {
        return !target->IsInBetween(_caster, _trigger, 5.0f);
    }

private:
    Unit const *_caster;
    WorldObject const *_trigger;
};

class mob_quilen_statue : public CreatureScript
{
public:
	mob_quilen_statue() : CreatureScript("mob_quilen_statue") { }

	enum Events
	{
		EVENT_LEAPING_RUSH = 1,

	};

	struct mob_quilen_statue_AI : public ScriptedAI
	{
		mob_quilen_statue_AI(Creature* creature) : ScriptedAI(creature)	{}

		void JustDied(Unit* /*killer*/)
		{
			if (!me->isDead())
				return;
			
			me->DespawnOrUnsummon(1000);
			
		}

		void EnterCombat(Unit* /*unit*/)
		{
			DoMeleeAttackIfReady();
			events.ScheduleEvent(EVENT_LEAPING_RUSH, 2000);
		}

		void UpdateAI(uint32 const diff)
		{
			if (!UpdateVictim() || me->HasUnitState(UNIT_STATE_CASTING))
				return;

			events.Update(diff);

			while (uint32 eventId = events.ExecuteEvent())
			{
				switch (eventId)
				{

				case EVENT_LEAPING_RUSH:
					if (Unit* pTarget = me->FindNearestPlayer(10.0f, true))
						me->CastSpell(pTarget, SPELL_LEAPING_RUSH);
					events.ScheduleEvent(EVENT_LEAPING_RUSH, urand(10000, 15000));
				}
			}
			DoMeleeAttackIfReady();
		}

	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_quilen_statue_AI(creature);
	}
};


class mob_quilen_summon : public CreatureScript
{
public:
	mob_quilen_summon() : CreatureScript("mob_quilen_summon") { }

	struct mob_quilen_summon_AI : public ScriptedAI
	{
		int32 stack;
		mob_quilen_summon_AI(Creature* creature) : ScriptedAI(creature)
		{
			me->SetReactState(REACT_PASSIVE);
			me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
		}

		void OnSpellClick(Unit* /*clicker*/)
		{
			Map::PlayerList const &pList = me->GetMap()->GetPlayers();

			if (!pList.isEmpty())

				for (Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr)
			{
				Player* pPlayer = itr->getSource();
				pPlayer->SummonCreature(NPC_QUILEN_LOOTED, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
				pPlayer->AddAura(SPELL_AURA_TO_ACHIEVE, pPlayer);
				me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
				me->DespawnOrUnsummon();
				int32 stack = pPlayer->GetAuraCount(SPELL_AURA_TO_ACHIEVE);

				switch (stack)
				{
				case 1:
					me->GetInstanceScript()->DoSendNotifyToInstance("Quilen Adquiered 1/5");
					break;
				case 2:
					me->GetInstanceScript()->DoSendNotifyToInstance("Quilen Adquiered 2/5");
					break;
				case 3:
					me->GetInstanceScript()->DoSendNotifyToInstance("Quilen Adquiered 3/5");
					break;
				case 4:
					me->GetInstanceScript()->DoSendNotifyToInstance("Quilen Adquiered 4/5");
					break;
				case 5:
					me->GetInstanceScript()->DoSendNotifyToInstance("Quilen Adquiered 5/5");
					me->GetInstanceScript()->DoCompleteAchievement(ACHIEVEMENTS_QUILEN_STATUES);
					pPlayer->RemoveAura(SPELL_AURA_TO_ACHIEVE);
					if (Creature* pCreature = pPlayer->FindNearestCreature(NPC_QUILEN_LOOTED, 100.0f))
						pCreature->DespawnOrUnsummon(2000);
					break;
				}
				
			}
			
		}

	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_quilen_summon_AI(creature);
	}
};

class mob_quilen_loot : public CreatureScript
{
public:
	mob_quilen_loot() : CreatureScript("mob_quilen_loot") { }

	struct mob_quilen_loot_AI : public ScriptedAI
	{
		mob_quilen_loot_AI(Creature* creature) : ScriptedAI(creature)
		{
			me->GetMotionMaster()->Clear();
		}

		void MoveInLineOfSight(Unit* pWho)
		{
			if (pWho->GetTypeId() == TYPEID_PLAYER && pWho->GetDistance(me) < 6.0f)
				me->GetMotionMaster()->MoveFollow(pWho, 3.0f, 0.0f, MOTION_SLOT_ACTIVE);
		}
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new mob_quilen_loot_AI(creature);
	}
};

class ancient_mechanism_summoner : public CreatureScript
{
public:
	ancient_mechanism_summoner() : CreatureScript("ancient_mechanism_summoner") { }

	struct ancient_mechanism_summoner_AI : public ScriptedAI
	{
		ancient_mechanism_summoner_AI(Creature* creature) : ScriptedAI(creature)
		{
			me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
			me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
		}

		void OnSpellClick(Unit* clicker)
		{
			Map::PlayerList const &pList = me->GetMap()->GetPlayers();

			if (!pList.isEmpty())

				for (Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr)
			{
				Player* pPlayer = itr->getSource();
				pPlayer->SummonCreature(CRYSTAL_SUMMONED_TRIGGER, -4632.45f, -2613.78f, 21.8994f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 3000);
				me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				me->DespawnOrUnsummon();
			}
		}       
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new ancient_mechanism_summoner_AI(creature);
	}
};

class ancient_mechanism_summoned_trigger : public CreatureScript
{
public:
	ancient_mechanism_summoned_trigger() : CreatureScript("ancient_mechanism_summoned_trigger") { }

	struct ancient_mechanism_summoned_trigger_AI : public ScriptedAI
	{
		ancient_mechanism_summoned_trigger_AI(Creature* creature) : ScriptedAI(creature)
		{
			me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
			me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
		}

		void OnSpellClick(Unit* clicker)
		{
			Map::PlayerList const &pList = me->GetMap()->GetPlayers();

			if (!pList.isEmpty())

				for (Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr)
			{
				Player* pPlayer = itr->getSource();
				pPlayer->SummonCreature(TRIGGER_METEOR, -4634.17f, -2613.78f, 56.7029f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 3000);
				me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
				me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
				if (Creature* pCreature = me->FindNearestCreature(TRIGGER_METEOR, 150.0f))
				{
					pCreature->SetCanFly(true);
					pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
					pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
					pCreature->AddAura(SPELL_COSMETIC_METEOR, pCreature);
					pCreature->AddAura(SPELL_BALL_OF_FLAMES_COSMETIC, pCreature);
					pCreature->CastSpell(pCreature, SPELL_MECHANISM_DEFENSE, false);
				}
				me->GetInstanceScript()->DoCompleteAchievement(ACHIEVEMENTS_WHAT_DOES_THE_BUTTOM);
				me->DespawnOrUnsummon();
			}
		}       
	};

	CreatureAI* GetAI(Creature* creature) const
	{
		return new ancient_mechanism_summoned_trigger_AI(creature);
	}
};

class spell_dart_damage : public SpellScriptLoader
{
public:
    spell_dart_damage() : SpellScriptLoader("spell_dart_damage") { }

    class spell_dart_damage_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dart_damage_SpellScript);

        bool Validate(SpellInfo const*  )
        {
            return true;
        }

        void SelectTarget(std::list<WorldObject*>& targetList)
        {
            if (!GetCaster())
                return;

            if (targetList.empty())
            {
                FinishCast(SPELL_FAILED_NO_VALID_TARGETS);
                return;
            }

            std::list<Creature*> targets;
            std::list<WorldObject*> finalTargets;
            GetCreatureListWithEntryInGrid(targets, GetCaster(), CREATURE_SWORD_LAUNCHER, 200.0f);

            targets.remove_if(OnlyTriggerInFrontPredicate(GetCaster()));

            for (auto pTarget : targetList)
            {
                for (auto pTrigger : targets)
                {
                    if (pTarget->IsInBetween(GetCaster(), pTrigger, 2.0f))
                        finalTargets.push_back(pTarget);
                }
            }

            targetList = finalTargets;
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dart_damage_SpellScript::SelectTarget, EFFECT_0, TARGET_UNIT_CONE_ENEMY_104);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dart_damage_SpellScript();
    }
};

class spell_dart : public SpellScriptLoader
{
public:
    spell_dart() : SpellScriptLoader("spell_dart") { }

    class spell_dart_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_dart_SpellScript);

        bool Validate(SpellInfo const* /*spell*/)
        {
            return true;
        }

        // set up initial variables and check if caster is creature
        // this will let use safely use ToCreature() casts in entire script
        bool Load()
        {
            return true;
        }

        void SelectTarget(std::list<WorldObject*>& targetList)
        {
            if (!GetCaster())
                return;

            if (targetList.empty())
            {
                FinishCast(SPELL_FAILED_NO_VALID_TARGETS);
                return;
            }

            //Select the two targets.
            std::list<WorldObject*> targets = targetList;
            targetList.remove_if(OnlyTriggerInFrontPredicate(GetCaster()));
            targetList.remove_if(CheckIfValidTarget());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_dart_SpellScript::SelectTarget, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_dart_SpellScript();
    }
};

class TargetCheck
{
public:
    TargetCheck(Unit* caster) : _caster(caster) { }

    bool operator()(WorldObject* target) const
    {
        return !target->ToCreature() || target->GetEntry() != 59481 || target->GetGUID() == _caster->GetGUID();
    }
private:
    Unit* _caster;
};

class ActiveTrapCheck
{
public:
    ActiveTrapCheck(uint32 aura) : _aura(aura) { }

    bool operator()(WorldObject* target) const
    {
        return target->ToCreature() && target->ToCreature()->HasAura(_aura);
    }

private:
    uint32 _aura;
};

class spell_activate_blades : public SpellScriptLoader
{
public:
    spell_activate_blades() : SpellScriptLoader("spell_activate_blades") { }

    class spell_activate_blades_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_activate_blades_SpellScript);

        bool Validate(SpellInfo const* /*spell*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_BLADES_1) || !sSpellMgr->GetSpellInfo(SPELL_BLADES_2))
                return false;
            return true;
        }

        void SelectTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(TargetCheck(GetCaster()));
            targets.remove_if(ActiveTrapCheck(SPELL_BLADES_1));
            targets.remove_if(ActiveTrapCheck(SPELL_BLADES_2));

            if (targets.size() > 1)
                targets.resize(1);
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_activate_blades_SpellScript::SelectTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_activate_blades_SpellScript();
    }
};

class spell_turn_off_blades : public SpellScriptLoader
{
public:
    spell_turn_off_blades() : SpellScriptLoader("spell_turn_off_blades") { }

    class spell_turn_off_blades_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_turn_off_blades_SpellScript);

        bool Validate(SpellInfo const* /*spell*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_TURN_OFF_BLADES))
                return false;
            return true;
        }

        void HandlePreCast()
        {
            if (GetCaster())
            {
                GetCaster()->CastSpell(GetCaster(), SPELL_BLADES_1, false);
                GetCaster()->CastSpell(GetCaster(), SPELL_BLADES_2, false);
            }
        }

        void Register()
        {
            BeforeCast += SpellCastFn(spell_turn_off_blades_SpellScript::HandlePreCast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_turn_off_blades_SpellScript();
    }
};

class spell_groundslam_xin : public SpellScriptLoader
{
public:
    spell_groundslam_xin() : SpellScriptLoader("spell_groundslam_xin") { }

    class spell_groundslam_xin_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_groundslam_xin_SpellScript);

        bool Validate(SpellInfo const* /*spell*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_GROUND_SLAM))
                return false;
            return true;
        }

        void HandlePrecast()
        {
            if (GetCaster())
                GetCaster()->AddUnitState(UNIT_STATE_CANNOT_TURN);
        }

        void HandleAftercast()
        {
            if (GetCaster())
                GetCaster()->ClearUnitState(UNIT_STATE_CANNOT_TURN);
        }

        void Register()
        {
            BeforeCast += SpellCastFn(spell_groundslam_xin_SpellScript::HandlePrecast);
            AfterCast += SpellCastFn(spell_groundslam_xin_SpellScript::HandleAftercast);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_groundslam_xin_SpellScript;
    }
};

class spell_crossbow_xin : public SpellScriptLoader
{
public:
    spell_crossbow_xin() : SpellScriptLoader("spell_crossbow_xin") { }

    class spell_crossbow_xin_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_crossbow_xin_SpellScript);

        bool Validate(SpellInfo const* /*spell*/)
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_DART_DAMAGE))
                return false;
            return true;
        }

        void SelectTarget(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            std::list<WorldObject*> finalTarget;

            finalTarget.push_back(WoWSource::Containers::SelectRandomContainerElement(targets));

            if (!finalTarget.empty())
                targets = finalTarget;
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_crossbow_xin_SpellScript::SelectTarget, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_crossbow_xin_SpellScript();
    }
};



void AddSC_boss_xin_the_weaponmaster()
{
    new boss_xin_the_weaponmaster();
    new npc_animated_axe();
    new mob_animated_staff();
    new npc_fire_ring_trigger();
	new mob_quilen_statue();
	new mob_quilen_summon();
	new mob_quilen_loot();
    new spell_dart();
    new spell_dart_damage();
    new spell_activate_blades();
    new spell_turn_off_blades();
    new spell_groundslam_xin();
    new spell_crossbow_xin();
	new ancient_mechanism_summoner();
	new ancient_mechanism_summoned_trigger();
}