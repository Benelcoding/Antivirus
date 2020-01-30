#include <dirent.h> //used to traverse files in a directory.
#include <stdio.h> //used for printing to the screen.
#include <stdlib.h> //used for dynamic memory allocation.
#include <windows.h> //is used to get a handle on the console and print text in color!
#include "config.h" //has constants used for printing colors.
#include "declarations.h" //has declarations of all functions in this file.

char* GetFileCharacters(FILE* file,int* info_size){
    int length=0;
    char file_character; //gets input from the file, character by character.
    char* input_ptr=NULL; //all the data that was on the file will be in this array when we're done here.
    char* temp_ptr; //used to protect previously gathered data in case the realloc function fails and returns NULL.
    file_character=fgetc(file); //getting the first character from the file.
    do{
        temp_ptr = (char*)realloc(input_ptr,(length+1)*sizeof(char)); //enlarging the dynamically allocated array
        if(temp_ptr!=NULL){
            input_ptr = temp_ptr;
            input_ptr[length++]=file_character; //adding the new character to the array.
            file_character=fgetc(file); //getting the next character from the file.
        }
    }while((file_character!=EOF) & (temp_ptr!=NULL));
    *info_size=length;
    if(temp_ptr==NULL){ //if temp_ptr is null, that means that we couldn't allocate memory.
        printf("There was a problem with reading the file: realloc failed to reallocate memory\n");return NULL;
    }
    else{
        return input_ptr;
    }
}

char* ConnectDirectoryPath(DIR* dir,char* temp_path,struct dirent* folder){
    if(dir==NULL){ //if the pointer to the directory is null, that must mean the path that we were given was invalid.
        printf("The path given in the argument to the directory is invalid or inaccessible...\n");
        return NULL;
    }
    folder = readdir(dir); //reads a file from the directory, starting from the first and goes to the next one each time.
    if(folder==NULL){  //checks if we went past the last file in the directory, meaning we finished our work.
        printf("Done going over the directory.\n");
        return NULL;
    }
    while(*(folder->d_name)=='.'){ //dirent will sometimes return invalid names for files (which will always be '.') so we must cycle past them.
        folder=readdir(dir);
    }
    temp_path=realloc(temp_path,strlen(folder->d_name)+strlen(temp_path)+1);
    return strcat(temp_path,folder->d_name); //returns the path to the directory concatted with the file name.
}

int ExistsInCharr(int info_length,int sign_length,char* info,char* sign){
    for(int i=0;i<info_length;i++){ //goes over the whole "info" string.
        int flag=1; //uses a flag to check if the "sign" string is present in the "info" string.
        for(int j=0;j<sign_length;j++){//compares each char in "sign" to a char in "info" one by one.
            flag*=(sign[j]==info[i+j]);
        }
        if(flag==1){
            return 1;//if after going over all of the "sign", flag is 1, that means that "sign" is present in "info".
        }
    }
    return 0; //if the function made it here, then "sign" isn't present in "info".
}

int ExistsInFile(char* file_path,char* virus_sign,int virus_length){
    FILE* file = fopen(file_path,"r"); //connects the the file at "file_path" to read from it.
    int file_size;
    char* file_info = GetFileCharacters(file,&file_size); //gets the file's contents and it's size.
    return ExistsInCharr(file_size,virus_length,file_info,virus_sign); //checking if the sign is present in the file's contents.

void SearchInDirectoryFiles(char* dir_path,struct dirent* folder,char* virus_sign,int virus_length){
    char* file_path;
    char* temp_path;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //connecting to the console.
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo); //getting info from the console, including the font's info.
    saved_attributes = consoleInfo.wAttributes; //saving the original system text color.
    DIR* dir = opendir(dir_path);  //connects to the directory in the location dir_path.
    do{
        free(temp_path); //the dynamically allocated array from the function Concat_Char_Arrays is no longer needed, so we free the memory space it took up.
        temp_path = malloc(strlen(dir_path)+1);
        strcpy(temp_path,dir_path);
        file_path = ConnectDirectoryPath(dir,temp_path,folder); //gets a path to a file from the folder.

        if(file_path!=NULL){
            if(ExistsInFile(temp_path,virus_sign,virus_length)){
                SetConsoleTextAttribute(hConsole, UNSAFE_COLOR); //sets the print color to the safe color.
            }
            else{
                SetConsoleTextAttribute(hConsole, SAFE_COLOR); //sets the print color to the unsafe color.
            }
        printf("%s\n",temp_path); //prints the file name in the color set by the previous "if" statement.
        SetConsoleTextAttribute(hConsole, saved_attributes); // Restore original attributes.
        }
    }while(file_path!=NULL); //goes as long as there are still files in the directory.
    free(file_path); //the dynamically allocated array from the function Concat_Char_Arrays is no longer needed, so we free the memory space it took up.
}
