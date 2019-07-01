#include "worker.h"
#include "ui_worker.h"
extern Control *CONTROL;
#define SearchMax 100
#define SearchByDepotID 0
#define SearchByDepotName 1
#define SearchByClientID 2
#define SearchByClientName 3
#define SearchBySupplierID 4
#define SearchBySupplierName 5
#define SearchByGoodsID 6
#define SearchByGoodsName 7
#define SearchByStatus 8
#define SearchByWorkerID 9
#define SearchByWorkerName 10
#define SearchByWorkerSex 11
#define SearchByWorkerAge 12
#define SearchByWorkerType 13

Worker::Worker(QWidget *parent) :
    QDialog (parent),
    ui(new Ui::Worker)
{
    ui->setupUi(this);

    ui->WelcomeText->setText("Welcome staff of " + QString::fromStdString(CONTROL->Name) + "!");
    ui->WelcomeText->adjustSize();

    ui->StartTime->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->EndTime->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
    ui->StartTime->setCalendarPopup(true);
    ui->EndTime->setCalendarPopup(true);
    ui->StartTime->setDateTime(QDateTime::currentDateTime().addDays(-7));
    ui->EndTime->setDateTime(QDateTime::currentDateTime().addDays(+7));

    ui->Storage->setColumnCount(15);
    ui->Storage->setHorizontalHeaderLabels(QStringList() << "ID" << "DepotID" << "DepotName" << "GoodsID" << "GoodsName"
                                           << "Detail" << "Price" << "Count" << " StorageDate"
                                           << "SupplierID" << "SupplierName"  << "PurchaseID" << "PurchaseName" << "ReviewID" << "StorageStatus");
    ui->Storage->verticalHeader()->setVisible(false); // 隐藏水平header


    ui->Delivery->setColumnCount(15);
    ui->Delivery->setHorizontalHeaderLabels(QStringList() << "ID" << "DepotID" << "DepotName" << "GoodsID" << "GoodsName"
                                            << "Detail" << "Price" << "Count" << " DeliveryDate"
                                            << "ClientID" << "ClientName" << "SellerID"  << "SellerName" << "ReviewID" << "DeliveryStatus");
    ui->Delivery->verticalHeader()->setVisible(false); // 隐藏水平header

    ui->LackOfGoods->setColumnCount(15);
    ui->LackOfGoods->setHorizontalHeaderLabels(QStringList() << "ID" << "DepotID" << "DepotName" << "GoodsID" << "GoodsName"
                                               << "Detail" << "Price" << "Count" << " DeliveryDate"
                                               << "ClientID" << "ClientName" << "SellerID"  << "SellerName" << "ReviewID" << "DeliveryStatus");
    ui->LackOfGoods->verticalHeader()->setVisible(false); // 隐藏水平header

    ui->Inventory->setColumnCount(6);
    ui->Inventory->setHorizontalHeaderLabels(QStringList()<< "DepotID" << "DepotName"
                                             << "GoodsID" << "GoodsName" << "GoodsDetail" << "Inventory");
    ui->Inventory->verticalHeader()->setVisible(false); // 隐藏水平header

    ui->OutOfStock->setColumnCount(7);
    ui->OutOfStock->setHorizontalHeaderLabels(QStringList()<< "DepotID" << "DepotName"
                                              << "GoodsID" << "GoodsName" << "GoodsDetail"
                                              << "Inventory" << "MinInventory");
    ui->OutOfStock->verticalHeader()->setVisible(false); // 隐藏水平header


    ui->Storage->resizeColumnsToContents();//根据表头内容调整列宽
    ui->Storage->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不可编辑
    ui->Storage->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->Delivery->resizeColumnsToContents();
    ui->Delivery->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Delivery->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->LackOfGoods->resizeColumnsToContents();
    ui->LackOfGoods->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->LackOfGoods->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->Inventory->resizeColumnsToContents();
    ui->Inventory->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Inventory->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->OutOfStock->resizeColumnsToContents();
    ui->OutOfStock->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->OutOfStock->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行

    if(CONTROL->TYPE == Purchaser || CONTROL->TYPE == Reviewer)
        ui->tabWidget->setCurrentIndex(PageStorage);
    else if(CONTROL->TYPE == Seller)
        ui->tabWidget->setCurrentIndex(PageDelivery);
    else
        ui->tabWidget->setCurrentIndex(PageInventory);

    ui->DepotInfo->setColumnCount(4);
    ui->DepotInfo->setHorizontalHeaderLabels(QStringList()<< "ID" << "Name" << "City" << "Tel");
    ui->DepotInfo->verticalHeader()->setVisible(false); // 隐藏水平header
    ui->DepotInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->DepotInfo->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行

    ui->GoodsInfo->setColumnCount(4);
    ui->GoodsInfo->setHorizontalHeaderLabels(QStringList()<< "ID" << "Name" << "Introduction" << "MinInventory");
    ui->GoodsInfo->verticalHeader()->setVisible(false); // 隐藏水平header
    ui->GoodsInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->GoodsInfo->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行

    ui->WorkerInfo->setColumnCount(6);
    ui->WorkerInfo->setHorizontalHeaderLabels(QStringList()<< "ID" << "Name" << "Sex" << "Age" << "Tel" << "Type");
    ui->WorkerInfo->verticalHeader()->setVisible(false); // 隐藏水平header
    ui->WorkerInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->WorkerInfo->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行

    ui->ClientInfo->setColumnCount(4);
    ui->ClientInfo->setHorizontalHeaderLabels(QStringList()<< "ID" << "Name" << "City"<< "Tel");
    ui->ClientInfo->verticalHeader()->setVisible(false); // 隐藏水平header
    ui->ClientInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->ClientInfo->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行

    ui->SupplierInfo->setColumnCount(4);
    ui->SupplierInfo->setHorizontalHeaderLabels(QStringList()<< "ID" << "Name" << "City"<< "Tel");
    ui->SupplierInfo->verticalHeader()->setVisible(false); // 隐藏水平header
    ui->SupplierInfo->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->SupplierInfo->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行

    m_accessManager = new QNetworkAccessManager(this);
    QObject::connect(this->m_accessManager, SIGNAL(finished(QNetworkReply*)),
                     this, SLOT(finishedSlot(QNetworkReply*)));

    QObject::connect(this, SIGNAL(SendData(int,QList<QTableWidgetItem*>)),DialogPage, SLOT(ReceiveData(int,QList<QTableWidgetItem*>)));
    QObject::connect(this, SIGNAL(SendInsert(int)),DialogPage, SLOT(ReceiveInsert(int)));
    QObject::connect(this, SIGNAL(SendBaseData(int,QList<QTableWidgetItem*>)),InsertBasePage, SLOT(ReceiveData(int,QList<QTableWidgetItem*>)));
    QObject::connect(this, SIGNAL(SendInsertBase(int)),InsertBasePage, SLOT(ReceiveInsert(int)));
    QObject::connect(DialogPage, SIGNAL(SendUpdateTab1(int,QString,QString,QString)),this, SLOT(UpdateStorage(int,QString,QString,QString)));
    QObject::connect(DialogPage, SIGNAL(SendUpdateTab2(int,QString,QString,QString)),this, SLOT(UpdateDelivery(int,QString,QString,QString)));
    QObject::connect(InsertBasePage, SIGNAL(SendUpdateDepot(int,QString)),this, SLOT(UpdateDepot(int,QString)));
    QObject::connect(InsertBasePage, SIGNAL(SendUpdateGoods(int,QString)),this, SLOT(UpdateGoods(int,QString)));
    QObject::connect(InsertBasePage, SIGNAL(SendUpdateClient(int,QString)),this, SLOT(UpdateClient(int,QString)));
    QObject::connect(InsertBasePage, SIGNAL(SendUpdateSupplier(int,QString)),this, SLOT(UpdateSupplier(int,QString)));
}

