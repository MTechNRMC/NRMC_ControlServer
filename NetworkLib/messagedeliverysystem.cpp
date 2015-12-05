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
	throw NotImplementedException;
}

void MessageDeliverySystem::queueMessage ( Message* message )
{
	throw NotImplementedException;
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
	throw NotImplementedException;
}

MessageDeliverySystem::~MessageDeliverySystem (  )
{
	throw NotImplementedException;
}

void MessageDeliverySystem::handler ( struct sockaddr_in& addr, char* msg )
{
	throw NotImplementedException;
}

