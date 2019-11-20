CC=g++
CFLAGS=-I.
DEPS = Statistics.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

statistics: statistics.o Statistics.o
	$(CC) -o statistics statistics.o Statistics.o

clean:
	rm -rf *.o statistics
