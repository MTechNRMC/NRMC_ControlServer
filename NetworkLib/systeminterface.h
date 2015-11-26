#ifndef SYSTEMINTERFACE_H
#define SYSTEMINTERFACE_H

namespace NRMCNetwork
{
	// Interface
	class SystemInterface
	{
	  // Associations
	  // Attributes
	  // Operations
	  public:
		SystemInterface (  ) {}
		virtual ~SystemInterface (  ) {}
		virtual bool startSystem (  ) = 0;
		virtual bool stopSystem (  ) = 0;
	};
}

#endif
