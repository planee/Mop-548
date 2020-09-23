#include "ScriptPCH.h"
#include "throne_of_the_four_winds.h"

#define MAX_ENCOUNTER 2

static const DoorData doordata[] = 
{
    {0, 0, DOOR_TYPE_ROOM, BOUNDARY_NONE},
};

enum InstanceEnums
{
	// Spells
	SPELL_SLIPSTREAM_BUFF = 87740,
	SPELL_SLIPSTREAM_PLAYER_VISUAL = 85063,
	SPELL_RELENTLESS_STORM_VISUAL = 89428,
	SPELL_STAY_CHILL_ACHIEVEMENT_CREDIT = 94119,
	SPELL_WIND_CHILL_10 = 84645,
	SPELL_WIND_CHILL_25 = 93123,
	SPELL_WIND_CHILL_10H = 93124,
	SPELL_WIND_CHILL_25H = 93125,
};

Position const GoBackPositions[8] =
{
	{ -16, 1021, 205, 0 },
	{ -80, 1021, 205, 0 },
	{ -256, 850, 205, 0 },
	{ -256, 785, 205, 0 },
	{ -83, 610, 205, 0 },
	{ -18, 610, 205, 0 },
	{ 156, 780, 205, 0 },
	{ 156, 850, 205, 0 },
};

Position const AlakirSlipstreamPositions[4] =
{
	{ -51.0972f, 576.807f, 200.7063f, 1.553343f },
	{ -287.604f, 816.51f, 200.7063f, 0.0f },
	{ 188.823f, 813.54f, 200.7063f, 3.124139f },
	{ -47.9531f, 1053.3f, 200.7063f, 4.694936f },
};

