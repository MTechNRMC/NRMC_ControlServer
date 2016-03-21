#ifndef SERIALPORTINTERFACE_H
#define SERIALPORTINTERFACE_H

#include <string>

using std::string;

namespace NRMCHardware
{
	// Interface
	class SerialPortInterface
	{
		// Associations
		// Attributes
		// Operations
	public:
		virtual string getPortName() = 0;
		virtual int getBaudRate() = 0;
		SerialPortInterface() {};
		virtual ~SerialPortInterface() {};
		virtual char* readBytes() = 0;
		virtual string readLine() = 0;
		virtual char* readBytes(int size) = 0;
		virtual string readLine(char terminator) = 0;
		virtual void writeBytes(char* message) = 0;
		virtual void writeBytes(char* message, int size) = 0;
		virtual void writeLine(string line) = 0;
		virtual void writeLine(string line, char terminator) = 0;
		virtual bool closePort() = 0;
	};
}
#endif
