#ifndef SETSPEEDBYTEMESSAGE_H
#define SETSPEEDBYTEMESSAGE_H

#include "message.h"

namespace NRMCNetwork
{
	class SetSpeedByteMessage: public Message
	{
	  // Associations
	  // Attributes
	  private:
		int size;
		char* rawMsg;
		  struct Data
		  {
			  char opcode;
			  unsigned short motorNum;
			  char speed;
		  } data;
		struct sockaddr_in addr;
	  // Operations
	  public:
		int getSize() const;
		SetSpeedByteMessage ( char* msg, int size, struct sockaddr_in& addr );
		SetSpeedByteMessage ( int opcode, int motorNum, int speed, struct sockaddr_in& addr );
		SetSpeedByteMessage ( const SetSpeedByteMessage& msg );
		virtual ~SetSpeedByteMessage(  );
		sockaddr_in getAddress (  ) const;
		const char* getMessage (  ) const;
		int getOpcode (  ) const;
		int getMotorNum (  ) const;
		char getSpeed (  ) const;
		SetSpeedByteMessage* clone (  ) const;
	};
}

#endif
