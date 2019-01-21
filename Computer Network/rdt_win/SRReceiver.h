#ifndef STOP_WAIT_RDT_RECEIVER_H
#define STOP_WAIT_RDT_RECEIVER_H
#include "RdtReceiver.h"
#include <vector>
class SRReceiver :public RdtReceiver
{
private:
	int base;				   // 期待收到的下一个报文序号
	int expectSequenceNumberRcvd;	
	Packet AckPkt;				//上次发送的确认报文

	const int N;
	const int size;	  
	vector<Packet> buff;


public:
	SRReceiver();
	virtual ~SRReceiver();

public:

	void receive(Packet &packet);	//接收报文，将被NetworkService调用
	bool between(int acknum);
};

#endif

