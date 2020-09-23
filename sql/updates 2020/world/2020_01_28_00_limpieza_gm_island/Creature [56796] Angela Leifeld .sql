/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 28/1/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Angela Leifeld';
SET @ENTRY 		:= '56796';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '39501', '0', '0', '0', @CREATURE, 'First Aid Trainer', '', '0', '35', '35', '0', '0', '35', '35', '81', '0', '1', '1.14286', '0', '1.14286', '1', '0', '35', '70', '0', '18', '1', '2000', '2000', '1', '512', '2048', '0', '0', '2', '0', '0', '0', '35', '70', '18', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1.1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '', '16048');

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES 
(@ENTRY, '0', '0', '0', '257', '0', ''); 


/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('39501', '0.208', '1.5', '1', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 56796 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '0', '1519', '5151', '1', '1', '0', '0', '-8521.53', '816.257', '106.602', '2.87979', '120', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-8521.53' AND `position_y` REGEXP '816.257' AND `position_z` REGEXP '106.602' AND `phaseMask` = '1' AND `map` = '0');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-8521.53' AND `position_y` REGEXP '816.257' AND `position_z` REGEXP '106.602' AND `phaseMask` = '1' AND `map` = '0');
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
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES 
(@ENTRY, '3273', '100', '129', '0', '5'),  /* Spell(3273): First Aid*/
(@ENTRY, '3274', '500', '129', '50', '10'),  /* Spell(3274): First Aid*/
(@ENTRY, '3276', '100', '129', '40', '0'),  /* Spell(3276): Heavy Linen Bandage*/
(@ENTRY, '3277', '250', '129', '80', '0'),  /* Spell(3277): Wool Bandage*/
(@ENTRY, '3278', '1000', '129', '115', '0'),  /* Spell(3278): Heavy Wool Bandage*/
(@ENTRY, '7924', '1000', '129', '125', '25'),  /* Spell(7924): First Aid*/
(@ENTRY, '7928', '5000', '129', '150', '0'),  /* Spell(7928): Silk Bandage*/
(@ENTRY, '7929', '5000', '129', '180', '0'),  /* Spell(7929): Heavy Silk Bandage*/
(@ENTRY, '7934', '250', '129', '80', '0'),  /* Spell(7934): Anti-Venom*/
(@ENTRY, '10840', '10000', '129', '210', '0'),  /* Spell(10840): Mageweave Bandage*/
(@ENTRY, '10841', '10000', '129', '240', '0'),  /* Spell(10841): Heavy Mageweave Bandage*/
(@ENTRY, '10846', '25000', '129', '225', '35'),  /* Spell(10846): First Aid*/
(@ENTRY, '18629', '20000', '129', '260', '0'),  /* Spell(18629): Runecloth Bandage*/
(@ENTRY, '18630', '20000', '129', '290', '0'),  /* Spell(18630): Heavy Runecloth Bandage*/
(@ENTRY, '27028', '100000', '129', '275', '50'),  /* Spell(27028): First Aid*/
(@ENTRY, '27032', '20000', '129', '300', '0'),  /* Spell(27032): Netherweave Bandage*/
(@ENTRY, '27033', '40000', '129', '330', '0'),  /* Spell(27033): Heavy Netherweave Bandage*/
(@ENTRY, '45542', '150000', '129', '350', '65'),  /* Spell(45542): First Aid*/
(@ENTRY, '45545', '40000', '129', '350', '0'),  /* Spell(45545): Frostweave Bandage*/
(@ENTRY, '45546', '60000', '129', '390', '0'),  /* Spell(45546): Heavy Frostweave Bandage*/
(@ENTRY, '74556', '60000', '129', '425', '0'),  /* Spell(74556): Embersilk Bandage*/
(@ENTRY, '74557', '80000', '129', '475', '0'),  /* Spell(74557): Heavy Embersilk Bandage*/
(@ENTRY, '74558', '15000', '129', '525', '0'),  /* Spell(74558): Field Bandage: Dense Embersilk*/
(@ENTRY, '74559', '250000', '129', '425', '75'),  /* Spell(74559): First Aid*/
(@ENTRY, '88893', '80000', '129', '525', '0'),  /* Spell(88893): Dense Embersilk Bandage*/
(@ENTRY, '102697', '100000', '129', '500', '0'),  /* Spell(102697): Windwool Bandage*/
(@ENTRY, '102698', '122222', '129', '550', '0'),  /* Spell(102698): Heavy Windwool Bandage*/
(@ENTRY, '110406', '333333', '129', '500', '80');  /* Spell(110406): First Aid*/


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
/* Step 1.8 Table  `waypoints */
DELETE FROM waypoints WHERE  `entry` = @ENTRY;
/* Step 2.5 Table  `npc_spellclick_spells */
DELETE FROM npc_spellclick_spells WHERE  `npc_entry` = @ENTRY;
/* Step 2.6 Table  `pet_levelstats */
DELETE FROM pet_levelstats WHERE  `creature_entry` = @ENTRY;

