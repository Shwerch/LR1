CXX = g++
CXXFLAGS = -O3 -std=c++23 -pedantic -Wall -Wextra -Werror -Iinclude
SOURCES = src/main.cpp src/tree.cpp src/queue.cpp src/doubly_list.cpp src/forward_list.cpp src/stack.cpp src/array.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = program

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)