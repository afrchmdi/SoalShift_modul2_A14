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
  int pid_is;
  pid = fork();

  pid_is = getpid();
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
  int j;
  int sid_is;
  // sid_=getsid(0);
  char buf[6];
  for(j=0; j<strlen(buf); j++)
  {
    buf[j] = '\0';
  }
  // sprintf(buf, "%d", getsid(0));
  sid_is = getsid(0);

  FILE *this;
  this = fopen("/home/Penunggu/modul2/sid", "w");
  fprintf(this, "%d\n%d\n", sid_is, pid_is);
  fclose(this);

  while(1) {
    time_t y = time(NULL);
    struct tm tm = *localtime(&y);
    char here[100];
    snprintf(here, sizeof(here), "%d:%d:%d-%d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
            tm.tm_hour, tm.tm_min);

            // printf("%s\n", here);

    char *filename;
    if((filename = malloc(strlen("/home/Penunggu/")+strlen(here)+1)) != NULL){
        filename[0] = '\0';
        strcat(filename,"/home/Penunggu/log");
        strcat(filename,here);
    }

    printf("here %s\n", filename);
    // mkdir(filename, 0700);
    // chdir(filename);

    int j;
    for (j=0; j<30; j++)
    {
      FILE *f1;
      FILE *f2;
      char da_log[] = "/var/log/syslog";
      // f1=fopen(da_log);
      char nameit[1024];

      int k;
      for (k=0; k<strlen(nameit); k++)
      {
        nameit[k] = '\0';
      }

      snprintf(nameit, sizeof(nameit), "%s/log%d.log", filename, i);
      printf("this? %s\n", nameit);
      i++;
    }




    sleep(1800);
  }

  exit(EXIT_SUCCESS);
}
