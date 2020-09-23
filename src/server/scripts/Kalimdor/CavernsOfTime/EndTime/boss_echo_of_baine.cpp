#include "ScriptPCH.h"
#include "end_time.h"

enum Yells
{
    SAY_AGGRO   = 0,
    SAY_DEATH   = 1,
    SAY_INTRO   = 2,
    SAY_KILL    = 3,
    SAY_SPELL   = 4,
	SAY_THROW_TOTEM,
};

enum Spells
{
    SPELL_BAINE_VISUALS     = 101624,
	SPELL_BAINE_AXE_VIS     = 101834, //Visual on Axe

    SPELL_THROW_TOTEM       = 101615,
    SPELL_PULVERIZE         = 101626, 
    SPELL_PULVERIZE_DMG     = 101627, 
    SPELL_PULVERIZE_AOE     = 101625,
    SPELL_MOLTEN_AXE        = 101836,
    SPELL_MOLTEN_FIST       = 101866,
    SPELL_THROW_TOTEM_BACK  = 101602,
    SPELL_THROW_TOTEM_AURA  = 107837,
};

enum Events
{
    EVENT_PULVERIZE        = 1,
    EVENT_THROW_TOTEM      = 2,
    EVENT_CHECK_SELF       = 3,
	EVENT_PULVERIZE_DAMAGE = 4,
};

enum Adds
{
    NPC_ROCK_ISLAND     = 54496,
    NPC_BAINES_TOTEM    = 54434,
	NPC_PUL_LOCATION    = 54447,
};

#define SAY_LAVA_CHAT "My wrath knows no bounds!"
#define SAY_LAVA2_CHAT "There will be no escape!"

