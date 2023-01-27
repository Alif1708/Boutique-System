-- phpMyAdmin SQL Dump
-- version 5.0.3
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Sep 12, 2021 at 11:07 PM
-- Server version: 10.4.14-MariaDB
-- PHP Version: 7.4.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `alyphcollection`
--

-- --------------------------------------------------------

--
-- Table structure for table `authorizedstaff`
--

CREATE TABLE `authorizedstaff` (
  `STAFF_ID` varchar(15) NOT NULL,
  `STAFF_PASSWORD` varchar(15) NOT NULL,
  `STAFF_NAME` varchar(30) NOT NULL,
  `STAFF_PHONE` char(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `authorizedstaff`
--

INSERT INTO `authorizedstaff` (`STAFF_ID`, `STAFF_PASSWORD`, `STAFF_NAME`, `STAFF_PHONE`) VALUES
('afini94', 'afini94', 'Nur Afini', '0115236589'),
('Alef123', 'Alef1234', 'Alef Ismael', '09876543321'),
('alyph00', 'alyph00', 'Alyph Ismail', '0117856246'),
('hilmi96', 'hilmi96', 'Hilmi Khair', '0177512468'),
('staff', 'staff', '', ''),
('Zaf1', 'Zaf2', 'Zafi', '0987654'),
('zaini01', 'zaini01', 'Zaini Johar', '0117856465');

-- --------------------------------------------------------

--
-- Table structure for table `buy`
--

CREATE TABLE `buy` (
  `BUY_ID` int(11) NOT NULL,
  `GOODS_ID` int(11) NOT NULL,
  `BUY_QUANTITY` int(11) NOT NULL,
  `BUY_TOTALPRICE` double NOT NULL,
  `RECEIPT_NO` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `goods`
--

CREATE TABLE `goods` (
  `GOODS_ID` int(11) NOT NULL,
  `GOODS_NAME` varchar(30) CHARACTER SET utf8mb4 NOT NULL,
  `GOODS_PRICE` double NOT NULL,
  `GOODS_STOCK` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_bin;

--
-- Dumping data for table `goods`
--

INSERT INTO `goods` (`GOODS_ID`, `GOODS_NAME`, `GOODS_PRICE`, `GOODS_STOCK`) VALUES
(1000, 'Baju Kurung', 90, 58),
(1001, 'Baju Kebaya', 85, 40),
(1002, 'Serkup Kepala', 10, 20),
(1003, 'Jubah Lelaki', 110, 28),
(1004, 'Jubah Perempuan', 85, 20),
(1005, 'Tudung Shawl', 20, 22),
(1006, 'Tudung Bawal', 15, 30),
(1007, 'Kurta Lelaki', 65, 20),
(1008, 'Kopiah Lelaki', 10, 28),
(1009, 'Sejadah Lipat', 55, 23),
(1010, 'Minyak Attar', 10, 20),
(1012, 'Kerongsang', 35, 20),
(1013, 'Tasbih Digital', 10, 10),
(1015, 'Baju Kebarong', 85, 10),
(1016, 'Seluar Haji', 15, 10),
(1017, 'Baju Melayu', 100, 20),
(1026, 'Baju Haji', 65, 50);

-- --------------------------------------------------------

--
-- Table structure for table `salerecord`
--

CREATE TABLE `salerecord` (
  `SALE_ID` int(11) NOT NULL,
  `BUY_ID` int(11) NOT NULL,
  `GOODS_ID` int(11) NOT NULL,
  `BUY_QUANTITY` int(11) NOT NULL,
  `BUY_TOTALPRICE` double NOT NULL,
  `DATESOLD` datetime NOT NULL DEFAULT current_timestamp(),
  `RECEIPT_NO` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `salerecord`
--

INSERT INTO `salerecord` (`SALE_ID`, `BUY_ID`, `GOODS_ID`, `BUY_QUANTITY`, `BUY_TOTALPRICE`, `DATESOLD`, `RECEIPT_NO`) VALUES
(129, 2108, 1000, 2, 20, '2021-09-12 18:33:05', 20141),
(130, 2109, 1005, 5, 100, '2021-09-12 21:11:43', 18513),
(131, 2110, 1003, 7, 770, '2021-09-13 00:16:27', 21748),
(132, 2111, 1003, 2, 220, '2021-09-13 03:22:07', 24826);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `authorizedstaff`
--
ALTER TABLE `authorizedstaff`
  ADD PRIMARY KEY (`STAFF_ID`),
  ADD UNIQUE KEY `AUTHORIZEDSTAFF_PHONE_UQ` (`STAFF_PHONE`) USING BTREE;

--
-- Indexes for table `buy`
--
ALTER TABLE `buy`
  ADD PRIMARY KEY (`BUY_ID`);

--
-- Indexes for table `goods`
--
ALTER TABLE `goods`
  ADD PRIMARY KEY (`GOODS_ID`);

--
-- Indexes for table `salerecord`
--
ALTER TABLE `salerecord`
  ADD PRIMARY KEY (`SALE_ID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `buy`
--
ALTER TABLE `buy`
  MODIFY `BUY_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2112;

--
-- AUTO_INCREMENT for table `goods`
--
ALTER TABLE `goods`
  MODIFY `GOODS_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=1028;

--
-- AUTO_INCREMENT for table `salerecord`
--
ALTER TABLE `salerecord`
  MODIFY `SALE_ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=133;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
