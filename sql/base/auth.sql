-- --------------------------------------------------------
-- Host:                         127.0.0.1
-- Versión del servidor:         5.5.9-log - MySQL Community Server (GPL)
-- SO del servidor:              Win32
-- HeidiSQL Versión:             9.4.0.5186
-- --------------------------------------------------------

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET NAMES utf8 */;
/*!50503 SET NAMES utf8mb4 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

-- Volcando estructura para tabla auth.account
CREATE TABLE IF NOT EXISTS `account` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Identifier',
  `username` varchar(32) NOT NULL DEFAULT '',
  `username_wod623` varchar(250) NOT NULL DEFAULT '',
  `token_key_wod623` varchar(100) NOT NULL DEFAULT '',
  `sha_pass_hash` varchar(40) NOT NULL DEFAULT '',
  `sha_pass_hash_wod623` varchar(40) NOT NULL DEFAULT '',
  `sessionkey` varchar(80) NOT NULL DEFAULT '',
  `v` varchar(64) NOT NULL DEFAULT '',
  `s` varchar(64) NOT NULL DEFAULT '',
  `token_key_548` varchar(100) NOT NULL DEFAULT '',
  `token_key_335a` varchar(100) NOT NULL DEFAULT '',
  `email` varchar(254) NOT NULL DEFAULT '',
  `reg_mail_335a` varchar(255) NOT NULL DEFAULT '',
  `joindate` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `last_ip` varchar(15) NOT NULL DEFAULT '127.0.0.1',
  `last_attempt_ip_548` varchar(15) NOT NULL DEFAULT '127.0.0.1',
  `last_attempt_ip_335a` varchar(15) NOT NULL DEFAULT '127.0.0.1',
  `failed_logins` int(10) unsigned NOT NULL DEFAULT '0',
  `locked` smallint(3) NOT NULL DEFAULT '1',
  `lock_country_335a` varchar(2) NOT NULL DEFAULT '00',
  `last_login` timestamp NOT NULL DEFAULT '0000-00-00 00:00:00',
  `online` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `expansion` tinyint(3) unsigned NOT NULL DEFAULT '5',
  `mutetime` bigint(20) NOT NULL DEFAULT '0',
  `mutereason` varchar(255) NOT NULL DEFAULT ' ',
  `muteby` varchar(50) DEFAULT NULL,
  `locale` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `os` varchar(4) NOT NULL DEFAULT '',
  `recruiter` int(10) unsigned NOT NULL DEFAULT '0',
  `bnet2_pass_hash` varchar(256) NOT NULL DEFAULT '',
  `bnet2_salt` varchar(64) NOT NULL DEFAULT '',
  `google_auth` varchar(15) DEFAULT NULL,
  `rsa_clear` blob,
  `admin` tinyint(3) NOT NULL DEFAULT '0',
  `activate` tinyint(4) DEFAULT '0',
  `payment` tinyint(4) DEFAULT '0',
  `service_flags` int(10) unsigned NOT NULL DEFAULT '0',
  `custom_flags` int(10) unsigned NOT NULL DEFAULT '0',
  `forum_email` varchar(254) DEFAULT '',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_username` (`username`),
  KEY `recruiterIndex` (`recruiter`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Account System';

-- Volcando datos para la tabla auth.account: 0 rows
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
/*!40000 ALTER TABLE `account` ENABLE KEYS */;

