/*
* Copyright (C) 2014-2017 RoG_WoW Source  <http://wow.rog.snet
*
* Dont Share The SourceCode
*
*/

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "Player.h"
#include "Vehicle.h"
#include "Group.h"

#include "stormstout_brewery.h"

/* Yells and events

First Alemental after Hoptallus:

Ancient Brewmaster says: Whatzit... are they... what are they doin' to our alementals?
Ancient Brewmaster yells: Hey... hey YOU! Those are OUR, flying... beer monsters?

Ancestral Brewmaster:
Ancestral Brewmaster says(1): Are these guys Alliance or Horde?
Ancestral Brewmaster says(3): Why does it matter?
Ancestral Brewmaster says(1): I need to know which side to stop rooting for!

Ancestral Brewmaster says(1): Do you think all of this fighting is educational for this group?
Ancestral Brewmaster says(2): Yes, it will drive them to read books!

Ancestral Brewmaster says(1): Do you think that undead party made it through in one piece?
Ancestral Brewmaster says(2): No, I don't think they had the guts!

Ancestral Brewmaster says(1): Do you think that we can return to life after death?
Ancestral Brewmaster says(2): Sure! That last group did about thirty times!

Ancestral Brewmaster says(1): Finally, we've seen a good group!
Ancestral Brewmaster says(3): Does that mean we can stop coming here now?

Ancestral Brewmaster says(1): How many of these outlanders does it take to paint a wall?
Ancestral Brewmaster says(3): I don't know, how many?
Ancestral Brewmaster says(1): It depends on how hard you throw them!

Ancestral Brewmaster says(1): I liked that last group!
Ancestral Brewmaster says(2): What did you like about it?
Ancestral Brewmaster says(1): I thought it was the last group!

Ancestral Brewmaster says(1): I think that druid had the hots for me!

Ancestral Brewmaster says(1): I wonder if there's anything this healer isn't good at!
Ancestral Brewmaster says(3): Sure! Choosing which group to be in!

Ancestral Brewmaster says(1): I've got a great joke for you!
Ancestral Brewmaster says(x): What's that?
Ancestral Brewmaster says(1): These guys' weapons!

Ancestral Brewmaster says(1): Just when I think a group is the worst, something wonderful happends!
Ancestral Brewmaster says(3): What's that?
Ancestral Brewmaster says(1): They leave!

Ancestral Brewmaster says(1): That last priest had me smitten!

Ancestral Brewmaster says(1): That last shaman really knew his place!
Ancestral Brewmaster says(2): And where is that?
Ancestral Brewmaster says(1): Outland!

Ancestral Brewmaster says(1): The last paladin offered me eternal salvation!
Ancestral Brewmaster says(2): What'd you say?
Ancestral Brewmaster says(1): Kings, please.

Ancestral Brewmaster says(1): This group is awful!
Ancestral Brewmaster says(3): Terrible!
Ancestral Brewmaster says(1): Disgusting!
Ancestral Brewmaster says(3): See you here tomorrow?
Ancestral Brewmaster says(1): Absolutely!

Ancestral Brewmaster says(1): This view is terrible!
Ancestral Brewmaster says(2): What, are you having trouble seeing the fight?
Ancestral Brewmaster says(1): No, I can see it perfectly!

Ancestral Brewmaster says(1): Why didn't that mage put intellect on his weapon?
Ancestral Brewmaster says(2): Because he didn't want it to be smarter than he was!

Ancestral Brewmaster says(1): You fool, you're sleeping through the fight!
Ancestral Brewmaster says(2): Who's the fool? You're watching it!

Ancestral Brewmaster says(1): You know what's the best thing about this group?
Ancestral Brewmaster says(2): What?
Ancestral Brewmaster says(1): They opened the doors so we can escape!

Ancestral Brewmaster says(1): You know, I really envy these guys!
Ancestral Brewmaster says(3): Why's that?
Ancestral Brewmaster says(1): Becose they get to spend so much time with that foxy spirit healer!

Ancestral Brewmaster says(1): You know, getting items must be hard for these guys!
Ancestral Brewmaster says(3): Why's that?
Ancestral Brewmaster says(1): Because pants never drop when they're around!

Ancestral Brewmaster says(1): I think this group will really improve with age!
Ancestral Brewmaster says(2): You think they'll get better?
Ancestral Brewmaster says(1): No, my eyesight will get worse!

Ancestral Brewmaster says(1): I think I'm going to need another drink!
Ancestral Brewmaster says(2): Why do you say that?
Ancestral Brewmaster says(1): I'm beginning to like these guys!

Ancestral Brewmaster says(1): Pay up, they made it through those alementals!
Ancestral Brewmaster says(3): Double or nothing on the next group?
*/

// Chen Stormstout / Auntie Stormstout intro yells.
enum IntroYells
{
    AUNTIE_ENTRANCE_SAY_1   = 0, // Auntie Stormstout says: Oh, hello Zan, it is good of you to visit ol' Auntie Stormstout.
    CHEN_ENTRANCE_SAY_1     = 0, // Chen Stormstout   says: I am not Zan - I am Chen Stormstout!
    AUNTIE_ENTRANCE_SAY_2   = 1, // Auntie Stormstout says: Oh, Zan! You remind me so much of your father.
    CHEN_ENTRANCE_SAY_2     = 1, // Chen Stormstout   says: Tell me, what has happened here?
    AUNTIE_ENTRANCE_SAY_3   = 2, // Auntie Stormstout says: It is certainly a nice day outside!
    CHEN_ENTRANCE_SAY_3     = 2, // Chen Stormstout   says: Where are the other Stormstouts? Why are hozen all over the brewery?
    AUNTIE_ENTRANCE_SAY_4   = 3, // Auntie Stormstout says: Have you seen the size of Esme's turnips?
    CHEN_ENTRANCE_SAY_4     = 3, // Chen Stormstout   says: Auntie Stormstout... why is the brewery abandoned?
    AUNTIE_ENTRANCE_SAY_5   = 4, // Auntie Stormstout says: Abandoned? Oh heavens no! Uncle Gao is in charge while the others are beyond the wall. Isn't that exciting?
    CHEN_ENTRANCE_SAY_5     = 4, // Chen Stormstout   says: I see - and where is Uncle Gao?
    AUNTIE_ENTRANCE_SAY_6   = 5, // Auntie Stormstout says: I have some cookies for you!
    CHEN_ENTRANCE_SAY_6     = 5, // Chen Stormstout   says: There is no time for cookies! Well, one cookie. Just one.
    CHEN_ENTRANCE_SAY_7     = 6  // Chen Stormstout   says: Wait - these are ghost cookies. These aren't filling at all!
};

// Hozen Bouncer yells.
enum BouncerYells
{
    SAY_OOK_KILLED          = 0, // You take down Ook-Ook...
    SAY_MEANS               = 1, // You know what dat mean...
    SAY_NEW_OOK             = 2, // You da new Ook!
    SAY_PARTY               = 3  // Get da party started for da new Ook!
};

