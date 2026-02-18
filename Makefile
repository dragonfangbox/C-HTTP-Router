CC := gcc
CFLAGS := -Wall
INCLUDES := -Isrc

CFILES := $(wildcard src/*.c)

.PHONY: build debug

build:
	$(CC) $(CFLAGS) -o main $(CFILES) $(INCLUDES)

debug:
	$(CC) $(CLFAGS) -fsanitize=address -O0 -g -o main.out $(CFILES) $(INCLUDES)
