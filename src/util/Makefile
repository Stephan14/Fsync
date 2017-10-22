CXX = g++

CXXFLAGS += -std=c++11

LDFLAGS += -L /usr/local/lib 

SRCS += $(wildcard *.cc)
OBJSDIR += object
OBJS += $(patsubst %.cc, $(OBJSDIR)/%.o, $(SRCS))

all : $(OBJS)
	@echo "create object files"

$(OBJSDIR)/%.o : %.cc 
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	-rm -f object/*.o