Worker::~Worker()
{
    delete ui;
}

void Worker::SetStorage()
{
    ui->Storage->setRowCount(recommend.size());
    int i = 0;
    for(;i<recommend.size();i++)
    {
        ui->Storage->setItem(i,0,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("ID").toInt())));
        ui->Storage->setItem(i,1,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("DepotID").toInt())));
        ui->Storage->setItem(i,2,new QTableWidgetItem(recommend.at(i).toObject().value("DepotName").toString()));
        ui->Storage->setItem(i,3,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("GoodsID").toInt())));
        ui->Storage->setItem(i,4,new QTableWidgetItem(recommend.at(i).toObject().value("GoodsName").toString()));
        ui->Storage->setItem(i,5,new QTableWidgetItem(recommend.at(i).toObject().value("Detail").toString()));
        ui->Storage->setItem(i,6,new QTableWidgetItem(recommend.at(i).toObject().value("Price").toString()));
        ui->Storage->setItem(i,7,new QTableWidgetItem(recommend.at(i).toObject().value("Count").toString()));
        ui->Storage->setItem(i,8,new QTableWidgetItem(recommend.at(i).toObject().value("Date").toString()));
        ui->Storage->setItem(i,9,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("SupplierID").toInt())));
        ui->Storage->setItem(i,10,new QTableWidgetItem(recommend.at(i).toObject().value("SupplierName").toString()));
        ui->Storage->setItem(i,11,new QTableWidgetItem(recommend.at(i).toObject().value("PurchaseID").toString()));
        ui->Storage->setItem(i,12,new QTableWidgetItem(recommend.at(i).toObject().value("PurchaseName").toString()));
        ui->Storage->setItem(i,13,new QTableWidgetItem(recommend.at(i).toObject().value("ReviewID").toString()));
        QString SS = recommend.at(i).toObject().value("Status").toString() == "1"?"审核通过":"未审核";
        ui->Storage->setItem(i,14,new QTableWidgetItem(SS));
    }
}

void Worker::SetDelivery()
{
    ui->Delivery->setRowCount(recommend.size());
    int i = 0;
    for(;i<recommend.size();i++)
    {
        ui->Delivery->setItem(i,0,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("ID").toInt())));
        ui->Delivery->setItem(i,1,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("DepotID").toInt())));
        ui->Delivery->setItem(i,2,new QTableWidgetItem(recommend.at(i).toObject().value("DepotName").toString()));
        ui->Delivery->setItem(i,3,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("GoodsID").toInt())));
        ui->Delivery->setItem(i,4,new QTableWidgetItem(recommend.at(i).toObject().value("GoodsName").toString()));
        ui->Delivery->setItem(i,5,new QTableWidgetItem(recommend.at(i).toObject().value("Detail").toString()));
        ui->Delivery->setItem(i,6,new QTableWidgetItem(recommend.at(i).toObject().value("Price").toString()));
        ui->Delivery->setItem(i,7,new QTableWidgetItem(recommend.at(i).toObject().value("Count").toString()));
        ui->Delivery->setItem(i,8,new QTableWidgetItem(recommend.at(i).toObject().value("Date").toString()));
        ui->Delivery->setItem(i,9,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("ClientID").toInt())));
        ui->Delivery->setItem(i,10,new QTableWidgetItem(recommend.at(i).toObject().value("ClientName").toString()));
        ui->Delivery->setItem(i,11,new QTableWidgetItem(recommend.at(i).toObject().value("SellerID").toString()));
        ui->Delivery->setItem(i,12,new QTableWidgetItem(recommend.at(i).toObject().value("SellerName").toString()));
        ui->Delivery->setItem(i,13,new QTableWidgetItem(recommend.at(i).toObject().value("ReviewID").toString()));
        QString SS = recommend.at(i).toObject().value("Status").toString() == "1"?"审核通过":"未审核";
        ui->Delivery->setItem(i,14,new QTableWidgetItem(SS));
    }
}

