#include "generalhardwarequerysystem.h"

#include <stdexcept>
#include "../NetworkLib/liadrmessage.h"

using namespace NRMC_GHQS;
using NRMCNetwork::LIADRMessage;
using NRMCHardware::Lidar;
using NRMCHardware::PeripheralSystem;
using NRMCHardware::SmrtPeripheral;
using std::runtime_error;

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

GeneralHardwareQuerySystem::GeneralHardwareQuerySystem ( HardwareInterface& hardwareLayer )
{
	/** !!!used for testing only!!! **/
	networkInterface = 0;
	hardwareInterface = &hardwareLayer;
	init();
}

GeneralHardwareQuerySystem::GeneralHardwareQuerySystem ( MDS_Interface& mdSystem, HardwareInterface& hardwareLayer )
{
	networkInterface = &mdSystem;
	hardwareInterface = &hardwareLayer;
	init();
}

GeneralHardwareQuerySystem::~GeneralHardwareQuerySystem (  )
{
	networkInterface = 0;
	hardwareInterface = 0;
}

void GeneralHardwareQuerySystem::init()
{
	// start the lidars scan
	SmrtPeripheral* locLidarPhral = hardwareInterface->getPeripheral(PeripheralSystem::LocalizationLIDAR);

	Lidar* ldr = dynamic_cast<Lidar*>(locLidarPhral->getPeripheral());

	if(ldr == 0)
		runtime_error("Failed to start the LIDAR(s)");

	ldr->startScan();

	delete locLidarPhral;
	ldr = 0;
	locLidarPhral = 0;
}
