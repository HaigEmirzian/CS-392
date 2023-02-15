#include "utils.h"

// Pledge: I pledge my honor that I have abided by the Stevens Honor System.
// Name: Haig Emirzian

/*
	You are free to use any data type you like in this file.
    However, other than the five functions declared in "utils.h",
    DO NOT create any other functions.
	
*/

int cmpr_int(void* a, void* b) {
    int na = (*(int*) a);
    int nb = (*(int*) b);
    
    if(na < nb){
        return -1;
    } else if(na > nb){
        return 1;
    } else{
        return 0;
    }
}

int cmpr_float(void* a,void* b) {
	float na = (*(float*) a);
    float nb = (*(float*) b);

    if(na < nb){
        return -1;
    } else if(na > nb){
        return 1;
    } else{
        return 0;
    }
}

void print_int(void* var) {
    int length = sizeof(var)/sizeof(var[0]);

	(int*)result = (int*)var;

    for(int i = 0; i < length; i++){
        printf("%d\n", result);
    }
}

void print_float(void* var) {
	int length = sizeof(var)/sizeof(var[0]);

	(float*)result = (float*)var;
    
    for(int i = 0; i < length; i++){
        printf("%f\n", result);
    }
}


void* read_array(char* filename, char* format, size_t* len) {
	FILE* fp;
    
    if((fp = fopen(filename, "r")) == NULL){
        fprintf(stderr, "File failed to open.\n");
        exit(1);
    } 
}