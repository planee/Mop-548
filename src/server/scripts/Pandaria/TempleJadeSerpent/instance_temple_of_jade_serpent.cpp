/*
* Copyright (C) 2014-2017 RoG_WoW Source  <http://wow.rog.snet
*
* Dont Share The SourceCode
*
*/

#include "ScriptMgr.h"
#include "InstanceScript.h"

#include "temple_of_jade_serpent.h"

#define EVENT_LOREWALKER_STONESTEP_SUNS 0
#define EVENT_LOREWALKER_STONESTEP_TRIAL 1

enum SharedSpells
{
    //Spells for Lorewalker Stonestep event.
    SPELL_SHA_CORRUPTION        = 107034, //On spawn: Lot of mobs and decoration
    //ZAO SUNSEEKER SPELLS
    SPELL_SHA_CORRUPTION_3      = 120000, //OnSpawn: Jiang
    //LOREWALKER STONESTEP SPELLS
    SPELL_ROOT_SELF             = 106822,

    //Scroll
    SPELL_DRAW_SHA_2            = 111393,
    SPELL_DRAW_SHA_3            = 111431,

    //SUN SPELLS
    SPELL_DRAW_SHA              = 111395,
    SPELL_SUN                   = 107349,
    SPELL_GROW_LOW              = 104921,
    SPELL_GROW_HIGH             = 111701,
    SPELL_SUNFIRE_EXPLOSION     = 111737,
    SPELL_DUMMY_NUKE            = 105898, //11 00 04 - 11 07 05 - 11 40 22
    SPELL_SUNFIRE_BLAST         = 111853,
    SPELL_SUNFIRE_RAYS          = 107223, //09 26 28 - 09 46 29 - 10 06 46
    SPELL_EXTRACT_SHA           = 111764,
    SPELL_EXTRACT_SHA_2         = 111806,
    SPELL_EXTRACT_SHA_3         = 111807,
    SPELL_EXTRACT_SHA_4         = 111768,
    SPELL_UNKNOWN               = 105581,
    //JIANG SPELLS
    SPELL_JUGGLER_JIANG         = 114745, //OnSpawn: Jiang
    //THE SONGBIRD QUEEN SPELLS
    SPELL_SINGING_SONGBIRD      = 114789, //OnSpawn: Songbird
    //HAUNTING SHA SPELLS
    SPELL_HAUNTING_GAZE         = 114650, //OnSpawn
    //XIANG SPELLS
    SPELL_JUGGLER_XIANG         = 114718,
    //FISH SPELLS
    SPELL_WATER_BUBBLE          = 114549, //OnSpawn
    //ChannelSpell : 42808, 512
    
    SPELL_POSSESSED_BY_SHA                  = 110164, //On Spawn
    SPELL_JADE_ESSENCE                      = 106797, //AddAura on phase 2
    SPELL_TRANSFORM_VISUAL                  = 74620, //When the dragon is dead, cast this and remove the possess aura.
    
    SPELL_FIGMENT_OF_DOUBT_2    = 106935,
    SPELL_COPY_WEAPON           = 41054,
    SPELL_COPY_WEAPON_2         = 41055,
    SPELL_BOUNDS_OF_REALITY_2   = 117665,
    SPELL_RIFT_OF_DOUBT         = 109504,
};

enum Types
{
    TYPE_LOREWALKTER_STONESTEP = 0,
    TYPE_NUMBER_SUN_DEFEATED = 1,
    TYPE_SET_SUNS_SELECTABLE = 2,
    TYPE_LOREWALKER_STONESTEP_TALK_AFTER_ZAO = 3,
    TYPE_SET_SCROLL_SELECTABLE = 4,
    TYPE_GET_EVENT_LOREWALKER_STONESTEP = 5,
    TYPE_LIU_FLAMEHEART_STATUS = 6,
    TYPE_IS_WIPE = 7,
    TYPE_CLASS_FIGMENT = 8,
    TYPE_CLASS_FIGMENT_DIE = 9,
};

