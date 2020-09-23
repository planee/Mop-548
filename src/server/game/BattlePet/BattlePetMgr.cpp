/*
* Copyright (C) 2008-2012 TrinityCore <http://www.trinitycore.org/>
* Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#include "Common.h"
#include "DBCEnums.h"
#include "ObjectMgr.h"
#include "GuildMgr.h"
#include "World.h"
#include "WorldPacket.h"
#include "DatabaseEnv.h"
#include "AchievementMgr.h"
#include "Arena.h"
#include "CellImpl.h"
#include "GameEventMgr.h"
#include "GridNotifiersImpl.h"
#include "Guild.h"
#include "Language.h"
#include "Player.h"
#include "SpellMgr.h"
#include "DisableMgr.h"
#include "ScriptMgr.h"
#include "MapManager.h"
#include "Battleground.h"
#include "BattlegroundAB.h"
#include "Map.h"
#include "InstanceScript.h"
#include "Group.h"
#include "BattlePetMgr.h"
#include "PetJournal/PetJounral.h"
#include "PetJournal/BattlePetTemplate.h"
#include "LFBMgr.h"
#include "Battle/PetBattle.h"
#include "PetJounral.h"

BattlePetMgr::BattlePetMgr(Player* owner) : m_player(owner)
{
}

typedef std::vector<BattlePet::PetTemplate*> PetList;

void BattlePetMgr::GetBattlePetList(PetBattleDataList &battlePetList) const
{
    auto spellMap = m_player->GetSpellMap();
	BattlePet::PetJournal* petjournal = m_player->GetPetJournal();
	PetList const* listpet = petjournal->GetPetList();
	petjournal->ConvertOldPetsToBattlePet();

	for (PetList::const_iterator iter = listpet->begin(); iter != listpet->end(); ++iter)
	{
		auto proto = *iter;
		PetBattleData pet(proto->GetNPCId(), proto->GetModel(), proto->GetSpecies(), proto->GetSpellId());
		battlePetList.push_back(pet);
	}    
}

void BattlePetMgr::BuildBattlePetJournal(WorldPacket *data)
{
    PetBattleDataList petList;
    GetBattlePetList(petList);	
	
    ByteBuffer dataBuffer;

    data->Initialize(SMSG_BATTLE_PET_JOURNAL);

    data->WriteBits(0, 25);                     // Battle Team
    data->WriteBits(petList.size(), 19);

    // bits part
	BattlePet::PetJournal* petjournal = m_player->GetPetJournal();
	PetList const* listpet = petjournal->GetPetList();
	for (PetList::const_iterator iter = listpet->begin(); iter != listpet->end(); ++iter){

		auto proto = *iter;
		ObjectGuid petGuid = uint64(proto->GetId());//uint64(proto->GetSpellId());
		bool quality = (proto->GetQuality()) ? false : true;
		data->WriteBits(0, 7);								// name length											
		data->WriteBit(true);								// hasQuality, inversed		
		data->WriteBit(petGuid[3]);
		data->WriteBit(true);								// hasBreed, inversed
		data->WriteBit(petGuid[5]);
		data->WriteBit(petGuid[0]);
		data->WriteBit(true);								// hasFlags, inversed
		data->WriteBit(false);								// hasFirstOwnerGuid
		data->WriteBit(petGuid[2]);
		// if hasfirstownerguid bits 7 1 6 2 4 3 0 5
		data->WriteBit(false);								// BATTLE_PET_FLAG_NOT_ACCOUNT_BOUND
		data->WriteBit(petGuid[7]);
		data->WriteBit(petGuid[4]);
		data->WriteBit(petGuid[6]);
		data->WriteBit(petGuid[1]);

		if (false)
			dataBuffer << uint16(proto->GetFlags());					// hasFlags

		dataBuffer << uint32(proto->GetCurrentHealth());				// Health or MaxHealth
		dataBuffer << uint32(proto->GetSpeed());						// Speed

		if (false)
			dataBuffer << uint16(proto->GetBreed());					// hasBreed

		if (false)
			dataBuffer << uint16(proto->GetQuality());					// hasQuality

		dataBuffer.WriteByteSeq(petGuid[5]);
		dataBuffer << uint16(proto->GetXp());							// Experience
		dataBuffer.WriteByteSeq(petGuid[2]);
		dataBuffer.WriteByteSeq(petGuid[1]);
		dataBuffer.WriteByteSeq(petGuid[6]);
		dataBuffer << uint32(proto->GetMaxHealth());					// MaxHealth or Health
		dataBuffer << uint32(proto->GetModel());						// Model
		dataBuffer << uint32(proto->GetSpecies());						// Species
		dataBuffer << uint32(proto->GetNPCId());						// PetEntry
		dataBuffer << uint32(proto->GetPower());						// Power
		dataBuffer.WriteByteSeq(petGuid[3]);
		dataBuffer << uint16(proto->GetLevel());						// Level
		dataBuffer.WriteByteSeq(petGuid[0]);
		dataBuffer.WriteByteSeq(petGuid[4]);		
		dataBuffer.WriteByteSeq(petGuid[7]);
	}    

    data->WriteBit(1);                          // Slots enabled
    data->FlushBits();

    if (dataBuffer.size())
        data->append(dataBuffer);

    *data << uint16(1);                         // Unk
}

void WorldSession::HandleSummonBattlePet(WorldPacket& recvData)
{ 
	sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_BATTLE_PET_SUMMON_COMPANION");

	ObjectGuid petEntry;

	petEntry[0] = recvData.ReadBit();
	petEntry[3] = recvData.ReadBit();
	petEntry[6] = recvData.ReadBit();
	petEntry[4] = recvData.ReadBit();
	petEntry[5] = recvData.ReadBit();
	petEntry[7] = recvData.ReadBit();
	petEntry[2] = recvData.ReadBit();
	petEntry[1] = recvData.ReadBit();

	recvData.ReadByteSeq(petEntry[3]);
	recvData.ReadByteSeq(petEntry[1]);
	recvData.ReadByteSeq(petEntry[5]);
	recvData.ReadByteSeq(petEntry[4]);
	recvData.ReadByteSeq(petEntry[2]);
	recvData.ReadByteSeq(petEntry[6]);
	recvData.ReadByteSeq(petEntry[0]);
	recvData.ReadByteSeq(petEntry[7]);

	Player* player = GetPlayer();
	BattlePet::PetJournal* journal = player->GetPetJournal();	

	BattlePet::PetTemplate* battlePet = journal->GetBattlePet(petEntry);
	if (!battlePet)
	{
		sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_SUMMON_BATTLE_PET_COMPANION - Player %u tryed to summon battle pet companion %lu which it doesn't own!",
			player->GetGUIDLow(), (uint64)petEntry);
		return;
	}

	if (!battlePet->GetCurrentHealth())
	{
		sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_SUMMON_BATTLE_PET_COMPANION - Player %u tryed to summon battle pet companion %lu which is dead!",
			player->GetGUIDLow(), (uint64)petEntry);
		return;
	}

	if (journal->GetCurrentSummonId() == petEntry)
		journal->UnSummonCurrentBattlePet(false);
	else
	{
		if (uint32 summonSpell = battlePet->GetSummonSpell())
		{
			journal->SetCurrentSummonId(petEntry);
			player->CastSpell(player, summonSpell, true);
		}
	}
}

void WorldSession::HandleBattlePetCage(WorldPacket& recvData)
{
	ObjectGuid petEntry;

	petEntry[5] = recvData.ReadBit();
	petEntry[3] = recvData.ReadBit();
	petEntry[7] = recvData.ReadBit();
	petEntry[0] = recvData.ReadBit();
	petEntry[6] = recvData.ReadBit();
	petEntry[1] = recvData.ReadBit();
	petEntry[4] = recvData.ReadBit();
	petEntry[2] = recvData.ReadBit();

	recvData.ReadByteSeq(petEntry[4]);
	recvData.ReadByteSeq(petEntry[5]);
	recvData.ReadByteSeq(petEntry[3]);
	recvData.ReadByteSeq(petEntry[7]);
	recvData.ReadByteSeq(petEntry[6]);
	recvData.ReadByteSeq(petEntry[0]);
	recvData.ReadByteSeq(petEntry[2]);
	recvData.ReadByteSeq(petEntry[1]);

	BattlePet::PetJournal* journal = GetPlayer()->GetPetJournal();
	
	BattlePet::PetTemplate* proto = journal->GetBattlePet(petEntry);
	if (!proto)
	{
		sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_BATTLE_PET_CAGE - Player %u tryed to release Battle Pet %lu which it doesn't own!",
			GetPlayer()->GetGUIDLow(), (uint64)petEntry);
		return;
	}

	if (proto->HasSpeciesFlag(BATTLE_PET_FLAG_NOT_CAGEABLE))
	{
		sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_BATTLE_PET_CAGE - Player %u tryed to cage Battle Pet %lu which isn't cageable!",
			GetPlayer()->GetGUIDLow(), (uint64)petEntry);
		return;
	}

	journal->Cage(proto);
}

void WorldSession::HandleBattlePetDelete(WorldPacket& recvData)
{
	sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_BATTLE_PET_DELETE");

	ObjectGuid petEntry;

	petEntry[1] = recvData.ReadBit();
	petEntry[0] = recvData.ReadBit();
	petEntry[4] = recvData.ReadBit();
	petEntry[3] = recvData.ReadBit();
	petEntry[5] = recvData.ReadBit();
	petEntry[6] = recvData.ReadBit();
	petEntry[2] = recvData.ReadBit();
	petEntry[7] = recvData.ReadBit();

	recvData.ReadByteSeq(petEntry[5]);
	recvData.ReadByteSeq(petEntry[3]);
	recvData.ReadByteSeq(petEntry[2]);
	recvData.ReadByteSeq(petEntry[0]);
	recvData.ReadByteSeq(petEntry[1]);
	recvData.ReadByteSeq(petEntry[4]);
	recvData.ReadByteSeq(petEntry[7]);
	recvData.ReadByteSeq(petEntry[6]);

	BattlePet::PetJournal* journal = GetPlayer()->GetPetJournal();	

	BattlePet::PetTemplate* battlePet = journal->GetBattlePet(petEntry);
	if (!battlePet)
	{
		sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_BATTLE_PET_DELETE - Player %u tryed to release Battle Pet %lu which it doesn't own!",
			GetPlayer()->GetGUIDLow(), (uint64)petEntry);
		return;
	}

	if (!battlePet->HasSpeciesFlag(BATTLE_PET_FLAG_RELEASABLE))
	{
		sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_BATTLE_PET_DELETE - Player %u tryed to release Battle Pet %lu which isn't releasable!",
			GetPlayer()->GetGUIDLow(), (uint64)petEntry);
		return;
	}

	journal->Delete(battlePet);
}

void WorldSession::HandleBattlePetModifyName(WorldPacket& recvData)
{
	sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_BATTLE_PET_MODIFY_NAME");

	ObjectGuid petEntry;
	uint8 nicknameLen;
	std::string nickname;
	bool hasDeclinedNames;

	uint8 declinedNameLen[MAX_DECLINED_NAME_CASES];
	DeclinedName declinedname;

	petEntry[3] = recvData.ReadBit();
	petEntry[4] = recvData.ReadBit();
	petEntry[7] = recvData.ReadBit();
	petEntry[0] = recvData.ReadBit();
	petEntry[6] = recvData.ReadBit();
	petEntry[2] = recvData.ReadBit();
	nicknameLen = recvData.ReadBits(7);
	hasDeclinedNames = recvData.ReadBit();
	petEntry[5] = recvData.ReadBit();
	petEntry[1] = recvData.ReadBit();

	if (hasDeclinedNames)
	{
		for (uint8 i = 0; i < MAX_DECLINED_NAME_CASES; i++)
		{
			declinedNameLen[i] = recvData.ReadBits(7);
		}
	}
	
	recvData.ReadByteSeq(petEntry[3]);
	recvData.ReadByteSeq(petEntry[7]);
	recvData.ReadByteSeq(petEntry[5]);
	recvData.ReadByteSeq(petEntry[2]);
	nickname = recvData.ReadString(nicknameLen);
	recvData.ReadByteSeq(petEntry[1]);
	recvData.ReadByteSeq(petEntry[4]);
	recvData.ReadByteSeq(petEntry[6]);
	recvData.ReadByteSeq(petEntry[0]);

	if (hasDeclinedNames)
	{
		for (uint8 i = 0; i < MAX_DECLINED_NAME_CASES; i++)
		{
			declinedname.name[i] = recvData.ReadString(declinedNameLen[i]);
		}
	}

	BattlePet::PetJournal* journal = GetPlayer()->GetPetJournal();

	BattlePet::PetTemplate* battlePet = journal->GetBattlePet(petEntry);
	if (!battlePet)
	{
		sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_BATTLE_PET_MODIFY_NAME - Player %u tryed to set the name for Battle Pet %lu which it doesn't own!",
			GetPlayer()->GetGUIDLow(), (uint64)petEntry);
		return;
	}

	if (nickname.size() > BATTLE_PET_MAX_NAME_LENGTH)
	{
		sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_BATTLE_PET_MODIFY_NAME - Player %u tryed to set the name for Battle Pet %lu with an invalid length!",
			GetPlayer()->GetGUIDLow(), (uint64)petEntry);
		return;
	}

	if (hasDeclinedNames)
	{
		std::wstring wname;
		Utf8toWStr(nickname, wname);
		if (!ObjectMgr::CheckDeclinedNames(wname, declinedname))
			return;

		for (uint8 i = 0; i < MAX_DECLINED_NAME_CASES; i++)
		{
			battlePet->SetDeclinedName(i, declinedname.name[i]);
		}
	}

	// TODO: check for invalid characters, ect...

	battlePet->SetNickname(nickname);
	battlePet->SetTimestamp((uint32)time(NULL));

	if (journal->GetCurrentSummonId())
	{
		if (journal->GetCurrentSummon())
			journal->GetCurrentSummon()->SetUInt32Value(UNIT_FIELD_BATTLE_PET_COMPANION_NAME_TIMESTAMP, battlePet->GetTimestamp());
	}

	if (hasDeclinedNames)
	{
		SQLTransaction trans = CharacterDatabase.BeginTransaction();
		battlePet->SaveDeclinedNames(trans);
		CharacterDatabase.CommitTransaction(trans);
	}
}

void WorldSession::HandleBattlePetQueryName(WorldPacket& recvData)
{
	return;

	sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_BATTLE_PET_QUERY_NAME");

	ObjectGuid petEntry, petguid;

	petEntry[4] = recvData.ReadBit();
	petEntry[1] = recvData.ReadBit();
	petguid[2] = recvData.ReadBit();
	petguid[5] = recvData.ReadBit();
	petguid[7] = recvData.ReadBit();
	petEntry[5] = recvData.ReadBit();
	petguid[6] = recvData.ReadBit();
	petEntry[0] = recvData.ReadBit();
	petEntry[7] = recvData.ReadBit();
	petEntry[2] = recvData.ReadBit();
	petguid[1] = recvData.ReadBit();
	petEntry[3] = recvData.ReadBit();
	petguid[0] = recvData.ReadBit();
	petEntry[6] = recvData.ReadBit();
	petguid[3] = recvData.ReadBit();
	petguid[4] = recvData.ReadBit();

	recvData.ReadByteSeq(petguid[6]);
	recvData.ReadByteSeq(petguid[2]);
	recvData.ReadByteSeq(petEntry[5]);
	recvData.ReadByteSeq(petguid[4]);
	recvData.ReadByteSeq(petguid[3]);
	recvData.ReadByteSeq(petguid[5]);
	recvData.ReadByteSeq(petEntry[1]);
	recvData.ReadByteSeq(petguid[7]);
	recvData.ReadByteSeq(petEntry[6]);
	recvData.ReadByteSeq(petEntry[3]);
	recvData.ReadByteSeq(petEntry[0]);
	recvData.ReadByteSeq(petEntry[4]);
	recvData.ReadByteSeq(petEntry[7]);
	recvData.ReadByteSeq(petEntry[5]);
	recvData.ReadByteSeq(petguid[0]);
	recvData.ReadByteSeq(petguid[1]);


	Unit* tempUnit = sObjectAccessor->GetUnit(*_player, petguid);
	if (!tempUnit)
	{
		sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_BATTLE_PET_QUERY_NAME - Player %u queried the name of Battle Pet %lu which doesnt't exist in world!",
			GetPlayer()->GetGUIDLow(), (uint64)petEntry);
		return;
	}

	Minion* minion = static_cast<Minion*>(tempUnit->ToTempSummon());
	if (!minion)
		return;

	Unit* owner = minion->GetOwner();
	BattlePet::PetTemplate* proto = nullptr;

	if (Player* player = owner->ToPlayer())
	{
		BattlePet::PetJournal* journal = player->GetPetJournal();
		proto = journal->GetBattlePet(petEntry);
	}
	else
		proto = minion->GetBattlePetTemplate();

	if (!proto)
		return;

	BattlePetSpeciesEntry const* speciesEntry = sBattlePetSpeciesStore.LookupEntry(proto->GetSpecies());
	DeclinedName const* petDeclinedNames = proto->GetDeclinedNames();

	WorldPacket data(SMSG_BATTLE_PET_QUERY_NAME_RESPONSE, 8 + 4 + 4 + 5 + proto->GetNickname().size());
	data << uint64(petEntry);
	data << uint32(proto->GetTimestamp());
	data << uint32(speciesEntry->NpcId);
	data.WriteBit(1);               // has names
	data.WriteBits(proto->GetNickname().size(), 8);

	for (uint8 i = 0; i < MAX_DECLINED_NAME_CASES; i++)
	{
		if (petDeclinedNames)
			data.WriteBits(petDeclinedNames->name[i].size(), 7);
		else
			data.WriteBits(0, 7);
	}

	data.WriteBit(0);               // allowed?

	data.WriteString(proto->GetNickname());

	for (uint8 i = 0; i < MAX_DECLINED_NAME_CASES; i++)
	{
		if (petDeclinedNames && petDeclinedNames->name[i].size())
			data.WriteString(petDeclinedNames->name[i]);
	}

	SendPacket(&data);
}

void WorldSession::HandleBattlePetSetBattleSlot(WorldPacket& recvData)
{
	sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_BATTLE_PET_SET_BATTLE_SLOT");

	uint8 slot;
	ObjectGuid petEntry;

	recvData >> slot;

	petEntry[4] = recvData.ReadBit();
	petEntry[3] = recvData.ReadBit();
	petEntry[0] = recvData.ReadBit();
	petEntry[5] = recvData.ReadBit();
	petEntry[1] = recvData.ReadBit();
	petEntry[7] = recvData.ReadBit();
	petEntry[6] = recvData.ReadBit();
	petEntry[2] = recvData.ReadBit();

	recvData.ReadByteSeq(petEntry[2]);
	recvData.ReadByteSeq(petEntry[1]);
	recvData.ReadByteSeq(petEntry[0]);
	recvData.ReadByteSeq(petEntry[3]);
	recvData.ReadByteSeq(petEntry[5]);
	recvData.ReadByteSeq(petEntry[7]);
	recvData.ReadByteSeq(petEntry[6]);
	recvData.ReadByteSeq(petEntry[4]);

	BattlePet::PetJournal* journal = GetPlayer()->GetPetJournal();

	BattlePet::PetTemplate* battlePet = journal->GetBattlePet(petEntry);
	if (!battlePet)
	{
		sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_BATTLE_PET_SET_BATTLE_SLOT - Player %u tryed to add Battle Pet %lu to loadout which it doesn't own!",
			GetPlayer()->GetGUIDLow(), (uint64)petEntry);
		return;
	}

	if (!journal->LoadoutSlotIsUnlocked(slot))
	{
		sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_BATTLE_PET_SET_BATTLE_SLOT - Player %u tryed to add Battle Pet %lu into slot %u which is locked!",
			GetPlayer()->GetGUIDLow(), (uint64)petEntry, slot);
		return;
	}

	// this check is also done clientside
	if (battlePet->HasSpeciesFlag(BATTLE_PET_FLAG_COMPANION))
	{
		sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_BATTLE_PET_SET_BATTLE_SLOT - Player %u tryed to add a compainion Battle Pet %lu into slot %u!",
			GetPlayer()->GetGUIDLow(), (uint64)petEntry, slot);
		return;
	}

	// sever handles slot swapping, find source slot and replace it with the destination slot
	uint8 srcSlot = journal->GetLoadoutSlotForBattlePet(petEntry);
	if (srcSlot != BATTLE_PET_LOADOUT_SLOT_NONE)
		journal->SetLoadoutSlot(srcSlot, journal->GetLoadoutSlot(slot));

	journal->SetLoadoutSlot(slot, petEntry);
}

enum BattlePetFlagModes
{
	BATTLE_PET_FLAG_MODE_UNSET = 0,
	BATTLE_PET_FLAG_MODE_SET = 1
};

void WorldSession::HandleBattlePetSetFlags(WorldPacket& recvData)
{
	sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_BATTLE_PET_SET_FLAGS");

	ObjectGuid petEntry;
	uint32 flag;

	recvData >> flag;

	uint8 mode = recvData.ReadBits(2);

	petEntry[5] = recvData.ReadBit();
	petEntry[7] = recvData.ReadBit();
	petEntry[3] = recvData.ReadBit();
	petEntry[4] = recvData.ReadBit();
	petEntry[6] = recvData.ReadBit();
	petEntry[0] = recvData.ReadBit();
	petEntry[1] = recvData.ReadBit();
	petEntry[2] = recvData.ReadBit();

	recvData.ReadByteSeq(petEntry[6]);
	recvData.ReadByteSeq(petEntry[1]);
	recvData.ReadByteSeq(petEntry[3]);
	recvData.ReadByteSeq(petEntry[7]);
	recvData.ReadByteSeq(petEntry[4]);
	recvData.ReadByteSeq(petEntry[2]);
	recvData.ReadByteSeq(petEntry[0]);
	recvData.ReadByteSeq(petEntry[5]);

	BattlePet::PetTemplate* battlePet = GetPlayer()->GetPetJournal()->GetBattlePet(petEntry);
	if (!battlePet)
	{
		sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_BATTLE_PET_SET_FLAGS - Player %u tryed to set the flags for Battle Pet %lu which it doesn't own!",
			GetPlayer()->GetGUIDLow(), (uint64)petEntry);
		return;
	}

	// list of flags the client can currently change
	if (flag != BATTLE_PET_JOURNAL_FLAG_FAVORITES
		&& flag != BATTLE_PET_JOURNAL_FLAG_ABILITY_1
		&& flag != BATTLE_PET_JOURNAL_FLAG_ABILITY_2
		&& flag != BATTLE_PET_JOURNAL_FLAG_ABILITY_3)
	{
		sLog->outDebug(LOG_FILTER_NETWORKIO, "CMSG_BATTLE_PET_SET_FLAGS - Player %u tryed to set an invalid Battle Pet flag %u!",
			GetPlayer()->GetGUIDLow(), flag);
		return;
	}

	// TODO: check if Battle Pet is correct level for ability

	switch (mode)
	{
	case BATTLE_PET_FLAG_MODE_SET:
		battlePet->SetFlag(flag);
		break;
	case BATTLE_PET_FLAG_MODE_UNSET:
		battlePet->UnSetFlag(flag);
		break;
	}
}

void WorldSession::HandleBattlePetStartPvPMatchMaking(WorldPacket& /*recv*/){	
	sLFBMgr->Join(GetPlayer());
}

