CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra

main:
	$(CC) main.c $(CFLAGS) -o main