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
#include <pwd.h>
#include <grp.h>

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

    char *dimana="/home/Penunggu/modul2/hatiku";

    char *findher="elen.ku";
    struct dirent *dirr;
    DIR *dir = opendir(dimana);

    int i;

    char here[1024];
    char siapa_u[1024];
    char siapa_g[1024];

    struct stat this;
    struct passwd *who_u;
    struct group *who_g;

    if (!dir)
    {
      // printf("???\n");
      return 0;
    }

    while ((dirr = readdir(dir)) != NULL)
    {

      if (strcmp(dirr->d_name, ".") != 0 || strcmp(dirr->d_name, "..") != 0 && dirr->d_type != DT_DIR)
      {
        int len=strlen(dirr->d_name);
        char apa1[len+1];

        for (i=0; i<len+1; i++)
        {
            apa1[i] = '\0';
        }

        strcpy(apa1, dirr->d_name);

        // printf("find %s\n", findher);
          if (strcmp(apa1, findher) != 0)
          {

            for (i=0; i<strlen(here); i++)
            {
                here[i] = '\0';
            }
            snprintf(here, sizeof(here), "%s/%s", dimana, findher);
            // strcat(dimana, "/");
            // strcat(dimana, findher);

            if(!stat(here, &this))
            {
              who_u = getpwuid(this.st_uid);
              // printf("%s -- ", who_u->pw_name);
              who_g = getgrgid(this.st_gid);
              // printf("%s\n", who_g->gr_name);
              for (i=0; i<len+1; i++)
              {
                  siapa_u[i] = '\0';
                  siapa_g[i] = '\0';
              }
              strcpy(siapa_u, who_u->pw_name);
              strcpy(siapa_g, who_g->gr_name);
              if(strcmp(siapa_u, "www-data") == 0 && strcmp(siapa_g, "www-data") == 0)
              {
                // printf("here %s\n", here);

                if (chmod(here, 0777))
                {
                    // printf("hm:(\n");
                }
                else
                {
                  // printf("here %s\n", here);
                  if(remove(here) != 0)
                  {
                    // printf("maaf gagal :(\n");
                  }
                  else
                  {
                    // printf("you sure? | undo\n");
                  }
                }
              }
              else
              {
                // printf("permission denied\n");
              }
            }
            // printf("g.\n");
          }
      }
      // printf("lewat\n");
    }


    sleep(3);
  }

  exit(EXIT_SUCCESS);
}
