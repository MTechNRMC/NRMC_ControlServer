#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include "peripheraltype.h"

// Interface
class Peripheral 
{
  // Associations
  // Attributes
  // Operations
  public:
    Peripheral (  ){};
    ~Peripheral (  ){};
    PeripheralType getType (  );
    virtual bool connectedTo ( SerialPortInterface& port ) = 0;
};

#endif
