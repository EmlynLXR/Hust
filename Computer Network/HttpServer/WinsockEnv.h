#pragma once
#include<thread>
class WinsockEnv
{
private:
	WinsockEnv(void);
	~WinsockEnv(void);
public:
	static int Startup(std::thread::id threadid);
};