void Worker::SetLackOfGoods()
{
    ui->LackOfGoods->setRowCount(recommend.size());
    int i = 0;
    for(;i<recommend.size();i++)
    {
        ui->LackOfGoods->setItem(i,0,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("ID").toInt())));
        ui->LackOfGoods->setItem(i,1,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("DepotID").toInt())));
        ui->LackOfGoods->setItem(i,2,new QTableWidgetItem(recommend.at(i).toObject().value("DepotName").toString()));
        ui->LackOfGoods->setItem(i,3,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("GoodsID").toInt())));
        ui->LackOfGoods->setItem(i,4,new QTableWidgetItem(recommend.at(i).toObject().value("GoodsName").toString()));
        ui->LackOfGoods->setItem(i,5,new QTableWidgetItem(recommend.at(i).toObject().value("Detail").toString()));
        ui->LackOfGoods->setItem(i,6,new QTableWidgetItem(recommend.at(i).toObject().value("Price").toString()));
        ui->LackOfGoods->setItem(i,7,new QTableWidgetItem(recommend.at(i).toObject().value("Count").toString()));
        ui->LackOfGoods->setItem(i,8,new QTableWidgetItem(recommend.at(i).toObject().value("Date").toString()));
        ui->LackOfGoods->setItem(i,9,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("ClientID").toInt())));
        ui->LackOfGoods->setItem(i,10,new QTableWidgetItem(recommend.at(i).toObject().value("ClientName").toString()));
        ui->LackOfGoods->setItem(i,11,new QTableWidgetItem(recommend.at(i).toObject().value("SellerID").toString()));
        ui->LackOfGoods->setItem(i,12,new QTableWidgetItem(recommend.at(i).toObject().value("SellerName").toString()));
        ui->LackOfGoods->setItem(i,13,new QTableWidgetItem(recommend.at(i).toObject().value("ReviewID").toString()));
        QString SS = recommend.at(i).toObject().value("Status").toString() == "1"?"审核通过":"未审核";
        ui->LackOfGoods->setItem(i,14,new QTableWidgetItem(SS));
    }
}

void Worker::SetInventory()
{
    ui->Inventory->setRowCount(recommend.size());
    int i = 0;
    for(;i<recommend.size();i++)
    {
        ui->Inventory->setItem(i,0,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("DepotID").toInt())));
        ui->Inventory->setItem(i,1,new QTableWidgetItem(recommend.at(i).toObject().value("DepotName").toString()));
        ui->Inventory->setItem(i,2,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("GoodsID").toInt())));
        ui->Inventory->setItem(i,3,new QTableWidgetItem(recommend.at(i).toObject().value("GoodsName").toString()));
        ui->Inventory->setItem(i,4,new QTableWidgetItem(recommend.at(i).toObject().value("GoodsDetail").toString()));
        ui->Inventory->setItem(i,5,new QTableWidgetItem(recommend.at(i).toObject().value("Inventory").toString()));
    }
}

void Worker::SetOutOfStock()
{
    ui->OutOfStock->setRowCount(recommend.size());
    int i = 0;
    for(;i<recommend.size();i++)
    {
        ui->OutOfStock->setItem(i,0,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("DepotID").toInt())));
        ui->OutOfStock->setItem(i,1,new QTableWidgetItem(recommend.at(i).toObject().value("DepotName").toString()));
        ui->OutOfStock->setItem(i,2,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("GoodsID").toInt())));
        ui->OutOfStock->setItem(i,3,new QTableWidgetItem(recommend.at(i).toObject().value("GoodsName").toString()));
        ui->OutOfStock->setItem(i,4,new QTableWidgetItem(recommend.at(i).toObject().value("Detail").toString()));
        ui->OutOfStock->setItem(i,5,new QTableWidgetItem(recommend.at(i).toObject().value("Inventory").toString()));
        ui->OutOfStock->setItem(i,6,new QTableWidgetItem(recommend.at(i).toObject().value("MinInventory").toString()));
    }
}

void Worker::SetDepotInfo()
{
    ui->DepotInfo->setRowCount(recommend.size());
    int i = 0;
    for(;i<recommend.size();i++)
    {
        ui->DepotInfo->setItem(i,0,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("ID").toInt())));
        ui->DepotInfo->setItem(i,1,new QTableWidgetItem(recommend.at(i).toObject().value("Name").toString()));
        ui->DepotInfo->setItem(i,2,new QTableWidgetItem(recommend.at(i).toObject().value("City").toString()));
        ui->DepotInfo->setItem(i,3,new QTableWidgetItem(recommend.at(i).toObject().value("Tel").toString()));
    }
}

void Worker::SetGoodsInfo()
{
    ui->GoodsInfo->setRowCount(recommend.size());
    int i = 0;
    for(;i<recommend.size();i++)
    {
        ui->GoodsInfo->setItem(i,0,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("ID").toInt())));
        ui->GoodsInfo->setItem(i,1,new QTableWidgetItem(recommend.at(i).toObject().value("Name").toString()));
        ui->GoodsInfo->setItem(i,2,new QTableWidgetItem(recommend.at(i).toObject().value("Introduction").toString()));
        ui->GoodsInfo->setItem(i,3,new QTableWidgetItem(recommend.at(i).toObject().value("MinInventory").toString()));
    }
}

void Worker::SetWorkerInfo()
{
    ui->WorkerInfo->setRowCount(recommend.size());
    int i = 0;
    for(;i<recommend.size();i++)
    {
        ui->WorkerInfo->setItem(i,0,new QTableWidgetItem(recommend.at(i).toObject().value("ID").toString()));
        ui->WorkerInfo->setItem(i,1,new QTableWidgetItem(recommend.at(i).toObject().value("Name").toString()));
        ui->WorkerInfo->setItem(i,2,new QTableWidgetItem(recommend.at(i).toObject().value("Sex").toString()));
        ui->WorkerInfo->setItem(i,3,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("Age").toInt())));
        ui->WorkerInfo->setItem(i,4,new QTableWidgetItem(recommend.at(i).toObject().value("Tel").toString()));
        int type = recommend.at(i).toObject().value("Type").toString().toInt();
        QString SS= "";
        switch (type) {
        case Purchaser:
            SS="采购人员";break;
        case Seller:
            SS="销售人员";break;
        case Reviewer:
            SS="审核人员";break;
        case Manager:
            SS="管理人员";break;
        }
        ui->WorkerInfo->setItem(i,5,new QTableWidgetItem(SS));
    }
}

void Worker::SetClientInfo()
{
    ui->ClientInfo->setRowCount(recommend.size());
    int i = 0;
    for(;i<recommend.size();i++)
    {
        ui->ClientInfo->setItem(i,0,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("ID").toInt())));
        ui->ClientInfo->setItem(i,1,new QTableWidgetItem(recommend.at(i).toObject().value("Name").toString()));
        ui->ClientInfo->setItem(i,2,new QTableWidgetItem(recommend.at(i).toObject().value("City").toString()));
        ui->ClientInfo->setItem(i,3,new QTableWidgetItem(recommend.at(i).toObject().value("Tel").toString()));
    }
}

