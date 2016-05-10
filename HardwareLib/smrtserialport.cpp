#include "smrtserialport.h"

using namespace NRMCHardware;

bool SmrtSerialPort::isClosed(  ) const
{
	return closed;
}

SerialPortInterface& SmrtSerialPort::getSerialPort(  ) const
{
	return serialPort;
}

SmrtSerialPort::SmrtSerialPort(SerialPortInterface& port, SerialPortFactory& factory)
{
	this->closed = false;
	this->serialPort = port;
	this->factory = factory;
}

SmrtSerialPort::~SmrtSerialPort (  )
{
	if (!closed)
		close();
}

bool SmrtSerialPort::close (  )
{
	closed = factory->closePort(*serialPort);

	return closed;
}

