/*
SQL BlackCore WoW				  
Desarrollado por:
Fecha: 23/10/2019
### Scripts Privados / Derechos Reservados BlackCore WoW ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= '';
SET @ENTRY 		:= '29312';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `quest_template` */
DELETE FROM  `quest_template` WHERE `Id` = 29312;
INSERT INTO `quest_template` (`Id`, `Method`, `Level`, `MinLevel`, `MaxLevel`, `ZoneOrSort`, `Type`, `SuggestedPlayers`, `LimitTime`, `RequiredTeam`, `RequiredClasses`, `RequiredRaces`, `RequiredSkillId`, `RequiredSkillPoints`, `RequiredFactionId1`, `RequiredFactionId2`, `RequiredFactionValue1`, `RequiredFactionValue2`, `RequiredFactionKills`, `RequiredFactionKillsCount`, `RequiredPetBattleWith`, `RequiredMinRepFaction`, `RequiredMaxRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepValue`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestIdChain`, `RewardXPId`, `RewardXPId2`, `RewardOrRequiredMoney`, `RewardMoneyMaxLevel`, `RewardSpell`, `RewardSpellCast`, `RewardHonor`, `RewardHonorMultiplier`, `RewardMailTemplateId`, `RewardMailDelay`, `SourceItemId`, `SourceItemCount`, `SourceSpellId`, `Flags`, `Flags2`, `SpecialFlags`, `MinimapTargetMark`, `RewardTitleId`, `RequiredPlayerKills`, `RewardTalents`, `RewardArenaPoints`, `RewardSkillId`, `RewardSkillPoints`, `RewardReputationMask`, `QuestGiverPortrait`, `RewardPackageItemId`, `QuestTurnInPortrait`, `RewardItemId1`, `RewardItemId2`, `RewardItemId3`, `RewardItemId4`, `RewardItemCount1`, `RewardItemCount2`, `RewardItemCount3`, `RewardItemCount4`, `RewardChoiceItemId1`, `RewardChoiceItemId2`, `RewardChoiceItemId3`, `RewardChoiceItemId4`, `RewardChoiceItemId5`, `RewardChoiceItemId6`, `RewardChoiceItemCount1`, `RewardChoiceItemCount2`, `RewardChoiceItemCount3`, `RewardChoiceItemCount4`, `RewardChoiceItemCount5`, `RewardChoiceItemCount6`, `RewardFactionId1`, `RewardFactionId2`, `RewardFactionId3`, `RewardFactionId4`, `RewardFactionId5`, `RewardFactionValueId1`, `RewardFactionValueId2`, `RewardFactionValueId3`, `RewardFactionValueId4`, `RewardFactionValueId5`, `RewardFactionValueIdOverride1`, `RewardFactionValueIdOverride2`, `RewardFactionValueIdOverride3`, `RewardFactionValueIdOverride4`, `RewardFactionValueIdOverride5`, `PointMapId`, `PointX`, `PointY`, `PointOption`, `Title`, `Objectives`, `Details`, `EndText`, `OfferRewardText`, `RequestItemsText`, `CompletedText`, `RequiredNpcOrGo1`, `RequiredNpcOrGo2`, `RequiredNpcOrGo3`, `RequiredNpcOrGo4`, `RequiredNpcOrGo5`, `RequiredNpcOrGo6`, `RequiredNpcOrGo7`, `RequiredNpcOrGo8`, `RequiredNpcOrGo9`, `RequiredNpcOrGo10`, `RequiredNpcOrGoCount1`, `RequiredNpcOrGoCount2`, `RequiredNpcOrGoCount3`, `RequiredNpcOrGoCount4`, `RequiredNpcOrGoCount5`, `RequiredNpcOrGoCount6`, `RequiredNpcOrGoCount7`, `RequiredNpcOrGoCount8`, `RequiredNpcOrGoCount9`, `RequiredNpcOrGoCount10`, `RequiredSourceItemId1`, `RequiredSourceItemId2`, `RequiredSourceItemId3`, `RequiredSourceItemId4`, `RequiredSourceItemCount1`, `RequiredSourceItemCount2`, `RequiredSourceItemCount3`, `RequiredSourceItemCount4`, `RequiredItemId1`, `RequiredItemId2`, `RequiredItemId3`, `RequiredItemId4`, `RequiredItemId5`, `RequiredItemId6`, `RequiredItemId7`, `RequiredItemId8`, `RequiredItemId9`, `RequiredItemId10`, `RequiredItemCount1`, `RequiredItemCount2`, `RequiredItemCount3`, `RequiredItemCount4`, `RequiredItemCount5`, `RequiredItemCount6`, `RequiredItemCount7`, `RequiredItemCount8`, `RequiredItemCount9`, `RequiredItemCount10`, `RequiredSpell`, `RequiredSpellCast1`, `RequiredSpellCast2`, `RequiredSpellCast3`, `RequiredSpellCast4`, `RequiredSpellCast5`, `RequiredSpellCast6`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ObjectiveText5`, `ObjectiveText6`, `ObjectiveText7`, `ObjectiveText8`, `ObjectiveText9`, `ObjectiveText10`, `RewardCurrencyId1`, `RewardCurrencyId2`, `RewardCurrencyId3`, `RewardCurrencyId4`, `RewardCurrencyCount1`, `RewardCurrencyCount2`, `RewardCurrencyCount3`, `RewardCurrencyCount4`, `RequiredCurrencyId1`, `RequiredCurrencyId2`, `RequiredCurrencyId3`, `RequiredCurrencyId4`, `RequiredCurrencyCount1`, `RequiredCurrencyCount2`, `RequiredCurrencyCount3`, `RequiredCurrencyCount4`, `QuestGiverTextWindow`, `QuestGiverTargetName`, `QuestTurnTextWindow`, `QuestTurnTargetName`, `SoundAccept`, `SoundTurnIn`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `EmoteOnIncomplete`, `EmoteOnComplete`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `WDBVerified`) VALUES 
('29312', '0', '1', '85', '0', '0', '0', '0', '0', '-1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '29307', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '65536', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '71086', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '', '', '', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '71085', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '0', '0', '', '', '', '', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '', '', '890', '878', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1');

