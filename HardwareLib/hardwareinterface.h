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
		HardwareInterface(  ){}
		virtual ~HardwareInterface(  ){}
		virtual SmrtPeripheral* getPeripheral ( PeripheralType type, bool forceConnect = false) = 0;
		virtual void returnPeripheral ( Peripheral& peripheral ) = 0;
	};
}

#endif
