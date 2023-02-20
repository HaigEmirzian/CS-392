# Pledge: I pledge my honor that I have abided by the Stevens Honor System.
# Name: Haig Emirzian

CC = gcc
CFLAGS = -c -g -Wall -Werror -pedantic-errors

all: main.o insertion.o utils.o
	$(CC) $(CFLAGS) $^ -o a.out

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o a.out
