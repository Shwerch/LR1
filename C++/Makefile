CXX = g++
CXXFLAGS = -O3 -std=c++23 -pedantic -Wall -Wextra -Werror -Iinclude
SOURCES = src/main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = program

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run:
	./$(EXECUTABLE)

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)