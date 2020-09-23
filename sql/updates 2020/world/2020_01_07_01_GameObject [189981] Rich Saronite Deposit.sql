/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 7/1/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Rich Saronite Deposit';
SET @ENTRY 		:= '189981';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 4.1 Table  `gameobject_template */
DELETE FROM `gameobject_template` WHERE `entry` = @ENTRY;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`,  `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `unkInt32`, `AIName`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '3', '7804', 'Rich Saronite Deposit', '', '', '', '0', '0', '0.75', '0', '0', '0', '0', '0', '0', '1784', '189981', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '75', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '65', '', '', '15595'); 


/* Step 4.1 Table  `gameobject */
DELETE FROM `gameobject` WHERE `id` = @ENTRY;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `phaseId`, `position_x`, `position_y`, `position_z`, `orientation`,`rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `isActive`, `protect_anti_doublet`) VALUES 
(NULL, @ENTRY, '571', '67', '4462', '1', '1', '0', '6523.62', '-1265.09', '405.482', '-1.58825', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '67', '4462', '1', '1', '0', '6518.71', '-1309.9', '407.208', '2.21656', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4507', '1', '1', '0', '6514.27', '896.626', '290.645', '1.29154', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4504', '1', '1', '0', '6466.15', '137.682', '444.719', '2.35619', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '67', '4419', '1', '1', '0', '6394.66', '-876.401', '409.343', '1.27409', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4520', '1', '1', '0', '6367.61', '1682.05', '548.518', '-0.83776', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '67', '4451', '1', '1', '0', '6344.36', '-785.474', '408.019', '-1.8675', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4385', '1', '1', '0', '6215.25', '5172.35', '-97.6636', '0.24435', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '6205.15', '4325.34', '-38.2094', '-0.05236', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '6174.17', '5636.43', '-22.3877', '-1.93731', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4519', '1', '1', '0', '6171.92', '2015.67', '531.432', '-1.43117', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4519', '1', '1', '0', '6166.92', '2004.08', '541.962', '1.79769', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4504', '1', '1', '0', '6145.68', '658.17', '215.264', '-1.41372', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4282', '1', '1', '0', '6096.59', '3644.3', '143.128', '-2.84488', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4522', '1', '1', '0', '6038.56', '2326.35', '514.513', '1.69297', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '67', '4419', '1', '1', '0', '5990.06', '-1015.17', '446.638', '2.19911', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4519', '1', '1', '0', '5957.89', '2517.91', '537.277', '1.09956', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4522', '1', '1', '0', '5914.5', '2015.98', '516.339', '2.93214', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4283', '1', '1', '0', '5859.75', '4020.99', '-68.8248', '0.10472', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4522', '1', '1', '0', '5857.44', '1936.72', '510.884', '0.17453', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '4615', '1', '1', '0', '5842.43', '1858.81', '-345.3', '-2.68781', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5827.04', '4457.58', '-130.453', '1.64061', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5735.86', '5612.5', '-67.5912', '-2.58308', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5684.08', '5541.49', '-72.1058', '-1.64061', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5656.22', '6023.45', '-28.9304', '-1.88495', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4295', '1', '1', '0', '5608.65', '3865.18', '-99.3376', '-1.91986', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4283', '1', '1', '0', '5522.84', '3836.81', '-62.7052', '2.04204', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4290', '1', '1', '0', '5521.06', '4926.98', '-192.771', '2.56563', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5509.58', '3579.71', '-12.9631', '1.43117', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4285', '1', '1', '0', '5494.62', '5677.87', '-97.2142', '1.93731', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4293', '1', '1', '0', '5483.64', '4688.75', '-122.003', '0.8203', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4285', '1', '1', '0', '5455.97', '5712.2', '-102.766', '-0.59341', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '5449.99', '3279.56', '417.628', '-0.994837', '0', '0', '0', '1', '1200', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4387', '1', '1', '0', '5443.15', '4694.67', '-187.941', '2.44346', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '5374.9', '3447.72', '387.202', '-0.366518', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5341.82', '5396.05', '-106.745', '2.00713', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5325.52', '6025.47', '-16.2582', '-0.83776', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4293', '1', '1', '0', '5271.99', '5251.52', '-124.859', '1.5708', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5232.45', '4195.25', '-93.5727', '1.67551', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4288', '1', '1', '0', '5199.74', '5436.71', '-81.6717', '-0.69813', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5171.4', '3794.75', '-12.2962', '2.00713', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '210', '1', '1', '0', '5112.76', '1896.37', '712.176', '-2.47837', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5094.27', '5217.79', '-88.322', '-2.21656', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5013.69', '5436.41', '-94.5146', '-1.0821', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '210', '210', '1', '1', '0', '5010.67', '1804.19', '678.496', '-2.86233', '0', '0', '0', '1', '1200', '100', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4585', '1', '1', '0', '4889.06', '1872.17', '457.047', '-2.65289', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4884.83', '4321.19', '-54.8871', '-3.00195', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4287', '1', '1', '0', '4847.24', '5953.83', '-15.9588', '-1.15192', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4287', '1', '1', '0', '4846.78', '5769.55', '-57.8889', '2.56563', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4585', '1', '1', '0', '4824.48', '2116.74', '344.722', '0.279252', '0', '0', '0', '1', '1200', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4737.14', '4847.46', '-67.218', '1.65806', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4732.28', '5135.1', '-53.4326', '-1.51844', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '4716.54', '4978.44', '-44.2661', '1.62316', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '4566.63', '2525.63', '361.946', '2.28638', '0', '0', '0', '1', '1200', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4581', '1', '1', '0', '4404', '1979.09', '411.626', '3.00195', '0', '0', '0', '1', '1200', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4584', '1', '1', '0', '4366.34', '1737.62', '367.385', '-2.11185', '0', '0', '0', '1', '1200', '100', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4584', '1', '1', '0', '4219.43', '1780.07', '350.979', '3.07541', '0', '0', '0.999452', '0.0330874', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '4161.99', '1967.17', '354.405', '-0.523598', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '4197', '4197', '1', '1', '0', '4108.6', '1969.11', '360.346', '1.39626', '0', '0', '0', '1', '1200', '255', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5546.83', '5923.93', '-50.437', '4.22419', '0', '0', '0.857041', '-0.515248', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5412.6', '5945.01', '-49.3529', '2.46489', '0', '0', '0.943304', '0.33193', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '3711', '1', '1', '0', '5283.07', '6009.83', '-36.5702', '2.31562', '0', '0', '0.915927', '0.401345', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4287', '1', '1', '0', '5039.1', '5952.98', '-55.4363', '3.6508', '0', '0', '0.967763', '-0.251863', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '571', '3711', '4287', '1', '1', '0', '4920.54', '6011.48', '-7.1446', '2.96751', '0', '0', '0.996214', '0.0869338', '300', '0', '1', '0', '0'); 


/*## Step 2: GObject Loots ###########################################*/

/* Step x.x Table  `gameobject_loot_template */
DELETE FROM gameobject_loot_template WHERE  `entry` = @ENTRY;
INSERT INTO `gameobject_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES 
(@ENTRY, '36912', '100', '1', '0', '3', '4'), 
(@ENTRY, '37701', '10', '1', '1', '1', '2'), 
(@ENTRY, '37703', '10', '1', '1', '1', '2'); 


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 36912;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('36912', '7', '7', '-1', 'Saronite Ore', '57335', '1', '262144', '8192', '0.9957', '1', '1', '6000', '1500', '0', '-1', '-1', '75', '0', '755', '400', '0', '0', '0', '0', '0', '0', '20', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1024', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '16135'); 


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 37701;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('37701', '7', '10', '-1', 'Crystallized Earth', '60020', '1', '1024', '8192', '0.9884', '1', '1', '2400', '600', '0', '-1', '-1', '75', '0', '0', '0', '0', '0', '0', '0', '0', '0', '10', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '49248', '0', '-1', '500', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '', '0', '0', '0', '0', '0', '4', '0', '0', '0', '0', '0', '0', '0', '1224', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '16135'); 


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 37703;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('37703', '7', '10', '-1', 'Crystallized Shadow', '55243', '1', '1024', '8192', '0.9957', '1', '1', '2400', '600', '0', '-1', '-1', '75', '0', '0', '0', '0', '0', '0', '0', '0', '0', '10', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '49246', '0', '-1', '500', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '', '0', '0', '0', '0', '0', '4', '0', '0', '0', '0', '0', '0', '0', '1224', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '16135'); 


/* Step 2.6 GObject > Quest Items Data: ItemID - Quality - SellPrice - ItemLevel - RequiredLevel - Name */
/*
36912  1  WAIHT_COMMON      0g 15s 0c  75  0  Saronite Ore
37701  1  WAIHT_COMMON      0g 6s 0c  75  0  Crystallized Earth
37703  1  WAIHT_COMMON      0g 6s 0c  75  0  Crystallized Shadow
*/



/* Step 2.2 Table  `gameobject_questrelation */
DELETE FROM  `gameobject_questrelation` WHERE `id`= @ENTRY;
/* Step 2.2 Table  `gameobject_involvedrelation */
DELETE FROM  `gameobject_involvedrelation` WHERE `id`= @ENTRY;
/*## Step 3: GObjects Conditions #####################################*/

/*## Step 4: GObjects Needs to Work ##################################*/


