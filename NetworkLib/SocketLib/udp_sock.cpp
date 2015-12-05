#include "udp_sock.h"

using namespace Sockets;

exception UDP_Sock::getLastException (  )
{
	throw NotImplementedException;
}

void UDP_Sock::clearError (  )
{
	throw NotImplementedException;
}

UDP_Sock::UDP_Sock ( int port, bool multicast )
{
}

UDP_Sock::UDP_Sock ( int port, int timeout, bool multicast )
{
}

UDP_Sock::UDP_Sock ( const UDP_Sock& socket )
{
}

UDP_Sock::~UDP_Sock (  )
{
}

void UDP_Sock::close (  )
{
	throw NotImplementedException;
}

bool UDP_Sock::connect ( string addr )
{
	throw NotImplementedException;
}

bool UDP_Sock::send ( char* msg )
{
	throw NotImplementedException;
}

bool UDP_Sock::send ( char* msg, string ip )
{
	throw NotImplementedException;
}

UDP_Sock::send ( char* msg, const struct sockaddr_in& addr )
{
	throw NotImplementedException;
}

bool UDP_Sock::startReceive ( void (*handler)(struct sockaddr_in&, char*) )
{
	throw NotImplementedException;
}

bool UDP_Sock::stopReceive (  )
{
	throw NotImplementedException;
}

char* UDP_Sock::receive (  )
{
	throw NotImplementedException;
}

void UDP_Sock::receive ( void (*handler)(struct sockaddr_in, char*) )
{
	throw NotImplementedException;
}

