CC = gcc
CFLAGS = -Wall -std=c99
TARGET = speed

all: $(TARGET)

speed: speed.c
	$(CC) $(CFLAGS) -o speed speed.c

clean:
	rm -f $(TARGET)

.PHONY: clean