-- MySQL dump 10.11
--
-- Host: localhost    Database: ananas_inventory_demo
-- ------------------------------------------------------
-- Server version	5.0.37

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `a_journ`
--

DROP TABLE IF EXISTS `a_journ`;
CREATE TABLE `a_journ` (
  `id` bigint(20) NOT NULL default '0',
  `typej` int(11) default NULL,
  `idd` bigint(20) default NULL,
  `typed` int(11) default NULL,
  `ddate` datetime default NULL,
  `pnum` char(254) NOT NULL default '',
  `num` int(11) default NULL,
  `mf` char(1) default NULL,
  `df` char(1) default NULL,
  `cf` char(1) default NULL,
  PRIMARY KEY  (`id`),
  KEY `a_journ_idx0` (`typej`),
  KEY `a_journ_idx1` (`idd`),
  KEY `a_journ_idx2` (`typed`),
  KEY `a_journ_idx3` (`ddate`),
  KEY `a_journ_idx4` (`pnum`),
  KEY `a_journ_idx5` (`num`),
  KEY `a_journ_idx6` (`mf`),
  KEY `a_journ_idx7` (`df`),
  KEY `a_journ_idx8` (`cf`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `a_journ`
--

LOCK TABLES `a_journ` WRITE;
/*!40000 ALTER TABLE `a_journ` DISABLE KEYS */;
INSERT INTO `a_journ` VALUES (43,NULL,42,101,'2007-12-19 18:04:58','Приходная накладная',1,NULL,NULL,'1'),(60,NULL,59,1061,'2007-12-19 18:10:21','Платежное поручение',2,NULL,NULL,'1'),(65,NULL,64,988,'2007-12-19 18:17:41','Приходный кассовый ордер',3,NULL,NULL,'1'),(71,NULL,70,576,'2007-12-19 18:24:36','Расходная накладная',4,NULL,NULL,'1'),(87,NULL,86,1002,'2007-12-19 18:37:10','Расходный кассовый ордер',5,NULL,NULL,'1'),(90,NULL,89,874,'2007-12-19 18:38:50','Счет',6,NULL,NULL,NULL);
/*!40000 ALTER TABLE `a_journ` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ce129`
--

DROP TABLE IF EXISTS `ce129`;
CREATE TABLE `ce129` (
  `id` bigint(20) NOT NULL default '0',
  `df` char(1) default NULL,
  `idg` bigint(20) default NULL,
  `ido` bigint(20) default NULL,
  `uf134` char(120) default NULL,
  `uf138` char(30) default NULL,
  `uf136` char(120) default NULL,
  `uf642` decimal(3,1) default NULL,
  `uf644` decimal(3,1) default NULL,
  `uf819` char(254) default NULL,
  `uf1146` char(30) default NULL,
  PRIMARY KEY  (`id`),
  KEY `ce129_idx0` (`df`),
  KEY `ce129_idx1` (`idg`),
  KEY `ce129_idx2` (`ido`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ce129`
--

LOCK TABLES `ce129` WRITE;
/*!40000 ALTER TABLE `ce129` DISABLE KEYS */;
INSERT INTO `ce129` VALUES (6,'0',3,NULL,'Водка Кристалл',NULL,NULL,'0.0','0.0',NULL,NULL),(7,'0',3,NULL,'Коньяк \"Дагестанский\" две звезды',NULL,NULL,'0.0','0.0',NULL,NULL),(8,'0',3,NULL,'Коньяк \"Дагестанский\" три звезды',NULL,NULL,'0.0','0.0',NULL,NULL),(9,'0',3,NULL,'Коньяк \"Дагестанский\" четыре звезды',NULL,NULL,'0.0','0.0',NULL,NULL),(10,'0',3,NULL,'Коньяк \"Дагестанский\" пять звезд',NULL,NULL,'0.0','0.0',NULL,NULL),(11,'0',4,NULL,'Вафли в шоколаде',NULL,NULL,'0.0','0.0',NULL,NULL),(12,'0',4,NULL,'Конфеты \"Маскарад\"',NULL,NULL,'0.0','0.0',NULL,NULL),(13,'0',4,NULL,'Орех грецкий',NULL,NULL,'0.0','0.0',NULL,NULL),(14,'0',4,NULL,'Печенье Восток',NULL,NULL,'0.0','0.0',NULL,NULL),(15,'0',4,NULL,'Печенье Домашнее',NULL,NULL,'0.0','0.0',NULL,NULL),(16,'0',4,NULL,'Печенье Привет',NULL,NULL,'0.0','0.0',NULL,NULL),(17,'0',4,NULL,'Пряник Сувенир',NULL,NULL,'0.0','0.0',NULL,NULL),(18,'0',5,NULL,'Бутылка пластиковая',NULL,NULL,'0.0','0.0',NULL,NULL),(19,'0',5,NULL,'Бутылка стеклянная',NULL,NULL,'0.0','0.0',NULL,NULL),(20,'0',5,NULL,'Ящик деревянный',NULL,NULL,'0.0','0.0',NULL,NULL),(21,'0',5,NULL,'Ящик пластиковый',NULL,NULL,'0.0','0.0',NULL,NULL),(22,'0',2,NULL,'Лампочка элекрическая 100 Вт.',NULL,NULL,'0.0','0.0',NULL,NULL),(23,'0',2,NULL,'Лампочка электрическая 75Вт',NULL,NULL,'0.0','0.0',NULL,NULL),(24,'0',2,NULL,'Пила по металлу',NULL,NULL,'0.0','0.0',NULL,NULL),(25,'0',2,NULL,'Колючая проволока',NULL,NULL,'0.0','0.0',NULL,NULL),(26,'0',2,NULL,'Шланг резиновый',NULL,NULL,'0.0','0.0',NULL,NULL),(27,'0',2,NULL,'Перчатки садовые резиновые',NULL,NULL,'0.0','0.0',NULL,NULL);
/*!40000 ALTER TABLE `ce129` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ce310`
--

DROP TABLE IF EXISTS `ce310`;
CREATE TABLE `ce310` (
  `id` bigint(20) NOT NULL default '0',
  `df` char(1) default NULL,
  `idg` bigint(20) default NULL,
  `ido` bigint(20) default NULL,
  `uf315` char(60) default NULL,
  `uf317` char(160) default NULL,
  `uf776` char(100) default NULL,
  `uf778` char(200) default NULL,
  `uf780` char(100) default NULL,
  `uf782` char(6) default NULL,
  `uf784` char(30) default NULL,
  `uf786` char(30) default NULL,
  `uf788` char(254) default NULL,
  `uf790` char(100) default NULL,
  `uf792` char(100) default NULL,
  `uf794` char(100) default NULL,
  `uf796` char(100) default NULL,
  `uf798` char(254) default NULL,
  PRIMARY KEY  (`id`),
  KEY `ce310_idx0` (`df`),
  KEY `ce310_idx1` (`idg`),
  KEY `ce310_idx2` (`ido`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ce310`
--

LOCK TABLES `ce310` WRITE;
/*!40000 ALTER TABLE `ce310` DISABLE KEYS */;
INSERT INTO `ce310` VALUES (33,'0',32,NULL,'ИЧП \"Приволжское\"','Марий-Эл, г. Йошкар-Ола','00000111112222233333',NULL,NULL,'нет','8 (8364) 124456','нет','privolg@ichp.ru','Сбербанк','99023233366532002','00000111112222233333','00000111112222233333',NULL),(34,'0',32,NULL,'000 \"Хомяк\"','Америка','99999222224444422222',NULL,NULL,NULL,NULL,NULL,NULL,'Bank of NewYork',NULL,'999234342265665','000043300003322355',NULL),(35,'0',32,NULL,'OAO \"Лавровый лист\"','Марий Эл','999993333399999933333',NULL,NULL,NULL,NULL,NULL,NULL,'банк Йошкар-Ола','99003248994023423','99003248993323434','933436556994023423',NULL),(36,'0',32,NULL,'ООЗТ \"Аранеус\"','Марий Эл',NULL,NULL,NULL,NULL,'8 (8364) 751255',NULL,'araneus@mari-el.ru','Сбербанк',NULL,NULL,NULL,NULL);
/*!40000 ALTER TABLE `ce310` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ce828`
--

DROP TABLE IF EXISTS `ce828`;
CREATE TABLE `ce828` (
  `id` bigint(20) NOT NULL default '0',
  `df` char(1) default NULL,
  `idg` bigint(20) default NULL,
  `ido` bigint(20) default NULL,
  `uf838` char(200) default NULL,
  `uf840` char(200) default NULL,
  PRIMARY KEY  (`id`),
  KEY `ce828_idx0` (`df`),
  KEY `ce828_idx1` (`idg`),
  KEY `ce828_idx2` (`ido`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ce828`
--

LOCK TABLES `ce828` WRITE;
/*!40000 ALTER TABLE `ce828` DISABLE KEYS */;
INSERT INTO `ce828` VALUES (39,'0',0,NULL,'ИНН','10000233400000002209'),(40,'0',0,NULL,'Расч. счет','777823400034322250003'),(47,'0',0,NULL,'Название','Пятерка диалог инвест'),(48,'0',0,NULL,'Руководитель','Кирк Керкорян'),(58,'0',0,NULL,'Главный бухгалтер','Уорен Баффет'),(62,'0',0,NULL,'КПП','0000000000000'),(63,'0',0,NULL,'Банк','Банк Ренессанс Капитал'),(67,'0',0,NULL,'Кассир','Джордж Сорос'),(68,'0',0,NULL,'ОКУД','00000000'),(69,'0',0,NULL,'ОКПО','0000000'),(76,'0',0,NULL,'Адрес','Лас-Вегас, ул. Стрип, д.12б'),(161,'',0,0,'Телефон','200-82-00'),(162,'',0,0,'Факс','200-82-00'),(163,'',0,0,'Email','info@gov'),(164,'',0,0,'Web','president.ru'),(165,'',0,0,'БИК','20082008'),(166,'',0,0,'Кор. счет','1112223300002008');
/*!40000 ALTER TABLE `ce828` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ce909`
--

DROP TABLE IF EXISTS `ce909`;
CREATE TABLE `ce909` (
  `id` bigint(20) NOT NULL default '0',
  `df` char(1) default NULL,
  `idg` bigint(20) default NULL,
  `ido` bigint(20) default NULL,
  `uf917` char(100) default NULL,
  `uf921` decimal(3,0) default NULL,
  PRIMARY KEY  (`id`),
  KEY `ce909_idx0` (`df`),
  KEY `ce909_idx1` (`idg`),
  KEY `ce909_idx2` (`ido`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ce909`
--

LOCK TABLES `ce909` WRITE;
/*!40000 ALTER TABLE `ce909` DISABLE KEYS */;
INSERT INTO `ce909` VALUES (29,'0',0,NULL,'Гончарова 1','1'),(30,'0',0,NULL,'Анциферова 21','2'),(31,'0',0,NULL,'Карла-Маркса 110','3');
/*!40000 ALTER TABLE `ce909` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cg129`
--

DROP TABLE IF EXISTS `cg129`;
CREATE TABLE `cg129` (
  `id` bigint(20) NOT NULL default '0',
  `df` char(1) default NULL,
  `level` bigint(20) default NULL,
  `idp` bigint(20) default NULL,
  `uf146` char(80) default NULL,
  PRIMARY KEY  (`id`),
  KEY `cg129_idx0` (`df`),
  KEY `cg129_idx1` (`level`),
  KEY `cg129_idx2` (`idp`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `cg129`
--

LOCK TABLES `cg129` WRITE;
/*!40000 ALTER TABLE `cg129` DISABLE KEYS */;
INSERT INTO `cg129` VALUES (2,'0',0,0,'Хозтовары'),(3,'0',0,0,'Вино-водочные'),(4,'0',0,0,'Продукты питания'),(5,'0',0,0,'Тара');
/*!40000 ALTER TABLE `cg129` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cg310`
--

DROP TABLE IF EXISTS `cg310`;
CREATE TABLE `cg310` (
  `id` bigint(20) NOT NULL default '0',
  `df` char(1) default NULL,
  `level` bigint(20) default NULL,
  `idp` bigint(20) default NULL,
  `uf638` char(150) default NULL,
  PRIMARY KEY  (`id`),
  KEY `cg310_idx0` (`df`),
  KEY `cg310_idx1` (`level`),
  KEY `cg310_idx2` (`idp`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `cg310`
--

LOCK TABLES `cg310` WRITE;
/*!40000 ALTER TABLE `cg310` DISABLE KEYS */;
INSERT INTO `cg310` VALUES (32,'0',0,0,'Поставщики и покупаетли');
/*!40000 ALTER TABLE `cg310` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cg828`
--

DROP TABLE IF EXISTS `cg828`;
CREATE TABLE `cg828` (
  `id` bigint(20) NOT NULL default '0',
  `df` char(1) default NULL,
  `level` bigint(20) default NULL,
  `idp` bigint(20) default NULL,
  `uf836` char(50) default NULL,
  PRIMARY KEY  (`id`),
  KEY `cg828_idx0` (`df`),
  KEY `cg828_idx1` (`level`),
  KEY `cg828_idx2` (`idp`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `cg828`
--

LOCK TABLES `cg828` WRITE;
/*!40000 ALTER TABLE `cg828` DISABLE KEYS */;
INSERT INTO `cg828` VALUES (37,'0',0,0,'Реквизиты'),(38,'0',0,0,'Сотрудники');
/*!40000 ALTER TABLE `cg828` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `cg909`
--

DROP TABLE IF EXISTS `cg909`;
CREATE TABLE `cg909` (
  `id` bigint(20) NOT NULL default '0',
  `df` char(1) default NULL,
  `level` bigint(20) default NULL,
  `idp` bigint(20) default NULL,
  `uf919` char(100) default NULL,
  PRIMARY KEY  (`id`),
  KEY `cg909_idx0` (`df`),
  KEY `cg909_idx1` (`level`),
  KEY `cg909_idx2` (`idp`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `cg909`
--

LOCK TABLES `cg909` WRITE;
/*!40000 ALTER TABLE `cg909` DISABLE KEYS */;
INSERT INTO `cg909` VALUES (28,'0',0,0,'Склады в Йошкар-Оле');
/*!40000 ALTER TABLE `cg909` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dh1002`
--

DROP TABLE IF EXISTS `dh1002`;
CREATE TABLE `dh1002` (
  `id` bigint(20) NOT NULL default '0',
  `uf1221` char(50) default NULL,
  `uf1223` datetime default NULL,
  `uf1225` bigint(20) default NULL,
  `uf1227` char(200) default NULL,
  `uf1229` decimal(12,2) default NULL,
  `uf1231` char(200) default NULL,
  `uf1233` char(254) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `dh1002`
--

LOCK TABLES `dh1002` WRITE;
/*!40000 ALTER TABLE `dh1002` DISABLE KEYS */;
INSERT INTO `dh1002` VALUES (86,'5','2007-12-18 00:00:00',34,'за поставленные товары','26000.00',NULL,'');
/*!40000 ALTER TABLE `dh1002` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dh101`
--

DROP TABLE IF EXISTS `dh101`;
CREATE TABLE `dh101` (
  `id` bigint(20) NOT NULL default '0',
  `uf121` char(100) default NULL,
  `uf123` datetime default NULL,
  `uf354` char(254) default NULL,
  `uf629` bigint(20) default NULL,
  `uf986` bigint(20) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `dh101`
--

LOCK TABLES `dh101` WRITE;
/*!40000 ALTER TABLE `dh101` DISABLE KEYS */;
INSERT INTO `dh101` VALUES (42,'1','2007-12-18 00:00:00','нет',34,30);
/*!40000 ALTER TABLE `dh101` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dh1051`
--

DROP TABLE IF EXISTS `dh1051`;
CREATE TABLE `dh1051` (
  `id` bigint(20) NOT NULL default '0',
  `uf1124` decimal(10,0) default NULL,
  `uf1126` datetime default NULL,
  `uf1318` bigint(20) default NULL,
  `uf1320` decimal(10,2) default NULL,
  `uf1322` char(254) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `dh1051`
--

LOCK TABLES `dh1051` WRITE;
/*!40000 ALTER TABLE `dh1051` DISABLE KEYS */;
/*!40000 ALTER TABLE `dh1051` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dh1061`
--

DROP TABLE IF EXISTS `dh1061`;
CREATE TABLE `dh1061` (
  `id` bigint(20) NOT NULL default '0',
  `uf1129` char(100) default NULL,
  `uf1131` datetime default NULL,
  `uf1148` bigint(20) default NULL,
  `uf1150` decimal(12,2) default NULL,
  `uf1152` char(254) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `dh1061`
--

LOCK TABLES `dh1061` WRITE;
/*!40000 ALTER TABLE `dh1061` DISABLE KEYS */;
INSERT INTO `dh1061` VALUES (59,'2','2007-12-18 00:00:00',35,'30000.00','кредит на производственные нужды');
/*!40000 ALTER TABLE `dh1061` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dh576`
--

DROP TABLE IF EXISTS `dh576`;
CREATE TABLE `dh576` (
  `id` bigint(20) NOT NULL default '0',
  `uf582` char(100) default NULL,
  `uf584` datetime default NULL,
  `uf586` bigint(20) default NULL,
  `uf766` char(254) default NULL,
  `uf984` bigint(20) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `dh576`
--

LOCK TABLES `dh576` WRITE;
/*!40000 ALTER TABLE `dh576` DISABLE KEYS */;
INSERT INTO `dh576` VALUES (70,'4','2007-12-18 00:00:00',33,'продажа товаров',29);
/*!40000 ALTER TABLE `dh576` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dh874`
--

DROP TABLE IF EXISTS `dh874`;
CREATE TABLE `dh874` (
  `id` bigint(20) NOT NULL default '0',
  `uf880` char(100) default NULL,
  `uf882` datetime default NULL,
  `uf884` bigint(20) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `dh874`
--

LOCK TABLES `dh874` WRITE;
/*!40000 ALTER TABLE `dh874` DISABLE KEYS */;
INSERT INTO `dh874` VALUES (89,'6','2007-12-18 00:00:00',36);
/*!40000 ALTER TABLE `dh874` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dh988`
--

DROP TABLE IF EXISTS `dh988`;
CREATE TABLE `dh988` (
  `id` bigint(20) NOT NULL default '0',
  `uf994` decimal(12,0) default NULL,
  `uf996` datetime default NULL,
  `uf998` bigint(20) default NULL,
  `uf1000` char(200) default NULL,
  `uf1219` decimal(10,2) default NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `dh988`
--

LOCK TABLES `dh988` WRITE;
/*!40000 ALTER TABLE `dh988` DISABLE KEYS */;
INSERT INTO `dh988` VALUES (64,'3','2007-12-18 00:00:00',35,'деньги за кредит','30000.00');
/*!40000 ALTER TABLE `dh988` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dt101_126`
--

DROP TABLE IF EXISTS `dt101_126`;
CREATE TABLE `dt101_126` (
  `id` bigint(20) NOT NULL default '0',
  `idd` bigint(20) default NULL,
  `ln` bigint(20) default NULL,
  `uf127` bigint(20) default NULL,
  `uf140` decimal(10,0) default NULL,
  `uf142` decimal(10,2) default NULL,
  `uf356` char(254) default NULL,
  `uf448` decimal(10,2) default NULL,
  PRIMARY KEY  (`id`),
  KEY `dt101_126_idx0` (`idd`),
  KEY `dt101_126_idx1` (`ln`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `dt101_126`
--

LOCK TABLES `dt101_126` WRITE;
/*!40000 ALTER TABLE `dt101_126` DISABLE KEYS */;
INSERT INTO `dt101_126` VALUES (44,42,0,10,'20','600.00',NULL,'12000.00'),(45,42,1,9,'25','500.00',NULL,'12500.00'),(46,42,2,6,'10','150.00',NULL,'1500.00');
/*!40000 ALTER TABLE `dt101_126` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dt576_588`
--

DROP TABLE IF EXISTS `dt576_588`;
CREATE TABLE `dt576_588` (
  `id` bigint(20) NOT NULL default '0',
  `idd` bigint(20) default NULL,
  `ln` bigint(20) default NULL,
  `uf589` bigint(20) default NULL,
  `uf591` decimal(12,0) default NULL,
  `uf593` decimal(12,2) default NULL,
  `uf768` decimal(12,2) default NULL,
  `uf770` decimal(12,2) default NULL,
  `uf772` decimal(12,2) default NULL,
  `uf774` decimal(12,2) default NULL,
  PRIMARY KEY  (`id`),
  KEY `dt576_588_idx0` (`idd`),
  KEY `dt576_588_idx1` (`ln`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `dt576_588`
--

LOCK TABLES `dt576_588` WRITE;
/*!40000 ALTER TABLE `dt576_588` DISABLE KEYS */;
INSERT INTO `dt576_588` VALUES (72,70,0,24,'1','30.00','30.00','30.00','30.00','0.00'),(73,70,1,27,'1','20.00','20.00','20.00','20.00','0.00'),(74,70,2,26,'5','10.00','50.00','10.00','50.00','0.00'),(75,70,3,25,'3','20.00','60.00','20.00','60.00','0.00');
/*!40000 ALTER TABLE `dt576_588` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `dt874_886`
--

DROP TABLE IF EXISTS `dt874_886`;
CREATE TABLE `dt874_886` (
  `id` bigint(20) NOT NULL default '0',
  `idd` bigint(20) default NULL,
  `ln` bigint(20) default NULL,
  `uf887` bigint(20) default NULL,
  `uf889` char(50) default NULL,
  `uf890` decimal(10,0) default NULL,
  `uf892` decimal(12,2) default NULL,
  `uf895` decimal(12,2) default NULL,
  PRIMARY KEY  (`id`),
  KEY `dt874_886_idx0` (`idd`),
  KEY `dt874_886_idx1` (`ln`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `dt874_886`
--

LOCK TABLES `dt874_886` WRITE;
/*!40000 ALTER TABLE `dt874_886` DISABLE KEYS */;
INSERT INTO `dt874_886` VALUES (91,89,0,6,'бут.','20','100.00','2000.00');
/*!40000 ALTER TABLE `dt874_886` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `idc`
--

DROP TABLE IF EXISTS `idc`;
CREATE TABLE `idc` (
  `tname` char(40) default NULL,
  `uindices` char(240) default NULL,
  `idxname` char(64) default NULL,
  KEY `idc_idx0` (`tname`),
  KEY `idc_idx1` (`uindices`),
  KEY `idc_idx2` (`idxname`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `idc`
--

LOCK TABLES `idc` WRITE;
/*!40000 ALTER TABLE `idc` DISABLE KEYS */;
/*!40000 ALTER TABLE `idc` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `r_rl`
--

DROP TABLE IF EXISTS `r_rl`;
CREATE TABLE `r_rl` (
  `idr` bigint(20) default NULL,
  `permission` int(11) default NULL,
  `object` bigint(20) default NULL,
  KEY `r_rl_idx0` (`idr`),
  KEY `r_rl_idx1` (`permission`),
  KEY `r_rl_idx2` (`object`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `r_rl`
--

LOCK TABLES `r_rl` WRITE;
/*!40000 ALTER TABLE `r_rl` DISABLE KEYS */;
/*!40000 ALTER TABLE `r_rl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ra296`
--

DROP TABLE IF EXISTS `ra296`;
CREATE TABLE `ra296` (
  `id` bigint(20) NOT NULL default '0',
  `idd` bigint(20) default NULL,
  `iddt` bigint(20) default NULL,
  `ln` bigint(20) default NULL,
  `date` datetime default NULL,
  `uf814` decimal(10,0) default NULL,
  `uf1324` decimal(12,2) default NULL,
  `uf302` char(10) default NULL,
  `uf304` char(10) default NULL,
  `uf308` bigint(20) default NULL,
  `uf321` bigint(20) default NULL,
  `uf1144` bigint(20) default NULL,
  `uf298` char(200) default NULL,
  PRIMARY KEY  (`id`),
  KEY `ra296_idx0` (`idd`),
  KEY `ra296_idx1` (`iddt`),
  KEY `ra296_idx2` (`ln`),
  KEY `ra296_idx3` (`date`),
  KEY `ra296_idx4` (`uf814`),
  KEY `ra296_idx5` (`uf1324`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ra296`
--

LOCK TABLES `ra296` WRITE;
/*!40000 ALTER TABLE `ra296` DISABLE KEYS */;
INSERT INTO `ra296` VALUES (138,42,0,0,'2005-11-18 18:04:58','0','270.00','68','19',0,0,0,'зачет НДС'),(137,42,0,0,'2005-11-18 18:04:58','0','270.00','19','60',0,0,0,'учет НДС'),(136,42,46,2,'2005-11-18 18:04:58','10','1500.00','41.2','60',6,34,30,'Оприходование товара'),(135,42,0,0,'2005-11-18 18:04:58','0','2250.00','68','19',0,0,0,'зачет НДС'),(134,42,0,0,'2005-11-18 18:04:58','0','2250.00','19','60',0,0,0,'учет НДС'),(133,42,45,1,'2005-11-18 18:04:58','25','12500.00','41.2','60',9,34,30,'Оприходование товара'),(132,42,0,0,'2005-11-18 18:04:58','0','2160.00','68','19',0,0,0,'зачет НДС'),(131,42,0,0,'2005-11-18 18:04:58','0','2160.00','19','60',0,0,0,'учет НДС'),(130,42,44,0,'2005-11-18 18:04:58','20','12000.00','41.2','60',10,34,30,'Оприходование товара'),(139,59,0,0,'2005-11-18 18:10:21','0','-30000.00','60','51',0,35,0,'оплата с расч. счета'),(129,64,0,0,'2005-11-18 18:17:41','0','30000.00','50','90',0,35,0,'реализ. товара через кассу'),(159,70,0,0,'2007-12-19 18:24:36','0','10.80','90','68',0,0,0,'начисление задолженности по НДС'),(158,70,75,3,'2007-12-19 18:24:36','-3','-60.00','90','41.2',25,33,29,'списание реализ. товаров'),(157,70,0,0,'2007-12-19 18:24:36','0','9.00','90','68',0,0,0,'начисление задолженности по НДС'),(156,70,74,2,'2007-12-19 18:24:36','-5','-50.00','90','41.2',26,33,29,'списание реализ. товаров'),(155,70,0,0,'2007-12-19 18:24:36','0','3.60','90','68',0,0,0,'начисление задолженности по НДС'),(154,70,73,1,'2007-12-19 18:24:36','-1','-20.00','90','41.2',27,33,29,'списание реализ. товаров'),(153,70,0,0,'2007-12-19 18:24:36','0','5.40','90','68',0,0,0,'начисление задолженности по НДС'),(152,70,72,0,'2007-12-19 18:24:36','-1','-30.00','90','41.2',24,33,29,'списание реализ. товаров'),(148,86,0,0,'2005-11-18 18:37:10','0','-26000.00','60','50',0,34,0,'оплата через кассу');
/*!40000 ALTER TABLE `ra296` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ra296_d1144`
--

DROP TABLE IF EXISTS `ra296_d1144`;
CREATE TABLE `ra296_d1144` (
  `date` datetime default NULL,
  `uf1144` bigint(20) default NULL,
  `uf814` decimal(10,0) default NULL,
  `uf1324` decimal(12,2) default NULL,
  KEY `ra296_d1144_idx0` (`date`),
  KEY `ra296_d1144_idx1` (`uf814`),
  KEY `ra296_d1144_idx2` (`uf1324`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ra296_d1144`
--

LOCK TABLES `ra296_d1144` WRITE;
/*!40000 ALTER TABLE `ra296_d1144` DISABLE KEYS */;
INSERT INTO `ra296_d1144` VALUES ('2005-11-18 18:04:58',30,'55','26000.00'),('2005-11-18 18:24:36',29,'-10','-160.00'),('2007-12-19 18:24:36',29,'-10','-160.00');
/*!40000 ALTER TABLE `ra296_d1144` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ra296_d302`
--

DROP TABLE IF EXISTS `ra296_d302`;
CREATE TABLE `ra296_d302` (
  `date` datetime default NULL,
  `uf302` char(10) default NULL,
  `uf814` decimal(10,0) default NULL,
  `uf1324` decimal(12,2) default NULL,
  KEY `ra296_d302_idx0` (`date`),
  KEY `ra296_d302_idx1` (`uf814`),
  KEY `ra296_d302_idx2` (`uf1324`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ra296_d302`
--

LOCK TABLES `ra296_d302` WRITE;
/*!40000 ALTER TABLE `ra296_d302` DISABLE KEYS */;
INSERT INTO `ra296_d302` VALUES ('2005-11-18 18:04:58','19','0','4680.00'),('2005-11-18 18:04:58','68','0','4680.00'),('2005-11-18 18:10:21','60','0','-30000.00'),('2005-11-18 18:17:41','50','0','30000.00'),('2005-11-18 18:24:36','90','-10','-131.20'),('2005-11-18 18:37:10','60','0','-56000.00'),('2007-12-19 18:24:36','90','-10','-131.20');
/*!40000 ALTER TABLE `ra296_d302` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ra296_d304`
--

DROP TABLE IF EXISTS `ra296_d304`;
CREATE TABLE `ra296_d304` (
  `date` datetime default NULL,
  `uf304` char(10) default NULL,
  `uf814` decimal(10,0) default NULL,
  `uf1324` decimal(12,2) default NULL,
  KEY `ra296_d304_idx0` (`date`),
  KEY `ra296_d304_idx1` (`uf814`),
  KEY `ra296_d304_idx2` (`uf1324`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ra296_d304`
--

LOCK TABLES `ra296_d304` WRITE;
/*!40000 ALTER TABLE `ra296_d304` DISABLE KEYS */;
INSERT INTO `ra296_d304` VALUES ('2005-11-18 18:04:58','60','55','30680.00'),('2005-11-18 18:04:58','19','0','4680.00'),('2005-11-18 18:10:21','51','0','-30000.00'),('2005-11-18 18:17:41','90','0','30000.00'),('2005-11-18 18:24:36','68','0','28.80'),('2005-11-18 18:37:10','50','0','-26000.00'),('2007-12-19 18:24:36','68','0','28.80');
/*!40000 ALTER TABLE `ra296_d304` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ra296_d308`
--

DROP TABLE IF EXISTS `ra296_d308`;
CREATE TABLE `ra296_d308` (
  `date` datetime default NULL,
  `uf308` bigint(20) default NULL,
  `uf814` decimal(10,0) default NULL,
  `uf1324` decimal(12,2) default NULL,
  KEY `ra296_d308_idx0` (`date`),
  KEY `ra296_d308_idx1` (`uf814`),
  KEY `ra296_d308_idx2` (`uf1324`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ra296_d308`
--

LOCK TABLES `ra296_d308` WRITE;
/*!40000 ALTER TABLE `ra296_d308` DISABLE KEYS */;
INSERT INTO `ra296_d308` VALUES ('2005-11-18 18:04:58',10,'20','12000.00'),('2005-11-18 18:04:58',9,'25','12500.00'),('2005-11-18 18:04:58',6,'10','1500.00'),('2005-11-18 18:24:36',24,'-1','-30.00'),('2005-11-18 18:24:36',27,'-1','-20.00'),('2005-11-18 18:24:36',26,'-5','-50.00'),('2005-11-18 18:24:36',25,'-3','-60.00'),('2007-12-19 18:24:36',25,'-3','-60.00'),('2007-12-19 18:24:36',26,'-5','-50.00'),('2007-12-19 18:24:36',27,'-1','-20.00'),('2007-12-19 18:24:36',24,'-1','-30.00');
/*!40000 ALTER TABLE `ra296_d308` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `ra296_d321`
--

DROP TABLE IF EXISTS `ra296_d321`;
CREATE TABLE `ra296_d321` (
  `date` datetime default NULL,
  `uf321` bigint(20) default NULL,
  `uf814` decimal(10,0) default NULL,
  `uf1324` decimal(12,2) default NULL,
  KEY `ra296_d321_idx0` (`date`),
  KEY `ra296_d321_idx1` (`uf814`),
  KEY `ra296_d321_idx2` (`uf1324`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `ra296_d321`
--

LOCK TABLES `ra296_d321` WRITE;
/*!40000 ALTER TABLE `ra296_d321` DISABLE KEYS */;
INSERT INTO `ra296_d321` VALUES ('2005-11-18 18:04:58',34,'55','26000.00'),('2005-11-18 18:10:21',35,'0','-30000.00'),('2005-11-18 18:17:41',35,'0','0.00'),('2005-11-18 18:24:36',33,'-10','-160.00'),('2005-11-18 18:37:10',34,'55','0.00'),('2007-12-19 18:24:36',33,'-10','-160.00');
/*!40000 ALTER TABLE `ra296_d321` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `rl`
--

DROP TABLE IF EXISTS `rl`;
CREATE TABLE `rl` (
  `id` bigint(20) NOT NULL default '0',
  `name` char(50) default NULL,
  PRIMARY KEY  (`id`),
  KEY `rl_idx0` (`name`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `rl`
--

LOCK TABLES `rl` WRITE;
/*!40000 ALTER TABLE `rl` DISABLE KEYS */;
/*!40000 ALTER TABLE `rl` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `uniques`
--

DROP TABLE IF EXISTS `uniques`;
CREATE TABLE `uniques` (
  `id` bigint(20) NOT NULL auto_increment,
  `otype` int(11) default NULL,
  `df` char(1) default NULL,
  PRIMARY KEY  (`id`),
  KEY `uniques_idx0` (`otype`),
  KEY `uniques_idx1` (`df`)
) ENGINE=MyISAM AUTO_INCREMENT=167 DEFAULT CHARSET=utf8;

--
-- Dumping data for table `uniques`
--

LOCK TABLES `uniques` WRITE;
/*!40000 ALTER TABLE `uniques` DISABLE KEYS */;
INSERT INTO `uniques` VALUES (1,0,NULL),(2,129,NULL),(3,129,NULL),(4,129,NULL),(5,129,NULL),(6,129,NULL),(7,129,NULL),(8,129,NULL),(9,129,NULL),(10,129,NULL),(11,129,NULL),(12,129,NULL),(13,129,NULL),(14,129,NULL),(15,129,NULL),(16,129,NULL),(17,129,NULL),(18,129,NULL),(19,129,NULL),(20,129,NULL),(21,129,NULL),(22,129,NULL),(23,129,NULL),(24,129,NULL),(25,129,NULL),(26,129,NULL),(27,129,NULL),(28,909,NULL),(29,909,NULL),(30,909,NULL),(31,909,NULL),(32,310,NULL),(33,310,NULL),(34,310,NULL),(35,310,NULL),(36,310,NULL),(37,828,NULL),(38,828,NULL),(39,828,NULL),(40,828,NULL),(41,0,NULL),(42,101,NULL),(43,1,NULL),(44,126,NULL),(45,126,NULL),(46,126,NULL),(47,828,NULL),(48,828,NULL),(49,296,NULL),(50,296,NULL),(51,296,NULL),(52,296,NULL),(53,296,NULL),(54,296,NULL),(55,296,NULL),(56,296,NULL),(57,296,NULL),(58,828,NULL),(59,1061,NULL),(60,1,NULL),(61,296,NULL),(62,828,NULL),(63,828,NULL),(64,988,NULL),(65,1,NULL),(66,296,NULL),(67,828,NULL),(68,828,NULL),(69,828,NULL),(70,576,NULL),(71,1,NULL),(72,588,NULL),(73,588,NULL),(74,588,NULL),(75,588,NULL),(76,828,NULL),(77,296,NULL),(78,296,NULL),(79,296,NULL),(80,296,NULL),(81,296,NULL),(82,296,NULL),(83,296,NULL),(84,296,NULL),(85,0,NULL),(86,1002,NULL),(87,1,NULL),(88,296,NULL),(89,874,NULL),(90,1,NULL),(91,886,NULL),(92,0,NULL),(93,-11773530,NULL),(94,-11773530,NULL),(95,-11773530,NULL),(96,-657670,NULL),(97,-11773530,NULL),(98,-11773530,NULL),(99,-11773530,NULL),(100,296,NULL),(101,296,NULL),(102,296,NULL),(103,296,NULL),(104,296,NULL),(105,296,NULL),(106,296,NULL),(107,296,NULL),(108,-11773530,NULL),(109,296,NULL),(110,296,NULL),(111,296,NULL),(112,296,NULL),(113,296,NULL),(114,296,NULL),(115,296,NULL),(116,296,NULL),(117,296,NULL),(118,0,NULL),(119,296,NULL),(120,296,NULL),(121,296,NULL),(122,296,NULL),(123,296,NULL),(124,296,NULL),(125,296,NULL),(126,296,NULL),(127,296,NULL),(128,296,NULL),(129,296,NULL),(130,296,NULL),(131,296,NULL),(132,296,NULL),(133,296,NULL),(134,296,NULL),(135,296,NULL),(136,296,NULL),(137,296,NULL),(138,296,NULL),(139,296,NULL),(140,296,NULL),(141,296,NULL),(142,296,NULL),(143,296,NULL),(144,296,NULL),(145,296,NULL),(146,296,NULL),(147,296,NULL),(148,296,NULL),(149,0,NULL),(150,0,NULL),(151,0,NULL),(152,296,NULL),(153,296,NULL),(154,296,NULL),(155,296,NULL),(156,296,NULL),(157,296,NULL),(158,296,NULL),(159,296,NULL),(160,0,NULL),(161,828,NULL),(162,828,NULL),(163,828,NULL),(164,828,NULL),(165,828,NULL),(166,828,NULL);
/*!40000 ALTER TABLE `uniques` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `usr`
--

DROP TABLE IF EXISTS `usr`;
CREATE TABLE `usr` (
  `id` bigint(20) NOT NULL default '0',
  `fname` char(25) default NULL,
  `lname` char(30) default NULL,
  `login` char(20) default NULL,
  `password` char(100) default NULL,
  PRIMARY KEY  (`id`),
  KEY `usr_idx0` (`fname`),
  KEY `usr_idx1` (`lname`),
  KEY `usr_idx2` (`login`),
  KEY `usr_idx3` (`password`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `usr`
--

LOCK TABLES `usr` WRITE;
/*!40000 ALTER TABLE `usr` DISABLE KEYS */;
/*!40000 ALTER TABLE `usr` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `usr_rl`
--

DROP TABLE IF EXISTS `usr_rl`;
CREATE TABLE `usr_rl` (
  `id` bigint(20) default NULL,
  `idr` bigint(20) default NULL,
  KEY `usr_rl_idx0` (`id`),
  KEY `usr_rl_idx1` (`idr`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

--
-- Dumping data for table `usr_rl`
--

LOCK TABLES `usr_rl` WRITE;
/*!40000 ALTER TABLE `usr_rl` DISABLE KEYS */;
/*!40000 ALTER TABLE `usr_rl` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2007-12-30  8:32:54