-- Volcando estructura para tabla auth.accounts_to_delete
CREATE TABLE IF NOT EXISTS `accounts_to_delete` (
  `id` int(11) unsigned NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Account System';

-- Volcando datos para la tabla auth.accounts_to_delete: 0 rows
/*!40000 ALTER TABLE `accounts_to_delete` DISABLE KEYS */;
/*!40000 ALTER TABLE `accounts_to_delete` ENABLE KEYS */;

-- Volcando estructura para tabla auth.account_access
CREATE TABLE IF NOT EXISTS `account_access` (
  `id` int(10) unsigned NOT NULL,
  `gmlevel` tinyint(3) unsigned NOT NULL,
  `RealmID` int(11) NOT NULL DEFAULT '-1',
  `comment` varchar(35) NOT NULL DEFAULT 'name of the account',
  PRIMARY KEY (`id`,`RealmID`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.account_access: 0 rows
/*!40000 ALTER TABLE `account_access` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_access` ENABLE KEYS */;

-- Volcando estructura para tabla auth.account_banned
CREATE TABLE IF NOT EXISTS `account_banned` (
  `id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Account id',
  `externalban` int(10) unsigned NOT NULL DEFAULT '0',
  `bandate` int(10) unsigned NOT NULL DEFAULT '0',
  `unbandate` int(10) unsigned NOT NULL DEFAULT '0',
  `bannedby` varchar(50) NOT NULL,
  `banreason` varchar(255) NOT NULL,
  `active` tinyint(3) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`,`bandate`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Ban List';

-- Volcando datos para la tabla auth.account_banned: 0 rows
/*!40000 ALTER TABLE `account_banned` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_banned` ENABLE KEYS */;

-- Volcando estructura para tabla auth.account_premium
CREATE TABLE IF NOT EXISTS `account_premium` (
  `id` int(11) NOT NULL DEFAULT '0' COMMENT 'Account id',
  `setdate` bigint(40) NOT NULL DEFAULT '0',
  `unsetdate` bigint(40) NOT NULL DEFAULT '0',
  `premium_type` tinyint(4) unsigned NOT NULL DEFAULT '1',
  `active` tinyint(4) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`,`setdate`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Premium Accounts';

-- Volcando datos para la tabla auth.account_premium: 0 rows
/*!40000 ALTER TABLE `account_premium` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_premium` ENABLE KEYS */;

-- Volcando estructura para tabla auth.account_punishment
CREATE TABLE IF NOT EXISTS `account_punishment` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `account` int(11) unsigned NOT NULL,
  `by` int(11) NOT NULL,
  `penalty_points` int(11) unsigned NOT NULL,
  `comment` varchar(255) NOT NULL,
  `time` bigint(20) unsigned NOT NULL,
  `active` tinyint(3) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=99 DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.account_punishment: 0 rows
/*!40000 ALTER TABLE `account_punishment` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_punishment` ENABLE KEYS */;

-- Volcando estructura para tabla auth.account_rates
CREATE TABLE IF NOT EXISTS `account_rates` (
  `account_id` int(10) NOT NULL DEFAULT '0',
  `player_guid` int(10) NOT NULL DEFAULT '0',
  `playerqueue` int(10) NOT NULL DEFAULT '0' COMMENT 'The player have to wait player queue to enter',
  `xp_rate` float NOT NULL DEFAULT '1',
  `reputation_rate` float NOT NULL DEFAULT '1',
  `money_rate` float NOT NULL DEFAULT '1',
  `skill_rate` float NOT NULL DEFAULT '1',
  `comment` text,
  PRIMARY KEY (`account_id`,`player_guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.account_rates: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `account_rates` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_rates` ENABLE KEYS */;

-- Volcando estructura para tabla auth.account_rates_tournament
CREATE TABLE IF NOT EXISTS `account_rates_tournament` (
  `account_id` int(10) NOT NULL DEFAULT '0',
  `player_guid` int(10) NOT NULL DEFAULT '0',
  `playerqueue` int(10) NOT NULL DEFAULT '0' COMMENT 'The player have to wait player queue to enter',
  `xp_rate` float NOT NULL DEFAULT '1',
  `reputation_rate` float NOT NULL DEFAULT '1',
  `money_rate` float NOT NULL DEFAULT '1',
  `skill_rate` float NOT NULL DEFAULT '1',
  `comment` text,
  PRIMARY KEY (`account_id`,`player_guid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.account_rates_tournament: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `account_rates_tournament` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_rates_tournament` ENABLE KEYS */;

-- Volcando estructura para tabla auth.account_tempban
CREATE TABLE IF NOT EXISTS `account_tempban` (
  `accountId` int(11) NOT NULL,
  `reason` varchar(255) NOT NULL,
  PRIMARY KEY (`accountId`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.account_tempban: 0 rows
/*!40000 ALTER TABLE `account_tempban` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_tempban` ENABLE KEYS */;

-- Volcando estructura para tabla auth.account_warning
CREATE TABLE IF NOT EXISTS `account_warning` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `accountId` int(11) unsigned NOT NULL,
  `by_account` int(11) unsigned NOT NULL,
  `comment` varchar(255) NOT NULL,
  `time` bigint(20) unsigned NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=169 DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.account_warning: 0 rows
/*!40000 ALTER TABLE `account_warning` DISABLE KEYS */;
/*!40000 ALTER TABLE `account_warning` ENABLE KEYS */;

-- Volcando estructura para tabla auth.bug_tickets
CREATE TABLE IF NOT EXISTS `bug_tickets` (
  `ticketId` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `realm` int(10) unsigned NOT NULL DEFAULT '0',
  `guid` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier of ticket creator',
  `message` text NOT NULL,
  `createTime` int(10) unsigned NOT NULL DEFAULT '0',
  `pool` varchar(32) NOT NULL,
  `mapId` smallint(5) unsigned NOT NULL DEFAULT '0',
  `posX` float NOT NULL DEFAULT '0',
  `posY` float NOT NULL DEFAULT '0',
  `posZ` float NOT NULL DEFAULT '0',
  `closedBy` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`ticketId`)
) ENGINE=MyISAM AUTO_INCREMENT=990 DEFAULT CHARSET=utf8 COMMENT='Support System';

-- Volcando datos para la tabla auth.bug_tickets: 0 rows
/*!40000 ALTER TABLE `bug_tickets` DISABLE KEYS */;
/*!40000 ALTER TABLE `bug_tickets` ENABLE KEYS */;

-- Volcando estructura para tabla auth.ip2nation
CREATE TABLE IF NOT EXISTS `ip2nation` (
  `ip` int(11) unsigned NOT NULL DEFAULT '0',
  `country` varchar(2) NOT NULL DEFAULT '',
  KEY `ip` (`ip`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.ip2nation: 0 rows
/*!40000 ALTER TABLE `ip2nation` DISABLE KEYS */;
/*!40000 ALTER TABLE `ip2nation` ENABLE KEYS */;

-- Volcando estructura para tabla auth.ip2nationcountries
CREATE TABLE IF NOT EXISTS `ip2nationcountries` (
  `code` varchar(2) NOT NULL DEFAULT '',
  `iso_code_2` varchar(2) NOT NULL DEFAULT '',
  `iso_code_3` varchar(3) DEFAULT '',
  `iso_country` varchar(255) NOT NULL DEFAULT '',
  `country` varchar(255) NOT NULL DEFAULT '',
  `lat` float NOT NULL DEFAULT '0',
  `lon` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`code`),
  KEY `code` (`code`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.ip2nationcountries: 0 rows
/*!40000 ALTER TABLE `ip2nationcountries` DISABLE KEYS */;
/*!40000 ALTER TABLE `ip2nationcountries` ENABLE KEYS */;

-- Volcando estructura para tabla auth.ip_banned
CREATE TABLE IF NOT EXISTS `ip_banned` (
  `ip` varchar(15) NOT NULL DEFAULT '127.0.0.1',
  `bandate` int(10) unsigned NOT NULL,
  `unbandate` int(10) NOT NULL,
  `bannedby` varchar(50) NOT NULL DEFAULT '[Console]',
  `banreason` varchar(255) NOT NULL DEFAULT 'no reason',
  PRIMARY KEY (`ip`,`bandate`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Banned IPs';

-- Volcando datos para la tabla auth.ip_banned: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `ip_banned` DISABLE KEYS */;
/*!40000 ALTER TABLE `ip_banned` ENABLE KEYS */;

-- Volcando estructura para tabla auth.ip_banned_copy
CREATE TABLE IF NOT EXISTS `ip_banned_copy` (
  `ip` varchar(15) NOT NULL DEFAULT '127.0.0.1',
  `bandate` int(10) unsigned NOT NULL,
  `unbandate` int(10) NOT NULL,
  `bannedby` varchar(50) NOT NULL DEFAULT '[Console]',
  `banreason` varchar(255) NOT NULL DEFAULT 'no reason',
  PRIMARY KEY (`ip`,`bandate`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Banned IPs';

-- Volcando datos para la tabla auth.ip_banned_copy: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `ip_banned_copy` DISABLE KEYS */;
/*!40000 ALTER TABLE `ip_banned_copy` ENABLE KEYS */;

-- Volcando estructura para tabla auth.lk335a_account_access
CREATE TABLE IF NOT EXISTS `lk335a_account_access` (
  `id` int(10) unsigned NOT NULL,
  `gmlevel` tinyint(3) unsigned NOT NULL,
  `RealmID` int(11) NOT NULL DEFAULT '-1',
  PRIMARY KEY (`id`,`RealmID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.lk335a_account_access: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `lk335a_account_access` DISABLE KEYS */;
/*!40000 ALTER TABLE `lk335a_account_access` ENABLE KEYS */;

-- Volcando estructura para tabla auth.lk335a_account_muted
CREATE TABLE IF NOT EXISTS `lk335a_account_muted` (
  `guid` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Global Unique Identifier',
  `mutedate` int(10) unsigned NOT NULL DEFAULT '0',
  `mutetime` int(10) unsigned NOT NULL DEFAULT '0',
  `mutedby` varchar(50) NOT NULL,
  `mutereason` varchar(255) NOT NULL,
  PRIMARY KEY (`guid`,`mutedate`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='mute List';

-- Volcando datos para la tabla auth.lk335a_account_muted: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `lk335a_account_muted` DISABLE KEYS */;
/*!40000 ALTER TABLE `lk335a_account_muted` ENABLE KEYS */;

-- Volcando estructura para tabla auth.lk335a_autobroadcast
CREATE TABLE IF NOT EXISTS `lk335a_autobroadcast` (
  `realmid` int(11) NOT NULL DEFAULT '-1',
  `id` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `weight` tinyint(3) unsigned DEFAULT '1',
  `text` longtext NOT NULL,
  PRIMARY KEY (`id`,`realmid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.lk335a_autobroadcast: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `lk335a_autobroadcast` DISABLE KEYS */;
/*!40000 ALTER TABLE `lk335a_autobroadcast` ENABLE KEYS */;

-- Volcando estructura para tabla auth.lk335a_ip2nation
CREATE TABLE IF NOT EXISTS `lk335a_ip2nation` (
  `ip` int(11) unsigned NOT NULL DEFAULT '0',
  `country` char(2) NOT NULL DEFAULT '',
  KEY `ip` (`ip`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.lk335a_ip2nation: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `lk335a_ip2nation` DISABLE KEYS */;
/*!40000 ALTER TABLE `lk335a_ip2nation` ENABLE KEYS */;

-- Volcando estructura para tabla auth.lk335a_ip2nationcountries
CREATE TABLE IF NOT EXISTS `lk335a_ip2nationcountries` (
  `code` varchar(4) NOT NULL DEFAULT '',
  `iso_code_2` varchar(2) NOT NULL DEFAULT '',
  `iso_code_3` varchar(3) DEFAULT '',
  `iso_country` varchar(255) NOT NULL DEFAULT '',
  `country` varchar(255) NOT NULL DEFAULT '',
  `lat` float NOT NULL DEFAULT '0',
  `lon` float NOT NULL DEFAULT '0',
  PRIMARY KEY (`code`),
  KEY `code` (`code`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.lk335a_ip2nationcountries: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `lk335a_ip2nationcountries` DISABLE KEYS */;
/*!40000 ALTER TABLE `lk335a_ip2nationcountries` ENABLE KEYS */;

-- Volcando estructura para tabla auth.lk335a_logs
CREATE TABLE IF NOT EXISTS `lk335a_logs` (
  `time` int(10) unsigned NOT NULL,
  `realm` int(10) unsigned NOT NULL,
  `type` varchar(250) NOT NULL,
  `level` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `string` text CHARACTER SET latin1
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.lk335a_logs: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `lk335a_logs` DISABLE KEYS */;
/*!40000 ALTER TABLE `lk335a_logs` ENABLE KEYS */;

-- Volcando estructura para tabla auth.lk335a_logs_ip_actions
CREATE TABLE IF NOT EXISTS `lk335a_logs_ip_actions` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Unique Identifier',
  `account_id` int(10) unsigned NOT NULL COMMENT 'Account ID',
  `character_guid` int(10) unsigned NOT NULL COMMENT 'Character Guid',
  `type` tinyint(3) unsigned NOT NULL,
  `ip` varchar(15) NOT NULL DEFAULT '127.0.0.1',
  `systemnote` text COMMENT 'Notes inserted by system',
  `unixtime` int(10) unsigned NOT NULL COMMENT 'Unixtime',
  `time` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'Timestamp',
  `comment` text COMMENT 'Allows users to add a comment',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Used to log ips of individual actions';

-- Volcando datos para la tabla auth.lk335a_logs_ip_actions: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `lk335a_logs_ip_actions` DISABLE KEYS */;
/*!40000 ALTER TABLE `lk335a_logs_ip_actions` ENABLE KEYS */;

-- Volcando estructura para tabla auth.lk335a_rbac_account_groups
CREATE TABLE IF NOT EXISTS `lk335a_rbac_account_groups` (
  `accountId` int(10) unsigned NOT NULL COMMENT 'Account id',
  `groupId` int(10) unsigned NOT NULL COMMENT 'Group id',
  `realmId` int(11) NOT NULL DEFAULT '-1' COMMENT 'Realm Id, -1 means all',
  PRIMARY KEY (`accountId`,`groupId`,`realmId`),
  KEY `fk__rbac_account_groups__rbac_groups` (`groupId`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Account-Group relation';

-- Volcando datos para la tabla auth.lk335a_rbac_account_groups: 0 rows
/*!40000 ALTER TABLE `lk335a_rbac_account_groups` DISABLE KEYS */;
/*!40000 ALTER TABLE `lk335a_rbac_account_groups` ENABLE KEYS */;

-- Volcando estructura para tabla auth.lk335a_rbac_account_permissions
CREATE TABLE IF NOT EXISTS `lk335a_rbac_account_permissions` (
  `accountId` int(10) unsigned NOT NULL COMMENT 'Account id',
  `permissionId` int(10) unsigned NOT NULL COMMENT 'Permission id',
  `granted` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'Granted = 1, Denied = 0',
  `realmId` int(11) NOT NULL DEFAULT '-1' COMMENT 'Realm Id, -1 means all',
  PRIMARY KEY (`accountId`,`permissionId`,`realmId`),
  KEY `fk__rbac_account_roles__rbac_permissions` (`permissionId`),
  CONSTRAINT `lk335a_rbac_account_permissions_ibfk_2` FOREIGN KEY (`permissionId`) REFERENCES `lk335a_rbac_permissions` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Account-Permission relation';

-- Volcando datos para la tabla auth.lk335a_rbac_account_permissions: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `lk335a_rbac_account_permissions` DISABLE KEYS */;
/*!40000 ALTER TABLE `lk335a_rbac_account_permissions` ENABLE KEYS */;

-- Volcando estructura para tabla auth.lk335a_rbac_default_permissions
CREATE TABLE IF NOT EXISTS `lk335a_rbac_default_permissions` (
  `secId` int(10) unsigned NOT NULL COMMENT 'Security Level id',
  `permissionId` int(10) unsigned NOT NULL COMMENT 'permission id',
  `realmId` int(11) NOT NULL DEFAULT '-1' COMMENT 'Realm Id, -1 means all',
  PRIMARY KEY (`secId`,`permissionId`,`realmId`),
  KEY `fk__rbac_default_permissions__rbac_permissions` (`permissionId`),
  CONSTRAINT `fk__rbac_default_permissions__rbac_permissions` FOREIGN KEY (`permissionId`) REFERENCES `lk335a_rbac_permissions` (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Default permission to assign to different account security levels';

-- Volcando datos para la tabla auth.lk335a_rbac_default_permissions: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `lk335a_rbac_default_permissions` DISABLE KEYS */;
/*!40000 ALTER TABLE `lk335a_rbac_default_permissions` ENABLE KEYS */;

-- Volcando estructura para tabla auth.lk335a_rbac_group_roles
CREATE TABLE IF NOT EXISTS `lk335a_rbac_group_roles` (
  `groupId` int(10) unsigned NOT NULL COMMENT 'group id',
  `roleId` int(10) unsigned NOT NULL COMMENT 'Role id',
  PRIMARY KEY (`groupId`,`roleId`),
  KEY `fk__rbac_group_roles__rbac_roles` (`roleId`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Group Role relation';

-- Volcando datos para la tabla auth.lk335a_rbac_group_roles: 0 rows
/*!40000 ALTER TABLE `lk335a_rbac_group_roles` DISABLE KEYS */;
/*!40000 ALTER TABLE `lk335a_rbac_group_roles` ENABLE KEYS */;

-- Volcando estructura para tabla auth.lk335a_rbac_linked_permissions
CREATE TABLE IF NOT EXISTS `lk335a_rbac_linked_permissions` (
  `id` int(10) unsigned NOT NULL COMMENT 'Permission id',
  `linkedId` int(10) unsigned NOT NULL COMMENT 'Linked Permission id',
  PRIMARY KEY (`id`,`linkedId`),
  KEY `fk__rbac_linked_permissions__rbac_permissions1` (`id`),
  KEY `fk__rbac_linked_permissions__rbac_permissions2` (`linkedId`),
  CONSTRAINT `fk__rbac_linked_permissions__rbac_permissions1` FOREIGN KEY (`id`) REFERENCES `lk335a_rbac_permissions` (`id`) ON DELETE CASCADE,
  CONSTRAINT `fk__rbac_linked_permissions__rbac_permissions2` FOREIGN KEY (`linkedId`) REFERENCES `lk335a_rbac_permissions` (`id`) ON DELETE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Permission - Linked Permission relation';

-- Volcando datos para la tabla auth.lk335a_rbac_linked_permissions: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `lk335a_rbac_linked_permissions` DISABLE KEYS */;
/*!40000 ALTER TABLE `lk335a_rbac_linked_permissions` ENABLE KEYS */;

-- Volcando estructura para tabla auth.lk335a_rbac_permissions
CREATE TABLE IF NOT EXISTS `lk335a_rbac_permissions` (
  `id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Permission id',
  `name` varchar(100) NOT NULL COMMENT 'Permission name',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Permission List';

-- Volcando datos para la tabla auth.lk335a_rbac_permissions: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `lk335a_rbac_permissions` DISABLE KEYS */;
/*!40000 ALTER TABLE `lk335a_rbac_permissions` ENABLE KEYS */;

-- Volcando estructura para tabla auth.lk335a_updates
CREATE TABLE IF NOT EXISTS `lk335a_updates` (
  `name` varchar(200) NOT NULL COMMENT 'filename with extension of the update.',
  `hash` char(40) DEFAULT '' COMMENT 'sha1 hash of the sql file.',
  `state` enum('RELEASED','ARCHIVED') NOT NULL DEFAULT 'RELEASED' COMMENT 'defines if an update is released or archived.',
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP COMMENT 'timestamp when the query was applied.',
  `speed` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'time the query takes to apply in ms.',
  PRIMARY KEY (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='List of all applied updates in this database.';

-- Volcando datos para la tabla auth.lk335a_updates: 0 rows
/*!40000 ALTER TABLE `lk335a_updates` DISABLE KEYS */;
/*!40000 ALTER TABLE `lk335a_updates` ENABLE KEYS */;

-- Volcando estructura para tabla auth.lk335a_updates_include
CREATE TABLE IF NOT EXISTS `lk335a_updates_include` (
  `path` varchar(200) NOT NULL COMMENT 'directory to include. $ means relative to the source directory.',
  `state` enum('RELEASED','ARCHIVED') NOT NULL DEFAULT 'RELEASED' COMMENT 'defines if the directory contains released or archived updates.',
  PRIMARY KEY (`path`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='List of directories where we want to include sql updates.';

-- Volcando datos para la tabla auth.lk335a_updates_include: 0 rows
/*!40000 ALTER TABLE `lk335a_updates_include` DISABLE KEYS */;
/*!40000 ALTER TABLE `lk335a_updates_include` ENABLE KEYS */;

-- Volcando estructura para tabla auth.logs
CREATE TABLE IF NOT EXISTS `logs` (
  `time` int(10) unsigned NOT NULL,
  `realm` int(10) unsigned NOT NULL,
  `type` tinyint(3) unsigned NOT NULL,
  `level` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `string` text CHARACTER SET latin1
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.logs: 0 rows
/*!40000 ALTER TABLE `logs` DISABLE KEYS */;
/*!40000 ALTER TABLE `logs` ENABLE KEYS */;

-- Volcando estructura para tabla auth.mop548_account_access
CREATE TABLE IF NOT EXISTS `mop548_account_access` (
  `id` int(10) unsigned NOT NULL,
  `gmlevel` tinyint(3) unsigned NOT NULL,
  `RealmID` int(11) NOT NULL DEFAULT '-1',
  `comment` text,
  PRIMARY KEY (`id`,`RealmID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.mop548_account_access: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `mop548_account_access` DISABLE KEYS */;
/*!40000 ALTER TABLE `mop548_account_access` ENABLE KEYS */;

-- Volcando estructura para tabla auth.mop548_account_log_ip
CREATE TABLE IF NOT EXISTS `mop548_account_log_ip` (
  `accountid` int(11) unsigned NOT NULL,
  `ip` varchar(30) NOT NULL DEFAULT '0.0.0.0',
  `date` datetime DEFAULT NULL,
  PRIMARY KEY (`accountid`,`ip`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- Volcando datos para la tabla auth.mop548_account_log_ip: 0 rows
/*!40000 ALTER TABLE `mop548_account_log_ip` DISABLE KEYS */;
/*!40000 ALTER TABLE `mop548_account_log_ip` ENABLE KEYS */;

-- Volcando estructura para tabla auth.mop548_account_premium
CREATE TABLE IF NOT EXISTS `mop548_account_premium` (
  `id` int(11) NOT NULL DEFAULT '0' COMMENT 'Account id',
  `setdate` bigint(40) NOT NULL DEFAULT '0',
  `unsetdate` bigint(40) NOT NULL DEFAULT '0',
  `premium_type` tinyint(4) unsigned NOT NULL DEFAULT '1',
  `gm` varchar(12) NOT NULL DEFAULT '0',
  `active` tinyint(4) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`,`setdate`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.mop548_account_premium: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `mop548_account_premium` DISABLE KEYS */;
/*!40000 ALTER TABLE `mop548_account_premium` ENABLE KEYS */;

-- Volcando estructura para tabla auth.mop548_account_spell
CREATE TABLE IF NOT EXISTS `mop548_account_spell` (
  `accountId` bigint(20) NOT NULL,
  `spell` int(10) NOT NULL,
  `active` tinyint(1) DEFAULT NULL,
  `disabled` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`accountId`,`spell`),
  KEY `account` (`accountId`) USING HASH,
  KEY `account_spell` (`accountId`,`spell`) USING HASH
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Volcando datos para la tabla auth.mop548_account_spell: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `mop548_account_spell` DISABLE KEYS */;
/*!40000 ALTER TABLE `mop548_account_spell` ENABLE KEYS */;

-- Volcando estructura para tabla auth.mop548_account_spell_tournament
CREATE TABLE IF NOT EXISTS `mop548_account_spell_tournament` (
  `accountId` int(21) unsigned NOT NULL,
  `spell` int(10) NOT NULL,
  `active` tinyint(1) DEFAULT NULL,
  `disabled` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`accountId`,`spell`),
  KEY `account` (`accountId`) USING HASH,
  KEY `account_spell` (`accountId`,`spell`) USING HASH
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Volcando datos para la tabla auth.mop548_account_spell_tournament: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `mop548_account_spell_tournament` DISABLE KEYS */;
/*!40000 ALTER TABLE `mop548_account_spell_tournament` ENABLE KEYS */;

-- Volcando estructura para tabla auth.mop548_account_vip
CREATE TABLE IF NOT EXISTS `mop548_account_vip` (
  `acc_id` int(10) NOT NULL,
  `viplevel` tinyint(4) NOT NULL DEFAULT '1',
  `active` tinyint(4) NOT NULL DEFAULT '1',
  PRIMARY KEY (`acc_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Volcando datos para la tabla auth.mop548_account_vip: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `mop548_account_vip` DISABLE KEYS */;
/*!40000 ALTER TABLE `mop548_account_vip` ENABLE KEYS */;

-- Volcando estructura para tabla auth.mop548_chat_filter
CREATE TABLE IF NOT EXISTS `mop548_chat_filter` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Identifier',
  `text` char(64) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.mop548_chat_filter: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `mop548_chat_filter` DISABLE KEYS */;
/*!40000 ALTER TABLE `mop548_chat_filter` ENABLE KEYS */;

-- Volcando estructura para tabla auth.mop548_firewall_farms
CREATE TABLE IF NOT EXISTS `mop548_firewall_farms` (
  `ip` tinytext NOT NULL,
  `type` tinyint(1) unsigned NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Volcando datos para la tabla auth.mop548_firewall_farms: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `mop548_firewall_farms` DISABLE KEYS */;
/*!40000 ALTER TABLE `mop548_firewall_farms` ENABLE KEYS */;

-- Volcando estructura para tabla auth.mop548_ip_to_country
CREATE TABLE IF NOT EXISTS `mop548_ip_to_country` (
  `IP_FROM` double NOT NULL,
  `IP_TO` double NOT NULL,
  `COUNTRY_CODE` char(2) DEFAULT NULL,
  `COUNTRY_CODE_3` char(3) NOT NULL,
  `COUNTRY_NAME` varchar(50) DEFAULT NULL,
  PRIMARY KEY (`IP_FROM`,`IP_TO`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

-- Volcando datos para la tabla auth.mop548_ip_to_country: 0 rows
/*!40000 ALTER TABLE `mop548_ip_to_country` DISABLE KEYS */;
/*!40000 ALTER TABLE `mop548_ip_to_country` ENABLE KEYS */;

-- Volcando estructura para tabla auth.mop548_logs
CREATE TABLE IF NOT EXISTS `mop548_logs` (
  `time` int(10) unsigned NOT NULL,
  `realm` int(10) unsigned NOT NULL,
  `type` tinyint(3) unsigned NOT NULL,
  `level` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `string` text CHARACTER SET latin1
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.mop548_logs: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `mop548_logs` DISABLE KEYS */;
/*!40000 ALTER TABLE `mop548_logs` ENABLE KEYS */;

-- Volcando estructura para tabla auth.mop548_log_vote
CREATE TABLE IF NOT EXISTS `mop548_log_vote` (
  `top_name` varchar(15) NOT NULL DEFAULT 'top',
  `ip` varchar(15) NOT NULL DEFAULT '0.0.0.0',
  `date` int(11) NOT NULL,
  PRIMARY KEY (`top_name`,`ip`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Volcando datos para la tabla auth.mop548_log_vote: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `mop548_log_vote` DISABLE KEYS */;
/*!40000 ALTER TABLE `mop548_log_vote` ENABLE KEYS */;

-- Volcando estructura para tabla auth.mop548_mails
CREATE TABLE IF NOT EXISTS `mop548_mails` (
  `email` varchar(254) NOT NULL DEFAULT ''
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.mop548_mails: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `mop548_mails` DISABLE KEYS */;
/*!40000 ALTER TABLE `mop548_mails` ENABLE KEYS */;

-- Volcando estructura para tabla auth.mop548_transferts
CREATE TABLE IF NOT EXISTS `mop548_transferts` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `account` int(11) NOT NULL,
  `perso_guid` int(11) NOT NULL,
  `from` int(11) NOT NULL,
  `to` int(11) NOT NULL,
  `revision` blob NOT NULL,
  `dump` longtext NOT NULL,
  `last_error` blob NOT NULL,
  `nb_attempt` int(11) NOT NULL,
  `state` int(10) DEFAULT NULL,
  `error` int(10) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Volcando datos para la tabla auth.mop548_transferts: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `mop548_transferts` DISABLE KEYS */;
/*!40000 ALTER TABLE `mop548_transferts` ENABLE KEYS */;

-- Volcando estructura para tabla auth.mop548_transferts_logs
CREATE TABLE IF NOT EXISTS `mop548_transferts_logs` (
  `id` int(11) DEFAULT NULL,
  `account` int(11) DEFAULT NULL,
  `perso_guid` int(11) DEFAULT NULL,
  `from` int(2) DEFAULT NULL,
  `to` int(2) DEFAULT NULL,
  `dump` longtext
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Volcando datos para la tabla auth.mop548_transferts_logs: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `mop548_transferts_logs` DISABLE KEYS */;
/*!40000 ALTER TABLE `mop548_transferts_logs` ENABLE KEYS */;

-- Volcando estructura para tabla auth.rbac_account_groups
CREATE TABLE IF NOT EXISTS `rbac_account_groups` (
  `accountId` int(10) unsigned NOT NULL COMMENT 'Account id',
  `groupId` int(10) unsigned NOT NULL COMMENT 'Group id',
  `realmId` int(11) NOT NULL DEFAULT '-1' COMMENT 'Realm Id, -1 means all',
  PRIMARY KEY (`accountId`,`groupId`,`realmId`),
  KEY `fk__rbac_account_groups__rbac_groups` (`groupId`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Account-Group relation';

-- Volcando datos para la tabla auth.rbac_account_groups: 0 rows
/*!40000 ALTER TABLE `rbac_account_groups` DISABLE KEYS */;
/*!40000 ALTER TABLE `rbac_account_groups` ENABLE KEYS */;

-- Volcando estructura para tabla auth.rbac_account_permissions
CREATE TABLE IF NOT EXISTS `rbac_account_permissions` (
  `accountId` int(10) unsigned NOT NULL COMMENT 'Account id',
  `permissionId` int(10) unsigned NOT NULL COMMENT 'Permission id',
  `granted` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'Granted = 1, Denied = 0',
  `realmId` int(11) NOT NULL DEFAULT '-1' COMMENT 'Realm Id, -1 means all',
  PRIMARY KEY (`accountId`,`permissionId`,`realmId`),
  KEY `fk__rbac_account_roles__rbac_permissions` (`permissionId`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Account-Permission relation';

-- Volcando datos para la tabla auth.rbac_account_permissions: 0 rows
/*!40000 ALTER TABLE `rbac_account_permissions` DISABLE KEYS */;
/*!40000 ALTER TABLE `rbac_account_permissions` ENABLE KEYS */;

-- Volcando estructura para tabla auth.rbac_account_roles
CREATE TABLE IF NOT EXISTS `rbac_account_roles` (
  `accountId` int(10) unsigned NOT NULL COMMENT 'Account id',
  `roleId` int(10) unsigned NOT NULL COMMENT 'Role id',
  `granted` tinyint(1) NOT NULL DEFAULT '1' COMMENT 'Granted = 1, Denied = 0',
  `realmId` int(11) NOT NULL DEFAULT '-1' COMMENT 'Realm Id, -1 means all',
  PRIMARY KEY (`accountId`,`roleId`,`realmId`),
  KEY `fk__rbac_account_roles__rbac_roles` (`roleId`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Account-Role relation';

-- Volcando datos para la tabla auth.rbac_account_roles: 0 rows
/*!40000 ALTER TABLE `rbac_account_roles` DISABLE KEYS */;
/*!40000 ALTER TABLE `rbac_account_roles` ENABLE KEYS */;

-- Volcando estructura para tabla auth.rbac_groups
CREATE TABLE IF NOT EXISTS `rbac_groups` (
  `id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Group id',
  `name` varchar(100) NOT NULL COMMENT 'Group name',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Group List';

-- Volcando datos para la tabla auth.rbac_groups: 0 rows
/*!40000 ALTER TABLE `rbac_groups` DISABLE KEYS */;
/*!40000 ALTER TABLE `rbac_groups` ENABLE KEYS */;

-- Volcando estructura para tabla auth.rbac_group_roles
CREATE TABLE IF NOT EXISTS `rbac_group_roles` (
  `groupId` int(10) unsigned NOT NULL COMMENT 'group id',
  `roleId` int(10) unsigned NOT NULL COMMENT 'Role id',
  PRIMARY KEY (`groupId`,`roleId`),
  KEY `fk__rbac_group_roles__rbac_roles` (`roleId`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Group Role relation';

-- Volcando datos para la tabla auth.rbac_group_roles: 0 rows
/*!40000 ALTER TABLE `rbac_group_roles` DISABLE KEYS */;
/*!40000 ALTER TABLE `rbac_group_roles` ENABLE KEYS */;

-- Volcando estructura para tabla auth.rbac_permissions___
CREATE TABLE IF NOT EXISTS `rbac_permissions___` (
  `id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Permission id',
  `name` varchar(100) NOT NULL COMMENT 'Permission name',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Permission List';

-- Volcando datos para la tabla auth.rbac_permissions___: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `rbac_permissions___` DISABLE KEYS */;
/*!40000 ALTER TABLE `rbac_permissions___` ENABLE KEYS */;

-- Volcando estructura para tabla auth.rbac_roles
CREATE TABLE IF NOT EXISTS `rbac_roles` (
  `id` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Role id',
  `name` varchar(100) NOT NULL COMMENT 'Role name',
  PRIMARY KEY (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Roles List';

-- Volcando datos para la tabla auth.rbac_roles: 0 rows
/*!40000 ALTER TABLE `rbac_roles` DISABLE KEYS */;
/*!40000 ALTER TABLE `rbac_roles` ENABLE KEYS */;

-- Volcando estructura para tabla auth.rbac_role_permissions
CREATE TABLE IF NOT EXISTS `rbac_role_permissions` (
  `roleId` int(10) unsigned NOT NULL COMMENT 'Role id',
  `permissionId` int(10) unsigned NOT NULL COMMENT 'Permission id',
  PRIMARY KEY (`roleId`,`permissionId`),
  KEY `fk__role_permissions__rbac_permissions` (`permissionId`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Role Permission relation';

-- Volcando datos para la tabla auth.rbac_role_permissions: 0 rows
/*!40000 ALTER TABLE `rbac_role_permissions` DISABLE KEYS */;
/*!40000 ALTER TABLE `rbac_role_permissions` ENABLE KEYS */;

-- Volcando estructura para tabla auth.rbac_security_level_groups
CREATE TABLE IF NOT EXISTS `rbac_security_level_groups` (
  `secId` tinyint(3) unsigned NOT NULL COMMENT 'Security Level id',
  `groupId` int(10) unsigned NOT NULL COMMENT 'group id',
  PRIMARY KEY (`secId`,`groupId`),
  KEY `fk__rbac_security_level_groups__rbac_groups` (`groupId`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='Default groups to assign when an account is set gm level';

-- Volcando datos para la tabla auth.rbac_security_level_groups: 0 rows
/*!40000 ALTER TABLE `rbac_security_level_groups` DISABLE KEYS */;
/*!40000 ALTER TABLE `rbac_security_level_groups` ENABLE KEYS */;

-- Volcando estructura para tabla auth.realmcharacters
CREATE TABLE IF NOT EXISTS `realmcharacters` (
  `realmid` int(10) unsigned NOT NULL DEFAULT '0',
  `acctid` int(10) unsigned NOT NULL,
  `numchars` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`realmid`,`acctid`),
  KEY `acctid` (`acctid`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC COMMENT='Realm Character Tracker';

-- Volcando datos para la tabla auth.realmcharacters: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `realmcharacters` DISABLE KEYS */;
/*!40000 ALTER TABLE `realmcharacters` ENABLE KEYS */;

-- Volcando estructura para tabla auth.realmlist
CREATE TABLE IF NOT EXISTS `realmlist` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `name` varchar(32) NOT NULL DEFAULT '',
  `address` varchar(255) NOT NULL DEFAULT '127.0.0.1',
  `localAddress` varchar(255) NOT NULL DEFAULT '127.0.0.1',
  `localSubnetMask` varchar(255) NOT NULL DEFAULT '255.255.255.0',
  `port` smallint(5) unsigned NOT NULL DEFAULT '8085',
  `icon` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `flag` tinyint(3) unsigned NOT NULL DEFAULT '2',
  `timezone` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `allowedSecurityLevel` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `motd` varchar(255) NOT NULL DEFAULT 'Welcome on our server.',
  `population` float unsigned NOT NULL DEFAULT '0',
  `gamebuild` int(10) unsigned NOT NULL DEFAULT '15595',
  `online` int(10) DEFAULT '0',
  `delay` int(10) unsigned NOT NULL DEFAULT '0',
  `queue` int(10) unsigned NOT NULL DEFAULT '0',
  `lastupdate` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  UNIQUE KEY `idx_name` (`name`) USING BTREE
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8 COMMENT='Realm System';

-- Volcando datos para la tabla auth.realmlist: ~1 rows (aproximadamente)
/*!40000 ALTER TABLE `realmlist` DISABLE KEYS */;
INSERT INTO `realmlist` (`id`, `name`, `address`, `localAddress`, `localSubnetMask`, `port`, `icon`, `flag`, `timezone`, `allowedSecurityLevel`, `motd`, `population`, `gamebuild`, `online`, `delay`, `queue`, `lastupdate`) VALUES
	(1, 'Silverwing', '127.0.0.1', '127.0.0.1', '255.255.255.0', 8085, 0, 2, 1, 0, 'Welcome to Our Server.', 0, 18019, 0, 0, 0, 0);
/*!40000 ALTER TABLE `realmlist` ENABLE KEYS */;

-- Volcando estructura para tabla auth.uptime
CREATE TABLE IF NOT EXISTS `uptime` (
  `realmid` int(10) unsigned NOT NULL,
  `starttime` int(10) unsigned NOT NULL DEFAULT '0',
  `uptime` int(10) unsigned NOT NULL DEFAULT '0',
  `maxplayers` smallint(5) unsigned NOT NULL DEFAULT '0',
  `revision` varchar(255) NOT NULL DEFAULT 'Trinitycore',
  PRIMARY KEY (`realmid`,`starttime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COMMENT='Uptime system';

-- Volcando datos para la tabla auth.uptime: ~1 rows (aproximadamente)
/*!40000 ALTER TABLE `uptime` DISABLE KEYS */;
INSERT INTO `uptime` (`realmid`, `starttime`, `uptime`, `maxplayers`, `revision`) VALUES
	(1, 1561774444, 0, 0, 'WoWSource rev. 2016-04-01 00:00:00 +0000 (rev.1) (Win64, Release)');
/*!40000 ALTER TABLE `uptime` ENABLE KEYS */;

-- Volcando estructura para tabla auth.user_reporting
CREATE TABLE IF NOT EXISTS `user_reporting` (
  `ga` int(10) unsigned NOT NULL,
  `account_id` int(10) unsigned NOT NULL,
  `creation_date` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `step` int(10) NOT NULL DEFAULT '0',
  `referer` varchar(255) NOT NULL,
  `last_ip` varchar(255) NOT NULL,
  `has_view_creation` tinyint(3) unsigned DEFAULT '0',
  PRIMARY KEY (`ga`,`account_id`),
  KEY `ga_idx` (`ga`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.user_reporting: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `user_reporting` DISABLE KEYS */;
/*!40000 ALTER TABLE `user_reporting` ENABLE KEYS */;

-- Volcando estructura para tabla auth.vip_accounts
CREATE TABLE IF NOT EXISTS `vip_accounts` (
  `id` int(11) NOT NULL DEFAULT '0' COMMENT 'Account id',
  `type` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `setdate` bigint(40) NOT NULL DEFAULT '0',
  `unsetdate` bigint(40) NOT NULL DEFAULT '0',
  `active` tinyint(4) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`,`setdate`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8 COMMENT='VIP Accounts';

-- Volcando datos para la tabla auth.vip_accounts: 0 rows
/*!40000 ALTER TABLE `vip_accounts` DISABLE KEYS */;
/*!40000 ALTER TABLE `vip_accounts` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_account_access
CREATE TABLE IF NOT EXISTS `wod623_account_access` (
  `id` int(10) unsigned NOT NULL,
  `gmlevel` tinyint(3) unsigned NOT NULL,
  `RealmID` int(11) NOT NULL DEFAULT '-1',
  `comment` text,
  PRIMARY KEY (`id`,`RealmID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.wod623_account_access: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_account_access` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_account_access` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_account_battlepay
CREATE TABLE IF NOT EXISTS `wod623_account_battlepay` (
  `accountId` int(11) unsigned NOT NULL,
  `points` int(11) NOT NULL,
  PRIMARY KEY (`accountId`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_account_battlepay: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_account_battlepay` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_account_battlepay` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_account_battlepet
CREATE TABLE IF NOT EXISTS `wod623_account_battlepet` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `account` int(10) unsigned NOT NULL DEFAULT '0',
  `slot` int(11) NOT NULL DEFAULT '-1',
  `name` varchar(50) NOT NULL,
  `nameTimeStamp` int(10) unsigned NOT NULL DEFAULT '0',
  `species` int(10) unsigned NOT NULL DEFAULT '0',
  `quality` int(10) unsigned NOT NULL DEFAULT '0',
  `breed` int(10) unsigned NOT NULL DEFAULT '0',
  `level` int(10) unsigned NOT NULL DEFAULT '0',
  `xp` int(10) unsigned NOT NULL DEFAULT '0',
  `display` int(10) unsigned NOT NULL DEFAULT '0',
  `health` int(11) NOT NULL DEFAULT '0',
  `flags` int(10) unsigned NOT NULL DEFAULT '0',
  `infoPower` int(11) NOT NULL DEFAULT '0',
  `infoMaxHealth` int(11) NOT NULL DEFAULT '0',
  `infoSpeed` int(11) NOT NULL DEFAULT '0',
  `infoGender` int(11) NOT NULL DEFAULT '0',
  `declinedGenitive` varchar(50) NOT NULL,
  `declinedNative` varchar(50) NOT NULL,
  `declinedAccusative` varchar(50) NOT NULL,
  `declinedInstrumental` varchar(50) NOT NULL,
  `declinedPrepositional` varchar(50) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `account` (`account`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_account_battlepet: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_account_battlepet` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_account_battlepet` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_account_heirlooms
CREATE TABLE IF NOT EXISTS `wod623_account_heirlooms` (
  `account_id` int(10) unsigned NOT NULL DEFAULT '0',
  `heirloom_id` int(10) unsigned NOT NULL DEFAULT '0',
  `upgrade_flags` int(10) unsigned NOT NULL DEFAULT '0',
  `groupRealmMask` int(10) unsigned NOT NULL,
  PRIMARY KEY (`account_id`,`heirloom_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_account_heirlooms: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_account_heirlooms` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_account_heirlooms` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_account_log_ip
CREATE TABLE IF NOT EXISTS `wod623_account_log_ip` (
  `accountid` int(11) unsigned NOT NULL,
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `ip` varchar(30) NOT NULL DEFAULT '0.0.0.0',
  `date` datetime DEFAULT NULL,
  `error` int(10) unsigned NOT NULL DEFAULT '0',
  `source` int(10) unsigned NOT NULL DEFAULT '2',
  PRIMARY KEY (`accountid`,`ip`,`id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_account_log_ip: 0 rows
/*!40000 ALTER TABLE `wod623_account_log_ip` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_account_log_ip` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_account_loyalty
CREATE TABLE IF NOT EXISTS `wod623_account_loyalty` (
  `AccountID` int(11) unsigned NOT NULL,
  `LastClaim` int(11) NOT NULL DEFAULT '0',
  `LastEventReset` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`AccountID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_account_loyalty: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_account_loyalty` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_account_loyalty` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_account_loyalty_event
CREATE TABLE IF NOT EXISTS `wod623_account_loyalty_event` (
  `AccountID` int(11) unsigned NOT NULL,
  `Event` int(11) unsigned NOT NULL DEFAULT '0',
  `Count` int(11) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`AccountID`,`Event`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_account_loyalty_event: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_account_loyalty_event` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_account_loyalty_event` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_account_note
CREATE TABLE IF NOT EXISTS `wod623_account_note` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `account_id` int(10) unsigned DEFAULT NULL,
  `note` text,
  `date` int(11) DEFAULT NULL,
  `notedby` varchar(255) DEFAULT NULL,
  KEY `id` (`id`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_account_note: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_account_note` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_account_note` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_account_premium
CREATE TABLE IF NOT EXISTS `wod623_account_premium` (
  `id` int(11) NOT NULL DEFAULT '0' COMMENT 'Account id',
  `setdate` bigint(40) NOT NULL DEFAULT '0',
  `unsetdate` bigint(40) NOT NULL DEFAULT '0',
  `premium_type` tinyint(4) unsigned NOT NULL DEFAULT '1',
  `gm` varchar(12) NOT NULL DEFAULT '0',
  `active` tinyint(4) NOT NULL DEFAULT '1',
  PRIMARY KEY (`id`,`setdate`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.wod623_account_premium: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_account_premium` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_account_premium` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_account_spell
CREATE TABLE IF NOT EXISTS `wod623_account_spell` (
  `accountId` bigint(20) NOT NULL,
  `spell` int(10) NOT NULL,
  `active` tinyint(1) DEFAULT NULL,
  `disabled` tinyint(1) DEFAULT NULL,
  `IsMountFavorite` tinyint(1) NOT NULL DEFAULT '0',
  `groupRealmMask` int(10) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`accountId`,`spell`),
  KEY `account` (`accountId`) USING HASH,
  KEY `account_spell` (`accountId`,`spell`) USING HASH
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Volcando datos para la tabla auth.wod623_account_spell: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_account_spell` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_account_spell` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_account_spell_old
CREATE TABLE IF NOT EXISTS `wod623_account_spell_old` (
  `accountId` int(20) NOT NULL,
  `spell` int(10) NOT NULL,
  `active` tinyint(1) DEFAULT NULL,
  `disabled` tinyint(1) DEFAULT NULL,
  `IsMountFavorite` tinyint(1) NOT NULL DEFAULT '0',
  `groupRealmMask` int(10) unsigned NOT NULL,
  PRIMARY KEY (`accountId`,`spell`),
  KEY `account` (`accountId`) USING HASH,
  KEY `account_spell` (`accountId`,`spell`) USING HASH
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

-- Volcando datos para la tabla auth.wod623_account_spell_old: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_account_spell_old` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_account_spell_old` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_account_toys
CREATE TABLE IF NOT EXISTS `wod623_account_toys` (
  `account_id` int(10) unsigned NOT NULL,
  `item_id` int(10) unsigned NOT NULL,
  `is_favorite` tinyint(1) NOT NULL DEFAULT '0',
  PRIMARY KEY (`account_id`,`item_id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_account_toys: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_account_toys` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_account_toys` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_account_vote
CREATE TABLE IF NOT EXISTS `wod623_account_vote` (
  `account` int(11) unsigned NOT NULL,
  `remainingTime` int(11) unsigned NOT NULL,
  PRIMARY KEY (`account`),
  UNIQUE KEY `account` (`account`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_account_vote: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_account_vote` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_account_vote` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_autobroadcast
CREATE TABLE IF NOT EXISTS `wod623_autobroadcast` (
  `Expension` int(11) DEFAULT NULL,
  `RealmID` int(11) DEFAULT NULL,
  `Text` blob,
  `TextFR` blob,
  `TextES` blob,
  `textRU` blob
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_autobroadcast: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_autobroadcast` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_autobroadcast` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_battlenet_modules
CREATE TABLE IF NOT EXISTS `wod623_battlenet_modules` (
  `Hash` varchar(64) NOT NULL,
  `Name` varchar(64) NOT NULL DEFAULT '',
  `Type` varchar(8) NOT NULL,
  `System` varchar(8) NOT NULL,
  `Data` text,
  PRIMARY KEY (`Name`,`System`),
  UNIQUE KEY `uk_name_type_system` (`Name`,`Type`,`System`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_battlenet_modules: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_battlenet_modules` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_battlenet_modules` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_bnet_allowed_build
CREATE TABLE IF NOT EXISTS `wod623_bnet_allowed_build` (
  `build` int(11) DEFAULT NULL,
  `version` varchar(40) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_bnet_allowed_build: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_bnet_allowed_build` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_bnet_allowed_build` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_character_renderer_queue
CREATE TABLE IF NOT EXISTS `wod623_character_renderer_queue` (
  `guid` int(11) DEFAULT NULL,
  `race` tinyint(3) DEFAULT NULL,
  `gender` tinyint(3) DEFAULT NULL,
  `class` tinyint(3) DEFAULT NULL,
  `skinColor` tinyint(3) DEFAULT NULL,
  `face` tinyint(3) DEFAULT NULL,
  `hairStyle` tinyint(3) DEFAULT NULL,
  `hairColor` tinyint(3) DEFAULT NULL,
  `facialHair` tinyint(3) DEFAULT NULL,
  `equipment` blob
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_character_renderer_queue: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_character_renderer_queue` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_character_renderer_queue` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_firewall_farms
CREATE TABLE IF NOT EXISTS `wod623_firewall_farms` (
  `ip` tinytext NOT NULL,
  `type` tinyint(1) unsigned NOT NULL DEFAULT '0'
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_firewall_farms: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_firewall_farms` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_firewall_farms` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_ip_to_country
CREATE TABLE IF NOT EXISTS `wod623_ip_to_country` (
  `IP_FROM` bigint(20) unsigned NOT NULL,
  `IP_TO` bigint(20) unsigned NOT NULL,
  `REGISTRY` char(7) NOT NULL,
  `ASSIGNED` bigint(20) NOT NULL,
  `CTRY` char(2) NOT NULL,
  `CNTRY` char(3) NOT NULL,
  `COUNTRY` varchar(100) NOT NULL,
  PRIMARY KEY (`IP_FROM`,`IP_TO`),
  KEY `IP_FROM` (`IP_FROM`) USING BTREE,
  KEY `IP_TO` (`IP_TO`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_ip_to_country: 0 rows
/*!40000 ALTER TABLE `wod623_ip_to_country` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_ip_to_country` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_logs
CREATE TABLE IF NOT EXISTS `wod623_logs` (
  `time` int(10) unsigned NOT NULL,
  `realm` int(10) unsigned NOT NULL,
  `type` tinyint(3) unsigned NOT NULL,
  `level` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `string` text CHARACTER SET latin1
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- Volcando datos para la tabla auth.wod623_logs: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_logs` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_logs` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_log_vote
CREATE TABLE IF NOT EXISTS `wod623_log_vote` (
  `top_name` varchar(15) NOT NULL DEFAULT 'top',
  `ip` varchar(15) NOT NULL DEFAULT '0.0.0.0',
  `date` int(11) NOT NULL,
  PRIMARY KEY (`top_name`,`ip`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_log_vote: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_log_vote` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_log_vote` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_motd
CREATE TABLE IF NOT EXISTS `wod623_motd` (
  `RealmID` int(10) unsigned NOT NULL,
  `Text` text NOT NULL,
  `TextFR` text NOT NULL,
  `TextES` text NOT NULL,
  `TextRU` text NOT NULL,
  PRIMARY KEY (`RealmID`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_motd: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_motd` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_motd` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_stat_lifetime_retention
CREATE TABLE IF NOT EXISTS `wod623_stat_lifetime_retention` (
  `minutes` int(11) NOT NULL,
  `usersPercentage` float(11,8) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_stat_lifetime_retention: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_stat_lifetime_retention` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_stat_lifetime_retention` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_transferts
CREATE TABLE IF NOT EXISTS `wod623_transferts` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `account` int(11) NOT NULL,
  `perso_guid` int(11) NOT NULL,
  `from` int(11) NOT NULL,
  `to` int(11) NOT NULL,
  `revision` blob NOT NULL,
  `dump` longtext NOT NULL,
  `last_error` blob NOT NULL,
  `nb_attempt` int(11) NOT NULL,
  `state` int(10) NOT NULL DEFAULT '0',
  `error` int(10) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_transferts: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_transferts` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_transferts` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_transferts_logs
CREATE TABLE IF NOT EXISTS `wod623_transferts_logs` (
  `id` int(11) DEFAULT NULL,
  `account` int(11) DEFAULT NULL,
  `perso_guid` int(11) DEFAULT NULL,
  `from` int(2) DEFAULT NULL,
  `to` int(2) DEFAULT NULL,
  `dump` longtext
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_transferts_logs: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_transferts_logs` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_transferts_logs` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_webshop_delivery_interexp_transfer
CREATE TABLE IF NOT EXISTS `wod623_webshop_delivery_interexp_transfer` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `account` int(11) NOT NULL,
  `guid` int(11) NOT NULL,
  `dump` longtext NOT NULL,
  `destrealm` int(11) NOT NULL,
  `state` int(11) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_webshop_delivery_interexp_transfer: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_webshop_delivery_interexp_transfer` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_webshop_delivery_interexp_transfer` ENABLE KEYS */;

-- Volcando estructura para tabla auth.wod623_webshop_delivery_interrealm_transfer
CREATE TABLE IF NOT EXISTS `wod623_webshop_delivery_interrealm_transfer` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `account` int(11) unsigned NOT NULL DEFAULT '0',
  `guid` int(11) unsigned NOT NULL DEFAULT '0',
  `startrealm` int(11) unsigned NOT NULL DEFAULT '0',
  `destrealm` int(11) unsigned NOT NULL DEFAULT '0',
  `revision` blob,
  `dump` longtext,
  `last_error` blob,
  `nb_attempt` int(11) unsigned NOT NULL DEFAULT '0',
  `state` int(10) unsigned NOT NULL DEFAULT '1',
  `error` int(10) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `account` (`account`) USING BTREE,
  KEY `guid` (`guid`) USING BTREE,
  KEY `startrealm` (`startrealm`) USING BTREE,
  KEY `destrealm` (`destrealm`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;

-- Volcando datos para la tabla auth.wod623_webshop_delivery_interrealm_transfer: ~0 rows (aproximadamente)
/*!40000 ALTER TABLE `wod623_webshop_delivery_interrealm_transfer` DISABLE KEYS */;
/*!40000 ALTER TABLE `wod623_webshop_delivery_interrealm_transfer` ENABLE KEYS */;

-- Volcando estructura para disparador auth.mail_update
SET @OLDTMP_SQL_MODE=@@SQL_MODE, SQL_MODE='';
DELIMITER //
CREATE TRIGGER `mail_update` BEFORE INSERT ON `account` FOR EACH ROW SET NEW.forum_email = CONCAT(NEW.username, "@rog.snet")//
DELIMITER ;
SET SQL_MODE=@OLDTMP_SQL_MODE;

/*!40101 SET SQL_MODE=IFNULL(@OLD_SQL_MODE, '') */;
/*!40014 SET FOREIGN_KEY_CHECKS=IF(@OLD_FOREIGN_KEY_CHECKS IS NULL, 1, @OLD_FOREIGN_KEY_CHECKS) */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
