#Macros to specify compiler, compiler/linking flags, target file
C++  = g++
CFLAGS = -Wall -std=c++11 -funsigned-char -pthread 
CTESTFLAGS = -g -pthread 
GTESTFLAGS = -L ../googletest-release-1.7.0/ -l gtest -l gtest_main #-l gmock
TESTINCLUDES = -I ../googletest-release-1.7.0/include/
AR = ar
ARFLAGS = rvs
LD = g++
LDFLAGS = 
LIBS = NetworkLib/NRMCNetworkLib.a NetworkLib/SocketLib/SocketLib.a MCS_Lib/NRMC_MCSLib.a HardwareLib/NRMCHardwareLib.a
OBJS = 
TSTOBJS = 
ARLIB = 
EXEC = ControlServer
EXECSRC = CntrlSrvrDriver.cpp

#Rules to create target file Driver
# If any files on line with colon are modified, then recompile the object file
all:		$(EXEC)
		
$(EXEC):	$(LIBS)
		$(C++) $(CFLAGS) $(EXECSRC) -o $(EXEC) $(LIBS) 
		
Libs:		$(LIBS)
		
NetworkLib/NRMCNetworkLib.a:
		(cd NetworkLib; make all;)
		
NetworkLib/SocketLib.a:
		
MCS_Lib/NRMC_MCSLib.a:
		(cd MCS_Lib; make all;)
		
HardwareLib/NRMCHardwareLib.a:
		(cd HardwareLib; make all;)

clean:	
		(cd NetworkLib; make clean)
		(cd MCS_Lib; make clean;)
		(cd HardwareLib; make clean;)
		rm -f $(EXEC)
	
