/*
SQL RoG WoW				  
Desarrollado por:
Fecha: 27/10/2019
### Scripts Privados / Derechos Reservados RoG WoW ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Silkmaster Tsai';
SET @ENTRY 		:= '57405';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '39634', '0', '0', '0', @CREATURE, '\"The Tailor of Pandaria\"', '', '0', '86', '86', '4', '0', '35', '35', '83', '0', '1', '1.14286', '0', '1.14286', '1', '1', '0', '0', '0', '0', '1', '2000', '2000', '1', '32768', '0', '0', '0', '2', '0', '0', '0', '0', '0', '0', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1783', '0', '', '1');

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES 
(@ENTRY, '0', '0', '0', '1', '0', ''); 


/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('39634', '0.347222', '1.5', '0', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 57405 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '530', '6455', '3431', '1', '1', '0', '0', '10360.8', '-6340.19', '31.3821', '2.94393', '300', '0', '0', '184350', '0', '0', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '860', '5736', '5825', '1', '32832', '0', '0', '1370.62', '3595.51', '88.9137', '2.306', '300', '0', '0', '184350', '0', '0', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '870', '5805', '5986', '1', '1', '0', '0', '-467.582', '219.476', '165.921', '1.44862', '1800', '0', '0', '1', '0', '0', '3', '0', '32768', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '10360.8' AND `position_y` REGEXP '-6340.19' AND `position_z` REGEXP '31.3821' AND `phaseMask` = '1' AND `map` = '530');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '10360.8' AND `position_y` REGEXP '-6340.19' AND `position_z` REGEXP '31.3821' AND `phaseMask` = '1' AND `map` = '530');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '1370.62' AND `position_y` REGEXP '3595.51' AND `position_z` REGEXP '88.9137' AND `phaseMask` = '32832' AND `map` = '860');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '1370.62' AND `position_y` REGEXP '3595.51' AND `position_z` REGEXP '88.9137' AND `phaseMask` = '32832' AND `map` = '860');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-467.582' AND `position_y` REGEXP '219.476' AND `position_z` REGEXP '165.921' AND `phaseMask` = '1' AND `map` = '870');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-467.582' AND `position_y` REGEXP '219.476' AND `position_z` REGEXP '165.921' AND `phaseMask` = '1' AND `map` = '870');
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
(@ENTRY, '2385', '50', '197', '10', '0'),  /* Spell(2385): Brown Linen Vest*/
(@ENTRY, '2386', '200', '197', '65', '0'),  /* Spell(2386): Linen Boots*/
(@ENTRY, '2392', '50', '197', '40', '0'),  /* Spell(2392): Red Linen Shirt*/
(@ENTRY, '2393', '25', '197', '1', '0'),  /* Spell(2393): White Linen Shirt*/
(@ENTRY, '2394', '50', '197', '40', '0'),  /* Spell(2394): Blue Linen Shirt*/
(@ENTRY, '2395', '300', '197', '70', '0'),  /* Spell(2395): Barbaric Linen Vest*/
(@ENTRY, '2396', '200', '197', '70', '0'),  /* Spell(2396): Green Linen Shirt*/
(@ENTRY, '2397', '200', '197', '60', '0'),  /* Spell(2397): Reinforced Linen Cape*/
(@ENTRY, '2399', '300', '197', '85', '0'),  /* Spell(2399): Green Woolen Vest*/
(@ENTRY, '2401', '300', '197', '95', '0'),  /* Spell(2401): Woolen Boots*/
(@ENTRY, '2402', '250', '197', '75', '0'),  /* Spell(2402): Woolen Cape*/
(@ENTRY, '2406', '200', '197', '100', '0'),  /* Spell(2406): Gray Woolen Shirt*/
(@ENTRY, '2964', '100', '197', '75', '0'),  /* Spell(2964): Bolt of Woolen Cloth*/
(@ENTRY, '3755', '100', '197', '45', '0'),  /* Spell(3755): Linen Bag*/
(@ENTRY, '3757', '200', '197', '80', '0'),  /* Spell(3757): Woolen Bag*/
(@ENTRY, '3813', '800', '197', '150', '0'),  /* Spell(3813): Small Silk Pack*/
(@ENTRY, '3839', '500', '197', '125', '0'),  /* Spell(3839): Bolt of Silk Cloth*/
(@ENTRY, '3840', '100', '197', '35', '0'),  /* Spell(3840): Heavy Linen Gloves*/
(@ENTRY, '3841', '200', '197', '60', '0'),  /* Spell(3841): Green Linen Bracers*/
(@ENTRY, '3842', '300', '197', '70', '0'),  /* Spell(3842): Handstitched Linen Britches*/
(@ENTRY, '3843', '400', '197', '85', '0'),  /* Spell(3843): Heavy Woolen Gloves*/
(@ENTRY, '3845', '300', '197', '80', '0'),  /* Spell(3845): Soft-soled Linen Boots*/
(@ENTRY, '3848', '500', '197', '110', '0'),  /* Spell(3848): Double-stitched Woolen Shoulders*/
(@ENTRY, '3850', '500', '197', '110', '0'),  /* Spell(3850): Heavy Woolen Pants*/
(@ENTRY, '3852', '750', '197', '130', '0'),  /* Spell(3852): Gloves of Meditation*/
(@ENTRY, '3855', '750', '197', '125', '0'),  /* Spell(3855): Spidersilk Boots*/
(@ENTRY, '3859', '750', '197', '150', '0'),  /* Spell(3859): Azure Silk Vest*/
(@ENTRY, '3861', '1000', '197', '185', '0'),  /* Spell(3861): Long Silken Cloak*/
(@ENTRY, '3865', '1000', '197', '175', '0'),  /* Spell(3865): Bolt of Mageweave*/
(@ENTRY, '3866', '250', '197', '110', '0'),  /* Spell(3866): Stylish Red Shirt*/
(@ENTRY, '3871', '500', '197', '170', '0'),  /* Spell(3871): Formal White Shirt*/
(@ENTRY, '3908', '10', '197', '0', '5'),  /* Spell(3908): Tailoring*/
(@ENTRY, '3909', '500', '197', '50', '10'),  /* Spell(3909): Tailoring*/
(@ENTRY, '3910', '5000', '197', '125', '25'),  /* Spell(3910): Tailoring*/
(@ENTRY, '3914', '50', '197', '30', '0'),  /* Spell(3914): Brown Linen Pants*/
(@ENTRY, '6521', '400', '197', '90', '0'),  /* Spell(6521): Pearl-clasped Cloak*/
(@ENTRY, '6690', '1000', '197', '135', '0'),  /* Spell(6690): Lesser Wizard's Robe*/
(@ENTRY, '7623', '50', '197', '30', '0'),  /* Spell(7623): Brown Linen Robe*/
(@ENTRY, '7624', '50', '197', '30', '0'),  /* Spell(7624): White Linen Robe*/
(@ENTRY, '8465', '50', '197', '40', '0'),  /* Spell(8465): Simple Dress*/
(@ENTRY, '8467', '250', '197', '110', '0'),  /* Spell(8467): White Woolen Dress*/
(@ENTRY, '8483', '500', '197', '160', '0'),  /* Spell(8483): White Swashbuckler's Shirt*/
(@ENTRY, '8489', '750', '197', '175', '0'),  /* Spell(8489): Red Swashbuckler's Shirt*/
(@ENTRY, '8758', '600', '197', '140', '0'),  /* Spell(8758): Azure Silk Pants*/
(@ENTRY, '8760', '600', '197', '145', '0'),  /* Spell(8760): Azure Silk Hood*/
(@ENTRY, '8762', '750', '197', '160', '0'),  /* Spell(8762): Silk Headband*/
(@ENTRY, '8764', '900', '197', '170', '0'),  /* Spell(8764): Earthen Vest*/
(@ENTRY, '8766', '1000', '197', '175', '0'),  /* Spell(8766): Azure Silk Belt*/
(@ENTRY, '8770', '1000', '197', '190', '0'),  /* Spell(8770): Robe of Power*/
(@ENTRY, '8772', '1000', '197', '175', '0'),  /* Spell(8772): Crimson Silk Belt*/
(@ENTRY, '8774', '1000', '197', '180', '0'),  /* Spell(8774): Green Silken Shoulders*/
(@ENTRY, '8776', '50', '197', '15', '0'),  /* Spell(8776): Linen Belt*/
(@ENTRY, '8791', '2500', '197', '185', '0'),  /* Spell(8791): Crimson Silk Vest*/
(@ENTRY, '8799', '3000', '197', '195', '0'),  /* Spell(8799): Crimson Silk Pantaloons*/
(@ENTRY, '8804', '5000', '197', '210', '0'),  /* Spell(8804): Crimson Silk Gloves*/
(@ENTRY, '12045', '50', '197', '20', '0'),  /* Spell(12045): Simple Linen Boots*/
(@ENTRY, '12046', '300', '197', '75', '0'),  /* Spell(12046): Simple Kilt*/
(@ENTRY, '12048', '4000', '197', '205', '0'),  /* Spell(12048): Black Mageweave Vest*/
(@ENTRY, '12049', '4000', '197', '205', '0'),  /* Spell(12049): Black Mageweave Leggings*/
(@ENTRY, '12050', '4000', '197', '210', '0'),  /* Spell(12050): Black Mageweave Robe*/
(@ENTRY, '12052', '5000', '197', '210', '0'),  /* Spell(12052): Shadoweave Pants*/
(@ENTRY, '12053', '5000', '197', '215', '0'),  /* Spell(12053): Black Mageweave Gloves*/
(@ENTRY, '12055', '5500', '197', '215', '0'),  /* Spell(12055): Shadoweave Robe*/
(@ENTRY, '12061', '2500', '197', '215', '0'),  /* Spell(12061): Orange Mageweave Shirt*/
(@ENTRY, '12065', '5000', '197', '225', '0'),  /* Spell(12065): Mageweave Bag*/
(@ENTRY, '12067', '5000', '197', '225', '0'),  /* Spell(12067): Dreamweave Gloves*/
(@ENTRY, '12069', '5000', '197', '225', '0'),  /* Spell(12069): Cindercloth Robe*/
(@ENTRY, '12070', '5000', '197', '225', '0'),  /* Spell(12070): Dreamweave Vest*/
(@ENTRY, '12071', '6000', '197', '225', '0'),  /* Spell(12071): Shadoweave Gloves*/
(@ENTRY, '12072', '6000', '197', '230', '0'),  /* Spell(12072): Black Mageweave Headband*/
(@ENTRY, '12073', '6000', '197', '230', '0'),  /* Spell(12073): Black Mageweave Boots*/
(@ENTRY, '12074', '6000', '197', '230', '0'),  /* Spell(12074): Black Mageweave Shoulders*/
(@ENTRY, '12076', '6500', '197', '235', '0'),  /* Spell(12076): Shadoweave Shoulders*/
(@ENTRY, '12077', '5000', '197', '235', '0'),  /* Spell(12077): Simple Black Dress*/
(@ENTRY, '12079', '6500', '197', '235', '0'),  /* Spell(12079): Red Mageweave Bag*/
(@ENTRY, '12082', '7000', '197', '240', '0'),  /* Spell(12082): Shadoweave Boots*/
(@ENTRY, '12088', '7500', '197', '245', '0'),  /* Spell(12088): Cindercloth Boots*/
(@ENTRY, '12092', '7500', '197', '250', '0'),  /* Spell(12092): Dreamweave Circlet*/
(@ENTRY, '12180', '50000', '197', '200', '35'),  /* Spell(12180): Tailoring*/
(@ENTRY, '18401', '10000', '197', '250', '0'),  /* Spell(18401): Bolt of Runecloth*/
(@ENTRY, '18402', '10000', '197', '255', '0'),  /* Spell(18402): Runecloth Belt*/
(@ENTRY, '18403', '10000', '197', '255', '0'),  /* Spell(18403): Frostweave Tunic*/
(@ENTRY, '18406', '10000', '197', '260', '0'),  /* Spell(18406): Runecloth Robe*/
(@ENTRY, '18407', '10000', '197', '260', '0'),  /* Spell(18407): Runecloth Tunic*/
(@ENTRY, '18409', '10000', '197', '265', '0'),  /* Spell(18409): Runecloth Cloak*/
(@ENTRY, '18410', '10000', '197', '265', '0'),  /* Spell(18410): Ghostweave Belt*/
(@ENTRY, '18411', '10000', '197', '265', '0'),  /* Spell(18411): Frostweave Gloves*/
(@ENTRY, '18413', '10000', '197', '270', '0'),  /* Spell(18413): Ghostweave Gloves*/
(@ENTRY, '18414', '10000', '197', '270', '0'),  /* Spell(18414): Brightcloth Robe*/
(@ENTRY, '18415', '10000', '197', '270', '0'),  /* Spell(18415): Brightcloth Gloves*/
(@ENTRY, '18416', '12500', '197', '275', '0'),  /* Spell(18416): Ghostweave Vest*/
(@ENTRY, '18417', '12500', '197', '275', '0'),  /* Spell(18417): Runecloth Gloves*/
(@ENTRY, '18420', '12500', '197', '275', '0'),  /* Spell(18420): Brightcloth Cloak*/
(@ENTRY, '18421', '12500', '197', '275', '0'),  /* Spell(18421): Wizardweave Leggings*/
(@ENTRY, '18423', '15000', '197', '280', '0'),  /* Spell(18423): Runecloth Boots*/
(@ENTRY, '18424', '15000', '197', '280', '0'),  /* Spell(18424): Frostweave Pants*/
(@ENTRY, '18437', '15000', '197', '285', '0'),  /* Spell(18437): Felcloth Boots*/
(@ENTRY, '18438', '15000', '197', '285', '0'),  /* Spell(18438): Runecloth Pants*/
(@ENTRY, '18441', '15000', '197', '290', '0'),  /* Spell(18441): Ghostweave Pants*/
(@ENTRY, '18442', '15000', '197', '290', '0'),  /* Spell(18442): Felcloth Hood*/
(@ENTRY, '18444', '15000', '197', '295', '0'),  /* Spell(18444): Runecloth Headband*/
(@ENTRY, '18446', '15000', '197', '300', '0'),  /* Spell(18446): Wizardweave Robe*/
(@ENTRY, '18449', '15000', '197', '300', '0'),  /* Spell(18449): Runecloth Shoulders*/
(@ENTRY, '18450', '15000', '197', '300', '0'),  /* Spell(18450): Wizardweave Turban*/
(@ENTRY, '18451', '15000', '197', '300', '0'),  /* Spell(18451): Felcloth Robe*/
(@ENTRY, '18453', '15000', '197', '300', '0'),  /* Spell(18453): Felcloth Shoulders*/
(@ENTRY, '26745', '15000', '197', '300', '0'),  /* Spell(26745): Bolt of Netherweave*/
(@ENTRY, '26746', '15000', '197', '315', '0'),  /* Spell(26746): Netherweave Bag*/
(@ENTRY, '26764', '15000', '197', '310', '0'),  /* Spell(26764): Netherweave Bracers*/
(@ENTRY, '26765', '15000', '197', '310', '0'),  /* Spell(26765): Netherweave Belt*/
(@ENTRY, '26770', '20000', '197', '320', '0'),  /* Spell(26770): Netherweave Gloves*/
(@ENTRY, '26771', '20000', '197', '325', '0'),  /* Spell(26771): Netherweave Pants*/
(@ENTRY, '26772', '20000', '197', '335', '0'),  /* Spell(26772): Netherweave Boots*/
(@ENTRY, '26790', '100000', '197', '275', '50'),  /* Spell(26790): Tailoring*/
(@ENTRY, '31460', '15000', '197', '300', '0'),  /* Spell(31460): Netherweave Net*/
(@ENTRY, '51309', '350000', '197', '350', '65'),  /* Spell(51309): Tailoring*/
(@ENTRY, '55642', '125000', '197', '420', '0'),  /* Spell(55642): Lightweave Embroidery*/
(@ENTRY, '55769', '125000', '197', '420', '0'),  /* Spell(55769): Darkglow Embroidery*/
(@ENTRY, '55777', '125000', '197', '420', '0'),  /* Spell(55777): Swordguard Embroidery*/
(@ENTRY, '55898', '50000', '197', '360', '0'),  /* Spell(55898): Frostweave Net*/
(@ENTRY, '55899', '50000', '197', '350', '0'),  /* Spell(55899): Bolt of Frostweave*/
(@ENTRY, '55900', '125000', '197', '400', '0'),  /* Spell(55900): Bolt of Imbued Frostweave*/
(@ENTRY, '55901', '50000', '197', '395', '0'),  /* Spell(55901): Duskweave Leggings*/
(@ENTRY, '55902', '50000', '197', '350', '0'),  /* Spell(55902): Frostwoven Shoulders*/
(@ENTRY, '55903', '50000', '197', '360', '0'),  /* Spell(55903): Frostwoven Robe*/
(@ENTRY, '55904', '50000', '197', '360', '0'),  /* Spell(55904): Frostwoven Gloves*/
(@ENTRY, '55906', '50000', '197', '375', '0'),  /* Spell(55906): Frostwoven Boots*/
(@ENTRY, '55907', '50000', '197', '380', '0'),  /* Spell(55907): Frostwoven Cowl*/
(@ENTRY, '55908', '50000', '197', '370', '0'),  /* Spell(55908): Frostwoven Belt*/
(@ENTRY, '55910', '80000', '197', '385', '0'),  /* Spell(55910): Mystic Frostwoven Shoulders*/
(@ENTRY, '55911', '80000', '197', '390', '0'),  /* Spell(55911): Mystic Frostwoven Robe*/
(@ENTRY, '55913', '80000', '197', '385', '0'),  /* Spell(55913): Mystic Frostwoven Wristwraps*/
(@ENTRY, '55914', '50000', '197', '395', '0'),  /* Spell(55914): Duskweave Belt*/
(@ENTRY, '55919', '100000', '197', '395', '0'),  /* Spell(55919): Duskweave Cowl*/
(@ENTRY, '55920', '50000', '197', '400', '0'),  /* Spell(55920): Duskweave Wristwraps*/
(@ENTRY, '55921', '100000', '197', '405', '0'),  /* Spell(55921): Duskweave Robe*/
(@ENTRY, '55922', '100000', '197', '405', '0'),  /* Spell(55922): Duskweave Gloves*/
(@ENTRY, '55923', '100000', '197', '410', '0'),  /* Spell(55923): Duskweave Shoulders*/
(@ENTRY, '55924', '125000', '197', '410', '0'),  /* Spell(55924): Duskweave Boots*/
(@ENTRY, '55925', '125000', '197', '415', '0'),  /* Spell(55925): Black Duskweave Leggings*/
(@ENTRY, '55941', '125000', '197', '420', '0'),  /* Spell(55941): Black Duskweave Robe*/
(@ENTRY, '55943', '125000', '197', '415', '0'),  /* Spell(55943): Black Duskweave Wristwraps*/
(@ENTRY, '55995', '50000', '197', '400', '0'),  /* Spell(55995): Yellow Lumberjack Shirt*/
(@ENTRY, '56000', '50000', '197', '400', '0'),  /* Spell(56000): Green Workman's Shirt*/
(@ENTRY, '56001', '100000', '197', '415', '0'),  /* Spell(56001): Moonshroud*/
(@ENTRY, '56002', '100000', '197', '415', '0'),  /* Spell(56002): Ebonweave*/
(@ENTRY, '56003', '100000', '197', '415', '0'),  /* Spell(56003): Spellweave*/
(@ENTRY, '56007', '80000', '197', '410', '0'),  /* Spell(56007): Frostweave Bag*/
(@ENTRY, '56008', '100000', '197', '400', '0'),  /* Spell(56008): Shining Spellthread*/
(@ENTRY, '56010', '100000', '197', '400', '0'),  /* Spell(56010): Azure Spellthread*/
(@ENTRY, '56014', '100000', '197', '390', '0'),  /* Spell(56014): Cloak of the Moon*/
(@ENTRY, '56015', '100000', '197', '395', '0'),  /* Spell(56015): Cloak of Frozen Spirits*/
(@ENTRY, '56018', '100000', '197', '425', '0'),  /* Spell(56018): Hat of Wintry Doom*/
(@ENTRY, '56019', '100000', '197', '420', '0'),  /* Spell(56019): Silky Iceshard Boots*/
(@ENTRY, '56020', '100000', '197', '420', '0'),  /* Spell(56020): Deep Frozen Cord*/
(@ENTRY, '56021', '100000', '197', '425', '0'),  /* Spell(56021): Frostmoon Pants*/
(@ENTRY, '56022', '100000', '197', '420', '0'),  /* Spell(56022): Light Blessed Mittens*/
(@ENTRY, '56023', '100000', '197', '420', '0'),  /* Spell(56023): Aurora Slippers*/
(@ENTRY, '56024', '200000', '197', '440', '0'),  /* Spell(56024): Moonshroud Robe*/
(@ENTRY, '56025', '200000', '197', '435', '0'),  /* Spell(56025): Moonshroud Gloves*/
(@ENTRY, '56026', '200000', '197', '440', '0'),  /* Spell(56026): Ebonweave Robe*/
(@ENTRY, '56027', '200000', '197', '435', '0'),  /* Spell(56027): Ebonweave Gloves*/
(@ENTRY, '56028', '200000', '197', '440', '0'),  /* Spell(56028): Spellweave Robe*/
(@ENTRY, '56029', '200000', '197', '435', '0'),  /* Spell(56029): Spellweave Gloves*/
(@ENTRY, '56030', '50000', '197', '380', '0'),  /* Spell(56030): Frostwoven Leggings*/
(@ENTRY, '56031', '50000', '197', '350', '0'),  /* Spell(56031): Frostwoven Wristwraps*/
(@ENTRY, '56034', '100000', '197', '405', '0'),  /* Spell(56034): Master's Spellthread*/
(@ENTRY, '56039', '100000', '197', '405', '0'),  /* Spell(56039): Sanctified Spellthread*/
(@ENTRY, '59582', '100000', '197', '415', '0'),  /* Spell(59582): Frostsavage Belt*/
(@ENTRY, '59583', '100000', '197', '415', '0'),  /* Spell(59583): Frostsavage Bracers*/
(@ENTRY, '59584', '100000', '197', '420', '0'),  /* Spell(59584): Frostsavage Shoulders*/
(@ENTRY, '59585', '100000', '197', '420', '0'),  /* Spell(59585): Frostsavage Boots*/
(@ENTRY, '59586', '100000', '197', '420', '0'),  /* Spell(59586): Frostsavage Gloves*/
(@ENTRY, '59587', '100000', '197', '420', '0'),  /* Spell(59587): Frostsavage Robe*/
(@ENTRY, '59588', '120000', '197', '420', '0'),  /* Spell(59588): Frostsavage Leggings*/
(@ENTRY, '59589', '120000', '197', '420', '0'),  /* Spell(59589): Frostsavage Cowl*/
(@ENTRY, '60969', '15000', '197', '300', '0'),  /* Spell(60969): Flying Carpet*/
(@ENTRY, '60971', '150000', '197', '425', '0'),  /* Spell(60971): Magnificent Flying Carpet*/
(@ENTRY, '60990', '180000', '197', '420', '0'),  /* Spell(60990): Glacial Waistband*/
(@ENTRY, '60993', '180000', '197', '425', '0'),  /* Spell(60993): Glacial Robe*/
(@ENTRY, '60994', '180000', '197', '420', '0'),  /* Spell(60994): Glacial Slippers*/
(@ENTRY, '63742', '750', '197', '125', '0'),  /* Spell(63742): Spidersilk Drape*/
(@ENTRY, '64729', '100000', '197', '400', '0'),  /* Spell(64729): Frostguard Drape*/
(@ENTRY, '64730', '100000', '197', '405', '0'),  /* Spell(64730): Cloak of Crimson Snow*/
(@ENTRY, '74964', '100000', '197', '425', '0'),  /* Spell(74964): Bolt of Embersilk Cloth*/
(@ENTRY, '75141', '150000', '197', '515', '0'),  /* Spell(75141): Dream of Skywall*/
(@ENTRY, '75142', '150000', '197', '505', '0'),  /* Spell(75142): Dream of Deepholm*/
(@ENTRY, '75144', '150000', '197', '500', '0'),  /* Spell(75144): Dream of Hyjal*/
(@ENTRY, '75145', '150000', '197', '510', '0'),  /* Spell(75145): Dream of Ragnaros*/
(@ENTRY, '75146', '150000', '197', '500', '0'),  /* Spell(75146): Dream of Azshara*/
(@ENTRY, '75156', '500000', '197', '425', '75'),  /* Spell(75156): Tailoring*/
(@ENTRY, '75247', '100000', '197', '425', '0'),  /* Spell(75247): Embersilk Net*/
(@ENTRY, '75248', '120000', '197', '445', '0'),  /* Spell(75248): Deathsilk Belt*/
(@ENTRY, '75249', '120000', '197', '445', '0'),  /* Spell(75249): Deathsilk Bracers*/
(@ENTRY, '75250', '120000', '197', '450', '0'),  /* Spell(75250): Enchanted Spellthread*/
(@ENTRY, '75251', '120000', '197', '455', '0'),  /* Spell(75251): Deathsilk Shoulders*/
(@ENTRY, '75252', '120000', '197', '455', '0'),  /* Spell(75252): Deathsilk Boots*/
(@ENTRY, '75253', '120000', '197', '460', '0'),  /* Spell(75253): Deathsilk Gloves*/
(@ENTRY, '75254', '120000', '197', '460', '0'),  /* Spell(75254): Deathsilk Leggings*/
(@ENTRY, '75255', '120000', '197', '460', '0'),  /* Spell(75255): Ghostly Spellthread*/
(@ENTRY, '75256', '120000', '197', '465', '0'),  /* Spell(75256): Deathsilk Cowl*/
(@ENTRY, '75257', '120000', '197', '465', '0'),  /* Spell(75257): Deathsilk Robe*/
(@ENTRY, '75258', '120000', '197', '470', '0'),  /* Spell(75258): Spiritmend Belt*/
(@ENTRY, '75259', '120000', '197', '470', '0'),  /* Spell(75259): Spiritmend Bracers*/
(@ENTRY, '75260', '120000', '197', '475', '0'),  /* Spell(75260): Spiritmend Shoulders*/
(@ENTRY, '75261', '120000', '197', '475', '0'),  /* Spell(75261): Spiritmend Boots*/
(@ENTRY, '75262', '150000', '197', '480', '0'),  /* Spell(75262): Spiritmend Gloves*/
(@ENTRY, '75263', '150000', '197', '480', '0'),  /* Spell(75263): Spiritmend Leggings*/
(@ENTRY, '75264', '150000', '197', '480', '0'),  /* Spell(75264): Embersilk Bag*/
(@ENTRY, '75265', '150000', '197', '480', '0'),  /* Spell(75265): Otherworldly Bag*/
(@ENTRY, '75266', '150000', '197', '485', '0'),  /* Spell(75266): Spiritmend Cowl*/
(@ENTRY, '75267', '150000', '197', '485', '0'),  /* Spell(75267): Spiritmend Robe*/
(@ENTRY, '75268', '150000', '197', '490', '0'),  /* Spell(75268): Hyjal Expedition Bag*/
(@ENTRY, '75269', '180000', '197', '510', '0'),  /* Spell(75269): Vicious Fireweave Belt*/
(@ENTRY, '75270', '150000', '197', '500', '0'),  /* Spell(75270): Vicious Embersilk Bracers*/
(@ENTRY, '75290', '150000', '197', '500', '0'),  /* Spell(75290): Vicious Fireweave Bracers*/
(@ENTRY, '75291', '180000', '197', '505', '0'),  /* Spell(75291): Vicious Embersilk Shoulders*/
(@ENTRY, '75292', '180000', '197', '510', '0'),  /* Spell(75292): Vicious Fireweave Shoulders*/
(@ENTRY, '75293', '180000', '197', '510', '0'),  /* Spell(75293): Vicious Embersilk Belt*/
(@ENTRY, '75294', '180000', '197', '515', '0'),  /* Spell(75294): Vicious Fireweave Boots*/
(@ENTRY, '75295', '180000', '197', '515', '0'),  /* Spell(75295): Vicious Embersilk Gloves*/
(@ENTRY, '75296', '180000', '197', '520', '0'),  /* Spell(75296): Vicious Fireweave Gloves*/
(@ENTRY, '75297', '180000', '197', '520', '0'),  /* Spell(75297): Vicious Embersilk Boots*/
(@ENTRY, '94743', '240000', '197', '525', '0'),  /* Spell(94743): Dream of Destruction*/
(@ENTRY, '99537', '150000', '197', '490', '0'),  /* Spell(99537): Vicious Embersilk Cape*/
(@ENTRY, '110426', '600000', '197', '500', '80'),  /* Spell(110426): Tailoring*/
(@ENTRY, '125523', '24000', '197', '555', '0'),  /* Spell(125523): Windwool Hood*/
(@ENTRY, '125524', '24000', '197', '535', '0'),  /* Spell(125524): Windwool Shoulders*/
(@ENTRY, '125525', '24000', '197', '555', '0'),  /* Spell(125525): Windwool Tunic*/
(@ENTRY, '125526', '24000', '197', '525', '0'),  /* Spell(125526): Windwool Gloves*/
(@ENTRY, '125527', '24000', '197', '545', '0'),  /* Spell(125527): Windwool Pants*/
(@ENTRY, '125528', '24000', '197', '525', '0'),  /* Spell(125528): Windwool Bracers*/
(@ENTRY, '125529', '24000', '197', '545', '0'),  /* Spell(125529): Windwool Boots*/
(@ENTRY, '125530', '24000', '197', '535', '0'),  /* Spell(125530): Windwool Belt*/
(@ENTRY, '125551', '24000', '197', '500', '0'),  /* Spell(125551): Bolt of Windwool Cloth*/
(@ENTRY, '125552', '24000', '197', '530', '0'),  /* Spell(125552): Pearlescent Spellthread*/
(@ENTRY, '125553', '24000', '197', '540', '0'),  /* Spell(125553): Cerulean Spellthread*/
(@ENTRY, '125557', '24000', '197', '550', '0'),  /* Spell(125557): Imperial Silk*/
(@ENTRY, '130325', '24000', '197', '560', '0'),  /* Spell(130325): Song of Harmony*/
(@ENTRY, '134585', '180000', '197', '515', '0');  /* Spell(134585): Bipsi's Gloves*/


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
('57405', '30072');  /* Quest(30072): Where Silk Comes From ,QuestMinLevel: 86 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 


/* Step 2.2 Table  `creature_involvedrelation */
DELETE FROM  `creature_involvedrelation` WHERE `id`= @ENTRY;
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES 
('57405', '30072'),  /* Quest(30072): Where Silk Comes From ,QuestMinLevel: 86 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('57405', '32035');  /* Quest(32035): Got Silk? ,QuestMinLevel: 86 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 


/* Step 1.8 Table  `waypoints */
DELETE FROM waypoints WHERE  `entry` = @ENTRY;
/* Step 2.5 Table  `npc_spellclick_spells */
DELETE FROM npc_spellclick_spells WHERE  `npc_entry` = @ENTRY;
/* Step 2.6 Table  `pet_levelstats */
DELETE FROM pet_levelstats WHERE  `creature_entry` = @ENTRY;

