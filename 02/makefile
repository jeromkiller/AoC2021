#generic makefile to copy into each folder

CC=gcc
CFLAGS=-Wall -Wextra

SRC = $(wildcard *.c)
SRC := $(filter-out common, $(SRC))
OUT = $(SRC:.c=)
HEAD = $(wildcard *.h)
commonSRC = $(wildcard common/*.c)
commonOBJ = $(commonSRC:.c=.o)

all: $(OUT)

% : %.c $(commonOBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(commonOBJ): $(commonSRC)
	$(CC) -c $< -o $@ $(CFLAGS)

.PHONY: clean
clean :
	rm $(commonOBJ)
	rm $(OUT)
