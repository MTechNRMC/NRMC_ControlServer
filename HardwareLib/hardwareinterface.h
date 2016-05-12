#ifndef HARDWAREINTERFACE_H
#define HARDWAREINTERFACE_H

#include "smrtperipheral.h"
#include "peripheralsystem.h"

namespace NRMCHardware
{
	class SmrtPeripheral;

	// Interface
	class HardwareInterface 
	{
	  // Associations
	  // Attributes
	  // Operations
	  public:
		HardwareInterface(  ){}
		virtual ~HardwareInterface(  ){}
		virtual SmrtPeripheral* getPeripheral ( PeripheralSystem sys, bool forceConnect = false) = 0;
		virtual void returnPeripheral ( Peripheral& peripheral ) = 0;
	};
}

#endif
