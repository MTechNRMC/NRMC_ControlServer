#ifndef MDS_INTERFACE_H
#define MDS_INTERFACE_H

#include "message.h"

namespace NRMCNetwork
{
	// Interface
	class MDS_Interface
	{
	  // Associations
	  // Attributes
	  // Operations
	  public:
		MDS_Interface (  ) {}
		virtual ~MDS_Interface (  ) {}
		virtual void queueMessage ( Message* message ) = 0;
	};
}

#endif
