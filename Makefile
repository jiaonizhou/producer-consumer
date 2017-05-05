CC=gcc
IDIR=-I.
LIBS=-lpthread

all: Main.o CircularBuffer.o
	$(CC) -o producerconsumer $^ $(LIBS)


CircularBuffer.o: CircularBuffer.c
	$(CC) -c -o $@ $< $(IDIR)

Main.o: Main.c
	$(CC) -c -o $@ $< $(IDIR)
