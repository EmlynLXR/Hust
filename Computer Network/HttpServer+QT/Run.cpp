//多线程输出混乱
#pragma once
#include "Server.h"
#include "Config.h"
#include <thread>
void run(int port,string ip,string path)
{
	Server srv;
	srv.threadid = this_thread::get_id();
	if (srv.WinsockStartup() == -1) return;
	if (srv.ServerStartup(port, ip) == -1) return;
	if (srv.ListenStartup() == -1) return;
	if (srv.Loop(path) == -1) return;
}
int main() {
	// 申请存储线程的数组
	std::thread threads[50];
	int thread_num = 0;
	for (int i = 0; i < 2; i++)
	{
		threads[i] = std::thread(run, Config::PORT[i],"127.0.0.1","");
		thread_num++;
	}
	for (int i = 0; i < thread_num; i++)
		threads[i].join();

	// 释放套接字
	WSACleanup();
	return 0;
}
