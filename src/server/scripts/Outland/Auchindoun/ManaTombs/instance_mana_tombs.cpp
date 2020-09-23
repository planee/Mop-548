/*
 * Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
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

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "mana_tombs.h"
#include "CreatureAI.h"


class instance_mana_tombs : public InstanceMapScript
{
    public:
		instance_mana_tombs() : InstanceMapScript("instance_mana_tombs", 557) {}

        struct instance_mana_tombs_InstanceMapScript : public InstanceScript
        {
			uint64 Boss_PandemoniusGUID;
			uint64 Boos_TavarokGUID;
			uint64 Boss_ShaffarGUID;
			uint64 Boss_YorGUID;
			uint32 m_auiEncounter[EncounterCount];
			std::string str_data;

            instance_mana_tombs_InstanceMapScript(Map* map) : InstanceScript(map)
            {
                SetBossNumber(EncounterCount);
            }

			void Initialize()
			{
				memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

				Boss_PandemoniusGUID = 0;
				Boos_TavarokGUID = 0;
				Boss_ShaffarGUID = 0;
				Boss_YorGUID = 0;
			}

			void OnCreatureCreate(Creature* creature)
			{
				switch (creature->GetEntry())
				{
				case 18341:
					Boss_PandemoniusGUID = creature->GetGUID();
					break;
				case 18343:
					Boos_TavarokGUID = creature->GetGUID();
					break;
				case 18344:
					Boss_ShaffarGUID = creature->GetGUID();
					break;
				}
			}

			uint64 GetData64(uint32 data)
			{
				switch (data)
				{
				case DATA_PANDEMONIUS:          return Boss_PandemoniusGUID;
				case DATA_TAVAROK:              return Boos_TavarokGUID;
				case DATA_NEXUSPRINCE_SHAFFAR:    return Boss_ShaffarGUID;
				case DATA_YOR:                return Boss_YorGUID;
				}

				return 0;
			}

			void SetData(uint32 type, uint32 data)
			{
				switch (type)
				{
				case DATA_PANDEMONIUS:
					m_auiEncounter[0] = data;
					break;
				case DATA_TAVAROK:
					m_auiEncounter[1] = data;
					break;
				case DATA_NEXUSPRINCE_SHAFFAR:
					m_auiEncounter[2] = data;
					break;
				case DATA_YOR:
					m_auiEncounter[3] = data;
					break;
				}

				if (data == DONE)
				{
					OUT_SAVE_INST_DATA;

					std::ostringstream saveStream;
					saveStream << m_auiEncounter[0] << ' ' << m_auiEncounter[1] << ' ' << m_auiEncounter[2] << ' ' << m_auiEncounter[3];

					str_data = saveStream.str();

					SaveToDB();
					OUT_SAVE_INST_DATA_COMPLETE;
				}
			}

			uint32 GetData(uint32 type)
			{
				switch (type)
				{
				case DATA_PANDEMONIUS:             return m_auiEncounter[0];
				case DATA_TAVAROK:               return m_auiEncounter[1];
				case DATA_NEXUSPRINCE_SHAFFAR:   return m_auiEncounter[2];
				case DATA_YOR:					return m_auiEncounter[3];
				}

				return 0;
			}

			const char* Save()
			{
				return str_data.c_str();
			}

			void Load(const char* in)
			{
				if (!in)
				{
					OUT_LOAD_INST_DATA_FAIL;
					return;
				}

				OUT_LOAD_INST_DATA(in);

				std::istringstream loadStream(in);
				loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2];

				for (uint8 i = 0; i < EncounterCount; ++i)
					if (m_auiEncounter[i] == IN_PROGRESS || m_auiEncounter[i] == FAIL)
						m_auiEncounter[i] = NOT_STARTED;

				OUT_LOAD_INST_DATA_COMPLETE;
			}
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_mana_tombs_InstanceMapScript(map);
        }
};

void AddSC_instance_mana_tombs()
{
    new instance_mana_tombs();
}
