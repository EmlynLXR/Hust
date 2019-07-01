#include "login.h"
#include "ui_login.h"
extern Control *CONTROL;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //添加暗注释
    ui->UserName->setPlaceholderText(QStringLiteral("编号/名字"));
    ui->UserPWD->setPlaceholderText(QStringLiteral("密码"));

    ui->UserType->addItem("采购人员");
    ui->UserType->addItem("审核人员");
    ui->UserType->addItem("销售人员");
    ui->UserType->addItem("管理人员");
    ui->UserType->setCurrentIndex(0);

    m_accessManager = new QNetworkAccessManager(this);
    QObject::connect(this->m_accessManager, SIGNAL(finished(QNetworkReply*)),
                 this, SLOT(finishedSlot(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_LoginIn_clicked()
{
    WorkerID = ui->UserName->toPlainText().toStdString();
    WorkerType = ui->UserType->currentIndex();
    if(WorkerID == "")
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("No UserName!"),QMessageBox::Yes);
        return;
    }
    if(ui->UserPWD->toPlainText().toStdString() == "")
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("No Password!"),QMessageBox::Yes);
        return;
    }

    QNetworkRequest* request = new QNetworkRequest();
    QUrl url= QUrl(CONTROL->MyUrl.toString() + "/login");
    QUrlQuery query;

    query.addQueryItem("ID", QString::fromStdString(WorkerID));
    query.addQueryItem("Type", QString::number(WorkerType));
    url.setQuery(query);
    request->setUrl(url);
    QNetworkReply*reply = m_accessManager->get(*request);
}

void MainWindow::LoginInByPWD()
{
    if(ui->UserPWD->toPlainText() == QString::fromStdString(WorkerPWD))
    {
        QMessageBox::information(this,tr("Prompt dialog"),tr("Login successfully!"),QMessageBox::Yes);
        this->hide();
        WorkerPage = new Worker;
        WorkerPage->show();
    }
    else
        QMessageBox::information(this,tr("Prompt dialog"),tr("Wrong Password!"),QMessageBox::Yes);
}

void MainWindow::finishedSlot(QNetworkReply *reply)
{
    login=false;
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
                             if(data_value["PWD"] != "")
                             {
                                 login=true;
                                 WorkerPWD = data_value["PWD"].toString().toStdString();
                                 CONTROL->ID = WorkerID;
                                 CONTROL->TYPE = WorkerType;
                                 CONTROL->PWD = data_value["PWD"].toString().toStdString();
                                 CONTROL->Name = data_value["Name"].toString().toStdString();
                                 CONTROL->Sex = data_value["Sex"].toString().toStdString();
                                 CONTROL->Tel = data_value["Tel"].toString().toStdString();
                                 CONTROL->Age = data_value["Age"].toInt();

                                 LoginInByPWD();
                             }
                             else
                                 QMessageBox::information(this,tr("Prompt dialog"),tr("Login error!"),QMessageBox::Yes);
                         }
                         else
                             QMessageBox::information(this,tr("Prompt dialog"),tr("Login error!"),QMessageBox::Yes);
                     }
                     else if(code_value==1)
                         QMessageBox::information(this,tr("Prompt dialog"),tr("No UserName!"),QMessageBox::Yes);
                     else if(code_value==2)
                         QMessageBox::information(this,tr("Prompt dialog"),tr("No UserType!"),QMessageBox::Yes);
                     else if(code_value==3)
                         QMessageBox::information(this,tr("Prompt dialog"),tr("User does not exist or password is invalid!"),QMessageBox::Yes);
                     else
                         QMessageBox::information(this,tr("Prompt dialog"),tr("User does not exist or password is invalid!"),QMessageBox::Yes);
                 }
                 else
                     QMessageBox::information(this,tr("Prompt dialog"),tr("Login error!"),QMessageBox::Yes);
            }
         }
    }
    else
    {
         QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
         qDebug(qPrintable(reply->errorString()));
    }
    reply->deleteLater();
}

