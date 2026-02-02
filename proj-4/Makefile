CC = gcc
CFLAGS = -Wall -std=c99
TARGETS = lswc redirout

all: $(TARGETS)

lswc: lswc.c
	$(CC) $(CFLAGS) -o lswc lswc.c

redirout: redirout.c
	$(CC) $(CFLAGS) -o redirout redirout.c

clean:
	rm -f $(TARGETS)

.PHONY: all clean