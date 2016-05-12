#ifndef LOCALIZATIONINTERFACE_H
#define LOCALIZATIONINTERFACE_H

#include "position.h"
#include "localizationobserver.h"

// Interface
namespace NRMC_ACS
{
	class LocalizationInterface
	{
		// Associations
		// Attributes
		// Operations
	public:
		virtual Position getPosition() = 0;
		LocalizationInterface() {};
		virtual ~LocalizationInterface() {};
		virtual void subscribe ( LocalizationObserver& subscriber ) = 0;
		virtual void unsubscribe ( LocalizationObserver& observer ) = 0;
	};
}
#endif
