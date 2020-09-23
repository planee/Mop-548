#include "ScriptPCH.h"
#include "halls_of_origination.h"

enum ScriptTexts
{
    SAY_DEATH   = 0,
    SAY_AGGRO   = 1,
    SAY_KILL    = 2,
};

enum Spells
{
    SPELL_FLAME_BOLT                = 77370,
    SPELL_FLAME_BOLT_DMG            = 75540, 
    SPELL_FLAME_BOLT_DMG_H          = 89881, 
    SPELL_RAGING_SMASH              = 83650,
    SPELL_EARTH_SPIKE               = 94974,
    SPELL_EARTH_SPIKE_DMG           = 75339,
    SPELL_EARTH_SPIKE_DMG_H         = 89882,
    SPELL_EARTH_SPIKE_KILL          = 89398,
    SPELL_QUICKSAND                 = 75546,
    SPELL_QUICKSAND_AOE             = 75547,
    SPELL_QUICKSAND_AOE_H           = 89880,
    SPELL_QUICKSAND_DIS             = 89396,

    SPELL_SAND_VORTEX_DUMMY1        = 79441,
    SPELL_SAND_VORTEX_DUMMY2        = 93570,
    SPELL_SAND_VORTEX               = 83097,
    SPELL_SAND_VORTEX_DMG           = 83096, 

    SPELL_SUBMERGE                  = 53421,

    SPELL_SUMMON_DUSTBONE_HORROR    = 75521,
    SPELL_SUMMON_JEWELED_SCARAB     = 75462,

    SPELL_SMASH                     = 75453,

	SPELL_PTAH_EXPLOSION            = 75519,
	SPELL_SANDSTORM                 = 75491,

	RIDE_CAMEL                      = 89397,
};
 
enum Events
{
    EVENT_FLAME_BOLT    = 1,
    EVENT_RAGING_SMASH  = 2,
    EVENT_EARTH_POINT   = 3,
    EVENT_SUBMERGE      = 4,
    EVENT_SUMMON        = 5,      
    EVENT_STORM_MOVE    = 6,
    EVENT_VORTEX_DUST   = 7,
    EVENT_SMASH         = 8,
    EVENT_MERGE         = 9,
	EVENT_PTAH_EXPLODE  = 10,
	EVENT_QUICKSAND     = 11,
};
 
enum Adds
{
    NPC_QUICKSAND               = 40503, // 75546
    NPC_DUSTBONE_HORROR         = 40450,
    NPC_JEWELED_SCARAB          = 40458,
    NPC_TUMULTUOUS_EARTHSTORM   = 40406,
    NPC_BEETLE_STALKER          = 40459,
};

