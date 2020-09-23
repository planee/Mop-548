/*
* Copyright (C) 2014-2017 RoG_WoW Source  <http://wow.rog.snet
*
* Dont Share The SourceCode
*
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "temple_of_jade_serpent.h"

#define TYPE_CLASS_FIGMENT 8
#define TYPE_CLASS_FIGMENT_DIE 9

enum eSpells
{
    SPELL_WITHER_WILL           = 106736,
    SPELL_TOUCH_OF_NOTHINGNESS  = 106113,
    SPELL_FIGMENT_OF_DOUBT      = 106937,
    SPELL_BOUNDS_OF_REALITY     = 131498,
    SPELL_BOUNDS_OF_REALITY_2   = 117665,
    SPELL_CHI_WAVE              = 132464,
    SPELL_CHI_WAVE_2            = 132466,
    SPELL_SEED_OF_DOUBT         = 123916,
    SPELL_RIFT_OF_DOUBT         = 109504,
    
    SPELL_FIGMENT_OF_DOUBT_2    = 106935,
    SPELL_FIGMENT_OF_DOUBT_3    = 106936,
    SPELL_COPY_WEAPON           = 41054,
    SPELL_COPY_WEAPON_2         = 41055,
    SPELL_GROW                  = 104921,
    SPELL_DROWNED_STATE         = 117509,
    SPELL_DRAW_DOUBT            = 106290,
    SPELL_KNOCK_BACK_SELF       = 117525,
    SPELL_GATHERING_DOUBT       = 117570,
    SPELL_GATHERING_DOUBT_2     = 117571,
    SPELL_INVISIBILITY_DETECTION= 126839,
    SPELL_WEAKENED_BLOWS        = 115798,
    SPELL_RELEASE_DOUBT         = 106112,
    SPELL_SHADOWFORM            = 142024,
};

enum eEvents
{
    EVENT_WITHER_WILL = 1,
    EVENT_TOUCH_OF_NOTHINGNESS = 2,
    EVENT_BOUNDS_OF_REALITY = 3,


    /* Figment of Doubt */    
    EVENT_GATHERING_DOUBT = 4,
    EVENT_SPELL_PHANTOM_STRIKE = 5,
    EVENT_SPELL_ARMOR_BUFF = 6,
    EVENT_SPELL_FURY = 7,
    EVENT_SANCTUARY = 8,
    EVENT_STUN = 10,
    EVENT_BLADE_SONG = 11,
    EVENT_UNTAMED_FURY = 12,
    EVENT_GLIMPSE_OF_MADNESS = 13,
    EVENT_ATTACK_PLAYERS = 14,
};

enum Actions
{
    ACTION_FIGMENT_ATTACK,
};

enum eTalks
{
    TALK_AGGRO,
    TALK_DEATH,
    TALK_FIGMENT_01,
    TALK_FIGMENT_02,
    TALK_RESET,
    TALK_SLAY_01,
    TALK_SLAY_02,
};

enum Achievements
{
    // Defeat the Sha of Doubt in Temple of the Jade Serpent while under the effects of Purified Water.
    ACHI_CLEANING_UP = 6475,
    // Defeat the Sha of Doubt in Temple of the Jade Serpent while under the effect of 4 Seeds of Doubt on Heroic difficulty.
    ACHI_SEEDS_OF_DOUBT = 6671,
    // Defeat the Sha of Doubt in Temple of the Jade Serpent
    ACHI_TEMPLE_OF_THE_JADE_SERPENT = 6757,
    //Defeat the Sha of Doubt in Temple of the Jade Serpent in Heroic Difficulty
    ACHI_HEROIC_TEMPLE_OF_THE_JADE_SERPENT = 6758,
};

