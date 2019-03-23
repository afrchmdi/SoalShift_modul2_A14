#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

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
  // close(STDOUT_FILENO);
  close(STDERR_FILENO);

  int i = 1;

  while(1) {
    struct stat dastat;
    char nama[] = "/home/Penunggu/Documents/makanan";
    char tothis[200];
    char wat[] = "makan_sehat";
    char end[4] = ".txt";


    stat("/home/Penunggu/Documents/makanan/makan_enak.txt",&dastat);
    time_t filetime;
    filetime = dastat.st_atime;

     time_t wattime;
     wattime = time(NULL);
     double tik = difftime(wattime, filetime);
     printf("diff %f\n", tik);

     if (tik <= 30)
     {
       int j;
       for (j=0; j<strlen(tothis); j++)
       {
         tothis[j] = '\0';
       }
       snprintf(tothis, sizeof(tothis), "%s/%s%d.txt", nama, wat, i);
       // strcpy(tothis, nama);
       // strcat(tothis, "/");
       // strcat(tothis, wat);
       // strcat(tothis, i);
       // strcat(tothis, ".txt");
       // printf("tothis %s\n", tothis);
       i++;
       FILE *fh;
       fh=fopen(tothis,"w");
     }


    sleep(5);
  }

  exit(EXIT_SUCCESS);
}
