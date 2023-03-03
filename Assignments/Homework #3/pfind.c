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
    if(strlen(permString) != 10){
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
        }
    }
    return true;
}

//recursively navigates directory tree and prints out files that match target perms
void navigatingFiles(const char* directory, const char* permString){
    DIR* dr;
    if((dr = opendir(directory)) == NULL){
        char path[100];
        realpath(directory, path);
        fprintf(stderr, "Error: Cannot open directory '%s'. Permission denied.\n", path);
        exit(EXIT_FAILURE);
    }

    //snprintf() to concatenate /home and test_dir /home/test_dir
    //get perms of files or directory use stat() stat will give perms in number mode change to rwx format
    //use strcmp()
    //if statement: if file or dir, if dir then recursive call

    struct stat fileinfo;
    int status = stat(directory, &fileinfo);
    char permBits[10] = "";
    char* r = "r";
    char* w = "w";
    char* x = "x";
    char* - = "-";

    if((fileinfo.st_mode & S_IRUSR) || (fileinfo.st_mode & S_IRGRP) || (fileinfo.st_mode & S_IROTH)){
        strcat(permBits, r);
    } else{
        strcat(permBits, -);
    }

    if((fileinfo.st_mode & S_IWUSR) || (fileinfo.st_mode & S_IWGRP) || (fileinfo.st_mode & S_IWOTH)){
        strcat(permBits, w);
    } else{
        strcat(permBits, -);
    }

    if((fileinfo.st_mode & S_IXUSR) || (fileinfo.st_mode & S_IXGRP) || (fileinfo.st_mode & S_IXOTH)){
        strcat(permBits, x);
    } else{
        strcat(permBits, -);
    }

    strcat(permBits, '\0');

    if(S_ISREG(fileinfo.st_mode)){
        //if reg file, then print file
    } else if(S_ISDIR(fileinfo.st_mode)){
        struct dirent* de;
        while((de = readdir(dr)) != NULL){
            if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0){
                continue;
            }
            char* newDir = malloc(strlen(directory) + strlen(de->d_name) + 2);
            snprintf(newDir, strlen(directory) + strlen(de->d_name) + 2, "%s/%s", directory, de->d_name);
            navigatingFiles(newDir, permString);
            free(newDir);
        }
    }

    closedir(dr);
}

int main(){
    
    //tests validString
    char* print = "rwxrwxrwx";
    validString(print);

    //tests navigatingFiles
    char* danger_dir = "test_dir";
    char* permString = "rwxrwxrwx";
    navigatingFiles(danger_dir, permString);

    return 0;
}