class boss_sha_of_doubt : public CreatureScript
{
    public:
        boss_sha_of_doubt() : CreatureScript("boss_sha_of_doubt") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_sha_of_doubt_AI(creature);
        }

        struct boss_sha_of_doubt_AI : public BossAI
        {
            boss_sha_of_doubt_AI(Creature* creature) : BossAI(creature, BOSS_SHA_OF_DOUBT_DATA)
            {
                me->CastSpell(me, SPELL_INVISIBILITY_DETECTION, false);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

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
            bool isAtBoundsOfReality;

            void Reset()
            {
                Talk(TALK_RESET);
                events.Reset();
                _Reset();

                DespawnCreatures(NPC_FIGMENT_OF_DOUBT);
                me->SetReactState(REACT_PASSIVE);
                if (instance)
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_DRAW_DOUBT);
                me->RemoveAura(SPELL_RIFT_OF_DOUBT);

                if (Creature* liu = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_LIU_FLAMEHEART)))
                {
                    if (liu->isDead())
                    {
                        if (GameObject* go = me->FindNearestGameObject(GO_DOOR_LIU_FLAMEHEART, 50.0f))
                            go->SetGoState(GO_STATE_ACTIVE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    }
                }
            }

            void KilledUnit(Unit* u)
            {
                Talk(TALK_SLAY_01 + urand(0, 1));
            }

            void JustDied(Unit* u)
            {
                Talk(TALK_DEATH);
                Map* map = me->GetMap();
                if (GameObject* go = me->FindNearestGameObject(GO_DOOR_LIU_FLAMEHEART, 50.0f))
                go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);

                if (instance)
                instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_DRAW_DOUBT);

                me->RemoveAura(SPELL_RIFT_OF_DOUBT);

                if (map && map->IsDungeon())
                {
                    Map::PlayerList const &PlayerList = map->GetPlayers();
                    if (!PlayerList.isEmpty())
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    if (Player* player = i->getSource())
                    {
                       if (player->HasAura(SPELL_TOUCH_OF_NOTHINGNESS))
                       player->RemoveAurasDueToSpell(SPELL_TOUCH_OF_NOTHINGNESS, player->GetGUID());
                       if (map->IsHeroic())
                       {
                           instance->DoCompleteAchievement(ACHI_HEROIC_TEMPLE_OF_THE_JADE_SERPENT); //Achievement Temple of the Jade Serpent Heroic
                           instance->DoCompleteAchievement(ACHI_TEMPLE_OF_THE_JADE_SERPENT);
                           if (player->HasAura(SPELL_PURIFIED_WATER)) // Spell Purified Water
                           player->CompletedAchievement(sAchievementMgr->GetAchievement(ACHI_CLEANING_UP));
                           if (AuraPtr seed = player->GetAura(SPELL_SEED_OF_DOUBT))
                           if (seed->GetStackAmount() == 4)
                           player->CompletedAchievement(sAchievementMgr->GetAchievement(ACHI_SEEDS_OF_DOUBT));
                        }
                       else 
                           instance->DoCompleteAchievement(ACHI_TEMPLE_OF_THE_JADE_SERPENT); //Achievement Temple of the Jade Serpent
                     }
                }
                DespawnCreatures(NPC_FIGMENT_OF_DOUBT);
            }

            void EnterCombat(Unit* unit)
            {
                me->SetReactState(REACT_AGGRESSIVE);
                Talk(TALK_AGGRO);
                if (GameObject* go = me->FindNearestGameObject(GO_DOOR_LIU_FLAMEHEART, 50.0f))
                    go->SetGoState(GO_STATE_READY);

                events.ScheduleEvent(EVENT_WITHER_WILL, 5000);
                events.ScheduleEvent(EVENT_TOUCH_OF_NOTHINGNESS, 500);
                events.ScheduleEvent(EVENT_BOUNDS_OF_REALITY, 3000);
            }

            void DoAction(const int32 action)
            {
                if (action == ACTION_START_SHA_OF_DOUBT)
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }

            void DespawnCreatures(uint32 entry)
            {
                std::list<Creature*> creatures;
                GetCreatureListWithEntryInGrid(creatures, me, entry, 50.0f);

                if (creatures.empty())
                    return;

                for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                    (*iter)->DespawnOrUnsummon();
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
                        case EVENT_WITHER_WILL:
                            if (!me->HasAura(SPELL_BOUNDS_OF_REALITY_2))
                            {
                                if (Unit* firstTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                {
                                    me->CastSpell(firstTarget, SPELL_WITHER_WILL, false);
                                    if (Unit* secondTarget = SelectTarget(SELECT_TARGET_RANDOM))
                                    if (firstTarget != secondTarget)
                                        me->CastSpell(secondTarget, SPELL_WITHER_WILL, false);
                                }
                            }
                            events.ScheduleEvent(EVENT_WITHER_WILL, 5000);

                            break;
                        case EVENT_TOUCH_OF_NOTHINGNESS:
                            if (!me->HasAura(SPELL_BOUNDS_OF_REALITY_2))
                                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                                    me->CastSpell(target, SPELL_TOUCH_OF_NOTHINGNESS, false);
                            events.ScheduleEvent(EVENT_TOUCH_OF_NOTHINGNESS, 30000);

                            break;
                        case EVENT_BOUNDS_OF_REALITY:
                        {
                            Talk(TALK_FIGMENT_01 + urand(0, 1));
                            if (me->GetInstanceScript())
                                me->GetInstanceScript()->SetData(TYPE_CLASS_FIGMENT, 0);
                            me->CastSpell(me, SPELL_BOUNDS_OF_REALITY_2, false);
                            me->CastSpell(me, SPELL_RIFT_OF_DOUBT, true);
                            //Spawns the figment of doubt
                            Map::PlayerList const& PlayerList = me->GetMap()->GetPlayers();

                            if (!PlayerList.isEmpty())
                            {
                                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                                {
                                    Player* plr = i->getSource();
                                    if (!plr)
                                        continue;
                                    plr->CastSpell(plr, SPELL_FIGMENT_OF_DOUBT_3, false);
                                    if (Creature* creature = plr->FindNearestCreature(NPC_FIGMENT_OF_DOUBT, 5.0f, true))
                                        creature->AI()->DoAction(ACTION_FIGMENT_ATTACK);
                                }
                            }
                            events.ScheduleEvent(EVENT_BOUNDS_OF_REALITY, 60000);

                            break;
                        }
                        default:
                            break;
                    }
                }
                
                if (!me->HasAura(SPELL_BOUNDS_OF_REALITY_2))
                    DoMeleeAttackIfReady();
            }
        };
};

