#ifndef EXCHANGESUBSCRIBER_H
#define EXCHANGESUBSCRIBER_H

#include "message.h"

namespace NRMCNetwork
{
	// Interface
	class ExchangeSubscriber
	{
	  // Associations
	  // Attributes
	  // Operations
	  public:
		ExchangeSubscriber (  ) {}
		virtual ~ExchangeSubscriber (  ) {}
		virtual void queueMessage ( const Message& message ) = 0;
		virtual bool subscriberWants ( const Message& message ) = 0;
	};
}

#endif