class instance_throne_of_the_four_winds : public InstanceMapScript
{
    public:
        instance_throne_of_the_four_winds() : InstanceMapScript("instance_throne_of_the_four_winds", 754) { }

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_throne_of_the_four_winds_InstanceMapScript(map);
        }

		struct instance_throne_of_the_four_winds_InstanceMapScript : public InstanceScript
		{
			instance_throne_of_the_four_winds_InstanceMapScript(Map* map) : InstanceScript(map)
			{
				SetBossNumber(MAX_BOSSES);
				LoadDoorData(doordata);
			}
			void Initialize()
			{
				for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
					Encounter[i] = NOT_STARTED;
				uiAnshalGUID = 0;
				uiNezirGUID = 0;
				uiRohashGUID = 0;
				uiAlakirGUID = 0;
				GatheringStrength = 0;
				WeatherData = 0;
				AlakirFlightData = 0;
				playerTimer = 2000;

				AnshalPlatform = NezirPlatform = RohashPlatform = 0;
				SkyWallRaid = SkyWallWind = HeartOfWindGUID = 0;
			}

			uint32 Encounter[MAX_ENCOUNTER];
			InstanceScript* addAchievement;
			uint64 AnshalPlatform;
			uint64 NezirPlatform;
			uint64 RohashPlatform;
			uint64 SkyWallRaid;
			uint64 SkyWallWind;
			uint64 HeartOfWindGUID;
			
			uint8 GatheringStrength;
			uint8 WeatherData;
			uint8 AlakirFlightData;
			
			uint64 uiAnshalGUID;
			uint64 uiNezirGUID;
			uint64 uiRohashGUID;
			uint64 uiAlakirGUID;

			void OnPlayerEnter(Player* player)
			{
				std::list<Creature*> spawnedCreature;
				GetCreatureListWithEntryInGrid(spawnedCreature, player, NPC_SLIPSTREAM_ALAKIR_1, 500.0f);
				for (std::list<Creature*>::iterator itr = spawnedCreature.begin(); itr != spawnedCreature.end(); ++itr)
				if (GetData(DATA_ALAKIR_EVENT) == DONE)
				{
					// fly buff on kill Al'akir
					player->CastSpell(player, 89107, true);
				}
				//Summon Splistream if server crash or raid lost connection
				if (spawnedCreature.empty())
				if (GetData(DATA_CONCLAVE_OF_WIND) == DONE)
				SummonSplistreamAlakir();
			}

			bool IsEncounterInProgress() const
			{
				for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
				{
					if (Encounter[i] == IN_PROGRESS)
						return true;
				}
				return false;
			}

			void BeforePlayerEnter(Player* pPlayer)
			{
				if (!uiTeamInInstance)
					uiTeamInInstance = pPlayer->GetTeam();
			}

			void OnCreatureCreate(Creature* pCreature)
			{
				switch (pCreature->GetEntry())
				{
				case NPC_ANSHAL:
					uiAnshalGUID = pCreature->GetGUID();
					break;
				case NPC_NEZIR:
					uiNezirGUID = pCreature->GetGUID();
					break;
				case NPC_ROHASH:
					uiRohashGUID = pCreature->GetGUID();
					break;
				case NPC_ALAKIR:
					uiAlakirGUID = pCreature->GetGUID();
						break;
				}
			}

			void OnGameObjectCreate(GameObject* go)
			{
				switch (go->GetEntry())
				{
				case GO_NAZIR_PLATFORM:
					NezirPlatform = go->GetGUID();
					go->setActive(true);
					break;

				case GO_ANSHAL_PLATFORM:
					AnshalPlatform = go->GetGUID();
					go->setActive(true);
					break;

				case GO_ROHASH_PLATFORM:
					RohashPlatform = go->GetGUID();
					go->setActive(true);
					break;
				case GO_SKYWALL_RAID:
					SkyWallRaid = go->GetGUID();
					go->setActive(true);
					break;
				case GO_SKYWALL_WIND:
					SkyWallWind = go->GetGUID();
					go->setActive(true);
					break;
				case GO_HEART_OF_WIND_10:
					if (instance->GetDifficulty() == RAID_DIFFICULTY_10MAN_NORMAL)
						HeartOfWindGUID = go->GetGUID();
					break;
				case GO_HEART_OF_WIND_25:
					if (instance->GetDifficulty() ==  RAID_DIFFICULTY_25MAN_NORMAL)
						HeartOfWindGUID = go->GetGUID();
					break;
				case GO_HEART_OF_WIND_10H:
					if (instance->GetDifficulty() == RAID_DIFFICULTY_10MAN_HEROIC)
						HeartOfWindGUID = go->GetGUID();
					break;
				case GO_HEART_OF_WIND_25H:
					if (instance->GetDifficulty() == RAID_DIFFICULTY_25MAN_HEROIC)
						HeartOfWindGUID = go->GetGUID();
					break;
				}
			}

			void OnGameObjectRemove(GameObject* pGo)
			{
			}

			void SetData(uint32 type, uint32 data)
			{
				switch (type)
				{
				case DATA_GATHERING_STRENGTH:
					GatheringStrength = data;
					break;
				case DATA_CONCLAVE_OF_WIND:
					switch (data)
					{
					case IN_PROGRESS:
						if (Creature* Anshal = instance->GetCreature(uiAnshalGUID))
						{
							if (Anshal->isAlive())
							{
								Anshal->SetInCombatWithZone();
								SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, Anshal);
							}
						}
						if (Creature* Nezir = instance->GetCreature(uiNezirGUID))
						{
							if (Nezir->isAlive())
							{
								Nezir->SetInCombatWithZone();
								SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, Nezir);
							}
						}
						if (Creature* Rohash = instance->GetCreature(uiRohashGUID))
						{
							if (Rohash->isAlive())
							{
								Rohash->SetInCombatWithZone();
								SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, Rohash);
							}
						}
						break;

					case FAIL:
						if (Creature* Anshal = instance->GetCreature(uiAnshalGUID))
						{
							SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, Anshal);
							Anshal->Respawn(true);
						}
						if (Creature* Nezir = instance->GetCreature(uiNezirGUID))
						{
							SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, Nezir);
							Nezir->Respawn(true);
						}
						if (Creature* Rohash = instance->GetCreature(uiRohashGUID))
						{
							SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, Rohash);
							Rohash->Respawn(true);
						}
						break;

					case DONE:
						SummonSplistreamAlakir();
						SaveToDB();
						break;
					}
					Encounter[0] = data;
					break;
				case DATA_ALAKIR_EVENT:
					switch (data)
					{
					case IN_PROGRESS:
						break;
					case DONE:
						if (GameObject* go = instance->GetGameObject(HeartOfWindGUID))
							go->SetPhaseMask(PHASEMASK_NORMAL, true);
						DoRespawnGameObject(HeartOfWindGUID, 7 * DAY);
						SaveToDB();
						break;
					}
					Encounter[1] = data;
					break;
				case DATA_WEATHER_EVENT:
					WeatherData = data;
					break;
				case DATA_ALAKIR_FLIGHT_PHASE:
					switch (data)
					{
					case NOT_STARTED:
						if (GameObject* go = instance->GetGameObject(AnshalPlatform))
						if (GameObject* go = instance->GetGameObject(NezirPlatform))
						if (GameObject* go = instance->GetGameObject(RohashPlatform))
						if (GameObject* go = instance->GetGameObject(SkyWallRaid))
						{
							go->SetGoState(GO_STATE_READY);
						}
						break;
					case IN_PROGRESS:
						if (GameObject* go = instance->GetGameObject(SkyWallRaid))
							go->SetDestructibleState(GO_DESTRUCTIBLE_DESTROYED);
						break;
					case FAIL:
						if (GameObject* go = instance->GetGameObject(SkyWallRaid))
							go->SetDestructibleState(GO_DESTRUCTIBLE_REBUILDING);
						break;
					case DONE:
						if (GameObject* go = instance->GetGameObject(SkyWallWind))
							go->Delete();
						break;
					}
						AlakirFlightData = data;
						break;
					


					if (data == DONE)
						SaveToDB();

					if (data == IN_PROGRESS)
					{
						if (Creature* Anshal = instance->GetCreature(uiAnshalGUID))
							Anshal->RemoveAura(SPELL_PRE_COMBAT_EFFECT_ANSHAL);

						if (Creature* Nezir = instance->GetCreature(uiNezirGUID))
							Nezir->RemoveAura(SPELL_PRE_COMBAT_EFFECT_NEZIR);

						if (Creature* Rohash = instance->GetCreature(uiRohashGUID))
							Rohash->RemoveAura(SPELL_PRE_COMBAT_EFFECT_ROHASH);

					}
					else if (data == FAIL || data == NOT_STARTED)
					{
						if (Creature* Anshal = instance->GetCreature(uiAnshalGUID))
						if (!Anshal->HasAura(SPELL_PRE_COMBAT_EFFECT_ANSHAL))
							Anshal->CastSpell(Anshal, SPELL_PRE_COMBAT_EFFECT_ANSHAL, true);

						if (Creature* Nezir = instance->GetCreature(uiNezirGUID))
						if (!Nezir->HasAura(SPELL_PRE_COMBAT_EFFECT_NEZIR))
							Nezir->CastSpell(Nezir, SPELL_PRE_COMBAT_EFFECT_NEZIR, true);

						if (Creature* Rohash = instance->GetCreature(uiRohashGUID))
						if (!Rohash->HasAura(SPELL_PRE_COMBAT_EFFECT_ROHASH))
							Rohash->CastSpell(Rohash, SPELL_PRE_COMBAT_EFFECT_ROHASH, true);
					}
				}
			}

			bool SetBossState(uint32 id, EncounterState state)
			{
				if (!InstanceScript::SetBossState(id, state))
					return false;

				return true;
			}

			uint32 GetData(uint32 type) const
			{
				switch (type)
				{
				case DATA_CONCLAVE_OF_WIND:
					return Encounter[0];
				case DATA_ALAKIR_EVENT:
					return Encounter[1];
				case DATA_GATHERING_STRENGTH:
					return GatheringStrength;
				case DATA_WEATHER_EVENT:
					return WeatherData;
				case DATA_ALAKIR_FLIGHT_PHASE:
					return AlakirFlightData;
				}
				return 0;
			}

			uint64 GetData64(uint32 type)
			{
				switch (type)
				{
				case DATA_ANSHAL: 
					return uiAnshalGUID;
				case DATA_NEZIR: 
					return uiNezirGUID;
				case DATA_ROHASH: 
					return uiRohashGUID;
				case DATA_ALAKIR: 
					return uiAlakirGUID;
				}
				return 0;
			}

			
			std::string GetSaveData()
			{
				OUT_SAVE_INST_DATA;

				std::string str_data;

				std::ostringstream saveStream;
				saveStream << "T W" << Encounter[0] << " " << Encounter[1];

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
				uint16 data0, data1;

				std::istringstream loadStream(in);
				loadStream >> dataHead1 >> dataHead2 >> data0 >> data1;

				if (dataHead1 == 'T' && dataHead2 == 'W')
				{
					Encounter[0] = data0;
					Encounter[1] = data1;
					for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
					{
						if (Encounter[i] == IN_PROGRESS)
							Encounter[i] = NOT_STARTED;
					}
				}
				else OUT_LOAD_INST_DATA_FAIL;

				OUT_LOAD_INST_DATA_COMPLETE;
			}

			void Update(uint32 diff)
			{
				if (playerTimer <= diff)
				{
					Map::PlayerList const &plrList = instance->GetPlayers();

					if (!plrList.isEmpty())
					for (Map::PlayerList::const_iterator i = plrList.begin(); i != plrList.end(); ++i)
					if (Player* pPlayer = i->getSource())
					if (pPlayer->isDead())
						if (pPlayer->GetPositionZ() < 160.0f && !pPlayer->IsBeingTeleported())
						pPlayer->NearTeleportTo(startPos.GetPositionX(), startPos.GetPositionY(), startPos.GetPositionZ(), startPos.GetOrientation());

					playerTimer = 2000;
				}
				else
					playerTimer -= diff;				
			}
			
		private:
			uint32 uiTeamInInstance;
			uint32 playerTimer;

			void SummonSplistreamAlakir()
			{
				for (int i = 0; i < 4; ++i)
				instance->SummonCreature(NPC_SLIPSTREAM_ALAKIR_1, AlakirSlipstreamPositions[i]);
			}
		};
};

