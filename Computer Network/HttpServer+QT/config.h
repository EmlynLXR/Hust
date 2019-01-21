#pragma once
#include <string>
#include <vector>
#include <winsock2.h>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <thread>
#include <list>
using namespace std;

//保存配置信息
class Config
{
public:
    static const int MAXCONNECTION;		//最大连接数
    static const int BUFFERLENGTH;		//缓冲区大小
    static const string SERVERADDRESS;  //服务器地址
    static const int PORT;				//服务器端口
    static const string PATH;
    static const u_long BLOCKMODE;			//SOCKET阻塞模式
    static vector<string> split(const string& str, const string& delim);
    static void recvBuf_remsg(string http, string &head, string &msg, string path);
private:
    Config(void);
    ~Config(void);
};
