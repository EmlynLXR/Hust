#include "server.h"
#include "winsockenv.h"
#include <algorithm>
#include <QString>
#include "httpserver.h"
#include "ui_httpserver.h"


Server::Server(void)
{
    this->recvBuf = new char[Config::BUFFERLENGTH]; //初始化接受缓冲区
    memset(this->recvBuf, '\0', Config::BUFFERLENGTH);

    this->rcvedMessages = new list<string>();
    this->sessions = new list<SOCKET>();
    this->closedSessions = new list<SOCKET>();
}
Server::~Server(void)
{
    //释放接受缓冲区
    if (this->recvBuf != NULL) {
        delete this->recvBuf;
        this->recvBuf = NULL;
    }


    //关闭server socket
    if (this->srvSocket != NULL) {
        closesocket(this->srvSocket);
        this->srvSocket = NULL;
    }

    //关闭所有会话socket并释放会话队列
    if (this->sessions != NULL) {
        for (list<SOCKET>::iterator itor = this->sessions->begin(); itor != this->sessions->end(); itor++)
            closesocket(*itor); //关闭会话
        delete this->sessions;  //释放队列
        this->sessions = NULL;
    }
    //释放失效会话队列
    if (this->closedSessions != NULL) {
        for (list<SOCKET>::iterator itor = this->closedSessions->begin(); itor != this->closedSessions->end(); itor++)
            closesocket(*itor); //关闭会话
        delete this->closedSessions;//释放队列
        this->closedSessions = NULL;
    }

    //释放接受消息队列
    if (this->rcvedMessages != NULL) {
        this->rcvedMessages->clear(); //清除消息队列中的消息
        delete this->rcvedMessages;	// 释放消息队列
        this->rcvedMessages = NULL;
    }


    WSACleanup(); //清理winsock 运行环境
}

//初始化Winsock
int Server::WinsockStartup() {
    if (WinsockEnv::Startup() == -1) return -1;	//初始化Winsock
    return 0;
}

//初始化Server，包括创建sockect，绑定到IP和PORT
int Server::ServerStartup(int PORT,string SERVERADDRESS) {
    //创建 TCP socket
    int id;
    this->srvSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->srvSocket == INVALID_SOCKET) {
        qDebug() << "Server socket creare error ! [WSAGetLastError :" << id << "]";
        WSACleanup();
        return -1;
    }
   qDebug()<< "Server socket create ok!\n";

    //设置服务器IP地址和端口号
    this->srvAddr.sin_family = AF_INET;
    this->srvAddr.sin_port = htons(u_short(PORT));
    this->srvAddr.sin_addr.S_un.S_addr = inet_addr(SERVERADDRESS.c_str()); //这是另外一种设置IP地址的方法

    //绑定 socket to Server's IP and port
    int rtn = ::bind(this->srvSocket, (LPSOCKADDR)&(this->srvAddr), sizeof(this->srvAddr));
    if (rtn == SOCKET_ERROR) {
        qDebug()<< "Server socket bind error! [WSAGetLastError :" << id << "]";
        closesocket(this->srvSocket);
        WSACleanup();
        return -1;
    }
    qDebug() << "Server socket bind ok!\n";
    return 0;
}

//开始监听,等待客户的连接请求
int Server::ListenStartup() {
    int rtn = listen(this->srvSocket, Config::MAXCONNECTION);
    if (rtn == SOCKET_ERROR) {
        qDebug("Server socket listen error ! ");
        closesocket(this->srvSocket);
        WSACleanup();
        return -1;
    }
    qDebug("Server socket listen ok!\n");
    return 0;
}

//将收到的客户端消息保存到消息队列
void Server::AddRecvMessage(string str) {
    if (!str.empty())
        this->rcvedMessages->insert(this->rcvedMessages->end(), str);

}

//将新的会话SOCKET加入队列
void Server::AddSession(SOCKET session) {
    if (session != INVALID_SOCKET) {
        this->sessions->insert(this->sessions->end(), session);
    }
}

//将失效的会话SOCKET加入队列
void Server::AddClosedSession(SOCKET session) {
    if (session != INVALID_SOCKET) {
        this->closedSessions->insert(this->closedSessions->end(), session);
    }
}

