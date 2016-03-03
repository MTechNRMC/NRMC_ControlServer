#include "subscribableexchange.h"

using namespace NRMCNetwork;

SubscribableExchange::SubscribableExchange (  )
{
	
}

SubscribableExchange::~SubscribableExchange (  )
{
	for(int i = 0; i < subscribers; i++)
		delete subscribers[i];

	subscribers.clear();
}

vector<ExchangeSubscriber*> SubscribableExchange::getSubscribers const (  )
{
	return subscribers;
}

void SubscribableExchange::subscribe ( ExchangeSubscriber& subscriber )
{
	subscribers.push_back(subscriber);
}

void SubscribableExchange::updateSubscribers ( const Message& message )
{
	for (int i = 0; i < subscribers.size(); i++)
	{
		subscribers[i].queueMessage (message);
	}
}

