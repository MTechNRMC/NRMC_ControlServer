#include "messagedeliverysystem.h"

using namespace NRMCNetwork;

static MessageDeliverySystem* MessageDeliverySystem::getInstance (  )
{
}

static MessageDeliverySystem* MessageDeliverySystem::getInstance ( NetworkInterface* socket )
{
}

void MessageDeliverySystem::queueMessage ( Message* message )
{
}

bool MessageDeliverySystem::startSystem (  )
{
}

bool MessageDeliverySystem::stopSystem (  )
{
}

MessageDeliverySystem::MessageDeliverySystem ( NetworkInterface* socket )
{
}

void MessageDeliverySystem::handler ( struct sockaddr_in& addr, char* msg )
{
}

