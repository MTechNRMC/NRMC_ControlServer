#ifndef MANUALCONTROLSYSTEM_H
#define MANUALCONTROLSYSTEM_H

#include <queue>
#include <thread>

#include "../NetworkLib/exchangesubscriber.h"
#include "../NetworkLib/mds_interface.h"
#include "../NetworkLib/motordir16message.h"
#include "../NetworkLib/setspeedbytemessage.h"

#include "../HardwareLib/hardwareinterface.h"
#include "../HardwareLib/motorcontroller.h"

#include "../Util/systeminterface.h"

using std::queue;
using std::thread;

using NRMCUtil::SystemInterface;
using NRMCNetwork::ExchangeSubscriber;
using NRMCNetwork::MDS_Interface;
using NRMCNetwork::SetSpeedByteMessage;
using NRMCNetwork::Message;
using NRMCNetwork::MotorDir16Message;
using NRMCHardware::HardwareInterface;
using NRMCHardware::MotorController;


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
		thread mcsThread;
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
