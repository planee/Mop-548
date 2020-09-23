/*
SQL RoG WoW				  
Desarrollado por:
Fecha: 1/1/2020
### Scripts Privados / Derechos Reservados RoG WoW ########
### Datos SQL ###########################################*/
SET @CREATURE  	:= 'Bienvenido a RoG WoW';
SET @ENTRY 		:= '60000';
/*SET @MAP   		:= 530;       *//*(Outland)*/
/*SET @ZONE  		:= 6455;      *//*(Sunstrider Isle)*/
/*SET @AREA  		:= 3431;      *//*(Sunstrider Isle)*/
/*#######################################################*/


/* Step 1.1 Table  `quest_template` */
DELETE FROM  `quest_template` WHERE `Id` = 60000;

/*## Step 2: Quest Givers ############################################*/

/* Step 2.2 Table  `creature_questrelation */
DELETE FROM  `creature_questrelation` WHERE `quest`= 60000;


/* Step 2.2 Table  `gameobject_questrelation */
DELETE FROM  `gameobject_questrelation` WHERE `quest`= 60000;
/*## Step 3: Quest POIs ##############################################*/

/* Step 3.4 Table  `quest_poi` */
DELETE FROM  `quest_poi` WHERE `questId` = 60000;


/* Step 3.5 Table  `quest_poi_points` */
DELETE FROM  `quest_poi_points` WHERE `questId` = 60000;


/*## Step 3: Quest Scripts ##############################################*/

/* Step Final Table  `quest_start_scripts` */
DELETE FROM  `quest_start_scripts` WHERE `id` = 60000;
/* Step Final Table  `quest_end_scripts` */
DELETE FROM  `quest_end_scripts` WHERE `id` = 60000;
/*## Step 4: Quest Receivers #########################################*/

/* Step 2.2 Table  `creature_involvedrelation */
DELETE FROM  `creature_involvedrelation` WHERE `quest`= 60000;


/* Step 2.2 Table  `gameobject_involvedrelation */
DELETE FROM  `gameobject_involvedrelation` WHERE `quest`= 60000;
/*## Step 5: Quest Items Reward ######################################*/




