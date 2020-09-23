/*
 * Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
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
Name: cast_commandscript
%Complete: 100
Comment: All cast related commands
Category: commandscripts
EndScriptData */

#include "ScriptMgr.h"
#include "Chat.h"

class cast_commandscript : public CommandScript
{
public:
    cast_commandscript() : CommandScript("cast_commandscript") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand castCommandTable[] =
        {
            { "back",           SEC_ADMINISTRATOR,  false, &HandleCastBackCommand,              "", NULL },
            { "dist",           SEC_ADMINISTRATOR,  false, &HandleCastDistCommand,              "", NULL },
            { "self",           SEC_ADMINISTRATOR,  false, &HandleCastSelfCommand,              "", NULL },
            { "target",         SEC_ADMINISTRATOR,  false, &HandleCastTargetCommad,             "", NULL },
            { "dest",           SEC_ADMINISTRATOR,  false, &HandleCastDestCommand,              "", NULL },
            { "visual",         SEC_ADMINISTRATOR,  false, &HandleCastVisualCommand,            "", NULL },
            { "",               SEC_ADMINISTRATOR,  false, &HandleCastCommand,                  "", NULL },
            { NULL,             0,                  false, NULL,                                "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "cast",           SEC_ADMINISTRATOR,  false, NULL,                                "", castCommandTable },
            { NULL,             0,                  false, NULL,                                "", NULL }
        };
        return commandTable;
    }

