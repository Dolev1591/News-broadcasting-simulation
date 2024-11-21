CXX = g++
CXXFLAGS = -std=c++11 -pthread -Wall -g

LDFLAGS = -pthread

# Source files
SRCS = main.cpp BoundedBuffer.cpp UnboundedBuffer.cpp Producer.cpp Dispatcher.cpp CoEditor.cpp ScreenManager.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = ex3.out

# Default target
all: $(EXEC)

# Rule to create the executable
$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(EXEC) $(OBJS)

# Rule to compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean
