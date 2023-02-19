# Pledge: I pledge my honor that I have abided by the Stevens Honor System.
# Name: Haig Emirzian


all: main.o insertion.o utils.o
	gcc main.o insertion.o utils.o -o a.out

main.o: main.c
	gcc main.c -c -Wall

utils.o: utils.c
	gcc utils.c -c

insertion.o: insertion.c
	gcc insertion.c -c

clean:
	rm *.o
