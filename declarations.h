char* Get_File_Characters(FILE* file,int* info_size); //gets all the file's contents and puts them in a char array that is dynamically allocated
char* Connect_Directory_Path(char* dir_path,struct dirent* folder);

char* Concat_Char_Arrays(char* arr_1,char* arr_2);
char* Duplicate_Char_Array(char* arr);
int Get_Arr_Size(char* arr_1);

void Search_In_Directory_Files(char* dir_path,struct dirent* folder,char* virus_sign,int virus_length);
int Exists_In_File(char* file_path,char* virus_sign,int virus_length);
int Exists_In_Charr(char* info,char* sign);
