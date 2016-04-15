#ifndef LOCALIZATIONSYSTEM_H
#define LOCALIZATIONSYSTEM_H

#include "localizationinterface.h"
#include "position.h"

#include "../GHQ_Lib/ghqs_interface.h"
#include "../GHQ_Lib/ghqs_observer.h"

using NRMC_GHQS::GHQS_Observer;
using NRMC_GHQS::GHQS_Interface;

namespace NRMC_ACS
{
	class LocalizationSystem : public GHQS_Observer, public LocalizationInterface
	{
		// Associations
		// Attributes
	public:
		GHQS_Interface* ghqs;
		// Operations
	public:
		Position getPosition();
		LocalizationSystem(double xCenterOffset, double yCenterOffset, double xOffset, double yOffset, double resolution, GHQS_Interface& ghqs);
		~LocalizationSystem();
		void notify();
	};
}

#endif
