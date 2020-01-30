#include "definitions.c"
/*
has the definitions of the functions used here, as well as the libraries
<stdio.h> and <dirent.h> that we need for printing and using dirent to traverse files respectively.
*/

char* virus_sign; //stores the virus's signature.
FILE* virus_file; //stored a pointer to the file that has the virus's signature.
struct dirent* folder; //stores a pointer to the structure that handles traversing the directory that we are given.
int virus_length; //length of the virus's signature
/*
Main:
Entrance Clause: gets the number of arguments given when it was called, and an array that has these arguments. they are:
 0) The calling of main, 1) The path to the file where the virus signature is stored, and
 2) The path to the directory where we want to search for the signature in it's files.

 Exit Clause: Prints the names of the files that don't have the virus signature in a safe color (in our case green)
 and the files that do have the virus's signature get printed in an unsafe color (in our case red).
*/
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

