/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 80015
Source Host           : localhost:3306
Source Database       : depot

Target Server Type    : MYSQL
Target Server Version : 80015
File Encoding         : 65001

Date: 2019-06-10 19:50:02
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `client`
-- ----------------------------
DROP TABLE IF EXISTS `client`;
CREATE TABLE `client` (
  `ID` int(255) NOT NULL AUTO_INCREMENT,
  `Name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `City` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Tel` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=8 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of client
-- ----------------------------
INSERT INTO `client` VALUES ('1', '客户1', '武汉', '123');
INSERT INTO `client` VALUES ('2', '客户2', '武汉', '56');
INSERT INTO `client` VALUES ('3', '客户3', '武汉', '89');

-- ----------------------------
-- Table structure for `delivery`
-- ----------------------------
DROP TABLE IF EXISTS `delivery`;
CREATE TABLE `delivery` (
  `ID` int(255) NOT NULL AUTO_INCREMENT,
  `DepotID` int(255) NOT NULL,
  `GoodsID` int(255) NOT NULL,
  `Price` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Count` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `ClientID` int(255) NOT NULL,
  `Date` datetime NOT NULL,
  `SellerID` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Status` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `ReviewID` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  PRIMARY KEY (`ID`),
  KEY `delivery_ibfk_1` (`DepotID`),
  KEY `delivery_ibfk_2` (`GoodsID`),
  KEY `delivery_ibfk_4` (`SellerID`),
  KEY `delivery_ibfk_5` (`ReviewID`),
  KEY `ClientID` (`ClientID`),
  CONSTRAINT `delivery_ibfk_1` FOREIGN KEY (`DepotID`) REFERENCES `depot` (`ID`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `delivery_ibfk_2` FOREIGN KEY (`GoodsID`) REFERENCES `goods` (`ID`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `delivery_ibfk_4` FOREIGN KEY (`SellerID`) REFERENCES `worker` (`ID`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `delivery_ibfk_5` FOREIGN KEY (`ReviewID`) REFERENCES `worker` (`ID`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `delivery_ibfk_6` FOREIGN KEY (`ClientID`) REFERENCES `client` (`ID`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=34 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of delivery
-- ----------------------------
INSERT INTO `delivery` VALUES ('1', '1', '2', '5', '800', '1', '2019-05-29 16:27:14', '6', '1', '11');
INSERT INTO `delivery` VALUES ('5', '1', '1', '20.000000', '2.000000', '2', '2019-05-31 14:19:51', '6', '1', '13');
INSERT INTO `delivery` VALUES ('7', '1', '2', '20.000000', '20.000000', '1', '2019-06-02 00:02:34', '6', '1', '11');
INSERT INTO `delivery` VALUES ('18', '1', '1', '1.000000', '600.000000', '2', '2019-06-02 00:23:48', '6', '1', '11');
INSERT INTO `delivery` VALUES ('19', '1', '1', '1.000000', '200', '2', '2019-06-02 00:26:44', '6', '1', '15');
INSERT INTO `delivery` VALUES ('20', '1', '1', '1.000000', '200.000000', '1', '2019-06-02 00:49:37', '6', '1', '14');
INSERT INTO `delivery` VALUES ('21', '1', '1', '1.000000', '20.000000', '1', '2019-06-02 00:52:42', '6', '1', '14');
INSERT INTO `delivery` VALUES ('23', '1', '1', '44.000000', '1.000000', '1', '2019-06-02 20:24:12', '6', '1', '12');
INSERT INTO `delivery` VALUES ('24', '1', '1', '1.000000', '20', '1', '2019-06-02 20:24:26', '7', '1', '12');
INSERT INTO `delivery` VALUES ('25', '1', '1', '1.000000', '200.000000', '1', '2019-06-03 09:34:50', '7', '1', '15');
INSERT INTO `delivery` VALUES ('26', '1', '1', '1.000000', '20.000000', '1', '2019-06-03 09:35:04', '7', '1', '15');
INSERT INTO `delivery` VALUES ('27', '4', '1', '1.000000', '20.000000', '1', '2019-06-03 09:34:00', '6', '0', null);
INSERT INTO `delivery` VALUES ('29', '1', '1', '1.000000', '100.000000', '1', '2019-06-03 09:42:38', '6', '1', '15');
INSERT INTO `delivery` VALUES ('30', '1', '1', '5.000000', '200.000000', '1', '2019-06-03 09:58:25', '6', '1', '15');
INSERT INTO `delivery` VALUES ('31', '1', '1', '10.000000', '20.000000', '1', '2019-06-10 17:37:28', '6', '1', '15');
INSERT INTO `delivery` VALUES ('32', '1', '1', '5.000000', '200.000000', '1', '2019-06-10 17:41:09', '6', '1', '15');
INSERT INTO `delivery` VALUES ('33', '1', '1', '10.000000', '150.000000', '1', '2019-06-10 17:44:53', '6', '1', '15');

-- ----------------------------
-- Table structure for `depot`
-- ----------------------------
DROP TABLE IF EXISTS `depot`;
CREATE TABLE `depot` (
  `ID` int(255) NOT NULL AUTO_INCREMENT,
  `Name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `City` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Tel` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`ID`),
  KEY `ID` (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=22 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of depot
-- ----------------------------
INSERT INTO `depot` VALUES ('1', '武汉仓库1', '武汉', '123');
INSERT INTO `depot` VALUES ('2', '武汉仓库2', '武汉', '1123');
INSERT INTO `depot` VALUES ('3', '襄阳仓库3', '襄阳', '3');
INSERT INTO `depot` VALUES ('4', '襄阳仓库1', '襄阳', '123');

-- ----------------------------
-- Table structure for `goods`
-- ----------------------------
DROP TABLE IF EXISTS `goods`;
CREATE TABLE `goods` (
  `ID` int(255) NOT NULL AUTO_INCREMENT,
  `Name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Introduction` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL,
  `MinInventory` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `ID` (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=36 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of goods
-- ----------------------------
INSERT INTO `goods` VALUES ('1', '矿泉水', '农夫山泉', '500');
INSERT INTO `goods` VALUES ('2', '矿泉水', '百岁山', '500');
INSERT INTO `goods` VALUES ('3', '新华字典', '字典', '500');
INSERT INTO `goods` VALUES ('4', '日程本', '', '1000');
INSERT INTO `goods` VALUES ('5', '便利贴', '晨光', '1000');
INSERT INTO `goods` VALUES ('6', '圆珠笔', '晨光', '1000');
INSERT INTO `goods` VALUES ('7', '中性笔', 'MUJI', '500');
INSERT INTO `goods` VALUES ('8', '中性笔', '晨光', '200');

-- ----------------------------
-- Table structure for `inventory`
-- ----------------------------
DROP TABLE IF EXISTS `inventory`;
CREATE TABLE `inventory` (
  `GoodsID` int(255) NOT NULL,
  `Inventory` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `DepotID` int(255) NOT NULL,
  PRIMARY KEY (`GoodsID`,`DepotID`),
  KEY `GoodsID` (`GoodsID`),
  KEY `inventory_ibfk_2` (`DepotID`),
  CONSTRAINT `inventory_ibfk_1` FOREIGN KEY (`GoodsID`) REFERENCES `goods` (`ID`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `inventory_ibfk_2` FOREIGN KEY (`DepotID`) REFERENCES `depot` (`ID`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of inventory
-- ----------------------------
INSERT INTO `inventory` VALUES ('1', '100', '1');
INSERT INTO `inventory` VALUES ('1', '1.000000', '4');
INSERT INTO `inventory` VALUES ('2', '1', '1');
INSERT INTO `inventory` VALUES ('2', '100.000000', '4');
INSERT INTO `inventory` VALUES ('3', '9', '3');

-- ----------------------------
-- Table structure for `lackofgoods`
-- ----------------------------
DROP TABLE IF EXISTS `lackofgoods`;
CREATE TABLE `lackofgoods` (
  `ID` int(11) NOT NULL,
  PRIMARY KEY (`ID`),
  CONSTRAINT `lackofgoods_ibfk_1` FOREIGN KEY (`ID`) REFERENCES `delivery` (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of lackofgoods
-- ----------------------------

-- ----------------------------
-- Table structure for `storage`
-- ----------------------------
DROP TABLE IF EXISTS `storage`;
CREATE TABLE `storage` (
  `ID` int(255) NOT NULL AUTO_INCREMENT,
  `DepotID` int(255) NOT NULL,
  `GoodsID` int(255) NOT NULL,
  `Price` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Count` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `SupplierID` int(255) NOT NULL,
  `Date` datetime NOT NULL,
  `PurchaseID` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Status` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `ReviewID` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT '',
  PRIMARY KEY (`ID`),
  KEY `DepotID` (`DepotID`),
  KEY `GoodsID` (`GoodsID`),
  KEY `PurchaseID` (`PurchaseID`),
  KEY `storage_ibfk_6` (`SupplierID`),
  KEY `ReviewID` (`ReviewID`),
  CONSTRAINT `storage_ibfk_1` FOREIGN KEY (`DepotID`) REFERENCES `depot` (`ID`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `storage_ibfk_2` FOREIGN KEY (`GoodsID`) REFERENCES `goods` (`ID`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `storage_ibfk_4` FOREIGN KEY (`PurchaseID`) REFERENCES `worker` (`ID`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `storage_ibfk_6` FOREIGN KEY (`SupplierID`) REFERENCES `supplier` (`ID`) ON DELETE RESTRICT ON UPDATE CASCADE,
  CONSTRAINT `storage_ibfk_7` FOREIGN KEY (`ReviewID`) REFERENCES `worker` (`ID`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=48 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of storage
-- ----------------------------
INSERT INTO `storage` VALUES ('1', '1', '1', '2', '500', '1', '2019-05-31 14:06:47', '1', '1', '11');
INSERT INTO `storage` VALUES ('11', '1', '2', '1', '20', '2', '2019-05-31 14:03:55', '1', '1', '11');
INSERT INTO `storage` VALUES ('14', '1', '2', '1', '1', '1', '2019-05-31 14:06:29', '1', '1', '11');
INSERT INTO `storage` VALUES ('25', '4', '1', '1.000000', '1.000000', '3', '2019-05-31 14:17:44', '1', '1', '11');
INSERT INTO `storage` VALUES ('29', '3', '3', '3.000000', '3.000000', '3', '2019-06-02 20:39:39', '1', '1', '13');
INSERT INTO `storage` VALUES ('30', '1', '1', '1.000000', '20', '1', '2019-06-02 20:24:53', '1', '1', '12');
INSERT INTO `storage` VALUES ('31', '1', '1', '1.000000', '300', '1', '2019-06-02 20:35:43', '1', '1', '15');
INSERT INTO `storage` VALUES ('32', '1', '1', '1.000000', '200', '1', '2019-06-02 20:36:38', '1', '1', '15');
INSERT INTO `storage` VALUES ('39', '1', '1', '1.000000', '20.000000', '1', '2019-06-03 09:42:51', '1', '1', '15');
INSERT INTO `storage` VALUES ('40', '1', '1', '1.000000', '300.000000', '1', '2019-06-03 09:43:56', '1', '1', '13');
INSERT INTO `storage` VALUES ('41', '1', '1', '2.000000', '50.000000', '3', '2019-06-03 09:57:45', '1', '1', '15');
INSERT INTO `storage` VALUES ('42', '1', '1', '1.000000', '200.000000', '1', '2019-06-03 09:59:40', '1', '1', '12');
INSERT INTO `storage` VALUES ('44', '4', '2', '3.000000', '100.000000', '2', '2019-06-10 18:02:50', '2', '1', '15');
INSERT INTO `storage` VALUES ('45', '1', '1', '1.000000', '10.000000', '1', '2019-06-10 17:36:29', '1', '1', '15');
INSERT INTO `storage` VALUES ('46', '1', '1', '1.000000', '10.000000', '1', '2019-06-10 17:47:50', '1', '1', '15');
INSERT INTO `storage` VALUES ('47', '1', '1', '0.500000', '300.000000', '1', '2019-06-10 17:58:31', '1', '1', '15');

-- ----------------------------
-- Table structure for `supplier`
-- ----------------------------
DROP TABLE IF EXISTS `supplier`;
CREATE TABLE `supplier` (
  `ID` int(11) NOT NULL AUTO_INCREMENT,
  `Name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `City` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Tel` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`ID`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of supplier
-- ----------------------------
INSERT INTO `supplier` VALUES ('1', '供应商1', '武汉', '12');
INSERT INTO `supplier` VALUES ('2', '供应商2', '武汉', '45');
INSERT INTO `supplier` VALUES ('3', '供应商3', '武汉', '89');

-- ----------------------------
-- Table structure for `worker`
-- ----------------------------
DROP TABLE IF EXISTS `worker`;
CREATE TABLE `worker` (
  `ID` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `PWD` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  `Sex` varchar(255) DEFAULT NULL,
  `Age` int(255) DEFAULT NULL,
  `Tel` varchar(255) DEFAULT NULL,
  `WorkerType` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL,
  PRIMARY KEY (`ID`),
  KEY `ID` (`ID`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of worker
-- ----------------------------
INSERT INTO `worker` VALUES ('1', '123', '采购人员1', '男', '40', '123456789', '0');
INSERT INTO `worker` VALUES ('10', '456', '销售人员5', '女', '34', '123456789', '2');
INSERT INTO `worker` VALUES ('11', '789', '审核人员1', '男', '32', '123456789', '1');
INSERT INTO `worker` VALUES ('12', '789', '审核人员2', '女', '31', '123456789', '1');
INSERT INTO `worker` VALUES ('13', '789', '审核人员3', '男', '30', '123456789', '1');
INSERT INTO `worker` VALUES ('14', '789', '审核人员4', '女', '35', '123456789', '1');
INSERT INTO `worker` VALUES ('15', '789', '审核人员5', '男', '37', '123456789', '1');
INSERT INTO `worker` VALUES ('16', '123', '管理人员1', '男', '20', '123456789', '3');
INSERT INTO `worker` VALUES ('2', '123', '采购人员2', '女', '30', '123456789', '0');
INSERT INTO `worker` VALUES ('3', '123', '采购人员3', '男', '32', '123456789', '0');
INSERT INTO `worker` VALUES ('4', '123', '采购人员4', '女', '35', '123456789', '0');
INSERT INTO `worker` VALUES ('5', '123', '采购人员5', '男', '42', '123456789', '0');
INSERT INTO `worker` VALUES ('6', '456', '销售人员1', '女', '28', '123456789', '2');
INSERT INTO `worker` VALUES ('7', '456', '销售人员2', '男', '29', '123456789', '2');
INSERT INTO `worker` VALUES ('8', '456', '销售人员3', '女', '26', '123456789', '2');
INSERT INTO `worker` VALUES ('9', '456', '销售人员4', '男', '30', '123456789', '2');

-- ----------------------------
-- View structure for `outofstock`
-- ----------------------------
DROP VIEW IF EXISTS `outofstock`;
CREATE ALGORITHM=UNDEFINED DEFINER=`root`@`localhost` SQL SECURITY DEFINER VIEW `outofstock` AS select `inventory`.`GoodsID` AS `GoodsID`,`inventory`.`Inventory` AS `Inventory`,`inventory`.`DepotID` AS `DepotID`,`goods`.`Name` AS `GoodsName`,`depot`.`Name` AS `DepotName`,`goods`.`MinInventory` AS `MinInventory`,`goods`.`Introduction` AS `Detail` from ((`goods` join `inventory`) join `depot`) where ((`goods`.`ID` = `inventory`.`GoodsID`) and (`inventory`.`Inventory` <= `goods`.`MinInventory`) and (`inventory`.`DepotID` = `depot`.`ID`)) ;
