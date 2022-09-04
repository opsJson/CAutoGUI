CC=gcc
CFLAGS=-std=c99 -pedantic -Wall -Wextra

c-autogui:
	$(CC) main.c $(CFLAGS) -o main