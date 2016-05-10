#include "../../googletest-release-1.7.0/include/gtest/gtest.h"
#include  "../setspeedbytemessage.h"

class SetSpeedByteMessageTest : public testing::Test
{
protected:
	virtual void SetUp()
	{}
	virtual void TearDown()
	{}
};

TEST_F(SetSpeedByteMessageTest, rawToSpeed)
{
	struct sockaddr_in test;
	char result[] = {0x02, 0xA0, 0x2E, 0xFF};

	char* testData = new char[sizeof(result)];

	// copy the test data
	for(int x=0; x<sizeof(result); x++)
		testData[x] = result[x];

	NRMCNetwork::SetSpeedByteMessage msg(testData, sizeof(result), test);
	ASSERT_EQ(result[0], msg.getOpcode());
	ASSERT_EQ(0xA02E, msg.getMotorNum());
	ASSERT_EQ(result[3], msg.getSpeed());
}

//tests that the constructor will handle null properly
TEST_F(SetSpeedByteMessageTest, msgNull)
{
	struct sockaddr_in test;
	char* nullPointer = NULL;
	ASSERT_ANY_THROW(NRMCNetwork::SetSpeedByteMessage msg(nullPointer, 3, test));
	char testData[] = {0x02, 0xA0};
	ASSERT_ANY_THROW(NRMCNetwork::SetSpeedByteMessage msg(testData, 2, test));
}

//tests that the constructur is successfully translating data
TEST_F(SetSpeedByteMessageTest, dataConstructor)
{
	struct sockaddr_in test;
	NRMCNetwork::SetSpeedByteMessage msg(2, 41006, 0xFF, test);
	ASSERT_EQ(0x02, msg.getOpcode());
	ASSERT_EQ(0xA02E, msg.getMotorNum());
	ASSERT_EQ((char)0xFF, msg.getSpeed());
}

//test that the copy constructor is successfully working
TEST_F(SetSpeedByteMessageTest, copyConstructor)
{
	struct sockaddr_in test;
	NRMCNetwork::SetSpeedByteMessage* msg = new NRMCNetwork::SetSpeedByteMessage(2, 41006, 0xFF, test);

	NRMCNetwork::SetSpeedByteMessage* clone = msg->clone();
	delete msg;
	ASSERT_EQ(0x02, clone->getOpcode());
	ASSERT_EQ(0xA02E, clone->getMotorNum());
	ASSERT_EQ((char)0xFF, clone->getSpeed());
}
