/*
SQLyog Community v13.1.6 (64 bit)
MySQL - 5.6.48-log 
*********************************************************************
*/
/*!40101 SET NAMES utf8 */;

create table `spell_bonus_data` (
	`entry` mediumint (8),
	`direct_bonus` float ,
	`dot_bonus` float ,
	`ap_bonus` float ,
	`ap_dot_bonus` float ,
	`comments` varchar (765)
); 
insert into `spell_bonus_data` (`entry`, `direct_bonus`, `dot_bonus`, `ap_bonus`, `ap_dot_bonus`, `comments`) values('53385','2.58','0','-1','-1','Paladin - Tormenta Divina');
