#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "messagedeliverysystem.h"
#include "opcodeonlymessage.h"
#include "motordir16message.h"
#include "setspeedbytemessage.h"

#define DELAY 100	// 0.1 second delay

using namespace NRMCNetwork;

MessageDeliverySystem& MessageDeliverySystem::getInstance (  )
{
	static MessageDeliverySystem instance;
	
	return instance;
}

MessageDeliverySystem& MessageDeliverySystem::operator+=( NetworkInterface* interface )
{
	this->attachNetworkInterface( interface );
	
	return *this;
}

void MessageDeliverySystem::attachNetworkInterface( NetworkInterface* interface )
{
	if(socket != 0){
		socket->close();
		delete socket;
		socket = 0;
	}
	socket = interface;
}

void MessageDeliverySystem::queueMessage ( Message* message )
{
	queueLock.lock();
	msgSendQueue.push(message);
	queueLock.unlock();
}

bool MessageDeliverySystem::startSystem (  )
{
	if (run == true)
		return false;	// already running

	try
	{
		run = true;
		mdsThread = new thread(&MessageDeliverySystem::mds, this);
	}
	catch (exception& e)
	{
		throw e;	// pass along
	}

	return true;
}

bool MessageDeliverySystem::stopSystem (  )
{
	run = false;

	try
	{
		// wait the delay *2 to give a chance for a gracefull exit
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY * 2));

		// delete the thread
		if (mdsThread != 0)
			delete mdsThread;

		mdsThread = 0;
	}
	catch (exception& e)
	{
		throw e;	// pass the exception along
	}

	return true;
}

MessageDeliverySystem::MessageDeliverySystem (  )
{
	socket = 0;
	mdsThread = 0;
}

MessageDeliverySystem::~MessageDeliverySystem (  )
{
	stopSystem();
	
	if(socket != 0){
		socket->close();
		delete socket;
		socket = 0;
	}
	while(!msgSendQueue.empty()){
		Message* temp = msgSendQueue.front();
		msgSendQueue.pop();
		delete temp;
		temp = 0;
	}
}

void MessageDeliverySystem::handler ( struct sockaddr_in& addr, char* msg )
{
	Message* tmpMsg = 0;
	switch ((int)msg[0])
	{
	case 0x00:	// ping
		queueMessage(new OpcodeOnlyMessage(0x00, addr));	// send response
		break;
	case 0x01:	// move message
		tmpMsg = new MotorDir16Message(msg, addr);
		break;
	case 0x02:	// speed message
		tmpMsg = new SetSpeedByteMessage(msg, addr);
		break;
	case 0xFD:	// current mode
	case 0xFE:	// Start Auto Mode
	case 0xFF:	// Stop Auto Mode
		tmpMsg = new OpcodeOnlyMessage(msg, addr);
		break;
	default:
		break;
	}

	// check if it was a ping
	if (tmpMsg != 0)
	{
		updateSubscribers(*tmpMsg);	// if not update the subscribers
		delete tmpMsg;				// clean up
	}
}

void MessageDeliverySystem::mds()
{
	while (run)
	{
		queueLock.lock();
		while (!msgSendQueue.empty())
		{
			Message* tmpMsg = msgSendQueue.front();
			msgSendQueue.pop();
			queueLock.unlock();

			// send the message
			socket->send(tmpMsg->getMessage(), inet_ntoa(tmpMsg->getAddress().sin_addr));

			delete tmpMsg;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
	}
}
