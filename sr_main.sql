-- phpMyAdmin SQL Dump
-- version 4.0.9
-- http://www.phpmyadmin.net
--
-- Host: 127.0.0.1
-- Generation Time: Jan 05, 2014 at 02:30 AM
-- Server version: 5.5.34
-- PHP Version: 5.4.22

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `sr_main`
--

-- --------------------------------------------------------

--
-- Table structure for table `activities`
--

CREATE TABLE IF NOT EXISTS `activities` (
  `id` mediumint(9) NOT NULL AUTO_INCREMENT COMMENT 'AI Key',
  `patient_id` mediumint(9) DEFAULT NULL,
  `protocol_id` mediumint(9) DEFAULT NULL,
  `exercise_id` mediumint(9) DEFAULT NULL,
  `date_time` datetime NOT NULL,
  `left_calc` int(11) DEFAULT NULL,
  `right_calc` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=549 ;

--
-- Dumping data for table `activities`
--

INSERT INTO `activities` (`id`, `patient_id`, `protocol_id`, `exercise_id`, `date_time`, `left_calc`, `right_calc`) VALUES
(4, 1, 2, 1, '0000-00-00 00:00:00', 3, 4),
(5, 1, 2, 1, '0000-00-00 00:00:00', 5, 6),
(6, 1, 4, 2, '0000-00-00 00:00:00', NULL, NULL),
(10, 1, 1, 70, '0000-00-00 00:00:00', 117, 118),
(9, 1, 1, 70, '0000-00-00 00:00:00', 115, 116),
(11, 1, 1, 70, '0000-00-00 00:00:00', 119, 120),
(14, 1, 2, 1, '0000-00-00 00:00:00', 7, 8),
(142, 5, 29, 78, '0000-00-00 00:00:00', NULL, NULL),
(141, 5, 27, 37, '0000-00-00 00:00:00', 137, 138),
(140, 5, 28, 39, '0000-00-00 00:00:00', 135, 136),
(139, 5, 26, 15, '0000-00-00 00:00:00', 133, 134),
(138, 1, 29, 78, '0000-00-00 00:00:00', NULL, NULL),
(137, 1, 29, 78, '0000-00-00 00:00:00', NULL, NULL),
(136, 1, 28, 39, '0000-00-00 00:00:00', 131, 132),
(135, 1, 28, 39, '0000-00-00 00:00:00', 129, 130),
(134, 1, 27, 37, '0000-00-00 00:00:00', 127, 128),
(133, 1, 27, 37, '0000-00-00 00:00:00', 125, 126),
(132, 1, 26, 15, '0000-00-00 00:00:00', 123, 124),
(131, 1, 26, 15, '0000-00-00 00:00:00', 121, 122),
(143, 6, 26, 17, '0000-00-00 00:00:00', 139, 140),
(144, 6, 27, 37, '0000-00-00 00:00:00', 141, 142),
(145, 6, 28, 39, '0000-00-00 00:00:00', 143, 144),
(146, 6, 29, 78, '0000-00-00 00:00:00', NULL, NULL),
(149, 6, 4, 2, '0000-00-00 00:00:00', NULL, NULL),
(148, 6, 2, 1, '0000-00-00 00:00:00', 9, 10),
(150, 7, 26, 17, '0000-00-00 00:00:00', 145, 146),
(151, 7, 27, 37, '0000-00-00 00:00:00', 147, 148),
(152, 7, 28, 39, '0000-00-00 00:00:00', 149, 150),
(153, 7, 29, 78, '0000-00-00 00:00:00', NULL, NULL),
(154, 7, 4, 2, '0000-00-00 00:00:00', NULL, NULL),
(155, 7, 2, 1, '0000-00-00 00:00:00', 11, 12),
(156, 8, 26, 17, '0000-00-00 00:00:00', 151, 152),
(157, 8, 27, 37, '0000-00-00 00:00:00', 153, 154),
(158, 8, 28, 39, '0000-00-00 00:00:00', 155, 156),
(159, 8, 28, 78, '0000-00-00 00:00:00', NULL, NULL),
(160, 8, 2, 1, '0000-00-00 00:00:00', 13, 14),
(161, 8, 1, 70, '0000-00-00 00:00:00', 157, 158),
(162, 9, 26, 17, '0000-00-00 00:00:00', 159, 160),
(163, 9, 27, 37, '0000-00-00 00:00:00', 161, 162),
(164, 9, 28, 39, '0000-00-00 00:00:00', 163, 164),
(165, 9, 29, 78, '0000-00-00 00:00:00', NULL, NULL),
(166, 9, 2, 1, '0000-00-00 00:00:00', 15, 16),
(167, 9, 1, 70, '0000-00-00 00:00:00', 165, 166),
(168, 10, 26, 15, '0000-00-00 00:00:00', 167, 168),
(169, 10, 27, 37, '0000-00-00 00:00:00', 169, 170),
(170, 10, 28, 39, '0000-00-00 00:00:00', 171, 172),
(171, 10, 29, 78, '0000-00-00 00:00:00', NULL, NULL),
(172, 10, 2, 1, '0000-00-00 00:00:00', 17, 18),
(173, 10, 1, 70, '0000-00-00 00:00:00', 173, 174),
(174, 11, 26, 17, '0000-00-00 00:00:00', 175, 176),
(175, 11, 27, 37, '0000-00-00 00:00:00', 177, 178),
(176, 11, 28, 39, '0000-00-00 00:00:00', 179, 180),
(177, 11, 29, 78, '0000-00-00 00:00:00', NULL, NULL),
(178, 11, 2, 1, '0000-00-00 00:00:00', 19, 20),
(179, 11, 1, 70, '0000-00-00 00:00:00', 181, 182),
(180, 12, 26, 17, '0000-00-00 00:00:00', 183, 184),
(181, 12, 27, 37, '0000-00-00 00:00:00', 185, 186),
(182, 12, 28, 39, '0000-00-00 00:00:00', 187, 188),
(183, 12, 29, 78, '0000-00-00 00:00:00', NULL, NULL),
(184, 12, 2, 1, '0000-00-00 00:00:00', 21, 22),
(185, 12, 1, 70, '0000-00-00 00:00:00', 189, 190),
(186, 13, 26, 17, '0000-00-00 00:00:00', 191, 192),
(187, 13, 27, 37, '0000-00-00 00:00:00', 193, 194),
(188, 13, 28, 39, '0000-00-00 00:00:00', 195, 196),
(189, 13, 29, 78, '0000-00-00 00:00:00', NULL, NULL),
(190, 13, 2, 1, '0000-00-00 00:00:00', 23, 24),
(191, 13, 1, 70, '0000-00-00 00:00:00', 197, 198),
(192, 14, 26, 17, '0000-00-00 00:00:00', 199, 200),
(193, 14, 27, 37, '0000-00-00 00:00:00', 201, 202),
(194, 14, 28, 39, '0000-00-00 00:00:00', 203, 204),
(195, 14, 29, 78, '0000-00-00 00:00:00', NULL, NULL),
(196, 14, 2, 1, '0000-00-00 00:00:00', 25, 26),
(197, 14, 1, 70, '0000-00-00 00:00:00', 205, 206),
(198, 15, 26, 17, '0000-00-00 00:00:00', 207, 208),
(199, 15, 27, 37, '0000-00-00 00:00:00', 209, 210),
(200, 15, 28, 39, '0000-00-00 00:00:00', 211, 212),
(201, 15, 29, 78, '0000-00-00 00:00:00', NULL, NULL),
(202, 15, 2, 1, '0000-00-00 00:00:00', 27, 28),
(203, 15, 1, 70, '0000-00-00 00:00:00', 213, 214),
(204, 16, 26, 17, '0000-00-00 00:00:00', 215, 216),
(205, 16, 27, 37, '0000-00-00 00:00:00', 217, 218),
(206, 16, 28, 39, '0000-00-00 00:00:00', 219, 220),
(207, 16, 2, 1, '0000-00-00 00:00:00', 29, 30),
(208, 16, 1, 70, '0000-00-00 00:00:00', 221, 222),
(209, 21, 49, 70, '0000-00-00 00:00:00', 223, 224),
(221, 22, 0, 15, '0000-00-00 00:00:00', 223, 224),
(222, 22, 4, 2, '0000-00-00 00:00:00', 223, 224),
(223, 22, 1, 1, '0000-00-00 00:00:00', 223, 224),
(224, 22, 29, 1, '0000-00-00 00:00:00', 223, 224),
(225, 22, 191, 1, '0000-00-00 00:00:00', 223, 224),
(226, 33, 0, 15, '0000-00-00 00:00:00', 229, 230),
(227, 33, 0, 32, '0000-00-00 00:00:00', 231, 232),
(228, 33, 0, 32, '0000-00-00 00:00:00', 233, 234),
(229, 33, 0, 32, '0000-00-00 00:00:00', 235, 236),
(230, 33, 0, 32, '0000-00-00 00:00:00', 237, 238),
(231, 33, 0, 32, '0000-00-00 00:00:00', 239, 240),
(232, 33, 0, 37, '0000-00-00 00:00:00', 241, 242),
(233, 44, 0, 1, '0000-00-00 00:00:00', 29, 30),
(234, 44, 0, 15, '0000-00-00 00:00:00', 245, 246),
(235, 66, 0, 37, '0000-00-00 00:00:00', 247, 248),
(236, 66, 0, 78, '0000-00-00 00:00:00', 249, 250),
(237, 55, 0, 70, '0000-00-00 00:00:00', 251, 252),
(238, 55, 0, 1, '0000-00-00 00:00:00', 31, 32),
(239, 55, 0, 1, '0000-00-00 00:00:00', 33, 34),
(240, 66, 0, 15, '0000-00-00 00:00:00', 253, 254),
(241, 55, 0, 1, '0000-00-00 00:00:00', 35, 36),
(242, 66, 0, 15, '0000-00-00 00:00:00', 255, 256),
(243, 66, 0, 15, '0000-00-00 00:00:00', 257, 258),
(244, 55, 0, 70, '0000-00-00 00:00:00', 259, 260),
(245, 55, 0, 70, '0000-00-00 00:00:00', 261, 262),
(336, 1, 0, 37, '0000-00-00 00:00:00', 439, 440),
(247, 1, 0, 1, '0000-00-00 00:00:00', 37, 38),
(248, 66, 0, 15, '0000-00-00 00:00:00', 265, 266),
(335, 1, 0, 17, '0000-00-00 00:00:00', 437, 438),
(250, 1, 0, 15, '0000-00-00 00:00:00', 269, 270),
(251, 1, 0, 15, '0000-00-00 00:00:00', 271, 272),
(252, 1, 0, 15, '0000-00-00 00:00:00', 273, 274),
(253, 1, 0, 15, '0000-00-00 00:00:00', 275, 276),
(254, 1, 0, 15, '0000-00-00 00:00:00', 277, 278),
(255, 1, 0, 15, '0000-00-00 00:00:00', 279, 280),
(256, 1, 0, 15, '0000-00-00 00:00:00', 281, 282),
(257, 1, 0, 15, '0000-00-00 00:00:00', 283, 284),
(258, 1, 0, 15, '0000-00-00 00:00:00', 285, 286),
(343, 1, 0, 37, '0000-00-00 00:00:00', 451, 452),
(342, 3, 0, 1, '0000-00-00 00:00:00', 41, 42),
(341, 3, 0, 43, '0000-00-00 00:00:00', 449, 450),
(340, 2, 0, 31, '0000-00-00 00:00:00', 447, 448),
(339, 1, 0, 37, '0000-00-00 00:00:00', 445, 446),
(264, 1, 0, 15, '0000-00-00 00:00:00', 297, 298),
(265, 1, 0, 15, '0000-00-00 00:00:00', 299, 300),
(266, 1, 0, 15, '0000-00-00 00:00:00', 301, 302),
(334, 1, 0, 17, '0000-00-00 00:00:00', 435, 436),
(268, 1, 0, 78, '0000-00-00 00:00:00', 305, 306),
(269, 1, 0, 78, '0000-00-00 00:00:00', 307, 308),
(270, 1, 0, 78, '0000-00-00 00:00:00', 309, 310),
(271, 1, 0, 78, '0000-00-00 00:00:00', 311, 312),
(272, 1, 0, 78, '0000-00-00 00:00:00', 313, 314),
(273, 1, 0, 78, '0000-00-00 00:00:00', 315, 316),
(274, 1, 0, 78, '0000-00-00 00:00:00', 317, 318),
(275, 1, 0, 15, '0000-00-00 00:00:00', 319, 320),
(276, 1, 0, 15, '0000-00-00 00:00:00', 321, 322),
(277, 1, 0, 15, '0000-00-00 00:00:00', 323, 324),
(278, 1, 0, 15, '0000-00-00 00:00:00', 325, 326),
(279, 1, 0, 15, '0000-00-00 00:00:00', 327, 328),
(280, 1, 0, 15, '0000-00-00 00:00:00', 329, 330),
(281, 1, 0, 15, '0000-00-00 00:00:00', 331, 332),
(282, 1, 0, 15, '0000-00-00 00:00:00', 333, 334),
(283, 1, 0, 15, '0000-00-00 00:00:00', 335, 336),
(284, 1, 0, 15, '0000-00-00 00:00:00', 337, 338),
(285, 1, 0, 15, '0000-00-00 00:00:00', 339, 340),
(338, 1, 0, 37, '0000-00-00 00:00:00', 443, 444),
(337, 1, 0, 37, '0000-00-00 00:00:00', 441, 442),
(332, 1, 0, 8, '0000-00-00 00:00:00', 431, 432),
(289, 1, 0, 1, '0000-00-00 00:00:00', 39, 40),
(290, 1, 0, 15, '0000-00-00 00:00:00', 347, 348),
(291, 1, 0, 15, '0000-00-00 00:00:00', 349, 350),
(292, 1, 0, 15, '0000-00-00 00:00:00', 351, 352),
(293, 1, 0, 15, '0000-00-00 00:00:00', 353, 354),
(294, 1, 0, 17, '0000-00-00 00:00:00', 355, 356),
(295, 1, 0, 18, '0000-00-00 00:00:00', 357, 358),
(296, 1, 0, 18, '0000-00-00 00:00:00', 359, 360),
(297, 1, 0, 18, '0000-00-00 00:00:00', 361, 362),
(298, 1, 0, 32, '0000-00-00 00:00:00', 363, 364),
(333, 1, 0, 15, '0000-00-00 00:00:00', 433, 434),
(300, 1, 0, 36, '0000-00-00 00:00:00', 367, 368),
(301, 1, 0, 36, '0000-00-00 00:00:00', 369, 370),
(302, 1, 0, 36, '0000-00-00 00:00:00', 371, 372),
(303, 1, 0, 16, '0000-00-00 00:00:00', 373, 374),
(304, 1, 0, 20, '0000-00-00 00:00:00', 375, 376),
(305, 1, 0, 15, '0000-00-00 00:00:00', 377, 378),
(306, 1, 0, 21, '0000-00-00 00:00:00', 379, 380),
(307, 1, 0, 21, '0000-00-00 00:00:00', 381, 382),
(308, 1, 0, 21, '0000-00-00 00:00:00', 383, 384),
(309, 1, 0, 8, '0000-00-00 00:00:00', 385, 386),
(310, 1, 0, 8, '0000-00-00 00:00:00', 387, 388),
(311, 1, 0, 8, '0000-00-00 00:00:00', 389, 390),
(312, 1, 0, 8, '0000-00-00 00:00:00', 391, 392),
(313, 1, 0, 8, '0000-00-00 00:00:00', 393, 394),
(314, 1, 0, 8, '0000-00-00 00:00:00', 395, 396),
(315, 1, 0, 20, '0000-00-00 00:00:00', 397, 398),
(316, 1, 0, 20, '0000-00-00 00:00:00', 399, 400),
(317, 1, 0, 20, '0000-00-00 00:00:00', 401, 402),
(318, 1, 0, 20, '0000-00-00 00:00:00', 403, 404),
(319, 1, 0, 8, '0000-00-00 00:00:00', 405, 406),
(320, 1, 0, 8, '0000-00-00 00:00:00', 407, 408),
(321, 1, 0, 15, '0000-00-00 00:00:00', 409, 410),
(322, 1, 0, 25, '0000-00-00 00:00:00', 411, 412),
(323, 1, 0, 8, '0000-00-00 00:00:00', 413, 414),
(324, 1, 0, 16, '0000-00-00 00:00:00', 415, 416),
(325, 1, 0, 17, '0000-00-00 00:00:00', 417, 418),
(326, 1, 0, 17, '0000-00-00 00:00:00', 419, 420),
(327, 1, 0, 17, '0000-00-00 00:00:00', 421, 422),
(328, 1, 0, 15, '0000-00-00 00:00:00', 423, 424),
(329, 1, 0, 8, '0000-00-00 00:00:00', 425, 426),
(330, 1, 0, 70, '0000-00-00 00:00:00', 427, 428),
(331, 1, 0, 37, '0000-00-00 00:00:00', 429, 430),
(344, 223, 0, 1, '0000-00-00 00:00:00', 43, 44),
(345, 223, 0, 23, '0000-00-00 00:00:00', 453, 454),
(346, 223, 0, 23, '0000-00-00 00:00:00', 455, 456),
(347, 223, 0, 1, '0000-00-00 00:00:00', 45, 46),
(348, 76, 0, 28, '0000-00-00 00:00:00', 457, 458),
(349, 76, 0, 1, '0000-00-00 00:00:00', 47, 48),
(350, 76, 0, 1, '0000-00-00 00:00:00', 49, 50),
(351, 76, 0, 1, '0000-00-00 00:00:00', 51, 52),
(352, 76, 0, 28, '0000-00-00 00:00:00', 459, 460),
(353, 76, 0, 28, '0000-00-00 00:00:00', 461, 462),
(354, 76, 0, 28, '0000-00-00 00:00:00', 463, 464),
(355, 76, 0, 28, '0000-00-00 00:00:00', 465, 466),
(356, 76, 0, 28, '0000-00-00 00:00:00', 467, 468),
(357, 76, 0, 28, '0000-00-00 00:00:00', 469, 470),
(358, 76, 0, 1, '0000-00-00 00:00:00', 53, 54),
(359, 76, 0, 1, '0000-00-00 00:00:00', 55, 56),
(360, 76, 0, 1, '0000-00-00 00:00:00', 57, 58),
(361, 76, 0, 1, '0000-00-00 00:00:00', 59, 60),
(362, 76, 0, 1, '0000-00-00 00:00:00', 61, 62),
(363, 76, 0, 28, '0000-00-00 00:00:00', 471, 472),
(364, 76, 0, 28, '0000-00-00 00:00:00', 473, 474),
(365, 76, 0, 28, '0000-00-00 00:00:00', 475, 476),
(366, 76, 0, 28, '0000-00-00 00:00:00', 477, 478),
(367, 76, 0, 28, '0000-00-00 00:00:00', 479, 480),
(368, 76, 0, 1, '0000-00-00 00:00:00', 63, 64),
(369, 76, 0, 28, '0000-00-00 00:00:00', 481, 482),
(370, 76, 0, 28, '0000-00-00 00:00:00', 483, 484),
(371, 76, 0, 28, '0000-00-00 00:00:00', 485, 486),
(372, 76, 0, 28, '0000-00-00 00:00:00', 487, 488),
(373, 76, 0, 28, '0000-00-00 00:00:00', 489, 490),
(374, 76, 0, 28, '0000-00-00 00:00:00', 491, 492),
(375, 76, 0, 28, '0000-00-00 00:00:00', 493, 494),
(376, 76, 0, 28, '0000-00-00 00:00:00', 495, 496),
(377, 76, 0, 28, '0000-00-00 00:00:00', 497, 498),
(378, 76, 0, 28, '0000-00-00 00:00:00', 499, 500),
(379, 76, 0, 28, '0000-00-00 00:00:00', 501, 502),
(380, 76, 0, 28, '0000-00-00 00:00:00', 503, 504),
(381, 76, 0, 28, '0000-00-00 00:00:00', 505, 506),
(382, 76, 0, 28, '0000-00-00 00:00:00', 507, 508),
(383, 76, 0, 28, '0000-00-00 00:00:00', 509, 510),
(384, 76, 0, 28, '0000-00-00 00:00:00', 511, 512),
(385, 76, 0, 28, '0000-00-00 00:00:00', 513, 514),
(386, 76, 0, 28, '0000-00-00 00:00:00', 515, 516),
(387, 76, 0, 28, '0000-00-00 00:00:00', 517, 518),
(388, 77, 0, 37, '0000-00-00 00:00:00', 519, 520),
(389, 77, 0, 37, '0000-00-00 00:00:00', 521, 522),
(390, 77, 0, 30, '0000-00-00 00:00:00', 523, 524),
(391, 24, 0, 25, '0000-00-00 00:00:00', 525, 526),
(392, 77, 0, 17, '0000-00-00 00:00:00', 527, 528),
(393, 77, 0, 30, '0000-00-00 00:00:00', 529, 530),
(394, 77, 0, 30, '0000-00-00 00:00:00', 531, 532),
(395, 77, 0, 30, '0000-00-00 00:00:00', 533, 534),
(396, 77, 0, 71, '0000-00-00 00:00:00', 535, 536),
(397, 77, 0, 32, '0000-00-00 00:00:00', 537, 538),
(398, 77, 0, 32, '0000-00-00 00:00:00', 539, 540),
(399, 77, 0, 32, '0000-00-00 00:00:00', 541, 542),
(400, 77, 0, 32, '0000-00-00 00:00:00', 543, 544),
(401, 77, 0, 32, '0000-00-00 00:00:00', 545, 546),
(402, 77, 0, 32, '0000-00-00 00:00:00', 547, 548),
(403, 77, 0, 32, '0000-00-00 00:00:00', 549, 550),
(404, 77, 0, 32, '0000-00-00 00:00:00', 551, 552),
(405, 77, 0, 32, '0000-00-00 00:00:00', 553, 554),
(406, 77, 0, 30, '0000-00-00 00:00:00', 555, 556),
(407, 77, 0, 32, '0000-00-00 00:00:00', 557, 558),
(408, 77, 0, 32, '0000-00-00 00:00:00', 559, 560),
(409, 77, 0, 32, '0000-00-00 00:00:00', 561, 562),
(410, 77, 0, 32, '0000-00-00 00:00:00', 563, 564),
(411, 77, 0, 32, '0000-00-00 00:00:00', 565, 566),
(412, 77, 0, 32, '0000-00-00 00:00:00', 567, 568),
(413, 77, 0, 32, '0000-00-00 00:00:00', 569, 570),
(414, 77, 0, 32, '0000-00-00 00:00:00', 571, 572),
(415, 77, 0, 32, '0000-00-00 00:00:00', 573, 574),
(416, 77, 0, 32, '0000-00-00 00:00:00', 575, 576),
(417, 77, 0, 32, '0000-00-00 00:00:00', 577, 578),
(418, 77, 0, 32, '0000-00-00 00:00:00', 579, 580),
(419, 77, 0, 32, '0000-00-00 00:00:00', 581, 582),
(420, 77, 0, 32, '0000-00-00 00:00:00', 583, 584),
(421, 77, 0, 32, '0000-00-00 00:00:00', 585, 586),
(422, 78, 0, 38, '0000-00-00 00:00:00', 587, 588),
(423, 78, 0, 38, '0000-00-00 00:00:00', 589, 590),
(424, 78, 0, 38, '0000-00-00 00:00:00', 591, 592),
(425, 227, 0, 73, '0000-00-00 00:00:00', 593, 594),
(426, 227, 0, 38, '0000-00-00 00:00:00', 595, 596),
(427, 227, 0, 39, '0000-00-00 00:00:00', 597, 598),
(428, 227, 0, 70, '0000-00-00 00:00:00', 599, 600),
(429, 227, 0, 70, '0000-00-00 00:00:00', 601, 602),
(430, 227, 0, 18, '0000-00-00 00:00:00', 603, 604),
(431, 227, 0, 1, '0000-00-00 00:00:00', 65, 66),
(432, 227, 0, 99, '0000-00-00 00:00:00', 605, 606),
(433, 227, 0, 99, '0000-00-00 00:00:00', 607, 608),
(434, 227, 0, 99, '0000-00-00 00:00:00', 609, 610),
(435, 227, 0, 99, '0000-00-00 00:00:00', 611, 612),
(436, 227, 0, 99, '0000-00-00 00:00:00', 613, 614),
(437, 227, 0, 70, '0000-00-00 00:00:00', 615, 616),
(438, 227, 0, 99, '0000-00-00 00:00:00', 617, 618),
(439, 227, 0, 39, '0000-00-00 00:00:00', 619, 620),
(440, 227, 0, 38, '0000-00-00 00:00:00', 621, 622),
(441, 227, 0, 70, '0000-00-00 00:00:00', 623, 624),
(442, 227, 0, 18, '0000-00-00 00:00:00', 625, 626),
(443, 227, 0, 73, '0000-00-00 00:00:00', 627, 628),
(444, 227, 0, 70, '0000-00-00 00:00:00', 629, 630),
(445, 227, 0, 38, '0000-00-00 00:00:00', 631, 632),
(446, 227, 0, 39, '0000-00-00 00:00:00', 633, 634),
(447, 227, 0, 99, '0000-00-00 00:00:00', 635, 636),
(448, 227, 0, 99, '0000-00-00 00:00:00', 637, 638),
(449, 227, 0, 39, '0000-00-00 00:00:00', 639, 640),
(450, 227, 0, 38, '0000-00-00 00:00:00', 641, 642),
(451, 227, 0, 70, '0000-00-00 00:00:00', 643, 644),
(452, 227, 0, 18, '0000-00-00 00:00:00', 645, 646),
(453, 227, 0, 73, '0000-00-00 00:00:00', 647, 648),
(454, 227, 0, 1, '0000-00-00 00:00:00', 67, 68),
(455, 227, 0, 38, '0000-00-00 00:00:00', 649, 650),
(456, 227, 0, 39, '0000-00-00 00:00:00', 651, 652),
(457, 227, 0, 99, '0000-00-00 00:00:00', 653, 654),
(458, 227, 0, 99, '0000-00-00 00:00:00', 655, 656),
(459, 227, 0, 39, '0000-00-00 00:00:00', 657, 658),
(460, 227, 0, 38, '0000-00-00 00:00:00', 659, 660),
(461, 227, 0, 70, '0000-00-00 00:00:00', 661, 662),
(462, 227, 0, 70, '0000-00-00 00:00:00', 663, 664),
(463, 227, 0, 18, '0000-00-00 00:00:00', 665, 666),
(464, 227, 0, 1, '0000-00-00 00:00:00', 69, 70),
(465, 77, 0, 32, '0000-00-00 00:00:00', 667, 668),
(466, 77, 0, 32, '0000-00-00 00:00:00', 669, 670),
(467, 77, 0, 17, '0000-00-00 00:00:00', 671, 672),
(468, 77, 0, 32, '0000-00-00 00:00:00', 673, 674),
(469, 77, 0, 32, '0000-00-00 00:00:00', 675, 676),
(470, 77, 0, 32, '0000-00-00 00:00:00', 677, 678),
(471, 77, 0, 32, '0000-00-00 00:00:00', 679, 680),
(472, 77, 0, 32, '0000-00-00 00:00:00', 681, 682),
(473, 77, 0, 32, '0000-00-00 00:00:00', 683, 684),
(474, 76, 0, -1, '0000-00-00 00:00:00', 1, 2),
(475, 76, 0, -1, '0000-00-00 00:00:00', 71, 72),
(476, 75, 491, -1, '0000-00-00 00:00:00', 5, 6),
(477, 76, 0, -1, '0000-00-00 00:00:00', 7, 8),
(478, 76, 0, -2, '0000-00-00 00:00:00', 9, 10),
(479, 76, 0, -2, '0000-00-00 00:00:00', 11, 12),
(480, 76, 0, -2, '0000-00-00 00:00:00', 13, 14),
(481, 76, 0, -2, '0000-00-00 00:00:00', 15, 16),
(482, 76, 0, -1, '0000-00-00 00:00:00', 17, 18),
(483, 76, 0, -1, '0000-00-00 00:00:00', 19, 20),
(484, 76, 0, -1, '0000-00-00 00:00:00', 21, 22),
(485, 76, 0, -1, '0000-00-00 00:00:00', 23, 24),
(486, 76, 0, -1, '0000-00-00 00:00:00', 25, 26),
(487, 76, 0, -1, '0000-00-00 00:00:00', 27, 28),
(488, 76, 0, -1, '0000-00-00 00:00:00', 29, 30),
(489, 76, 0, -1, '0000-00-00 00:00:00', 31, 32),
(490, 76, 0, -1, '0000-00-00 00:00:00', 33, 34),
(491, 76, 0, -1, '0000-00-00 00:00:00', 35, 36),
(492, 76, 0, -1, '0000-00-00 00:00:00', 37, 38),
(493, 76, 0, -1, '0000-00-00 00:00:00', 39, 40),
(494, 1, 0, 6, '0000-00-00 00:00:00', 41, 42),
(495, 1, 0, 6, '0000-00-00 00:00:00', 43, 44),
(496, 1, 0, 6, '0000-00-00 00:00:00', 47, 48),
(497, 1, 0, 6, '0000-00-00 00:00:00', 49, 50),
(498, 76, 0, 4, '0000-00-00 00:00:00', 51, 52),
(499, 76, 0, 1, '0000-00-00 00:00:00', 74, 75),
(500, 76, 0, 1, '0000-00-00 00:00:00', 76, 77),
(501, 76, 0, 1, '0000-00-00 00:00:00', 78, 79),
(502, 76, 0, 1, '0000-00-00 00:00:00', 80, 81),
(503, 76, 0, 4, '0000-00-00 00:00:00', 53, 54),
(504, 76, 0, 4, '0000-00-00 00:00:00', 55, 56),
(505, 76, 0, 70, '0000-00-00 00:00:00', 685, 686),
(506, 76, 0, 70, '0000-00-00 00:00:00', 687, 688),
(507, 76, 0, 28, '0000-00-00 00:00:00', 689, 690),
(508, 76, 0, 28, '0000-00-00 00:00:00', 691, 692),
(509, 76, 0, 1, '0000-00-00 00:00:00', 82, 83),
(510, 76, 0, 1, '0000-00-00 00:00:00', 84, 85),
(511, 76, 0, 28, '0000-00-00 00:00:00', 693, 694),
(512, 76, 0, 28, '0000-00-00 00:00:00', 695, 696),
(513, 76, 0, 4, '0000-00-00 00:00:00', 57, 58),
(514, 76, 0, 4, '0000-00-00 00:00:00', 59, 60),
(515, 76, 0, 1, '0000-00-00 00:00:00', 86, 87),
(516, 76, 0, 1, '0000-00-00 00:00:00', 88, 89),
(517, 76, 0, 1, '0000-00-00 00:00:00', 90, 91),
(518, 76, 0, 4, '0000-00-00 00:00:00', 61, 62),
(519, 76, 0, 1, '0000-00-00 00:00:00', 92, 93),
(520, 76, 0, 1, '0000-00-00 00:00:00', 94, 95),
(521, 76, 0, 1, '0000-00-00 00:00:00', 96, 97),
(522, 76, 0, 1, '0000-00-00 00:00:00', 98, 99),
(523, 76, 0, 28, '0000-00-00 00:00:00', 698, 699),
(524, 76, 0, 4, '0000-00-00 00:00:00', 63, 64),
(525, 76, 0, 1, '0000-00-00 00:00:00', 100, 101),
(526, 76, 0, 28, '0000-00-00 00:00:00', 700, 701),
(527, 76, 0, 4, '0000-00-00 00:00:00', 65, 66),
(528, 76, 0, 1, '0000-00-00 00:00:00', 102, 103),
(529, 76, 0, 1, '0000-00-00 00:00:00', 104, 105),
(530, 76, 0, 107, '0000-00-00 00:00:00', 67, 68),
(531, 76, 0, 28, '0000-00-00 00:00:00', 702, 703),
(532, 76, 0, 4, '0000-00-00 00:00:00', 69, 70),
(533, 76, 0, 1, '0000-00-00 00:00:00', 106, 107),
(534, 76, 0, 1, '0000-00-00 00:00:00', 108, 109),
(535, 76, 0, 1, '0000-00-00 00:00:00', 110, 111),
(536, 245, 0, 37, '0000-00-00 00:00:00', 704, 705),
(537, 245, 0, 37, '0000-00-00 00:00:00', 706, 707),
(538, 245, 0, 37, '0000-00-00 00:00:00', 708, 709),
(539, 245, 0, 37, '0000-00-00 00:00:00', 710, 711),
(540, 245, 0, 37, '0000-00-00 00:00:00', 712, 713),
(541, 245, 0, 37, '0000-00-00 00:00:00', 714, 715),
(542, 245, 0, 37, '0000-00-00 00:00:00', 716, 717),
(543, 245, 0, 37, '0000-00-00 00:00:00', 718, 719),
(544, 245, 0, 37, '0000-00-00 00:00:00', 720, 721),
(545, 245, 0, 37, '0000-00-00 00:00:00', 726, 727),
(546, 245, 0, 37, '0000-00-00 00:00:00', 728, 729),
(547, 245, 0, 37, '0000-00-00 00:00:00', 730, 731),
(548, 245, 0, 37, '0000-00-00 00:00:00', 732, 733);

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE IF NOT EXISTS `admin` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `username` varchar(20) COLLATE utf8_bin NOT NULL,
  `first_name` varchar(20) COLLATE utf8_bin NOT NULL,
  `last_name` varchar(20) COLLATE utf8_bin NOT NULL,
  `password` varchar(128) COLLATE utf8_bin NOT NULL,
  `email` varchar(60) COLLATE utf8_bin NOT NULL,
  `type` int(2) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=5 ;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`id`, `username`, `first_name`, `last_name`, `password`, `email`, `type`) VALUES
