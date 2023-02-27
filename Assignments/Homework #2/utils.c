#include "utils.h"
#include <string.h>
#include <stdlib.h>

// Pledge: I pledge my honor that I have abided by the Stevens Honor System.
// Name: Haig Emirzian

/*
	You are free to use any data type you like in this file.
    However, other than the five functions declared in "utils.h",
    DO NOT create any other functions.
	
*/

//compares ints in iSort
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

//compares floats in iSort
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

//prints int in iPrint
void print_int(void* var) {
    int result = *((int*) var);
    printf("%d\n", result);
    
}

//prints float in iPrint
void print_float(void* var) {
	float result = *((float*) var);
    printf("%f\n", result);
}

//reads every line from a file and stores each number in an array
void* read_array(char* filename, char* format, size_t* len) {
    FILE* fp;

    if((fp = fopen(filename, "r")) == NULL){
        fprintf(stderr, "File failed to open.\n");
        exit(1);
    } 

    int lineLength = 1024;
    int numberOfNewLines = 0;

    //executes if numbers in file are ints
    if(strcmp(format, "%d") == 0){
        int index = 0;
        char fgetsArray[lineLength];
        while(fgets(fgetsArray, lineLength, fp)){
            numberOfNewLines++;
        }
        //creates an array of the data according to the number of lines
        fseek(fp, 0, SEEK_SET);
        int* dataArray = malloc(numberOfNewLines * sizeof(int));
        index = 0;

        while(fgets(fgetsArray, lineLength, fp)){
            dataArray[index] = atoi(fgetsArray);
            index++;
        }

        //closes file and updates length
        fclose(fp);
        *len = numberOfNewLines;
        return dataArray;
    } 
    
    //executes if numbers in file are floats
    if(strcmp(format, "%f") == 0){
        int index = 0;
        char fgetsArray[lineLength];
        while(fgets(fgetsArray, lineLength, fp)){
            numberOfNewLines++;
        }
        //creates an array of the data according to the number of lines
        fseek(fp, 0, SEEK_SET);
        float* dataArray = malloc(numberOfNewLines * sizeof(float));
        index = 0;

        while(fgets(fgetsArray, lineLength, fp)){
            dataArray[index] = atof(fgetsArray);
            index++;
        }

        //closes file and updates length
        fclose(fp);
        *len = numberOfNewLines;
        return dataArray;
    } 

    //if none return, then exit
    fprintf(stderr, "Try a different type.\n");
    exit(1);
}