class AreaTrigger_at_return_wind : public AreaTriggerScript
{
public:

	AreaTrigger_at_return_wind()
		: AreaTriggerScript("at_return_wind") {}

	bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
	{
		InstanceScript* instance = player->GetInstanceScript();
		if (instance)
		{
			if (player->isAlive())
			{
				if (instance->GetData(DATA_CONCLAVE_OF_WIND) != DONE)
				{
					float smallestDist = player->GetDistance2d(GoBackPositions[0].GetPositionX(), GoBackPositions[0].GetPositionY());
					int PointToGo = 0;
					for (int i = 0; i < 8; i++)
					{
						float distance = player->GetDistance2d(GoBackPositions[i].GetPositionX(), GoBackPositions[i].GetPositionY());
						if (distance < smallestDist)
						{
							smallestDist = distance;
							PointToGo = i;
						}
					}
					player->GetMotionMaster()->MoveJump(GoBackPositions[PointToGo], 50, 10);
					player->AddAura(SPELL_SLIPSTREAM_BUFF, player);
					player->AddAura(SPELL_SLIPSTREAM_PLAYER_VISUAL, player);
				}
				else if (instance->GetData(DATA_CONCLAVE_OF_WIND) == DONE && (instance->GetData(DATA_ALAKIR_FLIGHT_PHASE) == NOT_STARTED || instance->GetData(DATA_ALAKIR_FLIGHT_PHASE) == FAIL))
				{
					if (player->HasAura(SPELL_RELENTLESS_STORM_VISUAL))
						return false;

					player->CastSpell(player, SPELL_RELENTLESS_STORM_VISUAL, true);
					float speedFly = (210.0f - player->GetPositionZ()) / 15;
					player->GetMotionMaster()->MoveJump(player->GetPositionX(), player->GetPositionY(), 220.0f, speedFly, speedFly);
				}
			}
		}

		return true;
	}
};
void AddSC_instance_throne_of_the_four_winds()
{
    new instance_throne_of_the_four_winds();
	new AreaTrigger_at_return_wind();
}
