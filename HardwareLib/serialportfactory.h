#ifndef SERIALPORTFACTORY_H
#define SERIALPORTFACTORY_H

#include "smrtserialport.h"
#include "paritybit.h"

namespace NRMCHardware
{
	// Interface
	class SerialPortFactory
	{
	public:
		SerialPortFactory() {};
		~SerialPortFactory() {};
		virtual SmrtSerialPort* openPort(int baudRate, string portName) = 0;
		virtual SmrtSerialPort* openPort(ParityBit parity, string portName, int baudRate) = 0;
		virtual SmrtSerialPort* openPort(string portName, int baudRate, ParityBit parity, int dataBits) = 0;
		virtual SmrtSerialPort* openPort(int baudRate, ParityBit parity, int dataBits, StopBits stopBits, string portName) = 0;
		virtual SmrtSerialPort* openPort(bool(*checkConnected)(SerialPortInterface&), int baudRate) = 0;
		virtual SmrtSerialPort* openPort(int baudRate, ParityBit parity, bool(*checkConnected)(SerialPortInterface&)) = 0;
		virtual SmrtSerialPort* openPort(bool(*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity, int dataBits) = 0;
		virtual SmrtSerialPort* openPort(ParityBit parity, int dataBits, stopBit stopBits, int baudRate, bool(*checkConnected)(SerialPortInterface&)) = 0;
		virtual bool closePort(SmrtSerialPort& port) = 0;
		virtual void addPortToPool(string portName) = 0;
		virtual void removePortFromPool(string portName) = 0;
		virtual void refreshAvailablePorts() = 0;
	};
}
#endif
