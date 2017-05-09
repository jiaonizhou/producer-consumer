CC=gcc
IDIR=-I.
LIBS=-lpthread

prodcon: Main.o CircularBuffer.o
	$(CC) -o $@ $^ $(LIBS)

CircularBuffer.o: CircularBuffer.c
	$(CC) -c -o $@ $< $(IDIR)

Main.o: Main.c
	$(CC) -c -o $@ $< $(IDIR)

clean:
	rm Main.o CircularBuffer.o producerconsumer
