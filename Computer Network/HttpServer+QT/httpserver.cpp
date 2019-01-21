#include "httpserver.h"
#include "ui_httpserver.h"
#include "winsockenv.h"
#include "config.h"
#include <QString>
#include <winsock.h>
#include <winsock2.h>
#include <QObject>
using namespace std;

void HttpServer::run(int port,string ip,string path)
{
    Server srv = *(new Server());
    //connect(&srv,&Server::send2ui, this->ui->messages, &QTextBrowser::append);

    srv.threadid = this_thread::get_id();
    if (srv.WinsockStartup() == -1) return;
    if (srv.ServerStartup(port, ip) == -1) return;
    if (srv.ListenStartup() == -1) return;
    serverlist->insert(serverlist->end(),srv);
    serveropen=1;
    if (srv.Loop(path) == -1) return;
    return;
}

HttpServer::HttpServer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::HttpServer)
{
    ui->setupUi(this);

    ui->ip_edit->setText(Config::SERVERADDRESS.c_str());
    ui->port_edit->setText("80");
    ui->path_edit->setText(Config::PATH.c_str());
    thread_num=0;
    serveropen=0;
    ui->messages->moveCursor(QTextCursor::End);
    ui->messages->setStyleSheet("QTextBrowser{background-color:rgb(255,255,255);"
                               "border:0px solid transparent;"
                               "border-top:0px solid rgb(230,230,230);"
                               "padding-left:10px;}");
}

HttpServer::~HttpServer()
{
    if(ui!=nullptr)
    {
       delete ui;
       ui=nullptr;
    }
    if (this->serverlist != nullptr) {
        for (list<Server>::iterator itor = this->serverlist->begin(); itor != this->serverlist->end(); itor++)
        {
            closesocket(itor->srvSocket);
            itor->~Server();
        }
        delete this->serverlist;
        this->serverlist = nullptr;
    }
}

void HttpServer::on_connect_button_clicked()
{
    if(serveropen==0)
    {
        int n;
        this->serverlist = new list<Server>();
        QString Qport=ui->port_edit->text();
        int port[10];
        vector<string> ports = Config::split(Qport.toStdString(), " ");
        if(ports.size()==0)
        {
            port[0]=Config::PORT;
            n = 1;
        }
        else
        {
            for (int i = 0; i < ports.size(); i++)
            {
                port[i] = atoi(ports[i].c_str());
            }
            n = ports.size();
        }

        QString Qip=ui->ip_edit->text();
        string ip;
        if(!Qip.isEmpty())
            ip=Qip.toStdString();
        else
            ip=Config::SERVERADDRESS;
        QString Qpath=ui->path_edit->text();
        string path;
        if(!Qpath.isEmpty())
            path=Qpath.toStdString();
        else
            path=Config::PATH;

        ui->messages->append("server opened.\n");
        for (int i = 0; i < n; i++)
        {
            threads[i] = std::thread(&HttpServer::run, this,port[i],ip,path);
            thread_num++;
        }
        for (int i = 0; i < thread_num; i++)
            threads[i].detach();
    }
    else
        ui->messages->append("server is opened already.\n");
}
void HttpServer::on_change_button_clicked(){}
void HttpServer::on_close_button_clicked()
{
    if(serveropen==1)
    {
        if (this->serverlist != nullptr) {
            for (list<Server>::iterator itor = this->serverlist->begin(); itor != this->serverlist->end(); itor++)
            {
                closesocket(itor->srvSocket);
                //itor->srvSocket=NULL;
                itor->~Server();

            }
            //delete this->serverlist;
            this->serverlist = nullptr;
        }
        thread_num=0;
        ui->messages->append("server closed.\n");
        serveropen=0;
    }
    else
        ui->messages->append("no server is open.\n");
    return;
}