enum PtahData
{
	DATA_SUMMON_DEATHS = 0
};

 
class boss_earthrager_ptah : public CreatureScript
{
    public:
        boss_earthrager_ptah() : CreatureScript("boss_earthrager_ptah") {}
 
        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_earthrager_ptahAI(creature);
        }

        struct boss_earthrager_ptahAI : public BossAI
        {
            boss_earthrager_ptahAI(Creature* pCreature) : BossAI(pCreature, DATA_EARTHRAGER_PTAH)
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

            uint8 count;
            uint8 phase;

            void InitializeAI()
            {
                if (!instance || static_cast<InstanceMap*>(me->GetMap())->GetScriptId() != sObjectMgr->GetScriptId(HOScriptName))
                    me->IsAIEnabled = false;
                else if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
				_summonDeaths = 0;
                _Reset();

                me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
                
                phase = 0;
            }

            void EnterCombat(Unit * who)
            {
                Talk(SAY_AGGRO);

                events.ScheduleEvent(EVENT_FLAME_BOLT, urand(5000, 8000));
                events.ScheduleEvent(EVENT_RAGING_SMASH, urand(7000, 10000));
                events.ScheduleEvent(EVENT_EARTH_POINT, urand(12000, 15000));
                DoZoneInCombat();
                instance->SetBossState(DATA_EARTHRAGER_PTAH, IN_PROGRESS);
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
						Map* map = me->GetMap();
						if (!map)
							return;
						//Achievement Straw That Broke the Camel's Back
						if (map->GetDifficulty() == DUNGEON_DIFFICULTY_HEROIC && player->HasAura(RIDE_CAMEL))
							instance->DoCompleteAchievement(5294);
					}
				}
            }
            
            void KilledUnit(Unit* who)
            {
                Talk(SAY_KILL);
            }
      
			void SendWeather(WeatherState weather, float grade) const
			{
				WorldPacket data(SMSG_WEATHER, 9);
				data << uint32(weather);
				data << float(grade);
				data << uint8(0);
				SendPacketToPlayers(&data);
			}

			// Send packet to all players in Tomb of the Earthrager
			void SendPacketToPlayers(WorldPacket const* data) const
			{
				Map::PlayerList const& players = me->GetMap()->GetPlayers();
				if (!players.isEmpty())
				for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
				if (Player* player = itr->getSource())
				if (player->GetAreaId() == AREA_TOMB_OF_THE_EARTHRAGER)
					player->GetSession()->SendPacket(data);
			}

			//void SetData(uint32 index, uint32 /*value*/)
			/*{
				if (index == DATA_SUMMON_DEATHS)
				{
					++_summonDeaths;
					if (_summonDeaths == 10) // All summons died
					events.ScheduleEvent(EVENT_MERGE, 1000);
					
				}
			}*/

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;
                                       
                events.Update(diff);
 
                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (me->HealthBelowPct(50) && phase == 0)
                {
                    phase = 1;
                    me->RemoveAllAuras();
                    me->AttackStop();
                    me->SetReactState(REACT_PASSIVE);
					DoCast(me, SPELL_SANDSTORM);
                    //DoCast(me, SPELL_SUBMERGE);
                    me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
                    events.Reset();
                    events.ScheduleEvent(EVENT_SUBMERGE, 2000);
					events.ScheduleEvent(EVENT_PTAH_EXPLODE, 6000);
                    return;
                }

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_SUBMERGE:
                            for (uint8 i = 0; i < 2; ++i)
                                if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                    DoCast(pTarget, SPELL_SUMMON_DUSTBONE_HORROR, true);
                            
                            for (uint8 i = 0; i < 8; ++i)
                                if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                    DoCast(pTarget, SPELL_SUMMON_JEWELED_SCARAB, true);
						    
							SendWeather(WEATHER_STATE_LIGHT_SANDSTORM, 1.0f);
                            //DoCast(me, SPELL_SAND_VORTEX, true);
                           events.ScheduleEvent(EVENT_MERGE, 30000);
							events.ScheduleEvent(EVENT_QUICKSAND, 10000);
							events.ScheduleEvent(EVENT_VORTEX_DUST, 10000);
                            break;
                        case EVENT_MERGE:
                            me->RemoveAllAuras();
                            me->RemoveFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_NOT_SELECTABLE);
                            me->SetReactState(REACT_AGGRESSIVE);
							SendWeather(WEATHER_STATE_FOG, 0.0f);
                            me->GetMotionMaster()->MoveChase(me->getVictim());
							events.Reset();
                            events.ScheduleEvent(EVENT_FLAME_BOLT, urand(5000, 8000));
                            events.ScheduleEvent(EVENT_RAGING_SMASH, urand(7000, 10000));
                            events.ScheduleEvent(EVENT_EARTH_POINT, urand(12000, 15000));
                            break;
                        case EVENT_FLAME_BOLT:
                            DoCast(me, SPELL_FLAME_BOLT);
                            events.ScheduleEvent(EVENT_FLAME_BOLT, urand(16000, 20000));
                            break;
                        case EVENT_RAGING_SMASH:
                            DoCastVictim(SPELL_RAGING_SMASH);
                            events.ScheduleEvent(EVENT_RAGING_SMASH, urand(10000, 15000));
                            break;
                        case EVENT_EARTH_POINT:
                            if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM))
								DoCast(pTarget, SPELL_EARTH_SPIKE);
                            events.ScheduleEvent(EVENT_EARTH_POINT, urand(20000, 25000));
                            break;  
						case EVENT_PTAH_EXPLODE:
							DoCast(me, SPELL_PTAH_EXPLOSION);
							break;
						case EVENT_QUICKSAND:
							// Spell not in DBC, it is not cast either, according to sniffs
							if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
							{
								if (Creature* quicksand = me->SummonCreature(NPC_QUICKSAND, *target))
									quicksand->SetUInt32Value(UNIT_CREATED_BY_SPELL, SPELL_QUICKSAND);
								DoCast(target, SPELL_QUICKSAND);
								events.ScheduleEvent(EVENT_QUICKSAND, 10000);
							}
							break;
						case EVENT_VORTEX_DUST:
							if (IsHeroic())
							{
								DoCastAOE(SPELL_SAND_VORTEX);
							}
							events.ScheduleEvent(EVENT_VORTEX_DUST, 10000);
							return;
                    }
                }

                DoMeleeAttackIfReady();
            }
				protected:
					uint8 _summonDeaths;
					uint64 targetGUID;
        };
};

