CC = gcc
CFLAGS = -g -Wall

all: main.o blackbox.o
	$(CC) $(CFLAGS) -o main main.o blackbox.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

clean:
	rm main.o main
