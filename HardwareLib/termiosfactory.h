#ifndef TERMIOSFACTORY_H
#define TERMIOSFACTORY_H

#include "termiosserialport.h"
#include "serialportfactory.h"
#include "paritybit.h"

// Singleton
class TermiosFactory: public SerialPortFactory 
{
  // Attributes
  public:
    vector<string> portPool;
  // Operations
  public:
    static TermiosFactory& getInstance (  );
    SmrtSerialPort* openPort ( string portName, int baudRate );
    SmrtSerialPort* openPort ( string portName, int baudRate, ParityBit parity );
    SmrtSerialPort* openPort ( string portName, int baudRate, ParityBit parity, int dataBits );
    SmrtSerialPort* openPort ( string portName, int baudRate, ParityBit parity, int dataBits, StopBits stopBits );
    SmrtSerialPort* openPort ( bool (*checkConnected)(SerialPortInterface&), int baudRate );
    SmrtSerialPort* openPort ( bool (*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity );
    SmrtSerialPort* openPort ( bool (*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity, int dataBits );
    SmrtSerialPort* openPort ( bool (*checkConnected)(SerialPortInterface&), int baudRate, ParityBit parity, int dataBits, stopBit stopBits );
    bool closePort ( SmrtSerialPort& port );
    void addPortToPool ( string portName );
    void removePortFromPool ( string portName );
    void refreshAvailablePorts (  );
  private:
    TermiosFactory (  );
    ~TermiosFactory (  );
};

#endif
