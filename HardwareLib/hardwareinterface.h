#ifndef HARDWAREINTERFACE_H
#define HARDWAREINTERFACE_H

#include "peripheraltype.h"

namespace NRMCHardware
{
	// Interface
	class HardwareInterface 
	{
	  // Associations
	  // Attributes
	  // Operations
	  public:
		PeripheralInterface (  )	{};
		~PeripheralInterface (  )	{};
		SmrtPeripheral* getPeripheral ( PeripheralType type, bool forceConnect = false) = 0;
		void returnPeripheral ( Peripheral& peripheral ) = 0;
	};
}

#endif
