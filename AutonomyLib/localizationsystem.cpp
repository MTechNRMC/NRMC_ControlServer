#include "localizationsystem.h"
#include <functional>

using namespace NRMC_ACS;
using std::bad_function_call;

Position LocalizationSystem::getPosition (  )
{
	throw bad_function_call();
}

LocalizationSystem::LocalizationSystem ( double xCenterOffset, double yCenterOffset, double xOffset, double yOffset, double resolution, GHQS_Interface& ghqs )
{
}

LocalizationSystem::~LocalizationSystem (  )
{
}

void LocalizationSystem::notify (  )
{
	throw bad_function_call();
}

