#ifndef INSERTBASE_H
#define INSERTBASE_H

#include "header.h"
#include "control.h"
#define FunInsert 0
namespace Ui {
class InsertBase;
}
class InsertBase: public QDialog
{
    Q_OBJECT
public:
    explicit InsertBase(QWidget *parent = nullptr);
    ~InsertBase();

private slots:
    void finishedSlot(QNetworkReply *reply);
    void on_CancelBtn_clicked();
    void on_ApplyBtn_clicked();

public slots:
    void ReceiveData(int TabIndex,QList<QTableWidgetItem*> DATA);
    void ReceiveInsert(int TabIndex);
signals:
    void SendUpdateDepot(int SearchKind,QString SearchInfo);
    void SendUpdateGoods(int SearchKind,QString SearchInfo);
    void SendUpdateClient(int SearchKind,QString SearchInfo);
    void SendUpdateSupplier(int SearchKind,QString SearchInfo);
signals:
//    void SendUpdateTab1(int SearchKind,QString SearchInfo,QString,QString);
//    void SendUpdateTab2(int SearchKind,QString SearchInfo,QString,QString);

private:
    void CloseDialog();
    void Insert();
    void Modify();

private:
    Ui::InsertBase *ui;
    QNetworkAccessManager* m_accessManager;
    int CurrentFun;
    QJsonArray recommend;
    int TabIndex;
    QList<QTableWidgetItem*> DATA;
};

#endif // INSERTBASE_H
