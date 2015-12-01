#Macros to specify compiler, compiler/linking flags, target file
C++  = g++
CFLAGS = -Wall -m32 -std=c++11 -pthread
AR = ar
ARFLAGS = rvs
LD = g++
LDFLAGS = 
LIBS = 
OBJS = UDP_Sock.o
TSTOBJS = 
ARLIB = SocketLib.a
TSTEXEC = 

#Rules to create target file Driver
# If any files on line with colon are modified, then recompile the object file
all:		$(ARLIB)
		
$(ARLIB):	$(OBJS)
		$(AR) $(ARFLAGS) $(ARLIB) $(OBJS)
		
UDP_Sock.o:				networkinterface.h udp_sock.h udp_sock.cpp
		$(C++) $(CFLAGS) -c udp_sock.cpp

clean:
		rm -f $(OBJS) $(TSTEXEC) $(ARLIB) $(TSTOBJS)

test:		$(TSTEXEC)

$(TSTEXEC):	$(ARLIB) $(TSTOBJS)
		$(LD) $(LDFLAGS) -o $(TSTEXEC) $(TSTOBJS) $(ARLIB)