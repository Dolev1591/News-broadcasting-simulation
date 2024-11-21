CXX = g++
CXXFLAGS = -std=c++11 -pthread -Wall -g -Iheaders  # Include headers directory
LDFLAGS = -pthread

# Source files (now in src directory)
SRCS = src/main.cpp src/BoundedBuffer.cpp src/UnboundedBuffer.cpp src/Producer.cpp src/Dispatcher.cpp src/CoEditor.cpp src/ScreenManager.cpp

# Object files (place .o files in src directory)
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = ex3.out

# Default target
all: $(EXEC)

# Rule to create the executable
$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) -o $(EXEC) $(OBJS)

# Rule to compile source files into object files
src/%.o: src/%.cpp  # Updated rule for object files in src/
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean

