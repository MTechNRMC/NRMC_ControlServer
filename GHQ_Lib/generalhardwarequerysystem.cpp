#include "generalhardwarequerysystem.h"

using namespace NRMC_GHQS;

static GHQS_Interface& GeneralHardwareQuerySystem::getInstance (  )
{
}

void GeneralHardwareQuerySystem::queueMessage ( Message& message )
{
}

bool GeneralHardwareQuerySystem::subscriberWants ( Message& message )
{
}

Message* GeneralHardwareQuerySystem::queryHardware ( Device device )
{
}

bool GeneralHardwareQuerySystem::startHardwareStream ( GHQS_Observer& observer )
{
}

bool GeneralHardwareQuerySystem::stopHardwareStream ( GHQS_Observer& observer )
{
}

GeneralHardwareQuerySystem::GeneralHardwareQuerySystem ( MDS_Interface& mdSystem, HardwareInterface& hardwareLayer )
{
}

GeneralHardwareQuerySystem::~GeneralHardwareQuerySystem (  )
{
}

