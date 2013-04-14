CC=g++
CFLAGS=-Wall -O2
LDFLAGS=
INCLUDE=-Iinclude
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(patsubst src/%.cpp, build/%.o, $(SOURCES))

EXECUTABLE=producer consumer

all: $(EXECUTABLE)

producer:
	$(CC) src/producer.cpp $(INCLUDE) $(CFLAGS) -o producer

consumer:
	$(CC) src/consumer.cpp $(INCLUDE) $(CFLAGS) -o consumer

clean:
	rm -rf build/*.o producer consumer