// Ancestral Brewmaster yells.
enum AncestralBrewmasterYells
{
    SAY_ABM_HOPTALLUS_1     = 0, // Whatzit... are they... what are they doin' to our alementals?
    SAY_ABM_HOPTALLUS_2     = 0, // Hey... hey YOU! Those are OUR flying... beer monsters?
};

#define ANN_ILLUSION "Removing the spirit's illusion damages the hozen's fragile mind!"

enum Spells
{
    // FRIENDLY
    SPELL_AUNTIE_VISUAL     = 115618, // Auntie Stormstout visual.
    SPELL_GUSHING_BREW_BVIS = 114379, // Gushing Brew beam visual (The Great Wheel).
    SPELL_GUSHING_BREW_A    = 114380, // Gushing Brew aura (NPC that has beam cast on).
    SPELL_LEAKING_BEER_B_A  = 146604, // Dummy for NPC on Keg.
    SPELL_BEER_PUDDLE_VIS   = 112960, // Beer on ground visual.

    // HOSTILE

    // Aqua Dancer - Once killed, their deaths will damage the Sodden Hozen Brawlers for half their health.
    SPELL_AQUATIC_ILLUSION  = 107044, // Gives Sodden Hozen Brawler SPELL_WATER_STRIKE.
    SPELL_AQUAT_ILLUSION_R  = 114655, // Removal damage.

    // Fiery Trickster - Once killed, their deaths will damage the Inflamed Hozen Brawlers for half their health.
    SPELL_FIERY_ILLUSION    = 107175, // Gives Inflamed Hozen Brawler SPELL_FIRE_STRIKE.
    SPELL_FIERY_ILLUSION_R  = 114656, // Removal damage.

    // Sodded Hozen Brawler
    SPELL_WATER_STRIKE      = 107046,

    // Inflamed Hozen Brawler
    SPELL_FIRE_STRIKE       = 107176,

    // Hozen Bouncer - 2 bouncers only, after Ook-Ook. After yells they run, crash into each other, die.
    SPELL_HOZEN_DOORGUARD   = 107019,
    SPELL_DANCE_PARTY_ANIM  = 128271,

    // Sleepy Hozen Brawler, Drunken Hozen Brawler.
    SPELL_COSMETIC_SLEEP    = 124557, // Used by Sleepy.
    SPELL_UPPERCUT          = 80182,

    // Habanero Brew
    SPELL_PROC_EXPLOSION    = 106787,
    SPELL_SPICY_EXPLOSION   = 107205,

    SPELL_BREW_BARREL_EXPL  = 107351, // Barrel monkey explosion.

    // Stout Brew Alemental
    SPELL_BREW_BOLT         = 115652,
    SPELL_BLACKOUT_BREW     = 106851,
    SPELL_BLACKOUT_DRUNK    = 106857, // At 10 stacks of SPELL_BLACKOUT_BREW.

    // Sudsy Brew Alemental
    SPELL_BREW_BOLT2        = 115650,
    SPELL_SUDS              = 116178, // Creates NPC_POOL_OF_SUDS at target location.
    AURA_SUDS               = 116179, // Periodic dmg trigger aura.
    SPELL_SUDS_DUMMY_VIS    = 119418, // Tooltip: "Can summon puddles of suds."

    // Unruly Alemental
    SPELL_BREW_BOLT3        = 118104,
    SPELL_BREWHAHA          = 118099,

    // Bubbling Brew Alemental
    SPELL_BREW_BOLT4        = 116155,
    SPELL_BUBBLE_SHIELD     = 128708,

    // Fizzy Brew Alemental
    // Uses SPELL_BREW_BOLT2.
    SPELL_CARBONATION_M     = 116162, // Missile.
    SPELL_CARBONATION_S     = 116164, // Creates NPC_CARBONATION_POOL at target location.
    AURA_CARBONATION        = 116168, // Periodic dmg trigger aura.

    // Bloated Brew Alemental
    // Uses SPELL_BREW_BOLT.
    SPELL_BLOAT             = 106546,

    // Yeasty Brew Alemental
    // Uses SPELL_BREW_BOLT4.
    // Uses Ferment in boss script.

    //Golden Hopling for Achievement 6402 Ling-Ting's Herbal Journey
    SPELL_GOLDEN_VERMING_VISUAL = 116320,
    SPELL_GOLDEN_VERMING_CAUGHT = 115038,
    SPELL_LING_TING_HERBAL      = 115037, 
};

enum Events
{
    // Trash

    EVENT_UPPERCUT          = 1,
    EVENT_WATER_STRIKE,
    EVENT_FIRE_STRIKE,

    EVENT_BREW_BOLT,
    EVENT_BLACKOUT_BREW,
    EVENT_BREW_BOLT2,
    EVENT_SUDS,
    EVENT_BREW_BOLT3,
    EVENT_CARBONATION,
    EVENT_BLOAT,
    EVENT_BUBBLE_SHIELD,
    EVENT_BREW_BOLT4,

    // Hozen Bouncer
    EVENT_SAY_OOK_KILLED,
    EVENT_BOUNCER_CHECK_PLAYERS,
    EVENT_RUN_AND_CRASH,

    // Chen Stormstout / Auntie Stormstout intro event
    EVENT_AUNTIE_ENTRANCE_SAY_1,
    EVENT_CHEN_ENTRANCE_SAY_1,
    EVENT_AUNTIE_ENTRANCE_SAY_2,
    EVENT_CHEN_ENTRANCE_SAY_2,
    EVENT_AUNTIE_ENTRANCE_SAY_3,
    EVENT_CHEN_ENTRANCE_SAY_3,
    EVENT_AUNTIE_ENTRANCE_SAY_4,
    EVENT_CHEN_ENTRANCE_SAY_4,
    EVENT_AUNTIE_ENTRANCE_SAY_5,
    EVENT_CHEN_ENTRANCE_SAY_5,
    EVENT_AUNTIE_ENTRANCE_SAY_6,
    EVENT_CHEN_ENTRANCE_SAY_6,
    EVENT_CHEN_ENTRANCE_SAY_7,

    // Ancestral Brewmaster
    EVENT_SPEAK_HOPTALLUS_1,
    EVENT_SPEAK_HOPTALLUS_2,
    EVENT_SPEAK_RANDOM
};

enum Actions
{
    ACTION_START_INTRO      = 0, // Chen Stormstout intro start.
};

enum Datas
{
    DATA_IS_IN_COMBAT = 1
};


enum Equip
{
    EQUIP_PARTY_HOZEN = 80580,
    EQUIP_DRUNKEN_HOZEN = 37924
};

const Position PartyPos[10] =
{
    { -758.984f, 1319.69f, 146.713f, 1.75602f }, 
    { -753.338f, 1343.89f, 146.805f, 1.87639f }, 
    { -751.726f, 1335.13f, 146.725f, 1.84827f }, 
    { -741.608f, 1344.25f, 146.767f, 1.74814f }, 
    { -754.252f, 1310.81f, 146.707f, 1.76277f },
    { -762.189f, 1332.24f, 146.723f, 1.85727f },
    { -738.114f, 1329.45f, 146.716f, 1.81677f },
    { -736.851f, 1316.96f, 146.708f, 1.86402f },
    { -744.831f, 1312.80f, 146.700f, 1.78123f }
};

