#include "peripheralfactory.h"

using namespace NRMCHardware;

static PeripheralFactory& PeripheralFactory::getInstance (  )
{
}

SmrtPeripheral* PeripheralFactory::getPeripheral ( PeripheralType type )
{
}

void PeripheralFactory::attachFactory ( SerialPortFactory* factory )
{
}

void PeripheralFactory::returnPeripheral ( Peripheral& peripheral )
{
}

PeripheralFactory::PeripheralFactory (  )
{
}

PeripheralFactory::~PeripheralFactory (  )
{
}

