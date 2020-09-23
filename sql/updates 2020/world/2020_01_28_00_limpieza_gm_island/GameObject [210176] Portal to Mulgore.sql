/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 28/1/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Portal to Mulgore';
SET @ENTRY 		:= '210176';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 4.1 Table  `gameobject_template */
DELETE FROM `gameobject_template` WHERE `entry` = @ENTRY;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`,  `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `unkInt32`, `AIName`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '22', '4397', 'Portal to Mulgore', '', '', '', '1735', '0', '1', '0', '0', '0', '0', '0', '0', '103582', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '15595'); 


/* Step 4.1 Table  `gameobject */
DELETE FROM `gameobject` WHERE `id` = @ENTRY;
INSERT INTO `gameobject` (`guid`, `id`, `map`, `zoneId`, `areaId`, `spawnMask`, `phaseMask`, `phaseId`, `position_x`, `position_y`, `position_z`, `orientation`,`rotation0`, `rotation1`, `rotation2`, `rotation3`, `spawntimesecs`, `animprogress`, `state`, `isActive`, `protect_anti_doublet`) VALUES 
(NULL, @ENTRY, '974', '5861', '5904', '1', '1', '0', '-4447.96', '6331.43', '13.2646', '0', '0', '0', '0', '1', '7200', '255', '1', '0', '0'); 


/*## Step 2: GObject Loots ###########################################*/

/* Step x.x Table  `gameobject_loot_template */
DELETE FROM gameobject_loot_template WHERE  `entry` = @ENTRY;
/* Step 2.6 GObject > Quest Items Data: ItemID - Quality - SellPrice - ItemLevel - RequiredLevel - Name */
/*



/* Step 2.2 Table  `gameobject_questrelation */
DELETE FROM  `gameobject_questrelation` WHERE `id`= @ENTRY;
/* Step 2.2 Table  `gameobject_involvedrelation */
DELETE FROM  `gameobject_involvedrelation` WHERE `id`= @ENTRY;
/*## Step 3: GObjects Conditions #####################################*/

/*## Step 4: GObjects Needs to Work ##################################*/


