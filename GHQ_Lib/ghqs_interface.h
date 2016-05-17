#ifndef GHQS_INTERFACE_H
#define GHQS_INTERFACE_H

#include "ghqs_observer.h"
#include "device.h"

#include "../NetworkLib/message.h"

using NRMCNetwork::Message;

namespace NRMC_GHQS
{
	class GHQS_Interface
	{
		// Associations
		// Attributes
		// Operations
	public:
		GHQS_Interface() {};
		virtual ~GHQS_Interface() {};
		virtual Message* queryHardware(Device device) = 0;
	};
}
#endif
