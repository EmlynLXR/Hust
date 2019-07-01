#ifndef DAILOG_H
#define DAILOG_H
#include "header.h"
#include "control.h"
#define FunWorkerUpdate 0
#define FunReviewUpdate 1
#define FunWorkerInsert 2
#define FunUpdateDepotName 3
#define FunUpdateGoodsName 4
#define FunGetGoods 5
#define FunGetDepot 6
#define FunGetClient 7
namespace Ui {
class dialog;
}
class dialog: public QDialog
{
    Q_OBJECT
public:
    explicit dialog(QWidget *parent = nullptr);
    ~dialog();

private slots:
    void finishedSlot(QNetworkReply *reply);
    void on_CancelBtn_clicked();
    void on_ApplyBtn_clicked();

    void on_GoodsName_currentIndexChanged(int index);

    void on_DepotName_currentIndexChanged(int index);

    void on_ClientName_currentIndexChanged(int index);

public slots:
    void ReceiveData(int TabIndex,QList<QTableWidgetItem*> DATA);
    void ReceiveInsert(int TabIndex);

signals:
    void SendUpdateTab1(int SearchKind,QString SearchInfo,QString,QString);
    void SendUpdateTab2(int SearchKind,QString SearchInfo,QString,QString);

private:
    void ReviewUpdate();
    void WorkerUpdate();
    void WorkerInsert();

    void CloseDialog();
    void GetGoods();
    void SetGoods();
    void GetDepot();
    void SetDepot();
    void GetClient();
    void SetClient();

private:
    Ui::dialog *ui;
    QNetworkAccessManager* m_accessManager;
    int CurrentFun;
    QJsonArray recommend;
    int TabIndex;
    QList<QTableWidgetItem*> DATA;
    QJsonArray Goods,Depot,Client;
};

#endif // DAILOG_H
