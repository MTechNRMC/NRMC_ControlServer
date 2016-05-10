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

SmrtSerialPort * TermiosFactory::openPort(bool(*checkConnected)(SerialPortInterface&), int baudRate)
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
		catch (exception& e)
		{/*ignore exception*/}
	}

	// no device was found connected to the device
	return 0;
}

bool TermiosFactory::closePort(SmrtSerialPort& port)
{
	bool closed = port.getSerialPort().closePort();

	if(closed)
		addPortToPool(port.getSerialPort().getPortName());

	delete port.serialPort;

	return closed;
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

	// find all active ttys and add them to the list
	for(int x = 0; x < 256; x++)
	{
		string ttyACM = rootPortDir + "ACM" + string(x) + "/device";
		string ttyUSB = rootPortDir + "USB" + string(x) + "/device";
		struct stat sb;

		// check for ACM
		if(lstat(ttyACM.c_str(), &sb) == 0)
			portPool.push_back(ttyACM);	// port exists

		// check for USB
		if(lstat(ttyUSB.c_str(), &sb) == 0)
					portPool.push_back(ttyUSB);	// port exists
	}
}

TermiosFactory::TermiosFactory (  )
{
	// get the ports available
	refreshAvailablePorts();
}

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
		throw exception("Invalid baud rate passed. See termios.h for valid baud rates");

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
		throw exception("Invalid parity passed. Termios only supports Even, Odd or no parity");
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
		throw exception("Invalid data size passed. Termios only supports 5, 6, 7, and 8");
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
		throw exception("Invalid stop bit passed. Termios only supports One or Two stop bit(s)");
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
