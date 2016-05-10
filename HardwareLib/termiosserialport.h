#ifndef TERMIOSSERIALPORT_H
#define TERMIOSSERIALPORT_H

#include <termios.h>
#include <vector>
#include "serialportinterface.h"

using std::vector;

namespace NRMCHardware
{
	class TermiosSerialPort : public SerialPortInterface
	{
		// Associations
		// Attributes
	private:
		bool open;
		int ttyFd;
		string portName;
		speed_t baudRate;
		tcflag_t  controlFlags;
		// Operations
	public:
		bool isOpen();
		string getPortName();
		int getBaudRate();
		TermiosSerialPort(string portName, speed_t baudRate);
		TermiosSerialPort(string portName, speed_t baudRate, tcflag_t controlFlags);
		virtual ~TermiosSerialPort();
		vector<char> readBytes();
		string readLine();
		vector<char> readBytes(int size);
		string readLine(char terminator);
		void writeBytes(vector<char>& message);
		void writeBytes(char* message, int size);
		void writeLine(string line);
		void writeLine(string line, char terminator);
		bool closePort();
	};
}
#endif
