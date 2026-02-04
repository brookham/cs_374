CC = gcc
CFLAGS = -Wall -std=c99
TARGETS =5-3 mmap_flat_lock

all: $(TARGETS)

mmap_write: mmap_flat_lock.c
	$(CC) $(CFLAGS) -o mmap_flat_lock mmap_flat_lock.c

# # mmap_read: mmap_read.c
# # 	$(CC) $(CFLAGS) -o mmap_read mmap_read.c

5-3: 5-3.c
	$(CC) $(CFLAGS) -o 5-3 5-3.c

clean:
	rm -f $(TARGETS)

.PHONY: all clean