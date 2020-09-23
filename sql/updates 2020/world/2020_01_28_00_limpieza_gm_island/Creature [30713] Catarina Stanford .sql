/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 28/1/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Catarina Stanford';
SET @ENTRY 		:= '30713';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `creature_template` */
DELETE FROM `creature_template` WHERE `entry` = @ENTRY;
INSERT INTO `creature_template` (`entry`, `difficulty_entry_1`, `difficulty_entry_2`, `difficulty_entry_3`, `difficulty_entry_4`, `difficulty_entry_5`, `difficulty_entry_6`, `difficulty_entry_7`, `difficulty_entry_8`, `difficulty_entry_9`, `difficulty_entry_10`, `difficulty_entry_11`, `difficulty_entry_12`, `difficulty_entry_13`, `difficulty_entry_14`, `difficulty_entry_15`, `KillCredit1`, `KillCredit2`, `modelid1`, `modelid2`, `modelid3`, `modelid4`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `exp`, `exp_unk`, `faction_A`, `faction_H`, `npcflag`, `npcflag2`, `speed_walk`, `speed_run`, `speed_swim`, `speed_fly`, `scale`, `rank`, `mindmg`, `maxdmg`, `dmgschool`, `attackpower`, `dmg_multiplier`, `baseattacktime`, `rangeattacktime`, `unit_class`, `unit_flags`, `unit_flags2`, `dynamicflags`, `family`, `trainer_type`, `trainer_spell`, `trainer_class`, `trainer_race`, `minrangedmg`, `maxrangedmg`, `rangedattackpower`, `type`, `type_flags`, `type_flags2`, `lootid`, `pickpocketloot`, `skinloot`, `resistance1`, `resistance2`, `resistance3`, `resistance4`, `resistance5`, `resistance6`, `spell1`, `spell2`, `spell3`, `spell4`, `spell5`, `spell6`, `spell7`, `spell8`, `PetSpellDataId`, `VehicleId`, `mingold`, `maxgold`, `AIName`, `MovementType`, `InhabitType`, `HoverHeight`, `Health_mod`, `Mana_mod`, `Mana_mod_extra`, `Armor_mod`, `RacialLeader`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `movementId`, `RegenHealth`, `equipment_id`, `mechanic_immune_mask`, `flags_extra`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '27261', '0', '0', '0', @CREATURE, 'Inscription Trainer', '', '0', '35', '35', '0', '0', '35', '35', '80', '0', '1', '1.14286', '0', '1.14286', '1', '0', '34', '48', '0', '52', '1', '2000', '2000', '8', '32768', '2048', '0', '0', '2', '0', '0', '0', '29', '43', '17', '7', '4096', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '3', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '30713', '0', '0', '', '16048');

/* Step 1.2 Table `creature_equip_template */
DELETE FROM `creature_equip_template` WHERE `entry`= 30713;
INSERT INTO `creature_equip_template` (`entry`, `itemEntry1`, `itemEntry2`, `itemEntry3`) VALUES 
('30713', '12862', '0', '0'); /* [ItemEntry1(12862): Monster - Item, Book - Black Simple] */

/* Step 1.3 Table  creature_template_addon */
DELETE FROM creature_template_addon WHERE  `entry` = @ENTRY;
INSERT INTO `creature_template_addon` (`entry`,`path_id`,`mount`,`bytes1`,`bytes2`,`emote`,`auras`) VALUES 
(@ENTRY, '0', '0', '0', '257', '0', ''); 


/* Step 2.7 Table  `creature_model_info */
DELETE m1 FROM creature_template AS ct JOIN creature_model_info AS m1 ON ct.modelid1 = m1.modelid OR ct.modelid2 = m1.modelid OR ct.modelid3 = m1.modelid OR ct.modelid4 = m1.modelid WHERE entry = @ENTRY;
INSERT INTO `creature_model_info` (`modelid`,`bounding_radius`,`combat_reach`,`gender`,`modelid_other_gender`) VALUES 
('27261', '0.208', '1.5', '1', '0'); 


