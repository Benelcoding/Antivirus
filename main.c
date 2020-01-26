#include "definitions.c"
#include "declarations.h"

char* virus_sign;
FILE* virus_file;
struct dirent* folder;

int main(int argc, char** argv){
    virus_file = fopen(argv[1],"r");
    virus_sign = Get_File_Characters(virus_file);

    Search_In_Directory_Files(argv[2],folder,virus_sign);
}