class boss_echo_of_baine : public CreatureScript
{
    public:
        boss_echo_of_baine() : CreatureScript("boss_echo_of_baine") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new boss_echo_of_baineAI(pCreature);
        }

        struct boss_echo_of_baineAI : public BossAI
        {
            boss_echo_of_baineAI(Creature* pCreature) : BossAI(pCreature, DATA_ECHO_OF_BAINE)
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
                bIntroDone = false;
            }

            bool bIntroDone;

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
				me->SetFloatValue(UNIT_FIELD_BOUNDING_RADIUS, 5.0f);
				me->SetFloatValue(UNIT_FIELD_COMBAT_REACH, 5.0f);
				if (instance) // Open the doors.
				{
					instance->SetBossState(DATA_ECHO_OF_BAINE, NOT_STARTED);
				}
				//Disable Wall of Flame 
				if (GameObject* go = me->FindNearestGameObject(GO_WALL_OF_FLAME, 500.0f))
					go->Delete();
				//Rebuilding Platform
				if (GameObject* platform = me->FindNearestGameObject(GO_PLATFORM_2, 500.0f))
					platform->SetDestructibleState(GO_DESTRUCTIBLE_REBUILDING);
				else if (GameObject* platform = me->FindNearestGameObject(GO_PLATFORM_3, 500.0f))
					platform->SetDestructibleState(GO_DESTRUCTIBLE_REBUILDING);
				else if (GameObject* platform = me->FindNearestGameObject(GO_PLATFORM_4, 500.0f))
					platform->SetDestructibleState(GO_DESTRUCTIBLE_REBUILDING);
				else if (GameObject* platform = me->FindNearestGameObject(GO_PLATFORM_1, 500.0f))
					platform->SetDestructibleState(GO_DESTRUCTIBLE_REBUILDING);
				//Condition for visual of Baine
				if (!me->HasAura(SPELL_BAINE_VISUALS))
					DoCast(me, SPELL_BAINE_VISUALS);
				//Delete totem of Baines
				std::list<Creature*> creatures;
				GetCreatureListWithEntryInGrid(creatures, me, NPC_BAINES_TOTEM, 1000.0f);
				if (!creatures.empty())
				for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
					(*iter)->DespawnOrUnsummon();
			}

            void EnterCombat(Unit* /*who*/)
            {
                Talk(SAY_AGGRO);				
				//Active Wall of Flame during the combat
				me->SummonGameObject(GO_WALL_OF_FLAME, 4418.55f, 1391.46f, 119.009f, 4.67748f, 0, 0, 0, 1, 9000000);
				me->SummonGameObject(GO_WALL_OF_FLAME, 4339.28f, 1391.69f, 118.867f, 3.9619f, 0, 0, 0, 1, 9000000);
				me->SummonGameObject(GO_WALL_OF_FLAME, 4339.28f, 1391.69f, 118.867f, 3.9619f, 0, 0, 0, 1, 9000000);
				me->SummonGameObject(GO_WALL_OF_FLAME, 4418.55f, 1391.46f, 119.009f, 4.67748f, 0, 0, 0, 1, 9000000);

				events.ScheduleEvent(EVENT_PULVERIZE, 60000);
				events.ScheduleEvent(EVENT_THROW_TOTEM, 10000);
                events.ScheduleEvent(EVENT_CHECK_SELF, 1000);

                instance->SetBossState(DATA_ECHO_OF_BAINE, IN_PROGRESS);
                DoZoneInCombat();

            }

            void EnterEvadeMode()
            {
                instance->SetData(DATA_PLATFORMS, NOT_STARTED);
				//Delete Wall of Flame if group death
				std::list<GameObject*> goList;
				GetGameObjectListWithEntryInGrid(goList, me, GO_WALL_OF_FLAME, 500.0f);
				for (auto itr : goList)
					itr->Delete();
                BossAI::EnterEvadeMode();
            }

            void MoveInLineOfSight(Unit* who)
            {
                if (bIntroDone)
                    return;

                if (who->GetTypeId() != TYPEID_PLAYER)
                    return;

                if (!me->IsWithinDistInMap(who, 100.0f, false))
                    return;

                Talk(SAY_INTRO);
                bIntroDone = true;
            }

            void JustDied(Unit* killer)
            {
                _JustDied();
                Talk(SAY_DEATH);
				
				//Delete Wall of Flame if group death
				std::list<GameObject*> goList;
				GetGameObjectListWithEntryInGrid(goList, me, GO_WALL_OF_FLAME, 500.0f);
				for (auto itr : goList)
					itr->Delete();
                // Quest
                Map::PlayerList const &PlayerList = instance->instance->GetPlayers();
                if (!PlayerList.isEmpty())
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        if (Player* pPlayer = i->getSource())
                            if (me->GetDistance2d(pPlayer) <= 50.0f && pPlayer->GetQuestStatus(30097) == QUEST_STATUS_INCOMPLETE)
                                DoCast(pPlayer, SPELL_ARCHIVED_BAINE, true);
			    if (instance)
				{
								instance->SetBossState(DATA_ECHO_OF_BAINE, DONE);													
								/*instance->HandleGameObject(4001, true); // Open the doors.
								instance->HandleGameObject(4002, true);*/
								instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me); // Remove
			    }
            }

            void KilledUnit(Unit * /*victim*/)
            {
                Talk(SAY_KILL);
            }

            void MovementInform(uint32 type, uint32 data)
            {
                if (type == EFFECT_MOTION_TYPE)
                    if (data == EVENT_JUMP)
                        DoCastAOE(SPELL_PULVERIZE_DMG);
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

				//Add visual for axe baine
				if (me->HasAura(SPELL_MOLTEN_AXE) && !me->HasAura(SPELL_BAINE_AXE_VIS))
					DoCast(me, SPELL_BAINE_AXE_VIS);
				else if (!me->HasAura(SPELL_MOLTEN_AXE) && me->HasAura(SPELL_BAINE_AXE_VIS))
					me->RemoveAurasDueToSpell(SPELL_BAINE_AXE_VIS);
				
				Map::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
				if (!PlayerList.isEmpty())
				for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
				if (Player* playr = i->getSource())
				{

					if (playr->IsInWater() && !playr->HasAura(SPELL_MOLTEN_FIST))
						playr->AddAura(SPELL_MOLTEN_FIST, playr); // Add the damage aura to players in Magma.
					if (me->IsInWater() && !me->HasAura(SPELL_MOLTEN_AXE) && playr->IsInWater())//add the molten axe damage
						DoCast(me, SPELL_MOLTEN_AXE);
				}
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_CHECK_SELF:
							/*if (me->HasUnitMovementFlag(MOVEMENTFLAG_SWIMMING) && !me->HasAura(SPELL_MOLTEN_AXE))
							{
								DoCast(me, SPELL_MOLTEN_AXE);
							}*/
							if (me->GetPositionY() < 1378.0f)
                            {
                                EnterEvadeMode();
                                return;
                            }
                            events.ScheduleEvent(EVENT_CHECK_SELF, 1000);
                            break;
                        case EVENT_PULVERIZE:
							me->MonsterYell(urand(0, 1) == 1 ? SAY_LAVA_CHAT : SAY_LAVA2_CHAT, 0, 0);
							Talk(SAY_SPELL); 
							if (Creature * target = me->FindNearestCreature(NPC_PUL_LOCATION, 250.0f))
							{
								me->CastSpell(target, SPELL_PULVERIZE_AOE, true);
							}
							events.ScheduleEvent(EVENT_PULVERIZE, 60000); // every 60 secs.
							events.ScheduleEvent(EVENT_PULVERIZE_DAMAGE, 3000); // You have 3 secs to run.
                            //events.ScheduleEvent(EVENT_THROW_TOTEM, 25000);
                            //events.ScheduleEvent(EVENT_THROW_TOTEM, 25000);
                            break;
                        case EVENT_THROW_TOTEM:
                        {
						    Talk(SAY_THROW_TOTEM);
                            Unit* pTarget = NULL;
                            pTarget = SelectTarget(SELECT_TARGET_FARTHEST, 1, PositionSelector());
                            if (!pTarget)
                                pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, PositionSelector());
                            if (pTarget)
                                DoCast(pTarget, SPELL_THROW_TOTEM);
							events.ScheduleEvent(EVENT_THROW_TOTEM, 25000); // every 25 secs.
                            break;
                        }
						case EVENT_PULVERIZE_DAMAGE:
							if (GameObject* platform = me->FindNearestGameObject(GO_PLATFORM_2, 10.0f))
								platform->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);
							else if (GameObject* platform = me->FindNearestGameObject(GO_PLATFORM_3, 10.0f))
								platform->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);
							else if (GameObject* platform = me->FindNearestGameObject(GO_PLATFORM_4, 10.0f))
								platform->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);
							else if (GameObject* platform = me->FindNearestGameObject(GO_PLATFORM_1, 10.0f))
								platform->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);
							/*if (Creature * target = me->FindNearestCreature(NPC_PUL_LOCATION, 100.0f))
								DoCast(target, SPELL_PULVERIZE_DMG);*/
							break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        private:
            struct PositionSelector : public std::unary_function<Unit*, bool>
            {
                public:
                    
                    //PositionSelector(bool b) : _b(b) {}

                    bool operator()(Unit const* target) const
                    {
                        if (target->GetTypeId() != TYPEID_PLAYER)
                            return false;

                        if (target->GetAreaId() != AREA_OBSIDIAN)
                            return false;

                        if (target->IsInWater())
                            return false;

                        return true;
                    }
                private:
                    bool _b;
            };
        };      
};

