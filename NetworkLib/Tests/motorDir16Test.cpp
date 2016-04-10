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

TEST_F(motor16DirTest, msg16)
{
	struct sockaddr_in test;
	char testData[] = {0x01, 0xd7, 0x00};
	NRMCNetwork::MotorDir16Message msg(testData, test);
	ASSERT_EQ(0xd700, msg.getMotorDir());
}
