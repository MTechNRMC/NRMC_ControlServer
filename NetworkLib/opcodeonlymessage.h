#ifndef OPCODEONLYMESSAGE_H
#define OPCODEONLYMESSAGE_H

#include <exception>
#include "message.h"
#include "notimplementedexception.h"

using std::exception;

namespace NRMCNetwork
{
	class OpcodeOnlyMessage: public Message
	{
	  // Associations
	  // Attributes
	  private:
		char* rawMsg;
		int opcode;
		sockaddr_in addr;
	  // Operations
	  public:
		OpcodeOnlyMessage ( char* msg, struct sockaddr_in& addr );
		OpcodeOnlyMessage ( int opcode, struct sockaddr_in& addr );
		OpcodeOnlyMessage ( const OpcodeOnlyMessage& msg );
		virtual ~OpcodeOnlyMessage(  );
		struct sockaddr_in& getAddress (  ) const;
		char* getMessage (  ) const;
		int getOpcode (  ) const;
		OpcodeOnlyMessage* clone (  ) const;
	};
}

#endif
