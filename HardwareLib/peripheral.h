#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include <string>
#include "peripheraltype.h"

using std::string;

namespace NRMCHardware
{
	// Interface
	class Peripheral 
	{
	  // Associations
	  // Attributes
	  // Operations
	  public:
		Peripheral (  ){};
		~Peripheral (  ){};
		virtual PeripheralType getType (  ) = 0;
		virtual string getConnectedPort() = 0;
		virtual bool connectedTo ( SerialPortInterface& port ) = 0;
	};
}
#endif
