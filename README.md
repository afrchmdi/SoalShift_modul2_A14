# SoalShift_modul2_A14

Soal Shift Modul 2
1. [Soal 1](#1-soal-1)
2. [Soal 2](#2-soal-2)
3. [Soal 3](#3-soal-3)
4. [Soal 4](#4-soal-4)
5. [Soal 5](#5-soal-5)


### 1. Soal 1
##### Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
##### Catatan : Tidak boleh menggunakan crontab.

```sh
#include <stdio.h> 
#include <dirent.h> 
#include <string.h>

char *rename_it(char * remove_it)
{
    char re [100];
    char *ext=strrchr(remove_it, '.');
    char *ree = strncpy(re, remove_it, ext-remove_it);
    //printf("THISSSS??? %s\n", ree);
    return ree;
}


// void thiss(char * path){
    
//     if(ext) {
//         char *hehe=ext;

//         if((strcmp(hehe, ".png")) == 0){

//             if (len > 9){
//                 if(!strcmp(exx, "_grey.png")){
//               char *ext=strrchr(path, '.');
//     char *exx=strrchr(path, '_');
//     char extension[] = "_grey.png";
//     int len=strlen(path);     // printf("%s..\n", path);
//                     printf("this is NOT the file you-re looking for\n");
//                     return;
//                 }
//             }
//             printf("this IS the file you are lookin for!\n");
//             char *re=rename_it(dirr->d_name);
//             //printf("THIS????? %s\n", re);
//             char *newname=strcat(re, "_grey.png");
//             // rename(path, newname);
//             // printf("hmmm %s\n", newname);
//         }
//     }
        
// }

void wat_file(char *path)
{
    struct dirent *dirr;
    DIR *da_dir = opendir(path);
    char this[1000];

    if (!da_dir)
        return;

    while ((dirr = readdir(da_dir)) != NULL)
    {
        if (strcmp(dirr->d_name, ".") != 0 && strcmp(dirr->d_name, "..") != 0)
        {
            if (dirr->d_type == DT_REG)
            {
                printf("file : %s\n", dirr->d_name);
                // printf("type is: %d", dirr->d_type);
                //thiss(dirr->d_name);

                char *ext=strrchr(dirr->d_name, '.');
                char *exx=strrchr(dirr->d_name, '_');
                char extension[] = "_grey.png";
                int len=strlen(dirr->d_name);

                if(ext) {
                    char *hehe=ext;

                    if((strcmp(hehe, ".png")) == 0){

                        if (len > 9){
                            if(!strcmp(exx, "_grey.png")){
                            // printf("%s..\n", path);
                                printf("this is NOT the file you-re looking for\n");
                                return;
                            }
                        }
                        printf("this IS the file you are lookin for!\n");
                        char *re=rename_it(dirr->d_name);
                        //printf("THIS????? %s\n", re);
                        //char *newname=strcat(re, "_grey.png");
                        rename(dirr->d_name, strcat(re, "_grey.png"));
                        if(rename(dirr->d_name, strcat(re, "_grey.png")) == 0){
                            printf("hmmm %s\n", dirr->d_name);
                        }
                        else{
                            printf("gagal:(\n");
                        }
                    }
                }
                
            }
                
            else if(dirr->d_type == DT_DIR)
            {
                strcpy(this, path);
                strcat(this, "/");
                strcat(this, dirr->d_name);
                printf("in folderrr :%s\n", dirr->d_name);
                //printf("-- %s\n", this);
                printf("--------\n");
                wat_file(this);
            }
            else{
                printf("file.. : %s\n", dirr->d_name);
            }
        }
    }
    printf("-------------------\n\n");

    closedir(da_dir);
}

int main(void) 
{

    wat_file(".");


    return 0; 
} 
```

