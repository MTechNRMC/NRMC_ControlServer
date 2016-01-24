#include "motordir16message.h"

MotorDir16Message::MotorDir16Message ( char* msg, struct sockaddr_in& addr )
{
}

MotorDir16Message::MotorDir16Message ( int opcode, short motorDir, struct sockaddr_in& addr )
{
}

MotorDir16Message::MotorDir16Message ( const MotorDir16Message& msg )
{
}

MotorDir16Message::~MotorDir16Message (  )
{
}

struct sockaddr_in& MotorDir16Message::getAddress (  ) const
{
}

char* MotorDir16Message::getMessage (  ) const
{
}

int MotorDir16Message::getOpcode (  ) const
{
}

int MotorDir16Message::getMotorDir (  ) const
{
}

OpcodeOnlyMessage* MotorDir16Message::clone (  ) const
{
}

