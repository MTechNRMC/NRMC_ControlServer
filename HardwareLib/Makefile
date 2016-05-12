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
OBJS = micromaestro12.o peripheralfactory.o smrtperipheral.o termiosfactory.o termiosserialport.o
TSTOBJS = 
ARLIB = NRMCHardwareLib.a
TSTEXEC = 

#Rules to create target file Driver
# If any files on line with colon are modified, then recompile the object file
all:		$(ARLIB)
		
$(ARLIB):	$(OBJS)
		$(AR) $(ARFLAGS) $(ARLIB) $(OBJS) $(LIBS)
		
micromaestro12.o:		peripheral.h motorcontroller.h servocontroller.h serialportinterface.h
		$(C++) $(CFLAGS) -c micromaestro12.cpp
		
peripheralfactory.o:		smrtperipheral.h serialportfactory.h hardwareinterface.h peripheraltype.h micromaestro12.h
		$(C++) $(CFLAGS) -c peripheralfactory.cpp
		
smrtperipheral.o:		peripheraltype.h peripheral.h hardwareinterface.h
		$(C++) $(CFLAGS) -c smrtperipheral.cpp
		
termiosfactory.o:		termiosserialport.h serialportfactory.h paritybit.h stopbit.h
		$(C++) $(CFLAGS) -c termiosfactory.cpp
		
termiosserialport.o:	serialportinterface.h
		$(C++) $(CFLAGS) -c termiosserialport.cpp
		
clean:
		rm -f $(OBJS) $(TSTEXEC) $(ARLIB) $(TSTOBJS)

test:		$(TSTEXEC)

$(TSTEXEC):	$(ARLIB) $(TSTOBJS)
		$(C++) $(CTESTFLAGS) $(TESTINCLUDES) -o $(TSTEXEC) Tests/mcstest.cpp $(GTESTFLAGS) $(TSTOBJS) $(ARLIB)
		
#######################Compile commands for test objects start here#######################
#Tests/manualcontrolsystemtest.o:			Tests/manualcontrolsystemtest.cpp manualcontrolsystem.h
#		$(C++) $(CTESTFLAGS) $(GTESTFLAGS) -c Tests/manualcontrolsystemtest.cpp $(TESTINCLUDES) -o Tests/manualcontrolsystemtest.o