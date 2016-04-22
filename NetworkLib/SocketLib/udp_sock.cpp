#include "udp_sock.h"
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <errno.h>
#include <cstring>


using namespace Socket;

int UDP_Sock::getPort()
{
	return port;
}

int UDP_Sock::getTimeout()
{
	return timeout;
}

bool UDP_Sock::getMulticast()
{
	return multicast;
}

exception* UDP_Sock::getLastException (  )
{
	return lastException;
}

void UDP_Sock::clearError (  )
{
	delete lastException;
	lastException = 0;
}

UDP_Sock::UDP_Sock ( int port, bool multicast)
{
	UDP_Sock(port, DEFAULT_TIMEOUT, multicast);
}

UDP_Sock::UDP_Sock ( int port, int timeout, bool multicast)
{
	// set up the default interface to bind to
	sockaddr_in defualtInterface;
	memset((char*)&defualtInterface, 0, sizeof(defualtInterface));
	defualtInterface.sin_family = ADDR_FAMILY;
	defualtInterface.sin_addr.s_addr = htonl(INADDR_ANY);
	defualtInterface.sin_port = htons(port);


	UDP_Sock(port, timeout, multicast, defualtInterface);
}

UDP_Sock::UDP_Sock(int port, int timeout, bool multicast, sockaddr_in& sctInterface)
{
	// set the timeout
	timeval timeoutVal;
	timeoutVal.tv_sec = 0;
	timeoutVal.tv_usec = timeout*1000;

	// set the attributes
	this->port = port;
	this->timeout = timeout;
	this->multicast = multicast;
	this->rx = false;
	this->rcvThread = 0;

	// open the socket
	if ((sct = socket(ADDR_FAMILY, SOCK_DGRAM, 0)) < 0)
		throw errorNumToException(errno);

	// check if the timeout should be set
	if(timeout > 0)
		// set the receive timeout
		if (setsockopt(sct, SOL_SOCKET, SO_RCVTIMEO, &timeoutVal, sizeof(timeoutVal)) < 0)
			throw errorNumToException(errno);	// timeout failed to set

	// bind the socket
	if (bind(sct, (sockaddr*)&sctInterface, sizeof(sctInterface)) < 0)
		throw errorNumToException(errno);
}

UDP_Sock::UDP_Sock ( const UDP_Sock& socket )
{
	UDP_Sock(socket.port, socket.timeout, socket.multicast);
}

UDP_Sock::~UDP_Sock (  )
{
	closeSocket();
}

void UDP_Sock::closeSocket (  )
{
	stopReceive();	// first stop receiving messages

	// close the socket
	close(sct);
}

bool UDP_Sock::connect ( string addr )
{
	// do nothing
//	defaultAddr = addr;
	return true;
}

bool UDP_Sock::sendMsg (const char* msg )
{
	return sendMsg(msg, defaultAddr);
}

bool UDP_Sock::sendMsg (const char* msg, string ip )
{
	// set up the basic address
	sockaddr_in dst;
	memset((char*)&dst, 0, sizeof(dst));
	dst.sin_family = ADDR_FAMILY;
	dst.sin_port = htons(port);

	// translate the ip string to the binary format
	if (inet_pton(ADDR_FAMILY, ip.c_str(), &(dst.sin_addr)) < 0)
	{
		lastException = errorNumToException(errno);
		return false;	// failed
	}

	return sendMsg(msg, dst);
}

bool UDP_Sock::sendMsg (const char* msg, const sockaddr_in& addr )
{
	if (sendto(sct, msg, sizeof(msg), 0, (sockaddr*)&addr, sizeof(addr)) < 0)
	{
		lastException = errorNumToException(errno);
		return false;	// failed
	}

	return true;
}

bool UDP_Sock::startReceive ( void (*handler)(sockaddr_in&, char*) )
{
	// check if the sock is already receiving
	if (rx == true)
	{
		lastException = new runtime_error("Receive is already running");
		return false;
	}

	try
	{
		// set to transmit
		rx = true;
		void (UDP_Sock::*rcvFunc)(void (*handler)(sockaddr_in&, char*)) = &UDP_Sock::receiveMsg;
		// create the thread
		rcvThread = new thread(rcvFunc,this,handler);
	}
	catch (exception& e)
	{
		rx = false;

		if (lastException != 0)
			clearError();

		lastException = &e;
		return false;
	}

	return true;
}

bool UDP_Sock::stopReceive (  )
{
	// check if receive has been started
	if (!rx && rcvThread == 0)
		return true;	// already stopped so return true

	// set the receive flag to false to stop receiving
	rx = false;

	try
	{
		// wait for the timeout*2 to allow the thread to exit gracefully
		std::this_thread::sleep_for(std::chrono::milliseconds(timeout * 2));

		// delete the thread
		if(rcvThread!=0)
			delete rcvThread;

		rcvThread = 0;
	}
	catch (exception& e)
	{
		if (lastException != 0)
			clearError();

		lastException = &e;
		return false;
	}

	return true;
}

char* UDP_Sock::receiveMsg()
{
	return 0;
}

char* UDP_Sock::receiveMsg ( sockaddr_in& msgAddr )
{
	int msgLength = 0;
	char buffer[BUFFER_SIZE];
	char* msg;
	socklen_t addrSize = sizeof(msgAddr);

	memset(buffer, 0, sizeof(buffer));

	if ((msgLength = recvfrom(sct, buffer, BUFFER_SIZE, 0, (sockaddr *)&msgAddr, &addrSize)) < 0)
		return 0;	// no message received

	msg = new char[msgLength];

	// copy the message from the buffer
	for (int index = 0; index < msgLength; index++)
		msg[index] = buffer[index];

	// return the message
	return msg;
}

void UDP_Sock::receiveMsg ( void (*handler)(sockaddr_in&, char*) )
{
	char* msg;
	sockaddr_in msgAddr;
	memset((char*)&msgAddr, 0, sizeof(msgAddr));
	msgAddr.sin_family = ADDR_FAMILY;
	msgAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	msgAddr.sin_port = htons(port);

	while (rx)
	{
		msg = receiveMsg(msgAddr);
		if (msg != 0)
			handler(msgAddr, msg);	// pass the info to the handler
	}
}

runtime_error* UDP_Sock::errorNumToException(int err)
{
	switch (err)
	{
	case EAFNOSUPPORT:
		return new runtime_error("Specfied address family is not suported");
	case EMFILE:
		return new runtime_error("Process has exhausted file descriptors");
	case ENFILE:
		return new runtime_error("System has exhausted file descriptors");
	case EPROTONOSUPPORT:
		return new runtime_error("Specfied address family is not suport the specfied protocol");
	case EPROTOTYPE:
		return new runtime_error("Specfied protocol does not support specfied socket type");
	case EACCES:
		return new runtime_error("Process has insufficient privileges");
	case ENOBUFS:
		return new runtime_error("Insuffucuent resources availble");
	case ENOMEM:
		return new runtime_error("Insuffucuent memory availble");
	default:
		return new runtime_error("An unknown error has occured");
	}
}
