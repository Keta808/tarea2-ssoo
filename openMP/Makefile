CC = g++
CFLAGS = -std=c++11 -fopenmp
LIBS = `pkg-config --cflags --libs opencv4`

all: openMP

openMP: openMP.cpp
	$(CC) -o openMP openMP.cpp $(CFLAGS) $(LIBS)

clean:
	rm -f openMP
