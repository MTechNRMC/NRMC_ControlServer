#ifndef PERIPHERALFACTORY_H
#define PERIPHERALFACTORY_H

#include <vector>
#include "smrtperipheral.h"
#include "serialportfactory.h"
#include "hardwareinterface.h"
#include "peripheraltype.h"
#include "micromaestro12.h"

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
		SmrtPeripheral* getPeripheral(PeripheralType type, bool forceConnect = false);
		void attachFactory(SerialPortFactory& factory);
		void returnPeripheral(Peripheral& peripheral);
	private:
		PeripheralFactory();
		~PeripheralFactory();
		SmrtPeripheral* checkPool(PeripheralType type);
		SmrtPeripheral* connectPeripheral(PeripheralType type);
	};
}
#endif
