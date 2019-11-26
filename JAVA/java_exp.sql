/*
Navicat MySQL Data Transfer

Source Server         : localhost
Source Server Version : 80015
Source Host           : localhost:3306
Source Database       : java_exp

Target Server Type    : MYSQL
Target Server Version : 80015
File Encoding         : 65001

Date: 2019-05-22 18:16:03
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `t_brxx`
-- ----------------------------
DROP TABLE IF EXISTS `t_brxx`;
CREATE TABLE `t_brxx` (
  `BRBH` char(6) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '病人编号，数字',
  `BRMC` char(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '病人名称',
  `DLKL` char(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '登录口令',
  `YCJE` decimal(10,2) NOT NULL COMMENT '病人预存金额',
  `DLRQ` datetime DEFAULT NULL COMMENT '最后一次登录日期及时间',
  PRIMARY KEY (`BRBH`),
  KEY `BRBH` (`BRBH`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of t_brxx
-- ----------------------------
INSERT INTO `t_brxx` VALUES ('000001', '李病', '123', '3.00', '2019-05-22 16:02:02');
INSERT INTO `t_brxx` VALUES ('000002', '张病', '123', '18.00', '2019-04-22 21:01:49');
INSERT INTO `t_brxx` VALUES ('000003', '刘病', '123', '15.00', '2019-04-22 20:33:13');
INSERT INTO `t_brxx` VALUES ('000004', '杨病', '123', '12.00', '2019-04-22 21:01:13');
INSERT INTO `t_brxx` VALUES ('000005', '王病', '123', '4.00', '2019-04-22 21:00:47');
INSERT INTO `t_brxx` VALUES ('000006', '公孙病', '123', '28.00', '2019-04-22 21:00:15');

-- ----------------------------
-- Table structure for `t_ghxx`
-- ----------------------------
DROP TABLE IF EXISTS `t_ghxx`;
CREATE TABLE `t_ghxx` (
  `GHBH` char(6) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `HZBH` char(6) DEFAULT NULL,
  `YSBH` char(6) DEFAULT NULL,
  `BRBH` char(6) DEFAULT NULL,
  `GHRC` int(11) DEFAULT NULL,
  `THBZ` tinyint(4) DEFAULT NULL,
  `GHFY` decimal(8,0) DEFAULT NULL,
  `RQSJ` datetime DEFAULT NULL,
  `KBSJ` datetime DEFAULT NULL,
  PRIMARY KEY (`GHBH`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of t_ghxx
-- ----------------------------
INSERT INTO `t_ghxx` VALUES ('000001', '000001', '000003', '000001', '1', '0', '5', '2019-04-22 19:31:00', null);
INSERT INTO `t_ghxx` VALUES ('000002', '000006', '000006', '000001', '1', '0', '1', '2019-04-22 20:12:05', null);
INSERT INTO `t_ghxx` VALUES ('000003', '000004', '000002', '000001', '1', '0', '1', '2019-04-22 20:13:57', null);
INSERT INTO `t_ghxx` VALUES ('000004', '000005', '000005', '000001', '1', '0', '5', '2019-04-22 20:17:09', null);
INSERT INTO `t_ghxx` VALUES ('000005', '000005', '000005', '000001', '2', '0', '5', '2019-04-22 20:18:52', null);
INSERT INTO `t_ghxx` VALUES ('000006', '000006', '000006', '000001', '2', '0', '1', '2019-04-22 20:21:19', null);
INSERT INTO `t_ghxx` VALUES ('000007', '000006', '000006', '000001', '3', '0', '1', '2019-04-22 20:22:55', null);
INSERT INTO `t_ghxx` VALUES ('000008', '000012', '000012', '000001', '1', '0', '1', '2019-04-22 20:24:27', null);
INSERT INTO `t_ghxx` VALUES ('000009', '000008', '000007', '000001', '1', '0', '1', '2019-04-22 20:25:28', null);
INSERT INTO `t_ghxx` VALUES ('000010', '000012', '000012', '000002', '2', '0', '1', '2019-04-22 20:26:03', null);
INSERT INTO `t_ghxx` VALUES ('000011', '000006', '000006', '000005', '4', '0', '1', '2019-04-22 20:28:23', null);
INSERT INTO `t_ghxx` VALUES ('000012', '000002', '000003', '000004', '1', '0', '1', '2019-04-22 20:30:05', null);
INSERT INTO `t_ghxx` VALUES ('000013', '000002', '000004', '000004', '2', '0', '1', '2019-04-22 20:30:44', null);
INSERT INTO `t_ghxx` VALUES ('000014', '000006', '000005', '000006', '5', '0', '1', '2019-04-22 21:00:23', null);
INSERT INTO `t_ghxx` VALUES ('000015', '000006', '000006', '000006', '6', '0', '1', '2019-04-22 21:00:30', null);
INSERT INTO `t_ghxx` VALUES ('000016', '000006', '000006', '000005', '7', '0', '1', '2019-04-22 21:00:54', null);
INSERT INTO `t_ghxx` VALUES ('000017', '000006', '000005', '000004', '8', '0', '1', '2019-04-22 21:01:19', null);
INSERT INTO `t_ghxx` VALUES ('000018', '000006', '000006', '000004', '9', '0', '1', '2019-04-22 21:01:25', null);
INSERT INTO `t_ghxx` VALUES ('000019', '000006', '000006', '000002', '10', '0', '1', '2019-04-22 21:01:55', null);
INSERT INTO `t_ghxx` VALUES ('000020', '000005', '000005', '000001', '3', '0', '5', '2019-04-22 21:21:20', null);
INSERT INTO `t_ghxx` VALUES ('000021', '000005', '000005', '000001', '4', '0', '5', '2019-05-22 15:46:03', null);

-- ----------------------------
-- Table structure for `t_hzxx`
-- ----------------------------
DROP TABLE IF EXISTS `t_hzxx`;
CREATE TABLE `t_hzxx` (
  `HZBH` char(6) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '号种编号，数字，第1索引',
  `HZMC` char(12) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '号种名称',
  `PYZS` char(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '号种名称的拼音字首',
  `KSBH` char(6) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '号种所属科室，第2索引',
  `SFZJ` tinyint(4) NOT NULL COMMENT '是否专家号，即号种类别',
  `GHRS` int(11) NOT NULL COMMENT '每日限定的挂号人数',
  `GHFY` decimal(8,2) NOT NULL COMMENT '挂号费',
  PRIMARY KEY (`HZBH`),
  KEY `HZBH` (`HZBH`) USING BTREE,
  KEY `KSBH` (`KSBH`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of t_hzxx
-- ----------------------------
INSERT INTO `t_hzxx` VALUES ('000001', '外科专家号', 'WKZJH', '000002', '1', '10', '5.00');
INSERT INTO `t_hzxx` VALUES ('000002', '外科普通号', 'WKPTH', '000002', '0', '20', '1.00');
INSERT INTO `t_hzxx` VALUES ('000003', '内科专家号', 'NKZJH', '000001', '1', '10', '5.00');
INSERT INTO `t_hzxx` VALUES ('000004', '内科普通号', 'NKPTH', '000001', '0', '30', '1.00');
INSERT INTO `t_hzxx` VALUES ('000005', '儿科专家号', 'EKZJH', '000003', '1', '10', '5.00');
INSERT INTO `t_hzxx` VALUES ('000006', '儿科普通号', 'EKPTH', '000003', '0', '10', '1.00');
INSERT INTO `t_hzxx` VALUES ('000007', '妇科专家号', 'FKZJH', '000004', '1', '10', '5.00');
INSERT INTO `t_hzxx` VALUES ('000008', '妇科普通号', 'FKPTH', '000004', '0', '20', '1.00');
INSERT INTO `t_hzxx` VALUES ('000009', '眼科专家号', 'YKZJH', '000005', '1', '10', '5.00');
INSERT INTO `t_hzxx` VALUES ('000010', '眼科普通号', 'YKPTH', '000005', '0', '20', '1.00');
INSERT INTO `t_hzxx` VALUES ('000011', '皮肤科专家号', 'PFKZJH', '000006', '1', '10', '5.00');
INSERT INTO `t_hzxx` VALUES ('000012', '皮肤科普通号', 'PFKPTH', '000006', '0', '30', '1.00');

-- ----------------------------
-- Table structure for `t_ksxx`
-- ----------------------------
DROP TABLE IF EXISTS `t_ksxx`;
CREATE TABLE `t_ksxx` (
  `KSBH` char(6) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '科室编号，数字',
  `KSMC` char(10) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '科室名称',
  `PYZS` char(8) CHARACTER SET utf8 COLLATE utf8_general_ci NOT NULL COMMENT '科室名称的拼音字首',
  PRIMARY KEY (`KSBH`),
  KEY `KSBH` (`KSBH`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of t_ksxx
-- ----------------------------
INSERT INTO `t_ksxx` VALUES ('000001', '内科', 'NK');
INSERT INTO `t_ksxx` VALUES ('000002', '外科', 'WK');
INSERT INTO `t_ksxx` VALUES ('000003', '儿科', 'EK');
INSERT INTO `t_ksxx` VALUES ('000004', '妇科', 'FK');
INSERT INTO `t_ksxx` VALUES ('000005', '眼科', 'YK');
INSERT INTO `t_ksxx` VALUES ('000006', '皮肤科', 'PFK');

-- ----------------------------
-- Table structure for `t_ksys`
-- ----------------------------
DROP TABLE IF EXISTS `t_ksys`;
CREATE TABLE `t_ksys` (
  `YSBH` char(6) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '医生编号，数字，第1索引',
  `KSBH` char(6) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '所属科室编号，第2索引',
  `YSMC` char(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '医生名称',
  `PYZS` char(4) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '医生名称的拼音字首',
  `DLKL` char(8) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL COMMENT '登录口令',
  `SFZJ` tinyint(4) NOT NULL COMMENT '是否专家',
  `DLRQ` datetime DEFAULT NULL COMMENT '最后一次登录日期及时间',
  PRIMARY KEY (`YSBH`),
  KEY `YSBH` (`YSBH`) USING BTREE,
  KEY `KSBH` (`KSBH`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;

-- ----------------------------
-- Records of t_ksys
-- ----------------------------
INSERT INTO `t_ksys` VALUES ('000001', '000001', '冯一', 'FY', '456', '1', '2019-05-21 22:04:35');
INSERT INTO `t_ksys` VALUES ('000002', '000001', '陈', 'C', '456', '0', '2019-04-05 14:55:46');
INSERT INTO `t_ksys` VALUES ('000003', '000002', '黄', 'H', '456', '1', '2019-04-22 21:11:23');
INSERT INTO `t_ksys` VALUES ('000004', '000002', '周', 'Z', '456', '0', '2019-04-05 14:57:07');
INSERT INTO `t_ksys` VALUES ('000005', '000003', '吴', 'Q', '456', '1', '2019-04-22 21:22:46');
INSERT INTO `t_ksys` VALUES ('000006', '000003', '徐', 'X', '456', '0', '2019-05-22 16:02:33');
INSERT INTO `t_ksys` VALUES ('000007', '000004', '郑一', 'ZY', '456', '1', '2019-04-05 14:58:11');
INSERT INTO `t_ksys` VALUES ('000008', '000004', '马', 'M', '456', '0', '2019-04-05 14:58:31');
INSERT INTO `t_ksys` VALUES ('000009', '000005', '朱一', 'ZY', '456', '1', '2019-04-05 14:58:53');
INSERT INTO `t_ksys` VALUES ('000010', '000005', '胡一', 'HY', '456', '0', '2019-04-05 14:59:17');
INSERT INTO `t_ksys` VALUES ('000011', '000006', '郭', 'G', '456', '1', '2019-04-05 14:59:36');
INSERT INTO `t_ksys` VALUES ('000012', '000006', '顾一', 'GY', '456', '0', '2019-04-05 14:59:52');
