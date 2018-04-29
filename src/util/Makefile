CXX = g++

CXXFLAGS += -std=c++11

LDFLAGS += -L /usr/local/lib 

SRCS += $(wildcard *.cc)
OBJSDIR += .obj
OBJS += $(patsubst %.cc, $(OBJSDIR)/%.o, $(SRCS))

MAKE_OBJECT_DIR := $(shell mkdir -p $(OBJSDIR))

all : $(MAKE_OBJECT_DIR) $(OBJS)
	@echo "create object files"


$(OBJSDIR)/%.o : %.cc 
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	-rm -f .obj/*.o
