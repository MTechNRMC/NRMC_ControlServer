#include "termiosfactory.h"

static TermiosFactory& TermiosFactory::getInstance (  )
{
}

SmrtSerialPort* TermiosFactory::openPort ( string portName, int baudRate, ParityBit parity )
{
}

SmrtSerialPort* TermiosFactory::openPort ( string portName, int baudRate, ParityBit parity, int dataBits )
{
}

SmrtSerialPort* TermiosFactory::openPort ( string portName, int baudRate, ParityBit parity, int dataBits, StopBits stopBits )
{
}

SmrtSerialPort* TermiosFactory::openPort ( bool (*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity )
{
}

SmrtSerialPort* TermiosFactory::openPort ( bool (*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity, int dataBits )
{
}

SmrtSerialPort* TermiosFactory::openPort ( bool (*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity, int dataBits, stopBit stopBits )
{
}

TermiosFactory::TermiosFactory (  )
{
}

TermiosFactory::~TermiosFactory (  )
{
}

