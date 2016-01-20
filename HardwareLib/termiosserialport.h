#ifndef TERMIOSSERIALPORT_H
#define TERMIOSSERIALPORT_H

#include "serialportinterface.h"

class TermiosSerialPort: public SerialPortInterface 
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
    string getPortName (  );
    int getBaudRate (  );
    TermiosSerialPort ( string portName );
    TermiosSerialPort ( string portName, speed_t baudRate );
    TermiosSerialPort ( string portName, speed_t baudRate, tcflag_t controlFlags );
    ~TermiosSerialPort (  );
    char* read (  );
    string readLine (  );
    char* read ( int size );
    string readLine ( char terminator );
    void write ( char* message );
    void write ( char* message, int size );
    void writeLine ( string line );
    void writeLine ( string line, char terminator );
    bool close (  );
};

#endif
