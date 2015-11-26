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

struct sockaddr_in& OpcodeOnlyMessage::getAddress const (  )
{
}

char* OpcodeOnlyMessage::getMessage const (  )
{
}

int OpcodeOnlyMessage::getOpcode const (  )
{
}

OpcodeOnlyMessage* OpcodeOnlyMessage::clone const (  )
{
}

