#ifndef WORKER_H
#define WORKER_H
#include "header.h"
#include "control.h"
#include "dialog.h"
#include "insertbase.h"

#define FunUpdateStorage 0
#define FunUpdateDelivery 1
#define FunDeleteStorage 2
#define FunDeleteDelivery 3
#define FunUpdateInventory 4
#define FunUpdateOutOfStock 5
#define FunUpdateDepot 6
#define FunUpdateGoods 7
#define FunUpdateWorker 8
#define FunUpdateClient 9
#define FunUpdateSupplier 10
#define FunDeleteDepot 11
#define FunDeleteGoods 12
#define FunDeleteWorker 13
#define FunDeleteClient 14
#define FunDeleteSupplier 15
#define FunUpdateLackOfGoods 16


namespace Ui {
class Worker;
}
class Worker: public QDialog
{
    Q_OBJECT

public:
    explicit Worker(QWidget *parent = nullptr);
    ~Worker();

private slots:
    void finishedSlot(QNetworkReply *reply);

    void on_Modify_clicked();

    void on_Insert_clicked();

    void on_Delete_clicked();

    void on_Search_clicked();

    void on_SearchKind_currentIndexChanged(int index);

    void on_tabWidget_currentChanged(int index);

signals:
    void SendData(int TabIndex,QList<QTableWidgetItem*> DATA);
    void SendInsert(int TabIndex);
    void SendInsertBase(int TabIndex);
    void SendBaseData(int TabIndex,QList<QTableWidgetItem*> DATA);

private:
    Ui::Worker *ui;
    QNetworkAccessManager* m_accessManager;
    int CurrentFun;
    dialog* DialogPage = new dialog;
    InsertBase* InsertBasePage = new InsertBase;

    QJsonArray recommend;
    QList<int> ColumnCount = {15,15,15,6,7,4,4,6,4,4};
public slots:
    void UpdateStorage(int SearchKind,QString SearchInfo,QString StartTime,QString EndTime);
    void UpdateDelivery(int SearchKind,QString SearchInfo,QString StartTime,QString EndTime);
    void UpdateLackOfGoods(int SearchKind,QString SearchInfo,QString StartTime,QString EndTime);
    void UpdateInventory(int SearchKind,QString SearchInfo);
    void UpdateOutOfStock(int SearchKind,QString SearchInfo);
    void SetStorage();
    void SetDelivery();
    void SetLackOfGoods();
    void SetInventory();
    void SetOutOfStock();

    void UpdateDepot(int SearchKind,QString SearchInfo);
    void UpdateGoods(int SearchKind,QString SearchInfo);
    void UpdateWorker(int SearchKind,QString SearchInfo);
    void UpdateClient(int SearchKind,QString SearchInfo);
    void UpdateSupplier(int SearchKind,QString SearchInfo);
    void SetDepotInfo();
    void SetGoodsInfo();
    void SetWorkerInfo();
    void SetClientInfo();
    void SetSupplierInfo();
};

#endif // WORKER_H
