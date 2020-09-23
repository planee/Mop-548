#include "ScriptPCH.h"
#include "halls_of_origination.h"

enum Texts
{
    SAY_DEATH   = 0,
    SAY_AGGRO   = 1,
    SAY_KILL    = 2,
};

enum Spells
{
    // Setesh
    SPELL_CHAOS_BOLT            = 77069,
	SPELL_REIGN_OF_CHAOS        = 77023,
	SPELL_CHAOS_BLAST_SUMMON    = 76674,
	SPELL_CHAOS_BLAST_MISSILE   = 76676,
	SPELL_CHAOS_BLAST_DAMAGE    = 76681,
    SPELL_SEED_OF_CHAOS         = 76870,
	SPELL_CHAOS_PORTAL_CHANNEL  = 76784,
	SPELL_PORTAL_VISUAL         = 76714,
    
    // Void Sentinel
    SPELL_VOID_BARRIER          = 76959,
    SPELL_CHARGED_FISTS         = 77238,

    // Void Seeker
    SPELL_ANTI_MAGIC_PRISON     = 76903,
    SPELL_SHADOW_BOLT_VOLLEY    = 76146, //r
    SPELL_SHADOW_BOLT_VOLLEY_H  = 89846, //r

	//Void Lord
	SPELL_VOID_BURST            = 77475,
	SPELL_VOID_INFUSION         = 77470,
};

enum NPCs
{
    NPC_VOID_SENTINEL       = 41208,
    NPC_VOID_SEEKER         = 41371,
    NPC_VOID_WURM           = 41374,
    NPC_CHAOS_PORTAL        = 41055,
    NPC_REIGN_OF_CHAOS      = 41168, // 77026
    NPC_VOID_LORD           = 41364, // 77458
	NPC_CHAOS_SEED          = 41126,
	NPC_CHAOS_BLAST         = 41041,
};

enum Events
{
    EVENT_CHAOS_BOLT            = 1,
    EVENT_SUMMON_CHAOS_PORTAL   = 2,
	EVENT_SEED_OF_CHAOS         = 3,
	EVENT_REIGN_OF_CHAOS        = 4,
	EVENT_CHAOS_BLAST           = 5,

    EVENT_SUMMON_6              = 6,
    EVENT_SUMMON_10             = 7,
    EVENT_SUMMON_12             = 8,
    EVENT_SUMMON_15             = 9,

    EVENT_ANTI_MAGIC_PRISON     = 10,
    EVENT_SHADOW_BOLT_VOLLEY    = 11,

    EVENT_VOID_BARRIER          = 12,
    EVENT_CHARGED_FISTS         = 13,

    EVENT_MOVE                  = 14,
	EVENT_ENABLE_VISUAL         = 15,
};

enum SeteshSummonTypes
{
    SETESH_SUMMON_WURM      = 1,
    SETESH_SUMMON_SENTINEL  = 2,
    SETESH_SUMMON_SEEKER    = 3,
};

enum MISC
{
	POINT_CHAOS_PORTAL = 1,
	DATA_CHAOS_PORTAL = 1,
	DATA_RESET_PORTAL = 2,
};

const Position movepos[9] =
{
    {-481.55f, 14.15f, 343.92f, 2.07f},
    {-490.31f, 25.55f, 343.93f, 2.56f},
    {-508.35f, 30.95f, 343.94f, 3.08f},
    {-524.62f, 30.30f, 343.93f, 3.35f},
    {-534.63f, 22.76f, 343.92f, 4.08f},
    {-539.40f, 9.067f, 343.92f, 4.67f},
    {-537.78f, -3.28f, 343.92f, 5.11f},
    {-528.39f, -16.43f, 343.93f, 5.85f},
    {-513.85f, -19.04f, 343.93f, 6.15f}
};

