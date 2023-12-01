CC = g++
CFLAGS = -std=c++11
LIBS = `pkg-config --cflags --libs opencv4`

all: secuencial

secuencial: secuencial.cpp
	$(CC) -o secuencial secuencial.cpp $(CFLAGS) $(LIBS)

clean:
	rm -f secuencial
