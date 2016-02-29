#ifndef PERIPHERALFACTORY_H
#define PERIPHERALFACTORY_H

#include "smrtperipheral.h"
#include "serialportfactory.h"
#include "hardwareinterface.h"
#include "peripheraltype.h"

namespace NRMCHardware
{
	// Singleton
	class PeripheralFactory : public HardwareInterface
	{
		// Attributes
	private:
		SerialPortFactory* srlPrtFactory;
		vector<Peripheral*> peripheralPool;
		// Operations
	public:
		static PeripheralFactory& getInstance();
		SmrtPeripheral* getPeripheral(PeripheralType type);
		void attachFactory(SerialPortFactory* factory);
		void returnPeripheral(Peripheral& peripheral);
	private:
		PeripheralFactory();
		~PeripheralFactory();
	};
}
#endif