class boss_setesh : public CreatureScript
{
    public:
        boss_setesh() : CreatureScript("boss_setesh") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_seteshAI(creature);
        }

        struct boss_seteshAI : public BossAI
        {
            boss_seteshAI(Creature* creature) : BossAI(creature, DATA_SETESH)
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

            void Reset()
            {
                _Reset();
				me->SetReactState(REACT_AGGRESSIVE);
				DespawnCreatures(NPC_VOID_SENTINEL);
				DespawnCreatures(NPC_VOID_SEEKER);
				DespawnCreatures(NPC_VOID_WURM);
				DespawnCreatures(NPC_CHAOS_PORTAL);
				DespawnCreatures(NPC_REIGN_OF_CHAOS);
				DespawnCreatures(NPC_VOID_LORD);
				DespawnCreatures(NPC_CHAOS_SEED);
				DespawnCreatures(NPC_CHAOS_BLAST);
				Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
				if (!PlayerList.isEmpty())
				{
					for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
					{
						Player *player = i->getSource();
						if (player->HasAura(SPELL_CHAOS_BLAST_DAMAGE))
							player->RemoveAura(SPELL_CHAOS_BLAST_DAMAGE);
     				}
				}
            }

            void EnterCombat(Unit* who)
            {
				BossAI::EnterCombat(who);
                Talk (SAY_AGGRO);
				events.ScheduleEvent(EVENT_CHAOS_BOLT, 1000);
                events.ScheduleEvent(EVENT_SUMMON_CHAOS_PORTAL, 20000);
                events.ScheduleEvent(EVENT_MOVE, 2000);
				events.ScheduleEvent(EVENT_REIGN_OF_CHAOS, urand(20000, 25000));
				events.ScheduleEvent(EVENT_SEED_OF_CHAOS, urand(30000, 35000));
				//Fix this event in the future
				//events.ScheduleEvent(EVENT_CHAOS_BLAST, urand(10000, 12000));
                me->SetReactState(REACT_PASSIVE);
                DoZoneInCombat();
                instance->SetBossState(DATA_SETESH, IN_PROGRESS);
            }

			void MovementInform(uint32 type, uint32 id)
		    {
			    if (type == POINT_MOTION_TYPE)
			    {
				    switch (id)
				    {
                        case 1:
                            events.ScheduleEvent(EVENT_MOVE, 1000);
                            break;
                    }
			    }
		    }
			
            void KilledUnit(Unit* who)
            {
                Talk(SAY_KILL);
            }

            void JustDied(Unit* /*who*/)
            {
                _JustDied();
                Talk(SAY_DEATH);
				DespawnCreatures(NPC_VOID_SENTINEL);
				DespawnCreatures(NPC_VOID_SEEKER);
				DespawnCreatures(NPC_VOID_WURM);
				DespawnCreatures(NPC_CHAOS_PORTAL);
				DespawnCreatures(NPC_REIGN_OF_CHAOS);
				DespawnCreatures(NPC_VOID_LORD);
				DespawnCreatures(NPC_CHAOS_SEED);
				DespawnCreatures(NPC_CHAOS_BLAST);
				Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
				if (!PlayerList.isEmpty())
				{
					for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
					{
						Player *player = i->getSource();
						if (player->HasAura(SPELL_CHAOS_BLAST_DAMAGE))
							player->RemoveAura(SPELL_CHAOS_BLAST_DAMAGE);
					}
				}
            }

			void SpellHitTarget(Unit* target, const SpellInfo* spell)
			{
				if (spell->Id == SPELL_CHAOS_BLAST_MISSILE)
				{
					target->CastSpell(target, SPELL_CHAOS_BLAST_DAMAGE, true);
					//This line provoke crash in the server
					//target->ToCreature()->DespawnOrUnsummon(15000);
				}
			}

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
					    case EVENT_CHAOS_BLAST:					
								DoCast(SPELL_CHAOS_BLAST_SUMMON);
								DoCast(SPELL_CHAOS_BLAST_MISSILE);
							events.ScheduleEvent(EVENT_CHAOS_BLAST, urand(18000, 20000));
						    break;
                        case EVENT_CHAOS_BOLT:
                            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                DoCast(pTarget, SPELL_CHAOS_BOLT);
							events.ScheduleEvent(EVENT_CHAOS_BOLT, 2000);
                            break;
						case EVENT_REIGN_OF_CHAOS:
							DoCast(me, SPELL_REIGN_OF_CHAOS, false);
							events.ScheduleEvent(EVENT_REIGN_OF_CHAOS, urand(20000, 25000));
							break;
                        case EVENT_SUMMON_CHAOS_PORTAL:
                            me->SummonCreature(NPC_CHAOS_PORTAL,
                                me->GetPositionX(),
                                me->GetPositionY(),
                                me->GetPositionZ(),
                                me->GetOrientation(),
                                IsHeroic()? TEMPSUMMON_DEAD_DESPAWN: TEMPSUMMON_TIMED_DESPAWN,
                                IsHeroic()? 0: 35000);
                            events.ScheduleEvent(EVENT_SUMMON_CHAOS_PORTAL, urand(40000, 45000));
                            break;
                        case EVENT_MOVE:
                            me->GetMotionMaster()->MovePoint(1, movepos[urand(0, 8)]);
                            break;
						case EVENT_SEED_OF_CHAOS:
							if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
							if (Creature* seed = me->SummonCreature(NPC_CHAOS_SEED, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ() + 30.0f))
								seed->GetMotionMaster()->MovePoint(1, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ());
							events.ScheduleEvent(EVENT_SEED_OF_CHAOS, urand(30000, 35000));
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

        };
};

