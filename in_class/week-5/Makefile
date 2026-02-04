CC = gcc
CFLAGS = -Wall -std=c99
TARGETS = mmap_write mmap_read 5-3

all: $(TARGETS)

# # mmap_write: mmap_write.c
# # 	$(CC) $(CFLAGS) -o mmap_write mmap_write.c

# # mmap_read: mmap_read.c
# # 	$(CC) $(CFLAGS) -o mmap_read mmap_read.c

# mmap_read: 5-3.c
	$(CC) $(CFLAGS) -o 5-3 5-3.c

clean:
	rm -f $(TARGETS)

.PHONY: all clean