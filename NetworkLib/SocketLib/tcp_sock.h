#ifndef TCP_SOCK_H
#define TCP_SOCK_H

#include "networkinterface.h"
#include "notimplementedexception.h"

namespace Sockets
{
	class TCP_Sock: public NetworkInterface
	{
	  // Associations
	  // Attributes
	  private:
		int port;
		bool server;
		ServerSocket srvSocket;
		Socket clientSocket;
		exception lastException;
		void (*handler)(struct sockaddr_in&, char*);
		pthread_t rcvThread;
		volatile boolean rx;
		int timeout;
	  // Operations
	  public:
		exception getLastException (  );
		TCP_Sock ( int port, bool server );
		TCP_Sock ( int port, int timeout, bool server );
		TCP_Sock ( TCP_Sock socket );
		~TCP_Sock (  );
		void run (  );
		Exception getLastException (  );
		bool connect ( string addr );
		void close (  );
		void clearError (  );
		bool send ( char* msg );
		bool send ( char* msg, string ip );
		bool startReceive ( HandableObject handler );
		bool stopReceive (  );
		byte[] receive (  );
		byte[] receive ( Socket sct );
	  private:
		void send ( byte[] msg, Socket sct );
		void serverReceive ( void (*handler)(struct sockaddr_in&, char*) );
		void clientReceive ( void (*handler)(struct sockaddr_in&, char*) );
	  protected:
		void receive ( Handable Object handler );
	};
}

#endif