uint8 goldenHoplingCount;

// Instance Scripted events and dialogues.

// Set adds with p_Entry around p_Creature in combat in p_Dist radius. If p_Entry omitted, entries with same entry as p_Creature will EnterCombat
void SetOtherAddsInCombat(Creature* p_Creature, Unit* p_Target, uint32 p_Entry = 0, float p_Dist = 10.0f)
{
    if (!p_Creature || !p_Target || p_Target->GetTypeId() != TYPEID_PLAYER)
        return;

    p_Creature->AI()->AttackStart(p_Target);
    p_Creature->SetInCombatWith(p_Target);

    std::list<Creature*> l_CreatureList;
    GetCreatureListWithEntryInGrid(l_CreatureList, p_Creature, p_Entry ? p_Entry : p_Creature->GetEntry(), p_Dist);

    if (l_CreatureList.empty())
        return;

    for (Creature* l_Creature : l_CreatureList)
    {
        if (l_Creature != p_Creature && !l_Creature->AI()->GetData(DATA_IS_IN_COMBAT))
            l_Creature->AI()->EnterCombat(p_Target);

        l_Creature->AI()->AttackStart(p_Target);
        l_Creature->SetInCombatWith(p_Target);
    }
}

class at_stormstout_brewery_entrance : public AreaTriggerScript
{
    public:
        at_stormstout_brewery_entrance() : AreaTriggerScript("at_stormstout_brewery_entrance") { }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
        {
            if (!player)
                return true;

            InstanceScript* instance = player->GetInstanceScript();
            if (!instance)
                return true;

            if (instance->GetData(DATA_HOZEN_KILLED) < HOZEN_KILLS_NEEDED && instance->GetData(DATA_OOK_SUMMONED) == false && instance->GetData(DATA_OOKOOK_EVENT) != DONE)
            {
                // Add the Hozen Counter aura.
                if (player->GetGroup())
                {
                    for (GroupReference* itr = player->GetGroup()->GetFirstMember(); itr != NULL; itr = itr->next())
                    {
                        if (Player* member = itr->getSource())
                        {
                            if (!member->HasAura(SPELL_BANANA_BAR))
                            {
                                member->AddAura(SPELL_BANANA_BAR, member);
                                member->SetPower(POWER_ALTERNATE_POWER, instance->GetData(DATA_HOZEN_KILLED));
                            }
                        }
                    }
                }
                else
                {
                    player->AddAura(SPELL_BANANA_BAR, player);
                    player->SetPower(POWER_ALTERNATE_POWER, instance->GetData(DATA_HOZEN_KILLED));
                }

                // Make the intro event start, once.
                if (Creature* auntieStormstout = player->FindNearestCreature(NPC_AUNTIE_STORMSTOUT, 100.0f, true))
                {
                    if (!auntieStormstout->HasAura(SPELL_AUNTIE_VISUAL))
                    {
                        auntieStormstout->AddAura(SPELL_AUNTIE_VISUAL, auntieStormstout);
                        if (Creature* chenStormstout = player->FindNearestCreature(NPC_CHEN_STORMSTOUT_ENTRANCE, 100.0f, true))
                            chenStormstout->AI()->DoAction(ACTION_START_INTRO);
                    }
                }
            }

            return true;
        }
};

// Chen Stormstout entrance 59704.
class npc_chen_stormstout_entrance : public CreatureScript
{
    public :
        npc_chen_stormstout_entrance() : CreatureScript("npc_chen_stormstout_entrance") { }

        struct npc_chen_stormstout_entrance_AI : public ScriptedAI
        {
            npc_chen_stormstout_entrance_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;
            Creature* auntieStormstout;
            bool introStarted;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                auntieStormstout = NULL;
                introStarted = false;
            }

            void DoAction(int32 const action)
            {
                if (action == ACTION_START_INTRO && introStarted)
                    return;

                switch (action)
                {
                    case ACTION_START_INTRO:
                        if (Creature* auntie = me->FindNearestCreature(NPC_AUNTIE_STORMSTOUT, 100.0f, true))
                            auntieStormstout = auntie;
                        goldenHoplingCount = 0;
                        introStarted = true;
                        events.ScheduleEvent(EVENT_AUNTIE_ENTRANCE_SAY_1, 1000);
                        break;

                    default: break;
                }
            };

            void UpdateAI(const uint32 diff)
            {
                events.Update(diff);

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_AUNTIE_ENTRANCE_SAY_1:
                            auntieStormstout->AI()->Talk(AUNTIE_ENTRANCE_SAY_1);
                            auntieStormstout->HandleEmote(EMOTE_ONESHOT_TALK);
                            events.ScheduleEvent(EVENT_CHEN_ENTRANCE_SAY_1, 8000);
                            break;

                        case EVENT_CHEN_ENTRANCE_SAY_1:
                            Talk(CHEN_ENTRANCE_SAY_1);
                            me->HandleEmote(EMOTE_ONESHOT_EXCLAMATION);
                            events.ScheduleEvent(EVENT_AUNTIE_ENTRANCE_SAY_2, 5000);
                            break;

                        case EVENT_AUNTIE_ENTRANCE_SAY_2:
                            auntieStormstout->AI()->Talk(AUNTIE_ENTRANCE_SAY_2);
                            auntieStormstout->HandleEmote(EMOTE_ONESHOT_TALK);
                            events.ScheduleEvent(EVENT_CHEN_ENTRANCE_SAY_2, 6000);
                            break;

                        case EVENT_CHEN_ENTRANCE_SAY_2:
                            Talk(CHEN_ENTRANCE_SAY_2);
                            me->HandleEmote(EMOTE_ONESHOT_QUESTION);
                            events.ScheduleEvent(EVENT_AUNTIE_ENTRANCE_SAY_3, 5000);
                            break;

                        case EVENT_AUNTIE_ENTRANCE_SAY_3:
                            auntieStormstout->AI()->Talk(AUNTIE_ENTRANCE_SAY_3);
                            auntieStormstout->HandleEmote(EMOTE_ONESHOT_EXCLAMATION);
                            events.ScheduleEvent(EVENT_CHEN_ENTRANCE_SAY_3, 5000);
                            break;

                        case EVENT_CHEN_ENTRANCE_SAY_3:
                            Talk(CHEN_ENTRANCE_SAY_3);
                            me->HandleEmote(EMOTE_ONESHOT_QUESTION);
                            events.ScheduleEvent(EVENT_AUNTIE_ENTRANCE_SAY_4, 9000);
                            break;

                        case EVENT_AUNTIE_ENTRANCE_SAY_4:
                            auntieStormstout->AI()->Talk(AUNTIE_ENTRANCE_SAY_4);
                            auntieStormstout->HandleEmote(EMOTE_ONESHOT_QUESTION);
                            events.ScheduleEvent(EVENT_CHEN_ENTRANCE_SAY_4, 5500);
                            break;

                        case EVENT_CHEN_ENTRANCE_SAY_4:
                            Talk(CHEN_ENTRANCE_SAY_4);
                            me->HandleEmote(EMOTE_ONESHOT_TALK);
                            events.ScheduleEvent(EVENT_AUNTIE_ENTRANCE_SAY_5, 6500);
                            break;

                        case EVENT_AUNTIE_ENTRANCE_SAY_5:
                            auntieStormstout->AI()->Talk(AUNTIE_ENTRANCE_SAY_5);
                            auntieStormstout->HandleEmote(EMOTE_ONESHOT_TALK);
                            events.ScheduleEvent(EVENT_CHEN_ENTRANCE_SAY_5, 11000);
                            break;

                        case EVENT_CHEN_ENTRANCE_SAY_5:
                            Talk(CHEN_ENTRANCE_SAY_5);
                            me->HandleEmote(EMOTE_ONESHOT_TALK);
                            events.ScheduleEvent(EVENT_AUNTIE_ENTRANCE_SAY_6, 4500);
                            break;

                        case EVENT_AUNTIE_ENTRANCE_SAY_6:
                            auntieStormstout->AI()->Talk(AUNTIE_ENTRANCE_SAY_6);
                            auntieStormstout->HandleEmote(EMOTE_ONESHOT_POINT);
                            events.ScheduleEvent(EVENT_CHEN_ENTRANCE_SAY_6, 4500);
                            break;

                        case EVENT_CHEN_ENTRANCE_SAY_6:
                            Talk(CHEN_ENTRANCE_SAY_6);
                            me->HandleEmote(EMOTE_ONESHOT_NO);
                            events.ScheduleEvent(EVENT_CHEN_ENTRANCE_SAY_7, 15000);
                            break;

                        case EVENT_CHEN_ENTRANCE_SAY_7:
                            Talk(CHEN_ENTRANCE_SAY_7);
                            me->HandleEmote(EMOTE_ONESHOT_EAT);
                            break;

                        default: break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_chen_stormstout_entrance_AI(creature);
        }
};

