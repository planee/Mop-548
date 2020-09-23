/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 28/1/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Theresa Denman';
SET @ENTRY 		:= '44582';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '33974', '0', '0', '0', @CREATURE, 'Jewelcrafting Trainer', '', '11861', '30', '30', '0', '0', '35', '35', '17', '0', '1', '1.14286', '0', '1.14286', '1', '0', '38', '57', '0', '14', '1', '2000', '2000', '1', '512', '2048', '0', '0', '2', '0', '0', '0', '30', '46', '11', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '', '16048');

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES 
(@ENTRY, '0', '0', '0', '257', '0', ''); 


/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('33974', '0.208', '1.5', '1', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 44582 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '0', '1519', '5148', '1', '1', '0', '0', '-8712.15', '620.003', '101.589', '0.244346', '120', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-8712.15' AND `position_y` REGEXP '620.003' AND `position_z` REGEXP '101.589' AND `phaseMask` = '1' AND `map` = '0');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-8712.15' AND `position_y` REGEXP '620.003' AND `position_z` REGEXP '101.589' AND `phaseMask` = '1' AND `map` = '0');
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
DELETE FROM gossip_menu WHERE  `entry` = 11861;
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES 
(11861, 10846); 
/* Step 4.6 Table  `npc_text` */
DELETE FROM npc_text WHERE `ID` = 10846;
INSERT INTO `npc_text` (`ID`,`text0_0`,`text0_1`,`lang0`,`prob0`,`em0_0`,`em0_1`,`em0_2`,`em0_3`,`em0_4`,`em0_5`,`text1_0`,`text1_1`,`lang1`,`prob1`,`em1_0`,`em1_1`,`em1_2`,`em1_3`,`em1_4`,`em1_5`,`text2_0`,`text2_1`,`lang2`,`prob2`,`em2_0`,`em2_1`,`em2_2`,`em2_3`,`em2_4`,`em2_5`,`text3_0`,`text3_1`,`lang3`,`prob3`,`em3_0`,`em3_1`,`em3_2`,`em3_3`,`em3_4`,`em3_5`,`text4_0`,`text4_1`,`lang4`,`prob4`,`em4_0`,`em4_1`,`em4_2`,`em4_3`,`em4_4`,`em4_5`,`text5_0`,`text5_1`,`lang5`,`prob5`,`em5_0`,`em5_1`,`em5_2`,`em5_3`,`em5_4`,`em5_5`,`text6_0`,`text6_1`,`lang6`,`prob6`,`em6_0`,`em6_1`,`em6_2`,`em6_3`,`em6_4`,`em6_5`,`text7_0`,`text7_1`,`lang7`,`prob7`,`em7_0`,`em7_1`,`em7_2`,`em7_3`,`em7_4`,`em7_5`,`WDBVerified`) VALUES 
('10846', 'I can instruct you in jewelcrafting.  Interested?', 'I can instruct you in jewelcrafting.  Interested?', '0', '1', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '15595'); 




/* Step 2.7 Table  `gossip_menu_option */
DELETE FROM gossip_menu_option WHERE  `menu_id` = 11861;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
('11861', '0', '3', 'Train me.', '5', '16', '0', '0', '0', '0', '');


/*## Step 5: Creature NPC Trainer / Vendor ############################*/