class npc_echo_of_baine_baines_totem : public CreatureScript
{
    public:
        npc_echo_of_baine_baines_totem() : CreatureScript("npc_echo_of_baine_baines_totem") { }

        CreatureAI* GetAI(Creature* pCreature) const
        {
            return new npc_echo_of_baine_baines_totemAI(pCreature);
        }

        struct npc_echo_of_baine_baines_totemAI : public Scripted_NoMovementAI
        {
            npc_echo_of_baine_baines_totemAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature){ }

            //bool bDespawn;

            //void OnSpellClick(Unit* /*who*/)
            /*{
                if (!bDespawn)
                {
                    bDespawn = true;
                    me->DespawnOrUnsummon();
                }
            }*/
			bool totem;

			void Reset()
			{
				totem = true;
			}

			void DamageTaken(Unit* /*attacker*/, uint32& damage)
			{
				me->setFaction(2110);
				if (Creature * boss = me->FindNearestCreature(NPC_ECHO_OF_BAINE, 300.0f))
				if (totem)
				{
					DoCast(boss, SPELL_THROW_TOTEM_BACK);
					me->DespawnOrUnsummon(1000);
					totem = false;
				}
			}
		private:
			EventMap events;
        };      
};

class spell_echo_of_baine_pulverize_aoe : public SpellScriptLoader
{
    public:
        spell_echo_of_baine_pulverize_aoe() : SpellScriptLoader("spell_echo_of_baine_pulverize_aoe") { }

        class spell_echo_of_baine_pulverize_aoe_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_echo_of_baine_pulverize_aoe_SpellScript);

            void FilterTargets(std::list<WorldObject*>& targets)
            {
                if (!GetCaster() || !GetCaster()->getVictim())
                    return;

                std::list<WorldObject*> tempList;
                for (std::list<WorldObject*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
                    if ((*itr)->ToUnit() && !(*itr)->ToUnit()->IsInWater())
                        tempList.push_back((*itr));

                if (tempList.size() > 1)
                    tempList.remove(GetCaster()->getVictim());

                targets.clear();
                if (!tempList.empty())
                    targets.push_back(WoWSource::Containers::SelectRandomContainerElement(tempList));
            }

            void HandleDummy(SpellEffIndex /*effIndex*/)
			{
                if (!GetCaster() || !GetHitUnit())
                    return;

                GetCaster()->CastSpell(GetHitUnit(), SPELL_PULVERIZE, true);
            }

            void Register()
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_echo_of_baine_pulverize_aoe_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                OnEffectHitTarget += SpellEffectFn(spell_echo_of_baine_pulverize_aoe_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_echo_of_baine_pulverize_aoe_SpellScript();
        }
};

void AddSC_boss_echo_of_baine()
{
    new boss_echo_of_baine();
    new npc_echo_of_baine_baines_totem();
    new spell_echo_of_baine_pulverize_aoe();
}