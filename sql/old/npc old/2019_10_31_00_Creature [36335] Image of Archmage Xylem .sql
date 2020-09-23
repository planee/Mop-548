/*
SQL RoG WoW				  
Desarrollado por:
Fecha: 31/10/2019
### Scripts Privados / Derechos Reservados RoG WoW ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Image of Archmage Xylem';
SET @ENTRY 		:= '36335';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '29670', '0', '0', '0', @CREATURE, '', '', '0', '85', '85', '0', '0', '35', '35', '2', '0', '1.14286', '1', '0', '1.14286', '1', '0', '425', '510', '0', '43', '1', '2000', '2000', '8', '512', '2048', '0', '0', '0', '0', '0', '0', '425', '510', '43', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1.35', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '', '16048');

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('29670', '0.3672', '1.8', '0', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 36335 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '1', '16', '4799', '1', '1', '29670', '0', '4515.12', '-5190.95', '305.154', '5.02655', '300', '0', '0', '5804', '19394', '0', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '16', '4800', '1', '1', '0', '0', '4392.93', '-5086.18', '335.399', '3.98412', '300', '0', '0', '3', '19394', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '4515.12' AND `position_y` REGEXP '-5190.95' AND `position_z` REGEXP '305.154' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '4515.12' AND `position_y` REGEXP '-5190.95' AND `position_z` REGEXP '305.154' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '4392.93' AND `position_y` REGEXP '-5086.18' AND `position_z` REGEXP '335.399' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '4392.93' AND `position_y` REGEXP '-5086.18' AND `position_z` REGEXP '335.399' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;


/*## Step 2: Creature Loots ##########################################*/

/* Step 2.2 Table  `creature_loot_currency */
DELETE FROM creature_loot_currency WHERE  `creature_id` = @ENTRY;
/* Step 2.1 Table  `creature_onkill_reputation */
DELETE FROM creature_onkill_reputation WHERE `creature_id` = @ENTRY;
/* Step 2.3 Table  `pickpocketing_loot_template */
DELETE FROM pickpocketing_loot_template WHERE `entry` = @ENTRY;
/* Step 2.4 Table  `skinning_loot_template */
DELETE FROM skinning_loot_template WHERE  `entry` = @ENTRY;
/*Creature Loot Template Items Data: Id - Quality - SellPrice - ItemLevel - RequiredLevel - Name */
/*
/*Pickpocketing Loot Template Items Data: Id - Quality - SellPrice - ItemLevel - RequiredLevel - Name */
/*
*/
/*Skinning Loot Template Items Data: Id - Quality - SellPrice - ItemLevel - RequiredLevel - Name */
/*
*/


/*## Step 3: Creature Extras ##########################################*/

/* Step 3.3 Table  `creature_summon_groups` */
DELETE FROM  `creature_summon_groups` WHERE `summonerId` = @ENTRY AND `summonerType` = 0;
/*## Step 4: Creature Gossip Menu Options #############################*/

/* Step 2.7 Table  `gossip_menu */
DELETE FROM gossip_menu WHERE  `entry` = 0;
/*## Step 5: Creature NPC Trainer / Vendor ############################*/

/* Step 2.0 Table  `npc_trainer */
DELETE FROM npc_trainer WHERE `entry` = @ENTRY;
/* Step 1.9 Table  `npc_vendor */
DELETE FROM npc_vendor WHERE  `entry` = @ENTRY;
/*## Step 6: Creature NPC Conditions ##################################*/

/* Step 6.9 Table `conditions` */
/*DELETE FROM  `conditions` WHERE `SourceTypeOrReferenceId` AND `SourceGroup`;
*/

/*## Step 7: Creature NPC Needs to Work ###############################*/

/* Step 2.2 Table  `creature_questrelation */
DELETE FROM  `creature_questrelation` WHERE `id`= @ENTRY;
/* Step 2.2 Table  `creature_involvedrelation */
DELETE FROM  `creature_involvedrelation` WHERE `id`= @ENTRY;
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES 
('36335', '14300');  /* Quest(14300): The Trial of Fire ,QuestMinLevel: 15 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 


/* Step 1.8 Table  `waypoints */
DELETE FROM waypoints WHERE  `entry` = @ENTRY;
/* Step 2.5 Table  `npc_spellclick_spells */
DELETE FROM npc_spellclick_spells WHERE  `npc_entry` = @ENTRY;
/* Step 2.6 Table  `pet_levelstats */
DELETE FROM pet_levelstats WHERE  `creature_entry` = @ENTRY;