(3, 'mcstephens', 'Matthew', 'Stephens', '8M7eqtCIQpTXMHidxpMIsC5Z7KlzKpyc', 'mcstephens@gmail.com', 1),
(4, 'mgray', 'Mark', 'Gray', 'awJ4X+PbPhn9c0/fV5Bns+4xkqRYT4wX', 'mgray15@angelo.edu', 0);

-- --------------------------------------------------------

--
-- Table structure for table `admin_types`
--

CREATE TABLE IF NOT EXISTS `admin_types` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` varchar(32) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=2 ;

--
-- Dumping data for table `admin_types`
--

INSERT INTO `admin_types` (`id`, `type`) VALUES
(1, 'administrator');

-- --------------------------------------------------------

--
-- Table structure for table `articles`
--

CREATE TABLE IF NOT EXISTS `articles` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(128) COLLATE utf8_bin NOT NULL,
  `article` text COLLATE utf8_bin NOT NULL,
  `entry_date` varchar(64) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=10 ;

--
-- Dumping data for table `articles`
--

INSERT INTO `articles` (`id`, `name`, `article`, `entry_date`) VALUES
(1, 'Article 1', '<p>Fusce sollicitudin lobortis enim, vitae tempus libero lobortis nec. Quisque sit amet porta massa. Phasellus sed\nante ac nibh laoreet tincidunt a in mauris. Donec sit amet enim elementum, volutpat diam at, luctus dolor. Donec \nconvallis mollis pulvinar. Nunc egestas enim leo, ut tempus neque elementum sit amet. Donec elementum condimentum \nipsum, eget facilisis metus facilisis vitae. .</p>', '2013-12-22'),
(2, 'Article 2', '<p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Suspendisse aliquam consequat ornare. \nPellentesque sodales, sapien ut volutpat feugiat, risus nunc iaculis diam, sed lacinia dolor odio \nvel velit. Sed ut lorem semper, ornare turpis eget, suscipit lorem. Integer varius cursus leo sed \ncursus. Cras diam neque, euismod vitae sapien ut, imperdiet viverra metus.</p>', '2013-12-23'),
(3, 'Article 3', '<p>Sed sit amet bibendum orci. Suspendisse pellentesque aliquam neque, ac rutrum lacus pellentesque vitae.&nbsp;Morbi sed nibh eget risus laoreet volutpat. Integer fermentum aliquet tempus..</p>\n', '2013-12-24'),
(4, 'CitiBizList', '<p><a href="http://107.21.206.109/press/PR_Rising_Venture_Award_Citibiz_6_2011.pdf" target="_blank">MedHab, Coltrix among top five at Rice Alliance competition</a></p>\n', '2013-12-27'),
(5, 'Fort Worth Business Press', '<p><a href="http://107.21.206.109/press/PR_Patent_New_Release_5_2011.pdf" target="_blank">Mansfield firm gets patent for medical product</a></p>\r\n', '2013-12-27'),
(6, 'Star-Telegram', '<p><a href="http://107.21.206.109/press/PR_TECH_awards.pdf" target="_blank">TECH Fort Worth IMPACT Awards Finalists</a></p>\r\n', '2013-12-27'),
(7, 'Neeley School of Business', '<p><a href="http://107.21.206.109/press/PR_Entrepreneur_09102010.pdf" target="_blank">Do You Have What it Takes to be an Entrepreneur?</a></p>\r\n', '2013-12-27'),
(8, 'Star Telegram (Sandra Baker)', '<p><a href="http://107.21.206.109/press/PR_Award_07052010.pdf" target="_blank">Award is step in the right direction for inventors of leg-rehab device</a></p>\r\n', '2013-12-27'),
(9, 'dBusinessNews', '<p><a href="http://107.21.206.109/press/PR_MostPromising_06292010.pdf" target="_blank">Rice Alliance recognizes MedHab as &#39;Most Promising&#39;</a></p>\r\n', '2013-12-27');

-- --------------------------------------------------------

--
-- Table structure for table `authlock`
--

CREATE TABLE IF NOT EXISTS `authlock` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `user_id` int(11) NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=26 ;

--
-- Dumping data for table `authlock`
--

INSERT INTO `authlock` (`id`, `user_id`, `timestamp`) VALUES
(20, 1, '2012-08-01 22:30:45');

-- --------------------------------------------------------

--
-- Table structure for table `authlock_log`
--

CREATE TABLE IF NOT EXISTS `authlock_log` (
  `id` bigint(20) unsigned NOT NULL AUTO_INCREMENT,
  `user_id` mediumint(9) NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=8 ;

--
-- Dumping data for table `authlock_log`
--

INSERT INTO `authlock_log` (`id`, `user_id`, `timestamp`) VALUES
(1, 0, '2012-08-01 22:02:26'),
(2, 0, '2012-08-01 22:30:45'),
(3, 0, '2012-08-01 22:38:54'),
(4, 0, '2013-05-11 00:13:29'),
(5, 0, '2013-05-24 20:28:33'),
(6, 0, '2013-05-25 00:34:43'),
(7, 0, '2013-07-19 02:11:41');

-- --------------------------------------------------------

--
-- Table structure for table `coefficients`
--

CREATE TABLE IF NOT EXISTS `coefficients` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `serial_number` int(11) DEFAULT NULL,
  `type` int(11) DEFAULT NULL,
  `f1_c1` float DEFAULT NULL,
  `f1_c2` float DEFAULT NULL,
  `f1_c3` float DEFAULT NULL,
  `f1_c4` float DEFAULT NULL,
  `f2_c1` float DEFAULT NULL,
  `f2_c2` float DEFAULT NULL,
  `f2_c3` float DEFAULT NULL,
  `f2_c4` float DEFAULT NULL,
  `f3_c1` float DEFAULT NULL,
  `f3_c2` float DEFAULT NULL,
  `f3_c3` float DEFAULT NULL,
  `f3_c4` float DEFAULT NULL,
  `f4_c1` float DEFAULT NULL,
  `f4_c2` float DEFAULT NULL,
  `f4_c3` float DEFAULT NULL,
  `f4_c4` float DEFAULT NULL,
  `ax_offset` float DEFAULT NULL,
  `ax_sensitivity` float DEFAULT NULL,
  `ay_offset` float DEFAULT NULL,
  `ay_sensitivity` float DEFAULT NULL,
  `az_offset` float DEFAULT NULL,
  `az_sensitivity` float DEFAULT NULL,
  `gx_offset` float DEFAULT NULL,
  `gx_sensitivity` float DEFAULT NULL,
  `gy_offset` float DEFAULT NULL,
  `gy_sensitivity` float DEFAULT NULL,
  `gz_offset` float DEFAULT NULL,
  `gz_sensitivity` float DEFAULT NULL,
  `mx_offset` float DEFAULT NULL,
  `mx_sensitivity` float DEFAULT NULL,
  `my_offset` float DEFAULT NULL,
  `my_sensitivity` float DEFAULT NULL,
  `mz_offset` float DEFAULT NULL,
  `mz_sensitivity` float DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

-- --------------------------------------------------------

--
-- Table structure for table `custom_exercises`
--

CREATE TABLE IF NOT EXISTS `custom_exercises` (
  `id` mediumint(9) NOT NULL AUTO_INCREMENT,
  `exercise_id` mediumint(9) NOT NULL,
  `reps` mediumint(9) NOT NULL,
  `hold_time` int(11) DEFAULT NULL COMMENT 'seconds to hold a ROM exercise',
  `weight` int(11) DEFAULT NULL COMMENT 'Max weight bearing percent',
  PRIMARY KEY (`id`),
  KEY `ExId` (`exercise_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=39 ;

