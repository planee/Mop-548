/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 28/1/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Lien Farner';
SET @ENTRY 		:= '47384';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '35576', '0', '0', '0', @CREATURE, 'Profession Trainer', '', '12188', '10', '10', '0', '0', '35', '35', '81', '0', '1', '1.14286', '0', '1.14286', '1', '0', '10', '15', '0', '4', '1', '2000', '2000', '1', '0', '2048', '0', '0', '2', '0', '0', '0', '8', '12', '3', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '', '16048');

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES 
(@ENTRY, '0', '0', '0', '1', '0', ''); 


/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('35576', '0.306', '1.5', '0', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 47384 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '0', '12', '87', '1', '1', '0', '0', '-9494.04', '79.2656', '56.2886', '0.925025', '120', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-9494.04' AND `position_y` REGEXP '79.2656' AND `position_z` REGEXP '56.2886' AND `phaseMask` = '1' AND `map` = '0');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-9494.04' AND `position_y` REGEXP '79.2656' AND `position_z` REGEXP '56.2886' AND `phaseMask` = '1' AND `map` = '0');
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
DELETE FROM gossip_menu WHERE  `entry` = 12188;
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES 
(12188, 17128); 
/* Step 4.6 Table  `npc_text` */
DELETE FROM npc_text WHERE `ID` = 17128;
INSERT INTO `npc_text` (`ID`,`text0_0`,`text0_1`,`lang0`,`prob0`,`em0_0`,`em0_1`,`em0_2`,`em0_3`,`em0_4`,`em0_5`,`text1_0`,`text1_1`,`lang1`,`prob1`,`em1_0`,`em1_1`,`em1_2`,`em1_3`,`em1_4`,`em1_5`,`text2_0`,`text2_1`,`lang2`,`prob2`,`em2_0`,`em2_1`,`em2_2`,`em2_3`,`em2_4`,`em2_5`,`text3_0`,`text3_1`,`lang3`,`prob3`,`em3_0`,`em3_1`,`em3_2`,`em3_3`,`em3_4`,`em3_5`,`text4_0`,`text4_1`,`lang4`,`prob4`,`em4_0`,`em4_1`,`em4_2`,`em4_3`,`em4_4`,`em4_5`,`text5_0`,`text5_1`,`lang5`,`prob5`,`em5_0`,`em5_1`,`em5_2`,`em5_3`,`em5_4`,`em5_5`,`text6_0`,`text6_1`,`lang6`,`prob6`,`em6_0`,`em6_1`,`em6_2`,`em6_3`,`em6_4`,`em6_5`,`text7_0`,`text7_1`,`lang7`,`prob7`,`em7_0`,`em7_1`,`em7_2`,`em7_3`,`em7_4`,`em7_5`,`WDBVerified`) VALUES 
('17128', 'Herbalism allows you to locate and gather herbs from the wild. These can be sold at the auction house or used to support the Alchemy or Inscription professions.

Skilled herbalists can also use their knowledge of the earth to heal themselves.', 'Herbalism allows you to locate and gather herbs from the wild. These can be sold at the auction house or used to support the Alchemy or Inscription professions.

Skilled herbalists can also use their knowledge of the earth to heal themselves.', '0', '1', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '15595'); 




/* Step 2.7 Table  `gossip_menu_option */
DELETE FROM gossip_menu_option WHERE  `menu_id` = 12188;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
('12188', '11', '3', 'Train me in Herbalism.', '5', '16', '0', '0', '0', '0', '');
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
('12188', '12', '0', 'Tell me about Alchemy.', '0', '0', '0', '0', '0', '0', '');
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
('12188', '13', '0', 'Tell me about Inscription.', '0', '0', '0', '0', '0', '0', '');
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
('12188', '14', '0', 'Tell me about gathering professions.', '0', '0', '0', '0', '0', '0', '');
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
('12188', '15', '0', 'Tell me about production professions.', '0', '0', '0', '0', '0', '0', '');


/*## Step 5: Creature NPC Trainer / Vendor ############################*/

/* Step 2.0 Table  `npc_trainer */
DELETE FROM npc_trainer WHERE `entry` = @ENTRY;
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES 
(@ENTRY, '2020', '10', '0', '0', '0'),  /* Spell(2020): Apprentice Blacksmith*/
(@ENTRY, '2153', '50', '165', '15', '0'),  /* Spell(2153): Handstitched Leather Pants*/
(@ENTRY, '2155', '10', '0', '0', '0'),  /* Spell(2155): Apprentice Leatherworker*/
(@ENTRY, '2160', '100', '165', '40', '0'),  /* Spell(2160): Embossed Leather Vest*/
(@ENTRY, '2161', '100', '165', '55', '0'),  /* Spell(2161): Embossed Leather Boots*/
(@ENTRY, '2162', '100', '165', '60', '0'),  /* Spell(2162): Embossed Leather Cloak*/
(@ENTRY, '2275', '10', '0', '0', '5'),  /* Spell(2275): Apprentice Alchemist*/
(@ENTRY, '2331', '100', '171', '25', '0'),  /* Spell(2331): Minor Mana Potion*/
(@ENTRY, '2332', '150', '171', '40', '0'),  /* Spell(2332): Minor Rejuvenation Potion*/
(@ENTRY, '2334', '250', '171', '50', '0'),  /* Spell(2334): Elixir of Minor Fortitude*/
(@ENTRY, '2337', '1000', '171', '55', '0'),  /* Spell(2337): Lesser Healing Potion*/
(@ENTRY, '2372', '10', '0', '0', '0'),  /* Spell(2372): Apprentice Herbalist*/
(@ENTRY, '2385', '50', '197', '10', '0'),  /* Spell(2385): Brown Linen Vest*/
(@ENTRY, '2386', '200', '197', '65', '0'),  /* Spell(2386): Linen Boots*/
(@ENTRY, '2392', '50', '197', '40', '0'),  /* Spell(2392): Red Linen Shirt*/
(@ENTRY, '2393', '25', '197', '1', '0'),  /* Spell(2393): White Linen Shirt*/
(@ENTRY, '2394', '50', '197', '40', '0'),  /* Spell(2394): Blue Linen Shirt*/
(@ENTRY, '2395', '300', '197', '70', '0'),  /* Spell(2395): Barbaric Linen Vest*/
(@ENTRY, '2396', '200', '197', '70', '0'),  /* Spell(2396): Green Linen Shirt*/
(@ENTRY, '2397', '200', '197', '60', '0'),  /* Spell(2397): Reinforced Linen Cape*/
(@ENTRY, '2402', '250', '197', '75', '0'),  /* Spell(2402): Woolen Cape*/
(@ENTRY, '2581', '10', '0', '0', '0'),  /* Spell(2581): Apprentice Miner*/
(@ENTRY, '2658', '200', '186', '65', '0'),  /* Spell(2658): Smelt Silver*/
(@ENTRY, '2659', '200', '186', '50', '0'),  /* Spell(2659): Smelt Bronze*/
(@ENTRY, '2661', '100', '164', '35', '0'),  /* Spell(2661): Copper Chain Belt*/
(@ENTRY, '2662', '50', '164', '1', '0'),  /* Spell(2662): Copper Chain Pants*/
(@ENTRY, '2665', '100', '164', '65', '0'),  /* Spell(2665): Coarse Sharpening Stone*/
(@ENTRY, '2666', '200', '164', '70', '0'),  /* Spell(2666): Runed Copper Belt*/
(@ENTRY, '2737', '50', '164', '15', '0'),  /* Spell(2737): Copper Mace*/
(@ENTRY, '2738', '50', '164', '20', '0'),  /* Spell(2738): Copper Axe*/
(@ENTRY, '2739', '50', '164', '25', '0'),  /* Spell(2739): Copper Shortsword*/
(@ENTRY, '2964', '100', '197', '75', '0'),  /* Spell(2964): Bolt of Woolen Cloth*/
(@ENTRY, '3116', '100', '164', '65', '0'),  /* Spell(3116): Coarse Weightstone*/
(@ENTRY, '3170', '50', '171', '15', '0'),  /* Spell(3170): Weak Troll's Blood Elixir*/
(@ENTRY, '3293', '250', '164', '35', '0'),  /* Spell(3293): Copper Battle Axe*/
(@ENTRY, '3294', '500', '164', '70', '0'),  /* Spell(3294): Thick War Axe*/
(@ENTRY, '3304', '50', '186', '50', '0'),  /* Spell(3304): Smelt Tin*/
(@ENTRY, '3319', '50', '164', '20', '0'),  /* Spell(3319): Copper Chain Boots*/
(@ENTRY, '3320', '100', '164', '25', '0'),  /* Spell(3320): Rough Grinding Stone*/
(@ENTRY, '3323', '100', '164', '40', '0'),  /* Spell(3323): Runed Copper Gauntlets*/
(@ENTRY, '3324', '200', '164', '45', '0'),  /* Spell(3324): Runed Copper Pants*/
(@ENTRY, '3326', '250', '164', '75', '0'),  /* Spell(3326): Coarse Grinding Stone*/
(@ENTRY, '3753', '75', '165', '25', '0'),  /* Spell(3753): Handstitched Leather Belt*/
(@ENTRY, '3755', '100', '197', '45', '0'),  /* Spell(3755): Linen Bag*/
(@ENTRY, '3756', '150', '165', '55', '0'),  /* Spell(3756): Embossed Leather Gloves*/
(@ENTRY, '3759', '200', '165', '75', '0'),  /* Spell(3759): Embossed Leather Pants*/
(@ENTRY, '3816', '50', '165', '35', '0'),  /* Spell(3816): Cured Light Hide*/
(@ENTRY, '3840', '100', '197', '35', '0'),  /* Spell(3840): Heavy Linen Gloves*/
(@ENTRY, '3841', '200', '197', '60', '0'),  /* Spell(3841): Green Linen Bracers*/
(@ENTRY, '3842', '300', '197', '70', '0'),  /* Spell(3842): Handstitched Linen Britches*/
(@ENTRY, '3911', '10', '0', '0', '0'),  /* Spell(3911): Apprentice Tailor*/
(@ENTRY, '3914', '50', '197', '30', '0'),  /* Spell(3914): Brown Linen Pants*/
(@ENTRY, '3922', '115', '202', '30', '0'),  /* Spell(3922): Handful of Copper Bolts*/
(@ENTRY, '3923', '130', '202', '30', '0'),  /* Spell(3923): Rough Copper Bomb*/
(@ENTRY, '3925', '150', '202', '50', '0'),  /* Spell(3925): Rough Boomstick*/
(@ENTRY, '3929', '250', '202', '65', '0'),  /* Spell(3929): Coarse Blasting Powder*/
(@ENTRY, '3931', '250', '202', '65', '0'),  /* Spell(3931): Coarse Dynamite*/
(@ENTRY, '3977', '200', '202', '60', '0'),  /* Spell(3977): Crude Scope*/
(@ENTRY, '4039', '10', '0', '0', '0'),  /* Spell(4039): Apprentice Engineer*/
(@ENTRY, '7408', '300', '164', '65', '0'),  /* Spell(7408): Heavy Copper Maul*/
(@ENTRY, '7414', '10', '0', '0', '0'),  /* Spell(7414): Apprentice Enchanter*/
(@ENTRY, '7420', '50', '333', '15', '0'),  /* Spell(7420): Enchant Chest - Minor Health*/
(@ENTRY, '7426', '100', '333', '40', '0'),  /* Spell(7426): Enchant Chest - Minor Absorption*/
(@ENTRY, '7430', '150', '202', '50', '0'),  /* Spell(7430): Arclight Spanner*/
(@ENTRY, '7457', '250', '333', '50', '0'),  /* Spell(7457): Enchant Bracer - Minor Stamina*/
(@ENTRY, '7623', '50', '197', '30', '0'),  /* Spell(7623): Brown Linen Robe*/
(@ENTRY, '7624', '50', '197', '30', '0'),  /* Spell(7624): White Linen Robe*/
(@ENTRY, '7748', '250', '333', '60', '0'),  /* Spell(7748): Enchant Chest - Lesser Health*/
(@ENTRY, '7771', '200', '333', '70', '0'),  /* Spell(7771): Enchant Cloak - Minor Protection*/
(@ENTRY, '8465', '50', '197', '40', '0'),  /* Spell(8465): Simple Dress*/
(@ENTRY, '8615', '10', '0', '0', '0'),  /* Spell(8615): Apprentice Skinner*/
(@ENTRY, '8776', '50', '197', '15', '0'),  /* Spell(8776): Linen Belt*/
(@ENTRY, '8880', '100', '164', '30', '0'),  /* Spell(8880): Copper Dagger*/
(@ENTRY, '9065', '150', '165', '70', '0'),  /* Spell(9065): Light Leather Bracers*/
(@ENTRY, '9983', '100', '164', '30', '0'),  /* Spell(9983): Copper Claymore*/
(@ENTRY, '12045', '50', '197', '20', '0'),  /* Spell(12045): Simple Linen Boots*/
(@ENTRY, '12046', '300', '197', '75', '0'),  /* Spell(12046): Simple Kilt*/
(@ENTRY, '14293', '50', '333', '10', '0'),  /* Spell(14293): Lesser Magic Wand*/
(@ENTRY, '14807', '200', '333', '70', '0'),  /* Spell(14807): Greater Magic Wand*/
(@ENTRY, '25245', '10', '0', '0', '0'),  /* Spell(25245): Apprentice Jewelcrafter*/
(@ENTRY, '25278', '200', '755', '50', '0'),  /* Spell(25278): Bronze Setting*/
(@ENTRY, '25280', '200', '755', '50', '0'),  /* Spell(25280): Elegant Silver Ring*/
(@ENTRY, '25283', '100', '755', '30', '0'),  /* Spell(25283): Inlaid Malachite Ring*/
(@ENTRY, '25284', '400', '755', '60', '0'),  /* Spell(25284): Simple Pearl Ring*/
(@ENTRY, '25287', '400', '755', '70', '0'),  /* Spell(25287): Gloom Band*/
(@ENTRY, '25490', '300', '755', '50', '0'),  /* Spell(25490): Solid Bronze Ring*/
(@ENTRY, '26926', '50', '755', '5', '0'),  /* Spell(26926): Heavy Copper Ring*/
(@ENTRY, '26927', '300', '755', '50', '0'),  /* Spell(26927): Thick Bronze Necklace*/
(@ENTRY, '26928', '100', '755', '30', '0'),  /* Spell(26928): Ornate Tigerseye Necklace*/
(@ENTRY, '31252', '100', '755', '20', '0'),  /* Spell(31252): Prospecting*/
(@ENTRY, '32178', '100', '755', '20', '0'),  /* Spell(32178): Malachite Pendant*/
(@ENTRY, '32179', '100', '755', '20', '0'),  /* Spell(32179): Tigerseye Band*/
(@ENTRY, '32801', '200', '755', '50', '0'),  /* Spell(32801): Coarse Stone Statue*/
(@ENTRY, '36523', '600', '755', '75', '0'),  /* Spell(36523): Brilliant Necklace*/
(@ENTRY, '37818', '500', '755', '65', '0'),  /* Spell(37818): Bronze Band of Force*/
(@ENTRY, '45375', '10', '0', '0', '0'),  /* Spell(45375): Apprentice Scribe*/
(@ENTRY, '48248', '50', '773', '35', '0'),  /* Spell(48248): Scroll of Recall*/
(@ENTRY, '50598', '400', '773', '75', '0'),  /* Spell(50598): Scroll of Intellect II*/
(@ENTRY, '50605', '400', '773', '75', '0'),  /* Spell(50605): Scroll of Spirit II*/
(@ENTRY, '50612', '400', '773', '75', '0'),  /* Spell(50612): Scroll of Stamina II*/
(@ENTRY, '52739', '150', '773', '35', '0'),  /* Spell(52739): Enchanting Vellum*/
(@ENTRY, '52843', '50', '773', '35', '0'),  /* Spell(52843): Moonglow Ink*/
(@ENTRY, '53462', '300', '773', '75', '0'),  /* Spell(53462): Midnight Ink*/
(@ENTRY, '58472', '50', '773', '15', '0'),  /* Spell(58472): Scroll of Agility*/
(@ENTRY, '58484', '50', '773', '15', '0'),  /* Spell(58484): Scroll of Strength*/
(@ENTRY, '61288', '1000', '773', '75', '0');  /* Spell(61288): Minor Inscription Research*/


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