void WorldSession::HandleBattlePetStopPvPMatchMaking(WorldPacket& recv)
{	
	sLFBMgr->Leave(GetPlayer());
}

void WorldSession::HandleBattlePetAcceptPvpMatchMaking(WorldPacket& recv)
{
	bool result = recv.ReadBit();	
	sLFBMgr->UpdateProposal(GetPlayer()->GetGUID(), result);
}

void WorldSession::HandlePetBattleAction(WorldPacket& recv)
{
	BattlePet::ActionInfo action;	
	bool hasActionArg0 = !recv.ReadBit();
	action.m_unkBit = !recv.ReadBit();
	bool hasActionArg1 = !recv.ReadBit();
	bool unkbit4 = !recv.ReadBit();
	bool hasAction = !recv.ReadBit();
	bool hasActionIndex = !recv.ReadBit();
	bool unkbit7 = !recv.ReadBit();

	uint8 unk7 = 0;
	uint8 unk4 = 0;
	if (hasActionArg1)
		action.m_petIndex = recv.read<uint8>();
	if (hasAction)
		recv >> action.m_action;
	if (hasActionIndex)
		recv >> action.m_index;
	if (hasActionArg0)
		recv >> action.m_abilityId;
	if (unkbit7)
		recv >> unk7;
	if (unkbit4)
		recv >> unk4;

	if (GetPlayer() && GetPlayer()->GetPetBattle())
		GetPlayer()->GetPetBattle()->HandleAction(GetPlayer(), &action);
}

void WorldSession::HandlePetBattleSetActivePet(WorldPacket& recv)
{
	uint8 unkVal;
	recv >> unkVal;	
	BattlePet::Battle* battle = GetPlayer()->GetPetBattle();
	if (!battle)
		return;

	battle->InitialMember(GetPlayer());
}

void WorldSession::HandlePetBattleEnd(WorldPacket& recv)
{
	if (this->PlayerLogout())
		return;
	
	WorldPacket data(SMSG_PET_BATTLE_END);
	SendPacket(&data);

	sLFBMgr->FinishBattle(GetPlayer());
}

void WorldSession::SendPetBattleCreateError(PetBattleCreateResult result)
{
	WorldPacket data(SMSG_PET_BATTLE_CREATE_ERROR, 5);	
	data.WriteBit(result == PetBattleCreateResult::PET_BATTLE_CREATE_ERROR);
	if (result != PetBattleCreateResult::PET_BATTLE_CREATE_ERROR)
		data << uint8(result);
	SendPacket(&data);
}

PetBattleCreateResult WorldSession::CheckIsPetBattleAvailable()
{
	//PET_BATTLE_CREATE_ALREADY_CREATED
	
	if (!GetPlayer()->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_BATTLE_PET_ENABLED))
		return PetBattleCreateResult::PET_BATTLE_CREATE_INCORRECT_PLAYER_TARGET;

	if (GetPlayer()->isInCombat())
		return PetBattleCreateResult::PET_BATTLE_CREATE_IN_COMBAT;

	if (GetPlayer()->IsMounted())
		return PetBattleCreateResult::PET_BATTLE_CREATE_MOUNT;

	if (GetPlayer()->IsFlying())
		return PetBattleCreateResult::PET_BATTLE_CREATE_FLYING;

	uint8 pets = 0;
	uint8 alivePets = 0;
	
	BattlePet::PetJournal const* journal = GetPlayer()->GetPetJournal();	
	
	for (uint8 i = 0; i < BATTLE_PET_MAX_LOADOUT_SLOTS; ++i)
	{
		uint64 id = journal->GetLoadoutSlot(i);				
		
		if (pets > 0 && alivePets > 0)
			break;

		if (id == 0)
			continue;

		BattlePet::PetTemplate const* proto = journal->GetBattlePet(id);		
		if (!proto)
			continue;		
		++pets;

		if (!proto->IsPetAvailableForBattle())
			continue;
		
		++alivePets;
	}	

	if (pets == 0)
		return PetBattleCreateResult::PET_BATTLE_CREATE_NO_PET_IN_SLOTS_2;

	if (alivePets == 0)
		return PetBattleCreateResult::PET_BATTLE_CREATE_PETS_DIED;

	return PetBattleCreateResult::PET_BATTLE_CREATE_OK;
}

void WorldSession::HandleBattlePetStartPvPDuel(WorldPacket& recv)
{
	if (this->PlayerLogout())
		return;
	
	BattlePet::PositionData pos;	
	for (uint8 i = 0; i < PET_BATTLE_OPPONENT_COUNT; ++i)
	{
		G3D::Vector3& initialPosition = pos.m_positions[i];

		recv >> initialPosition.z >> initialPosition.x >> initialPosition.y;
	}

	G3D::Vector3& center = pos.m_center;
	recv >> center.x >> center.y >> center.z;

	bool hasPetOrientation = !recv.ReadBit();

	ObjectGuid opponent;

	opponent[3] = recv.ReadBit();
	opponent[0] = recv.ReadBit();
	opponent[2] = recv.ReadBit();
	opponent[7] = recv.ReadBit();
	opponent[6] = recv.ReadBit();
	opponent[5] = recv.ReadBit();
	opponent[1] = recv.ReadBit();
	opponent[4] = recv.ReadBit();

	bool hasStatus = !recv.ReadBit();
	int32 status = 0;

	recv.ReadByteSeq(opponent[4]);
	recv.ReadByteSeq(opponent[5]);
	recv.ReadByteSeq(opponent[7]);
	recv.ReadByteSeq(opponent[0]);
	recv.ReadByteSeq(opponent[3]);
	recv.ReadByteSeq(opponent[2]);
	recv.ReadByteSeq(opponent[1]);
	recv.ReadByteSeq(opponent[6]);

	if (hasStatus)
		recv >> status;

	if (hasPetOrientation)
		recv >> pos.m_orientation;

	Player* opponentPlayer = sObjectAccessor->FindPlayer(opponent);
	if (!opponentPlayer)
	{
		SendPetBattleCreateError(PetBattleCreateResult::PET_BATTLE_CREATE_INCORRECT_PLAYER_TARGET);
		return;
	}

	if (status == 4)
	{
		SendPetBattleCreateError(PetBattleCreateResult::PET_BATTLE_CREATE_SURFACE);
		return;
	}

	if (GetPlayer()->GetMapId() != opponentPlayer->GetMapId())
	{
		SendPetBattleCreateError(PetBattleCreateResult::PET_BATTLE_CREATE_INCORRECT_PLAYER_TARGET);
		return;
	}

	if (!GetPlayer()->IsWithinDist(opponentPlayer, 10.0f))
	{
		SendPetBattleCreateError(PetBattleCreateResult::PET_BATTLE_CREATE_TARGET_OUT_OF_RANGE);
		return;
	}

	PetBattleCreateResult initResult = CheckIsPetBattleAvailable();
	if (initResult != PetBattleCreateResult::PET_BATTLE_CREATE_OK)
	{
		SendPetBattleCreateError(initResult);
		return;
	}

	PetBattleCreateResult oppResult = opponentPlayer->GetSession()->CheckIsPetBattleAvailable();
	if (oppResult != PetBattleCreateResult::PET_BATTLE_CREATE_OK)
	{
		SendPetBattleCreateError(PetBattleCreateResult::PET_BATTLE_CREATE_ERROR);
		return;
	}

	status = 0;

	ObjectGuid guid = GetPlayer()->GetGUID();
	WorldPacket data(SMSG_BATTLE_PET_START_PVP_DUEL_REQUEST);
	data.WriteBit(guid[4]);
	data.WriteBit(status == 0);
	data.WriteBit(guid[2]);
	data.WriteBit(guid[5]);
	data.WriteBit(guid[7]);
	data.WriteBit(guid[3]);
	data.WriteBit(guid[6]);
	data.WriteBit(guid[0]);
	data.WriteBit(guid[1]);
	data.WriteBit(G3D::fuzzyEq(pos.m_orientation, 0.0f));
	if (!G3D::fuzzyEq(pos.m_orientation, 0.0f))
		data << float(pos.m_orientation);

	data.WriteByteSeq(guid[1]);
	data << float(pos.m_center.y);
	data.WriteByteSeq(guid[0]);
	data.WriteByteSeq(guid[5]);
	data << float(pos.m_center.z);
	if (status != 0)
		data << uint32(status);

	data.WriteByteSeq(guid[2]);
	for (G3D::Vector3 const& vect : pos.m_positions)
	{
		data << vect.z << vect.y << vect.x;
	}

	data << float(pos.m_center.x);
	data.WriteByteSeq(guid[7]);
	data.WriteByteSeq(guid[3]);
	data.WriteByteSeq(guid[4]);
	data.WriteByteSeq(guid[6]);		
	opponentPlayer->SendDirectMessage(&data);
}

