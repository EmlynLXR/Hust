#ifndef CONTROL_H
#define CONTROL_H

#include "header.h"
class Control:public QObject
{
    Q_OBJECT

public:
    QUrl MyUrl;
    std::string ID,Name,Sex,Tel,PWD;
    int TYPE,Age;
    int CurrentFun;
    Control()
    {
        TYPE=0;
        ID="";
        PWD="";
        Name="";
        Sex="";
        Age=0;
        Tel="";
        CurrentFun=0;
        MyUrl= QUrl("http://127.0.0.1:8888");

    }
    ~Control()
    {
    }
};

#endif // CONTROL_H
