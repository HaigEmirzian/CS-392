# Pledge: I pledge my honor that I have abided by the Stevens Honor System.
# Name: Haig Emirzian

a.out: main.o utils.o insertion.o
	gcc main.o utils.o insertion.o -o a.out
main.o: main.c
	gcc -c -g -Wall -Werror -pedantic-errors main.c
insertion.o: insertion.c insertion.h
	gcc -c -g -Wall -Werror -pedantic-errors insertion.c
utils.o: utils.c utils.h
	gcc -c -g -Wall -Werror -pedantic-errors utils.c
clean:
	rm -f *.o