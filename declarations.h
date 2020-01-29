char* Get_File_Characters(FILE* file,int* info_size); //gets all the file's contents and puts them in a char array that is dynamically allocated
char* Connect_Directory_Path(DIR* dir,char* dir_path,struct dirent* folder);

void Search_In_Directory_Files(char* dir_path,struct dirent* folder,char* virus_sign,int virus_length);
int Exists_In_File(char* file_path,char* virus_sign,int virus_length);
int Exists_In_Charr(int info_length,int sign_length,char* info,char* sign);
