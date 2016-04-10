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
OBJS = manualcontrolsystem.o
TSTOBJS = Tests/manualcontrolsystemtest.o
ARLIB = NRMC_MCSLib.a
TSTEXEC = Tests/mcstest

#Rules to create target file Driver
# If any files on line with colon are modified, then recompile the object file
all:		$(ARLIB)
		
$(ARLIB):	$(OBJS)
		$(AR) $(ARFLAGS) $(ARLIB) $(OBJS) $(LIBS)
		
manualcontrolsystem.o:		../NetworkLib/exchangesubscriber.h ../NetworkLib/mds_interface.h ../NetworkLib/motordir16message.h ../NetworkLib/setspeedbytemessage.h ../HardwareLib/hardwareinterface.h ../HardwareLib/motorcontroller.h ../Util/systeminterface.h manualcontrolsystem.h manualcontrolsystem.cpp
		$(C++) $(CFLAGS) -c manualcontrolsystem.cpp
		
clean:
		rm -f $(OBJS) $(TSTEXEC) $(ARLIB) $(TSTOBJS)

test:		$(TSTEXEC)

$(TSTEXEC):	$(ARLIB) $(TSTOBJS)
		$(C++) $(CTESTFLAGS) $(TESTINCLUDES) -o $(TSTEXEC) Tests/mcstest.cpp $(GTESTFLAGS) $(TSTOBJS) $(ARLIB)
		
#######################Compile commands for test objects start here#######################
Tests/manualcontrolsystemtest.o:			Tests/manualcontrolsystemtest.cpp manualcontrolsystem.h
		$(C++) $(CTESTFLAGS) $(GTESTFLAGS) -c Tests/manualcontrolsystemtest.cpp $(TESTINCLUDES) -o Tests/manualcontrolsystemtest.o