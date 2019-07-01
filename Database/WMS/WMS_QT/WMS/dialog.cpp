#include "dialog.h"
#include "ui_dialog.h"
extern Control *CONTROL;
dialog::dialog(QWidget *parent) :
    QDialog (parent),
    ui(new Ui::dialog)
{
    ui->setupUi(this);
    ui->StatusCbx->addItem("未审核");
    ui->StatusCbx->addItem("审核通过");

    m_accessManager = new QNetworkAccessManager(this);
    QObject::connect(this->m_accessManager, SIGNAL(finished(QNetworkReply*)),
                 this, SLOT(finishedSlot(QNetworkReply*)));
}

dialog::~dialog()
{
    delete ui;
}

void dialog::GetGoods()
{
    CurrentFun = FunGetGoods;
    QNetworkRequest* request = new QNetworkRequest();
    QUrl url= QUrl(CONTROL->MyUrl.toString() + "/GetGoods");
    request->setUrl(url);
    QNetworkReply*reply = m_accessManager->get(*request);
}

void dialog::SetGoods()
{
    dialog::Goods = recommend;
    ui->GoodsName->clear();
    for(int i =0;i<Goods.size();i++)
    {
        ui->GoodsName->addItem(Goods.at(i).toObject().value("Name").toString());
        if(CONTROL->CurrentFun == FunModify && DATA.at(3)->text() == QString::number(Goods.at(i).toObject().value("ID").toInt()))
            ui->GoodsName->setCurrentIndex(i);
    }

    GetDepot();
}

void dialog::GetDepot()
{
    CurrentFun = FunGetDepot;
    QNetworkRequest* request = new QNetworkRequest();
    QUrl url= QUrl(CONTROL->MyUrl.toString() + "/GetDepot");
    request->setUrl(url);
    QNetworkReply*reply = m_accessManager->get(*request);
}

void dialog::SetDepot()
{
    dialog::Depot = recommend;
    ui->DepotName->clear();
    for(int i =0;i<Depot.size();i++)
    {
        ui->DepotName->addItem(Depot.at(i).toObject().value("Name").toString());
        if(CONTROL->CurrentFun == FunModify && DATA.at(1)->text() == QString::number(Depot.at(i).toObject().value("ID").toInt()))
            ui->DepotName->setCurrentIndex(i);
    }
    GetClient();
}

void dialog::GetClient()
{
    CurrentFun = FunGetClient;
    QNetworkRequest* request = new QNetworkRequest();
    QUrl url;
    if(TabIndex == PageStorage)
        url = QUrl(CONTROL->MyUrl.toString() + "/GetSupplier");
    else if(TabIndex == PageDelivery)
        url = QUrl(CONTROL->MyUrl.toString() + "/GetClient");
    request->setUrl(url);
    QNetworkReply*reply = m_accessManager->get(*request);
}

void dialog::SetClient()
{
    dialog::Client = recommend;
    ui->ClientName->clear();
    for(int i =0;i<Client.size();i++)
    {
        ui->ClientName->addItem(Client.at(i).toObject().value("Name").toString());
        if(CONTROL->CurrentFun == FunModify && DATA.at(9)->text() == QString::number(Client.at(i).toObject().value("ID").toInt()))
            ui->ClientName->setCurrentIndex(i);
    }
}

