#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <error.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>

int main()
{
  FILE *getpid;
  char line[100];
  pid_t killpid;

  getpid = fopen("/home/Penunggu/modul2/sid", "r");
  while(fgets(line, sizeof(line), getpid))
  {
    strcpy(killpid, line);
    kill(killpid, SIGKILL);
    printf("kill %d\n", killpid);
  }

  return 0;
}
