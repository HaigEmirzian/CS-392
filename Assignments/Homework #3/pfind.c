#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

// Pledge: I pledge my honor that I have abided by the Stevens Honor System.
// Name: Haig Emirzian

//checks to see if permission string is valid
bool validString(const char* permString){
    for(int i = 0; i < 9; i+=3){
        if((i != "r") && (i != "w") && (i != "x") && (i != "-")){
            fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", permString);
            exit(EXIT_FAILURE);
        }else if((permString[i] != "r" || permString[i] != "-") && (permString[i+1] != "w" || permString[i] != "-") && (permString[i+2] != "x" || permString[i] != "-")){
            fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", permString);
            exit(EXIT_FAILURE);
        }
    }
    return true;
}

//recursively navigates directory tree and prints out files that match target perms
void navigatingDirectories(const char* directory, const char* permString){

}

int main(int argc, char* argv[]){
    
    return 0;
}