#include "opcodeonlymessage.h"

using namespace NRMCNetwork;

OpcodeOnlyMessage::OpcodeOnlyMessage ( char* msg, struct sockaddr_in& addr )
{
	if (msg == 0)
		throw exception("Null message was passed");

	this->rawMsg = msg;
	this->addr = addr;
	this->opcode = (int)rawMsg[0];
}

OpcodeOnlyMessage::OpcodeOnlyMessage ( int opcode, struct sockaddr_in& addr )
{
	this->opcode = opcode;
	this->addr = addr;
	this->rawMsg = new char[1];

	rawMsg[0] = (char)opcode;
}

OpcodeOnlyMessage::OpcodeOnlyMessage ( const OpcodeOnlyMessage& msg )
{
	this->opcode = msg.opcode;

	this->rawMsg = new char[1];			// opcode only messages are only 1 byte long
	this->rawMsg[1] = msg.rawMsg[1];

	this->addr = msg.addr;
}

OpcodeOnlyMessage::~OpcodeOnlyMessage (   )
{
	delete[] rawMsg;
	rawMsg = 0;
}

struct sockaddr_in& OpcodeOnlyMessage::getAddress (  ) const
{
	return &addr;
}

char* OpcodeOnlyMessage::getMessage (  ) const
{
	return rawMsg;
}

int OpcodeOnlyMessage::getOpcode (  ) const
{
	return opcode;
}

OpcodeOnlyMessage* OpcodeOnlyMessage::clone (  ) const
{
	return new OpcodeOnlyMessage(this);
}

