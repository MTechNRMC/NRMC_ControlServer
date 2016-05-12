#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H

#include <string>
#include <exception>

using std::string;
using std::exception;

namespace Socket
{
	// Interface
	class NetworkInterface
	{
	  // Associations
	  // Attributes
	  // Operations
	  public:
		NetworkInterface (  ) {}
		virtual ~NetworkInterface (  ) {}
		virtual exception* getLastException (  ) = 0;
		virtual bool connect ( string addr ) = 0;
		virtual void closeSocket (  ) = 0;
		virtual void clearError (  ) = 0;
		virtual bool sendMsg (const char* msg, unsigned int size ) = 0;
		virtual bool sendMsg (const char* msg, unsigned int size, string ip ) = 0;
		virtual bool startReceive ( void (*handler)(struct sockaddr_in&, char*, int) ) = 0;
		virtual bool stopReceive (  ) = 0;
		virtual char* receiveMsg ( int& size ) = 0;
	};
}

#endif
