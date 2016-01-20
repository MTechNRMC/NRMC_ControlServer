#ifndef SERIALPORTINTERFACE_H
#define SERIALPORTINTERFACE_H


// Interface
class SerialPortInterface 
{
  // Associations
  // Attributes
  // Operations
  public:
    virtual string getPortName (  ) = 0;
    virtual int getBaudRate (  ) = 0;
    SerialPortInterface (  ){};
    ~SerialPortInterface (  ){};
    virtual char* read (  ) = 0;
    virtual string readLine (  ) = 0;
    virtual char* read ( int size ) = 0;
    virtual string readLine ( char terminator ) = 0;
    virtual void write ( char* message ) = 0;
    virtual void write ( char* message, int size ) = 0;
    virtual void writeLine ( string line ) = 0;
    virtual void writeLine ( string line, char terminator ) = 0;
    virtual bool close (  ) = 0;
};

#endif
