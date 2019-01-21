#include "stdafx.h"
#include "Global.h"
#include "GBNRdtSender.h"



GBNRdtSender::GBNRdtSender() :nextseqnum(0), waitingState(false),N(4),base(0),size(8)
{
}


GBNRdtSender::~GBNRdtSender()
{
}


void GBNRdtSender::print_window() {
	std::cout << "输出窗口内容：\n";
	for (vector<Packet>::iterator iter = sndpkt.begin(); iter != sndpkt.end(); iter++)
	{
		pUtils->printPacket("窗口内容：", (*iter));
	}
	std::cout << "\n";
}
bool  GBNRdtSender::between(int acknum)
{
	if (this->base <= this->nextseqnum)
		return acknum >= this->base && acknum < this->nextseqnum;
	else
		return acknum >= this->base || acknum < this->nextseqnum;
}

//需进行确定！！！！！！！
bool GBNRdtSender::getWaitingState() {
	if ((this->nextseqnum - this->base + this->size) % this->size == this->N)
		this->waitingState = true;
	else
		this->waitingState = false;
	return waitingState;
}

bool GBNRdtSender::send(Message &message) {
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
	if (this->base == this->nextseqnum)
		pns->startTimer(SENDER, Configuration::TIME_OUT, this->base);//启动发送方第一个packet的定时器
	pns->sendToNetworkLayer(RECEIVER, packet);								//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方

	sndpkt.push_back(packet);
	this->nextseqnum = (this->nextseqnum + 1) % this->size;
	print_window();
	return true;
}

void GBNRdtSender::receive(Packet &ackPkt) {
	cout << endl << endl;
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//如果校验和正确，并且确认序号=发送方已发送并等待确认的数据包序号
	if (checkSum == ackPkt.checksum) {
		cout << "sender::receive::" << ackPkt.acknum << endl;
		pns->stopTimer(SENDER,this->base);

		
		if (between(ackPkt.acknum))
		{
			pUtils->printPacket("发送方正确收到确认", ackPkt);
			this->base = (ackPkt.acknum + 1) % this->size;
			if (!sndpkt.empty())
			{
				vector<Packet>::iterator iter = sndpkt.begin();
				for (; iter != sndpkt.end(); iter++)
				{
					if ((*iter).seqnum == ackPkt.acknum)
					{
						iter++;
						break;
					}
				}
				sndpkt.erase(sndpkt.begin(), iter);
			}
		}
		else
			cout << "该ack已被接受过！" << endl;

		if (this->base != this->nextseqnum)
			pns->startTimer(SENDER, Configuration::TIME_OUT, this->base);
	}
	print_window();
}

void GBNRdtSender::timeoutHandler(int seqNum) {
	//唯一一个定时器,无需考虑seqNum
	cout << endl << endl;
	cout << "timeout::" << seqNum << endl;
	if (this->base != this->nextseqnum)
	{
		pns->stopTimer(SENDER, this->base);
		pns->startTimer(SENDER, Configuration::TIME_OUT, this->base);
		if(!sndpkt.empty())	
			for (vector< Packet >::iterator iter = sndpkt.begin(); iter != sndpkt.end(); iter++)
			{
				pUtils->printPacket("发送方定时器时间到，重发未发送成功的报文", (*iter));
				pns->sendToNetworkLayer(RECEIVER, (*iter));			//重新发送数据包	
			}
	}
	print_window();
}
