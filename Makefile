CC = gcc
CFLAGS=-Wall -g

VPATH = sm
TARGET = main

main:
	$(CC) $(CFLAGS) -o $< main main.c event_queue.h event_queue.c;

clean:
	rm -f $(TARGET)