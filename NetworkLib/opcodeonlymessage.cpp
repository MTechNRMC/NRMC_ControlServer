#include <stdexcept>
#include "opcodeonlymessage.h"

using std::invalid_argument;
using namespace NRMCNetwork;

OpcodeOnlyMessage::OpcodeOnlyMessage ( char* msg, int size, struct sockaddr_in& addr )
{
	if (msg == 0)
		throw invalid_argument("Null message was passed");

	this->size = size;
	this->rawMsg = msg;	// first byte of the message is the opcode
	this->addr = addr;
	this->opcode = (int)rawMsg[0];
}

OpcodeOnlyMessage::OpcodeOnlyMessage ( int opcode, struct sockaddr_in& addr )
{
	this->opcode = opcode;
	this->addr = addr;
	this->size = 1;

	rawMsg = new char[1];
	rawMsg[0] = (char)opcode;
}

OpcodeOnlyMessage::OpcodeOnlyMessage ( const OpcodeOnlyMessage& msg )
{
	size = msg.size;
	addr = msg.addr;
	opcode = msg.opcode;

	rawMsg = new char[msg.size];

	for(int i=0;i<msg.size;i++)
		rawMsg[i] = msg.rawMsg[i];
}

OpcodeOnlyMessage::~OpcodeOnlyMessage (   )
{
	delete[] rawMsg;
	rawMsg = 0;
}

int OpcodeOnlyMessage::getSize() const
{
	return size;
}

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

