#include "insertbase.h"
#include "ui_insertbase.h"
extern Control *CONTROL;
InsertBase::InsertBase(QWidget *parent) :
    QDialog (parent),
    ui(new Ui::InsertBase)
{
    ui->setupUi(this);

    m_accessManager = new QNetworkAccessManager(this);
    QObject::connect(this->m_accessManager, SIGNAL(finished(QNetworkReply*)),
                 this, SLOT(finishedSlot(QNetworkReply*)));
}

InsertBase::~InsertBase()
{
    delete ui;
}

void InsertBase::CloseDialog()
{
    if(TabIndex == PageDepot)
        SendUpdateDepot(0,"");
    else if(TabIndex == PageGoods)
        SendUpdateGoods(0,"");
    else if(TabIndex == PageClient)
        SendUpdateClient(0,"");
    else if(TabIndex == PageSupplier)
        SendUpdateSupplier(0,"");
    this->close();
}

void InsertBase::ReceiveData(int TabIndex,QList<QTableWidgetItem*> DATA)
{
    setWindowTitle("Modify");
    InsertBase::TabIndex = TabIndex;
    InsertBase::DATA = DATA;
    ui->textEdit_2->setText(DATA.at(1)->text());
    ui->textEdit_3->setText(DATA.at(2)->text());
    ui->textEdit_4->setText(DATA.at(3)->text());
    ui->label_2->setText("Name:");
    ui->label_3->setText("City:");
    ui->label_4->setText("Tel:");
    if(TabIndex == PageGoods)
    {
      ui->label_3->setText("Introduction:");
      ui->label_4->setText("MinInventory:");
    }
}

void InsertBase::ReceiveInsert(int TabIndex)
{
    setWindowTitle("Insert");
    ui->textEdit_2->setText(nullptr);
    ui->textEdit_3->setText(nullptr);
    ui->textEdit_4->setText(nullptr);
    InsertBase::TabIndex = TabIndex;
    ui->label_2->setText("Name:");
    ui->label_3->setText("City:");
    ui->label_4->setText("Tel:");
    if(TabIndex == PageGoods)
    {
      ui->label_3->setText("Introduction:");
      ui->label_4->setText("MinInventory:");
    }
}


void InsertBase::finishedSlot(QNetworkReply *reply)
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

void InsertBase::on_CancelBtn_clicked()
{
    this->close();
}

void InsertBase::on_ApplyBtn_clicked()
{
    if(CONTROL->CurrentFun == FunModify)
    {
        Modify();
    }
    else if(CONTROL->CurrentFun == FunInsert)
    {
        Insert();
    }
}

void InsertBase::Insert()
{
    //检验是否为空
    bool flag = false;
    if(ui->textEdit_2->toPlainText() == nullptr)
        flag = true;
    if(ui->textEdit_3->toPlainText() == nullptr and TabIndex != PageGoods)
        flag = true;
    if(ui->textEdit_4->toPlainText() == nullptr)
        flag = true;

    if(flag == true)
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Not filled out!"),QMessageBox::Yes);
    }
    else
    {
        CurrentFun = FunInsert;
        QNetworkRequest* request = new QNetworkRequest();
        QUrl url= QUrl(CONTROL->MyUrl.toString() + "/Insert");
        QUrlQuery query;
        query.addQueryItem("table", QString::number(TabIndex));
        query.addQueryItem("Name", ui->textEdit_2->toPlainText());
        query.addQueryItem("City", ui->textEdit_3->toPlainText());
        query.addQueryItem("Tel", ui->textEdit_4->toPlainText());
        url.setQuery(query);
        request->setUrl(url);
        QNetworkReply*reply = m_accessManager->get(*request);
    }
}

void InsertBase::Modify()
{
    //检验是否进行更改
    bool flag = false;
    if(ui->textEdit_2->toPlainText() != DATA.at(1)->text())
        flag = true;
    if(ui->textEdit_3->toPlainText() != DATA.at(2)->text())
        flag = true;
    if(ui->textEdit_4->toPlainText() != DATA.at(3)->text())
        flag = true;

    if(flag == false)
        this->close();
    else
    {
        CurrentFun = FunModify;
        QNetworkRequest* request = new QNetworkRequest();
        QUrl url= QUrl(CONTROL->MyUrl.toString() + "/Update");
        QUrlQuery query;
        query.addQueryItem("table", QString::number(TabIndex));
        query.addQueryItem("ID", DATA.at(0)->text());
        query.addQueryItem("Name", ui->textEdit_2->toPlainText());
        query.addQueryItem("City", ui->textEdit_3->toPlainText());
        query.addQueryItem("Tel", ui->textEdit_4->toPlainText());
        url.setQuery(query);
        request->setUrl(url);
        request->setUrl(url);
        QNetworkReply*reply = m_accessManager->get(*request);
    }
}