class npc_setesh_chaos_portal : public CreatureScript
{
    public:
        npc_setesh_chaos_portal() : CreatureScript("npc_setesh_chaos_portal") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_setesh_chaos_portalAI(creature);
        }

        struct npc_setesh_chaos_portalAI : public Scripted_NoMovementAI
        {
            npc_setesh_chaos_portalAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
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

            InstanceScript* pInstance;
            EventMap events;

            void SeteshSummon(SeteshSummonTypes type)
            {
                if (!pInstance)
                    return;

                if (Creature* pSetesh = pInstance->instance->GetCreature(pInstance->GetData64(DATA_SETESH)))
                {    
                    switch (type)
                    {
                        case SETESH_SUMMON_WURM:
                            pSetesh->SummonCreature(NPC_VOID_WURM,
                                me->GetPositionX(),
                                me->GetPositionY(),
                                me->GetPositionZ(),
                                me->GetOrientation());
                            pSetesh->SummonCreature(NPC_VOID_WURM,
                                me->GetPositionX(),
                                me->GetPositionY(),
                                me->GetPositionZ(),
                                me->GetOrientation());
                            break;
                        case SETESH_SUMMON_SENTINEL:
                            pSetesh->SummonCreature(NPC_VOID_SENTINEL,
                                me->GetPositionX(),
                                me->GetPositionY(),
                                me->GetPositionZ(),
                                me->GetOrientation());
                            break;
                        case SETESH_SUMMON_SEEKER:
                            pSetesh->SummonCreature(NPC_VOID_SEEKER,
                                me->GetPositionX(),
                                me->GetPositionY(),
                                me->GetPositionZ(),
                                me->GetOrientation());
                            break;
                    }
                }
            }

            void Reset()
            {
                me->SetReactState(REACT_PASSIVE);

                if (!IsHeroic())
                {
					events.ScheduleEvent(EVENT_ENABLE_VISUAL, 2000);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
                    SeteshSummon(SETESH_SUMMON_WURM);
                    events.ScheduleEvent(EVENT_SUMMON_12, 12000);
                }
                else
                {
					events.ScheduleEvent(EVENT_ENABLE_VISUAL, 2000);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
                    SeteshSummon(SETESH_SUMMON_SENTINEL);
                    events.ScheduleEvent(EVENT_SUMMON_6, 12000);
                }
            }

            void UpdateAI(uint32 const diff)
            {
                events.Update(diff);

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
					case EVENT_ENABLE_VISUAL:
						DoCast(SPELL_PORTAL_VISUAL);
						me->SetFloatValue(OBJECT_FIELD_SCALE_X, 3.0f);
						break;
                        case EVENT_SUMMON_6:
                            SeteshSummon(SETESH_SUMMON_WURM);
                            events.ScheduleEvent(EVENT_SUMMON_10, 10000);
                            break;
                        case EVENT_SUMMON_10:
                            SeteshSummon(SETESH_SUMMON_SEEKER);
                            events.ScheduleEvent(EVENT_SUMMON_15, 15000);
                            break;
                        case EVENT_SUMMON_12:
                            SeteshSummon(SETESH_SUMMON_SEEKER);
                            events.ScheduleEvent(EVENT_SUMMON_15, 15000);   
                            break;
                        case EVENT_SUMMON_15:
                            if (IsHeroic())
                            {
                                if (urand(0, 1))
                                    SeteshSummon(SETESH_SUMMON_WURM);
                                else
                                    SeteshSummon(SETESH_SUMMON_SENTINEL);
                                events.ScheduleEvent(EVENT_SUMMON_15, 15000);
                            }
                            else
                            {
                                SeteshSummon(SETESH_SUMMON_SENTINEL);
                                me->DespawnOrUnsummon();
                            }
                            break;
                    }
                }
            }
        };

};

