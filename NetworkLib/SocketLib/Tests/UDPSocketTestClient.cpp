#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <exception>

#include "../networkinterface.h"
#include "../udp_sock.h"

using std::cout;
using std::cin;
using std::string;
using std::exception;

using Socket::UDP_Sock;

void handler(sockaddr_in&, char*, int);

int main(int argc, char** args)
{
	int port;
	string ip;
	string msg;

	cout << "Enter IP: ";
	cin >> ip;
	cout << "Enter Port: ";
	cin >> port;

	try
	{
		UDP_Sock* sock = new UDP_Sock(port, false);		// open the socket


		sock->startReceive(handler);		// start receiving

		cout << "Enter Message\n";
		getline(std::cin,msg);
		while(true)
		{
			cout << "> ";
//			cin >> msg;
			std::cin.clear();
			getline(std::cin,msg);

			if(msg.empty())
				break;

			sock->sendMsg(msg.c_str(), msg.size(), ip);
		}

		delete sock;
	}
	catch(exception* e)
	{
		cout << e->what();
	}

	return 0;
}

void handler(sockaddr_in& addr, char* msg, int size)
{
	cout << "Received message from: " << inet_ntoa(addr.sin_addr) << std::endl;
	cout << "Message: " << msg << std::endl;
}
