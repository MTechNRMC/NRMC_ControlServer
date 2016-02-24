#include "smrtperipheral.h"

PeripheralType SmrtPeripheral::getType (  )
{
	return peripheral->getType();
}

SmrtPeripheral::SmrtPeripheral ( Peripheral& peripheral, HardwareInterface& factory )
{
	this->peripheral = peripheral;
	this->factory = factory;
}

SmrtPeripheral::~SmrtPeripheral (  )
{
	factory->returnPeripheral(peripheral);
}

Peripheral* SmrtPeripheral::peripheral (  )
{
	return peripheral;
}