void dialog::ReceiveData(int TabIndex,QList<QTableWidgetItem*> DATA)
{
    setWindowTitle("Modify");
    dialog::TabIndex = TabIndex;
    dialog::DATA = DATA;
    ui->ID->setText(DATA.at(0)->text());
    ui->DepotID->setText(DATA.at(1)->text());
    ui->GoodsID->setText(DATA.at(3)->text());
    ui->Price->setText(DATA.at(6)->text());
    ui->Count->setText(DATA.at(7)->text());
    ui->ClientID->setText(DATA.at(9)->text());
    ui->WorkerID->setText(DATA.at(11)->text());
    ui->ReviewID->setText(DATA.at(13)->text());
    if(DATA.at(14)->text() == "未审核")
        ui->StatusCbx->setCurrentIndex(0);
    else if(DATA.at(14)->text() == "审核通过")
        ui->StatusCbx->setCurrentIndex(1);

    if(TabIndex == PageStorage)//入库单
    {
        ui->ClientLabel->setText("Supplier:");
        ui->WorkerLabel->setText("PurchaseID:");      
    }
    else if(TabIndex == PageDelivery)//出库单
    {
        ui->ClientLabel->setText("Client:");
        ui->WorkerLabel->setText("SellerID:");
    }

    if(CONTROL->TYPE == Purchaser || CONTROL->TYPE == Seller)//采购人员 or 销售人员
    {
        ui->ID->setEnabled(false);
        ui->WorkerID->setEnabled(false);
        ui->ReviewID->setEnabled(false);
        ui->StatusCbx->setEnabled(false);
    }
    else if(CONTROL->TYPE == Reviewer)//审核人员
    {
        ui->ID->setEnabled(false);
        ui->WorkerID->setEnabled(false);
        ui->ReviewID->setEnabled(false);

        ui->DepotID->setEnabled(false);
        ui->GoodsID->setEnabled(false);
        ui->Price->setEnabled(false);
        ui->Count->setEnabled(false);
        ui->ClientID->setEnabled(false);

        ui->DepotName->setEnabled(false);
        ui->GoodsName->setEnabled(false);
        ui->ClientName->setEnabled(false);

        if(ui->ReviewID->toPlainText() == "")
        {
            ui->ReviewID->setText(QString::fromStdString(CONTROL->ID));
        }
    }
    GetGoods();
}

void dialog::ReceiveInsert(int TabIndex)
{
    setWindowTitle("Insert");
    dialog::TabIndex = TabIndex;
    ui->ID->setText(nullptr);
    ui->DepotID->setText(nullptr);
    ui->GoodsID->setText(nullptr);
    ui->Price->setText(nullptr);
    ui->Count->setText(nullptr);
    ui->ReviewID->setText(nullptr);
    ui->ClientID->setText(nullptr);
    ui->WorkerID->setText(nullptr);
    ui->StatusCbx->setCurrentIndex(0);

    ui->ID->setEnabled(false);
    ui->WorkerID->setEnabled(false);
    ui->ReviewID->setEnabled(false);
    ui->StatusCbx->setEnabled(false);

    if(TabIndex == PageStorage)
    {
        ui->ClientLabel->setText("Supplier:");
        ui->WorkerLabel->setText("PurchaseID:");
    }
    else if(TabIndex == PageDelivery)
    {
        ui->ClientLabel->setText("Client:");
        ui->WorkerLabel->setText("SellerID:");
    }
    ui->WorkerID->setText(QString::fromStdString(CONTROL->ID));
    GetGoods();
}

void dialog::finishedSlot(QNetworkReply *reply)
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
                        QJsonValue data_value = obj.take("data");
                        if (data_value.isArray())
                        {
                            recommend = data_value.toArray();
                            switch (CurrentFun)
                            {
                            case FunGetGoods:
                                SetGoods();break;
                            case FunGetDepot:
                                SetDepot();break;
                            case FunGetClient:
                                SetClient();break;
                            }
                        }
                        else
                        {
                            switch (CONTROL->CurrentFun) {
                                case FunModify:
                                    QMessageBox::information(this,tr("Prompt dialog"),tr("Successfully modified!"),QMessageBox::Yes);
                                break;
                                case FunInsert:
                                    QMessageBox::information(this,tr("Prompt dialog"),tr("Successfully inserted!"),QMessageBox::Yes);
                                break;
                            }
                            CloseDialog();
                        }
                    }
                    else if(code_value == 2)
                    {
                        QMessageBox::information(this,tr("Prompt dialog"),tr("Added to table LackOfGoods!"),QMessageBox::Yes);
                        CloseDialog();
                    }
                    else
                        QMessageBox::information(this,tr("Prompt dialog"),tr("Error code!"),QMessageBox::Yes);
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

void dialog::on_CancelBtn_clicked()
{
    this->close();
}

void dialog::on_ApplyBtn_clicked()
{
    if(CONTROL->CurrentFun == FunModify)
    {
        if(CONTROL->TYPE == Reviewer)//审核人员
            ReviewUpdate();
        else if(CONTROL->TYPE == Purchaser | CONTROL->TYPE == Seller)
            WorkerUpdate();
    }
    else if(CONTROL->CurrentFun == FunInsert)
    {
        WorkerInsert();
    }
}

