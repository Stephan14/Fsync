HOST_SYSTEM = $(shell uname | cut -f 1 -d_)
SYSTEM ?= $(HOST_SYSTEM)

CXX = g++

OBJSDIR = object

ifeq ($(SYSTEM),Darwin)
	LIBS += `pkg-config --libs protobuf grpc++ grpc`\
			-lgrpc++_reflection\
			-ldl 
else
	LIBS += `pkg-config --libs protobuf grpc++ grpc`\
			-Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
			-ldl 
endif

.PHONY: all clean
all: FileTest PrepareTest

FileTest: $(OBJSDIR)/FileTest.o ../util/object/File.o
	$(CXX) $^ -o $@ -lgtest

PrepareTest:  $(OBJSDIR)/PrepareTest.o  ../object/Prepare.o ../util/object/File.o ../object/Server.pb.o 
	$(CXX)  $^  $(LIBS) -o $@  -lgtest -std=c++11  -g

$(OBJSDIR)/%.o : %.cc 
	$(CXX) -c $<  -std=c++11 -o $@

clean:
	rm object/*.o


