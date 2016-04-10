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
	char testData[] = {0x02, 0xA0, 0x2E, 0xFF};
	NRMCNetwork::SetSpeedByteMessage msg(testData, test);
	ASSERT_EQ(0xA02E, msg.getMotorNum());
	ASSERT_EQ(0xFF, msg.getSpeed());
}
