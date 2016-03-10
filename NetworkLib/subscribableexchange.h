#ifndef SUBSCRIBABLEEXCHANGE_H
#define SUBSCRIBABLEEXCHANGE_H

#include <vector>
#include "exchangesubscriber.h"

using std::vector;

namespace NRMCNetwork
{
	class SubscribableExchange
	{
	  // Attributes
	  private:
		vector<ExchangeSubscriber*> subscribers;
	  // Operations
	  public:
		SubscribableExchange (  );
		virtual ~SubscribableExchange (   );
		const vector<ExchangeSubscriber*> getSubscribers (  ) const;
		void subscribe ( ExchangeSubscriber& subscriber );
		void unsubscribe(ExchangeSubscriber& subscriber);
	  protected:
		void updateSubscribers ( const Message& message );
	};
}

#endif
