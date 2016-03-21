#include <vector>
#include <fcntl.h>
#include <exception>
#include "termiosserialport.h"

using std::vector;
using std::runtime_error;
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

TermiosSerialPort::TermiosSerialPort ( string portName, speed_t baudRate )
{
	tcflag_t defaultFlags = 0;

	// set 8bit no parity with 1 stop bit
	defaultFlags |= CS8;	// note that by only setting the data size no parity and 1 stop bit are already set as they are 0

	TermiosSerialPort(portName, baudRate, defaultFlags);
}

TermiosSerialPort::TermiosSerialPort (string portName, speed_t baudRate, tcflag_t controlFlags)
{
	this->ttyFd = open(portName.c_str(), O_RDWR|O_NONBLOCK);
	this->portName = portName;
	this->baudRate = baudRate;
	this->controlFlags = controlFlags;

	termios tty;
	memset(&tty, 0, sizeof(tty));
	if(tcgetattr(this->ttyFd, &tty) != 0)
		throw runtime_error("");
}

TermiosSerialPort::~TermiosSerialPort (  )
{
	closePort();	// close the serial port
}

char* TermiosSerialPort::readBytes (  )
{
	char byte;
	char* msg;
	vector<char> buffer;		// create a vector to store the bytes that are read in

	// read all the data from the buffer in
	while(read(ttyFd, &byte, 1) > 0)
		buffer.push_back(byte);

	msg = new char[buffer.size()];
	// create a copy of the message
	for(int b=0; b<buffer.size(); b++)
		msg[b] = buffer[b];

	return msg;
}

string TermiosSerialPort::readLine (  )
{
	readLine('\n');		// default to reading to the newline
}

char* TermiosSerialPort::readBytes ( int size )
{
	char* buffer = new char[size];		// create a buffer the size of the bytes that need to be received
	memset(buffer, 0, size);			// 0 the buffer
	read(ttyFd, buffer, size);			// read the message

	return buffer;						// return the buffer
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

void TermiosSerialPort::writeBytes ( char* message )
{
	write(ttyFd, message, sizeof(message));
}

void TermiosSerialPort::writeBytes ( char* message, int size )
{
	write(ttyFd, message, size);
}

void TermiosSerialPort::writeLine ( string line )
{
	writeBytes((char*)line.c_str());
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

