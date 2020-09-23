/*
SQL RoG WoW				  
Desarrollado por:
Fecha: 27/10/2019
### Scripts Privados / Derechos Reservados RoG WoW ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= '';
SET @ENTRY 		:= '31281';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `quest_template` */
DELETE FROM  `quest_template` WHERE `Id` = 31281;
INSERT INTO `quest_template` (`Id`, `Method`, `Level`, `MinLevel`, `MaxLevel`, `ZoneOrSort`, `Type`, `SuggestedPlayers`, `LimitTime`, `RequiredTeam`, `RequiredClasses`, `RequiredRaces`, `RequiredSkillId`, `RequiredSkillPoints`, `RequiredFactionId1`, `RequiredFactionId2`, `RequiredFactionValue1`, `RequiredFactionValue2`, `RequiredFactionKills`, `RequiredFactionKillsCount`, `RequiredPetBattleWith`, `RequiredMinRepFaction`, `RequiredMaxRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepValue`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestIdChain`, `RewardXPId`, `RewardXPId2`, `RewardOrRequiredMoney`, `RewardMoneyMaxLevel`, `RewardSpell`, `RewardSpellCast`, `RewardHonor`, `RewardHonorMultiplier`, `RewardMailTemplateId`, `RewardMailDelay`, `SourceItemId`, `SourceItemCount`, `SourceSpellId`, `Flags`, `Flags2`, `SpecialFlags`, `MinimapTargetMark`, `RewardTitleId`, `RequiredPlayerKills`, `RewardTalents`, `RewardArenaPoints`, `RewardSkillId`, `RewardSkillPoints`, `RewardReputationMask`, `QuestGiverPortrait`, `RewardPackageItemId`, `QuestTurnInPortrait`, `RewardItemId1`, `RewardItemId2`, `RewardItemId3`, `RewardItemId4`, `RewardItemCount1`, `RewardItemCount2`, `RewardItemCount3`, `RewardItemCount4`, `RewardChoiceItemId1`, `RewardChoiceItemId2`, `RewardChoiceItemId3`, `RewardChoiceItemId4`, `RewardChoiceItemId5`, `RewardChoiceItemId6`, `RewardChoiceItemCount1`, `RewardChoiceItemCount2`, `RewardChoiceItemCount3`, `RewardChoiceItemCount4`, `RewardChoiceItemCount5`, `RewardChoiceItemCount6`, `RewardFactionId1`, `RewardFactionId2`, `RewardFactionId3`, `RewardFactionId4`, `RewardFactionId5`, `RewardFactionValueId1`, `RewardFactionValueId2`, `RewardFactionValueId3`, `RewardFactionValueId4`, `RewardFactionValueId5`, `RewardFactionValueIdOverride1`, `RewardFactionValueIdOverride2`, `RewardFactionValueIdOverride3`, `RewardFactionValueIdOverride4`, `RewardFactionValueIdOverride5`, `PointMapId`, `PointX`, `PointY`, `PointOption`, `Title`, `Objectives`, `Details`, `EndText`, `OfferRewardText`, `RequestItemsText`, `CompletedText`, `RequiredNpcOrGo1`, `RequiredNpcOrGo2`, `RequiredNpcOrGo3`, `RequiredNpcOrGo4`, `RequiredNpcOrGo5`, `RequiredNpcOrGo6`, `RequiredNpcOrGo7`, `RequiredNpcOrGo8`, `RequiredNpcOrGo9`, `RequiredNpcOrGo10`, `RequiredNpcOrGoCount1`, `RequiredNpcOrGoCount2`, `RequiredNpcOrGoCount3`, `RequiredNpcOrGoCount4`, `RequiredNpcOrGoCount5`, `RequiredNpcOrGoCount6`, `RequiredNpcOrGoCount7`, `RequiredNpcOrGoCount8`, `RequiredNpcOrGoCount9`, `RequiredNpcOrGoCount10`, `RequiredSourceItemId1`, `RequiredSourceItemId2`, `RequiredSourceItemId3`, `RequiredSourceItemId4`, `RequiredSourceItemCount1`, `RequiredSourceItemCount2`, `RequiredSourceItemCount3`, `RequiredSourceItemCount4`, `RequiredItemId1`, `RequiredItemId2`, `RequiredItemId3`, `RequiredItemId4`, `RequiredItemId5`, `RequiredItemId6`, `RequiredItemId7`, `RequiredItemId8`, `RequiredItemId9`, `RequiredItemId10`, `RequiredItemCount1`, `RequiredItemCount2`, `RequiredItemCount3`, `RequiredItemCount4`, `RequiredItemCount5`, `RequiredItemCount6`, `RequiredItemCount7`, `RequiredItemCount8`, `RequiredItemCount9`, `RequiredItemCount10`, `RequiredSpell`, `RequiredSpellCast1`, `RequiredSpellCast2`, `RequiredSpellCast3`, `RequiredSpellCast4`, `RequiredSpellCast5`, `RequiredSpellCast6`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`, `ObjectiveText5`, `ObjectiveText6`, `ObjectiveText7`, `ObjectiveText8`, `ObjectiveText9`, `ObjectiveText10`, `RewardCurrencyId1`, `RewardCurrencyId2`, `RewardCurrencyId3`, `RewardCurrencyId4`, `RewardCurrencyCount1`, `RewardCurrencyCount2`, `RewardCurrencyCount3`, `RewardCurrencyCount4`, `RequiredCurrencyId1`, `RequiredCurrencyId2`, `RequiredCurrencyId3`, `RequiredCurrencyId4`, `RequiredCurrencyCount1`, `RequiredCurrencyCount2`, `RequiredCurrencyCount3`, `RequiredCurrencyCount4`, `QuestGiverTextWindow`, `QuestGiverTargetName`, `QuestTurnTextWindow`, `QuestTurnTargetName`, `SoundAccept`, `SoundTurnIn`, `DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`, `EmoteOnIncomplete`, `EmoteOnComplete`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`, `OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4`, `StartScript`, `CompleteScript`, `WDBVerified`) VALUES 
('31281', '2', '1', '85', '0', '0', '0', '0', '0', '-1', '0', '0', '185', '525', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '31302', '0', '0', '0', '0', '0', '0', '125322', '0', '0', '1', '0', '0', '0', '0', '0', '65544', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '', '', '', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '86057', '0', '0', '0', '0', '0', '0', '0', '0', '0', '5', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '0', '0', '', '', '', '', '', '', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '', '', '890', '878', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1');

/*## Step 2: Quest Givers ############################################*/

/* Step 2.2 Table  `creature_questrelation */
DELETE FROM  `creature_questrelation` WHERE `quest`= 31281;
INSERT INTO `creature_questrelation` (`id`, `quest`) VALUES 
('64231', '31281');  /* Quest(31281):  ,QuestMinLevel: 85 ,QuestProfession ID: 185[Cooking] */ 


/* Step 2.2 Table  `gameobject_questrelation */
DELETE FROM  `gameobject_questrelation` WHERE `quest`= 31281;
/*## Step 3: Quest POIs ##############################################*/

/* Step 3.4 Table  `quest_poi` */
DELETE FROM  `quest_poi` WHERE `questId` = 31281;
INSERT INTO `quest_poi` (`questId`, `id`, `objIndex`, `mapid`, `WorldMapAreaId`, `unk2`, `unk3`, `unk4`, `FloorId`) VALUES 
('31281', '0', '-1', '870', '807', '0', '0', '0', '0'); 


/* Step 3.5 Table  `quest_poi_points` */
DELETE FROM  `quest_poi_points` WHERE `questId` = 31281;
INSERT INTO `quest_poi_points` (`questId`, `id`, `idx`, `x`, `y`) VALUES 
('31281', '0', '0', '-245', '576'); 


/*## Step 3: Quest Scripts ##############################################*/

/* Step Final Table  `quest_start_scripts` */
DELETE FROM  `quest_start_scripts` WHERE `id` = 31281;
/* Step Final Table  `quest_end_scripts` */
DELETE FROM  `quest_end_scripts` WHERE `id` = 31281;
/*## Step 4: Quest Receivers #########################################*/

/* Step 2.2 Table  `creature_involvedrelation */
DELETE FROM  `creature_involvedrelation` WHERE `quest`= 31281;
INSERT INTO `creature_involvedrelation` (`id`, `quest`) VALUES 
('64231', '31281');  /* Quest(31281):  ,QuestMinLevel: 85 ,QuestProfession ID: 185[Cooking] */ 


/* Step 2.2 Table  `gameobject_involvedrelation */
DELETE FROM  `gameobject_involvedrelation` WHERE `quest`= 31281;
/*## Step 5: Quest Items Reward ######################################*/

/* Step 5.8 Reward Items Choice: Name - Quality - SellPrice - ItemLevel - RequiredLevel */
/*
*/
/* Step 5.9 Reward Items: Name - Quality - SellPrice - ItemLevel - RequiredLevel */
/*
*/
/*## Step 6: Quest Conditions ########################################*/

/*## Step 7: Quest Needs to Work #####################################*/


