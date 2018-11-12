CC=gcc
CFLAGS=-Wall -std=c99 -O2
EXEC=main

all: $(EXEC)

main: main.o
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -rf *.o

fullclean: clean
	rm -rf $(EXEC)
