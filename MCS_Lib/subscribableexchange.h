#ifndef SUBSCRIBABLEEXCHANGE_H
#define SUBSCRIBABLEEXCHANGE_H

#include <vector>
#include "exchangesubscriber.h"
#include "notimplementedexception.h"

using std::vector;

namespace NRMCNetwork
{
	class SubscribableExchange
	{
	  // Associations
	   ExchangeSubscriber * unnamed;
	  // Attributes
	  private:
		vector<ExchangeSubscriber*> subscribers;
	  // Operations
	  public:
		SubscribableExchange (  );
		virtual ~SubscribableExchange (   );
		vector<ExchangeSubscriber*> getSubscribers const (  );
		void subscribe ( ExchangeSubscriber& subscriber );
	  protected:
		void updateSubscribers ( const Message& message );
	};
}

#endif
