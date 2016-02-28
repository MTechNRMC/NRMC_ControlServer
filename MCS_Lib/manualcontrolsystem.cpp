#include "manualcontrolsystem.h"

using namespace NRMC_MCS;

ManualControlSystem::ManualControlSystem ( MDS_Interface& networkInterface, HardwareInterface& hardwareInterface )
{
	this->manualControl = true;
	this->run = false;
	this->networkInterface = networkInterface;
	this->hardwareInterface = hardwareInterface;
	this->mcsThread = 0;

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
	if (run == true)
		return false;	// already running

	try
	{
		run = true;
		mcsThread = new thread(mcs);
	}
	catch (exception& e)
	{
		throw e;	// pass along
	}

	return true;
}

bool NRMC_MCS::ManualControlSystem::stopSystem()
{
	run = false;

	try
	{
		// wait the delay *2 to give a chance for a gracefull exit
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY * 2));

		// delete the thread
		if (mcsThread != 0)
			delete mcsThread;

		rcvThread = 0;
	}
	catch (exception& e)
	{
		throw e;	// pass the exception along
	}

	return true;
}

void NRMC_MCS::ManualControlSystem::mcs()
{
	while (run)
	{
		while (run && !msgQueue.empty())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		}

			// stop if no commands received
	}
}