void Worker::SetSupplierInfo()
{
    ui->SupplierInfo->setRowCount(recommend.size());
    int i = 0;
    for(;i<recommend.size();i++)
    {
        ui->SupplierInfo->setItem(i,0,new QTableWidgetItem(QString::number(recommend.at(i).toObject().value("ID").toInt())));
        ui->SupplierInfo->setItem(i,1,new QTableWidgetItem(recommend.at(i).toObject().value("Name").toString()));
        ui->SupplierInfo->setItem(i,2,new QTableWidgetItem(recommend.at(i).toObject().value("City").toString()));
        ui->SupplierInfo->setItem(i,3,new QTableWidgetItem(recommend.at(i).toObject().value("Tel").toString()));
    }
}

void Worker::UpdateStorage(int SearchKind,QString SearchInfo,QString StartTime,QString EndTime)
{
    if((SearchKind == SearchByClientID || SearchKind == SearchByClientName) && SearchInfo != "")
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Cannot search the storage through the client!"),QMessageBox::Yes);
        return;
    }
    if(StartTime == "")
        StartTime = ui->StartTime->text();
    if(EndTime == "")
        EndTime = ui->EndTime->text();
    if(SearchKind == SearchMax)
        SearchKind = ui->SearchKind->currentIndex();
    if(SearchInfo == "")
        SearchInfo = ui->SearchInfo->toPlainText();
    CurrentFun = FunUpdateStorage;
    QNetworkRequest* request = new QNetworkRequest();
    QUrl url= QUrl(CONTROL->MyUrl.toString() + "/GetStorage");
    QUrlQuery query;
    if(SearchInfo != "")
    {
        query.addQueryItem("Kind", QString::number(SearchKind));
        query.addQueryItem("Info", SearchInfo);
    }
    query.addQueryItem("SS", StartTime);
    query.addQueryItem("EE", EndTime);
    url.setQuery(query);
    request->setUrl(url);
    QNetworkReply*reply = m_accessManager->get(*request);
}

void Worker::UpdateDelivery(int SearchKind,QString SearchInfo,QString StartTime,QString EndTime)
{
    if((SearchKind == SearchBySupplierID || SearchKind == SearchBySupplierName)  && SearchInfo != "")
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Cannot search the delivery through the supplier!"),QMessageBox::Yes);
        return;
    }
    if(StartTime == "")
        StartTime = ui->StartTime->text();
    if(EndTime == "")
        EndTime = ui->EndTime->text();
    if(SearchKind == SearchMax)
        SearchKind = ui->SearchKind->currentIndex();
    if(SearchInfo == "")
        SearchInfo = ui->SearchInfo->toPlainText();
    CurrentFun = FunUpdateDelivery;
    QNetworkRequest* request = new QNetworkRequest();
    QUrl url= QUrl(CONTROL->MyUrl.toString() + "/GetDelivery");
    QUrlQuery query;
    if(SearchInfo != "")
    {
        query.addQueryItem("Kind", QString::number(SearchKind));
        query.addQueryItem("Info", SearchInfo);
    }
    query.addQueryItem("SS", StartTime);
    query.addQueryItem("EE", EndTime);
    url.setQuery(query);
    request->setUrl(url);
    QNetworkReply*reply = m_accessManager->get(*request);
}

void Worker::UpdateLackOfGoods(int SearchKind,QString SearchInfo,QString StartTime,QString EndTime)
{
    if((SearchKind == SearchBySupplierID || SearchKind == SearchBySupplierName )  && SearchInfo != "")
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Cannot search the lackofgoods through the supplier!"),QMessageBox::Yes);
        return;
    }
    if(StartTime == "")
        StartTime = ui->StartTime->text();
    if(EndTime == "")
        EndTime = ui->EndTime->text();
    if(SearchKind == SearchMax)
        SearchKind = ui->SearchKind->currentIndex();
    if(SearchInfo == "")
        SearchInfo = ui->SearchInfo->toPlainText();
    CurrentFun = FunUpdateLackOfGoods;
    QNetworkRequest* request = new QNetworkRequest();
    QUrl url= QUrl(CONTROL->MyUrl.toString() + "/GetLackOfGoods");
    QUrlQuery query;
    if(SearchInfo != "")
    {
        query.addQueryItem("Kind", QString::number(SearchKind));
        query.addQueryItem("Info", SearchInfo);
    }
    query.addQueryItem("SS", StartTime);
    query.addQueryItem("EE", EndTime);
    url.setQuery(query);
    request->setUrl(url);
    QNetworkReply*reply = m_accessManager->get(*request);
}

void Worker::UpdateInventory(int SearchKind,QString SearchInfo)
{
    if(!(SearchKind == SearchByDepotID || SearchKind == SearchByDepotName || SearchKind == SearchByGoodsID || SearchKind == SearchByGoodsName)
            && SearchInfo != "")
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Cannot search inventory based on this condition!"),QMessageBox::Yes);
        return;
    }
    if(SearchKind == SearchMax)
        SearchKind = ui->SearchKind->currentIndex();
    if(SearchInfo == "")
        SearchInfo = ui->SearchInfo->toPlainText();
    CurrentFun = FunUpdateInventory;
    QNetworkRequest* request = new QNetworkRequest();
    QUrl url= QUrl(CONTROL->MyUrl.toString() + "/GetInventory");
    QUrlQuery query;
    if(SearchInfo != "")
    {
        query.addQueryItem("Kind", QString::number(SearchKind));
        query.addQueryItem("Info", SearchInfo);
        url.setQuery(query);
    }
    request->setUrl(url);
    QNetworkReply*reply = m_accessManager->get(*request);
}

void Worker::UpdateOutOfStock(int SearchKind,QString SearchInfo)
{
    if(!(SearchKind == SearchByDepotID || SearchKind == SearchByDepotName || SearchKind == SearchByGoodsID || SearchKind == SearchByGoodsName)
            && SearchInfo != "")
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Cannot search OutOfStock based on this condition!"),QMessageBox::Yes);
        return;
    }
    if(SearchKind == SearchMax)
        SearchKind = ui->SearchKind->currentIndex();
    if(SearchInfo == "")
        SearchInfo = ui->SearchInfo->toPlainText();
    CurrentFun = FunUpdateOutOfStock;
    QNetworkRequest* request = new QNetworkRequest();
    QUrl url= QUrl(CONTROL->MyUrl.toString() + "/GetOutOfStock");
    QUrlQuery query;
    if(SearchInfo != "")
    {
        query.addQueryItem("Kind", QString::number(SearchKind));
        query.addQueryItem("Info", SearchInfo);
        url.setQuery(query);
    }
    request->setUrl(url);
    QNetworkReply*reply = m_accessManager->get(*request);
}

