PROTOC = protoc 
PROTOS_PATH = .
SUBDIR = ../src/
GRPC_CPP_PLUGIN = grpc_cpp_plugin 
GRPC_CPP_PLUGIN_PATH ?= `which $(GRPC_CPP_PLUGIN)`

all: ../src/Server.grpc.pb.cc ../src/Server.pb.cc

$(SUBDIR)%.grpc.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --grpc_out=$(SUBDIR) --plugin=protoc-gen-grpc=$(GRPC_CPP_PLUGIN_PATH) $<

$(SUBDIR)%.pb.cc: %.proto
	$(PROTOC) -I $(PROTOS_PATH) --cpp_out=$(SUBDIR) $<

.PHONY: clean
clean: 
	-rm -f ../src/*.pb.*