void WorldSession::HandleBattlePetAcceptPvPDuel(WorldPacket& recv)
{
	ObjectGuid initiator;

	initiator[0] = recv.ReadBit();
	initiator[2] = recv.ReadBit();
	initiator[4] = recv.ReadBit();
	initiator[5] = recv.ReadBit();
	initiator[7] = recv.ReadBit();
	initiator[6] = recv.ReadBit();
	initiator[3] = recv.ReadBit();
	bool result = !recv.ReadBit();
	initiator[1] = recv.ReadBit();

	recv.ReadByteSeq(initiator[7]);
	recv.ReadByteSeq(initiator[2]);
	recv.ReadByteSeq(initiator[3]);
	recv.ReadByteSeq(initiator[1]);
	recv.ReadByteSeq(initiator[5]);
	recv.ReadByteSeq(initiator[4]);
	recv.ReadByteSeq(initiator[0]);
	recv.ReadByteSeq(initiator[6]);
	
	Player* player = sObjectAccessor->FindPlayer(initiator);	
	if (player)
	{				
		if (result)
		{			
			BattlePet::Battle::CreateBattle(player, GetPlayer());
		}
		else{			
			player->GetSession()->SendPetBattleCreateError(PetBattleCreateResult::PET_BATTLE_CREATE_REJECT);
		}			
	}
}