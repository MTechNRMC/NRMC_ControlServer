#include "liadrmessage.h"

using namespace NRMCNetwork;

LIADRMessage::LIADRMessage ( char* msg, sockaddr_in& addr )
{/** UNUSED **/}

LIADRMessage::LIADRMessage ( int opcode, const vector<ScanPoint>& scan, sockaddr_in& addr )
{
	this->opcode = opcode;
	this->scan = scan;
	this->addr = addr;
}

LIADRMessage::LIADRMessage ( const LIADRMessage& msg )
{
	opcode = msg.opcode;
	scan = msg.scan;
	addr = msg.addr;
}

LIADRMessage::~LIADRMessage (  )
{}

vector<ScanPoint>& LIADRMessage::getScan()
{
	return scan;
}

int LIADRMessage::getOpcode (  ) const
{
	return opcode;
}

sockaddr_in LIADRMessage::getAddress (  ) const
{
	return addr;
}

const char* LIADRMessage::getMessage (  ) const
{
	return 0;
}

Message* LIADRMessage::clone(  ) const
{
	return new LIADRMessage(*this);
}

int LIADRMessage::getSize() const
{
	return -1;
}
