#ifndef MANUALCONTROLSYSTEM_H
#define MANUALCONTROLSYSTEM_H

#include <queue>
#include <thread>
#include <stdexcept>

#include "exchangesubscriber.h"
#include "hardwareinterface.h"
#include "smrtperipheral.h"
#include "systeminterface.h"
#include "mds_interface.h"
#include "subscribableexchange.h"
#include "peripheraltype.h"

#define DELAY 100	// 0.1 second delay

using std::queue;
using std::thread;
using std::exception;

using NRMCUtil::SystemInterface;
using NRMCNetwork::ExchangeSubscriber;
using NRMCNetwork::MDS_Interface;
using NRMCNetwork::Message;
using NRMCNetwork::SubscribableExchange;
using NRMCHardware::HardwareInterface;
using NRMCHardware::SmrtPeripheral;
using NRMCHardware::PeripheralType;


namespace NRMC_MCS
{
	class ManualControlSystem : public ExchangeSubscriber, public SystemInterface
	{
		// Associations
		// Attributes
	private:
		bool manualControl;
		virtual bool run;
		MDS_Interface* networkInterface;
		HardwareInterface* hardwareInterface;
		virtual queue<Message*> msgQueue;
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
	};
}

#endif
