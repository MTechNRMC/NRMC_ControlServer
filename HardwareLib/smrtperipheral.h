#ifndef SMRTPERIPHERAL_H
#define SMRTPERIPHERAL_H

#include "peripheraltype.h"
#include "peripheral.h"
#include "hardwareinterface.h"

namespace NRMCHardware
{
	class HardwareInterface;

	class SmrtPeripheral
	{
		// Associations
		// Attributes
	private:
		Peripheral* peripheral;
		HardwareInterface* factory;
		// Operations
	public:
		PeripheralType getType();
		SmrtPeripheral(Peripheral& peripheral, HardwareInterface& factory);
		~SmrtPeripheral();
		Peripheral* getPeripheral();
	};
}
#endif
