#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include <string>
#include "peripheraltype.h"
#include "peripheralsystem.h"

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
		virtual ~Peripheral (  ){};
		virtual PeripheralType getType (  ) = 0;
		virtual PeripheralSystem getSystem ( ) = 0;
		virtual string getConnectedPort(  ) = 0;
	};
}
#endif
