CXX = g++
CXXFLAGS = -Wall

SOURCES = main.cpp
OBJECTS = main.o
EXECUTABLE = main.exe

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean all doc

clean:
	rm $(OBJECTS) $(EXECUTABLE)

doc:
	doxygen

all: main.exe doc

valgrind: $(EXECUTABLE)
	valgrind -s --leak-check=full ./main.exe