#generic makefile to copy into each folder

CC=gcc
CFLAGS=-Wall -Wextra

SRC = $(wildcard *.c)
OUT = $(SRC:.c=)

all: $(OUT)

$OUT: $(files)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean :
	rm $(OUT)
