/*
SQLyog Community v13.1.6 (64 bit)
MySQL - 5.6.48-log 
*********************************************************************
*/
/*!40101 SET NAMES utf8 */;

create table `creature_template_addon` (
	`entry` mediumint (8),
	`path_id` int (10),
	`mount` mediumint (8),
	`bytes1` int (10),
	`bytes2` int (10),
	`emote` mediumint (8),
	`auras` text 
); 
insert into `creature_template_addon` (`entry`, `path_id`, `mount`, `bytes1`, `bytes2`, `emote`, `auras`) values('900001','0','29681','33554432','0','0','121221');
