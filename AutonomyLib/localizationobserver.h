#ifndef LOCALIZATIONOBSERVER_H
#define LOCALIZATIONOBSERVER_H


namespace NRMC_ACS
{
	// Interface
	class LocalizationObserver 
	{
	  // Associations
	  // Attributes
	  // Operations
	  public:
		LocalizationObserver() {};
		virtual ~LocalizationObserver() {};
		virtual void notify ( Position& pos ) = 0;
	};
}
#endif
