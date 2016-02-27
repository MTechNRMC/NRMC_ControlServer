#include "manualcontrolsystem.h"

using namespace NRMC_MCS;

ManualControlSystem::ManualControlSystem ( MDS_Interface& networkInterface, HardwareInterface& hardwareInterface )
{
	this->manualControl = true;
	this->networkInterface = networkInterface;
	this->hardwareInterface = hardwareInterface;

	((SubscribableExchange)networkInterface).subscribe(*this);
}

ManualControlSystem::~ManualControlSystem (  )
{
	stopSystem();

	// clear the queue
	while (!msgQueue.empty())
	{
		delete msgQueue.front();
		msgQueue.pop();
	}
}

void ManualControlSystem::queueMessage ( const Message& message )
{
	msgQueue.push(message);
}

bool ManualControlSystem::subscriberWants ( const Message& message )
{
	switch (message.getOpcode())
	{
	case 1:
	case 2:
	case 254:
	case 255:
		return true;
	default:
		return false;
	}
}

bool NRMC_MCS::ManualControlSystem::startSystem()
{
	return false;
}

bool NRMC_MCS::ManualControlSystem::stopSystem()
{
	return false;
}
