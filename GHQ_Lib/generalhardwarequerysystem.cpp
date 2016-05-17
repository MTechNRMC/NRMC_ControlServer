#include "generalhardwarequerysystem.h"
#include <exception>

using namespace NRMC_GHQS;
using std::bad_function_call;

GHQS_Interface& GeneralHardwareQuerySystem::getInstance (  )
{
	throw bad_function_call();
}

void GeneralHardwareQuerySystem::queueMessage ( Message& message )
{
	throw bad_function_call();
}

bool GeneralHardwareQuerySystem::subscriberWants ( Message& message )
{
	throw bad_function_call();
}

Message* GeneralHardwareQuerySystem::queryHardware ( Device device )
{
	Message* msg = 0;

	return msg;
}

bool GeneralHardwareQuerySystem::startHardwareStream ( GHQS_Observer& observer )
{
	throw bad_function_call();
}

bool GeneralHardwareQuerySystem::stopHardwareStream ( GHQS_Observer& observer )
{
	throw bad_function_call();
}

GeneralHardwareQuerySystem::GeneralHardwareQuerySystem ( MDS_Interface& mdSystem, HardwareInterface& hardwareLayer )
{
}

GeneralHardwareQuerySystem::~GeneralHardwareQuerySystem (  )
{
}

