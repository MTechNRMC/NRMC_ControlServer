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
OBJS = generalhardwarequerysystem.o
TSTOBJS = 
ARLIB = NRMC_GHQSLib.a
TSTEXEC = Tests/GHQLidarExample

#Rules to create target file Driver
# If any files on line with colon are modified, then recompile the object file
all:		$(ARLIB)
		
$(ARLIB):	$(OBJS)
		$(AR) $(ARFLAGS) $(ARLIB) $(OBJS) $(LIBS)
		
generalhardwarequerysystem.o:		../NetworkLib/exchangesubscriber.h ../NetworkLib/mds_interface.h ../NetworkLib/message.h ../HardwareLib/hardwareinterface.h device.h ghqs_interface.h ghqs_observer.h
		$(C++) $(CFLAGS) -c generalhardwarequerysystem.cpp
		
clean:
		rm -f $(OBJS) $(TSTEXEC) $(ARLIB) $(TSTOBJS)

test:		$(TSTEXEC)

$(TSTEXEC):	$(ARLIB)
		$(C++) $(CFLAGS) -o $(TSTEXEC) Tests/GHQLidarExample.cpp $(ARLIB) ../NetworkLib/NRMCNetworkLib.a ../HardwareLib/NRMCHardwareLib.a ../HardwareLib/RPLidarLib/librplidar_sdk.a
		
#######################Compile commands for test objects start here#######################
#Tests/manualcontrolsystemtest.o:			Tests/manualcontrolsystemtest.cpp manualcontrolsystem.h
#		$(C++) $(CTESTFLAGS) $(GTESTFLAGS) -c Tests/manualcontrolsystemtest.cpp $(TESTINCLUDES) -o Tests/manualcontrolsystemtest.o