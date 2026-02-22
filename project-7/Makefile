CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = grayscaler

all: $(TARGET)

$(TARGET): grayscaler.c ppm.c
	$(CC) $(CFLAGS) grayscaler.c ppm.c -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: clean