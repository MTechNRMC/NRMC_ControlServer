#ifndef TERMIOSFACTORY_H
#define TERMIOSFACTORY_H

#include <string>
#include <vector>
#include <exception>
#include <termios.h>
#include <sys/stat.h>
#include "termiosserialport.h"
#include "serialportfactory.h"
#include "paritybit.h"
#include "stopbit.h"

using std::string;
using std::vector;
using std::exception;

namespace NRMCHardware
{
	// Singleton
	class TermiosFactory : public SerialPortFactory
	{
		// Attributes
	private:
		const string rootPortDir = "/sys/class/tty/";
	public:
		vector<string> portPool;
		// Operations
	public:
		static TermiosFactory& getInstance();
		SmrtSerialPort* openPort(string portName, int baudRate);
		SmrtSerialPort* openPort(string portName, int baudRate, ParityBit parity);
		SmrtSerialPort* openPort(string portName, int baudRate, ParityBit parity, int dataBits);
		SmrtSerialPort* openPort(string portName, int baudRate, ParityBit parity, int dataBits, StopBit stopBits);
		SmrtSerialPort* openPort(bool(*checkConnected)(SerialPortInterface&), int baudRate);
		SmrtSerialPort* openPort(bool(*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity);
		SmrtSerialPort* openPort(bool(*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity, int dataBits);
		SmrtSerialPort* openPort(bool(*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity, int dataBits, StopBit stopBits);
		bool closePort(SmrtSerialPort& port);
		void addPortToPool(string portName);
		void removePortFromPool(string portName);
		void refreshAvailablePorts();
	private:
		TermiosFactory();
		~TermiosFactory();
		SerialPortInterface* openTermiosPort(string portName, int baudRate, ParityBit parity, int dataBits, StopBit stopBits);
	};
}
#endif
