CC=g++
CFLAGS=-c -g -Wall -O3
LDFLAGS=-lboost_thread
INCLUDE=-Iinclude
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(patsubst src/%.cpp, build/%.o, $(SOURCES))

EXECUTABLE=bufferRing

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@
clean:
	rm -rf build/*.o bufferRing
