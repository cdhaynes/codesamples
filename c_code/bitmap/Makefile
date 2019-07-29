CC=gcc
CFLAGS=-g -Wall
#adjust APUE dir root accordingly
APUE=./apue
INC_PATH=-I $(APUE)/include
LIB_PATH=-L $(APUE)/lib/
LIB=-lapue
targets = bmp

all: $(targets)

%: %.c
	$(CC) $(CFLAGS) $(INC_PATH) $(LIB_PATH) $@.c -o $@ $(LIB)

.PHONY : clean
clean: $(targets)
	rm -rf bmp
