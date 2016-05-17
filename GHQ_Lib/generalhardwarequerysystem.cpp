#include "generalhardwarequerysystem.h"
#include <exception>
#include "../NetworkLib/liadrmessage.h"

using namespace NRMC_GHQS;
using std::bad_function_call;
using NRMCNetwork::LIADRMessage;
using NRMCHardware::Lidar;
using NRMCHardware::PeripheralSystem;

Message* GeneralHardwareQuerySystem::queryHardware ( Device device )
{
	sockaddr_in dummyAddr;
	Message* msg = 0;

	switch(device)
	{
	case Device::LocalizationLIDAR:
		Lidar* rp = dynamic_cast<Lidar*>(hardwareInterface->getPeripheral(PeripheralSystem::LocalizationLIDAR));

		if(rp == 0)
			break;

		msg = new LIADRMessage(0, rp->getScan(), dummyAddr);
		break;
	}

	return msg;
}

GeneralHardwareQuerySystem::GeneralHardwareQuerySystem ( MDS_Interface& mdSystem, HardwareInterface& hardwareLayer )
{
	networkInterface = &mdSystem;
	hardwareInterface = &hardwareLayer;
}

GeneralHardwareQuerySystem::~GeneralHardwareQuerySystem (  )
{}

