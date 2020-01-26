#include "definitions.c"
#include "declarations.h"

char* virus_sign;
FILE* virus_file;
DIR* dir_path;
struct dirent* folder;

int main(int argc, char** argv){
    virus_file = fopen(argv[0],"r");
    virus_sign = Get_File_Characters(virus_file);

    dir_path = opendir(argv[1]);
    Search_In_Directory_Files(dir_path,folder,virus_sign);
}

