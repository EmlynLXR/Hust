#include "stdafx.h"
#include "Global.h"
#include "SRReceiver.h"


SRReceiver::SRReceiver():size(8),N(4),base(0)
{
	AckPkt.acknum = -1; //初始状态下，上次发送的确认包的确认序号为-1，使得当第一个接受的数据包出错时该确认报文的确认号为-1
	AckPkt.checksum = 0;
	AckPkt.seqnum = -1;	//忽略该字段
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		AckPkt.payload[i] = '.';
	}
	AckPkt.checksum = pUtils->calculateCheckSum(AckPkt);
}


SRReceiver::~SRReceiver()
{
}

bool SRReceiver::between(int acknum)
{
	int nextseqnum = (this->base + 4) % this->size;
	if (this->base <= nextseqnum)
		return acknum >= this->base && acknum < nextseqnum;
	else
		return acknum >= this->base || acknum < nextseqnum;
}

void SRReceiver::receive(Packet &packet) {
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(packet);
	cout << endl << endl;
	cout << "receiver::base::" << this->base << endl;
	cout << "receiver::packet.seqnum::" << packet.seqnum << endl;
	cout << "checkSum::" << checkSum << endl;
	cout << "checkSum::" << packet.checksum << endl;
	//如果校验和正确，同时收到报文的序号等于接收方期待收到的报文序号一致
	if (checkSum == packet.checksum)
	{
		if (this->base != packet.seqnum)
		{
			if (between(packet.seqnum))
			{
				pUtils->printPacket("接收方正确收到发送方的报文,并存入缓冲区", packet);
				vector< Packet >::iterator iter;
				iter = find(buff.begin(), buff.end(), packet);
				if (iter == buff.end())
					buff.push_back(packet);
			}
			else
				pUtils->printPacket("该包裹已接受过", packet);
			AckPkt.acknum = packet.seqnum; //确认序号等于收到的报文序号
			AckPkt.seqnum = 0;
			AckPkt.checksum = 0;
			AckPkt.checksum = pUtils->calculateCheckSum(AckPkt);
			pUtils->printPacket("接收方发送确认报文", AckPkt);
			pns->sendToNetworkLayer(SENDER, AckPkt);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方
		}
		else
		{
			pUtils->printPacket("接收方正确收到发送方的报文", packet);


			//取出Message，向上递交给应用层
			Message msg;
			memcpy(msg.data, packet.payload, sizeof(packet.payload));
			pns->delivertoAppLayer(RECEIVER, msg);
			this->base = (this->base + 1) % this->size;

			if (!buff.empty())
			{
				vector< Packet >::iterator iter = buff.begin();
				cout << "iter->second.seqnum::" << (*iter).seqnum << endl;
				cout << "receiver::base::" << this->base << endl;
				if ((*iter).seqnum == this->base)
				{
					cout << "向上传递之前的一些数据" << endl;
					while (iter != buff.end())
					{
						
						if ((*iter).seqnum != this->base)
						{
							cout << "之后的数据不是相邻数据之后再传送" << endl;
							break;
						}
							
						//取出Message，向上递交给应用层
						Message msg;
						memcpy(msg.data, (*iter).payload, sizeof((*iter).payload));
						pns->delivertoAppLayer(RECEIVER, msg);
						this->base = (this->base + 1) % this->size;

						iter++;

					}
					buff.erase(buff.begin(), iter);
				}

			}


			AckPkt.acknum = packet.seqnum; //确认序号等于收到的报文序号
			AckPkt.seqnum = 0;
			AckPkt.checksum = 0;
			AckPkt.checksum = pUtils->calculateCheckSum(AckPkt);
			pUtils->printPacket("接收方发送确认报文", AckPkt);
			pns->sendToNetworkLayer(SENDER, AckPkt);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方

		}

	}
	else {
		if (checkSum != packet.checksum) {
			pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
		}
		else {
			pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号不对", packet);
		}
	}

}