// Ancestral Brewmaster 59075.
class npc_ancestral_brewmaster : public CreatureScript
{
    public :
        npc_ancestral_brewmaster() : CreatureScript("npc_ancestral_brewmaster") { }

        struct npc_ancestral_brewmaster_AI : public ScriptedAI
        {
            npc_ancestral_brewmaster_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;
            bool said, alone, hasTwo, hasThree;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                me->SetReactState(REACT_PASSIVE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                said = false;
                hasTwo = me->FindNearestCreature(NPC_ANCESTRAL_BREWMASTER_2, 4.0f, true) ? true : false;
                hasThree = (hasTwo && me->FindNearestCreature(NPC_ANCESTRAL_BREWMASTER_3, 4.0f, true)) ? true : false;
                alone = (!hasTwo && !hasThree) ? true : false;
            }

            void UpdateAI(const uint32 diff)
            {
                // Check stuff for the Brewmasters after Hoptallus.
                if (!said && hasTwo && instance->GetData(DATA_HOPTALLUS_EVENT) == DONE)
                {
                    if (me->FindNearestPlayer(20.0f, true))
                    {
                        if (Creature* Alemental = me->FindNearestCreature(NPC_BLOATED_BREW_ALEMENTAL, 20.0f, true))
                        {
                            if (Alemental->isInCombat())
                            {
                                events.ScheduleEvent(EVENT_SPEAK_HOPTALLUS_1, 2000);
                                said = true;
                            }
                        }
                    }
                }

                events.Update(diff);

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_SPEAK_HOPTALLUS_1:
                            Talk(SAY_ABM_HOPTALLUS_1);
                            me->HandleEmote(EMOTE_ONESHOT_QUESTION);
                            events.ScheduleEvent(EVENT_SPEAK_HOPTALLUS_2, 8000);
                            break;

                        case EVENT_SPEAK_HOPTALLUS_2:
                            if (Creature* brewMaster2 = me->FindNearestCreature(NPC_ANCESTRAL_BREWMASTER_2, 5.0f, true))
                            {
                                brewMaster2->AI()->Talk(SAY_ABM_HOPTALLUS_2);
                                brewMaster2->HandleEmote(EMOTE_ONESHOT_EXCLAMATION);
					        }
                            break;

                        case EVENT_SPEAK_RANDOM:
                            break;

                        default: break;
                    }
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_ancestral_brewmaster_AI(creature);
        }
};

// Instance trash scripts.

// Sodden Hozen Brawler 59605.
class npc_sodden_hozen_brawler : public CreatureScript
{
    public :
        npc_sodden_hozen_brawler() : CreatureScript("npc_sodden_hozen_brawler") { }

        struct npc_sodden_hozen_brawler_AI : public ScriptedAI
        {
            npc_sodden_hozen_brawler_AI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                instance = creature->GetInstanceScript();
                summonedFirstHelper = false;
            }

            InstanceScript* instance;
            EventMap events;
            SummonList summons;
            bool summonedFirstHelper, helperDead, m_IsInCombat;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                summons.DespawnAll();
                helperDead = false;
                m_IsInCombat = false;
                me->SetReactState(REACT_DEFENSIVE);

                // Summon the "helper".
                if (!summonedFirstHelper)
                {
                    me->SummonCreature(NPC_AQUA_DANCER, me->GetPositionX(), me->GetPositionY() + 4.0f, me->GetPositionZ() + 8.0f, me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
                    summonedFirstHelper = true;
                }
            }

            void EnterCombat(Unit* p_Who)
            {
                if (!m_IsInCombat && p_Who->GetTypeId() == TYPEID_PLAYER)
                {
                    m_IsInCombat = true;
                    me->SetReactState(REACT_AGGRESSIVE);
                    SetOtherAddsInCombat(me, p_Who);
                }
            }

            uint32 GetData(uint32 p_Data)
            {
                if (p_Data == DATA_IS_IN_COMBAT)
                    return m_IsInCombat ? 1 : 0;
                return 0;
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void JustReachedHome()
            {
                if (helperDead)
                    me->SummonCreature(NPC_AQUA_DANCER, me->GetPositionX(), me->GetPositionY() + 4.0f, me->GetPositionZ() + 8.0f, me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
            }

            void JustDied(Unit* /*killer*/)
            {
                summons.DespawnAll();
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);

		        if (me->isInCombat())
                    summon->SetInCombatWithZone();

                if (summon->GetEntry() == NPC_AQUA_DANCER)
                {
                    summon->SetCanFly(true);
                    summon->SetDisableGravity(true);
                    summon->SetReactState(REACT_PASSIVE);
                    summon->CastSpell(me, SPELL_AQUATIC_ILLUSION, false);
                }
            }

            void SummonedCreatureDies(Creature* summon, Unit* /*killer*/)
            {
                summons.Despawn(summon);
                me->RemoveAurasDueToSpell(SPELL_AQUATIC_ILLUSION);
                DoCast(me, SPELL_AQUAT_ILLUSION_R);
                me->MonsterTextEmote(ANN_ILLUSION, NULL, true);
                helperDead = true;
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_sodden_hozen_brawler_AI(creature);
        }
};

// Inflamed Hozen Brawler 56924.
class npc_inflamed_hozen_brawler : public CreatureScript
{
    public :
        npc_inflamed_hozen_brawler() : CreatureScript("npc_inflamed_hozen_brawler") { }

