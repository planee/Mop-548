/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 7/1/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Small Thorium Vein';
SET @ENTRY 		:= '324';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 4.1 Table  `gameobject_template */
DELETE FROM `gameobject_template` WHERE `entry` = @ENTRY;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`,  `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `unkInt32`, `AIName`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '3', '3951', 'Small Thorium Vein', '', '', '', '94', '0', '0.5', '0', '0', '0', '0', '0', '0', '400', '324', '0', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '50', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '15595'); 


/* Step 4.1 Table  `gameobject */
DELETE FROM `gameobject` WHERE `id` = @ENTRY;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `phaseId`, `position_x`, `position_y`, `position_z`, `orientation`,`rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `isActive`, `protect_anti_doublet`) VALUES 
(NULL, @ENTRY, '1', '618', '2241', '1', '1', '0', '8205.87', '-3710.19', '731.187', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2241', '1', '1', '0', '8093.88', '-3721.22', '736.913', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2241', '1', '1', '0', '8052.18', '-4106.5', '709.412', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '618', '1', '1', '0', '7958.79', '-4459.15', '725.549', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '618', '1', '1', '0', '7800.66', '-4646.77', '712.265', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2242', '1', '1', '0', '7675.33', '-4910.79', '698.404', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2241', '1', '1', '0', '7587.46', '-3771.28', '720.367', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '618', '1', '1', '0', '7380.87', '-4210.57', '706.524', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2253', '1', '1', '0', '7273.57', '-3965.13', '713.907', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '618', '1', '1', '0', '7268.84', '-4729.48', '694.893', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '618', '1', '1', '0', '7068.04', '-4547.58', '650.076', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '618', '1', '1', '0', '6984.05', '-4569.05', '718.013', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2246', '1', '1', '0', '6917.58', '-2405.69', '592.434', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2246', '1', '1', '0', '6804.65', '-2849.83', '583.228', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '618', '1', '1', '0', '6755.22', '-3313.92', '673.196', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2246', '1', '1', '0', '6721.12', '-2585.63', '545.067', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2247', '1', '1', '0', '6693.55', '-5400.07', '763.665', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2247', '1', '1', '0', '6691.19', '-5299.36', '749.69', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2247', '1', '1', '0', '6651.75', '-5249.67', '753.747', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '618', '1', '1', '0', '6645.27', '-3202.9', '622.287', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '618', '1', '1', '0', '6319.26', '-3785.16', '729.313', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '618', '1', '1', '0', '6234.71', '-2361.84', '583.348', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2245', '1', '1', '0', '6159.97', '-4262.01', '655.703', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2245', '1', '1', '0', '6126.54', '-4203.09', '637.947', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2247', '1', '1', '0', '6123.08', '-5105.42', '819.122', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2245', '1', '1', '0', '6057.77', '-4223.18', '634.042', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2245', '1', '1', '0', '6021.06', '-4707.93', '788.524', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2247', '1', '1', '0', '5959.1', '-5074.64', '810.86', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2250', '1', '1', '0', '5787.78', '-4827.11', '795.082', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2248', '1', '1', '0', '5743.38', '-4412.79', '781.076', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2250', '1', '1', '0', '5544.79', '-4847.31', '818.242', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2250', '1', '1', '0', '5519.35', '-4860.67', '848.844', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2249', '1', '1', '0', '5509.29', '-4471.6', '770.541', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2249', '1', '1', '0', '5500.69', '-4617.51', '808.391', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '618', '2249', '1', '1', '0', '5210.11', '-4880.98', '697.195', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '8', '1777', '1', '1', '0', '-10504.9', '-2662.56', '52.0784', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '8', '75', '1', '1', '0', '-10542', '-3140.26', '33.7232', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '8', '1777', '1', '1', '0', '-10628.4', '-2467.36', '34.8427', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '8', '1797', '1', '1', '0', '-10704.9', '-3690.63', '31.7934', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '8', '1817', '1', '1', '0', '-10788.7', '-3734.79', '26.2039', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '8', '1817', '1', '1', '0', '-10831.8', '-3680.46', '23.1619', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '4', '1437', '1', '1', '0', '-10880.3', '-2870.79', '24.4796', '3.08918', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '8', '1817', '1', '1', '0', '-10887.8', '-3697.42', '19.5338', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '8', '1817', '1', '1', '0', '-11013.3', '-3691.09', '23.5298', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '4', '1438', '1', '1', '0', '-11132.3', '-3282.56', '15.667', '3.08918', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '4', '1437', '1', '1', '0', '-11153.7', '-2677.12', '17.2944', '4.57276', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '4', '2517', '1', '1', '0', '-11293.1', '-2909.63', '-1.53078', '0', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '4', '4', '1', '1', '0', '-11397.7', '-3196.66', '28.4255', '1.36136', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '4', '4', '1', '1', '0', '-11595.8', '-2978.78', '35.8618', '1.36136', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '4', '4', '1', '1', '0', '-11605.1', '-2723.5', '12.3934', '4.71239', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '0', '4', '4', '1', '1', '0', '-11642.4', '-3534.97', '35.3055', '1.36136', '0', '0', '0', '1', '900', '255', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '1942', '1', '1', '0', '-7914.77', '-1935.93', '-270.477', '3.61786', '0', '0', '0.97178', '-0.23589', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '1942', '1', '1', '0', '-7850.8', '-2044.9', '-272.037', '3.63358', '0', '0', '0.969896', '-0.243519', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '1942', '1', '1', '0', '-7808.99', '-2094.8', '-267.29', '5.24363', '0', '0', '0.496686', '-0.86793', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '1942', '1', '1', '0', '-7661.56', '-2219.62', '-266.108', '5.69523', '0', '0', '0.28976', '-0.957099', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '1942', '1', '1', '0', '-7475.88', '-2282.64', '-258.786', '4.98053', '0', '0', '0.606242', '-0.79528', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '1942', '1', '1', '0', '-7325.39', '-2319.83', '-263.606', '5.86016', '0', '0', '0.209938', '-0.977715', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '1942', '1', '1', '0', '-7176.41', '-2291.66', '-268.087', '5.86802', '0', '0', '0.206097', '-0.978532', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '490', '1', '1', '0', '-7037.87', '-2301.44', '-266.647', '0.134605', '0', '0', '0.0672515', '0.997736', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '4885', '1', '1', '0', '-6880.18', '-2245.83', '-266.594', '0.146386', '0', '0', '0.0731274', '0.997323', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '4885', '1', '1', '0', '-6715.87', '-2195.16', '-264.454', '0.900368', '0', '0', '0.435131', '0.900367', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '4885', '1', '1', '0', '-6563.95', '-2101.24', '-269.39', '0.173874', '0', '0', '0.0868276', '0.996223', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '4885', '1', '1', '0', '-6469.87', '-1984.46', '-271.35', '1.3559', '0', '0', '0.627197', '0.778861', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '542', '1', '1', '0', '-6458.11', '-1847.01', '-269.475', '0.433056', '0', '0', '0.21484', '0.976649', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '542', '1', '1', '0', '-6365.82', '-1767.4', '-266.222', '0.472325', '0', '0', '0.233974', '0.972243', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '542', '1', '1', '0', '-6352.71', '-1658.3', '-266.62', '0.971053', '0', '0', '0.466674', '0.884429', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '538', '1', '1', '0', '-6316.54', '-1531.01', '-261.568', '1.24202', '0', '0', '0.581855', '0.813292', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '538', '1', '1', '0', '-6302.8', '-1367.65', '-265.13', '1.32056', '0', '0', '0.613336', '0.789822', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '538', '1', '1', '0', '-6283.73', '-1207.39', '-265.651', '1.12421', '0', '0', '0.532967', '0.846136', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '538', '1', '1', '0', '-6353.09', '-1033.7', '-267.716', '2.05098', '0', '0', '0.854967', '0.518682', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '4884', '1', '1', '0', '-6453.94', '-827.112', '-269.707', '1.86641', '0', '0', '0.803531', '0.595263', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '4884', '1', '1', '0', '-6466.81', '-633.742', '-268.771', '1.34019', '0', '0', '0.62106', '0.783763', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '4884', '1', '1', '0', '-6598.74', '-560.503', '-265.799', '3.233', '0', '0', '0.998956', '-0.045688', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '4884', '1', '1', '0', '-6788.84', '-437.675', '-269.783', '2.39262', '0', '0', '0.930696', '0.365793', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '4884', '1', '1', '0', '-6983.83', '-377.282', '-267.618', '2.47116', '0', '0', '0.94434', '0.328972', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '543', '1', '1', '0', '-7139.34', '-354.652', '-267.211', '2.77354', '0', '0', '0.983115', '0.182988', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '543', '1', '1', '0', '-7325.38', '-351.27', '-265.56', '2.62039', '0', '0', '0.966235', '0.257662', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '543', '1', '1', '0', '-7482.48', '-406.693', '-264.628', '3.34688', '0', '0', '0.994737', '-0.102465', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '539', '1', '1', '0', '-7654.68', '-456.198', '-269.188', '3.20158', '0', '0', '0.99955', '-0.0299915', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '539', '1', '1', '0', '-7801.51', '-556.251', '-259.684', '3.10341', '0', '0', '0.999818', '0.0190909', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '539', '1', '1', '0', '-7944.66', '-599.685', '-250.291', '3.34296', '0', '0', '0.994936', '-0.100511', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '539', '1', '1', '0', '-8006.72', '-753.965', '-237.687', '3.79063', '0', '0', '0.947804', '-0.318854', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '539', '1', '1', '0', '-8047.67', '-892.974', '-255.703', '3.67675', '0', '0', '0.964413', '-0.264399', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '539', '1', '1', '0', '-8080.01', '-1077.23', '-261.295', '3.86133', '0', '0', '0.935943', '-0.352151', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '540', '1', '1', '0', '-8103.65', '-1487.99', '-268.676', '4.66636', '0', '0', '0.723193', '-0.690646', '300', '0', '1', '0', '0'), 
(NULL, @ENTRY, '1', '490', '490', '1', '1', '0', '-8039.95', '-1666.83', '-267.755', '4.98837', '0', '0', '0.603119', '-0.797651', '300', '0', '1', '0', '0'); 


/*## Step 2: GObject Loots ###########################################*/

/* Step x.x Table  `gameobject_loot_template */
DELETE FROM gameobject_loot_template WHERE  `entry` = @ENTRY;
INSERT INTO `gameobject_loot_template` (`entry`,`item`,`ChanceOrQuestChance`,`lootmode`,`groupid`,`mincountOrRef`,`maxcount`) VALUES 
(@ENTRY, '10620', '100', '1', '0', '1', '2'), 
(@ENTRY, '12365', '50', '1', '1', '1', '3'); 


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 10620;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('10620', '7', '7', '-1', 'Thorium Ore', '20658', '1', '262144', '8192', '0.9994', '1', '1', '1000', '250', '0', '-1', '-1', '40', '0', '755', '250', '0', '0', '0', '0', '0', '0', '20', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1024', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '16135'); 


/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 12365;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('12365', '7', '7', '-1', 'Dense Stone', '23148', '1', '0', '8192', '0.9887', '1', '1', '1000', '250', '0', '-1', '-1', '45', '0', '0', '0', '0', '0', '0', '0', '0', '0', '20', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '0', '', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1024', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '16135'); 


/* Step 2.6 GObject > Quest Items Data: ItemID - Quality - SellPrice - ItemLevel - RequiredLevel - Name */
/*
10620  1  WAIHT_COMMON      0g 2s 50c  40  0  Thorium Ore
12365  1  WAIHT_COMMON      0g 2s 50c  45  0  Dense Stone
*/



/* Step 2.2 Table  `gameobject_questrelation */
DELETE FROM  `gameobject_questrelation` WHERE `id`= @ENTRY;
/* Step 2.2 Table  `gameobject_involvedrelation */
DELETE FROM  `gameobject_involvedrelation` WHERE `id`= @ENTRY;
/*## Step 3: GObjects Conditions #####################################*/

/*## Step 4: GObjects Needs to Work ##################################*/


