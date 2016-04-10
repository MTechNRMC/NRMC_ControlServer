#include "../../googletest-release-1.7.0/include/gtest/gtest.h"
#include "../opcodeonlymessage.h"

class OpcodeOnlyTest : public testing::Test
{
protected:
	virtual void SetUp()
	{}
	virtual void TearDown()
	{}
};

TEST_F(OpcodeOnlyTest, rawToOpcode)
{
	struct sockaddr_in test;
	char testData[] = { 0xFE, 0xCD, 0x01, 0x25, 0x80 };
	NRMCNetwork::OpcodeOnlyMessage msg(testData, test);
	ASSERT_EQ(0xFE, msg.getOpcode());
}

TEST_F(OpcodeOnlyTest, opcodeToRaw)
{
	struct sockaddr_in test;
	NRMCNetwork::OpcodeOnlyMessage msg(10, test);
	ASSERT_EQ(10, msg.getMessage()[0]);
}

TEST_F(OpcodeOnlyTest, exceptionCheck)
{
	struct sockaddr_in test; 
	ASSERT_ANY_THROW(NRMCNetwork::OpcodeOnlyMessage msg((char*)0, test));
}