void Worker::UpdateDepot(int SearchKind,QString SearchInfo)
{
    if(!(SearchKind == SearchByDepotID || SearchKind == SearchByDepotName)
            && SearchInfo != "")
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Cannot search depot based on this condition!"),QMessageBox::Yes);
        return;
    }
    if(SearchKind == SearchMax)
        SearchKind = ui->SearchKind->currentIndex();
    if(SearchInfo == "")
        SearchInfo = ui->SearchInfo->toPlainText();
    CurrentFun = FunUpdateDepot;
    QNetworkRequest* request = new QNetworkRequest();
    QUrl url= QUrl(CONTROL->MyUrl.toString() + "/GetDepot");
    QUrlQuery query;
    if(SearchInfo != "")
    {
        query.addQueryItem("Kind", QString::number(SearchKind));
        query.addQueryItem("Info", SearchInfo);
        url.setQuery(query);
    }
    request->setUrl(url);
    QNetworkReply*reply = m_accessManager->get(*request);
}

void Worker::UpdateGoods(int SearchKind,QString SearchInfo)
{
    if(!(SearchKind == SearchByGoodsID || SearchKind == SearchByGoodsName)
            && SearchInfo != "")
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Cannot search goods based on this condition!"),QMessageBox::Yes);
        return;
    }
    if(SearchKind == SearchMax)
        SearchKind = ui->SearchKind->currentIndex();
    if(SearchInfo == "")
        SearchInfo = ui->SearchInfo->toPlainText();
    CurrentFun = FunUpdateGoods;
    QNetworkRequest* request = new QNetworkRequest();
    QUrl url= QUrl(CONTROL->MyUrl.toString() + "/GetGoods");
    QUrlQuery query;
    if(SearchInfo != "")
    {
        query.addQueryItem("Kind", QString::number(SearchKind));
        query.addQueryItem("Info", SearchInfo);
        url.setQuery(query);
    }
    request->setUrl(url);
    QNetworkReply*reply = m_accessManager->get(*request);
}

void Worker::UpdateWorker(int SearchKind,QString SearchInfo)
{
    if(!(SearchKind == SearchByWorkerID || SearchKind == SearchByWorkerName || SearchKind == SearchByWorkerSex || SearchByWorkerAge)
            && SearchInfo != "")
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Cannot search worker based on this condition!"),QMessageBox::Yes);
        return;
    }
    if(SearchKind == SearchMax)
        SearchKind = ui->SearchKind->currentIndex();
    if(SearchInfo == "")
        SearchInfo = ui->SearchInfo->toPlainText();
    if(SearchKind == SearchByWorkerSex)
    {
        if(SearchInfo == "1")
            SearchInfo = "男";
        else if(SearchInfo == "0")
            SearchInfo = "女";
        else
        {
            QMessageBox::information(this,tr("Prompt dialog"),tr("Unknown gender!"),QMessageBox::Yes);
            return;
        }
    }
    CurrentFun = FunUpdateWorker;
    QNetworkRequest* request = new QNetworkRequest();
    QUrl url= QUrl(CONTROL->MyUrl.toString() + "/GetWorker");
    QUrlQuery query;
    if(SearchInfo != "")
    {
        query.addQueryItem("Kind", QString::number(SearchKind));
        query.addQueryItem("Info", SearchInfo);
        url.setQuery(query);
    }
    request->setUrl(url);
    QNetworkReply*reply = m_accessManager->get(*request);
}

void Worker::UpdateClient(int SearchKind,QString SearchInfo)
{
    if(!(SearchKind == SearchByClientID || SearchKind == SearchByClientName)
            && SearchInfo != "")
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Cannot search client based on this condition!"),QMessageBox::Yes);
        return;
    }
    if(SearchKind == SearchMax)
        SearchKind = ui->SearchKind->currentIndex();
    if(SearchInfo == "")
        SearchInfo = ui->SearchInfo->toPlainText();
    CurrentFun = FunUpdateClient;
    QNetworkRequest* request = new QNetworkRequest();
    QUrl url= QUrl(CONTROL->MyUrl.toString() + "/GetClient");
    QUrlQuery query;
    if(SearchInfo != "")
    {
        query.addQueryItem("Kind", QString::number(SearchKind));
        query.addQueryItem("Info", SearchInfo);
        url.setQuery(query);
    }
    request->setUrl(url);
    QNetworkReply*reply = m_accessManager->get(*request);
}

void Worker::UpdateSupplier(int SearchKind,QString SearchInfo)
{
    if(!(SearchKind == SearchBySupplierID || SearchKind == SearchBySupplierName)
            && SearchInfo != "")
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Cannot search supplier based on this condition!"),QMessageBox::Yes);
        return;
    }
    if(SearchKind == SearchMax)
        SearchKind = ui->SearchKind->currentIndex();
    if(SearchInfo == "")
        SearchInfo = ui->SearchInfo->toPlainText();
    CurrentFun = FunUpdateSupplier;
    QNetworkRequest* request = new QNetworkRequest();
    QUrl url= QUrl(CONTROL->MyUrl.toString() + "/GetSupplier");
    QUrlQuery query;
    if(SearchInfo != "")
    {
        query.addQueryItem("Kind", QString::number(SearchKind));
        query.addQueryItem("Info", SearchInfo);
        url.setQuery(query);
    }
    request->setUrl(url);
    QNetworkReply*reply = m_accessManager->get(*request);
}

