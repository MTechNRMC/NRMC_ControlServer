#include <stdexcept>
#include "motordir16message.h"

using std::invalid_argument;
using namespace NRMCNetwork;

MotorDir16Message::MotorDir16Message ( char* msg, struct sockaddr_in& addr )
{
	if (sizeof(msg) > 2)
	{
		for (int x = 0; x < 3; x++)
			this->msg.rawMsg[x] = msg[x];

		this->addr = addr;
	}
	else
		throw invalid_argument("Invalid message size");
}

MotorDir16Message::MotorDir16Message ( int opcode, short motorDir, struct sockaddr_in& addr )
{
	this->msg.data.opcode = (char)opcode;
	this->msg.data.motorDir = motorDir;
	this->addr = addr;	// replace with deep copy late
}

MotorDir16Message::MotorDir16Message ( const MotorDir16Message& msg )
{
	this->msg.data.opcode = msg.msg.data.opcode;
	this->msg.data.motorDir = msg.msg.data.motorDir;
	addr = msg.addr;	// replace with deep copy later
}

MotorDir16Message::~MotorDir16Message (  )
{}

struct sockaddr_in MotorDir16Message::getAddress (  ) const
{
	return addr;
}

const char* MotorDir16Message::getMessage (  ) const
{
	return msg.rawMsg;
}

int MotorDir16Message::getOpcode (  ) const
{
	return (int)msg.data.opcode;
}

int MotorDir16Message::getMotorDir (  ) const
{
	return msg.data.motorDir;
}

MotorDir16Message* MotorDir16Message::clone (  ) const
{
	return new MotorDir16Message(*this);
}

