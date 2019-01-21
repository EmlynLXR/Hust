#ifndef STOP_WAIT_RDT_SENDER_H
#define STOP_WAIT_RDT_SENDER_H
#include "RdtSender.h"
#include <list>
#include <vector>
class SRSender :public RdtSender
{
private:
	int nextseqnum;	// ��һ��������� 
	bool waitingState;				// �Ƿ��ڵȴ�Ack��״̬
	Packet packetWaitingAck;		//�ѷ��Ͳ��ȴ�Ack�����ݰ�
	int base;
	const int N;
	const int size;
	vector< Packet> sndpkt;
	vector< Packet> acklist;

public:

	bool getWaitingState();
	bool send(Message &message);						//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(Packet &ackPkt);						//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);					//Timeout handler������NetworkServiceSimulator����

public:
	SRSender();
	virtual ~SRSender();
	bool  between(int num);
	void print_window();
};

#endif
