/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 28/1/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Rogg';
SET @ENTRY 		:= '37072';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '4382', '0', '0', '0', @CREATURE, 'Blacksmithing Trainer', '', '0', '60', '60', '0', '0', '35', '35', '80', '0', '1', '1.14286', '0', '1.14286', '1', '0', '104', '138', '0', '252', '1', '2000', '2000', '1', '512', '2048', '0', '0', '2', '0', '0', '0', '72', '106', '26', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1.35', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '37072', '0', '0', '', '16048');

/* Step 1.2 Table `creature_equip_template */
DELETE FROM `creature_equip_template` WHERE `entry`= 37072;
INSERT INTO `creature_equip_template` (`entry`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES 
('37072', '2182', '0', '0'); /* [ItemEntry1(2182): Monster - Mace, Ornate Metal Hammer] */

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES 
(@ENTRY, '0', '0', '0', '257', '0', ''); 


/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('4382', '0.372', '1.5', '0', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 37072 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '1', '1637', '5170', '1', '1', '0', '0', '1591.39', '-4275.7', '21.5463', '1.0472', '120', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '1591.39' AND `position_y` REGEXP '-4275.7' AND `position_z` REGEXP '21.5463' AND `phaseMask` = '1' AND `map` = '1');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '1591.39' AND `position_y` REGEXP '-4275.7' AND `position_z` REGEXP '21.5463' AND `phaseMask` = '1' AND `map` = '1');
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
(@ENTRY, '2018', '10', '164', '0', '5'),  /* Spell(2018): Blacksmithing*/
(@ENTRY, '2661', '100', '164', '35', '0'),  /* Spell(2661): Copper Chain Belt*/
(@ENTRY, '2662', '50', '164', '1', '0'),  /* Spell(2662): Copper Chain Pants*/
(@ENTRY, '2664', '500', '164', '90', '0'),  /* Spell(2664): Runed Copper Bracers*/
(@ENTRY, '2665', '100', '164', '65', '0'),  /* Spell(2665): Coarse Sharpening Stone*/
(@ENTRY, '2666', '200', '164', '70', '0'),  /* Spell(2666): Runed Copper Belt*/
(@ENTRY, '2668', '300', '164', '105', '0'),  /* Spell(2668): Rough Bronze Leggings*/
(@ENTRY, '2670', '500', '164', '105', '0'),  /* Spell(2670): Rough Bronze Cuirass*/
(@ENTRY, '2672', '500', '164', '120', '0'),  /* Spell(2672): Patterned Bronze Bracers*/
(@ENTRY, '2674', '1000', '164', '125', '0'),  /* Spell(2674): Heavy Sharpening Stone*/
(@ENTRY, '2675', '1000', '164', '145', '0'),  /* Spell(2675): Shining Silver Breastplate*/
(@ENTRY, '2737', '50', '164', '15', '0'),  /* Spell(2737): Copper Mace*/
(@ENTRY, '2738', '50', '164', '20', '0'),  /* Spell(2738): Copper Axe*/
(@ENTRY, '2739', '50', '164', '25', '0'),  /* Spell(2739): Copper Shortsword*/
(@ENTRY, '2740', '200', '164', '110', '0'),  /* Spell(2740): Bronze Mace*/
(@ENTRY, '2741', '200', '164', '115', '0'),  /* Spell(2741): Bronze Axe*/
(@ENTRY, '2742', '200', '164', '120', '0'),  /* Spell(2742): Bronze Shortsword*/
(@ENTRY, '3100', '500', '164', '50', '10'),  /* Spell(3100): Blacksmithing*/
(@ENTRY, '3116', '100', '164', '65', '0'),  /* Spell(3116): Coarse Weightstone*/
(@ENTRY, '3117', '1000', '164', '125', '0'),  /* Spell(3117): Heavy Weightstone*/
(@ENTRY, '3292', '500', '164', '95', '0'),  /* Spell(3292): Heavy Copper Broadsword*/
(@ENTRY, '3293', '250', '164', '35', '0'),  /* Spell(3293): Copper Battle Axe*/
(@ENTRY, '3294', '500', '164', '70', '0'),  /* Spell(3294): Thick War Axe*/
(@ENTRY, '3296', '1000', '164', '130', '0'),  /* Spell(3296): Heavy Bronze Mace*/
(@ENTRY, '3319', '50', '164', '20', '0'),  /* Spell(3319): Copper Chain Boots*/
(@ENTRY, '3320', '100', '164', '25', '0'),  /* Spell(3320): Rough Grinding Stone*/
(@ENTRY, '3323', '100', '164', '40', '0'),  /* Spell(3323): Runed Copper Gauntlets*/
(@ENTRY, '3324', '200', '164', '45', '0'),  /* Spell(3324): Runed Copper Pants*/
(@ENTRY, '3326', '250', '164', '75', '0'),  /* Spell(3326): Coarse Grinding Stone*/
(@ENTRY, '3328', '500', '164', '110', '0'),  /* Spell(3328): Rough Bronze Shoulders*/
(@ENTRY, '3331', '500', '164', '130', '0'),  /* Spell(3331): Silvered Bronze Boots*/
(@ENTRY, '3333', '1000', '164', '135', '0'),  /* Spell(3333): Silvered Bronze Gauntlets*/
(@ENTRY, '3337', '1000', '164', '125', '0'),  /* Spell(3337): Heavy Grinding Stone*/
(@ENTRY, '3491', '600', '164', '105', '0'),  /* Spell(3491): Big Bronze Knife*/
(@ENTRY, '3501', '1000', '164', '165', '0'),  /* Spell(3501): Green Iron Bracers*/
(@ENTRY, '3502', '1250', '164', '170', '0'),  /* Spell(3502): Green Iron Helm*/
(@ENTRY, '3506', '5000', '164', '155', '0'),  /* Spell(3506): Green Iron Leggings*/
(@ENTRY, '3508', '7500', '164', '180', '0'),  /* Spell(3508): Green Iron Hauberk*/
(@ENTRY, '3538', '5000', '164', '125', '25'),  /* Spell(3538): Blacksmithing*/
(@ENTRY, '6517', '800', '164', '110', '0'),  /* Spell(6517): Pearl-handled Dagger*/
(@ENTRY, '7223', '1000', '164', '185', '0'),  /* Spell(7223): Golden Scale Bracers*/
(@ENTRY, '7408', '300', '164', '65', '0'),  /* Spell(7408): Heavy Copper Maul*/
(@ENTRY, '7817', '200', '164', '95', '0'),  /* Spell(7817): Rough Bronze Boots*/
(@ENTRY, '8768', '250', '164', '150', '0'),  /* Spell(8768): Iron Buckle*/
(@ENTRY, '8880', '100', '164', '30', '0'),  /* Spell(8880): Copper Dagger*/
(@ENTRY, '9785', '50000', '164', '200', '35'),  /* Spell(9785): Blacksmithing*/
(@ENTRY, '9916', '2500', '164', '200', '0'),  /* Spell(9916): Steel Breastplate*/
(@ENTRY, '9918', '2500', '164', '200', '0'),  /* Spell(9918): Solid Sharpening Stone*/
(@ENTRY, '9920', '2500', '164', '200', '0'),  /* Spell(9920): Solid Grinding Stone*/
(@ENTRY, '9921', '2500', '164', '200', '0'),  /* Spell(9921): Solid Weightstone*/
(@ENTRY, '9926', '5000', '164', '205', '0'),  /* Spell(9926): Heavy Mithril Shoulder*/
(@ENTRY, '9928', '5000', '164', '205', '0'),  /* Spell(9928): Heavy Mithril Gauntlet*/
(@ENTRY, '9931', '5000', '164', '210', '0'),  /* Spell(9931): Mithril Scale Pants*/
(@ENTRY, '9935', '5000', '164', '215', '0'),  /* Spell(9935): Steel Plate Helm*/
(@ENTRY, '9959', '15000', '164', '230', '0'),  /* Spell(9959): Heavy Mithril Breastplate*/
(@ENTRY, '9961', '15000', '164', '230', '0'),  /* Spell(9961): Mithril Coif*/
(@ENTRY, '9968', '20000', '164', '235', '0'),  /* Spell(9968): Heavy Mithril Boots*/
(@ENTRY, '9983', '100', '164', '30', '0'),  /* Spell(9983): Copper Claymore*/
(@ENTRY, '9985', '250', '164', '125', '0'),  /* Spell(9985): Bronze Warhammer*/
(@ENTRY, '9986', '500', '164', '130', '0'),  /* Spell(9986): Bronze Greatsword*/
(@ENTRY, '9987', '500', '164', '135', '0'),  /* Spell(9987): Bronze Battle Axe*/
(@ENTRY, '9993', '10000', '164', '210', '0'),  /* Spell(9993): Heavy Mithril Axe*/
(@ENTRY, '10001', '15000', '164', '230', '0'),  /* Spell(10001): Big Black Mace*/
(@ENTRY, '15972', '7500', '164', '180', '0'),  /* Spell(15972): Glinting Steel Dagger*/
(@ENTRY, '16639', '10000', '164', '250', '0'),  /* Spell(16639): Dense Grinding Stone*/
(@ENTRY, '16640', '10000', '164', '250', '0'),  /* Spell(16640): Dense Weightstone*/
(@ENTRY, '16641', '10000', '164', '250', '0'),  /* Spell(16641): Dense Sharpening Stone*/
(@ENTRY, '16642', '10000', '164', '250', '0'),  /* Spell(16642): Thorium Armor*/
(@ENTRY, '16643', '10000', '164', '250', '0'),  /* Spell(16643): Thorium Belt*/
(@ENTRY, '16644', '10000', '164', '255', '0'),  /* Spell(16644): Thorium Bracers*/
(@ENTRY, '16646', '10000', '164', '265', '0'),  /* Spell(16646): Imperial Plate Shoulders*/
(@ENTRY, '16647', '10000', '164', '265', '0'),  /* Spell(16647): Imperial Plate Belt*/
(@ENTRY, '16649', '10000', '164', '270', '0'),  /* Spell(16649): Imperial Plate Bracers*/
(@ENTRY, '16652', '10000', '164', '280', '0'),  /* Spell(16652): Thorium Boots*/
(@ENTRY, '16653', '10000', '164', '280', '0'),  /* Spell(16653): Thorium Helm*/
(@ENTRY, '16657', '10000', '164', '295', '0'),  /* Spell(16657): Imperial Plate Boots*/
(@ENTRY, '16658', '10000', '164', '295', '0'),  /* Spell(16658): Imperial Plate Helm*/
(@ENTRY, '16662', '12000', '164', '300', '0'),  /* Spell(16662): Thorium Leggings*/
(@ENTRY, '16663', '12000', '164', '300', '0'),  /* Spell(16663): Imperial Plate Chest*/
(@ENTRY, '16730', '12000', '164', '300', '0'),  /* Spell(16730): Imperial Plate Leggings*/
(@ENTRY, '16969', '15000', '164', '275', '0'),  /* Spell(16969): Ornate Thorium Handaxe*/
(@ENTRY, '16971', '15000', '164', '280', '0'),  /* Spell(16971): Huge Thorium Battleaxe*/
(@ENTRY, '19666', '100', '164', '100', '0'),  /* Spell(19666): Silver Skeleton Key*/
(@ENTRY, '19667', '250', '164', '150', '0'),  /* Spell(19667): Golden Skeleton Key*/
(@ENTRY, '19668', '2500', '164', '200', '0'),  /* Spell(19668): Truesilver Skeleton Key*/
(@ENTRY, '19669', '10000', '164', '275', '0'),  /* Spell(19669): Arcanite Skeleton Key*/
(@ENTRY, '29545', '15000', '164', '300', '0'),  /* Spell(29545): Fel Iron Plate Gloves*/
(@ENTRY, '29547', '15000', '164', '305', '0'),  /* Spell(29547): Fel Iron Plate Belt*/
(@ENTRY, '29548', '20000', '164', '315', '0'),  /* Spell(29548): Fel Iron Plate Boots*/
(@ENTRY, '29549', '20000', '164', '315', '0'),  /* Spell(29549): Fel Iron Plate Pants*/
(@ENTRY, '29550', '25000', '164', '325', '0'),  /* Spell(29550): Fel Iron Breastplate*/
(@ENTRY, '29551', '15000', '164', '300', '0'),  /* Spell(29551): Fel Iron Chain Coif*/
(@ENTRY, '29552', '18000', '164', '310', '0'),  /* Spell(29552): Fel Iron Chain Gloves*/
(@ENTRY, '29553', '20000', '164', '315', '0'),  /* Spell(29553): Fel Iron Chain Bracers*/
(@ENTRY, '29556', '22000', '164', '320', '0'),  /* Spell(29556): Fel Iron Chain Tunic*/
(@ENTRY, '29557', '18000', '164', '310', '0'),  /* Spell(29557): Fel Iron Hatchet*/
(@ENTRY, '29558', '20000', '164', '315', '0'),  /* Spell(29558): Fel Iron Hammer*/
(@ENTRY, '29565', '22000', '164', '320', '0'),  /* Spell(29565): Fel Iron Greatsword*/
(@ENTRY, '29654', '15000', '164', '300', '0'),  /* Spell(29654): Fel Sharpening Stone*/
(@ENTRY, '29844', '100000', '164', '275', '50'),  /* Spell(29844): Blacksmithing*/
(@ENTRY, '32284', '25000', '164', '325', '0'),  /* Spell(32284): Lesser Rune of Warding*/
(@ENTRY, '34607', '15000', '164', '300', '0'),  /* Spell(34607): Fel Weightstone*/
(@ENTRY, '51300', '350000', '164', '350', '65'),  /* Spell(51300): Blacksmithing*/
(@ENTRY, '52567', '30000', '164', '370', '0'),  /* Spell(52567): Cobalt Legplates*/
(@ENTRY, '52568', '30000', '164', '350', '0'),  /* Spell(52568): Cobalt Belt*/
(@ENTRY, '52569', '30000', '164', '350', '0'),  /* Spell(52569): Cobalt Boots*/
(@ENTRY, '52570', '30000', '164', '375', '0'),  /* Spell(52570): Cobalt Chestpiece*/
(@ENTRY, '52571', '30000', '164', '370', '0'),  /* Spell(52571): Cobalt Helm*/
(@ENTRY, '52572', '30000', '164', '360', '0'),  /* Spell(52572): Cobalt Shoulders*/
(@ENTRY, '54550', '30000', '164', '360', '0'),  /* Spell(54550): Cobalt Triangle Shield*/
(@ENTRY, '54551', '40000', '164', '395', '0'),  /* Spell(54551): Tempered Saronite Belt*/
(@ENTRY, '54552', '40000', '164', '400', '0'),  /* Spell(54552): Tempered Saronite Boots*/
(@ENTRY, '54553', '40000', '164', '400', '0'),  /* Spell(54553): Tempered Saronite Breastplate*/
(@ENTRY, '54554', '40000', '164', '395', '0'),  /* Spell(54554): Tempered Saronite Legplates*/
(@ENTRY, '54555', '40000', '164', '405', '0'),  /* Spell(54555): Tempered Saronite Helm*/
(@ENTRY, '54556', '40000', '164', '405', '0'),  /* Spell(54556): Tempered Saronite Shoulders*/
(@ENTRY, '54557', '40000', '164', '390', '0'),  /* Spell(54557): Saronite Defender*/
(@ENTRY, '54917', '30000', '164', '375', '0'),  /* Spell(54917): Spiked Cobalt Helm*/
(@ENTRY, '54918', '30000', '164', '380', '0'),  /* Spell(54918): Spiked Cobalt Boots*/
(@ENTRY, '54941', '30000', '164', '385', '0'),  /* Spell(54941): Spiked Cobalt Shoulders*/
(@ENTRY, '54944', '30000', '164', '385', '0'),  /* Spell(54944): Spiked Cobalt Chestpiece*/
(@ENTRY, '54945', '35000', '164', '390', '0'),  /* Spell(54945): Spiked Cobalt Gauntlets*/
(@ENTRY, '54946', '30000', '164', '395', '0'),  /* Spell(54946): Spiked Cobalt Belt*/
(@ENTRY, '54947', '35000', '164', '395', '0'),  /* Spell(54947): Spiked Cobalt Legplates*/
(@ENTRY, '54948', '30000', '164', '400', '0'),  /* Spell(54948): Spiked Cobalt Bracers*/
(@ENTRY, '54949', '30000', '164', '400', '0'),  /* Spell(54949): Horned Cobalt Helm*/
(@ENTRY, '55013', '40000', '164', '390', '0'),  /* Spell(55013): Saronite Protector*/
(@ENTRY, '55014', '35000', '164', '410', '0'),  /* Spell(55014): Saronite Bulwark*/
(@ENTRY, '55015', '40000', '164', '415', '0'),  /* Spell(55015): Tempered Saronite Gauntlets*/
(@ENTRY, '55017', '40000', '164', '410', '0'),  /* Spell(55017): Tempered Saronite Bracers*/
(@ENTRY, '55055', '40000', '164', '395', '0'),  /* Spell(55055): Brilliant Saronite Legplates*/
(@ENTRY, '55056', '40000', '164', '400', '0'),  /* Spell(55056): Brilliant Saronite Gauntlets*/
(@ENTRY, '55057', '40000', '164', '405', '0'),  /* Spell(55057): Brilliant Saronite Boots*/
(@ENTRY, '55058', '45000', '164', '415', '0'),  /* Spell(55058): Brilliant Saronite Breastplate*/
(@ENTRY, '55174', '50000', '164', '390', '0'),  /* Spell(55174): Honed Cobalt Cleaver*/
(@ENTRY, '55177', '50000', '164', '395', '0'),  /* Spell(55177): Savage Cobalt Slicer*/
(@ENTRY, '55179', '50000', '164', '400', '0'),  /* Spell(55179): Saronite Ambusher*/
(@ENTRY, '55181', '50000', '164', '405', '0'),  /* Spell(55181): Saronite Shiv*/
(@ENTRY, '55182', '40000', '164', '410', '0'),  /* Spell(55182): Furious Saronite Beatstick*/
(@ENTRY, '55185', '45000', '164', '415', '0'),  /* Spell(55185): Saronite Mindcrusher*/
(@ENTRY, '55200', '35000', '164', '380', '0'),  /* Spell(55200): Sturdy Cobalt Quickblade*/
(@ENTRY, '55201', '35000', '164', '380', '0'),  /* Spell(55201): Cobalt Tenderizer*/
(@ENTRY, '55203', '35000', '164', '385', '0'),  /* Spell(55203): Forged Cobalt Claymore*/
(@ENTRY, '55204', '35000', '164', '390', '0'),  /* Spell(55204): Notched Cobalt War Axe*/
(@ENTRY, '55206', '40000', '164', '405', '0'),  /* Spell(55206): Deadly Saronite Dirk*/
(@ENTRY, '55298', '45000', '164', '420', '0'),  /* Spell(55298): Vengeance Bindings*/
(@ENTRY, '55300', '45000', '164', '420', '0'),  /* Spell(55300): Righteous Gauntlets*/
(@ENTRY, '55301', '45000', '164', '420', '0'),  /* Spell(55301): Daunting Handguards*/
(@ENTRY, '55302', '45000', '164', '425', '0'),  /* Spell(55302): Helm of Command*/
(@ENTRY, '55303', '45000', '164', '425', '0'),  /* Spell(55303): Daunting Legplates*/
(@ENTRY, '55304', '45000', '164', '425', '0'),  /* Spell(55304): Righteous Greaves*/
(@ENTRY, '55305', '45000', '164', '420', '0'),  /* Spell(55305): Savage Saronite Bracers*/
(@ENTRY, '55306', '45000', '164', '420', '0'),  /* Spell(55306): Savage Saronite Pauldrons*/
(@ENTRY, '55307', '45000', '164', '420', '0'),  /* Spell(55307): Savage Saronite Waistguard*/
(@ENTRY, '55308', '45000', '164', '420', '0'),  /* Spell(55308): Savage Saronite Walkers*/
(@ENTRY, '55309', '45000', '164', '420', '0'),  /* Spell(55309): Savage Saronite Gauntlets*/
(@ENTRY, '55310', '45000', '164', '425', '0'),  /* Spell(55310): Savage Saronite Legplates*/
(@ENTRY, '55311', '45000', '164', '425', '0'),  /* Spell(55311): Savage Saronite Hauberk*/
(@ENTRY, '55312', '45000', '164', '425', '0'),  /* Spell(55312): Savage Saronite Skullshield*/
(@ENTRY, '55369', '180000', '164', '440', '0'),  /* Spell(55369): Titansteel Destroyer*/
(@ENTRY, '55370', '150000', '164', '440', '0'),  /* Spell(55370): Titansteel Bonecrusher*/
(@ENTRY, '55371', '150000', '164', '440', '0'),  /* Spell(55371): Titansteel Guardian*/
(@ENTRY, '55372', '120000', '164', '440', '0'),  /* Spell(55372): Spiked Titansteel Helm*/
(@ENTRY, '55373', '120000', '164', '440', '0'),  /* Spell(55373): Tempered Titansteel Helm*/
(@ENTRY, '55374', '120000', '164', '440', '0'),  /* Spell(55374): Brilliant Titansteel Helm*/
(@ENTRY, '55375', '120000', '164', '440', '0'),  /* Spell(55375): Spiked Titansteel Treads*/
(@ENTRY, '55376', '120000', '164', '440', '0'),  /* Spell(55376): Tempered Titansteel Treads*/
(@ENTRY, '55377', '120000', '164', '440', '0'),  /* Spell(55377): Brilliant Titansteel Treads*/
(@ENTRY, '55628', '45000', '164', '400', '0'),  /* Spell(55628): Socket Bracer*/
(@ENTRY, '55641', '45000', '164', '400', '0'),  /* Spell(55641): Socket Gloves*/
(@ENTRY, '55656', '50000', '164', '415', '0'),  /* Spell(55656): Eternal Belt Buckle*/
(@ENTRY, '55834', '30000', '164', '360', '0'),  /* Spell(55834): Cobalt Bracers*/
(@ENTRY, '55835', '30000', '164', '370', '0'),  /* Spell(55835): Cobalt Gauntlets*/
(@ENTRY, '55839', '42000', '164', '420', '0'),  /* Spell(55839): Titanium Weapon Chain*/
(@ENTRY, '56234', '150000', '164', '440', '0'),  /* Spell(56234): Titansteel Shanker*/
(@ENTRY, '56280', '40000', '164', '410', '0'),  /* Spell(56280): Cudgel of Saronite Justice*/
(@ENTRY, '56357', '42000', '164', '420', '0'),  /* Spell(56357): Titanium Shield Spike*/
(@ENTRY, '56400', '150000', '164', '440', '0'),  /* Spell(56400): Titansteel Shield Wall*/
(@ENTRY, '56549', '45000', '164', '420', '0'),  /* Spell(56549): Ornate Saronite Bracers*/
(@ENTRY, '56550', '45000', '164', '420', '0'),  /* Spell(56550): Ornate Saronite Pauldrons*/
(@ENTRY, '56551', '45000', '164', '420', '0'),  /* Spell(56551): Ornate Saronite Waistguard*/
(@ENTRY, '56552', '45000', '164', '420', '0'),  /* Spell(56552): Ornate Saronite Walkers*/
(@ENTRY, '56553', '45000', '164', '420', '0'),  /* Spell(56553): Ornate Saronite Gauntlets*/
(@ENTRY, '56554', '45000', '164', '425', '0'),  /* Spell(56554): Ornate Saronite Legplates*/
(@ENTRY, '56555', '45000', '164', '425', '0'),  /* Spell(56555): Ornate Saronite Hauberk*/
(@ENTRY, '56556', '45000', '164', '425', '0'),  /* Spell(56556): Ornate Saronite Skullshield*/
(@ENTRY, '59405', '30000', '164', '350', '0'),  /* Spell(59405): Cobalt Skeleton Key*/
(@ENTRY, '59406', '45000', '164', '430', '0'),  /* Spell(59406): Titanium Skeleton Key*/
(@ENTRY, '59436', '40000', '164', '395', '0'),  /* Spell(59436): Brilliant Saronite Belt*/
(@ENTRY, '59438', '40000', '164', '400', '0'),  /* Spell(59438): Brilliant Saronite Bracers*/
(@ENTRY, '59440', '40000', '164', '405', '0'),  /* Spell(59440): Brilliant Saronite Pauldrons*/
(@ENTRY, '59441', '45000', '164', '415', '0'),  /* Spell(59441): Brilliant Saronite Helm*/
(@ENTRY, '59442', '40000', '164', '410', '0'),  /* Spell(59442): Saronite Spellblade*/
(@ENTRY, '61008', '120000', '164', '425', '0'),  /* Spell(61008): Icebane Chestguard*/
(@ENTRY, '61009', '120000', '164', '420', '0'),  /* Spell(61009): Icebane Girdle*/
(@ENTRY, '61010', '120000', '164', '420', '0'),  /* Spell(61010): Icebane Treads*/
(@ENTRY, '63182', '150000', '164', '440', '0'),  /* Spell(63182): Titansteel Spellblade*/
(@ENTRY, '76178', '15000', '164', '425', '0'),  /* Spell(76178): Folded Obsidium*/
(@ENTRY, '76179', '40000', '164', '440', '0'),  /* Spell(76179): Hardened Obsidium Bracers*/
(@ENTRY, '76180', '50000', '164', '450', '0'),  /* Spell(76180): Hardened Obsidium Gauntlets*/
(@ENTRY, '76181', '55000', '164', '460', '0'),  /* Spell(76181): Hardened Obsidium Belt*/
(@ENTRY, '76182', '60000', '164', '470', '0'),  /* Spell(76182): Hardened Obsidium Boots*/
(@ENTRY, '76258', '65000', '164', '480', '0'),  /* Spell(76258): Hardened Obsidium Shoulders*/
(@ENTRY, '76259', '65000', '164', '490', '0'),  /* Spell(76259): Hardened Obsidium Legguards*/
(@ENTRY, '76260', '65000', '164', '490', '0'),  /* Spell(76260): Hardened Obsidium Helm*/
(@ENTRY, '76261', '75000', '164', '500', '0'),  /* Spell(76261): Hardened Obsidium Breastplate*/
(@ENTRY, '76262', '40000', '164', '440', '0'),  /* Spell(76262): Redsteel Bracers*/
(@ENTRY, '76263', '50000', '164', '450', '0'),  /* Spell(76263): Redsteel Gauntlets*/
(@ENTRY, '76264', '55000', '164', '460', '0'),  /* Spell(76264): Redsteel Belt*/
(@ENTRY, '76265', '60000', '164', '470', '0'),  /* Spell(76265): Redsteel Boots*/
(@ENTRY, '76266', '65000', '164', '480', '0'),  /* Spell(76266): Redsteel Shoulders*/
(@ENTRY, '76267', '65000', '164', '490', '0'),  /* Spell(76267): Redsteel Legguards*/
(@ENTRY, '76269', '75000', '164', '500', '0'),  /* Spell(76269): Redsteel Helm*/
(@ENTRY, '76270', '75000', '164', '500', '0'),  /* Spell(76270): Redsteel Breastplate*/
(@ENTRY, '76280', '40000', '164', '440', '0'),  /* Spell(76280): Stormforged Bracers*/
(@ENTRY, '76281', '50000', '164', '450', '0'),  /* Spell(76281): Stormforged Gauntlets*/
(@ENTRY, '76283', '55000', '164', '460', '0'),  /* Spell(76283): Stormforged Belt*/
(@ENTRY, '76285', '60000', '164', '470', '0'),  /* Spell(76285): Stormforged Boots*/
(@ENTRY, '76286', '65000', '164', '480', '0'),  /* Spell(76286): Stormforged Shoulders*/
(@ENTRY, '76287', '65000', '164', '480', '0'),  /* Spell(76287): Stormforged Legguards*/
(@ENTRY, '76288', '65000', '164', '490', '0'),  /* Spell(76288): Stormforged Helm*/
(@ENTRY, '76289', '75000', '164', '500', '0'),  /* Spell(76289): Stormforged Breastplate*/
(@ENTRY, '76291', '50000', '164', '450', '0'),  /* Spell(76291): Hardened Obsidium Shield*/
(@ENTRY, '76293', '60000', '164', '470', '0'),  /* Spell(76293): Stormforged Shield*/
(@ENTRY, '76433', '50000', '164', '460', '0'),  /* Spell(76433): Decapitator's Razor*/
(@ENTRY, '76434', '60000', '164', '470', '0'),  /* Spell(76434): Cold-Forged Shank*/
(@ENTRY, '76435', '65000', '164', '480', '0'),  /* Spell(76435): Fire-Etched Dagger*/
(@ENTRY, '76436', '65000', '164', '480', '0'),  /* Spell(76436): Lifeforce Hammer*/
(@ENTRY, '76437', '65000', '164', '480', '0'),  /* Spell(76437): Obsidium Executioner*/
(@ENTRY, '76438', '60000', '164', '475', '0'),  /* Spell(76438): Obsidium Skeleton Key*/
(@ENTRY, '76441', '65000', '164', '490', '0'),  /* Spell(76441): Elementium Shield Spike*/
(@ENTRY, '76474', '60000', '164', '470', '0'),  /* Spell(76474): Obsidium Bladespear*/
(@ENTRY, '76666', '500000', '164', '425', '75'),  /* Spell(76666): Blacksmithing*/
(@ENTRY, '110396', '685714', '164', '500', '80'),  /* Spell(110396): Blacksmithing*/
(@ENTRY, '122576', '91428', '164', '550', '0'),  /* Spell(122576): Ghost-Forged Helm*/
(@ENTRY, '122577', '91428', '164', '540', '0'),  /* Spell(122577): Ghost-Forged Shoulders*/
(@ENTRY, '122578', '91428', '164', '550', '0'),  /* Spell(122578): Ghost-Forged Breastplate*/
(@ENTRY, '122579', '91428', '164', '525', '0'),  /* Spell(122579): Ghost-Forged Gauntlets*/
(@ENTRY, '122580', '91428', '164', '530', '0'),  /* Spell(122580): Ghost-Forged Legplates*/
(@ENTRY, '122581', '91428', '164', '500', '0'),  /* Spell(122581): Ghost-Forged Bracers*/
(@ENTRY, '122582', '91428', '164', '530', '0'),  /* Spell(122582): Ghost-Forged Boots*/
(@ENTRY, '122583', '91428', '164', '525', '0'),  /* Spell(122583): Ghost-Forged Belt*/
(@ENTRY, '122633', '91428', '164', '500', '0'),  /* Spell(122633): Ghostly Skeleton Key*/
(@ENTRY, '122635', '91428', '164', '540', '0'),  /* Spell(122635): Lightsteel Shield*/
(@ENTRY, '122636', '91428', '164', '545', '0'),  /* Spell(122636): Spiritguard Shield*/
(@ENTRY, '122637', '91428', '164', '545', '0'),  /* Spell(122637): Forgewire Axe*/
(@ENTRY, '122638', '91428', '164', '545', '0'),  /* Spell(122638): Ghost-Forged Blade*/
(@ENTRY, '122639', '91428', '164', '560', '0'),  /* Spell(122639): Phantasmal Hammer*/
(@ENTRY, '122640', '91428', '164', '565', '0'),  /* Spell(122640): Spiritblade Decimator*/
(@ENTRY, '122641', '91428', '164', '565', '0');  /* Spell(122641): Ghost Shard*/


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

