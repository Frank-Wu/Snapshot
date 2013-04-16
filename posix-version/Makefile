CC=g++
CFLAGS=-Wall -O2
LDFLAGS=-lpthread
INCLUDE=-Iinclude
SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(patsubst src/%.cpp, build/%.o, $(SOURCES))

EXECUTABLE=producer consumer

all: $(EXECUTABLE)

producer:
	$(CC) src/producer.cpp $(INCLUDE) $(CFLAGS) $(LDFLAGS) -o producer

consumer:
	$(CC) src/consumer.cpp $(INCLUDE) $(CFLAGS) $(LDFLAGS) -o consumer

clean:
	rm -rf build/*.o producer consumer
