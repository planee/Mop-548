/* ScriptData
Name: rcontrol_Commandscript
%Complete: 0%
Comment: Remote Server info And Control t command
Category: Development tools
Author: Eddard
EndScriptData */

#include "ScriptMgr.h"
#include "Chat.h"

class rcontrol_Commandscript : public CommandScript
{
    public:
        rcontrol_Commandscript() : CommandScript("rcontrol_Commandscript") { }

		ChatCommand* GetCommands() const
        {
			static ChatCommand rcontrolCommandTable[] =
			{
				{ "gethordecount",        SEC_CONSOLE,   true, &HandleGetHordeCount,       "", NULL },
				{ "getaliancecount",      SEC_CONSOLE,   true, &HandleGetAlianceCount,     "", NULL },
				{ "getplayercount",       SEC_CONSOLE,   true, &HandleGetPlayerCount,      "", NULL },
				{ "getmaxplayercount",    SEC_CONSOLE,   true, &HandleGetMaxPlayerCount,   "", NULL },
				{ "getupdatetime",        SEC_CONSOLE,   true, &HandleGetUpdateTime,       "", NULL },
				{ NULL,                             0,   false, NULL,                      "", NULL }
			};
            static ChatCommand commandTable[] =
            {
                { "rcontrol",     SEC_CONSOLE,   false,   NULL,      "", rcontrolCommandTable },
                { NULL,                     0,   false,   NULL,      "",                 NULL }
            };
			return commandTable;
        }
		/* Return the ammount of Horde players on-line */
		static bool HandleGetHordeCount(ChatHandler* handler, const char* /*args*/)
		{
			SessionMap sessions = sWorld->GetAllSessions();
			uint32 hordeCount = 0;
			for (auto itr : sessions)
			{
				if (Player* player = itr.second->GetPlayer())
					if (player->GetTeamId() == TEAM_HORDE)
						hordeCount++;
			}
			handler->PSendSysMessage("%u", hordeCount);
			return true;
		}
		/* Return the ammount of Alliance players on-line */
		static bool HandleGetAlianceCount(ChatHandler* handler, const char* /*args*/)
		{
			SessionMap sessions = sWorld->GetAllSessions();
			uint32 alianceCount = 0;
			for (auto itr : sessions)
			{
				if (Player* player = itr.second->GetPlayer())
					if (player->GetTeamId() == TEAM_ALLIANCE)
						alianceCount++;
			}
			handler->PSendSysMessage("%u", alianceCount);
			return true;
		}
		/* Return the ammount of players on-line */
		static bool HandleGetPlayerCount(ChatHandler* handler, const char* /*args*/)
        {
			uint32 playersNum = sWorld->GetPlayerCount();
            handler->PSendSysMessage("%u", playersNum);
            return true;
        }
		/* Return the max ammount of players on-line */
		static bool HandleGetMaxPlayerCount(ChatHandler* handler, const char* /*args*/)
		{
			uint32 maxPlayersNum = sWorld->GetMaxPlayerCount();
			handler->PSendSysMessage("%u", maxPlayersNum);
			return true;
		}
		/* Return Server's uptime */
		static bool HandleGetUpdateTime(ChatHandler* handler, const char* /*args*/)
		{
			uint64 timeInSecs = sWorld->GetUptime();
			uint64 secs = timeInSecs % MINUTE;
			uint64 minutes = timeInSecs % HOUR / MINUTE;
			uint64 hours = timeInSecs % DAY / HOUR;
			uint64 days = timeInSecs / DAY;
			std::ostringstream uptime;
			uptime
				<< days    << ":"
				<< hours   << ":"
				<< minutes << ":"
				<< secs;
			handler->PSendSysMessage("%s", uptime.str());
			return true;
		}
};

void AddSC_rcontrol_Commandscript()
{
    new rcontrol_Commandscript();
}