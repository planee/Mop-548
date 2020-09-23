/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 4/2/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Overseer Oilfist';
SET @ENTRY 		:= '14625';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '14653', '0', '0', '0', @CREATURE, 'The Thorium Brotherhood', '', '12293', '60', '60', '0', '0', '1475', '1475', '3', '0', '1', '1.14286', '0', '1.14286', '1', '0', '104', '138', '0', '252', '1', '2000', '2000', '1', '768', '2048', '0', '0', '0', '0', '0', '0', '72', '106', '26', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1.35', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '14625', '0', '2', '', '16048');

/* Step 1.2 Table `creature_equip_template */
DELETE FROM `creature_equip_template` WHERE `entry`= 14625;
INSERT INTO `creature_equip_template` (`entry`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES 
('14625', '17383', '0', '0'); /* [ItemEntry1(17383): Monster - Axe, 2H Horde Black War Axe] */

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('14653', '0.347', '1.5', '0', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 14625 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '0', '51', '1446', '1', '1', '0', '14625', '-6527.94', '-1154.36', '310.696', '4.41111', '300', '0', '0', '8240', '0', '0', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '0', '51', '5615', '1', '1', '0', '14625', '-6685.34', '-1422.98', '241.804', '3.10706', '300', '0', '0', '8240', '0', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-6527.94' AND `position_y` REGEXP '-1154.36' AND `position_z` REGEXP '310.696' AND `phaseMask` = '1' AND `map` = '0');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-6527.94' AND `position_y` REGEXP '-1154.36' AND `position_z` REGEXP '310.696' AND `phaseMask` = '1' AND `map` = '0');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-6685.34' AND `position_y` REGEXP '-1422.98' AND `position_z` REGEXP '241.804' AND `phaseMask` = '1' AND `map` = '0');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-6685.34' AND `position_y` REGEXP '-1422.98' AND `position_z` REGEXP '241.804' AND `phaseMask` = '1' AND `map` = '0');
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
DELETE FROM gossip_menu WHERE  `entry` = 12293;
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES 
(12293, 17268); 
/* Step 4.6 Table  `npc_text` */
DELETE FROM npc_text WHERE `ID` = 17268;
INSERT INTO `npc_text` (`ID`,`text0_0`,`text0_1`,`lang0`,`prob0`,`em0_0`,`em0_1`,`em0_2`,`em0_3`,`em0_4`,`em0_5`,`text1_0`,`text1_1`,`lang1`,`prob1`,`em1_0`,`em1_1`,`em1_2`,`em1_3`,`em1_4`,`em1_5`,`text2_0`,`text2_1`,`lang2`,`prob2`,`em2_0`,`em2_1`,`em2_2`,`em2_3`,`em2_4`,`em2_5`,`text3_0`,`text3_1`,`lang3`,`prob3`,`em3_0`,`em3_1`,`em3_2`,`em3_3`,`em3_4`,`em3_5`,`text4_0`,`text4_1`,`lang4`,`prob4`,`em4_0`,`em4_1`,`em4_2`,`em4_3`,`em4_4`,`em4_5`,`text5_0`,`text5_1`,`lang5`,`prob5`,`em5_0`,`em5_1`,`em5_2`,`em5_3`,`em5_4`,`em5_5`,`text6_0`,`text6_1`,`lang6`,`prob6`,`em6_0`,`em6_1`,`em6_2`,`em6_3`,`em6_4`,`em6_5`,`text7_0`,`text7_1`,`lang7`,`prob7`,`em7_0`,`em7_1`,`em7_2`,`em7_3`,`em7_4`,`em7_5`,`WDBVerified`) VALUES 
('17268', 'Welcome to Thorium Point.  As Overseer, I\'m responsible for all the activities of the Thorium Brotherhood.  While that mainly involves mining, smithing, and some minor guard duty, we\'ve lately become more of a martial organization... out of necessity.', '', '0', '1', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '15595'); 




/* Step 2.7 Table  `gossip_menu_option */
DELETE FROM gossip_menu_option WHERE  `menu_id` = 12293;
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
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES 
('14625', '27470'),  /* Quest(27470): A Potential Ally ,QuestMinLevel: 57 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '27965'),  /* Quest(27965): Thorium Point: The Seat of the Brotherhood ,QuestMinLevel: 46 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '28035'),  /* Quest(28035): The Mountain-Lord's Support ,QuestMinLevel: 46 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '28052'),  /* Quest(28052): Operation: Stir the Cauldron ,QuestMinLevel: 46 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '28061'),  /* Quest(28061): Minions of Calcinder ,QuestMinLevel: 46 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '28062'),  /* Quest(28062): From Whence He Came ,QuestMinLevel: 46 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '28064'),  /* Quest(28064): Welcome to the Brotherhood ,QuestMinLevel: 46 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '28099'),  /* Quest(28099): Rasha'krak ,QuestMinLevel: 46 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '28514'),  /* Quest(28514): Mouton Flamestar ,QuestMinLevel: 49 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '28515');  /* Quest(28515): Mouton Flamestar ,QuestMinLevel: 49 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 


/* Step 2.2 Table  `creature_involvedrelation */
DELETE FROM  `creature_involvedrelation` WHERE `id`= @ENTRY;
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES 
('14625', '8858'),  /* Quest(8858): Secrets of the Colossus - Regal ,QuestMinLevel: 51 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '27965'),  /* Quest(27965): Thorium Point: The Seat of the Brotherhood ,QuestMinLevel: 46 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '28035'),  /* Quest(28035): The Mountain-Lord's Support ,QuestMinLevel: 46 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '28060'),  /* Quest(28060): Twisted Twilight Ties ,QuestMinLevel: 46 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '28061'),  /* Quest(28061): Minions of Calcinder ,QuestMinLevel: 46 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '28062'),  /* Quest(28062): From Whence He Came ,QuestMinLevel: 46 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '28064'),  /* Quest(28064): Welcome to the Brotherhood ,QuestMinLevel: 46 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('14625', '28099');  /* Quest(28099): Rasha'krak ,QuestMinLevel: 46 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 


/* Step 1.8 Table  `waypoints */
DELETE FROM waypoints WHERE  `entry` = @ENTRY;
/* Step 2.5 Table  `npc_spellclick_spells */
DELETE FROM npc_spellclick_spells WHERE  `npc_entry` = @ENTRY;
/* Step 2.6 Table  `pet_levelstats */
DELETE FROM pet_levelstats WHERE  `creature_entry` = @ENTRY;

