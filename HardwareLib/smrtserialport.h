#ifndef SMRTSERIALPORT_H
#define SMRTSERIALPORT_H

#include "serialportinterface.h"
#include "serialportfactory.h"

namespace NRMCHardware
{
	class SmrtSerialPort
	{
		// Associations
		// Attributes
	private:
		bool closed;
		SerialPortInterface* serialPort;
		SerialPortFactory* factory;
		// Operations
	public:
		bool isClosed() const;
		SerialPortInterface& serialPort() const;
		SmrtSerialPort(SerialPortInterface& port, SerialPortFactory& factory);
		~SmrtSerialPort();
		bool close();
	};
}
#endif
