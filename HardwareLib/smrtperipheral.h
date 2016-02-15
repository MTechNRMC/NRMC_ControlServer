#ifndef SMRTPERIPHERAL_H
#define SMRTPERIPHERAL_H

#include "peripheraltype.h"
#include "peripheral.h"
#include "hardwareinterface.h"

class SmrtPeripheral 
{
  // Associations
  // Attributes
  private:
    Peripheral* peripheral;
	HardwareInterface* factory;
  // Operations
  public:
    PeripheralType getType (  );
    SmrtPeripheral ( Peripheral& peripheral, HardwareInterface& factory );
    ~SmrtPeripheral (  );
    Peripheral* peripheral (  );
};

#endif