/*## Step 2: Quest Givers ############################################*/

/* Step 2.2 Table  `creature_questrelation */
DELETE FROM  `creature_questrelation` WHERE `quest`= 29312;
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES 
('53466', '29312');  /* Quest(29312):  ,QuestMinLevel: 85 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 


/* Step 2.2 Table  `gameobject_questrelation */
DELETE FROM  `gameobject_questrelation` WHERE `quest`= 29312;
/*## Step 3: Quest POIs ##############################################*/

/* Step 3.4 Table  `quest_poi` */
DELETE FROM  `quest_poi` WHERE `questId` = 29312;
INSERT INTO `quest_poi` (`questId`, `id`, `objIndex`, `mapid`, `WorldMapAreaId`, `unk2`, `unk3`, `unk4`, `FloorId`) VALUES 
('29312', '0', '-1', '0', '301', '0', '0', '1', '0'), 
('29312', '1', '0', '0', '301', '0', '0', '7', '251663'); 


/* Step 3.5 Table  `quest_poi_points` */
DELETE FROM  `quest_poi_points` WHERE `questId` = 29312;
INSERT INTO `quest_poi_points` (`questId`, `id`, `idx`, `x`, `y`) VALUES 
('29312', '0', '0', '-8642', '771'), 
('29312', '1', '0', '-8683', '733'); 


/*## Step 3: Quest Scripts ##############################################*/

/* Step Final Table  `quest_start_scripts` */
DELETE FROM  `quest_start_scripts` WHERE `id` = 29312;
/* Step Final Table  `quest_end_scripts` */
DELETE FROM  `quest_end_scripts` WHERE `id` = 29312;
/*## Step 4: Quest Receivers #########################################*/

/* Step 2.2 Table  `creature_involvedrelation */
DELETE FROM  `creature_involvedrelation` WHERE `quest`= 29312;
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES 
('53422', '29312');  /* Quest(29312):  ,QuestMinLevel: 85 ,QuestProfession ID: 0[THIS SKILL DONT EXIST] */ 


/* Step 2.2 Table  `gameobject_involvedrelation */
DELETE FROM  `gameobject_involvedrelation` WHERE `quest`= 29312;
/*## Step 5: Quest Items Reward ######################################*/

/* Step 5.8 Reward Items Choice: Name - Quality - SellPrice - ItemLevel - RequiredLevel */
/*
71086  5  ORANGE_LEGENDARY  70g 23s 64c  397  85  Dragonwrath, Tarecgosa's Rest
*/
/* Step 5.9 Reward Items: Name - Quality - SellPrice - ItemLevel - RequiredLevel */
/*
*/
/*## Step 6: Quest Conditions ########################################*/

/*## Step 7: Quest Needs to Work #####################################*/

/* Step 3.1 Table  `item_template */
DELETE FROM item_template WHERE entry = 71086;
INSERT INTO `item_template` (`entry`, `class`, `subclass`, `SoundOverrideSubclass`, `name`, `displayid`, `Quality`, `Flags`, `FlagsExtra`, `Unk430_1`, `Unk430_2`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_unk1_1`, `stat_unk2_1`, `stat_type2`, `stat_value2`, `stat_unk1_2`, `stat_unk2_2`, `stat_type3`, `stat_value3`, `stat_unk1_3`, `stat_unk2_3`, `stat_type4`, `stat_value4`, `stat_unk1_4`, `stat_unk2_4`, `stat_type5`, `stat_value5`, `stat_unk1_5`, `stat_unk2_5`, `stat_type6`, `stat_value6`, `stat_unk1_6`, `stat_unk2_6`, `stat_type7`, `stat_value7`, `stat_unk1_7`, `stat_unk2_7`, `stat_type8`, `stat_value8`, `stat_unk1_8`, `stat_unk2_8`, `stat_type9`, `stat_value9`, `stat_unk1_9`, `stat_unk2_9`, `stat_type10`, `stat_value10`, `stat_unk1_10`, `stat_unk2_10`, `ScalingStatDistribution`, `DamageType`, `delay`, `RangedModRange`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `description`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `RandomSuffix`, `itemset`, `MaxDurability`, `area`, `Map`, `BagFamily`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `ArmorDamageModifier`, `duration`, `ItemLimitCategory`, `HolidayId`, `StatScalingFactor`, `CurrencySubstitutionId`, `CurrencySubstitutionCount`, `flagsCustom`, `WDBVerified`) VALUES 
('71086', '2', '10', '-1', 'Dragonwrath, Tarecgosa\'s Rest', '99788', '5', '192', '6300160', '0.9892', '1', '1', '3511820', '702364', '17', '-1', '-1', '397', '85', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '5', '426', '5259', '2', '7', '730', '7889', '0', '31', '314', '3559', '0', '36', '271', '3418', '1', '45', '2786', '30121', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '3300', '0', '101056', '1', '0', '-1', '0', '-1', '101641', '0', '0', '1500', '330', '1500', '101151', '1', '0', '0', '0', '0', '0', '0', '0', '-1', '0', '-1', '0', '0', '0', '-1', '0', '-1', '1', '', '0', '0', '0', '0', '0', '2', '2', '0', '0', '0', '0', '0', '0', '0', '0', '2', '0', '2', '0', '2', '0', '4150', '0', '0', '0', '0', '0', '0.4', '0', '0', '0', '15595'); 



