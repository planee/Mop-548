/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 4/2/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Rhea';
SET @ENTRY 		:= '46654';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '35212', '0', '0', '0', @CREATURE, '', '', '12148', '85', '85', '3', '0', '35', '35', '3', '0', '1', '1.14286', '0', '1.14286', '1', '0', '550', '950', '0', '36', '1', '2000', '2000', '1', '32768', '2048', '0', '0', '0', '0', '0', '0', '400', '600', '150', '2', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '', '16048');

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES 
(@ENTRY, '0', '0', '65536', '1', '0', ''); 


/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('35212', '0.306', '1.5', '1', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 46654 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '0', '3', '5519', '1', '65535', '0', '0', '-6983.54', '-3937.83', '263.889', '2.44841', '300', '0', '0', '154980', '0', '0', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '0', '3', '5564', '1', '1', '0', '0', '-7031.15', '-2586.9', '254.077', '1.93753', '300', '0', '0', '77490', '0', '0', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '0', '3', '5565', '1', '65535', '0', '0', '-6722.78', '-2481.3', '274.564', '2.97176', '300', '0', '0', '154980', '0', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-6983.54' AND `position_y` REGEXP '-3937.83' AND `position_z` REGEXP '263.889' AND `phaseMask` = '65535' AND `map` = '0');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-6983.54' AND `position_y` REGEXP '-3937.83' AND `position_z` REGEXP '263.889' AND `phaseMask` = '65535' AND `map` = '0');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-7031.15' AND `position_y` REGEXP '-2586.9' AND `position_z` REGEXP '254.077' AND `phaseMask` = '1' AND `map` = '0');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-7031.15' AND `position_y` REGEXP '-2586.9' AND `position_z` REGEXP '254.077' AND `phaseMask` = '1' AND `map` = '0');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-6722.78' AND `position_y` REGEXP '-2481.3' AND `position_z` REGEXP '274.564' AND `phaseMask` = '65535' AND `map` = '0');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-6722.78' AND `position_y` REGEXP '-2481.3' AND `position_z` REGEXP '274.564' AND `phaseMask` = '65535' AND `map` = '0');
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
DELETE FROM gossip_menu WHERE  `entry` = 12148;
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES 
(12148, 17078); 
/* Step 4.6 Table  `npc_text` */
DELETE FROM npc_text WHERE `ID` = 17078;
INSERT INTO `npc_text` (`ID`,`text0_0`,`text0_1`,`lang0`,`prob0`,`em0_0`,`em0_1`,`em0_2`,`em0_3`,`em0_4`,`em0_5`,`text1_0`,`text1_1`,`lang1`,`prob1`,`em1_0`,`em1_1`,`em1_2`,`em1_3`,`em1_4`,`em1_5`,`text2_0`,`text2_1`,`lang2`,`prob2`,`em2_0`,`em2_1`,`em2_2`,`em2_3`,`em2_4`,`em2_5`,`text3_0`,`text3_1`,`lang3`,`prob3`,`em3_0`,`em3_1`,`em3_2`,`em3_3`,`em3_4`,`em3_5`,`text4_0`,`text4_1`,`lang4`,`prob4`,`em4_0`,`em4_1`,`em4_2`,`em4_3`,`em4_4`,`em4_5`,`text5_0`,`text5_1`,`lang5`,`prob5`,`em5_0`,`em5_1`,`em5_2`,`em5_3`,`em5_4`,`em5_5`,`text6_0`,`text6_1`,`lang6`,`prob6`,`em6_0`,`em6_1`,`em6_2`,`em6_3`,`em6_4`,`em6_5`,`text7_0`,`text7_1`,`lang7`,`prob7`,`em7_0`,`em7_1`,`em7_2`,`em7_3`,`em7_4`,`em7_5`,`WDBVerified`) VALUES 
('17078', '', 'Greetings.', '0', '1', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '15595'); 




/* Step 2.7 Table  `gossip_menu_option */
DELETE FROM gossip_menu_option WHERE  `menu_id` = 12148;
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
('46654', '27764'),  /* Quest(27764): A Strange Request ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27765'),  /* Quest(27765): First Sample: Wild Eggs ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27766'),  /* Quest(27766): Second Sample: Whelps ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27769'),  /* Quest(27769): Rhea Revealed ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27770'),  /* Quest(27770): Lifting the Veil ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27771'),  /* Quest(27771): Third Sample: Implanted Eggs ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27827'),  /* Quest(27827): The Swift, the Fierce, and the Stout ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27830'),  /* Quest(27830): Their Hunt Continues ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27831'),  /* Quest(27831): The Sorrow and the Fury ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27832'),  /* Quest(27832): The Hidden Clutch ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27858'),  /* Quest(27858): Rheastrasza's Gift ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27890'),  /* Quest(27890): The Bad Dogs ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27895'),  /* Quest(27895): Their Hunt Continues ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27896'),  /* Quest(27896): The Sorrow and the Fury ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27897'),  /* Quest(27897): The Hidden Clutch ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27898');  /* Quest(27898): Rheastrasza's Gift ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 


/* Step 2.2 Table  `creature_involvedrelation */
DELETE FROM  `creature_involvedrelation` WHERE `id`= @ENTRY;
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES 
('46654', '27764'),  /* Quest(27764): A Strange Request ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27765'),  /* Quest(27765): First Sample: Wild Eggs ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27766'),  /* Quest(27766): Second Sample: Whelps ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27770'),  /* Quest(27770): Lifting the Veil ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27771'),  /* Quest(27771): Third Sample: Implanted Eggs ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27826'),  /* Quest(27826): Into the Dragon's Mouth ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27829'),  /* Quest(27829): The Wrath of a Dragonflight ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27830'),  /* Quest(27830): Their Hunt Continues ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27831'),  /* Quest(27831): The Sorrow and the Fury ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27832'),  /* Quest(27832): The Hidden Clutch ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27858'),  /* Quest(27858): Rheastrasza's Gift ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27889'),  /* Quest(27889): New Kargath ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27894'),  /* Quest(27894): The Wrath of a Dragonflight ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27895'),  /* Quest(27895): Their Hunt Continues ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27896'),  /* Quest(27896): The Sorrow and the Fury ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27897'),  /* Quest(27897): The Hidden Clutch ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('46654', '27898');  /* Quest(27898): Rheastrasza's Gift ,QuestMinLevel: 44 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 


/* Step 1.8 Table  `waypoints */
DELETE FROM waypoints WHERE  `entry` = @ENTRY;
/* Step 2.5 Table  `npc_spellclick_spells */
DELETE FROM npc_spellclick_spells WHERE  `npc_entry` = @ENTRY;
/* Step 2.6 Table  `pet_levelstats */
DELETE FROM pet_levelstats WHERE  `creature_entry` = @ENTRY;

