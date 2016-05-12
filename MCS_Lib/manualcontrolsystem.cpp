#include <stdexcept>

#include "manualcontrolsystem.h"

#include "../HardwareLib/direction.h"
#include "../HardwareLib/smrtperipheral.h"
#include "../HardwareLib/peripheralsystem.h"
#include "../HardwareLib/servocontroller.h"

#include "../NetworkLib/subscribableexchange.h"

#define DELAY 100	// 0.1 second delay
#define ARMSERVO 5	// the arms for the robot. NOTE: they need to be treated as a servo

using namespace NRMC_MCS;

using NRMCHardware::Direction;
using NRMCHardware::SmrtPeripheral;
using NRMCHardware::PeripheralSystem;
using NRMCHardware::ServoController;
using NRMCNetwork::SubscribableExchange;

using std::exception;
using std::invalid_argument;

ManualControlSystem::ManualControlSystem ( MDS_Interface& networkInterface, HardwareInterface& hardwareInterface )
{
	this->manualControl = true;
	this->run = false;
	this->networkInterface = &networkInterface;
	this->hardwareInterface = &hardwareInterface;

	SubscribableExchange* exchange = dynamic_cast<SubscribableExchange*>(&networkInterface);

	// check if the cast was successful
	if(exchange == 0)
		throw invalid_argument("The passed network interface does not support SubscribaleExchange");

	exchange->subscribe(*this);
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

	// unsubscribe
	dynamic_cast<SubscribableExchange*>(networkInterface)->unsubscribe(*this);
}

void ManualControlSystem::queueMessage ( const Message& message )
{
	Message* tmp = message.clone();
	queueLock.lock();
	msgQueue.push(tmp);
	queueLock.unlock();
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
		mcsThread = thread(&ManualControlSystem::mcs, this);
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

		mcsThread.join();

	}
	catch (exception& e)
	{
		throw e;	// pass the exception along
	}

	return true;
}

void NRMC_MCS::ManualControlSystem::mcs()
{
	bool unlock = false;
	SmrtPeripheral* controller = manualControl ? hardwareInterface->getPeripheral(PeripheralSystem::LocomotionSystem) : 0;

	while (run)
	{
		queueLock.lock();
		unlock = true;
		while (run && !msgQueue.empty())
		{
			switch (msgQueue.front()->getOpcode())
			{
			case 0x01:
				if(controller != 0)
					move((MotorDir16Message*)msgQueue.front(), dynamic_cast<MotorController*>(controller->getPeripheral()));
				break;
			case 0x02:
				if(controller != 0)
					setThrottle((SetSpeedByteMessage*)msgQueue.front(), dynamic_cast<MotorController*>(controller->getPeripheral()));
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
					controller = hardwareInterface->getPeripheral(PeripheralSystem::LocomotionSystem);
				break;
			}

			// remove the message
			delete msgQueue.front();
			msgQueue.pop();

			queueLock.unlock();
			unlock = false;

			// small delay for next command 
			std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
		}
		if(unlock)
			queueLock.unlock();

		// stop if no commands received
		eStop(dynamic_cast<MotorController*>(controller->getPeripheral()));
	}
}

void NRMC_MCS::ManualControlSystem::move(MotorDir16Message * msg, MotorController* controller)
{
	static const char DELTA = 1;
	static char pos = 127;
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

		if(motor == ARMSERVO)
		{
			if(pos < '\xFE' && pos > '\x00')
			{
				switch(direction)
				{
				case Direction::forward:
					pos += DELTA;
					break;
				case Direction::backward:
					pos -= DELTA;
					break;
				default:
					break;
				}
			}

			// send the command
			ServoController* svc = dynamic_cast<ServoController*>(controller);

			if(svc != 0)
				svc->setPos(motor, pos);
		}
		else
			// send the command
			controller->setDirection(motor, direction);
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
