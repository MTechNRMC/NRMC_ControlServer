#Macros to specify compiler, compiler/linking flags, target file
C++  = g++
CFLAGS = -Wall -std=c++11 -funsigned-char
CTESTFLAGS = -g -pthread 
GTESTFLAGS = -L ../googletest-release-1.7.0/ -l gtest -l gtest_main 
TESTINCLUDES = -I ../googletest-release-1.7.0/include/
AR = ar
ARFLAGS = rvs
LD = g++
LDFLAGS = 
LIBS = 
OBJS = opcodeonlymessage.o motordir16message.o setspeedbytemessage.o subscribableexchange.o messagedeliverysystem.o
TSTOBJS = Tests/opcodeonlytest.o Tests/message16DirTest.o Tests/setspeedbytemessagetest.o
ARLIB = NRMCNetworkLib.a
TSTEXEC = Tests/networktest

#Rules to create target file Driver
# If any files on line with colon are modified, then recompile the object file
all:		$(ARLIB)
		
$(ARLIB):	$(OBJS)
		$(AR) $(ARFLAGS) $(ARLIB) $(OBJS) $(LIBS)
		
opcodeonlymessage.o:		message.h opcodeonlymessage.h opcodeonlymessage.cpp
		$(C++) $(CFLAGS) -c opcodeonlymessage.cpp
		
motordir16message.o:		message.h motordir16message.h motordir16message.cpp
		$(C++) $(CFLAGS) -c motordir16message.cpp
		
setspeedbytemessage.o:		message.h setspeedbytemessage.h setspeedbytemessage.cpp
		$(C++) $(CFLAGS) -c setspeedbytemessage.cpp

subscribableexchange.o:		exchangesubscriber.h subscribableexchange.h subscribableexchange.cpp
		$(C++) $(CFLAGS) -c subscribableexchange.cpp
		
messagedeliverysystem.o:	message.h SocketLib/networkinterface.h mds_interface.h ../Util/systeminterface.h subscribableexchange.h messagedeliverysystem.h messagedeliverysystem.cpp
		$(C++) $(CFLAGS) -c messagedeliverysystem.cpp
		
clean:
		rm -f $(OBJS) $(TSTEXEC) $(ARLIB) $(TSTOBJS)

test:		$(TSTEXEC)

$(TSTEXEC):	$(ARLIB) $(TSTOBJS)
		$(C++) $(CTESTFLAGS) $(TESTINCLUDES) -o $(TSTEXEC) Tests/networktest.cpp $(GTESTFLAGS) $(TSTOBJS) $(ARLIB)
		
#######################Compile commands for test objects start here#######################
Tests/opcodeonlytest.o:			Tests/opcodeonlytest.cpp opcodeonlymessage.h
		$(C++) $(CTESTFLAGS) $(GTESTFLAGS) -c Tests/opcodeonlytest.cpp $(TESTINCLUDES) -o Tests/opcodeonlytest.o
		
Tests/message16DirTest.o:   Tests/motorDir16Test.cpp motordir16message.h
		$(C++) $(CTESTFLAGS) $(GTESTFLAGS) -c Tests/motorDir16Test.cpp $(TESTINCLUDES) -o Tests/message16DirTest.o

Tests/setspeedbytemessagetest.o:                Tests/setspeedbytemessagetest.cpp setspeedbytemessage.h
		$(C++) $(CTESTFLAGS) $(GTESTFLAGS) -c Tests/setspeedbytemessagetest.cpp $(TESTINCLUDES) -o Tests/setspeedbytemessagetest.o

