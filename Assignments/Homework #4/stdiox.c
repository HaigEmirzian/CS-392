#include "stdiox.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>


int fprintfx(char* filename, char format, void* data);


int fscanfx(char* filename, char format, void* dst);


int clean();











int main(int argc, char const *argv[]) {

    int array[5] = {1,2,-9,12,-3};
    char* string = "Hello!";

    /* Print integers to stdout */
    for (size_t i = 0; i < 5; i++) {
        fprintfx("", 'd', &array[i]);
    }

    /* Print string to stdout */
    fprintfx("", 's', string);

    /* Error: unrecognized format */
    fprintfx("", 'i', string);

    /* Write integers to a text file */
    for(size_t i = 0; i < 5; i ++){
        fprintfx("text", 'd',&array[i]);
    }

    /* Write string to a text file */
    fprintfx("text", 's', string);

    clean();

    char newstr[1024] = {0};
    int num;
    /* Receive a string from stdin */
    fscanfx("", 's', newstr);
    /* Print out the string to stdout */
    fprintfx("", 's', newstr);

    /* Receive an integer from stdin */
    fscanfx("", 'd',&num);
    /* Print out the integer to stdout */
    fprintfx("", 'd',&num);

    /* Read a file */
    while(!fscanfx("text", 's', newstr)){
        fprintfx("", 's', "Line: ");
        fprintfx("", 's', newstr);
    }

    /* Close opened files */
    clean();

    return 0;
}