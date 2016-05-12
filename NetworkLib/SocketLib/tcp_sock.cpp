#include "tcp_sock.h"

using namespace Sockets;

exception TCP_Sock::getLastException (  )
{
	throw NotImplementedException;
}

TCP_Sock::TCP_Sock ( int port, bool server )
{
}

TCP_Sock::TCP_Sock ( int port, int timeout, bool server )
{
}

TCP_Sock::TCP_Sock ( TCP_Sock socket )
{
}

TCP_Sock::~TCP_Sock (  )
{
}

void TCP_Sock::run (  )
{
	throw NotImplementedException;
}

Exception TCP_Sock::getLastException (  )
{
	throw NotImplementedException;
}

bool TCP_Sock::connect ( string addr )
{
	throw NotImplementedException;
}

void TCP_Sock::close (  )
{
	throw NotImplementedException;
}

void TCP_Sock::clearError (  )
{
	throw NotImplementedException;
}

bool TCP_Sock::send ( char* msg )
{
	throw NotImplementedException;
}

bool TCP_Sock::send ( char* msg, string ip )
{
	throw NotImplementedException;
}

bool TCP_Sock::startReceive ( HandableObject handler )
{
	throw NotImplementedException;
}

bool TCP_Sock::stopReceive (  )
{
	throw NotImplementedException;
}

byte[] TCP_Sock::receive (  )
{
	throw NotImplementedException;
}

byte[] TCP_Sock::receive ( Socket sct )
{
	throw NotImplementedException;
}

void TCP_Sock::send ( byte[] msg, Socket sct )
{
	throw NotImplementedException;
}

void TCP_Sock::serverReceive ( void (*handler)(struct sockaddr_in&, char*) )
{
	throw NotImplementedException;
}

void TCP_Sock::clientReceive ( void (*handler)(struct sockaddr_in&, char*) )
{
	throw NotImplementedException;
}

void TCP_Sock::receive ( Handable Object handler )
{
	throw NotImplementedException;
}

