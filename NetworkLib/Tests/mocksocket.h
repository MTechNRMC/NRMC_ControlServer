#ifndef NETWORKLIB_TESTS_MOCKSOCKET_H_
#define NETWORKLIB_TESTS_MOCKSOCKET_H_

#include "../SocketLib/networkinterface.h"
#include <gmock/gmock.h>

class MockSocket : public Socket::NetworkInterface
{
public:
	~MockSocket(){}
	MOCK_METHOD0(closeSocket, void());
	MOCK_METHOD2(sendMsg, bool(const char*, unsigned int));
	MOCK_METHOD3(sendMsg, bool(const char*, unsigned int, string));
	MOCK_METHOD0(stopReceive, bool());
	MOCK_METHOD0(getLastException, exception*());
	MOCK_METHOD0(clearError, void());
	MOCK_METHOD1(receiveMsg, char*(int&));
	MOCK_METHOD1(connect, bool(string));

	bool startReceive(void (*handler)(struct sockaddr_in&, char*, int))
	{
		char* test = new char[10];
		struct sockaddr_in testAddr;
		int testSize = 10;

		handler(testAddr,test,testSize);

		return true;
	}
};

#endif /* NETWORKLIB_TESTS_MOCKSOCKET_H_ */
