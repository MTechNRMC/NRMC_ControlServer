#ifndef SMRTPERIPHERAL_H
#define SMRTPERIPHERAL_H

#include "peripheraltype.h"
#include "peripheral.h"

class SmrtPeripheral 
{
  // Associations
  // Attributes
  private:
    Peripheral* peripheral;
    PeripheralInterface* factory;
  // Operations
  public:
    PeripheralType getType (  );
    SmrtPeripheral ( Peripheral& peripheral, PeripheralInterface& factory );
    ~SmrtPeripheral (  );
    Peripheral* peripheral (  );
};

#endif
