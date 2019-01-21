#include "stdafx.h"
#include "Global.h"
#include "SRSender.h"


SRSender::SRSender():nextseqnum(0), waitingState(false), N(4), base(0), size(8)
{
}


SRSender::~SRSender()
{
}
//需进行确定！！！！！！！
bool SRSender::getWaitingState() {
	if ((this->nextseqnum - this->base + this->size) % this->size == this->N)
		this->waitingState = true;
	else
		this->waitingState = false;
	return waitingState;
}

void SRSender::print_window() {
	std::cout << "输出窗口内容：\n";
	for (vector<Packet>::iterator iter = sndpkt.begin(); iter != sndpkt.end(); iter++)
	{
		pUtils->printPacket("窗口内容：", (*iter));
	}
	std::cout << "\n";
}

bool SRSender::send(Message &message) {
	if (this->getWaitingState()) { //发送方处于等待确认状态
		return false;
	}
	cout << endl << endl;
	Packet packet;
	packet.acknum = -1;//忽略该字段
	packet.seqnum = this->nextseqnum;
	packet.checksum = 0;
	memcpy(packet.payload, message.data, sizeof(message.data));
	packet.checksum = pUtils->calculateCheckSum(packet);

	pUtils->printPacket("发送方发送报文", packet);
	if(this->base==this->nextseqnum)
		pns->startTimer(SENDER, Configuration::TIME_OUT, this->base);//启动发送方第一个packet的定时器
	pns->sendToNetworkLayer(RECEIVER, packet);								//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方

	sndpkt.push_back(packet);
	this->nextseqnum = (this->nextseqnum + 1) % this->size;
	print_window();
	return true;
}

bool  SRSender::between(int acknum)
{
	if (this->base <= this->nextseqnum)
		return acknum >= this->base && acknum < this->nextseqnum;
	else
		return acknum >= this->base || acknum < this->nextseqnum;
}

void SRSender::receive(Packet &ackPkt) {
	cout << endl << endl;
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	cout << "sender::base::" << this->base << endl;
	cout << "sender::receive::" << ackPkt.acknum << endl;
	cout << "checkSum::" << checkSum << endl;
	cout << "checkSum::" << ackPkt.checksum << endl;
	//如果校验和正确，并且确认序号=发送方已发送并等待确认的数据包序号
	if (checkSum == ackPkt.checksum) 
	{	
		
		if (between(ackPkt.acknum))
		{
			pns->stopTimer(SENDER, this->base);
			vector< Packet>::iterator iter = sndpkt.begin();
			for (; iter != sndpkt.end(); iter++)
			{
				if ((*iter).seqnum == ackPkt.acknum)
				{
					sndpkt.erase(iter);
					break;
				}
			}
			if (this->base == ackPkt.acknum)
			{
				pUtils->printPacket("发送方正确收到确认", ackPkt);


				this->base = (this->base + 1) % this->size;

				if (!acklist.empty())
				{
					vector< Packet>::iterator iter = acklist.begin();
					cout << "iter->second.acknum::" << (*iter).acknum << endl;
					cout << "sender::base::" << this->base << endl;
					if ((*iter).acknum == this->base)
					{
						cout << "确认之前的一些数据" << endl;
						while (iter != acklist.end())
						{
							if ((*iter).acknum != this->base)
							{
								cout << "之后的数据不是相邻数据之后再传送" << endl;
								break;
							}

							pUtils->printPacket("发送方同时确认", (*iter));
							this->base = (this->base + 1) % this->size;
							iter++;

						}
						if (iter != acklist.begin())
							acklist.erase(acklist.begin(), iter);
					}

				}	
			}
			else
			{
				pUtils->printPacket("发送方正确收到确认并存入缓冲区", ackPkt);
				vector< Packet>::iterator iter = find(acklist.begin(),acklist.end(),ackPkt);
				if (iter == acklist.end())
					acklist.push_back(ackPkt);
			}

			if (this->base != this->nextseqnum)
				pns->startTimer(SENDER, Configuration::TIME_OUT, this->base);
		}
		else
			pUtils->printPacket("该ack已被接受过！", ackPkt);

	}
	else
		pUtils->printPacket("发送方没有正确收到接收方的ACK报文,数据校验错误", ackPkt);
	print_window();
}

void SRSender::timeoutHandler(int seqNum) {
	//唯一一个定时器,无需考虑seqNum
	cout << endl << endl;
	cout << "timeout::" << seqNum << endl;

	vector< Packet >::iterator iter;
	for (iter = sndpkt.begin(); iter != sndpkt.end(); iter++)
	{
		if (iter->seqnum == seqNum)
		{
			pUtils->printPacket("发送方定时器时间到，重发传输超时的报文", (*iter));
			pns->stopTimer(SENDER, seqNum);										//首先关闭定时器
			pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//重新启动发送方定时器
			pns->sendToNetworkLayer(RECEIVER, (*iter));			//重新发送数据包
		}
	}
	print_window();
}