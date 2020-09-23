/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 4/2/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Master Mathias Shaw';
SET @ENTRY 		:= '45796';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '34974', '0', '0', '0', @CREATURE, 'Leader of SI:7', '', '12098', '85', '85', '3', '0', '12', '12', '3', '0', '1', '1.14286', '0', '1.14286', '1', '1', '500', '750', '0', '187', '35', '1000', '2000', '4', '33536', '2048', '0', '0', '0', '0', '0', '0', '400', '600', '150', '7', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '10', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1783', '0', '', '16048');

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('34974', '0.3672', '1.8', '0', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 45796 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '0', '4922', '5472', '1', '1', '0', '0', '-4396.04', '-4434.55', '287.291', '1.595', '900', '0', '0', '774900', '0', '0', '0', '0', '0', '0', '0', '0', '0'), 
(NULL, @ENTRY, '0', '4922', '5473', '1', '1', '0', '0', '-4469.98', '-4355.02', '328.272', '1.54503', '300', '0', '0', '774900', '0', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-4396.04' AND `position_y` REGEXP '-4434.55' AND `position_z` REGEXP '287.291' AND `phaseMask` = '1' AND `map` = '0');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-4396.04' AND `position_y` REGEXP '-4434.55' AND `position_z` REGEXP '287.291' AND `phaseMask` = '1' AND `map` = '0');
DELETE FROM  `creature_formations` WHERE `leaderGUID` = @GUID;
/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-4469.98' AND `position_y` REGEXP '-4355.02' AND `position_z` REGEXP '328.272' AND `phaseMask` = '1' AND `map` = '0');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-4469.98' AND `position_y` REGEXP '-4355.02' AND `position_z` REGEXP '328.272' AND `phaseMask` = '1' AND `map` = '0');
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
DELETE FROM gossip_menu WHERE  `entry` = 12098;
/* Step 2.7 Table  `gossip_menu_option */
DELETE FROM gossip_menu_option WHERE  `menu_id` = 12098;
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
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES 
('45796', '27652'),  /* Quest(27652): Dark Assassins ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27654'),  /* Quest(27654): Bring the Hammer Down ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27657'),  /* Quest(27657): Help from the Earthcaller ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27688'),  /* Quest(27688): Distract Them for Me ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27695'),  /* Quest(27695): The Elementium Axe ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27700'),  /* Quest(27700): Dragon, Unchained ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27702'),  /* Quest(27702): Coup de Grace ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27711'),  /* Quest(27711): Back to the Elementium Depths ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27784');  /* Quest(27784): The Hammer of Twilight ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 


/* Step 2.2 Table  `creature_involvedrelation */
DELETE FROM  `creature_involvedrelation` WHERE `id`= @ENTRY;
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES 
('45796', '27636'),  /* Quest(27636): Just You and Mathias ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27652'),  /* Quest(27652): Dark Assassins ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27654'),  /* Quest(27654): Bring the Hammer Down ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27688'),  /* Quest(27688): Distract Them for Me ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27695'),  /* Quest(27695): The Elementium Axe ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27700'),  /* Quest(27700): Dragon, Unchained ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27702'),  /* Quest(27702): Coup de Grace ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27719'),  /* Quest(27719): Water of Life ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 
('45796', '27782');  /* Quest(27782): Mathias Needs You ,QuestMinLevel: 84 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 


/* Step 1.8 Table  `waypoints */
DELETE FROM waypoints WHERE  `entry` = @ENTRY;
/* Step 2.5 Table  `npc_spellclick_spells */
DELETE FROM npc_spellclick_spells WHERE  `npc_entry` = @ENTRY;
/* Step 2.6 Table  `pet_levelstats */
DELETE FROM pet_levelstats WHERE  `creature_entry` = @ENTRY;