    static bool HandleCastCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Unit* target = handler->getSelectedUnit();
        if (!target)
        {
            handler->SendSysMessage(LANG_SELECT_CHAR_OR_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r or Htalent form
        uint32 spellId = handler->extractSpellIdFromLink((char*)args);
        if (!spellId)
            return false;

        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
        if (!spellInfo)
        {
            handler->PSendSysMessage(LANG_COMMAND_NOSPELLFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!SpellMgr::IsSpellValid(spellInfo, handler->GetSession()->GetPlayer()))
        {
            handler->PSendSysMessage(LANG_COMMAND_SPELL_BROKEN, spellId);
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* triggeredStr = strtok(NULL, " ");
        if (triggeredStr)
        {
            int l = strlen(triggeredStr);
            if (strncmp(triggeredStr, "triggered", l) != 0)
                return false;
        }

        bool triggered = (triggeredStr != NULL);

        handler->GetSession()->GetPlayer()->CastSpell(target, spellId, triggered);

        return true;
    }

    static bool HandleCastBackCommand(ChatHandler* handler, char const* args)
    {
        Creature* caster = handler->getSelectedCreature();
        if (!caster)
        {
            handler->SendSysMessage(LANG_SELECT_CHAR_OR_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r
        // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r or Htalent form
        uint32 spellId = handler->extractSpellIdFromLink((char*)args);
        if (!spellId || !sSpellMgr->GetSpellInfo(spellId))
        {
            handler->PSendSysMessage(LANG_COMMAND_NOSPELLFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* triggeredStr = strtok(NULL, " ");
        if (triggeredStr)
        {
            int l = strlen(triggeredStr);
            if (strncmp(triggeredStr, "triggered", l) != 0)
                return false;
        }

        bool triggered = (triggeredStr != NULL);

        caster->CastSpell(handler->GetSession()->GetPlayer(), spellId, triggered);

        return true;
    }

    static bool HandleCastDistCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r or Htalent form
        uint32 spellId = handler->extractSpellIdFromLink((char*)args);
        if (!spellId)
            return false;

        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
        if (!spellInfo)
        {
            handler->PSendSysMessage(LANG_COMMAND_NOSPELLFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!SpellMgr::IsSpellValid(spellInfo, handler->GetSession()->GetPlayer()))
        {
            handler->PSendSysMessage(LANG_COMMAND_SPELL_BROKEN, spellId);
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* distStr = strtok(NULL, " ");

        float dist = 0;

        if (distStr)
            sscanf(distStr, "%f", &dist);

        char* triggeredStr = strtok(NULL, " ");
        if (triggeredStr)
        {
            int l = strlen(triggeredStr);
            if (strncmp(triggeredStr, "triggered", l) != 0)
                return false;
        }

        bool triggered = (triggeredStr != NULL);

        float x, y, z;
        handler->GetSession()->GetPlayer()->GetClosePoint(x, y, z, dist);

        handler->GetSession()->GetPlayer()->CastSpell(x, y, z, spellId, triggered);

        return true;
    }

    static bool HandleCastSelfCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Unit* target = handler->getSelectedUnit();
        if (!target)
        {
            handler->SendSysMessage(LANG_SELECT_CHAR_OR_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r or Htalent form
        uint32 spellId = handler->extractSpellIdFromLink((char*)args);
        if (!spellId)
            return false;

        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
        if (!spellInfo)
            return false;

        if (!SpellMgr::IsSpellValid(spellInfo, handler->GetSession()->GetPlayer()))
        {
            handler->PSendSysMessage(LANG_COMMAND_SPELL_BROKEN, spellId);
            handler->SetSentErrorMessage(true);
            return false;
        }

        target->CastSpell(target, spellId, false);

        return true;
    }

    static bool HandleCastTargetCommad(ChatHandler* handler, char const* args)
    {
        Creature* caster = handler->getSelectedCreature();
        if (!caster)
        {
            handler->SendSysMessage(LANG_SELECT_CHAR_OR_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!caster->getVictim())
        {
            handler->SendSysMessage(LANG_SELECTED_TARGET_NOT_HAVE_VICTIM);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r or Htalent form
        uint32 spellId = handler->extractSpellIdFromLink((char*)args);
        if (!spellId || !sSpellMgr->GetSpellInfo(spellId))
        {
            handler->PSendSysMessage(LANG_COMMAND_NOSPELLFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* triggeredStr = strtok(NULL, " ");
        if (triggeredStr)
        {
            int l = strlen(triggeredStr);
            if (strncmp(triggeredStr, "triggered", l) != 0)
                return false;
        }

        bool triggered = (triggeredStr != NULL);

        caster->CastSpell(caster->getVictim(), spellId, triggered);

        return true;
    }

    static bool HandleCastDestCommand(ChatHandler* handler, char const* args)
    {
        Unit* caster = handler->getSelectedUnit();
        if (!caster)
        {
            handler->SendSysMessage(LANG_SELECT_CHAR_OR_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r or Htalent form
        uint32 spellId = handler->extractSpellIdFromLink((char*)args);
        if (!spellId || !sSpellMgr->GetSpellInfo(spellId))
        {
            handler->PSendSysMessage(LANG_COMMAND_NOSPELLFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        char* posX = strtok(NULL, " ");
        char* posY = strtok(NULL, " ");
        char* posZ = strtok(NULL, " ");

        if (!posX || !posY || !posZ)
            return false;

        float x = float(atof(posX));
        float y = float(atof(posY));
        float z = float(atof(posZ));

        char* triggeredStr = strtok(NULL, " ");
        if (triggeredStr)
        {
            int l = strlen(triggeredStr);
            if (strncmp(triggeredStr, "triggered", l) != 0)
                return false;
        }

        bool triggered = (triggeredStr != NULL);

        caster->CastSpell(x, y, z, spellId, triggered);

        return true;
    }

    static bool HandleCastVisualCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
        {
            handler->SendSysMessage("The command cast visual play the animation of a spell.");
            handler->SendSysMessage("Usage: cast visual #spellID #visualposition #speed #thisAsPos #speedAsTime");
            handler->SendSysMessage("#thisAsPos #speedAsTime are optionals and are booleans i.e true or false, false by default.");
            handler->SendSysMessage("Examples:");
            handler->SendSysMessage(".cast visual 19411 0 12.0");
            handler->SendSysMessage(".cast visual 19411 0 12.0 true true");
            handler->SetSentErrorMessage(true);
            return false;
        }
        //
        Unit* targuet = handler->getSelectedUnit();
        //
        if (!targuet)
        {
            handler->SendSysMessage(LANG_SELECT_CHAR_OR_CREATURE);
            handler->SetSentErrorMessage(true);
            return false;
        }
        //
        strtok((char*)args, " ");
        // Get the visual to dispaly
        char const* visualS      = strtok(NULL, " ");
        //
        char const* speedS       = strtok(NULL, " ");
        //
        char const* thisAsPosS   = strtok(NULL, " ");
        //
        char const* speedAsTimeS = strtok(NULL, " ");
        // number or [name] Shift-click form |color|Hspell:spell_id|h[name]|h|r or Htalent form
        uint32 spellId = handler->extractSpellIdFromLink((char*)args);
        // Get the spell info
        SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId);
        // Check the spell ID and the spell Info
        if (!spellId || !spellInfo)
        {
            handler->PSendSysMessage(LANG_COMMAND_NOSPELLFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }                                                                
        // Validate spell
        if (!SpellMgr::IsSpellValid(spellInfo, handler->GetSession()->GetPlayer()))
        {
            handler->PSendSysMessage(LANG_COMMAND_SPELL_BROKEN, spellId);
            handler->SetSentErrorMessage(true);
            return false;
        }
        //
        if (!visualS)
        {
            handler->SendSysMessage("You most enter wich visual will be played, 0 or 1.");
            handler->SetSentErrorMessage(true);
            return false;                               
        }
        // 
        uint32 visual = atoi(visualS);
        //
        if (!(visual == 0 || visual == 1))
        {
            handler->SendSysMessage("Incorrect visual position value, most be 0 or 1.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        //
        uint32 visualID = spellInfo->SpellVisual[visual];
        //
        if (!speedS)
        {
            handler->SendSysMessage("You most enter a speed value.");
            handler->SetSentErrorMessage(true);
            return false;
        }
        //
        float speed = float(atof(speedS));
        //
        bool _thisAsPos = false;
        //
        bool _speedAsTime = false;
        //
        if (thisAsPosS && !speedAsTimeS)
        {
            int l = strlen(thisAsPosS);
            _thisAsPos = strncmp(thisAsPosS, "true", l) != 0;
        }
        else if (thisAsPosS && speedAsTimeS)
        {
            int l = strlen(thisAsPosS);
            _thisAsPos = strncmp(thisAsPosS, "true", l) != 0;
            int m = strlen(thisAsPosS);
            _speedAsTime = strncmp(speedAsTimeS, "true", l) != 0;
        }
        std::string value = "Spell visual played: " + std::to_string(visualID);
        //
        handler->SendSysMessage(value.c_str());
        //
        handler->GetSession()->GetPlayer()->SendPlaySpellVisual(visualID, targuet, speed, _thisAsPos, _speedAsTime);
        //
        return true;
    }
};

void AddSC_cast_commandscript()
{
    new cast_commandscript();
}
