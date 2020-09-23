/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 28/1/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Gonto';
SET @ENTRY 		:= '46357';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '35051', '0', '0', '0', @CREATURE, 'Mining Trainer', '', '7690', '35', '35', '0', '0', '35', '35', '81', '0', '1', '1.14286', '0', '1.14286', '1', '0', '45', '68', '0', '17', '1', '2000', '2000', '1', '512', '2048', '0', '0', '2', '0', '0', '0', '36', '54', '14', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '46357', '0', '0', '', '16048');

/* Step 1.2 Table `creature_equip_template */
DELETE FROM `creature_equip_template` WHERE `entry`= 46357;
INSERT INTO `creature_equip_template` (`entry`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES 
('46357', '1910', '0', '0'); /* [ItemEntry1(1910): Monster - Item, Pick] */

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES 
(@ENTRY, '0', '0', '0', '257', '0', ''); 


/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('35051', '0.372', '1.5', '0', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 46357 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '1', '1637', '5170', '1', '1', '0', '0', '1574.99', '-4281.41', '21.476', '5.93412', '120', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '1574.99' AND `position_y` REGEXP '-4281.41' AND `position_z` REGEXP '21.476' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '1574.99' AND `position_y` REGEXP '-4281.41' AND `position_z` REGEXP '21.476' AND `phaseMask` = '1' AND `map` = '1');
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
DELETE FROM gossip_menu WHERE  `entry` = 7690;
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES 
(7690, 9384); 
/* Step 4.6 Table  `npc_text` */
DELETE FROM npc_text WHERE `ID` = 9384;
INSERT INTO `npc_text` (`ID`,`text0_0`,`text0_1`,`lang0`,`prob0`,`em0_0`,`em0_1`,`em0_2`,`em0_3`,`em0_4`,`em0_5`,`text1_0`,`text1_1`,`lang1`,`prob1`,`em1_0`,`em1_1`,`em1_2`,`em1_3`,`em1_4`,`em1_5`,`text2_0`,`text2_1`,`lang2`,`prob2`,`em2_0`,`em2_1`,`em2_2`,`em2_3`,`em2_4`,`em2_5`,`text3_0`,`text3_1`,`lang3`,`prob3`,`em3_0`,`em3_1`,`em3_2`,`em3_3`,`em3_4`,`em3_5`,`text4_0`,`text4_1`,`lang4`,`prob4`,`em4_0`,`em4_1`,`em4_2`,`em4_3`,`em4_4`,`em4_5`,`text5_0`,`text5_1`,`lang5`,`prob5`,`em5_0`,`em5_1`,`em5_2`,`em5_3`,`em5_4`,`em5_5`,`text6_0`,`text6_1`,`lang6`,`prob6`,`em6_0`,`em6_1`,`em6_2`,`em6_3`,`em6_4`,`em6_5`,`text7_0`,`text7_1`,`lang7`,`prob7`,`em7_0`,`em7_1`,`em7_2`,`em7_3`,`em7_4`,`em7_5`,`WDBVerified`) VALUES 
('9384', 'I can instruct you in mining.  Interested?', 'I can instruct you in mining.  Interested?', '0', '1', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '15595'); 




/* Step 2.7 Table  `gossip_menu_option */
DELETE FROM gossip_menu_option WHERE  `menu_id` = 7690;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
('7690', '0', '3', 'Train me.', '5', '16', '0', '0', '0', '0', '');


/*## Step 5: Creature NPC Trainer / Vendor ############################*/

/* Step 2.0 Table  `npc_trainer */
DELETE FROM npc_trainer WHERE `entry` = @ENTRY;
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES 
(@ENTRY, '2575', '10', '186', '0', '5'),  /* Spell(2575): Mining*/
(@ENTRY, '2576', '500', '186', '50', '10'),  /* Spell(2576): Mining*/
(@ENTRY, '2658', '200', '186', '65', '0'),  /* Spell(2658): Smelt Silver*/
(@ENTRY, '2659', '200', '186', '50', '0'),  /* Spell(2659): Smelt Bronze*/
(@ENTRY, '3304', '50', '186', '50', '0'),  /* Spell(3304): Smelt Tin*/
(@ENTRY, '3307', '500', '186', '100', '0'),  /* Spell(3307): Smelt Iron*/
(@ENTRY, '3308', '600', '186', '115', '0'),  /* Spell(3308): Smelt Gold*/
(@ENTRY, '3564', '5000', '186', '125', '25'),  /* Spell(3564): Mining*/
(@ENTRY, '3569', '750', '186', '125', '0'),  /* Spell(3569): Smelt Steel*/
(@ENTRY, '10097', '5000', '186', '150', '0'),  /* Spell(10097): Smelt Mithril*/
(@ENTRY, '10098', '10000', '186', '165', '0'),  /* Spell(10098): Smelt Truesilver*/
(@ENTRY, '10248', '50000', '186', '200', '35'),  /* Spell(10248): Mining*/
(@ENTRY, '16153', '20000', '186', '230', '0'),  /* Spell(16153): Smelt Thorium*/
(@ENTRY, '29354', '100000', '186', '275', '50'),  /* Spell(29354): Mining*/
(@ENTRY, '29356', '40000', '186', '275', '0'),  /* Spell(29356): Smelt Fel Iron*/
(@ENTRY, '29358', '40000', '186', '325', '0'),  /* Spell(29358): Smelt Adamantite*/
(@ENTRY, '29359', '40000', '186', '350', '0'),  /* Spell(29359): Smelt Eternium*/
(@ENTRY, '29360', '40000', '186', '350', '0'),  /* Spell(29360): Smelt Felsteel*/
(@ENTRY, '29361', '100000', '186', '375', '0'),  /* Spell(29361): Smelt Khorium*/
(@ENTRY, '29686', '100000', '186', '375', '0'),  /* Spell(29686): Smelt Hardened Adamantite*/
(@ENTRY, '35750', '10000', '186', '300', '0'),  /* Spell(35750): Earth Shatter*/
(@ENTRY, '35751', '10000', '186', '300', '0'),  /* Spell(35751): Fire Sunder*/
(@ENTRY, '49252', '100000', '186', '350', '0'),  /* Spell(49252): Smelt Cobalt*/
(@ENTRY, '49258', '150000', '186', '400', '0'),  /* Spell(49258): Smelt Saronite*/
(@ENTRY, '50310', '350000', '186', '350', '65'),  /* Spell(50310): Mining*/
(@ENTRY, '55208', '200000', '186', '450', '0'),  /* Spell(55208): Smelt Titansteel*/
(@ENTRY, '55211', '200000', '186', '450', '0'),  /* Spell(55211): Smelt Titanium*/
(@ENTRY, '70524', '10000', '186', '250', '0'),  /* Spell(70524): Enchanted Thorium Bar*/
(@ENTRY, '74517', '500000', '186', '425', '75'),  /* Spell(74517): Mining*/
(@ENTRY, '74529', '50000', '186', '525', '0'),  /* Spell(74529): Smelt Pyrite*/
(@ENTRY, '74530', '50000', '186', '475', '0'),  /* Spell(74530): Smelt Elementium*/
(@ENTRY, '74537', '50000', '186', '500', '0'),  /* Spell(74537): Smelt Hardened Elementium*/
(@ENTRY, '84038', '50000', '186', '425', '0'),  /* Spell(84038): Smelt Obsidium*/
(@ENTRY, '102161', '666666', '186', '500', '80'),  /* Spell(102161): Mining*/
(@ENTRY, '102165', '66666', '186', '500', '0'),  /* Spell(102165): Smelt Ghost Iron*/
(@ENTRY, '102167', '66666', '186', '600', '0');  /* Spell(102167): Smelt Trillium*/


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

