#ifndef LOCALIZATIONINTERFACE_H
#define LOCALIZATIONINTERFACE_H

#include "position.h"

// Interface
namespace NRMC_ACS
{
	class LocalizationInterface
	{
		// Associations
		// Attributes
		// Operations
	public:
		LocalizationInterface() {};
		~LocalizationInterface() {};
		virtual Position getPosition() = 0;
	};
}
#endif