//将失效的SOCKET从会话SOCKET队列删除
void Server::RemoveClosedSession(SOCKET closedSession) {
    if (closedSession != INVALID_SOCKET) {
        list<SOCKET>::iterator itor = find(this->sessions->begin(), this->sessions->end(), closedSession);
        if (itor != this->sessions->end())
            this->sessions->erase(itor);
    }
}

//将失效的SOCKET从会话SOCKET队列删除
void Server::RemoveClosedSession() {
    for (list<SOCKET>::iterator itor = this->closedSessions->begin(); itor != this->closedSessions->end(); itor++) {
        this->RemoveClosedSession(*itor);
    }
}

//从SOCKET s接受消息
void Server::recvMessage(SOCKET socket,string PATH) {
    sockaddr_in clientAddr = GetClientAddress(socket);

    int receivedBytes = recv(socket, this->recvBuf, Config::BUFFERLENGTH, 0);
    if (receivedBytes == SOCKET_ERROR || receivedBytes == 0) {//接受数据错误，把产生错误的会话socekt加入sessionsClosed队列
        this->AddClosedSession(socket);
        qDebug() <<inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << " to "
            << inet_ntoa(this->srvAddr.sin_addr) << ":" << ntohs(this->srvAddr.sin_port) << ": failed to receive data." << endl;
    }
    else {
        recvBuf[receivedBytes] = '\0';
        recvBuf[receivedBytes] = '\0';

        qDebug() << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << " to " <<
            inet_ntoa(this->srvAddr.sin_addr) << ":" << ntohs(this->srvAddr.sin_port)<< recvBuf << endl;
        string remsg = "", head = "";
        Config::recvBuf_remsg(recvBuf, head, remsg,PATH); //处理HTTP请求报文并获得响应报文


        qDebug() << inet_ntoa(this->srvAddr.sin_addr) << ":" << ntohs(this->srvAddr.sin_port) <<
            " to " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << ":" << head.c_str() << endl;
        if (remsg != "")
            this->AddRecvMessage(remsg); //将收到的消息加入到消息队列
        memset(this->recvBuf, '\0', Config::BUFFERLENGTH);//清除接受缓冲区
    }
}

//向SOCKET s发送消息
void Server::sendMessage(SOCKET socket, string msg) {
    int rtn = send(socket, msg.c_str(), msg.size(), 0);
    if (rtn == SOCKET_ERROR) {//发送数据错误，把产生错误的会话socekt加入sessionsClosed队列

        sockaddr_in clientAddr = GetClientAddress(socket);
        int id = WSAGetLastError();
        qDebug() << "[WSAGetLastError:" << id << "]"<< "Send to client failed."
            << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << " leave." << endl;
        this->AddClosedSession(socket);
    }
}

//向其他客户转发信息
void Server::ForwardMessage()
{
    if (this->numOfSocketSignaled > 0)
    {
        if (!this->rcvedMessages->empty())
        {//如果消息队列不为空
            for (list<string>::iterator msgItor = this->rcvedMessages->begin(); msgItor != this->rcvedMessages->end(); msgItor++)
            {//对消息队列中的每一条消息
                for (list<SOCKET>::iterator sockItor = this->sessions->begin(); sockItor != this->sessions->end(); sockItor++)
                {//对会话socket队列中的每个socket
                    if (FD_ISSET(*sockItor, &this->wfds)) {
                        this->sendMessage(*sockItor, *msgItor);
                    }
                }
            }
        }
        this->rcvedMessages->clear(); //向其他客户转发消息后，清除消息队列
    }
}


