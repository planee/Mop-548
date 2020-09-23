/*
SQL RoG WoW				  
Desarrollado por:
Fecha: 27/10/2019
### Scripts Privados / Derechos Reservados RoG WoW ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Zeb\'tula Stoneshield';
SET @ENTRY 		:= '69517';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '47588', '47589', '0', '0', @CREATURE, '', '', '0', '90', '90', '4', '0', '14', '14', '0', '0', '1', '1.14286', '0', '1.14286', '1', '0', '9839', '14339', '0', '42299', '1', '2000', '2000', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '7', '0', '0', '69517', '69517', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '3577', '3577', '', '0', '3', '1', '1.5', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '', '17614');

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('47588', '0.3', '1.5', '2', '0'), 
('47589', '0.3', '1.5', '2', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 69517 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '1064', '6507', '6726', '1', '4096', '0', '0', '6917.53', '6026.46', '7.54733', '3.55567', '300', '0', '0', '393941', '0', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '6917.53' AND `position_y` REGEXP '6026.46' AND `position_z` REGEXP '7.54733' AND `phaseMask` = '4096' AND `map` = '1064');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '6917.53' AND `position_y` REGEXP '6026.46' AND `position_z` REGEXP '7.54733' AND `phaseMask` = '4096' AND `map` = '1064');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;


/*## Step 2: Creature Loots ##########################################*/

/* Step 1.3 Table  `creature_loot_template */
DELETE FROM `creature_loot_template` WHERE `entry` = 69517;
INSERT INTO `creature_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`) VALUES 
('69517', '100865', '0.03', '1', '0', '1', '1'); 


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 100865;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('100865', '9', '4', '-1', 'Plans: Balanced Trillium Ingot and Its Uses', '55297', '3', '65600', '24576', '1.0268', '1', '1', '0', '0', '0', '-1', '-1', '90', '1', '164', '600', '0', '0', '0', '0', '0', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '143646', '0', '-1', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '1', 'Teaches you how to create Balanced Trillium Ingots. Also teaches you one of the ways in which it can be used.', '0', '0', '0', '0', '0', '4', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'); 


/* Step 2.2 Table  `creature_loot_currency */
DELETE FROM creature_loot_currency WHERE  `creature_id` = @ENTRY;
/* Step 2.1 Table  `creature_onkill_reputation */
DELETE FROM creature_onkill_reputation WHERE `creature_id` = @ENTRY;
INSERT INTO `creature_onkill_reputation` (`creature_id`,`RewOnKillRepFaction1`,`RewOnKillRepFaction2`,`MaxStanding1`,`IsTeamAward1`,`RewOnKillRepValue1`,`MaxStanding2`,`IsTeamAward2`,`RewOnKillRepValue2`,`TeamDependent`) VALUES 
(@ENTRY, '1359', '0', '0', '0', '25', '0', '0', '0', '0'); 


/* Step 2.3 Table  `pickpocketing_loot_template */
DELETE FROM pickpocketing_loot_template WHERE `entry` = @ENTRY;
INSERT INTO `pickpocketing_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES 
(@ENTRY, '87530', '0.27', '1', '0', '1', '1'), 
(@ENTRY, '88158', '0.08', '1', '0', '1', '1'), 
(@ENTRY, '88165', '0.3', '1', '0', '1', '1'); 


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 87530;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('87530', '15', '0', '-1', 'A Steamy Romance Novel: Hot and Misty', '18164', '0', '0', '8192', '1.0174', '1', '1', '50000', '12500', '0', '-1', '-1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '20', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '', '4596', '0', '1', '0', '0', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '16135'); 


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 88158;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('88158', '15', '0', '-1', 'Jade Infinity Charm', '54322', '0', '0', '8192', '0.9544', '1', '1', '200000', '50000', '0', '-1', '-1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '20', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', 'The depths go on forever.', '0', '0', '0', '0', '0', '4', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '16135'); 


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 88165;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('88165', '15', '0', '-1', 'Vine-Cracked Junkbox', '15590', '1', '4', '8192', '1.0066', '1', '1', '0', '0', '0', '-1', '-1', '90', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '', '0', '0', '0', '0', '2048', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '16135'); 


/* Step 2.4 Table  `skinning_loot_template */
DELETE FROM skinning_loot_template WHERE  `entry` = @ENTRY;
/*Creature Loot Template Items Data: Id - Quality - SellPrice - ItemLevel - RequiredLevel - Name */
/*
100865  3  BLUE_RARE         90  1  Plans: Balanced Trillium Ingot and Its Uses
*/
/*Pickpocketing Loot Template Items Data: Id - Quality - SellPrice - ItemLevel - RequiredLevel - Name */
/*
87530  0  GREY_POOR         1g 25s 0c  1  0  A Steamy Romance Novel: Hot and Misty
88158  0  GREY_POOR         5g 0s 0c  1  0  Jade Infinity Charm
88165  1  WAIHT_COMMON      90  0  Vine-Cracked Junkbox
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
/* Step 1.8 Table  `waypoints */
DELETE FROM waypoints WHERE  `entry` = @ENTRY;
/* Step 2.5 Table  `npc_spellclick_spells */
DELETE FROM npc_spellclick_spells WHERE  `npc_entry` = @ENTRY;
/* Step 2.6 Table  `pet_levelstats */
DELETE FROM pet_levelstats WHERE  `creature_entry` = @ENTRY;

