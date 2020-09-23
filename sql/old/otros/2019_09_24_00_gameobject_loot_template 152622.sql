
DELETE FROM `gameobject_loot_template` WHERE `entry`=152622;
insert into `gameobject_loot_template` (`entry`, `item`, `ChanceOrQuestChance`, `lootmode`, `groupid`, `mincountOrRef`, `maxcount`)values
('152622','49207','100','1','0','1','1'),
('152622','10714','100','1','0','1','1');

DELETE FROM `gameobject_template` WHERE `entry`=152622;
insert into `gameobject_template` (`entry`, `type`, `displayId`, `name`, `IconName`, `castBarCaption`, `unk1`, `faction`, `flags`, `size`, `questItem1`, `questItem2`, `questItem3`, `questItem4`, `questItem5`, `questItem6`, `data0`, `data1`, `data2`, `data3`, `data4`, `data5`, `data6`, `data7`, `data8`, `data9`, `data10`, `data11`, `data12`, `data13`, `data14`, `data15`, `data16`, `data17`, `data18`, `data19`, `data20`, `data21`, `data22`, `data23`, `data24`, `data25`, `data26`, `data27`, `data28`, `data29`, `data30`, `data31`, `unkInt32`, `AIName`, `ScriptName`, `WDBVerified`) values
('152622','3','219','Azsharite Formation','','Collecting','','0','0','1','49207','0','0','0','0','0','93','152622','30','1','0','0','0','0','0','0','0','0','0','0','19676','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','','','15595');