class npc_setesh_void_sentinel : public CreatureScript
{
    public:
        npc_setesh_void_sentinel() : CreatureScript("npc_setesh_void_sentinel") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_setesh_void_sentinelAI(creature);
        }

        struct npc_setesh_void_sentinelAI : public ScriptedAI
        {
            npc_setesh_void_sentinelAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* pInstance;
            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                    return;
                
                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_CHARGED_FISTS:
                            DoCast(me, SPELL_CHARGED_FISTS);
                            events.ScheduleEvent(EVENT_CHARGED_FISTS, urand(18000, 22000));
                            break;
                        case EVENT_VOID_BARRIER:
                            DoCast(me, SPELL_VOID_BARRIER);
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
	};
};

class npc_setesh_void_seeker : public CreatureScript
{
    public:
        npc_setesh_void_seeker() : CreatureScript("npc_setesh_void_seeker") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_setesh_void_seekerAI(creature);
        }

        struct npc_setesh_void_seekerAI : public ScriptedAI
        {
            npc_setesh_void_seekerAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
                pInstance = pCreature->GetInstanceScript();
            }

            InstanceScript* pInstance;
            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* who)
            {
                if (urand(0, 1))
                    events.ScheduleEvent(EVENT_ANTI_MAGIC_PRISON, urand(3000, 5000));
                else
                    events.ScheduleEvent(EVENT_SHADOW_BOLT_VOLLEY, urand(3000, 5000));
            }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                    return;
                    
                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                    case EVENT_ANTI_MAGIC_PRISON:
                        if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(pTarget, SPELL_ANTI_MAGIC_PRISON);
                        events.ScheduleEvent(EVENT_ANTI_MAGIC_PRISON, urand(31000, 33000));
                        break;
                    case EVENT_SHADOW_BOLT_VOLLEY:
                        DoCastAOE(SPELL_SHADOW_BOLT_VOLLEY);
                        events.ScheduleEvent(EVENT_SHADOW_BOLT_VOLLEY, urand(9000, 13000));
                        break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

};

class npc_chaos_seed : public CreatureScript
{
	struct npc_chaos_seedAI : public ScriptedAI
	{
		npc_chaos_seedAI(Creature* creature) : ScriptedAI(creature) {}

		void MovementInform(uint32 /*type*/, uint32 id)
		{
			if (id == 1)
			{
				DoCast(me, SPELL_SEED_OF_CHAOS, true);
				me->DespawnOrUnsummon(2000);
			}
		}
	};

public:
	npc_chaos_seed() : CreatureScript("npc_chaos_seed") {}

	CreatureAI* GetAI(Creature* creature) const
	{
		return new npc_chaos_seedAI(creature);
	}
};

/*****************
**Void Lord
******************/

class npc_void_lord : public CreatureScript
{
public:
	npc_void_lord() : CreatureScript("npc_void_lord") {}

	struct npc_void_lordAI : public ScriptedAI
	{
		npc_void_lordAI(Creature *c) : ScriptedAI(c) {}

		uint32 explotion;
		uint32 volley;

		void Reset()
		{
			explotion = 30000;
			volley = 16000;
		}

		void UpdateAI(const uint32 diff)
		{
			if (!UpdateVictim())
				return;

			if (explotion <= diff)
			{
				DoCast(me, SPELL_VOID_BURST);
				explotion = 30000;
			}
			else explotion -= diff;

			if (volley <= diff)
			{
				DoCast(me, SPELL_VOID_INFUSION);
				volley = 16000;
			}
			else volley -= diff;

			DoMeleeAttackIfReady();
		}
	};

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_void_lordAI(pCreature);
	}

};

void AddSC_boss_setesh()
{
    new boss_setesh();
    new npc_setesh_chaos_portal();
    new npc_setesh_void_sentinel();
    new npc_setesh_void_seeker();
	new npc_chaos_seed();
	new npc_void_lord();
}