void Worker::finishedSlot(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray responseData = reply->readAll();
        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(responseData, &json_error);
        if(json_error.error == QJsonParseError::NoError)
        {
            if(parse_doucment.isObject())
            {
                QJsonObject obj = parse_doucment.object();
                if(obj.contains("code"))
                {
                    QJsonValue code_value = obj.take("code");
                    if(code_value == 0)
                    {
                        if(obj.contains("data"))
                        {
                            QJsonValue data_value = obj.take("data");
                            if (data_value.isArray())
                            {
                                recommend = data_value.toArray();
                                switch (CurrentFun)
                                {
                                case FunUpdateDelivery:
                                    SetDelivery();break;
                                case FunUpdateLackOfGoods:
                                    SetLackOfGoods();break;
                                case FunUpdateStorage:
                                    SetStorage();break;
                                case FunUpdateInventory:
                                    SetInventory();break;
                                case FunUpdateOutOfStock:
                                    SetOutOfStock();break;
                                case FunUpdateDepot:
                                    SetDepotInfo();break;
                                case FunUpdateGoods:
                                    SetGoodsInfo();break;
                                case FunUpdateWorker:
                                    SetWorkerInfo();break;
                                case FunUpdateClient:
                                    SetClientInfo();break;
                                case FunUpdateSupplier:
                                    SetSupplierInfo();break;
                                }
                            }
                            else
                            {
                                QMessageBox::information(this,tr("Prompt dialog"),tr("Successfully deleted!"),QMessageBox::Yes);
                                switch (CurrentFun)
                                {
                                case FunDeleteDelivery:
                                    UpdateDelivery(SearchMax,"","","");break;
                                case FunDeleteStorage:
                                    UpdateStorage(SearchMax,"","","");break;
                                case FunDeleteDepot:
                                    UpdateDepot(SearchMax,"");break;
                                case FunDeleteGoods:
                                    UpdateGoods(SearchMax,"");break;
                                case FunDeleteWorker:
                                    UpdateWorker(SearchMax,"");break;
                                case FunDeleteClient:
                                    UpdateClient(SearchMax,"");break;
                                case FunDeleteSupplier:
                                    UpdateSupplier(SearchMax,"");break;
                                }
                            }
                        }
                        else
                            QMessageBox::information(this,tr("Prompt dialog"),tr("Error!"),QMessageBox::Yes);
                    }
                    else if(code_value == 1)
                    {
                        switch (CurrentFun) {
                        case FunUpdateDelivery:
                        case FunUpdateLackOfGoods:
                        case FunUpdateStorage:
                        case FunUpdateInventory:
                        case FunUpdateOutOfStock:
                        case FunUpdateDepot:
                        case FunUpdateGoods:
                        case FunUpdateWorker:
                        case FunUpdateClient:
                        case FunUpdateSupplier:
                            QMessageBox::information(this,tr("Prompt dialog"),tr("No relevant data!"),QMessageBox::Yes);
                            recommend = {};
                            switch (CurrentFun)
                            {
                            case FunUpdateDelivery:
                                SetDelivery();break;
                            case FunUpdateLackOfGoods:
                                SetLackOfGoods();break;
                            case FunUpdateStorage:
                                SetStorage();break;
                            case FunUpdateInventory:
                                SetInventory();break;
                            case FunUpdateOutOfStock:
                                SetOutOfStock();break;
                            case FunUpdateDepot:
                                SetDepotInfo();break;
                            case FunUpdateGoods:
                                SetGoodsInfo();break;
                            case FunUpdateWorker:
                                SetWorkerInfo();break;
                            case FunUpdateClient:
                                SetClientInfo();break;
                            case FunUpdateSupplier:
                                SetSupplierInfo();break;
                            }
                            break;
                        case FunDeleteDelivery:
                        case FunDeleteStorage:
                        case FunDeleteDepot:
                        case FunDeleteGoods:
                        case FunDeleteWorker:
                        case FunDeleteClient:
                        case FunDeleteSupplier:
                            QMessageBox::information(this,tr("Prompt dialog"),tr("Failed to delete!"),QMessageBox::Yes);
                            break;
                        }

                    }
                    else if(code_value == 2)
                        QMessageBox::information(this,tr("Prompt dialog"),tr("The query condition does not match the query type!"),QMessageBox::Yes);
                    else
                        QMessageBox::information(this,tr("Prompt dialog"),tr("Error!"),QMessageBox::Yes);
                }
                else
                    QMessageBox::information(this,tr("Prompt dialog"),tr("Error!"),QMessageBox::Yes);
            }

        }
    }
    else
    {
        qDebug()<<"handle errors here";
        QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

        qDebug(qPrintable(reply->errorString()));
    }
    reply->deleteLater();
}

void Worker::on_Modify_clicked()
{
    if((ui->tabWidget->currentIndex() >= PageLackOfGoods and CONTROL->TYPE <= 2) ||
            (ui->tabWidget->currentIndex() < PageLackOfGoods and CONTROL->TYPE == Manager))
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Current user does not have permission to modify inventory!"),QMessageBox::Yes);
        return;
    }
    else if((!(ui->tabWidget->currentIndex() >= PageDepot) && CONTROL->TYPE == Manager) ||
            (ui->tabWidget->currentIndex() >= PageGoods && CONTROL->TYPE != Manager))
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Current page data cannot be modified!"),QMessageBox::Yes);
        return;
    }
    QList<QTableWidgetItem*>items;
    int tab = ui->tabWidget->currentIndex();
    if(tab == PageStorage)
        items = ui->Storage->selectedItems();
    else if(tab == PageDelivery)
        items = ui->Delivery->selectedItems();
    else if (tab == PageDepot)
        items = ui->DepotInfo->selectedItems();
    else if (tab == PageGoods)
        items = ui->GoodsInfo->selectedItems();
    else if (tab == PageClient)
        items = ui->ClientInfo->selectedItems();
    else if (tab == PageSupplier)
        items = ui->SupplierInfo->selectedItems();
    else
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Current page data cannot be modified!"),QMessageBox::Yes);
        return;
    }
    int count=items.count();
    if(count == 0)
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("No selected row information!"),QMessageBox::Yes);
    }
    else if(count > ColumnCount[tab])
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Select more than one line!"),QMessageBox::Yes);
    }
    else
    {
        if(tab == PageStorage || tab == PageDelivery)
        {
            if(items.at(14)->text() == "审核通过")
            {//若已审核通过则不可修改
                QMessageBox::information(this,tr("Prompt dialog"),tr("The order has been approved!"),QMessageBox::Yes);
            }
            else if(CONTROL->TYPE != Reviewer && CONTROL->TYPE != Manager && QString::fromStdString(CONTROL->ID) != items.at(11)->text())
            {//不可修改他人订单
                QMessageBox::information(this,tr("Prompt dialog"),tr("Cannot modify other people's orders!"),QMessageBox::Yes);
                return;
            }
            else
            {
                emit SendData(tab,items);
                CONTROL->CurrentFun = FunModify;
                DialogPage->show();
            }
        }
        else
        {
            emit SendBaseData(tab,items);
            CONTROL->CurrentFun = FunModify;
            InsertBasePage->show();
        }
    }
}

