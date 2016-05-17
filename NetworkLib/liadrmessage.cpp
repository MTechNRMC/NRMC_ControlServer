#include "liadrmessage.h"

using namespace NRMCNetwork;

LIADRMessage::LIADRMessage ( char* msg, sockaddr_in& addr )
{	/** UNUSED **/	}

LIADRMessage::LIADRMessage ( int opcode, vector<ScanPoint>& scan, sockaddr_in& addr )
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

int LIADRMessage::getOpcode (  )
{
	return opcode;
}

sockaddr_in& LIADRMessage::getAddress (  )
{
	return addr;
}

char* LIADRMessage::getMessage (  )
{
	return 0;
}

