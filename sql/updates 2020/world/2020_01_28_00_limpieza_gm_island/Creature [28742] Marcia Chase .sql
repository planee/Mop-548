/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 28/1/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Marcia Chase';
SET @ENTRY 		:= '28742';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '25655', '0', '0', '0', @CREATURE, 'Fishing Trainer & Supplies', '', '9833', '75', '75', '2', '0', '35', '35', '723', '0', '1', '1.14286', '0', '1.14286', '1', '0', '342', '485', '0', '392', '1', '2000', '2000', '1', '32768', '2048', '0', '0', '2', '0', '0', '0', '295', '438', '68', '7', '4096', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '28742', '0', '0', '', '16048');

/* Step 1.2 Table `creature_equip_template */
DELETE FROM `creature_equip_template` WHERE `entry`= 28742;
INSERT INTO `creature_equip_template` (`entry`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES 
('28742', '1117', '0', '0'); /* [ItemEntry1(1117): Monster - Item, Fishing Pole] */

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES 
(@ENTRY, '0', '0', '0', '257', '0', ''); 


/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('25655', '0.208', '1.5', '1', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 28742 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '571', '4395', '4551', '1', '1', '25655', '0', '5707.31', '612.214', '646.791', '1.69297', '300', '0', '0', '10635', '0', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '5707.31' AND `position_y` REGEXP '612.214' AND `position_z` REGEXP '646.791' AND `phaseMask` = '1' AND `map` = '571');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
INSERT INTO `creature_addon` (`guid`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES 
(@GUID, '0', '0', '0', '257', '30', ''); 



/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '5707.31' AND `position_y` REGEXP '612.214' AND `position_z` REGEXP '646.791' AND `phaseMask` = '1' AND `map` = '571');
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
DELETE FROM gossip_menu WHERE  `entry` = 9833;
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES 
(9833, 13591); 
/* Step 4.6 Table  `npc_text` */
DELETE FROM npc_text WHERE `ID` = 13591;
INSERT INTO `npc_text` (`ID`,`text0_0`,`text0_1`,`lang0`,`prob0`,`em0_0`,`em0_1`,`em0_2`,`em0_3`,`em0_4`,`em0_5`,`text1_0`,`text1_1`,`lang1`,`prob1`,`em1_0`,`em1_1`,`em1_2`,`em1_3`,`em1_4`,`em1_5`,`text2_0`,`text2_1`,`lang2`,`prob2`,`em2_0`,`em2_1`,`em2_2`,`em2_3`,`em2_4`,`em2_5`,`text3_0`,`text3_1`,`lang3`,`prob3`,`em3_0`,`em3_1`,`em3_2`,`em3_3`,`em3_4`,`em3_5`,`text4_0`,`text4_1`,`lang4`,`prob4`,`em4_0`,`em4_1`,`em4_2`,`em4_3`,`em4_4`,`em4_5`,`text5_0`,`text5_1`,`lang5`,`prob5`,`em5_0`,`em5_1`,`em5_2`,`em5_3`,`em5_4`,`em5_5`,`text6_0`,`text6_1`,`lang6`,`prob6`,`em6_0`,`em6_1`,`em6_2`,`em6_3`,`em6_4`,`em6_5`,`text7_0`,`text7_1`,`lang7`,`prob7`,`em7_0`,`em7_1`,`em7_2`,`em7_3`,`em7_4`,`em7_5`,`WDBVerified`) VALUES 
('13591', '', 'Hello there! Care to buy some fishing supplies, or perhaps take a lesson or two?', '0', '1', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '12340'); 




/* Step 2.7 Table  `gossip_menu_option */
DELETE FROM gossip_menu_option WHERE  `menu_id` = 9833;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
('9833', '0', '3', 'Train me.', '5', '16', '0', '0', '0', '0', '');
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
('9833', '1', '1', 'I want to browse your goods.', '3', '128', '0', '0', '0', '0', '');


/*## Step 5: Creature NPC Trainer / Vendor ############################*/

/* Step 2.0 Table  `npc_trainer */
DELETE FROM npc_trainer WHERE `entry` = @ENTRY;
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES 
(@ENTRY, '7733', '100', '0', '0', '5'),  /* Spell(7733): Apprentice Fishing*/
(@ENTRY, '7734', '500', '356', '50', '10'),  /* Spell(7734): Journeyman Fishing*/
(@ENTRY, '18249', '25000', '356', '200', '35'),  /* Spell(18249): Artisan Fishing*/
(@ENTRY, '51293', '150000', '356', '350', '65'),  /* Spell(51293): Grand Master Fishing*/
(@ENTRY, '54083', '10000', '356', '125', '20'),  /* Spell(54083): Expert Fishing*/
(@ENTRY, '54084', '100000', '356', '275', '50'),  /* Spell(54084): Master Fishing*/
(@ENTRY, '88869', '500000', '356', '425', '75'),  /* Spell(88869): Illustrious Grand Master Fishing*/
(@ENTRY, '110412', '300000', '356', '500', '81');  /* Spell(110412): Zen Master Fishing*/


/* Step 1.9 Table  `npc_vendor */
DELETE FROM npc_vendor WHERE  `entry` = @ENTRY;
INSERT INTO `npc_vendor` (`entry`,`slot`,`item`,`maxcount`,`incrtime`,`ExtendedCost`,`type`) VALUES 
(@ENTRY, '0', '6256', '0', '0', '0', '1'),   /* Item(6256): Fishing Pole, ItemLevel: 1, RequiredLevel: 0, ItemQuality: WAIHT_COMMON     */
(@ENTRY, '0', '6365', '1', '3600', '0', '1'),   /* Item(6365): Strong Fishing Pole, ItemLevel: 10, RequiredLevel: 5, ItemQuality: WAIHT_COMMON     */
(@ENTRY, '0', '6529', '0', '0', '0', '1'),   /* Item(6529): Shiny Bauble, ItemLevel: 10, RequiredLevel: 0, ItemQuality: WAIHT_COMMON     */
(@ENTRY, '0', '6530', '0', '0', '0', '1'),   /* Item(6530): Nightcrawlers, ItemLevel: 20, RequiredLevel: 0, ItemQuality: WAIHT_COMMON     */
(@ENTRY, '0', '6532', '0', '0', '0', '1'),   /* Item(6532): Bright Baubles, ItemLevel: 30, RequiredLevel: 0, ItemQuality: WAIHT_COMMON     */
(@ENTRY, '0', '6533', '2', '3600', '0', '1'),   /* Item(6533): Aquadynamic Fish Attractor, ItemLevel: 30, RequiredLevel: 0, ItemQuality: WAIHT_COMMON     */
(@ENTRY, '0', '33451', '0', '0', '0', '1'),   /* Item(33451): Fillet of Icefin, ItemLevel: 65, RequiredLevel: 65, ItemQuality: WAIHT_COMMON     */
(@ENTRY, '0', '35951', '0', '0', '0', '1');   /* Item(35951): Poached Emperor Salmon, ItemLevel: 75, RequiredLevel: 75, ItemQuality: WAIHT_COMMON     */


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 6256;
/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 6365;
/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 6529;
/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 6530;
/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 6532;
/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 6533;
/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 33451;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('33451', '0', '5', '-1', 'Fillet of Icefin', '50869', '1', '0', '8192', '1.0028', '1', '5', '8500', '425', '0', '-1', '-1', '65', '65', '0', '0', '0', '0', '0', '0', '0', '0', '20', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '43180', '0', '-1', '0', '11', '1000', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '', '0', '0', '0', '0', '0', '4', '0', '0', '0', '0', '0', '0', '0', '65536', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '16135'); 


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 35951;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('35951', '0', '5', '-1', 'Poached Emperor Salmon', '50872', '1', '0', '8192', '0.9806', '1', '5', '16000', '800', '0', '-1', '-1', '75', '75', '0', '0', '0', '0', '0', '0', '0', '0', '20', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '45548', '0', '-1', '0', '11', '1000', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '', '0', '0', '0', '0', '0', '4', '0', '0', '0', '0', '0', '0', '0', '65536', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '16135'); 


/*## Step 6: Creature NPC Conditions ##################################*/

/* Step 6.9 Table `conditions` */
/*DELETE FROM  `conditions` WHERE `SourceTypeOrReferenceId` AND `SourceGroup`;
*/

/*## Step 7: Creature NPC Needs to Work ###############################*/

/* Step 2.2 Table  `creature_questrelation */
DELETE FROM  `creature_questrelation` WHERE `id`= @ENTRY;
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES 
('28742', '13830'),  /* Quest(13830): The Ghostfish ,QuestMinLevel: 70 ,QuestProfession ID: 356[Fishing] */ 
('28742', '13832'),  /* Quest(13832): Jewel Of The Sewers ,QuestMinLevel: 70 ,QuestProfession ID: 356[Fishing] */ 
('28742', '13833'),  /* Quest(13833): Blood Is Thicker ,QuestMinLevel: 70 ,QuestProfession ID: 356[Fishing] */ 
('28742', '13834'),  /* Quest(13834): Dangerously Delicious ,QuestMinLevel: 70 ,QuestProfession ID: 356[Fishing] */ 
('28742', '13836');  /* Quest(13836): Disarmed! ,QuestMinLevel: 70 ,QuestProfession ID: 356[Fishing] */ 


/* Step 2.2 Table  `creature_involvedrelation */
DELETE FROM  `creature_involvedrelation` WHERE `id`= @ENTRY;
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES 
('28742', '13830'),  /* Quest(13830): The Ghostfish ,QuestMinLevel: 70 ,QuestProfession ID: 356[Fishing] */ 
('28742', '13832'),  /* Quest(13832): Jewel Of The Sewers ,QuestMinLevel: 70 ,QuestProfession ID: 356[Fishing] */ 
('28742', '13833'),  /* Quest(13833): Blood Is Thicker ,QuestMinLevel: 70 ,QuestProfession ID: 356[Fishing] */ 
('28742', '13834');  /* Quest(13834): Dangerously Delicious ,QuestMinLevel: 70 ,QuestProfession ID: 356[Fishing] */ 


/* Step 1.8 Table  `waypoints */
DELETE FROM waypoints WHERE  `entry` = @ENTRY;
/* Step 2.5 Table  `npc_spellclick_spells */
DELETE FROM npc_spellclick_spells WHERE  `npc_entry` = @ENTRY;
/* Step 2.6 Table  `pet_levelstats */
DELETE FROM pet_levelstats WHERE  `creature_entry` = @ENTRY;

