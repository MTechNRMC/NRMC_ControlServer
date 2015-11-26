#Macros to specify compiler, compiler/linking flags, target file
C++  = g++
CFLAGS = 
AR = ar
ARFLAGS = rvs
LD = g++
LDFLAGS = 
LIBS = 
OBJS = MessageDeliverySystem.o OpcodeOnlyMessage.o SubscribableExchange.o
TSTOBJS = 
ARLIB = NRMCNetworkLib.a
TSTEXEC = 

#Rules to create target file Driver
# If any files on line with colon are modified, then recompile the object file
all:		$(ARLIB)
		
$(ARLIB):	$(OBJS)
		$(AR) $(ARFLAGS) $(ARLIB) $(OBJS) $(LIBS)
		
OpcodeOnlyMessage.o:		message.h opcodeonlymessage.h opcodeonlymessage.cpp
		$(C++) $(CFLAGS) -c opcodeonlymessage.cpp

SubscribableExchange.o:		exchangesubscriber.h subscriableexchange.h subscriableexchange.cpp
		$(C++) $(CFLAGS) -c subscriableexchange.cpp
		
MessageDeliverySystem.o:	message.h SocketLib/networkinterface.h mds_interface.h systeminterface.h subscribableexchange.h messagedeliverysystem.h messagedeliverysystem.cpp
		$(C++) $(CFLAGS) -c messagedeliverysystem.cpp
		
clean:
		rm -f $(OBJS) $(TSTEXEC) $(ARLIB) $(TSTOBJS)

test:		$(TSTEXEC)

$(TSTEXEC):	$(ARLIB) $(TSTOBJS)
		$(LD) $(LDFLAGS) -o $(TSTEXEC) $(TSTOBJS) $(ARLIB)