#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

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
    struct stat dastat;
    char *nama = "/home/Penunggu/Documents/makanan";
    char tothis[1000];
    char *wat = "makanan_enak";
    char end[4] = "txt";
    int i;

    snprintf(tothis, sizeof(tothis), "%s/%s", nama, wat);
    stat("makan_enak.txt",&dastat);
    int i;
    time_t filetime;
    filetime = dastat.st_atime;

     time_t wattime;
     wattime = time(NULL);
     double tik = difftime(wattime, filetime);
     printf("%f\n", tik);

     if (tik <= 30)
     {
       FILE *fh;
       fh=fopen(tothis,"w");
     }


    sleep(30);
  }

  exit(EXIT_SUCCESS);
}
