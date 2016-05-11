#include "peripheralfactory.h"
#include "micromaestro12.h"

#define MM16PORT "/dev/ttyACM1"
using namespace NRMCHardware;

PeripheralFactory& PeripheralFactory::getInstance (  )
{
	static PeripheralFactory instance;

	return instance;
}

SmrtPeripheral* PeripheralFactory::getPeripheral ( PeripheralSystem sys, bool forceConnect)
{
	SmrtPeripheral* peripheral = forceConnect ? 0 : checkPool(sys);

	//check if there was a peroperal of the requested type in the pool and if not attempt to connect a periperal of that type
	if (peripheral == 0)
		peripheral = connectPeripheral(sys);

	return peripheral;
}

void PeripheralFactory::attachFactory ( SerialPortFactory& factory )
{
	// check if a fectory is attached
	if (srlPrtFactory != 0)
	{
		// dispose of the attached factory
		delete srlPrtFactory;
		srlPrtFactory = 0;
	}

	srlPrtFactory = &factory;
}

void PeripheralFactory::returnPeripheral ( Peripheral& peripheral )
{
	peripheralPool.push_back(&peripheral);
}

PeripheralFactory::PeripheralFactory (  )
{
	srlPrtFactory = 0;
}

PeripheralFactory::~PeripheralFactory (  )
{
	srlPrtFactory = 0;

	// destroy the pool
	for (unsigned int index = 0; index < peripheralPool.size(); index++)
		delete peripheralPool[index];

	peripheralPool.clear();
}

SmrtPeripheral * NRMCHardware::PeripheralFactory::checkPool(PeripheralSystem sys)
{
	SmrtPeripheral* periperal = 0;

	if (!peripheralPool.empty())
	{
		// search if there is already a peripheral in the pool
		for (vector<Peripheral*>::iterator it = peripheralPool.begin(); it != peripheralPool.end(); ++it)
		{
			if ((*it)->getSystem() == sys)
			{
				periperal = new SmrtPeripheral(*(*it), *this);
				peripheralPool.erase(it);
				break;
			}
		}
	}

	return periperal;
}

SmrtPeripheral * NRMCHardware::PeripheralFactory::connectPeripheral(PeripheralSystem sys)
{
	Peripheral* tmp = 0;
	SmrtPeripheral* periperal = 0;

	switch (sys)
	{
	case NRMCHardware::LocomotionSystem:
		tmp = new MicroMaestro12(srlPrtFactory->openPort(MM16PORT, 9600), NRMCHardware::LocomotionSystem);	// we use a micromaestro for servo and motor control
		break;
	case NRMCHardware::MSP430SensorSystem:
		break;
	case NRMCHardware::ObsticalDetectionLIDAR:
		break;
	case NRMCHardware::LocalizationLIDAR:
		break;
	}

	if (tmp != 0)
		periperal = new SmrtPeripheral(*tmp, *this);

	return periperal;
}

