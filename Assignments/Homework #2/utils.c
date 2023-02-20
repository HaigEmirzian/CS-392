#include "utils.h"
#include <string.h>

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

    if(na < nb) {
        return -1;
    } else if(na > nb) {
        return 1;
    } else {
        return 0;
    }
}

void print_int(void* var) {
    int *result = var;
    int length = sizeof(result) / sizeof(result[0]);

    for(int i = 0; i < length; i++){
        printf("%d\n", result[i]);
    }
}

void print_float(void* var) {
	float *result = var;
    int length = sizeof(result) / sizeof(result[0]);

    for(int i = 0; i < length; i++){
        printf("%f\n", result[i]);
    }
}


void* read_array(char* filename, char* format, size_t* len) {
	FILE* fp;
    
    if((fp = fopen((*filename), "r")) == NULL){
        fprintf(stderr, "File failed to open.\n");
        exit(1);
    } 

    int lineLength = 1024;

    if(strcmp(format, "%d") == 0){
        int arrayLength = *len;
        int* dataArray = malloc(arrayLength * sizeof(int));
        
        int index = 0;
        char fgetsArray[lineLength];
        while (fgets(fgetsArray, lineLength, fp)){
            dataArray[index] = atoi(fgetsArray);
            index++;
        }
        fclose(fp);
        return dataArray;
    } 
    
    if(strcmp((*format), "%f") == 0){
        int arrayLength = *len;
        float* dataArray = malloc(arrayLength * sizeof(float));
        
        int index = 0;
        char fgetsArray[lineLength];
        while (fgets(fgetsArray, lineLength, fp)) {
            dataArray[index] = atof(fgetsArray);
            index++;
        }
        fclose(fp);
        return dataArray;
    } 

    fprintf(stderr, "Error: Try again.\n");
    exit(1);
}