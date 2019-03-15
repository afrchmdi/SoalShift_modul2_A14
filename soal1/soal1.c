#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

void wat_list(char *dari);

int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  while(1) {

    wat_list("/home/Penunggu/modul2");

    sleep(20);
  }

  exit(EXIT_SUCCESS);
}

void wat_list(char *dari)
{
    struct dirent *dirr;
    DIR *dir = opendir(dari);
    int i;
    char where[]="/home/Penunggu/modul2/gambar/";

    if (!dir)
        return;
        //printf("before while");
    while ((dirr = readdir(dir)) != NULL)
    {
        if (dirr->d_type == DT_DIR) {

            char path[1024];

            //printf("hehe\n");
            for (i=0; i<strlen(path); i++)
            {
                path[i] = '\0';
            }


            if (strcmp(dirr->d_name, ".") == 0 || strcmp(dirr->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", dari, dirr->d_name);
            wat_list(path);
        }
        else
        {
            int len=strlen(dirr->d_name);
            char apa1[len+1];

            for (i=0; i<len+1; i++)
            {
                apa1[i] = '\0';
            }

            strcpy(apa1, dirr->d_name);

            char *ext=strrchr(apa1, '.');
            char *exx=strrchr(apa1, '_');
            int flag=0;

            if (ext)
            {
              //printf("apa? %s\n", ext);
              if (strcmp(ext, ".png") == 0)
              {
                if (exx){
                  //printf("apaa? %s\n", exx);
                  if(!strcmp(exx, "_grey.png"))
                  {
                    //printf("this is NOT the file you re lookin for\n");
                    //printf("not file : %s\n", dirr->d_name);

                    char gimana[1024];
                    char dimana[1024];
                    for (i=0; i<strlen(gimana); i++)
                    {
                        gimana[i] = '\0';
                        dimana[i] = '\0';
                    }
                    strcpy(gimana, dirr->d_name);
                    snprintf(dimana, sizeof(dimana), "/home/Penunggu/modul2/gambar/%s", gimana);
                    //printf("%s\n", dimana);
                    if (rename(gimana, dimana) != 0)
                    {
                      //printf("gabisa :(\n");
                    }
                    flag=1;
                  }

                }
                if (flag==0)
                {
                  //printf("this IS the file you're lookin for!\n");
                  //printf("file is : %s\n", dirr->d_name);


                  //===============================================
                  // printf("%d\n", len);
                  char nameit[len+6];

                  for (i=0; i<len+1; i++)
                  {
                      nameit[i] = '\0';
                  }
                  strncpy(nameit, apa1, len-4);
                  strcat(nameit, "_grey.png");

                  // printf("should be: %s\n", nameit);
                  char posisi[1024];
                  char no[1024];
                  for (i=0; i<strlen(posisi); i++)
                  {
                      posisi[i] = '\0';
                      no[i] = '\0';
                  }
                  snprintf(posisi, sizeof(posisi), "/home/Penunggu/modul2/gambar/%s", nameit);
                  //printf("where?? %s\n", posisi);
                  strcpy(no, dirr->d_name);
                  if(rename(no, posisi) == 0)
                  {
                    //printf(":)\n");
                  }
                  else
                  {
                    //printf("gagal:(\n");
                    for (i=0; i<strlen(posisi); i++)
                    {
                        no[i] = '\0';
                    }
                    strcpy(no, dirr->d_name);
                    rename(no, posisi);
                  }

                }
              }

            }

    }
  //  printf("dir or not dir that is the question\n");

  }
  //printf("============\n");
  closedir(dir);
}
