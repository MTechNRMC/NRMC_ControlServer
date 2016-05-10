#include <stdexcept>
#include "motordir16message.h"

using std::invalid_argument;
using namespace NRMCNetwork;

int MotorDir16Message::getSize() const
{
	return size;
}

MotorDir16Message::MotorDir16Message ( char* msg, int size, struct sockaddr_in& addr )
{
	if (size > 2 && msg != 0)
	{
		this->size = size;
		this->rawMsg = msg;

		// translate the message
		data.opcode = msg[0];
		data.motorDir = 0;
		data.motorDir |= msg[1];
		data.motorDir <<= 8;
		data.motorDir |= msg[2];

		this->addr = addr;
	}
	else
		throw invalid_argument("Invalid message size");
}

MotorDir16Message::MotorDir16Message ( int opcode, short motorDir, struct sockaddr_in& addr )
{
	this->data.opcode = (char)opcode;
	this->data.motorDir = motorDir;
	this->addr = addr;	// replace with deep copy late
	this->size = 3;
	this->rawMsg = new char[this->size];

	this->rawMsg[0] = (char)opcode;			// encode the opcode
	this->rawMsg[1] = (char)motorDir >> 8;	// encode the msb
	this->rawMsg[2] = (char)motorDir;		// encode the lsb
}

MotorDir16Message::MotorDir16Message ( const MotorDir16Message& msg )
{
	this->size = msg.size;
	this->data.opcode = msg.data.opcode;
	this->data.motorDir = msg.data.motorDir;
	this->addr = msg.addr;

	this->rawMsg = new char[msg.size];

	for(int i=0;i<msg.size;i++)
		this->rawMsg[i] = msg.rawMsg[i];
}

MotorDir16Message::~MotorDir16Message (  )
{
	delete[] rawMsg;
	rawMsg = 0;
}

struct sockaddr_in MotorDir16Message::getAddress (  ) const
{
	return addr;
}

const char* MotorDir16Message::getMessage (  ) const
{
	return rawMsg;
}

int MotorDir16Message::getOpcode (  ) const
{
	return (int)data.opcode;
}

int MotorDir16Message::getMotorDir (  ) const
{
	return (int)data.motorDir;
}

MotorDir16Message* MotorDir16Message::clone (  ) const
{
	return new MotorDir16Message(*this);
}

