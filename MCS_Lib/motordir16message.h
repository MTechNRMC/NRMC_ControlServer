#ifndef MOTORDIR16MESSAGE_H
#define MOTORDIR16MESSAGE_H

#include "message.h"

class MotorDir16Message: public Message 
{
  // Associations
  // Attributes
  private:
    char* rawMsg;
    int opcode;
    short motorDir;
    struct sockaddr_in& addr;
  // Operations
  public:
    MotorDir16Message ( char* msg, struct sockaddr_in& addr );
    MotorDir16Message ( int opcode, short motorDir, struct sockaddr_in& addr );
	MotorDir16Message ( const MotorDir16Message& msg);
    ~MotorDir16Message (  );
    struct sockaddr_in& getAddress (  ) const;
    char* getMessage (  ) const;
    int getOpcode (  ) const;
    int getMotorDir (  ) const;
    OpcodeOnlyMessage* clone (  ) const;
};

#endif
