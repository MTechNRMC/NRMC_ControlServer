#ifndef MANUALCONTROLSYSTEM_H
#define MANUALCONTROLSYSTEM_H

#include <queue>

#include "exchangesubscriber.h"
#include "hardwareinterface.h"
#include "systeminterface.h"
#include "mds_interface.h"
#include "subscribableexchange.h"

using std::queue;

using NRMCUtil::SystemInterface;
using NRMCNetwork::ExchangeSubscriber;
using NRMCNetwork::MDS_Interface;
using NRMCNetwork::Message;
using NRMCNetwork::SubscribableExchange;

namespace NRMC_MCS
{
	class ManualControlSystem : public ExchangeSubscriber, public SystemInterface
	{
		// Associations
		// Attributes
	private:
		bool manualControl;
		MDS_Interface* networkInterface;
		HardwareInterface* hardwareInterface;
		queue<Message*> msgQueue;
		// Operations
	public:
		ManualControlSystem(MDS_Interface& networkInterface, HardwareInterface& hardwareInterface);
		~ManualControlSystem();
		void queueMessage(const Message& message);
		bool subscriberWants(const Message& message);
		bool startSystem();
		bool stopSystem();
	};
}

#endif
