#ifndef PERIPHERALFACTORY_H
#define PERIPHERALFACTORY_H

#include <vector>
#include "smrtperipheral.h"
#include "serialportfactory.h"
#include "hardwareinterface.h"
#include "peripheralsystem.h"

using std::vector;

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
		SmrtPeripheral* getPeripheral(PeripheralSystem sys, bool forceConnect = false);
		void attachFactory(SerialPortFactory& factory);
		void returnPeripheral(Peripheral& peripheral);
	private:
		PeripheralFactory();
		~PeripheralFactory();
		SmrtPeripheral* checkPool(PeripheralSystem sys);
		SmrtPeripheral* connectPeripheral(PeripheralSystem sys);
	};
}
#endif
