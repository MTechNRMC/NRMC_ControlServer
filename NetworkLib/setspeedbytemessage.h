#ifndef OPCODEONLYMESSAGE_H
#define OPCODEONLYMESSAGE_H

#include "message.h"
#include "notimplementedexception.h"

namespace NRMCNetwork
{
	class SetSpeedByteMessage: public Message
	{
	  // Associations
	  // Attributes
	  private:
		char* rawMsg;
		int opcode;
		struct sockaddr_in& addr;
	  // Operations
	  public:
		SetSpeedByteMessage ( char* msg, struct sockaddr_in& addr );
		SetSpeedByteMessage ( int opcode, struct sockaddr_in& addr );
		SetSpeedByteMessage ( const SetSpeedByteMessage& msg );
		virtual ~SetSpeedByteMessage(  );
		struct sockaddr_in& getAddress (  ) const;
		char* getMessage (  ) const;
		int getOpcode (  ) const;
		unsigned short getMotorNum (  ) const;
		char getSpeed (  ) const;
		SetSpeedByteMessage* clone (  ) const;
	};
}

#endif