class mob_figment_of_doubt : public CreatureScript
{
    public:
        mob_figment_of_doubt() : CreatureScript("mob_figment_of_doubt") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new mob_figment_of_doubt_AI(creature);
        }

        enum Classes
        {
            CLASS_DPS,
            CLASS_HEAL,
            CLASS_TANK,
        };

        struct mob_figment_of_doubt_AI : public ScriptedAI
        {
            mob_figment_of_doubt_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
                creature->CastSpell(creature, SPELL_GROW, false);
                creature->CastSpell(creature, SPELL_SHADOWFORM, false);
                Classes cl = Classes(me->GetInstanceScript()->GetData(TYPE_CLASS_FIGMENT));
                if (cl <= CLASS_TANK)
                    _class = cl;
                else
                    _class = CLASS_DPS;

                creature->SetReactState(REACT_PASSIVE);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                if (instance)
                {
                    if (me->isSummon())
                    {
                        player = me->ToTempSummon()->GetSummoner()->ToPlayer();
                    }
                }

                emote = false;
                aggro = false;
            }
            EventMap events;
            Classes _class;
            InstanceScript* instance;
            Player* player;
            bool emote;
            bool aggro;

            void JustDied(Unit* killer)
            {
                me->CastSpell(me, SPELL_DROWNED_STATE, false);
                me->RemoveAura(SPELL_GATHERING_DOUBT);
                player->RemoveAura(SPELL_DRAW_DOUBT);
                me->ForcedDespawn(5000);
                me->GetInstanceScript()->SetData(TYPE_CLASS_FIGMENT_DIE, _class);
            }

            void EnterCombat(Unit* u)
            {
                if (player)   
                    me->AddAura(SPELL_DRAW_DOUBT, player);
                
                me->CastSpell(me, SPELL_GATHERING_DOUBT, false);
                events.ScheduleEvent(EVENT_GATHERING_DOUBT, 1000);               

                switch (_class)
                {
                    case CLASS_DPS:
                        events.ScheduleEvent(EVENT_SPELL_FURY, 5000);
                        events.ScheduleEvent(EVENT_BLADE_SONG, 13000);
                        events.ScheduleEvent(EVENT_GLIMPSE_OF_MADNESS, 8000);
                    case CLASS_HEAL:
                        events.ScheduleEvent(EVENT_SPELL_PHANTOM_STRIKE, 20000);
                        events.ScheduleEvent(EVENT_STUN, 7000);
                    case CLASS_TANK:
                        events.ScheduleEvent(EVENT_SPELL_ARMOR_BUFF, 10000);
                        events.ScheduleEvent(EVENT_SANCTUARY, 10000);
                        events.ScheduleEvent(EVENT_STUN, 7000);
                        break;
                }
            }

            void DoAction(const int32 action)
            {
                switch (action)
                {
                case ACTION_FIGMENT_ATTACK:
                    me->SetInCombatWithZone();
                    events.ScheduleEvent(EVENT_ATTACK_PLAYERS, 2 * IN_MILLISECONDS);
                    break;
                }
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (!emote)
                {
                    me->HandleEmoteCommand(EMOTE_STATE_DROWNED);
                    emote = true;
                }

                if (aggro)
                {
                    if (me->getVictim() != player)
                        AttackStart(player);
                }

                if (player->isDead())
                    me->DespawnOrUnsummon();

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_ATTACK_PLAYERS:
                            me->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            me->SetReactState(REACT_AGGRESSIVE);
                            if (player)
                            {
                                AttackStart(player);
                                me->AddThreat(player, 99999.0f);                           
                                aggro = true;
                            }
                            events.CancelEvent(EVENT_ATTACK_PLAYERS);
                            break;
                        case EVENT_GATHERING_DOUBT:
                            if (me->GetAuraCount(SPELL_GATHERING_DOUBT_2) == 30)
                            {
                                if (Creature* bossSha = ObjectAccessor::GetCreature(*me, instance->GetData64(BOSS_SHA_OF_DOUBT)))
                                {
                                    me->CastSpell(bossSha, SPELL_CHI_WAVE, true);
                                    me->CastSpell(bossSha, SPELL_RELEASE_DOUBT, false);
                                    bossSha->RemoveAura(SPELL_RIFT_OF_DOUBT);
                                }

                                me->RemoveAura(SPELL_GATHERING_DOUBT);

                                me->DealDamage(me, me->GetMaxHealth());
                                me->DespawnOrUnsummon(1000);
                            }
                            else
                                events.ScheduleEvent(EVENT_GATHERING_DOUBT, 1000);
                            break;
                        case EVENT_SPELL_PHANTOM_STRIKE:
                            if (me->getVictim())
                                me->CastSpell(me->getVictim(), 9806, false);
                            events.ScheduleEvent(EVENT_SPELL_PHANTOM_STRIKE, 20000);
                            break;
                        case EVENT_SPELL_ARMOR_BUFF:
                            me->CastSpell(me, 34199, false);
                            events.ScheduleEvent(EVENT_SPELL_ARMOR_BUFF, 10000);
                            break;
                        case EVENT_SPELL_FURY:
                            me->CastSpell(me, 15494, false);
                            events.ScheduleEvent(EVENT_SPELL_FURY, 5000);
                            break;
                        case EVENT_SANCTUARY:
                            me->CastSpell(me, 69207, false);
                            events.ScheduleEvent(EVENT_SANCTUARY, 10000);
                            break;
                        case EVENT_STUN:
                            if (me->getVictim())
                                me->CastSpell(me->getVictim(), 23454, false);
                            events.ScheduleEvent(EVENT_STUN, 7000);
                            break;
                        case EVENT_BLADE_SONG:
                            me->CastSpell(me, 38282, false);
                            events.ScheduleEvent(EVENT_BLADE_SONG, 13000);
                            break;
                        case EVENT_UNTAMED_FURY:
                            me->CastSpell(me, 23719, false);
                            events.ScheduleEvent(EVENT_UNTAMED_FURY, 9000);
                            break;
                        case EVENT_GLIMPSE_OF_MADNESS:
                            if (me->getVictim())
                                me->CastSpell(me->getVictim(), 26108, false);
                            events.ScheduleEvent(EVENT_GLIMPSE_OF_MADNESS, 8000);
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };
};

class ShaCheck
{
public:
    bool operator()(const WorldObject* target)
    {
        if (target->ToCreature())
        {
            if (target->GetEntry() == BOSS_SHA_OF_DOUBT)
                return false;
        }
        return true;
    }
};

//Called Draw Doubt 106112
class spell_sha_draw_doubt : public SpellScriptLoader
{
public:
    spell_sha_draw_doubt() : SpellScriptLoader("spell_sha_draw_doubt") { }

    class spell_sha_draw_doubt_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_sha_draw_doubt_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            if (!GetCaster())
                return;

            targets.remove_if(ShaCheck());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_sha_draw_doubt_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_sha_draw_doubt_SpellScript();
    }
};

void AddSC_boss_sha_of_doubt()
{
    new boss_sha_of_doubt();
    new mob_figment_of_doubt();
    new spell_sha_draw_doubt();
}