        struct npc_inflamed_hozen_brawler_AI : public ScriptedAI
        {
            npc_inflamed_hozen_brawler_AI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                instance = creature->GetInstanceScript();
                summonedFirstHelper = false;
            }

            InstanceScript* instance;
            EventMap events;
            SummonList summons;
            bool summonedFirstHelper, helperDead, m_IsInCombat;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                summons.DespawnAll();
                helperDead = false;
                m_IsInCombat = false;

                // Summon the "helper".
                if (!summonedFirstHelper)
                {
                    me->SummonCreature(NPC_FIERY_TRICKSTER, me->GetPositionX(), me->GetPositionY() + 4.0f, me->GetPositionZ() + 8.0f, me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
                    summonedFirstHelper = true;
                }
                me->SetReactState(REACT_DEFENSIVE);
            }

            void EnterCombat(Unit* who) 
            { 
                if (!m_IsInCombat && who->GetTypeId() == TYPEID_PLAYER)
                {
                    m_IsInCombat = true;
                    me->SetReactState(REACT_AGGRESSIVE);
                    SetOtherAddsInCombat(me, who);
                }
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            uint32 GetData(uint32 p_Data)
            {
                if (p_Data == DATA_IS_IN_COMBAT)
                    return m_IsInCombat ? 1 : 0;
                return 0;
            }

            void JustReachedHome()
            {
                if (helperDead)
                    me->SummonCreature(NPC_FIERY_TRICKSTER, me->GetPositionX(), me->GetPositionY() + 4.0f, me->GetPositionZ() + 8.0f, me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN);
            }

            void JustDied(Unit* /*killer*/)
            {
                summons.DespawnAll();
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);

		        if (me->isInCombat())
                    summon->SetInCombatWithZone();

                if (summon->GetEntry() == NPC_FIERY_TRICKSTER)
                {
                    summon->SetCanFly(true);
                    summon->SetDisableGravity(true);
                    summon->SetReactState(REACT_PASSIVE);
                    summon->CastSpell(me, SPELL_FIERY_ILLUSION, false);
                }
            }

            void SummonedCreatureDies(Creature* summon, Unit* /*killer*/)
            {
                summons.Despawn(summon);
                me->RemoveAurasDueToSpell(SPELL_FIERY_ILLUSION);
                DoCast(me, SPELL_FIERY_ILLUSION_R);
                me->MonsterTextEmote(ANN_ILLUSION, NULL, true);
                helperDead = true;
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_inflamed_hozen_brawler_AI(creature);
        }
};

// Hozen Bouncer 56849.
class npc_hozen_bouncer : public CreatureScript
{
public:
    npc_hozen_bouncer() : CreatureScript("npc_hozen_bouncer") { }

    struct npc_hozen_bouncer_AI : public ScriptedAI
    {
        npc_hozen_bouncer_AI(Creature* creature) : ScriptedAI(creature)
        {
            m_Instance = creature->GetInstanceScript();
        }

        InstanceScript* m_Instance;
        EventMap events;
        bool m_IsInCombat;
        bool summoned;
        uint8 l_SayCount;

        void Reset()
        {
            events.Reset();
            m_IsInCombat = false;
            summoned = false;

            if (m_Instance)
            if (m_Instance->GetData(DATA_OOKOOK_EVENT) != DONE)
                m_IsInCombat = true;

            me->SetReactState(REACT_PASSIVE);
            l_SayCount = 0;

            if (m_IsInCombat)
                events.ScheduleEvent(EVENT_BOUNCER_CHECK_PLAYERS, 300);
        }

        void DoAction(int32 const p_Action)
        {
            switch (p_Action)
            {
            case ACTION_OOK_OOK_TALK:
            {
                 events.ScheduleEvent(EVENT_SAY_OOK_KILLED, 2000);
                 break;
            }
            case ACTION_OOK_OOK_DEAD:
            {
                 m_IsInCombat = false;
                 me->SetReactState(REACT_PASSIVE);
                 me->RemoveAura(SPELL_HOZEN_DOORGUARD);
                 events.ScheduleEvent(EVENT_RUN_AND_CRASH, 18000);
                 break;
            }
            default:
                break;
            }
        }

        void EnterEvadeMode()
        {
            if (m_Instance)
            if (m_Instance->GetData(DATA_OOKOOK_EVENT) != DONE)
                m_IsInCombat = true;

            if (m_IsInCombat)
                events.ScheduleEvent(EVENT_BOUNCER_CHECK_PLAYERS, 300);

            me->GetMotionMaster()->MoveTargetedHome();
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (!me->isAlive() || type != POINT_MOTION_TYPE || id != 1)
                return;

            me->CastSpell(me, SPELL_DANCE_PARTY_ANIM, true);
        }

        void UpdateAI(const uint32 diff)
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_BOUNCER_CHECK_PLAYERS:
                    if (me->FindNearestPlayer(10.0) && m_IsInCombat)
                    {
                        if (!me->HasAura(SPELL_HOZEN_DOORGUARD))
                            me->CastSpell(me, SPELL_HOZEN_DOORGUARD, true);
                    }
                    else
                        me->RemoveAura(SPELL_HOZEN_DOORGUARD);
                    events.ScheduleEvent(EVENT_BOUNCER_CHECK_PLAYERS, 300);
                    break;
                case EVENT_SAY_OOK_KILLED:
                    Talk(SAY_OOK_KILLED + l_SayCount++);

                    if (!summoned)
                    {
                        summoned = true;
                        for (uint32 i = 0; i < 10; ++i)
                            me->SummonCreature(NPC_HOZEN_PARTY_ANIMAL, PartyPos[i], TEMPSUMMON_MANUAL_DESPAWN);
                        std::list<Creature*> l_AddList;
                        GetCreatureListWithEntryInGrid(l_AddList, me, NPC_HOZEN_PARTY_ANIMAL, 100.0f);
                        if (!l_AddList.empty())
                        for (std::list<Creature*>::iterator iter = l_AddList.begin(); iter != l_AddList.end(); ++iter)
                            (*iter)->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                    }

                    if (l_SayCount < 3)
                        events.ScheduleEvent(EVENT_SAY_OOK_KILLED, 4000);
                    break;
                case EVENT_RUN_AND_CRASH:
                    me->GetMotionMaster()->MovePoint(1, -747.929f, 1323.334f, 146.715f);
                    break;
                
                default:
                    break;
                }
            }

            if (m_IsInCombat)
                DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_hozen_bouncer_AI(creature);
    }
};

// Sleepy Hozen Brawler 56863, Drunken Hozen Brawler 56862.
class npc_drunken_sleepy_hozen_brawler : public CreatureScript
{
    public :
        npc_drunken_sleepy_hozen_brawler() : CreatureScript("npc_drunken_sleepy_hozen_brawler") { }

        struct npc_drunken_sleepy_hozen_brawler_AI : public ScriptedAI
        {
            npc_drunken_sleepy_hozen_brawler_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;
            bool m_IsInCombat;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                me->SetReactState(REACT_DEFENSIVE);

