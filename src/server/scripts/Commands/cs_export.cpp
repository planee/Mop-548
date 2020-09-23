/* ScriptData
Name: export_Commandscript
%Complete: 27%
Comment: Export development command
Category: Development tools
Author: Eddard and Mayor
EndScriptData */
// para organizarlo usar std::stew

#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "Chat.h"
#include <stdlib.h>
#include <atltime.h>

/*#####
# CommadExport Main Class
#####*/

class CommadExportHelper
{
	public:
		/*#####
		# GetIntemName by entry
		#####*/
		std::string GetIntemName(uint32 item_entry, bool validate)
		{
			//Check if is on template
			if (ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(item_entry))
			{
				if (itemProto->Name1.size() > 0)
					return itemProto->Name1;
				else
					return "";
			}
			else
				if (validate)
				{
					if (ItemEntry const* dbcItem = sItemStore.LookupEntry(item_entry))
						return "THIS ITEM IS JUST VISUAL, DONT HAVE TEMPLATE";
					else
						return "THIS ITEM DONT EXIST";
				}
				else
					return "";
		}
		/*#####
		# GetItemLevel by entry
		#####*/
		std::ostringstream GetItemLevel(uint32 item_entry)
		{
			std::ostringstream ItemLevelString;
			//Check if is on template
			if (ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(item_entry))
			{
				ItemLevelString << itemProto->ItemLevel;
				return ItemLevelString;
			}	
			else
			{
				ItemLevelString << "THIS ITEM DONT EXIST";
				return ItemLevelString;
			}
    	}
		/*#####
		# GetRequiredLevel by entry
		#####*/
		std::ostringstream GetRequiredLevel(uint32 item_entry)
		{
			std::ostringstream RequiredLevelString;
			//Check if is on template
			if (ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(item_entry))
			{
				RequiredLevelString << itemProto->RequiredLevel;
				return RequiredLevelString;
			}	
			else
			{
				RequiredLevelString << "THIS ITEM DONT EXIST";
				return RequiredLevelString;
			}
		}
		/*#####
		# GetQuestNameByEntry by entry
		#####*/
		std::string GetQuestNameByEntry(uint32 quest_entry)
		{
			/*Check if quest_entry exist*/
			if (Quest const* quetProto = sObjectMgr->GetQuestTemplate(quest_entry))
				return quetProto->GetTitle();
			else
				return "THIS QUEST DONT EXITS ON DB";
		}
		/*#####
		# GetQuestMinLevel by entry
		#####*/
		uint32 GetQuestMinLevel(uint32 quest_Min_level)
		{
			/*Check if quest_entry exist*/
			if (Quest const* questProtolevel = sObjectMgr->GetQuestTemplate(quest_Min_level))
				return questProtolevel->GetMinLevel();
			else
				return 0;
		}
		/*#####
		# GetQuestRequiredSkill This is for know what profession the quest is
		#####*/
		uint32 GetQuestRequiredSkill(uint32 quest_required_skill)
		{
			/*Check if quest_entry exist*/
			if (Quest const* questProtolevel = sObjectMgr->GetQuestTemplate(quest_required_skill))
				return questProtolevel->GetRequiredSkill();
			else
				return 0;
		}
		/*#####
		# GetSpellNameByEntry by entry
		#####*/
		std::string GetSpellNameByEntry(uint32 spellId)
		{
			/*Check if Spell ID exist*/
			if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spellId))
				return spellInfo->SpellName;
			else
				return "THIS SPELL DONT EXIST";
		}
		/*#####
		# GetSkillNameByEntry by ID
		#####*/
		std::string GetSkillNameByEntry(uint32 skillID)
		{
			if(SkillLineEntry const* skillInfo = sSkillLineStore.LookupEntry(skillID))
				return skillInfo->name;
			else
				return "THIS SKILL DONT EXIST";
		}
		
		/*#####
		# GetMapName
		#####*/
		std::string GetMapName(uint32 MapName)
		{
			if(MapEntry const* mapInfo = sMapStore.LookupEntry(MapName))
				return mapInfo->name;
			else
				return "THIS MAP DONT EXIST";
		}
		/*#####
		# Get Area and Zone Name by ID
		#####*/
		std::string GetZoneOrAreaName(uint32 ID)
		{
			if( AreaTableEntry const* areaEntry = GetAreaEntryByAreaID(ID))
				return areaEntry->area_name;
			else
				return "THIS ZONE OR AREA DONT EXIST";
		}
		/*#####
		# Get GetItemQuality by Entry
		#####*/
		enum Quality
		{
			GREY_POOR	         = 0,
			WAIHT_COMMON         = 1,
			GREEN_UNCOMMON       = 2,
			BLUE_RARE            = 3,
			PURPULE_EPIC         = 4,
			ORANGE_LEGENDARY     = 5,
			RED_ARTIFACT         = 6,
			GOLD_HEIRLOOM        = 7
		};
		/* Function GetItemQuality */
		std::string GetItemQuality(uint32 item_entry)
		{
			if(ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(item_entry))
			{
				switch (itemProto->Quality)
				{
					case GREY_POOR:
						return "GREY_POOR       ";
						break;
					case WAIHT_COMMON:
						return "WAIHT_COMMON    ";
						break;
					case GREEN_UNCOMMON: 
						return "GREEN_UNCOMMON  ";
						break;
					case BLUE_RARE:
						return "BLUE_RARE       ";
						break;
					case PURPULE_EPIC:
						return "PURPULE_EPIC    ";
						break;
					case ORANGE_LEGENDARY:
						return "ORANGE_LEGENDARY";
						break;
					case RED_ARTIFACT:
						return "RED_ARTIFACT    ";
						break;
					case GOLD_HEIRLOOM:
						return "GOLD_HEIRLOOM   ";
						break;
					default:
						return "<unknown>      ";
						break;
				}
			}
			else
				return "<unknown>";
		}
		/*#####
		# Get Area and Zone by Position
		#####*/
		uint32 GetZoneOrAreaID(uint32 map, float position_x, float position_y, float position_z, bool zoneOrArea)
		{
			if(sMapMgr->IsValidMapCoord(map ,position_x, position_y, position_z))
			{
				/* True for Zone, False for Area */
				if (zoneOrArea)
				{
					uint32 ZoneId = sMapMgr->GetZoneId(map ,position_x, position_y, position_z);
					return ZoneId;
				}
				else
				{
					uint32 AreaId = sMapMgr->GetAreaId(map ,position_x, position_y, position_z);
					return AreaId;
				}
			}
			else
				return (int)"ERROR";
		}
	private:
		/*Export Data*/
		std::ostringstream dump_data;
		std::ostringstream fileName;
};

/*#####
# Export Creature
#####*/

class CommandExportCreature : public CommadExportHelper
{
private:
	ChatHandler* fHandler;
	std::ostringstream fCacheStream;

public:
	/// Author: 
	/// <summary>
	/// Sustituye los caracteres en una cadena string
	/// </summary>
	/// <param name="aInput">Cadena de entrada.</param>
	/// <return>Cadena con los caracteres sustituidos.</return>
	std::string CheckScapeChar(std::string &aInput, std::string &aScapeChar)
	{
		//
		std::ostringstream _aFirst;
		/* Check for scape characters */
		int _Start = 0, _Index;
		do {
			std::string _Aux;
			_Index = aInput.find(aScapeChar, _Start);
			if (_Index != std::string::npos)
			{
				_Aux = aInput.substr(_Start, _Index - _Start);
				_aFirst << _Aux << "";
				_Start = _Index + 1;
			}
			else
			{
				_Aux = aInput.substr(_Start, aInput.length() - _Start);
				_aFirst << _Aux;
			}
		} while (_Index != std::string::npos);
		/* Return Value */
		return _aFirst.str();
	}
	/// Author: 
	/// <summary>
	/// Sustituye los caracteres no permitidos por el sistema operativo
	/// </summary>
	/// <param name="aInput">Cadena de entrada.</param>
	/// <return>Cadena con los caracteres sustituidos.</return>
	std::string CheckName(std::string &aInput)
	{
		//
		std::string _scape[] = { "\\", "/", ":", "*", "?", "<", ">", "|", "\"" };
		//
		std::string _aInput = aInput;
		//
		for (auto itr : _scape)
		{
			_aInput = CheckScapeChar(_aInput, itr);
		}
		/* Return Value */
		return _aInput;
	}
	/// Author: 
	/// <summary>
	/// Sustituye los caracteres ', " por \', \" respectivamente
	/// </summary>
	/// <param name="aInput">Cadena de entrada.</param>
	/// <return>Cadena con los caracteres sustituidos.</return>
	std::string SafeSQLParams(std::string &aInput)
		{
			std::ostringstream _aFirst;
			std::ostringstream _aSecond;
			/* Check for ' */
			int _Start = 0, _Index;
			do {
				std::string _Aux;
				_Index = aInput.find('\'', _Start);
				if (_Index != std::string::npos)
				{
					_Aux = aInput.substr(_Start, _Index - _Start);
					_aFirst <<_Aux << "\\'"; 
					_Start = _Index + 1;
				} else
				{
					_Aux = aInput.substr(_Start, aInput.length() - _Start);
					_aFirst <<_Aux;
				}
			} while(_Index != std::string::npos);
			/* Check for " */
			_Start = 0;
			do {
				std::string _Aux;
				_Index = _aFirst.str().find('\"', _Start);
				if (_Index != std::string::npos)
				{
					_Aux = _aFirst.str().substr(_Start, _Index - _Start);
					_aSecond <<_Aux << "\\\""; 
					_Start = _Index + 1;
				} else
				{
					_Aux = _aFirst.str().substr(_Start, _aFirst.str().length() - _Start);
					_aSecond <<_Aux;
				}
			} while(_Index != std::string::npos);
			/* Return Value */
			return _aSecond.str();
		}
	/// Author: 
	/// <summary>
	/// Sustituye los caracteres ', " por \', \" respectivamente
	/// </summary>
	/// <param name="aInput">Cadena de entrada.</param>
	/// <return>Cadena con los caracteres sustituidos.</return>
	std::string SafeSQLParamsExt(std::string aInput)
	{
		std::ostringstream _aFirst;
		std::ostringstream _aSecond;
		/* Check for ' */
		int _Start = 0, _Index;
		do {
			std::string _Aux;
			_Index = aInput.find('\'', _Start);
			if (_Index != std::string::npos)
			{
				_Aux = aInput.substr(_Start, _Index - _Start);
				_aFirst << _Aux << "\\'";
				_Start = _Index + 1;
			}
			else
			{
				_Aux = aInput.substr(_Start, aInput.length() - _Start);
				_aFirst << _Aux;
			}
		} while (_Index != std::string::npos);
		/* Check for " */
		_Start = 0;
		do {
			std::string _Aux;
			_Index = _aFirst.str().find('\"', _Start);
			if (_Index != std::string::npos)
			{
				_Aux = _aFirst.str().substr(_Start, _Index - _Start);
				_aSecond << _Aux << "\\\"";
				_Start = _Index + 1;
			}
			else
			{
				_Aux = _aFirst.str().substr(_Start, _aFirst.str().length() - _Start);
				_aSecond << _Aux;
			}
		} while (_Index != std::string::npos);
		/* Return Value */
		return _aSecond.str();
	}
private:
	/// Author: 
	/// <summary>
	/// Escribe en un fichero el valor existente en la cache de exportación.
	/// </summary>
	/// <param name="aInput">Cadena de entrada.</param>
	/// <return>Cadena con los caracteres sustituidos.</return>
	void FlushToFile(std::string &aFileName, int aEntry, std::string &aCreatureName)
	{
		time_t _CurTime = time(NULL);

		CTime _CTime(_CurTime);
		tm _LocalTm = *localtime(&_CurTime);
		std::ostringstream _ExportHeader;

		_ExportHeader 
			<< "/*\n" 
			<< "SQL ZONAXTREMA 				  \n"
			<< "Desarrollado por:\n"
			<< "Fecha: " << _CTime.GetDay() << "/" << _CTime.GetMonth() << "/" << _CTime.GetYear() << "\n"
			<< "### Scripts Trabajados por ZONAXTREMA  ########\n" 
			<< "### Datos SQL ###########################################*/\n" 
			<< "SET @CREATURE  	:= '" << this->SafeSQLParams(aCreatureName) << "';\n" 
			<< "SET @ENTRY 		:= '" << aEntry << "';\n" 
			<< "/*SET @MAP   		:= 530;       *//*(Outland)*/\n"
			<< "/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/\n"
			<< "/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/\n"
			<< "/*#######################################################*/\n"
			<< "\n";
		
		FILE* fout = fopen(aFileName.c_str(), "w");
		fprintf(fout, "%s\n", _ExportHeader.str().c_str());
		fprintf(fout, "%s\n", this->fCacheStream.str().c_str());
		fclose(fout);
	}


