#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
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

char* Connect_Directory_Path(char* dir_path,struct dirent* folder){
    printf("Enters Connect_Directory_Path \n");
    DIR* dir = opendir(dir_path);  //connects to the directory in the location dir_path
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
    return Concat_Char_Arrays(dir_path,folder->d_name); //returns the path to the directory concatted with the file name
}

int Exists_In_Charr(char* info,char* sign){
    printf("Enters Exists_In_Charr \n\n");
    int sign_length = Get_Arr_Size(sign);
    int info_length = Get_Arr_Size(info);
    int flag=1;
    for(int i=0;i<info_length;i++){
        for(int j=0;j<sign_length;j++){
            flag*=(sign[j]==info[i+j]);
        }
        if(flag==1){
            return 1;
        }
    }
    printf("\nExits Exists_In_Charr \n");
    return 0;
}

int Exists_In_File(char* file_path,char* virus_sign,int virus_length){
    printf("Enters Exists_in_file \n\n");
    FILE* file = fopen(file_path,"r");
    int file_size;
    char* file_info = Get_File_Characters(file,&file_size);
    printf("The file's size is: %d\n",file_size);
    printf("%s\n",file_info);
    printf("\nExits Exists_in_file \n");

    return Exists_In_Charr(file_info,virus_sign);
}

void Search_In_Directory_Files(char* dir_path,struct dirent* folder,char* virus_sign,int virus_length){
    printf("Enters Search_In_Directory_Files \n\n");
    char* file_path;
    do{
        file_path = Connect_Directory_Path(dir_path,folder); //gets a path to a file from the folder

        if(Exists_In_File(file_path,virus_sign,virus_length)){
            printf(SAFE_COLOR); //sets the print color to the safe color
        }
        else{
            printf(UNSAFE_COLOR); //sets the print color to the unsafe color
        }
        printf("%s\n",*(folder->d_name)); //prints the file name in the color set by the previous "if" statement
        printf(NORMAL_COLOR);
        free(file_path); //the dynamically allocated array from the function Concat_Char_Arrays is no longer needed, so we free the memory space it took up.

    }while(file_path!=NULL); //goes as long as there are still files in the directory
    printf("\nExits Search_In_Directory_Files \n");
}

char* Concat_Char_Arrays(char* arr_1,char* arr_2){
    printf("Enters Concat_Char_Arrays \n\n");
    char* concatted=Duplicate_Char_Array(arr_1);
    char arr_2_char=arr_2[0];
    printf("arr2char: %c\n",arr_2_char);

    int length_of_arr_1=Get_Arr_Size(arr_1);
    int length_of_arr_2=Get_Arr_Size(arr_2);

    printf("length 1: %d\nlength 2: %d\n",length_of_arr_1,length_of_arr_2);

    for(int i=length_of_arr_1+1;arr_2_char!='\0';i++){
        realloc(concatted,((i)*sizeof(char)));
        concatted[i-1]=arr_2_char;
        arr_2_char=arr_2[i-length_of_arr_1];
    }
    printf("arr_1: %s\narr_2: %s\nconcatted: %s\n",arr_1,arr_2,concatted);
    printf("\nExits Concat_Char_Arrays \n");
    printf("\nExits Connect_Directory_Path \n");
    return concatted;
}

int Get_Arr_Size(char* arr_1)
{
    int i=1;
    while(arr_1[i]!='\0'){
        i++;
    }
    return i;
}

char* Duplicate_Char_Array(char* arr){
    printf("Enters Duplicate_Char_Array \n\n");
    char* dupe = malloc(Get_Arr_Size(arr));
    char arr_char=arr[0];
    for(int i=0;arr_char!='\0';i++){
        arr_char=arr[i];
        dupe[i]=arr_char;
    }
    printf("\nexits Duplicate_Char_Array \n");
    return dupe;
}



