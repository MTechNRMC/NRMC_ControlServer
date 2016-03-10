#include <stdexcept>
#include "opcodeonlymessage.h"

using std::invalid_argument;
using namespace NRMCNetwork;

OpcodeOnlyMessage::OpcodeOnlyMessage ( char* msg, struct sockaddr_in& addr )
{
	if (msg == 0)
		throw invalid_argument("Null message was passed");

	this->rawMsg[0] = msg[1];	// first byte of the message is the opcode
	this->addr = addr;
	this->opcode = (int)rawMsg[0];
}

OpcodeOnlyMessage::OpcodeOnlyMessage ( int opcode, struct sockaddr_in& addr )
{
	this->opcode = opcode;
	this->addr = addr;

	rawMsg[0] = (char)opcode;
}

OpcodeOnlyMessage::OpcodeOnlyMessage ( const OpcodeOnlyMessage& msg )
{
	this->opcode = msg.opcode;

	this->rawMsg[0] = msg.rawMsg[0];

	this->addr = msg.addr;
}

OpcodeOnlyMessage::~OpcodeOnlyMessage (   )
{}

struct sockaddr_in OpcodeOnlyMessage::getAddress (  ) const
{
	return addr;
}

const char* OpcodeOnlyMessage::getMessage (  ) const
{
	return rawMsg;
}

int OpcodeOnlyMessage::getOpcode (  ) const
{
	return opcode;
}

OpcodeOnlyMessage* OpcodeOnlyMessage::clone (  ) const
{
	return new OpcodeOnlyMessage(*this);
}

