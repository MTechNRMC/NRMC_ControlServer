#ifndef GHQS_OBSERVER_H
#define GHQS_OBSERVER_H


// Interface
namespace NRMC_GHQS
{
	class GHQS_Observer
	{
		// Associations
		// Attributes
		// Operations
	public:
		GHQS_Observer() {};
		virtual ~GHQS_Observer() {};
		virtual void notify() = 0;
	};
}

#endif