void Worker::on_Insert_clicked()
{
    if((ui->tabWidget->currentIndex() >= PageLackOfGoods and CONTROL->TYPE <= 2) ||
            (ui->tabWidget->currentIndex() < PageLackOfGoods and CONTROL->TYPE == Manager) ||
            CONTROL->TYPE == Reviewer )
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Current user does not have permission to insert inventory!"),QMessageBox::Yes);
        return;
    }
    else if((ui->tabWidget->currentIndex() < PageDepot || ui->tabWidget->currentIndex() == PageWorker) and CONTROL->TYPE >= 3)
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Current page data cannot be modified!"),QMessageBox::Yes);
        return;
    }
    else if(ui->tabWidget->currentIndex() >= PageDepot and CONTROL->TYPE >= 3)
    {
        CONTROL->CurrentFun = FunInsert;
        emit SendInsertBase(ui->tabWidget->currentIndex());
        InsertBasePage->show();
    }
    else
    {
        CONTROL->CurrentFun = FunInsert;
        emit SendInsert(ui->tabWidget->currentIndex());
        DialogPage->show();
    }
}

void Worker::on_Delete_clicked()
{
    if((ui->tabWidget->currentIndex() >= PageLackOfGoods and CONTROL->TYPE <= 2) ||
            (ui->tabWidget->currentIndex() < PageLackOfGoods and CONTROL->TYPE == Manager) ||
            CONTROL->TYPE == Reviewer )
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Current user does not have permission to delete inventory!"),QMessageBox::Yes);
        return;
    }
    else if((!(ui->tabWidget->currentIndex() >= PageDepot) && CONTROL->TYPE == Manager) ||
            (ui->tabWidget->currentIndex() >= PageGoods && CONTROL->TYPE != Manager))
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Current page data cannot be modified!"),QMessageBox::Yes);
        return;
    }
    QList<QTableWidgetItem*>items;
    int tab = ui->tabWidget->currentIndex();
    QString table = "";
    if(tab == PageStorage)
        items = ui->Storage->selectedItems();
    else if(tab == PageDelivery)
        items = ui->Delivery->selectedItems();
    else if(tab == PageDepot)
        items = ui->DepotInfo->selectedItems();
    else if(tab == PageGoods)
        items = ui->GoodsInfo->selectedItems();
    else if(tab == PageWorker)
        items = ui->WorkerInfo->selectedItems();
    else if(tab == PageClient)
        items = ui->ClientInfo->selectedItems();
    else if(tab == PageSupplier)
        items = ui->SupplierInfo->selectedItems();
    else
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Current page data cannot be modified!"),QMessageBox::Yes);
        return;
    }
    int count=items.count();
    if(count == 0)
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("No selected row information!"),QMessageBox::Yes);
        return;
    }
    else if(count > ColumnCount[tab])
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Select more than one line!"),QMessageBox::Yes);
        return;
    }
    else
    {
        if(tab == PageStorage || tab == PageDelivery)
        {
            if(items.at(14)->text() == "审核通过")//审核通过则不可删除
            {
                QMessageBox::information(this,tr("Prompt dialog"),tr("The order has been approved!"),QMessageBox::Yes);
                return;
            }
            else if(CONTROL->TYPE != Reviewer && CONTROL->TYPE != Manager && QString::fromStdString(CONTROL->ID) != items.at(11)->text())
            {//不可删除别人的订单
                QMessageBox::information(this,tr("Prompt dialog"),tr("Cannot modify other people's orders!"),QMessageBox::Yes);
                return;
            }
            else
            {
                if(tab == PageStorage)
                {
                    CurrentFun = FunDeleteStorage;
                    table = "Storage";
                }
                else if(tab == PageDelivery)
                {
                    CurrentFun = FunDeleteDelivery;
                    table = "Delivery";
                }
            }
        }
        else
        {
            if(tab == PageDepot)
            {
                CurrentFun = FunDeleteDepot;
                table = "Depot";
            }
            else if(tab == PageGoods)
            {
                CurrentFun = FunDeleteGoods;
                table = "Goods";
            }
            else if(tab == PageWorker)
            {
                CurrentFun = FunDeleteWorker;
                table = "Worker";
            }
            else if(tab == PageClient)
            {
                CurrentFun = FunDeleteClient;
                table = "Client";
            }
            else if(tab == PageSupplier)
            {
                CurrentFun = FunDeleteSupplier;
                table = "Supplier";
            }
            else
            {
                QMessageBox::information(this,tr("Prompt dialog"),tr("Error TabWidget!"),QMessageBox::Yes);
                return;
            }
        }
    }
    QNetworkRequest* request = new QNetworkRequest();
    QUrl url= QUrl(CONTROL->MyUrl.toString() + "/Delete");
    QUrlQuery query;
    query.addQueryItem("ID", items.at(0)->text());
    query.addQueryItem("table", table);
    url.setQuery(query);
    request->setUrl(url);
    QNetworkReply*reply = m_accessManager->get(*request);
}