--
-- Dumping data for table `custom_exercises`
--

INSERT INTO `custom_exercises` (`id`, `exercise_id`, `reps`, `hold_time`, `weight`) VALUES
(1, 70, 10, 5, 50),
(2, 1, 1, 5, 50),
(3, 4, 10, 5, 50),
(4, 2, 1, 3, 50),
(29, 78, 10, 5, 50),
(28, 39, 10, 5, 50),
(27, 37, 10, 5, 50),
(26, 15, 10, 5, 50),
(25, 6, 10, 5, 50),
(24, 17, 10, 5, 50),
(30, 23, 10, 5, 50),
(38, 24, 10, 5, 50),
(37, 25, 10, 5, 50);

-- --------------------------------------------------------

--
-- Table structure for table `exercises`
--

CREATE TABLE IF NOT EXISTS `exercises` (
  `id` mediumint(9) NOT NULL AUTO_INCREMENT,
  `type` char(10) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `description` varchar(500) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `name` varchar(50) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `url` varchar(100) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `image` varchar(30) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `db_img` varchar(100) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `start_degrees` int(11) DEFAULT NULL,
  `anticlockwise` tinyint(1) DEFAULT NULL COMMENT '0 = false, 1 = true',
  `joint` varchar(10) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `isometric` tinyint(1) DEFAULT NULL COMMENT '0 = false, 1 = true',
  `primary_dashboard` int(11) DEFAULT NULL,
  `secondary_dashboard` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=130 ;

--
-- Dumping data for table `exercises`
--

INSERT INTO `exercises` (`id`, `type`, `description`, `name`, `url`, `image`, `db_img`, `start_degrees`, `anticlockwise`, `joint`, `isometric`, `primary_dashboard`, `secondary_dashboard`) VALUES
(1, '2', 'Stand in place as still as possible.  Do this for the hold time recommended by your provider.', 'Standing', NULL, 'images/exercise_img_1.png', 'dashboard_rom/images/images-rom/129_db.png', 90, 0, NULL, 0, 1, 0),
(2, '1', 'Gait', 'Gait', NULL, NULL, 'dashboard_rom/images/temp.png', 90, 0, NULL, 0, 3, 0),
(3, '2', 'Out of Protocol', 'Out of Protocol', NULL, NULL, 'dashboard_rom/images/temp.png', 0, 0, NULL, 0, 3, 0),
(4, '1', 'Walk 20 steps.', 'Walk - 20 Steps', NULL, NULL, 'dashboard_rom/images/temp.png', 90, 0, NULL, 0, 3, 0),
(5, '1', 'Walk 50 steps.', 'Walk - 5 Minutes', 'G_D2bRjKCVs', NULL, 'dashboard_rom/images/temp.png', 90, 0, NULL, 0, 3, 0),
(6, '1', 'Walk 100 steps.', 'Walk - 10 Minutes', 'BuO42-5_Rmo', NULL, 'dashboard_rom/images/temp.png', 90, 0, NULL, 0, 3, 0),
(7, '1', 'Walk 500 steps.', 'Walk - 15 Minutes', 'C3K1xZ_Ex-M', NULL, 'dashboard_rom/images/temp.png', 0, 1, NULL, 0, 3, 0),
(8, '1', 'Walk a quarter of a mile.', 'Walk - 30 Minutes', NULL, NULL, 'dashboard_rom/images/rom_hk27_db.png', 90, 0, NULL, 0, 3, 0),
(9, '1', 'Walk a half of a mile.', 'Walk - 45 Minutes', NULL, NULL, 'dashboard_rom/images/rom_hk29_db.png', 90, 0, NULL, 0, 3, 0),
(10, '1', 'Walk a mile.', 'Walk - 1 Hour', NULL, NULL, 'dashboard_rom/images/rom_le11_db.png', 90, 1, NULL, 0, 3, 0),
(16, '3', 'Balance on one foot, then rise on ball of foot.', 'Heel Raise (Unilateral, Standing) ', 'BuO42-5_Rmo', 'images/AF21.png', 'dashboard_rom/images/images-rom/16_db.png', 0, 1, 'A', 0, 2, 1),
(15, '3', 'Rise on balls of feet.', 'Heel Raise (Bilateral, Standing)', 'qxxLY9Ca04c', 'images/AF20.png', 'dashboard_rom/images/images-rom/15_db.png', 0, 1, 'A', 0, 2, 1),
(17, '3', 'Rock back on heels', 'Toe Raise (Standing) ', 'l0hDEEYAslc', 'images/AF22.png', 'dashboard_rom/images/images-rom/17_db.png', 180, 0, 'A', 0, 2, 1),
(18, '3', 'Sitting with one leg over edge of table or bed and a weight around foot, flex ankle, moving toes toward knee.', 'Dorsiflexion', '-syaAjQybsc', 'images/AF27.png', 'dashboard_rom/images/images-rom/18_db.png', 180, 0, 'A', 0, 2, 0),
(19, '3', 'Lying on stomach with one knee bent and a weight around foot, point foot toward ceiling.', 'Plantar Flexion (Knee Flexed, Prone) ', 'X21SDuwALY0', 'images/AF28.png', 'dashboard_rom/images/images-rom/19_db.png', 180, 0, 'A', 0, 2, 0),
(20, '3', 'With _____ pound weight around one foot, big toe up, bend ankle up and turn foot in.', 'Inversion (Side-Lying) ', 'DPlK6pMevH4', 'images/AF29.png', 'dashboard_rom/images/images-rom/20_db.png', 180, 0, 'A', 0, 2, 0),
(21, '3', 'With _____ pound weight around one foot, big toe down, bend ankle up and turn foot out.', 'Eversion (Side-Lying) ', 'W3hfa-KpsAE', 'images/AF30.png', 'dashboard_rom/images/images-rom/21_db.png', 180, 1, 'A', 0, 2, 0),
(22, '3', 'Feet flat, other foot forward, slide one foot back until gentle stretch is felt.  Keep entire foot on floor. Hold _____ seconds. Relax', 'Dorsiflexion (Self-Mobilization, Sitting) ', '7IjX64Qn4gA', 'images/AF42.png', 'dashboard_rom/images/images-rom/AF42.png', 90, 1, 'AK', 1, 1, 2),
(23, '3', 'Stand on ______ foot, hands on hips.  Keeping hips level, bend forward as if to touch forehead to wall.  Hold _____ seconds.', 'Balance: Forward Lean ', 'ko0f-GLSk6I', 'images/AF45.png', 'dashboard_rom/images/images-rom/AF45.png', 270, 1, 'AKH', 0, 1, 0),
(24, '3', 'Stand on ______ foot, holding ______ pound weight in other hand.  Bend knee, lowering body and reach across.  Hold _____ seconds.', 'Balance: Reach ', '-97BXKnQaSA', 'images/AF46.png', 'dashboard_rom/images/images-rom/AF46.png', 0, 1, 'AKH', 0, 1, 0),
(25, '3', 'Attempt to balance on _____ leg eyes _____.  Hold _____ seconds.', 'Balance with Eyes Open', 'mOZi180WdEc', 'images/AF15.png', 'dashboard_rom/images/images-rom/AF15.png', 0, 1, 'AKH', 0, 1, 0),
(26, '3', 'Eyes _____, balance with _____ leg on dense foam.  Hold _____ seconds.', 'Balance on Foam with Eyes Closed', 'sZY-eHxoZzs', 'images/AF26.png', 'dashboard_rom/images/images-rom/AF26.png', 0, 1, 'AKH', 0, 1, 0),
(27, '3', 'Bring _____ heel toward buttocks as close as possible.  Hold _____ seconds.', 'Self-Mobilization: Knee Flexion (Prone) ', 'YCvfyy-h-KY', 'images/HK8.png', 'dashboard_rom/images/images-rom/27_db.png', 0, 1, 'K', 0, 1, 2),
(28, '3', 'Tighten muscles on front of _____ thigh, then lift leg _____ inches from surface, keeping knee locked.', 'Straight Leg Raise (phase 1)', 'wAeueAklkao', 'images/HK17.png', 'dashboard_rom/images/images-rom/28_db.png', 0, 1, 'HK', 0, 2, 0),
(29, '3', 'Resting on forearms, tighten muscles on front of _____ thigh, then lift leg _____ inches from surface, keeping knee locked.', 'Straight Leg Raise (phase 2)', 'kQ-zbMz3Urs', 'images/HK18.png', 'dashboard_rom/images/images-rom/29_db.png', 0, 1, 'HK', 0, 2, 0),
(30, '3', 'Resting on hands, tighten muscles on front of _____ thigh, then lift leg _____ inches from surface, keeping knee locked.', 'Straight Leg Raise (phase 3)', 'LNlUkA59Ah8', 'images/HK19.png', 'dashboard_rom/images/images-rom/30_db.png', 0, 1, 'HK', 0, 2, 0),
(31, '3', 'Tighten muscles on front of _____ thigh, then lift leg _____ inches from surface, keeping knee locked.', 'Hip Extension (Prone) ', 'KwTAKx6KzNI', 'images/HK20.png', 'dashboard_rom/images/images-rom/31_db.png', 0, 1, 'HK', 0, 2, 1),
(32, '3', 'Tighten muscles on front of _____ thigh, then lift leg _____ inches from surface, keeping knee locked.', 'Hip Abduction ', 'Nx8cMCdZeYA', 'images/HK21.png', 'dashboard_rom/images/images-rom/32_db.png', 0, 1, 'HK', 0, 2, 0),
(33, '3', 'Tighten muscles on front of _____ thigh, then lift leg _____ inches from surface, keeping knee locked.', 'Hip Adduction', 'T5OYZT3IqJs', 'images/HK22.png', 'dashboard_rom/images/images-rom/33_db.png', 0, 1, 'H', 0, 2, 0),
(34, '3', 'With _____ knee over bolster, straighten knee by tightening muscles on top of thigh.  Keep bottom of knee on bolster.', 'Strengthening: Terminal Knee Extension (Supine) ', 'rnIryFuDJxY', 'images/HK23.png', 'dashboard_rom/images/images-rom/34_db.png', 0, 1, 'K', 0, 2, 0),
(35, '3', 'With support, bend _____ knee as far as possible.', 'Knee Flexion (Standing) ', 'LPCUe8ABgH0', 'images/HK24.png', 'dashboard_rom/images/images-rom/35_db.png', 90, 0, 'K', 0, 1, 2),
(36, '3', 'With tubing around _____ leg, bring leg across body.', 'Hip Adduction (Resisted) ', 'HT5f9yD6_w8', 'images/HK26.png', 'dashboard_rom/images/images-rom/36_db.png', 90, 0, 'H', 0, 2, 1),
(37, '3', 'With tubing around _____ leg, other side toward anchor, extend leg out from side.', 'Hip Abduction (Resisted) ', 'FTmPiBhEpJg', 'images/HK27.png', 'dashboard_rom/images/images-rom/37_db.png', 90, 0, 'H', 0, 2, 1),
(38, '3', 'With tubing around _____ leg, face anchor and pull leg straight back.', 'Hip Extension (Resisted) ', 'VDiPH12IQDw', 'images/HK28.png', 'dashboard_rom/images/images-rom/38_db.png', 90, 0, 'H', 0, 2, 1),
(39, '3', 'With tubing around _____ ankle, anchor behind, bring leg forward, keeping knee straight.', 'Hip Flexion (Resisted) ', '8xGswFLgtyc', 'images/HK29.png', 'dashboard_rom/images/images-rom/39_db.png', 90, 0, 'H', 0, 2, 1),
(40, '3', 'With tubing around ____ leg, anchor behind on the same side, begin with leg out behind.  Pull leg across front of body as if kicking a soccer ball.', 'Hip Diagonal Abduction (Resisted)', 'NRYmH9x9bqQ', 'images/HK30.png', 'dashboard_rom/images/images-rom/40_db.png', 90, 0, 'H', 0, 2, 1),
(41, '3', 'With tubing around _____ leg, anchor behind on other side, begin with leg in and behind.  Extend leg out from side as in karate kick.', 'Hip Diagonal Abduction', 'sUnllYCG-aM', 'images/HK31.png', 'dashboard_rom/images/images-rom/41_db.png', 90, 0, 'H', 0, 2, 1),
(42, '3', 'Place heels together and pull feet toward groin until stretch is felt in groin and inner thigh. Hold _____ seconds.', 'Stretching Inner Thigh ', 'qhCSlLvNkaY', 'images/HK32.png', 'dashboard_rom/images/images-rom/HK32.png', 0, 1, 'KH', 1, 1, 2),
(43, '3', 'Lying on floor with _____ leg on wall, other leg through doorway, scoot buttocks toward wall until stretch is felt in back of thigh. As leg relaxes, scoot closer to wall.  Hold _____ seconds.', 'Stretching Hamstring (Against Wall)', 'ipU4SimBDVM', 'images/HK33.png', 'dashboard_rom/images/images-rom/HK33.png', 0, 1, 'KH', 1, 1, 2),
(44, '3', 'Kneeling on _____ knee, slowly push pelvis down while slightly arching back until stretch is felt on front of hip.', 'Stretching Hip Flexor', 'EPxZW7XEyrM', 'images/HK34.png', 'dashboard_rom/images/images-rom/44_db.png', 0, 1, 'KHA', 0, 2, 1),
(45, '3', 'Cross _____ leg over other thigh and place elbow over outside of knee. Gently stretch buttock muscles by pushing bent knee across body.  Hold _____ seconds.', 'Stretching Piriformis', 'setYDRbrJpg', 'images/HK35.png', 'dashboard_rom/images/images-rom/HK35.png', 0, 1, 'H', 1, 1, 2),
(46, '3', 'Cross _____ leg over the other, then lean to same side until stretch is felt on other hip.  Hold _____ seconds.', 'Stretching Tensor', '-a62iNxjAjY', 'images/HK36.png', 'dashboard_rom/images/images-rom/46_db.png', 0, 1, 'H', 0, 2, 1),
(47, '3', 'Pull _____ heel toward buttock until stretch is felt in front of thigh.  Hold _____ seconds.', 'Stretching Quadriceps (Standing)', 'GY8Z_LyrR6k', 'images/HK37.png', 'dashboard_rom/images/images-rom/47_db.png', 0, 1, 'KH', 0, 2, 1),
(48, '3', 'Supporting _____ thigh behind knee, slowly straighten knee until stretch is felt in back of thigh.  Hold _____ seconds.', 'Stretching Hamstring (Supine)', '423Vl_NaZYE', 'images/HK38.png', 'dashboard_rom/images/images-rom/48_db.png', 0, 1, 'KH', 0, 2, 0),
(49, '3', 'Place _____ foot on stool.  Slowly lean forward, keeping back straight, until stretch is felt in back of thigh.  Hold _____ seconds.', 'Stretching Hamstring (Standing)', '1oFCrDoVqsQ', 'images/HK39.png', 'dashboard_rom/images/images-rom/49_db.png', 0, 1, 'HK', 0, 2, 1),
(50, '3', 'With _____ leg straight, tuck other foot near groin.  Reach down until stretch is felt in back of thigh.  Keep back straight.  Hold _____ seconds.', 'Stretching Hamstring (Sitting)', 'ipU4SimBDVM', 'images/HK40.png', 'dashboard_rom/images/images-rom/HK39.png', 0, 1, 'HK', 1, 1, 2),
(51, '3', 'Stand with _____ foot back, leg straight, forward leg bent.  Keeping heel on floor, turned slightly out, lean into wall until stretch is felt in calf.  Hold _____ seconds.', 'Stretching Gastroc', '1NyQymWmsQA', 'images/HK41.png', 'dashboard_rom/images/images-rom/HK41.png', 0, 1, 'AK', 0, 1, 0),
(52, '3', 'Stand with _____ foot back, both knees bent.  Keeping heels on floor, turned slightly out, lean into wall until stretch is felt in lower calf.  Hold _____ seconds.', 'Stretching Soleus', 'GOMlySMnE6M', 'images/HK42.png', 'dashboard_rom/images/images-rom/HK42.png', 0, 1, 'AK', 0, 1, 0),
(53, '3', 'Facing anchor with _____ knee slightly bent and tubing just above knee, gently pull knee straight back.  Do not overextend knee.', 'Terminal Knee Extension (Resisted)', 'V-FiFvdvIEw', 'images/HK43.png', 'dashboard_rom/images/images-rom/53_db.png', 90, 0, 'KH', 0, 2, 1),
(54, '3', 'Facing anchor with tubing on _____ ankle, leg straight out, bend knee.', 'Hamstring Curl (Resisted, Sitting)', 'LzKdzuCF2Ws', 'images/HK44.png', 'dashboard_rom/images/images-rom/54_db.png', 0, 0, 'K', 0, 2, 0),
(55, '3', 'Anchor behind, with tubing on _____ ankle, leg straight, bend knee.', 'Hamstring Curl (Resisted, Prone) ', 'U8nU2qmv70U', 'images/HK45.png', 'dashboard_rom/images/images-rom/55_db.png', 0, 1, 'K', 0, 2, 0),
(56, '3', 'Slowly "walk" or slide feet on wall toward floor until stretch is felt in knees.', 'Knee Wall Slide', 'ejkeNPZcQvQ', 'images/HK47.png', 'dashboard_rom/images/images-rom/HK47.png', 0, 0, 'K', 1, 1, 2),
(57, '3', 'Cross legs, ____ on top.  Gently pull other knee toward chest until stretch is felt in buttock/hip of top leg.', 'Piriformis (Sitting)', 'rpulCxkYp2Y', 'images/HK48.png', 'dashboard_rom/images/images-rom/57_db.png', 270, 1, 'H', 0, 1, 2),
(58, '3', 'With band looped around _____ ankle and under other foot, straighten leg with ankle loop.  Keep other leg bent to increase resistance.', 'Knee Extension (Resisted, Sitting) ', 'DvyUYQQfdIo', 'images/HK55.png', 'dashboard_rom/images/images-rom/58_db.png', 90, 0, 'K', 0, 2, 0),
(59, '3', 'Stand on step, _____ leg off step, knee straight.  Raise unsupported hip keeping knee straight.', 'Hip Hike', 'ha-oVJawVmQ', 'images/HK56.png', 'dashboard_rom/images/images-rom/59_db.png', 180, 0, 'H', 0, 2, 1),
(60, '3', 'Sit with band under _____ foot and looped around ankle of supported leg.  Pull unsupported leg back.', 'Knee Flexion (Resisted, Sitting) ', 'bkYtA-mMNJQ', 'images/HK57.png', 'dashboard_rom/images/images-rom/60_db.png', 90, 1, 'K', 0, 2, 0),
(61, '3', 'Sit with band loop around _____ ankle, anchor on same side.  Keeping thigh flat and knee bent at right angle, pull ankle across body.', 'Hip External Rotation (resisted, sitting) ', 'nNIwD-yRS0g', 'images/HK58.png', 'dashboard_rom/images/images-rom/61_db.png', 90, 0, 'H', 0, 2, 0),
(62, '3', 'Sit with band loop around _____ ankle, anchor on other side. Keeping thigh flat and knee bent at right angle, pull ankle away from body.', 'Hip Internal Rotation (Resisted, Sitting) ', 'f0YLlMlfz30', 'images/HK59.png', 'dashboard_rom/images/images-rom/62_db.png', 90, 0, 'H', 0, 2, 0),
(63, '3', 'With _____ foot on _____ inch step, raise other hip at right angle letting knee bend.', 'Hip Flexion ', 'WWVpCLpe1_o', 'images/HK60.png', 'dashboard_rom/images/images-rom/63_db.png', 0, 1, 'HK', 0, 2, 1),
(64, '3', 'With _____ leg supported, chair in front for balance, slowly bend other leg until stretch is felt in thigh of supported leg.  Hold _____ seconds.', 'Stretching Hip Flexor ', '_UjKQKDqf_o', 'images/HK61.png', 'dashboard_rom/images/images-rom/64_db.png', 0, 1, 'HK', 0, 2, 1),
(65, '3', 'Sit with knee straight and towel looped around _____ foot.  Gently pull on towel until stretch is felt in calf.  Hold _____ seconds.', 'Stretching Calf ', 'oJtJu2VK8rM', 'images/HK63.png', 'dashboard_rom/images/images-rom/65_db.png', 270, 0, 'AHK', 0, 2, 0),
(66, '3', 'Pull _____ knee toward opposite shoulder.  Hold _____ seconds.', 'Stretching Piriformis (Supine) ', 'L9kYazwJxpA', 'images/HK66.png', 'dashboard_rom/images/images-rom/66_db.png', 180, 1, 'H', 0, 2, 0),
(67, '3', 'Cross _____ leg behind other leg.  Bend at waist, reaching toward floor. Hold _____ seconds.', 'Stretching Iliotibial Band ', 'u4_LPfOjJhs', 'images/HK67.png', 'dashboard_rom/images/images-rom/HK67.png', 0, 1, 'HK', 1, 1, 2),
(68, '3', 'With _____ knee on knee-height surface, support with same side hand. Gently pull heel toward buttock. Hold _____ seconds.', 'Stretching Quadriceps ', '2_sh3RjPvTk', 'images/HK68.png', 'dashboard_rom/images/images-rom/68_db.png', 0, 1, 'AK', 0, 1, 2),
(69, '3', 'Stand with ball between knees. Squat with head up, reaching back with buttocks as if sitting down.', 'Mini Squat with Ball Squeeze ', 'PaOY3x3Q0lA', 'images/HK75.png', 'dashboard_rom/images/images-rom/HK75.png', 0, 1, 'AHK', 0, 1, 0),
(70, '3', 'Place _____ pound weight on _____ ankle and straighten knee fully, lower _____.', 'Knee Extension (Sitting) ', '4-ao5bmCo2k', 'images/HK76.png', 'dashboard_rom/images/images-rom/70_db.png', 90, 0, 'K', 0, 2, 0),
(71, '3', 'Sit on edge of chair, feet flat on floor. Stand upright extending knees fully.', 'Sit to Stand ', '9JL_sZcMcFs', 'images/HK77.png', 'dashboard_rom/images/images-rom/HK77.png', 0, 1, 'AHK', 0, 1, 0),
(72, '3', 'Keeping feet flat on floor, should width apart, squat as low as comfortable. Use support as necessary.', 'Chair Squat ', 't5K5s2N2l_E', 'images/HK78.png', 'dashboard_rom/images/images-rom/HK78.png', 0, 1, 'AHK', 0, 1, 0),
(73, '2', 'Stand with feet shoulder width apart and squat deeply, head and chest up.', 'Deep Squat', '6-zHVgF55Gk', 'images/HK79.png', 'dashboard_rom/images/images-rom/HK79.png', 0, 1, 'AHK', 0, 1, 0),
(74, '3', 'With support, _____ pound weight around _____ ankle, slowly bend knee up.  Return _____.', 'Knee Flexion (Resisted, Standing) ', '3mnMNCBujTk', 'images/HK80.png', 'dashboard_rom/images/images-rom/74_db.png', 90, 0, 'K', 0, 1, 2),
(75, '3', 'With foot of involved leg on step, straighten leg. Return.', 'Single Leg Step Up ', 'kW3N8GxaAHE', 'images/LE4.png', 'dashboard_rom/images/images-rom/75_db.png', 0, 1, 'AHK', 0, 1, 2),
(76, '3', 'Move onto step with one foot, then the other.  Step back off the same way.', 'Forward Step Up ', 'Z8lOnubcwMM', 'images/LE5.png', 'dashboard_rom/images/images-rom/76_db.png', 0, 1, 'AHK', 0, 1, 2),
(77, '3', 'Step on backwards with one foot, then the other. Step off forward the same way.', 'Retro Step Up ', 'Fhz9-K1rPA4', 'images/LE6.png', 'dashboard_rom/images/images-rom/77_db.png', 0, 1, 'AHK', 0, 1, 2),
(78, '3', 'With feet shoulder-width apart and back against wall, slide down wall until knees are at 30-45 degrees. Return.', 'Quarter Squat ', 'X9VQ9vgb02E', 'images/LE11.png', 'dashboard_rom/images/images-rom/LE11.png', 90, 1, 'AHK', 1, 1, 2),
(79, '3', 'Standing on involved leg with back against wall, slide down wall until knee is at 30-45 degrees. Return.', 'Single Leg Quarter Squat ', 'rETz-ywxCk4', 'images/LE12.png', 'dashboard_rom/images/images-rom/LE12.png', 0, 1, 'AHK', 1, 1, 2),
(80, '3', 'Rotate foot and ankle on board clockwise. Then rotate counterclockwise.', 'Balance Board (Sitting) ', 'i5qYeSNLOqo', 'images/LE32.png', 'dashboard_rom/images/temp.png', 0, 1, 'A', 1, 1, 2),
(81, '3', 'With involved leg on board and other foot on floor, rotate board clockwise, then counterclockwise.', 'Balance Board (Standing, Two Feet) ', 'Gi2bJNSmwB8', 'images/LE33.png', 'dashboard_rom/images/temp.png', 0, 1, 'A', 1, 1, 2),
(82, '3', 'Standing on board on the involved leg, rotate board clockwise, then counterclockwise.', 'Balance Board (Standing, One Foot) ', 'Kgxo-daci1I', 'images/LE34.png', 'dashboard_rom/images/temp.png', 0, 1, 'AHK', 0, 1, 0),
(83, '3', 'Pedal forward or backward. Adjust seat so leg is nearly straight when down.', 'Reserved', 'XUszlsxHf2k', 'images/LE37.png', 'dashboard_rom/images/images-rom/83_db.png', 0, 1, 'AHK', 0, 1, 2),
(84, '3', '_____ forward on treadmill at ______ mph with a ______ % elevation for ______ minutes or Do Program ___________ for _______ minutes.', 'Forward Treadmill ', 'pjQm2PDSAFY', 'images/LE45.png', 'dashboard_rom/images/images-rom/84_db.png', 0, 1, 'AHK', 0, 1, 2),
(85, '3', 'Walk backwards on treadmill at ______ mph with a ______ % elevation for _____ minutes.  Or do program _________________ for _____ minutes.', 'Backward Treadmill ', '5TaPVqw9qTg', 'images/LE46.png', 'dashboard_rom/images/images-rom/85_db.png', 0, 1, 'AHK', 0, 1, 2),
(86, '3', 'Perform side steps on treadmill at _____ mph with a _____ % elevation for _____ minutes or Do program _______________ for _____ minutes.', 'Sideways Treadmill ', 'ZewqSSXr2hg', 'images/LE47.png', 'dashboard_rom/images/images-rom/86_db.png', 0, 1, 'AHK', 0, 1, 2),
(87, '3', 'Using both legs "walk" forward down a long hallway.', 'Forward Stool Walk ', 'y6dmDeqkODM', 'images/LE49.png', 'dashboard_rom/images/temp.png', 0, 1, 'AK', 0, 1, 0),
(88, '3', 'Using both legs "walk" backward down a long hallway.', 'Retro Stool Walk ', 'PBpoTkTaofs', 'images/LE50.png', 'dashboard_rom/images/temp.png', 0, 1, 'AK', 0, 1, 0),
(89, '3', 'Using both legs "walk" sideways using side steps down a long hallway.', 'Sideways Stool Walk ', 'uXhAvw8Zecc', 'images/LE51.png', 'dashboard_rom/images/temp.png', 0, 1, 'AK', 0, 1, 0),
(93, '3', 'With rolled pillow against wall, press outer border of foot into pillow.  Hold _____ seconds. Relax.', 'Isometric Eversion', '5kZK1JJ9gVY', 'images/AF03.png', 'dashboard_rom/images/images-rom/AF03.png', 270, 1, 'AHK', 1, 1, 2),
(91, '3', 'With rolled pillow between feet, press inner borders of feet into pillow.  Hold for _____ seconds.  Relax', 'Isometric Inversion', 'aPy-zjbs31o', 'images/AF04.png', 'dashboard_rom/images/images-rom/AF04.png', 270, 1, 'AHK', 1, 1, 2),
(92, '3', 'With rolled pillow between feet, squeeze feet together.  Hold _____ seconds. Relax.', 'Isometric Dorsiflexion', 'Ir9ibhzl2hw', 'images/AF02.png', 'dashboard_rom/images/images-rom/AF02.png', 270, 1, 'AHK', 1, 1, 2),
(90, '3', 'With rolled pillow against wall, press foot into pillow. Hold for prescribed seconds. Relax.', 'Isometric Plantar Flexion', '5QsRcbdovO0', 'images/AF01.png', 'dashboard_rom/images/images-rom/AF01.png', 270, 1, 'AHK', 1, 1, 2),
(94, '3', 'With foot turned outward, tighten muscles on back of thigh by pulling heel downward into surface.  Hold _____ seconds.', 'Strengthening: External Hamstring', 'PorO6LAC2OA', 'images/HK13.png', 'dashboard_rom/images/images-rom/HK13.png', 270, 1, 'AHK', 1, 1, 2),
(95, '3', 'With foot turned inward, tighten muscles on back of thigh by pulling heel downward into surface.  Hold _____ seconds.', 'Strengthening: Internal Hamstring', 'Egw1nS2VnVc', 'images/HK12.png', 'dashboard_rom/images/images-rom/HK12.png', 0, 0, 'AHK', 1, 1, 2),
(96, '3', 'With folded pillow between knees, squeeze knees together.  Hold _____ seconds.', 'Strengthening: Isometric Hip Adduction', 'KAC88xxglWE', 'images/HK16.png', 'dashboard_rom/images/images-rom/HK16.png', 270, 0, 'AHK', 1, 1, 2),
(97, '3', 'Using a folded pillow, push outside of knee into wall. Hold _____ seconds.', 'Strengthening: Isometric Hip Abduction', 'UXYdUmvKrRU', 'images/HK15.png', 'dashboard_rom/images/images-rom/HK15.png', 270, 0, 'AHK', 1, 1, 2),
(98, '3', 'Tighten muscles on top of thigh by pushing knees down into surface. Hold _____ seconds.', 'Strengthening: Quadriceps Sets', NULL, 'images/HK11.png', 'dashboard_rom/images/images-rom/HK11.png', 0, 1, 'AHK', 1, 1, 2),
(99, '3', 'Eyes _____, balance with _____ leg on dense foam.  Hold _____ seconds.', 'Balance on Foam with Eyes Open', '5TTf2aGv5uQ', 'images/AF26.png', 'dashboard_rom/images/images-rom/AF26.png', 0, 1, 'AKH', 0, 1, 0),
(100, '3', 'Attempt to balance on _____ leg eyes _____.  Hold _____ seconds.', 'Balance with Eyes Closed', 'XpCoEwGzPrI', 'images/AF15.png', 'dashboard_rom/images/images-rom/AF15.png', 0, 1, 'AKH', 0, 1, 0),
(101, '3', 'Anchor behind, with tubing on _____ ankle, leg straight, bend knee.', 'Hamstring Curl (Prone)', 'lC88ymqsIGU', 'images/HK45-1.png', 'dashboard_rom/images/images-rom/101_db.png', 0, 1, 'K', 0, 2, 0),
(102, '3', 'Facing anchor with tubing on _____ ankle, leg straight out, bend knee.', 'Hamstring Curl (Sitting)', 'yfYGTX5sNsQ', 'images/HK44-1.png', 'dashboard_rom/images/images-rom/102_db.png', 0, 0, 'K', 0, 2, 0),
(103, '3', 'With tubing around _____ leg, face anchor and pull leg straight back.', 'Hip Extension (Standing)', 'GLebZ1MRFt0', 'images/HK28-1.png', 'dashboard_rom/images/images-rom/103_db.png', 90, 0, 'H', 0, 1, 2),
(104, '3', 'Sit with band loop around _____ ankle, anchor on other side. Keeping thigh flat and knee bent at right angle, pull ankle away from body.', 'Hip Internal Rotation (Sitting)', 'RP2uoLc_SPw', 'images/HK59-1.png', 'dashboard_rom/images/images-rom/104_db.png', 90, 0, 'H', 0, 2, 0),
(105, '3', 'Sit with band loop around _____ ankle, anchor on same side.  Keeping thigh flat and knee bent at right angle, pull ankle across body.', 'Hip External Rotation (Sitting)', 'QrY4ETkGQGI', 'images/HK58-1.png', 'dashboard_rom/images/images-rom/105_db.png', 90, 0, 'H', 0, 2, 0),
(106, '2', 'Pedal forward or backward. Adjust seat so leg is nearly straight when down.', 'Biking - 5 Minutes', 'XUszlsxHf2k', 'images/LE37.png', 'dashboard_rom/images/temp.png', 0, 1, 'AHK', 0, 4, 0),
(107, '2', 'Pedal forward or backward. Adjust seat so leg is nearly straight when down.', 'Biking - 10 Minutes', 'XUszlsxHf2k', 'images/LE37.png', 'dashboard_rom/images/temp.png', 0, 1, 'AHK', 0, 4, 0),
(108, '2', 'Pedal forward or backward. Adjust seat so leg is nearly straight when down.', 'Biking - 15 Minutes', 'XUszlsxHf2k', 'images/LE37.png', 'dashboard_rom/images/temp.png', 0, 1, 'AHK', 0, 4, 0),
(109, '2', 'Pedal forward or backward. Adjust seat so leg is nearly straight when down.', 'Biking - 30 Minutes', 'XUszlsxHf2k', 'images/LE37.png', 'dashboard_rom/images/temp.png', 0, 1, 'AHK', 0, 4, 0),
(110, '2', 'Pedal forward or backward. Adjust seat so leg is nearly straight when down.', 'Biking - 45 Minutes', 'XUszlsxHf2k', 'images/LE37.png', 'dashboard_rom/images/temp.png', 0, 1, 'AHK', 0, 4, 0),
(111, '2', 'Pedal forward or backward. Adjust seat so leg is nearly straight when down.', 'Biking - 1 Hour', 'XUszlsxHf2k', 'images/LE37.png', 'dashboard_rom/images/temp.png', 0, 1, 'AHK', 0, 4, 0),
(112, '3', 'Lift each leg one at a time', 'Marching Steps', 'nCzHT3raQZ8', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/112_db.png', 0, 1, 'AKH', 0, 1, 2),
(113, '3', 'Bending your knees with back straight step to the left 3 steps, then to the right 3 steps.', 'Bent Knee Side Steps', '5loI_qm6DVU', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/113_db.png', 0, 1, 'AKH', 0, 1, 2),
(114, '3', 'Laying on the ground, bring your knees up. Then, bring your buttocks up, tightening the muscles for ___ seconds, release.', 'Bridges', 'vXc3yUQ7z3Q', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/114_db.png', 0, 1, 'AKH', 0, 1, 2),
(115, '3', 'Leaning on a counter with either your hands or forearms, back straight, raise your heels up and hold for ___ seconds, release.', 'Counter Top Plank', 'ARV4QykcpOI', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/115_db.png', 0, 1, 'AKH', 0, 1, 2),
(116, '3', 'Legs apart, with dumbells in your hands, bend your knees keeping your back straight and hold for __ seconds.', 'Dumbell Squat', 'ffI6JrxM234', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/116_db.png', 0, 1, 'AKH', 0, 1, 2),
(117, '3', 'Balancing on one leg, toss a ball in the air and catch it for __ seconds.  Then switch legs and repeat.', 'Single Leg Stance with Ball Toss', 'XazLySEe4ow', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/117_db.png', 0, 1, 'AKH', 0, 1, 2),
(118, '3', 'Hands on your hips, standing straight up, put one leg forward and bend it half way down, hold for __ seconds.  Do the same for the other leg.', 'Mini Squat (Lunge)', 'QUAsCKVBWFA', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/118_db.png', 0, 1, 'AKH', 0, 1, 2),
(119, '3', 'Bending your knees, walk forward with arms swinging the opposite direction of your legs. Can be done backwards.', 'Monster Walk', 'xCCw0wbq5fc', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/119_db.png', 0, 1, 'AKH', 0, 1, 2),
(120, '3', 'Bending your left knee, extend your right foot forward and hold for __ seconds.  Then repeat on the other leg.', 'Single Leg Bent Knee Toe Touch Forward', 'OgSlCM_wdW8', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/120_db.png', 0, 1, 'AKH', 0, 1, 2),
(121, '3', 'Bending your left knee, extend your right foot to the side and hold for __ seconds.  Then repeat on the other leg.', 'Single Leg Bent Knee Toe Touch Side', 'KBn-XaR1O40', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/121_db.png', 0, 1, 'AKH', 0, 1, 2),
(122, '3', 'Bending your left knee, extend your right foot behind you and hold for __ seconds.  Then repeat on the other leg.', 'Single Leg Bent Knee Toe Touch to Rear', 'lHWXBLyr2aM', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/122_db.png', 0, 1, 'AKH', 0, 1, 2),
(123, '3', 'Standing straight up, extend your right foot forward and hold for __ seconds.  Then repeat on the other leg.', 'Single Leg Toe Touch Forward', 'O0wO3pl00ew', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/123_db.png', 0, 1, 'AKH', 0, 1, 2),
(124, '3', 'Standing straight up, extend your right foot behind you and hold for __ seconds.  Then repeat on the other leg.', 'Single Leg Toe Touch Rear', 'QrCD1B228-8', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/124_db.png', 0, 1, 'AKH', 0, 1, 2),
(125, '3', 'Standing straight up, extend your right foot to the side and hold for __ seconds.  Then repeat on the other leg.', 'Single Leg Toe Touch Side', 'RlSmVvLB0-k', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/125_db.png', 0, 1, 'AKH', 0, 1, 2),
(126, '3', 'Keeping your knees bent, take three steps diagonally with your right leg, then three steps with your left leg.', 'Zig Zag Step', 'iXpPcdZCzIQ', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/126_db.png', 0, 1, 'AKH', 0, 1, 2),
(127, '3', 'Lying on your side, bend your knees and then lift the upper knee using only your hips.  Hold ___ seconds.  Repeat on your other side.', 'The Clams', 'wiPd-8ERnt0', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/127_db.png', 0, 1, 'AKH', 0, 1, 2),
(128, '3', 'Lying on your side supporting yourself with your left arm, raise your hips up off the ground and hold for ___ seconds.  Repeat on other side.', 'Side Lying Plank', 'OmNGBZzP9Cw', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/128_db.png', 0, 1, 'AKH', 0, 1, 2),
(129, '3', 'Place right leg on stool or step, twist your body and step up lifting your left leg and holding for ___ seconds. Repeat on the other foot.', 'Transverse Step Up', 'nFzzaCmgyKI', 'images/usc_exercise.png', 'dashboard_rom/images/images-rom/129_db.png', 0, 1, 'AKH', 0, 1, 2);

-- --------------------------------------------------------

--
-- Table structure for table `exercise_types`
--

CREATE TABLE IF NOT EXISTS `exercise_types` (
  `id` smallint(2) NOT NULL,
  `name` char(5) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Dumping data for table `exercise_types`
--

INSERT INTO `exercise_types` (`id`, `name`) VALUES
(1, 'gait'),
(2, 'force'),
(3, 'rom');

-- --------------------------------------------------------

--
-- Table structure for table `extended_dates`
--

CREATE TABLE IF NOT EXISTS `extended_dates` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `patient_id` int(11) NOT NULL,
  `extended_from` date NOT NULL,
  `extended_to` date NOT NULL,
  `extended_when` datetime NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=56 ;

--
-- Dumping data for table `extended_dates`
--

INSERT INTO `extended_dates` (`id`, `patient_id`, `extended_from`, `extended_to`, `extended_when`) VALUES
(1, 12, '2012-06-14', '2012-07-14', '2012-06-27 00:00:00'),
(2, 12, '0000-00-00', '2012-07-21', '2012-06-28 00:00:00'),
(3, 12, '0000-00-00', '2012-07-28', '2012-06-28 00:00:00'),
(4, 12, '0000-00-00', '2012-07-31', '2012-06-28 00:00:00'),
(5, 12, '0000-00-00', '2012-08-04', '2012-06-28 16:45:28'),
(6, 12, '0000-00-00', '2012-08-11', '2012-06-28 17:00:07'),
(7, 12, '0000-00-00', '2012-09-01', '2012-06-28 18:58:25'),
(8, 12, '0000-00-00', '2012-07-31', '2012-06-28 19:00:20'),
(9, 12, '0000-00-00', '2012-08-01', '2012-06-28 21:12:31'),
(10, 12, '0000-00-00', '2012-08-02', '2012-06-28 21:23:45'),
(12, 14, '0000-00-00', '2012-07-01', '2012-06-28 21:45:13'),
(13, 15, '0000-00-00', '2012-07-07', '2012-06-29 18:54:22'),
(14, 1, '0000-00-00', '2012-07-14', '2012-07-10 21:00:03'),
(15, 54, '0000-00-00', '2012-07-21', '2012-07-10 21:23:27'),
(16, 27, '0000-00-00', '2012-07-14', '2012-07-11 20:33:54'),
(17, 0, '0000-00-00', '0000-00-00', '2012-07-11 20:35:57'),
(18, 59, '2012-07-14', '2012-07-16', '2012-07-12 19:54:17'),
(19, 59, '0000-00-00', '2012-07-18', '2012-07-12 20:10:24'),
(20, 59, '0000-00-00', '2012-07-18', '2012-07-12 20:12:36'),
(21, 59, '0000-00-00', '2012-07-20', '2012-07-12 20:23:45'),
(22, 59, '0000-00-00', '2012-07-20', '2012-07-12 20:25:16'),
(23, 59, '0000-00-00', '2012-07-22', '2012-07-12 20:31:13'),
(24, 59, '0000-00-00', '2012-07-22', '2012-07-12 20:31:45'),
(25, 59, '2012-07-22', '2012-07-24', '2012-07-12 20:33:27'),
(26, 59, '2012-07-24', '2012-07-26', '2012-07-12 21:46:08'),
(27, 60, '2012-08-31', '2012-09-30', '2012-07-13 17:00:54'),
(28, 61, '2012-07-14', '2012-07-20', '2012-07-17 15:51:43'),
(29, 61, '2012-07-20', '2012-07-23', '2012-07-17 19:32:11'),
(30, 66, '2012-07-24', '2012-07-31', '2012-07-17 22:43:07'),
(31, 76, '2012-11-09', '2013-01-01', '2012-12-27 16:09:34'),
(32, 73, '2013-01-18', '2013-09-07', '2013-05-06 18:34:33'),
(33, 248, '0000-00-00', '2013-06-01', '2013-05-06 18:43:49'),
(34, 248, '2013-06-01', '2013-09-30', '2013-05-06 18:44:09'),
(35, 72, '2012-11-30', '2013-05-10', '2013-05-06 18:54:54'),
(36, 1, '2012-06-14', '2013-06-30', '2013-05-24 19:38:55'),
(37, 0, '0000-00-00', '0000-00-00', '2013-11-06 20:48:39'),
(38, 0, '0000-00-00', '0000-00-00', '2013-11-06 20:48:39'),
(39, 0, '0000-00-00', '0000-00-00', '2013-11-06 22:45:37'),
(40, 0, '0000-00-00', '0000-00-00', '2013-11-06 22:45:37'),
(41, 0, '0000-00-00', '0000-00-00', '2013-11-06 22:45:37'),
(42, 0, '0000-00-00', '0000-00-00', '2013-11-06 22:45:37'),
(43, 0, '0000-00-00', '0000-00-00', '2013-11-06 22:45:37'),
(44, 0, '0000-00-00', '0000-00-00', '2013-11-06 22:45:37'),
(45, 0, '0000-00-00', '0000-00-00', '2013-11-06 22:47:54'),
(46, 0, '0000-00-00', '0000-00-00', '2013-11-06 22:47:57'),
(47, 0, '0000-00-00', '0000-00-00', '2013-11-06 23:05:24'),
(48, 0, '0000-00-00', '0000-00-00', '2013-11-06 23:05:24'),
(49, 0, '0000-00-00', '0000-00-00', '2013-11-06 23:05:24'),
(50, 0, '0000-00-00', '0000-00-00', '2013-11-06 23:05:24'),
(51, 0, '0000-00-00', '0000-00-00', '2013-11-06 23:05:24'),
(52, 0, '0000-00-00', '0000-00-00', '2013-11-06 23:05:24'),
(53, 0, '0000-00-00', '0000-00-00', '2013-11-06 23:05:59'),
(54, 0, '0000-00-00', '0000-00-00', '2013-11-06 23:06:00'),
(55, 23170, '2013-12-18', '2013-12-20', '2013-12-11 19:29:00');

-- --------------------------------------------------------

--
-- Table structure for table `forcecalculations`
--

CREATE TABLE IF NOT EXISTS `forcecalculations` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `average` double DEFAULT NULL,
  `min` double DEFAULT NULL,
  `max` double DEFAULT NULL,
  `over_max` int(11) DEFAULT NULL,
  `under_min` int(11) DEFAULT NULL,
  `time` int(11) DEFAULT NULL,
  `force1` double DEFAULT NULL,
  `force2` double DEFAULT NULL,
  `force3` double DEFAULT NULL,
  `force4` double DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=112 ;

--
-- Dumping data for table `forcecalculations`
--

INSERT INTO `forcecalculations` (`id`, `average`, `min`, `max`, `over_max`, `under_min`, `time`, `force1`, `force2`, `force3`, `force4`) VALUES
(1, 10, 11, 12, 13, 14, 15, 1.6, 1.7, 1.8, 1.9),
(2, 20, 21, 22, 23, 24, 25, 2.6, 2.7, 2.8, 2.9),
(3, 121.44583837531, 106.25954198473, 131.90839694656, 1, 0, 574, 20.996583628433, 10.862805449383, 11.467642583315, 32.576617323435),
(4, 121.44583837531, 106.25954198473, 131.90839694656, 1, 0, 574, 13.676050277676, 0.71230942394908, 2.7344340929824, 6.9735572208266),
(5, 121.44583837531, 106.25954198473, 131.90839694656, 1, 0, 574, 20.996583628433, 10.862805449383, 11.467642583315, 32.576617323435),
(6, 121.44583837531, 106.25954198473, 131.90839694656, 1, 0, 574, 13.676050277676, 0.71230942394908, 2.7344340929824, 6.9735572208266),
(7, 121.44583837531, 106.25954198473, 131.90839694656, 1, 0, 574, 20.996583628433, 10.862805449383, 11.467642583315, 32.576617323435),
(8, 121.44583837531, 106.25954198473, 131.90839694656, 1, 0, 574, 13.676050277676, 0.71230942394908, 2.7344340929824, 6.9735572208266),
(9, 90.927164179732, 82.819460726846, 101.82424916574, 1, 0, 561, 4.7102800749582, 8.030479527422, 19.117520764605, 13.833761934387),
(10, 90.927164179732, 82.819460726846, 101.82424916574, 1, 0, 561, 4.5613780840544, 4.4240883347471, 18.677009995905, 26.64548128392),
(11, 104.82589037095, 102.68251273345, 108.96321070234, 1, 0, 554, 13.298965533051, 15.501955833302, 14.108524376398, 15.327160018887),
(12, 104.82589037095, 102.68251273345, 108.96321070234, 1, 0, 554, 9.2263682136187, 7.203592315197, 10.511788605312, 14.821645104233),
(13, 85.071290763795, 81.319027181688, 89.476454293629, 1, 0, 569, 5.9193532456119, 6.5079898866092, 17.076458329907, 14.347379343952),
(14, 85.071290763795, 81.319027181688, 89.476454293629, 1, 0, 569, 7.9214043740581, 9.6736036656162, 7.3171357844627, 31.236675369783),
(15, 74.164657892979, 63.92523364486, 81.964285714286, 1, 0, 556, 8.2943427908188, 4.2259065005139, 14.399164528079, 14.28317389891),
(16, 74.164657892979, 63.92523364486, 81.964285714286, 1, 0, 556, 23.803817587513, 12.630743257474, 10.642808357294, 11.720043079397),
(17, 52.769948600022, 46.485849056604, 61.27427184466, 17, 0, 565, 6.609053838516, 8.8205401792179, 13.691147710958, 9.9681090861396),
(18, 52.769948600022, 46.485849056604, 61.27427184466, 17, 0, 565, 6.1991946181445, 4.9517729424821, 6.5958076524379, 43.164373972104),
(19, 103.85431376108, 92.842105263158, 113.82113821138, 1, 0, 558, 12.173657832928, 8.4894530499318, 8.1843317521937, 14.425188098731),
(20, 103.85431376108, 92.842105263158, 113.82113821138, 1, 0, 558, 21.592149261275, 11.542331087677, 12.014579410678, 11.578309506585),
(21, 80.593521949744, 75.585014409222, 91.712643678161, 1, 0, 568, 13.031416288306, 18.149526029583, 7.0277255388364, 12.799890339315),
(22, 80.593521949744, 75.585014409222, 91.712643678161, 1, 0, 568, 15.030800925314, 20.9663121969, 2.4826993238002, 10.511629357946),
(23, 68.900045647631, 63.715481171548, 76.592592592593, 1, 0, 558, 2.4234823000592, 2.7020794612014, 8.5506373222945, 22.972761367313),
(24, 68.900045647631, 63.715481171548, 76.592592592593, 1, 0, 558, 5.648702132357, 7.4462544984559, 19.71485416487, 30.54122875345),
(25, 166.16962508516, 165.59187129551, 166.73870783305, 1, 0, 566, 95.031033055059, 0.15653236035895, 0.20203895900445, 1.2206427681126),
(26, 166.16962508516, 165.59187129551, 166.73870783305, 1, 0, 566, 0.68599185979277, 0.40394530035497, 1.0433664172022, 1.2564492801153),
(27, 91.751345010461, 86.601398601399, 95.620338983051, 1, 0, 561, 12.190983792266, 8.5256735186419, 8.6590775749226, 23.968070352809),
(28, 91.751345010461, 86.601398601399, 95.620338983051, 1, 0, 561, 17.141912868566, 15.163214570397, 5.8649904311335, 8.486076891264),
(29, 125.52601028987, 117.52066115702, 130.39405204461, 1, 0, 576, 8.6490697371674, 2.7066526295861, 3.1728735259481, 38.435965411042),
(30, 125.52601028987, 117.52066115702, 130.39405204461, 1, 0, 576, 4.98081626707, 4.3538118151532, 13.698605274268, 24.002205339765),
(31, 64.2303, 48, 93.3333, 2, 42, 146, 11.6665, 9.13106, 9.38629, 13.8839),
(32, 81.5232, 66.6667, 112, 42, 2, 146, 13.2234, 10.881, 18.1411, 13.6867),
(33, 25.9928, 53.3333, 72.7273, 0, 4, 22, 9.44056, 8.51463, 8.51463, 13.2414),
(34, 39.4618, 87.2727, 106.667, 4, 0, 22, 13.1572, 15.0932, 17.0293, 15.0091),
(35, 67.6407, 48, 88.8889, 3, 105, 301, 12.3722, 9.31169, 9.74693, 12.7528),
(36, 85.449, 71.1111, 112, 105, 3, 301, 12.0442, 11.5728, 18.8828, 13.3165),
(37, 69.5927, 48, 96, 4, 132, 406, 12.3829, 9.56753, 9.78806, 12.7431),
(38, 86.8605, 64, 112, 132, 4, 406, 11.2261, 13.2755, 18.749, 12.2679),
(39, 94.9139, 28.9933, 133.818, 685, 74, 1574, 0, 0, 0, 0),
(40, 64.0696, 26.1818, 131.007, 74, 685, 1574, 0, 0, 0, 0),
(41, 56.4324, 43.6364, 74.6667, 39, 0, 87, 9.01609, 7.9378, 10.359, 12.5379),
(42, 85.1768, 85.3333, 116.364, 39, 0, 87, 16.1117, 9.08706, 17.9171, 17.0333),
(43, 0, 0, 0, 0, 0, 221, 9.28914, 8.25414, 10.0196, 14.5753),
(44, 0, 0, 0, 0, 0, 221, 15.3445, 8.80417, 17.5355, 16.1778),
(45, 0, 0, 0, 0, 0, 2798, 7.48353, 7.62209, 11.3717, 23.3881),
(46, 0, 0, 0, 0, 0, 2798, 13.4186, 7.82557, 14.6401, 14.2503),
(47, 0, 0, 0, 0, 0, 1591, 24.9244, 17.8783, 16.5593, 14.9046),
(48, 0, 0, 0, 0, 0, 1591, 6.98733, 3.68036, 7.57483, 7.49091),
(49, 0, 0, 0, 0, 0, 1161, 16.4175, 14.5884, 22.6831, 16.1569),
(50, 0, 0, 0, 0, 0, 1161, 8.20705, 4.2115, 8.82562, 8.91003),
(51, 0, 0, 0, 0, 0, 823, 10.5786, 8.14628, 10.0063, 11.337),
(52, 0, 0, 0, 0, 0, 823, 17.8915, 9.0689, 16.7392, 16.2323),
(53, 0, 0, 0, 0, 0, 509, 7.89574, 23.8407, 18.9588, 6.37438),
(54, 0, 0, 0, 0, 0, 509, 5.39453, 9.15388, 22.3072, 6.07477),
(55, 0, 0, 0, 0, 0, 502, 7.78332, 23.7123, 19.0005, 6.64016),
(56, 0, 0, 0, 0, 0, 502, 5.19509, 9.31333, 22.0697, 6.28558),
(57, 0, 0, 0, 0, 0, 518, 7.92517, 24.0068, 19.1417, 6.28138),
(58, 0, 0, 0, 0, 0, 518, 5.10086, 9.04442, 22.2487, 6.25105),
(59, 0, 0, 0, 0, 0, 488, 7.87201, 23.9307, 18.9736, 6.5034),
(60, 0, 0, 0, 0, 0, 488, 5.24142, 9.13756, 22.1566, 6.18483),
(61, 0, 0, 0, 0, 0, 9957, 8.91374, 7.86378, 10.3905, 14.3248),
(62, 0, 0, 0, 0, 0, 9957, 15.4253, 9.37415, 17.1335, 16.5742),
(63, 0, 0, 0, 0, 0, 782, 7.40327, 20.2527, 20.8455, 10.6142),
(64, 0, 0, 0, 0, 0, 782, 11.6604, 23.3784, 5.08468, 0.760811),
(65, 0, 0, 0, 0, 0, 3056, 2.33218, 5.52664, 16.6988, 15.1656),
(66, 0, 0, 0, 0, 0, 3056, 6.26223, 7.48606, 25.9019, 20.6266),
(67, 0, 0, 0, 0, 0, 46, 4.7215, 12.5536, 14.7775, 10.1956),
(68, 0, 0, 0, 0, 0, 46, 14.6761, 9.57527, 10.9669, 22.5336),
(69, 0, 0, 0, 0, 0, 45, 6.05696, 15.3714, 19.3287, 15.0049),
(70, 0, 0, 0, 0, 0, 45, 12.1139, 12.45, 7.23343, 12.4407),
(71, 0, 0, 0, 0, 0, 1150, 7.64901, 25.1855, 18.2286, 6.20696),
(72, 0, 0, 0, 0, 0, 1150, 5.34947, 9.59742, 21.054, 6.729),
(73, 0, 0, 0, 0, 0, 310, 9.18453, 7.72023, 5.88514, 5.57649),
(74, 0, 0, 0, 0, 0, 161, 9.45984, 8.35233, 5.7787, 5.80403),
(75, 0, 0, 0, 0, 0, 161, 14.877, 19.8824, 19.5753, 16.2704),
(76, 26.8367, 17.6471, 36.3636, 120, 0, 261, 9.85487, 7.01084, 5.59532, 5.4449),
(77, 69.3319, 63.6364, 82.3529, 126, 0, 261, 15.3314, 20.5459, 20.3942, 15.8226),
(78, 49.8962, 44.0945, 65.2482, 128, 0, 266, 3.22683, 4.04656, 23.3367, 21.2352),
(79, 46.3444, 34.7518, 55.9055, 128, 0, 266, 6.25643, 4.24288, 21.5947, 16.0607),
(80, 54.0589, 44.0945, 64.3357, 148, 0, 306, 3.52007, 3.78496, 25.9872, 22.593),
(81, 42.6731, 35.6643, 55.9055, 148, 0, 306, 6.1711, 3.92693, 19.1574, 14.8593),
(82, 27.1205, 17.6471, 35, 114, 0, 245, 9.88596, 7.27896, 5.32011, 5.78951),
(83, 68.7979, 65, 82.3529, 118, 0, 245, 15.2903, 20.4814, 20.4501, 15.5037),
(84, 27.1919, 22.2222, 33.3333, 142, 0, 303, 9.91778, 7.36673, 5.26992, 5.5655),
(85, 69.5078, 66.6667, 77.7778, 147, 0, 303, 15.3692, 20.5529, 20.5211, 15.4368),
(86, 26.6544, 17.6471, 33.3333, 127, 0, 277, 9.86171, 6.6985, 5.35926, 5.73321),
(87, 69.7355, 66.6667, 82.3529, 134, 0, 277, 15.4257, 20.6991, 20.6241, 15.5984),
(88, 26.9506, 17.6471, 33.3333, 134, 0, 294, 9.96447, 7.04195, 5.25499, 5.63816),
(89, 69.648, 66.6667, 82.3529, 142, 0, 294, 15.4028, 20.6705, 20.537, 15.4901),
(90, 46.4002, 45.4545, 61.5385, 35, 0, 79, 14.5535, 14.9454, 10.9449, 12.6811),
(91, 40.9415, 38.4615, 54.5455, 35, 0, 79, 14.9613, 14.6003, 8.60829, 8.70517),
(92, 49.0975, 41.6667, 61.5385, 51, 0, 111, 14.3658, 15.1617, 11.6412, 12.79),
(93, 41.8935, 38.4615, 58.3333, 51, 0, 111, 14.4232, 14.6655, 7.90512, 9.04754),
(94, 49.919, 41.6667, 63.6364, 50, 0, 109, 14.6186, 15.0416, 11.2177, 14.0833),
(95, 40.9067, 36.3636, 58.3333, 50, 0, 109, 14.6755, 12.0088, 8.99608, 9.35831),
(96, 50.7691, 45.4545, 61.5385, 82, 0, 173, 14.28, 14.6877, 11.247, 13.6691),
(97, 43.4506, 38.4615, 54.5455, 82, 0, 173, 14.9294, 12.9102, 8.55307, 9.72355),
(98, 50.9227, 41.6667, 61.5385, 71, 0, 151, 14.9966, 15.0196, 11.5579, 12.9603),
(99, 42.4548, 38.4615, 58.3333, 71, 0, 151, 14.563, 13.5063, 8.2739, 9.1225),
(100, 51.5498, 45.4545, 63.6364, 78, 0, 166, 15.0582, 15.0145, 11.0324, 13.7492),
(101, 42.4261, 36.3636, 54.5455, 78, 0, 166, 14.5122, 13.0393, 8.55137, 9.04286),
(102, 50.2868, 42.8571, 63.6364, 73, 0, 155, 14.7054, 14.634, 11.0606, 13.3548),
(103, 43.2616, 36.3636, 57.1429, 73, 0, 155, 14.6147, 13.4489, 9.0521, 9.12948),
(104, 51.6413, 41.6667, 61.5385, 77, 0, 163, 14.928, 15.0514, 11.784, 13.2533),
(105, 42.2237, 38.4615, 58.3333, 77, 0, 163, 13.894, 14.3914, 7.60745, 9.0906),
(106, 50.508, 41.6667, 63.6364, 59, 0, 128, 15.1107, 15.0023, 11.0033, 13.672),
(107, 41.6795, 36.3636, 58.3333, 59, 0, 128, 14.483, 13.1588, 8.12654, 9.44332),
(108, 49.8806, 42.8571, 66.6667, 53, 0, 115, 14.7264, 14.3893, 11.2384, 14.277),
(109, 41.4237, 33.3333, 57.1429, 53, 0, 115, 14.31, 13.7252, 8.02777, 9.30588),
(110, 49.6929, 42.8571, 63.6364, 53, 0, 116, 14.1979, 15.9005, 11.3318, 12.9508),
(111, 41.6864, 36.3636, 57.1429, 53, 0, 116, 14.6393, 12.3838, 9.04298, 9.55292);

-- --------------------------------------------------------

--
-- Table structure for table `forms`
--

CREATE TABLE IF NOT EXISTS `forms` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `aob1` tinyint(1) DEFAULT NULL,
  `aob2` tinyint(1) DEFAULT NULL,
  `aob3` tinyint(1) DEFAULT NULL,
  `aob4` tinyint(1) DEFAULT NULL,
  `aob5` tinyint(1) DEFAULT NULL,
  `aob6` tinyint(1) DEFAULT NULL,
  `insurance` varchar(50) DEFAULT NULL,
  `ctt_prov` varchar(50) DEFAULT NULL,
  `ctt_date` varchar(20) DEFAULT NULL,
  `ctt1` tinyint(1) DEFAULT NULL,
  `pfp_name` varchar(50) DEFAULT NULL,
  `pfp_rep` varchar(50) DEFAULT NULL,
  `pfp_rel` varchar(30) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=21 ;

--
-- Dumping data for table `forms`
--

INSERT INTO `forms` (`id`, `aob1`, `aob2`, `aob3`, `aob4`, `aob5`, `aob6`, `insurance`, `ctt_prov`, `ctt_date`, `ctt1`, `pfp_name`, `pfp_rep`, `pfp_rel`) VALUES
(3, 1, 1, 1, 1, 1, 1, 'MG Insurance Co.', 'Mathew Gray', '10-04-2012', 1, 'Ariel Buck', '', ''),
(4, 1, 1, 1, 1, 1, 1, 'MG Insurance Co.', 'Mathew Gray', '10-04-2012', 1, 'Mathew Gray', '', ''),
(5, 1, 1, 1, 1, 1, 1, 'MG Insurance Co.', 'Bill Hickock', '11-02-2012', 1, 'Amanda Fake', '', ''),
(6, 1, 1, 1, 1, 1, 1, 'MEdHab', 'Dr. Bell', 'November 3, 2012', 1, 'Tim', '', ''),
(7, 1, 1, 1, 1, 1, 1, 'aaa', 'bbb', 'ccc', 1, 'ddd', 'eee', 'fff'),
(8, 1, 1, 1, 1, 1, 1, 'Blank', 'Someone', 'somedate', 1, 'Mathew Gray', '', ''),
(9, 1, 1, 1, 1, 1, 1, 'gggg', 'ddd', 'ddd', 1, 'ddd', 'ddd', 'ddd'),
(10, 1, 1, 1, 1, 1, 1, '3333', '333', '333', 1, '333', '333', '333'),
(11, 1, 1, 1, 1, 1, 1, '333', '33', '33', 1, '33', '33', '33'),
(12, 1, 1, 1, 1, 1, 1, 'Fake', 'Someone', 'somedate', 1, 'Martin, Ashton', '', ''),
(13, 1, 1, 1, 1, 1, 1, '''', 'Dr. Bill Jones', '5/7/2013', 1, 'Jane Doe', '''', ''''),
(14, 1, 1, 1, 1, 1, 1, 'ghjk', 'wert', 'wert', 1, 'sdfg', 'dfgh', 'fghj'),
(15, 1, 1, 1, 1, 1, 1, 'asdf', 'sdfg', 'sdfg', 1, 'dfgh', 'dfgh', 'dfgh'),
(16, 1, 1, 1, 1, 1, 1, 'sdfg', 'sdfg', 'sdfg', 1, 'qer', 'twer', 'rty'),
(17, 1, 1, 1, 1, 1, 1, 'asdf', 'sdfg', 'asdf', 1, 'dfgh', 'dfgh', 'fghj'),
(18, 1, 1, 1, 1, 1, 1, 'sdfg', 'cvbn', 'xcvb', 1, 'qwer', 'wert', 'erty'),
(19, 1, 1, 1, 1, 1, 1, 'vbnm', 'cake', 'cake', 1, 'cake', 'cake', 'cake'),
(20, 1, 1, 1, 1, 1, 1, 'thing', 'thing', 'thing', 1, 'thing', 'thing', 'thing');

-- --------------------------------------------------------

--
-- Table structure for table `gaitcalculations`
--

CREATE TABLE IF NOT EXISTS `gaitcalculations` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `stride_dist` double DEFAULT NULL,
  `swing_time` double DEFAULT NULL,
  `stance_time` double DEFAULT NULL,
  `time` double DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=71 ;

--
-- Dumping data for table `gaitcalculations`
--

INSERT INTO `gaitcalculations` (`id`, `stride_dist`, `swing_time`, `stance_time`, `time`) VALUES
(1, 0, 0, 0, 0),
(2, 0, 0, 0, 0),
(3, 38.6947, 42.96, 25.28, 271.2),
(4, 261.083, 30.36, 21.16, 84),
(5, 14, 2.5, 1.7, 80.6),
(6, 12, 2.2, 1.4, 80.6),
(7, 396.527, 40.52, 24.92, 169.84),
(8, -1015.74, 50.68, 35.2, 137.8),
(9, -49.1778, 41.9, 24.2, 158.72),
(10, -10.6649, 46.7, 30.84, 315.78),
(11, -82.5351, 46.96, 30.48, 231.02),
(12, -38.054, 46.58, 26.46, 334.24),
(13, 0, 0, 0, 0),
(14, 0, 0, 0, 0),
(15, -1.39562, 14.42, 11.7, 26.12),
(16, 2.9795, 14.18, 9.3, 31.94),
(17, 0, 0, 0, 0),
(18, 0, 0, 0, 0),
(19, -34.1711, 21.08, 9.24, 30.32),
(20, 1162.42, 21.08, 10.68, 54.68),
(21, 217.354, 12.92, 6.8, 33.4),
(22, -2.17777, 12.44, 7.12, 36.76),
(23, 349.197, 19.44, 8.8, 74.92),
(24, 0, 0, 0, 0),
(25, 0, 0, 0, 0),
(26, 0, 0, 0, 0),
(27, 331.537, 24.32, 12.4, 219.72),
(28, -308.027, 25.44, 19.12, 137.2),
(29, 39.0586, 27, 25.96, 52.96),
(30, 0, 0, 0, 0),
(31, 372.095, 16.52, 6.28, 22.8),
(32, -309.509, 16.28, 6.88, 23.16),
(33, 699.753, 18.6, 9.4, 28),
(34, 334.023, 18.8, 10, 28.8),
(35, 266.467, 21.28, 16.16, 166.92),
(36, 300, 22.12, 16.32, 199.48),
(37, 277.094, 8.28, 3, 34.16),
(38, 0, 0, 0, 0),
(39, 199.551, 7.04, 2.72, 24.4),
(40, 200, 7.12, 2.8, 24.6),
(41, 256.864, 9.28, 3.64, 38.44),
(42, 200, 7.24, 2.88, 25.2),
(43, 290.316, 7.68, 2.8, 31.36),
(44, 200, 6.12, 2.36, 21.16),
(45, 100, 2.92, 0.8, 3.72),
(46, 145.84, 4.48, 1.16, 5.64),
(47, 50, 3.36, 0.36, 3.72),
(48, 119.953, 3.36, 0.6, 3.96),
(49, 161.98, 4.84, 2, 6.84),
(50, 158.681, 4.8, 1.88, 6.68),
(51, 941.637, 28.52, 11.08, 39.6),
(52, 970.879, 26.76, 10.04, 36.8),
(53, 400, 15.76, 7.92, 23.68),
(54, 400, 14.12, 6.88, 21),
(55, 410.785, 15.16, 6.28, 21.44),
(56, 425.266, 15.4, 6.2, 21.6),
(57, 0, 0, 0, 0),
(58, 0, 0, 0, 0),
(59, 0, 0, 0, 0),
(60, 0, 0, 0, 0),
(61, 0, 0, 0, 0),
(62, 0, 0, 0, 0),
(63, 0, 0, 0, 0),
(64, 0, 0, 0, 0),
(65, 0, 0, 0, 0),
(66, 0, 0, 0, 0),
(67, 0, 0, 0, 0),
(68, 0, 0, 0, 0),
(69, 0, 0, 0, 0),
(70, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `injurycategories`
--

CREATE TABLE IF NOT EXISTS `injurycategories` (
  `id` mediumint(9) NOT NULL AUTO_INCREMENT,
  `description` char(30) NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=5 ;

--
-- Dumping data for table `injurycategories`
--

INSERT INTO `injurycategories` (`id`, `description`) VALUES
(1, 'Hip'),
(2, 'Knee'),
(3, 'Ankle');

-- --------------------------------------------------------

--
-- Table structure for table `injurytypes`
--

CREATE TABLE IF NOT EXISTS `injurytypes` (
  `id` mediumint(9) NOT NULL AUTO_INCREMENT,
  `name` char(30) NOT NULL,
  `category` mediumint(9) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `category` (`category`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=40 ;

--
-- Dumping data for table `injurytypes`
--

INSERT INTO `injurytypes` (`id`, `name`, `category`) VALUES
(1, 'Total Hip Replacement', 1),
(2, 'Partial Hip Replacement', 1),
(3, 'Total Reconstruction', 1),
(4, 'Partial Reconstruction', 1),
(5, 'Revision', 1),
(6, 'Repair', 1),
(7, 'Fractured Hip', 1),
(8, 'Dislocated Hip', 1),
(9, 'Introduction or Removal', 1),
(11, 'Total Knee Replacement', 2),
(12, 'Partial Knee Replacement', 2),
(13, 'Total Reconstruction', 2),
(14, 'Partial Reconstruction', 2),
(15, 'Revision', 2),
(16, 'Repair', 2),
(17, 'Fractured Knee', 2),
(18, 'Dislocated Knee', 2),
(19, 'Arthroscopy', 2),
(20, 'ACL', 2),
(21, 'Introduction or Removal', 2),
(22, 'Amputation', 2),
(23, 'Total Ankle Replacement', 3),
(24, 'Partial Ankle Replacement', 3),
(25, 'Total Reconstruction', 3),
(26, 'Partial Reconstruction', 3),
(27, 'Revision', 3),
(28, 'Repair', 3),
(29, 'Fractured Ankle', 3),
(30, 'Dislocated Ankle', 3),
(31, 'Introduction or Removal', 3),
(32, 'Arthrodesis', 3),
(33, 'Amputation', 3),
(34, 'Hindquarter', 4),
(35, 'Femur', 4),
(36, 'Tibia/Fibula', 4),
(37, 'Ankle', 4),
(38, 'Foot', 4),
(39, 'Toes', 4);

-- --------------------------------------------------------

--
-- Table structure for table `notes`
--

CREATE TABLE IF NOT EXISTS `notes` (
  `ClientID` int(11) DEFAULT NULL,
  `Date` datetime DEFAULT NULL,
  `Subject` varchar(30) DEFAULT NULL,
  `Note` varchar(255) DEFAULT NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `notes`
--

INSERT INTO `notes` (`ClientID`, `Date`, `Subject`, `Note`) VALUES
(1, '2012-02-15 00:00:00', 'This is a SOAP Note', 'SOAP Notes are really cool and useful for doctors!  I''m writing this one to test them on our dashboard!'),
(1, '2012-02-15 00:00:00', 'Exercise Added', 'Today I added another exercise to the patients protocol.  This exercise should help improve flexibility.'),
(1, '2012-02-15 13:19:25', 'Hello World!', 'This is a new note!'),
(1, '2012-02-15 13:19:58', 'More notes!', 'More notes is better than fewer notes!'),
(1, '2012-02-15 13:20:16', 'One Note', 'One note is better than no notes at all!'),
(2, '2012-02-15 13:21:52', 'First Appointment', 'In my first appointment with John Deer I assigned him 3 new exercises and showed him how they are done.'),
(1, '2012-02-15 14:14:58', '349m 29!!', '[{#}3km4 m3;iau4 k32k'),
(1, '2012-02-16 09:55:04', '''(SELECT Subject FROM Notes)''', 'Hello'),
(1, '2012-03-01 14:05:22', 'Added Exercises', 'Today I was in a meeting with whoever and added an exercise.'),
(23, '2012-05-21 15:30:05', 'First Appointment', 'lskdjfkjwekj'),
(23, '2012-05-21 15:31:00', 'Next Visit', 'more notes'),
(27, '2012-05-21 20:10:15', 'First Appointment', 'I had my first appointment with Bruce Lee.'),
(64, '2012-07-17 15:30:43', 'first note', 'making a note for myself'),
(66, '2012-07-17 22:33:19', 'First Meeting', 'I assigned two exercises to the patient.'),
(1, '2013-11-06 20:44:21', '1', '1'),
(0, '2013-11-06 20:44:21', '', ''),
(6, '2013-11-06 20:48:39', '1', '1'),
(7, '2013-11-06 20:48:39', '1', '1'),
(6, '2013-11-06 20:48:39', '1', '1'),
(7, '2013-11-06 20:48:39', '1', '1'),
(0, '2013-11-06 22:09:17', '', ''),
(1, '2013-11-06 22:09:17', '1', '1'),
(6, '2013-11-06 22:44:58', '1', '1'),
(7, '2013-11-06 22:44:58', '1', '1'),
(6, '2013-11-06 22:44:58', '1', '1'),
(7, '2013-11-06 22:44:58', '1', '1'),
(6, '2013-11-06 22:45:36', '1', '1'),
(7, '2013-11-06 22:45:36', '1', '1'),
(6, '2013-11-06 22:45:37', '1', '1'),
(7, '2013-11-06 22:45:37', '1', '1'),
(0, '2013-11-06 22:46:51', '', ''),
(0, '2013-11-06 22:46:51', '1', '1'),
(1, '2013-12-10 20:54:12', 'test1', 'test2');

-- --------------------------------------------------------

--
-- Table structure for table `notifications`
--

CREATE TABLE IF NOT EXISTS `notifications` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `message` varchar(500) DEFAULT NULL,
  `date` date DEFAULT NULL,
  `time` time DEFAULT NULL,
  `new` tinyint(1) DEFAULT NULL,
  `doctor_id` mediumint(9) DEFAULT NULL,
  `type` mediumint(9) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=87 ;

--
-- Dumping data for table `notifications`
--

INSERT INTO `notifications` (`id`, `message`, `date`, `time`, `new`, `doctor_id`, `type`) VALUES
(69, 'This is a warning message', '2012-05-24', '19:04:24', 0, 6, 1),
(70, 'This is a warning message', '2012-05-24', '19:04:24', 0, 6, 2),
(71, 'This is a warning message', '2012-05-24', '19:04:24', 0, 6, 2),
(72, 'This is a warning message', '2012-05-24', '19:04:24', 0, 6, 2),
(73, 'This is a warning message', '2012-05-24', '19:04:25', 0, 6, 2),
(74, 'This is a warning message', '2012-05-24', '19:04:35', 0, 6, 2),
(75, 'This is a warning message', '2012-05-24', '19:04:39', 0, 6, 2),
(76, 'This is a warning message', '2012-05-24', '20:36:32', 0, 6, 0),
(77, 'This is a warning message', '2012-05-24', '20:48:22', 0, 6, 0),
(78, 'New Message', '2012-05-25', '15:58:47', 0, 6, 0),
(79, 'New Message', '2012-05-25', '15:59:22', 0, 6, 0),
(80, 'New Message', '2012-05-25', '15:59:22', 0, 6, 0),
(81, 'New Message', '2012-05-25', '15:59:23', 0, 6, 0),
(82, 'New Message', '2012-05-25', '15:59:23', 0, 6, 0),
(83, 'New Message', '2012-05-25', '15:59:23', 0, 6, 0),
(84, 'New Message', '2012-05-25', '15:59:24', 0, 6, 0),
(85, 'New Message', '2012-05-25', '15:59:24', 0, 6, 0),
(86, 'New Message', '2012-05-25', '15:59:24', 0, 6, 0);

-- --------------------------------------------------------

--
-- Table structure for table `patients`
--

CREATE TABLE IF NOT EXISTS `patients` (
  `user_id` int(11) NOT NULL,
  `provider_id` mediumint(9) DEFAULT NULL,
  `mrn` varchar(32) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `start_date` date DEFAULT NULL,
  `end_date` date DEFAULT NULL,
  `reg_date` date DEFAULT NULL,
  `processed_date` date DEFAULT NULL,
  `weight` mediumint(9) DEFAULT NULL,
  `height` varchar(30) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `pt` varchar(60) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `dr` varchar(60) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `injured_leg` tinyint(1) DEFAULT NULL COMMENT '0 = left, 1 = right',
  `times` int(11) DEFAULT NULL,
  `phone_num` varchar(9) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `status_treatment` tinyint(4) DEFAULT NULL,
  `form_id` int(11) NOT NULL DEFAULT '0',
  `aob_accepted` tinyint(1) DEFAULT NULL,
  `ctt_accepted` tinyint(1) DEFAULT NULL,
  `pfp_accepted` tinyint(1) DEFAULT NULL,
  PRIMARY KEY (`user_id`),
  KEY `doctor_id` (`provider_id`),
  KEY `user_id` (`user_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `patients`
--

INSERT INTO `patients` (`user_id`, `provider_id`, `mrn`, `start_date`, `end_date`, `reg_date`, `processed_date`, `weight`, `height`, `pt`, `dr`, `injured_leg`, `times`, `phone_num`, `status_treatment`, `form_id`, `aob_accepted`, `ctt_accepted`, `pfp_accepted`) VALUES
(62, 59, '123456789', '2014-01-01', '2014-03-14', '2014-01-03', NULL, 200, '72', '', 'Mike Jones', 0, 3, '555555555', NULL, 0, NULL, NULL, NULL);

-- --------------------------------------------------------

--
-- Table structure for table `protocols`
--

CREATE TABLE IF NOT EXISTS `protocols` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `patient_id` mediumint(9) NOT NULL,
  `custom_exercise_id` mediumint(9) NOT NULL,
  `active` smallint(1) NOT NULL,
  `mandatory` smallint(1) DEFAULT NULL,
  `start_date` date DEFAULT NULL,
  `end_date` date DEFAULT NULL,
  PRIMARY KEY (`id`),
  KEY `ClientID` (`patient_id`),
  KEY `CExID` (`custom_exercise_id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=46582 ;

--
-- Dumping data for table `protocols`
--

INSERT INTO `protocols` (`id`, `patient_id`, `custom_exercise_id`, `active`, `mandatory`, `start_date`, `end_date`) VALUES
(1, 22, 27, 0, 0, '2012-05-10', NULL),
(2, 22, 2, 0, 0, '2012-05-10', NULL),
(385, 3, 332, 1, 1, '2012-10-30', NULL),
(384, 3, 331, 1, 0, '2012-10-30', NULL),
(383, 3, 330, 1, 0, '2012-10-30', NULL),
(6, 22, 25, 0, 0, '2012-05-10', NULL),
(7, 22, 24, 0, 0, '2012-05-10', NULL),
(8, 22, 28, 0, 0, '2012-05-10', NULL),
(382, 3, 329, 1, 0, '2012-10-30', NULL),
(10, 5, 26, 1, 0, '2012-05-10', NULL),
(11, 5, 27, 0, 0, '2012-05-10', NULL),
(12, 5, 28, 0, 0, '2012-05-10', NULL),
(13, 5, 29, 0, 0, '2012-05-10', NULL),
(14, 6, 26, 1, 0, '2012-05-10', NULL),
(15, 6, 27, 0, 0, '2012-05-10', NULL),
(16, 6, 28, 1, 0, '2012-05-10', NULL),
(17, 6, 29, 1, 0, '2012-05-10', NULL),
(18, 22, 2, 0, 0, '2012-05-10', NULL),
(19, 6, 2, 1, 0, '2012-05-10', NULL),
(20, 6, 4, 1, 0, '2012-05-10', NULL),
(21, 7, 26, 1, 0, '2012-05-10', NULL),
(22, 7, 27, 1, 0, '2012-05-10', NULL),
(23, 7, 28, 1, 0, '2012-05-10', NULL),
(24, 7, 29, 1, 0, '2012-05-10', NULL),
(25, 7, 2, 1, 0, '2012-05-10', NULL),
(26, 7, 4, 1, 0, '2012-05-10', NULL),
(27, 8, 26, 1, 0, '2012-05-10', NULL),
(28, 8, 27, 1, 0, '2012-05-10', NULL),
(29, 8, 28, 1, 0, '2012-05-10', NULL),
(30, 8, 29, 1, 0, '2012-05-10', NULL),
(31, 8, 2, 1, 0, '2012-05-10', NULL),
(32, 8, 4, 1, 0, '2012-05-10', NULL),
(33, 8, 1, 1, 0, '2012-05-10', NULL),
(34, 9, 26, 1, 0, '2012-05-10', NULL),
(35, 9, 27, 1, 0, '2012-05-10', NULL),
(36, 9, 28, 1, 0, '2012-05-10', NULL),
(37, 9, 29, 1, 0, '2012-05-10', NULL),
(38, 9, 2, 1, 0, '2012-05-10', NULL),
(39, 9, 4, 1, 0, '2012-05-10', NULL),
(40, 9, 1, 1, 0, '2012-05-10', NULL),
(41, 10, 26, 1, 0, '2012-04-18', NULL),
(42, 10, 27, 1, 0, '2012-04-18', NULL),
(43, 10, 28, 1, 0, '2012-04-18', NULL),
(44, 10, 29, 0, 0, '2012-04-18', NULL),
(45, 10, 2, 1, 0, '2012-04-18', NULL),
(46, 10, 4, 1, 0, '2012-04-18', NULL),
(47, 10, 1, 1, 0, '2012-04-18', NULL),
(48, 11, 26, 1, 0, '2012-05-10', NULL),
(49, 11, 27, 1, 0, '2012-05-10', NULL),
(50, 11, 28, 1, 0, '2012-05-10', NULL),
(51, 11, 29, 1, 0, '2012-05-10', NULL),
(52, 11, 2, 1, 0, '2012-05-10', NULL),
(53, 11, 4, 1, 0, '2012-05-10', NULL),
(54, 11, 1, 1, 0, '2012-05-10', NULL),
(55, 12, 26, 1, 0, '2012-05-10', NULL),
(56, 12, 27, 1, 0, '2012-05-10', NULL),
(57, 12, 28, 1, 0, '2012-05-10', NULL),
(58, 12, 29, 1, 0, '2012-05-10', NULL),
(59, 12, 2, 1, 0, '2012-05-10', NULL),
(60, 12, 4, 1, 0, '2012-05-10', NULL),
(61, 12, 1, 1, 0, '2012-05-10', NULL),
(62, 13, 26, 1, 0, '2012-05-10', NULL),
(63, 13, 27, 1, 0, '2012-05-10', NULL),
(64, 13, 28, 1, 0, '2012-05-10', NULL),
(65, 13, 29, 1, 0, '2012-05-10', NULL),
(66, 13, 2, 1, 0, '2012-05-10', NULL),
(67, 13, 4, 1, 0, '2012-05-10', NULL),
(68, 13, 1, 1, 0, '2012-05-10', NULL),
(69, 14, 26, 1, 0, '2012-05-10', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `providers`
--

CREATE TABLE IF NOT EXISTS `providers` (
  `user_id` int(11) NOT NULL,
  `npin` varchar(30) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `business_name` varchar(60) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `business_address` varchar(255) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `phone_num` varchar(9) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `cell_num` varchar(9) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `registration_date` date NOT NULL,
  `processed_date` date DEFAULT NULL,
  PRIMARY KEY (`user_id`),
  KEY `fk_user_id` (`user_id`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `providers`
--

INSERT INTO `providers` (`user_id`, `npin`, `business_name`, `business_address`, `phone_num`, `cell_num`, `registration_date`, `processed_date`) VALUES
(59, '123456', 'MedHab', '26 Amberwood Drive', '317512645', NULL, '0000-00-00', NULL);

-- --------------------------------------------------------

--
-- Table structure for table `romcalculations`
--

CREATE TABLE IF NOT EXISTS `romcalculations` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `average` double DEFAULT NULL,
  `minimum` decimal(6,0) DEFAULT NULL,
  `maximum` double DEFAULT NULL,
  `reps` int(11) DEFAULT NULL,
  `time` int(11) DEFAULT NULL,
  `rep_average` double DEFAULT NULL,
  `rep_min` double DEFAULT NULL,
  `rep_max` double DEFAULT NULL,
  `force1` double DEFAULT NULL,
  `force2` double DEFAULT NULL,
  `force3` double DEFAULT NULL,
  `force4` double DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=734 ;

--
-- Dumping data for table `romcalculations`
--

INSERT INTO `romcalculations` (`id`, `average`, `minimum`, `maximum`, `reps`, `time`, `rep_average`, `rep_min`, `rep_max`, `force1`, `force2`, `force3`, `force4`) VALUES
(1, 16.8, '111', 333, 4, 5, 6, 7, 8, 3.7, 3.9, 13.4, 10.2),
(2, 23.1, '22', 38.6, 7, 8, 9, 1, 9, 23.1, 3.2, 13.4, 29),
(3, 16.8, '111', 333, 4, 5, 6, 7, 8, 3.7, 3.9, 13.4, 10.2),
(4, 23.1, '22', 38.6, 7, 8, 9, 1, 9, 23.1, 4.5, 13.4, 29),
(117, 59.862523021901, '30', 71.270328752098, 10, 113, 6.02, 5.1, 6.5, 18.848012170339, 0, 0, 1.0287978330513),
(118, 62.604043266296, '25', 74.207889721736, 10, 126, 8.03, 7.4, 8.7, 65.830166298943, 0, 0, 0),
(119, 62.900117167756, '26', 74.637660375383, 10, 126, 7.95, 7.4, 8.7, 65.830166298943, 0, 0, 0),
(120, 59.505500697424, '29', 70.978206728635, 10, 113, 6.15, 5.3, 6.7, 18.848012170339, 0, 0, 1.0287978330513),
(160, 18.277405634459, '7', 29.048664281625, 14, 83, 2.75, 0.9, 4.3, 42.77684338467, 1.4796243341301, 1.4796243341301, 1.7883514704511),
(121, 17.170285417224, '6', 23.764641414203, 10, 100, 4.39, 4.2, 4.5, 23.260972600377, 3.5017224931896, 3.5017224931896, 8.7257497453818),
(122, 19.0271821547, '7', 26.473069446154, 10, 100, 4.44, 4.3, 4.6, 36.038179997515, 4.4214592027075, 4.4214592027075, 4.9713735352884),
(123, 16.295376580993, '7', 19.885163334379, 10, 100, 4.35, 4, 4.7, 25.084987522345, 8.498633224904, 8.498633224904, 14.047280227196),
(124, 19.38202006516, '7', 23.234430465564, 10, 100, 4.46, 4.2, 4.9, 20.610796105931, 6.7486907845077, 6.7486907845077, 8.124160931442),
(125, 20.450689731438, '7', 43.323761767921, 11, 99, 3.6636363636364, 0.6, 4.3, 3.6758631425321, 13.408402905844, 13.408402905844, 10.20399262538),
(126, 24.321654057805, '9', 50.424363478125, 10, 100, 4.16, 3.9, 5.1, 23.117289471921, 13.398759615911, 13.398759615911, 29.029613242267),
(127, 25.655575180463, '8', 35.63281815359, 10, 97, 4.27, 3.5, 5, 1.6907446603409, 16.82765555651, 16.82765555651, 12.391556739832);

-- --------------------------------------------------------

--
-- Table structure for table `serial`
--

CREATE TABLE IF NOT EXISTS `serial` (
  `serial_number` bigint(12) NOT NULL,
  `macl` varchar(12) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `macr` varchar(12) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
  `admin_id` mediumint(9) NOT NULL DEFAULT '0' COMMENT 'id of employee that requested the sn be generated',
  `patient_id` mediumint(9) NOT NULL COMMENT 'patient to which the sn is assigned',
  PRIMARY KEY (`serial_number`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `serial`
--

INSERT INTO `serial` (`serial_number`, `macl`, `macr`, `timestamp`, `admin_id`, `patient_id`) VALUES
(100000000000, '0', '0', '2013-12-31 19:41:31', 0, 0),
(100000000001, '0', '0', '2013-12-31 19:41:35', 0, 0),
(100000000002, '0', '0', '2013-12-31 19:41:37', 0, 0),
(100000000003, '0', '0', '2013-12-31 19:41:39', 0, 0),
(100000000004, '0', '0', '2013-12-31 19:41:41', 0, 0),
(100000000005, '0', '0', '2013-12-31 19:41:43', 0, 0),
(100000000006, '0', '0', '2013-12-31 19:41:45', 0, 0),
(100000000007, '0', '0', '2013-12-31 19:41:47', 0, 0),
(100000000008, '0', '0', '2013-12-31 19:41:49', 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `sessions`
--

CREATE TABLE IF NOT EXISTS `sessions` (
  `session_id` varchar(40) COLLATE utf8_bin NOT NULL DEFAULT '0',
  `ip_address` varchar(45) COLLATE utf8_bin NOT NULL DEFAULT '0',
  `user_agent` varchar(120) COLLATE utf8_bin NOT NULL,
  `last_activity` int(10) unsigned NOT NULL DEFAULT '0',
  `user_data` text COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`session_id`),
  KEY `last_activity_idx` (`last_activity`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin;

--
-- Dumping data for table `sessions`
--

INSERT INTO `sessions` (`session_id`, `ip_address`, `user_agent`, `last_activity`, `user_data`) VALUES
('a310ff7d63cf98feebd4a89994490bf9', '127.0.0.1', 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/31.0.1650.63 Safari/537.36', 1388788182, 'a:7:{s:9:"user_data";s:0:"";s:9:"logged_in";b:1;s:7:"user_id";s:2:"59";s:9:"user_type";s:1:"1";s:10:"first_name";s:7:"Matthew";s:9:"last_name";s:8:"Stephens";s:16:"selected_patient";s:2:"62";}');

-- --------------------------------------------------------

--
-- Table structure for table `standard_emails`
--

CREATE TABLE IF NOT EXISTS `standard_emails` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(45) CHARACTER SET latin1 NOT NULL,
  `subject` varchar(128) COLLATE utf8_bin NOT NULL,
  `content` text CHARACTER SET latin1 NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=6 ;

--
-- Dumping data for table `standard_emails`
--

INSERT INTO `standard_emails` (`id`, `name`, `subject`, `content`) VALUES
(1, 'emailD', '', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Ut rutrum, nulla in vestibulum dapibus, diam sem laoreet risus, sed rutrum dui justo eu lorem. Aliquam fermentum viverra lorem, et imperdiet.'),
(2, 'emailE', '', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Curabitur non metus quis mi vulputate adipiscing. Aliquam erat volutpat. Maecenas consectetur. '),
(3, 'emailF', '', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras id metus massa. Ut placerat tellus sit amet risus viverra dignissim. Nunc non est dui, viverra luctus risus. Proin congue bibendum purus, quis dictum neque pellentesque eu. Aliquam non dui et lorem hendrerit viverra in non felis. Donec quis libero orci. Aliquam a massa sit amet lectus facilisis pretium fermentum sed justo. Proin eleifend semper nisi, et vehicula quam varius at. Ut tellus libero, dictum at varius nec, ullamcorper non mauris. Fusce lacinia, lorem nec tempor porta, erat eros faucibus nibh, vel egestas nunc dui sollicitudin nibh. Quisque vitae erat non nulla pharetra laoreet vitae fermentum elit. Ut lacinia auctor urna eu placerat. Pellentesque a nibh a elit lacinia sagittis ut nec neque. Donec et ligula id neque consequat iaculis a ac enim. Nunc ac tellus a mi varius pellentesque at ut lacus. Nam vehicula dictum turpis id porta. Quisque gravida ultrices congue. In fermentum tempus nibh, in rhoncus velit mollis eu. Aenean eget sem risus, id accumsan sem. Mauris volutpat eleifend sem eu blandit. Sed feugiat interdum augue eu laoreet. Morbi sit amet justo quis ligula tincidunt commodo non id ipsum. In sapien dolor, tempus ut mattis eget, vehicula eget arcu. Class aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Aenean placerat malesuada interdum. '),
(4, 'emailG', '', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed sit amet augue vitae arcu bibendum laoreet. Integer blandit imperdiet pretium. \n\nDuis at lorem mi. Curabitur non pretium diam. Vivamus volutpat semper consequat. Sed sit amet justo ipsum. Etiam rutrum odio sed quam fermentum tristique commodo dolor mattis. Ut elementum interdum dolor, non congue mauris eleifend vitae. Fusce elementum bibendum euismod. \n\nPellentesque sit amet nunc ut magna malesuada consequat. Aliquam at imperdiet mauris.  Nunc at arcu nisi. In hac habitasse platea dictumst. \n\nClass aptent taciti sociosqu ad litora torquent per conubia nostra, per inceptos himenaeos. Nullam ornare tincidunt turpis, at aliquam. '),
(5, 'emailH', '', 'Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed sit amet augue vitae arcu bibendum laoreet. Integer blandit imperdiet pretium.');

-- --------------------------------------------------------

--
-- Table structure for table `stepcalculations`
--

CREATE TABLE IF NOT EXISTS `stepcalculations` (
  `step_num` int(11) DEFAULT NULL,
  `gait_id` int(11) DEFAULT NULL,
  `stride_dist` double DEFAULT NULL,
  `swing_time` double DEFAULT NULL,
  `stance_time` double DEFAULT NULL,
  `id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=193 ;

--
-- Dumping data for table `stepcalculations`
--

INSERT INTO `stepcalculations` (`step_num`, `gait_id`, `stride_dist`, `swing_time`, `stance_time`, `id`) VALUES
(1, 3, 12.1624, 13.16, 9.48, 1),
(1, 5, 12.45, 13.3, 8.32, 2),
(2, 5, 11.45, 12.3, 7.32, 3),
(3, 5, 13.45, 13.56, 8.72, 4),
(4, 5, 16.45, 17.56, 10.72, 5),
(1, 6, 12.45, 13.3, 8.32, 6),
(4, 6, 16.45, 17.56, 10.72, 7),
(3, 6, 13.45, 13.56, 8.72, 8),
(2, 6, 11.45, 12.3, 7.32, 9),
(1, 7, 81.0614, 15.16, 10.84, 10),
(2, 7, 2.86302, 2.84, 0.52, 11),
(3, 7, -2.07328, 10.76, 8.92, 12),
(4, 7, 314.675, 11.76, 4.64, 13),
(1, 8, -923.706, 30.52, 21.4, 14);

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE IF NOT EXISTS `users` (
  `id` mediumint(9) NOT NULL AUTO_INCREMENT,
  `type` int(11) NOT NULL,
  `first_name` char(30) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `last_name` char(30) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL,
  `password` varchar(40) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `email` varchar(50) CHARACTER SET utf8 COLLATE utf8_bin DEFAULT NULL,
  `active` tinyint(1) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `id_UNIQUE` (`id`)
) ENGINE=MyISAM  DEFAULT CHARSET=latin1 AUTO_INCREMENT=63 ;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`id`, `type`, `first_name`, `last_name`, `password`, `email`, `active`) VALUES
(59, 1, 'Matthew', 'Stephens', 'i2i4+/gvXJKPAxBFvLaq8zcnuy+JJJ9/', 'mcstephens@gmail.com', 1),
(62, 2, 'Billy', 'Bob', 'bMriH7E3WWIQeSTqml7Y0XoEh6xshSvY', 'billybob@web.com', 1);

-- --------------------------------------------------------

--
-- Table structure for table `user_type`
--

CREATE TABLE IF NOT EXISTS `user_type` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `type` varchar(32) COLLATE utf8_bin NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `type` (`type`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_bin AUTO_INCREMENT=3 ;

--
-- Dumping data for table `user_type`
--

INSERT INTO `user_type` (`id`, `type`) VALUES
(2, 'patient'),
(1, 'provider');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