void dialog::WorkerInsert()
{
    //检验是否进行更改
    bool flag = false;
    if(ui->GoodsID->text() == nullptr)
        flag = true;
    if(ui->Price->toPlainText() == nullptr)
        flag = true;
    if(ui->Count->toPlainText() == nullptr)
        flag = true;
    if(ui->ClientID->text() == nullptr)
        flag = true;

    if(flag == true)
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Not filled out!"),QMessageBox::Yes);
    }
    else
    {
        CurrentFun = FunWorkerInsert;
        QNetworkRequest* request = new QNetworkRequest();
        QUrl url= QUrl(CONTROL->MyUrl.toString() + "/Insert");
        QUrlQuery query;
        query.addQueryItem("table", QString::number(dialog::TabIndex));
        query.addQueryItem("DepotID", ui->DepotID->text());
        query.addQueryItem("GoodsID", ui->GoodsID->text());
        query.addQueryItem("Price", ui->Price->toPlainText());
        query.addQueryItem("Count", ui->Count->toPlainText());
        query.addQueryItem("ClientID", ui->ClientID->text());
        query.addQueryItem("WorkerID", QString::fromStdString(CONTROL->ID));
        url.setQuery(query);
        request->setUrl(url);
        QNetworkReply*reply = m_accessManager->get(*request);
    }
}

void dialog::ReviewUpdate()
{
    if(ui->StatusCbx->currentText() == dialog::DATA.at(14)->text())//无改变
        this->close();
    else
    {
        CurrentFun = FunReviewUpdate;
        QNetworkRequest* request = new QNetworkRequest();
        QUrl url= QUrl(CONTROL->MyUrl.toString() + "/UpdateStatus");
        QUrlQuery query;
        query.addQueryItem("ID", DATA.at(0)->text());
        query.addQueryItem("table", QString::number(dialog::TabIndex));
        query.addQueryItem("ReviewID", QString::fromStdString(CONTROL->ID));
        query.addQueryItem("DepotID", ui->DepotID->text());
        query.addQueryItem("GoodsID", ui->GoodsID->text());
        query.addQueryItem("Count", ui->Count->toPlainText());
        url.setQuery(query);
        request->setUrl(url);
        QNetworkReply*reply = m_accessManager->get(*request);
    }
}

void dialog::WorkerUpdate()
{
    //检验是否进行更改
    bool flag = false;
    if(ui->DepotID->text() != DATA.at(1)->text())
        flag = true;
    if(ui->GoodsID->text() != DATA.at(3)->text())
        flag = true;
    if(ui->Price->toPlainText() != DATA.at(6)->text())
        flag = true;
    if(ui->Count->toPlainText() != DATA.at(7)->text())
        flag = true;
    if(ui->ClientID->text() != DATA.at(9)->text())
        flag = true;

    if(flag == false)
        this->close();
    else
    {
        CurrentFun = FunWorkerUpdate;
        QNetworkRequest* request = new QNetworkRequest();
        QUrl url= QUrl(CONTROL->MyUrl.toString() + "/Update");
        QUrlQuery query;
        query.addQueryItem("ID", DATA.at(0)->text());
        query.addQueryItem("table", QString::number(dialog::TabIndex));
        query.addQueryItem("DepotID", ui->DepotID->text());
        query.addQueryItem("GoodsID", ui->GoodsID->text());
        query.addQueryItem("Price", ui->Price->toPlainText());
        query.addQueryItem("Count", ui->Count->toPlainText());
        query.addQueryItem("SupplierID", ui->ClientID->text());
        url.setQuery(query);
        request->setUrl(url);
        QNetworkReply*reply = m_accessManager->get(*request);
    }
}

void dialog::CloseDialog()
{
    if(dialog::TabIndex == PageStorage)
        emit SendUpdateTab1(0,"","","");
    else if(dialog::TabIndex == PageDelivery)
        emit SendUpdateTab2(0,"","","");
    this->close();
}


void dialog::on_GoodsName_currentIndexChanged(int index)
{
    ui->GoodsID->setText(QString::number(Goods.at(index).toObject().value("ID").toInt()));
}

void dialog::on_DepotName_currentIndexChanged(int index)
{
    ui->DepotID->setText(QString::number(Depot.at(index).toObject().value("ID").toInt()));
}

void dialog::on_ClientName_currentIndexChanged(int index)
{
    ui->ClientID->setText(QString::number(Client.at(index).toObject().value("ID").toInt()));
}