                m_IsInCombat = false;
                // Add Sleep cosmetic to the Sleepy Hozen Brawlers.
                if (me->GetEntry() == NPC_SLEEPY_HOZEN_BRAWLER && !me->HasAura(SPELL_COSMETIC_SLEEP))
                    me->AddAura(SPELL_COSMETIC_SLEEP, me);
                // Add weapon & fighting visual for Drunken Hozen Brawlers.
                else
                {
                    SetEquipmentSlots(false, EQUIP_DRUNKEN_HOZEN, 0, 0);
                    events.ScheduleEvent(EVENT_UPPERCUT, 2000);
                }
            }

            void DamageTaken(Unit* /*p_Attacker*/, uint32& /*p_Damage*/)
            {
                if (m_IsInCombat)
                    return;
            }

            void EnterCombat(Unit* who)
            {
                if (me->GetEntry() == NPC_SLEEPY_HOZEN_BRAWLER)
                {
                    // Remove Sleep cosmetic from the Sleepy Hozen Brawlers.
                    me->RemoveAurasDueToSpell(SPELL_COSMETIC_SLEEP);

                    // Check the Habanero Brew barrels.
                    if (Creature* habanero = me->FindNearestCreature(NPC_HABANERO_BREW, 10.0f))
                        habanero->CastSpell(habanero, SPELL_SPICY_EXPLOSION, false);
                }
                // Drunken Hozen
                else if (!m_IsInCombat && who->GetTypeId() == TYPEID_PLAYER)
                {
                    m_IsInCombat = true;
                    me->SetReactState(REACT_AGGRESSIVE);
                    SetOtherAddsInCombat(me, who);
                    SetOtherAddsInCombat(me, who, NPC_HOZEN_PARTY_ANIMAL);
                }
            }

            uint32 GetData(uint32 p_Data)
            {
                if (p_Data == DATA_IS_IN_COMBAT)
                    return m_IsInCombat ? 1 : 0;
                return 0;
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void JustReachedHome()
            {
                // Add Sleep cosmetic to the Sleepy Hozen Brawlers.
                if (me->GetEntry() == NPC_SLEEPY_HOZEN_BRAWLER && !me->HasAura(SPELL_COSMETIC_SLEEP))
                    me->AddAura(SPELL_COSMETIC_SLEEP, me);
                else
                    me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_ONESHOT_ATTACK1H);
            }

            void UpdateAI(const uint32 diff)
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
                        case EVENT_UPPERCUT:
                        {
                            if (!m_IsInCombat)
                            {
                                std::list<Creature*> l_HozenList;
                                GetCreatureListWithEntryInGrid(l_HozenList, me, NPC_DRUNKEN_HOZEN_BRAWLER, 5.0f);
                                for (Creature* l_Hozen : l_HozenList)
                                {
                                    if (l_Hozen == me)
                                        continue;

                                    me->CastSpell(l_Hozen, SPELL_UPPERCUT, true);
                                }

                                events.ScheduleEvent(EVENT_UPPERCUT, 2000);
                            }

                            break;
                        }
                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_drunken_sleepy_hozen_brawler_AI(creature);
        }
};

// 59684 - 56927 - Hozen Party Animal
class npc_hozen_party_animal : public CreatureScript
{
public:
    npc_hozen_party_animal() : CreatureScript("npc_hozen_party_animal") { }

    struct npc_hozen_party_animalAI : public ScriptedAI
    {
        npc_hozen_party_animalAI(Creature* p_Creature) : ScriptedAI(p_Creature) { }

        bool m_IsInCombat;

        void Reset()
        {
            m_IsInCombat = false;
            me->SetReactState(REACT_DEFENSIVE);
            SetEquipmentSlots(false, EQUIP_PARTY_HOZEN, 0, 0);
        }

        void EnterCombat(Unit* p_Attacker)
        {
            if (!m_IsInCombat && p_Attacker->GetTypeId() == TYPEID_PLAYER)
            {
                m_IsInCombat = true;
                me->SetReactState(REACT_AGGRESSIVE);
                SetOtherAddsInCombat(me, p_Attacker);
            }
        }

        uint32 GetData(uint32 p_Data)
        {
            if (p_Data == DATA_IS_IN_COMBAT)
                return m_IsInCombat ? 1 : 0;
            return 0;
        }

        void EnterEvadeMode()
        {
            Reset();
            me->GetMotionMaster()->MoveTargetedHome();
        }

        void MovementInform(uint32 p_Type, uint32 p_Id)
        {
            if (p_Type != POINT_MOTION_TYPE || p_Id != 2)
                return;

            me->DespawnOrUnsummon();
        }
    };

    CreatureAI* GetAI(Creature* p_Creature) const
    {
        return new npc_hozen_party_animalAI(p_Creature);
    }
};


// Stout Brew Alemental 59519.
class npc_stout_brew_alemental : public CreatureScript
{
    public :
        npc_stout_brew_alemental() : CreatureScript("npc_stout_brew_alemental") { }

        struct npc_stout_brew_alemental_AI : public ScriptedAI
        {
            npc_stout_brew_alemental_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BREW_BOLT, urand(2000, 6000));
                events.ScheduleEvent(EVENT_BLACKOUT_BREW, urand(12000, 17000));
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void UpdateAI(const uint32 diff)
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
                        case EVENT_BREW_BOLT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BREW_BOLT);
                            events.ScheduleEvent(EVENT_BREW_BOLT, urand(7000, 11000));
                            break;

                        case EVENT_BLACKOUT_BREW:
                            DoCast(me, SPELL_BLACKOUT_BREW);
                            events.ScheduleEvent(EVENT_BLACKOUT_BREW, urand(18000, 23000));
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_stout_brew_alemental_AI(creature);
        }
};

// Sudsy Brew Alemental 59522.
class npc_sudsy_brew_alemental : public CreatureScript
{
    public :
        npc_sudsy_brew_alemental() : CreatureScript("npc_sudsy_brew_alemental") { }

        struct npc_sudsy_brew_alemental_AI : public ScriptedAI
        {
            npc_sudsy_brew_alemental_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                me->AddAura(SPELL_SUDS_DUMMY_VIS, me);
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BREW_BOLT2, urand(2000, 6000));
                events.ScheduleEvent(EVENT_SUDS, urand(9000, 12000));
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void UpdateAI(const uint32 diff)
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
                        case EVENT_BREW_BOLT2:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BREW_BOLT2);
                            events.ScheduleEvent(EVENT_BREW_BOLT2, urand(7000, 11000));
                            break;

                        case EVENT_SUDS:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_SUDS);
                            events.ScheduleEvent(EVENT_SUDS, urand(18000, 22000));
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_sudsy_brew_alemental_AI(creature);
        }
};

// Pool of Suds 56748.
class npc_pool_of_suds : public CreatureScript
{
    public :
        npc_pool_of_suds() : CreatureScript("npc_pool_of_suds") { }

        struct npc_pool_of_suds_AI : public ScriptedAI
        {
            npc_pool_of_suds_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                Reset();
            }

            void Reset()
            {
                me->AddAura(AURA_SUDS, me);
                me->SetReactState(REACT_PASSIVE);
            }

            void UpdateAI(const uint32 diff) { } // No melee.
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_pool_of_suds_AI(creature);
        }
};

