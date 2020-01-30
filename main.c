#include "definitions.c"


char* virus_sign; //stores the virus's signature.
FILE* virus_file; //stored a pointer to the file that has the virus's signature.
struct dirent* folder; //stores a pointer to the structure that handles traversing the directory that we are given.
int virus_length; //length of the virus's signature

int main(int argc, char** argv){
    if(argc!=3){
        printf("Invalid input! There should be exactly 2 arguments with the function declaration!\n"); //self explanatory (by the message).
    }
    virus_file = fopen(argv[1],"r"); //stores a pointer to the file who's path was sent in the first argument, which is the file that has the virus signature.
    virus_sign = GetFileCharacters(virus_file,&virus_length); //gets the contents of the virus file, which are the virus's signature.

    SearchInDirectoryFiles(argv[2],folder,virus_sign,virus_length); //handles searching for the virus's signature in the directory that was given as the second argument.

    fclose(virus_file); //closes the file.
    free(virus_sign); //frees the allocated memory we used to store the virus's sign.
    return 0;
}

