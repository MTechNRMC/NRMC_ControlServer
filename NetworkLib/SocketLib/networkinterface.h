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
		virtual exception getLastException (  ) = 0;
		virtual bool connect ( string addr ) = 0;
		virtual void close (  ) = 0;
		virtual void clearError (  ) = 0;
		virtual bool send (const char* msg ) = 0;
		virtual bool send (const char* msg, string ip ) = 0;
		virtual bool startReceive ( void (*handler)(struct sockaddr_in&, char*) ) = 0;
		virtual bool stopReceive (  ) = 0;
		virtual char* receive (  ) = 0;
	};
}

#endif
