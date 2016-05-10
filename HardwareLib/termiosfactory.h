#ifndef TERMIOSFACTORY_H
#define TERMIOSFACTORY_H

#include <string>
#include <termios.h>
#include <sys/stat.h>
#include "termiosserialport.h"
#include "serialportfactory.h"
#include "paritybit.h"
#include "stopbit.h"

using std::string;

namespace NRMCHardware
{
	// Singleton
	class TermiosFactory : public SerialPortFactory
	{
		// Attributes
		// Operations
	public:
		static TermiosFactory& getInstance();
		SerialPortInterface* openPort(string portName, int baudRate);
		SerialPortInterface* openPort(string portName, int baudRate, ParityBit parity);
		SerialPortInterface* openPort(string portName, int baudRate, ParityBit parity, int dataBits);
		SerialPortInterface* openPort(string portName, int baudRate, ParityBit parity, int dataBits, StopBit stopBits);
	private:
		TermiosFactory();
		~TermiosFactory();
		SerialPortInterface* openTermiosPort(string portName, int baudRate, ParityBit parity, int dataBits, StopBit stopBits);
		speed_t intTospeed_t(int baudRate);
	};
}
#endif