int Server::AcceptRequestionFromClient() {
    sockaddr_in clientAddr;		//客户端IP地址
    int nAddrLen = sizeof(clientAddr);
    u_long blockMode = Config::BLOCKMODE;//将session socket设为非阻塞模式以监听客户连接请求

    //检查srvSocket是否收到用户连接请求
    if (this->numOfSocketSignaled > 0) {
        if (FD_ISSET(this->srvSocket, &rfds)) {  //有客户连接请求到来
            this->numOfSocketSignaled--;

            //产生会话socket
            SOCKET newSession = accept(this->srvSocket, (LPSOCKADDR)&(clientAddr), &nAddrLen);
            if (newSession == INVALID_SOCKET) {
                qDebug() << "Server accept connection request error!\n";
                return -1;
            }
            qDebug() << "New client connection request arrived and new session created\n";

                        //将新的会话socket设为非阻塞模式，
            if (ioctlsocket(newSession, FIONBIO, &blockMode) == SOCKET_ERROR) {
                qDebug() << "ioctlsocket() for new session failed with error!\n";
                return -1;
            }

            //将新的session加入会话队列
            this->AddSession(newSession);

            sockaddr_in clientAddr;
            int nameLen, rtn;
            nameLen = sizeof(clientAddr);
            rtn = getpeername(newSession, (LPSOCKADDR)&clientAddr, &nameLen);

            qDebug() << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << " connect to "
                << inet_ntoa(this->srvAddr.sin_addr) << ":" << ntohs(this->srvAddr.sin_port) << "!" << endl;
        }
    }
    return 0;
}

void Server::ReceieveMessageFromClients(string PATH) {
    if (this->numOfSocketSignaled > 0) {
        //遍历会话列表中的所有socket，检查是否有数据到来
        for (list<SOCKET>::iterator itor = this->sessions->begin(); itor != this->sessions->end(); itor++) {
            if (FD_ISSET(*itor, &rfds)) {  //某会话socket有数据到来
                //接受数据
                this->recvMessage(*itor,PATH);
            }
        }//end for
    }
}

//得到客户端IP地址
sockaddr_in  Server::GetClientAddress(SOCKET s) {
    sockaddr_in clientAddr;
    int nameLen, rtn;

    nameLen = sizeof(clientAddr);
    rtn = getpeername(s, (LPSOCKADDR)&clientAddr, &nameLen);
    if (rtn != SOCKET_ERROR) {
        return clientAddr;
    }
}

//接受客户端发来的请求和数据并转发
int Server::Loop(string PATH) {
    u_long blockMode = Config::BLOCKMODE;//将srvSock设为非阻塞模式以监听客户连接请求
    int rtn;

    if ((rtn = ioctlsocket(this->srvSocket, FIONBIO, &blockMode) == SOCKET_ERROR)) { //FIONBIO：允许或禁止套接口s的非阻塞模式。
        int id = WSAGetLastError();
        qDebug() << "[WSAGetLastError:" << id << "]" << "ioctlsocket() failed with error!\n";
        return -1;
    }
    qDebug() << "ioctlsocket() for server socket ok!Waiting for client connection and data\n";
    while (true) { //等待客户的连接请求
        //首先从会话SOCKET队列中删除掉已经关闭的会话socket
        this->RemoveClosedSession();

        //Prepare the read and write socket sets for network I/O notification.
        FD_ZERO(&this->rfds);
        FD_ZERO(&this->wfds);

        //把srvSocket加入到rfds，等待用户连接请求
        FD_SET(this->srvSocket, &this->rfds);

        //把当前的会话socket加入到rfds,等待用户数据的到来;加到wfds，等待socket可发送数据
        for (list<SOCKET>::iterator itor = this->sessions->begin(); itor != this->sessions->end(); itor++) {
            FD_SET(*itor, &rfds);
            FD_SET(*itor, &wfds);
        }

        //等待用户连接请求或用户数据到来或会话socke可发送数据
        if ((this->numOfSocketSignaled = select(0, &this->rfds, &this->wfds, NULL, NULL)) == SOCKET_ERROR) { //select函数返回有可读或可写的socket的总数，保存在rtn里.最后一个参数设定等待时间，如为NULL则为阻塞模式
            int id = WSAGetLastError();
            qDebug() << "[WSAGetLastError:" << id << "]" << "select() failed with error!\n";
            return -1;
        }


        //当程序运行到这里，意味着有用户连接请求到来，或有用户数据到来，或有会话socket可以发送数据

        //首先检查是否有客户请求连接到来
        if (this->AcceptRequestionFromClient() != 0) return -1;

        //然后向客户端发送数据
        this->ForwardMessage();

        //最后接受客户端发来的数据
        this->ReceieveMessageFromClients(PATH);
    }

    return 0;
}