// Unruly Alemental 56684.
class npc_unruly_alemental : public CreatureScript
{
    public :
        npc_unruly_alemental() : CreatureScript("npc_unruly_alemental") { }

        struct npc_unruly_alemental_AI : public ScriptedAI
        {
            npc_unruly_alemental_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();

                if (!me->HasAura(SPELL_BREWHAHA))
                    me->AddAura(SPELL_BREWHAHA, me);
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BREW_BOLT3, urand(2000, 6000));
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void JustReachedHome()
            {
                if (!me->HasAura(SPELL_BREWHAHA))
                    me->AddAura(SPELL_BREWHAHA, me);
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
                        case EVENT_BREW_BOLT3:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BREW_BOLT3);
                            events.ScheduleEvent(EVENT_BREW_BOLT3, urand(7000, 11000));
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_unruly_alemental_AI(creature);
        }
};

// Fizzy Brew Alemental 59520.
class npc_fizzy_brew_alemental : public CreatureScript
{
    public :
        npc_fizzy_brew_alemental() : CreatureScript("npc_fizzy_brew_alemental") { }

        struct npc_fizzy_brew_alemental_AI : public ScriptedAI
        {
            npc_fizzy_brew_alemental_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BREW_BOLT2, urand(2000, 6000));
                events.ScheduleEvent(EVENT_CARBONATION, urand(9000, 12000));
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void UpdateAI(const uint32 diff)
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
                        case EVENT_BREW_BOLT2:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BREW_BOLT2);
                            events.ScheduleEvent(EVENT_BREW_BOLT2, urand(7000, 11000));
                            break;

                        case EVENT_CARBONATION:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_CARBONATION_M);
                            events.ScheduleEvent(EVENT_CARBONATION, urand(22000, 26000));
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_fizzy_brew_alemental_AI(creature);
        }
};

// Pool of Carbonation 56746.
class npc_pool_of_carbonation : public CreatureScript
{
    public :
        npc_pool_of_carbonation() : CreatureScript("npc_pool_of_carbonation") { }

        struct npc_pool_of_carbonation_AI : public ScriptedAI
        {
            npc_pool_of_carbonation_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;

            void IsSummonedBy(Unit* /*summoner*/)
            {
                Reset();
            }

            void Reset()
            {
                me->AddAura(AURA_CARBONATION, me);
                me->SetReactState(REACT_PASSIVE);
            }

            void UpdateAI(uint32 const diff) { } // No melee.
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_pool_of_carbonation_AI(creature);
        }
};

// Bloated Brew Alemental 59518.
class npc_bloated_brew_alemental : public CreatureScript
{
    public :
        npc_bloated_brew_alemental() : CreatureScript("npc_bloated_brew_alemental") { }

        struct npc_bloated_brew_alemental_AI : public ScriptedAI
        {
            npc_bloated_brew_alemental_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BREW_BOLT, urand(2000, 6000));
                events.ScheduleEvent(EVENT_BLOAT, urand(10000, 14000));
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void UpdateAI(const uint32 diff)
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
                        case EVENT_BREW_BOLT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BREW_BOLT);
                            events.ScheduleEvent(EVENT_BREW_BOLT, urand(7000, 11000));
                            break;

                        case EVENT_BLOAT:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BLOAT);
                            events.ScheduleEvent(EVENT_BLOAT, urand(32000, 37000));
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_bloated_brew_alemental_AI(creature);
        }
};

// Bubbling Brew Alemental 59521.
class npc_bubbling_brew_alemental : public CreatureScript
{
    public :
        npc_bubbling_brew_alemental() : CreatureScript("npc_bubbling_brew_alemental") { }

        struct npc_bubbling_brew_alemental_AI : public ScriptedAI
        {
            npc_bubbling_brew_alemental_AI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;
            SummonList summons;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
                summons.DespawnAll();
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BREW_BOLT4, urand(2000, 6000));
                events.ScheduleEvent(EVENT_BUBBLE_SHIELD, urand(9000, 17000));
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void JustDied(Unit* /*killer*/)
            {
                summons.DespawnAll();
            }

            void JustSummoned(Creature* summon)
            {
                summons.Summon(summon);
                summon->setActive(true);

		        if (me->isInCombat())
                    summon->SetInCombatWithZone();

                if (summon->GetEntry() == NPC_BUBBLE_SHIELD_TRASH)
                {
                    summon->SetReactState(REACT_PASSIVE);
                    summon->AddAura(SPELL_BUBBLE_SHIELD, me);
                }
            }

            void SummonedCreatureDies(Creature* summon, Unit* /*killer*/)
            {
                summons.Despawn(summon);

				if (AuraPtr aura = me->GetAura(SPELL_BUBBLE_SHIELD))
                {
                    if (aura->GetStackAmount() > 1)
                        me->SetAuraStack(SPELL_BUBBLE_SHIELD, me, aura->GetStackAmount() - 1);
                    else
                        me->RemoveAurasDueToSpell(SPELL_BUBBLE_SHIELD);
                }
            }

            void UpdateAI(const uint32 diff)
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
                        case EVENT_BREW_BOLT4:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BREW_BOLT4);
                            events.ScheduleEvent(EVENT_BREW_BOLT4, urand(7000, 11000));
                            break;

                        case EVENT_BUBBLE_SHIELD:
                            for (uint8 i = 0; i < 4; i++)
                                me->SummonCreature(NPC_BUBBLE_SHIELD_TRASH, me->GetPositionX() + frand(3.0f, -3.0f), me->GetPositionX() + frand(3.0f, -3.0f), me->GetPositionZ() + 0.1f, 0, TEMPSUMMON_MANUAL_DESPAWN);
                            events.ScheduleEvent(EVENT_BUBBLE_SHIELD, urand(42000, 54000));
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_bubbling_brew_alemental_AI(creature);
        }
};

// Yeasty Brew Alemental 59494.
class npc_yeasty_brew_alemental : public CreatureScript
{
    public :
        npc_yeasty_brew_alemental() : CreatureScript("npc_yeasty_brew_alemental") { }

        struct npc_yeasty_brew_alemental_AI : public ScriptedAI
        {
            npc_yeasty_brew_alemental_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                events.Reset();
            }

            void EnterCombat(Unit* /*who*/)
            {
                events.ScheduleEvent(EVENT_BREW_BOLT4, urand(2000, 6000));
            }

            void EnterEvadeMode()
            {
                Reset();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->MoveTargetedHome();
            }

            void UpdateAI(const uint32 diff)
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
                        case EVENT_BREW_BOLT4:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                                DoCast(target, SPELL_BREW_BOLT4);
                            events.ScheduleEvent(EVENT_BREW_BOLT4, urand(7000, 11000));
                            break;

                        default: break;
                    }
                }

                DoMeleeAttackIfReady();
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_yeasty_brew_alemental_AI(creature);
        }
};

// Leaking beer barrel 73186.
class npc_leaking_beer_barrel : public CreatureScript
{
    public :
        npc_leaking_beer_barrel() : CreatureScript("npc_leaking_beer_barrel") { }

        struct npc_leaking_beer_barrel_AI : public ScriptedAI
        {
            npc_leaking_beer_barrel_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                if (Creature* beerBunny = me->FindNearestCreature(NPC_BEER_BARREL_BUNNY, 15.0f, true))
                    DoCast(beerBunny, SPELL_GUSHING_BREW_BVIS);
            }

