OBJS=parse

CC=gcc

CFLAGS=-g -O3 -std=c99

all: ${OBJS}
	@echo "USAGE: ./parse [file]"

clean:
	rm -f *.o ${OBJS}