class npc_ptah_dustbone_horror: public CreatureScript
{
    public:
        npc_ptah_dustbone_horror() : CreatureScript("npc_ptah_dustbone_horror") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_ptah_dustbone_horrorAI(pCreature);
        }

        struct npc_ptah_dustbone_horrorAI : public ScriptedAI
        {
            npc_ptah_dustbone_horrorAI(Creature* pCreature) : ScriptedAI(pCreature)
            {
            }

            EventMap events;

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* who)
            {
                events.ScheduleEvent(EVENT_SMASH, urand(2000, 8000));
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
                        case EVENT_SMASH:
                            DoCast(me->getVictim(), SPELL_SMASH);
                            events.ScheduleEvent(EVENT_SMASH, urand(5000, 10000));
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class spell_earthrager_ptah_flame_bolt : public SpellScriptLoader
{
public:
	spell_earthrager_ptah_flame_bolt() : SpellScriptLoader("spell_earthrager_ptah_flame_bolt") { }

	class spell_earthrager_ptah_flame_bolt_SpellScript : public SpellScript
	{
		PrepareSpellScript(spell_earthrager_ptah_flame_bolt_SpellScript);

		void FilterTargets(std::list<WorldObject*>& targets)
		{
			WoWSource::Containers::RandomResizeList(targets, GetCaster()->GetMap()->IsHeroic() ? 3 : 2);
		}

		void Register()
		{
			OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_earthrager_ptah_flame_bolt_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
		}
	};

	SpellScript* GetSpellScript() const
	{
		return new spell_earthrager_ptah_flame_bolt_SpellScript();
	}
};

class spell_earthrager_ptah_explosion : public SpellScriptLoader
{
public:
	spell_earthrager_ptah_explosion() : SpellScriptLoader("spell_earthrager_ptah_explosion") { }

	class spell_earthrager_ptah_explosion_AuraScript : public AuraScript
	{
		PrepareAuraScript(spell_earthrager_ptah_explosion_AuraScript);

		void SetFlags (constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
		{
			if (Unit* ptah = GetCaster())
			{
				ptah->SetFlag(UNIT_FIELD_FLAGS, uint32(UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_UNK_29 | UNIT_FLAG_UNK_31));
				ptah->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
			}
		}

		void RemoveFlags (constAuraEffectPtr /*aurEff*/, AuraEffectHandleModes /*mode*/)
		{
			if (Unit* ptah = GetCaster())
			{
				ptah->RemoveFlag(UNIT_FIELD_FLAGS, uint32(UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_UNK_29 | UNIT_FLAG_UNK_31));
				ptah->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
			}
		}

		void Register()
		{
			OnEffectApply += AuraEffectApplyFn(spell_earthrager_ptah_explosion_AuraScript::SetFlags, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
			OnEffectRemove += AuraEffectRemoveFn(spell_earthrager_ptah_explosion_AuraScript::RemoveFlags, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
		}
	};

	AuraScript* GetAuraScript() const
	{
		return new spell_earthrager_ptah_explosion_AuraScript();
	}
};

class npc_quicksand : public CreatureScript
{
public:
	npc_quicksand() : CreatureScript("npc_quicksand") { }

	CreatureAI* GetAI(Creature* pCreature) const
	{
		return new npc_quicksandAI(pCreature);
	}

	struct npc_quicksandAI : public Scripted_NoMovementAI
	{
		npc_quicksandAI(Creature* creature) : Scripted_NoMovementAI(creature)
		{
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
			me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			me->SetReactState(REACT_PASSIVE);
		}

		void Reset()
		{
			DoCast(me, 75548);
			//DoCastAOE(SPELL_QUICKSAND_AOE);
		}

		void UpdateAI(const uint32 diff)
		{
		}
	};
};

void AddSC_boss_earthrager_ptah()
{
    new boss_earthrager_ptah();
    new npc_ptah_dustbone_horror();
	new npc_quicksand();
	new spell_earthrager_ptah_flame_bolt();
	new spell_earthrager_ptah_explosion();
}