void Worker::on_Search_clicked()
{
    QString SearchInfo = ui->SearchInfo->toPlainText();
    QString StartTime = ui->StartTime->text();
    QString EndTime = ui->EndTime->text();
    int tab = ui->tabWidget->currentIndex();
    int tab2 = ui->SearchKind->currentIndex();
    int SearchKind;
    if(tab == PageStorage)
    {
        if(tab2 == 0)
            SearchKind=SearchByDepotID;
        else if(tab2 == 1)
            SearchKind=SearchByDepotName;
        else if(tab2 == 2)
            SearchKind = SearchBySupplierID;
        else if(tab2 == 3)
            SearchKind = SearchBySupplierName;
        else if(tab2 == 4)
            SearchKind = SearchByGoodsID;
        else if(tab2 == 5)
            SearchKind = SearchByGoodsName;
        else if(tab2 == 6)
            SearchKind = SearchByStatus;
    }
    else if(tab == PageDelivery || tab == PageLackOfGoods)
    {
        if(tab2 == 0)
            SearchKind=SearchByDepotID;
        else if(tab2 == 1)
            SearchKind=SearchByDepotName;
        else if(tab2 == 2)
            SearchKind = SearchByClientID;
        else if(tab2 == 3)
            SearchKind = SearchByClientName;
        else if(tab2 == 4)
            SearchKind = SearchByGoodsID;
        else if(tab2 == 5)
            SearchKind = SearchByGoodsName;
        else if(tab2 == 6)
            SearchKind = SearchByStatus;
    }
    else if(tab == PageInventory || tab == PageOutOfStock)
    {
        if(tab2 == 0)
            SearchKind=SearchByDepotID;
        else if(tab2 == 1)
            SearchKind=SearchByDepotName;
        else if(tab2 == 2)
            SearchKind = SearchByGoodsID;
        else if(tab2 == 3)
            SearchKind = SearchByGoodsName;
    }
    else if(tab == PageDepot)
    {
        if(tab2 == 0)
            SearchKind=SearchByDepotID;
        else if(tab2 == 1)
            SearchKind=SearchByDepotName;
    }
    else if(tab == PageGoods)
    {
        if(tab2 == 0)
            SearchKind=SearchByGoodsID;
        else if(tab2 == 1)
            SearchKind=SearchByGoodsName;
    }
    else if(tab == PageClient)
    {
        if(tab2 == 0)
            SearchKind=SearchByClientID;
        else if(tab2 == 1)
            SearchKind=SearchByClientName;
    }
    else if(tab == PageSupplier)
    {
        if(tab2 == 0)
            SearchKind=SearchBySupplierID;
        else if(tab2 == 1)
            SearchKind=SearchBySupplierName;
    }
    else if(tab == PageWorker)
    {
        if(tab2 == 0)
            SearchKind=SearchByWorkerID;
        else if(tab2 == 1)
            SearchKind=SearchByWorkerName;
        else if(tab2 == 2)
            SearchKind = SearchByWorkerSex;
        else if(tab2 == 3)
            SearchKind = SearchByWorkerAge;
        else if(tab2 == 4)
            SearchKind = SearchByWorkerType;
    }

    if(tab == PageStorage && CONTROL->TYPE != Seller)
        UpdateStorage(SearchKind,SearchInfo,StartTime,EndTime);
    else if(tab == PageDelivery && CONTROL->TYPE != Purchaser)
        UpdateDelivery(SearchKind,SearchInfo,StartTime,EndTime);
    else if (tab == PageLackOfGoods)
        UpdateLackOfGoods(SearchKind,SearchInfo,StartTime,EndTime);
    else if(tab == PageInventory)
        UpdateInventory(SearchKind,SearchInfo);
    else if(tab == PageOutOfStock)
        UpdateOutOfStock(SearchKind,SearchInfo);
    else if(tab == PageDepot)
        UpdateDepot(SearchKind,SearchInfo);
    else if(tab == PageGoods)
        UpdateGoods(SearchKind,SearchInfo);
    else if(tab == PageWorker)
        UpdateWorker(SearchKind,SearchInfo);
    else if(tab == PageClient)
        UpdateClient(SearchKind,SearchInfo);
    else if(tab == PageSupplier)
        UpdateSupplier(SearchKind,SearchInfo);
    else
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Permission denied!"),QMessageBox::Yes);
    }
}

void Worker::on_SearchKind_currentIndexChanged(int index)
{
    int tab = ui->tabWidget->currentIndex();
    ui->SearchInfo->setText(nullptr);
    if(tab == PageWorker && index == 2)
        ui->SearchInfo->setPlaceholderText("1：男 0：女");
    else if(tab == PageWorker && index == 3)
        ui->SearchInfo->setPlaceholderText("如：20-30");
    else if(tab == PageWorker && index == 4)
        ui->SearchInfo->setPlaceholderText("0:采购 1:审核 2:销售 3:管理");
    else if((tab == PageStorage || tab == PageDelivery) && index == 6)
        ui->SearchInfo->setPlaceholderText("1：审核通过 0：未审核");
    else
        ui->SearchInfo->setPlaceholderText("请输入查询条件");
}

void Worker::on_tabWidget_currentChanged(int index)
{
    ui->SearchKind->clear();
    if(index == PageStorage)
    {
        ui->SearchKind->addItem("仓库编号");
        ui->SearchKind->addItem("仓库名称");
        ui->SearchKind->addItem("供应商编号");
        ui->SearchKind->addItem("供应商名称");
        ui->SearchKind->addItem("货品编号");
        ui->SearchKind->addItem("货品名称");
        ui->SearchKind->addItem("审核状态");
    }
    else if(index == PageDelivery)
    {
        ui->SearchKind->addItem("仓库编号");
        ui->SearchKind->addItem("仓库名称");
        ui->SearchKind->addItem("客户编号");
        ui->SearchKind->addItem("客户名称");
        ui->SearchKind->addItem("货品编号");
        ui->SearchKind->addItem("货品名称");
        ui->SearchKind->addItem("审核状态");
    }
    else if(index == PageLackOfGoods)
    {
        ui->SearchKind->addItem("仓库编号");
        ui->SearchKind->addItem("仓库名称");
        ui->SearchKind->addItem("客户编号");
        ui->SearchKind->addItem("客户名称");
        ui->SearchKind->addItem("货品编号");
        ui->SearchKind->addItem("货品名称");
    }
    else if(index == PageInventory || index == PageOutOfStock)
    {
        ui->SearchKind->addItem("仓库编号");
        ui->SearchKind->addItem("仓库名称");
        ui->SearchKind->addItem("货品编号");
        ui->SearchKind->addItem("货品名称");
    }
    else if(index == PageDepot || index == PageGoods || index == PageClient || index == PageSupplier)
    {
        ui->SearchKind->addItem("编号");
        ui->SearchKind->addItem("名称");
    }
    else if(index == PageWorker)
    {
        ui->SearchKind->addItem("编号");
        ui->SearchKind->addItem("名称");
        ui->SearchKind->addItem("性别");
        ui->SearchKind->addItem("年龄");
        ui->SearchKind->addItem("类别");
    }
}
