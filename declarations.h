char* GetFileCharacters(FILE* file,int* info_size);
/*
Enter Clause: gets a pointer to a file, and a pointer to a int variable that is used to return the length of the contents inside the file.
Exit Clause: returns the contents of the file in a string format(char*).
*/

char* ConnectDirectoryPath(DIR* dir,char* temp_path,struct dirent* folder);
/*
Enter Clause: gets a pointer to the directory where the files are, its path, and a structure (dirent) that is used to go over the files in it.
Exit Clause: return the path to the file it connected to, and if we have reached the end of the directory returns NULL.

connects to the files in the directory one by one, letting us read the contents.
*/


int ExistsInFile(char* file_path,char* virus_sign,int virus_length);
/*
Enter Clause: gets a path to a file, a string and the string's length.
Exit Clause: returns 1 if the string exists in the file and 0 if it doesn't.
*/

int ExistsInCharr(int info_length,int sign_length,char* info,char* sign);
/*
Enter Clause: gets two strings and their lengths.
Exit Clause: returns 1 if the string "sign" exists in the string "info" and 0 if it doesn't.
*/

void SearchInDirectoryFiles(char* dir_path,struct dirent* folder,char* virus_sign,int virus_length);
/*
Enter Clause: gets a path to a directory, a pointer to it's dirent structure, a string and it's length.
Exit Clause: None.

This function handles basically the entire project.
It uses the previously mentioned functions to check if the string that it was sent exists in each file.
if so, prints the file's name in the color that represents an unsafe file (in this case red).
if not, it still prints the file's name but in the color that represents a safe file (in this case green).
*/
