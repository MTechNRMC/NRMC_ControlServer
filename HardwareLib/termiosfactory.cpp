#include "termiosfactory.h"

using namespace NRMCHardware;

static TermiosFactory& TermiosFactory::getInstance (  )
{
	static TermiosFactory instance;

	return *instance;
}

SmrtSerialPort * TermiosFactory::openPort(string portName, int baudRate)
{
	return openPort(portName, baudRate, ParityBit::None);
}

SmrtSerialPort* TermiosFactory::openPort ( string portName, int baudRate, ParityBit parity )
{
	return openPort(portName, baudRate, parity, 8);
}

SmrtSerialPort* TermiosFactory::openPort ( string portName, int baudRate, ParityBit parity, int dataBits )
{
	return openPort(portName, baudRate, parity, dataBits, StopBit::One);
}

SmrtSerialPort* TermiosFactory::openPort ( string portName, int baudRate, ParityBit parity, int dataBits, StopBit stopBits )
{
	SmrtSerialPort* port = 0;
	SerialPortInterface* serialPort = openTermiosPort(portName, baudRate, parity, dataBits, stopBits);

	if (serialPort != 0)
		port = new SmrtSerialPort(*serialPort, *this);

	return port;
}

SmrtSerialPort * TermiosFactory::openPort(bool(*checkConnected)(SerialPortInterface &), int baudRate)
{
	return openPort(checkConnected, baudRate, ParityBit::None);
}

SmrtSerialPort* TermiosFactory::openPort ( bool (*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity )
{
	return openPort(checkConnected, baudRate, ParityBit::None, 8);
}

SmrtSerialPort* TermiosFactory::openPort ( bool (*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity, int dataBits )
{
	return openPort(checkConnected, baudRate, parity, dataBits, StopBit::One);
}

SmrtSerialPort* TermiosFactory::openPort ( bool (*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity, int dataBits, StopBit stopBits )
{
	for (vector<string>::iterator it = portPool.begin(); it != portPool.end(); ++it)
	{
		try
		{
			SerialPortInterface* tmpPort = openTermiosPort(*it, baudRate, parity, dataBits, stopBits);	// open a port that is in the pool

			// check if the port is connected to the device
			if (checkConnected(*tmpPort))
			{
				portPool.erase(it);
				return new SmrtSerialPort(*tmpPort, *this);
			}

			delete tmpPort;
			tmpPort = 0;
		}
		catch (exception e)
		{/*ignore excption*/}
	}

	// no device was found connected to the device
	return 0;
}

bool TermiosFactory::closePort(SmrtSerialPort& port)
{
	bool closed = port.serialPort->close();

	if(closed)
		addPortToPool(port.serialPort->getPortName());

	delete port.serialPort;

	return close;
}
void TermiosFactory::addPortToPool(string portName)
{
	portPool.push_back(portName);
}
void TermiosFactory::removePortFromPool(string portName)
{
	for (vector<string>::iterator it = portPool.begin(); it != portPool.end(); ++it)
	{
		if ((*it).compare(portName) != 0)
		{
			portPool.erase(it);
			break;
		}
	}
}
void TermiosFactory::refreshAvailablePorts()
{
	portPool.clear();	// clear the pool
}

TermiosFactory::TermiosFactory (  )
{
	// get the ports available
	refreshAvailablePorts();
}

TermiosFactory::~TermiosFactory (  )
{}

int NRMCHardware::TermiosFactory::openTermiosPort(string portName, int baudRate, ParityBit parity, int dataBits, StopBit stopBits)
{
	return 0;
}

