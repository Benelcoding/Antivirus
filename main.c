#include "definitions.c"


char* virus_sign;
FILE* virus_file;
struct dirent* folder;
int virus_length;

int main(int argc, char** argv){
    if(argc!=3){
        printf("Invalid input! There should be exactly 2 arguments with the function declaration!\n");
    }
    virus_file = fopen(argv[1],"r");
    virus_sign = Get_File_Characters(virus_file,&virus_length);

    Search_In_Directory_Files(argv[2],folder,virus_sign,virus_length);

    fclose(virus_file);
    free(virus_sign);
    return 0;
}

