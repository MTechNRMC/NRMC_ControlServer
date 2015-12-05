#ifndef UDP_SOCK_H
#define UDP_SOCK_H

#include "networkinterface.h"
#include "notimplementedexception.h"

namespace Sockets
{
	class UDP_Sock: public NetworkInterface {
	  // Associations
	  // Attributes
	  private:
		int port;
		struct sockaddr_in defaultAddr;
		int sct;
		exception lastException;
		pthread_t  rcvThread;
		void  (*handler)(struct sockaddr_in&, char*);
		volatile bool rx;
	  // Operations
	  public:
		exception getLastException (  );
		void clearError (  );
		UDP_Sock ( int port, bool multicast );
		UDP_Sock ( int port, int timeout, bool multicast );
		UDP_Sock ( const UDP_Sock& socket );
		~UDP_Sock (  );
		void close (  );
		bool connect ( string addr );
		bool send ( char* msg );
		bool send ( char* msg, string ip );
		send ( char* msg, const struct sockaddr_in& addr );
		bool startReceive ( void (*handler)(struct sockaddr_in&, char*) );
		bool stopReceive (  );
		char* receive (  );
	  protected:
		void receive ( void (*handler)(struct sockaddr_in, char*) );
	};
}
#endif
