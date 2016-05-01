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

TEST_F(OpcodeOnlyTest, copyTest)
{
	struct sockaddr_in test;
	char result[] = { 0xFE, 0xCD, 0x01, 0x25, 0x80 };
	char* testData = new char[5];

	// copy the test data
	for(int x=0; x<5; x++)
		testData[x] = result[x];
	
	NRMCNetwork::OpcodeOnlyMessage* msg1 = new NRMCNetwork::OpcodeOnlyMessage(10, test);
	NRMCNetwork::OpcodeOnlyMessage msg2(*msg1);

	NRMCNetwork::OpcodeOnlyMessage* msg3 = new NRMCNetwork::OpcodeOnlyMessage(testData, test);
	NRMCNetwork::OpcodeOnlyMessage msg4(*msg3);
	
	// remove the first and thrid message
//	delete msg1;
//	delete msg3;
//	msg1 = 0;
//	msg3 = 0;

	// check the opcodes
	ASSERT_EQ(10, msg2.getOpcode());
	ASSERT_EQ(0xFE, msg4.getOpcode());

	ASSERT_EQ(result[0], msg4.getMessage()[0]);

	// check the raw message
//	for(int x=0; x<5; x++)
//		ASSERT_EQ(result[x],msg4.getMessage()[x]);
}
