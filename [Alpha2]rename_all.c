/*                          Application : Extension changer for multiple files ( windows )

                            features : supports extension changing of multiple files at once
                                     : change up to 50 files in one execution

                            version :                   YY.MM.ver
                                      initial release : 20.08.01Beta   ( current )

                            This program is an open-source work of an individual programmer 'illogical'.
                            Around 30% of part is copied/inspired from StackOverflow.
                            https://stackoverflow.com/questions/51804567/c-writing-readdir-to-char-array-variable/51804792
                            You're welcomed to test it's vulnerability and suggest for improvements.

                            Suggest and mail me at preritvishal3@gmail.com

                            Warm regards : illogical AKA Prerit Vishal

*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>                           // opendir
#include <dirent.h>                              // opendir, readdir
#include <limits.h>                              // for PATH_MAX

#define n printf("\n");
#define t printf("\t");

//Global Declarations

char default_path[500];                          // default path to look in
char name_of_file[500];                          // for copying and renaming selected file
char extension[7];                               // for extension
size_t i=0;                                      // for non negative value
struct dirent *read_dir_ptr = NULL;              // dirent pointer (readdir)
       DIR *directory_pointer = NULL;            // directory pointer (opendir)
int file_num = -50,loop_var=0;                   // selection file by number

// Functions

void enter_path(void);              // function to enter dir path
void open_dir(char a[]);            // function to open the entered path
void list_files(void);              // function to list files in opened dir
void enter_extension(void);         // function to store and check the extension
void rename_files(void);            // function to check how one or all files are selected


int main (){

    enter_path();                   // prompt to enter path
    open_dir(default_path);         // function to open the entered path
    list_files();                   // function to list file
    enter_extension();              // type in extension to rename
    rename_files();                 // rename the file

return 0;
}

void enter_path(void){
    n;n;t;
    printf("Enter the path of directory : ");
    gets(default_path);
    n;n;
}

void open_dir(char default_path[]){
    directory_pointer = opendir(default_path);
    if(directory_pointer == NULL )
    {
        n;t;
        perror("Error ");
        exit(0);
    }
    else
        printf("\n\tDirectory opened.\n\n");
}

void list_files(void){
    i=0;
    while ((read_dir_ptr = readdir(directory_pointer)))
    {
        if (!strcmp (read_dir_ptr->d_name, ".") || !strcmp (read_dir_ptr->d_name, ".."))    // to skip "." files
            continue;

            printf("%5d   %-30s\n",++i,(read_dir_ptr->d_name));
    }
}

void enter_extension(void){
    printf("\n\tEnter extension with \".\" : ");
    scanf("%s",extension);

    if(extension[0]!='.'){
        char temp[7] = {0};
        strcpy(temp,extension);

        extension[0] = '.';
        strcat(extension,temp);
    }
    n;
}

void rename_files(void){
  int i = 0;
    char temp[500]={};
    char temp1[5] = {};

    directory_pointer = opendir(default_path);
    while ((read_dir_ptr = readdir(directory_pointer)))
    {
        if (!strcmp (read_dir_ptr->d_name, ".") || !strcmp (read_dir_ptr->d_name, ".."))    // to skip "." files
            continue;

            temp[0] = '\0';
            strcpy(name_of_file,(read_dir_ptr->d_name));

            strcpy(temp,"File_");
            itoa(i,temp1,10);
            strcat(temp,temp1);
            strcat(temp,extension);

            printf("\nTemp : %s",temp);
            //getch();
            ++i;

          // activating the code below this will show real effect on the path you entered
            // you've been warned

                char old_path[700]={};
                char new_path[700]={};

                strcpy(old_path,default_path);
                strcat(old_path,"\\");
                strcat(old_path,name_of_file);

                strcpy(new_path,default_path);
                strcat(new_path,"\\");
                strcat(new_path,temp);

                rename(old_path,new_path);
    }
closedir(directory_pointer);
}
