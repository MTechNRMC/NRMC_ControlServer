#ifndef TERMIOSSERIALPORT_H
#define TERMIOSSERIALPORT_H

#include <termios.h>
#include "serialportinterface.h"

namespace NRMCHardware
{
	class TermiosSerialPort : public SerialPortInterface
	{
		// Associations
		// Attributes
	private:
		int ttyFd;
		string portName;
		speed_t baudRate;
		tcflag_t  controlFlags;
		// Operations
	public:
		string getPortName();
		int getBaudRate();
		TermiosSerialPort(string portName, speed_t baudRate);
		TermiosSerialPort(string portName, speed_t baudRate, tcflag_t controlFlags);
		virtual ~TermiosSerialPort();
		char* readBytes();
		string readLine();
		char* readBytes(int size);
		string readLine(char terminator);
		void writeBytes(char* message);
		void writeBytes(char* message, int size);
		void writeLine(string line);
		void writeLine(string line, char terminator);
		bool closePort();
	};
}
#endif
