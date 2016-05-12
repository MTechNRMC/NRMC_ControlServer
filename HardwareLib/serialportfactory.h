#ifndef SERIALPORTFACTORY_H
#define SERIALPORTFACTORY_H

#include <string>
#include "serialportinterface.h"
#include "paritybit.h"
#include "stopbit.h"

using std::string;

namespace NRMCHardware
{
	// Interface
	class SerialPortFactory
	{
	public:
		SerialPortFactory() {};
		virtual ~SerialPortFactory() {};
		virtual SerialPortInterface* openPort(string portName, int baudRate) = 0;
		virtual SerialPortInterface* openPort(string portName, int baudRate, ParityBit parity) = 0;
		virtual SerialPortInterface* openPort(string portName, int baudRate, ParityBit parity, int dataBits) = 0;
		virtual SerialPortInterface* openPort(string portName, int baudRate, ParityBit parity, int dataBits, StopBit stopBits) = 0;
	};
}
#endif
