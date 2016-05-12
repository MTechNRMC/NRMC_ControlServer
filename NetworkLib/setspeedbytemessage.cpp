#include <stdexcept>
#include "setspeedbytemessage.h"

using std::invalid_argument;
using namespace NRMCNetwork;

int SetSpeedByteMessage::getSize() const
{
	return size;
}

SetSpeedByteMessage::SetSpeedByteMessage ( char* msg, int size, struct sockaddr_in& addr )
{
	if (size > 3 && msg != 0)
	{
		this->size = size;
		this->rawMsg = msg;

		// translate the message
		data.opcode = msg[0];
		data.motorNum = 0;
		data.motorNum |= msg[1];
		data.motorNum <<= 8;
		data.motorNum |= msg[2];
		data.speed = msg[3];

		this->addr = addr;
	}
	else
		throw invalid_argument("Invalid message size");
}

SetSpeedByteMessage::SetSpeedByteMessage ( int opcode, int motorNum, int speed, struct sockaddr_in& addr )
{
	this->data.opcode = (char)opcode;
	this->data.motorNum = (unsigned short)motorNum;
	this->data.speed = speed;
	this->size = 4;

	this->rawMsg = new char[this->size];

	this->rawMsg[0] = (char)opcode;			// encode the opcode
	this->rawMsg[1] = (char)motorNum >> 8;	// encode the msb
	this->rawMsg[2] = (char)motorNum;		// encode the lsb
	this->rawMsg[3] = (char)speed;			// encode the speed
}

SetSpeedByteMessage::SetSpeedByteMessage ( const SetSpeedByteMessage& msg )
{
	this->data = msg.data;
	this->addr = msg.addr;
	this->size = msg.size;

	this->rawMsg = new char[msg.size];

	for(int i=0;i<msg.size;i++)
		this->rawMsg[i] = msg.rawMsg[i];
}

SetSpeedByteMessage::~SetSpeedByteMessage (   )
{
	delete[] rawMsg;
	rawMsg = 0;
}

sockaddr_in SetSpeedByteMessage::getAddress (  ) const
{
	return addr;
}

const char* SetSpeedByteMessage::getMessage (  ) const
{
	return rawMsg;
}

int SetSpeedByteMessage::getOpcode (  ) const
{
	return (int)data.opcode;
}

int SetSpeedByteMessage::getMotorNum (  ) const
{
	return (int)data.motorNum;
}

char SetSpeedByteMessage::getSpeed (  ) const
{
	return data.speed;
}

SetSpeedByteMessage* SetSpeedByteMessage::clone (  ) const
{
	return new SetSpeedByteMessage(*this);
}

