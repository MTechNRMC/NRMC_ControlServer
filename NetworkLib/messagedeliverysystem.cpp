#include "messagedeliverysystem.h"

using namespace NRMCNetwork;

static MessageDeliverySystem& MessageDeliverySystem::getInstance (  )
{
	static MessageDeliverySystem instance;
	
	return *instance;
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
	msgSendQueue.push_back(message);
}

bool MessageDeliverySystem::startSystem (  )
{
	throw NotImplementedException;
}

bool MessageDeliverySystem::stopSystem (  )
{
	throw NotImplementedException;
}

MessageDeliverySystem::MessageDeliverySystem (  )
{
	socket = 0;
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
		Message* temp = msgSendQueue.pop_front();
		delete temp;
		temp = 0;
	}
}

void MessageDeliverySystem::handler ( struct sockaddr_in& addr, char* msg )
{
	throw NotImplementedException;
}

