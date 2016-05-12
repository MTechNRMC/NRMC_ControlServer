#Macros to specify compiler, compiler/linking flags, target file
C++  = g++
CFLAGS = -Wall -std=c++11 -pthread	#need if undefined reference to 'pthread_create' may need -lpthread
AR = ar
ARFLAGS = rvs
LD = g++
LDFLAGS = 
LIBS = 
OBJS = UDP_Sock.o
TSTOBJS = 
ARLIB = SocketLib.a
TSTEXEC = Tests/TestClient

#Rules to create target file Driver
# If any files on line with colon are modified, then recompile the object file
all:		$(ARLIB)
		
$(ARLIB):	$(OBJS)
		$(AR) $(ARFLAGS) $(ARLIB) $(OBJS)
		
UDP_Sock.o:				networkinterface.h udp_sock.h udp_sock.cpp
		$(C++) $(CFLAGS) -c udp_sock.cpp -o UDP_Sock.o

clean:
		rm -f $(OBJS) $(TSTEXEC) $(ARLIB) $(TSTOBJS)

test:		$(TSTEXEC)

$(TSTEXEC):	$(ARLIB) 
		$(C++) $(CFLAGS) -o $(TSTEXEC) Tests/UDPSocketTestClient.cpp $(ARLIB)