	/// Author: Boris Cabrera
	/// <summary>
	/// Exportar todo lo referente a la tabla gameobject_involvedrelation
	/// </summary>
	/// <param name="aGAmeObjectId">.</param> 
	/// <param name="aQuestId">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportGameObjectInvolvedRelation(uint32 aGAmeObjectId, uint32 aQuestId) 
	{
		QueryResult _Result;
		uint32 _rowCount = 1;

		if(aGAmeObjectId != 0 && aQuestId == 0)
		{
			_Result = WorldDatabase.PQuery(
				"SELECT  "
				"`id`,  "
				"`quest` "
				"FROM `gameobject_involvedrelation` WHERE id = '%u';", aGAmeObjectId);

			//Add the delete	
			this->fCacheStream 
				<< "/* Step 2.2 Table  `gameobject_involvedrelation */\n"
				//<< "DELETE FROM  `gameobject_involvedrelation` WHERE `id`= " << aGAmeObjectId << ";\n";
				<< "DELETE FROM  `gameobject_involvedrelation` WHERE `id`= " << "@ENTRY" << ";\n";

		} else if (aGAmeObjectId == 0 && aQuestId != 0)
		{
			 _Result = WorldDatabase.PQuery(
				"SELECT  "
				"`id`,  "
				"`quest` "
				"FROM `gameobject_involvedrelation` WHERE quest = '%u';", aQuestId);

			 //Add the delete
			 this->fCacheStream 
				<< "/* Step 2.2 Table  `gameobject_involvedrelation */\n"
				<< "DELETE FROM  `gameobject_involvedrelation` WHERE `quest`= " << aQuestId << ";\n";
		} else
		{
			return false;
		}

		if (_Result)
		{
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 id      = _Fields[_Index++].GetUInt32();
				uint32 quest   = _Fields[_Index++].GetUInt32();

				if (_rowCount == 1)
				{
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `gameobject_involvedrelation` ("
						<< "`id`, "
						<< "`quest`) VALUES \n";
				}

				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << id << "',"
					<< " '" << quest << "')";

				//
				// 
				if (_Result->GetRowCount() == _rowCount)
					this->fCacheStream << "; ";
				else
					this->fCacheStream << ", ";
				
				//
				// Solo como comentario
				this->fCacheStream << " /* " << "Quest(" << quest << "): " << this->GetQuestNameByEntry(quest) <<" ,QuestMinLevel: " << this->GetQuestMinLevel(quest) <<" ,QuestProfession ID: " << this->GetQuestRequiredSkill(quest) << "[" << this->GetSkillNameByEntry(GetQuestRequiredSkill(quest)) << "]" << " */ \n";
				_rowCount++;
			} while (_Result->NextRow());
			
			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de un gobject.
			this->fHandler->PSendSysMessage("    gameobject_involvedrelation exported.");
		} else
			return false;
		return true;
	}
	/// Author: Boris Cabrera
	/// <summary>
	/// Exportar todo lo referente a la tabla quest_poi
	/// </summary>
	/// <param name="aquestId">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportQuestPoi(uint32 aquestId)
	{
		QueryResult _Result = WorldDatabase.PQuery(
			"SELECT * FROM `quest_poi` WHERE `questId` = '%u';", aquestId);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 3.4 Table  `quest_poi` */\n"
			<< "DELETE FROM  `quest_poi` WHERE `questId` = " << aquestId << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 questId            = _Fields[_Index++].GetUInt32();
				uint32 id                 = _Fields[_Index++].GetUInt32();
				int32  objIndex           = _Fields[_Index++].GetInt32();
				uint32 mapid              = _Fields[_Index++].GetUInt32();
				uint32 WorldMapAreaId     = _Fields[_Index++].GetUInt32();
				uint32 unk2               = _Fields[_Index++].GetUInt32();
				uint32 unk3               = _Fields[_Index++].GetUInt32();
				uint32 unk4               = _Fields[_Index++].GetUInt32();
				uint32 FloorId            = _Fields[_Index++].GetUInt32();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `quest_poi` ("
						<< "`questId`, "
						<< "`id`, "
						<< "`objIndex`, "
						<< "`mapid`, "
						<< "`WorldMapAreaId`, "
						<< "`unk2`, "
						<< "`unk3`, "
						<< "`unk4`, "
						<< "`FloorId`) VALUES \n";
				} else
					this->fCacheStream << ", \n";
				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << questId << "',"
					<< " '" << id << "',"
					<< " '" << objIndex << "',"
					<< " '" << mapid << "',"
					<< " '" << WorldMapAreaId << "',"
					<< " '" << unk2 << "',"
					<< " '" << unk3 << "',"
					<< " '" << unk4 << "',"
					<< " '" << FloorId << "')";

				//
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//

			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    quest_poi exported.");
		} else
			return false;
		return true;
	}	

	/// Author: Mayor (Yuri Roque)
	/// <summary>
	/// Exportar todo lo referente a la tabla quest_start_scripts
	/// </summary>
	/// <param name="id">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>

	bool exportQuest_Start_Scripts(uint32 aquestId)
	{
		QueryResult _Result = WorldDatabase.PQuery(
			"SELECT * FROM `quest_start_scripts` WHERE `id` = '%u';", aquestId);

		//Add the delete
		this->fCacheStream
			<< "/* Step Final Table  `quest_start_scripts` */\n"
			<< "DELETE FROM  `quest_start_scripts` WHERE `id` = " << aquestId << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 id = _Fields[_Index++].GetUInt32();
				uint32 delay = _Fields[_Index++].GetUInt32();
				int32  command = _Fields[_Index++].GetInt32();
				uint32 datalong = _Fields[_Index++].GetUInt32();
				uint32 datalong2 = _Fields[_Index++].GetUInt32();
				uint32 dataint = _Fields[_Index++].GetUInt32();
				float x = _Fields[_Index++].GetFloat();
				float y = _Fields[_Index++].GetFloat();
				float z = _Fields[_Index++].GetFloat();
				float o = _Fields[_Index++].GetFloat();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `quest_start_scripts` ("
						<< "`id`, "
						<< "`delay`, "
						<< "`command`, "
						<< "`datalong`, "
						<< "`datalong2`, "
						<< "`dataint`, "
						<< "`x`, "
						<< "`y`, "
						<< "`z`, "
						<< "`o`) VALUES \n";
				}
				else
					this->fCacheStream << ", \n";
				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << id << "',"
					<< " '" << delay << "',"
					<< " '" << command << "',"
					<< " '" << datalong << "',"
					<< " '" << datalong2 << "',"
					<< " '" << dataint << "',"
					<< " '" << x << "',"
					<< " '" << y << "',"
					<< " '" << z << "',"
					<< " '" << 0 << "')";

				//
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//

			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    quest_start_scripts exported.");
		}
		else
			return false;
		return true;
	}
	/// Author: Mayor (Yuri Roque)
	/// <summary>
	/// Exportar todo lo referente a la tabla quest_start_scripts
	/// </summary>
	/// <param name="id">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>

	bool exportQuest_End_Scripts(uint32 aquestId)
	{
		QueryResult _Result = WorldDatabase.PQuery(
			"SELECT * FROM `quest_end_scripts` WHERE `id` = '%u';", aquestId);

		//Add the delete
		this->fCacheStream
			<< "/* Step Final Table  `quest_end_scripts` */\n"
			<< "DELETE FROM  `quest_end_scripts` WHERE `id` = " << aquestId << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 id = _Fields[_Index++].GetUInt32();
				uint32 delay = _Fields[_Index++].GetUInt32();
				int32  command = _Fields[_Index++].GetInt32();
				uint32 datalong = _Fields[_Index++].GetUInt32();
				uint32 datalong2 = _Fields[_Index++].GetUInt32();
				uint32 dataint = _Fields[_Index++].GetUInt32();
				float x = _Fields[_Index++].GetFloat();
				float y = _Fields[_Index++].GetFloat();
				float z = _Fields[_Index++].GetFloat();
				float o = _Fields[_Index++].GetFloat();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `quest_end_scripts` ("
						<< "`id`, "
						<< "`delay`, "
						<< "`command`, "
						<< "`datalong`, "
						<< "`datalong2`, "
						<< "`dataint`, "
						<< "`x`, "
						<< "`y`, "
						<< "`z`, "
						<< "`o`) VALUES \n";
				}
				else
					this->fCacheStream << ", \n";
				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << id << "',"
					<< " '" << delay << "',"
					<< " '" << command << "',"
					<< " '" << datalong << "',"
					<< " '" << datalong2 << "',"
					<< " '" << dataint << "',"
					<< " '" << x << "',"
					<< " '" << y << "',"
					<< " '" << z << "',"
					<< " '" << 0 << "')";

				//
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//

			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    quest_end_scripts Exported.");
		}
		else
			return false;
		return true;
	}
	/// Author: Boris Cabrera
	/// <summary>
	/// Exportar todo lo referente a la tabla quest_poi_points
	/// </summary>
	/// <param name="aquestId">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportQuestPoiPoints(uint32 aquestId)
	{
		QueryResult _Result = WorldDatabase.PQuery(
			"SELECT * FROM `quest_poi_points` WHERE `questId` = '%u'  ORDER BY id ASC, idx ASC;", aquestId);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 3.5 Table  `quest_poi_points` */\n"
			<< "DELETE FROM  `quest_poi_points` WHERE `questId` = " << aquestId << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 questId            = _Fields[_Index++].GetUInt32();
				uint32 id                 = _Fields[_Index++].GetUInt32();
				uint32 idx                = _Fields[_Index++].GetUInt32();
				int32  x                  = _Fields[_Index++].GetInt32();
				int32  y                  = _Fields[_Index++].GetInt32();				

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `quest_poi_points` ("
						<< "`questId`, "
						<< "`id`, "
						<< "`idx`, "
						<< "`x`, "
						<< "`y`) VALUES \n";
				} else
					this->fCacheStream << ", \n";
				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << questId << "',"
					<< " '" << id << "',"
					<< " '" << idx << "',"
					<< " '" << x << "',"
					<< " '" << y << "')";

				//
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//

			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    quest_poi_points exported.");
		} else
			return false;
		return true;
	}
	/// Author: Boris Cabrera
	/// <summary>
	/// Exportar todo lo referente a la tabla gameobject_questrelation
	/// </summary>
	/// <param name="aGAmeObjectId">.</param> 
	/// <param name="aQuestId">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportGameObjectQuestRelation(uint32 aGAmeObjectId, uint32 aQuestId) // Preguntar si se pasa el QuestGiver o el GoEntry
	{
		QueryResult _Result;
		uint32 _rowCount = 1;

		if(aGAmeObjectId != 0 && aQuestId == 0)
		{
			_Result = WorldDatabase.PQuery(
				"SELECT  "
				"`id`,  "
				"`quest` "
				"FROM `gameobject_questrelation` WHERE id = '%u';", aGAmeObjectId);

			//Add the delete
			this->fCacheStream 
				<< "/* Step 2.2 Table  `gameobject_questrelation */\n"
				//<< "DELETE FROM  `gameobject_questrelation` WHERE `id`= " << aGAmeObjectId << ";\n";
				<< "DELETE FROM  `gameobject_questrelation` WHERE `id`= " << "@ENTRY" << ";\n";

		} else if (aGAmeObjectId == 0 && aQuestId != 0)
		{
			 _Result = WorldDatabase.PQuery(
				"SELECT  "
				"`id`,  "
				"`quest` "
				"FROM `gameobject_questrelation` WHERE quest = '%u';", aQuestId);

			 //Add the delete
			 this->fCacheStream 
				<< "/* Step 2.2 Table  `gameobject_questrelation */\n"
				<< "DELETE FROM  `gameobject_questrelation` WHERE `quest`= " << aQuestId << ";\n";

		} else
		{
			return false;
		}

		if (_Result)
		{
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 id      = _Fields[_Index++].GetUInt32();
				uint32 quest   = _Fields[_Index++].GetUInt32();

				if (_rowCount == 1)
				{
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `gameobject_questrelation` ("
						<< "`id`, "
						<< "`quest`) VALUES \n";
				}

				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << id << "',"
					<< " '" << quest << "')";

				//
				// 
				if (_Result->GetRowCount() == _rowCount)
					this->fCacheStream << "; ";
				else
					this->fCacheStream << ", ";
				
				//
				// Solo como comentario
				this->fCacheStream << " /* " << "Quest(" << quest << "): " << this->GetQuestNameByEntry(quest) <<" ,QuestMinLevel: " << this->GetQuestMinLevel(quest) <<" ,QuestProfession ID: " << this->GetQuestRequiredSkill(quest) << "[" << this->GetSkillNameByEntry(GetQuestRequiredSkill(quest)) << "]" << " */ \n";
				_rowCount++;
			} while (_Result->NextRow());
			
			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de un gobject.
			this->fHandler->PSendSysMessage("    gameobject_questrelation exported.");
		} else
			return false;
		return true;
	}
	/// Author: Magus & Boris Cabrera
	/// <summary>
	/// Exportar todo lo referente a la tabla quest_template
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportQuestTemplate(uint32 aEntry, std::string &aQuestName)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `quest_template` WHERE Id = '%u';", aEntry);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 1.1 Table  `quest_template` */\n"
			<< "DELETE FROM  `quest_template` WHERE `Id` = " << aEntry << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
			    uint32	Id                              = _Fields[_Index++].GetUInt32();
                uint32  Method                          = _Fields[_Index++].GetUInt32();
                int32   Level                           = _Fields[_Index++].GetInt32();
                uint32  MinLevel                        = _Fields[_Index++].GetUInt32();
                uint32	MaxLevel                        = _Fields[_Index++].GetUInt32();
                int32	ZoneOrSort                      = _Fields[_Index++].GetInt32();
                uint32	Type	                        = _Fields[_Index++].GetUInt32();
                uint32	SuggestedPlayers                = _Fields[_Index++].GetUInt32();
                uint32	LimitTime	                    = _Fields[_Index++].GetUInt32();
                int32	RequiredTeam	                = _Fields[_Index++].GetInt32();
                int32	RequiredClasses	                = _Fields[_Index++].GetInt32();
                int32	RequiredRaces	                = _Fields[_Index++].GetInt32();
                uint32	RequiredSkillId	                = _Fields[_Index++].GetUInt32();
                uint32	RequiredSkillPoints	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredFactionId1	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredFactionId2	            = _Fields[_Index++].GetUInt32();
                int32	RequiredFactionValue1	        = _Fields[_Index++].GetInt32();
                int32	RequiredFactionValue2	        = _Fields[_Index++].GetInt32();
                uint32	RequiredFactionKills	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredFactionKillsCount	    = _Fields[_Index++].GetUInt32();
                uint32	RequiredPetBattleWith	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredMinRepFaction	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredMaxRepFaction	        = _Fields[_Index++].GetUInt32();
                int32	RequiredMinRepValue	            = _Fields[_Index++].GetInt32();
                int32	RequiredMaxRepValue	            = _Fields[_Index++].GetInt32();
                int32	PrevQuestId	                    = _Fields[_Index++].GetInt32();
                int32	NextQuestId	                    = _Fields[_Index++].GetInt32();
                int32	ExclusiveGroup	                = _Fields[_Index++].GetInt32();
                uint32	NextQuestIdChain	            = _Fields[_Index++].GetUInt32();
                uint32	RewardXPId	                    = _Fields[_Index++].GetUInt32();
                uint32	RewardXPId2	                    = _Fields[_Index++].GetUInt32();
                int32	RewardOrRequiredMoney	        = _Fields[_Index++].GetInt32();
                uint32	RewardMoneyMaxLevel	            = _Fields[_Index++].GetUInt32();
                uint32	RewardSpell	                    = _Fields[_Index++].GetUInt32();
                int32	RewardSpellCast	                = _Fields[_Index++].GetInt32();
                uint32	RewardHonor	                    = _Fields[_Index++].GetUInt32();
                float	RewardHonorMultiplier	        = _Fields[_Index++].GetFloat();
                uint32	RewardMailTemplateId	        = _Fields[_Index++].GetUInt32();
                uint32	RewardMailDelay	                = _Fields[_Index++].GetUInt32();
                uint32	SourceItemId	                = _Fields[_Index++].GetUInt32();
                uint32	SourceItemCount	                = _Fields[_Index++].GetUInt32();
                uint32	SourceSpellId	                = _Fields[_Index++].GetUInt32();
                uint32	Flags	                        = _Fields[_Index++].GetUInt32();
				uint32  Flags2	                        = _Fields[_Index++].GetUInt32();
                uint32	SpecialFlags	                = _Fields[_Index++].GetUInt32();
                uint32	MinimapTargetMark	            = _Fields[_Index++].GetUInt32();
                uint32	RewardTitleId	                = _Fields[_Index++].GetUInt32();
                uint32	RequiredPlayerKills	            = _Fields[_Index++].GetUInt32();
                uint32	RewardTalents	                = _Fields[_Index++].GetUInt32();
                int32	RewardArenaPoints	            = _Fields[_Index++].GetInt32();
                uint32	RewardSkillId	                = _Fields[_Index++].GetUInt32();
                uint32	RewardSkillPoints	            = _Fields[_Index++].GetUInt32();
                uint32	RewardReputationMask	        = _Fields[_Index++].GetUInt32();
                uint32	QuestGiverPortrait	            = _Fields[_Index++].GetUInt32();
				uint32  RewardPackageItemId             = _Fields[_Index++].GetUInt32();
                uint32	QuestTurnInPortrait	            = _Fields[_Index++].GetUInt32();
                uint32	RewardItemId1	                = _Fields[_Index++].GetUInt32();
                uint32	RewardItemId2	                = _Fields[_Index++].GetUInt32();
                uint32	RewardItemId3	                = _Fields[_Index++].GetUInt32();
                uint32	RewardItemId4	                = _Fields[_Index++].GetUInt32();
                uint32	RewardItemCount1	            = _Fields[_Index++].GetUInt32();
                uint32	RewardItemCount2	            = _Fields[_Index++].GetUInt32();
                uint32	RewardItemCount3	            = _Fields[_Index++].GetUInt32();
                uint32	RewardItemCount4	            = _Fields[_Index++].GetUInt32();
                uint32	RewardChoiceItemId1	            = _Fields[_Index++].GetUInt32();
                uint32	RewardChoiceItemId2	            = _Fields[_Index++].GetUInt32();
                uint32	RewardChoiceItemId3	            = _Fields[_Index++].GetUInt32();
                uint32	RewardChoiceItemId4	            = _Fields[_Index++].GetUInt32();
                uint32	RewardChoiceItemId5	            = _Fields[_Index++].GetUInt32();
                uint32	RewardChoiceItemId6	            = _Fields[_Index++].GetUInt32();
                uint32	RewardChoiceItemCount1	        = _Fields[_Index++].GetUInt32();
                uint32	RewardChoiceItemCount2	        = _Fields[_Index++].GetUInt32();
                uint32	RewardChoiceItemCount3	        = _Fields[_Index++].GetUInt32();
                uint32	RewardChoiceItemCount4	        = _Fields[_Index++].GetUInt32();
                uint32	RewardChoiceItemCount5	        = _Fields[_Index++].GetUInt32();
                uint32	RewardChoiceItemCount6	        = _Fields[_Index++].GetUInt32();
                uint32	RewardFactionId1	            = _Fields[_Index++].GetUInt32();
                uint32	RewardFactionId2	            = _Fields[_Index++].GetUInt32();
                uint32	RewardFactionId3	            = _Fields[_Index++].GetUInt32();
                uint32	RewardFactionId4	            = _Fields[_Index++].GetUInt32();
                uint32	RewardFactionId5	            = _Fields[_Index++].GetUInt32();
                uint32	RewardFactionValueId1	        = _Fields[_Index++].GetUInt32();
                uint32	RewardFactionValueId2	        = _Fields[_Index++].GetUInt32();
                uint32	RewardFactionValueId3	        = _Fields[_Index++].GetUInt32();
                uint32	RewardFactionValueId4	        = _Fields[_Index++].GetUInt32();
                uint32	RewardFactionValueId5	        = _Fields[_Index++].GetUInt32();
                uint32	RewardFactionValueIdOverride1	= _Fields[_Index++].GetUInt32();
                uint32	RewardFactionValueIdOverride2	= _Fields[_Index++].GetUInt32();
                uint32	RewardFactionValueIdOverride3	= _Fields[_Index++].GetUInt32();
                uint32	RewardFactionValueIdOverride4	= _Fields[_Index++].GetUInt32();
                uint32	RewardFactionValueIdOverride5	= _Fields[_Index++].GetUInt32();
                uint32	PointMapId	                    = _Fields[_Index++].GetUInt32();
                float	PointX	                        = _Fields[_Index++].GetFloat();
                float	PointY	                        = _Fields[_Index++].GetFloat();
                uint32	PointOption	                    = _Fields[_Index++].GetUInt32();
                std::string	Title	                    = aQuestName = _Fields[_Index++].GetString();
                std::string	Objectives	                = _Fields[_Index++].GetString();
                std::string	Details                 	= _Fields[_Index++].GetString();
                std::string	EndText                 	= _Fields[_Index++].GetString();
                std::string	OfferRewardText	            = _Fields[_Index++].GetString();
                std::string	RequestItemsText	        = _Fields[_Index++].GetString();
                std::string	CompletedText	            = _Fields[_Index++].GetString();
                int32	RequiredNpcOrGo1	            = _Fields[_Index++].GetInt32();
                int32	RequiredNpcOrGo2	            = _Fields[_Index++].GetInt32();
                int32	RequiredNpcOrGo3	            = _Fields[_Index++].GetInt32();
                int32	RequiredNpcOrGo4	            = _Fields[_Index++].GetInt32();
                int32	RequiredNpcOrGo5	            = _Fields[_Index++].GetInt32();
                int32	RequiredNpcOrGo6	            = _Fields[_Index++].GetInt32();
                int32	RequiredNpcOrGo7	            = _Fields[_Index++].GetInt32();
                int32	RequiredNpcOrGo8	            = _Fields[_Index++].GetInt32();
                int32	RequiredNpcOrGo9	            = _Fields[_Index++].GetInt32();
                int32	RequiredNpcOrGo10	            = _Fields[_Index++].GetInt32();
                uint32	RequiredNpcOrGoCount1	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredNpcOrGoCount2	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredNpcOrGoCount3	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredNpcOrGoCount4	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredNpcOrGoCount5	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredNpcOrGoCount6	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredNpcOrGoCount7	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredNpcOrGoCount8	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredNpcOrGoCount9	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredNpcOrGoCount10	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredSourceItemId1	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredSourceItemId2	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredSourceItemId3	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredSourceItemId4	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredSourceItemCount1	    = _Fields[_Index++].GetUInt32();
                uint32	RequiredSourceItemCount2	    = _Fields[_Index++].GetUInt32();
                uint32	RequiredSourceItemCount3	    = _Fields[_Index++].GetUInt32();
                uint32	RequiredSourceItemCount4	    = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemId1	                = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemId2	                = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemId3              	= _Fields[_Index++].GetUInt32();
                uint32	RequiredItemId4	                = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemId5	                = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemId6	                = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemId7              	= _Fields[_Index++].GetUInt32();
                uint32	RequiredItemId8             	= _Fields[_Index++].GetUInt32();
                uint32	RequiredItemId9	                = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemId10	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemCount1	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemCount2	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemCount3	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemCount4	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemCount5	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemCount6	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemCount7	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemCount8	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemCount9	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredItemCount10	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredSpell	                = _Fields[_Index++].GetUInt32();
                uint32	RequiredSpellCast1	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredSpellCast2	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredSpellCast3	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredSpellCast4	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredSpellCast5             	= _Fields[_Index++].GetUInt32();
                uint32	RequiredSpellCast6           	= _Fields[_Index++].GetUInt32();
                std::string	ObjectiveText1	            = _Fields[_Index++].GetString();
                std::string	ObjectiveText2	            = _Fields[_Index++].GetString();
                std::string	ObjectiveText3	            = _Fields[_Index++].GetString();
                std::string	ObjectiveText4	            = _Fields[_Index++].GetString();
                std::string	ObjectiveText5	            = _Fields[_Index++].GetString();
                std::string	ObjectiveText6	            = _Fields[_Index++].GetString();
                std::string	ObjectiveText7	            = _Fields[_Index++].GetString();
                std::string	ObjectiveText8	            = _Fields[_Index++].GetString();
                std::string	ObjectiveText9	            = _Fields[_Index++].GetString();
                std::string	ObjectiveText10	            = _Fields[_Index++].GetString();
                uint32	RewardCurrencyId1	            = _Fields[_Index++].GetUInt32();
                uint32	RewardCurrencyId2	            = _Fields[_Index++].GetUInt32();
                uint32	RewardCurrencyId3	            = _Fields[_Index++].GetUInt32();
                uint32	RewardCurrencyId4	            = _Fields[_Index++].GetUInt32();
                uint32	RewardCurrencyCount1	        = _Fields[_Index++].GetUInt32();
                uint32	RewardCurrencyCount2	        = _Fields[_Index++].GetUInt32();
                uint32	RewardCurrencyCount3	        = _Fields[_Index++].GetUInt32();
                uint32	RewardCurrencyCount4	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredCurrencyId1	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredCurrencyId2	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredCurrencyId3	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredCurrencyId4	            = _Fields[_Index++].GetUInt32();
                uint32	RequiredCurrencyCount1	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredCurrencyCount2	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredCurrencyCount3	        = _Fields[_Index++].GetUInt32();
                uint32	RequiredCurrencyCount4	        = _Fields[_Index++].GetUInt32();
                std::string	QuestGiverTextWindow	    = _Fields[_Index++].GetString();
                std::string	QuestGiverTargetName	    = _Fields[_Index++].GetString();
                std::string	QuestTurnTextWindow	        = _Fields[_Index++].GetString();
                std::string	QuestTurnTargetName      	= _Fields[_Index++].GetString();
                uint32	SoundAccept                 	= _Fields[_Index++].GetUInt32();
                uint32	SoundTurnIn	                    = _Fields[_Index++].GetUInt32();
                uint32	DetailsEmote1	                = _Fields[_Index++].GetUInt32();
                uint32	DetailsEmote2	                = _Fields[_Index++].GetUInt32();
                uint32	DetailsEmote3	                = _Fields[_Index++].GetUInt32();
                uint32	DetailsEmote4	                = _Fields[_Index++].GetUInt32();
                uint32	DetailsEmoteDelay1           	= _Fields[_Index++].GetUInt32();
                uint32	DetailsEmoteDelay2           	= _Fields[_Index++].GetUInt32();
                uint32	DetailsEmoteDelay3             	= _Fields[_Index++].GetUInt32();
                uint32	DetailsEmoteDelay4	            = _Fields[_Index++].GetUInt32();
                uint32	EmoteOnIncomplete	            = _Fields[_Index++].GetUInt32();
                uint32	EmoteOnComplete             	= _Fields[_Index++].GetUInt32();
                uint32	OfferRewardEmote1           	= _Fields[_Index++].GetUInt32();
                uint32	OfferRewardEmote2           	= _Fields[_Index++].GetUInt32();
                uint32	OfferRewardEmote3            	= _Fields[_Index++].GetUInt32();
                uint32	OfferRewardEmote4           	= _Fields[_Index++].GetUInt32();
                uint32	OfferRewardEmoteDelay1	        = _Fields[_Index++].GetUInt32();
                uint32	OfferRewardEmoteDelay2         	= _Fields[_Index++].GetUInt32();
                uint32	OfferRewardEmoteDelay3	        = _Fields[_Index++].GetUInt32();
                uint32	OfferRewardEmoteDelay4	        = _Fields[_Index++].GetUInt32();
                uint32	StartScript	                    = _Fields[_Index++].GetUInt32();
                uint32	CompleteScript	                = _Fields[_Index++].GetUInt32();
                uint32	WDBVerified                 	= _Fields[_Index++].GetUInt32();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `quest_template` (" 
						<<	"`Id`, "
						<<	"`Method`, "
						<<	"`Level`, "
						<<	"`MinLevel`, "
						<<	"`MaxLevel`, "
						<<	"`ZoneOrSort`, "
						<<	"`Type`, "
						<<	"`SuggestedPlayers`, "
						<<	"`LimitTime`, "
						<<	"`RequiredTeam`, "
						<<	"`RequiredClasses`, "
						<<	"`RequiredRaces`, "
						<<	"`RequiredSkillId`, "
						<<	"`RequiredSkillPoints`, "
						<<	"`RequiredFactionId1`, "
						<<	"`RequiredFactionId2`, "
						<<	"`RequiredFactionValue1`, "
						<<	"`RequiredFactionValue2`, "
						<<	"`RequiredFactionKills`, "
						<<	"`RequiredFactionKillsCount`, "
						<<	"`RequiredPetBattleWith`, "
						<<	"`RequiredMinRepFaction`, "
						<<	"`RequiredMaxRepFaction`, "
						<<	"`RequiredMinRepValue`, "
						<<	"`RequiredMaxRepValue`, "
						<<	"`PrevQuestId`, "
						<<	"`NextQuestId`, "
						<<	"`ExclusiveGroup`, "
						<<	"`NextQuestIdChain`, "
						<<	"`RewardXPId`, "
						<<	"`RewardXPId2`, "
						<<	"`RewardOrRequiredMoney`, "
						<<	"`RewardMoneyMaxLevel`, "
						<<	"`RewardSpell`, "
						<<	"`RewardSpellCast`, "
						<<	"`RewardHonor`, "
						<<	"`RewardHonorMultiplier`, "
						<<	"`RewardMailTemplateId`, "
						<<	"`RewardMailDelay`, "
						<<	"`SourceItemId`, "
						<<	"`SourceItemCount`, "
						<<	"`SourceSpellId`, "
						<<	"`Flags`, "
						<<  "`Flags2`, "
						<<	"`SpecialFlags`, "
						<<	"`MinimapTargetMark`, "
						<<	"`RewardTitleId`, "
						<<	"`RequiredPlayerKills`, "
						<<	"`RewardTalents`, "
						<<	"`RewardArenaPoints`, "
						<<	"`RewardSkillId`, "
						<<	"`RewardSkillPoints`, "
						<<	"`RewardReputationMask`, "
						<<	"`QuestGiverPortrait`, "
						<<	"`RewardPackageItemId`, "
						<<	"`QuestTurnInPortrait`, "
						<<	"`RewardItemId1`, "
						<<	"`RewardItemId2`, "
						<<	"`RewardItemId3`, "
						<<	"`RewardItemId4`, "
						<<	"`RewardItemCount1`, "
						<<	"`RewardItemCount2`, "
						<<	"`RewardItemCount3`, "
						<<	"`RewardItemCount4`, "
						<<	"`RewardChoiceItemId1`, "
						<<	"`RewardChoiceItemId2`, "
						<<	"`RewardChoiceItemId3`, "
						<<	"`RewardChoiceItemId4`, "
						<<	"`RewardChoiceItemId5`, "
						<<	"`RewardChoiceItemId6`, "
						<<	"`RewardChoiceItemCount1`, "
						<<	"`RewardChoiceItemCount2`, "
						<<	"`RewardChoiceItemCount3`, "
						<<	"`RewardChoiceItemCount4`, "
						<<	"`RewardChoiceItemCount5`, "
						<<	"`RewardChoiceItemCount6`, "
						<<	"`RewardFactionId1`, "
						<<	"`RewardFactionId2`, "
						<<	"`RewardFactionId3`, "
						<<	"`RewardFactionId4`, "
						<<	"`RewardFactionId5`, "
						<<	"`RewardFactionValueId1`, "
						<<	"`RewardFactionValueId2`, "
						<<	"`RewardFactionValueId3`, "
						<<	"`RewardFactionValueId4`, "
						<<	"`RewardFactionValueId5`, "
						<<	"`RewardFactionValueIdOverride1`, "
						<<	"`RewardFactionValueIdOverride2`, "
						<<	"`RewardFactionValueIdOverride3`, "
						<<	"`RewardFactionValueIdOverride4`, "
						<<	"`RewardFactionValueIdOverride5`, "
						<<	"`PointMapId`, "
						<<	"`PointX`, "
						<<	"`PointY`, "
						<<	"`PointOption`, "
						<<	"`Title`, "
						<<	"`Objectives`, "
						<<	"`Details`, "
						<<	"`EndText`, "
						<<	"`OfferRewardText`, "
						<<	"`RequestItemsText`, "
						<<	"`CompletedText`, "
						<<	"`RequiredNpcOrGo1`, "
						<<	"`RequiredNpcOrGo2`, "
						<<	"`RequiredNpcOrGo3`, "
						<<	"`RequiredNpcOrGo4`, "
						<<	"`RequiredNpcOrGo5`, "
						<<	"`RequiredNpcOrGo6`, "
						<<	"`RequiredNpcOrGo7`, "
						<<	"`RequiredNpcOrGo8`, "
						<<	"`RequiredNpcOrGo9`, "
						<<	"`RequiredNpcOrGo10`, "
						<<	"`RequiredNpcOrGoCount1`, "
						<<	"`RequiredNpcOrGoCount2`, "
						<<	"`RequiredNpcOrGoCount3`, "
						<<	"`RequiredNpcOrGoCount4`, "
						<<	"`RequiredNpcOrGoCount5`, "
						<<	"`RequiredNpcOrGoCount6`, "
						<<	"`RequiredNpcOrGoCount7`, "
						<<	"`RequiredNpcOrGoCount8`, "
						<<	"`RequiredNpcOrGoCount9`, "
						<<	"`RequiredNpcOrGoCount10`, "
						<<	"`RequiredSourceItemId1`, "
						<<	"`RequiredSourceItemId2`, "
						<<	"`RequiredSourceItemId3`, "
						<<	"`RequiredSourceItemId4`, "
						<<	"`RequiredSourceItemCount1`, "
						<<	"`RequiredSourceItemCount2`, "
						<<	"`RequiredSourceItemCount3`, "
						<<	"`RequiredSourceItemCount4`, "
						<<	"`RequiredItemId1`, "
						<<	"`RequiredItemId2`, "
						<<	"`RequiredItemId3`, "
						<<	"`RequiredItemId4`, "
						<<	"`RequiredItemId5`, "
						<<	"`RequiredItemId6`, "
						<<	"`RequiredItemId7`, "
						<<	"`RequiredItemId8`, "
						<<	"`RequiredItemId9`, "
						<<	"`RequiredItemId10`, "
						<<	"`RequiredItemCount1`, "
						<<	"`RequiredItemCount2`, "
						<<	"`RequiredItemCount3`, "
						<<	"`RequiredItemCount4`, "
						<<	"`RequiredItemCount5`, "
						<<	"`RequiredItemCount6`, "
						<<	"`RequiredItemCount7`, "
						<<	"`RequiredItemCount8`, "
						<<	"`RequiredItemCount9`, "
						<<	"`RequiredItemCount10`, "
						<<	"`RequiredSpell`, "
						<<	"`RequiredSpellCast1`, "
						<<	"`RequiredSpellCast2`, "
						<<	"`RequiredSpellCast3`, "
						<<	"`RequiredSpellCast4`, "
						<<	"`RequiredSpellCast5`, "
						<<	"`RequiredSpellCast6`, "
						<<	"`ObjectiveText1`, "
						<<	"`ObjectiveText2`, "
						<<	"`ObjectiveText3`, "
						<<	"`ObjectiveText4`, "
						<<	"`ObjectiveText5`, "
						<<	"`ObjectiveText6`, "
						<<	"`ObjectiveText7`, "
						<<	"`ObjectiveText8`, "
						<<	"`ObjectiveText9`, "
						<<	"`ObjectiveText10`, "
						<<	"`RewardCurrencyId1`, "
						<<	"`RewardCurrencyId2`, "
						<<	"`RewardCurrencyId3`, "
						<<	"`RewardCurrencyId4`, "
						<<	"`RewardCurrencyCount1`, "
						<<	"`RewardCurrencyCount2`, "
						<<	"`RewardCurrencyCount3`, "
						<<	"`RewardCurrencyCount4`, "
						<<	"`RequiredCurrencyId1`, "
						<<	"`RequiredCurrencyId2`, "
						<<	"`RequiredCurrencyId3`, "
						<<	"`RequiredCurrencyId4`, "
						<<	"`RequiredCurrencyCount1`, "
						<<	"`RequiredCurrencyCount2`, "
						<<	"`RequiredCurrencyCount3`, "
						<<	"`RequiredCurrencyCount4`, "
						<<	"`QuestGiverTextWindow`, "
						<<	"`QuestGiverTargetName`, "
						<<	"`QuestTurnTextWindow`, "
						<<	"`QuestTurnTargetName`, "
						<<	"`SoundAccept`, "
						<<	"`SoundTurnIn`, "
						<<	"`DetailsEmote1`, "
						<<	"`DetailsEmote2`, "
						<<	"`DetailsEmote3`, "
						<<	"`DetailsEmote4`, "
						<<	"`DetailsEmoteDelay1`, "
						<<	"`DetailsEmoteDelay2`, "
						<<	"`DetailsEmoteDelay3`, "
						<<	"`DetailsEmoteDelay4`, "
						<<	"`EmoteOnIncomplete`, "
						<<	"`EmoteOnComplete`, "
						<<	"`OfferRewardEmote1`, "
						<<	"`OfferRewardEmote2`, "
						<<	"`OfferRewardEmote3`, "
						<<	"`OfferRewardEmote4`, "
						<<	"`OfferRewardEmoteDelay1`, "
						<<	"`OfferRewardEmoteDelay2`, "
						<<	"`OfferRewardEmoteDelay3`, "
						<<	"`OfferRewardEmoteDelay4`, "
						<<	"`StartScript`, "
						<<	"`CompleteScript`, "
						<<	"`WDBVerified`) VALUES \n";
				} else
					this->fCacheStream << ", \n";
				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('"  <<  Id << "'," 
					<< " '" <<	Method << "'," 
					<< " '" <<	Level << "'," 
					<< " '" <<	MinLevel << "'," 
					<< " '" <<	MaxLevel << "'," 
					<< " '" <<	ZoneOrSort	<< "'," 
					<< " '" <<	Type	<< "'," 
					<< " '" <<	SuggestedPlayers	<< "'," 
					<< " '" <<	LimitTime	<< "'," 
					<< " '" <<	RequiredTeam	<< "'," 
					<< " '" <<	RequiredClasses	<< "'," 
					<< " '" <<	RequiredRaces	<< "'," 
					<< " '" <<	RequiredSkillId	<< "'," 
					<< " '" <<	RequiredSkillPoints	<< "'," 
					<< " '" <<	RequiredFactionId1	<< "'," 
					<< " '" <<	RequiredFactionId2	<< "'," 
					<< " '" <<	RequiredFactionValue1	<< "'," 
					<< " '" <<	RequiredFactionValue2	<< "'," 
					<< " '" <<	RequiredFactionKills	<< "'," 
					<< " '" <<	RequiredFactionKillsCount	<< "'," 
					<< " '" <<	RequiredPetBattleWith	<< "'," 
					<< " '" <<	RequiredMinRepFaction	<< "'," 
					<< " '" <<	RequiredMaxRepFaction	<< "'," 
					<< " '" <<	RequiredMinRepValue	<< "'," 
					<< " '" <<	RequiredMaxRepValue	<< "'," 
					<< " '" <<	PrevQuestId	<< "'," 
					<< " '" <<	NextQuestId	<< "'," 
					<< " '" <<	ExclusiveGroup	<< "'," 
					<< " '" <<	NextQuestIdChain	<< "'," 
					<< " '" <<	RewardXPId	<< "'," 
					<< " '" <<	RewardXPId2	<< "'," 
					<< " '" <<	RewardOrRequiredMoney	<< "'," 
					<< " '" <<	RewardMoneyMaxLevel	<< "'," 
					<< " '" <<	RewardSpell	<< "'," 
					<< " '" <<	RewardSpellCast	<< "'," 
					<< " '" <<	RewardHonor	<< "'," 
					<< " '" <<	RewardHonorMultiplier	<< "'," 
					<< " '" <<	RewardMailTemplateId	<< "'," 
					<< " '" <<	RewardMailDelay	<< "'," 
					<< " '" <<	SourceItemId	<< "'," 
					<< " '" <<	SourceItemCount	<< "'," 
					<< " '" <<	SourceSpellId	<< "'," 
					<< " '" <<	Flags	<< "',"
					<< " '" <<	Flags2	<< "',"
					<< " '" <<	SpecialFlags	<< "'," 
					<< " '" <<	MinimapTargetMark	<< "'," 
					<< " '" <<	RewardTitleId	<< "'," 
					<< " '" <<	RequiredPlayerKills	<< "'," 
					<< " '" <<	RewardTalents	<< "'," 
					<< " '" <<	RewardArenaPoints	<< "'," 
					<< " '" <<	RewardSkillId	<< "'," 
					<< " '" <<	RewardSkillPoints	<< "'," 
					<< " '" <<	RewardReputationMask	<< "'," 
					<< " '" <<	QuestGiverPortrait	<< "'," 
					<< " '" <<  RewardPackageItemId	<< "'," 
					<< " '" <<	QuestTurnInPortrait	<< "'," 
					<< " '" <<	RewardItemId1	<< "'," 
					<< " '" <<	RewardItemId2	<< "'," 
					<< " '" <<	RewardItemId3	<< "'," 
					<< " '" <<	RewardItemId4	<< "'," 
					<< " '" <<	RewardItemCount1	<< "'," 
					<< " '" <<	RewardItemCount2	<< "'," 
					<< " '" <<	RewardItemCount3	<< "'," 
					<< " '" <<	RewardItemCount4	<< "'," 
					<< " '" <<	RewardChoiceItemId1	<< "'," 
					<< " '" <<	RewardChoiceItemId2	<< "'," 
					<< " '" <<	RewardChoiceItemId3	<< "'," 
					<< " '" <<	RewardChoiceItemId4	<< "'," 
					<< " '" <<	RewardChoiceItemId5	<< "'," 
					<< " '" <<	RewardChoiceItemId6	<< "'," 
					<< " '" <<	RewardChoiceItemCount1	<< "'," 
					<< " '" <<	RewardChoiceItemCount2	<< "'," 
					<< " '" <<	RewardChoiceItemCount3	<< "'," 
					<< " '" <<	RewardChoiceItemCount4	<< "'," 
					<< " '" <<	RewardChoiceItemCount5	<< "'," 
					<< " '" <<	RewardChoiceItemCount6	<< "'," 
					<< " '" <<	RewardFactionId1	<< "'," 
					<< " '" <<	RewardFactionId2	<< "'," 
					<< " '" <<	RewardFactionId3	<< "'," 
					<< " '" <<	RewardFactionId4	<< "'," 
					<< " '" <<	RewardFactionId5	<< "'," 
					<< " '" <<	RewardFactionValueId1	<< "'," 
					<< " '" <<	RewardFactionValueId2	<< "'," 
					<< " '" <<	RewardFactionValueId3	<< "'," 
					<< " '" <<	RewardFactionValueId4	<< "'," 
					<< " '" <<	RewardFactionValueId5	<< "'," 
					<< " '" <<	RewardFactionValueIdOverride1	<< "'," 
					<< " '" <<	RewardFactionValueIdOverride2	<< "'," 
					<< " '" <<	RewardFactionValueIdOverride3	<< "'," 
					<< " '" <<	RewardFactionValueIdOverride4	<< "'," 
					<< " '" <<	RewardFactionValueIdOverride5	<< "'," 
					<< " '" <<	PointMapId	<< "'," 
					<< " '" <<	PointX	<< "'," 
					<< " '" <<	PointY	<< "'," 
					<< " '" <<	PointOption	<< "'," 
					<< " '" <<	this->SafeSQLParams(Title) << "'," 
					<< " '" <<	this->SafeSQLParams(Objectives)	<< "'," 
					<< " '" <<	this->SafeSQLParams(Details)	<< "'," 
					<< " '" <<	this->SafeSQLParams(EndText)	<< "'," 
					<< " '" <<	this->SafeSQLParams(OfferRewardText)	<< "'," 
					<< " '" <<	this->SafeSQLParams(RequestItemsText)	<< "'," 
					<< " '" <<	this->SafeSQLParams(CompletedText)	<< "'," 
					<< " '" <<	RequiredNpcOrGo1	<< "'," 
					<< " '" <<	RequiredNpcOrGo2	<< "'," 
					<< " '" <<	RequiredNpcOrGo3	<< "'," 
					<< " '" <<	RequiredNpcOrGo4	<< "'," 
					<< " '" <<	RequiredNpcOrGo5	<< "'," 
					<< " '" <<	RequiredNpcOrGo6	<< "'," 
					<< " '" <<	RequiredNpcOrGo7	<< "'," 
					<< " '" <<	RequiredNpcOrGo8	<< "'," 
					<< " '" <<	RequiredNpcOrGo9	<< "'," 
					<< " '" <<	RequiredNpcOrGo10	<< "'," 
					<< " '" <<	RequiredNpcOrGoCount1	<< "'," 
					<< " '" <<	RequiredNpcOrGoCount2	<< "'," 
					<< " '" <<	RequiredNpcOrGoCount3	<< "'," 
					<< " '" <<	RequiredNpcOrGoCount4	<< "'," 
					<< " '" <<	RequiredNpcOrGoCount5	<< "'," 
					<< " '" <<	RequiredNpcOrGoCount6	<< "'," 
					<< " '" <<	RequiredNpcOrGoCount7	<< "'," 
					<< " '" <<	RequiredNpcOrGoCount8	<< "'," 
					<< " '" <<	RequiredNpcOrGoCount9	<< "'," 
					<< " '" <<	RequiredNpcOrGoCount10	<< "'," 
					<< " '" <<	RequiredSourceItemId1	<< "'," 
					<< " '" <<	RequiredSourceItemId2	<< "'," 
					<< " '" <<	RequiredSourceItemId3	<< "'," 
					<< " '" <<	RequiredSourceItemId4	<< "'," 
					<< " '" <<	RequiredSourceItemCount1	<< "'," 
					<< " '" <<	RequiredSourceItemCount2	<< "'," 
					<< " '" <<	RequiredSourceItemCount3	<< "'," 
					<< " '" <<	RequiredSourceItemCount4	<< "'," 
					<< " '" <<	RequiredItemId1	<< "'," 
					<< " '" <<	RequiredItemId2	<< "'," 
					<< " '" <<	RequiredItemId3	<< "'," 
					<< " '" <<	RequiredItemId4	<< "'," 
					<< " '" <<	RequiredItemId5	<< "'," 
					<< " '" <<	RequiredItemId6	<< "'," 
					<< " '" <<	RequiredItemId7	<< "'," 
					<< " '" <<	RequiredItemId8	<< "'," 
					<< " '" <<	RequiredItemId9	<< "'," 
					<< " '" <<	RequiredItemId10	<< "'," 
					<< " '" <<	RequiredItemCount1	<< "'," 
					<< " '" <<	RequiredItemCount2	<< "'," 
					<< " '" <<	RequiredItemCount3	<< "'," 
					<< " '" <<	RequiredItemCount4	<< "'," 
					<< " '" <<	RequiredItemCount5	<< "'," 
					<< " '" <<	RequiredItemCount6	<< "'," 
					<< " '" <<	RequiredItemCount7	<< "'," 
					<< " '" <<	RequiredItemCount8	<< "'," 
					<< " '" <<	RequiredItemCount9	<< "'," 
					<< " '" <<	RequiredItemCount10	<< "'," 
					<< " '" <<	RequiredSpell	<< "'," 
					<< " '" <<	RequiredSpellCast1	<< "'," 
					<< " '" <<	RequiredSpellCast2	<< "'," 
					<< " '" <<	RequiredSpellCast3	<< "'," 
					<< " '" <<	RequiredSpellCast4	<< "'," 
					<< " '" <<	RequiredSpellCast5	<< "'," 
					<< " '" <<	RequiredSpellCast6	<< "'," 
					<< " '" <<	this->SafeSQLParams(ObjectiveText1)	<< "'," 
					<< " '" <<	this->SafeSQLParams(ObjectiveText2)	<< "'," 
					<< " '" <<	this->SafeSQLParams(ObjectiveText3)	<< "'," 
					<< " '" <<	this->SafeSQLParams(ObjectiveText4)	<< "'," 
					<< " '" <<	this->SafeSQLParams(ObjectiveText5)	<< "'," 
					<< " '" <<	this->SafeSQLParams(ObjectiveText6)	<< "'," 
					<< " '" <<	this->SafeSQLParams(ObjectiveText7)	<< "'," 
					<< " '" <<	this->SafeSQLParams(ObjectiveText8)	<< "'," 
					<< " '" <<	this->SafeSQLParams(ObjectiveText9)	<< "'," 
					<< " '" <<	this->SafeSQLParams(ObjectiveText10) << "'," 
					<< " '" <<	RewardCurrencyId1	<< "'," 
					<< " '" <<	RewardCurrencyId2	<< "'," 
					<< " '" <<	RewardCurrencyId3	<< "'," 
					<< " '" <<	RewardCurrencyId4	<< "'," 
					<< " '" <<	RewardCurrencyCount1	<< "'," 
					<< " '" <<	RewardCurrencyCount2	<< "'," 
					<< " '" <<	RewardCurrencyCount3	<< "'," 
					<< " '" <<	RewardCurrencyCount4	<< "'," 
					<< " '" <<	RequiredCurrencyId1	<< "'," 
					<< " '" <<	RequiredCurrencyId2	<< "'," 
					<< " '" <<	RequiredCurrencyId3	<< "'," 
					<< " '" <<	RequiredCurrencyId4	<< "'," 
					<< " '" <<	RequiredCurrencyCount1	<< "'," 
					<< " '" <<	RequiredCurrencyCount2	<< "'," 
					<< " '" <<	RequiredCurrencyCount3	<< "'," 
					<< " '" <<	RequiredCurrencyCount4	<< "'," 
					<< " '" <<  this->SafeSQLParams(QuestGiverTextWindow) << "',"
					<< " '" <<  this->SafeSQLParams(QuestGiverTargetName) << "',"
					<< " '" <<  this->SafeSQLParams(QuestTurnTextWindow) << "',"
					<< " '" <<  this->SafeSQLParams(QuestTurnTargetName) << "',"
					<< " '" <<	SoundAccept	<< "'," 
					<< " '" <<	SoundTurnIn	<< "'," 
					<< " '" <<	DetailsEmote1	<< "'," 
					<< " '" <<	DetailsEmote2	<< "'," 
					<< " '" <<	DetailsEmote3	<< "'," 
					<< " '" <<	DetailsEmote4	<< "'," 
					<< " '" <<	DetailsEmoteDelay1	<< "'," 
					<< " '" <<	DetailsEmoteDelay2	<< "'," 
					<< " '" <<	DetailsEmoteDelay3	<< "'," 
					<< " '" <<	DetailsEmoteDelay4	<< "'," 
					<< " '" <<	EmoteOnIncomplete	<< "'," 
					<< " '" <<	EmoteOnComplete	<< "'," 
					<< " '" <<	OfferRewardEmote1	<< "'," 
					<< " '" <<	OfferRewardEmote2	<< "'," 
					<< " '" <<	OfferRewardEmote3	<< "'," 
					<< " '" <<	OfferRewardEmote4	<< "'," 
					<< " '" <<	OfferRewardEmoteDelay1	<< "'," 
					<< " '" <<	OfferRewardEmoteDelay2	<< "'," 
					<< " '" <<	OfferRewardEmoteDelay3	<< "'," 
					<< " '" <<	OfferRewardEmoteDelay4	<< "'," 
					<< " '" <<	StartScript	<< "'," 
					<< " '" <<	CompleteScript	<< "'," 
					<< " '" <<	WDBVerified	<< "');";

				//
			} while (_Result->NextRow());

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto los quest_template de un quest
			this->fHandler->PSendSysMessage("    quest_template exported.");
		} else
			return false;
		return true;
	}
	/// Author: Boris Cabrera
	/// <summary>
	/// Exportar todo lo referente a la tabla gameobject_loot_template
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportGameobjectLootTemplate(uint32 aEntry, std::ostringstream &aDescriptions)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `gameobject_loot_template` WHERE entry = '%u';", aEntry);
		std::list<uint64> _itemsToExport;

		//Add the delete
		this->fCacheStream 
			<< "/* Step x.x Table  `gameobject_loot_template */\n"
			//<< "DELETE FROM gameobject_loot_template WHERE  `entry` = " << aEntry << ";\n";
			<< "DELETE FROM gameobject_loot_template WHERE  `entry` = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			int32 _ReferencesIndex = 0;
			int32 *_References = new int32[_Result->GetRowCount()];
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 entry               = _Fields[_Index++].GetUInt32();
				uint32 item                = abs(_Fields[_Index++].GetInt32());
				float  ChanceOrQuestChance = _Fields[_Index++].GetFloat();
				uint32 lootmode            = uint32(_Fields[_Index++].GetUInt16());
				uint32 groupid             = uint32(_Fields[_Index++].GetUInt8());
				int32  mincountOrRef       = _Fields[_Index++].GetInt32();
				int32  maxcount            = int32(_Fields[_Index++].GetUInt8());

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `gameobject_loot_template` ("
						<< "`entry`,"
						<< "`item`,"
						<< "`ChanceOrQuestChance`,"
						<< "`lootmode`,"
						<< "`groupid`,"
						<< "`mincountOrRef`,"
						<< "`maxcount`) VALUES \n";
				} else
					this->fCacheStream << ", \n";
				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << entry << "',"
					<< "(" << "@ENTRY" << ","
					<< " '" << item << "',"
					<< " '" << ChanceOrQuestChance << "',"
					<< " '" << lootmode << "',"
					<< " '" << groupid << "',"
					<< " '" << mincountOrRef << "',"
					<< " '" << maxcount << "')";

				//
				// Solo como comentario
				//this->fCacheStream << " /* Item(" << item << "): " << GetIntemName(item, true) << ", ItemLevel: " << GetItemLevel(item).str().c_str() << ", RequiredLevel: " << GetRequiredLevel(item).str().c_str() << ", ItemQuality: " << GetItemQuality(item) << " */";
				//
				// exportar los reference templates
				if (mincountOrRef < 0) {
					_References[_ReferencesIndex] = mincountOrRef;
					_ReferencesIndex++;
				}
				// exportar los items
				if (mincountOrRef > 0)
					_itemsToExport.push_back(item);
				//
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";

			//
			//Export items corectly sorted.
			for (auto _citem : _itemsToExport)
			{
				this->exportItemTemplate(_citem);
				if (ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(_citem))
				{
					aDescriptions
						<< itemProto->ItemId << "  " 
						<< itemProto->Quality << "  "
						<< GetItemQuality(_citem) << "  ";
					//Decent way to read item price.
					if (itemProto->SellPrice)
					{
						uint32 _gold = (itemProto->SellPrice / GOLD);
						uint32 _silv = ((itemProto->SellPrice % GOLD) / SILVER);
						uint32 _copp = ((itemProto->SellPrice % GOLD) % SILVER);
						aDescriptions
							<< _gold << "g " << _silv << "s " << _copp << "c  ";
					}
					aDescriptions
						<< itemProto->ItemLevel << "  "
						<< itemProto->RequiredLevel << "  "  
						<< itemProto->Name1 << "\n";
				}
			}

			//
			// Comment end.
			aDescriptions
				<< "*/\n";

			//
			// Export Reference Loot Template
			for (int i = 0; i < _ReferencesIndex; i++)
				this->exportReferenceLootTemplate(abs(_References[i]), aDescriptions);

			delete[] _References;

			// Clear the list.
			_itemsToExport.clear();

			//
			// Notificar al usuario q se exporto los gameobject_loot_template de un gameobject.
			this->fHandler->PSendSysMessage("    gameobject_loot_template exported.");
		} else
			return false;
		return true;
	}
	/// Author: Lester Pastrana
	/// <summary>
	/// Exportar todo lo referente a la tabla gameobject
	/// </summary>
	/// <param name="aGameObjID">Identificador del Objeto a exportar.</param>
	/// <param name="aGameObjectName">Devuelve el nombre del la plantilla de objeto.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportGameObject(uint32 aGameObjID)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `gameobject` WHERE `id` = '%u';", aGameObjID);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 4.1 Table  `gameobject */\n"
			//<< "DELETE FROM `gameobject` WHERE `id` = " << aGameObjID << ";\n";
			<< "DELETE FROM `gameobject` WHERE `id` = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 guid						= _Fields[_Index++].GetUInt32();
				uint32 id						= _Fields[_Index++].GetUInt32();
				uint16 mapid					= _Fields[_Index++].GetUInt16();
				uint16 zoneId					= _Fields[_Index++].GetUInt16();
				uint16 areaId					= _Fields[_Index++].GetUInt16();
				uint32 spawnMask				= _Fields[_Index++].GetUInt32();
				uint16 phaseMask				= _Fields[_Index++].GetUInt16();
				uint32 phaseId				    = _Fields[_Index++].GetUInt32();
				float posX						= _Fields[_Index++].GetFloat();
				float posY						= _Fields[_Index++].GetFloat();
				float posZ						= _Fields[_Index++].GetFloat();
				float orientation				= _Fields[_Index++].GetFloat();
				float rotation0					= _Fields[_Index++].GetFloat();
				float rotation1					= _Fields[_Index++].GetFloat();
				float rotation2					= _Fields[_Index++].GetFloat();
				float rotation3					= _Fields[_Index++].GetFloat();
				uint32 spawntimesecs			= _Fields[_Index++].GetInt32();
				uint32 animprogress				= (uint32)_Fields[_Index++].GetUInt8();
				uint32 go_state					= _Fields[_Index++].GetUInt8();
				uint32 isActive					= (uint32)_Fields[_Index++].GetBool();
				uint32 protectAntiDoublet		= _Fields[_Index++].GetInt32();

				if (!sMapStore.LookupEntry(mapid))
					continue;

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream 
						<< "INSERT INTO `gameobject` ("
						<< "`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `phaseId`, `position_x`, `position_y`, `position_z`, `orientation`,"
						<< "`rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `isActive`, `protect_anti_doublet`) VALUES \n";
				} else
					this->fCacheStream << ", \n";
				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << guid << "',"
					//<< " '" << id << "',"
					<< "(" << "NULL" << ","
					<< " " << "@ENTRY" << ","
					<< " '" << mapid << "',"
					<< " '" << this->GetZoneOrAreaID(mapid, posX, posY, posZ, true) << "',"
					<< " '" << this->GetZoneOrAreaID(mapid, posX, posY, posZ, false) << "',"
					<< " '" << spawnMask << "',"
					<< " '" << phaseMask << "',"
					<< " '" << phaseId << "',"
					<< " '" << posX << "',"
					<< " '" << posY << "',"
					<< " '" << posZ << "',"
					<< " '" << orientation << "',"
					<< " '" << rotation0 << "',"
					<< " '" << rotation1 << "',"
					<< " '" << rotation2 << "',"
					<< " '" << rotation3 << "',"
					<< " '" << spawntimesecs << "',"
					<< " '" << animprogress << "',"
					<< " '" << go_state << "',"
					<< " '" << isActive << "',"
					<< " '" << protectAntiDoublet << "')";

				//
				// Solo como comentario
				;
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    gameobject exported.");
		} else
			return false;
		return true;
	}
	/// Author: Lester Pastrana
	/// <summary>
	/// Exportar todo lo referente a la tabla gameobject_template
	/// </summary>
	/// <param name="aGameObjID">Identificador del Objeto a exportar.</param>
	/// <param name="aGameObjectName">Devuelve el nombre del la plantilla de objeto.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportGameObjectTemplate(uint32 aGameObjID, std::string &aGameObjectName)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `gameobject_template` WHERE `entry` = '%u';", aGameObjID);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 4.1 Table  `gameobject_template */\n"
			//<< "DELETE FROM `gameobject_template` WHERE `entry` = " << aGameObjID << ";\n";
			<< "DELETE FROM `gameobject_template` WHERE `entry` = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 _Entry					= _Fields[_Index++].GetUInt32();
				uint32 type						= (uint32)_Fields[_Index++].GetUInt8();
				uint32 displayId				= _Fields[_Index++].GetUInt32();
				std::string name				= aGameObjectName = _Fields[_Index++].GetString();
				std::string IconName			= _Fields[_Index++].GetString();
				std::string castBarCaption		= _Fields[_Index++].GetString();
				std::string unk1				= _Fields[_Index++].GetString();
				uint16 faction					= _Fields[_Index++].GetUInt16();
				uint32 flags					= _Fields[_Index++].GetUInt32();
				float size						= _Fields[_Index++].GetFloat();

				uint32 questItems1				= _Fields[_Index++].GetUInt32();
				uint32 questItems2				= _Fields[_Index++].GetUInt32();
				uint32 questItems3				= _Fields[_Index++].GetUInt32();
				uint32 questItems4				= _Fields[_Index++].GetUInt32();
				uint32 questItems5				= _Fields[_Index++].GetUInt32();
				uint32 questItems6				= _Fields[_Index++].GetUInt32();
				
				uint32  data0					= _Fields[_Index++].GetUInt32();
				uint32  data1					= _Fields[_Index++].GetUInt32();
				uint32  data2					= _Fields[_Index++].GetUInt32();
				uint32  data3					= _Fields[_Index++].GetUInt32();
				uint32  data4					= _Fields[_Index++].GetUInt32();
				uint32  data5					= _Fields[_Index++].GetUInt32();
				uint32  data6					= _Fields[_Index++].GetUInt32();
				uint32  data7					= _Fields[_Index++].GetUInt32();
				uint32  data8					= _Fields[_Index++].GetUInt32();
				uint32  data9					= _Fields[_Index++].GetUInt32();
				uint32  data10					= _Fields[_Index++].GetUInt32();
				uint32  data11					= _Fields[_Index++].GetUInt32();
				uint32  data12					= _Fields[_Index++].GetUInt32();
				uint32  data13					= _Fields[_Index++].GetUInt32();
				uint32  data14					= _Fields[_Index++].GetUInt32();
				uint32  data15					= _Fields[_Index++].GetUInt32();
				uint32  data16					= _Fields[_Index++].GetUInt32();
				uint32  data17					= _Fields[_Index++].GetUInt32();
				uint32  data18					= _Fields[_Index++].GetUInt32();
				uint32  data19					= _Fields[_Index++].GetUInt32();
				uint32  data20					= _Fields[_Index++].GetUInt32();
				uint32  data21					= _Fields[_Index++].GetUInt32();
				uint32  data22					= _Fields[_Index++].GetUInt32();
				uint32  data23					= _Fields[_Index++].GetUInt32();
				uint32  data24					= _Fields[_Index++].GetUInt32();
				uint32  data25					= _Fields[_Index++].GetUInt32();
				uint32  data26					= _Fields[_Index++].GetUInt32();
				uint32  data27					= _Fields[_Index++].GetUInt32();
				int32   data28					= _Fields[_Index++].GetInt32();
				uint32  data29					= _Fields[_Index++].GetUInt32();
				uint32  data30					= _Fields[_Index++].GetUInt32();
				uint32  data31					= _Fields[_Index++].GetUInt32();
				int32 unkInt32					= _Fields[_Index++].GetInt32();
				std::string AIName				= _Fields[_Index++].GetString();
				std::string ScriptName			= _Fields[_Index++].GetString();
				int16 WDBVerified				= _Fields[_Index++].GetInt16();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `gameobject_template` ("
						//    0      1      2        3       4             5          6      7       8     9        10         11          12
						<< "`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`,  "
						//      13          14          15       16     17     18     19     20     21     22     23     24     25      26      27      28
						<< "`questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, "
						//    29      30      31      32      33      34      35      36      37      38      39      40      41      42      43      44
						<< "`data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, "
						//    45      46      47       48       49        50           51
						<< "`data29`, `data30`, `data31`, `unkInt32`, `AIName`, `ScriptName`, `WDBVerified`) VALUES \n";
				} else
					this->fCacheStream << ", \n";
				
				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << _Entry << "',"
					<< "(" << "@ENTRY" << ","
					<< " '" << type << "',"
					<< " '" << displayId << "',"
					<< " '" << this->SafeSQLParams(name) << "',"
					<< " '" << this->SafeSQLParams(IconName) << "',"
					<< " '" << this->SafeSQLParams(castBarCaption) << "',"
					<< " '" << this->SafeSQLParams(unk1) << "',"
					<< " '" << faction << "',"
					<< " '" << flags << "',"
					<< " '" << size << "',"
					<< " '" << questItems1 << "',"
					<< " '" << questItems2 << "',"
					<< " '" << questItems3 << "',"
					<< " '" << questItems4 << "',"
					<< " '" << questItems5 << "',"
					<< " '" << questItems6 << "',"
					<< " '" << data0 << "',"
					<< " '" << data1 << "',"
					<< " '" << data2 << "',"
					<< " '" << data3 << "',"
					<< " '" << data4 << "',"
					<< " '" << data5 << "',"
					<< " '" << data6 << "',"
					<< " '" << data7 << "',"
					<< " '" << data8 << "',"
					<< " '" << data9 << "',"
					<< " '" << data10 << "',"
					<< " '" << data11 << "',"
					<< " '" << data12 << "',"
					<< " '" << data13 << "',"
					<< " '" << data14 << "',"
					<< " '" << data15 << "',"
					<< " '" << data16 << "',"
					<< " '" << data17 << "',"
					<< " '" << data18 << "',"
					<< " '" << data19 << "',"
					<< " '" << data20 << "',"
					<< " '" << data21 << "',"
					<< " '" << data22 << "',"
					<< " '" << data23 << "',"
					<< " '" << data24 << "',"
					<< " '" << data25 << "',"
					<< " '" << data26 << "',"
					<< " '" << data27 << "',"
					<< " '" << data28 << "',"
					<< " '" << data29 << "',"
					<< " '" << data30 << "',"
					<< " '" << data31 << "',"
					<< " '" << unkInt32 << "',"
					<< " '" << this->SafeSQLParams(AIName) << "',"
					<< " '" << this->SafeSQLParams(ScriptName) << "',"
					<< " '" << WDBVerified << "')";

				//
				// Solo como comentario
				;
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    gameobject_template exported.");
		} else
			return false;
		return true;
	}
	/// Author: MAYOR
	/// <summary> aProspecting_loot_template deveria ser en entry del item **** en item_template
	/// Escribe en un fichero el valor existente en la cache de exportación.
	/// </summary> 
	/// <param name="aInput">Cadena de entrada.</param>
	/// <return>Cadena con los caracteres sustituidos.</return>
	bool exportProspectingLootTemplate(uint32 aProspecting_loot_template)
	{
		std::list<uint64> _itemsToExport;
		QueryResult _Result = WorldDatabase.PQuery(
			"SELECT "
			"`entry`, "
			"`item`, "
			"`ChanceOrQuestChance`, "
			"`lootmode`, "
			"`groupid`, "
			"`mincountOrRef`, "
			"`maxcount` "
			"FROM `prospecting_loot_template` WHERE entry = '%u';", aProspecting_loot_template);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 1.3 Table  `prospecting_loot_template */\n"
			<< "DELETE FROM `prospecting_loot_template` WHERE `entry` = " << aProspecting_loot_template << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 entry			    = _Fields[_Index++].GetUInt32();
				uint32 item					= _Fields[_Index++].GetUInt32();
				float  ChanceOrQuestChance  = _Fields[_Index++].GetFloat();
				uint32 lootmode             = uint32(_Fields[_Index++].GetUInt16());
				uint32 groupid			    = uint32(_Fields[_Index++].GetUInt8());
				int32  mincountOrRef        = _Fields[_Index++].GetInt32();
				int32 maxcount		        = int32(_Fields[_Index++].GetUInt8());

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `prospecting_loot_template` ("
						<< "`entry`, "
						<< "`item`, "
						<< "`ChanceOrQuestChance`, "
						<< "`lootmode`, "
						<< "`groupid`, "
						<< "`mincountOrRef`, "
						<< "`maxcount`) VALUES \n";
				} else
					this->fCacheStream << ", \n";
				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << entry << "',"
					<< " '" << item << "',"
					<< " '" << ChanceOrQuestChance << "',"
					<< " '" << lootmode << "',"
					<< " '" << groupid << "',"
					<< " '" << mincountOrRef << "',"
					<< " '" << maxcount << "')";

				//
				// Solo como comentario
				//this->fCacheStream << " /* Item(" << item << "): " << GetIntemName(item, true) << ", ItemLevel: " << GetItemLevel(item).str().c_str() << ", RequiredLevel: " << GetRequiredLevel(item).str().c_str() << ", ItemQuality: " << GetItemQuality(item) << " */";
				//
				// exportar los items
				_itemsToExport.push_back(item);
				//
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";

			//
			//Export items corectly sorted.
			for (auto _citem : _itemsToExport)
				this->exportItemTemplate(_citem);

			// Clear the list.
			_itemsToExport.clear();

			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    prospecting_loot_template exported.");
		} else
			return false;
		return true;
	}
	/// Authors: Boris Cabrera.
	/// <summary>
	/// Exportar todo lo referente a la tabla item_template
	/// </summary>
	/// <param name="aItemID">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportItemTemplateFromDBC(uint32 aItemID, ItemTemplate const * itemTemplate)
	{
		//Add the delete
		this->fCacheStream 
			<< "/* Step 3.1 Table  `item_template */\n"
			<< "DELETE FROM item_template WHERE entry = " << aItemID << ";\n";
		
		//
		// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
		uint32 entry                      = itemTemplate->ItemId;
		uint32 _Class                     = itemTemplate->Class;
		uint32 subclass                   = itemTemplate->SubClass;
		int32  SoundOverrideSubclass      = itemTemplate->SoundOverrideSubclass;
		std::string name                  = itemTemplate->Name1;
		uint32 displayid                  = itemTemplate->DisplayInfoID;
		uint32 Quality                    = itemTemplate->Quality;
		uint32 Flags                      = itemTemplate->Flags;
		uint32 FlagsExtra                 = itemTemplate->Flags2;
		float  Unk430_1                   = itemTemplate->Unk430_1;
		float  Unk430_2                   = itemTemplate->Unk430_2;
		uint32 BuyCount                   = itemTemplate->BuyCount;
		int32  BuyPrice                   = itemTemplate->BuyPrice;
		uint32 SellPrice                  = itemTemplate->SellPrice;
		uint32 InventoryType              = itemTemplate->InventoryType;
		int32  AllowableClass             = itemTemplate->AllowableClass;
		int32  AllowableRace              = itemTemplate->AllowableRace;
		uint32 ItemLevel                  = itemTemplate->ItemLevel;
		uint32 RequiredLevel              = itemTemplate->RequiredLevel;
		uint32 RequiredSkill              = itemTemplate->RequiredSkill;
		uint32 RequiredSkillRank          = itemTemplate->RequiredSkillRank;
		uint32 requiredspell              = itemTemplate->RequiredSpell;
		uint32 requiredhonorrank          = itemTemplate->RequiredHonorRank;
		uint32 RequiredCityRank           = itemTemplate->RequiredCityRank;
		uint32 RequiredReputationFaction  = itemTemplate->RequiredReputationFaction;
		uint32 RequiredReputationRank     = itemTemplate->RequiredReputationRank;
		int32  maxcount                   = itemTemplate->MaxCount;
		int32  stackable                  = itemTemplate->Stackable;
		uint32 ContainerSlots             = itemTemplate->ContainerSlots;
		uint32 stat_type1                 = itemTemplate->ItemStat[0].ItemStatType;
		int32  stat_value1                = itemTemplate->ItemStat[0].ItemStatValue;
		int32 stat_unk1_1                 = itemTemplate->ItemStat[0].ItemStatUnk1;
		int32 stat_unk2_1                 = itemTemplate->ItemStat[0].ItemStatUnk2;
		uint32 stat_type2                 = itemTemplate->ItemStat[1].ItemStatType;
		int32 stat_value2                 = itemTemplate->ItemStat[1].ItemStatValue;
		int32 stat_unk1_2                 = itemTemplate->ItemStat[1].ItemStatUnk1;
		int32 stat_unk2_2                 = itemTemplate->ItemStat[1].ItemStatUnk1;
		uint32 stat_type3                 = itemTemplate->ItemStat[2].ItemStatType;
		int32 stat_value3                 = itemTemplate->ItemStat[2].ItemStatValue;
		int32 stat_unk1_3                 = itemTemplate->ItemStat[2].ItemStatUnk1;
		int32 stat_unk2_3                 = itemTemplate->ItemStat[2].ItemStatUnk2;
		uint32 stat_type4                 = itemTemplate->ItemStat[3].ItemStatType;
		int32 stat_value4                 = itemTemplate->ItemStat[3].ItemStatValue;
		int32 stat_unk1_4                 = itemTemplate->ItemStat[3].ItemStatUnk1;
		int32 stat_unk2_4                 = itemTemplate->ItemStat[3].ItemStatUnk2;
		uint32 stat_type5                 = itemTemplate->ItemStat[4].ItemStatType;
		int32 stat_value5                 = itemTemplate->ItemStat[4].ItemStatValue;
		int32 stat_unk1_5                 = itemTemplate->ItemStat[4].ItemStatUnk1;
		int32 stat_unk2_5                 = itemTemplate->ItemStat[4].ItemStatUnk2;
		uint32 stat_type6                 = itemTemplate->ItemStat[5].ItemStatType;
		int32 stat_value6                 = itemTemplate->ItemStat[5].ItemStatValue;
		int32 stat_unk1_6                 = itemTemplate->ItemStat[5].ItemStatUnk1;
		int32 stat_unk2_6                 = itemTemplate->ItemStat[5].ItemStatUnk2;
		uint32 stat_type7                 = itemTemplate->ItemStat[6].ItemStatType;
		int32 stat_value7                 = itemTemplate->ItemStat[6].ItemStatValue;
		int32 stat_unk1_7                 = itemTemplate->ItemStat[6].ItemStatUnk1;
		int32 stat_unk2_7                 = itemTemplate->ItemStat[6].ItemStatUnk2;
		uint32 stat_type8                 = itemTemplate->ItemStat[7].ItemStatType;
		int32 stat_value8                 = itemTemplate->ItemStat[7].ItemStatValue;
		int32 stat_unk1_8                 = itemTemplate->ItemStat[7].ItemStatUnk1;
		int32 stat_unk2_8                 = itemTemplate->ItemStat[7].ItemStatUnk2;
		uint32 stat_type9                 = itemTemplate->ItemStat[8].ItemStatType;
		int32 stat_value9                 = itemTemplate->ItemStat[8].ItemStatValue;
		int32 stat_unk1_9                 = itemTemplate->ItemStat[8].ItemStatUnk1;
		int32 stat_unk2_9                 = itemTemplate->ItemStat[8].ItemStatUnk2;
		uint32 stat_type10                = itemTemplate->ItemStat[9].ItemStatType;
		int32 stat_value10                = itemTemplate->ItemStat[9].ItemStatValue;
		int32 stat_unk1_10                = itemTemplate->ItemStat[9].ItemStatUnk1;
		int32 stat_unk2_10                = itemTemplate->ItemStat[9].ItemStatUnk2;
		uint32 ScalingStatDistribution    = itemTemplate->ScalingStatDistribution;
		uint32 DamageType                 = itemTemplate->DamageType;
		uint32 delay                      = itemTemplate->Delay;
		float RangedModRange              = itemTemplate->RangedModRange;
		uint32 spellid_1                  = itemTemplate->Spells[0].SpellId;
		uint32 spelltrigger_1             = itemTemplate->Spells[0].SpellTrigger;
		int32  spellcharges_1             = itemTemplate->Spells[0].SpellCharges;
		int32  spellcooldown_1            = itemTemplate->Spells[0].SpellCooldown;
		uint32 spellcategory_1            = itemTemplate->Spells[0].SpellCategory;
		int32  spellcategorycooldown_1    = itemTemplate->Spells[0].SpellCategoryCooldown;
		uint32 spellid_2                  = itemTemplate->Spells[1].SpellId;
		uint32 spelltrigger_2             = itemTemplate->Spells[1].SpellTrigger;
		int32  spellcharges_2             = itemTemplate->Spells[1].SpellCharges;
		int32  spellcooldown_2            = itemTemplate->Spells[1].SpellCooldown;
		uint32 spellcategory_2            = itemTemplate->Spells[1].SpellCategory;
		int32  spellcategorycooldown_2    = itemTemplate->Spells[1].SpellCategoryCooldown;
		uint32 spellid_3                  = itemTemplate->Spells[2].SpellId;
		uint32 spelltrigger_3             = itemTemplate->Spells[2].SpellTrigger;
		int32  spellcharges_3             = itemTemplate->Spells[2].SpellCharges;
		int32  spellcooldown_3            = itemTemplate->Spells[2].SpellCooldown;
		uint32 spellcategory_3            = itemTemplate->Spells[2].SpellCategory;
		int32  spellcategorycooldown_3    = itemTemplate->Spells[2].SpellCategoryCooldown;
		uint32 spellid_4                  = itemTemplate->Spells[3].SpellId;
		uint32 spelltrigger_4             = itemTemplate->Spells[3].SpellTrigger;
		int32  spellcharges_4             = itemTemplate->Spells[3].SpellCharges;
		int32  spellcooldown_4            = itemTemplate->Spells[3].SpellCooldown;
		uint32 spellcategory_4            = itemTemplate->Spells[3].SpellCategory;
		int32  spellcategorycooldown_4    = itemTemplate->Spells[3].SpellCategoryCooldown;
		uint32 spellid_5                  = itemTemplate->Spells[4].SpellId;
		uint32 spelltrigger_5             = itemTemplate->Spells[4].SpellTrigger;
		int32 spellcharges_5              = itemTemplate->Spells[4].SpellCharges;
		int32  spellcooldown_5            = itemTemplate->Spells[4].SpellCooldown;
		uint32 spellcategory_5            = itemTemplate->Spells[4].SpellCategory;
		int32  spellcategorycooldown_5    = itemTemplate->Spells[4].SpellCategoryCooldown;
		uint32 bonding                    = itemTemplate->Bonding;
		std::string description           = itemTemplate->Description;
		uint32 PageText                   = itemTemplate->PageText;
		uint32 LanguageID                 = itemTemplate->LanguageID;
		uint32 PageMaterial               = itemTemplate->PageMaterial;
		uint32 startquest                 = itemTemplate->StartQuest;
		uint32 lockid                     = itemTemplate->LockID;
		int32  Material                   = itemTemplate->Material;
		uint32 sheath                     = itemTemplate->Sheath;
		int32  RandomProperty             = itemTemplate->RandomProperty;
		int32  RandomSuffix               = itemTemplate->RandomSuffix;
		uint32 itemset                    = itemTemplate->ItemSet;
		uint32 MaxDurability              = itemTemplate->MaxDurability;
		uint32 area                       = itemTemplate->Area;
		uint32 Map                        = itemTemplate->Map;
		uint32 BagFamily                  = itemTemplate->BagFamily;
		uint32 TotemCategory              = itemTemplate->TotemCategory;
		uint32 socketColor_1              = itemTemplate->Socket[0].Color;
		uint32 socketContent_1            = itemTemplate->Socket[0].Content;
		uint32 socketColor_2              = itemTemplate->Socket[1].Color;
		uint32 socketContent_2            = itemTemplate->Socket[1].Content;
		uint32 socketColor_3              = itemTemplate->Socket[2].Color;
		uint32 socketContent_3            = itemTemplate->Socket[2].Content;
		uint32 socketBonus                = itemTemplate->socketBonus;
		uint32 GemProperties              = itemTemplate->GemProperties;
		float  ArmorDamageModifier        = itemTemplate->ArmorDamageModifier;
		uint32 duration                   = itemTemplate->Duration;
		uint32 ItemLimitCategory          = itemTemplate->ItemLimitCategory;
		uint32 HolidayId                  = itemTemplate->HolidayId;
		float StatScalingFactor           = itemTemplate->StatScalingFactor;
		uint32  CurrencySubstitutionId    = itemTemplate->CurrencySubstitutionId;
		uint32 CurrencySubstitutionCount  = itemTemplate->CurrencySubstitutionCount;
		int32 flagsCustom                 = itemTemplate->FlagsCu;
		int32 WDBVerified                 = 18414;

				//
		// Agregar la query a la cache de almacenamiento.
		this->fCacheStream
			<< "INSERT INTO `item_template` ("
			<< "`entry`, "
			<< "`class`, "
			<< "`subclass`, "
			<< "`SoundOverrideSubclass`, "
			<< "`name`, "
			<< "`displayid`, "
			<< "`Quality`, "
			<< "`Flags`, "
			<< "`FlagsExtra`, "
			<< "`Unk430_1`, "
			<< "`Unk430_2`, "
			<< "`BuyCount`, "
			<< "`BuyPrice`, "
			<< "`SellPrice`, "
			<< "`InventoryType`, "
			<< "`AllowableClass`, "
			<< "`AllowableRace`, "
			<< "`ItemLevel`, "
			<< "`RequiredLevel`, "
			<< "`RequiredSkill`, "
			<< "`RequiredSkillRank`, "
			<< "`requiredspell`, "
			<< "`requiredhonorrank`, "
			<< "`RequiredCityRank`, "
			<< "`RequiredReputationFaction`, "
			<< "`RequiredReputationRank`, "
			<< "`maxcount`, "
			<< "`stackable`, "
			<< "`ContainerSlots`, "
			<< "`stat_type1`, "
			<< "`stat_value1`, "
			<< "`stat_unk1_1`, "
			<< "`stat_unk2_1`, "
			<< "`stat_type2`, "
			<< "`stat_value2`, "
			<< "`stat_unk1_2`, "
			<< "`stat_unk2_2`, "
			<< "`stat_type3`, "
			<< "`stat_value3`, "
			<< "`stat_unk1_3`, "
			<< "`stat_unk2_3`, "
			<< "`stat_type4`, "
			<< "`stat_value4`, "
			<< "`stat_unk1_4`, "
			<< "`stat_unk2_4`, "
			<< "`stat_type5`, "
			<< "`stat_value5`, "
			<< "`stat_unk1_5`, "
			<< "`stat_unk2_5`, "
			<< "`stat_type6`, "
			<< "`stat_value6`, "
			<< "`stat_unk1_6`, "
			<< "`stat_unk2_6`, "
			<< "`stat_type7`, "
			<< "`stat_value7`, "
			<< "`stat_unk1_7`, "
			<< "`stat_unk2_7`, "
			<< "`stat_type8`, "
			<< "`stat_value8`, "
			<< "`stat_unk1_8`, "
			<< "`stat_unk2_8`, "
			<< "`stat_type9`, "
			<< "`stat_value9`, "
			<< "`stat_unk1_9`, "
			<< "`stat_unk2_9`, "
			<< "`stat_type10`, "
			<< "`stat_value10`, "
			<< "`stat_unk1_10`, "
			<< "`stat_unk2_10`, "
			<< "`ScalingStatDistribution`, "
			<< "`DamageType`, "
			<< "`delay`, "
			<< "`RangedModRange`, "
			<< "`spellid_1`, "
			<< "`spelltrigger_1`, "
			<< "`spellcharges_1`, "
			<< "`spellcooldown_1`, "
			<< "`spellcategory_1`, "
			<< "`spellcategorycooldown_1`, "
			<< "`spellid_2`, "
			<< "`spelltrigger_2`, "
			<< "`spellcharges_2`, "
			<< "`spellcooldown_2`, "
			<< "`spellcategory_2`, "
			<< "`spellcategorycooldown_2`, "
			<< "`spellid_3`, "
			<< "`spelltrigger_3`, "
			<< "`spellcharges_3`, "
			<< "`spellcooldown_3`, "
			<< "`spellcategory_3`, "
			<< "`spellcategorycooldown_3`, "
			<< "`spellid_4`, "
			<< "`spelltrigger_4`, "
			<< "`spellcharges_4`, "
			<< "`spellcooldown_4`, "
			<< "`spellcategory_4`, "
			<< "`spellcategorycooldown_4`, "
			<< "`spellid_5`, "
			<< "`spelltrigger_5`, "
			<< "`spellcharges_5`, "
			<< "`spellcooldown_5`, "
			<< "`spellcategory_5`, "
			<< "`spellcategorycooldown_5`, "
			<< "`bonding`, "
			<< "`description`, "
			<< "`PageText`, "
			<< "`LanguageID`, "
			<< "`PageMaterial`, "
			<< "`startquest`, "
			<< "`lockid`, "
			<< "`Material`, "
			<< "`sheath`, "
			<< "`RandomProperty`, "
			<< "`RandomSuffix`, "
			<< "`itemset`, "
			<< "`MaxDurability`, "
			<< "`area`, "
			<< "`Map`, "
			<< "`BagFamily`, "
			<< "`TotemCategory`, "
			<< "`socketColor_1`, "
			<< "`socketContent_1`, "
			<< "`socketColor_2`, "
			<< "`socketContent_2`, "
			<< "`socketColor_3`, "
			<< "`socketContent_3`, "
			<< "`socketBonus`, "
			<< "`GemProperties`, "
			<< "`ArmorDamageModifier`, "
			<< "`duration`, "
			<< "`ItemLimitCategory`, "
			<< "`HolidayId`, "
			<< "`StatScalingFactor`, "
			<< "`CurrencySubstitutionId`, "
			<< "`CurrencySubstitutionCount`, "
			<< "`flagsCustom`, "
			<< "`WDBVerified`) VALUES \n";

		//
		// Insertar los parámetros.
		this->fCacheStream
			<< "('" << entry << "',"
			<< " '" << _Class << "',"
			<< " '" << subclass << "',"
			<< " '" << SoundOverrideSubclass << "',"
			<< " '" << this->SafeSQLParams(name) << "',"
			<< " '" << displayid << "',"
			<< " '" << Quality << "',"
			<< " '" << Flags << "',"
			<< " '" << FlagsExtra << "',"
			<< " '" << Unk430_1 << "',"
			<< " '" << Unk430_2 << "',"
			<< " '" << BuyCount << "',"
			<< " '" << BuyPrice << "',"
			<< " '" << SellPrice << "',"
			<< " '" << InventoryType << "',"
			<< " '" << AllowableClass << "',"
			<< " '" << AllowableRace << "',"
			<< " '" << ItemLevel << "',"
			<< " '" << RequiredLevel << "',"
			<< " '" << RequiredSkill << "',"
			<< " '" << RequiredSkillRank << "',"
			<< " '" << requiredspell << "',"
			<< " '" << requiredhonorrank << "',"
			<< " '" << RequiredCityRank << "',"
			<< " '" << RequiredReputationFaction << "',"
			<< " '" << RequiredReputationRank << "',"
			<< " '" << maxcount << "',"
			<< " '" << stackable << "',"
			<< " '" << ContainerSlots << "',"
			<< " '" << stat_type1 << "',"
			<< " '" << stat_value1 << "',"
			<< " '" << stat_unk1_1 << "',"
			<< " '" << stat_unk2_1 << "',"
			<< " '" << stat_type2 << "',"
			<< " '" << stat_value2 << "',"
			<< " '" << stat_unk1_2 << "',"
			<< " '" << stat_unk2_2 << "',"
			<< " '" << stat_type3 << "',"
			<< " '" << stat_value3 << "',"
			<< " '" << stat_unk1_3 << "',"
			<< " '" << stat_unk2_3 << "',"
			<< " '" << stat_type4 << "',"
			<< " '" << stat_value4 << "',"
			<< " '" << stat_unk1_4 << "',"
			<< " '" << stat_unk2_4 << "',"
			<< " '" << stat_type5 << "',"
			<< " '" << stat_value5 << "',"
			<< " '" << stat_unk1_5 << "',"
			<< " '" << stat_unk2_5 << "',"
			<< " '" << stat_type6 << "',"
			<< " '" << stat_value6 << "',"
			<< " '" << stat_unk1_6 << "',"
			<< " '" << stat_unk2_6 << "',"
			<< " '" << stat_type7 << "',"
			<< " '" << stat_value7 << "',"
			<< " '" << stat_unk1_7 << "',"
			<< " '" << stat_unk2_7 << "',"
			<< " '" << stat_type8 << "',"
			<< " '" << stat_value8 << "',"
			<< " '" << stat_unk1_8 << "',"
			<< " '" << stat_unk2_8 << "',"
			<< " '" << stat_type9 << "',"
			<< " '" << stat_value9 << "',"
			<< " '" << stat_unk1_9 << "',"
			<< " '" << stat_unk2_9 << "',"
			<< " '" << stat_type10 << "',"
			<< " '" << stat_value10 << "',"
			<< " '" << stat_unk1_10 << "',"
			<< " '" << stat_unk2_10 << "',"
			<< " '" << ScalingStatDistribution << "',"
			<< " '" << DamageType << "',"
			<< " '" << delay << "',"
			<< " '" << RangedModRange << "',"
			<< " '" << spellid_1 << "',"
			<< " '" << spelltrigger_1 << "',"
			<< " '" << spellcharges_1 << "',"
			<< " '" << spellcooldown_1 << "',"
			<< " '" << spellcategory_1 << "',"
			<< " '" << spellcategorycooldown_1 << "',"
			<< " '" << spellid_2 << "',"
			<< " '" << spelltrigger_2 << "',"
			<< " '" << spellcharges_2 << "',"
			<< " '" << spellcooldown_2 << "',"
			<< " '" << spellcategory_2 << "',"
			<< " '" << spellcategorycooldown_2 << "',"
			<< " '" << spellid_3 << "',"
			<< " '" << spelltrigger_3 << "',"
			<< " '" << spellcharges_3 << "',"
			<< " '" << spellcooldown_3 << "',"
			<< " '" << spellcategory_3 << "',"
			<< " '" << spellcategorycooldown_3 << "',"
			<< " '" << spellid_4 << "',"
			<< " '" << spelltrigger_4 << "',"
			<< " '" << spellcharges_4 << "',"
			<< " '" << spellcooldown_4 << "',"
			<< " '" << spellcategory_4 << "',"
			<< " '" << spellcategorycooldown_4 << "',"
			<< " '" << spellid_5 << "',"
			<< " '" << spelltrigger_5 << "',"
			<< " '" << spellcharges_5 << "',"
			<< " '" << spellcooldown_5 << "',"
			<< " '" << spellcategory_5 << "',"
			<< " '" << spellcategorycooldown_5 << "',"
			<< " '" << bonding << "',"
			<< " '" << this->SafeSQLParams(description) << "',"
			<< " '" << PageText << "',"
			<< " '" << LanguageID << "',"
			<< " '" << PageMaterial << "',"
			<< " '" << startquest << "',"
			<< " '" << lockid << "',"
			<< " '" << Material << "',"
			<< " '" << sheath << "',"
			<< " '" << RandomProperty << "',"
			<< " '" << RandomSuffix << "',"
			<< " '" << itemset << "',"
			<< " '" << MaxDurability << "',"
			<< " '" << area << "',"
			<< " '" << Map << "',"
			<< " '" << BagFamily << "',"
			<< " '" << TotemCategory << "',"
			<< " '" << socketColor_1 << "',"
			<< " '" << socketContent_1 << "',"
			<< " '" << socketColor_2 << "',"
			<< " '" << socketContent_2 << "',"
			<< " '" << socketColor_3 << "',"
			<< " '" << socketContent_3 << "',"
			<< " '" << socketBonus << "',"
			<< " '" << GemProperties << "',"
			<< " '" << ArmorDamageModifier << "',"
			<< " '" << duration << "',"
			<< " '" << ItemLimitCategory << "',"
			<< " '" << HolidayId << "',"
			<< " '" << StatScalingFactor << "',"
			<< " '" << CurrencySubstitutionId << "',"
			<< " '" << CurrencySubstitutionCount << "',"
			<< " '" << flagsCustom << "',"
			<< " '" << WDBVerified << "')";
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    item_template exported.");

			return true;
	}
	/// Authors: Lester Pastrana and Boris Cabrera.
	/// <summary>
	/// Exportar todo lo referente a la tabla item_template
	/// </summary>
	/// <param name="aItemID">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportItemTemplate(uint32 aItemID)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM item_template WHERE entry = '%u';", aItemID);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 3.1 Table  `item_template */\n"
			<< "DELETE FROM item_template WHERE entry = " << aItemID << ";\n";
	
		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 entry                      = _Fields[_Index++].GetUInt32();
				uint32 _Class                     = uint32(_Fields[_Index++].GetUInt8());
				uint32 subclass                   = uint32(_Fields[_Index++].GetUInt8());
				int32  SoundOverrideSubclass      = int32(_Fields[_Index++].GetInt8());
				std::string name                  = _Fields[_Index++].GetString();
				uint32 displayid                  = _Fields[_Index++].GetUInt32();
				uint32 Quality                    = uint32(_Fields[_Index++].GetUInt8());
				uint32 Flags                      = uint32(_Fields[_Index++].GetInt64());
				uint32 FlagsExtra                 = _Fields[_Index++].GetUInt32();
				float  Unk430_1                   = _Fields[_Index++].GetFloat();
				float  Unk430_2                   = _Fields[_Index++].GetFloat();
				uint32 BuyCount                   =  uint32(_Fields[_Index++].GetUInt8());
				int32  BuyPrice                   = int32(_Fields[_Index++].GetInt64());
				uint32 SellPrice                  = _Fields[_Index++].GetUInt32();
				uint32 InventoryType              = uint32(_Fields[_Index++].GetUInt8());
				int32  AllowableClass             = _Fields[_Index++].GetInt32();
				int32  AllowableRace              = _Fields[_Index++].GetInt32();
				uint32 ItemLevel                  = uint32(_Fields[_Index++].GetUInt16());
				uint32 RequiredLevel              = uint32(_Fields[_Index++].GetUInt8());
				uint32 RequiredSkill              = uint32(_Fields[_Index++].GetUInt16());
				uint32 RequiredSkillRank          = uint32(_Fields[_Index++].GetUInt16());
				uint32 requiredspell              = _Fields[_Index++].GetUInt32();
				uint32 requiredhonorrank          = _Fields[_Index++].GetUInt32();
				uint32 RequiredCityRank           = _Fields[_Index++].GetUInt32();
				uint32 RequiredReputationFaction  = uint32(_Fields[_Index++].GetUInt16());
				uint32 RequiredReputationRank     = uint32(_Fields[_Index++].GetUInt16());
				int32  maxcount                   = _Fields[_Index++].GetInt32();
				int32  stackable                  = _Fields[_Index++].GetInt32();
				uint32 ContainerSlots             =  uint32(_Fields[_Index++].GetUInt8());
				uint32 stat_type1                 = uint32(_Fields[_Index++].GetUInt8());
				int32  stat_value1                = int32(_Fields[_Index++].GetInt16());
				int32 stat_unk1_1                 = _Fields[_Index++].GetInt32();
				int32 stat_unk2_1                 = _Fields[_Index++].GetInt32();
				uint32 stat_type2                 = uint32(_Fields[_Index++].GetUInt8());
				int32 stat_value2                 = int32(_Fields[_Index++].GetInt16());
				int32 stat_unk1_2                 = _Fields[_Index++].GetInt32();
				int32 stat_unk2_2                 = _Fields[_Index++].GetInt32();
				uint32 stat_type3                 = uint32(_Fields[_Index++].GetUInt8());
				int32 stat_value3                 = int32(_Fields[_Index++].GetInt16());
				int32 stat_unk1_3                 = _Fields[_Index++].GetInt32();
				int32 stat_unk2_3                 = _Fields[_Index++].GetInt32();
				uint32 stat_type4                 = uint32(_Fields[_Index++].GetUInt8());
				int32 stat_value4                 = int32(_Fields[_Index++].GetInt16());
				int32 stat_unk1_4                 = _Fields[_Index++].GetInt32();
				int32 stat_unk2_4                 = _Fields[_Index++].GetInt32();
				uint32 stat_type5                 = uint32(_Fields[_Index++].GetUInt8());
				int32 stat_value5                 = int32(_Fields[_Index++].GetInt16());
				int32 stat_unk1_5                 = _Fields[_Index++].GetInt32();
				int32 stat_unk2_5                 = _Fields[_Index++].GetInt32();
				uint32 stat_type6                 = uint32(_Fields[_Index++].GetUInt8());
				int32 stat_value6                 = int32(_Fields[_Index++].GetInt16());
				int32 stat_unk1_6                 = _Fields[_Index++].GetInt32();
				int32 stat_unk2_6                 = _Fields[_Index++].GetInt32();
				uint32 stat_type7                 = uint32(_Fields[_Index++].GetUInt8());
				int32 stat_value7                 = int32(_Fields[_Index++].GetInt16());
				int32 stat_unk1_7                 = _Fields[_Index++].GetInt32();
				int32 stat_unk2_7                 = _Fields[_Index++].GetInt32();
				uint32 stat_type8                 = uint32(_Fields[_Index++].GetUInt8());
				int32 stat_value8                 = int32(_Fields[_Index++].GetInt16());
				int32 stat_unk1_8                 = _Fields[_Index++].GetInt32();
				int32 stat_unk2_8                 = _Fields[_Index++].GetInt32();
				uint32 stat_type9                 = uint32(_Fields[_Index++].GetUInt8());
				int32 stat_value9                 = _int32(_Fields[_Index++].GetInt16());
				int32 stat_unk1_9                 = _Fields[_Index++].GetInt32();
				int32 stat_unk2_9                 = _Fields[_Index++].GetInt32();
				uint32 stat_type10                = uint32(_Fields[_Index++].GetUInt8());
				int32 stat_value10                = int32(_Fields[_Index++].GetInt16());
				int32 stat_unk1_10                = _Fields[_Index++].GetInt32();
				int32 stat_unk2_10                = _Fields[_Index++].GetInt32();
				uint32 ScalingStatDistribution    = uint32(_Fields[_Index++].GetUInt16());
				uint32 DamageType                 = uint32(_Fields[_Index++].GetUInt8());
				uint32 delay                      = uint32(_Fields[_Index++].GetUInt16());
				float RangedModRange              = _Fields[_Index++].GetFloat();
				uint32 spellid_1                  = _Fields[_Index++].GetInt32();
				uint32 spelltrigger_1             = uint32(_Fields[_Index++].GetUInt8());
				int32  spellcharges_1             = int32(_Fields[_Index++].GetInt16());
				int32  spellcooldown_1            = _Fields[_Index++].GetInt32();
				uint32 spellcategory_1            = uint32(_Fields[_Index++].GetUInt16());
				int32  spellcategorycooldown_1    = _Fields[_Index++].GetInt32();
				uint32 spellid_2                  = _Fields[_Index++].GetInt32();
				uint32 spelltrigger_2             = uint32(_Fields[_Index++].GetUInt8());
				int32  spellcharges_2             = int32(_Fields[_Index++].GetInt16());
				int32  spellcooldown_2            = _Fields[_Index++].GetInt32();
				uint32 spellcategory_2            = uint32(_Fields[_Index++].GetUInt16());
				int32  spellcategorycooldown_2    = _Fields[_Index++].GetInt32();
				uint32 spellid_3                  = _Fields[_Index++].GetInt32();
				uint32 spelltrigger_3             = uint32(_Fields[_Index++].GetUInt8());
				int32  spellcharges_3             = int32(_Fields[_Index++].GetInt16());
				int32  spellcooldown_3            = _Fields[_Index++].GetInt32();
				uint32 spellcategory_3            = uint32(_Fields[_Index++].GetUInt16());
				int32  spellcategorycooldown_3    = _Fields[_Index++].GetInt32();
				uint32 spellid_4                  = _Fields[_Index++].GetInt32();
				uint32 spelltrigger_4             = uint32(_Fields[_Index++].GetUInt8());
				int32  spellcharges_4             = int32(_Fields[_Index++].GetInt16());
				int32  spellcooldown_4            = _Fields[_Index++].GetInt32();
				uint32 spellcategory_4            = uint32(_Fields[_Index++].GetUInt16());
				int32  spellcategorycooldown_4    = _Fields[_Index++].GetInt32();
				uint32 spellid_5                  = _Fields[_Index++].GetInt32();
				uint32 spelltrigger_5             = uint32(_Fields[_Index++].GetUInt8());
				int32 spellcharges_5              = int32(_Fields[_Index++].GetInt16());
				int32  spellcooldown_5            = _Fields[_Index++].GetInt32();
				uint32 spellcategory_5            = uint32(_Fields[_Index++].GetUInt16());
				int32  spellcategorycooldown_5    = _Fields[_Index++].GetInt32();
				uint32 bonding                    = uint32(_Fields[_Index++].GetUInt8());
				std::string description           = _Fields[_Index++].GetString();
				uint32 PageText                   = _Fields[_Index++].GetUInt32();
				uint32 LanguageID                 = uint32(_Fields[_Index++].GetUInt8());
				uint32 PageMaterial               = uint32(_Fields[_Index++].GetUInt8());
				uint32 startquest                 = _Fields[_Index++].GetUInt32();
				uint32 lockid                     = _Fields[_Index++].GetUInt32();
				int32  Material                   = int32(_Fields[_Index++].GetInt8());
				uint32 sheath                     = uint32(_Fields[_Index++].GetUInt8());
				int32 RandomProperty              = _Fields[_Index++].GetInt32();
				int32  RandomSuffix               = _Fields[_Index++].GetInt32();
				uint32 itemset                    = _Fields[_Index++].GetUInt32();
				uint32 MaxDurability              = uint32(_Fields[_Index++].GetUInt16());
				uint32 area                       = _Fields[_Index++].GetUInt32();
				uint32 Map                        = uint32(_Fields[_Index++].GetUInt16());
				uint32 BagFamily                  = _Fields[_Index++].GetUInt32();
				uint32 TotemCategory              = _Fields[_Index++].GetUInt32();
				uint32 socketColor_1              = uint32(_Fields[_Index++].GetUInt8());
				uint32 socketContent_1            = _Fields[_Index++].GetUInt32();
				uint32 socketColor_2              = uint32(_Fields[_Index++].GetUInt8());
				uint32 socketContent_2            = _Fields[_Index++].GetUInt32();
				uint32 socketColor_3              = uint32(_Fields[_Index++].GetUInt8());
				uint32 socketContent_3            = _Fields[_Index++].GetUInt32();
				uint32 socketBonus                = _Fields[_Index++].GetUInt32();
				uint32 GemProperties              = _Fields[_Index++].GetUInt32();
				float  ArmorDamageModifier        = _Fields[_Index++].GetFloat();
				uint32 duration                   = _Fields[_Index++].GetUInt32();
				uint32 ItemLimitCategory          = uint32(_Fields[_Index++].GetInt16());
				uint32 HolidayId                  = _Fields[_Index++].GetUInt32();
				float StatScalingFactor           = _Fields[_Index++].GetFloat();
				uint32  CurrencySubstitutionId    = _Fields[_Index++].GetUInt32();
				uint32 CurrencySubstitutionCount  = _Fields[_Index++].GetInt32();
				int32 flagsCustom                 = _Fields[_Index++].GetInt32();
				int32 WDBVerified                 = _Fields[_Index++].GetInt32();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `item_template` ("
						<< "`entry`, "
						<< "`class`, "
						<< "`subclass`, "
						<< "`SoundOverrideSubclass`, "
						<< "`name`, "
						<< "`displayid`, "
						<< "`Quality`, "
						<< "`Flags`, "
						<< "`FlagsExtra`, "
						<< "`Unk430_1`, "
						<< "`Unk430_2`, "
						<< "`BuyCount`, "
						<< "`BuyPrice`, "
						<< "`SellPrice`, "
						<< "`InventoryType`, "
						<< "`AllowableClass`, "
						<< "`AllowableRace`, "
						<< "`ItemLevel`, "
						<< "`RequiredLevel`, "
						<< "`RequiredSkill`, "
						<< "`RequiredSkillRank`, "
						<< "`requiredspell`, "
						<< "`requiredhonorrank`, "
						<< "`RequiredCityRank`, "
						<< "`RequiredReputationFaction`, "
						<< "`RequiredReputationRank`, "
						<< "`maxcount`, "
						<< "`stackable`, "
						<< "`ContainerSlots`, "
						<< "`stat_type1`, "
						<< "`stat_value1`, "
						<< "`stat_unk1_1`, "
						<< "`stat_unk2_1`, "
						<< "`stat_type2`, "
						<< "`stat_value2`, "
						<< "`stat_unk1_2`, "
						<< "`stat_unk2_2`, "
						<< "`stat_type3`, "
						<< "`stat_value3`, "
						<< "`stat_unk1_3`, "
						<< "`stat_unk2_3`, "
						<< "`stat_type4`, "
						<< "`stat_value4`, "
						<< "`stat_unk1_4`, "
						<< "`stat_unk2_4`, "
						<< "`stat_type5`, "
						<< "`stat_value5`, "
						<< "`stat_unk1_5`, "
						<< "`stat_unk2_5`, "
						<< "`stat_type6`, "
						<< "`stat_value6`, "
						<< "`stat_unk1_6`, "
						<< "`stat_unk2_6`, "
						<< "`stat_type7`, "
						<< "`stat_value7`, "
						<< "`stat_unk1_7`, "
						<< "`stat_unk2_7`, "
						<< "`stat_type8`, "
						<< "`stat_value8`, "
						<< "`stat_unk1_8`, "
						<< "`stat_unk2_8`, "
						<< "`stat_type9`, "
						<< "`stat_value9`, "
						<< "`stat_unk1_9`, "
						<< "`stat_unk2_9`, "
						<< "`stat_type10`, "
						<< "`stat_value10`, "
						<< "`stat_unk1_10`, "
						<< "`stat_unk2_10`, "
						<< "`ScalingStatDistribution`, "
						<< "`DamageType`, "
						<< "`delay`, "
						<< "`RangedModRange`, "
						<< "`spellid_1`, "
						<< "`spelltrigger_1`, "
						<< "`spellcharges_1`, "
						<< "`spellcooldown_1`, "
						<< "`spellcategory_1`, "
						<< "`spellcategorycooldown_1`, "
						<< "`spellid_2`, "
						<< "`spelltrigger_2`, "
						<< "`spellcharges_2`, "
						<< "`spellcooldown_2`, "
						<< "`spellcategory_2`, "
						<< "`spellcategorycooldown_2`, "
						<< "`spellid_3`, "
						<< "`spelltrigger_3`, "
						<< "`spellcharges_3`, "
						<< "`spellcooldown_3`, "
						<< "`spellcategory_3`, "
						<< "`spellcategorycooldown_3`, "
						<< "`spellid_4`, "
						<< "`spelltrigger_4`, "
						<< "`spellcharges_4`, "
						<< "`spellcooldown_4`, "
						<< "`spellcategory_4`, "
						<< "`spellcategorycooldown_4`, "
						<< "`spellid_5`, "
						<< "`spelltrigger_5`, "
						<< "`spellcharges_5`, "
						<< "`spellcooldown_5`, "
						<< "`spellcategory_5`, "
						<< "`spellcategorycooldown_5`, "
						<< "`bonding`, "
						<< "`description`, "
						<< "`PageText`, "
						<< "`LanguageID`, "
						<< "`PageMaterial`, "
						<< "`startquest`, "
						<< "`lockid`, "
						<< "`Material`, "
						<< "`sheath`, "
						<< "`RandomProperty`, "
						<< "`RandomSuffix`, "
						<< "`itemset`, "
						<< "`MaxDurability`, "
						<< "`area`, "
						<< "`Map`, "
						<< "`BagFamily`, "
						<< "`TotemCategory`, "
						<< "`socketColor_1`, "
						<< "`socketContent_1`, "
						<< "`socketColor_2`, "
						<< "`socketContent_2`, "
						<< "`socketColor_3`, "
						<< "`socketContent_3`, "
						<< "`socketBonus`, "
						<< "`GemProperties`, "
						<< "`ArmorDamageModifier`, "
						<< "`duration`, "
						<< "`ItemLimitCategory`, "
						<< "`HolidayId`, "
						<< "`StatScalingFactor`, "
						<< "`CurrencySubstitutionId`, "
						<< "`CurrencySubstitutionCount`, "
						<< "`flagsCustom`, "
						<< "`WDBVerified`) VALUES \n";
				} else
					this->fCacheStream << ", \n";
				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << entry << "',"
					<< " '" << _Class << "',"
					<< " '" << subclass << "',"
					<< " '" << SoundOverrideSubclass << "',"
					<< " '" << this->SafeSQLParams(name) << "',"
					<< " '" << displayid << "',"
					<< " '" << Quality << "',"
					<< " '" << Flags << "',"
					<< " '" << FlagsExtra << "',"
					<< " '" << Unk430_1 << "',"
					<< " '" << Unk430_2 << "',"
					<< " '" << BuyCount << "',"
					<< " '" << BuyPrice << "',"
					<< " '" << SellPrice << "',"
					<< " '" << InventoryType << "',"
					<< " '" << AllowableClass << "',"
					<< " '" << AllowableRace << "',"
					<< " '" << ItemLevel << "',"
					<< " '" << RequiredLevel << "',"
					<< " '" << RequiredSkill << "',"
					<< " '" << RequiredSkillRank << "',"
					<< " '" << requiredspell << "',"
					<< " '" << requiredhonorrank << "',"
					<< " '" << RequiredCityRank << "',"
					<< " '" << RequiredReputationFaction << "',"
					<< " '" << RequiredReputationRank << "',"
					<< " '" << maxcount << "',"
					<< " '" << stackable << "',"
					<< " '" << ContainerSlots << "',"
					<< " '" << stat_type1 << "',"
					<< " '" << stat_value1 << "',"
					<< " '" << stat_unk1_1 << "',"
					<< " '" << stat_unk2_1 << "',"
					<< " '" << stat_type2 << "',"
					<< " '" << stat_value2 << "',"
					<< " '" << stat_unk1_2 << "',"
					<< " '" << stat_unk2_2 << "',"
					<< " '" << stat_type3 << "',"
					<< " '" << stat_value3 << "',"
					<< " '" << stat_unk1_3 << "',"
					<< " '" << stat_unk2_3 << "',"
					<< " '" << stat_type4 << "',"
					<< " '" << stat_value4 << "',"
					<< " '" << stat_unk1_4 << "',"
					<< " '" << stat_unk2_4 << "',"
					<< " '" << stat_type5 << "',"
					<< " '" << stat_value5 << "',"
					<< " '" << stat_unk1_5 << "',"
					<< " '" << stat_unk2_5 << "',"
					<< " '" << stat_type6 << "',"
					<< " '" << stat_value6 << "',"
					<< " '" << stat_unk1_6 << "',"
					<< " '" << stat_unk2_6 << "',"
					<< " '" << stat_type7 << "',"
					<< " '" << stat_value7 << "',"
					<< " '" << stat_unk1_7 << "',"
					<< " '" << stat_unk2_7 << "',"
					<< " '" << stat_type8 << "',"
					<< " '" << stat_value8 << "',"
					<< " '" << stat_unk1_8 << "',"
					<< " '" << stat_unk2_8 << "',"
					<< " '" << stat_type9 << "',"
					<< " '" << stat_value9 << "',"
					<< " '" << stat_unk1_9 << "',"
					<< " '" << stat_unk2_9 << "',"
					<< " '" << stat_type10 << "',"
					<< " '" << stat_value10 << "',"
					<< " '" << stat_unk1_10 << "',"
					<< " '" << stat_unk2_10 << "',"
					<< " '" << ScalingStatDistribution << "',"
					<< " '" << DamageType << "',"
					<< " '" << delay << "',"
					<< " '" << RangedModRange << "',"
					<< " '" << spellid_1 << "',"
					<< " '" << spelltrigger_1 << "',"
					<< " '" << spellcharges_1 << "',"
					<< " '" << spellcooldown_1 << "',"
					<< " '" << spellcategory_1 << "',"
					<< " '" << spellcategorycooldown_1 << "',"
					<< " '" << spellid_2 << "',"
					<< " '" << spelltrigger_2 << "',"
					<< " '" << spellcharges_2 << "',"
					<< " '" << spellcooldown_2 << "',"
					<< " '" << spellcategory_2 << "',"
					<< " '" << spellcategorycooldown_2 << "',"
					<< " '" << spellid_3 << "',"
					<< " '" << spelltrigger_3 << "',"
					<< " '" << spellcharges_3 << "',"
					<< " '" << spellcooldown_3 << "',"
					<< " '" << spellcategory_3 << "',"
					<< " '" << spellcategorycooldown_3 << "',"
					<< " '" << spellid_4 << "',"
					<< " '" << spelltrigger_4 << "',"
					<< " '" << spellcharges_4 << "',"
					<< " '" << spellcooldown_4 << "',"
					<< " '" << spellcategory_4 << "',"
					<< " '" << spellcategorycooldown_4 << "',"
					<< " '" << spellid_5 << "',"
					<< " '" << spelltrigger_5 << "',"
					<< " '" << spellcharges_5 << "',"
					<< " '" << spellcooldown_5 << "',"
					<< " '" << spellcategory_5 << "',"
					<< " '" << spellcategorycooldown_5 << "',"
					<< " '" << bonding << "',"
					<< " '" << this->SafeSQLParams(description) << "',"
					<< " '" << PageText << "',"
					<< " '" << LanguageID << "',"
					<< " '" << PageMaterial << "',"
					<< " '" << startquest << "',"
					<< " '" << lockid << "',"
					<< " '" << Material << "',"
					<< " '" << sheath << "',"
					<< " '" << RandomProperty << "',"
					<< " '" << RandomSuffix << "',"
					<< " '" << itemset << "',"
					<< " '" << MaxDurability << "',"
					<< " '" << area << "',"
					<< " '" << Map << "',"
					<< " '" << BagFamily << "',"
					<< " '" << TotemCategory << "',"
					<< " '" << socketColor_1 << "',"
					<< " '" << socketContent_1 << "',"
					<< " '" << socketColor_2 << "',"
					<< " '" << socketContent_2 << "',"
					<< " '" << socketColor_3 << "',"
					<< " '" << socketContent_3 << "',"
					<< " '" << socketBonus << "',"
					<< " '" << GemProperties << "',"
					<< " '" << ArmorDamageModifier << "',"
					<< " '" << duration << "',"
					<< " '" << ItemLimitCategory << "',"
					<< " '" << HolidayId << "',"
					<< " '" << StatScalingFactor << "',"
					<< " '" << CurrencySubstitutionId << "',"
					<< " '" << CurrencySubstitutionCount << "',"
					<< " '" << flagsCustom << "',"
					<< " '" << WDBVerified << "')";

				//
				// Solo como comentario
				;
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    item_template exported.");
		} else
			return false;
		return true;
	}
	/// Author: Boris Cabrera
	/// <summary>
	/// Exportar todo lo referente a la tabla waypoint_data
	/// </summary>
	/// <param name="aId">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportWaypointData(uint32 aId, uint32 aPhaseMask, uint32 aMap, float aPosition_x, float aPosition_y, float aPosition_z)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `waypoint_data` WHERE id = '%u' ORDER BY id, point;", aId);

		//Add the delete
		this->fCacheStream
			<< "/* Step 3.4 Table  `waypoint_data` */\n"
			<< "SET @GUID := (SELECT `guid` FROM `creature` WHERE "
			<< "`position_x` REGEXP '" << aPosition_x << "' AND "
			<< "`position_y` REGEXP '" << aPosition_y << "' AND "
			<< "`position_z` REGEXP '" << aPosition_z << "' AND "
			<< "`phaseMask` = '" << aPhaseMask << "' AND "
			<< "`map` = '" << aMap << "');\n"
			<< "DELETE FROM  `waypoint_data` WHERE `id` = @GUID;\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 id             = _Fields[_Index++].GetUInt32();
				uint32 point          = _Fields[_Index++].GetUInt32();
				float position_x      = _Fields[_Index++].GetFloat();
				float position_y      = _Fields[_Index++].GetFloat();
				float position_z      = _Fields[_Index++].GetFloat();
				float orientation     = _Fields[_Index++].GetFloat();
				uint32 delay          = _Fields[_Index++].GetUInt32();
				uint32 move_flag      = _Fields[_Index++].GetUInt32();
				uint32 action         = _Fields[_Index++].GetUInt32();
				uint32 action_chance  = _Fields[_Index++].GetUInt32();
				uint32 wpguid         = _Fields[_Index++].GetUInt32();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream 
						<<"INSERT INTO `waypoint_data` ("
						<<"`id`,"
						<<"`point`,"
						<<"`position_x`,"
						<<"`position_y`,"
						<<"`position_z`,"
						<<"`orientation`,"
						<<"`delay`,"
						<<"`move_flag`,"
						<<"`action`,"
						<<"`action_chance`,"
						<<"`wpguid`) VALUES \n"; 
				} else
					this->fCacheStream << ", \n";
				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "(" << "@GUID" << ","
					<< " '" << point << "',"
					<< " '" << position_x << "',"
					<< " '" << position_y << "',"
					<< " '" << position_z << "',"
					<< " '" << orientation << "',"
					<< " '" << delay << "',"
					<< " '" << move_flag << "',"
					<< " '" << action << "',"
					<< " '" << action_chance << "',"
					<< " '" << wpguid << "')";

				//
				// Solo como comentario
				;
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    waypoint_data exported.");
		} else
			return false;
		return true;
	}	
	/// Author: Boris Cabrera
	/// <summary>
	/// Exportar todo lo referente a la tabla creature_summon_groups
	/// </summary>
	/// <param name="aSummonerId">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportCreatureSummonGroups(uint32 aSummonerId)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `creature_summon_groups` WHERE summonerId = '%u';", aSummonerId);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 3.3 Table  `creature_summon_groups` */\n"
			<< "DELETE FROM  `creature_summon_groups` WHERE `summonerId` = @ENTRY AND `summonerType` = 0;\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 summonerId      = _Fields[_Index++].GetUInt32();
				uint32 summonerType    = uint32(_Fields[_Index++].GetUInt8());
				uint32 groupId         = uint32(_Fields[_Index++].GetUInt8());
				uint32 entry           = _Fields[_Index++].GetUInt32();
				float  position_x      = _Fields[_Index++].GetFloat();
				float  position_y      = _Fields[_Index++].GetFloat();
				float  position_z      = _Fields[_Index++].GetFloat();
				float  orientation     = _Fields[_Index++].GetFloat();
				uint32 summonType      = uint32(_Fields[_Index++].GetUInt8());
				uint32 summonTime      = _Fields[_Index++].GetUInt32();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `creature_summon_groups` ("
						<< "`summonerId`,"
						<< "`summonerType`,"
						<< "`groupId`,"
						<< "`entry`,"
						<< "`position_x`,"
						<< "`position_y`,"
						<< "`position_z`,"
						<< "`orientation`,"
						<< "`summonType`,"
						<< "`summonTime`) VALUES \n";
				} else
					this->fCacheStream << ", \n";

				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << summonerId << "',"
					<< "(" << "@ENTRY" << ","
					<< " '" << summonerType << "',"
					<< " '" << groupId << "',"
					<< " '" << entry << "',"
					<< " '" << position_x << "',"
					<< " '" << position_y << "',"
					<< " '" << position_z << "',"
					<< " '" << orientation << "',"
					<< " '" << summonType << "',"
					<< " '" << summonTime << "')";

				//
				// Solo como comentario
				;
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    creature_summon_groups exported.");
		} else
			return false;
		return true;
	}
	/// Author: Boris Cabrera
	/// <summary>
	/// Exportar todo lo referente a la tabla creature_formations
	/// </summary>
	/// <param name="aCreatureFormations">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportCreatureFormations(uint32 aCreatureFormations, uint32 aPhaseMask, uint32 aMap, float aPosition_x, float aPosition_y, float aPosition_z)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `creature_formations` WHERE leaderGUID = '%u';", aCreatureFormations);

		//Add the delete
		this->fCacheStream
			<< "/* Step 3.1 Table  `creature_formations` */\n"
			<< "SET @GUID := (SELECT `guid` FROM `creature` WHERE "
			<< "`position_x` REGEXP '" << aPosition_x << "' AND "
			<< "`position_y` REGEXP '" << aPosition_y << "' AND "
			<< "`position_z` REGEXP '" << aPosition_z << "' AND "
			<< "`phaseMask` = '" << aPhaseMask << "' AND "
			<< "`map` = '" << aMap << "');\n"
			<< "DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;\n";


		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 leaderGUID 	 = _Fields[_Index++].GetUInt32();
				uint32 memberGUID	 = _Fields[_Index++].GetUInt32();
				float  dist          = _Fields[_Index++].GetFloat();
				float  angle         = _Fields[_Index++].GetFloat();
				uint32 groupAI       = _Fields[_Index++].GetUInt32();
				uint32 point_1       = uint32(_Fields[_Index++].GetUInt16());
				uint32 point_2       = uint32(_Fields[_Index++].GetUInt16());

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream 
						<<"INSERT INTO `creature_formations` ("
						<<"`leaderGUID`,"
						<<"`memberGUID`,"
						<<"`dist`,"
						<<"`angle`,"
						<<"`groupAI`,"
						<<"`point_1`,"
						<<"`point_2`) VALUES \n"; 
				} else
					this->fCacheStream << ", \n";

				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "(" << "@GUID" << ","
					<< " '" << memberGUID << "',"
					<< " '" << dist << "',"
					<< " '" << angle << "',"
					<< " '" << groupAI << "',"
					<< " '" << point_1 << "',"
					<< " '" << point_2 << "')";

				//
				// Solo como comentario
				//
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    creature_formations exported.");
		} else
			return false;
		return true;
	}
	/// Author: Lester Pastrana
	/// <summary>
	/// Exportar todo lo referente a la tabla creature_addon
	/// </summary>
	/// <param name="aCreatureGuid">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportCreatureAddon(uint32 aCreatureGuid, uint32 aPhaseMask, uint32 aMap, float aPosition_x, float aPosition_y, float aPosition_z)
	{
		std::list<uint64> _wayPointsToExport;

		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM creature_addon WHERE guid = '%u';", aCreatureGuid);

		//Add the delete
		this->fCacheStream
			//<< "/* Step 2.8 Table  `creature_addon` */\n"
			//<< "DELETE FROM `creature_addon` WHERE `guid` = "
			//<< "(SELECT `guid` FROM `creature` WHERE "
			//<< "`position_x` REGEXP '" << aPosition_x << "' AND "
			//<< "`position_y` REGEXP '" << aPosition_y << "' AND "
			//<< "`position_z` REGEXP '" << aPosition_z << "' AND "
			//<< "`phaseMask` = '" << aPhaseMask << "' AND "
			//<< "`map` = '" << aMap << "');\n";
			<< "/* Step 2.8 Table  `creature_addon` */\n"
			<< "SET @GUID := (SELECT `guid` FROM `creature` WHERE "
			<< "`position_x` REGEXP '" << aPosition_x << "' AND "
			<< "`position_y` REGEXP '" << aPosition_y << "' AND "
			<< "`position_z` REGEXP '" << aPosition_z << "' AND "
			<< "`phaseMask` = '" << aPhaseMask << "' AND "
			<< "`map` = '" << aMap << "');\n"
			<< "DELETE FROM `creature_addon` WHERE `guid` = @GUID;\n";


		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 guid					= _Fields[_Index++].GetUInt32();
				uint32 path_id				= _Fields[_Index++].GetUInt32();
				uint16 mount				= _Fields[_Index++].GetUInt16();
				uint32 bytes1               = _Fields[_Index++].GetUInt32();
				uint32 bytes2				= _Fields[_Index++].GetUInt32();
				uint32 emote				= _Fields[_Index++].GetUInt32();
				std::string auras			= _Fields[_Index++].GetString();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream 
						<<"INSERT INTO `creature_addon` ("
						<< "`guid`,"
						<<"`path_id`,"
						<<"`mount`,"
						<<"`bytes1`,"
						<<"`bytes2`,"
						<<"`emote`,"
						<<"`auras`) VALUES \n"; 
				} else
					this->fCacheStream << ", \n";
				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "(" << "@GUID" << ",";
				//
				// Insertar GUID si tiene path
				if (path_id != 0)
				{
					this->fCacheStream
						<< " " << "@GUID" << ",";
				}
				else
				{
					this->fCacheStream
						<< " '" << path_id << "',";
				}
				// 
				this->fCacheStream
					<< " '" << mount << "',"
					<< " '" << bytes1 << "',"
					<< " '" << bytes2 << "',"
					<< " '" << emote << "',"
					<< " '" << this->SafeSQLParams(auras) << "')";

				//
				// Solo como comentario
				;
				// Llenar la lista para Exportar los Waypoint Data que tenga la creatura por Creature addon
				if (path_id != 0)
					_wayPointsToExport.push_back(path_id);
			} while (_Result->NextRow());
			this->fCacheStream << "; \n\n";

			// Exportar los datos relacionados al GUID de la creatura.
			for (auto _cway : _wayPointsToExport)
			{
				//
				// Exportar los Waypoint Data que tenga la creatura por Creature addon
				this->exportWaypointData(_cway, aPhaseMask, aMap, aPosition_x, aPosition_y, aPosition_z);
			}
			// Clear the list.
			_wayPointsToExport.clear();

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";

			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    creature_addon exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla creature_model_info
	/// </summary>
	/// <param name="aCreatureEntryId">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportCreatureModelInfo(uint32 aCreatureEntryId)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT m1.* FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid  WHERE entry = '%u';", aCreatureEntryId);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 2.7 Table  `creature_model_info */\n"
			//<< "DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = " << aCreatureEntryId << ";\n";
			<< "DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 modelid				 = _Fields[_Index++].GetUInt32();
				float bounding_radius		 = _Fields[_Index++].GetFloat();
				float combat_reach	         = _Fields[_Index++].GetFloat();
				uint32 gender                = _Fields[_Index++].GetUInt32();
				uint32 modelid_other_gender  = _Fields[_Index++].GetUInt32();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream 
						<<"INSERT INTO `creature_model_info` ("
						<<"`modelid`,"
						<<"`bounding_radius`,"
						<<"`combat_reach`,"
						<<"`gender`,"
						<<"`modelid_other_gender`) VALUES \n"; 
				} else
					this->fCacheStream << ", \n";
				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << modelid << "',"
					<< " '" << bounding_radius << "',"
					<< " '" << combat_reach << "',"
					<< " '" << gender << "',"
					<< " '" << modelid_other_gender << "')";

				//
				// Solo como comentario
				;
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    creature_model_info exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla creature_template_addon
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportCreatureTemplateAddon(uint32 aTemplateAddon)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `creature_template_addon` WHERE entry = '%u';", aTemplateAddon);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 1.3 Table  creature_template_addon */\n"
			//<< "DELETE FROM creature_template_addon WHERE  `entry` = " << aTemplateAddon << ";\n";
			<< "DELETE FROM creature_template_addon WHERE  `entry` = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 entry		 = _Fields[_Index++].GetUInt32();
				uint32 path_id		 = _Fields[_Index++].GetUInt32();
				uint32 mount		 = _Fields[_Index++].GetUInt32();
				uint32 bytes1		 = _Fields[_Index++].GetUInt32();
				uint32 bytes2		 = _Fields[_Index++].GetUInt32();
				uint32 emote		 = _Fields[_Index++].GetUInt32();
				std::string auras	 = _Fields[_Index++].GetString();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream 
						<<"INSERT INTO `creature_template_addon` ("
						<<"`entry`,"
						<<"`path_id`,"
						<<"`mount`,"
						<<"`bytes1`,"
						<<"`bytes2`,"
						<<"`emote`,"
						<<"`auras`) VALUES \n"; 
				} else
					this->fCacheStream << ", \n";
				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << entry << "',"
					<< "(" << "@ENTRY" << ","
					<< " '" << path_id << "',"
					<< " '" << mount << "',"
					<< " '" << bytes1 << "',"
					<< " '" << bytes2 << "',"
					<< " '" << emote << "',"
					<< " '" << auras << "')";

				//
				// Solo como comentario
				;
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    creature_template_addon exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla gossip_menu_opcion
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportGossipMenuOption(uint32 aGossipMenuId)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `gossip_menu_option` WHERE menu_id = '%u';", aGossipMenuId);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 2.7 Table  `gossip_menu_option */\n"
			<< "DELETE FROM gossip_menu_option WHERE  `menu_id` = " << aGossipMenuId << ";\n";
		
		if (_Result)
		{
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 _Menu_id				= uint32(_Fields[_Index++].GetUInt16());
				uint32 _Id					= uint32(_Fields[_Index++].GetUInt16());
				uint32 _Option_icon			= _Fields[_Index++].GetUInt32();
				std::string _Option_text	= _Fields[_Index++].GetString();
				uint32 _Option_id			= uint32(_Fields[_Index++].GetUInt8());
				uint32 _Npc_option_npcflag	= _Fields[_Index++].GetUInt32();
				uint32 _Action_menu_id      = _Fields[_Index++].GetUInt32();
				uint32 _Action_poi_id		= _Fields[_Index++].GetUInt32();
				bool   _Box_coded			= _Fields[_Index++].GetBool();
				uint32 _Box_money			= _Fields[_Index++].GetUInt32();
				std::string _Box_text		= _Fields[_Index++].GetString();

				//
				// Agregar la query a la cache de almacenamiento.
				this->fCacheStream 
					<< "INSERT INTO `gossip_menu_option` ("
					<<"`menu_id`, "
					<<"`id`, "
					<<"`option_icon`, "
					<<"`option_text`, "
					<<"`option_id`, "
					<<"`npc_option_npcflag`, "
					<<"`action_menu_id`, "
					<<"`action_poi_id`, "
					<<"`box_coded`, "
					<<"`box_money`, "
					<<"`box_text`) VALUES \n"; 
				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << _Menu_id << "',"
					<< " '" << _Id << "',"
					<< " '" << _Option_icon << "',"
					<< " '" << this->SafeSQLParams(_Option_text) << "',"
					<< " '" << _Option_id << "',"
					<< " '" << _Npc_option_npcflag << "',"
					<< " '" << _Action_menu_id << "',"
					<< " '" << _Action_poi_id << "',"
					<< " '" << _Box_coded << "',"
					<< " '" << _Box_money << "',"
					<< " '" << this->SafeSQLParams(_Box_text)  << "');\n";

				if (_Action_menu_id != 0)
					exportGossipMenuOption(_Action_menu_id);

				//
				// Solo como comentario
				;
			} while (_Result->NextRow());

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    gossip_menu_opcion exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla npc_text
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportNpcText(uint32 aEntry)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `npc_text` WHERE ID = '%u';", aEntry);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 4.6 Table  `npc_text` */\n"
			<< "DELETE FROM npc_text WHERE `ID` = " << aEntry << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 ID                = _Fields[_Index++].GetUInt32();
				std::string text0_0      = _Fields[_Index++].GetString();
				std::string text0_1      = _Fields[_Index++].GetString();
				uint32 lang0    		 = uint32(_Fields[_Index++].GetUInt8());
				float prob0   		 	 = _Fields[_Index++].GetFloat();
				uint32 em0_0      		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em0_1     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em0_2     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em0_3    		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em0_4     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em0_5      		 = uint32(_Fields[_Index++].GetUInt16());
				std::string text1_0      = _Fields[_Index++].GetString();
				std::string text1_1      = _Fields[_Index++].GetString();
				uint32 lang1      		 = uint32(_Fields[_Index++].GetUInt8());
				float prob1      		 = _Fields[_Index++].GetFloat();
				uint32 em1_0      		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em1_1     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em1_2      		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em1_3     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em1_4     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em1_5     		 = uint32(_Fields[_Index++].GetUInt16());
				std::string text2_0      = _Fields[_Index++].GetString();
				std::string text2_1      = _Fields[_Index++].GetString();
				uint32 lang2     		 = uint32(_Fields[_Index++].GetUInt8());
				float prob2     		 = _Fields[_Index++].GetFloat();
				uint32 em2_0     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em2_1      	     = uint32(_Fields[_Index++].GetUInt16());
				uint32 em2_2      		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em2_3     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em2_4     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em2_5      		 = uint32(_Fields[_Index++].GetUInt16());
				std::string text3_0      = _Fields[_Index++].GetString();
				std::string text3_1      = _Fields[_Index++].GetString();
				uint32 lang3     		 = uint32(_Fields[_Index++].GetUInt8());
				float prob3      		 = _Fields[_Index++].GetFloat();
				uint32 em3_0      		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em3_1     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em3_2     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em3_3      		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em3_4     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em3_5     		 = uint32(_Fields[_Index++].GetUInt16());
				std::string text4_0      = _Fields[_Index++].GetString();
				std::string text4_1      = _Fields[_Index++].GetString();
				uint32 lang4     		 = uint32(_Fields[_Index++].GetUInt8());
				float prob4      		 = _Fields[_Index++].GetFloat();
				uint32 em4_0    		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em4_1    		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em4_2     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em4_3     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em4_4     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em4_5     		 = uint32(_Fields[_Index++].GetUInt16());
				std::string text5_0      = _Fields[_Index++].GetString();
				std::string text5_1      = _Fields[_Index++].GetString();
				uint32 lang5     		 = uint32(_Fields[_Index++].GetUInt8());
				float prob5     		 = _Fields[_Index++].GetFloat();
				uint32 em5_0   		     = uint32(_Fields[_Index++].GetUInt16());
				uint32 em5_1    		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em5_2    		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em5_3     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em5_4     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em5_5      		 = uint32(_Fields[_Index++].GetUInt16());
				std::string text6_0      = _Fields[_Index++].GetString();
				std::string text6_1      = _Fields[_Index++].GetString();
				uint32 lang6     		 = uint32(_Fields[_Index++].GetUInt8());
				float prob6     		 = _Fields[_Index++].GetFloat();
				uint32 em6_0    		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em6_1     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em6_2     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em6_3     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em6_4     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em6_5      		 = uint32(_Fields[_Index++].GetUInt16());
				std::string text7_0      = _Fields[_Index++].GetString();
				std::string text7_1      = _Fields[_Index++].GetString();
				uint32 lang7      		 = uint32(_Fields[_Index++].GetUInt8());
				float prob7     		 = _Fields[_Index++].GetFloat();
				uint32 em7_0     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em7_1     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em7_2     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em7_3     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em7_4     		 = uint32(_Fields[_Index++].GetUInt16());
				uint32 em7_5     		 = uint32(_Fields[_Index++].GetUInt16());
				int32 WDBVerified       = _Fields[_Index++].GetInt32();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream 
						<< "INSERT INTO `npc_text` ("
						<< "`ID`,"
						<< "`text0_0`,"
						<< "`text0_1`,"
						<< "`lang0`,"
						<< "`prob0`,"
						<< "`em0_0`,"
						<< "`em0_1`,"
						<< "`em0_2`,"
						<< "`em0_3`,"
						<< "`em0_4`,"
						<< "`em0_5`,"
						<< "`text1_0`,"
						<< "`text1_1`,"
						<< "`lang1`,"
						<< "`prob1`,"
						<< "`em1_0`,"
						<< "`em1_1`,"
						<< "`em1_2`,"
						<< "`em1_3`,"
						<< "`em1_4`,"
						<< "`em1_5`,"
						<< "`text2_0`,"
						<< "`text2_1`,"
						<< "`lang2`,"
						<< "`prob2`,"
						<< "`em2_0`,"
						<< "`em2_1`,"
						<< "`em2_2`,"
						<< "`em2_3`,"
						<< "`em2_4`,"
						<< "`em2_5`,"
						<< "`text3_0`,"
						<< "`text3_1`,"
						<< "`lang3`,"
						<< "`prob3`,"
						<< "`em3_0`,"
						<< "`em3_1`,"
						<< "`em3_2`,"
						<< "`em3_3`,"
						<< "`em3_4`,"
						<< "`em3_5`,"
						<< "`text4_0`,"
						<< "`text4_1`,"
						<< "`lang4`,"
						<< "`prob4`,"
						<< "`em4_0`,"
						<< "`em4_1`,"
						<< "`em4_2`,"
						<< "`em4_3`,"
						<< "`em4_4`,"
						<< "`em4_5`,"
						<< "`text5_0`,"
						<< "`text5_1`,"
						<< "`lang5`,"
						<< "`prob5`,"
						<< "`em5_0`,"
						<< "`em5_1`,"
						<< "`em5_2`,"
						<< "`em5_3`,"
						<< "`em5_4`,"
						<< "`em5_5`,"
						<< "`text6_0`,"
						<< "`text6_1`,"
						<< "`lang6`,"
						<< "`prob6`,"
						<< "`em6_0`,"
						<< "`em6_1`,"
						<< "`em6_2`,"
						<< "`em6_3`,"
						<< "`em6_4`,"
						<< "`em6_5`,"
						<< "`text7_0`,"
						<< "`text7_1`,"
						<< "`lang7`,"
						<< "`prob7`,"
						<< "`em7_0`,"
						<< "`em7_1`,"
						<< "`em7_2`,"
						<< "`em7_3`,"
						<< "`em7_4`,"
						<< "`em7_5`,"
						<< "`WDBVerified`) VALUES \n";
				} else
					this->fCacheStream << ", \n";

				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << ID << "',"
					<< " '" << SafeSQLParams(text0_0) << "',"
					<< " '" << SafeSQLParams(text0_1) << "',"
					<< " '" << lang0 << "',"
					<< " '" << prob0 << "',"
					<< " '" << em0_0 << "',"
					<< " '" << em0_1 << "',"
					<< " '" << em0_2 << "',"
					<< " '" << em0_3 << "',"
					<< " '" << em0_4 << "',"
					<< " '" << em0_5 << "',"
					<< " '" << SafeSQLParams(text1_0) << "',"
					<< " '" << SafeSQLParams(text1_1) << "',"
					<< " '" << lang1 << "',"
					<< " '" << prob1 << "',"
					<< " '" << em1_0 << "',"
					<< " '" << em1_1 << "',"
					<< " '" << em1_2 << "',"
					<< " '" << em1_3 << "',"
					<< " '" << em1_4 << "',"
					<< " '" << em1_5 << "',"
					<< " '" << SafeSQLParams(text2_0) << "',"
					<< " '" << SafeSQLParams(text2_1) << "',"
					<< " '" << lang2 << "',"
					<< " '" << prob2 << "',"
					<< " '" << em2_0 << "',"
					<< " '" << em2_1 << "',"
					<< " '" << em2_2 << "',"
					<< " '" << em2_3 << "',"
					<< " '" << em2_4 << "',"
					<< " '" << em2_5 << "',"
					<< " '" << SafeSQLParams(text3_0) << "',"
					<< " '" << SafeSQLParams(text3_1) << "',"
					<< " '" << lang3 << "',"
					<< " '" << prob3 << "',"
					<< " '" << em3_0 << "',"
					<< " '" << em3_1 << "',"
					<< " '" << em3_2 << "',"
					<< " '" << em3_3 << "',"
					<< " '" << em3_4 << "',"
					<< " '" << em3_5 << "',"
					<< " '" << SafeSQLParams(text4_0) << "',"
					<< " '" << SafeSQLParams(text4_1) << "',"
					<< " '" << lang4 << "',"
					<< " '" << prob4 << "',"
					<< " '" << em4_0 << "',"
					<< " '" << em4_1 << "',"
					<< " '" << em4_2 << "',"
					<< " '" << em4_3 << "',"
					<< " '" << em4_4 << "',"
					<< " '" << em4_5 << "',"
					<< " '" << SafeSQLParams(text5_0) << "',"
					<< " '" << SafeSQLParams(text5_1) << "',"
					<< " '" << lang5 << "',"
					<< " '" << prob5 << "',"
					<< " '" << em5_0 << "',"
					<< " '" << em5_1 << "',"
					<< " '" << em5_2 << "',"
					<< " '" << em5_3 << "',"
					<< " '" << em5_4 << "',"
					<< " '" << em5_5 << "',"
					<< " '" << SafeSQLParams(text6_0) << "',"
					<< " '" << SafeSQLParams(text6_1) << "',"
					<< " '" << lang6 << "',"
					<< " '" << prob6 << "',"
					<< " '" << em6_0 << "',"
					<< " '" << em6_1 << "',"
					<< " '" << em6_2 << "',"
					<< " '" << em6_3 << "',"
					<< " '" << em6_4 << "',"
					<< " '" << em6_5 << "',"
					<< " '" << SafeSQLParams(text7_0) << "',"
					<< " '" << SafeSQLParams(text7_1) << "',"
					<< " '" << lang7 << "',"
					<< " '" << prob7 << "',"
					<< " '" << em7_0 << "',"
					<< " '" << em7_1 << "',"
					<< " '" << em7_2 << "',"
					<< " '" << em7_3 << "',"
					<< " '" << em7_4 << "',"
					<< " '" << em7_5 << "',"
					<< " '" << WDBVerified << "')";

				//
				// Solo como comentario
				;
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    npc_text exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla gossip_menu
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportGossipMenu(uint32 aEntry)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `gossip_menu` WHERE entry = '%u';", aEntry);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 2.7 Table  `gossip_menu */\n"
			<< "DELETE FROM gossip_menu WHERE  `entry` = " << aEntry << ";\n";

		if (_Result)
		{
			int _Rows = 0;
			bool _IsFirstTime = true;
			int* _Gossig = new int[_Result->GetRowCount()];

			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 entry      = _Fields[_Index++].GetUInt32();
			  	uint32 text_id    = _Fields[_Index++].GetUInt32();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream 
						<<"INSERT INTO `gossip_menu` ("
						<<"`entry`,"
						<<"`text_id`) VALUES \n"; 
				} else
					this->fCacheStream << ", \n";

				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "(" << entry << ","
					<< " " << text_id << ")";



				_Gossig[_Rows++] = text_id;
				//
				// Solo como comentario
				;
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			for (int i = 0; i < _Rows; i++)
				this->exportNpcText(_Gossig[i]);

			//
			// Eliminar el buffer creado
			delete[] _Gossig;
			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    gossip_menu exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla pet_levelstats
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportPetLevelstats(uint32 aEntry)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `pet_levelstats` WHERE creature_entry = '%u';", aEntry);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 2.6 Table  `pet_levelstats */\n"
			//<< "DELETE FROM pet_levelstats WHERE  `creature_entry` = " << aEntry << ";\n";
			<< "DELETE FROM pet_levelstats WHERE  `creature_entry` = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 creature_entry   = _Fields[_Index++].GetUInt32();
			  	uint32 level			= _Fields[_Index++].GetUInt32();
				uint32 hp				= _Fields[_Index++].GetUInt32();
				uint32 mana				= _Fields[_Index++].GetUInt32();
			  	uint32 armor			= _Fields[_Index++].GetUInt32();
				uint32 str				= _Fields[_Index++].GetUInt32();
				uint32 agi				= _Fields[_Index++].GetUInt32();
				uint32 sta				= _Fields[_Index++].GetUInt32();
				uint32 inte				= _Fields[_Index++].GetUInt32();
				uint32 spi				= _Fields[_Index++].GetUInt32();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream 
						<<"INSERT INTO `pet_levelstats` ("
						<<"`creature_entry`,"
						<<"`level`,"
						<<"`hp`,"
						<<"`mana`,"
						<<"`armor`,"
						<<"`str`,"
						<<"`agi`,"
						<<"`sta`,"
						<<"`inte`,"
						<<"`spi`) VALUES \n"; 
				} else
					this->fCacheStream << ", \n";

				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << creature_entry << "',"
					<< "(" << "@ENTRY" << ","
					<< " '" << level << "',"
					<< " '" << hp << "',"
					<< " '" << mana << "',"
					<< " '" << armor << "',"
					<< " '" << str << "',"
					<< " '" << agi << "',"
					<< " '" << sta << "',"
					<< " '" << inte << "',"
					<< " '" << spi << "')";

				//
				// Solo como comentario
				;
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    pet_levelstats exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla npc_spellclick_spells
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportNpcSpellclickSpells(uint32 aSpellclickSpells)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `npc_spellclick_spells` WHERE npc_entry = '%u';", aSpellclickSpells);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 2.5 Table  `npc_spellclick_spells */\n"
			//<< "DELETE FROM npc_spellclick_spells WHERE  `npc_entry` = " << aSpellclickSpells << ";\n";
			<< "DELETE FROM npc_spellclick_spells WHERE  `npc_entry` = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 npc_entry     = _Fields[_Index++].GetUInt32();
			  	uint32 spell_id      = _Fields[_Index++].GetUInt32();
				uint32 cast_flags    = _Fields[_Index++].GetUInt32();
				uint32 user_type     = _Fields[_Index++].GetUInt32();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream 
						<<"INSERT INTO `npc_spellclick_spells` ("
						<<"`npc_entry`,"
						<<"`spell_id`,"
						<<"`cast_flags`,"
						<<"`user_type`) VALUES \n"; 
				} else
					this->fCacheStream << ", " << " /*" << " Spell(" << spell_id << "): " << GetSpellNameByEntry(spell_id) << "*/" "\n";

				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << npc_entry << "',"
					<< "(" << "@ENTRY" << ","
					<< " '" << spell_id << "',"
					<< " '" << cast_flags << "',"
					<< " '" << user_type << "')";

				//
				// Solo como comentario
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    npc_spellclick_spells exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla skinning_loot_template
	/// </summary>
	/// <param name="aSkinningLootTemplate">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportSkinningLootTemplate(uint32 aSkinningLootTemplate, std::ostringstream &aDescriptions)
	{
		std::list<uint64> _itemsToExport;
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `skinning_loot_template` WHERE entry = '%u';", aSkinningLootTemplate);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 2.4 Table  `skinning_loot_template */\n"
			//<< "DELETE FROM skinning_loot_template WHERE  `entry` = " << aSkinningLootTemplate << ";\n";
			<< "DELETE FROM skinning_loot_template WHERE  `entry` = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 entry				 = _Fields[_Index++].GetUInt32();
			  	uint32 item					 = _Fields[_Index++].GetUInt32();
				float ChanceOrQuestChance    = _Fields[_Index++].GetFloat();;
				uint32 lootmode			     = uint32(_Fields[_Index++].GetUInt16());
			  	uint32 groupid			 	 = uint32(_Fields[_Index++].GetUInt8());
				int32 mincountOrRef          = _Fields[_Index++].GetInt32();
				int32 maxcount               = int32(_Fields[_Index++].GetUInt8());

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream 
						<<"INSERT INTO `skinning_loot_template` ("
						<<"`entry`,"
						<<"`item`,"
						<<"`ChanceOrQuestChance`,"
						<<"`lootmode`,"
						<<"`groupid`,"
						<<"`mincountOrRef`,"
						<<"`maxcount`) VALUES \n"; 
				} else
					this->fCacheStream << ", \n";

				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << entry << "',"
					<< "(" << "@ENTRY" << ","
					<< " '" << item << "',"
					<< " '" << ChanceOrQuestChance << "',"
					<< " '" << lootmode << "',"
					<< " '" << groupid << "',"
					<< " '" << mincountOrRef << "',"
					<< " '" << maxcount << "')";

				//
				// Solo como comentario
				//this->fCacheStream << "  /* Item(" << item << "): " << GetIntemName(item, true) << ", ItemLevel: " << GetItemLevel(item).str().c_str() << ", RequiredLevel: " << GetRequiredLevel(item).str().c_str() << ", ItemQuality: " << GetItemQuality(item) << " */";
				//
				// exportar los items
				_itemsToExport.push_back(item);
				//
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//

			//
			//Export items corectly sorted.
			for (auto _citem : _itemsToExport)
			{
				this->exportItemTemplate(_citem);
				if (ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(_citem))
				{
					aDescriptions
						<< itemProto->ItemId << "  " 
						<< itemProto->Quality << "  "
						<< GetItemQuality(_citem) << "  ";
					//Decent way to read item price.
					if (itemProto->SellPrice)
					{
						uint32 _gold = (itemProto->SellPrice / GOLD);
						uint32 _silv = ((itemProto->SellPrice % GOLD) / SILVER);
						uint32 _copp = ((itemProto->SellPrice % GOLD) % SILVER);
						aDescriptions
							<< _gold << "g " << _silv << "s " << _copp << "c  ";
					}
					aDescriptions
						<< itemProto->ItemLevel << "  "
						<< itemProto->RequiredLevel << "  "  
						<< itemProto->Name1 << "\n";
				}
			}

			// Clear the list.
			_itemsToExport.clear();	

			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    skinning_loot_template exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla pickpocketing_loot_template
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportPickpocketingLootTemplate(uint32 aPickpocketingLootTemplate, std::ostringstream &aDescriptions)
	{
		std::list<uint64> _itemsToExport;
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `pickpocketing_loot_template` WHERE entry = '%u';", aPickpocketingLootTemplate);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 2.3 Table  `pickpocketing_loot_template */\n"
			//<< "DELETE FROM pickpocketing_loot_template WHERE `entry` = " << aPickpocketingLootTemplate << ";\n";
			<< "DELETE FROM pickpocketing_loot_template WHERE `entry` = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 entry				 = _Fields[_Index++].GetUInt32();
			  	uint32 item					 = _Fields[_Index++].GetFloat();
				float ChanceOrQuestChance    = _Fields[_Index++].GetFloat();
				uint32 lootmode			     = uint32(_Fields[_Index++].GetUInt16());
			  	uint32 groupid			 	 = uint32(_Fields[_Index++].GetUInt8());
				int32 mincountOrRef          = _Fields[_Index++].GetUInt32();
				int32 maxcount               = int32(_Fields[_Index++].GetUInt8());

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream 
						<<"INSERT INTO `pickpocketing_loot_template` ("
						<<"`entry`,"
						<<"`item`,"
						<<"`ChanceOrQuestChance`,"
						<<"`lootmode`,"
						<<"`groupid`,"
						<<"`mincountOrRef`,"
						<<"`maxcount`) VALUES \n"; 
				} else
					this->fCacheStream << ", \n";

				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << entry << "',"
					<< "(" << "@ENTRY" << ","
					<< " '" << item << "',"
					<< " '" << ChanceOrQuestChance << "',"
					<< " '" << lootmode << "',"
					<< " '" << groupid << "',"
					<< " '" << mincountOrRef << "',"
					<< " '" << maxcount << "')";

				//
				// Solo como comentario
				//this->fCacheStream << "  /* Item(" << item << "): " << GetIntemName(item, true) << ", ItemLevel: " << GetItemLevel(item).str().c_str() << ", RequiredLevel: " << GetRequiredLevel(item).str().c_str() << ", ItemQuality: " << GetItemQuality(item) << " */";
				//
				// exportar los items
				_itemsToExport.push_back(item);
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//

			//
			//Export items corectly sorted.
			for (auto _citem : _itemsToExport)
			{
				this->exportItemTemplate(_citem);
				if (ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(_citem))
				{
					aDescriptions
						<< itemProto->ItemId << "  " 
						<< itemProto->Quality << "  "
						<< GetItemQuality(_citem) << "  ";
					//Decent way to read item price.
					if (itemProto->SellPrice)
					{
						uint32 _gold = (itemProto->SellPrice / GOLD);
						uint32 _silv = ((itemProto->SellPrice % GOLD) / SILVER);
						uint32 _copp = ((itemProto->SellPrice % GOLD) % SILVER);
						aDescriptions
							<< _gold << "g " << _silv << "s " << _copp << "c  ";
					}
					aDescriptions
						<< itemProto->ItemLevel << "  "
						<< itemProto->RequiredLevel << "  "  
						<< itemProto->Name1 << "\n";
				}
			}

			// Clear the list.
			_itemsToExport.clear();				

			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    pickpocketing_loot_template exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla creature_loot_currency
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportCreatureLootCurrency(uint32 aCreatureLootCurrency)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `creature_loot_currency` WHERE creature_id = '%u';", aCreatureLootCurrency);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 2.2 Table  `creature_loot_currency */\n"
			//<< "DELETE FROM creature_loot_currency WHERE  `creature_id` = " << aCreatureLootCurrency << ";\n";
			<< "DELETE FROM creature_loot_currency WHERE  `creature_id` = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 creature_id        = _Fields[_Index++].GetUInt32();
			  	uint32 CurrencyId1        = _Fields[_Index++].GetUInt32();
				uint32 CurrencyId2        = _Fields[_Index++].GetUInt32();
				uint32 CurrencyId3        = _Fields[_Index++].GetUInt32();
			  	uint32 CurrencyCount1     = _Fields[_Index++].GetUInt32();
				uint32 CurrencyCount2     = _Fields[_Index++].GetUInt32();
				uint32 CurrencyCount3     = _Fields[_Index++].GetUInt32();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `creature_loot_currency` ("
						<< "`creature_id`,"
						<< "`CurrencyId1`,"
						<< "`CurrencyId2`,"
						<< "`CurrencyId3`,"
						<< "`CurrencyCount1`,"
						<< "`CurrencyCount2`,"
						<< "`CurrencyCount3`) VALUES \n";
				} else
					this->fCacheStream << ", \n";

				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << creature_id << "',"
					<< "(" << "@ENTRY" << ","
					<< " '" << CurrencyId1 << "',"
					<< " '" << CurrencyId2 << "',"
					<< " '" << CurrencyId3 << "',"
					<< " '" << CurrencyCount1 << "',"
					<< " '" << CurrencyCount2 << "',"
					<< " '" << CurrencyCount3 << "')";

				//
				// Solo como comentario
				;
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    creature_onkill_reputation exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla creature_onkill_reputation
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportCreatureOnkillReputation(uint32 aCreatureOnkillReputation)
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `creature_onkill_reputation` WHERE creature_id = '%u';", aCreatureOnkillReputation);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 2.1 Table  `creature_onkill_reputation */\n"
			//<< "DELETE FROM creature_onkill_reputation WHERE `creature_id` = " << aCreatureOnkillReputation << ";\n";
			<< "DELETE FROM creature_onkill_reputation WHERE `creature_id` = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 creature_id            = _Fields[_Index++].GetUInt32();
				int32  RewOnKillRepFaction1   = int32(_Fields[_Index++].GetInt16());
				int32  RewOnKillRepFaction2   = int32(_Fields[_Index++].GetInt16());
				bool   MaxStanding1           = _Fields[_Index++].GetBool();
				uint32 IsTeamAward1           = uint32(_Fields[_Index++].GetUInt8());
				int32  RewOnKillRepValue1     = _Fields[_Index++].GetInt32();
				bool   MaxStanding2           = _Fields[_Index++].GetBool();
				uint32 IsTeamAward2           = uint32(_Fields[_Index++].GetUInt8());
				int32  RewOnKillRepValue2     = _Fields[_Index++].GetInt32();
				uint32 TeamDependent          = uint32(_Fields[_Index++].GetUInt8());

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream 
						<<"INSERT INTO `creature_onkill_reputation` ("
						<<"`creature_id`,"
						<<"`RewOnKillRepFaction1`,"
						<<"`RewOnKillRepFaction2`,"
						<<"`MaxStanding1`,"
						<<"`IsTeamAward1`,"
						<<"`RewOnKillRepValue1`,"
						<<"`MaxStanding2`,"
						<<"`IsTeamAward2`,"
						<<"`RewOnKillRepValue2`,"
						<<"`TeamDependent`) VALUES \n"; 
				} else
					this->fCacheStream << ", \n";

				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << creature_id << "',"
					<< "(" << "@ENTRY" << ","
					<< " '" << RewOnKillRepFaction1 << "',"
					<< " '" << RewOnKillRepFaction2 << "',"
					<< " '" << MaxStanding1 << "',"
					<< " '" << IsTeamAward1 << "',"
					<< " '" << RewOnKillRepValue1 << "',"
					<< " '" << MaxStanding2 << "',"
					<< " '" << IsTeamAward2 << "',"
					<< " '" << RewOnKillRepValue2 << "',"
					<< " '" << TeamDependent << "')";

				//
				// Solo como comentario
				;
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    creature_onkill_reputation exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla npc_trainer
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportNPCTrainer(uint32 aNPCTrainer)
	{
		uint32 _rowCount = 1;

		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `npc_trainer` WHERE entry = '%u';", aNPCTrainer);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 2.0 Table  `npc_trainer */\n"
			//<< "DELETE FROM npc_trainer WHERE `entry` = " << aNPCTrainer << ";\n";
			<< "DELETE FROM npc_trainer WHERE `entry` = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 entry		 = _Fields[_Index++].GetUInt32();
				int32  spell		 = _Fields[_Index++].GetInt32();
				uint32 spellcost	 = _Fields[_Index++].GetUInt32();
				uint32 reqskill		 = _Fields[_Index++].GetUInt32();
				uint32 reqskillvalue = _Fields[_Index++].GetUInt32();
				uint32 reqlevel		 = _Fields[_Index++].GetUInt32();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `npc_trainer` ("
						<< "`entry`, "
						<< "`spell`, "
						<< "`spellcost`, "
						<< "`reqskill`, "
						<< "`reqskillvalue`, "
						<< "`reqlevel`) VALUES \n";
				}

				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << entry << "',"
					<< "(" << "@ENTRY" << ","
					<< " '" << spell << "',"
					<< " '" << spellcost << "',"
					<< " '" << reqskill << "',"
					<< " '" << reqskillvalue << "',"
					<< " '" << reqlevel << "')";

				//
				// 
				if (_Result->GetRowCount() == _rowCount)
					this->fCacheStream << "; ";
				else
					this->fCacheStream << ", ";

				//
				// Solo como comentario
				this->fCacheStream << " /*" << " Spell(" << spell << "): " << GetSpellNameByEntry(spell) << "*/\n";

				//
				//
				_rowCount++;
			} while (_Result->NextRow());

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    npc_trainer exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla npc_vendor
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportNPCVendor(uint32 aNPCVendor)		// se pasa el entry o el guid de la criatura
	{
		std::list<uint64> _itemsToExport;
		uint32 _rowCount = 1;

		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `npc_vendor` WHERE entry = '%u';", aNPCVendor);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 1.9 Table  `npc_vendor */\n"
			//<< "DELETE FROM npc_vendor WHERE  `entry` = " << aNPCVendor << ";\n";
			<< "DELETE FROM npc_vendor WHERE  `entry` = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 entry         = _Fields[_Index++].GetUInt32();
			  	uint32 slot          = _Fields[_Index++].GetUInt32();
				uint32 item          = _Fields[_Index++].GetUInt32();
				uint32 maxcount      = _Fields[_Index++].GetUInt32();
			  	uint32 incrtime      = _Fields[_Index++].GetUInt32();
				uint32 ExtendedCost  = _Fields[_Index++].GetUInt32();
				uint32 type          = _Fields[_Index++].GetUInt32();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `npc_vendor` ("
						<< "`entry`,"
						<< "`slot`,"
						<< "`item`,"
						<< "`maxcount`,"
						<< "`incrtime`,"
						<< "`ExtendedCost`,"
						<< "`type`) VALUES \n";
				}

				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << entry << "',"
					<< "(" << "@ENTRY" << ","
					<< " '" << slot << "',"
					<< " '" << item << "',"
					<< " '" << maxcount << "',"
					<< " '" << incrtime << "',"
					<< " '" << ExtendedCost << "',"
					<< " '" << type << "')";

				//
				// 
				if (_Result->GetRowCount() == _rowCount)
					this->fCacheStream << "; ";
				else
					this->fCacheStream << ", ";

				//
				// Solo como comentario
				this->fCacheStream << "  /* Item(" << item << "): " << this->GetIntemName(item, true) << ", ItemLevel: " << GetItemLevel(item).str().c_str() << ", RequiredLevel: " << GetRequiredLevel(item).str().c_str() << ", ItemQuality: " << GetItemQuality(item) << " */\n";
				//
				// exportar los items
				_itemsToExport.push_back(item);
				//
				_rowCount++;
			} while (_Result->NextRow());

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//

			//
			//Export items corectly sorted.
			for (auto _citem : _itemsToExport)
				this->exportItemTemplate(_citem);

			// Clear the list.
			_itemsToExport.clear();				

			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    creature_npc_vendors exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla waypoints
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportWaypoints(uint32 aEntry)		// se pasa el entry o el guid de la criatura
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `waypoints` WHERE entry = '%u';", aEntry);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 1.8 Table  `waypoints */\n"
			//<< "DELETE FROM waypoints WHERE  `entry` = " << aEntry << ";\n";
			<< "DELETE FROM waypoints WHERE  `entry` = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 entry						= _Fields[_Index++].GetUInt32();
                uint32 pointid						= uint32(_Fields[_Index++].GetUInt16());
				float position_x					= _Fields[_Index++].GetFloat();
				float position_y					= _Fields[_Index++].GetFloat();
				float position_z					= _Fields[_Index++].GetFloat();
				std::string point_comment			= _Fields[_Index++].GetString();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `waypoints` ("
						<< "`entry`,"
						<< "`pointid`,"
						<< "`position_x`,"
						<< "`position_y`,"
						<< "`position_z`,"
						<< "`point_comment`) VALUES \n";
				} else
					this->fCacheStream << ", \n";

				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << entry << "',"
					<< "(" << "@ENTRY" << ","
					<< " '" << pointid << "',"
					<< " '" << position_x << "',"
					<< " '" << position_y << "',"
					<< " '" << position_z << "',"
					<< " '" << this->SafeSQLParams(point_comment) << "')";

				//
				// Solo como comentario
				;
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    waypoints exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla creature_text
	/// </summary>
	/// <modify by="Lester">Cambie NULO por guid </modify>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportCreature(uint32 aEntry)
	{
		// Extra data Struct
		struct guidExportEntry
		{
			uint64 guid;
			uint32 pHmS;
			uint32 cMap;
			float  posX;
			float  posY;
			float  posZ;
		};
		// Extra data vector
		std::vector<guidExportEntry> _guidExportVector;

		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `creature` WHERE id = '%u' ORDER BY `areaId`;", aEntry);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 1.7 Table  `creature */\n"
			//<< "DELETE FROM creature WHERE  `id` = " << aEntry << ";\n";
			<< "DELETE FROM creature WHERE  `id` = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			uint64 _Rows = _Result->GetRowCount();

			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 guid						= uint32(_Fields[_Index++].GetUInt32());
                uint32 id						= uint32(_Fields[_Index++].GetUInt32());
				uint32 map						= uint32(_Fields[_Index++].GetUInt16());
				uint32 zoneId					= uint32(_Fields[_Index++].GetUInt16());
				uint32 areaId					= uint32(_Fields[_Index++].GetUInt16());
				uint32 spawnMask				= _Fields[_Index++].GetUInt32();
				uint32 phaseMask				= _Fields[_Index++].GetUInt32();	
				uint32 modelid					= _Fields[_Index++].GetUInt32();
				int32 equipment_id				= _Fields[_Index++].GetInt32();
				float position_x				= _Fields[_Index++].GetFloat();
				float position_y				= _Fields[_Index++].GetFloat();
				float position_z				= _Fields[_Index++].GetFloat();
				float orientation				= _Fields[_Index++].GetFloat();
				uint32 spawntimesecs			= _Fields[_Index++].GetUInt32();
				float spawndist				    = _Fields[_Index++].GetFloat();
				uint32 currentwaypoint			= _Fields[_Index++].GetUInt32();	
				uint32 curhealth				= _Fields[_Index++].GetUInt32();
				uint32 curmana					= _Fields[_Index++].GetUInt32();
				uint32 MovementType				= uint32(_Fields[_Index++].GetUInt8());
				uint32 npcflag					= _Fields[_Index++].GetUInt32();
				uint32 npcflag2					= _Fields[_Index++].GetUInt32();
				uint32 unit_flags				= _Fields[_Index++].GetUInt32();
				uint32 unit_flags2				= _Fields[_Index++].GetUInt32();
				uint32 dynamicflags				= _Fields[_Index++].GetUInt32();
				bool isActive					= _Fields[_Index++].GetBool();
				int32 protec_anti_doublet		= _Fields[_Index++].GetInt32();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `creature` ("
						<< "`guid`,"
						<< "`id`,"
						<< "`map`,"
						<< "`zoneId`,"
						<< "`areaId`,"
						<< "`spawnMask`,"
						<< "`phaseMask`,"
						<< "`modelid`,"
						<< "`equipment_id`,"
						<< "`position_x`,"
						<< "`position_y`,"
						<< "`position_z`,"
						<< "`orientation`,"
						<< "`spawntimesecs`,"
						<< "`spawndist`, "
						<< "`currentwaypoint`,"
						<< "`curhealth`, "
						<< "`curmana`, "
						<< "`MovementType`, "
						<< "`npcflag`, "
						<< "`npcflag2`, "
						<< "`unit_flags`,"
						<< "`unit_flags2`,"
						<< "`dynamicflags`,"
						<< "`isActive`,"
						<< "`protec_anti_doublet`) VALUES \n";
				} else
					this->fCacheStream << ", \n";

				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << guid << "',"
					//<< " '" << id << "',"
					<< "(" << "NULL" << ","
					<< " " << "@ENTRY" << ","
					<< " '" << map << "',"
					<< " '" << this->GetZoneOrAreaID(map ,position_x, position_y, position_z, true)  << "',"
					<< " '" << this->GetZoneOrAreaID(map ,position_x, position_y, position_z, false) << "',"
					<< " '" << spawnMask << "',"
					<< " '" << phaseMask << "',"
					<< " '" << modelid << "',"
					<< " '" << equipment_id << "',"
					<< " '" << position_x << "',"
					<< " '" << position_y << "',"
					<< " '" << position_z << "',"
					<< " '" << orientation << "',"
					<< " '" << spawntimesecs << "',"
					<< " '" << spawndist << "',"
					<< " '" << currentwaypoint << "',"
					<< " '" << curhealth << "',"
					<< " '" << curmana << "',"
					<< " '" << MovementType << "',"
					<< " '" << npcflag << "',"
					<< " '" << npcflag2 << "',"
					<< " '" << unit_flags << "',"
					<< " '" << unit_flags2 << "',"
					<< " '" << dynamicflags << "',"
					<< " '" << isActive << "',"
					<< " '" << protec_anti_doublet << "')";

				//
				/*Extra DATA*/
				guidExportEntry _cd;
				{
					_cd.guid = guid;
					_cd.pHmS = phaseMask;
					_cd.cMap = map;
					_cd.posX = position_x;
					_cd.posY = position_y;
					_cd.posZ = position_z;
				}
				//
				//Fill the data vector.
				_guidExportVector.push_back(_cd);
				//
			} while (_Result->NextRow());
			this->fCacheStream << "; \n\n";
			
			// Exportar los datos relacionados al GUID de la creatura.
			for (auto cguid : _guidExportVector)
			{
				//
				// Exportar las creature_addon referente a dicha creature
				this->exportCreatureAddon(cguid.guid, cguid.pHmS, cguid.cMap, cguid.posX, cguid.posY, cguid.posZ);
				//
				// Exportar lo referente a creature formations
				this->exportCreatureFormations(cguid.guid, cguid.pHmS, cguid.cMap, cguid.posX, cguid.posY, cguid.posZ);
			}
			
			// Clear the list.
			_guidExportVector.clear();
			
			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    creature exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla creature_text
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportCreatureText(uint32 aEntry)
	{
		QueryResult _Result = WorldDatabase.PQuery(
			"SELECT  "
			"`entry`,  "
			"`groupid`,  "
			"`id`,  "
			"`text`,  "
			"`type`,  "
			"`language`,  "
			"`probability`,  "
			"`emote`,  "
			"`duration`,  "
			"`sound`,  "
			"`comment` "
			"FROM `creature_text` WHERE entry = '%u';", aEntry);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 1.6 Table  `creature_text */\n"
            //<< "DELETE FROM  `creature_text` WHERE `entry`= " << aEntry << ";\n";
			<< "DELETE FROM  `creature_text` WHERE `entry`= " << "@ENTRY" << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 entry          = _Fields[_Index++].GetUInt32();
			  	uint32 groupid        = uint32(_Fields[_Index++].GetUInt8());
				uint32 id             = uint32(_Fields[_Index++].GetUInt8());
				std::string text      = _Fields[_Index++].GetString();
				uint32 type           = uint32(_Fields[_Index++].GetUInt8());
				uint32 language       = uint32(_Fields[_Index++].GetUInt8());
				float probability     = _Fields[_Index++].GetFloat();
				uint32 emote          = _Fields[_Index++].GetUInt32();
				uint32 duration       = _Fields[_Index++].GetUInt32();
				uint32 sound          = _Fields[_Index++].GetUInt32();
				std::string comment   = _Fields[_Index++].GetString();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `creature_text` (`"
						<< "entry`, "
						<< "`groupid`, "
						<< "`id`, "
						<< "`text`, "
						<< "`type`, "
						<< "`language`, "
						<< "`probability`, "
						<< "`emote`, "
						<< "`duration`, "
						<< "`sound`, "
						<< "`comment`) VALUES \n";
				} else
					this->fCacheStream << ", \n";

				//
				// Insertar los parámetros.
				this->fCacheStream
					//<< "('" << entry << "',"
					<< "(" << "@ENTRY" << ","
					<< " '" << groupid << "',"
					<< " '" << id << "',"
					<< " '" << this->SafeSQLParams(text) << "',"
					<< " '" << type << "',"
					<< " '" << language << "',"
					<< " '" << probability << "',"
					<< " '" << emote << "',"
					<< " '" << duration << "',"
					<< " '" << sound << "',"
					<< " '" << this->SafeSQLParams(comment) << "')";

				//
				// Solo como comentario
				;
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    creature_text exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla creature_involvedrelation
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportCreatureInvolvedRelation(uint32 aCreatureIsQuestGiver, uint32 aQuestId) // Preguntar si se pasa el QuestGiver o el CreatureEntry
	{
		QueryResult _Result;
		uint32 _rowCount = 1;

		if(aCreatureIsQuestGiver != 0 && aQuestId == 0)
		{
			_Result = WorldDatabase.PQuery(
				"SELECT  "
				"`id`,  "
				"`quest` "
				"FROM `creature_involvedrelation` WHERE id = '%u';", aCreatureIsQuestGiver);

			//Add the delete
			this->fCacheStream 
				<< "/* Step 2.2 Table  `creature_involvedrelation */\n"
				//<< "DELETE FROM  `creature_involvedrelation` WHERE `id`= " << aCreatureIsQuestGiver << ";\n";
				<< "DELETE FROM  `creature_involvedrelation` WHERE `id`= " << "@ENTRY" << ";\n";

		} else if (aCreatureIsQuestGiver == 0 && aQuestId != 0)
		{
			 _Result = WorldDatabase.PQuery(
				"SELECT  "
				"`id`,  "
				"`quest` "
				"FROM `creature_involvedrelation` WHERE quest = '%u';", aQuestId);

			 //Add the delete
			this->fCacheStream 
				<< "/* Step 2.2 Table  `creature_involvedrelation */\n"
				<< "DELETE FROM  `creature_involvedrelation` WHERE `quest`= " << aQuestId << ";\n";

		} else
		{
			return false;
		}

		if (_Result)
		{
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 id      = _Fields[_Index++].GetUInt32();
				uint32 quest   = _Fields[_Index++].GetUInt32();

				if (_rowCount == 1)
				{
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `creature_involvedrelation` ("
						<< "`id`, "
						<< "`quest`) VALUES \n";
				}

				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << id << "',"
					<< " '" << quest << "')";

				//
				// 
				if (_Result->GetRowCount() == _rowCount)
					this->fCacheStream << "; ";
				else
					this->fCacheStream << ", ";
				
				//
				// Solo como comentario
				this->fCacheStream << " /* " << "Quest(" << quest << "): " << this->GetQuestNameByEntry(quest) <<" ,QuestMinLevel: " << this->GetQuestMinLevel(quest) <<" ,QuestProfession ID: " << this->GetQuestRequiredSkill(quest) << "[" << this->GetSkillNameByEntry(GetQuestRequiredSkill(quest)) << "]" << " */ \n";
				_rowCount++;
			} while (_Result->NextRow());
			
			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de un gobject.
			this->fHandler->PSendSysMessage("    creature_involvedrelation exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla creature_questrelation
	/// </summary>
	/// <param name="aCreatureIsQuestGiver">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportCreatureQuestRelation(uint32 aCreatureIsQuestGiver, uint32 aQuestId) // Preguntar si se pasa el QuestGiver o el CreatureEntry
	{
		QueryResult _Result;
		uint32 _rowCount = 1;

		if(aCreatureIsQuestGiver != 0 && aQuestId == 0)
		{
			_Result = WorldDatabase.PQuery(
				"SELECT  "
				"`id`,  "
				"`quest` "
				"FROM `creature_questrelation` WHERE id = '%u';", aCreatureIsQuestGiver);

			//Add the delete
			this->fCacheStream 
				<< "/* Step 2.2 Table  `creature_questrelation */\n"
				//<< "DELETE FROM  `creature_questrelation` WHERE `id`= " << aCreatureIsQuestGiver << ";\n";
				<< "DELETE FROM  `creature_questrelation` WHERE `id`= " << "@ENTRY" << ";\n";

		} else if (aCreatureIsQuestGiver == 0 && aQuestId != 0)
		{
			 _Result = WorldDatabase.PQuery(
				"SELECT  "
				"`id`,  "
				"`quest` "
				"FROM `creature_questrelation` WHERE quest = '%u';", aQuestId);

			 //Add the delete
			this->fCacheStream 
				<< "/* Step 2.2 Table  `creature_questrelation */\n"
				<< "DELETE FROM  `creature_questrelation` WHERE `quest`= " << aQuestId << ";\n";

		} else
		{
			return false;
		}

		if (_Result)
		{
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 id      = _Fields[_Index++].GetUInt32();
				uint32 quest   = _Fields[_Index++].GetUInt32();

				if (_rowCount == 1)
				{
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `creature_questrelation` ("
						<< "`id`, "
						<< "`quest`) VALUES \n";
				}

				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << id << "',"
					<< " '" << quest << "')";

				//
				// 
				if (_Result->GetRowCount() == _rowCount)
					this->fCacheStream << "; ";
				else
					this->fCacheStream << ", ";
				
				//
				// Solo como comentario
				this->fCacheStream << " /* " << "Quest(" << quest << "): " << this->GetQuestNameByEntry(quest) <<" ,QuestMinLevel: " << this->GetQuestMinLevel(quest) <<" ,QuestProfession ID: " << this->GetQuestRequiredSkill(quest) << "[" << this->GetSkillNameByEntry(GetQuestRequiredSkill(quest)) << "]" << " */ \n";
				_rowCount++;
			} while (_Result->NextRow());
			
			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de un gobject.
			this->fHandler->PSendSysMessage("    creature_questrelation exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla reference_loot_template
	/// </summary>
	/// <param name="aCreatureLootId">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportReferenceLootTemplate(uint32 aMinCountOrRef, std::ostringstream &aDescriptions)
	{
		std::list<uint64> _itemsToExport, _subLoot;
		QueryResult _Result = WorldDatabase.PQuery(
			"SELECT * FROM `reference_loot_template` WHERE entry = '%u';", aMinCountOrRef);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 1.4 Table  `creature_loot_template */\n"
			<< "DELETE FROM `reference_loot_template` WHERE `entry` = " << aMinCountOrRef << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 entry			    = _Fields[_Index++].GetUInt32();
				uint32 item					= _Fields[_Index++].GetUInt32();
				float  ChanceOrQuestChance  = _Fields[_Index++].GetFloat();
				uint32 lootmode             = uint32(_Fields[_Index++].GetUInt16());
				uint32 groupid			    = uint32(_Fields[_Index++].GetUInt8());
				int32  mincountOrRef        = _Fields[_Index++].GetInt32();
				int32 maxcount		        = int32(_Fields[_Index++].GetUInt8());

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `reference_loot_template` ("
						<< "`entry`, "
						<< "`item`, "
						<< "`ChanceOrQuestChance`, "
						<< "`lootmode`, "
						<< "`groupid`, "
						<< "`mincountOrRef`, "
						<< "`maxcount`) VALUES \n";
				} else
					this->fCacheStream << ", \n";
				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << entry << "',"
					<< " '" << item << "',"
					<< " '" << ChanceOrQuestChance << "',"
					<< " '" << lootmode << "',"
					<< " '" << groupid << "',"
					<< " '" << mincountOrRef << "',"
					<< " '" << maxcount << "')";

				//
				// Solo como comentario
				//this->fCacheStream << " /* Item(" << item << "): " << GetIntemName(item, true) << ", ItemLevel: " << GetItemLevel(item).str().c_str() << ", RequiredLevel: " << GetRequiredLevel(item).str().c_str() << ", ItemQuality: " << GetItemQuality(item) << " */";
				
				//
				// exportar los items
				if (mincountOrRef < 0)
					_subLoot.push_back(abs(mincountOrRef));
				else
					_itemsToExport.push_back(item);
				//
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			
			//
			// Description header.
			aDescriptions
				<< "\n/*Reference Loot Template Items Data: Id - Quality - SellPrice - ItemLevel - RequiredLevel - Name */\n/*\n";

			//
			//Export items corectly sorted.
			for (auto _citem : _itemsToExport)
			{
				this->exportItemTemplate(_citem);
				if (ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(_citem))
				{
					aDescriptions
						<< itemProto->ItemId << "  "
						<< itemProto->Quality << "  "
						<< GetItemQuality(_citem) << "  ";
					//Decent way to read item price.
					if (itemProto->SellPrice)
					{
						uint32 _gold = (itemProto->SellPrice / GOLD);
						uint32 _silv = ((itemProto->SellPrice % GOLD) / SILVER);
						uint32 _copp = ((itemProto->SellPrice % GOLD) % SILVER);
						aDescriptions
							<< _gold << "g " << _silv << "s " << _copp << "c  ";
					}
					aDescriptions
						<< itemProto->ItemLevel << "  "
						<< itemProto->RequiredLevel << "  "
						<< itemProto->Name1 << "\n";
				}
			}

			//
			// Comment end.
			aDescriptions
				<< "*/\n";

			//
			// Export referenced loot template.
			for (auto _cSub : _subLoot)
				exportReferenceLootTemplate(_cSub, aDescriptions);

			//
			// Clear the list.
			_itemsToExport.clear();
			_subLoot.clear();

			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    creature_loot_template exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla creature_loot_template
	/// </summary>
	/// <param name="aCreatureLootId">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportCreatureLootTemplate(uint32 aCreatureLootId, std::ostringstream &aDescriptions)
	{
		std::list<uint64> _itemsToExport;
		QueryResult _Result = WorldDatabase.PQuery(
			"SELECT "
			"`entry`, "
			"`item`, "
			"`ChanceOrQuestChance`, "
			"`lootmode`, "
			"`groupid`, "
			"`mincountOrRef`, "
			"`maxcount` "
			"FROM `creature_loot_template` WHERE entry = '%u';", aCreatureLootId);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 1.3 Table  `creature_loot_template */\n"
			<< "DELETE FROM `creature_loot_template` WHERE `entry` = " << aCreatureLootId << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			int32 _ReferencesIndex = 0;
			int32 *_References = new int32[_Result->GetRowCount()];
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 entry			    = _Fields[_Index++].GetUInt32();
				uint32 item					= _Fields[_Index++].GetUInt32();
				float  ChanceOrQuestChance  = _Fields[_Index++].GetFloat();
				uint32 lootmode             = uint32(_Fields[_Index++].GetUInt16());
				uint32 groupid			    = uint32(_Fields[_Index++].GetUInt8());
				int32  mincountOrRef        = _Fields[_Index++].GetInt32();
				int32 maxcount		        = int32(_Fields[_Index++].GetUInt8());

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `creature_loot_template` ("
						<< "`entry`, "
						<< "`item`, "
						<< "`ChanceOrQuestChance`, "
						<< "`lootmode`, "
						<< "`groupid`, "
						<< "`mincountOrRef`, "
						<< "`maxcount`) VALUES \n";
				} else
					this->fCacheStream << ", \n";

				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << entry << "',"
					<< " '" << item << "',"
					<< " '" << ChanceOrQuestChance << "',"
					<< " '" << lootmode << "',"
					<< " '" << groupid << "',"
					<< " '" << mincountOrRef << "',"
					<< " '" << maxcount << "')";

				//
				// Solo como comentario
				//this->fCacheStream << " /* Item(" << item << "): " << GetIntemName(item, true) << ", ItemLevel: " << GetItemLevel(item).str().c_str() << ", RequiredLevel: " << GetRequiredLevel(item).str().c_str() << ", ItemQuality: " << GetItemQuality(item) << " */";
				//
				// exportar los reference templates
				if (mincountOrRef < 0) {
					_References[_ReferencesIndex] = mincountOrRef;
					_ReferencesIndex++;
				}
				// exportar los items
				if (mincountOrRef > 0)
					_itemsToExport.push_back(item);
				//
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//

			//
			//Export items corectly sorted.
			for (auto _citem : _itemsToExport)
			{
				this->exportItemTemplate(_citem);
				if (ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(_citem))
				{
					aDescriptions
						<< itemProto->ItemId << "  " 
						<< itemProto->Quality << "  "
						<< GetItemQuality(_citem) << "  ";
					//Decent way to read item price.
					if (itemProto->SellPrice)
					{
						uint32 _gold = (itemProto->SellPrice / GOLD);
						uint32 _silv = ((itemProto->SellPrice % GOLD) / SILVER);
						uint32 _copp = ((itemProto->SellPrice % GOLD) % SILVER);
						aDescriptions
							<< _gold << "g " << _silv << "s " << _copp << "c  ";
					}
					aDescriptions
						<< itemProto->ItemLevel << "  "
						<< itemProto->RequiredLevel << "  "  
						<< itemProto->Name1 << "\n";
				}
			}

			//
			// Comment end.
			aDescriptions
				<< "*/\n";

			//
			// Export Reference Loot Template
			for (int i = 0; i < _ReferencesIndex; i++)
				this->exportReferenceLootTemplate(abs(_References[i]), aDescriptions);

			delete[] _References;

			// Clear the list.
			_itemsToExport.clear();	

			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    creature_loot_template exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla creature_equipment_id
	/// </summary>
	/// <param name="aCreatureEquipmentId">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportCreatureEquipTemplate(uint32 aCreatureEquipmentId)
	{
		QueryResult _Result = WorldDatabase.PQuery(
			"SELECT  "
			"`entry`,  "
			"`itemEntry1`,  "
			"`itemEntry2`,  "
			"`itemEntry3` "
			"FROM `creature_equip_template` WHERE entry = '%u';", aCreatureEquipmentId);

		//Add the delete
		this->fCacheStream
			<< "/* Step 1.2 Table `creature_equip_template */\n"
            << "DELETE FROM `creature_equip_template` WHERE `entry`= " << aCreatureEquipmentId << ";\n";

		if (_Result)
		{
			uint16 _Index = 0;
			Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

			//
			// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
			uint32 _Entry      = _Fields[_Index++].GetUInt32();
			uint32 itemEntry1 = _Fields[_Index++].GetUInt32();
			uint32 itemEntry2 = _Fields[_Index++].GetUInt32();
			uint32 itemEntry3 = _Fields[_Index++].GetUInt32();
			
			//
			// Agregar la query a la cache de almacenamiento.
			this->fCacheStream 
				<< "INSERT INTO `creature_equip_template` (`"
				<< "entry`, "
				<< "`itemEntry1`, "
				<< "`itemEntry2`, "
				<< "`itemEntry3`) VALUES \n";
			//
			// Insertar los parámetros.
			this->fCacheStream
				<< "('" << _Entry << "',"
				<< " '" << itemEntry1 << "',"
				<< " '" << itemEntry2 << "',"
				<< " '" << itemEntry3 <<"');";
			
			//
			// Solo como comentario
			if (itemEntry1 != 0 || itemEntry2 != 0 || itemEntry3 != 0)
			{
				this->fCacheStream << " /* ";
				if (itemEntry1 != 0)
					this->fCacheStream <<"[ItemEntry1(" << itemEntry1 << "): " << GetIntemName(itemEntry1, true) << "] ";
				if (itemEntry2 != 0)
					this->fCacheStream <<"[ItemEntry2(" << itemEntry2 << "): " << GetIntemName(itemEntry2, true) << "] ";
				if(itemEntry3 != 0)
					this->fCacheStream <<"[ItemEntry3(" << itemEntry3 << "): " << GetIntemName(itemEntry3, true) << "] ";

				this->fCacheStream << "*/";
			}

			//
			// Referencia a los otros valores a exportar.
			;

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    creature_equip_template exported.");
		} else
			return false;
		return true;
	}
	/// Author: 
	/// <summary>
	/// Exportar todo lo referente a la tabla creature_template
	/// </summary>
	/// <param name="aEntry">Identificador de la plantilla de la criatura.</param>
	/// <param name="aCreatureLootId">.</param>
	/// <param name="aCreatureEquipmentId">.</param>
	/// <param name="aCreatureIsQuestGiver">.</param>
	/// <param name="aGossipMenuIdTemplate">.</param>
	/// <param name="aCreatureName">.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportCreatureTemplate(uint32 aEntry, uint32 *aCreatureLootId, uint32 *aCreatureEquipmentId, uint32 *aCreatureIsQuestGiver, uint32 *aGossipMenuIdTemplate, std::string &aCreatureName)
	{
		QueryResult _Result = WorldDatabase.PQuery(
			  "SELECT * FROM `creature_template` WHERE entry = '%u';", aEntry);

		//Add the delete
		this->fCacheStream 
			<< "/* Step 1.1 Table  `creature_template` */\n"
			//<< "DELETE FROM `creature_template` WHERE `entry` = " << aEntry << ";\n";
			<< "DELETE FROM `creature_template` WHERE `entry` = " << "@ENTRY" << ";\n";

		if (_Result)
		{
			uint16 _Index = 0;
			Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

			//
			// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
			uint32 _Entry                 = _Fields[_Index++].GetUInt32();
			uint32 _Difficulty_entry_1    = _Fields[_Index++].GetUInt32();
			uint32 _Difficulty_entry_2    = _Fields[_Index++].GetUInt32(); 
			uint32 _Difficulty_entry_3    = _Fields[_Index++].GetUInt32(); 
			uint32 _Difficulty_entry_4	 = _Fields[_Index++].GetUInt32(); 
			uint32 _Difficulty_entry_5	 = _Fields[_Index++].GetUInt32();  
			uint32 _Difficulty_entry_6    = _Fields[_Index++].GetUInt32(); 
			uint32 _Difficulty_entry_7    = _Fields[_Index++].GetUInt32();
			uint32 _Difficulty_entry_8    = _Fields[_Index++].GetUInt32(); 
			uint32 _Difficulty_entry_9    = _Fields[_Index++].GetUInt32(); 
			uint32 _Difficulty_entry_10		= _Fields[_Index++].GetUInt32(); 
			uint32 _Difficulty_entry_11		= _Fields[_Index++].GetUInt32();  
			uint32 _Difficulty_entry_12		= _Fields[_Index++].GetUInt32();
			uint32 _Difficulty_entry_13		= _Fields[_Index++].GetUInt32(); 
			uint32 _Difficulty_entry_14		= _Fields[_Index++].GetUInt32(); 
			uint32 _Difficulty_entry_15		= _Fields[_Index++].GetUInt32(); 
			uint32 _KillCredit1				= _Fields[_Index++].GetUInt32();
			uint32 _KillCredit2				= _Fields[_Index++].GetUInt32(); 
			uint32 _Modelid1				= _Fields[_Index++].GetUInt32();
			uint32 _Modelid2				= _Fields[_Index++].GetUInt32(); 
			uint32 _Modelid3				= _Fields[_Index++].GetUInt32();
			uint32 _Modelid4				= _Fields[_Index++].GetUInt32();
			std::string _Name				= _Fields[_Index++].GetString();
			std::string _Subname			= _Fields[_Index++].GetString();
			std::string _IconName			= _Fields[_Index++].GetString();
			uint32 _Gossip_menu_id			= _Fields[_Index++].GetUInt32();
			uint32 _Minlevel				= uint32(_Fields[_Index++].GetUInt8());
			uint32 _Maxlevel				= uint32(_Fields[_Index++].GetUInt8()); 
			uint32 _Exp						= uint32(_Fields[_Index++].GetInt16());
			uint32 _Exp_unk					= uint32(_Fields[_Index++].GetUInt16());
			uint32 _Faction_A				= uint32(_Fields[_Index++].GetUInt16()); 
			uint32 _Faction_H				= uint32(_Fields[_Index++].GetUInt16()); 
			uint32 _Npcflag					= _Fields[_Index++].GetUInt32();
			uint32 _Npcflag2				= _Fields[_Index++].GetUInt32();
			float _Speed_walk				= _Fields[_Index++].GetFloat();
			float _Speed_run				= _Fields[_Index++].GetFloat();
			float _Speed_swim				= _Fields[_Index++].GetFloat();
			float _Speed_fly				= _Fields[_Index++].GetFloat();
			float _Scale					= _Fields[_Index++].GetFloat(); 
			uint32 _Rank					= uint32(_Fields[_Index++].GetUInt8());
			float _Mindmg					= _Fields[_Index++].GetFloat();
			float _Maxdmg					= _Fields[_Index++].GetFloat();
			uint32 _Dmgschool				= uint32(_Fields[_Index++].GetInt8());
			uint32 _Attackpower				= _Fields[_Index++].GetUInt32();
			float _Dmg_multiplier			= _Fields[_Index++].GetFloat();
			uint32 _Baseattacktime			= _Fields[_Index++].GetUInt32();
			uint32 _Rangeattacktime			= _Fields[_Index++].GetUInt32();
			uint32 _Unit_class				= uint32(_Fields[_Index++].GetUInt8());
			uint32 _Unit_flags				= _Fields[_Index++].GetUInt32(); 
			uint32 _Unit_flags2				= _Fields[_Index++].GetUInt32();
			uint32 _Dynamicflags				= _Fields[_Index++].GetUInt32();
			uint32 _Family					= uint32(_Fields[_Index++].GetUInt32());
			uint32 _Trainer_type				= uint32(_Fields[_Index++].GetUInt8());
			uint32 _Trainer_spell			= _Fields[_Index++].GetUInt32();
			uint32 _Trainer_class			= uint32(_Fields[_Index++].GetUInt8());
			uint32 _Trainer_race			= uint32(_Fields[_Index++].GetUInt8());
			float _Minrangedmg				= _Fields[_Index++].GetFloat();
			float _Maxrangedmg				= _Fields[_Index++].GetFloat();
			uint32 _Rangedattackpower		= uint32(_Fields[_Index++].GetUInt16());
			uint32 _Type					= uint32(_Fields[_Index++].GetUInt8());
			uint32 _Type_flags				= _Fields[_Index++].GetUInt32();
			uint32 _Type_flags2				= _Fields[_Index++].GetUInt32();
			uint32 _Lootid					= _Fields[_Index++].GetUInt32();  
			uint32 _Pickpocketloot			= _Fields[_Index++].GetUInt32();
			uint32 _Skinloot              = _Fields[_Index++].GetUInt32();
			int32 _Resistance1            = _Fields[_Index++].GetInt16();
			int32 _Resistance2            = _Fields[_Index++].GetInt16(); 
			int32 _Resistance3            = _Fields[_Index++].GetInt16();
			int32 _Resistance4            = _Fields[_Index++].GetInt16();
			int32 _Resistance5            = _Fields[_Index++].GetInt16();
			int32 _Resistance6            = _Fields[_Index++].GetInt16();
			uint32 _Spell1                = _Fields[_Index++].GetUInt32();
			uint32 _Spell2                = _Fields[_Index++].GetUInt32();
			uint32 _Spell3                = _Fields[_Index++].GetUInt32();
			uint32 _Spell4                = _Fields[_Index++].GetUInt32();
			uint32 _Spell5                = _Fields[_Index++].GetUInt32();
			uint32 _Spell6                = _Fields[_Index++].GetUInt32();
			uint32 _Spell7                = _Fields[_Index++].GetUInt32();
			uint32 _Spell8                = _Fields[_Index++].GetUInt32();
			uint32 _PetSpellDataId        = _Fields[_Index++].GetUInt32();
			uint32 _VehicleId             = _Fields[_Index++].GetUInt32();
			uint32 _Mingold               = _Fields[_Index++].GetUInt32();
			uint32 _Maxgold               = _Fields[_Index++].GetUInt32();
			std::string _AIName           = _Fields[_Index++].GetString();
			uint32 _MovementType          = uint32(_Fields[_Index++].GetUInt8());
			uint32 _InhabitType           = uint32(_Fields[_Index++].GetUInt8());
			float _HoverHeight            = _Fields[_Index++].GetFloat();
			float _Health_mod             = _Fields[_Index++].GetFloat();
			float _Mana_mod               = _Fields[_Index++].GetFloat();
			float _Mana_mod_extra         = _Fields[_Index++].GetFloat();
			float _Armor_mod              = _Fields[_Index++].GetFloat();
			bool _RacialLeader            = _Fields[_Index++].GetBool(); 
			uint32 _QuestItem1            = _Fields[_Index++].GetUInt32();
			uint32 _QuestItem2            = _Fields[_Index++].GetUInt32();
			uint32 _QuestItem3            = _Fields[_Index++].GetUInt32();
			uint32 _QuestItem4            = _Fields[_Index++].GetUInt32();
			uint32 _QuestItem5            = _Fields[_Index++].GetUInt32();
			uint32 _QuestItem6            = _Fields[_Index++].GetUInt32();
			uint32 _MovementId            = _Fields[_Index++].GetUInt32();
			bool _RegenHealth             = _Fields[_Index++].GetBool();
			uint32 _Equipment_id          = _Fields[_Index++].GetUInt32();
			uint32 _Mechanic_immune_mask  = _Fields[_Index++].GetUInt32();
			uint32 _Flags_extra           = _Fields[_Index++].GetUInt32();
			std::string _ScriptName       = _Fields[_Index++].GetCString();  
			int32 _WDBVerified            = _Fields[_Index++].GetInt32();

			aCreatureName = _Name;
			//
			// Agregar la query a la cache de almacenamiento.
			this->fCacheStream << "INSERT INTO `creature_template` (" 
				<< "`entry`, "
				<< "`difficulty_entry_1`, "
				<< "`difficulty_entry_2`, " 
				<< "`difficulty_entry_3`, "
				<< "`difficulty_entry_4`, "
				<< "`difficulty_entry_5`, "
				<< "`difficulty_entry_6`, "
				<< "`difficulty_entry_7`, "
				<< "`difficulty_entry_8`, "
				<< "`difficulty_entry_9`, "
				<< "`difficulty_entry_10`, " 
				<< "`difficulty_entry_11`, " 
				<< "`difficulty_entry_12`, " 
				<< "`difficulty_entry_13`, "
				<< "`difficulty_entry_14`, "
				<< "`difficulty_entry_15`, "
				<< "`KillCredit1`, "
				<< "`KillCredit2`, "
				<< "`modelid1`, "
				<< "`modelid2`, "
				<< "`modelid3`, "
				<< "`modelid4`, "
				<< "`name`, "
				<< "`subname`, "
				<< "`IconName`, " 
				<< "`gossip_menu_id`, " 
				<< "`minlevel`, " 
				<< "`maxlevel`, "
				<< "`exp`, "
				<< "`exp_unk`, "
				<< "`faction_A`, "
				<< "`faction_H`, " 
				<< "`npcflag`, " 
				<< "`npcflag2`, "
				<< "`speed_walk`, "
				<< "`speed_run`, "
				<< "`speed_swim`, "
				<< "`speed_fly`, "
				<< "`scale`, "
				<< "`rank`, " 
				<< "`mindmg`, "
				<< "`maxdmg`, "
				<< "`dmgschool`, "
				<< "`attackpower`, "
				<< "`dmg_multiplier`, "
				<< "`baseattacktime`, "
				<< "`rangeattacktime`, "
				<< "`unit_class`, "
				<< "`unit_flags`, "
				<< "`unit_flags2`, "
				<< "`dynamicflags`, "
				<< "`family`, "
				<< "`trainer_type`, "
				<< "`trainer_spell`, "
				<< "`trainer_class`, "
				<< "`trainer_race`, "
				<< "`minrangedmg`, "
				<< "`maxrangedmg`, "
				<< "`rangedattackpower`, "
				<< "`type`, "
				<< "`type_flags`, "
				<< "`type_flags2`, "
				<< "`lootid`, "
				<< "`pickpocketloot`, "
				<< "`skinloot`, "
				<< "`resistance1`, " 
				<< "`resistance2`, "
				<< "`resistance3`, "
				<< "`resistance4`, "
				<< "`resistance5`, "
				<< "`resistance6`, "
				<< "`spell1`, "
				<< "`spell2`, "
				<< "`spell3`, "
				<< "`spell4`, "
				<< "`spell5`, "
				<< "`spell6`, "
				<< "`spell7`, "
				<< "`spell8`, "
				<< "`PetSpellDataId`, "
				<< "`VehicleId`, "
				<< "`mingold`, "
				<< "`maxgold`, "
				<< "`AIName`, "
				<< "`MovementType`, "
				<< "`InhabitType`, "
				<< "`HoverHeight`, "
				<< "`Health_mod`, "
				<< "`Mana_mod`, "
				<< "`Mana_mod_extra`, "
				<< "`Armor_mod`, " 
				<< "`RacialLeader`, "
				<< "`questItem1`, "
				<< "`questItem2`, " 
				<< "`questItem3`, " 
				<< "`questItem4`, " 
				<< "`questItem5`, " 
				<< "`questItem6`, " 
				<< "`movementId`, " 
				<< "`RegenHealth`, "
				<< "`equipment_id`, "
				<< "`mechanic_immune_mask`, "
				<< "`flags_extra`, "
				<< "`ScriptName`, "
				<< "`WDBVerified`) VALUES \n";
			//
			// Insertar los parámetros.
			this->fCacheStream
				//<< "(" << _Entry << ","
				<< "(" << "@ENTRY" << ","
				<< " '" << _Difficulty_entry_1 << "'," 
				<< " '" << _Difficulty_entry_2 << "',"  
				<< " '" << _Difficulty_entry_3 << "',"  
				<< " '" << _Difficulty_entry_4 << "',"  
				<< " '" << _Difficulty_entry_5 << "',"   
				<< " '" << _Difficulty_entry_6 << "',"  
				<< " '" << _Difficulty_entry_7 << "'," 
				<< " '" << _Difficulty_entry_8 << "',"  
				<< " '" << _Difficulty_entry_9 << "',"  
				<< " '" << _Difficulty_entry_10 << "',"  
				<< " '" << _Difficulty_entry_11 << "',"   
				<< " '" << _Difficulty_entry_12 << "'," 
				<< " '" << _Difficulty_entry_13 << "',"  
				<< " '" << _Difficulty_entry_14 << "',"  
				<< " '" << _Difficulty_entry_15 << "',"  
				<< " '" << _KillCredit1 << "'," 
				<< " '" << _KillCredit2 << "',"  
				<< " '" << _Modelid1 << "'," 
				<< " '" << _Modelid2 << "',"  
				<< " '" << _Modelid3 << "'," 
				<< " '" << _Modelid4 << "'," 
				//<< " '" << this->SafeSQLParams(_Name) << "'," 
				<< " " << "@CREATURE" << ","
				<< " '" << this->SafeSQLParams(_Subname) << "'," 
				<< " '" << this->SafeSQLParams(_IconName) << "'," 
				<< " '" << _Gossip_menu_id << "'," 
				<< " '" << _Minlevel << "'," 
				<< " '" << _Maxlevel << "',"  
				<< " '" << _Exp << "'," 
				<< " '" << _Exp_unk << "',"  
				<< " '" << _Faction_A << "',"  
				<< " '" << _Faction_H << "'," 
				<< " '" << _Npcflag << "',"  
				<< " '" << _Npcflag2 << "',"  
				<< " '" << _Speed_walk << "'," 
				<< " '" << _Speed_run << "',"
				<< " '" << _Speed_swim << "',"
				<< " '" << _Speed_fly << "'," 
				<< " '" << _Scale << "',"  
				<< " '" << _Rank << "'," 
				<< " '" << _Mindmg << "'," 
				<< " '" << _Maxdmg << "'," 
				<< " '" << _Dmgschool << "',"  
				<< " '" << _Attackpower << "'," 
				<< " '" << _Dmg_multiplier << "'," 
				<< " '" << _Baseattacktime << "'," 
				<< " '" << _Rangeattacktime << "'," 
				<< " '" << _Unit_class << "'," 
				<< " '" << _Unit_flags << "',"  
				<< " '" << _Unit_flags2 << "'," 
				<< " '" << _Dynamicflags << "'," 
				<< " '" << _Family << "'," 
				<< " '" << _Trainer_type << "',"  
				<< " '" << _Trainer_spell << "',"  
				<< " '" << _Trainer_class << "'," 
				<< " '" << _Trainer_race << "',"  
				<< " '" << _Minrangedmg << "',"   
				<< " '" << _Maxrangedmg << "'," 
				<< " '" << _Rangedattackpower << "'," 
				<< " '" << _Type << "',"  
				<< " '" << _Type_flags << "'," 
				<< " '" << _Type_flags2 << "'," 
				<< " '" << _Lootid << "',"   
				<< " '" << _Pickpocketloot << "'," 
				<< " '" << _Skinloot << "'," 
				<< " '" << _Resistance1 << "',"   
				<< " '" << _Resistance2 << "',"  
				<< " '" << _Resistance3 << "'," 
				<< " '" << _Resistance4 << "'," 
				<< " '" << _Resistance5 << "'," 
				<< " '" << _Resistance6 << "'," 
				<< " '" << _Spell1 << "',"  
				<< " '" << _Spell2 << "',"  
				<< " '" << _Spell3 << "'," 
				<< " '" << _Spell4 << "',"  
				<< " '" << _Spell5 << "'," 
				<< " '" << _Spell6 << "'," 
				<< " '" << _Spell7 << "'," 
				<< " '" << _Spell8 << "'," 
				<< " '" << _PetSpellDataId << "'," 
				<< " '" << _VehicleId << "'," 
				<< " '" << _Mingold << "'," 
				<< " '" << _Maxgold << "'," 
				<< " '" << this->SafeSQLParams(_AIName) << "',"  
				<< " '" << _MovementType << "'," 
				<< " '" << _InhabitType << "',"  
				<< " '" << _HoverHeight << "'," 
				<< " '" << _Health_mod << "'," 
				<< " '" << _Mana_mod << "'," 
				<< " '" << _Mana_mod_extra << "'," 
				<< " '" << _Armor_mod << "'," 
				<< " '" << _RacialLeader << "',"  
				<< " '" << _QuestItem1 << "',"  
				<< " '" << _QuestItem2 << "'," 
				<< " '" << _QuestItem3 << "',"  
				<< " '" << _QuestItem4 << "',"  
				<< " '" << _QuestItem5 << "',"  
				<< " '" << _QuestItem6 << "',"  
				<< " '" << _MovementId << "',"  
				<< " '" << _RegenHealth << "'," 
				<< " '" << _Equipment_id << "'," 
				<< " '" << _Mechanic_immune_mask << "',"  
				<< " '" << _Flags_extra << "',"  
				<< " '" << this->SafeSQLParams(_ScriptName) << "',"   
				<< " '" << _WDBVerified << "');";

			//
			// Referencia a los otros valores a exportar.
			*aCreatureLootId = _Lootid;
			*aCreatureEquipmentId = _Equipment_id;
			*aCreatureIsQuestGiver = _Npcflag;
			*aGossipMenuIdTemplate = _Gossip_menu_id;

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";

			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("%s's creature_template exported.", _Name.c_str());
		} else
			return false;
		return true;
	}

	/// Author: Lester Pastrana
	/// <summary>
	/// Exportar todo lo referente a la tabla smart_scripts
	/// </summary>
	/// <param name="aEntry">.</param>
	/// <param name="aSourceType">Indica la fuente de donde procede e smart scrip si es de una criatura, un gameobject u otro origen.</param>
	/// <return>Si no hay errores true, false en otro caso.</return>
	bool exportSmartScripts(uint32 aEntry, uint16 aSourceType)		// se pasa el entry o el guid de la criatura
	{
		QueryResult _Result = WorldDatabase.PQuery("SELECT * FROM `smart_scripts` WHERE entryorguid = '%u' AND `source_type`= %u;", aEntry, aSourceType);

		//Add the delete
		this->fCacheStream
			<< "/* Step 1.6 Table  `smart_scripts` */\n"
			<< "DELETE FROM smart_scripts WHERE `entryorguid` = " << aEntry << " AND `source_type`= " << aSourceType << ";\n";

		if (_Result)
		{
			bool _IsFirstTime = true;
			do {
				uint16 _Index = 0;
				Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 entry = _Fields[_Index++].GetUInt32();
				uint16 source_type = _Fields[_Index++].GetUInt8();
				uint16 event_id = _Fields[_Index++].GetUInt16();
				uint16 link = _Fields[_Index++].GetUInt16();
				uint16 event_type = _Fields[_Index++].GetUInt8();
				uint16 event_phase_mask = _Fields[_Index++].GetUInt8();
				uint16 event_chance = _Fields[_Index++].GetUInt8();
				uint16 event_flags = _Fields[_Index++].GetUInt8();

				uint32 event_param1 = _Fields[_Index++].GetUInt32();
				uint32 event_param2 = _Fields[_Index++].GetUInt32();
				uint32 event_param3 = _Fields[_Index++].GetUInt32();
				uint32 event_param4 = _Fields[_Index++].GetUInt32();

				uint16 action_type = _Fields[_Index++].GetUInt8();
				uint32 action_param1 = _Fields[_Index++].GetUInt32();
				uint32 action_param2 = _Fields[_Index++].GetUInt32();
				uint32 action_param3 = _Fields[_Index++].GetUInt32();
				uint32 action_param4 = _Fields[_Index++].GetUInt32();
				uint32 action_param5 = _Fields[_Index++].GetUInt32();
				uint32 action_param6 = _Fields[_Index++].GetUInt32();

				uint32 target_type = _Fields[_Index++].GetUInt8();
				uint32 target_param1 = _Fields[_Index++].GetUInt32();
				uint32 target_param2 = _Fields[_Index++].GetUInt32();
				uint32 target_param3 = _Fields[_Index++].GetUInt32();
				float target_x = _Fields[_Index++].GetFloat();
				float target_y = _Fields[_Index++].GetFloat();
				float target_z = _Fields[_Index++].GetFloat();
				float target_o = _Fields[_Index++].GetFloat();

				std::string comment = _Fields[_Index++].GetString();

				if (_IsFirstTime)
				{
					_IsFirstTime = false;
					//
					// Agregar la query a la cache de almacenamiento.
					this->fCacheStream
						<< "INSERT INTO `smart_scripts` ("
						<< "`entryorguid`, `source_type`, `id`, `link`, `event_type`, `event_phase_mask`, "
						<< "`event_chance`, `event_flags`, `event_param1`, `event_param2`, `event_param3`, `event_param4`, "
						<< "`action_type`, `action_param1`, `action_param2`, `action_param3`, `action_param4`, `action_param5`, `action_param6`, "
						<< "`target_type`, `target_param1`, `target_param2`, `target_param3`, `target_x`, `target_y`, `target_z`, `target_o`, "
						<< "`comment`) VALUES \n";
				}
				else
					this->fCacheStream << ", \n";

				//
				// Insertar los parámetros.
				this->fCacheStream
					<< "('" << entry << "',"
					<< " '" << source_type << "',"
					<< " '" << event_id << "',"
					<< " '" << link << "',"
					<< " '" << event_type << "',"
					<< " '" << event_phase_mask << "',"
					<< " '" << event_chance << "',"
					<< " '" << event_flags << "',"
					<< " '" << event_param1 << "'," << " '" << event_param2 << "'," << " '" << event_param3 << "'," << " '" << event_param4 << "',"
					<< " '" << action_type << "',"
					<< " '" << action_param1 << "'," << " '" << action_param2 << "'," << " '" << action_param3 << "'," << " '" << action_param4 << "'," << " '" << action_param5 << "'," << " '" << action_param6 << "',"
					<< " '" << target_type << "',"
					<< " '" << target_param1 << "'," << " '" << target_param2 << "'," << " '" << target_param3 << "',"
					<< " '" << target_x << "'," << " '" << target_y << "'," << " '" << target_z << "'," << " '" << target_o << "',"
					<< " '" << this->SafeSQLParams(comment) << "')";

				//
				// Solo como comentario
				;
			} while (_Result->NextRow());
			this->fCacheStream << "; \n";

			//
			// Seperador (solo de bonito en el fichero)
			this->fCacheStream << "\n\n";
			//
			// Notificar al usuario q se exporto las opciones de menu de una criatura.
			this->fHandler->PSendSysMessage("    smart_scripts exported.");
		}
		else
			return false;
		return true;
	}

public:
	/// Author: 
    /// <summary>
    /// inicializa una nueva instancia de la clase.
    /// </summary>
    /// <param name="aHandler">Objeto de chat global usado para notificar al cliente cualquier evento.</param>
	CommandExportCreature(ChatHandler* aHandler)
	{
		this->fHandler = aHandler;
	}

	/// Author: Lester Pastrana
    /// <summary>
    /// Exporta todos los valores referentes a un determinado identificador de una criatura.
    /// </summary>
    /// <param name="aEntry">Identificador de la criatura</param>
	bool ExportToSQLFile(uint32 aEntry)
	{
		std::string _CreatureName;
		std::ostringstream _FileName;
		std::ostringstream _ItemsDescription;
			
		uint32 _StartTime = ::getMSTime();
		uint32 _CreatureEquipmentId, _CreatureLootId, _CreatureIsQuestGiver, _GossipMenuIdTemplate;

		// Limpiar el flujo y exportar todas las dependencias del identificador especificado.
		this->fCacheStream.clear();
		if (this->exportCreatureTemplate(aEntry, &_CreatureLootId, &_CreatureEquipmentId, &_CreatureIsQuestGiver, &_GossipMenuIdTemplate, _CreatureName))
		{
			if (_CreatureEquipmentId != 0)
				this->exportCreatureEquipTemplate(_CreatureEquipmentId);
			this->exportCreatureTemplateAddon(aEntry);
			this->exportCreatureModelInfo(aEntry);
			this->exportCreatureText(aEntry);
			
			this->exportSmartScripts(aEntry, 0); //this->fCacheStream << "/* Step 1.6 Table `smart_scripts` */\n\n";

			this->exportCreature(aEntry);

			this->fCacheStream << "/*## Step 2: Creature Loots ##########################################*/\n\n";

			_ItemsDescription 
				<< "/*Creature Loot Template Items Data: Id - Quality - SellPrice - ItemLevel - RequiredLevel - Name */\n"
				<< "/*\n";

			if (_CreatureLootId != 0)
				this->exportCreatureLootTemplate(_CreatureLootId, _ItemsDescription);

			
			this->exportCreatureLootCurrency(aEntry);
			this->exportCreatureOnkillReputation(aEntry);
			
			_ItemsDescription 
				<< "/*Pickpocketing Loot Template Items Data: Id - Quality - SellPrice - ItemLevel - RequiredLevel - Name */\n"
				<< "/*\n";

			this->exportPickpocketingLootTemplate(aEntry, _ItemsDescription);

			_ItemsDescription << "*/\n";
			
			_ItemsDescription 
				<< "/*Skinning Loot Template Items Data: Id - Quality - SellPrice - ItemLevel - RequiredLevel - Name */\n"
				<< "/*\n";

			this->exportSkinningLootTemplate(aEntry, _ItemsDescription);

			_ItemsDescription << "*/\n";

			this->fCacheStream << _ItemsDescription.str().c_str() << "\n\n";
			this->fCacheStream << "/*## Step 3: Creature Extras ##########################################*/\n\n";

			this->exportCreatureSummonGroups(aEntry);

			this->fCacheStream 	<< "/*## Step 4: Creature Gossip Menu Options #############################*/\n\n";

			this->exportGossipMenu(_GossipMenuIdTemplate);
			if (_GossipMenuIdTemplate != 0)
				this->exportGossipMenuOption(_GossipMenuIdTemplate);


			this->fCacheStream 	<< "/*## Step 5: Creature NPC Trainer / Vendor ############################*/\n\n";

			this->exportNPCTrainer(aEntry);
			this->exportNPCVendor(aEntry);

			this->fCacheStream 
				<< "/*## Step 6: Creature NPC Conditions ##################################*/\n\n"
				<< "/* Step 6.9 Table `conditions` */\n"
				<< "/*DELETE FROM  `conditions` WHERE `SourceTypeOrReferenceId` AND `SourceGroup`;\n"
				<< "*/\n\n"
				<< "/*## Step 7: Creature NPC Needs to Work ###############################*/\n\n";
			
			this->exportCreatureQuestRelation(aEntry, 0);
			this->exportCreatureInvolvedRelation(aEntry, 0);
			this->exportWaypoints(aEntry);
			this->exportNpcSpellclickSpells(aEntry);
			this->exportPetLevelstats(aEntry);

			_FileName << "Creature " << "[" << aEntry << "] " << CheckName(_CreatureName) << " " << ".sql";
			this->FlushToFile(_FileName.str(), aEntry, _CreatureName);
			//
			// Notificar q todo acabo ok
			this->fHandler->PSendSysMessage("%s creature exported in: %u ms.", _CreatureName.c_str(), ::getMSTime() - _StartTime);

			return true;
		}
		this->fHandler->PSendSysMessage("exported creature entry: %u error.", aEntry);
		return false;
	}
	/// Author: Lester Pastrana and Boris Cabrera
    /// <summary>
    /// Exporta todos los objetos del juego y sus derivados que posean el identificador dado.
    /// </summary>
    /// <param name="aEntry">Identificador de la criatura</param>
	bool ExportGameObjectToSQLFile(uint32 aEntry)
	{
		std::string _GameObjectName;
		std::ostringstream _FileName;
		std::ostringstream _ItemsDescription;
		uint32 _StartTime = ::getMSTime();
		if (this->exportGameObjectTemplate(aEntry, _GameObjectName))
		{
			this->exportGameObject(aEntry);
			this->fCacheStream 
				<< "/*## Step 2: GObject Loots ###########################################*/\n\n";
			this->exportGameobjectLootTemplate(aEntry, _ItemsDescription);
			this->fCacheStream 
				<<  "/* Step 2.6 GObject > Quest Items Data: ItemID - Quality - SellPrice - ItemLevel - RequiredLevel - Name */\n" << "/*\n"
				<< _ItemsDescription.str().c_str() << "\n\n\n";
			this->exportGameObjectQuestRelation(aEntry, 0);
			this->exportGameObjectInvolvedRelation(aEntry, 0);
			this->fCacheStream 
				<< "/*## Step 3: GObjects Conditions #####################################*/\n\n"
				<< "/*## Step 4: GObjects Needs to Work ##################################*/\n\n";

			//
			// Exportar para el fichero
			_FileName << "GameObject " << "[" << aEntry << "] " << CheckName(_GameObjectName) << ".sql";
			this->FlushToFile(_FileName.str(), aEntry, _GameObjectName);

			this->fHandler->PSendSysMessage("%s gameobject_template exported in: %u ms.", _GameObjectName.c_str(), ::GetMSTimeDiffToNow(_StartTime));
			return true;
		}
		this->fHandler->PSendSysMessage("exported gameobject_template entry: %u error.", aEntry);
		return false;
	}
	/// Author: Boris Cabrera
    /// <summary>
    /// Exporta todos los Quests del juego y sus derivados que posean el identificador dado.
    /// </summary>
    /// <param name="aEntry">Identificador de la mision</param>
	bool ExportQuestToSQLFile(uint32 aEntry)
	{
		std::string _QuestName;
		std::ostringstream _FileName;
		uint32 _StartTime = ::getMSTime();
		std::list<uint64> _rewardItems;

		if (this->exportQuestTemplate(aEntry, _QuestName))
		{
			this->fCacheStream << "/*## Step 2: Quest Givers ############################################*/\n\n";

			this->exportCreatureQuestRelation(0, aEntry);
			this->exportGameObjectQuestRelation(0, aEntry);
			
			this->fCacheStream << "/*## Step 3: Quest POIs ##############################################*/\n\n";

			this->exportQuestPoi(aEntry);
			this->exportQuestPoiPoints(aEntry);
													 
			this->fCacheStream << "/*## Step 3: Quest Scripts ##############################################*/\n\n";

			this->exportQuest_Start_Scripts(aEntry);
			this->exportQuest_End_Scripts(aEntry);

			this->fCacheStream << "/*## Step 4: Quest Receivers #########################################*/\n\n";

			this->exportCreatureInvolvedRelation(0, aEntry);
			this->exportGameObjectInvolvedRelation(0, aEntry);

			this->fCacheStream << "/*## Step 5: Quest Items Reward ######################################*/\n\n";
			this->fCacheStream << "/* Step 5.8 Reward Items Choice: Name - Quality - SellPrice - ItemLevel - RequiredLevel */\n";

			Quest const* _quest = sObjectMgr->GetQuestTemplate(aEntry);

			for (int i = 0; i < 6; i++)
			{
				if (i == 0)
					this->fCacheStream << "/*\n";

				if (_quest->RewardChoiceItemId[i] != 0)
					if (ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(_quest->RewardChoiceItemId[i]))
					{
						_rewardItems.push_back(itemProto->ItemId);
						this->fCacheStream 
						<< itemProto->ItemId << "  " 
						<< itemProto->Quality << "  "
						<< GetItemQuality(itemProto->ItemId) << "  ";
						if (itemProto->SellPrice)
						{
							uint32 _gold = (itemProto->SellPrice / GOLD);
							uint32 _silv = ((itemProto->SellPrice % GOLD) / SILVER);
							uint32 _copp = ((itemProto->SellPrice % GOLD) % SILVER);
							this->fCacheStream
								<< _gold << "g " << _silv << "s " << _copp << "c  ";
						}
						this->fCacheStream
						<< itemProto->ItemLevel << "  "
						<< itemProto->RequiredLevel << "  "  
						<< itemProto->Name1 << "\n";
					}
				
				if (i == 5)
					this->fCacheStream << "*/\n";
			}
			
			this->fCacheStream << "/* Step 5.9 Reward Items: Name - Quality - SellPrice - ItemLevel - RequiredLevel */\n";

			for (int i = 0; i < 4; i++)
			{
				if (i == 0)
					this->fCacheStream << "/*\n";

				if (_quest->RewardItemId[i] != 0)
					if (ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(_quest->RewardItemId[i]))
					{
						_rewardItems.push_back(itemProto->ItemId);
						this->fCacheStream 
						<< itemProto->ItemId << "  " 
						<< itemProto->Quality << "  "
						<< GetItemQuality(itemProto->ItemId) << "  ";
						if (itemProto->SellPrice)
						{
							uint32 _gold = (itemProto->SellPrice / GOLD);
							uint32 _silv = ((itemProto->SellPrice % GOLD) / SILVER);
							uint32 _copp = ((itemProto->SellPrice % GOLD) % SILVER);
							this->fCacheStream
								<< _gold << "g " << _silv << "s " << _copp << "c  ";
						}
						this->fCacheStream
						<< itemProto->ItemLevel << "  "
						<< itemProto->RequiredLevel << "  "  
						<< itemProto->Name1 << "\n";
					}
					 
				if (i == 3)
					this->fCacheStream << "*/\n";
			}
					
			this->fCacheStream << "/*## Step 6: Quest Conditions ########################################*/\n\n";

			
			this->fCacheStream << "/*## Step 7: Quest Needs to Work #####################################*/\n\n";

			//Export items.
			for(auto _rItem : _rewardItems)
				this->exportItemTemplate(_rItem);

			//
			// Exportar para el fichero
			_FileName << "Quest " << "[" << aEntry << "] " << CheckName(_QuestName) << ".sql";
			this->FlushToFile(_FileName.str(), aEntry, _QuestName);

			this->fHandler->PSendSysMessage("%s quest_template exported in: %u ms.", _QuestName.c_str(), ::GetMSTimeDiffToNow(_StartTime));
			return true;
		}
		this->fHandler->PSendSysMessage("exported quest_template entry: %u error.", aEntry);
		return false;
	}
	/// Author: Boris Cabrera
    /// <summary>
    /// Exporta todos los Items del juego y sus derivados que posean el identificador dado.
    /// </summary>
    /// <param name="aEntry">Identificador del Item</param>
	bool ExportItemToSQLFile(uint32 aEntry, ItemTemplate const* aItemTemplate, bool aDBorDBC /*true for db, false for dbc*/)
	{
		std::string _ItemName;
		std::ostringstream _FileName;
		uint32 _StartTime = ::getMSTime();

		if (aDBorDBC)
		{
			if (this->exportItemTemplate(aEntry))
			{
				this->fCacheStream << "/*## Items ######################################*/\n\n";
				this->fCacheStream << "/* Items: ItemID - Quality - SellPrice - ItemLevel - RequiredLevel - Name */\n";

				if (ItemTemplate const* itemProto = sObjectMgr->GetItemTemplate(aEntry))
				{
					this->fCacheStream
						<< "/*\n"
						<< itemProto->ItemId << "  "
						<< itemProto->Quality << "  "
						<< GetItemQuality(aEntry) << "  ";
					//Decent way to read item price.
					if (itemProto->SellPrice)
					{
						uint32 _gold = (itemProto->SellPrice / GOLD);
						uint32 _silv = ((itemProto->SellPrice % GOLD) / SILVER);
						uint32 _copp = ((itemProto->SellPrice % GOLD) % SILVER);
						this->fCacheStream
							<< _gold << "g " << _silv << "s " << _copp << "c  ";
					}
					this->fCacheStream
						<< itemProto->ItemLevel << "  "
						<< itemProto->RequiredLevel << "  "
						<< itemProto->Name1 << "\n"
						<< "*/\n";
					_ItemName = itemProto->Name1;
				}

				//
				// Exportar para el fichero
				_FileName << "[" << "Item" << "] " << "[" << aEntry << "] " << ".sql";
				this->FlushToFile(_FileName.str(), aEntry, _ItemName);

				this->fHandler->PSendSysMessage("%s item_template exported in: %u ms.", _ItemName.c_str(), ::GetMSTimeDiffToNow(_StartTime));
				return true;
			}
		}
		else
		{
			if (this->exportItemTemplateFromDBC(aEntry, aItemTemplate))
			{
				this->fCacheStream << "/*## Items ######################################*/\n\n";
				this->fCacheStream << "/* Items: ItemID - Quality - SellPrice - ItemLevel - RequiredLevel - Name */\n";

				if (ItemTemplate const* itemProto = aItemTemplate)
				{
					this->fCacheStream
						<< "/*\n"
						<< itemProto->ItemId << "  "
						<< itemProto->Quality << "  "
						<< GetItemQuality(aEntry) << "  ";
					//Decent way to read item price.
					if (itemProto->SellPrice)
					{
						uint32 _gold = (itemProto->SellPrice / GOLD);
						uint32 _silv = ((itemProto->SellPrice % GOLD) / SILVER);
						uint32 _copp = ((itemProto->SellPrice % GOLD) % SILVER);
						this->fCacheStream
							<< _gold << "g " << _silv << "s " << _copp << "c  ";
					}
					this->fCacheStream
						<< itemProto->ItemLevel << "  "
						<< itemProto->RequiredLevel << "  "
						<< itemProto->Name1 << "\n"
						<< "*/\n";
					_ItemName = itemProto->Name1;
				}

				//
				// Exportar para el fichero
				_FileName << "[" << "Item" << "] " << "[" << aEntry << "] " << ".sql";
				this->FlushToFile(_FileName.str(), aEntry, _ItemName);

				this->fHandler->PSendSysMessage("%s item_template exported in: %u ms.", _ItemName.c_str(), ::GetMSTimeDiffToNow(_StartTime));
				return true;
			}
		}
		this->fHandler->PSendSysMessage("exported item_template entry: %u error.", aEntry);
		return false;
	}
};

/*#####
# export_Commandscript
#####*/

class export_Commandscript : public CommandScript
{
    public:
        export_Commandscript() : CommandScript("export_Commandscript") { }

		ChatCommand* GetCommands() const
        {
			static ChatCommand exportCreatureCommandTable[] =
			{
				{ "all",            SEC_GAMEMASTER,     true,  &HandleExportCreatureAllCommand,    "", NULL },
                { "by_map",         SEC_GAMEMASTER,     true,  &HandleExportCreatureByMapCommand,  "", NULL },
                { "by_zone",        SEC_GAMEMASTER,     true,  &HandleExportCreatureByZoneCommand, "", NULL },
                { "by_area",        SEC_GAMEMASTER,     true,  &HandleExportCreatureByAreaCommand, "", NULL },
				{ "",               SEC_GAMEMASTER,     false, &HandleExportCreatureCommand,       "", NULL },
				{ NULL,             0,                  false, NULL,                               "", NULL }
			};

			static ChatCommand HandleExportItemCommandTable[] =
			{
				{ "all",            SEC_GAMEMASTER,     true,  &HandleExportItemtAllCommand,       "", NULL },
				{ "",               SEC_GAMEMASTER,     false, &HandleExportItemCommand,           "", NULL },
				{ NULL,                      0,         false, NULL,                               "", NULL }
			};

			static ChatCommand HandleExportQuestCommandTable[] =
			{
				{ "all",            SEC_GAMEMASTER,     true,  &HandleExportQuestAllCommand,       "", NULL },
				{ "",               SEC_GAMEMASTER,     false, &HandleExportQuestCommand,          "", NULL },
				{ NULL,                      0,         false, NULL,                               "", NULL }
			};

			static ChatCommand HandleExportGOCommandTable[] =
			{
				{ "all",            SEC_GAMEMASTER,     true,  &HandleExportGOAllCommand,          "", NULL },
                { "by_map",         SEC_GAMEMASTER,     true,  &HandleExportGOByMapCommand,        "", NULL },
                { "by_zone",        SEC_GAMEMASTER,     true,  &HandleExportGOByZoneCommand,       "", NULL },
                { "by_area",        SEC_GAMEMASTER,     true,  &HandleExportGOByAreaCommand,       "", NULL },
				{ "",               SEC_GAMEMASTER,     false, &HandleExportGOCommand,             "", NULL },
				{ NULL,                      0,         false, NULL,                               "", NULL }
			};

			static ChatCommand exportCommandTable[] =
			{
				{ "allowed_areas",  SEC_GAMEMASTER,     true,  &HandleExportAllowedAreasCommand, "", NULL },
				{ "position",       SEC_GAMEMASTER,     false, &HandleExportPositionCommand,     "", NULL },
				{ "creature",       SEC_GAMEMASTER,     false, NULL,                             "", exportCreatureCommandTable },
				{ "item",           SEC_GAMEMASTER,     false, NULL,                             "", HandleExportItemCommandTable },
				{ "quest",          SEC_GAMEMASTER,     false, NULL,                             "", HandleExportQuestCommandTable },
				{ "go",             SEC_GAMEMASTER,     false, NULL,                             "", HandleExportGOCommandTable },
				{ "",               SEC_GAMEMASTER,     false, NULL,		                     "", NULL },
				{ NULL,             0,                  false, NULL,                             "", NULL }
			};

			static ChatCommand commandTable[] =
            {
                { "export",     SEC_GAMEMASTER,     true, NULL,        "", exportCommandTable },
                { NULL,         0,                  false, NULL,       "", NULL }
            };
			return commandTable;
        }

		/// Author:Eddard
		/// <summary>
		/// Ejecuta el comando de exportación de coordenadas con identificador especificado La forma de ejecución es .export position
		/// </summary>
		/// <param name="handler"></param>
		/// <param name="args"></param>
		static bool HandleExportAllowedAreasCommand(ChatHandler* aHandler, char const* aArgs)
		{
			CommandExportCreature _Export(aHandler); 
			//SafeSQLParamsExt

			std::ostringstream _sql;
			// 
			for (uint32 i = 0; i < sAreaStore.GetNumRows(); ++i)           // Areaflag numbered from 0
			{
				if (AreaTableEntry const* _areaEntry = sAreaStore.LookupEntry(i))
				{
					//
					MapEntry const* _mapEntry = sMapStore.LookupEntry(_areaEntry->mapid);
					AreaTableEntry const* _zoneEntry = GetAreaEntryByAreaID(_areaEntry->zone);
					//
					_sql <<
						"INSERT INTO `allowed_areas` (`map_id`, `map_name`, `zone_id`, `zone_name`, `area_id`, `area_name`, `area_level`, `zone_min_level`, `zone_max_level`, `intanceType`, `expanNum`, `allowed_enter`,  `comment`) VALUES \n"
						<< "('" << _areaEntry->mapid << "', "
						// Map name
						<< "'" << _Export.SafeSQLParamsExt((_mapEntry ? _mapEntry->name : "<unnamed map>")) << "', "
						// Zone entry
						<< "'" << _areaEntry->zone << "', "
						<< "'" << _Export.SafeSQLParamsExt((_zoneEntry ? _zoneEntry->area_name : "<unnamed zone>")) << "', "
						// Area Data
						<< "'" << _areaEntry->ID << "', "
						<< "'" << _Export.SafeSQLParamsExt((_areaEntry->area_name ? _areaEntry->area_name : "<unnamed area>")) << "', "
						<< "'" << _areaEntry->area_level << "', "
						<< "'" << "1" << "', "
						<< "'" << "1" << "', "
						<< "'" << (_mapEntry ? _mapEntry->map_type : 255) << "', "
						<< "'" << (_mapEntry ? _mapEntry->addon : 255) << "', "
						<< "'" << "0" << "', "
						<< "'" << "" << "');\n";
				}
			}

			FILE* fout = fopen("allowed_areas_data.sql", "w");
			fprintf(fout, "%s\n", _sql.str().c_str());
			fclose(fout);
			return true;
		}
		/// Author:Eddard
		/// <summary>
		/// Ejecuta el comando de exportación de coordenadas con identificador especificado La forma de ejecución es .export position
		/// </summary>
		/// <param name="handler"></param>
		/// <param name="args"></param>
		static bool HandleExportPositionCommand(ChatHandler* aHandler, char const* aArgs)
		{
			Unit* target = aHandler->getSelectedUnit();

			std::ostringstream _positionData;
			float _posX, _posY, _posZ, _ori;
			uint32 _Map, _Zone, _Area;

			if (target)
			{
				// Basic Position Data.
				_posX = target->GetPositionX();
				_posY = target->GetPositionY();
				_posZ = target->GetPositionZ();
				_ori = target->GetOrientation();
				_Map = target->GetMapId();

				// Generate Zone and Area.
				CommadExportHelper commanHelper;
				_Zone = commanHelper.GetZoneOrAreaID(_Map, _posX, _posY, _posZ, true);
				_Area = commanHelper.GetZoneOrAreaID(_Map, _posX, _posY, _posZ, false);

				_positionData
					<< "\n"
					<< "/* PositionX, PositionY, PositionZ, Orientation, Map, Zone, Area */( " << target->GetName() << " )\n"
					<< _posX << ", " << _posY << ", " << _posZ << ", " << _ori << ", " << _Map << ", " << _Zone << ", " << _Area << "\n";

				/**/
				_positionData
					<< "\n"
					<< "UPDATE `allowed_areas` SET `allowed_enter`='1' WHERE (`area_id`='" << _Zone << "');\n"
					<< "UPDATE `allowed_areas` SET `allowed_enter`='1' WHERE (`zone_id`='" << _Zone << "');";
				/**/

				// Write File
				FILE* fout = fopen("Positions", "a");
				fprintf(fout, "%s\n", _positionData.str().c_str());
				fclose(fout);

				// Notify
				aHandler->PSendSysMessage("Position of %s exported to File \"Position\"", target->GetName());
			}

			return true;
		}
		/// Author:Eddard
		/// <summary>
		/// Ejecuta el comando de exportación todos los items
		/// </summary>
		/// <param name="handler"></param>
		/// <param name="args"></param>
		static bool HandleExportItemtAllCommand(ChatHandler* aHandler, const char* aArgs)
		{
			CommandExportCreature _Export(aHandler);
			//
			ItemTemplateContainer const* itemTemplateStore = sObjectMgr->GetItemTemplateStore();
			//
			std::ostringstream fCacheStream;
			//
			for (auto itr : *itemTemplateStore)
			{
				//
				ItemTemplate const* itemTemplate = &itr.second;
				//Add the delete
				fCacheStream 
					<< "/* " << _Export.SafeSQLParams(std::string(itemTemplate->Name1)) << " */\n"
					<< "DELETE FROM item_template WHERE entry = \'" << itr.first << "\';\n";
		
				//
				// Obtener cada uno de los parámetros de la tabla de la bd según sus indices
				uint32 entry                      = itemTemplate->ItemId;
				uint32 _Class                     = itemTemplate->Class;
				uint32 subclass                   = itemTemplate->SubClass;
				int32  SoundOverrideSubclass      = itemTemplate->SoundOverrideSubclass;
				std::string name                  = itemTemplate->Name1;
				uint32 displayid                  = itemTemplate->DisplayInfoID;
				uint32 Quality                    = itemTemplate->Quality;
				uint32 Flags                      = itemTemplate->Flags;
				uint32 FlagsExtra                 = itemTemplate->Flags2;
				float  Unk430_1                   = itemTemplate->Unk430_1;
				float  Unk430_2                   = itemTemplate->Unk430_2;
				uint32 BuyCount                   = itemTemplate->BuyCount;
				int32  BuyPrice                   = itemTemplate->BuyPrice;
				uint32 SellPrice                  = itemTemplate->SellPrice;
				uint32 InventoryType              = itemTemplate->InventoryType;
				int32  AllowableClass             = itemTemplate->AllowableClass;
				int32  AllowableRace              = itemTemplate->AllowableRace;
				uint32 ItemLevel                  = itemTemplate->ItemLevel;
				uint32 RequiredLevel              = itemTemplate->RequiredLevel == 4294967295 ? 0 : itemTemplate->RequiredLevel;
				uint32 RequiredSkill              = itemTemplate->RequiredSkill;
				uint32 RequiredSkillRank          = itemTemplate->RequiredSkillRank;
				uint32 requiredspell              = itemTemplate->RequiredSpell;
				uint32 requiredhonorrank          = itemTemplate->RequiredHonorRank;
				uint32 RequiredCityRank           = itemTemplate->RequiredCityRank;
				uint32 RequiredReputationFaction  = itemTemplate->RequiredReputationFaction;
				uint32 RequiredReputationRank     = itemTemplate->RequiredReputationRank;
				int32  maxcount                   = itemTemplate->MaxCount;
				int32  stackable                  = itemTemplate->Stackable;
				uint32 ContainerSlots             = itemTemplate->ContainerSlots;
				uint32 stat_type1                 = itemTemplate->ItemStat[0].ItemStatType > 255 ? 0 : itemTemplate->ItemStat[0].ItemStatType;
				int32  stat_value1                = itemTemplate->ItemStat[0].ItemStatValue;
				int32 stat_unk1_1                 = itemTemplate->ItemStat[0].ItemStatUnk1;
				int32 stat_unk2_1                 = itemTemplate->ItemStat[0].ItemStatUnk2;
				uint32 stat_type2                 = itemTemplate->ItemStat[1].ItemStatType > 255 ? 0 : itemTemplate->ItemStat[1].ItemStatType;;
				int32 stat_value2                 = itemTemplate->ItemStat[1].ItemStatValue;
				int32 stat_unk1_2                 = itemTemplate->ItemStat[1].ItemStatUnk1;
				int32 stat_unk2_2                 = itemTemplate->ItemStat[1].ItemStatUnk1;
				uint32 stat_type3                 = itemTemplate->ItemStat[2].ItemStatType > 255 ? 0 : itemTemplate->ItemStat[2].ItemStatType;;
				int32 stat_value3                 = itemTemplate->ItemStat[2].ItemStatValue;
				int32 stat_unk1_3                 = itemTemplate->ItemStat[2].ItemStatUnk1;
				int32 stat_unk2_3                 = itemTemplate->ItemStat[2].ItemStatUnk2;
				uint32 stat_type4                 = itemTemplate->ItemStat[3].ItemStatType > 255 ? 0 : itemTemplate->ItemStat[3].ItemStatType;;
				int32 stat_value4                 = itemTemplate->ItemStat[3].ItemStatValue;
				int32 stat_unk1_4                 = itemTemplate->ItemStat[3].ItemStatUnk1;
				int32 stat_unk2_4                 = itemTemplate->ItemStat[3].ItemStatUnk2;
				uint32 stat_type5                 = itemTemplate->ItemStat[4].ItemStatType > 255 ? 0 : itemTemplate->ItemStat[4].ItemStatType;;
				int32 stat_value5                 = itemTemplate->ItemStat[4].ItemStatValue;
				int32 stat_unk1_5                 = itemTemplate->ItemStat[4].ItemStatUnk1;
				int32 stat_unk2_5                 = itemTemplate->ItemStat[4].ItemStatUnk2;
				uint32 stat_type6                 = itemTemplate->ItemStat[5].ItemStatType > 255 ? 0 : itemTemplate->ItemStat[5].ItemStatType;;
				int32 stat_value6                 = itemTemplate->ItemStat[5].ItemStatValue;
				int32 stat_unk1_6                 = itemTemplate->ItemStat[5].ItemStatUnk1;
				int32 stat_unk2_6                 = itemTemplate->ItemStat[5].ItemStatUnk2;
				uint32 stat_type7                 = itemTemplate->ItemStat[6].ItemStatType > 255 ? 0 : itemTemplate->ItemStat[6].ItemStatType;;
				int32 stat_value7                 = itemTemplate->ItemStat[6].ItemStatValue;
				int32 stat_unk1_7                 = itemTemplate->ItemStat[6].ItemStatUnk1;
				int32 stat_unk2_7                 = itemTemplate->ItemStat[6].ItemStatUnk2;
				uint32 stat_type8                 = itemTemplate->ItemStat[7].ItemStatType > 255 ? 0 : itemTemplate->ItemStat[7].ItemStatType;;
				int32 stat_value8                 = itemTemplate->ItemStat[7].ItemStatValue;
				int32 stat_unk1_8                 = itemTemplate->ItemStat[7].ItemStatUnk1;
				int32 stat_unk2_8                 = itemTemplate->ItemStat[7].ItemStatUnk2;
				uint32 stat_type9                 = itemTemplate->ItemStat[8].ItemStatType > 255 ? 0 : itemTemplate->ItemStat[8].ItemStatType;;
				int32 stat_value9                 = itemTemplate->ItemStat[8].ItemStatValue;
				int32 stat_unk1_9                 = itemTemplate->ItemStat[8].ItemStatUnk1;
				int32 stat_unk2_9                 = itemTemplate->ItemStat[8].ItemStatUnk2;
				uint32 stat_type10                = itemTemplate->ItemStat[9].ItemStatType > 255 ? 0 : itemTemplate->ItemStat[9].ItemStatType;;
				int32 stat_value10                = itemTemplate->ItemStat[9].ItemStatValue;
				int32 stat_unk1_10                = itemTemplate->ItemStat[9].ItemStatUnk1;
				int32 stat_unk2_10                = itemTemplate->ItemStat[9].ItemStatUnk2;
				uint32 ScalingStatDistribution    = itemTemplate->ScalingStatDistribution;
				uint32 DamageType                 = itemTemplate->DamageType;
				uint32 delay                      = itemTemplate->Delay;
				float RangedModRange              = itemTemplate->RangedModRange;
				uint32 spellid_1                  = itemTemplate->Spells[0].SpellId;
				uint32 spelltrigger_1             = itemTemplate->Spells[0].SpellTrigger == 4294967295 ? 0 : itemTemplate->Spells[0].SpellTrigger;
				int32  spellcharges_1             = itemTemplate->Spells[0].SpellCharges;
				int32  spellcooldown_1            = itemTemplate->Spells[0].SpellCooldown;
				uint32 spellcategory_1            = itemTemplate->Spells[0].SpellCategory;
				int32  spellcategorycooldown_1    = itemTemplate->Spells[0].SpellCategoryCooldown;
				uint32 spellid_2                  = itemTemplate->Spells[1].SpellId;
				uint32 spelltrigger_2             = itemTemplate->Spells[1].SpellTrigger == 4294967295 ? 0 : itemTemplate->Spells[1].SpellTrigger;
				int32  spellcharges_2             = itemTemplate->Spells[1].SpellCharges;
				int32  spellcooldown_2            = itemTemplate->Spells[1].SpellCooldown;
				uint32 spellcategory_2            = itemTemplate->Spells[1].SpellCategory;
				int32  spellcategorycooldown_2    = itemTemplate->Spells[1].SpellCategoryCooldown;
				uint32 spellid_3                  = itemTemplate->Spells[2].SpellId;
				uint32 spelltrigger_3             = itemTemplate->Spells[2].SpellTrigger == 4294967295 ? 0 : itemTemplate->Spells[2].SpellTrigger;
				int32  spellcharges_3             = itemTemplate->Spells[2].SpellCharges;
				int32  spellcooldown_3            = itemTemplate->Spells[2].SpellCooldown;
				uint32 spellcategory_3            = itemTemplate->Spells[2].SpellCategory;
				int32  spellcategorycooldown_3    = itemTemplate->Spells[2].SpellCategoryCooldown;
				uint32 spellid_4                  = itemTemplate->Spells[3].SpellId;
				uint32 spelltrigger_4             = itemTemplate->Spells[3].SpellTrigger == 4294967295 ? 0 : itemTemplate->Spells[3].SpellTrigger;
				int32  spellcharges_4             = itemTemplate->Spells[3].SpellCharges;
				int32  spellcooldown_4            = itemTemplate->Spells[3].SpellCooldown;
				uint32 spellcategory_4            = itemTemplate->Spells[3].SpellCategory;
				int32  spellcategorycooldown_4    = itemTemplate->Spells[3].SpellCategoryCooldown;
				uint32 spellid_5                  = itemTemplate->Spells[4].SpellId;
				uint32 spelltrigger_5             = itemTemplate->Spells[4].SpellTrigger == 4294967295 ? 0 : itemTemplate->Spells[4].SpellTrigger;
				int32 spellcharges_5              = itemTemplate->Spells[4].SpellCharges;
				int32  spellcooldown_5            = itemTemplate->Spells[4].SpellCooldown;
				uint32 spellcategory_5            = itemTemplate->Spells[4].SpellCategory;
				int32  spellcategorycooldown_5    = itemTemplate->Spells[4].SpellCategoryCooldown;
				uint32 bonding                    = itemTemplate->Bonding;
				std::string description           = itemTemplate->Description;
				uint32 PageText                   = itemTemplate->PageText;
				uint32 LanguageID                 = itemTemplate->LanguageID;
				uint32 PageMaterial               = itemTemplate->PageMaterial;
				uint32 startquest                 = itemTemplate->StartQuest;
				uint32 lockid                     = itemTemplate->LockID;
				int32  Material                   = itemTemplate->Material;
				uint32 sheath                     = itemTemplate->Sheath;
				int32  RandomProperty             = itemTemplate->RandomProperty;
				int32  RandomSuffix               = itemTemplate->RandomSuffix;
				uint32 itemset                    = itemTemplate->ItemSet;
				uint32 MaxDurability              = itemTemplate->MaxDurability;
				uint32 area                       = itemTemplate->Area;
				uint32 Map                        = itemTemplate->Map;
				uint32 BagFamily                  = itemTemplate->BagFamily;
				uint32 TotemCategory              = itemTemplate->TotemCategory;
				uint32 socketColor_1              = itemTemplate->Socket[0].Color;
				uint32 socketContent_1            = itemTemplate->Socket[0].Content;
				uint32 socketColor_2              = itemTemplate->Socket[1].Color;
				uint32 socketContent_2            = itemTemplate->Socket[1].Content;
				uint32 socketColor_3              = itemTemplate->Socket[2].Color;
				uint32 socketContent_3            = itemTemplate->Socket[2].Content;
				uint32 socketBonus                = itemTemplate->socketBonus;
				uint32 GemProperties              = itemTemplate->GemProperties;
				float  ArmorDamageModifier        = itemTemplate->ArmorDamageModifier;
				uint32 duration                   = itemTemplate->Duration;
				uint32 ItemLimitCategory          = itemTemplate->ItemLimitCategory;
				uint32 HolidayId                  = itemTemplate->HolidayId;
				float StatScalingFactor           = itemTemplate->StatScalingFactor;
				uint32  CurrencySubstitutionId    = itemTemplate->CurrencySubstitutionId;
				uint32 CurrencySubstitutionCount  = itemTemplate->CurrencySubstitutionCount;
				int32 flagsCustom                 = itemTemplate->FlagsCu;
				int32 WDBVerified                 = 18414;

				//
				// Agregar la query a la cache de almacenamiento.
				fCacheStream
					<< "INSERT INTO `item_template` ("
					<< "`entry`, "
					<< "`class`, "
					<< "`subclass`, "
					<< "`SoundOverrideSubclass`, "
					<< "`name`, "
					<< "`displayid`, "
					<< "`Quality`, "
					<< "`Flags`, "
					<< "`FlagsExtra`, "
					<< "`Unk430_1`, "
					<< "`Unk430_2`, "
					<< "`BuyCount`, "
					<< "`BuyPrice`, "
					<< "`SellPrice`, "
					<< "`InventoryType`, "
					<< "`AllowableClass`, "
					<< "`AllowableRace`, "
					<< "`ItemLevel`, "
					<< "`RequiredLevel`, "
					<< "`RequiredSkill`, "
					<< "`RequiredSkillRank`, "
					<< "`requiredspell`, "
					<< "`requiredhonorrank`, "
					<< "`RequiredCityRank`, "
					<< "`RequiredReputationFaction`, "
					<< "`RequiredReputationRank`, "
					<< "`maxcount`, "
					<< "`stackable`, "
					<< "`ContainerSlots`, "
					<< "`stat_type1`, "
					<< "`stat_value1`, "
					<< "`stat_unk1_1`, "
					<< "`stat_unk2_1`, "
					<< "`stat_type2`, "
					<< "`stat_value2`, "
					<< "`stat_unk1_2`, "
					<< "`stat_unk2_2`, "
					<< "`stat_type3`, "
					<< "`stat_value3`, "
					<< "`stat_unk1_3`, "
					<< "`stat_unk2_3`, "
					<< "`stat_type4`, "
					<< "`stat_value4`, "
					<< "`stat_unk1_4`, "
					<< "`stat_unk2_4`, "
					<< "`stat_type5`, "
					<< "`stat_value5`, "
					<< "`stat_unk1_5`, "
					<< "`stat_unk2_5`, "
					<< "`stat_type6`, "
					<< "`stat_value6`, "
					<< "`stat_unk1_6`, "
					<< "`stat_unk2_6`, "
					<< "`stat_type7`, "
					<< "`stat_value7`, "
					<< "`stat_unk1_7`, "
					<< "`stat_unk2_7`, "
					<< "`stat_type8`, "
					<< "`stat_value8`, "
					<< "`stat_unk1_8`, "
					<< "`stat_unk2_8`, "
					<< "`stat_type9`, "
					<< "`stat_value9`, "
					<< "`stat_unk1_9`, "
					<< "`stat_unk2_9`, "
					<< "`stat_type10`, "
					<< "`stat_value10`, "
					<< "`stat_unk1_10`, "
					<< "`stat_unk2_10`, "
					<< "`ScalingStatDistribution`, "
					<< "`DamageType`, "
					<< "`delay`, "
					<< "`RangedModRange`, "
					<< "`spellid_1`, "
					<< "`spelltrigger_1`, "
					<< "`spellcharges_1`, "
					<< "`spellcooldown_1`, "
					<< "`spellcategory_1`, "
					<< "`spellcategorycooldown_1`, "
					<< "`spellid_2`, "
					<< "`spelltrigger_2`, "
					<< "`spellcharges_2`, "
					<< "`spellcooldown_2`, "
					<< "`spellcategory_2`, "
					<< "`spellcategorycooldown_2`, "
					<< "`spellid_3`, "
					<< "`spelltrigger_3`, "
					<< "`spellcharges_3`, "
					<< "`spellcooldown_3`, "
					<< "`spellcategory_3`, "
					<< "`spellcategorycooldown_3`, "
					<< "`spellid_4`, "
					<< "`spelltrigger_4`, "
					<< "`spellcharges_4`, "
					<< "`spellcooldown_4`, "
					<< "`spellcategory_4`, "
					<< "`spellcategorycooldown_4`, "
					<< "`spellid_5`, "
					<< "`spelltrigger_5`, "
					<< "`spellcharges_5`, "
					<< "`spellcooldown_5`, "
					<< "`spellcategory_5`, "
					<< "`spellcategorycooldown_5`, "
					<< "`bonding`, "
					<< "`description`, "
					<< "`PageText`, "
					<< "`LanguageID`, "
					<< "`PageMaterial`, "
					<< "`startquest`, "
					<< "`lockid`, "
					<< "`Material`, "
					<< "`sheath`, "
					<< "`RandomProperty`, "
					<< "`RandomSuffix`, "
					<< "`itemset`, "
					<< "`MaxDurability`, "
					<< "`area`, "
					<< "`Map`, "
					<< "`BagFamily`, "
					<< "`TotemCategory`, "
					<< "`socketColor_1`, "
					<< "`socketContent_1`, "
					<< "`socketColor_2`, "
					<< "`socketContent_2`, "
					<< "`socketColor_3`, "
					<< "`socketContent_3`, "
					<< "`socketBonus`, "
					<< "`GemProperties`, "
					<< "`ArmorDamageModifier`, "
					<< "`duration`, "
					<< "`ItemLimitCategory`, "
					<< "`HolidayId`, "
					<< "`StatScalingFactor`, "
					<< "`CurrencySubstitutionId`, "
					<< "`CurrencySubstitutionCount`, "
					<< "`flagsCustom`, "
					<< "`WDBVerified`) VALUES \n";
				//
				// Insertar los parámetros.
				fCacheStream
					<< "('" << entry << "',"
					<< " '" << _Class << "',"
					<< " '" << subclass << "',"
					<< " '" << SoundOverrideSubclass << "',"
					<< " '" << _Export.SafeSQLParams(name) << "',"
					<< " '" << displayid << "',"
					<< " '" << Quality << "',"
					<< " '" << Flags << "',"
					<< " '" << FlagsExtra << "',"
					<< " '" << Unk430_1 << "',"
					<< " '" << Unk430_2 << "',"
					<< " '" << BuyCount << "',"
					<< " '" << BuyPrice << "',"
					<< " '" << SellPrice << "',"
					<< " '" << InventoryType << "',"
					<< " '" << AllowableClass << "',"
					<< " '" << AllowableRace << "',"
					<< " '" << ItemLevel << "',"
					<< " '" << RequiredLevel << "',"
					<< " '" << RequiredSkill << "',"
					<< " '" << RequiredSkillRank << "',"
					<< " '" << requiredspell << "',"
					<< " '" << requiredhonorrank << "',"
					<< " '" << RequiredCityRank << "',"
					<< " '" << RequiredReputationFaction << "',"
					<< " '" << RequiredReputationRank << "',"
					<< " '" << maxcount << "',"
					<< " '" << stackable << "',"
					<< " '" << ContainerSlots << "',"
					<< " '" << stat_type1 << "',"
					<< " '" << stat_value1 << "',"
					<< " '" << stat_unk1_1 << "',"
					<< " '" << stat_unk2_1 << "',"
					<< " '" << stat_type2 << "',"
					<< " '" << stat_value2 << "',"
					<< " '" << stat_unk1_2 << "',"
					<< " '" << stat_unk2_2 << "',"
					<< " '" << stat_type3 << "',"
					<< " '" << stat_value3 << "',"
					<< " '" << stat_unk1_3 << "',"
					<< " '" << stat_unk2_3 << "',"
					<< " '" << stat_type4 << "',"
					<< " '" << stat_value4 << "',"
					<< " '" << stat_unk1_4 << "',"
					<< " '" << stat_unk2_4 << "',"
					<< " '" << stat_type5 << "',"
					<< " '" << stat_value5 << "',"
					<< " '" << stat_unk1_5 << "',"
					<< " '" << stat_unk2_5 << "',"
					<< " '" << stat_type6 << "',"
					<< " '" << stat_value6 << "',"
					<< " '" << stat_unk1_6 << "',"
					<< " '" << stat_unk2_6 << "',"
					<< " '" << stat_type7 << "',"
					<< " '" << stat_value7 << "',"
					<< " '" << stat_unk1_7 << "',"
					<< " '" << stat_unk2_7 << "',"
					<< " '" << stat_type8 << "',"
					<< " '" << stat_value8 << "',"
					<< " '" << stat_unk1_8 << "',"
					<< " '" << stat_unk2_8 << "',"
					<< " '" << stat_type9 << "',"
					<< " '" << stat_value9 << "',"
					<< " '" << stat_unk1_9 << "',"
					<< " '" << stat_unk2_9 << "',"
					<< " '" << stat_type10 << "',"
					<< " '" << stat_value10 << "',"
					<< " '" << stat_unk1_10 << "',"
					<< " '" << stat_unk2_10 << "',"
					<< " '" << ScalingStatDistribution << "',"
					<< " '" << DamageType << "',"
					<< " '" << delay << "',"
					<< " '" << RangedModRange << "',"
					<< " '" << spellid_1 << "',"
					<< " '" << spelltrigger_1 << "',"
					<< " '" << spellcharges_1 << "',"
					<< " '" << spellcooldown_1 << "',"
					<< " '" << spellcategory_1 << "',"
					<< " '" << spellcategorycooldown_1 << "',"
					<< " '" << spellid_2 << "',"
					<< " '" << spelltrigger_2 << "',"
					<< " '" << spellcharges_2 << "',"
					<< " '" << spellcooldown_2 << "',"
					<< " '" << spellcategory_2 << "',"
					<< " '" << spellcategorycooldown_2 << "',"
					<< " '" << spellid_3 << "',"
					<< " '" << spelltrigger_3 << "',"
					<< " '" << spellcharges_3 << "',"
					<< " '" << spellcooldown_3 << "',"
					<< " '" << spellcategory_3 << "',"
					<< " '" << spellcategorycooldown_3 << "',"
					<< " '" << spellid_4 << "',"
					<< " '" << spelltrigger_4 << "',"
					<< " '" << spellcharges_4 << "',"
					<< " '" << spellcooldown_4 << "',"
					<< " '" << spellcategory_4 << "',"
					<< " '" << spellcategorycooldown_4 << "',"
					<< " '" << spellid_5 << "',"
					<< " '" << spelltrigger_5 << "',"
					<< " '" << spellcharges_5 << "',"
					<< " '" << spellcooldown_5 << "',"
					<< " '" << spellcategory_5 << "',"
					<< " '" << spellcategorycooldown_5 << "',"
					<< " '" << bonding << "',"
					<< " '" << _Export.SafeSQLParams(description) << "',"
					<< " '" << PageText << "',"
					<< " '" << LanguageID << "',"
					<< " '" << PageMaterial << "',"
					<< " '" << startquest << "',"
					<< " '" << lockid << "',"
					<< " '" << Material << "',"
					<< " '" << sheath << "',"
					<< " '" << RandomProperty << "',"
					<< " '" << RandomSuffix << "',"
					<< " '" << itemset << "',"
					<< " '" << MaxDurability << "',"
					<< " '" << area << "',"
					<< " '" << Map << "',"
					<< " '" << BagFamily << "',"
					<< " '" << TotemCategory << "',"
					<< " '" << socketColor_1 << "',"
					<< " '" << socketContent_1 << "',"
					<< " '" << socketColor_2 << "',"
					<< " '" << socketContent_2 << "',"
					<< " '" << socketColor_3 << "',"
					<< " '" << socketContent_3 << "',"
					<< " '" << socketBonus << "',"
					<< " '" << GemProperties << "',"
					<< " '" << ArmorDamageModifier << "',"
					<< " '" << duration << "',"
					<< " '" << ItemLimitCategory << "',"
					<< " '" << HolidayId << "',"
					<< " '" << StatScalingFactor << "',"
					<< " '" << CurrencySubstitutionId << "',"
					<< " '" << CurrencySubstitutionCount << "',"
					<< " '" << flagsCustom << "',"
					<< " '" << WDBVerified << "')";
					fCacheStream << "; \n";
					//
					// Seperador (solo de bonito en el fichero)
					fCacheStream << "\n\n";
			}
			//
			{
				// Exportar para el fichero
				std::ostringstream _FileName;
				_FileName << "[" << "Item" << "] " << "[" << "MERGE" << "] " << ".sql";
				FILE* fout = fopen(_FileName.str().c_str(), "w");
				fprintf(fout, "%s\n", fCacheStream.str().c_str());
				fclose(fout);
			}
			return true;
		}
		/// Author:Eddard
        /// <summary>
        /// Ejecuta el comando de exportación del item con identificador especificado La forma de ejecución es .export item #itemid
        /// </summary>
        /// <param name="handler"></param>
        /// <param name="args"></param>
		static bool HandleExportItemCommand(ChatHandler* aHandler, char const* aArgs)
		{
			if (!*aArgs)
				return false;

			uint32 _ItemID;
			char const *_Id = aHandler->extractKeyFromLink((char*)aArgs, "Hitem");
            if (!_Id)
				return false;
            _ItemID = uint32(atol(_Id));

			CommandExportCreature _Export(aHandler);
			return _Export.ExportItemToSQLFile(_ItemID, nullptr, true);
		}
		/// Author:Eddard
		/// <summary>
		/// Ejecuta el comando de exportación todos los quest
		/// </summary>
		/// <param name="handler"></param>
		/// <param name="args"></param>
		static bool HandleExportQuestAllCommand(ChatHandler* aHandler, const char* aArgs)
		{
			//
			std::list<uint32> _questIDs;
			//
			QueryResult _Result = WorldDatabase.PQuery(
				"SELECT "
				"quest_template.id "
				"FROM "
				"quest_template "
				"GROUP BY "
				"quest_template.id");

			if (_Result)
			{
				do {
					uint16 _Index = 0;
					Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

					uint32 entry = _Fields[_Index++].GetUInt32();

					_questIDs.push_back(entry);

				} while (_Result->NextRow());
			}
			else
				return false;

			for (auto itr : _questIDs)
			{
				CommandExportCreature _Export(aHandler);
				_Export.ExportQuestToSQLFile(itr);
			}

			return true;
		}
		/// Author:Eddard
        /// <summary>
        /// Ejecuta el comando de exportación del item con identificador especificado La forma de ejecución es .export quest #questid
        /// </summary>
        /// <param name="handler"></param>
        /// <param name="args"></param>
		static bool HandleExportQuestCommand(ChatHandler* aHandler, char const* aArgs)
		{
			if (!*aArgs)
				return false;

			uint32 _QuestID;
			char const *_Id = aHandler->extractKeyFromLink((char*)aArgs, "Hitem");
            if (!_Id)
				return false;
            _QuestID = uint32(atol(_Id));

			CommandExportCreature _Export(aHandler);
			return _Export.ExportQuestToSQLFile(_QuestID);
		}
		/// Author:
		/// <summary>
		/// Ejecuta el comando de exportación de todos lod gameobjects del gameobject
		/// </summary>
		/// <param name="handler"></param>
		/// <param name="args"></param>
		static bool HandleExportGOAllCommand(ChatHandler* aHandler, const char* aArgs)
		{
			//
			std::list<uint32> _gameobjectIDs;
			//
			QueryResult _Result = WorldDatabase.PQuery(
				"SELECT "
				"gameobject.id "
				"FROM "
				"gameobject "
				"GROUP BY "
				"gameobject.id");

			if (_Result)
			{
				do {
					uint16 _Index = 0;
					Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

					uint32 entry = _Fields[_Index++].GetUInt32();

					_gameobjectIDs.push_back(entry);

				} while (_Result->NextRow());
			}
			else
				return false;

			for (auto itr : _gameobjectIDs)
			{
				CommandExportCreature _Export(aHandler);
				_Export.ExportGameObjectToSQLFile(itr);
			}

			return true;
		}
        /// Author: Eddard
        /// <summary>
        /// Ejecuta el comando de exportación de todos lod gameobjects del gameobject en un mapa
        /// </summary>
        /// <param name="handler"></param>
        /// <param name="args"></param>
        static bool HandleExportGOByMapCommand(ChatHandler* aHandler, const char* aArgs)
        {
            if (!*aArgs)
                return false;

            uint32 _Entry;
            char const *_Id = aHandler->extractKeyFromLink((char*)aArgs, "Hitem");
            if (!_Id)
                return false;
            _Entry = uint32(atol(_Id));

            //
            std::list<uint32> _gameobjectIDs;
            //
            QueryResult _Result = WorldDatabase.PQuery(
                "SELECT "
                "gameobject.id "
                "FROM "
                "gameobject "
                "WHERE map = %u "
                "GROUP BY "
                "gameobject.id",
                _Entry);

            if (_Result)
            {
                do {
                    uint16 _Index = 0;
                    Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

                    uint32 entry = _Fields[_Index++].GetUInt32();

                    _gameobjectIDs.push_back(entry);

                } while (_Result->NextRow());
            }
            else
                return false;

            for (auto itr : _gameobjectIDs)
            {
                CommandExportCreature _Export(aHandler);
                _Export.ExportGameObjectToSQLFile(itr);
            }

            return true;
        }
        /// Author: Eddard
        /// <summary>
        /// Ejecuta el comando de exportación de todos lod gameobjects del gameobject en una zona
        /// </summary>
        /// <param name="handler"></param>
        /// <param name="args"></param>
        static bool HandleExportGOByZoneCommand(ChatHandler* aHandler, const char* aArgs)
        {
            if (!*aArgs)
                return false;

            uint32 _Entry;
            char const *_Id = aHandler->extractKeyFromLink((char*)aArgs, "Hitem");
            if (!_Id)
                return false;
            _Entry = uint32(atol(_Id));

            //
            std::list<uint32> _gameobjectIDs;
            //
            QueryResult _Result = WorldDatabase.PQuery(
                "SELECT "
                "gameobject.id "
                "FROM "
                "gameobject "
                "WHERE zoneId = %u "
                "GROUP BY "
                "gameobject.id",
                _Entry);

            if (_Result)
            {
                do {
                    uint16 _Index = 0;
                    Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

                    uint32 entry = _Fields[_Index++].GetUInt32();

                    _gameobjectIDs.push_back(entry);

                } while (_Result->NextRow());
            }
            else
                return false;

            for (auto itr : _gameobjectIDs)
            {
                CommandExportCreature _Export(aHandler);
                _Export.ExportGameObjectToSQLFile(itr);
            }

            return true;
        }
        /// Author: Eddard
        /// <summary>
        /// Ejecuta el comando de exportación de todos lod gameobjects del gameobject en un area
        /// </summary>
        /// <param name="handler"></param>
        /// <param name="args"></param>
        static bool HandleExportGOByAreaCommand(ChatHandler* aHandler, const char* aArgs)
        {
            if (!*aArgs)
                return false;

            uint32 _Entry;
            char const *_Id = aHandler->extractKeyFromLink((char*)aArgs, "Hitem");
            if (!_Id)
                return false;
            _Entry = uint32(atol(_Id));

            //
            std::list<uint32> _gameobjectIDs;
            //
            QueryResult _Result = WorldDatabase.PQuery(
                "SELECT "
                "gameobject.id "
                "FROM "
                "gameobject "
                "WHERE areaId = %u "
                "GROUP BY "
                "gameobject.id",
                _Entry);

            if (_Result)
            {
                do {
                    uint16 _Index = 0;
                    Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

                    uint32 entry = _Fields[_Index++].GetUInt32();

                    _gameobjectIDs.push_back(entry);

                } while (_Result->NextRow());
            }
            else
                return false;

            for (auto itr : _gameobjectIDs)
            {
                CommandExportCreature _Export(aHandler);
                _Export.ExportGameObjectToSQLFile(itr);
            }

            return true;
        }
        /// Author:
        /// <summary>
        /// Ejecuta el comando de exportación del item con identificador especificado La forma de ejecución es .export go #gobjectid
        /// </summary>
        /// <param name="handler"></param>
        /// <param name="args"></param>
        static bool HandleExportGOCommand(ChatHandler* aHandler, char const* aArgs)
        {
            if (!*aArgs)
                return false;

            uint32 _GameObjID;
            char const *_Id = aHandler->extractKeyFromLink((char*)aArgs, "Hitem");
            if (!_Id)
                return false;
            _GameObjID = uint32(atol(_Id));

            CommandExportCreature _Export(aHandler);
            return _Export.ExportGameObjectToSQLFile(_GameObjID);
        }
        /// Author: Eddard
        /// <summary>
        /// Ejecuta el comando de exportación de la creaturas de la base de datos
        ///
        /// La forma de ejecución para la creatura seleccionada es .export creature
        /// La forma de ejecución para la creatura por entry es .export creature #Creature_Entry
        /// </summary>
        /// <param name="handler"></param>
        /// <param name="args"></param>
        /// <example>.export creature 2133 exporta la creatura con Creature_Entry = 2311</example>
        static bool HandleExportCreatureAllCommand(ChatHandler* aHandler, const char* aArgs)
        {
            //
            std::list<uint32> _creatureIDs;
            //
            QueryResult _Result = WorldDatabase.PQuery(
                "SELECT "
                "creature.id "
                "FROM "
                "creature "
                "GROUP BY "
                "creature.id");

            if (_Result)
            {
                do {
                    uint16 _Index = 0;
                    Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

                    uint32 entry = _Fields[_Index++].GetUInt32();

                    _creatureIDs.push_back(entry);

                } while (_Result->NextRow());
            }
            else
                return false;

            for (auto itr : _creatureIDs)
            {
                CommandExportCreature _Export(aHandler);
                _Export.ExportToSQLFile(itr);
            }

            return true;
        }
        /// Author: Eddard
        /// <summary>
        /// Ejecuta el comando de exportación de la criaturas en un map entry 
        /// dado como parametro en el momento en que se ejecuta el comando.
        ///
        /// La forma de ejecución para la creatura por area es .export creature by_map #map_id
        /// </summary>
        /// <param name="handler"></param>
        /// <param name="args"></param>
        /// <example>.export creature by map </example>
        static bool HandleExportCreatureByMapCommand(ChatHandler* aHandler, const char* aArgs)
        {
            Creature* _Target = aHandler->getSelectedCreature();

            if (!*aArgs)
            {
                aHandler->SendSysMessage("You most enter a map id.");
                aHandler->SetSentErrorMessage(true);
                return false;
            }
            else
            {
                uint64 _Entry;

                // strtoull doesn't exist on WIN
#if PLATFORM == PLATFORM_WINDOWS
                _Entry = _strtoui64((char*)aArgs, NULL, 10);
#else
                _Entry = strtoull((char*)aArgs, NULL, 10);
#endif
                /*
                CommandExportCreature _Export(aHandler);
                _Export.ExportToSQLFile(_Entry);
                */

                //
                std::list<uint32> _creatureIDs;
                //
                QueryResult _Result = WorldDatabase.PQuery(
                    "SELECT "
                    "creature.id "
                    "FROM "
                    "creature "
                    "WHERE map = %u "
                    "GROUP BY "
                    "creature.id",
                    _Entry);

                if (_Result)
                {
                    do {
                        uint16 _Index = 0;
                        Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

                        uint32 entry = _Fields[_Index++].GetUInt32();

                        _creatureIDs.push_back(entry);

                    } while (_Result->NextRow());
                }
                else
                    return false;

                for (auto itr : _creatureIDs)
                {
                    CommandExportCreature _Export(aHandler);
                    _Export.ExportToSQLFile(itr);
                }
                return true;
            }
        }
        /// Author: Eddard
        /// <summary>
        /// Ejecuta el comando de exportación de la criaturas en una zone entry 
        /// dado como parametro en el momento en que se ejecuta el comando.
        ///
        /// La forma de ejecución para la creatura por area es .export creature by_zone #zone_id
        /// </summary>
        /// <param name="handler"></param>
        /// <param name="args"></param>
        /// <example>.export creature by zone </example>
        static bool HandleExportCreatureByZoneCommand(ChatHandler* aHandler, const char* aArgs)
        {
            Creature* _Target = aHandler->getSelectedCreature();

            if (!*aArgs)
            {
                aHandler->SendSysMessage("You most enter a zone id.");
                aHandler->SetSentErrorMessage(true);
                return false;
            }
            else
            {
                uint64 _Entry;

                // strtoull doesn't exist on WIN
#if PLATFORM == PLATFORM_WINDOWS
                _Entry = _strtoui64((char*)aArgs, NULL, 10);
#else
                _Entry = strtoull((char*)aArgs, NULL, 10);
#endif
                /*
                CommandExportCreature _Export(aHandler);
                _Export.ExportToSQLFile(_Entry);
                */

                //
                std::list<uint32> _creatureIDs;
                //
                QueryResult _Result = WorldDatabase.PQuery(
                    "SELECT "
                    "creature.id "
                    "FROM "
                    "creature "
                    "WHERE zoneId = %u "
                    "GROUP BY "
                    "creature.id",
                    _Entry);

                if (_Result)
                {
                    do {
                        uint16 _Index = 0;
                        Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

                        uint32 entry = _Fields[_Index++].GetUInt32();

                        _creatureIDs.push_back(entry);

                    } while (_Result->NextRow());
                }
                else
                    return false;

                for (auto itr : _creatureIDs)
                {
                    CommandExportCreature _Export(aHandler);
                    _Export.ExportToSQLFile(itr);
                }
                return true;
            }
        }
        /// Author: Eddard
        /// <summary>
        /// Ejecuta el comando de exportación de la criaturas en una area entry 
        /// dado como parametro en el momento en que se ejecuta el comando.
        ///
        /// La forma de ejecución para la creatura por area es .export creature by_area #area_id
        /// </summary>
        /// <param name="handler"></param>
        /// <param name="args"></param>
        /// <example>.export creature by area </example>
        static bool HandleExportCreatureByAreaCommand(ChatHandler* aHandler, const char* aArgs)
        {
            Creature* _Target = aHandler->getSelectedCreature();

            if (!*aArgs)
            {
                aHandler->SendSysMessage("You most enter a area id.");
                aHandler->SetSentErrorMessage(true);
                return false;
            }
            else
            {
                uint64 _Entry;

                // strtoull doesn't exist on WIN
#if PLATFORM == PLATFORM_WINDOWS
                _Entry = _strtoui64((char*)aArgs, NULL, 10);
#else
                _Entry = strtoull((char*)aArgs, NULL, 10);
#endif
                /*
                CommandExportCreature _Export(aHandler);
                _Export.ExportToSQLFile(_Entry);
                */

                //
                std::list<uint32> _creatureIDs;
                //
                QueryResult _Result = WorldDatabase.PQuery(
                    "SELECT "
                    "creature.id "
                    "FROM "
                    "creature "
                    "WHERE areaId = %u "
                    "GROUP BY "
                    "creature.id",
                    _Entry);

                if (_Result)
                {
                    do {
                        uint16 _Index = 0;
                        Field* _Fields = _Result->Fetch();		// Materializar la fila en un objeto

                        uint32 entry = _Fields[_Index++].GetUInt32();

                        _creatureIDs.push_back(entry);

                    } while (_Result->NextRow());
                }
                else
                    return false;

                for (auto itr : _creatureIDs)
                {
                    CommandExportCreature _Export(aHandler);
                    _Export.ExportToSQLFile(itr);
                }
                return true;
            }
        }
        /// Author: Eddard
        /// <summary>
        /// Ejecuta el comando de exportación de la criaturas que este seleccionada o exporta
        /// la creatura con el entry dado como parametro en el momento en que se ejecuta el comando.
        ///
        /// La forma de ejecución para la creatura seleccionada es .export creature
        /// La forma de ejecución para la creatura por entry es .export creature #Creature_Entry
        /// </summary>
        /// <param name="handler"></param>
        /// <param name="args"></param>
        /// <example>.export creature 2133 exporta la creatura con Creature_Entry = 2311</example>
        static bool HandleExportCreatureCommand(ChatHandler* aHandler, const char* aArgs)
        {
            Creature* _Target = aHandler->getSelectedCreature();

            if (!*aArgs && !_Target)
            {
                aHandler->SendSysMessage("You most select a creature or enter an creature entry.");
                aHandler->SetSentErrorMessage(true);
                return false;
            }
            else if (!*aArgs && _Target)
            {
                CommandExportCreature _Export(aHandler);
                _Export.ExportToSQLFile(_Target->GetEntry());
                return true;
            }
            else
            {
                uint64 _Entry;

                // strtoull doesn't exist on WIN
#if PLATFORM == PLATFORM_WINDOWS
                _Entry = _strtoui64((char*)aArgs, NULL, 10);
#else
                _Entry = strtoull((char*)aArgs, NULL, 10);
#endif

                CommandExportCreature _Export(aHandler);
                _Export.ExportToSQLFile(_Entry);
                return true;
            }
        }
};

void AddSC_export_Commandscript()
{
    new export_Commandscript();
}