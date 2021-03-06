#ifndef UDP_SOCK_H
#define UDP_SOCK_H

#include <thread>
#include <netinet/in.h>

#include "networkinterface.h"

#define ADDR_FAMILY AF_INET
#define DEFAULT_TIMEOUT 1000 // 1 second timeout by default
#define BUFFER_SIZE 1000

using std::thread;
using std::runtime_error;

namespace Socket
{
	class UDP_Sock : public NetworkInterface
	{
		// Associations
		// Attributes
	private:
		int port, timeout, sct;
		bool multicast;
		sockaddr_in defaultAddr;
		exception* lastException;
		thread rcvThread;
		volatile bool rx;
		// Operations
	public:
		int getPort();
		int getTimeout();
		bool getMulticast();
		exception* getLastException();
		void clearError();
		UDP_Sock(int port, bool multicast);
		UDP_Sock(int port, int timeout, bool multicast);
		UDP_Sock(int port, int timeout, bool multicast, sockaddr_in& sctInterface);
		UDP_Sock(const UDP_Sock& socket);
		~UDP_Sock();
		void closeSocket();
		bool connect(string addr);
		bool sendMsg(const char* msg, unsigned int size);
		bool sendMsg(const char* msg, unsigned int size, string ip);
		bool sendMsg(const char* msg, unsigned int size, const sockaddr_in& addr);
		bool startReceive(void(*handler)(sockaddr_in&, char*, int));
		bool stopReceive();
		char* receiveMsg ( int& size );
		char* receiveMsg(sockaddr_in& msgAddr, int& size);
	protected:
		void receiveMsg(void(*handler)(sockaddr_in&, char*, int));
	private:
		runtime_error* errorNumToException(int err);
		void init(int port, int timeout, bool multicast, sockaddr_in& sctInterface);
	};
}
#endif
