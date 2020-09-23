/*
SQL RoG WoW				  
Desarrollado por:
Fecha: 31/10/2019
### Scripts Privados / Derechos Reservados RoG WoW ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Frightened Peon';
SET @ENTRY 		:= '41989';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '10038', '11859', '11860', '0', @CREATURE, '', 'Inspect', '0', '19', '21', '0', '0', '7', '7', '16777216', '0', '1', '1.14286', '0', '1.14286', '1', '0', '26', '38', '0', '10', '1', '2000', '2000', '1', '33280', '2048', '0', '0', '0', '0', '0', '0', '21', '30', '8', '7', '6144', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1.3', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '41989', '0', '0', '', '16048');

/* Step 1.2 Table `creature_equip_template */
DELETE FROM `creature_equip_template` WHERE `entry`= 41989;
INSERT INTO `creature_equip_template` (`entry`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES 
('41989', '2901', '0', '0'); /* [ItemEntry1(2901): Mining Pick] */

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES 
(@ENTRY, '0', '0', '0', '1', '0', ''); 


/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('10038', '0.2976', '1.2', '0', '0'), 
('11859', '0.372', '1.5', '0', '11857'), 
('11860', '0.372', '1.5', '0', '11858'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
INSERT INTO `creature_text` (`entry`, `groupid`, `id`, `text`, `type`, `language`, `probability`, `emote`, `duration`, `sound`, `comment`) VALUES 
(@ENTRY, '0', '0', 'Oof! You touch naughty spot!', '12', '0', '100', '0', '0', '0', 'Raufen - Frightened Peon on spellclick'), 
(@ENTRY, '0', '1', 'Thanks!', '12', '0', '100', '0', '0', '0', 'Raufen - Frightened Peon on spellclick'), 
(@ENTRY, '0', '2', 'Which way to go???', '12', '0', '100', '0', '0', '0', 'Raufen - Frightened Peon on spellclick'), 
(@ENTRY, '0', '3', 'Why dis happen???', '12', '0', '100', '0', '0', '0', 'Raufen - Frightened Peon on spellclick'), 
(@ENTRY, '0', '4', 'You is friend. Thanks!', '12', '0', '100', '0', '0', '0', 'Raufen - Frightened Peon on spellclick'); 


/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 41989 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '1', '406', '2160', '1', '1', '0', '41989', '887.406', '-297.26', '8.43657', '4.8026', '300', '0', '0', '1167', '0', '0', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '2160', '1', '1', '0', '41989', '922.095', '-293.347', '-1.68512', '2.93336', '300', '0', '0', '1355', '0', '0', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '2160', '1', '1', '0', '41989', '901.167', '-274.284', '2.57942', '2.33253', '300', '0', '0', '1355', '0', '0', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '2160', '1', '1', '0', '41989', '887.214', '-272.551', '6.48711', '3.96223', '300', '0', '0', '1355', '0', '0', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '2160', '1', '1', '0', '41989', '940.514', '-254.741', '-2.22211', '0.180535', '300', '0', '0', '1258', '0', '0', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '2160', '1', '1', '11857', '41989', '957.823', '-260.7', '-5.11467', '2.58778', '300', '0', '0', '1355', '0', '0', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '2160', '1', '1', '0', '41989', '919.661', '-276.369', '-1.05786', '4.06826', '300', '0', '0', '1355', '0', '0', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '829.505', '-63.0521', '15.819', '5.65487', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '911.311', '-117.793', '10.4166', '3.35103', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '929.566', '-159.681', '8.33503', '2.54818', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '338.938', '-188.526', '59.3122', '5.65487', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '826.932', '-192.556', '15.0599', '5.65487', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '878.884', '-196.056', '9.72935', '2.80998', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '928.413', '-165.759', '8.9322', '2.96706', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '327.25', '-265.082', '61.8615', '0.575959', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '800.472', '-71.5781', '15.7171', '0.959931', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '681.359', '-60.9375', '33.5239', '1.44862', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '773.67', '44.6285', '9.31575', '5.25344', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '718.32', '34.934', '15.6779', '4.74729', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '851.818', '9.81944', '5.84491', '4.15388', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '769.562', '-26.1076', '13.168', '5.65487', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '802.3', '-41.6701', '16.1479', '2.77507', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '710.318', '-23.75', '23.2646', '0.191986', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '713.328', '-47.2656', '27.6686', '2.26893', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '512.906', '-14.059', '27.7397', '4.69494', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '583.391', '-45.2205', '30.3041', '0.20944', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '447.295', '-12.0781', '29.8675', '5.65487', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '444.724', '-20.0851', '30.1798', '5.67232', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '405.557', '-55.7865', '35.6467', '5.14872', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '452.439', '-83.1076', '39.7077', '0.506145', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '535.029', '-98.7517', '39.0764', '2.47837', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '1', '406', '4932', '1', '1', '0', '0', '603.276', '27.0069', '17.6735', '6.16101', '120', '7.786', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '887.406' AND `position_y` REGEXP '-297.26' AND `position_z` REGEXP '8.43657' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '887.406' AND `position_y` REGEXP '-297.26' AND `position_z` REGEXP '8.43657' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '922.095' AND `position_y` REGEXP '-293.347' AND `position_z` REGEXP '-1.68512' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '922.095' AND `position_y` REGEXP '-293.347' AND `position_z` REGEXP '-1.68512' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '901.167' AND `position_y` REGEXP '-274.284' AND `position_z` REGEXP '2.57942' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '901.167' AND `position_y` REGEXP '-274.284' AND `position_z` REGEXP '2.57942' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '887.214' AND `position_y` REGEXP '-272.551' AND `position_z` REGEXP '6.48711' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '887.214' AND `position_y` REGEXP '-272.551' AND `position_z` REGEXP '6.48711' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '940.514' AND `position_y` REGEXP '-254.741' AND `position_z` REGEXP '-2.22211' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '940.514' AND `position_y` REGEXP '-254.741' AND `position_z` REGEXP '-2.22211' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '957.823' AND `position_y` REGEXP '-260.7' AND `position_z` REGEXP '-5.11467' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '957.823' AND `position_y` REGEXP '-260.7' AND `position_z` REGEXP '-5.11467' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '919.661' AND `position_y` REGEXP '-276.369' AND `position_z` REGEXP '-1.05786' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '919.661' AND `position_y` REGEXP '-276.369' AND `position_z` REGEXP '-1.05786' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '829.505' AND `position_y` REGEXP '-63.0521' AND `position_z` REGEXP '15.819' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '829.505' AND `position_y` REGEXP '-63.0521' AND `position_z` REGEXP '15.819' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '911.311' AND `position_y` REGEXP '-117.793' AND `position_z` REGEXP '10.4166' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '911.311' AND `position_y` REGEXP '-117.793' AND `position_z` REGEXP '10.4166' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '929.566' AND `position_y` REGEXP '-159.681' AND `position_z` REGEXP '8.33503' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '929.566' AND `position_y` REGEXP '-159.681' AND `position_z` REGEXP '8.33503' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '338.938' AND `position_y` REGEXP '-188.526' AND `position_z` REGEXP '59.3122' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '338.938' AND `position_y` REGEXP '-188.526' AND `position_z` REGEXP '59.3122' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '826.932' AND `position_y` REGEXP '-192.556' AND `position_z` REGEXP '15.0599' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '826.932' AND `position_y` REGEXP '-192.556' AND `position_z` REGEXP '15.0599' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '878.884' AND `position_y` REGEXP '-196.056' AND `position_z` REGEXP '9.72935' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '878.884' AND `position_y` REGEXP '-196.056' AND `position_z` REGEXP '9.72935' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '928.413' AND `position_y` REGEXP '-165.759' AND `position_z` REGEXP '8.9322' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '928.413' AND `position_y` REGEXP '-165.759' AND `position_z` REGEXP '8.9322' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '327.25' AND `position_y` REGEXP '-265.082' AND `position_z` REGEXP '61.8615' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '327.25' AND `position_y` REGEXP '-265.082' AND `position_z` REGEXP '61.8615' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '800.472' AND `position_y` REGEXP '-71.5781' AND `position_z` REGEXP '15.7171' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '800.472' AND `position_y` REGEXP '-71.5781' AND `position_z` REGEXP '15.7171' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '681.359' AND `position_y` REGEXP '-60.9375' AND `position_z` REGEXP '33.5239' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '681.359' AND `position_y` REGEXP '-60.9375' AND `position_z` REGEXP '33.5239' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '773.67' AND `position_y` REGEXP '44.6285' AND `position_z` REGEXP '9.31575' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '773.67' AND `position_y` REGEXP '44.6285' AND `position_z` REGEXP '9.31575' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '718.32' AND `position_y` REGEXP '34.934' AND `position_z` REGEXP '15.6779' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '718.32' AND `position_y` REGEXP '34.934' AND `position_z` REGEXP '15.6779' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '851.818' AND `position_y` REGEXP '9.81944' AND `position_z` REGEXP '5.84491' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '851.818' AND `position_y` REGEXP '9.81944' AND `position_z` REGEXP '5.84491' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '769.562' AND `position_y` REGEXP '-26.1076' AND `position_z` REGEXP '13.168' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '769.562' AND `position_y` REGEXP '-26.1076' AND `position_z` REGEXP '13.168' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '802.3' AND `position_y` REGEXP '-41.6701' AND `position_z` REGEXP '16.1479' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '802.3' AND `position_y` REGEXP '-41.6701' AND `position_z` REGEXP '16.1479' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '710.318' AND `position_y` REGEXP '-23.75' AND `position_z` REGEXP '23.2646' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '710.318' AND `position_y` REGEXP '-23.75' AND `position_z` REGEXP '23.2646' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '713.328' AND `position_y` REGEXP '-47.2656' AND `position_z` REGEXP '27.6686' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '713.328' AND `position_y` REGEXP '-47.2656' AND `position_z` REGEXP '27.6686' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '512.906' AND `position_y` REGEXP '-14.059' AND `position_z` REGEXP '27.7397' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '512.906' AND `position_y` REGEXP '-14.059' AND `position_z` REGEXP '27.7397' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '583.391' AND `position_y` REGEXP '-45.2205' AND `position_z` REGEXP '30.3041' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '583.391' AND `position_y` REGEXP '-45.2205' AND `position_z` REGEXP '30.3041' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '447.295' AND `position_y` REGEXP '-12.0781' AND `position_z` REGEXP '29.8675' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '447.295' AND `position_y` REGEXP '-12.0781' AND `position_z` REGEXP '29.8675' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '444.724' AND `position_y` REGEXP '-20.0851' AND `position_z` REGEXP '30.1798' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '444.724' AND `position_y` REGEXP '-20.0851' AND `position_z` REGEXP '30.1798' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '405.557' AND `position_y` REGEXP '-55.7865' AND `position_z` REGEXP '35.6467' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '405.557' AND `position_y` REGEXP '-55.7865' AND `position_z` REGEXP '35.6467' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '452.439' AND `position_y` REGEXP '-83.1076' AND `position_z` REGEXP '39.7077' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '452.439' AND `position_y` REGEXP '-83.1076' AND `position_z` REGEXP '39.7077' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '535.029' AND `position_y` REGEXP '-98.7517' AND `position_z` REGEXP '39.0764' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '535.029' AND `position_y` REGEXP '-98.7517' AND `position_z` REGEXP '39.0764' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '603.276' AND `position_y` REGEXP '27.0069' AND `position_z` REGEXP '17.6735' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '603.276' AND `position_y` REGEXP '27.0069' AND `position_z` REGEXP '17.6735' AND `phaseMask` = '1' AND `map` = '1');
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
/* Step 1.8 Table  `waypoints */
DELETE FROM waypoints WHERE  `entry` = @ENTRY;
/* Step 2.5 Table  `npc_spellclick_spells */
DELETE FROM npc_spellclick_spells WHERE  `npc_entry` = @ENTRY;
INSERT INTO `npc_spellclick_spells` (`npc_entry`,`spell_id`,`cast_flags`,`user_type`) VALUES 
(@ENTRY, '78269', '1', '0'); 


/* Step 2.6 Table  `pet_levelstats */
DELETE FROM pet_levelstats WHERE  `creature_entry` = @ENTRY;