enum Status
{
    STATUS_LOREWALKER_STONESTEP_NONE        = 1,
    STATUS_LOREWALKER_STONESTEP_INTRO       = 2,
    STATUS_LOREWALKER_STONESTEP_SPAWN_SUNS  = 3,
    STATUS_LOREWALKER_STONESTEP_SPAWN_SUNS_2= 4,
    STATUS_LOREWALKER_STONESTEP_ZAO_COMBAT  = 5,
    STATUS_LOREWALKER_STONESTEP_FINISH      = 6,
};

class instance_temple_of_jade_serpent : public InstanceMapScript
{
public:
    instance_temple_of_jade_serpent() : InstanceMapScript("instance_temple_of_jade_serpent", 960) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_temple_of_jade_serpent_InstanceMapScript(map);
    }

    struct instance_temple_of_jade_serpent_InstanceMapScript : public InstanceScript
    {
        instance_temple_of_jade_serpent_InstanceMapScript(Map* map) : InstanceScript(map)
        {
            Initialize();
        }

        InstanceScript* pInstance;
        uint32 playerTimer;
        Map::PlayerList const &plrList = instance->GetPlayers();

        /*
        ** Wise Mari script.
        */
        uint64 doorWiseMari;
        uint64 wiseMariGUID;
        uint32 eventWiseMari;
        /*
        ** End of Wise Mari script
        */

        /*
        ** LoreWalkter Stonestep script.
        */
        uint8 eventChoosen;
        uint64 lorewalkter_stonestep;
        uint64 zao_sunseeker;
        uint64 scroll;
        uint64 door_lorewalker;
        uint64 guidPeril;
        uint64 guidStrife;
        uint32 eventStatus_lorewalkter_stonestep;
        uint32 eventStatus_numberSunDefeated;
        uint32 wipeTimer;
        uint32 eventStonestep;
        std::list<uint64> creatures_corrupted;
        std::list<uint64> sunfires;
        std::list<uint64> suns;
        std::list<uint64> sun_triggers;
        std::list<uint64> sha_summoned;
        /*
        ** End of Lorewalker Stonestep script.
        */

        /*
        ** Liu Flameheart script.
        */
        uint32 countMinionDeads;
        uint64 liuGuid;
        uint64 doorLiu;
        uint64 doorLiu_2;
        uint32 eventLiuFlameheart;
        std::list<uint64> mobs_liu;
        bool jump;
        /*
        ** End of Liu Flameheart script.
        */

        /*
        ** Sha of Doubt script.
        */
        uint64 sha_of_doubt_guid;
        uint8 countDps;
        uint8 countHeal;
        uint8 countTank;
        uint8 countFigments;
        uint32 eventShaofDoubt;
        /*
        ** End of Sha of Doubt script.
        */

        void Initialize()
        {
            SetBossNumber(MAX_ENCOUNTERS);

            // Wise Mari script
            doorWiseMari = 0;
            wiseMariGUID = 0;
            eventWiseMari = 0;

            //LoreWalkter Stonestep script.
            lorewalkter_stonestep = 0;
            zao_sunseeker = 0;
            scroll = 0;
            guidPeril = 0;
            guidStrife = 0;
            eventStatus_lorewalkter_stonestep = STATUS_LOREWALKER_STONESTEP_NONE;
            eventStatus_numberSunDefeated = 0;
            eventChoosen = 0;
            wipeTimer = 3000;
            eventStonestep = 0;

            //Liu Flameheart script.
            countMinionDeads = 0;
            liuGuid = 0;
            doorLiu = 0;
            doorLiu_2 = 0;
            eventLiuFlameheart = 0;
            jump = false;

            //Sha of doubt script.
            sha_of_doubt_guid = 0;
            countDps = 0;
            countTank = 0;
            countHeal = 0;
            countFigments = 0;
            eventShaofDoubt = 0;
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GO_DOOR_WISE_MARI:
                    doorWiseMari = go->GetGUID();
                    break;
				case GO_DOOR_LIU_FLAMEHEART_2:
                    doorLiu_2 = go->GetGUID();
                    break;
				case GO_DOOR_LOREWALKER_STONSTEP:
                    door_lorewalker = go->GetGUID();
                    break;
				case GO_DOOR_LIU_FLAMEHEART:
                    doorLiu = go->GetGUID();
                    break;
            }
        }
        
        void OnCreatureCreate(Creature* creature)
        {
            OnCreatureCreate_lorewalker_stonestep(creature);
            OnCreatureCreate_liu_flameheart(creature);
            OnCreatureCreate_sha_of_doubt(creature);

            if (creature->GetEntry() == 56448)
            	wiseMariGUID = creature->GetGUID();
        }

        void OnUnitDeath(Unit* unit)
        {
            OnUnitDeath_lorewalker_stonestep(unit);
            OnUnitDeath_liu_flameheat(unit);
        }
        
        void Update(uint32 diff) 
        {
            //LOREWALKER STONESTEP: If Wipe, we must clean the event.
            if (wipeTimer && IsWipe())
            {
                if (Creature* lorewalker = instance->GetCreature(lorewalkter_stonestep)) 
                if (pInstance = lorewalker->GetInstanceScript())
                if (pInstance->GetBossState(BOSS_LOREWALKER_STONESTEP) != DONE && pInstance->GetBossState(BOSS_WISE_MARI) == DONE)
                Wipe_lorewalker_stonestep();                
            }
            else
                wipeTimer -= diff;

            if (playerTimer <= diff)
            {
                if (!plrList.isEmpty())
                for (Map::PlayerList::const_iterator i = plrList.begin(); i != plrList.end(); ++i)
                if (Player* pPlayer = i->getSource())
                if (pInstance = pPlayer->GetInstanceScript())
                {
                    if (Creature* liu = instance->GetCreature(liuGuid))
                    {
                        if (liu->isDead())
                        {
                            if (Creature* sha = instance->GetCreature(sha_of_doubt_guid))
                            {
                                if (!sha->isInCombat())
                                {
                                    if (GameObject* go = sha->FindNearestGameObject(GO_DOOR_LIU_FLAMEHEART, 50.0f))
                                        go->SetGoState(GO_STATE_ACTIVE);
                                    sha->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                                }
                            }
                        }
                        else if (liu->isAlive() && !liu->isInCombat() && !jump)
                        {
                            std::list<Creature*> creatures;
                            GetCreatureListWithEntryInGrid(creatures, liu, NPC_MINION_OF_DOUBT, 1000.0f);

                            if (creatures.empty())
                                return;

                            for (std::list<Creature*>::iterator iter = creatures.begin(); iter != creatures.end(); ++iter)
                            if ((*iter)->isAlive())
                                return;
                            else
                            {
                                liu->AI()->DoAction(ACTION_JUMP_START);
                                jump = true;
                            }
                        }
                    }

                    if (Creature* wise = instance->GetCreature(wiseMariGUID))
                    if (Creature* lorewalker = instance->GetCreature(lorewalkter_stonestep))
                    {
                        if (wise->isDead() && lorewalker->isDead())
                        {
                            if (GameObject* go = wise->FindNearestGameObject(GO_DOOR_WISE_MARI, 100.0f))
                                go->SetGoState(GO_STATE_ACTIVE);

                            if (GameObject* go = lorewalker->FindNearestGameObject(GO_DOOR_LOREWALKER_STONSTEP, 100.0f))
                                go->SetGoState(GO_STATE_ACTIVE);
                        }
                    }
                }
                playerTimer = 2000;
            }
            else
                playerTimer -= diff;
        }

        void SetData(uint32 type, uint32 data)
        {
            SetData_lorewalker_stonestep(type, data);
            SetData_sha_of_doubt(type, data);

            SetBossState(type, EncounterState(data));

            if (data == DONE)
                SaveToDB();
        }

        uint32 GetData(uint32 type)
        {
            switch (type)
            {
            case TYPE_CLASS_FIGMENT:
                if (countDps < 2)
                    return 0;
                else if (countHeal == 0)
                    return 1;
                else if (countTank == 0)
                    return 2;
                return 3;
                break;
            case TYPE_IS_WIPE:
                return IsWipe();
            case TYPE_GET_EVENT_LOREWALKER_STONESTEP:
                return eventChoosen;
            case TYPE_LOREWALKTER_STONESTEP:
                return eventStatus_lorewalkter_stonestep;
            case TYPE_NUMBER_SUN_DEFEATED:
                return eventStatus_numberSunDefeated;
            default:
                return STATUS_NONE;
            case TYPE_LIU_FLAMEHEART_STATUS:
                {
                    Creature* creature = instance->GetCreature(liuGuid);
                    if (creature == nullptr)
                        return 2;

                    if (creature->GetHealthPct() < 70.f)
                        return 1;
                    else
                        return 0;
                }
                break;
            }

            if (type == DATA_WISE_MARI_EVENT)
                return eventWiseMari;

            if (type == DATA_LOREWALKER_STONESTEP_EVENT)
                return eventStonestep;

            if (type == DATA_LIU_FLAMEHEART_EVENT)
                return eventLiuFlameheart;

            if (type == DATA_SHA_OF_DOUBT_EVENT)
                return eventShaofDoubt;
        }

        uint64 GetData64(uint32 type)
        {
            switch (type)
            {
            case NPC_ZAO_SUNSEEKER:
                return zao_sunseeker;
            case BOSS_WISE_MARI:
                return wiseMariGUID;
            case BOSS_LOREWALKER_STONESTEP:
                return lorewalkter_stonestep;
            case BOSS_LIU_FLAMEHEART:
                return liuGuid;
            case BOSS_SHA_OF_DOUBT:
                return sha_of_doubt_guid;
            case  DATA_DOOR_WISE_MARI:
                return doorWiseMari;
            case  DATA_DOOR_LOREWALKER_STONSTEP:
                return door_lorewalker;
            }
            return 0;
        }

        void SetData_sha_of_doubt(uint32 type, uint32 data)
        {
            switch (type)
            {
            case TYPE_CLASS_FIGMENT_DIE:
                if (data == 0)
                    ++countDps;
                else if (data == 1)
                    ++countHeal;
                else
                    ++countTank;
                if (countDps + countHeal + countTank == countFigments)
                {
                    Creature* sha_doubt = instance->GetCreature(sha_of_doubt_guid);
                    if (!sha_doubt)
                        return;

                    sha_doubt->RemoveAura(SPELL_BOUNDS_OF_REALITY_2);
                    sha_doubt->RemoveAura(SPELL_RIFT_OF_DOUBT);
                    
                }
                break;
            case TYPE_CLASS_FIGMENT:
                countFigments = 0;
                countDps = 0;
                countHeal = 0;
                countTank = 0;
                break;
            }
        }
        void OnCreatureCreate_sha_of_doubt(Creature* creature)
        {
            switch (creature->GetEntry())
            {
            case BOSS_SHA_OF_DOUBT:
                sha_of_doubt_guid = creature->GetGUID();
                break;
            case NPC_FIGMENT_OF_DOUBT:
                if (creature->ToTempSummon())
                {
                    ++countFigments;
                    Unit* summoner = creature->ToTempSummon()->GetSummoner();
                    if (!summoner)
                        return;
                    summoner->AddAura(SPELL_FIGMENT_OF_DOUBT_2, creature);
                    creature->SetDisplayId(summoner->GetDisplayId());
                    creature->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_MIRROR_IMAGE);
                    summoner->CastSpell(creature, SPELL_COPY_WEAPON, false);
                    summoner->CastSpell(creature, SPELL_COPY_WEAPON_2, false);

                    Unit* caster = summoner;
                    Unit* target = creature;

                    if (!caster)
                        return;
                    uint32 prevItem = target->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID);
                    if (Player* player = caster->ToPlayer())

                    {
                        if (Item* mainItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND))
                            target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, mainItem->GetEntry());

                    }
                    else
                        target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID, caster->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID));

                    prevItem = target->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1);

                    if (Player* player = caster->ToPlayer())
                    {
                        if (Item* offItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND))
                            target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1, offItem->GetEntry());
                    }
                    else
                        target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1, caster->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 1));
                    
                    prevItem = target->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 2);

                    if (Player* player = caster->ToPlayer())
                    {
                        if (Item* rangedItem = player->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED))
                            target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 2, rangedItem->GetEntry());
                    }
                    else 
                        target->SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 2, caster->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID + 2));
                }
                break;
            }
        }

        void OnCreatureCreate_liu_flameheart(Creature* creature)
        {
            switch (creature->GetEntry())
            {
            case NPC_JADE_FIRE:
                creature->setFaction(14);
                creature->SetDisplayId(11686);
                creature->SetReactState(REACT_PASSIVE);
                creature->CastSpell(creature, 107108, true);
                creature->DespawnOrUnsummon(20000);
                break;
            case BOSS_LIU_FLAMEHEART:
                liuGuid = creature->GetGUID();
                break;
            }
        }
        void OnUnitDeath_liu_flameheat(Unit* unit)
        {
            if (unit->ToCreature() && unit->ToCreature()->GetEntry() == NPC_MINION_OF_DOUBT)
            {
                if (unit->GetAreaId() == 6119) //AreaId of Liu Flameheart.
                {
                    ++countMinionDeads;

                    //Spawn Liu Flameheart.
                    if (countMinionDeads == 3)   
                    if (Creature* creature = instance->GetCreature(liuGuid))
                        creature->AI()->DoAction(ACTION_JUMP_START);
                }
            }
        }

        void SetData_lorewalker_stonestep(uint32 type, uint32 data)
        {
            switch (type)
            {
            case TYPE_LOREWALKTER_STONESTEP:
                eventStatus_lorewalkter_stonestep = data;
                break;
            }
        }
        void OnCreatureCreate_lorewalker_stonestep(Creature* creature)
        {
            switch (creature->GetEntry())
            {
            case NPC_STRIFE:
                guidStrife = creature->GetGUID();
                break;
            case NPC_PERIL:
                guidPeril = creature->GetGUID();
                break;
            case NPC_SUN_TRIGGER:
                creature->setFaction(14);
                creature->SetDisplayId(11686);
                creature->SetReactState(REACT_PASSIVE);
                sun_triggers.push_back(creature->GetGUID());
                break;
            case NPC_SUN:
                creature->SetFlag(UNIT_NPC_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                suns.push_back(creature->GetGUID());
                break;
            case NPC_ZAO_SUNSEEKER:
                zao_sunseeker = creature->GetGUID();
                break;
            case BOSS_LOREWALKER_STONESTEP:
                lorewalkter_stonestep = creature->GetGUID();
                creature->CastSpell(creature, SPELL_ROOT_SELF, true);
                break;
            case NPC_SCROLL:
                scroll = creature->GetGUID();
                break;
                //Some creature that need an aura.
            case NPC_WISE_DRAGON:
            case NPC_WELL:
            case NPC_STRIFE_INI:
            case NPC_OSONG:
            case NPC_HEROINE:
            case NPC_MOON:
            case 59545:
            case 59552:
            case 59544:
                creature->CastSpell(creature, SPELL_SHA_CORRUPTION, false);
                creatures_corrupted.push_back(creature->GetGUID());
                break;
            case 59555: //Haunting Sha
                creature->CastSpell(creature, SPELL_SHA_CORRUPTION, false);
                creature->CastSpell(creature, SPELL_HAUNTING_GAZE, false);
                creatures_corrupted.push_back(creature->GetGUID());
                break;
            case 59553: //Gru
                creature->CastSpell(creature, SPELL_SHA_CORRUPTION, false);
                creature->CastSpell(creature, SPELL_SINGING_SONGBIRD, false);
                creatures_corrupted.push_back(creature->GetGUID());
                break;
            case 59546: //Poisson
                creature->CastSpell(creature, SPELL_SHA_CORRUPTION, false);
                creature->CastSpell(creature, SPELL_WATER_BUBBLE, false);
                creatures_corrupted.push_back(creature->GetGUID());
                break;
            case NPC_JIANG: //Jiang
                creatures_corrupted.push_back(creature->GetGUID());
                break;
            case NPC_XIANG: //Xiang
                creatures_corrupted.push_back(creature->GetGUID());
                break;
            case NPC_SWIRLING_SUNFIRE: //Feu solaire tourbillonement trigger
                creature->SetDisplayId(11686);
                creature->SetReactState(REACT_PASSIVE);
                sunfires.push_back(creature->GetGUID());
                break;
            default:
                if (creature->GetAreaId() == 6118)
                    mobs_liu.push_back(creature->GetGUID());
                break;
            }
        }
        void OnUnitDeath_lorewalker_stonestep(Unit* unit)
        {            
            // When the scroll dies, we must draw all the corrupted units.
            if (unit->GetGUID() == scroll)
            {
                //Depending on the event randomly choosen:
                eventChoosen = urand(EVENT_LOREWALKER_STONESTEP_SUNS, EVENT_LOREWALKER_STONESTEP_TRIAL);

                if (eventChoosen == EVENT_LOREWALKER_STONESTEP_SUNS)
                {
                    Creature* lorewalker = instance->GetCreature(lorewalkter_stonestep);
                    if (lorewalker && lorewalker->GetAI())
                        lorewalker->GetAI()->DoAction(ACTION_SPAWN_SUNS);
                    
                    eventStatus_lorewalkter_stonestep = STATUS_LOREWALKER_STONESTEP_SPAWN_SUNS;

                    //Then draw all the corrupted units and summon the suns.
                    for (auto guid : creatures_corrupted)
                    {
                        if (guid == lorewalkter_stonestep)
                            continue;
                        Creature* c = instance->GetCreature(guid);
                        if (c == nullptr)
                            continue;

                        unit->AddAura(SPELL_DRAW_SHA_2, c);
                        unit->AddAura(SPELL_DRAW_SHA_2, c);
                        c->CastSpell(unit, SPELL_DRAW_SHA_3, false);
                        c->ForcedDespawn(2000);
                    }
                }
                else if (eventChoosen == EVENT_LOREWALKER_STONESTEP_TRIAL)
                {
                    Creature* lorewalker = instance->GetCreature(lorewalkter_stonestep);
                    if (lorewalker && lorewalker->GetAI())
                        lorewalker->GetAI()->DoAction(ACTION_SPAWN_STRIFE_AND_PERIL);

                    //Then draw all the corrupted units and summon unit.
                    for (auto guid : creatures_corrupted)
                    {
                        if (guid == lorewalkter_stonestep)
                            continue;
                        Creature* c = instance->GetCreature(guid);
                        if (c == nullptr)
                            continue;

                        unit->AddAura(SPELL_DRAW_SHA_2, c);
                        unit->AddAura(SPELL_DRAW_SHA_2, c);
                        c->CastSpell(unit, SPELL_DRAW_SHA_3, false);
                        c->ForcedDespawn(2000);
                    }
                }
            }
        }
        
        void Wipe_lorewalker_stonestep()
        {
            Creature* creature;
            if(creature = instance->GetCreature(lorewalkter_stonestep))         
             if (creature->GetAI())
                    creature->GetAI()->Reset();

            eventStatus_numberSunDefeated = 0;
        }

        bool SetBossState(uint32 type, EncounterState state)
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            switch (type)
            {
            case BOSS_WISE_MARI:
            case BOSS_LOREWALKER_STONESTEP:
            case BOSS_LIU_FLAMEHEART:
            case BOSS_SHA_OF_DOUBT:
                break;
            }

            if (state == DONE)
            {
                SaveToDB();
            }

            return true;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::string str_data;

            std::ostringstream saveStream;
            saveStream << "J S " << GetBossSaveData()
                << eventWiseMari << ' ' << eventStonestep << ' '
                << eventLiuFlameheart << ' ' << eventShaofDoubt << ' ';

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

            if (dataHead1 == 'J' && dataHead2 == 'S')
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                {
                    uint32 tmpState;
                    loadStream >> tmpState;
                    if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                        tmpState = NOT_STARTED;
                    SetBossState(i, EncounterState(tmpState));
                }

                uint32 eventWiseMari1 = 0;
                loadStream >> eventWiseMari1;
                eventWiseMari = eventWiseMari1;

                uint32 eventStonestep1 = 0;
                loadStream >> eventStonestep1;
                eventStonestep = eventStonestep1;

                uint32 eventLiuFlameheart1 = 0;
                loadStream >> eventLiuFlameheart1;
                eventLiuFlameheart = eventLiuFlameheart1;

                uint32 eventShaofDoubt1 = 0;
                loadStream >> eventShaofDoubt1;
                eventShaofDoubt = eventShaofDoubt1;
            }
            else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_temple_of_jade_serpent()
{
    new instance_temple_of_jade_serpent();
}
