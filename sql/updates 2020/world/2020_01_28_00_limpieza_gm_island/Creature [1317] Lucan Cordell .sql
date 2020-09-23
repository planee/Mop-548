/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 28/1/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Lucan Cordell';
SET @ENTRY 		:= '1317';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1492', '0', '0', '0', @CREATURE, 'Enchanting Trainer', '', '4161', '35', '35', '0', '0', '35', '35', '83', '0', '1', '1.14286', '0', '1.14286', '1', '0', '49', '64', '0', '118', '1', '2000', '2000', '1', '512', '2048', '0', '0', '2', '0', '0', '0', '33', '49', '11', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1.1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '2', '', '16048');

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES 
(@ENTRY, '0', '0', '0', '257', '0', ''); 


/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('1492', '0.306', '1.5', '0', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 1317 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '0', '1519', '5154', '1', '1', '0', '0', '-8858.31', '803.734', '96.5175', '5.35816', '120', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-8858.31' AND `position_y` REGEXP '803.734' AND `position_z` REGEXP '96.5175' AND `phaseMask` = '1' AND `map` = '0');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-8858.31' AND `position_y` REGEXP '803.734' AND `position_z` REGEXP '96.5175' AND `phaseMask` = '1' AND `map` = '0');
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
DELETE FROM gossip_menu WHERE  `entry` = 4161;
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES 
(4161, 5207); 
/* Step 4.6 Table  `npc_text` */
DELETE FROM npc_text WHERE `ID` = 5207;
INSERT INTO `npc_text` (`ID`,`text0_0`,`text0_1`,`lang0`,`prob0`,`em0_0`,`em0_1`,`em0_2`,`em0_3`,`em0_4`,`em0_5`,`text1_0`,`text1_1`,`lang1`,`prob1`,`em1_0`,`em1_1`,`em1_2`,`em1_3`,`em1_4`,`em1_5`,`text2_0`,`text2_1`,`lang2`,`prob2`,`em2_0`,`em2_1`,`em2_2`,`em2_3`,`em2_4`,`em2_5`,`text3_0`,`text3_1`,`lang3`,`prob3`,`em3_0`,`em3_1`,`em3_2`,`em3_3`,`em3_4`,`em3_5`,`text4_0`,`text4_1`,`lang4`,`prob4`,`em4_0`,`em4_1`,`em4_2`,`em4_3`,`em4_4`,`em4_5`,`text5_0`,`text5_1`,`lang5`,`prob5`,`em5_0`,`em5_1`,`em5_2`,`em5_3`,`em5_4`,`em5_5`,`text6_0`,`text6_1`,`lang6`,`prob6`,`em6_0`,`em6_1`,`em6_2`,`em6_3`,`em6_4`,`em6_5`,`text7_0`,`text7_1`,`lang7`,`prob7`,`em7_0`,`em7_1`,`em7_2`,`em7_3`,`em7_4`,`em7_5`,`WDBVerified`) VALUES 
('5207', 'If you have what it takes, I will be happy to show you the way.', '', '0', '1', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '1'); 




/* Step 2.7 Table  `gossip_menu_option */
DELETE FROM gossip_menu_option WHERE  `menu_id` = 4161;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
('4161', '0', '3', 'Train me.', '5', '16', '0', '0', '0', '0', '');


/*## Step 5: Creature NPC Trainer / Vendor ############################*/

