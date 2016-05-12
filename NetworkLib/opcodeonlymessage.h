#ifndef OPCODEONLYMESSAGE_H
#define OPCODEONLYMESSAGE_H

#include "message.h"

namespace NRMCNetwork
{
	class OpcodeOnlyMessage: public Message
	{
	  // Associations
	  // Attributes
	  private:
		char* rawMsg;
		int opcode, size;
		sockaddr_in addr;
	  // Operations
	  public:
		OpcodeOnlyMessage ( char* msg, int size, struct sockaddr_in& addr );
		OpcodeOnlyMessage ( int opcode, struct sockaddr_in& addr );
		OpcodeOnlyMessage ( const OpcodeOnlyMessage& msg );
		virtual ~OpcodeOnlyMessage(  );
		int getSize() const;
		struct sockaddr_in getAddress (  ) const;
		const char* getMessage (  ) const;
		int getOpcode (  ) const;
		OpcodeOnlyMessage* clone (  ) const;
	};
}

#endif
