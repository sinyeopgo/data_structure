.SUFFIXES : .c .o
CC = gcc
CFLAGS = -g -Wall -ansi
 all: test

OBJS = Point.o
SRCS = $(OBJS:.o=.c)

test: $(OBJS)
	$(CC) -o Interview $(OBJS)

clean:
	rm -rf $(OBJS)
distclean:
	rm -rf $(OBJS) Interview test
