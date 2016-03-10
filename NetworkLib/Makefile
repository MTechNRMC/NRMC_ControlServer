#Macros to specify compiler, compiler/linking flags, target file
C++  = g++
CFLAGS = -Wall -std=c++11
CTESTFLAGS = -g -pthread
GTESTFLAGS = -L ../googletest-release-1.7.0/ -l gtest -l gtest_main 
TESTINCLUDES = -I ../googletest-release-1.7.0/include/
AR = ar
ARFLAGS = rvs
LD = g++
LDFLAGS = 
LIBS = 
OBJS = opcodeonlymessage.o motordir16message.o setspeedbytemessage.o subscribableexchange.o
TSTOBJS = Tests/opcodeonlytest.o
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
		
#MessageDeliverySystem.o:	message.h SocketLib/networkinterface.h mds_interface.h systeminterface.h subscribableexchange.h messagedeliverysystem.h messagedeliverysystem.cpp
#		$(C++) $(CFLAGS) -c messagedeliverysystem.cpp
		
clean:
		rm -f $(OBJS) $(TSTEXEC) $(ARLIB) $(TSTOBJS)

test:		$(TSTEXEC)

$(TSTEXEC):	$(ARLIB) $(TSTOBJS)
		$(C++) $(CTESTFLAGS) $(TESTINCLUDES) -o $(TSTEXEC) Tests/networktest.cpp $(GTESTFLAGS) $(TSTOBJS) $(ARLIB)
		
Tests/opcodeonlytest.o:			Tests/opcodeonlytest.cpp opcodeonlymessage.h
		$(C++) $(CTESTFLAGS) $(GTESTFLAGS) -c Tests/opcodeonlytest.cpp $(TESTINCLUDES) -o Tests/opcodeonlytest.o
