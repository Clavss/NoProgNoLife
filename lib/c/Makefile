CC=gcc
CFLAGS= -Wall -std=c99 -O2

AB: AB.o file.o
	$(CC) -o $@ $^ 

%o: %c %h
	$(CC) -c $< $(CFLAGS)

AB.o: file.h