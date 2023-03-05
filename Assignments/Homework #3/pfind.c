#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdbool.h>
#include <string.h> 
#include <unistd.h>

// Pledge: I pledge my honor that I have abided by the Stevens Honor System.
// Name: Haig Emirzian

//checks to see if permission string is valid
bool validString(const char* permString){
    //checks to see if permString is 9 bits with null terminator
    if(strlen(permString) != 9){
        fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", permString);
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < 9; i+=3){
        //checks to see if either r,w,x,- are being used
        if((permString[i] != 'r') && 
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
        }else{
            return true;
        }
    }
    
}

//recursively navigates directory tree and prints out files that match target perms
void navigatingFiles(const char* directory, const char* permString){
    DIR* dr;
    struct dirent* dir;
    struct stat fileinfo;
    char path[1024];

    if(validString(permString) != true){
        return;
    }

    if((dr = opendir(directory)) == NULL){
        realpath(directory, path);
        fprintf(stderr, "Error: Cannot open directory '%s'. Permission denied.\n", path);
        exit(EXIT_FAILURE);
    }
    
    while((dir = readdir(dr)) != NULL){
        if(strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0){
            continue;
        }

        char* newPath = realpath(directory, path);
        char* newDir = malloc(strlen(newPath) + strlen(dir->d_name) + 2);
        snprintf(newDir, strlen(newPath) + strlen(dir->d_name) + 2, "%s/%s", newPath, dir->d_name);

        int status = stat(newDir, &fileinfo);
        if(status < 0){
            fprintf(stderr, "Error: Cannot find information on file.\n");
        }

        if(S_ISREG(fileinfo.st_mode)){
            char permBits[10] = "";
            char* r = "r";
            char* w = "w";
            char* x = "x";
            char* dash = "-";

            if((fileinfo.st_mode & S_IRUSR)){
                strcat(permBits, r);
            } else{
                strcat(permBits, dash);
            }

            if((fileinfo.st_mode & S_IWUSR)){
                strcat(permBits, w);
            } else{
                strcat(permBits, dash);
            }

            if((fileinfo.st_mode & S_IXUSR)){
                strcat(permBits, x);
            } else{
                strcat(permBits, dash);
            }

            if((fileinfo.st_mode & S_IRGRP)){
                strcat(permBits, r);
            } else{
                strcat(permBits, dash);
            }

            if((fileinfo.st_mode & S_IWGRP)){
                strcat(permBits, w);
            } else{
                strcat(permBits, dash);
            }

            if((fileinfo.st_mode & S_IXGRP)){
                strcat(permBits, x);
            } else{
                strcat(permBits, dash);
            }

            if((fileinfo.st_mode & S_IROTH)){
                strcat(permBits, r);
            } else{
                strcat(permBits, dash);
            }

            if((fileinfo.st_mode & S_IWOTH)){
                strcat(permBits, w);
            } else{
                strcat(permBits, dash);
            }

            if((fileinfo.st_mode & S_IXOTH)){
                strcat(permBits, x);
            } else{
                strcat(permBits, dash);
            }

            strcat(permBits, "\0");

            if(strcmp(permBits, permString) == 0){
                printf("%s\n", newDir);
            }
        }else if(S_ISDIR(fileinfo.st_mode)){
            navigatingFiles(newDir, permString);
        }

        free(newDir);
    }
    closedir(dr);
}

int main(int argc, char* argv[]){
    
    navigatingFiles(argv[1], argv[2]);

    // Test: Valid Strings
    //char* permString1 = "rwxrwxrwx";
    // char* permString2 = "rw-rw-r--";
    // char* permString3 = "rwxrw-rw-";
    
    // validString(permString1); // should return true
    // validString(permString2); // should return true
    // validString(permString3); // should return true
    
    // Test: Invalid Strings
    // char* invalidPermString1 = "rwxrwxrwxr";
    // char* invalidPermString2 = "rwxrwxrx!";
    // char* invalidPermString3 = "rwrxw-rw-";

    // validString(invalidPermString1); // should print error message and exit
    // validString(invalidPermString2); // should print error message and exit
    // validString(invalidPermString3); // should print error message and exit

    //Test: Valid run
    // char* directory = "test_dir";
    // navigatingFiles(directory, "rwxrwx---");

    return 0;
}