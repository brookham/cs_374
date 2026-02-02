CC = gcc
CFLAGS = -Wall -std=c99
TARGET = lswc

$(TARGET): lswc.c
	$(CC) $(CFLAGS) -o $(TARGET) lswc.c

clean:
	rm -f $(TARGET)

.PHONY: clean