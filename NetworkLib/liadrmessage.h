#ifndef LIADRMESSAGE_H
#define LIADRMESSAGE_H

#include "message.h"

namespace NRMCNetwork
{
	class LIADRMessage : public Message
	{
		// Associations
		// Attributes
	private:
		int opcode;
		double distance;
		double angle;
		sockaddr_in& addr;
		// Operations
	public:
		LIADRMessage(char* msg, sockaddr_in& addr);
		LIADRMessage(int opcode, double distance, double angle, sockaddr_in& addr);
		LIADRMessage(const LIADRMessage& msg);
		~LIADRMessage();
		double getDistance();
		double getAngle();
		double getScanRate();
		int getRPM();
		int getOpcode();
		sockaddr_in& getAddress();
		char* getMessage();
	};
}

#endif
