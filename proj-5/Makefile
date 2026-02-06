CC = gcc
CFLAGS = -Wall -std=c99
TARGET = appendlog

all: $(TARGET)

appendlog: appendlog.c
	$(CC) $(CFLAGS) -o appendlog appendlog.c

clean:
	rm -f $(TARGET)

.PHONY: clean