/* Step 1.6 Table  `creature_text */
DELETE FROM  `creature_text` WHERE `entry`= @ENTRY;
/* Step 1.6 Table  `smart_scripts` */
DELETE FROM smart_scripts WHERE `entryorguid` = 30713 AND `source_type`= 0;
/* Step 1.7 Table  `creature */
DELETE FROM creature WHERE  `id` = @ENTRY;
INSERT INTO `creature` (`guid`,`id`,`map`,`zoneId`,`areaId`,`spawnMask`,`phaseMask`,`modelid`,`equipment_id`,`position_x`,`position_y`,`position_z`,`orientation`,`spawntimesecs`,`spawndist`, `currentwaypoint`,`curhealth`, `curmana`, `MovementType`, `npcflag`, `npcflag2`, `unit_flags`,`unit_flags2`,`dynamicflags`,`isActive`,`protec_anti_doublet`) VALUES 
(NULL, @ENTRY, '0', '1519', '5154', '1', '1', '0', '0', '-8862.5', '857.196', '99.6931', '4.06662', '120', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0'); 

/* Step 2.8 Table  `creature_addon` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-8862.5' AND `position_y` REGEXP '857.196' AND `position_z` REGEXP '99.6931' AND `phaseMask` = '1' AND `map` = '0');
DELETE FROM `creature_addon` WHERE `guid` = @GUID;
/* Step 3.1 Table  `creature_formations` */
SET @GUID := (SELECT `guid` FROM `creature` WHERE `position_x` REGEXP '-8862.5' AND `position_y` REGEXP '857.196' AND `position_z` REGEXP '99.6931' AND `phaseMask` = '1' AND `map` = '0');
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
(@ENTRY, '45357', '10', '773', '0', '5'),  /* Spell(45357): Inscription*/
(@ENTRY, '45358', '500', '773', '50', '10'),  /* Spell(45358): Inscription*/
(@ENTRY, '45359', '5000', '773', '125', '25'),  /* Spell(45359): Inscription*/
(@ENTRY, '45360', '50000', '773', '200', '35'),  /* Spell(45360): Inscription*/
(@ENTRY, '45361', '100000', '773', '275', '50'),  /* Spell(45361): Inscription*/
(@ENTRY, '45363', '350000', '773', '350', '65'),  /* Spell(45363): Inscription*/
(@ENTRY, '48121', '400', '773', '100', '0'),  /* Spell(48121): Glyph of Entangling Roots*/
(@ENTRY, '48247', '500', '773', '85', '0'),  /* Spell(48247): Mysterious Tarot*/
(@ENTRY, '48248', '50', '773', '35', '0'),  /* Spell(48248): Scroll of Recall*/
(@ENTRY, '50598', '400', '773', '75', '0'),  /* Spell(50598): Scroll of Intellect II*/
(@ENTRY, '50599', '750', '773', '165', '0'),  /* Spell(50599): Scroll of Intellect III*/
(@ENTRY, '50600', '4500', '773', '215', '0'),  /* Spell(50600): Scroll of Intellect IV*/
(@ENTRY, '50601', '10000', '773', '260', '0'),  /* Spell(50601): Scroll of Intellect V*/
(@ENTRY, '50602', '20000', '773', '300', '0'),  /* Spell(50602): Scroll of Intellect VI*/
(@ENTRY, '50603', '50000', '773', '360', '0'),  /* Spell(50603): Scroll of Intellect VII*/
(@ENTRY, '50604', '60000', '773', '410', '0'),  /* Spell(50604): Scroll of Intellect VIII*/
(@ENTRY, '50605', '400', '773', '75', '0'),  /* Spell(50605): Scroll of Spirit II*/
(@ENTRY, '50606', '750', '773', '160', '0'),  /* Spell(50606): Scroll of Spirit III*/
(@ENTRY, '50607', '4500', '773', '210', '0'),  /* Spell(50607): Scroll of Spirit IV*/
(@ENTRY, '50608', '10000', '773', '255', '0'),  /* Spell(50608): Scroll of Spirit V*/
(@ENTRY, '50609', '20000', '773', '295', '0'),  /* Spell(50609): Scroll of Spirit VI*/
(@ENTRY, '50610', '50000', '773', '355', '0'),  /* Spell(50610): Scroll of Spirit VII*/
(@ENTRY, '50611', '60000', '773', '405', '0'),  /* Spell(50611): Scroll of Spirit VIII*/
(@ENTRY, '50612', '400', '773', '75', '0'),  /* Spell(50612): Scroll of Stamina II*/
(@ENTRY, '50614', '750', '773', '155', '0'),  /* Spell(50614): Scroll of Stamina III*/
(@ENTRY, '50616', '4500', '773', '205', '0'),  /* Spell(50616): Scroll of Stamina IV*/
(@ENTRY, '50617', '10000', '773', '250', '0'),  /* Spell(50617): Scroll of Stamina V*/
(@ENTRY, '50618', '20000', '773', '290', '0'),  /* Spell(50618): Scroll of Stamina VI*/
(@ENTRY, '50619', '50000', '773', '350', '0'),  /* Spell(50619): Scroll of Stamina VII*/
(@ENTRY, '50620', '60000', '773', '400', '0'),  /* Spell(50620): Scroll of Stamina VIII*/
(@ENTRY, '52739', '150', '773', '35', '0'),  /* Spell(52739): Enchanting Vellum*/
(@ENTRY, '52843', '50', '773', '35', '0'),  /* Spell(52843): Moonglow Ink*/
(@ENTRY, '53462', '300', '773', '75', '0'),  /* Spell(53462): Midnight Ink*/
(@ENTRY, '56943', '30000', '773', '350', '0'),  /* Spell(56943): Glyph of Frenzied Regeneration*/
(@ENTRY, '56945', '500', '773', '115', '0'),  /* Spell(56945): Glyph of Healing Touch*/
(@ENTRY, '56948', '750', '773', '150', '0'),  /* Spell(56948): Glyph of the Orca*/
(@ENTRY, '56951', '750', '773', '130', '0'),  /* Spell(56951): Glyph of Savagery*/
(@ENTRY, '56952', '20000', '773', '310', '0'),  /* Spell(56952): Glyph of Pounce*/
(@ENTRY, '56953', '1000', '773', '170', '0'),  /* Spell(56953): Glyph of Rebirth*/
(@ENTRY, '56955', '300', '773', '80', '0'),  /* Spell(56955): Glyph of Rejuvenation*/
(@ENTRY, '56956', '3000', '773', '200', '0'),  /* Spell(56956): Glyph of Prowl*/
(@ENTRY, '56957', '10000', '773', '260', '0'),  /* Spell(56957): Glyph of Shred*/
(@ENTRY, '56959', '4500', '773', '220', '0'),  /* Spell(56959): Glyph of Guided Stars*/
(@ENTRY, '56961', '400', '773', '90', '0'),  /* Spell(56961): Glyph of Maul*/
(@ENTRY, '56963', '300', '773', '85', '0'),  /* Spell(56963): Glyph of Nature's Grasp*/
(@ENTRY, '56971', '500', '773', '115', '0'),  /* Spell(56971): Glyph of Loose Mana*/
(@ENTRY, '56972', '30000', '773', '335', '0'),  /* Spell(56972): Glyph of Arcane Explosion*/
(@ENTRY, '56973', '750', '773', '130', '0'),  /* Spell(56973): Glyph of Blink*/
(@ENTRY, '56974', '750', '773', '155', '0'),  /* Spell(56974): Glyph of Evocation*/
(@ENTRY, '56976', '300', '773', '80', '0'),  /* Spell(56976): Glyph of Frost Nova*/
(@ENTRY, '56978', '400', '773', '90', '0'),  /* Spell(56978): Glyph of Momentum*/
(@ENTRY, '56979', '6000', '773', '225', '0'),  /* Spell(56979): Glyph of Ice Block*/
(@ENTRY, '56980', '50000', '773', '375', '0'),  /* Spell(56980): Glyph of Splitting Ice*/
(@ENTRY, '56981', '1000', '773', '175', '0'),  /* Spell(56981): Glyph of Cone of Cold*/
(@ENTRY, '56984', '30000', '773', '325', '0'),  /* Spell(56984): Glyph of Mana Gem*/
(@ENTRY, '56987', '60000', '773', '400', '0'),  /* Spell(56987): Glyph of Polymorph*/
(@ENTRY, '56991', '20000', '773', '315', '0'),  /* Spell(56991): Glyph of Arcane Power*/
(@ENTRY, '56994', '1000', '773', '175', '0'),  /* Spell(56994): Glyph of Aspects*/
(@ENTRY, '56995', '400', '773', '100', '0'),  /* Spell(56995): Glyph of Camouflage*/
(@ENTRY, '56997', '500', '773', '115', '0'),  /* Spell(56997): Glyph of Mending*/
(@ENTRY, '57000', '3000', '773', '200', '0'),  /* Spell(57000): Glyph of Deterrence*/
(@ENTRY, '57001', '6000', '773', '225', '0'),  /* Spell(57001): Glyph of Disengage*/
(@ENTRY, '57002', '10000', '773', '260', '0'),  /* Spell(57002): Glyph of Freezing Trap*/
(@ENTRY, '57003', '30000', '773', '350', '0'),  /* Spell(57003): Glyph of Ice Trap*/
(@ENTRY, '57004', '300', '773', '80', '0'),  /* Spell(57004): Glyph of Misdirection*/
(@ENTRY, '57005', '750', '773', '130', '0'),  /* Spell(57005): Glyph of Explosive Trap*/
(@ENTRY, '57006', '50000', '773', '375', '0'),  /* Spell(57006): Glyph of Animal Bond*/
(@ENTRY, '57007', '750', '773', '150', '0'),  /* Spell(57007): Glyph of No Escape*/
(@ENTRY, '57008', '20000', '773', '315', '0'),  /* Spell(57008): Glyph of Pathfinding*/
(@ENTRY, '57009', '400', '773', '90', '0'),  /* Spell(57009): Glyph of Tame Beast*/
(@ENTRY, '57020', '1000', '773', '180', '0'),  /* Spell(57020): Glyph of Final Wrath*/
(@ENTRY, '57022', '300', '773', '80', '0'),  /* Spell(57022): Glyph of Divine Protection*/
(@ENTRY, '57023', '4500', '773', '205', '0'),  /* Spell(57023): Glyph of Consecration*/
(@ENTRY, '57024', '6000', '773', '230', '0'),  /* Spell(57024): Glyph of Avenging Wrath*/
(@ENTRY, '57025', '10000', '773', '265', '0'),  /* Spell(57025): Glyph of Blinding Light*/
(@ENTRY, '57026', '20000', '773', '300', '0'),  /* Spell(57026): Glyph of Word of Glory*/
(@ENTRY, '57027', '400', '773', '90', '0'),  /* Spell(57027): Glyph of Holy Wrath*/
(@ENTRY, '57029', '500', '773', '105', '0'),  /* Spell(57029): Glyph of Illumination*/
(@ENTRY, '57030', '500', '773', '120', '0'),  /* Spell(57030): Glyph of Double Jeopardy*/
(@ENTRY, '57031', '750', '773', '135', '0'),  /* Spell(57031): Glyph of Divinity*/
(@ENTRY, '57033', '30000', '773', '335', '0'),  /* Spell(57033): Glyph of Devotion Aura*/
(@ENTRY, '57036', '50000', '773', '375', '0'),  /* Spell(57036): Glyph of Turn Evil*/
(@ENTRY, '57113', '30000', '773', '340', '0'),  /* Spell(57113): Glyph of Ambush*/
(@ENTRY, '57114', '300', '773', '80', '0'),  /* Spell(57114): Glyph of Decoy*/
(@ENTRY, '57119', '400', '773', '95', '0'),  /* Spell(57119): Glyph of Evasion*/
(@ENTRY, '57120', '500', '773', '105', '0'),  /* Spell(57120): Glyph of Recovery*/
(@ENTRY, '57121', '500', '773', '120', '0'),  /* Spell(57121): Glyph of Expose Armor*/
(@ENTRY, '57122', '20000', '773', '305', '0'),  /* Spell(57122): Glyph of Feint*/
(@ENTRY, '57123', '750', '773', '135', '0'),  /* Spell(57123): Glyph of Garrote*/
(@ENTRY, '57125', '750', '773', '160', '0'),  /* Spell(57125): Glyph of Gouge*/
(@ENTRY, '57129', '3000', '773', '185', '0'),  /* Spell(57129): Glyph of Hemorraghing Veins*/
(@ENTRY, '57131', '4500', '773', '210', '0'),  /* Spell(57131): Glyph of Redirect*/
(@ENTRY, '57132', '6000', '773', '235', '0'),  /* Spell(57132): Glyph of Shiv*/
(@ENTRY, '57133', '15000', '773', '285', '0'),  /* Spell(57133): Glyph of Sprint*/
(@ENTRY, '57154', '7500', '773', '240', '0'),  /* Spell(57154): Glyph of Hindering Strikes*/
(@ENTRY, '57156', '15000', '773', '285', '0'),  /* Spell(57156): Glyph of Bloodthirst*/
(@ENTRY, '57157', '750', '773', '125', '0'),  /* Spell(57157): Glyph of Rude Interruption*/
(@ENTRY, '57158', '400', '773', '95', '0'),  /* Spell(57158): Glyph of Gag Order*/
(@ENTRY, '57161', '1000', '773', '170', '0'),  /* Spell(57161): Glyph of Die by the Sword*/
(@ENTRY, '57162', '300', '773', '85', '0'),  /* Spell(57162): Glyph of Enraged Speed*/
(@ENTRY, '57163', '500', '773', '110', '0'),  /* Spell(57163): Glyph of Hamstring*/
(@ENTRY, '57165', '3000', '773', '190', '0'),  /* Spell(57165): Glyph of Hold the Line*/
(@ENTRY, '57167', '750', '773', '140', '0'),  /* Spell(57167): Glyph of Hoarse Voice*/
(@ENTRY, '57168', '20000', '773', '320', '0'),  /* Spell(57168): Glyph of Sweeping Strikes*/
(@ENTRY, '57172', '30000', '773', '345', '0'),  /* Spell(57172): Glyph of Raging Wind*/
(@ENTRY, '57183', '6000', '773', '230', '0'),  /* Spell(57183): Glyph of Purify*/
(@ENTRY, '57184', '500', '773', '105', '0'),  /* Spell(57184): Glyph of Fade*/
(@ENTRY, '57185', '10000', '773', '270', '0'),  /* Spell(57185): Glyph of Fear Ward*/
(@ENTRY, '57186', '500', '773', '120', '0'),  /* Spell(57186): Glyph of Inner Sanctum*/
(@ENTRY, '57187', '20000', '773', '315', '0'),  /* Spell(57187): Glyph of Holy Nova*/
(@ENTRY, '57188', '750', '773', '135', '0'),  /* Spell(57188): Glyph of Inner Fire*/
(@ENTRY, '57192', '30000', '773', '350', '0'),  /* Spell(57192): Glyph of Holy Fire*/
(@ENTRY, '57194', '300', '773', '80', '0'),  /* Spell(57194): Glyph of Power Word: Shield*/
(@ENTRY, '57196', '400', '773', '95', '0'),  /* Spell(57196): Glyph of Psychic Scream*/
(@ENTRY, '57197', '750', '773', '160', '0'),  /* Spell(57197): Glyph of Renew*/
(@ENTRY, '57198', '50000', '773', '375', '0'),  /* Spell(57198): Glyph of Scourge Imprisonment*/
(@ENTRY, '57200', '1000', '773', '180', '0'),  /* Spell(57200): Glyph of Dispel Magic*/
(@ENTRY, '57201', '4500', '773', '210', '0'),  /* Spell(57201): Glyph of Smite*/
(@ENTRY, '57210', '10000', '773', '265', '0'),  /* Spell(57210): Glyph of Icebound Fortitude*/
(@ENTRY, '57213', '15000', '773', '285', '0'),  /* Spell(57213): Glyph of Death Grip*/
(@ENTRY, '57216', '10000', '773', '270', '0'),  /* Spell(57216): Glyph of Shifting Presences*/
(@ENTRY, '57219', '10000', '773', '280', '0'),  /* Spell(57219): Glyph of Icy Touch*/
(@ENTRY, '57221', '20000', '773', '300', '0'),  /* Spell(57221): Glyph of Pestilence*/
(@ENTRY, '57222', '30000', '773', '350', '0'),  /* Spell(57222): Glyph of Mind Freeze*/
(@ENTRY, '57224', '30000', '773', '330', '0'),  /* Spell(57224): Glyph of Foul Menagerie*/
(@ENTRY, '57225', '50000', '773', '375', '0'),  /* Spell(57225): Glyph of Strangulate*/
(@ENTRY, '57226', '20000', '773', '305', '0'),  /* Spell(57226): Glyph of Pillar of Frost*/
(@ENTRY, '57227', '30000', '773', '345', '0'),  /* Spell(57227): Glyph of Vampiric Blood*/
(@ENTRY, '57236', '20000', '773', '300', '0'),  /* Spell(57236): Glyph of Purge*/
(@ENTRY, '57238', '500', '773', '110', '0'),  /* Spell(57238): Glyph of Fire Nova*/
(@ENTRY, '57239', '300', '773', '85', '0'),  /* Spell(57239): Glyph of Flame Shock*/
(@ENTRY, '57240', '750', '773', '125', '0'),  /* Spell(57240): Glyph of Wind Shear*/
(@ENTRY, '57241', '3000', '773', '185', '0'),  /* Spell(57241): Glyph of Frost Shock*/
(@ENTRY, '57242', '4500', '773', '215', '0'),  /* Spell(57242): Glyph of Healing Stream Totem*/
(@ENTRY, '57244', '6000', '773', '235', '0'),  /* Spell(57244): Glyph of Totemic Recall*/
(@ENTRY, '57245', '750', '773', '140', '0'),  /* Spell(57245): Glyph of Telluric Currents*/
(@ENTRY, '57246', '400', '773', '95', '0'),  /* Spell(57246): Glyph of the Lakestrider*/
(@ENTRY, '57248', '50000', '773', '375', '0'),  /* Spell(57248): Glyph of Spiritwalker's Grace*/
(@ENTRY, '57249', '750', '773', '165', '0'),  /* Spell(57249): Glyph of Lava Lash*/
(@ENTRY, '57251', '10000', '773', '275', '0'),  /* Spell(57251): Glyph of Water Shield*/
(@ENTRY, '57252', '30000', '773', '330', '0'),  /* Spell(57252): Glyph of Cleansing Waters*/
(@ENTRY, '57257', '30000', '773', '350', '0'),  /* Spell(57257): Glyph of Hand of Gul'dan*/
(@ENTRY, '57259', '300', '773', '85', '0'),  /* Spell(57259): Glyph of Siphon Life*/
(@ENTRY, '57262', '750', '773', '125', '0'),  /* Spell(57262): Glyph of Fear*/
(@ENTRY, '57265', '500', '773', '110', '0'),  /* Spell(57265): Glyph of Health Funnel*/
(@ENTRY, '57266', '400', '773', '95', '0'),  /* Spell(57266): Glyph of Healthstone*/
(@ENTRY, '57269', '750', '773', '140', '0'),  /* Spell(57269): Glyph of Imp Swarm*/
(@ENTRY, '57270', '4500', '773', '215', '0'),  /* Spell(57270): Glyph of Havoc*/
(@ENTRY, '57271', '750', '773', '165', '0'),  /* Spell(57271): Glyph of Shadow Bolt*/
(@ENTRY, '57274', '7500', '773', '240', '0'),  /* Spell(57274): Glyph of Soulstone*/
(@ENTRY, '57275', '30000', '773', '325', '0'),  /* Spell(57275): Glyph of Carrion Swarm*/
(@ENTRY, '57277', '3000', '773', '190', '0'),  /* Spell(57277): Glyph of Falling Meteor*/
(@ENTRY, '57703', '400', '773', '85', '0'),  /* Spell(57703): Hunter's Ink*/
(@ENTRY, '57704', '400', '773', '100', '0'),  /* Spell(57704): Lion's Ink*/
(@ENTRY, '57706', '750', '773', '125', '0'),  /* Spell(57706): Dawnstar Ink*/
(@ENTRY, '57707', '750', '773', '150', '0'),  /* Spell(57707): Jadefire Ink*/
(@ENTRY, '57708', '750', '773', '175', '0'),  /* Spell(57708): Royal Ink*/
(@ENTRY, '57709', '3000', '773', '200', '0'),  /* Spell(57709): Celestial Ink*/
(@ENTRY, '57710', '6000', '773', '225', '0'),  /* Spell(57710): Fiery Ink*/
(@ENTRY, '57711', '10000', '773', '250', '0'),  /* Spell(57711): Shimmering Ink*/
(@ENTRY, '57712', '10000', '773', '275', '0'),  /* Spell(57712): Ink of the Sky*/
(@ENTRY, '57713', '20000', '773', '290', '0'),  /* Spell(57713): Ethereal Ink*/
(@ENTRY, '57714', '20000', '773', '325', '0'),  /* Spell(57714): Darkflame Ink*/
(@ENTRY, '57715', '50000', '773', '350', '0'),  /* Spell(57715): Ink of the Sea*/
(@ENTRY, '57716', '50000', '773', '375', '0'),  /* Spell(57716): Snowfall Ink*/
(@ENTRY, '58309', '300', '773', '75', '0'),  /* Spell(58309): Glyph of the Bear Cub*/
(@ENTRY, '58313', '300', '773', '75', '0'),  /* Spell(58313): Glyph of Flash of Light*/
(@ENTRY, '58344', '300', '773', '75', '0'),  /* Spell(58344): Glyph of Long Charge*/
(@ENTRY, '58346', '300', '773', '75', '0'),  /* Spell(58346): Glyph of Unending Rage*/
(@ENTRY, '58472', '50', '773', '15', '0'),  /* Spell(58472): Scroll of Agility*/
(@ENTRY, '58473', '400', '773', '85', '0'),  /* Spell(58473): Scroll of Agility II*/
(@ENTRY, '58476', '750', '773', '175', '0'),  /* Spell(58476): Scroll of Agility III*/
(@ENTRY, '58478', '4500', '773', '225', '0'),  /* Spell(58478): Scroll of Agility IV*/
(@ENTRY, '58480', '10000', '773', '270', '0'),  /* Spell(58480): Scroll of Agility V*/
(@ENTRY, '58481', '20000', '773', '310', '0'),  /* Spell(58481): Scroll of Agility VI*/
(@ENTRY, '58482', '50000', '773', '370', '0'),  /* Spell(58482): Scroll of Agility VII*/
(@ENTRY, '58483', '60000', '773', '420', '0'),  /* Spell(58483): Scroll of Agility VIII*/
(@ENTRY, '58484', '50', '773', '15', '0'),  /* Spell(58484): Scroll of Strength*/
(@ENTRY, '58485', '400', '773', '80', '0'),  /* Spell(58485): Scroll of Strength II*/
(@ENTRY, '58486', '750', '773', '170', '0'),  /* Spell(58486): Scroll of Strength III*/
(@ENTRY, '58487', '4500', '773', '220', '0'),  /* Spell(58487): Scroll of Strength IV*/
(@ENTRY, '58488', '10000', '773', '265', '0'),  /* Spell(58488): Scroll of Strength V*/
(@ENTRY, '58489', '20000', '773', '305', '0'),  /* Spell(58489): Scroll of Strength VI*/
(@ENTRY, '58490', '50000', '773', '365', '0'),  /* Spell(58490): Scroll of Strength VII*/
(@ENTRY, '58491', '60000', '773', '415', '0'),  /* Spell(58491): Scroll of Strength VIII*/
(@ENTRY, '58565', '500', '773', '85', '0'),  /* Spell(58565): Mystic Tome*/
(@ENTRY, '59326', '400', '773', '75', '0'),  /* Spell(59326): Glyph of Ghost Wolf*/
(@ENTRY, '59338', '20000', '773', '310', '0'),  /* Spell(59338): Glyph of Unholy Command*/
(@ENTRY, '59339', '20000', '773', '320', '0'),  /* Spell(59339): Glyph of Outbreak*/
(@ENTRY, '59340', '30000', '773', '340', '0'),  /* Spell(59340): Glyph of Corpse Explosion*/
(@ENTRY, '59387', '3000', '773', '200', '0'),  /* Spell(59387): Certificate of Ownership*/
(@ENTRY, '59475', '750', '773', '125', '0'),  /* Spell(59475): Tome of the Dawn*/
(@ENTRY, '59478', '750', '773', '125', '0'),  /* Spell(59478): Book of Survival*/
(@ENTRY, '59480', '750', '773', '125', '0'),  /* Spell(59480): Strange Tarot*/
(@ENTRY, '59484', '750', '773', '175', '0'),  /* Spell(59484): Tome of Kings*/
(@ENTRY, '59486', '750', '773', '175', '0'),  /* Spell(59486): Royal Guide of Escape Routes*/
(@ENTRY, '59487', '750', '773', '175', '0'),  /* Spell(59487): Arcane Tarot*/
(@ENTRY, '59489', '6000', '773', '225', '0'),  /* Spell(59489): Fire Eater's Guide*/
(@ENTRY, '59490', '6000', '773', '225', '0'),  /* Spell(59490): Book of Stars*/
(@ENTRY, '59491', '6000', '773', '225', '0'),  /* Spell(59491): Shadowy Tarot*/
(@ENTRY, '59493', '10000', '773', '275', '0'),  /* Spell(59493): Stormbound Tome*/
(@ENTRY, '59494', '10000', '773', '275', '0'),  /* Spell(59494): Manual of Clouds*/
(@ENTRY, '59495', '20000', '773', '325', '0'),  /* Spell(59495): Hellfire Tome*/
(@ENTRY, '59496', '20000', '773', '325', '0'),  /* Spell(59496): Book of Clever Tricks*/
(@ENTRY, '59497', '60000', '773', '400', '0'),  /* Spell(59497): Iron-bound Tome*/
(@ENTRY, '59498', '60000', '773', '400', '0'),  /* Spell(59498): Faces of Doom*/
(@ENTRY, '59502', '10000', '773', '275', '0'),  /* Spell(59502): Darkmoon Card*/
(@ENTRY, '59503', '20000', '773', '325', '0'),  /* Spell(59503): Greater Darkmoon Card*/
(@ENTRY, '59504', '60000', '773', '400', '0'),  /* Spell(59504): Darkmoon Card of the North*/
(@ENTRY, '60336', '3000', '773', '200', '0'),  /* Spell(60336): Scroll of Recall II*/
(@ENTRY, '60337', '50000', '773', '350', '0'),  /* Spell(60337): Scroll of Recall III*/
(@ENTRY, '61117', '75000', '773', '400', '0'),  /* Spell(61117): Master's Inscription of the Axe*/
(@ENTRY, '61118', '75000', '773', '400', '0'),  /* Spell(61118): Master's Inscription of the Crag*/
(@ENTRY, '61119', '75000', '773', '400', '0'),  /* Spell(61119): Master's Inscription of the Pinnacle*/
(@ENTRY, '61120', '75000', '773', '400', '0'),  /* Spell(61120): Master's Inscription of the Storm*/
(@ENTRY, '61177', '100000', '773', '385', '0'),  /* Spell(61177): Northrend Inscription Research*/
(@ENTRY, '61288', '1000', '773', '75', '0'),  /* Spell(61288): Minor Inscription Research*/
(@ENTRY, '62162', '50000', '773', '375', '0'),  /* Spell(62162): Glyph of the Master Shapeshifter*/
(@ENTRY, '64053', '50000', '773', '350', '0'),  /* Spell(64053): Twilight Tome*/
(@ENTRY, '64258', '10000', '773', '250', '0'),  /* Spell(64258): Glyph of Cyclone*/
(@ENTRY, '64259', '10000', '773', '255', '0'),  /* Spell(64259): Glyph of Binding Heal*/
(@ENTRY, '64260', '10000', '773', '255', '0'),  /* Spell(64260): Glyph of Disguise*/
(@ENTRY, '64261', '10000', '773', '250', '0'),  /* Spell(64261): Glyph of Deluge*/
(@ENTRY, '64262', '10000', '773', '255', '0'),  /* Spell(64262): Glyph of Shamanistic Rage*/
(@ENTRY, '64266', '10000', '773', '275', '0'),  /* Spell(64266): Glyph of Death Coil*/
(@ENTRY, '67600', '400', '773', '100', '0'),  /* Spell(67600): Glyph of Ferocious Bite*/
(@ENTRY, '69385', '120000', '773', '440', '0'),  /* Spell(69385): Runescroll of Fortitude*/
(@ENTRY, '71101', '10000', '773', '250', '0'),  /* Spell(71101): Glyph of Counterspell*/
(@ENTRY, '71102', '50000', '773', '375', '0'),  /* Spell(71102): Glyph of Eternal Resolve*/
(@ENTRY, '85785', '120000', '773', '500', '0'),  /* Spell(85785): Runescroll of Fortitude II*/
(@ENTRY, '86004', '80000', '773', '425', '0'),  /* Spell(86004): Blackfallow Ink*/
(@ENTRY, '86005', '90000', '773', '475', '0'),  /* Spell(86005): Inferno Ink*/
(@ENTRY, '86008', '500000', '773', '425', '75'),  /* Spell(86008): Inscription*/
(@ENTRY, '86375', '75000', '773', '500', '0'),  /* Spell(86375): Swiftsteel Inscription*/
(@ENTRY, '86401', '75000', '773', '500', '0'),  /* Spell(86401): Lionsmane Inscription*/
(@ENTRY, '86402', '75000', '773', '500', '0'),  /* Spell(86402): Inscription of the Earth Prince*/
(@ENTRY, '86403', '75000', '773', '500', '0'),  /* Spell(86403): Felfire Inscription*/
(@ENTRY, '86609', '80000', '773', '450', '0'),  /* Spell(86609): Mysterious Fortune Card*/
(@ENTRY, '86615', '200000', '773', '525', '0'),  /* Spell(86615): Darkmoon Card of Destruction*/
(@ENTRY, '86616', '90000', '773', '475', '0'),  /* Spell(86616): Book of Blood*/
(@ENTRY, '86640', '90000', '773', '475', '0'),  /* Spell(86640): Lord Rottington's Pressed Wisp Book*/
(@ENTRY, '86641', '120000', '773', '510', '0'),  /* Spell(86641): Dungeoneering Guide*/
(@ENTRY, '86642', '120000', '773', '510', '0'),  /* Spell(86642): Divine Companion*/
(@ENTRY, '86643', '120000', '773', '510', '0'),  /* Spell(86643): Battle Tome*/
(@ENTRY, '86648', '90000', '773', '480', '0'),  /* Spell(86648): Key to the Planes*/
(@ENTRY, '86649', '120000', '773', '505', '0'),  /* Spell(86649): Runed Staff*/
(@ENTRY, '86652', '150000', '773', '515', '0'),  /* Spell(86652): Rosethorn Staff*/
(@ENTRY, '86653', '150000', '773', '515', '0'),  /* Spell(86653): Silver Inlaid Staff*/
(@ENTRY, '89244', '100000', '773', '500', '0'),  /* Spell(89244): Forged Documents*/
(@ENTRY, '89368', '80000', '773', '445', '0'),  /* Spell(89368): Scroll of Intellect IX*/
(@ENTRY, '89369', '80000', '773', '465', '0'),  /* Spell(89369): Scroll of Strength IX*/
(@ENTRY, '89370', '80000', '773', '470', '0'),  /* Spell(89370): Scroll of Agility IX*/
(@ENTRY, '89371', '80000', '773', '455', '0'),  /* Spell(89371): Scroll of Spirit IX*/
(@ENTRY, '89372', '80000', '773', '460', '0'),  /* Spell(89372): Scroll of Stamina IX*/
(@ENTRY, '89373', '80000', '773', '450', '0'),  /* Spell(89373): Scroll of Protection IX*/
(@ENTRY, '89815', '80000', '773', '465', '0'),  /* Spell(89815): Glyph of Colossus Smash*/
(@ENTRY, '92026', '400', '773', '75', '0'),  /* Spell(92026): Vanishing Powder*/
(@ENTRY, '92027', '90000', '773', '475', '0'),  /* Spell(92027): Dust of Disappearance*/
(@ENTRY, '92579', '1000', '773', '180', '0'),  /* Spell(92579): Glyph of Blind*/
(@ENTRY, '94401', '500', '773', '120', '0'),  /* Spell(94401): Glyph of Cat Form*/
(@ENTRY, '94402', '30000', '773', '330', '0'),  /* Spell(94402): Glyph of Fae Silence*/
(@ENTRY, '94403', '500', '773', '120', '0'),  /* Spell(94403): Glyph of Faerie Fire*/
(@ENTRY, '94404', '750', '773', '150', '0'),  /* Spell(94404): Glyph of the Predator*/
(@ENTRY, '94405', '750', '773', '150', '0'),  /* Spell(94405): Glyph of Recklessness*/
(@ENTRY, '94406', '10000', '773', '250', '0'),  /* Spell(94406): Glyph of Bull Rush*/
(@ENTRY, '96284', '10000', '773', '275', '0'),  /* Spell(96284): Glyph of Dark Succor*/
(@ENTRY, '110417', '666666', '773', '500', '80'),  /* Spell(110417): Inscription*/
(@ENTRY, '111645', '222222', '773', '500', '0'),  /* Spell(111645): Ink of Dreams*/
(@ENTRY, '111646', '222222', '773', '500', '0'),  /* Spell(111646): Starlight Ink*/
(@ENTRY, '111830', '222222', '773', '600', '0'),  /* Spell(111830): Darkmoon Card of Mists*/
(@ENTRY, '111908', '222222', '773', '560', '0'),  /* Spell(111908): Inscribed Fan*/
(@ENTRY, '111909', '222222', '773', '560', '0'),  /* Spell(111909): Inscribed Jade Fan*/
(@ENTRY, '111910', '222222', '773', '560', '0'),  /* Spell(111910): Inscribed Red Fan*/
(@ENTRY, '111917', '222222', '773', '560', '0'),  /* Spell(111917): Rain Poppy Staff*/
(@ENTRY, '111918', '222222', '773', '560', '0'),  /* Spell(111918): Inscribed Crane Staff*/
(@ENTRY, '111919', '222222', '773', '560', '0'),  /* Spell(111919): Inscribed Serpent Staff*/
(@ENTRY, '111920', '222222', '773', '560', '0'),  /* Spell(111920): Ghost Iron Staff*/
(@ENTRY, '111921', '222222', '773', '560', '0'),  /* Spell(111921): Inscribed Tiger Staff*/
(@ENTRY, '112045', '222222', '773', '580', '0'),  /* Spell(112045): Runescroll of Fortitude III*/
(@ENTRY, '112437', '4500', '773', '220', '0'),  /* Spell(112437): Glyph of Nimble Brew*/
(@ENTRY, '112440', '50000', '773', '355', '0'),  /* Spell(112440): Glyph of Paralysis*/
(@ENTRY, '112442', '20000', '773', '320', '0'),  /* Spell(112442): Glyph of Life Cocoon*/
(@ENTRY, '112444', '50000', '773', '370', '0'),  /* Spell(112444): Glyph of Touch of Karma*/
(@ENTRY, '112450', '15000', '773', '295', '0'),  /* Spell(112450): Glyph of Leer of the Ox*/
(@ENTRY, '112451', '750', '773', '155', '0'),  /* Spell(112451): Glyph of Afterlife*/
(@ENTRY, '112452', '50000', '773', '360', '0'),  /* Spell(112452): Glyph of Sparring*/
(@ENTRY, '112454', '50000', '773', '365', '0'),  /* Spell(112454): Glyph of Detox*/
(@ENTRY, '112457', '10000', '773', '255', '0'),  /* Spell(112457): Glyph of Fortifying Brew*/
(@ENTRY, '112458', '50000', '773', '380', '0'),  /* Spell(112458): Glyph of Targeted Expulsion*/
(@ENTRY, '112462', '100000', '773', '485', '0'),  /* Spell(112462): Glyph of Crackling Tiger Lightning*/
(@ENTRY, '112463', '100000', '773', '495', '0'),  /* Spell(112463): Glyph of Flying Serpent Kick*/
(@ENTRY, '112469', '100000', '773', '490', '0'),  /* Spell(112469): Glyph of Fighting Pose*/
(@ENTRY, '112883', '222222', '773', '500', '0'),  /* Spell(112883): Tome of the Clear Mind*/
(@ENTRY, '112996', '555555', '773', '525', '0'),  /* Spell(112996): Scroll of Wisdom*/
(@ENTRY, '124442', '80000', '773', '450', '0'),  /* Spell(124442): Glyph of Aspect of the Beast*/
(@ENTRY, '124445', '80000', '773', '460', '0'),  /* Spell(124445): Glyph of Fists of Fury*/
(@ENTRY, '124451', '50000', '773', '380', '0'),  /* Spell(124451): Glyph of Zen Meditation*/
(@ENTRY, '124452', '80000', '773', '440', '0'),  /* Spell(124452): Glyph of Renewing Mists*/
(@ENTRY, '124453', '80000', '773', '445', '0'),  /* Spell(124453): Glyph of Spinning Crane Kick*/
(@ENTRY, '124455', '80000', '773', '465', '0'),  /* Spell(124455): Glyph of Surging Mist*/
(@ENTRY, '124456', '80000', '773', '470', '0'),  /* Spell(124456): Glyph of Touch of Death*/
(@ENTRY, '124459', '80000', '773', '455', '0'),  /* Spell(124459): Glyph of Mind Flay*/
(@ENTRY, '124463', '50000', '773', '380', '0'),  /* Spell(124463): Glyph of Fortuitous Spheres*/
(@ENTRY, '126801', '80000', '773', '440', '0'),  /* Spell(126801): Glyph of Fetch*/
(@ENTRY, '126988', '55555', '773', '600', '0'),  /* Spell(126988): Origami Crane*/
(@ENTRY, '126989', '55555', '773', '600', '0'),  /* Spell(126989): Origami Frog*/
(@ENTRY, '126994', '222222', '773', '570', '0'),  /* Spell(126994): Greater Ox Horn Inscription*/
(@ENTRY, '126995', '222222', '773', '570', '0'),  /* Spell(126995): Greater Crane Wing Inscription*/
(@ENTRY, '126996', '222222', '773', '570', '0'),  /* Spell(126996): Greater Tiger Claw Inscription*/
(@ENTRY, '126997', '222222', '773', '570', '0'),  /* Spell(126997): Greater Tiger Fang Inscription*/
(@ENTRY, '127007', '55555', '773', '600', '0'),  /* Spell(127007): Yu'lon Kite*/
(@ENTRY, '127009', '55555', '773', '600', '0'),  /* Spell(127009): Chi-ji Kite*/
(@ENTRY, '127016', '222222', '773', '540', '0'),  /* Spell(127016): Tiger Fang Inscription*/
(@ENTRY, '127017', '222222', '773', '540', '0'),  /* Spell(127017): Tiger Claw Inscription*/
(@ENTRY, '127018', '222222', '773', '540', '0'),  /* Spell(127018): Crane Wing Inscription*/
(@ENTRY, '127019', '222222', '773', '540', '0'),  /* Spell(127019): Ox Horn Inscription*/
(@ENTRY, '127020', '222222', '773', '575', '0'),  /* Spell(127020): Secret Tiger Fang Inscription*/
(@ENTRY, '127021', '222222', '773', '575', '0'),  /* Spell(127021): Secret Tiger Claw Inscription*/
(@ENTRY, '127023', '222222', '773', '575', '0'),  /* Spell(127023): Secret Crane Wing Inscription*/
(@ENTRY, '127024', '222222', '773', '575', '0'),  /* Spell(127024): Secret Ox Horn Inscription*/
(@ENTRY, '127625', '10000', '773', '255', '0');  /* Spell(127625): Glyph of Lightspring*/


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

