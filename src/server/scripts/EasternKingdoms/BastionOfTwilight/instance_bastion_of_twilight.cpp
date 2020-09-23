#include "ScriptPCH.h"
#include "bastion_of_twilight.h"

#define MAX_ENCOUNTER 5

static const DoorData doordata[] = 
{
    {DOOR_HALFUS_ENTRANCE,  DATA_HALFUS,            DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {DOOR_HALFUS_EXIT,      DATA_HALFUS,            DOOR_TYPE_PASSAGE,  BOUNDARY_NONE},
    {DOOR_THER_ENTRANCE,    DATA_VALIONA_THERALION, DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {DOOR_THER_EXIT,        DATA_VALIONA_THERALION, DOOR_TYPE_PASSAGE,  BOUNDARY_NONE},
    {DOOR_COUNCIL_ENTRANCE, DATA_COUNCIL,           DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    {DOOR_COUNCIL_EXIT,     DATA_COUNCIL,           DOOR_TYPE_PASSAGE,  BOUNDARY_NONE},
    {DOOR_CHOGALL_ENTRANCE, DATA_CHOGALL,           DOOR_TYPE_ROOM,     BOUNDARY_NONE},
    //{GO_CHOGALL_FLOOR,      DATA_CHOGALL,           DOOR_TYPE_PASSAGE,  BOUNDARY_NONE},
    {GO_SINESTRA_DOOR,      DATA_SINESTRA,          DOOR_TYPE_ROOM,     BOUNDARY_NONE},
};

class instance_bastion_of_twilight : public InstanceMapScript
{
public:
    instance_bastion_of_twilight() : InstanceMapScript("instance_bastion_of_twilight", 671) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_bastion_of_twilight_InstanceMapScript(map);
    }

    struct instance_bastion_of_twilight_InstanceMapScript: public InstanceScript
    {
        instance_bastion_of_twilight_InstanceMapScript(Map* map) : InstanceScript(map)
        {
			data_phase = 1;			
			memset(&Encounter, 0, sizeof(Encounter));
            SetBossNumber(MAX_ENCOUNTER);
            LoadDoorData(doordata);
            uiWyrmbreakerGUID = 0;
            uiValionaGUID = 0;
            uiTheralionGUID = 0;
            uiFeludiusGUID = 0;
            uiArionGUID = 0;
            uiIgnaciousGUID = 0;
            uiTerrastraGUID = 0;
            uiMonstrosityGUID = 0;
            uiWhelpCageGUID = 0;
            uiValionaTheralionHealth = 0;
            uiChogallGUID = 0;
            uiChogallFloorGUID = 0;
            memset(m_uiDialogs, 0, sizeof(m_uiDialogs));
            playerDied = 0;
            CacheoftheBroodmotherGUID = 0;
        }

		void Initialize()
		{
			for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
				uiEncounter[i] = NOT_STARTED;

			// Bosses
			// Halfus
			uiWyrmbreakerGUID = 0;
			// Ascendant Council
			data_phase = 0;
			ascendantcouncil = 0;
			uiFeludiusGUID = 0;
			uiIgnaciousGUID = 0;
			uiArionGUID = 0;
			uiTerrastraGUID = 0;
			uiMonstrosityGUID = 0;
			// Sinestra
			sinestra = 0;

			// Gobjects

			// Misc
			chogallHalfus = 0;
			chogallValiona = 0;
			chogallCouncil = 0;
		}

		bool IsEncounterInProgress() const
		{
			for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
				if (uiEncounter[i] == IN_PROGRESS)
					return true;

			return false;
		}

		void OnPlayerEnter(Player* player)
		{
			if (GetBossState(DATA_CHOGALL) == DONE)
			{
				if (GameObject* go = instance->GetGameObject(uiChogallFloorGUID))
					go->SetGoState(GO_STATE_ACTIVE);
			}
			if (GetBossState(DATA_COUNCIL) != DONE && GetBossState(DATA_VALIONA_THERALION) == DONE)
			{
				if (Creature* feludius = instance->GetCreature(uiFeludiusGUID))
				if (feludius->isDead())
				{
					feludius->Respawn();
					feludius->AI()->EnterEvadeMode();
				}					
				if (Creature* ignacious = instance->GetCreature(uiIgnaciousGUID))
				if (ignacious->isDead())
				{
					ignacious->Respawn();
					ignacious->AI()->EnterEvadeMode();
				}
				if (Creature* arion = instance->GetCreature(uiArionGUID))
				if (arion->isDead())
				{
					arion->Respawn();
					arion->AI()->EnterEvadeMode();
				}
				if (Creature* terrastra = instance->GetCreature(uiTerrastraGUID))
				if (terrastra->isDead())
				{
					terrastra->Respawn();	
					terrastra->AI()->EnterEvadeMode();
				}
				if (Creature* mostrosity = instance->GetCreature(uiMonstrosityGUID))
				if (mostrosity->isAlive())
				{
					mostrosity->AI()->EnterEvadeMode();
					mostrosity->DespawnOrUnsummon();
				}
					
			}
		}

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case NPC_HALFUS_WYRMBREAKER:
                    uiWyrmbreakerGUID = creature->GetGUID();
                    break;
                case NPC_VALIONA:
                    uiValionaGUID = creature->GetGUID();
                    break;
                case NPC_THERALION:
                    uiTheralionGUID = creature->GetGUID();
                    break;
                case NPC_FELUDIUS:
                    uiFeludiusGUID = creature->GetGUID();
                    break;
                case NPC_IGNACIOUS:
                    uiIgnaciousGUID = creature->GetGUID();
                    break;
                case NPC_ARION:
                    uiArionGUID = creature->GetGUID();
                    break;
                case NPC_TERRASTRA:
                    uiTerrastraGUID = creature->GetGUID();
                    break;
				case NPC_ELEMENTIUM_MONSTROSITY:
                    uiMonstrosityGUID = creature->GetGUID();
                    break;
                case NPC_CHOGALL:
                    uiChogallGUID = creature->GetGUID();
                    break;
				case NPC_CHOGALL_COUNCIL:
					chogallCouncil = creature->GetGUID();
					break;
				case NPC_CHOGALL_DRAGONS:
					chogallValiona = creature->GetGUID();
					break;
				case NPC_CHOGALL_HALFUS:
					chogallHalfus = creature->GetGUID();
					break;
            }
        }

        void OnGameObjectCreate(GameObject* pGo)
        {
            switch (pGo->GetEntry())
            {
            case GO_WHELP_CAGE:
                uiWhelpCageGUID = pGo->GetGUID();
                break;
            case DOOR_HALFUS_ENTRANCE:
                uiDoorHalfusEntranceGUID = pGo->GetGUID();
                AddDoor(pGo, true);
                break;
            case DOOR_HALFUS_EXIT:
                uiDoorHalfusExitGUID = pGo->GetGUID();
                AddDoor(pGo, true);
				break;
            case DOOR_THER_ENTRANCE:
                uiDoorTherEntranceGUID = pGo->GetGUID();
                AddDoor(pGo, true);
                break;
            case DOOR_THER_EXIT:
                uiDoorTherExitGUID = pGo->GetGUID();
                AddDoor(pGo, true);
                break;
            case DOOR_COUNCIL_ENTRANCE:
                uiDoorCouncilEntranceGUID = pGo->GetGUID();
                AddDoor(pGo, true);
                break;
            case DOOR_COUNCIL_EXIT:
                uiDoorCouncilExitGUID = pGo->GetGUID();
                AddDoor(pGo, true);
                break;
            case DOOR_CHOGALL_ENTRANCE:
                uiDoorChogallEntranceGUID = pGo->GetGUID();
                AddDoor(pGo, true);
                break;
            case GO_SINESTRA_DOOR:
                AddDoor(pGo, true);
                break;
            case GO_CHOGALL_FLOOR:
                AddDoor(pGo, true);
                uiChogallFloorGUID = pGo->GetGUID();
                break;
            case GO_CACHE_OF_THE_BROODMOTHER:
                if (instance->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC || instance->GetDifficulty() == RAID_DIFFICULTY_10MAN_HEROIC)
                    CacheoftheBroodmotherGUID = pGo->GetGUID();
            }
        }

        void OnUnitDeath(Unit* unit)
        {
            if (unit->GetTypeId() == TYPEID_PLAYER && GetBossState(DATA_SINESTRA) == IN_PROGRESS)
            {
                if (playerDied == 0)
                {
                    playerDied = 1;
                    SaveToDB();
                }
            }
        }

        uint64 GetData64(uint32 identifier)
        {
            switch (identifier)
            {
            case DATA_HALFUS:
                return uiWyrmbreakerGUID;
            case DATA_VALIONA:
                return uiValionaGUID;
            case DATA_THERALION:
                return uiTheralionGUID;
            case DATA_FELUDIUS:
                return uiFeludiusGUID;
            case DATA_IGNACIOUS:
                return uiIgnaciousGUID;
            case DATA_ARION:
                return uiArionGUID;
            case DATA_TERRASTRA:
                return uiTerrastraGUID;
            case DATA_MONSTROSITY:
                return uiMonstrosityGUID;
            case DATA_WHELP_CAGE:
                return uiWhelpCageGUID;
            case DATA_CHOGALL:
                return uiChogallGUID;
            }
            return 0;
        }

        uint32 GetData(uint32 type)
        {
            switch (type)
            {
            case DATA_HEALTH_VALIONA_THERALION:
                return uiValionaTheralionHealth;
            case DATA_DLG_ENTRANCE:
                return m_uiDialogs[0];
            case DATA_DLG_HALFUS:
                return m_uiDialogs[1];
            case DATA_DLG_VALIONA_THERALION:
                return m_uiDialogs[2];
            case DATA_DLG_COUNCIL_1:
                return m_uiDialogs[3];
            case DATA_DLG_COUNCIL_2:
                return m_uiDialogs[4];
            case DATA_DLG_COUNCIL_3:
                return m_uiDialogs[5];
            case DATA_DLG_CHOGALL:
                return m_uiDialogs[6];
            case DATA_DLG_SINESTRA:
                return m_uiDialogs[7];
            case DATA_WIPE_COUNT:
                return playerDied;
            }
            return 0;
        }

		bool SetBossState(uint32 data, EncounterState state)
		{
			if (!InstanceScript::SetBossState(data, state))
				return false;

			if (state == DONE)
			{
				switch (data)
				{
				case DATA_HALFUS:		
				case DATA_VALIONA_THERALION:
				case DATA_COUNCIL:
                    SaveToDB();
                    break;
				case DATA_CHOGALL:
                    if (Creature* chogall = instance->GetCreature(uiChogallGUID))
                    if (chogall->GetMap()->IsHeroic())
                    if (GameObject* go = instance->GetGameObject(uiChogallFloorGUID))
                        go->SetGoState(GO_STATE_ACTIVE);
                    SaveToDB();
				case DATA_SINESTRA:
                    SaveToDB();
					break;
				}
			}

			return true;
		}


        void SetData(uint32 type, uint32 data)
        {
            switch (type)
            {
                case DATA_HEALTH_VALIONA_THERALION:
                    uiValionaTheralionHealth = data;
                    break;
                case DATA_DLG_ENTRANCE:
                    m_uiDialogs[0] = data;
                    SaveToDB();
                    break;
                case DATA_DLG_HALFUS:
                    m_uiDialogs[1] = data;
                    SaveToDB();
                    break;
                case DATA_DLG_VALIONA_THERALION:
                    m_uiDialogs[2] = data;
                    SaveToDB();
                    break;
                case DATA_DLG_COUNCIL_1:
                    m_uiDialogs[3] = data;
                    SaveToDB();
                    break;
                case DATA_DLG_COUNCIL_2:
                    m_uiDialogs[4] = data;
                    SaveToDB();
                    break;
                case DATA_DLG_COUNCIL_3:
                    m_uiDialogs[5] = data;
                    SaveToDB();
                    break;
                case DATA_DLG_CHOGALL:
                    m_uiDialogs[6] = data;
                    SaveToDB();
                    break;
                case DATA_DLG_SINESTRA:
                    m_uiDialogs[7] = data;
                    SaveToDB();
                    break;
            }
        }

        bool CheckRequiredBosses(uint32 bossId, Player const* player = NULL) const
        {
            if (player && player->isGameMaster())
                return true;
        
            switch (bossId)
            {
                case DATA_VALIONA_THERALION:
                    if (GetBossState(DATA_HALFUS) != DONE)
                        return false;
                    break;
                case DATA_COUNCIL:
                    if (GetBossState(DATA_VALIONA_THERALION) != DONE)
                        return false;
                    break;
                case DATA_CHOGALL:
                    if (GetBossState(DATA_COUNCIL) != DONE)
                        return false;
                    break;
                case DATA_SINESTRA:
                    if (GetBossState(DATA_CHOGALL) != DONE)
                        return false;
                    break;
                default:   
                    break;
            }
            return true;
        }

        std::string GetDialogSaveData()
        {
            std::ostringstream saveStream;
            for (uint8 i = 0; i < 8; i++)
                saveStream << (uint32)m_uiDialogs[i] << " ";
            return saveStream.str();
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::string str_data;

            std::ostringstream saveStream;
            saveStream << "B T " << GetBossSaveData() << GetDialogSaveData() << playerDied << " ";

            str_data = saveStream.str();

            OUT_SAVE_INST_DATA_COMPLETE;
            return str_data;
        }

        void Load(const char* in)
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            char dataHead1, dataHead2;

            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2;

            if (dataHead1 == 'B' && dataHead2 == 'T')
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;
                    SetBossState(i, EncounterState(tmpState));
                }
                for (uint8 i = 0; i < 8; i++)
                {
                    uint32 tmpDlg;
                    loadStream >> tmpDlg;
                    if (tmpDlg != DONE)
                        tmpDlg = NOT_STARTED;
                    m_uiDialogs[i] = tmpDlg;
                }

                loadStream >> playerDied;


            } 
            else 
                OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }

		void Update(uint32 diff)
		{

			if (playerTimer <= diff)
			{
				if (!plrList.isEmpty())
				for (Map::PlayerList::const_iterator i = plrList.begin(); i != plrList.end(); ++i)
				if (Player* pPlayer = i->getSource())
				if (InstanceScript* pInstance = pPlayer->GetInstanceScript())
				{
					if (!instance->IsHeroic())
					if (pPlayer->GetPositionZ() < 700.0f && !pPlayer->IsBeingTeleported())
						pPlayer->NearTeleportTo(enterPos.GetPositionX(), enterPos.GetPositionY(), enterPos.GetPositionZ(), enterPos.GetOrientation());

				}
				playerTimer = 2000;
			}
			else
				playerTimer -= diff;

			if (resetTimer <= diff)
			{
				if (GetBossState(DATA_COUNCIL) != DONE && GetBossState(DATA_VALIONA_THERALION) == DONE)
				{
					if (!plrList.isEmpty())
					for (Map::PlayerList::const_iterator i = plrList.begin(); i != plrList.end(); ++i)
					if (Player* pPlayer = i->getSource())
					if (InstanceScript* pInstance = pPlayer->GetInstanceScript())
					{						
						if (pPlayer->isAlive())
							return;
						else
						{
							if (Creature* mostrosity = instance->GetCreature(uiMonstrosityGUID))
							if (mostrosity->isAlive())
								mostrosity->AI()->EnterEvadeMode();
							if (Creature* feludius = instance->GetCreature(uiFeludiusGUID))
							if (feludius->isDead())
							{
								feludius->Respawn();
								feludius->AI()->EnterEvadeMode();
							}
							if (Creature* ignacious = instance->GetCreature(uiIgnaciousGUID))
							if (ignacious->isDead())
							{
								ignacious->Respawn();
								ignacious->AI()->EnterEvadeMode();
							}
							if (Creature* arion = instance->GetCreature(uiArionGUID))
							if (arion->isDead())
							{
								arion->Respawn();
								arion->AI()->EnterEvadeMode();
							}
							if (Creature* terrastra = instance->GetCreature(uiTerrastraGUID))
							if (terrastra->isDead())
							{
								terrastra->Respawn();
								terrastra->AI()->EnterEvadeMode();
							}
						}
					}
				}

				if (GetBossState(DATA_VALIONA_THERALION) != DONE && GetBossState(DATA_HALFUS) == DONE)
				{
					if (Creature* valiona = instance->GetCreature(uiValionaGUID))
					if (Creature* theralion = instance->GetCreature(uiTheralionGUID))
					if (valiona->HasAura(47008) && !theralion->HasAura(47008) || theralion->HasAura(47008) && !valiona->HasAura(47008)) //Fix problem with Berserk in one dragon
					{
						valiona->RemoveAura(47008);
						theralion->RemoveAura(47008);
						valiona->GetMotionMaster()->MoveTargetedHome();
						theralion->GetMotionMaster()->MoveTargetedHome();
						valiona->AI()->Reset();
						theralion->AI()->Reset();
					}
				}
				
				resetTimer = 3000;
			}
			else
				resetTimer -= diff;

		}

        private:
			uint32 playerTimer;
			uint32 resetTimer;
            uint64 uiWyrmbreakerGUID;
            uint32 m_uiDialogs[8];
            uint64 uiValionaGUID;
            uint64 uiTheralionGUID;
            uint64 uiFeludiusGUID;
            uint64 uiArionGUID;
            uint64 uiIgnaciousGUID;
            uint64 uiTerrastraGUID;
            uint64 uiMonstrosityGUID;
            uint32 uiValionaTheralionHealth;
            uint64 uiChogallGUID;
            uint64 uiWhelpCageGUID;
            uint64 uiDoorHalfusEntranceGUID;
            uint64 uiDoorHalfusExitGUID;
            uint64 uiDoorTherEntranceGUID;
            uint64 uiDoorTherExitGUID;
            uint64 uiDoorCouncilEntranceGUID;
            uint64 uiDoorCouncilExitGUID;
            uint64 uiDoorChogallEntranceGUID;
            uint64 uiChogallFloorGUID;
            uint64 CacheoftheBroodmotherGUID;
            uint32 playerDied;
			uint32 uiEncounter[MAX_ENCOUNTER];
			uint8 data_phase;
			uint64 ascendantcouncil; 
			uint64 sinestra;
			// Misc
			uint64 chogallHalfus;
			uint64 chogallValiona;
			uint64 chogallCouncil;

			Map::PlayerList const &plrList = instance->GetPlayers();

			private:
				uint32 Encounter[MAX_ENCOUNTER];
    };
	
};
void AddSC_instance_bastion_of_twilight()
{
    new instance_bastion_of_twilight();
}