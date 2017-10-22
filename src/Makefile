HOST_SYSTEM = $(shell uname | cut -f 1 -d_)
SYSTEM ?= $(HOST_SYSTEM)

#设置编译器
CXX = g++

#设置编译选项
CXXFLAGS += -std=c++11

#设置预编译器选项
#CPPFLAGS += ./ 设置查找头文件

#设置链接器的参数，库的查找路径
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

#扫描制定路径设置源文件
SRCS += Server.grpc.pb.cc Server.pb.cc 
SRCS += $(wildcard *.cc)
CLIENT_SOURCE += FileClient.cc client_main.cc
SERVER_SOURCE += FileServer.cc server_main.cc
SERVER_SRCS += $(filter-out $(CLIENT_SOURCE), $(SRCS))
CLIENT_SRCS += $(filter-out $(SERVER_SOURCE), $(SRCS))

#设置目标文件
OBJSDIR += object
#OBJS += $(addprefix $(OBJSDIR), $(patsubst %.cc, %.o, $(SRCS))) #匹配替换并添加前缀
SERVER_OBJS += $(patsubst %.cc, $(OBJSDIR)/%.o, $(SERVER_SRCS))
CLIENT_OBJS += $(patsubst %.cc, $(OBJSDIR)/%.o, $(CLIENT_SRCS))

#设置依赖文件
DEPS += util/object/File.o 


PROTOC = protoc 
GRPC_CPP_PLUGIN = grpc_cpp_plugin 
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

PROTOS_PATH = ../proto 

#制定查找文件的路径
vpath %.proto $(PROTOS_PATH)
vpath %.cc ./ 

#子目录名字
SUBDIRS +=  ./util

all: $(SUBDIRS) server_main client_main #preparetest 

$(SUBDIRS): echo
	$(MAKE) -C $@ 

echo: 
	@echo $(SUBDIRS)

server_main: $(SERVER_OBJS) 
	$(CXX) $^ $(LDFLAGS)  $(CXXFLAGS) $(LIBS) $(DEPS) -o $@

client_main: $(CLIENT_OBJS) 
	$(CXX) $^ $(LDFLAGS)  $(CXXFLAGS) $(LIBS) $(DEPS) -o $@

#定义函数
#define complie_cc_file
#@for file in $(SRCS); do\
#	(echo "$(CXX) $(LDFLAGS) $(CXXFLAGS) $(LIBS) $(DEPS) $$file -o $@ " && $(CXX) $(LDFLAGS) $(CXXFLAGS) $(LIBS) $(DEPS) $$file -o $@)\
#done;
#endef

$(OBJSDIR)/%.o : %.cc 
	#调用函数
	#$(call complie_cc_file)	
	$(CXX) -c $< $(LDFLAGS)  $(CXXFLAGS) $(LIBS)  -o $@

#preparetest: $(OBJS) test/PrepareTest util/File.o Prepare.o  
#	$(CXX) $^ $(LDFLAGS) $(LIBS) -lgtest -o $@

#防止中间目标文件，设置需要保留的中间目标文件
.PRECIOUS: %.grpc.pb.cc
%.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=. --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

.PRECIOUS: %.pb.cc
%.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=. $<

.PHONY: clean
clean:
	-rm -f object/*.o  server_main
