#include <dirent.h>
#include <stdio.h>
#include "config.h"

char* Get_File_Characters(FILE* file){
    int length=0;
    char file_character; //gets input from the file, character by character
    char* input_ptr; //all the data that was on the file will be in this array when we're done here
    char* temp_ptr = 0; //used to protect previously gathered data in case the realloc function fails and returns NULL

    fscanf(file,"%c",file_character); //getting the first character from the file
    while((file_character!=EOF) & (temp_ptr!=NULL)){
        temp_ptr = realloc(input_ptr,(length+1)*sizeof(char)); //enlarging the dynamically allocated array
        if(temp_ptr!=NULL){
            input_ptr = temp_ptr;
            input_ptr[length++]=file_character; //adding the new character to the array
            fscanf(file,"%c",file_character); //getting the next character from the file
        }
    }
    if(temp_ptr==NULL){
        printf("There was a problem with reading the file: realloc failed to reallocate memory");return NULL;
    }
    else{
        return input_ptr;
    }
}

char* Connect_Directory_Path(char* dir_path,dirent* folder){
    DIR* dir = opendir(dir_path);
    if(dir==NULL){
        printf("The path given in the argument to the directory is invalid or inaccessible...");
        return NULL;
    }
    folder = readdir(dir); //reads a file from the directory, starting from the first and goes to the next one each time.
    if(folder==NULL){  //checks if we went past the last file in the directory, meaning we finished our work.
        printf("Done going over the directory.");
        return NULL;
    }
    return Concat_Char_Arrays(dir_path,folder->d_name); //returns the path to the directory concatted with the file name
}

char* Duplicate_Char_Array(char* arr){
    char* dupe = malloc(sizeof(arr));
    char arr_char=arr[0];
    for(int i=0;arr_char!='\0';i++){
        dupe[i]=arr_char;
        arr_char=arr[i];
    }
    return dupe;
}

char* Concat_Char_Arrays(char* arr_1,char* arr_2){
    char* concatted=Duplicate_Char_Array(arr_1);

    char arr_2_char=arr_2[0];
    int length_of_arr_1=sizeof(arr_1)/sizeof(char);

    for(int i=length_of_arr_1+1;arr_2_character!='\0';i++){
        realloc(concatted,((i)*sizeof(char)))
        concatted[i-1]=arr_2_char;
        arr_2_charr=arr_2[i-length_of_arr_1];
    }
    return concatted;
}

void Search_In_Directory_Files(char* dir_path,dirent* folder,char* virus_sign){
    char* file_path;
    do{
        file_path = Connect_Directory_Path(dir_path,folder); //gets a path to a file from the folder

        if(Exists_In_File(file_path,virus_sign)){
            printf(SAFE_COLOR); //sets the print color to the safe color
        }
        else{
            printf(UNSAFE_COLOR); //sets the print color to the unsafe color
        }
        print("%s\n",folder->d_name); //prints the file name in the color set by the previous "if" statement
        free(file_path); //the dynamically allocated array from the function Concat_Char_Arrays is no longer needed, so we free the memory space it took up.

    }while(file_path!=NULL); //goes as long as there are still files in the directory
}
int Exists_In_File(char* file_path,char* virus_sign);

int Exists_In_File(char* file_path,char* virus_sign){
    FILE* file = fopen(file_path);
    char* file_info = Get_File_Characters(file);
    return Exists_In_Charr(file_info,virus_sign);
}

int Exists_In_Charr(char* info,char* sign){
    sign_length = sizeof(sign)/sizeof(char);
    info_length = sizeof(info)/sizeof(char);
    int flag=1;
    for(int i=0;i<info_length;i++){
        for(int j=0;j<sign_length;j++){
            flag*=(sign[j]==info[i+j]);
        }
        if(flag==true){
            return 1;
        }
    }
    return 0;
}
