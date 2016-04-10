#include "subscribableexchange.h"

using namespace NRMCNetwork;

SubscribableExchange::SubscribableExchange (  )
{}

SubscribableExchange::~SubscribableExchange (  )
{
	for(unsigned int i = 0; i < subscribers.size(); i++)
		delete subscribers[i];

	subscribers.clear();
}

const vector<ExchangeSubscriber*> SubscribableExchange::getSubscribers(  ) const
{
	return subscribers;
}

void SubscribableExchange::subscribe ( ExchangeSubscriber& subscriber )
{
	subscribers.push_back(&subscriber);
}

void SubscribableExchange::unsubscribe(ExchangeSubscriber& subscriber)
{
	// look for the subscriber and delete them
	for(vector<ExchangeSubscriber*>::iterator it; it != subscribers.end(); ++it)
	{
		if(*it == &subscriber)
			subscribers.erase(it);
	}
}

void SubscribableExchange::updateSubscribers ( const Message& message )
{
	for (unsigned int i = 0; i < subscribers.size(); i++)
	{
		// check if the subscriber wants the message
		if(subscribers[i]->subscriberWants(message))
			subscribers[i]->queueMessage(*message.clone());	// if they do queue up a new message
	}
}

