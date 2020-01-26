char* Get_File_Characters(FILE* file); //gets all the file's contents and puts them in a char array that is dynamically allocated
char* Connect_Directory_Path(DIR* dir_path,dirent* folder);

char* Concat_Char_Arrays(char* arr_1,char* arr_2);
char* Duplicate_Char_Array(char* arr);

void Search_In_Directory_Files(DIR* dir_path,dirent* folder,char* virus_sign);
