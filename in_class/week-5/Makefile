CC = gcc
CFLAGS = -Wall -std=c99
TARGETS = mmap_write mmap_read

all: $(TARGETS)

mmap_write: mmap_write.c
	$(CC) $(CFLAGS) -o mmap_write mmap_write.c

mmap_read: mmap_read.c
	$(CC) $(CFLAGS) -o mmap_read mmap_read.c

clean:
	rm -f $(TARGETS)

.PHONY: all clean