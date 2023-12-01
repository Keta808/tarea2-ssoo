CC = g++
CFLAGS = -std=c++11
LIBS = `pkg-config --cflags --libs opencv4`

all: hilos

hilos: hilos.cpp
	$(CC) -o hilos hilos.cpp $(CFLAGS) $(LIBS)

clean:
	rm -f hilos
