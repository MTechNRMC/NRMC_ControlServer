#ifndef LOCALIZATIONSYSTEM_H
#define LOCALIZATIONSYSTEM_H
#include <vector>

#include "localizationobserver.h"
#include "localizationinterface.h"
#include "position.h"

#include "../GHQ_Lib/ghqs_interface.h"

using std::vector;
using NRMC_GHQS::GHQS_Interface;

namespace NRMC_ACS
{
	class LocalizationSystem : public LocalizationInterface
	{
		// Associations
		// Attributes
	private:
		GHQS_Interface* ghqs;
		vector<LocalizationObserver*> subscribers;
		// Operations
	public:
		Position getPosition();
		LocalizationSystem(double xCenterOffset, double yCenterOffset, double xOffset, double yOffset, double resolution, GHQS_Interface& ghqs);
		~LocalizationSystem();
		void subscribe ( LocalizationObserver& subscriber );
		void unsubscribe ( LocalizationObserver& subscriber );
	};
}

#endif
