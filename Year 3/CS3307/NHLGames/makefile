CXX = g++
CXXFLAGS = --std=c++11

SOURCES = main.cpp request.cpp callback.cpp game.cpp
EXECUTABLE = main

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -lcurl -o $@

clean:
	rm -f $(EXECUTABLE)