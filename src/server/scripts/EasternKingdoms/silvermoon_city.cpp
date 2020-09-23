/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2006-2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/* ScriptData
SDName: Silvermoon_City
SD%Complete: 100
SDComment: Quest support: 9685
SDCategory: Silvermoon City
EndScriptData */

/* ContentData
npc_blood_knight_stillblade
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum eStillbladeData
{
    SAY_HEAL                    = -1000193,

    QUEST_REDEEMING_THE_DEAD    = 9685,
    SPELL_SHIMMERING_VESSEL     = 31225,
    SPELL_REVIVE_SELF           = 32343,
};

enum LorthemarTheron
{
    SPELL_ARCANE_SHOCK  = 59715,
    SPELL_CLEAVE        = 15284,
    SPELL_MANA_BURN     = 33385,
    SPELL_MASS_CHARM    = 33384,
};

enum KingEvents
{
    EVENT_ARCANE_SHOCK = 1,
    EVENT_CLEAVE       = 2,
    EVENT_MANA_BURN    = 3,
    EVENT_MASS_CHARM   = 4,
};

/*#######
# npc_blood_knight_stillblade
#######*/

class npc_blood_knight_stillblade : public CreatureScript
{
public:
    npc_blood_knight_stillblade() : CreatureScript("npc_blood_knight_stillblade") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_blood_knight_stillbladeAI (creature);
    }

    struct npc_blood_knight_stillbladeAI : public ScriptedAI
    {
        npc_blood_knight_stillbladeAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 lifeTimer;
        bool spellHit;

        void Reset()
        {
            lifeTimer = 120000;
            me->SetStandState(UNIT_STAND_STATE_DEAD);
            me->SetUInt32Value(UNIT_FIELD_BYTES_1, 7);   // lay down
            spellHit = false;
        }

        void EnterCombat(Unit* /*who*/)
        {
        }

        void MoveInLineOfSight(Unit* /*who*/)
        {
        }

        void UpdateAI(const uint32 diff)
        {
            if (me->IsStandState())
            {
                if (lifeTimer <= diff)
                    me->AI()->EnterEvadeMode();
                else
                    lifeTimer -= diff;
            }
        }

        void SpellHit(Unit* Hitter, const SpellInfo* Spellkind)
        {
            if ((Spellkind->Id == SPELL_SHIMMERING_VESSEL) && !spellHit &&
                (Hitter->GetTypeId() == TYPEID_PLAYER) && (CAST_PLR(Hitter)->IsActiveQuest(QUEST_REDEEMING_THE_DEAD)))
            {
                CAST_PLR(Hitter)->AreaExploredOrEventHappens(QUEST_REDEEMING_THE_DEAD);
                DoCast(me, SPELL_REVIVE_SELF);
                me->SetStandState(UNIT_STAND_STATE_STAND);
                me->SetUInt32Value(OBJECT_FIELD_DYNAMIC_FLAGS, 0);
                //me->RemoveAllAuras();
                DoScriptText(SAY_HEAL, me);
                spellHit = true;
            }
        }
    };
};

/*#####
# npc_cairne_bloodhoof
######*/

#define GOSSIP_HCB "I know this is rather silly but a young ward who is a bit shy would like your hoofprint."
//TODO: verify abilities/timers
class boss_lorthemar_theron : public CreatureScript
{
public:
    boss_lorthemar_theron() : CreatureScript("boss_lorthemar_theron") { }

    struct boss_lorthemar_theronAI : public ScriptedAI
    {
        boss_lorthemar_theronAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() { events.Reset();}

        void EnterCombat(Unit* /*who*/)
        {
            events.ScheduleEvent(EVENT_ARCANE_SHOCK, 10000);
            events.ScheduleEvent(EVENT_CLEAVE, 5000);
            events.ScheduleEvent(EVENT_MANA_BURN, 30000);
            events.ScheduleEvent(EVENT_MASS_CHARM, 40000);
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
                case EVENT_ARCANE_SHOCK:
                    DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true), SPELL_ARCANE_SHOCK);
                    events.ScheduleEvent(EVENT_ARCANE_SHOCK, urand(10 * IN_MILLISECONDS, 30 * IN_MILLISECONDS));
                    break;
                case EVENT_CLEAVE:
                    DoCast(SelectTarget(SELECT_TARGET_TOPAGGRO, 0), SPELL_CLEAVE);
                    events.ScheduleEvent(EVENT_CLEAVE, urand(5 * IN_MILLISECONDS, 8 * IN_MILLISECONDS));
                    break;
                case EVENT_MANA_BURN:
                    DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true), SPELL_MANA_BURN);
                    events.ScheduleEvent(EVENT_MANA_BURN, urand(25 * IN_MILLISECONDS, 45 * IN_MILLISECONDS));
                    break;
                case EVENT_MASS_CHARM:
                    DoCastAOE(SPELL_MASS_CHARM);
                    events.ScheduleEvent(EVENT_MASS_CHARM, urand(1 * MINUTE*IN_MILLISECONDS, 2 * MINUTE*IN_MILLISECONDS));
                    break;
                }
            }
            DoMeleeAttackIfReady();
        }
    private:
        EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new boss_lorthemar_theronAI(creature);
    }
};

void AddSC_silvermoon_city()
{
    new npc_blood_knight_stillblade();
    new boss_lorthemar_theron();
}
