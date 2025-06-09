CC = gcc
CFLAGS = -g -Wall -Wextra -std=c17 -Werror -pedantic
SRCS = $(wildcard *.c)

all:
	$(CC) $(CFLAGS) $(SRCS) -o bin/log.out
