#include "opcodeonlymessage.h"

using namespace NRMCNetwork;

OpcodeOnlyMessage::OpcodeOnlyMessage ( char* msg, struct sockaddr_in& addr )
{
}

OpcodeOnlyMessage::OpcodeOnlyMessage ( int opcode, struct sockaddr_in& addr )
{
}

OpcodeOnlyMessage::OpcodeOnlyMessage ( const OpcodeOnlyMessage& msg )
{
}

OpcodeOnlyMessage::~OpcodeOnlyMessage (   )
{
}

struct sockaddr_in& OpcodeOnlyMessage::getAddress (  ) const
{
	throw NotImplementedException;
}

char* OpcodeOnlyMessage::getMessage (  ) const
{
	throw NotImplementedException;
}

int OpcodeOnlyMessage::getOpcode (  ) const
{
	throw NotImplementedException;
}

OpcodeOnlyMessage* OpcodeOnlyMessage::clone (  ) const
{
	throw NotImplementedException;
}

