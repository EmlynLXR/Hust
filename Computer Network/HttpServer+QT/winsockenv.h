#pragma once
#include "ui_httpserver.h"
class WinsockEnv
{
private:
	WinsockEnv(void);
	~WinsockEnv(void);
public:
    static int Startup();
};
