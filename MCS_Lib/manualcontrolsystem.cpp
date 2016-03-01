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
	case 0x01:
	case 0x02:
	case 0xFE:
	case 0xFF:
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
	SmrtPeripheral* controller = manualControl ? hardwareInterface->getPeripheral(PeripheralType::motorController) : 0;

	while (run)
	{
		while (run && !msgQueue.empty())
		{
			switch (msgQueue.front()->getOpcode())
			{
			case 0x01:
				move((MotorDir16Message*)msgQueue.front(), (MotorController*)controller->peripheral());
				break;
			case 0x02:
				setThrottle((SetSpeedByteMessage*)msgQueue.front(), (MotorController*)controller->peripheral());
				break;
			case 0xFE:
				manualControl = false;
				if (controller != 0)
				{
					delete controller;
					controller = 0;
				}
				break;
			case 0xFF:
				manualControl = true;
				if (controller == 0)
					controller = hardwareInterface->getPeripheral(PeripheralType::motorController);
				break;
			}

			// remove the message
			delete msgQueue.front();
			msgQueue.pop();

			// small delay for next command 
			std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		}

		// stop if no commands received
		eStop((MotorController*)controller->peripheral());
	}
}

void NRMC_MCS::ManualControlSystem::move(MotorDir16Message * msg, MotorController* controller)
{
	// check if manual control is disabled
	if (!manualControl || controller == 0)
		return;

	// set all 8 motors, or the max motors supported whatever is smallest, to a direction
	for (int motor = 0; motor < 8 && motor < controller->getNumOfMotors(); motor++)
	{
		Direction direction;

		// set the direction
		switch(msg->getMotorDir() >> (2 * motor) & 0x03)
		{
		case 0x01:
			direction = Direction::forward;
			break;
		case 0x02:
			direction = Direction::backward;
			break;
		default:
			direction = Direction::stop;
			break;
		}

		// send the command
		controller->setDirection(motor, dirction);
	}
}

void NRMC_MCS::ManualControlSystem::setThrottle(SetSpeedByteMessage * msg, MotorController* controller)
{
	// check if manual control is disabled
	if (!manualControl || controller == 0)
		return;

	controller->setSpeed(msg->getMotorNum(), msg->getSpeed());
}

void NRMC_MCS::ManualControlSystem::eStop(MotorController* controller)
{
	// check if manual control is disabled
	if (!manualControl || controller == 0)
		return;

	controller->allStop();
}