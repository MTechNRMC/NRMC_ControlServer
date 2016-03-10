#include <stdexcept>
#include "setspeedbytemessage.h"

using std::invalid_argument;
using namespace NRMCNetwork;

SetSpeedByteMessage::SetSpeedByteMessage ( char* msg, struct sockaddr_in& addr )
{
	if (sizeof(msg) > 3)
	{
		for (int x = 0; x < 4; x++)
			this->msg.rawMsg[x] = msg[x];

		this->addr = addr;
	}
	else
		throw invalid_argument("Invalid message size");
}

SetSpeedByteMessage::SetSpeedByteMessage ( int opcode, int motorNum, int speed, struct sockaddr_in& addr )
{
	this->msg.data.opcode = (char)opcode;
	this->msg.data.motorNum = (unsigned short)motorNum;
	this->msg.data.speed = speed;
}

SetSpeedByteMessage::SetSpeedByteMessage ( const SetSpeedByteMessage& msg )
{
	this->msg.data = msg.msg.data;
	this->addr = msg.addr;
}

SetSpeedByteMessage::~SetSpeedByteMessage (   )
{}

sockaddr_in SetSpeedByteMessage::getAddress (  ) const
{
	return addr;
}

const char* SetSpeedByteMessage::getMessage (  ) const
{
	return msg.rawMsg;
}

int SetSpeedByteMessage::getOpcode (  ) const
{
	return (int)msg.data.opcode;
}

int SetSpeedByteMessage::getMotorNum (  ) const
{
	return (int)msg.data.motorNum;
}

char SetSpeedByteMessage::getSpeed (  ) const
{
	return msg.data.speed;
}

SetSpeedByteMessage* SetSpeedByteMessage::clone (  ) const
{
	return new SetSpeedByteMessage(*this);
}

