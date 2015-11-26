#include "tcp_sock.h"

using namespace Sockets;

exception TCP_Sock::getLastException (  )
{
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
}

Exception TCP_Sock::getLastException (  )
{
}

bool TCP_Sock::connect ( string addr )
{
}

void TCP_Sock::close (  )
{
}

void TCP_Sock::clearError (  )
{
}

bool TCP_Sock::send ( char* msg )
{
}

bool TCP_Sock::send ( char* msg, string ip )
{
}

bool TCP_Sock::startReceive ( HandableObject handler )
{
}

bool TCP_Sock::stopReceive (  )
{
}

byte[] TCP_Sock::receive (  )
{
}

byte[] TCP_Sock::receive ( Socket sct )
{
}

void TCP_Sock::send ( byte[] msg, Socket sct )
{
}

void TCP_Sock::serverReceive ( void (*handler)(struct sockaddr_in&, char*) )
{
}

void TCP_Sock::clientReceive ( void (*handler)(struct sockaddr_in&, char*) )
{
}

void TCP_Sock::receive ( Handable Object handler )
{
}

