CC = gcc
CFLAGS = -Wall -std=c99
TARGET = filescanner

$(TARGET): filescanner.c
	$(CC) $(CFLAGS) -o $(TARGET) filescanner.c

clean:
	rm -f $(TARGET)

.PHONY: clean