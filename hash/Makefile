# Makefile for executable test

# *****************************************************
# Parameters to control Makefile operation

CC = gcc
CFLAGS = -ansi -pedantic -Wall -g

# ****************************************************
# Entries to bring the executable up to date

test: test.o hash.o
	$(CC) $(CFLAGS) -o test test.o hash.o

test.o: test.c hash.h
	$(CC) $(CFLAGS) -c test.c

hash.o: hash.c hash.h
	$(CC) $(CFLAGS) -c hash.c
