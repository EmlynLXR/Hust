#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QMainWindow>
#include "config.h"
#include "server.h"

#include <QThread>

namespace Ui {
class HttpServer;
}

class HttpServer : public QMainWindow
{
    Q_OBJECT
public:
    explicit HttpServer(QWidget *parent = nullptr);
    ~HttpServer();
    void run(int port,string ip,string path);
    std::thread threads[50];//线程队列
    list<Server> *serverlist;
    int thread_num;//线程数目
    bool serveropen;
private slots:
    void on_connect_button_clicked();

    void on_change_button_clicked();

    void on_close_button_clicked();

private:
    Ui::HttpServer *ui;
};

#endif // HTTPSERVER_H
