#include "peripheralfactory.h"

using namespace NRMCHardware;

static PeripheralFactory& PeripheralFactory::getInstance (  )
{
	static PeripheralFactory instance;

	return *instance;
}

SmrtPeripheral* PeripheralFactory::getPeripheral ( PeripheralType type, bool forceConnect)
{
	SmrtPeripheral* peripheral = forceConnect ? 0 : checkPool(type);

	//check if there was a peroperal of the requested type in the pool and if not attempt to connect a periperal of that type
	if (peripheral == 0)
		peripheral = connectPeripheral(type);

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

	srlPrtFactory = factory;
}

void PeripheralFactory::returnPeripheral ( Peripheral& peripheral )
{
	peripheralPool.push_back(peripheral);
}

PeripheralFactory::PeripheralFactory (  )
{
	srlPrtFactory = 0;
}

PeripheralFactory::~PeripheralFactory (  )
{
	// destroy the attached factory
	if (srlPrtFactory != 0)
	{
		delete srlPrtFactory;
		srlPrtFactory = 0;
	}

	// destroy the pool
	for (int index = 0; index < peripheralPool.size(); index++)
		delete peripheralPool[index];

	peripheralPool.clear();
}

SmrtPeripheral * NRMCHardware::PeripheralFactory::checkPool(PeripheralType type)
{
	SmrtPeripheral* periperal = 0;

	if (!peripheralPool.empty())
	{
		// search if there is already a peripheral in the pool
		for (vector<Peripheral*>::iterator it = peripheralPool.begin(); it != peripheralPool.end(); ++it)
		{
			if ((*it)->getType() & type != 0)
			{
				periperal = new SmrtPeripheral(*(*it), *this);
				peripheralPool.erase(it);
				break;
			}
		}
	}

	return periperal;
}

SmrtPeripheral * NRMCHardware::PeripheralFactory::connectPeripheral(PeripheralType type)
{
	Peripheral* tmp = 0;
	SmrtPeripheral* periperal = 0;

	switch (type)
	{
	case NRMCHardware::MotorController:
	case NRMCHardware::ServoController:
		tmp = srlPrtFactory->openPort(MicroMaestro12::connectedTo, 9600);	// we use a micromaestro for servo and motor control
		break;
	}

	if (tmp != 0)
		periperal = new SmrtPeripheral(*tmp, *this);

	return periperal;
}

