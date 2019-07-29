CC=gcc
CFLAGS=-g -Wall

all: object main

object: kml.c kml.h
		$(CC) $(CFLAGS) kml.c -c
main: lab11.c
		$(CC) $(CFLAGS) kml.o lab11.c
