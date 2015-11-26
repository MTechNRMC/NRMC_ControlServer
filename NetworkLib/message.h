#ifndef MESSAGE_H
#define MESSAGE_H

#include <netinet/in.h>

namespace NRMCNetwork
{
	// Interface
	class Message
	{
	private:
	  // Operations
	  public:
		Message (  ) {}
		virtual ~Message (  ) {}
		virtual struct sockaddr_in& getAddress const (  ) = 0;
		virtual char* getMessage const (  ) = 0;
		virtual int getOpcode const (  ) = 0;
		virtual Message* clone const (  ) = 0;
	};
}

#endif
