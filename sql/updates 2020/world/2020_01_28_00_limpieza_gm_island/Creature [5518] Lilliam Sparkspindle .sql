/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 28/1/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Lilliam Sparkspindle';
SET @ENTRY 		:= '5518';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '3314', '0', '0', '0', @CREATURE, 'Engineering Trainer', '', '4146', '35', '35', '0', '0', '35', '35', '83', '0', '1', '1.14286', '0', '1.14286', '1', '0', '49', '64', '0', '118', '1', '2000', '2000', '1', '512', '2048', '0', '0', '2', '0', '0', '0', '33', '49', '11', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1.1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '5518', '0', '2', '', '16048');

/* Step 1.2 Table `creature_equip_template */
DELETE FROM `creature_equip_template` WHERE `entry`= 5518;
INSERT INTO `creature_equip_template` (`entry`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES 
('5518', '4994', '0', '0'); /* [ItemEntry1(4994): Monster - Item, Gizmo] */

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES 
(@ENTRY, '0', '0', '0', '257', '0', ''); 


/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('3314', '0.3519', '1.725', '0', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 5518 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '0', '1519', '5150', '1', '1', '0', '0', '-8366.05', '630.964', '95.2242', '2.84489', '120', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-8366.05' AND `position_y` REGEXP '630.964' AND `position_z` REGEXP '95.2242' AND `phaseMask` = '1' AND `map` = '0');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-8366.05' AND `position_y` REGEXP '630.964' AND `position_z` REGEXP '95.2242' AND `phaseMask` = '1' AND `map` = '0');
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
DELETE FROM gossip_menu WHERE  `entry` = 4146;
INSERT INTO `gossip_menu` (`entry`,`text_id`) VALUES 
(4146, 5147); 
/* Step 4.6 Table  `npc_text` */
DELETE FROM npc_text WHERE `ID` = 5147;
INSERT INTO `npc_text` (`ID`,`text0_0`,`text0_1`,`lang0`,`prob0`,`em0_0`,`em0_1`,`em0_2`,`em0_3`,`em0_4`,`em0_5`,`text1_0`,`text1_1`,`lang1`,`prob1`,`em1_0`,`em1_1`,`em1_2`,`em1_3`,`em1_4`,`em1_5`,`text2_0`,`text2_1`,`lang2`,`prob2`,`em2_0`,`em2_1`,`em2_2`,`em2_3`,`em2_4`,`em2_5`,`text3_0`,`text3_1`,`lang3`,`prob3`,`em3_0`,`em3_1`,`em3_2`,`em3_3`,`em3_4`,`em3_5`,`text4_0`,`text4_1`,`lang4`,`prob4`,`em4_0`,`em4_1`,`em4_2`,`em4_3`,`em4_4`,`em4_5`,`text5_0`,`text5_1`,`lang5`,`prob5`,`em5_0`,`em5_1`,`em5_2`,`em5_3`,`em5_4`,`em5_5`,`text6_0`,`text6_1`,`lang6`,`prob6`,`em6_0`,`em6_1`,`em6_2`,`em6_3`,`em6_4`,`em6_5`,`text7_0`,`text7_1`,`lang7`,`prob7`,`em7_0`,`em7_1`,`em7_2`,`em7_3`,`em7_4`,`em7_5`,`WDBVerified`) VALUES 
('5147', 'Let\'s see... fourteen plus seven, carry the two... oh, yes?', '', '0', '1', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '12340'); 




/* Step 2.7 Table  `gossip_menu_option */
DELETE FROM gossip_menu_option WHERE  `menu_id` = 4146;
INSERT INTO `gossip_menu_option` (`menu_id`, `id`, `option_icon`, `option_text`, `option_id`, `npc_option_npcflag`, `action_menu_id`, `action_poi_id`, `box_coded`, `box_money`, `box_text`) VALUES 
('4146', '0', '3', 'Train me.', '5', '16', '0', '0', '0', '0', '');


/*## Step 5: Creature NPC Trainer / Vendor ############################*/

/* Step 2.0 Table  `npc_trainer */
DELETE FROM npc_trainer WHERE `entry` = @ENTRY;
INSERT INTO `npc_trainer` (`entry`, `spell`, `spellcost`, `reqskill`, `reqskillvalue`, `reqlevel`) VALUES 
(@ENTRY, '3922', '115', '202', '30', '0'),  /* Spell(3922): Handful of Copper Bolts*/
(@ENTRY, '3923', '130', '202', '30', '0'),  /* Spell(3923): Rough Copper Bomb*/
(@ENTRY, '3925', '150', '202', '50', '0'),  /* Spell(3925): Rough Boomstick*/
(@ENTRY, '3929', '250', '202', '65', '0'),  /* Spell(3929): Coarse Blasting Powder*/
(@ENTRY, '3931', '250', '202', '65', '0'),  /* Spell(3931): Coarse Dynamite*/
(@ENTRY, '3932', '300', '202', '85', '0'),  /* Spell(3932): Target Dummy*/
(@ENTRY, '3934', '400', '202', '100', '0'),  /* Spell(3934): Flying Tiger Goggles*/
(@ENTRY, '3936', '420', '202', '105', '0'),  /* Spell(3936): Deadly Blunderbuss*/
(@ENTRY, '3937', '450', '202', '105', '0'),  /* Spell(3937): Large Copper Bomb*/
(@ENTRY, '3938', '450', '202', '105', '0'),  /* Spell(3938): Bronze Tube*/
(@ENTRY, '3939', '500', '202', '120', '0'),  /* Spell(3939): Lovingly Crafted Boomstick*/
(@ENTRY, '3941', '500', '202', '120', '0'),  /* Spell(3941): Small Bronze Bomb*/
(@ENTRY, '3942', '500', '202', '125', '0'),  /* Spell(3942): Whirring Bronze Gizmo*/
(@ENTRY, '3945', '500', '202', '125', '0'),  /* Spell(3945): Heavy Blasting Powder*/
(@ENTRY, '3946', '500', '202', '125', '0'),  /* Spell(3946): Heavy Dynamite*/
(@ENTRY, '3949', '550', '202', '130', '0'),  /* Spell(3949): Silver-plated Shotgun*/
(@ENTRY, '3950', '600', '202', '140', '0'),  /* Spell(3950): Big Bronze Bomb*/
(@ENTRY, '3953', '600', '202', '145', '0'),  /* Spell(3953): Bronze Framework*/
(@ENTRY, '3955', '750', '202', '150', '0'),  /* Spell(3955): Explosive Sheep*/
(@ENTRY, '3956', '750', '202', '150', '0'),  /* Spell(3956): Green Tinted Goggles*/
(@ENTRY, '3958', '800', '202', '160', '0'),  /* Spell(3958): Iron Strut*/
(@ENTRY, '3961', '900', '202', '170', '0'),  /* Spell(3961): Gyrochronatom*/
(@ENTRY, '3962', '1000', '202', '175', '0'),  /* Spell(3962): Iron Grenade*/
(@ENTRY, '3963', '1000', '202', '175', '0'),  /* Spell(3963): Compact Harvest Reaper Kit*/
(@ENTRY, '3965', '1200', '202', '185', '0'),  /* Spell(3965): Advanced Target Dummy*/
(@ENTRY, '3967', '1400', '202', '190', '0'),  /* Spell(3967): Big Iron Bomb*/
(@ENTRY, '3973', '300', '202', '90', '0'),  /* Spell(3973): Silver Contact*/
(@ENTRY, '3977', '200', '202', '60', '0'),  /* Spell(3977): Crude Scope*/
(@ENTRY, '3978', '475', '202', '110', '0'),  /* Spell(3978): Standard Scope*/
(@ENTRY, '3979', '1200', '202', '180', '0'),  /* Spell(3979): Accurate Scope*/
(@ENTRY, '4036', '10', '202', '0', '5'),  /* Spell(4036): Engineering*/
(@ENTRY, '4037', '500', '202', '50', '10'),  /* Spell(4037): Engineering*/
(@ENTRY, '4038', '5000', '202', '125', '25'),  /* Spell(4038): Engineering*/
(@ENTRY, '6458', '400', '202', '135', '0'),  /* Spell(6458): Ornate Spyglass*/
(@ENTRY, '7430', '150', '202', '50', '0'),  /* Spell(7430): Arclight Spanner*/
(@ENTRY, '8334', '300', '202', '100', '0'),  /* Spell(8334): Clockwork Box*/
(@ENTRY, '8895', '2200', '202', '225', '0'),  /* Spell(8895): Goblin Rocket Boots*/
(@ENTRY, '9271', '500', '202', '150', '0'),  /* Spell(9271): Aquadynamic Fish Attractor*/
(@ENTRY, '12584', '1000', '202', '150', '0'),  /* Spell(12584): Gold Power Core*/
(@ENTRY, '12585', '1000', '202', '175', '0'),  /* Spell(12585): Solid Blasting Powder*/
(@ENTRY, '12586', '1000', '202', '175', '0'),  /* Spell(12586): Solid Dynamite*/
(@ENTRY, '12589', '1300', '202', '195', '0'),  /* Spell(12589): Mithril Tube*/
(@ENTRY, '12590', '1000', '202', '175', '0'),  /* Spell(12590): Gyromatic Micro-Adjustor*/
(@ENTRY, '12591', '1500', '202', '200', '0'),  /* Spell(12591): Unstable Trigger*/
(@ENTRY, '12594', '1600', '202', '205', '0'),  /* Spell(12594): Fire Goggles*/
(@ENTRY, '12595', '1600', '202', '205', '0'),  /* Spell(12595): Mithril Blunderbuss*/
(@ENTRY, '12599', '1800', '202', '215', '0'),  /* Spell(12599): Mithril Casing*/
(@ENTRY, '12603', '1800', '202', '215', '0'),  /* Spell(12603): Mithril Frag Bomb*/
(@ENTRY, '12615', '2500', '202', '225', '0'),  /* Spell(12615): Spellpower Goggles Xtreme*/
(@ENTRY, '12617', '2200', '202', '230', '0'),  /* Spell(12617): Deepdive Helmet*/
(@ENTRY, '12618', '2200', '202', '230', '0'),  /* Spell(12618): Rose Colored Goggles*/
(@ENTRY, '12619', '2400', '202', '235', '0'),  /* Spell(12619): Hi-Explosive Bomb*/
(@ENTRY, '12622', '2800', '202', '245', '0'),  /* Spell(12622): Green Lens*/
(@ENTRY, '12656', '50000', '202', '200', '35'),  /* Spell(12656): Engineering*/
(@ENTRY, '12715', '1000', '202', '205', '0'),  /* Spell(12715): Goblin Rocket Fuel Recipe*/
(@ENTRY, '12716', '1500', '202', '205', '0'),  /* Spell(12716): Goblin Mortar*/
(@ENTRY, '12717', '1500', '202', '205', '0'),  /* Spell(12717): Goblin Mining Helmet*/
(@ENTRY, '12718', '1500', '202', '205', '0'),  /* Spell(12718): Goblin Construction Helmet*/
(@ENTRY, '12754', '2600', '202', '235', '0'),  /* Spell(12754): The Big One*/
(@ENTRY, '12755', '2400', '202', '230', '0'),  /* Spell(12755): Goblin Bomb Dispenser*/
(@ENTRY, '12758', '3000', '202', '245', '0'),  /* Spell(12758): Goblin Rocket Helmet*/
(@ENTRY, '12759', '2800', '202', '240', '0'),  /* Spell(12759): Gnomish Death Ray*/
(@ENTRY, '12760', '1500', '202', '205', '0'),  /* Spell(12760): Goblin Sapper Charge*/
(@ENTRY, '12895', '1500', '202', '205', '0'),  /* Spell(12895): Inlaid Mithril Cylinder Plans*/
(@ENTRY, '12897', '2200', '202', '215', '0'),  /* Spell(12897): Gnomish Goggles*/
(@ENTRY, '12899', '1500', '202', '205', '0'),  /* Spell(12899): Gnomish Shrink Ray*/
(@ENTRY, '12902', '1800', '202', '210', '0'),  /* Spell(12902): Gnomish Net-o-Matic Projector*/
(@ENTRY, '12903', '2000', '202', '215', '0'),  /* Spell(12903): Gnomish Harm Prevention Belt*/
(@ENTRY, '12905', '1500', '202', '210', '0'),  /* Spell(12905): Gnomish Rocket Boots*/
(@ENTRY, '12906', '2400', '202', '230', '0'),  /* Spell(12906): Gnomish Battle Chicken*/
(@ENTRY, '12907', '2600', '202', '235', '0'),  /* Spell(12907): Gnomish Mind Control Cap*/
(@ENTRY, '12908', '2800', '202', '240', '0'),  /* Spell(12908): Goblin Dragon Gun*/
(@ENTRY, '15255', '1500', '202', '200', '0'),  /* Spell(15255): Mechanical Repair Kit*/
(@ENTRY, '19567', '4000', '202', '250', '0'),  /* Spell(19567): Salt Shaker*/
(@ENTRY, '19788', '4000', '202', '250', '0'),  /* Spell(19788): Dense Blasting Powder*/
(@ENTRY, '19790', '10000', '202', '260', '0'),  /* Spell(19790): Thorium Grenade*/
(@ENTRY, '19791', '5000', '202', '260', '0'),  /* Spell(19791): Thorium Widget*/
(@ENTRY, '19792', '10000', '202', '260', '0'),  /* Spell(19792): Thorium Rifle*/
(@ENTRY, '19794', '20000', '202', '270', '0'),  /* Spell(19794): Spellpower Goggles Xtreme Plus*/
(@ENTRY, '19795', '10000', '202', '275', '0'),  /* Spell(19795): Thorium Tube*/
(@ENTRY, '19825', '20000', '202', '290', '0'),  /* Spell(19825): Master Engineer's Goggles*/
(@ENTRY, '23070', '5000', '202', '250', '0'),  /* Spell(23070): Dense Dynamite*/
(@ENTRY, '23071', '5000', '202', '260', '0'),  /* Spell(23071): Truesilver Transformer*/
(@ENTRY, '30303', '10000', '202', '300', '0'),  /* Spell(30303): Elemental Blasting Powder*/
(@ENTRY, '30304', '10000', '202', '300', '0'),  /* Spell(30304): Fel Iron Casing*/
(@ENTRY, '30305', '10000', '202', '300', '0'),  /* Spell(30305): Handful of Fel Iron Bolts*/
(@ENTRY, '30306', '20000', '202', '325', '0'),  /* Spell(30306): Adamantite Frame*/
(@ENTRY, '30307', '50000', '202', '340', '0'),  /* Spell(30307): Hardened Adamantite Tube*/
(@ENTRY, '30308', '50000', '202', '340', '0'),  /* Spell(30308): Khorium Power Core*/
(@ENTRY, '30309', '50000', '202', '340', '0'),  /* Spell(30309): Felsteel Stabilizer*/
(@ENTRY, '30310', '15000', '202', '300', '0'),  /* Spell(30310): Fel Iron Bomb*/
(@ENTRY, '30311', '25000', '202', '325', '0'),  /* Spell(30311): Adamantite Grenade*/
(@ENTRY, '30312', '20000', '202', '320', '0'),  /* Spell(30312): Fel Iron Musket*/
(@ENTRY, '30350', '100000', '202', '275', '50'),  /* Spell(30350): Engineering*/
(@ENTRY, '30558', '25000', '202', '325', '0'),  /* Spell(30558): The Bigger One*/
(@ENTRY, '30560', '35000', '202', '340', '0'),  /* Spell(30560): Super Sapper Charge*/
(@ENTRY, '30563', '50000', '202', '350', '0'),  /* Spell(30563): Goblin Rocket Launcher*/
(@ENTRY, '30565', '100000', '202', '375', '0'),  /* Spell(30565): Foreman's Enchanted Helmet*/
(@ENTRY, '30566', '100000', '202', '375', '0'),  /* Spell(30566): Foreman's Reinforced Helmet*/
(@ENTRY, '30568', '25000', '202', '325', '0'),  /* Spell(30568): Gnomish Flame Turret*/
(@ENTRY, '30569', '35000', '202', '340', '0'),  /* Spell(30569): Gnomish Poultryizer*/
(@ENTRY, '30570', '50000', '202', '350', '0'),  /* Spell(30570): Nigh-Invulnerability Belt*/
(@ENTRY, '30574', '100000', '202', '375', '0'),  /* Spell(30574): Gnomish Power Goggles*/
(@ENTRY, '30575', '100000', '202', '375', '0'),  /* Spell(30575): Gnomish Battle Goggles*/
(@ENTRY, '39895', '10000', '202', '275', '0'),  /* Spell(39895): Fused Wiring*/
(@ENTRY, '39971', '20000', '202', '335', '0'),  /* Spell(39971): Icy Blasting Primers*/
(@ENTRY, '40274', '50000', '0', '350', '0'),  /* Spell(40274): Furious Gizmatic Goggles*/
(@ENTRY, '41307', '50000', '202', '375', '0'),  /* Spell(41307): Gyro-balanced Khorium Destroyer*/
(@ENTRY, '41311', '50000', '202', '350', '0'),  /* Spell(41311): Justicebringer 2000 Specs*/
(@ENTRY, '41312', '50000', '202', '350', '0'),  /* Spell(41312): Tankatronic Goggles*/
(@ENTRY, '41314', '50000', '202', '350', '0'),  /* Spell(41314): Surestrike Goggles v2.0*/
(@ENTRY, '41315', '50000', '202', '350', '0'),  /* Spell(41315): Gadgetstorm Goggles*/
(@ENTRY, '41316', '50000', '202', '350', '0'),  /* Spell(41316): Living Replicator Specs*/
(@ENTRY, '41317', '50000', '0', '350', '0'),  /* Spell(41317): Deathblow X11 Goggles*/
(@ENTRY, '41318', '50000', '0', '350', '0'),  /* Spell(41318): Wonderheal XT40 Shades*/
(@ENTRY, '41319', '50000', '0', '350', '0'),  /* Spell(41319): Magnified Moon Specs*/
(@ENTRY, '41320', '50000', '202', '350', '0'),  /* Spell(41320): Destruction Holo-gogs*/
(@ENTRY, '41321', '50000', '0', '350', '0'),  /* Spell(41321): Powerheal 4000 Lens*/
(@ENTRY, '44155', '60000', '202', '300', '0'),  /* Spell(44155): Flying Machine*/
(@ENTRY, '44157', '180000', '202', '375', '0'),  /* Spell(44157): Turbo-Charged Flying Machine*/
(@ENTRY, '51306', '350000', '202', '350', '65'),  /* Spell(51306): Engineering*/
(@ENTRY, '53281', '50000', '202', '350', '0'),  /* Spell(53281): Volatile Blasting Trigger*/
(@ENTRY, '54353', '125000', '202', '400', '0'),  /* Spell(54353): Mark "S" Boomstick*/
(@ENTRY, '54736', '100000', '202', '390', '0'),  /* Spell(54736): EMP Generator*/
(@ENTRY, '54793', '100000', '202', '380', '0'),  /* Spell(54793): Frag Belt*/
(@ENTRY, '54998', '125000', '202', '400', '0'),  /* Spell(54998): Hand-Mounted Pyro Rocket*/
(@ENTRY, '54999', '125000', '202', '400', '0'),  /* Spell(54999): Hyperspeed Accelerators*/
(@ENTRY, '55002', '100000', '202', '380', '0'),  /* Spell(55002): Flexweave Underlay*/
(@ENTRY, '55016', '125000', '202', '405', '0'),  /* Spell(55016): Nitro Boosts*/
(@ENTRY, '56349', '50000', '202', '350', '0'),  /* Spell(56349): Handful of Cobalt Bolts*/
(@ENTRY, '56459', '100000', '202', '375', '0'),  /* Spell(56459): Hammer Pick*/
(@ENTRY, '56460', '50000', '202', '350', '0'),  /* Spell(56460): Cobalt Frag Bomb*/
(@ENTRY, '56461', '100000', '202', '375', '0'),  /* Spell(56461): Bladed Pickaxe*/
(@ENTRY, '56462', '150000', '202', '435', '0'),  /* Spell(56462): Gnomish Army Knife*/
(@ENTRY, '56463', '100000', '202', '375', '0'),  /* Spell(56463): Explosive Decoy*/
(@ENTRY, '56464', '100000', '202', '375', '0'),  /* Spell(56464): Overcharged Capacitor*/
(@ENTRY, '56465', '125000', '202', '420', '0'),  /* Spell(56465): Mechanized Snow Goggles*/
(@ENTRY, '56466', '125000', '202', '420', '0'),  /* Spell(56466): Sonic Booster*/
(@ENTRY, '56467', '125000', '202', '420', '0'),  /* Spell(56467): Noise Machine*/
(@ENTRY, '56468', '125000', '202', '405', '0'),  /* Spell(56468): Box of Bombs*/
(@ENTRY, '56469', '150000', '202', '425', '0'),  /* Spell(56469): Gnomish Lightning Generator*/
(@ENTRY, '56470', '150000', '202', '425', '0'),  /* Spell(56470): Sun Scope*/
(@ENTRY, '56471', '100000', '202', '390', '0'),  /* Spell(56471): Froststeel Tube*/
(@ENTRY, '56472', '150000', '202', '425', '0'),  /* Spell(56472): MOLL-E*/
(@ENTRY, '56473', '150000', '202', '425', '0'),  /* Spell(56473): Gnomish X-Ray Specs*/
(@ENTRY, '56476', '125000', '202', '410', '0'),  /* Spell(56476): Healing Injector Kit*/
(@ENTRY, '56477', '125000', '202', '415', '0'),  /* Spell(56477): Mana Injector Kit*/
(@ENTRY, '56478', '200000', '202', '430', '0'),  /* Spell(56478): Heartseeker Scope*/
(@ENTRY, '56479', '200000', '202', '450', '0'),  /* Spell(56479): Armor Plated Combat Shotgun*/
(@ENTRY, '56480', '150000', '202', '440', '0'),  /* Spell(56480): Armored Titanium Goggles*/
(@ENTRY, '56481', '150000', '0', '440', '0'),  /* Spell(56481): Weakness Spectralizers*/
(@ENTRY, '56483', '150000', '202', '440', '0'),  /* Spell(56483): Charged Titanium Specs*/
(@ENTRY, '56484', '150000', '202', '440', '0'),  /* Spell(56484): Visage Liquification Goggles*/
(@ENTRY, '56486', '150000', '0', '440', '0'),  /* Spell(56486): Greensight Gogs*/
(@ENTRY, '56487', '150000', '202', '440', '0'),  /* Spell(56487): Electroflux Sight Enhancers*/
(@ENTRY, '56514', '150000', '202', '425', '0'),  /* Spell(56514): Global Thermal Sapper Charge*/
(@ENTRY, '56574', '150000', '202', '440', '0'),  /* Spell(56574): Truesight Ice Blinders*/
(@ENTRY, '60874', '200000', '202', '450', '0'),  /* Spell(60874): Nesingwary 4000*/
(@ENTRY, '61471', '100000', '202', '390', '0'),  /* Spell(61471): Diamond-cut Refractor Scope*/
(@ENTRY, '61481', '125000', '202', '420', '0'),  /* Spell(61481): Mechanized Snow Goggles*/
(@ENTRY, '61482', '125000', '202', '420', '0'),  /* Spell(61482): Mechanized Snow Goggles*/
(@ENTRY, '61483', '125000', '202', '420', '0'),  /* Spell(61483): Mechanized Snow Goggles*/
(@ENTRY, '62271', '150000', '202', '440', '0'),  /* Spell(62271): Unbreakable Healing Amplifiers*/
(@ENTRY, '63750', '5000', '202', '250', '0'),  /* Spell(63750): High-powered Flashlight*/
(@ENTRY, '63770', '125000', '202', '400', '0'),  /* Spell(63770): Reticulated Armor Webbing*/
(@ENTRY, '67326', '100000', '202', '410', '0'),  /* Spell(67326): Goblin Beam Welder*/
(@ENTRY, '67839', '100000', '202', '410', '0'),  /* Spell(67839): Mind Amplification Dish*/
(@ENTRY, '67920', '150000', '202', '435', '0'),  /* Spell(67920): Wormhole Generator: Northrend*/
(@ENTRY, '81714', '240000', '202', '525', '0'),  /* Spell(81714): Reinforced Bio-Optic Killshades*/
(@ENTRY, '81715', '240000', '202', '525', '0'),  /* Spell(81715): Specialized Bio-Optic Killshades*/
(@ENTRY, '81716', '240000', '202', '525', '0'),  /* Spell(81716): Deadly Bio-Optic Killshades*/
(@ENTRY, '81720', '240000', '202', '525', '0'),  /* Spell(81720): Energized Bio-Optic Killshades*/
(@ENTRY, '81722', '240000', '0', '525', '0'),  /* Spell(81722): Agile Bio-Optic Killshades*/
(@ENTRY, '81724', '240000', '0', '525', '0'),  /* Spell(81724): Camouflage Bio-Optic Killshades*/
(@ENTRY, '81725', '240000', '202', '525', '0'),  /* Spell(81725): Lightweight Bio-Optic Killshades*/
(@ENTRY, '82774', '500000', '202', '425', '75'),  /* Spell(82774): Engineering*/
(@ENTRY, '84403', '150000', '202', '425', '0'),  /* Spell(84403): Handful of Obsidium Bolts*/
(@ENTRY, '84406', '150000', '202', '440', '0'),  /* Spell(84406): Authentic Jr. Engineer Goggles*/
(@ENTRY, '84408', '150000', '202', '450', '0'),  /* Spell(84408): R19 Threatfinder*/
(@ENTRY, '84409', '160000', '202', '455', '0'),  /* Spell(84409): Volatile Seaforium Blastpack*/
(@ENTRY, '84410', '150000', '202', '450', '0'),  /* Spell(84410): Safety Catch Removal Kit*/
(@ENTRY, '84411', '160000', '202', '465', '0'),  /* Spell(84411): High-Powered Bolt Gun*/
(@ENTRY, '84412', '160000', '202', '475', '0'),  /* Spell(84412): Personal World Destroyer*/
(@ENTRY, '84413', '160000', '202', '475', '0'),  /* Spell(84413): De-Weaponized Mechanical Companion*/
(@ENTRY, '84415', '170000', '202', '475', '0'),  /* Spell(84415): Lure Master Tackle Box*/
(@ENTRY, '84416', '170000', '202', '475', '0'),  /* Spell(84416): Elementium Toolbox*/
(@ENTRY, '84417', '170000', '202', '495', '0'),  /* Spell(84417): Volatile Thunderstick*/
(@ENTRY, '84418', '170000', '202', '475', '0'),  /* Spell(84418): Elementium Dragonling*/
(@ENTRY, '84420', '170000', '202', '490', '0'),  /* Spell(84420): Finely-Tuned Throat Needler*/
(@ENTRY, '84421', '170000', '202', '490', '0'),  /* Spell(84421): Loot-a-Rang*/
(@ENTRY, '84428', '200000', '202', '515', '0'),  /* Spell(84428): Gnomish X-Ray Scope*/
(@ENTRY, '84429', '200000', '202', '505', '0'),  /* Spell(84429): Goblin Barbecue*/
(@ENTRY, '84430', '200000', '202', '510', '0'),  /* Spell(84430): Heat-Treated Spinning Lure*/
(@ENTRY, '84431', '240000', '202', '525', '0'),  /* Spell(84431): Overpowered Chicken Splitter*/
(@ENTRY, '84432', '240000', '202', '525', '0'),  /* Spell(84432): Kickback 5000*/
(@ENTRY, '94748', '150000', '202', '445', '0'),  /* Spell(94748): Electrified Ether*/
(@ENTRY, '95703', '150000', '202', '440', '0'),  /* Spell(95703): Electrostatic Condenser*/
(@ENTRY, '95705', '200000', '202', '500', '0'),  /* Spell(95705): Gnomish Gravity Well*/
(@ENTRY, '95707', '200000', '202', '500', '0'),  /* Spell(95707): Big Daddy*/
(@ENTRY, '108789', '57142', '202', '550', '0'),  /* Spell(108789): Phase Fingers*/
(@ENTRY, '109077', '57142', '202', '550', '0'),  /* Spell(109077): Incendiary Fireworks Launcher*/
(@ENTRY, '109099', '57142', '202', '550', '0'),  /* Spell(109099): Watergliding Jets*/
(@ENTRY, '110403', '685714', '202', '500', '80'),  /* Spell(110403): Engineering*/
(@ENTRY, '126392', '57142', '202', '550', '0'),  /* Spell(126392): Goblin Glider*/
(@ENTRY, '126731', '57142', '202', '550', '0'),  /* Spell(126731): Synapse Springs*/
(@ENTRY, '127113', '57142', '202', '500', '0'),  /* Spell(127113): Ghost Iron Bolts*/
(@ENTRY, '127114', '57142', '202', '500', '0'),  /* Spell(127114): High-Explosive Gunpowder*/
(@ENTRY, '127115', '57142', '202', '560', '0'),  /* Spell(127115): Lord Blastington's Scope of Doom*/
(@ENTRY, '127116', '57142', '202', '525', '0'),  /* Spell(127116): Mirror Scope*/
(@ENTRY, '127117', '57142', '202', '600', '0'),  /* Spell(127117): Lightweight Retinal Armor*/
(@ENTRY, '127118', '50000', '0', '600', '0'),  /* Spell(127118): Agile Retinal Armor*/
(@ENTRY, '127119', '55555', '0', '600', '0'),  /* Spell(127119): Camouflage Retinal Armor*/
(@ENTRY, '127120', '57142', '202', '600', '0'),  /* Spell(127120): Deadly Retinal Armor*/
(@ENTRY, '127121', '55555', '202', '600', '0'),  /* Spell(127121): Energized Retinal Armor*/
(@ENTRY, '127122', '57142', '202', '600', '0'),  /* Spell(127122): Specialized Retinal Armor*/
(@ENTRY, '127123', '57142', '202', '600', '0'),  /* Spell(127123): Reinforced Retinal Armor*/
(@ENTRY, '127124', '57142', '202', '500', '0'),  /* Spell(127124): Locksmith's Powderkeg*/
(@ENTRY, '127127', '57142', '202', '525', '0'),  /* Spell(127127): G91 Landshark*/
(@ENTRY, '127128', '57142', '202', '550', '0'),  /* Spell(127128): Goblin Dragon Gun, Mark II*/
(@ENTRY, '127129', '57142', '202', '600', '0'),  /* Spell(127129): Blingtron 4000*/
(@ENTRY, '127130', '57142', '202', '525', '0'),  /* Spell(127130): Mist-Piercing Goggles*/
(@ENTRY, '127131', '57142', '202', '550', '0'),  /* Spell(127131): Thermal Anvil*/
(@ENTRY, '127132', '57142', '202', '570', '0'),  /* Spell(127132): Wormhole Generator: Pandaria*/
(@ENTRY, '127134', '57142', '202', '550', '0'),  /* Spell(127134): Ghost Iron Dragonling*/
(@ENTRY, '127135', '57142', '202', '575', '0'),  /* Spell(127135): Mechanical Pandaren Dragonling*/
(@ENTRY, '127136', '57142', '202', '525', '0'),  /* Spell(127136): Big Game Hunter*/
(@ENTRY, '127137', '57142', '202', '565', '0'),  /* Spell(127137): Long-Range Trillium Sniper*/
(@ENTRY, '127138', '182857', '202', '600', '0'),  /* Spell(127138): Depleted-Kyparium Rocket*/
(@ENTRY, '127139', '182857', '202', '600', '0'),  /* Spell(127139): Geosynchronous World Spinner*/
(@ENTRY, '131211', '57142', '202', '550', '0'),  /* Spell(131211): Flashing Tinker's Gear*/
(@ENTRY, '131212', '57142', '202', '550', '0'),  /* Spell(131212): Fractured Tinker's Gear*/
(@ENTRY, '131213', '57142', '202', '550', '0'),  /* Spell(131213): Precise Tinker's Gear*/
(@ENTRY, '131214', '57142', '202', '550', '0'),  /* Spell(131214): Quick Tinker's Gear*/
(@ENTRY, '131215', '57142', '202', '550', '0'),  /* Spell(131215): Rigid Tinker's Gear*/
(@ENTRY, '131216', '57142', '202', '550', '0'),  /* Spell(131216): Smooth Tinker's Gear*/
(@ENTRY, '131217', '57142', '202', '550', '0'),  /* Spell(131217): Sparkling Tinker's Gear*/
(@ENTRY, '131218', '57142', '202', '550', '0'),  /* Spell(131218): Subtle Tinker's Gear*/
(@ENTRY, '131353', '57142', '202', '500', '0'),  /* Spell(131353): Pandaria Fireworks*/
(@ENTRY, '131563', '57142', '202', '550', '0');  /* Spell(131563): Tinker's Kit*/


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
('5518', '3630'),  /* Quest(3630): Gnome Engineering ,QuestMinLevel: 10 ,QuestProfession ID: 202[Engineering] */ 
('5518', '29475'),  /* Quest(29475): Goblin Engineering ,QuestMinLevel: 85 ,QuestProfession ID: 202[Engineering] */ 
('5518', '29477');  /* Quest(29477): Gnomish Engineering ,QuestMinLevel: 85 ,QuestProfession ID: 202[Engineering] */ 


/* Step 2.2 Table  `creature_involvedrelation */
DELETE FROM  `creature_involvedrelation` WHERE `id`= @ENTRY;
/* Step 1.8 Table  `waypoints */
DELETE FROM waypoints WHERE  `entry` = @ENTRY;
/* Step 2.5 Table  `npc_spellclick_spells */
DELETE FROM npc_spellclick_spells WHERE  `npc_entry` = @ENTRY;
/* Step 2.6 Table  `pet_levelstats */
DELETE FROM pet_levelstats WHERE  `creature_entry` = @ENTRY;

