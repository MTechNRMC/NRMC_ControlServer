#ifndef MANUALCONTROLSYSTEM_H
#define MANUALCONTROLSYSTEM_H

#include "exchangesubscriber.h"
#include "hardwareinterface.h"

class ManualControlSystem: public ExchangeSubscriber 
{
  // Associations
  // Attributes
  private:
    bool manualControl;
    MDS_Interface* networkInterface;
    HardwareInterface* hardwareInterface;
  // Operations
  public:
    ManualControlSystem ( MDS_Interface& networkInterface, HardwareInterface& hardwareInterface );
    ~ManualControlSystem (  );
    void queueMessage ( const Message& message );
    bool subscriberWants ( const Message& message );
};

#endif
