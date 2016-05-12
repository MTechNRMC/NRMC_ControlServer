#include "../../googletest-release-1.7.0/include/gtest/gtest.h"
#include "../motordir16message.h"

class motor16DirTest : public testing::Test
{
protected:
	virtual void SetUp()
	{}
	virtual void TearDown()
	{}
};

TEST_F(motor16DirTest, rawToDir)
{
	struct sockaddr_in test;
	char result[] = {0x01, 0xd7, 0x15};

	char* testData = new char[sizeof(result)];

	// copy the test data
	for(int x=0; x<sizeof(result); x++)
		testData[x] = result[x];

	NRMCNetwork::MotorDir16Message msg(testData, sizeof(result), test);
	ASSERT_EQ(0x01, msg.getOpcode());
	ASSERT_EQ(0xd715, msg.getMotorDir());
}

TEST_F(motor16DirTest, msgNull)
{
	struct sockaddr_in test;
	char* nullPointer = NULL;
	ASSERT_ANY_THROW(NRMCNetwork::MotorDir16Message msg(nullPointer, 3, test));
	char testData[] = {0x02, 0xA0};
	ASSERT_ANY_THROW(NRMCNetwork::MotorDir16Message msg(testData, 2, test));
}

TEST_F(motor16DirTest, valueToRaw)
{
	struct sockaddr_in test;
	NRMCNetwork::MotorDir16Message msg(2, 41006, test);
	ASSERT_EQ(0x02, msg.getOpcode());
	ASSERT_EQ(0xA02E, msg.getMotorDir());
}

TEST_F(motor16DirTest, copyConstructor)
{
	struct sockaddr_in test;
	NRMCNetwork::MotorDir16Message* msg = new NRMCNetwork::MotorDir16Message(2, 41006, test);

	NRMCNetwork::MotorDir16Message* clone = msg->clone();
	delete msg;
	ASSERT_EQ(0x02, clone->getOpcode());
	ASSERT_EQ(0xA02E, clone->getMotorDir());
}
