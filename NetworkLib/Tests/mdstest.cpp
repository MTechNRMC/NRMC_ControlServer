#include "mocksocket.h"
#include "mocksubscriber.h"
#include "../messagedeliverysystem.h"
#include "../opcodeonlymessage.h"
#include "../../googletest-release-1.7.0/include/gtest/gtest.h"
#include <string>

using std::string;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using NRMCNetwork::MessageDeliverySystem;
using NRMCNetwork::OpcodeOnlyMessage;

class mdsTest : public testing::Test
{
protected:
	virtual void SetUp()
	{}
	virtual void TearDown()
	{}
};

TEST_F(mdsTest, msgSendTest)
{
	MockSocket sct;
	struct sockaddr_in test;
	OpcodeOnlyMessage msg(10, test);
	EXPECT_CALL(sct, sendMsg(_,1,_))
	.Times(AtLeast(3));

	MessageDeliverySystem mds = MessageDeliverySystem::getInstance();
	mds.attachNetworkInterface(&sct);

	mds.queueMessage(msg.clone());
	mds.queueMessage(msg.clone());
	mds.queueMessage(msg.clone());
	mds.queueMessage(msg.clone());
}

TEST_F(mdsTest, msgReceiveTest)
{
	MockSubscriber sub;
	MockSocket sct;

	EXPECT_CALL(sub, subscriberWants(_))
	.WillRepeatedly(Return(true));
	EXPECT_CALL(sub, queueMessage(_))
	.Times(1);

	MessageDeliverySystem mds = MessageDeliverySystem::getInstance();
	mds.subscribe(sub);
	mds.attachNetworkInterface(&sct);
}
