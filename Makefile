CXX = g++
CXXFLAGS = -Wall

SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp = .o)
EXECUTABLE = main.exe

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean doc all

clean:
	rm $(OBJECTS) $(EXECUTABLE)

doc:
	doxygen -g

all:
	main.exe doc