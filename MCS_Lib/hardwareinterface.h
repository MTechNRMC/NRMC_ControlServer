#ifndef HARDWAREINTERFACE_H
#define HARDWAREINTERFACE_H

#include "peripheraltype.h"

// Interface
class HardwareInterface 
{
  // Associations
  // Attributes
  // Operations
  public:
	PeripheralInterface (  )	{};
    ~PeripheralInterface (  )	{};
    SmrtPeripheral* getPeripheral ( PeripheralType type );
    void returnPeripheral ( Peripheral& peripheral );
};

#endif
