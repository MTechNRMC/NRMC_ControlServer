#ifndef NETWORKLIB_TESTS_MOCKSUBSCRIBER_H_
#define NETWORKLIB_TESTS_MOCKSUBSCRIBER_H_

#include "../subscribableexchange.h"
#include "../message.h"
#include <gmock/gmock.h>

using NRMCNetwork::Message;

class MockSubscriber : public NRMCNetwork::ExchangeSubscriber
{
	~MockSubscriber(){}
	MOCK_METHOD1(queueMessage, void(const Message&));
	MOCK_METHOD1(subscriberWants, bool(const Message&));
};

#endif /* NETWORKLIB_TESTS_MOCKSUBSCRIBER_H_ */
