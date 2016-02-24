#include "smrtserialport.h"

bool SmrtSerialPort::isClosed const (  )
{
	return closed;
}

SerialPortInterface& SmrtSerialPort::serialPort const (  )
{
	return serialPort;
}

SmrtSerialPort::SmrtSerialPort ( SerialPortInterface& port, SerialPortFactory& factory )
{
	this->closed = false;
	this->serialPort = port;
	this->factory = factory;
}

SmrtSerialPort::~SmrtSerialPort (  )
{
	if (!closed)
		factory->close(this);
}

bool SmrtSerialPort::close (  )
{
	closed = factory->close(this);

	return closed;
}

