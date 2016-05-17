#include "localizationsystem.h"
#include <functional>

using namespace NRMC_ACS;
using std::bad_function_call;

Position LocalizationSystem::getPosition (  )
{
	throw bad_function_call();
}

LocalizationSystem::LocalizationSystem ( double xOffset, double yOffset, GHQS_Interface& ghqs )
{
}

LocalizationSystem::~LocalizationSystem (  )
{
}

void LocalizationSystem::subscribe ( LocalizationObserver& subscriber )
{
}

void LocalizationSystem::unsubscribe ( LocalizationObserver& subscriber )
{
}
