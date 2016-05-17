#include "generalhardwarequerysystem.h"
#include <exception>
#include "../NetworkLib/liadrmessage.h"

using namespace NRMC_GHQS;
using std::bad_function_call;
using NRMCNetwork::LIADRMessage;
using NRMCHardware::Lidar;
using NRMCHardware::PeripheralSystem;
using NRMCHardware::SmrtPeripheral;

Message* GeneralHardwareQuerySystem::queryHardware ( Device device )
{
	sockaddr_in dummyAddr;
	Message* msg = 0;

	switch(device)
	{
	case Device::LocalizationLIDAR:
		Lidar* rp;
		SmrtPeripheral* lidarPhral = hardwareInterface->getPeripheral(PeripheralSystem::LocalizationLIDAR);

		if((rp = dynamic_cast<Lidar*>(lidarPhral->getPeripheral())) == 0)
			break;

		msg = new LIADRMessage(0, rp->getScan(), dummyAddr);
		rp = 0;
		delete lidarPhral;
		lidarPhral = 0;
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

