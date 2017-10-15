HOST_SYSTEM = $(shell uname | cut -f 1 -d_)
SYSTEM ?= $(HOST_SYSTEM)

#设置编译器
CXX = g++

#设置编译选项
CXXFLAGS += -std=c++11

#CPPFLAGS += ./ 设置查找头文件

#设置库的查找路径
LDFLAGS += -L /usr/local/lib 

#设置动态搜索路径
#RTFLAGS += -Wl,-rpath=

#设置静态库
ifeq ($(SYSTEM),Darwin)
	LIBS += `pkg-config --libs protobuf grpc++ grpc`\
			-lgrpc++_reflection\
			-ldl 
	else
	LIBS += `pkg-config --libs protobuf grpc++ grpc`\
			-Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed\
			-ldl 
	endif

#设置目标文件
OBJS += Server.pb.o Server.grpc.pb.o

$(MAKE) -C ./util M=./

PROTOC = protoc 
GRPC_CPP_PLUGIN = grpc_cpp_plugin 
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

PROTOS_PATH = ../proto 

vpath %.proto $(PROTOS_PATH)

all: server_main client_main preparetest 

server_main: $(OBJS) FileServer.o server_main.o
	$(CXX) $^ $(LDFLAGS)  $(LIBS) -o $@

client_main: $(OBJS) FileClient.o client_main.o
	$(CXX) $^ $(LDFLAGS)  $(LIBS) -o $@

preparetest: $(OBJS) test/PrepareTest.o util/File.o Prepare.o  
	$(CXX) $^ $(LDFLAGS) $(LIBS) -lgtest -o $@

.PRECIOUS: %.grpc.pb.cc
%.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=. $<

.PHONY: clean
clean:
	-rm -f *.o *.pb.cc *.pb.h server_main
