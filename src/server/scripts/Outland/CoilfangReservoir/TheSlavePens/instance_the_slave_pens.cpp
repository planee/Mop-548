/*
 * Copyright (C) 2008-2014 TrinityCore <http://www.trinitycore.org/>
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

/*
This placeholder for the instance is needed for dungeon finding to be able
to give credit after the boss defined in lastEncounterDungeon is killed.
Without it, the party doing random dungeon won't get satchel of spoils and
gets instead the deserter debuff.
*/

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "the_slave_pens.h"

class instance_the_slave_pens : public InstanceMapScript
{
public:
	instance_the_slave_pens() : InstanceMapScript("instance_the_slave_pens", 547) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const 
    {
        return new instance_the_slave_pens_InstanceMapScript(map);
    }

    struct instance_the_slave_pens_InstanceMapScript : public InstanceScript
    {
		uint64 Boss_MenuTheBetrayerGUID;
		uint64 Boss_RokmarTheCrackerGUID;
		uint64 Boss_QuagmiranGUID;
		uint32 m_auiEncounter[EncounterCount];
		std::string str_data;

        instance_the_slave_pens_InstanceMapScript(Map* map) : InstanceScript(map) 
		{
			SetBossNumber(EncounterCount);
		}

		void Initialize()
		{
			memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

			Boss_MenuTheBetrayerGUID = 0;
			Boss_RokmarTheCrackerGUID = 0;
			Boss_QuagmiranGUID = 0;
		}

		void OnCreatureCreate(Creature* creature)
		{
			switch (creature->GetEntry())
			{
			case 17941:
				Boss_MenuTheBetrayerGUID = creature->GetGUID();
				break;
			case 17991:
				Boss_RokmarTheCrackerGUID = creature->GetGUID();
				break;
			case 17942:
				Boss_QuagmiranGUID = creature->GetGUID();
				break;
			}
		}

		uint64 GetData64(uint32 data)
		{
			switch (data)
			{
			case DATA_MENNU_THE_BETRAYER:          return Boss_MenuTheBetrayerGUID;
			case DATA_ROKMAR_THE_CRACKLER:         return Boss_RokmarTheCrackerGUID;
			case DATA_QUAGMIRRAN:				   return Boss_QuagmiranGUID;
			}

			return 0;
		}

		void SetData(uint32 type, uint32 data)
		{
			switch (type)
			{
			case DATA_MENNU_THE_BETRAYER:
				m_auiEncounter[0] = data;
				break;
			case DATA_ROKMAR_THE_CRACKLER:
				m_auiEncounter[1] = data;
				break;
			case DATA_QUAGMIRRAN:
				m_auiEncounter[2] = data;
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
			case DATA_MENNU_THE_BETRAYER:             return m_auiEncounter[0];
			case DATA_ROKMAR_THE_CRACKLER:           return m_auiEncounter[1];
			case DATA_QUAGMIRRAN:					 return m_auiEncounter[2];
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
};

void AddSC_instance_the_slave_pens()
{
    new instance_the_slave_pens();
}
