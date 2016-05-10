#include <fcntl.h>
#include <exception>
#include "termiosserialport.h"

using std::runtime_error;
using std::invalid_argument;

using namespace NRMCHardware;

string NRMCHardware::TermiosSerialPort::getPortName (  )
{
	return portName;
}

int TermiosSerialPort::getBaudRate (  )
{
	// set the correct baudRate
	switch (baudRate)
	{
	case B50:
		return 50;
		break;
	case B75:
		return 75;
		break;
	case B110:
		return 110;
		break;
	case B134:
		return 134;
		break;
	case B150:
		return 150;
		break;
	case B200:
		return 200;
		break;
	case B300:
		return 300;
		break;
	case B600:
		return 600;
		break;
	case B1200:
		return 1200;
		break;
	case B1800:
		return 1800;
		break;
	case B2400:
		return 2400;
		break;
	case B4800:
		return 4800;
		break;
	case B9600:
		return 9600;
		break;
	case B19200:
		return 19200;
		break;
	case B38400:
		return 38400;
		break;
	case B57600:
		return 57600;
		break;
	case B115200:
		return 115200;
		break;
	case B230400:
		return 230400;
		break;
	case B460800:
		return 460800;
		break;
	case B500000:
		return 500000;
		break;
	case B576000:
		return 576000;
		break;
	case B921600:
		return 921600;
		break;
	case B1000000:
		return 1000000;
		break;
	case B1152000:
		return 1152000;
		break;
	case B1500000:
		return 1500000;
		break;
	case B2000000:
		return 2000000;
		break;
	case B2500000:
		return 2500000;
		break;
	case B3000000:
		return 3000000;
		break;
	case B3500000:
		return 3500000;
		break;
	case B4000000:
		return 4000000;
		break;
	default:
		return 0; // bad baud
	}
}

// set port to 8bit no parity with 1 stop bit with specified baudRate
TermiosSerialPort::TermiosSerialPort ( string portName, speed_t baudRate ) : TermiosSerialPort(portName, baudRate, CS8)
{}

TermiosSerialPort::TermiosSerialPort (string portName, speed_t baudRate, tcflag_t controlFlags)
{
	static const int controlMask = ~(CSIZE | CSTOPB | PARENB | PARODD);

	termios config;

	this->ttyFd = open(portName.c_str(), O_RDWR|O_NOCTTY|O_NONBLOCK);
	this->portName = portName;
	this->baudRate = baudRate;
	this->controlFlags = controlFlags;

	memset(&config, 0, sizeof(config));

	if(ttyFd == -1)
		throw runtime_error("Failed to open: "+portName);

	if(!isatty(ttyFd))
		throw invalid_argument(portName+" is not a valid serial port");

	if(tcgetattr(ttyFd, &config))
		throw runtime_error("Failed to get the configuration for: "+portName);

	config.c_cflag &= controlMask;	// clear the size stop and parity flags
	config.c_cflag |= controlFlags;	// set the control flags

	// set baud
	if(cfsetispeed(&config, baudRate) < 0 || cfsetospeed(&config, baudRate))
		throw runtime_error("Error setting baud rate for: "+portName);

	// apply the configuration
	if(tcsetattr(ttyFd, TCSAFLUSH, &config) < 0)
		throw runtime_error("Unable to apply configuration to: "+portName);
}

TermiosSerialPort::~TermiosSerialPort (  )
{
	closePort();	// close the serial port
}

vector<char> TermiosSerialPort::readBytes (  )
{
	char byte;
	vector<char> buffer;		// create a vector to store the bytes that are read in

	// read all the data from the buffer in
	while(read(ttyFd, &byte, 1) > 0)
		buffer.push_back(byte);

	return buffer;
}

string TermiosSerialPort::readLine (  )
{
	readLine('\n');		// default to reading to the newline
}

vector<char> TermiosSerialPort::readBytes ( int size )
{
	char* buffer = new char[size];		// create a buffer the size of the bytes that need to be received
	memset(buffer, 0, size);			// 0 the buffer
	read(ttyFd, buffer, size);			// read the message
	vector<char> msg(buffer,size);
	delete buffer;
	buffer = 0;

	return msg;							// return the what was read
}

string TermiosSerialPort::readLine ( char terminator )
{
	char character = '';
	string msg = "";

	// read the first char in
	read(ttyFd, &character, 1);

	// read until the terminator is read
	while(character != terminator)
	{
		msg += character;
		read(ttyFd, &character, 1);
	}

	return msg;
}

void TermiosSerialPort::writeBytes( vector<char>& message )
{
	writeBytes(&message[0], message.size());
}

void TermiosSerialPort::writeBytes ( char* message, int size )
{
	write(ttyFd, message, size);
}

void TermiosSerialPort::writeLine ( string line )
{
	writeBytes((char*)line.c_str(), line.size());
}

void TermiosSerialPort::writeLine ( string line, char terminator )
{
	line += terminator;		// append the terminator char
	writeLine(line);
}

bool TermiosSerialPort::closePort (  )
{
	if(close(ttyFd) < 0)
		return false;
	return true;
}

