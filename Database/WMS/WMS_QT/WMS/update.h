#ifndef UPDATE_H
#define UPDATE_H

#include "header.h"
#include "control.h"

#define FunUpdateGoodsName 0

class update :public QObject
{
public:
    update();
    ~update();
private:
    QNetworkAccessManager* m_accessManager;
    int CurrentFun;
    QJsonArray recommend;

    void SetGoodsName();

private slots:
    void UpdateGoodsName();
    void finishedSlot(QNetworkReply *reply);
};

#endif // UPDATE_H
