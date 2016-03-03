#ifndef SERIALPORTFACTORY_H
#define SERIALPORTFACTORY_H

#include <string>
#include "smrtserialport.h"
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
		virtual SmrtSerialPort* openPort(string portName, int baudRate) = 0;
		virtual SmrtSerialPort* openPort(string portName, int baudRate, ParityBit parity) = 0;
		virtual SmrtSerialPort* openPort(string portName, int baudRate, ParityBit parity, int dataBits) = 0;
		virtual SmrtSerialPort* openPort(string portName, int baudRate, ParityBit parity, int dataBits, StopBit stopBits) = 0;
		virtual SmrtSerialPort* openPort(bool(*checkConnected)(SerialPortInterface&), int baudRate) = 0;
		virtual SmrtSerialPort* openPort(bool(*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity) = 0;
		virtual SmrtSerialPort* openPort(bool(*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity, int dataBits) = 0;
		virtual SmrtSerialPort* openPort(bool(*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity, int dataBits, StopBit stopBits) = 0;
		virtual bool closePort(SmrtSerialPort& port) = 0;
		virtual void addPortToPool(string portName) = 0;
		virtual void removePortFromPool(string portName) = 0;
		virtual void refreshAvailablePorts() = 0;
	};
}
#endif
