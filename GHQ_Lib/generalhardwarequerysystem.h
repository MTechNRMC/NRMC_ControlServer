#ifndef GENERALHARDWAREQUERYSYSTEM_H
#define GENERALHARDWAREQUERYSYSTEM_H

#include <vector>
#include <thread>

#include "ghqs_observer.h"
#include "ghqs_interface.h"
#include "device.h"

#include "../NetworkLib/message.h"
#include "../NetworkLib/exchangesubscriber.h"
#include "../NetworkLib/mds_interface.h"

#include "../HardwareLib/hardwareinterface.h"

using std::vector;
using std::thread;
using NRMCNetwork::ExchangeSubscriber;
using NRMCNetwork::Message;
using NRMCNetwork::MDS_Interface;
using NRMCHardware::HardwareInterface;

namespace NRMC_GHQS
{
	class GeneralHardwareQuerySystem : public GHQS_Interface, public ExchangeSubscriber
	{
		// Attributes
	public:
		vector<GHQS_Observer*> observers;
		thread* ghqsThread;
		// Operations
	public:
		static GHQS_Interface& getInstance();
		void queueMessage(Message& message);
		bool subscriberWants(Message& message);
		Message* queryHardware(Device device);
		bool startHardwareStream(GHQS_Observer& observer);
		bool stopHardwareStream(GHQS_Observer& observer);
	private:
		GeneralHardwareQuerySystem(MDS_Interface& mdSystem, HardwareInterface& hardwareLayer);
		~GeneralHardwareQuerySystem();
	};
}
#endif