            void UpdateAI(const uint32 diff) { }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_leaking_beer_barrel_AI(creature);
        }
};

// Beer barrel bunny 66215.
class npc_beer_barrel_bunny : public CreatureScript
{
    public :
        npc_beer_barrel_bunny() : CreatureScript("npc_beer_barrel_bunny") { }

        struct npc_beer_barrel_bunny_AI : public ScriptedAI
        {
            npc_beer_barrel_bunny_AI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
            }

            InstanceScript* instance;

            void InitializeAI()
            {
                if (!me->isDead())
                    Reset();
            }

            void Reset()
            {
                me->AddAura(SPELL_GUSHING_BREW_A, me);
            }

            void UpdateAI(const uint32 diff) { }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_beer_barrel_bunny_AI(creature);
        }
};

// Golden Hopling 59824.
class npc_golden_hopling : public CreatureScript
{
public:
    npc_golden_hopling() : CreatureScript("npc_golden_hopling") { }

    struct npc_golden_hoplingAI : public PassiveAI
    {
        npc_golden_hoplingAI(Creature* creature) : PassiveAI(creature)
        {
            instance = creature->GetInstanceScript();
        }

        InstanceScript* instance;
        EventMap events;

        void Reset()
        {
            me->AddAura(SPELL_GOLDEN_VERMING_VISUAL, me);
            me->SetReactState(REACT_PASSIVE);
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
            me->SetVisible(false);
        }

        void OnSpellClick(Unit* clicker)
        {
            me->CastSpell(me, SPELL_GOLDEN_VERMING_CAUGHT, false);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
            if (++goldenHoplingCount >= 30 && instance)
                instance->DoCompleteAchievement(6402); //Achievement 6402 Ling-Ting's Herbal Journey
            me->DespawnOrUnsummon();
        }

        void UpdateAI(const uint32 diff)
        {
            if (Player* player = me->FindNearestPlayer(25.0f, true))
            if (player->HasAura(SPELL_LING_TING_HERBAL))
                me->SetVisible(true);
            else
                me->SetVisible(false);

            events.Update(diff);
        }

    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_golden_hoplingAI(creature);
    }
};

// Spicy Explosion 107205, triggered by SPELL_PROC_EXPLOSION.
class spell_stormstout_brewery_habanero_beer : public SpellScriptLoader
{
    public:
        spell_stormstout_brewery_habanero_beer() : SpellScriptLoader("spell_stormstout_brewery_habanero_beer") { }

        class spell_stormstout_brewery_habanero_beer_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_stormstout_brewery_habanero_beer_SpellScript);

            void HandleInstaKill(SpellEffIndex /*effIndex*/)
            {
                if (!GetCaster())
                    return;

                std::list<Creature*> creatureList;
                GetCreatureListWithEntryInGrid(creatureList, GetCaster(), NPC_HABANERO_BREW, 10.0f);

                GetCaster()->RemoveAurasDueToSpell(SPELL_PROC_EXPLOSION);

                for (std::list<Creature*>::iterator barrel = creatureList.begin(); barrel != creatureList.end(); barrel++)
                {
                    if ((*barrel)->HasAura(SPELL_PROC_EXPLOSION))
                    {
                        (*barrel)->RemoveAurasDueToSpell(SPELL_PROC_EXPLOSION);
                        (*barrel)->CastSpell(*barrel, SPELL_SPICY_EXPLOSION, true);
                    }
                }
            }

            void HandleAfterCast()
            {
                if (Unit* caster = GetCaster())
                    if (caster->ToCreature())
                        caster->ToCreature()->DespawnOrUnsummon(1000);
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_stormstout_brewery_habanero_beer_SpellScript::HandleInstaKill, EFFECT_1, SPELL_EFFECT_INSTAKILL);
                AfterCast += SpellCastFn(spell_stormstout_brewery_habanero_beer_SpellScript::HandleAfterCast);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_stormstout_brewery_habanero_beer_SpellScript();
        }
};

/// Dance Party Animkit - 128271
class spell_stormstout_brewery_dance_party_animkit : public SpellScriptLoader
{
public:
    spell_stormstout_brewery_dance_party_animkit() : SpellScriptLoader("spell_stormstout_brewery_dance_party_animkit") { }

    class spell_stormstout_brewery_dance_party_animkit_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_stormstout_brewery_dance_party_animkit_SpellScript);

        void CorrectTargets(std::list<WorldObject*>& p_Targets)
        {
            if (p_Targets.empty())
                return;

            p_Targets.remove_if([this](WorldObject* p_Object) -> bool
            {
                if (p_Object == nullptr || p_Object->GetTypeId() == TypeID::TYPEID_PLAYER)
                    return true;

                return false;
            });
        }

        void Register() override
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_stormstout_brewery_dance_party_animkit_SpellScript::CorrectTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_stormstout_brewery_dance_party_animkit_SpellScript();
    }
};

class CheckGuardTarget
{
public:
    bool operator()(WorldObject* target) const
    {
        if (target->ToCreature())
        {
            if (target->GetEntry() == BOSS_OOKOOK)
                return true;
            if (target->GetEntry() == NPC_HOZEN_BOUNCER)
                return true;
            if (target->GetEntry() == NPC_OOK_BARREL)
                return true;            
        }

        if (Player* player = target->ToPlayer())
        {
            if (player->IsFalling())
                return true;
        }
        return false;
    }
};

// 114809 Doorguard
class spell_hozen_bouncer_doorguard : public SpellScriptLoader
{
public:
    spell_hozen_bouncer_doorguard() : SpellScriptLoader("spell_hozen_bouncer_doorguard") { }

    class spell_hozen_bouncer_doorguard_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_hozen_bouncer_doorguard_SpellScript);

        void FilterTargets(std::list<WorldObject*>& targets)
        {
            targets.remove_if(CheckGuardTarget());
        }

        void Register()
        {
            OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_hozen_bouncer_doorguard_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_hozen_bouncer_doorguard_SpellScript();
    }
};

void AddSC_stormstout_brewery()
{
    new at_stormstout_brewery_entrance();
    new npc_chen_stormstout_entrance();
    new npc_ancestral_brewmaster();
    new npc_sodden_hozen_brawler();
    new npc_inflamed_hozen_brawler();
    new npc_hozen_bouncer();
    new npc_drunken_sleepy_hozen_brawler();
    new npc_stout_brew_alemental();
    new npc_sudsy_brew_alemental();
    new npc_pool_of_suds();
    new npc_unruly_alemental();
    new npc_fizzy_brew_alemental();
    new npc_pool_of_carbonation();
    new npc_bloated_brew_alemental();
    new npc_bubbling_brew_alemental();
    new npc_yeasty_brew_alemental();
    new npc_leaking_beer_barrel();
    new npc_beer_barrel_bunny();
    new npc_golden_hopling();
    new spell_stormstout_brewery_habanero_beer();
    new spell_stormstout_brewery_dance_party_animkit(); ///< 128271
    new spell_hozen_bouncer_doorguard();
}
