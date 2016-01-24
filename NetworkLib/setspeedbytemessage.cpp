#include "SetSpeedByteMessage.h"

using namespace NRMCNetwork;

SetSpeedByteMessage::SetSpeedByteMessage ( char* msg, struct sockaddr_in& addr )
{
}

SetSpeedByteMessage::SetSpeedByteMessage ( int opcode, struct sockaddr_in& addr )
{
}

SetSpeedByteMessage::SetSpeedByteMessage ( const SetSpeedByteMessage& msg )
{
}

SetSpeedByteMessage::~SetSpeedByteMessage (   )
{
}

struct sockaddr_in& SetSpeedByteMessage::getAddress (  ) const
{
	throw NotImplementedException;
}

char* SetSpeedByteMessage::getMessage (  ) const
{
	throw NotImplementedException;
}

int SetSpeedByteMessage::getOpcode (  ) const
{
	throw NotImplementedException;
}

unsigned short SetSpeedByteMessage::getMotorNum (  ) const
{
	
}

char SetSpeedByteMessage::getSpeed (  ) const
{
	
}

SetSpeedByteMessage* SetSpeedByteMessage::clone (  ) const
{
	throw NotImplementedException;
}

