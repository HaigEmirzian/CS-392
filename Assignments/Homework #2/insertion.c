#include "insertion.h"

// Pledge: I pledge my honor that I have abided by the Stevens Honor System.
// Name: Haig Emirzian

/*
	We emphasize this: because this is a generic implementation, in insertion.c you must not use if-else to
	discriminate different data types in your code. Your code must be able to deal with any data type possible.
	Therefore, we limit the usage of the following primitive types:
	- int or size_t: only allowed as loop iterators;
	- char or u_int8_t: can be used as you wish;
	- Types that are used in the declarations of iSort() and iPrint(): feel free to use them for their _original_
      purpose;
	- All other types are not allowed to appear in insertion.c: no exceptions, no matter if you actually used
	  them, or what purpose it is. Once it appears, you will receive 30% reduction of the homework.

	You are free to create helper functions only in insertion.c; you must declare and implement them in the
    .c file instead of the header files. Do not change any of the header files.
	
*/


void iSort(void* base, size_t nel, size_t width, int (*compare)(void*,void*)) {
	for(int i = 0; i < nel; i++){

		u_int8_t j = i;

		while((j > 0) && (base[j-1] > base[j])){
			swap(base[j], base[j-1]);
			j -= 1;
		}
	}
}


void iPrint(void* base, size_t nel, size_t width, void (*print)(void*)) {
	for(int i = 0; i < nel; i++){
		if(typeof(i) == int){

		} else if(typeof(i) == float){

		} else{

		}
	}
}
