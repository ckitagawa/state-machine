CC = gcc

CFLAGS=-Wall -g

VPATH:=sm
TARGET = main

all:
	for i in $(TARGET) ; do \
		$(CC) $(CFLAGS) -o $$i $$i.c sm/event_queue.h sm/event_queue.c; \
	done

clean:
	for i in $(TARGET) ; do \
		rm -f $$i ; \
	done