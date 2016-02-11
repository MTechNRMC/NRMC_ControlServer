#ifndef UDP_SOCK_H
#define UDP_SOCK_H

#include <thread>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>

#include "networkinterface.h"
#include "notimplementedexception.h"

#define ADDR_FAMILY AF_INET
#define DEFAULT_TIMEOUT 1000 // 1 second timeout by default

using std::thread;

namespace Sockets
{
	class UDP_Sock : public NetworkInterface {
		// Associations
		// Attributes
	private:
		int port, timeout, sct;
		bool multicast;
		sockaddr_in defaultAddr;
		exception* lastException;
		thread*  rcvThread;
		volatile bool rx;
		// Operations
	public:
		int getPort();
		int getTimeout();
		bool getMulticast();
		exception getLastException();
		void clearError();
		UDP_Sock(int port, bool multicast);
		UDP_Sock(int port, int timeout, bool multicast);
		UDP_Sock(int port, int timeout, bool multicast, sockaddr_in& sctInterface);
		UDP_Sock(const UDP_Sock& socket);
		~UDP_Sock();
		void close();
		bool connect(string addr);
		bool send(char* msg);
		bool send(char* msg, string ip);
		bool send(char* msg, const struct sockaddr_in& addr);
		bool startReceive(void(*handler)(struct sockaddr_in&, char*));
		bool stopReceive();
		char* receive();
	protected:
		void receive(void(*handler)(struct sockaddr_in, char*));
	private:
		exception errorNumToException(int err);
	};
}
#endif
