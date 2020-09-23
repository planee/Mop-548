/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 28/1/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Simon Tanner';
SET @ENTRY 		:= '5564';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '3449', '0', '0', '0', @CREATURE, 'Leatherworking Trainer', '', '4203', '35', '35', '0', '0', '35', '35', '17', '0', '1', '1.14286', '0', '1.14286', '1', '0', '49', '64', '0', '118', '1', '2000', '2000', '1', '512', '2048', '0', '0', '2', '0', '0', '0', '33', '49', '11', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1.1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '2', '', '16048');

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES 
(@ENTRY, '0', '0', '0', '257', '0', '60913'); 


/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('3449', '0.306', '1.5', '0', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 5564 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '0', '1519', '5149', '1', '1', '0', '0', '-8725.55', '477.415', '98.6964', '5.24827', '120', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-8725.55' AND `position_y` REGEXP '477.415' AND `position_z` REGEXP '98.6964' AND `phaseMask` = '1' AND `map` = '0');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-8725.55' AND `position_y` REGEXP '477.415' AND `position_z` REGEXP '98.6964' AND `phaseMask` = '1' AND `map` = '0');
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
DELETE FROM gossip_menu WHERE  `entry` = 4203;
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES 
(4203, 5320); 
/* Step 4.6 Table  `npc_text` */
DELETE FROM npc_text WHERE `ID` = 5320;
INSERT INTO `npc_text` (`ID`,`text0_0`,`text0_1`,`lang0`,`prob0`,`em0_0`,`em0_1`,`em0_2`,`em0_3`,`em0_4`,`em0_5`,`text1_0`,`text1_1`,`lang1`,`prob1`,`em1_0`,`em1_1`,`em1_2`,`em1_3`,`em1_4`,`em1_5`,`text2_0`,`text2_1`,`lang2`,`prob2`,`em2_0`,`em2_1`,`em2_2`,`em2_3`,`em2_4`,`em2_5`,`text3_0`,`text3_1`,`lang3`,`prob3`,`em3_0`,`em3_1`,`em3_2`,`em3_3`,`em3_4`,`em3_5`,`text4_0`,`text4_1`,`lang4`,`prob4`,`em4_0`,`em4_1`,`em4_2`,`em4_3`,`em4_4`,`em4_5`,`text5_0`,`text5_1`,`lang5`,`prob5`,`em5_0`,`em5_1`,`em5_2`,`em5_3`,`em5_4`,`em5_5`,`text6_0`,`text6_1`,`lang6`,`prob6`,`em6_0`,`em6_1`,`em6_2`,`em6_3`,`em6_4`,`em6_5`,`text7_0`,`text7_1`,`lang7`,`prob7`,`em7_0`,`em7_1`,`em7_2`,`em7_3`,`em7_4`,`em7_5`,`WDBVerified`) VALUES 
('5320', 'Randal\'s a bit of a dandy, but he\'s dependable, which is more than I can say for a lot of the students I take on. Still, I guess I can\'t blame them for wanting a bit of adventure.', '', '0', '1', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '12340'); 




/* Step 2.7 Table  `gossip_menu_option */
DELETE FROM gossip_menu_option WHERE  `menu_id` = 4203;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
('4203', '0', '3', 'Train me.', '5', '16', '0', '0', '0', '0', '');


/*## Step 5: Creature NPC Trainer / Vendor ############################*/