/* Step 2.0 Table  `npc_trainer */
DELETE FROM npc_trainer WHERE `entry` = @ENTRY;
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES 
(@ENTRY, '7411', '10', '333', '0', '5'),  /* Spell(7411): Enchanting*/
(@ENTRY, '7412', '500', '333', '50', '10'),  /* Spell(7412): Enchanting*/
(@ENTRY, '7413', '5000', '333', '125', '25'),  /* Spell(7413): Enchanting*/
(@ENTRY, '7420', '50', '333', '15', '0'),  /* Spell(7420): Enchant Chest - Minor Health*/
(@ENTRY, '7426', '100', '333', '40', '0'),  /* Spell(7426): Enchant Chest - Minor Absorption*/
(@ENTRY, '7457', '250', '333', '50', '0'),  /* Spell(7457): Enchant Bracer - Minor Stamina*/
(@ENTRY, '7745', '500', '333', '100', '0'),  /* Spell(7745): Enchant 2H Weapon - Minor Impact*/
(@ENTRY, '7748', '250', '333', '60', '0'),  /* Spell(7748): Enchant Chest - Lesser Health*/
(@ENTRY, '7771', '200', '333', '70', '0'),  /* Spell(7771): Enchant Cloak - Minor Protection*/
(@ENTRY, '7779', '400', '333', '80', '0'),  /* Spell(7779): Enchant Bracer - Minor Agility*/
(@ENTRY, '7788', '500', '333', '90', '0'),  /* Spell(7788): Enchant Weapon - Minor Striking*/
(@ENTRY, '7857', '1000', '333', '120', '0'),  /* Spell(7857): Enchant Chest - Health*/
(@ENTRY, '7863', '1400', '333', '125', '0'),  /* Spell(7863): Enchant Boots - Minor Stamina*/
(@ENTRY, '13378', '600', '333', '105', '0'),  /* Spell(13378): Enchant Shield - Minor Stamina*/
(@ENTRY, '13421', '800', '333', '115', '0'),  /* Spell(13421): Enchant Cloak - Lesser Protection*/
(@ENTRY, '13485', '1500', '333', '130', '0'),  /* Spell(13485): Enchant Shield - Lesser Spirit*/
(@ENTRY, '13501', '1500', '333', '130', '0'),  /* Spell(13501): Enchant Bracer - Lesser Stamina*/
(@ENTRY, '13503', '2000', '333', '140', '0'),  /* Spell(13503): Enchant Weapon - Lesser Striking*/
(@ENTRY, '13529', '2400', '333', '145', '0'),  /* Spell(13529): Enchant 2H Weapon - Lesser Impact*/
(@ENTRY, '13538', '2500', '333', '140', '0'),  /* Spell(13538): Enchant Chest - Lesser Absorption*/
(@ENTRY, '13607', '2400', '333', '145', '0'),  /* Spell(13607): Enchant Chest - Mana*/
(@ENTRY, '13622', '2500', '333', '150', '0'),  /* Spell(13622): Enchant Bracer - Lesser Intellect*/
(@ENTRY, '13626', '2500', '333', '150', '0'),  /* Spell(13626): Enchant Chest - Minor Stats*/
(@ENTRY, '13631', '2600', '333', '155', '0'),  /* Spell(13631): Enchant Shield - Lesser Stamina*/
(@ENTRY, '13635', '2600', '333', '155', '0'),  /* Spell(13635): Enchant Cloak - Defense*/
(@ENTRY, '13637', '2800', '333', '160', '0'),  /* Spell(13637): Enchant Boots - Lesser Agility*/
(@ENTRY, '13640', '2700', '333', '160', '0'),  /* Spell(13640): Enchant Chest - Greater Health*/
(@ENTRY, '13642', '2800', '333', '165', '0'),  /* Spell(13642): Enchant Bracer - Spirit*/
(@ENTRY, '13644', '2800', '333', '170', '0'),  /* Spell(13644): Enchant Boots - Lesser Stamina*/
(@ENTRY, '13646', '2800', '333', '170', '0'),  /* Spell(13646): Enchant Bracer - Lesser Dodge*/
(@ENTRY, '13648', '2800', '333', '170', '0'),  /* Spell(13648): Enchant Bracer - Stamina*/
(@ENTRY, '13659', '3200', '333', '180', '0'),  /* Spell(13659): Enchant Shield - Spirit*/
(@ENTRY, '13661', '3600', '333', '180', '0'),  /* Spell(13661): Enchant Bracer - Strength*/
(@ENTRY, '13663', '3800', '333', '185', '0'),  /* Spell(13663): Enchant Chest - Greater Mana*/
(@ENTRY, '13693', '4000', '333', '195', '0'),  /* Spell(13693): Enchant Weapon - Striking*/
(@ENTRY, '13695', '4000', '333', '200', '0'),  /* Spell(13695): Enchant 2H Weapon - Impact*/
(@ENTRY, '13700', '4000', '333', '200', '0'),  /* Spell(13700): Enchant Chest - Lesser Stats*/
(@ENTRY, '13746', '4200', '333', '205', '0'),  /* Spell(13746): Enchant Cloak - Greater Defense*/
(@ENTRY, '13815', '4400', '333', '210', '0'),  /* Spell(13815): Enchant Gloves - Agility*/
(@ENTRY, '13822', '4400', '333', '210', '0'),  /* Spell(13822): Enchant Bracer - Intellect*/
(@ENTRY, '13836', '4600', '333', '215', '0'),  /* Spell(13836): Enchant Boots - Stamina*/
(@ENTRY, '13858', '4800', '333', '220', '0'),  /* Spell(13858): Enchant Chest - Superior Health*/
(@ENTRY, '13887', '5000', '333', '225', '0'),  /* Spell(13887): Enchant Gloves - Strength*/
(@ENTRY, '13890', '5000', '333', '225', '0'),  /* Spell(13890): Enchant Boots - Minor Speed*/
(@ENTRY, '13905', '5400', '333', '230', '0'),  /* Spell(13905): Enchant Shield - Greater Spirit*/
(@ENTRY, '13917', '5400', '333', '230', '0'),  /* Spell(13917): Enchant Chest - Superior Mana*/
(@ENTRY, '13920', '50000', '333', '200', '35'),  /* Spell(13920): Enchanting*/
(@ENTRY, '13935', '5800', '333', '235', '0'),  /* Spell(13935): Enchant Boots - Agility*/
(@ENTRY, '13937', '6200', '333', '240', '0'),  /* Spell(13937): Enchant 2H Weapon - Greater Impact*/
(@ENTRY, '13939', '6200', '333', '240', '0'),  /* Spell(13939): Enchant Bracer - Greater Strength*/
(@ENTRY, '13941', '6200', '333', '245', '0'),  /* Spell(13941): Enchant Chest - Stats*/
(@ENTRY, '13943', '6200', '333', '245', '0'),  /* Spell(13943): Enchant Weapon - Greater Striking*/
(@ENTRY, '13948', '6500', '333', '250', '0'),  /* Spell(13948): Enchant Gloves - Minor Haste*/
(@ENTRY, '14293', '50', '333', '10', '0'),  /* Spell(14293): Lesser Magic Wand*/
(@ENTRY, '14807', '200', '333', '70', '0'),  /* Spell(14807): Greater Magic Wand*/
(@ENTRY, '14809', '2600', '333', '155', '0'),  /* Spell(14809): Lesser Mystic Wand*/
(@ENTRY, '14810', '3000', '333', '175', '0'),  /* Spell(14810): Greater Mystic Wand*/
(@ENTRY, '17180', '10000', '333', '250', '0'),  /* Spell(17180): Enchanted Thorium Bar*/
(@ENTRY, '17181', '10000', '333', '250', '0'),  /* Spell(17181): Enchanted Leather*/
(@ENTRY, '20008', '10000', '333', '255', '0'),  /* Spell(20008): Enchant Bracer - Greater Intellect*/
(@ENTRY, '20012', '10000', '333', '270', '0'),  /* Spell(20012): Enchant Gloves - Greater Agility*/
(@ENTRY, '20013', '20000', '333', '295', '0'),  /* Spell(20013): Enchant Gloves - Greater Strength*/
(@ENTRY, '20016', '15000', '333', '280', '0'),  /* Spell(20016): Enchant Shield - Vitality*/
(@ENTRY, '20023', '20000', '333', '295', '0'),  /* Spell(20023): Enchant Boots - Greater Agility*/
(@ENTRY, '20028', '15000', '333', '290', '0'),  /* Spell(20028): Enchant Chest - Major Mana*/
(@ENTRY, '27899', '12500', '333', '305', '0'),  /* Spell(27899): Enchant Bracer - Brawn*/
(@ENTRY, '27905', '12500', '333', '315', '0'),  /* Spell(27905): Enchant Bracer - Stats*/
(@ENTRY, '27944', '15000', '333', '310', '0'),  /* Spell(27944): Enchant Shield - Lesser Dodge*/
(@ENTRY, '27957', '17500', '333', '315', '0'),  /* Spell(27957): Enchant Chest - Exceptional Health*/
(@ENTRY, '27958', '50000', '333', '350', '0'),  /* Spell(27958): Enchant Chest - Exceptional Mana*/
(@ENTRY, '27961', '15000', '333', '310', '0'),  /* Spell(27961): Enchant Cloak - Major Armor*/
(@ENTRY, '28027', '40000', '333', '325', '0'),  /* Spell(28027): Prismatic Sphere*/
(@ENTRY, '28028', '80000', '333', '350', '0'),  /* Spell(28028): Void Sphere*/
(@ENTRY, '28029', '100000', '333', '275', '50'),  /* Spell(28029): Enchanting*/
(@ENTRY, '33990', '20000', '333', '320', '0'),  /* Spell(33990): Enchant Chest - Major Spirit*/
(@ENTRY, '33991', '20000', '333', '300', '0'),  /* Spell(33991): Enchant Chest - Restore Mana Prime*/
(@ENTRY, '33993', '12500', '333', '305', '0'),  /* Spell(33993): Enchant Gloves - Blasting*/
(@ENTRY, '33995', '25000', '333', '340', '0'),  /* Spell(33995): Enchant Gloves - Major Strength*/
(@ENTRY, '33996', '15000', '333', '310', '0'),  /* Spell(33996): Enchant Gloves - Assault*/
(@ENTRY, '34001', '12500', '333', '305', '0'),  /* Spell(34001): Enchant Bracer - Major Intellect*/
(@ENTRY, '34002', '12500', '333', '300', '0'),  /* Spell(34002): Enchant Bracer - Lesser Assault*/
(@ENTRY, '34004', '15000', '333', '310', '0'),  /* Spell(34004): Enchant Cloak - Greater Agility*/
(@ENTRY, '42613', '10000', '333', '300', '0'),  /* Spell(42613): Nexus Transformation*/
(@ENTRY, '42615', '40000', '333', '335', '0'),  /* Spell(42615): Small Prismatic Shard*/
(@ENTRY, '44383', '25000', '333', '330', '0'),  /* Spell(44383): Enchant Shield - Resilience*/
(@ENTRY, '44484', '150000', '333', '405', '0'),  /* Spell(44484): Enchant Gloves - Expertise*/
(@ENTRY, '44488', '150000', '333', '410', '0'),  /* Spell(44488): Enchant Gloves - Precision*/
(@ENTRY, '44489', '150000', '333', '420', '0'),  /* Spell(44489): Enchant Shield - Dodge*/
(@ENTRY, '44492', '100000', '333', '395', '0'),  /* Spell(44492): Enchant Chest - Mighty Health*/
(@ENTRY, '44500', '100000', '333', '395', '0'),  /* Spell(44500): Enchant Cloak - Superior Agility*/
(@ENTRY, '44506', '50000', '333', '375', '0'),  /* Spell(44506): Enchant Gloves - Gatherer*/
(@ENTRY, '44508', '150000', '333', '410', '0'),  /* Spell(44508): Enchant Boots - Greater Spirit*/
(@ENTRY, '44509', '150000', '333', '420', '0'),  /* Spell(44509): Enchant Chest - Greater Mana Restoration*/
(@ENTRY, '44510', '150000', '333', '410', '0'),  /* Spell(44510): Enchant Weapon - Exceptional Spirit*/
(@ENTRY, '44513', '100000', '333', '395', '0'),  /* Spell(44513): Enchant Gloves - Greater Assault*/
(@ENTRY, '44528', '90000', '333', '385', '0'),  /* Spell(44528): Enchant Boots - Greater Fortitude*/
(@ENTRY, '44529', '150000', '333', '415', '0'),  /* Spell(44529): Enchant Gloves - Major Agility*/
(@ENTRY, '44555', '50000', '333', '375', '0'),  /* Spell(44555): Enchant Bracer - Exceptional Intellect*/
(@ENTRY, '44582', '100000', '333', '395', '0'),  /* Spell(44582): Enchant Cloak - Minor Power*/
(@ENTRY, '44584', '150000', '333', '405', '0'),  /* Spell(44584): Enchant Boots - Greater Vitality*/
(@ENTRY, '44589', '150000', '333', '415', '0'),  /* Spell(44589): Enchant Boots - Superior Agility*/
(@ENTRY, '44592', '50000', '333', '360', '0'),  /* Spell(44592): Enchant Gloves - Exceptional Spellpower*/
(@ENTRY, '44593', '150000', '333', '420', '0'),  /* Spell(44593): Enchant Bracer - Major Spirit*/
(@ENTRY, '44598', '150000', '333', '415', '0'),  /* Spell(44598): Enchant Bracer - Expertise*/
(@ENTRY, '44616', '100000', '333', '400', '0'),  /* Spell(44616): Enchant Bracer - Greater Stats*/
(@ENTRY, '44623', '50000', '333', '370', '0'),  /* Spell(44623): Enchant Chest - Super Stats*/
(@ENTRY, '44629', '100000', '333', '395', '0'),  /* Spell(44629): Enchant Weapon - Exceptional Spellpower*/
(@ENTRY, '44630', '80000', '333', '390', '0'),  /* Spell(44630): Enchant 2H Weapon - Greater Savagery*/
(@ENTRY, '44633', '150000', '333', '410', '0'),  /* Spell(44633): Enchant Weapon - Exceptional Agility*/
(@ENTRY, '44635', '100000', '333', '395', '0'),  /* Spell(44635): Enchant Bracer - Greater Spellpower*/
(@ENTRY, '44636', '100000', '333', '400', '0'),  /* Spell(44636): Enchant Ring - Lesser Intellect*/
(@ENTRY, '44645', '100000', '333', '400', '0'),  /* Spell(44645): Enchant Ring - Assault*/
(@ENTRY, '47766', '100000', '333', '400', '0'),  /* Spell(47766): Enchant Chest - Greater Dodge*/
(@ENTRY, '47900', '150000', '333', '425', '0'),  /* Spell(47900): Enchant Chest - Super Health*/
(@ENTRY, '51313', '350000', '333', '350', '65'),  /* Spell(51313): Enchanting*/
(@ENTRY, '59636', '100000', '333', '400', '0'),  /* Spell(59636): Enchant Ring - Lesser Stamina*/
(@ENTRY, '60606', '50000', '333', '375', '0'),  /* Spell(60606): Enchant Boots - Assault*/
(@ENTRY, '60609', '50000', '333', '350', '0'),  /* Spell(60609): Enchant Cloak - Speed*/
(@ENTRY, '60616', '50000', '333', '360', '0'),  /* Spell(60616): Enchant Bracer - Assault*/
(@ENTRY, '60621', '80000', '333', '380', '0'),  /* Spell(60621): Enchant Weapon - Greater Potency*/
(@ENTRY, '60623', '90000', '333', '385', '0'),  /* Spell(60623): Enchant Boots - Icewalker*/
(@ENTRY, '60653', '100000', '333', '395', '0'),  /* Spell(60653): Enchant Shield - Greater Intellect*/
(@ENTRY, '60663', '150000', '333', '420', '0'),  /* Spell(60663): Enchant Cloak - Major Agility*/
(@ENTRY, '60668', '150000', '333', '425', '0'),  /* Spell(60668): Enchant Gloves - Crusher*/
(@ENTRY, '62959', '90000', '333', '385', '0'),  /* Spell(62959): Enchant Staff - Spellpower*/
(@ENTRY, '63746', '5000', '333', '225', '0'),  /* Spell(63746): Enchant Boots - Lesser Accuracy*/
(@ENTRY, '69412', '150000', '333', '445', '0'),  /* Spell(69412): Abyssal Shatter*/
(@ENTRY, '74132', '30000', '333', '425', '0'),  /* Spell(74132): Enchant Gloves - Mastery*/
(@ENTRY, '74189', '30000', '333', '425', '0'),  /* Spell(74189): Enchant Boots - Earthen Vitality*/
(@ENTRY, '74191', '30000', '333', '425', '0'),  /* Spell(74191): Enchant Chest - Mighty Stats*/
(@ENTRY, '74192', '30000', '333', '435', '0'),  /* Spell(74192): Enchant Cloak - Lesser Power*/
(@ENTRY, '74193', '30000', '333', '435', '0'),  /* Spell(74193): Enchant Bracer - Speed*/
(@ENTRY, '74195', '30000', '333', '450', '0'),  /* Spell(74195): Enchant Weapon - Mending*/
(@ENTRY, '74197', '30000', '333', '450', '0'),  /* Spell(74197): Enchant Weapon - Avalanche*/
(@ENTRY, '74198', '30000', '333', '455', '0'),  /* Spell(74198): Enchant Gloves - Haste*/
(@ENTRY, '74199', '30000', '333', '455', '0'),  /* Spell(74199): Enchant Boots - Haste*/
(@ENTRY, '74200', '30000', '333', '460', '0'),  /* Spell(74200): Enchant Chest - Stamina*/
(@ENTRY, '74201', '30000', '333', '460', '0'),  /* Spell(74201): Enchant Bracer - Critical Strike*/
(@ENTRY, '74202', '30000', '333', '465', '0'),  /* Spell(74202): Enchant Cloak - Intellect*/
(@ENTRY, '74207', '30000', '333', '465', '0'),  /* Spell(74207): Enchant Shield - Protection*/
(@ENTRY, '74211', '30000', '333', '470', '0'),  /* Spell(74211): Enchant Weapon - Elemental Slayer*/
(@ENTRY, '74212', '30000', '333', '470', '0'),  /* Spell(74212): Enchant Gloves - Exceptional Strength*/
(@ENTRY, '74213', '30000', '333', '475', '0'),  /* Spell(74213): Enchant Boots - Major Agility*/
(@ENTRY, '74214', '30000', '333', '475', '0'),  /* Spell(74214): Enchant Chest - Mighty Resilience*/
(@ENTRY, '74215', '30000', '333', '475', '0'),  /* Spell(74215): Enchant Ring - Strength*/
(@ENTRY, '74216', '30000', '333', '475', '0'),  /* Spell(74216): Enchant Ring - Agility*/
(@ENTRY, '74217', '30000', '333', '475', '0'),  /* Spell(74217): Enchant Ring - Intellect*/
(@ENTRY, '74218', '30000', '333', '475', '0'),  /* Spell(74218): Enchant Ring - Stamina*/
(@ENTRY, '74220', '30000', '333', '480', '0'),  /* Spell(74220): Enchant Gloves - Greater Expertise*/
(@ENTRY, '74223', '30000', '333', '480', '0'),  /* Spell(74223): Enchant Weapon - Hurricane*/
(@ENTRY, '74225', '30000', '333', '485', '0'),  /* Spell(74225): Enchant Weapon - Heartsong*/
(@ENTRY, '74226', '30000', '333', '485', '0'),  /* Spell(74226): Enchant Shield - Mastery*/
(@ENTRY, '74229', '30000', '333', '490', '0'),  /* Spell(74229): Enchant Bracer - Superior Dodge*/
(@ENTRY, '74230', '30000', '333', '490', '0'),  /* Spell(74230): Enchant Cloak - Critical Strike*/
(@ENTRY, '74231', '30000', '333', '495', '0'),  /* Spell(74231): Enchant Chest - Exceptional Spirit*/
(@ENTRY, '74232', '30000', '333', '495', '0'),  /* Spell(74232): Enchant Bracer - Precision*/
(@ENTRY, '74234', '30000', '333', '500', '0'),  /* Spell(74234): Enchant Cloak - Protection*/
(@ENTRY, '74235', '30000', '333', '500', '0'),  /* Spell(74235): Enchant Off-Hand - Superior Intellect*/
(@ENTRY, '74236', '30000', '333', '505', '0'),  /* Spell(74236): Enchant Boots - Precision*/
(@ENTRY, '74237', '30000', '333', '505', '0'),  /* Spell(74237): Enchant Bracer - Exceptional Spirit*/
(@ENTRY, '74238', '30000', '333', '510', '0'),  /* Spell(74238): Enchant Boots - Mastery*/
(@ENTRY, '74239', '30000', '333', '510', '0'),  /* Spell(74239): Enchant Bracer - Greater Expertise*/
(@ENTRY, '74240', '30000', '333', '510', '0'),  /* Spell(74240): Enchant Cloak - Greater Intellect*/
(@ENTRY, '74258', '500000', '333', '425', '75'),  /* Spell(74258): Enchanting*/
(@ENTRY, '95471', '30000', '333', '470', '0'),  /* Spell(95471): Enchant 2H Weapon - Mighty Agility*/
(@ENTRY, '103461', '22857', '333', '550', '0'),  /* Spell(103461): Enchant Ring - Greater Agility*/
(@ENTRY, '103462', '22857', '333', '550', '0'),  /* Spell(103462): Enchant Ring - Greater Intellect*/
(@ENTRY, '103463', '22857', '333', '550', '0'),  /* Spell(103463): Enchant Ring - Greater Stamina*/
(@ENTRY, '103465', '22857', '333', '550', '0'),  /* Spell(103465): Enchant Ring - Greater Strength*/
(@ENTRY, '104338', '22857', '333', '500', '0'),  /* Spell(104338): Enchant Bracer - Mastery*/
(@ENTRY, '104385', '22857', '333', '525', '0'),  /* Spell(104385): Enchant Bracer - Major Dodge*/
(@ENTRY, '104392', '22857', '333', '525', '0'),  /* Spell(104392): Enchant Chest - Super Resilience*/
(@ENTRY, '104393', '22857', '333', '525', '0'),  /* Spell(104393): Enchant Chest - Mighty Spirit*/
(@ENTRY, '104395', '22857', '333', '575', '0'),  /* Spell(104395): Enchant Chest - Glorious Stats*/
(@ENTRY, '104397', '22857', '333', '550', '0'),  /* Spell(104397): Enchant Chest - Superior Stamina*/
(@ENTRY, '104398', '22857', '333', '550', '0'),  /* Spell(104398): Enchant Cloak - Accuracy*/
(@ENTRY, '104401', '22857', '333', '575', '0'),  /* Spell(104401): Enchant Cloak - Greater Protection*/
(@ENTRY, '104403', '22857', '333', '525', '0'),  /* Spell(104403): Enchant Cloak - Superior Intellect*/
(@ENTRY, '104404', '22857', '333', '500', '0'),  /* Spell(104404): Enchant Cloak - Superior Critical Strike*/
(@ENTRY, '104407', '22857', '333', '550', '0'),  /* Spell(104407): Enchant Boots - Greater Haste*/
(@ENTRY, '104408', '22857', '333', '525', '0'),  /* Spell(104408): Enchant Boots - Greater Precision*/
(@ENTRY, '104409', '22857', '333', '550', '0'),  /* Spell(104409): Enchant Boots - Blurred Speed*/
(@ENTRY, '104414', '22857', '333', '575', '0'),  /* Spell(104414): Enchant Boots - Pandaren's Step*/
(@ENTRY, '104416', '22857', '333', '525', '0'),  /* Spell(104416): Enchant Gloves - Greater Haste*/
(@ENTRY, '104417', '22857', '333', '550', '0'),  /* Spell(104417): Enchant Gloves - Superior Expertise*/
(@ENTRY, '104419', '22857', '333', '575', '0'),  /* Spell(104419): Enchant Gloves - Super Strength*/
(@ENTRY, '104420', '22857', '333', '575', '0'),  /* Spell(104420): Enchant Gloves - Superior Mastery*/
(@ENTRY, '104425', '22857', '333', '550', '0'),  /* Spell(104425): Enchant Weapon - Windsong*/
(@ENTRY, '104430', '22857', '333', '525', '0'),  /* Spell(104430): Enchant Weapon - Elemental Force*/
(@ENTRY, '104440', '22857', '333', '575', '0'),  /* Spell(104440): Enchant Weapon - Colossus*/
(@ENTRY, '104445', '22857', '333', '575', '0'),  /* Spell(104445): Enchant Off-Hand - Major Intellect*/
(@ENTRY, '104698', '30000', '333', '515', '0'),  /* Spell(104698): Maelstrom Shatter*/
(@ENTRY, '110400', '685714', '333', '500', '80'),  /* Spell(110400): Enchanting*/
(@ENTRY, '116497', '22857', '333', '500', '0'),  /* Spell(116497): Mysterious Essence*/
(@ENTRY, '116498', '22857', '333', '550', '0'),  /* Spell(116498): Ethereal Shard*/
(@ENTRY, '116499', '22857', '333', '600', '0'),  /* Spell(116499): Sha Crystal*/
(@ENTRY, '118237', '22857', '333', '535', '0'),  /* Spell(118237): Mysterious Diffusion*/
(@ENTRY, '118238', '22857', '333', '585', '0'),  /* Spell(118238): Ethereal Shatter*/
(@ENTRY, '118239', '22857', '333', '600', '0'),  /* Spell(118239): Sha Shatter*/
(@ENTRY, '130758', '22857', '333', '575', '0');  /* Spell(130758): Enchant Shield - Greater Parry*/


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
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES 
('1317', '27354'),  /* Quest(27354): Mastering the Arcane ,QuestMinLevel: 20 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('1317', '27355'),  /* Quest(27355): A Boon for the Powerful ,QuestMinLevel: 20 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('1317', '27361'),  /* Quest(27361): Favored of the Light ,QuestMinLevel: 20 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('1317', '27362'),  /* Quest(27362): Favored of Elune ,QuestMinLevel: 20 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('1317', '27363');  /* Quest(27363): A Budding Young Surgeon ,QuestMinLevel: 20 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 


/* Step 1.8 Table  `waypoints */
DELETE FROM waypoints WHERE  `entry` = @ENTRY;
/* Step 2.5 Table  `npc_spellclick_spells */
DELETE FROM npc_spellclick_spells WHERE  `npc_entry` = @ENTRY;
/* Step 2.6 Table  `pet_levelstats */
DELETE FROM pet_levelstats WHERE  `creature_entry` = @ENTRY;

