#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h> 

// Pledge: I pledge my honor that I have abided by the Stevens Honor System.
// Name: Haig Emirzian

//checks to see if permission string is valid
bool validString(const char* permString){
    for(int i = 0; i < 9; i+=3){
        //checks to see if permString is 9
        if(strlen(permString) != 9){
            fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", permString);
            exit(EXIT_FAILURE);
        }
        //checks to see if either r,w,x,- are being used
        else if((permString[i] != 'r') && 
                (permString[i] != 'w') && 
                (permString[i] != 'x') && 
                (permString[i] != '-')){
            
            fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", permString);
            exit(EXIT_FAILURE);
        }
        //checks to see if rwx are being used in the order they should be in
        else if(!((permString[i] == 'r' || permString[i] == '-') && 
                (permString[i+1] == 'w' || permString[i+1] == '-') && 
                (permString[i+2] == 'x' || permString[i+2] == '-'))){

            fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", permString);
            exit(EXIT_FAILURE);
        }
    }
    return true;
}

//recursively navigates directory tree and prints out files that match target perms
void navigatingFiles(const char* directory, const char* permString){
    // DIR* dr;
    // if((dr = opendir(directory)) == NULL){
    //     char path[100];
    //     realpath(directory, path);
    //     fprintf(stderr, "Error: Cannot open directory '%s'. Permission denied.\n", path);
    //     exit(EXIT_FAILURE);
    // }

    // //snprintf() to concatenate /home and test_dir /home/test_dir
    // //get perms of files or directory use stat() stat will give perms in number mode change to rwx format
    // //use strcmp()
    // //if statement: if file or dir, if dir then recursive call

    // struct stat fileinfo;
    // char* permBits = "";
    // int status = stat(directory, &fileinfo);

    // if((fileinfo.st_mode & S_IRUSR) == 1){
    //     //strcat(permBits, )
    // }


    // if(S_ISREG(fileinfo.st_mode)){

    // } else if(S_ISDIR(fileinfo.st_mode)){

    // }

}

int main(){
    
    char* print = "rwxrwxrwx";
    
    validString(print);

    char* danger_dir = "test_dir";
    char* permString = "rwxrwxrwx";
    navigatingFiles(danger_dir, permString);

    char* test1 = "Hello ";
    char* test2 = "World";
    // strcat(test1, test2);
    printf("%s\n",test1);

    return 0;
}