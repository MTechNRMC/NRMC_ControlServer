#include "liadrmessage.h"

using namespace NRMCNetwork;

LIADRMessage::LIADRMessage ( char* msg, sockaddr_in& addr )
{
}

LIADRMessage::LIADRMessage ( int opcode, double distance, double angle, sockaddr_in& addr )
{
}

LIADRMessage::LIADRMessage ( const LIADRMessage& msg )
{
}

LIADRMessage::~LIADRMessage (  )
{
}

double LIADRMessage::getDistance (  )
{
}

double LIADRMessage::getAngle (  )
{
}

double LIADRMessage::getScanRate (  )
{
}

int LIADRMessage::getRPM (  )
{
}

int LIADRMessage::getOpcode (  )
{
}

sockaddr_in& LIADRMessage::getAddress (  )
{
}

char* LIADRMessage::getMessage (  )
{
}

