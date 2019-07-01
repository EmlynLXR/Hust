#ifndef HEADER_H
#define HEADER_H
#include <string.h>
#include <strings.h>
#include <QList>
#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QTime>
#include <QDate>
#include <QTimer>
#include <QDebug>
#include <QDateTime>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <iostream>
#include <string.h>
#include <QFormLayout>
#include <QUrlQuery>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDesktopServices>
#include <QJsonArray>
#include <QMessageBox>
#include <QGridLayout>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>
#include <QTableWidgetItem>
#define FunInsert 0
#define FunModify 1

#define Purchaser 0//采购人员
#define Reviewer 1//审核人员
#define Seller 2//销售人员
#define Manager 3

#define PageStorage 0
#define PageDelivery 1
#define PageLackOfGoods 2
#define PageInventory 3
#define PageOutOfStock 4
#define PageDepot 5
#define PageGoods 6
#define PageWorker 7
#define PageClient 8
#define PageSupplier 9
#endif // HEADER_H