/* Step 2.0 Table  `npc_trainer */
DELETE FROM npc_trainer WHERE `entry` = @ENTRY;
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES 
(@ENTRY, '2108', '10', '165', '0', '5'),  /* Spell(2108): Leatherworking*/
(@ENTRY, '2153', '50', '165', '15', '0'),  /* Spell(2153): Handstitched Leather Pants*/
(@ENTRY, '2159', '250', '165', '85', '0'),  /* Spell(2159): Fine Leather Cloak*/
(@ENTRY, '2160', '100', '165', '40', '0'),  /* Spell(2160): Embossed Leather Vest*/
(@ENTRY, '2161', '100', '165', '55', '0'),  /* Spell(2161): Embossed Leather Boots*/
(@ENTRY, '2162', '100', '165', '60', '0'),  /* Spell(2162): Embossed Leather Cloak*/
(@ENTRY, '2165', '250', '165', '100', '0'),  /* Spell(2165): Medium Armor Kit*/
(@ENTRY, '2166', '450', '165', '120', '0'),  /* Spell(2166): Toughened Leather Armor*/
(@ENTRY, '2167', '350', '165', '100', '0'),  /* Spell(2167): Dark Leather Boots*/
(@ENTRY, '2168', '350', '165', '110', '0'),  /* Spell(2168): Dark Leather Cloak*/
(@ENTRY, '3104', '500', '165', '50', '10'),  /* Spell(3104): Leatherworking*/
(@ENTRY, '3753', '75', '165', '25', '0'),  /* Spell(3753): Handstitched Leather Belt*/
(@ENTRY, '3756', '150', '165', '55', '0'),  /* Spell(3756): Embossed Leather Gloves*/
(@ENTRY, '3759', '200', '165', '75', '0'),  /* Spell(3759): Embossed Leather Pants*/
(@ENTRY, '3760', '600', '165', '150', '0'),  /* Spell(3760): Hillman's Cloak*/
(@ENTRY, '3761', '350', '165', '85', '0'),  /* Spell(3761): Fine Leather Tunic*/
(@ENTRY, '3763', '300', '165', '80', '0'),  /* Spell(3763): Fine Leather Belt*/
(@ENTRY, '3764', '500', '165', '145', '0'),  /* Spell(3764): Hillman's Leather Gloves*/
(@ENTRY, '3766', '400', '165', '125', '0'),  /* Spell(3766): Dark Leather Belt*/
(@ENTRY, '3768', '500', '165', '130', '0'),  /* Spell(3768): Hillman's Shoulders*/
(@ENTRY, '3770', '500', '165', '135', '0'),  /* Spell(3770): Toughened Leather Gloves*/
(@ENTRY, '3774', '1000', '165', '160', '0'),  /* Spell(3774): Green Leather Belt*/
(@ENTRY, '3776', '1200', '165', '180', '0'),  /* Spell(3776): Green Leather Bracers*/
(@ENTRY, '3780', '750', '165', '150', '0'),  /* Spell(3780): Heavy Armor Kit*/
(@ENTRY, '3811', '5000', '165', '125', '25'),  /* Spell(3811): Leatherworking*/
(@ENTRY, '3816', '50', '165', '35', '0'),  /* Spell(3816): Cured Light Hide*/
(@ENTRY, '3817', '200', '165', '100', '0'),  /* Spell(3817): Cured Medium Hide*/
(@ENTRY, '3818', '500', '165', '150', '0'),  /* Spell(3818): Cured Heavy Hide*/
(@ENTRY, '6661', '2000', '165', '190', '0'),  /* Spell(6661): Barbaric Harness*/
(@ENTRY, '7135', '400', '165', '115', '0'),  /* Spell(7135): Dark Leather Pants*/
(@ENTRY, '7147', '1000', '165', '160', '0'),  /* Spell(7147): Guardian Pants*/
(@ENTRY, '7151', '1200', '165', '175', '0'),  /* Spell(7151): Barbaric Shoulders*/
(@ENTRY, '7156', '2400', '165', '190', '0'),  /* Spell(7156): Guardian Gloves*/
(@ENTRY, '9065', '150', '165', '70', '0'),  /* Spell(9065): Light Leather Bracers*/
(@ENTRY, '9068', '400', '165', '95', '0'),  /* Spell(9068): Light Leather Pants*/
(@ENTRY, '9074', '500', '165', '120', '0'),  /* Spell(9074): Nimble Leather Gloves*/
(@ENTRY, '9145', '500', '165', '125', '0'),  /* Spell(9145): Fletcher's Gloves*/
(@ENTRY, '9196', '1500', '165', '175', '0'),  /* Spell(9196): Dusky Leather Armor*/
(@ENTRY, '9198', '2000', '165', '180', '0'),  /* Spell(9198): Frost Leather Cloak*/
(@ENTRY, '9201', '2000', '165', '185', '0'),  /* Spell(9201): Dusky Bracers*/
(@ENTRY, '9206', '2500', '165', '195', '0'),  /* Spell(9206): Dusky Belt*/
(@ENTRY, '10482', '2000', '165', '200', '0'),  /* Spell(10482): Cured Thick Hide*/
(@ENTRY, '10487', '2000', '165', '200', '0'),  /* Spell(10487): Thick Armor Kit*/
(@ENTRY, '10499', '3000', '165', '205', '0'),  /* Spell(10499): Nightscape Tunic*/
(@ENTRY, '10507', '3000', '165', '205', '0'),  /* Spell(10507): Nightscape Headband*/
(@ENTRY, '10511', '3000', '165', '210', '0'),  /* Spell(10511): Turtle Scale Breastplate*/
(@ENTRY, '10518', '3500', '165', '210', '0'),  /* Spell(10518): Turtle Scale Bracers*/
(@ENTRY, '10548', '4000', '165', '230', '0'),  /* Spell(10548): Nightscape Pants*/
(@ENTRY, '10552', '4000', '165', '230', '0'),  /* Spell(10552): Turtle Scale Helm*/
(@ENTRY, '10556', '4500', '165', '235', '0'),  /* Spell(10556): Turtle Scale Leggings*/
(@ENTRY, '10558', '4500', '165', '235', '0'),  /* Spell(10558): Nightscape Boots*/
(@ENTRY, '10630', '10000', '165', '230', '0'),  /* Spell(10630): Gauntlets of the Sea*/
(@ENTRY, '10632', '10000', '165', '250', '0'),  /* Spell(10632): Helm of Fire*/
(@ENTRY, '10647', '10000', '165', '250', '0'),  /* Spell(10647): Feathered Breastplate*/
(@ENTRY, '10650', '10000', '165', '255', '0'),  /* Spell(10650): Dragonscale Breastplate*/
(@ENTRY, '10662', '50000', '165', '200', '35'),  /* Spell(10662): Leatherworking*/
(@ENTRY, '19047', '5000', '165', '250', '0'),  /* Spell(19047): Cured Rugged Hide*/
(@ENTRY, '19052', '10000', '165', '265', '0'),  /* Spell(19052): Wicked Leather Bracers*/
(@ENTRY, '19055', '10000', '165', '270', '0'),  /* Spell(19055): Runic Leather Gauntlets*/
(@ENTRY, '19058', '5000', '165', '250', '0'),  /* Spell(19058): Rugged Armor Kit*/
(@ENTRY, '19065', '10000', '165', '275', '0'),  /* Spell(19065): Runic Leather Bracers*/
(@ENTRY, '19071', '10000', '165', '280', '0'),  /* Spell(19071): Wicked Leather Headband*/
(@ENTRY, '19072', '10000', '165', '280', '0'),  /* Spell(19072): Runic Leather Belt*/
(@ENTRY, '19082', '15000', '165', '290', '0'),  /* Spell(19082): Runic Leather Headband*/
(@ENTRY, '19083', '15000', '165', '290', '0'),  /* Spell(19083): Wicked Leather Pants*/
(@ENTRY, '19091', '15000', '165', '300', '0'),  /* Spell(19091): Runic Leather Pants*/
(@ENTRY, '19092', '15000', '165', '300', '0'),  /* Spell(19092): Wicked Leather Belt*/
(@ENTRY, '19098', '15000', '165', '300', '0'),  /* Spell(19098): Wicked Leather Armor*/
(@ENTRY, '19102', '15000', '165', '300', '0'),  /* Spell(19102): Runic Leather Armor*/
(@ENTRY, '19103', '15000', '165', '300', '0'),  /* Spell(19103): Runic Leather Shoulders*/
(@ENTRY, '20648', '500', '165', '100', '0'),  /* Spell(20648): Medium Leather*/
(@ENTRY, '20649', '1000', '165', '150', '0'),  /* Spell(20649): Heavy Leather*/
(@ENTRY, '20650', '4000', '165', '200', '0'),  /* Spell(20650): Thick Leather*/
(@ENTRY, '22331', '5000', '165', '250', '0'),  /* Spell(22331): Rugged Leather*/
(@ENTRY, '24654', '50000', '165', '300', '0'),  /* Spell(24654): Blue Dragonscale Leggings*/
(@ENTRY, '24655', '30000', '165', '280', '0'),  /* Spell(24655): Green Dragonscale Gauntlets*/
(@ENTRY, '32454', '10000', '165', '300', '0'),  /* Spell(32454): Knothide Leather*/
(@ENTRY, '32455', '20000', '165', '325', '0'),  /* Spell(32455): Heavy Knothide Leather*/
(@ENTRY, '32456', '15000', '165', '300', '0'),  /* Spell(32456): Knothide Armor Kit*/
(@ENTRY, '32462', '15000', '165', '300', '0'),  /* Spell(32462): Felscale Gloves*/
(@ENTRY, '32463', '18000', '165', '310', '0'),  /* Spell(32463): Felscale Boots*/
(@ENTRY, '32464', '20000', '165', '320', '0'),  /* Spell(32464): Felscale Pants*/
(@ENTRY, '32465', '25000', '165', '335', '0'),  /* Spell(32465): Felscale Breastplate*/
(@ENTRY, '32466', '15000', '165', '300', '0'),  /* Spell(32466): Scaled Draenic Pants*/
(@ENTRY, '32467', '18000', '165', '310', '0'),  /* Spell(32467): Scaled Draenic Gloves*/
(@ENTRY, '32468', '20000', '165', '325', '0'),  /* Spell(32468): Scaled Draenic Vest*/
(@ENTRY, '32469', '25000', '165', '335', '0'),  /* Spell(32469): Scaled Draenic Boots*/
(@ENTRY, '32470', '15000', '165', '300', '0'),  /* Spell(32470): Thick Draenic Gloves*/
(@ENTRY, '32471', '18000', '165', '315', '0'),  /* Spell(32471): Thick Draenic Pants*/
(@ENTRY, '32472', '20000', '165', '320', '0'),  /* Spell(32472): Thick Draenic Boots*/
(@ENTRY, '32473', '25000', '165', '330', '0'),  /* Spell(32473): Thick Draenic Vest*/
(@ENTRY, '32478', '15000', '165', '300', '0'),  /* Spell(32478): Wild Draenish Boots*/
(@ENTRY, '32479', '18000', '165', '310', '0'),  /* Spell(32479): Wild Draenish Gloves*/
(@ENTRY, '32480', '20000', '165', '320', '0'),  /* Spell(32480): Wild Draenish Leggings*/
(@ENTRY, '32481', '25000', '165', '330', '0'),  /* Spell(32481): Wild Draenish Vest*/
(@ENTRY, '32549', '100000', '165', '275', '50'),  /* Spell(32549): Leatherworking*/
(@ENTRY, '35540', '20000', '165', '340', '0'),  /* Spell(35540): Drums of War*/
(@ENTRY, '36074', '10000', '165', '260', '0'),  /* Spell(36074): Blackstorm Leggings*/
(@ENTRY, '36075', '10000', '165', '260', '0'),  /* Spell(36075): Wildfeather Leggings*/
(@ENTRY, '36076', '10000', '165', '260', '0'),  /* Spell(36076): Dragonstrike Leggings*/
(@ENTRY, '36077', '40000', '165', '330', '0'),  /* Spell(36077): Primalstorm Breastplate*/
(@ENTRY, '36078', '40000', '165', '330', '0'),  /* Spell(36078): Living Crystal Breastplate*/
(@ENTRY, '36079', '40000', '165', '330', '0'),  /* Spell(36079): Golden Dragonstrike Breastplate*/
(@ENTRY, '44770', '50000', '165', '350', '0'),  /* Spell(44770): Glove Reinforcements*/
(@ENTRY, '44970', '50000', '165', '350', '0'),  /* Spell(44970): Heavy Knothide Armor Kit*/
(@ENTRY, '45100', '15000', '165', '300', '0'),  /* Spell(45100): Leatherworker's Satchel*/
(@ENTRY, '50936', '80000', '165', '390', '0'),  /* Spell(50936): Heavy Borean Leather*/
(@ENTRY, '50938', '30000', '165', '375', '0'),  /* Spell(50938): Iceborne Chestguard*/
(@ENTRY, '50939', '30000', '165', '370', '0'),  /* Spell(50939): Iceborne Leggings*/
(@ENTRY, '50940', '30000', '165', '380', '0'),  /* Spell(50940): Iceborne Shoulderpads*/
(@ENTRY, '50941', '30000', '165', '370', '0'),  /* Spell(50941): Iceborne Gloves*/
(@ENTRY, '50942', '30000', '165', '375', '0'),  /* Spell(50942): Iceborne Boots*/
(@ENTRY, '50943', '30000', '165', '380', '0'),  /* Spell(50943): Iceborne Belt*/
(@ENTRY, '50944', '30000', '165', '370', '0'),  /* Spell(50944): Arctic Chestpiece*/
(@ENTRY, '50945', '30000', '165', '375', '0'),  /* Spell(50945): Arctic Leggings*/
(@ENTRY, '50946', '30000', '165', '380', '0'),  /* Spell(50946): Arctic Shoulderpads*/
(@ENTRY, '50947', '30000', '165', '375', '0'),  /* Spell(50947): Arctic Gloves*/
(@ENTRY, '50948', '30000', '165', '370', '0'),  /* Spell(50948): Arctic Boots*/
(@ENTRY, '50949', '30000', '165', '380', '0'),  /* Spell(50949): Arctic Belt*/
(@ENTRY, '50950', '30000', '165', '375', '0'),  /* Spell(50950): Frostscale Chestguard*/
(@ENTRY, '50951', '30000', '165', '370', '0'),  /* Spell(50951): Frostscale Leggings*/
(@ENTRY, '50952', '30000', '165', '375', '0'),  /* Spell(50952): Frostscale Shoulders*/
(@ENTRY, '50953', '30000', '165', '380', '0'),  /* Spell(50953): Frostscale Gloves*/
(@ENTRY, '50954', '30000', '165', '380', '0'),  /* Spell(50954): Frostscale Boots*/
(@ENTRY, '50955', '30000', '165', '370', '0'),  /* Spell(50955): Frostscale Belt*/
(@ENTRY, '50956', '30000', '165', '375', '0'),  /* Spell(50956): Nerubian Chestguard*/
(@ENTRY, '50957', '30000', '165', '370', '0'),  /* Spell(50957): Nerubian Legguards*/
(@ENTRY, '50958', '30000', '165', '380', '0'),  /* Spell(50958): Nerubian Shoulders*/
(@ENTRY, '50959', '30000', '165', '370', '0'),  /* Spell(50959): Nerubian Gloves*/
(@ENTRY, '50960', '30000', '165', '380', '0'),  /* Spell(50960): Nerubian Boots*/
(@ENTRY, '50961', '30000', '165', '375', '0'),  /* Spell(50961): Nerubian Belt*/
(@ENTRY, '50962', '50000', '165', '350', '0'),  /* Spell(50962): Borean Armor Kit*/
(@ENTRY, '50963', '80000', '165', '395', '0'),  /* Spell(50963): Heavy Borean Armor Kit*/
(@ENTRY, '50964', '50000', '165', '405', '0'),  /* Spell(50964): Jormungar Leg Armor*/
(@ENTRY, '50965', '80000', '165', '425', '0'),  /* Spell(50965): Frosthide Leg Armor*/
(@ENTRY, '50966', '50000', '165', '400', '0'),  /* Spell(50966): Nerubian Leg Armor*/
(@ENTRY, '50967', '80000', '165', '425', '0'),  /* Spell(50967): Icescale Leg Armor*/
(@ENTRY, '51302', '350000', '165', '350', '65'),  /* Spell(51302): Leatherworking*/
(@ENTRY, '51568', '100000', '165', '400', '0'),  /* Spell(51568): Black Chitinguard Boots*/
(@ENTRY, '51569', '80000', '165', '395', '0'),  /* Spell(51569): Dark Arctic Leggings*/
(@ENTRY, '51570', '80000', '165', '395', '0'),  /* Spell(51570): Dark Arctic Chestpiece*/
(@ENTRY, '51571', '30000', '165', '385', '0'),  /* Spell(51571): Arctic Wristguards*/
(@ENTRY, '51572', '30000', '165', '385', '0'),  /* Spell(51572): Arctic Helm*/
(@ENTRY, '55199', '80000', '165', '395', '0'),  /* Spell(55199): Cloak of Tormented Skies*/
(@ENTRY, '57683', '70000', '165', '400', '0'),  /* Spell(57683): Fur Lining - Agility*/
(@ENTRY, '57690', '70000', '165', '400', '0'),  /* Spell(57690): Fur Lining - Stamina*/
(@ENTRY, '57691', '70000', '165', '400', '0'),  /* Spell(57691): Fur Lining - Intellect*/
(@ENTRY, '60599', '30000', '165', '385', '0'),  /* Spell(60599): Frostscale Bracers*/
(@ENTRY, '60600', '30000', '165', '385', '0'),  /* Spell(60600): Frostscale Helm*/
(@ENTRY, '60601', '80000', '165', '395', '0'),  /* Spell(60601): Dark Frostscale Leggings*/
(@ENTRY, '60604', '80000', '165', '395', '0'),  /* Spell(60604): Dark Frostscale Breastplate*/
(@ENTRY, '60605', '100000', '165', '400', '0'),  /* Spell(60605): Dragonstompers*/
(@ENTRY, '60607', '30000', '165', '385', '0'),  /* Spell(60607): Iceborne Wristguards*/
(@ENTRY, '60608', '30000', '165', '385', '0'),  /* Spell(60608): Iceborne Helm*/
(@ENTRY, '60611', '80000', '165', '395', '0'),  /* Spell(60611): Dark Iceborne Leggings*/
(@ENTRY, '60613', '80000', '165', '395', '0'),  /* Spell(60613): Dark Iceborne Chestguard*/
(@ENTRY, '60620', '100000', '165', '400', '0'),  /* Spell(60620): Bugsquashers*/
(@ENTRY, '60622', '30000', '165', '385', '0'),  /* Spell(60622): Nerubian Bracers*/
(@ENTRY, '60624', '30000', '165', '385', '0'),  /* Spell(60624): Nerubian Helm*/
(@ENTRY, '60627', '80000', '165', '395', '0'),  /* Spell(60627): Dark Nerubian Leggings*/
(@ENTRY, '60629', '80000', '165', '395', '0'),  /* Spell(60629): Dark Nerubian Chestpiece*/
(@ENTRY, '60630', '80000', '165', '400', '0'),  /* Spell(60630): Scaled Icewalkers*/
(@ENTRY, '60631', '80000', '165', '380', '0'),  /* Spell(60631): Cloak of Harsh Winds*/
(@ENTRY, '60637', '200000', '165', '440', '0'),  /* Spell(60637): Ice Striker's Cloak*/
(@ENTRY, '60640', '200000', '165', '440', '0'),  /* Spell(60640): Durable Nerubhide Cape*/
(@ENTRY, '60643', '50000', '165', '415', '0'),  /* Spell(60643): Pack of Endless Pockets*/
(@ENTRY, '60649', '100000', '165', '425', '0'),  /* Spell(60649): Razorstrike Breastplate*/
(@ENTRY, '60651', '100000', '165', '420', '0'),  /* Spell(60651): Virulent Spaulders*/
(@ENTRY, '60652', '100000', '165', '420', '0'),  /* Spell(60652): Eaglebane Bracers*/
(@ENTRY, '60655', '200000', '165', '425', '0'),  /* Spell(60655): Nightshock Hood*/
(@ENTRY, '60658', '200000', '165', '420', '0'),  /* Spell(60658): Nightshock Girdle*/
(@ENTRY, '60660', '100000', '165', '425', '0'),  /* Spell(60660): Leggings of Visceral Strikes*/
(@ENTRY, '60665', '100000', '165', '420', '0'),  /* Spell(60665): Seafoam Gauntlets*/
(@ENTRY, '60666', '80000', '165', '420', '0'),  /* Spell(60666): Jormscale Footpads*/
(@ENTRY, '60669', '100000', '165', '425', '0'),  /* Spell(60669): Wildscale Breastplate*/
(@ENTRY, '60671', '100000', '165', '420', '0'),  /* Spell(60671): Purehorn Spaulders*/
(@ENTRY, '62448', '80000', '165', '425', '0'),  /* Spell(62448): Earthen Leg Armor*/
(@ENTRY, '64661', '50000', '165', '350', '0'),  /* Spell(64661): Borean Leather*/
(@ENTRY, '69386', '200000', '165', '450', '0'),  /* Spell(69386): Drums of Forgotten Kings*/
(@ENTRY, '69388', '200000', '165', '450', '0'),  /* Spell(69388): Drums of the Wild*/
(@ENTRY, '78379', '75000', '165', '425', '0'),  /* Spell(78379): Savage Armor Kit*/
(@ENTRY, '78380', '75000', '165', '460', '0'),  /* Spell(78380): Savage Cloak*/
(@ENTRY, '78388', '75000', '165', '460', '0'),  /* Spell(78388): Tsunami Bracers*/
(@ENTRY, '78396', '75000', '165', '470', '0'),  /* Spell(78396): Tsunami Belt*/
(@ENTRY, '78398', '75000', '165', '450', '0'),  /* Spell(78398): Darkbrand Bracers*/
(@ENTRY, '78399', '75000', '165', '465', '0'),  /* Spell(78399): Darkbrand Gloves*/
(@ENTRY, '78405', '75000', '165', '470', '0'),  /* Spell(78405): Hardened Scale Cloak*/
(@ENTRY, '78406', '85000', '165', '475', '0'),  /* Spell(78406): Tsunami Gloves*/
(@ENTRY, '78407', '75000', '165', '465', '0'),  /* Spell(78407): Darkbrand Boots*/
(@ENTRY, '78410', '75000', '165', '450', '0'),  /* Spell(78410): Tsunami Boots*/
(@ENTRY, '78411', '85000', '165', '475', '0'),  /* Spell(78411): Darkbrand Shoulders*/
(@ENTRY, '78415', '75000', '165', '455', '0'),  /* Spell(78415): Tsunami Shoulders*/
(@ENTRY, '78416', '75000', '165', '455', '0'),  /* Spell(78416): Darkbrand Belt*/
(@ENTRY, '78419', '85000', '165', '475', '0'),  /* Spell(78419): Scorched Leg Armor*/
(@ENTRY, '78420', '85000', '165', '480', '0'),  /* Spell(78420): Twilight Leg Armor*/
(@ENTRY, '78423', '85000', '165', '490', '0'),  /* Spell(78423): Tsunami Chestguard*/
(@ENTRY, '78424', '85000', '165', '490', '0'),  /* Spell(78424): Darkbrand Helm*/
(@ENTRY, '78427', '85000', '165', '480', '0'),  /* Spell(78427): Tsunami Leggings*/
(@ENTRY, '78428', '85000', '165', '480', '0'),  /* Spell(78428): Darkbrand Chestguard*/
(@ENTRY, '78432', '85000', '165', '485', '0'),  /* Spell(78432): Tsunami Helm*/
(@ENTRY, '78433', '85000', '165', '485', '0'),  /* Spell(78433): Darkbrand Leggings*/
(@ENTRY, '78436', '85000', '165', '485', '0'),  /* Spell(78436): Heavy Savage Leather*/
(@ENTRY, '78437', '85000', '165', '485', '0'),  /* Spell(78437): Heavy Savage Armor Kit*/
(@ENTRY, '78438', '85000', '165', '495', '0'),  /* Spell(78438): Cloak of Beasts*/
(@ENTRY, '78439', '85000', '165', '495', '0'),  /* Spell(78439): Cloak of War*/
(@ENTRY, '81199', '500000', '165', '425', '75'),  /* Spell(81199): Leatherworking*/
(@ENTRY, '84950', '75000', '165', '425', '0'),  /* Spell(84950): Savage Leather*/
(@ENTRY, '99535', '100000', '165', '500', '0'),  /* Spell(99535): Vicious Hide Cloak*/
(@ENTRY, '99536', '100000', '165', '500', '0'),  /* Spell(99536): Vicious Fur Cloak*/
(@ENTRY, '110423', '685714', '165', '500', '80'),  /* Spell(110423): Leatherworking*/
(@ENTRY, '124124', '57142', '165', '545', '0'),  /* Spell(124124): Sha-Touched Leg Armor*/
(@ENTRY, '124125', '57142', '165', '555', '0'),  /* Spell(124125): Toughened Leg Armor*/
(@ENTRY, '124126', '57142', '165', '535', '0'),  /* Spell(124126): Brutal Leg Armor*/
(@ENTRY, '124549', '70000', '165', '400', '0'),  /* Spell(124549): Fur Lining - Strength*/
(@ENTRY, '124567', '70000', '165', '400', '0'),  /* Spell(124567): Primal Leg Reinforcements*/
(@ENTRY, '124568', '70000', '165', '400', '0'),  /* Spell(124568): Heavy Leg Reinforcements*/
(@ENTRY, '124569', '70000', '165', '400', '0'),  /* Spell(124569): Draconic Leg Reinforcements*/
(@ENTRY, '124571', '57142', '165', '555', '0'),  /* Spell(124571): Misthide Helm*/
(@ENTRY, '124572', '57142', '165', '540', '0'),  /* Spell(124572): Misthide Shoulders*/
(@ENTRY, '124573', '57142', '165', '560', '0'),  /* Spell(124573): Misthide Chestguard*/
(@ENTRY, '124574', '57142', '165', '545', '0'),  /* Spell(124574): Misthide Gloves*/
(@ENTRY, '124575', '57142', '165', '550', '0'),  /* Spell(124575): Misthide Leggings*/
(@ENTRY, '124576', '57142', '165', '530', '0'),  /* Spell(124576): Misthide Bracers*/
(@ENTRY, '124577', '57142', '165', '525', '0'),  /* Spell(124577): Misthide Boots*/
(@ENTRY, '124578', '57142', '165', '535', '0'),  /* Spell(124578): Misthide Belt*/
(@ENTRY, '124579', '57142', '165', '550', '0'),  /* Spell(124579): Stormscale Helm*/
(@ENTRY, '124580', '57142', '165', '545', '0'),  /* Spell(124580): Stormscale Shoulders*/
(@ENTRY, '124581', '57142', '165', '555', '0'),  /* Spell(124581): Stormscale Chestguard*/
(@ENTRY, '124582', '57142', '165', '540', '0'),  /* Spell(124582): Stormscale Gloves*/
(@ENTRY, '124583', '57142', '165', '560', '0'),  /* Spell(124583): Stormscale Leggings*/
(@ENTRY, '124584', '57142', '165', '525', '0'),  /* Spell(124584): Stormscale Bracers*/
(@ENTRY, '124585', '57142', '165', '535', '0'),  /* Spell(124585): Stormscale Boots*/
(@ENTRY, '124586', '57142', '165', '530', '0'),  /* Spell(124586): Stormscale Belt*/
(@ENTRY, '124627', '57142', '165', '500', '0'),  /* Spell(124627): Exotic Leather*/
(@ENTRY, '124628', '57142', '165', '525', '0'),  /* Spell(124628): Sha Armor Kit*/
(@ENTRY, '124635', '57142', '165', '555', '0'),  /* Spell(124635): Misthide Drape*/
(@ENTRY, '124636', '57142', '165', '550', '0'),  /* Spell(124636): Stormscale Drape*/
(@ENTRY, '124637', '57142', '165', '560', '0'),  /* Spell(124637): Quick Strike Cloak*/
(@ENTRY, '131865', '57142', '165', '550', '0');  /* Spell(131865): Magnificent Hide*/


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

