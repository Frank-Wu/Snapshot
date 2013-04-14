CC=g++
CFLAGS=-c -g -Wall -O3
LDFLAGS=
INCLUDE=-Iinclude
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(patsubst src/%.cpp, build/%.o, $(SOURCES))

EXECUTABLE=producer consumer

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

build/%.o: src/%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) $< -o $@
clean:
	rm -rf build/*.o producer consumer
