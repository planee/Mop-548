/*
SQL ZONAXTREMA 				  
Desarrollado por:
Fecha: 28/1/2020
### Scripts Trabajados por ZONAXTREMA  ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'The Raven\'s Claw,';
SET @ENTRY 		:= '0';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 4.1 Table  `gameobject_template */
DELETE FROM `gameobject_template` WHERE `entry` = @ENTRY;
INSERT INTO `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`,  `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `unkInt32`, `AIName`, `ScriptName`, `WDBVerified`) VALUES 
(@ENTRY, '1', '12', 'The Raven\'s Claw,', '', '', '', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '', '', '1'); 


/* Step 4.1 Table  `gameobject */
DELETE FROM `gameobject` WHERE `id` = @ENTRY;
/*## Step 2: GObject Loots ###########################################*/

/* Step x.x Table  `gameobject_loot_template */
DELETE FROM gameobject_loot_template WHERE  `entry` = @ENTRY;
/* Step 2.6 GObject > Quest Items Data: ItemID - Quality - SellPrice - ItemLevel - RequiredLevel - Name */
/*



/*## Step 3: GObjects Conditions #####################################*/

/*## Step 4: GObjects Needs to Work ##################################*/