/* Step 2.0 Table  `npc_trainer */
DELETE FROM npc_trainer WHERE `entry` = @ENTRY;
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES 
(@ENTRY, '25229', '10', '755', '0', '5'),  /* Spell(25229): Jewelcrafting*/
(@ENTRY, '25230', '500', '755', '50', '10'),  /* Spell(25230): Jewelcrafting*/
(@ENTRY, '25278', '200', '755', '50', '0'),  /* Spell(25278): Bronze Setting*/
(@ENTRY, '25280', '200', '755', '50', '0'),  /* Spell(25280): Elegant Silver Ring*/
(@ENTRY, '25283', '100', '755', '30', '0'),  /* Spell(25283): Inlaid Malachite Ring*/
(@ENTRY, '25284', '400', '755', '60', '0'),  /* Spell(25284): Simple Pearl Ring*/
(@ENTRY, '25287', '400', '755', '70', '0'),  /* Spell(25287): Gloom Band*/
(@ENTRY, '25305', '1000', '755', '90', '0'),  /* Spell(25305): Heavy Silver Ring*/
(@ENTRY, '25317', '600', '755', '80', '0'),  /* Spell(25317): Ring of Silver Might*/
(@ENTRY, '25318', '800', '755', '100', '0'),  /* Spell(25318): Ring of Twilight Shadows*/
(@ENTRY, '25321', '1500', '755', '120', '0'),  /* Spell(25321): Moonsoul Crown*/
(@ENTRY, '25490', '300', '755', '50', '0'),  /* Spell(25490): Solid Bronze Ring*/
(@ENTRY, '25498', '600', '755', '110', '0'),  /* Spell(25498): Barbaric Iron Collar*/
(@ENTRY, '25610', '1500', '755', '120', '0'),  /* Spell(25610): Pendant of the Agate Shield*/
(@ENTRY, '25612', '1500', '755', '125', '0'),  /* Spell(25612): Heavy Iron Knuckles*/
(@ENTRY, '25613', '1200', '755', '135', '0'),  /* Spell(25613): Golden Dragon Ring*/
(@ENTRY, '25615', '1500', '755', '150', '0'),  /* Spell(25615): Mithril Filigree*/
(@ENTRY, '25617', '1500', '755', '150', '0'),  /* Spell(25617): Blazing Citrine Ring*/
(@ENTRY, '25620', '2000', '755', '170', '0'),  /* Spell(25620): Engraved Truesilver Ring*/
(@ENTRY, '25621', '2000', '755', '180', '0'),  /* Spell(25621): Citrine Ring of Rapid Healing*/
(@ENTRY, '26872', '2500', '755', '200', '0'),  /* Spell(26872): Figurine - Jade Owl*/
(@ENTRY, '26874', '5000', '755', '210', '0'),  /* Spell(26874): Aquamarine Signet*/
(@ENTRY, '26876', '3000', '755', '220', '0'),  /* Spell(26876): Aquamarine Pendant of the Warrior*/
(@ENTRY, '26880', '3500', '755', '225', '0'),  /* Spell(26880): Thorium Setting*/
(@ENTRY, '26883', '4000', '755', '235', '0'),  /* Spell(26883): Ruby Pendant of Fire*/
(@ENTRY, '26885', '5000', '755', '240', '0'),  /* Spell(26885): Truesilver Healing Ring*/
(@ENTRY, '26902', '10000', '755', '260', '0'),  /* Spell(26902): Simple Opal Ring*/
(@ENTRY, '26903', '10000', '755', '275', '0'),  /* Spell(26903): Sapphire Signet*/
(@ENTRY, '26907', '10000', '755', '280', '0'),  /* Spell(26907): Onslaught Ring*/
(@ENTRY, '26908', '12000', '755', '280', '0'),  /* Spell(26908): Sapphire Pendant of Winter Night*/
(@ENTRY, '26911', '15000', '755', '290', '0'),  /* Spell(26911): Living Emerald Pendant*/
(@ENTRY, '26916', '20000', '755', '310', '0'),  /* Spell(26916): Band of Natural Fire*/
(@ENTRY, '26926', '50', '755', '5', '0'),  /* Spell(26926): Heavy Copper Ring*/
(@ENTRY, '26927', '300', '755', '50', '0'),  /* Spell(26927): Thick Bronze Necklace*/
(@ENTRY, '26928', '100', '755', '30', '0'),  /* Spell(26928): Ornate Tigerseye Necklace*/
(@ENTRY, '28894', '5000', '755', '125', '25'),  /* Spell(28894): Jewelcrafting*/
(@ENTRY, '28895', '50000', '755', '200', '35'),  /* Spell(28895): Jewelcrafting*/
(@ENTRY, '28897', '100000', '755', '275', '50'),  /* Spell(28897): Jewelcrafting*/
(@ENTRY, '28905', '10000', '755', '300', '0'),  /* Spell(28905): Bold Blood Garnet*/
(@ENTRY, '28910', '10000', '755', '300', '0'),  /* Spell(28910): Inscribed Flame Spessarite*/
(@ENTRY, '28914', '10000', '755', '315', '0'),  /* Spell(28914): Glinting Shadow Draenite*/
(@ENTRY, '28916', '10000', '755', '300', '0'),  /* Spell(28916): Radiant Deep Peridot*/
(@ENTRY, '28917', '10000', '755', '300', '0'),  /* Spell(28917): Jagged Deep Peridot*/
(@ENTRY, '28925', '10000', '755', '300', '0'),  /* Spell(28925): Timeless Shadow Draenite*/
(@ENTRY, '28936', '10000', '755', '325', '0'),  /* Spell(28936): Sovereign Shadow Draenite*/
(@ENTRY, '28948', '10000', '755', '325', '0'),  /* Spell(28948): Rigid Azure Moonstone*/
(@ENTRY, '28950', '10000', '755', '300', '0'),  /* Spell(28950): Solid Azure Moonstone*/
(@ENTRY, '28953', '10000', '755', '300', '0'),  /* Spell(28953): Sparkling Azure Moonstone*/
(@ENTRY, '31048', '20000', '755', '305', '0'),  /* Spell(31048): Fel Iron Blood Ring*/
(@ENTRY, '31049', '20000', '755', '305', '0'),  /* Spell(31049): Golden Draenite Ring*/
(@ENTRY, '31050', '25000', '755', '320', '0'),  /* Spell(31050): Azure Moonstone Ring*/
(@ENTRY, '31051', '30000', '755', '335', '0'),  /* Spell(31051): Thick Adamantite Necklace*/
(@ENTRY, '31052', '30000', '755', '335', '0'),  /* Spell(31052): Heavy Adamantite Ring*/
(@ENTRY, '31252', '100', '755', '20', '0'),  /* Spell(31252): Prospecting*/
(@ENTRY, '32178', '100', '755', '20', '0'),  /* Spell(32178): Malachite Pendant*/
(@ENTRY, '32179', '100', '755', '20', '0'),  /* Spell(32179): Tigerseye Band*/
(@ENTRY, '32801', '200', '755', '50', '0'),  /* Spell(32801): Coarse Stone Statue*/
(@ENTRY, '32807', '600', '755', '110', '0'),  /* Spell(32807): Heavy Stone Statue*/
(@ENTRY, '32808', '2000', '755', '175', '0'),  /* Spell(32808): Solid Stone Statue*/
(@ENTRY, '32809', '3500', '755', '225', '0'),  /* Spell(32809): Dense Stone Statue*/
(@ENTRY, '34590', '10000', '755', '300', '0'),  /* Spell(34590): Delicate Blood Garnet*/
(@ENTRY, '34955', '2500', '755', '180', '0'),  /* Spell(34955): Golden Ring of Power*/
(@ENTRY, '34959', '3000', '755', '200', '0'),  /* Spell(34959): Truesilver Commander's Ring*/
(@ENTRY, '34960', '10000', '755', '280', '0'),  /* Spell(34960): Glowing Thorium Band*/
(@ENTRY, '34961', '10000', '755', '290', '0'),  /* Spell(34961): Emerald Lion Ring*/
(@ENTRY, '36523', '600', '755', '75', '0'),  /* Spell(36523): Brilliant Necklace*/
(@ENTRY, '36524', '800', '755', '105', '0'),  /* Spell(36524): Heavy Jade Ring*/
(@ENTRY, '36525', '4000', '755', '230', '0'),  /* Spell(36525): Red Ring of Destruction*/
(@ENTRY, '36526', '10000', '755', '265', '0'),  /* Spell(36526): Diamond Focus Ring*/
(@ENTRY, '37818', '500', '755', '65', '0'),  /* Spell(37818): Bronze Band of Force*/
(@ENTRY, '38068', '20000', '755', '325', '0'),  /* Spell(38068): Mercurial Adamantite*/
(@ENTRY, '38175', '650', '755', '80', '0'),  /* Spell(38175): Bronze Torc*/
(@ENTRY, '40514', '8500', '755', '340', '0'),  /* Spell(40514): Necklace of the Deep*/
(@ENTRY, '41414', '10000', '755', '325', '0'),  /* Spell(41414): Brilliant Pearl Band*/
(@ENTRY, '41415', '10000', '755', '330', '0'),  /* Spell(41415): The Black Pearl*/
(@ENTRY, '41418', '30000', '755', '365', '0'),  /* Spell(41418): Crown of the Sea Witch*/
(@ENTRY, '41420', '8500', '755', '325', '0'),  /* Spell(41420): Purified Jaggal Pearl*/
(@ENTRY, '41429', '10000', '755', '350', '0'),  /* Spell(41429): Purified Shadow Pearl*/
(@ENTRY, '47280', '30000', '755', '350', '0'),  /* Spell(47280): Brilliant Glass*/
(@ENTRY, '51311', '350000', '755', '350', '65'),  /* Spell(51311): Jewelcrafting*/
(@ENTRY, '53831', '10000', '755', '350', '0'),  /* Spell(53831): Bold Bloodstone*/
(@ENTRY, '53832', '10000', '755', '350', '0'),  /* Spell(53832): Delicate Bloodstone*/
(@ENTRY, '53843', '10000', '755', '350', '0'),  /* Spell(53843): Subtle Sun Crystal*/
(@ENTRY, '53844', '10000', '755', '350', '0'),  /* Spell(53844): Flashing Bloodstone*/
(@ENTRY, '53845', '10000', '755', '350', '0'),  /* Spell(53845): Smooth Sun Crystal*/
(@ENTRY, '53852', '10000', '755', '350', '0'),  /* Spell(53852): Brilliant Bloodstone*/
(@ENTRY, '53854', '10000', '755', '350', '0'),  /* Spell(53854): Rigid Chalcedony*/
(@ENTRY, '53856', '10000', '755', '350', '0'),  /* Spell(53856): Quick Sun Crystal*/
(@ENTRY, '53859', '10000', '755', '350', '0'),  /* Spell(53859): Sovereign Shadow Crystal*/
(@ENTRY, '53860', '10000', '755', '350', '0'),  /* Spell(53860): Shifting Shadow Crystal*/
(@ENTRY, '53861', '10000', '755', '350', '0'),  /* Spell(53861): Glinting Shadow Crystal*/
(@ENTRY, '53870', '10000', '755', '350', '0'),  /* Spell(53870): Jagged Dark Jade*/
(@ENTRY, '53871', '10000', '755', '350', '0'),  /* Spell(53871): Guardian's Shadow Crystal*/
(@ENTRY, '53872', '10000', '755', '350', '0'),  /* Spell(53872): Inscribed Huge Citrine*/
(@ENTRY, '53873', '10000', '755', '350', '0'),  /* Spell(53873): Etched Shadow Crystal*/
(@ENTRY, '53874', '10000', '755', '350', '0'),  /* Spell(53874): Champion's Huge Citrine*/
(@ENTRY, '53876', '10000', '755', '350', '0'),  /* Spell(53876): Fierce Huge Citrine*/
(@ENTRY, '53880', '10000', '755', '350', '0'),  /* Spell(53880): Deft Huge Citrine*/
(@ENTRY, '53882', '10000', '755', '350', '0'),  /* Spell(53882): Potent Huge Citrine*/
(@ENTRY, '53883', '10000', '755', '350', '0'),  /* Spell(53883): Veiled Shadow Crystal*/
(@ENTRY, '53891', '10000', '755', '350', '0'),  /* Spell(53891): Stalwart Huge Citrine*/
(@ENTRY, '53892', '10000', '755', '350', '0'),  /* Spell(53892): Accurate Shadow Crystal*/
(@ENTRY, '53893', '10000', '755', '350', '0'),  /* Spell(53893): Resolute Huge Citrine*/
(@ENTRY, '53894', '10000', '755', '350', '0'),  /* Spell(53894): Timeless Shadow Crystal*/
(@ENTRY, '53918', '10000', '755', '350', '0'),  /* Spell(53918): Regal Dark Jade*/
(@ENTRY, '53920', '10000', '755', '350', '0'),  /* Spell(53920): Forceful Dark Jade*/
(@ENTRY, '53922', '10000', '755', '350', '0'),  /* Spell(53922): Misty Dark Jade*/
(@ENTRY, '53923', '10000', '755', '350', '0'),  /* Spell(53923): Lightning Dark Jade*/
(@ENTRY, '53925', '10000', '755', '350', '0'),  /* Spell(53925): Energized Dark Jade*/
(@ENTRY, '53934', '10000', '755', '350', '0'),  /* Spell(53934): Solid Chalcedony*/
(@ENTRY, '53941', '10000', '755', '350', '0'),  /* Spell(53941): Sparkling Chalcedony*/
(@ENTRY, '54017', '10000', '755', '350', '0'),  /* Spell(54017): Precise Bloodstone*/
(@ENTRY, '55386', '120000', '755', '420', '0'),  /* Spell(55386): Tireless Skyflare Diamond*/
(@ENTRY, '55394', '120000', '755', '420', '0'),  /* Spell(55394): Swift Skyflare Diamond*/
(@ENTRY, '55399', '120000', '755', '420', '0'),  /* Spell(55399): Powerful Earthsiege Diamond*/
(@ENTRY, '55402', '120000', '755', '420', '0'),  /* Spell(55402): Persistent Earthsiege Diamond*/
(@ENTRY, '56193', '10000', '755', '350', '0'),  /* Spell(56193): Bloodstone Band*/
(@ENTRY, '56194', '10000', '755', '350', '0'),  /* Spell(56194): Sun Rock Ring*/
(@ENTRY, '56195', '120000', '755', '380', '0'),  /* Spell(56195): Jade Dagger Pendant*/
(@ENTRY, '56196', '80000', '755', '380', '0'),  /* Spell(56196): Blood Sun Necklace*/
(@ENTRY, '56197', '100000', '755', '420', '0'),  /* Spell(56197): Dream Signet*/
(@ENTRY, '56199', '150000', '755', '400', '0'),  /* Spell(56199): Figurine - Ruby Hare*/
(@ENTRY, '56201', '150000', '755', '400', '0'),  /* Spell(56201): Figurine - Twilight Serpent*/
(@ENTRY, '56202', '150000', '755', '400', '0'),  /* Spell(56202): Figurine - Sapphire Owl*/
(@ENTRY, '56203', '150000', '755', '400', '0'),  /* Spell(56203): Figurine - Emerald Boar*/
(@ENTRY, '56205', '10000', '755', '350', '0'),  /* Spell(56205): Dark Jade Focusing Lens*/
(@ENTRY, '56206', '10000', '755', '350', '0'),  /* Spell(56206): Shadow Crystal Focusing Lens*/
(@ENTRY, '56208', '10000', '755', '350', '0'),  /* Spell(56208): Shadow Jade Focusing Lens*/
(@ENTRY, '56530', '10000', '755', '350', '0'),  /* Spell(56530): Enchanted Pearl*/
(@ENTRY, '56531', '100000', '755', '390', '0'),  /* Spell(56531): Enchanted Tear*/
(@ENTRY, '58141', '30000', '755', '350', '0'),  /* Spell(58141): Crystal Citrine Necklace*/
(@ENTRY, '58142', '30000', '755', '350', '0'),  /* Spell(58142): Crystal Chalcedony Amulet*/
(@ENTRY, '58143', '30000', '755', '350', '0'),  /* Spell(58143): Earthshadow Ring*/
(@ENTRY, '58144', '30000', '755', '350', '0'),  /* Spell(58144): Jade Ring of Slaying*/
(@ENTRY, '58145', '50000', '755', '390', '0'),  /* Spell(58145): Stoneguard Band*/
(@ENTRY, '58146', '50000', '755', '390', '0'),  /* Spell(58146): Shadowmight Ring*/
(@ENTRY, '59759', '150000', '755', '400', '0'),  /* Spell(59759): Figurine - Monarch Crab*/
(@ENTRY, '62242', '150000', '755', '425', '0'),  /* Spell(62242): Icy Prism*/
(@ENTRY, '62941', '10000', '755', '300', '0'),  /* Spell(62941): Prismatic Black Diamond*/
(@ENTRY, '63743', '3000', '755', '200', '0'),  /* Spell(63743): Amulet of Truesight*/
(@ENTRY, '64725', '100000', '755', '420', '0'),  /* Spell(64725): Emerald Choker*/
(@ENTRY, '64726', '100000', '755', '420', '0'),  /* Spell(64726): Sky Sapphire Amulet*/
(@ENTRY, '64727', '100000', '755', '420', '0'),  /* Spell(64727): Runed Mana Band*/
(@ENTRY, '64728', '100000', '755', '420', '0'),  /* Spell(64728): Scarlet Signet*/
(@ENTRY, '73222', '30000', '755', '425', '0'),  /* Spell(73222): Bold Carnelian*/
(@ENTRY, '73223', '30000', '755', '425', '0'),  /* Spell(73223): Delicate Carnelian*/
(@ENTRY, '73225', '30000', '755', '425', '0'),  /* Spell(73225): Brilliant Carnelian*/
(@ENTRY, '73226', '30000', '755', '425', '0'),  /* Spell(73226): Precise Carnelian*/
(@ENTRY, '73227', '30000', '755', '425', '0'),  /* Spell(73227): Solid Zephyrite*/
(@ENTRY, '73228', '30000', '755', '425', '0'),  /* Spell(73228): Sparkling Zephyrite*/
(@ENTRY, '73230', '30000', '755', '425', '0'),  /* Spell(73230): Rigid Zephyrite*/
(@ENTRY, '73232', '30000', '755', '425', '0'),  /* Spell(73232): Smooth Alicite*/
(@ENTRY, '73234', '30000', '755', '425', '0'),  /* Spell(73234): Quick Alicite*/
(@ENTRY, '73239', '30000', '755', '425', '0'),  /* Spell(73239): Fractured Alicite*/
(@ENTRY, '73240', '30000', '755', '425', '0'),  /* Spell(73240): Sovereign Nightstone*/
(@ENTRY, '73241', '30000', '755', '425', '0'),  /* Spell(73241): Shifting Nightstone*/
(@ENTRY, '73243', '30000', '755', '425', '0'),  /* Spell(73243): Timeless Nightstone*/
(@ENTRY, '73246', '30000', '755', '425', '0'),  /* Spell(73246): Etched Nightstone*/
(@ENTRY, '73247', '30000', '755', '425', '0'),  /* Spell(73247): Glinting Nightstone*/
(@ENTRY, '73249', '30000', '755', '425', '0'),  /* Spell(73249): Veiled Nightstone*/
(@ENTRY, '73250', '30000', '755', '425', '0'),  /* Spell(73250): Accurate Nightstone*/
(@ENTRY, '73266', '30000', '755', '425', '0'),  /* Spell(73266): Reckless Hessonite*/
(@ENTRY, '73267', '30000', '755', '425', '0'),  /* Spell(73267): Skillful Hessonite*/
(@ENTRY, '73268', '30000', '755', '425', '0'),  /* Spell(73268): Adept Hessonite*/
(@ENTRY, '73270', '30000', '755', '425', '0'),  /* Spell(73270): Artful Hessonite*/
(@ENTRY, '73274', '30000', '755', '425', '0'),  /* Spell(73274): Jagged Jasper*/
(@ENTRY, '73279', '30000', '755', '425', '0'),  /* Spell(73279): Puissant Jasper*/
(@ENTRY, '73281', '30000', '755', '425', '0'),  /* Spell(73281): Sensei's Jasper*/
(@ENTRY, '73318', '500000', '755', '425', '75'),  /* Spell(73318): Jewelcrafting*/
(@ENTRY, '73478', '30000', '755', '500', '0'),  /* Spell(73478): Fire Prism*/
(@ENTRY, '73494', '30000', '755', '425', '0'),  /* Spell(73494): Jasper Ring*/
(@ENTRY, '73495', '30000', '755', '450', '0'),  /* Spell(73495): Hessonite Band*/
(@ENTRY, '73496', '30000', '755', '435', '0'),  /* Spell(73496): Alicite Pendant*/
(@ENTRY, '73497', '30000', '755', '460', '0'),  /* Spell(73497): Nightstone Choker*/
(@ENTRY, '73620', '30000', '755', '460', '0'),  /* Spell(73620): Carnelian Spikes*/
(@ENTRY, '73621', '30000', '755', '490', '0'),  /* Spell(73621): The Perforator*/
(@ENTRY, '73622', '30000', '755', '435', '0'),  /* Spell(73622): Stardust*/
(@ENTRY, '99539', '40000', '755', '510', '0'),  /* Spell(99539): Vicious Sapphire Ring*/
(@ENTRY, '99540', '40000', '755', '510', '0'),  /* Spell(99540): Vicious Amberjewel Band*/
(@ENTRY, '99541', '40000', '755', '510', '0'),  /* Spell(99541): Vicious Ruby Signet*/
(@ENTRY, '99542', '45000', '755', '520', '0'),  /* Spell(99542): Vicious Sapphire Necklace*/
(@ENTRY, '99543', '45000', '755', '520', '0'),  /* Spell(99543): Vicious Amberjewel Pendant*/
(@ENTRY, '99544', '45000', '755', '520', '0'),  /* Spell(99544): Vicious Ruby Choker*/
(@ENTRY, '107598', '45714', '755', '550', '0'),  /* Spell(107598): Balanced Alexandrite*/
(@ENTRY, '107599', '45714', '755', '550', '0'),  /* Spell(107599): Effulgent Alexandrite*/
(@ENTRY, '107600', '45714', '755', '560', '0'),  /* Spell(107600): Energized Alexandrite*/
(@ENTRY, '107601', '45714', '755', '565', '0'),  /* Spell(107601): Forceful Alexandrite*/
(@ENTRY, '107602', '45714', '755', '530', '0'),  /* Spell(107602): Jagged Alexandrite*/
(@ENTRY, '107604', '45714', '755', '525', '0'),  /* Spell(107604): Lightning Alexandrite*/
(@ENTRY, '107605', '45714', '755', '540', '0'),  /* Spell(107605): Misty Alexandrite*/
(@ENTRY, '107606', '45714', '755', '530', '0'),  /* Spell(107606): Nimble Alexandrite*/
(@ENTRY, '107607', '45714', '755', '555', '0'),  /* Spell(107607): Piercing Alexandrite*/
(@ENTRY, '107608', '45714', '755', '570', '0'),  /* Spell(107608): Puissant Alexandrite*/
(@ENTRY, '107609', '45714', '755', '575', '0'),  /* Spell(107609): Radiant Alexandrite*/
(@ENTRY, '107610', '45714', '755', '535', '0'),  /* Spell(107610): Regal Alexandrite*/
(@ENTRY, '107611', '45714', '755', '545', '0'),  /* Spell(107611): Sensei's Alexandrite*/
(@ENTRY, '107612', '45714', '755', '540', '0'),  /* Spell(107612): Shattered Alexandrite*/
(@ENTRY, '107613', '45714', '755', '555', '0'),  /* Spell(107613): Steady Alexandrite*/
(@ENTRY, '107614', '45714', '755', '545', '0'),  /* Spell(107614): Turbid Alexandrite*/
(@ENTRY, '107615', '45714', '755', '525', '0'),  /* Spell(107615): Vivid Alexandrite*/
(@ENTRY, '107616', '45714', '755', '535', '0'),  /* Spell(107616): Zen Alexandrite*/
(@ENTRY, '107617', '45714', '755', '525', '0'),  /* Spell(107617): Rigid Lapis Lazuli*/
(@ENTRY, '107619', '45714', '755', '535', '0'),  /* Spell(107619): Solid Lapis Lazuli*/
(@ENTRY, '107620', '45714', '755', '545', '0'),  /* Spell(107620): Sparkling Lapis Lazuli*/
(@ENTRY, '107621', '45714', '755', '555', '0'),  /* Spell(107621): Stormy Lapis Lazuli*/
(@ENTRY, '107622', '45714', '755', '570', '0'),  /* Spell(107622): Bold Pandarian Garnet*/
(@ENTRY, '107623', '45714', '755', '560', '0'),  /* Spell(107623): Brilliant Pandarian Garnet*/
(@ENTRY, '107624', '45714', '755', '530', '0'),  /* Spell(107624): Delicate Pandarian Garnet*/
(@ENTRY, '107625', '45714', '755', '550', '0'),  /* Spell(107625): Flashing Pandarian Garnet*/
(@ENTRY, '107626', '45714', '755', '540', '0'),  /* Spell(107626): Precise Pandarian Garnet*/
(@ENTRY, '107627', '45714', '755', '550', '0'),  /* Spell(107627): Accurate Roguestone*/
(@ENTRY, '107628', '45714', '755', '555', '0'),  /* Spell(107628): Defender's Roguestone*/
(@ENTRY, '107630', '45714', '755', '525', '0'),  /* Spell(107630): Etched Roguestone*/
(@ENTRY, '107631', '45714', '755', '540', '0'),  /* Spell(107631): Glinting Roguestone*/
(@ENTRY, '107632', '45714', '755', '545', '0'),  /* Spell(107632): Guardian's Roguestone*/
(@ENTRY, '107633', '45714', '755', '525', '0'),  /* Spell(107633): Mysterious Roguestone*/
(@ENTRY, '107634', '45714', '755', '565', '0'),  /* Spell(107634): Purified Roguestone*/
(@ENTRY, '107635', '45714', '755', '575', '0'),  /* Spell(107635): Retaliating Roguestone*/
(@ENTRY, '107636', '45714', '755', '535', '0'),  /* Spell(107636): Shifting Roguestone*/
(@ENTRY, '107637', '45714', '755', '535', '0'),  /* Spell(107637): Sovereign Roguestone*/
(@ENTRY, '107638', '45714', '755', '560', '0'),  /* Spell(107638): Timeless Roguestone*/
(@ENTRY, '107639', '45714', '755', '530', '0'),  /* Spell(107639): Veiled Roguestone*/
(@ENTRY, '107640', '45714', '755', '535', '0'),  /* Spell(107640): Fractured Sunstone*/
(@ENTRY, '107641', '45714', '755', '545', '0'),  /* Spell(107641): Mystic Sunstone*/
(@ENTRY, '107642', '45714', '755', '555', '0'),  /* Spell(107642): Quick Sunstone*/
(@ENTRY, '107643', '45714', '755', '565', '0'),  /* Spell(107643): Smooth Sunstone*/
(@ENTRY, '107644', '45714', '755', '575', '0'),  /* Spell(107644): Subtle Sunstone*/
(@ENTRY, '107645', '45714', '755', '550', '0'),  /* Spell(107645): Adept Tiger Opal*/
(@ENTRY, '107646', '45714', '755', '525', '0'),  /* Spell(107646): Artful Tiger Opal*/
(@ENTRY, '107647', '45714', '755', '545', '0'),  /* Spell(107647): Champion's Tiger Opal*/
(@ENTRY, '107648', '45714', '755', '565', '0'),  /* Spell(107648): Crafty Tiger Opal*/
(@ENTRY, '107649', '45714', '755', '525', '0'),  /* Spell(107649): Deadly Tiger Opal*/
(@ENTRY, '107650', '45714', '755', '530', '0'),  /* Spell(107650): Deft Tiger Opal*/
(@ENTRY, '107651', '45714', '755', '555', '0'),  /* Spell(107651): Fierce Tiger Opal*/
(@ENTRY, '107652', '45714', '755', '535', '0'),  /* Spell(107652): Fine Tiger Opal*/
(@ENTRY, '107653', '45714', '755', '555', '0'),  /* Spell(107653): Inscribed Tiger Opal*/
(@ENTRY, '107654', '45714', '755', '530', '0'),  /* Spell(107654): Keen Tiger Opal*/
(@ENTRY, '107655', '45714', '755', '540', '0'),  /* Spell(107655): Lucent Tiger Opal*/
(@ENTRY, '107656', '45714', '755', '545', '0'),  /* Spell(107656): Polished Tiger Opal*/
(@ENTRY, '107657', '45714', '755', '560', '0'),  /* Spell(107657): Potent Tiger Opal*/
(@ENTRY, '107658', '45714', '755', '540', '0'),  /* Spell(107658): Reckless Tiger Opal*/
(@ENTRY, '107659', '45714', '755', '575', '0'),  /* Spell(107659): Resolute Tiger Opal*/
(@ENTRY, '107660', '45714', '755', '575', '0'),  /* Spell(107660): Resplendent Tiger Opal*/
(@ENTRY, '107661', '45714', '755', '560', '0'),  /* Spell(107661): Skillful Tiger Opal*/
(@ENTRY, '107662', '45714', '755', '570', '0'),  /* Spell(107662): Splendid Tiger Opal*/
(@ENTRY, '107663', '45714', '755', '565', '0'),  /* Spell(107663): Stalwart Tiger Opal*/
(@ENTRY, '107665', '45714', '755', '550', '0'),  /* Spell(107665): Tenuous Tiger Opal*/
(@ENTRY, '107666', '45714', '755', '570', '0'),  /* Spell(107666): Wicked Tiger Opal*/
(@ENTRY, '107667', '45714', '755', '535', '0'),  /* Spell(107667): Willful Tiger Opal*/
(@ENTRY, '110420', '685714', '755', '500', '80'),  /* Spell(110420): Jewelcrafting*/
(@ENTRY, '122661', '45714', '755', '500', '0'),  /* Spell(122661): Ornate Band*/
(@ENTRY, '122662', '45714', '755', '510', '0'),  /* Spell(122662): Shadowfire Necklace*/
(@ENTRY, '122663', '45714', '755', '525', '0'),  /* Spell(122663): Scrying Roguestone*/
(@ENTRY, '130655', '45714', '755', '570', '0'),  /* Spell(130655): Tense Roguestone*/
(@ENTRY, '130656', '45714', '755', '530', '0'),  /* Spell(130656): Assassin's Roguestone*/
(@ENTRY, '131593', '45714', '755', '525', '0'),  /* Spell(131593): River's Heart*/
(@ENTRY, '131686', '45714', '755', '550', '0'),  /* Spell(131686): Primordial Ruby*/
(@ENTRY, '131688', '45714', '755', '535', '0'),  /* Spell(131688): Wild Jade*/
(@ENTRY, '131690', '45714', '755', '535', '0'),  /* Spell(131690): Vermilion Onyx*/
(@ENTRY, '131691', '45714', '755', '545', '0'),  /* Spell(131691): Imperial Amethyst*/
(@ENTRY, '131695', '45714', '755', '525', '0'),  /* Spell(131695): Sun's Radiance*/
(@ENTRY, '131759', '45714', '755', '550', '0');  /* Spell(131759): Secrets of the Stone*/


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

