CC = gcc
CFLAGS = -Wall -std=c99
TARGET = mush

$(TARGET): mush.c
	$(CC) $(CFLAGS) -o $(TARGET) mush.c

clean:
	rm -f $(TARGET)

.PHONY: clean