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
	class GeneralHardwareQuerySystem : public GHQS_Interface
	{
		// Attributes
	public:
		MDS_Interface* networkInterface;
		HardwareInterface* hardwareInterface;
		vector<GHQS_Observer*> observers;
		// Operations
	public:
		Message* queryHardware(Device device);
		GeneralHardwareQuerySystem(MDS_Interface& mdSystem, HardwareInterface& hardwareLayer);
		~GeneralHardwareQuerySystem();
	};
}
#endif
