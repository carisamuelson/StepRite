CREATE DATABASE  IF NOT EXISTS `sr_main` /*!40100 DEFAULT CHARACTER SET latin1 */;
USE `sr_main`;
-- MySQL dump 10.13  Distrib 5.5.16, for Win32 (x86)
--
-- Host: 54.227.241.240    Database: sr_main
-- ------------------------------------------------------
-- Server version	5.1.71

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
-- Table structure for table `gaitCalculations`
--

DROP TABLE IF EXISTS `gaitCalculations`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `gaitCalculations` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `protocol_id` int(11) DEFAULT NULL,
  `protocol_num` int(11) DEFAULT NULL,
  `runID` tinyint(1) DEFAULT NULL,
  `foot` tinyint(1) DEFAULT NULL,
  `avg_pressure` decimal(5,2) DEFAULT NULL,
  `max_pressure` decimal(5,2) DEFAULT NULL,
  `num_elements` int(11) DEFAULT NULL,
  `f1` decimal(5,2) DEFAULT NULL,
  `f2` decimal(5,2) DEFAULT NULL,
  `f3` decimal(5,2) DEFAULT NULL,
  `f4` decimal(5,2) DEFAULT NULL,
  `clock_time` decimal(5,2) DEFAULT NULL,
  `avg_cadence_time` decimal(5,2) DEFAULT NULL,
  `number_of_strides` int(11) DEFAULT NULL,
  `avg_swing_time` decimal(5,2) DEFAULT NULL,
  `avg_step_time` decimal(5,2) DEFAULT NULL,
  `avg_max_pressure` decimal(10,2) DEFAULT NULL,
  `avg_stride_distance` decimal(10,2) DEFAULT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=39 DEFAULT CHARSET=latin1;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `gaitCalculations`
--

LOCK TABLES `gaitCalculations` WRITE;
/*!40000 ALTER TABLE `gaitCalculations` DISABLE KEYS */;
INSERT INTO `gaitCalculations` VALUES (38,25,4,3,1,0.50,0.88,2071,11.63,11.05,15.28,12.04,39.40,35.40,23,88.90,0.58,143.70,268.40),(37,25,4,3,0,0.50,1.00,2071,8.77,11.28,15.83,14.13,39.40,35.40,23,89.10,1.11,123.60,236.50),(36,25,4,2,1,0.48,0.88,2090,10.80,10.94,14.36,11.92,39.80,26.10,17,95.00,0.79,135.70,1191.60),(35,25,4,2,0,0.52,1.00,2090,8.36,12.04,16.27,15.31,39.80,26.10,17,92.90,1.31,109.20,574.50),(34,25,4,1,1,0.56,0.98,1781,10.46,27.55,8.69,9.37,33.60,26.40,14,94.20,2.86,740.40,246.80),(33,25,4,1,0,0.44,0.96,1781,11.83,17.10,7.68,7.31,33.60,26.40,14,96.90,1.13,419.20,732.80);
/*!40000 ALTER TABLE `gaitCalculations` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-01-08  0:01:57
