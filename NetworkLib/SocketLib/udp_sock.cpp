#include "udp_sock.h"

using namespace Sockets;

exception UDP_Sock::getLastException (  )
{
}

void UDP_Sock::clearError (  )
{
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
}

bool UDP_Sock::connect ( string addr )
{
}

bool UDP_Sock::send ( char* msg )
{
}

bool UDP_Sock::send ( char* msg, string ip )
{
}

UDP_Sock::send ( char* msg, const struct sockaddr_in& addr )
{
}

bool UDP_Sock::startReceive ( void (*handler)(struct sockaddr_in&, char*) )
{
}

bool UDP_Sock::stopReceive (  )
{
}

char* UDP_Sock::receive (  )
{
}

void UDP_Sock::receive ( void (*handler)(struct sockaddr_in, char*) )
{
}

