#ifndef MANUALCONTROLSYSTEM_H
#define MANUALCONTROLSYSTEM_H

#include <queue>
#include <thread>
#include <stdexcept>

#include "../NetworkLib/exchangesubscriber.h"
#include "../NetworkLib/mds_interface.h"
#include "../NetworkLib/subscribableexchange.h"
#include "../NetworkLib/motordir16message.h"
#include "../NetworkLib/setspeedbytemessage.h"

#include "../HardwareLib/hardwareinterface.h"
#include "../HardwareLib/smrtperipheral.h"
#include "../HardwareLib/motorcontroller.h"
#include "../HardwareLib/direction.h"

#include "../Util/systeminterface.h"

#define DELAY 100	// 0.1 second delay

using std::queue;
using std::thread;
using std::exception;

using NRMCUtil::SystemInterface;
using NRMCNetwork::ExchangeSubscriber;
using NRMCNetwork::MDS_Interface;
using NRMCNetwork::SetSpeedByteMessage;
using NRMCNetwork::SubscribableExchange;
using NRMCNetwork::Message;
using NRMCNetwork::MotorDir16Message;
using NRMCHardware::HardwareInterface;
using NRMCHardware::SmrtPeripheral;
using NRMCHardware::PeripheralType;
using NRMCHardware::MotorController;
using NRMCHardware::Direction;


namespace NRMC_MCS
{
	class ManualControlSystem : public ExchangeSubscriber, public SystemInterface
	{
		// Associations
		// Attributes
	private:
		bool manualControl;
		volatile bool run;
		MDS_Interface* networkInterface;
		HardwareInterface* hardwareInterface;
		queue<Message*> msgQueue;
		thread* mcsThread;
		// Operations
	public:
		ManualControlSystem(MDS_Interface& networkInterface, HardwareInterface& hardwareInterface);
		~ManualControlSystem();
		void queueMessage(const Message& message);
		bool subscriberWants(const Message& message);
		bool startSystem();
		bool stopSystem();
	private:
		void mcs();
		void move(MotorDir16Message* msg, MotorController* controller);
		void setThrottle(SetSpeedByteMessage* msg, MotorController* controller);
		void eStop(MotorController* controller);
	};
}

#endif
