#include "termiosserialport.h"

using namespace NRMCHardware;

string TermiosSerialPort::getPortName (  )
{
}

int TermiosSerialPort::getBaudRate (  )
{
}

TermiosSerialPort::TermiosSerialPort ( string portName )
{
}

TermiosSerialPort::TermiosSerialPort ( string portName, speed_t baudRate )
{
}

TermiosSerialPort::TermiosSerialPort (string portName, speed_t baudRate, tcflag_t controlFlags)
{
}

TermiosSerialPort::~TermiosSerialPort (  )
{
}

char* TermiosSerialPort::read (  )
{
}

string TermiosSerialPort::readLine (  )
{
}

char* TermiosSerialPort::read ( int size )
{
}

string TermiosSerialPort::readLine ( char terminator )
{
}

void TermiosSerialPort::write ( char* message )
{
}

void TermiosSerialPort::write ( char* message, int size )
{
}

void TermiosSerialPort::writeLine ( string line )
{
}

void TermiosSerialPort::writeLine ( string line, char terminator )
{
}

bool TermiosSerialPort::close (  )
{
}

