CC = gcc
CFLAGS=-Wall -g -I.
DEPS=sm/event_queue.h

TARGET = main

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: main.o sm/event_queue.c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c sm/event_queue.c

clean:
	rm -f $(TARGET)