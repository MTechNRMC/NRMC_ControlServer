#ifndef MOTORDIR16MESSAGE_H
#define MOTORDIR16MESSAGE_H

#include "message.h"

namespace NRMCNetwork
{
	class MotorDir16Message : public Message
	{
		// Associations
		// Attributes
	private:
		union Msg
		{
			char rawMsg[3];
			struct Data
			{
				char opcode;
				short motorDir;
			} data;
		} msg;
		struct sockaddr_in addr;
		// Operations
	public:
		MotorDir16Message(char* msg, struct sockaddr_in& addr);
		MotorDir16Message(int opcode, short motorDir, struct sockaddr_in& addr);
		MotorDir16Message ( const MotorDir16Message& msg );
		~MotorDir16Message();
		struct sockaddr_in getAddress() const;
		const char* getMessage() const;
		int getOpcode() const;
		int getMotorDir() const;
		MotorDir16Message* clone() const;
	};
}
#endif
