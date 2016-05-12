#include "termiosfactory.h"
#include <stdexcept>

using std::runtime_error;

using namespace NRMCHardware;

TermiosFactory& TermiosFactory::getInstance (  )
{
	static TermiosFactory instance;

	return instance;
}

SerialPortInterface * TermiosFactory::openPort(string portName, int baudRate)
{
	return openPort(portName, baudRate, ParityBit::None);
}

SerialPortInterface* TermiosFactory::openPort ( string portName, int baudRate, ParityBit parity )
{
	return openPort(portName, baudRate, parity, 8);
}

SerialPortInterface* TermiosFactory::openPort ( string portName, int baudRate, ParityBit parity, int dataBits )
{
	return openPort(portName, baudRate, parity, dataBits, StopBit::One);
}

SerialPortInterface* TermiosFactory::openPort ( string portName, int baudRate, ParityBit parity, int dataBits, StopBit stopBits )
{
	SerialPortInterface* serialPort = openTermiosPort(portName, baudRate, parity, dataBits, stopBits);

	return serialPort;
}

TermiosFactory::TermiosFactory (  )
{}

TermiosFactory::~TermiosFactory (  )
{}

SerialPortInterface* NRMCHardware::TermiosFactory::openTermiosPort(string portName, int baudRate, ParityBit parity, int dataBits, StopBit stopBits)
{
	speed_t rate;
	tcflag_t flags = 0;	// set all bits to low

	// set the correct baudRate
	rate = intTospeed_t(baudRate);

	// check if a good baud was returned
	if(rate == B0)
		throw runtime_error("Invalid baud rate passed. See termios.h for valid baud rates");

	/*	Keep for reference later
	// clear parity, stop, and data size bits
	flags &= ~(PARENB | CSTOPB | CSIZE);*/

	// set the control attributes
	// set parity bit first Linux can only use Odd or Even
	switch(parity)
	{
	case ParityBit::Even:
		flags |= PARENB;	// enable parity odd bit is low so even mode is active
		break;
	case ParityBit::Odd:
		flags |= PARENB;	// enable parity
		flags |= PARODD;	// set the odd bit for odd mode
		break;
	case ParityBit::None:
		break;		// parity is already disabled
	default:
		throw runtime_error("Invalid parity passed. Termios only supports Even, Odd or no parity");
	}

	// set data bits Linux can only use 5,6,7,8 bits
	switch(dataBits)
	{
	case 5:
		flags |= CS5;	// 5 data bits
		break;
	case 6:
		flags |= CS6;	// 6 data bits
		break;
	case 7:
		flags |= CS7;	// 7 data bits
		break;
	case 8:
		flags |= CS8;	// 8 data bits
		break;
	default:
		throw runtime_error("Invalid data size passed. Termios only supports 5, 6, 7, and 8");
	}

	// set the stop bit Linux can only use 1 or 2
	switch(stopBits)
	{
	case StopBit::One:
		break;				// already set to one stop bit
	case StopBit::Two:
		flags |= CSTOPB;	// set two stop bits
		break;
	default:
		throw runtime_error("Invalid stop bit passed. Termios only supports One or Two stop bit(s)");
	}

	return new TermiosSerialPort(portName, rate, flags);	// create the new serial port
}

speed_t NRMCHardware::TermiosFactory::intTospeed_t(int baudRate)
{
	speed_t rate;

	// set the correct baudRate
	switch (baudRate) {
	case 50:
		rate = B50;
		break;
	case 75:
		rate = B75;
		break;
	case 110:
		rate = B110;
		break;
	case 134:
		rate = B134;
		break;
	case 150:
		rate = B150;
		break;
	case 200:
		rate = B200;
		break;
	case 300:
		rate = B300;
		break;
	case 600:
		rate = B600;
		break;
	case 1200:
		rate = B1200;
		break;
	case 1800:
		rate = B1800;
		break;
	case 2400:
		rate = B2400;
		break;
	case 4800:
		rate = B4800;
		break;
	case 9600:
		rate = B9600;
		break;
	case 19200:
		rate = B19200;
		break;
	case 38400:
		rate = B38400;
		break;
	case 57600:
		rate = B57600;
		break;
	case 115200:
		rate = B115200;
		break;
	case 230400:
		rate = B230400;
		break;
	case 460800:
		rate = B460800;
		break;
	case 500000:
		rate = B500000;
		break;
	case 576000:
		rate = B576000;
		break;
	case 921600:
		rate = B921600;
		break;
	case 1000000:
		rate = B1000000;
		break;
	case 1152000:
		rate = B1152000;
		break;
	case 1500000:
		rate = B1500000;
		break;
	case 2000000:
		rate = B2000000;
		break;
	case 2500000:
		rate = B2500000;
		break;
	case 3000000:
		rate = B3000000;
		break;
	case 3500000:
		rate = B3500000;
		break;
	case 4000000:
		rate = B4000000;
		break;
	default:
		rate = B0; // bad baud
	}

	return rate;
}
