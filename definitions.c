#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "config.h"
#include "declarations.h"

char* Get_File_Characters(FILE* file,int* info_size){
    int length=0;
    char file_character; //gets input from the file, character by character
    char* input_ptr=NULL; //all the data that was on the file will be in this array when we're done here
    char* temp_ptr; //used to protect previously gathered data in case the realloc function fails and returns NULL
    file_character=fgetc(file); //getting the first character from the file
    do{
        temp_ptr = (char*)realloc(input_ptr,(length+1)*sizeof(char)); //enlarging the dynamically allocated array
        if(temp_ptr!=NULL){
            input_ptr = temp_ptr;
            input_ptr[length++]=file_character; //adding the new character to the array
            file_character=fgetc(file); //getting the next character from the file
        }
    }while((file_character!=EOF) & (temp_ptr!=NULL));
    *info_size=length;
    if(temp_ptr==NULL){
        printf("There was a problem with reading the file: realloc failed to reallocate memory\n");return NULL;
    }
    else{
        return input_ptr;
    }
}

char* Connect_Directory_Path(DIR* dir,char* dir_path,struct dirent* folder){
    if(dir==NULL){
        printf("The path given in the argument to the directory is invalid or inaccessible...\n");
        return NULL;
    }
    folder = readdir(dir); //reads a file from the directory, starting from the first and goes to the next one each time.
    if(folder==NULL){  //checks if we went past the last file in the directory, meaning we finished our work.
        printf("Done going over the directory.\n");
        return NULL;
    }
    while(*(folder->d_name)=='.'){
        folder=readdir(dir);
    }

    return strcat(dir_path,folder->d_name); //returns the path to the directory concatted with the file name
}

int Exists_In_Charr(int info_length,int sign_length,char* info,char* sign){
    printf("info is %s\n",info);
    printf("sign is %s\n",sign);
    for(int i=0;i<info_length;i++){
        int flag=1;
        for(int j=0;j<sign_length;j++){
            flag*=(sign[j]==info[i+j]);
        }
        if(flag==1){
            return 1;
        }
    }
    return 0;
}

int Exists_In_File(char* file_path,char* virus_sign,int virus_length){
    FILE* file = fopen(file_path,"r");
    int file_size;
    char* file_info = Get_File_Characters(file,&file_size);
    return Exists_In_Charr(file_size,virus_length,file_info,virus_sign);
}

void Search_In_Directory_Files(char* dir_path,struct dirent* folder,char* virus_sign,int virus_length){
    char* file_path;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //connecting to the console
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo); //getting info from the console, including the font's info
    saved_attributes = consoleInfo.wAttributes;
    DIR* dir = opendir(dir_path);  //connects to the directory in the location dir_path
    do{
        file_path = Connect_Directory_Path(dir,dir_path,folder); //gets a path to a file from the folder
        if(file_path!=NULL){
            if(Exists_In_File(file_path,virus_sign,virus_length)){
            SetConsoleTextAttribute(hConsole, UNSAFE_COLOR); //sets the print color to the safe color
        }
        else{
            SetConsoleTextAttribute(hConsole, SAFE_COLOR); //sets the print color to the unsafe color
        }
        printf("%s\n",file_path); //prints the file name in the color set by the previous "if" statement
        SetConsoleTextAttribute(hConsole, saved_attributes); // Restore original attributes
        }
    }while(file_path!=NULL); //goes as long as there are still files in the directory
    free(file_path); //the dynamically allocated array from the function Concat_Char_Arrays is no longer needed, so we free the memory space it took up.
}
