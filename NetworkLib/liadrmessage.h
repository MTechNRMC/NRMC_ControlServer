#ifndef LIADRMESSAGE_H
#define LIADRMESSAGE_H

#include "message.h"
#include <vector>
#include "../HardwareLib/lidar.h"

using NRMCHardware::ScanPoint;
using std::vector;

namespace NRMCNetwork
{
	class LIADRMessage : public Message
	{
		// Associations
		// Attributes
	private:
		int opcode;
		vector<ScanPoint> scan;
		sockaddr_in& addr;
		// Operations
	public:
		LIADRMessage(char* msg, sockaddr_in& addr);
		LIADRMessage(int opcode, vector<ScanPoint>& scan, sockaddr_in& addr);
		LIADRMessage(const LIADRMessage& msg);
		~LIADRMessage();
		vector<ScanPoint>& getScan();
		int getOpcode() const;
		sockaddr_in getAddress() const;
		const char* getMessage() const;
		Message* clone(  ) const;
		int getSize() const;
	};
}

#endif
