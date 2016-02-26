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
		  union Msg
		  {
			  char rawMsg[4];
			  struct Data
			  {
				  char opcode;
				  unsigned short motorNum;
				  char speed;
			  } data;
		  } msg;
		sockaddr_in addr;
	  // Operations
	  public:
		SetSpeedByteMessage ( char* msg, struct sockaddr_in& addr );
		SetSpeedByteMessage ( int opcode, int motorNum, int speed, struct sockaddr_in& addr );
		SetSpeedByteMessage ( const SetSpeedByteMessage& msg );
		virtual ~SetSpeedByteMessage(  );
		sockaddr_in& getAddress (  ) const;
		char* getMessage (  ) const;
		int getOpcode (  ) const;
		int getMotorNum (  ) const;
		char getSpeed (  ) const;
		SetSpeedByteMessage* clone (  ) const;
	};
}

#endif
