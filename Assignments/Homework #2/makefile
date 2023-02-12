# Pledge: I pledge my honor that I have abided by the Stevens Honor System.
# Name: Haig Emirzian

CC = gcc
CFLAGS = -c -Wall

all: main.o insertion.o utils.o
	@echo "* Linking all objects..."
	$(CC) main.o insertion.o utils.o -o a.out

main.o: main.c
	@echo "* Compiling main.c..."
	$(CC) main.c $(CFLAGS)

utils.o: utils.c
	@echo "* Compiling utils.c..."
	gcc utils.c -c

insertion.o: insertion.c
	@echo "* Compiling insertion.c..."
	gcc insertion.c -c

clean:
	@echo "Cleaning up..."
	rm *.o
