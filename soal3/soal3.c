#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
// #include <fstream>
#include <sys/wait.h>

int main()
{
  pid_t satu;
  pid_t dua;
  pid_t tiga;

  int how;
  int da_pipe[2];

  char *do1[3] = {"unzip", "campur2.zip", NULL};
  char *do2[3] = {"ls, campur2", NULL};
  char *do3[3] = {"grep", ".txt$", NULL};

  if(pipe(da_pipe) == -1)
  {
    perror("pipe");
  }

  satu = fork();

  if(satu == 0)
  {
    execv("/usr/bin/unzip", do1);

  }
    while((waitpid(satu, &how, 0)) > 0);

    dua = fork();

    if(dua == 0)
    {
      // close(da_pipe[1]);

      close(da_pipe[0]);
      // dup2(da_pipe[1], STDOUT_FILENO);
      dup2(da_pipe[1], STDOUT_FILENO);
      execv("/bin/ls", do2);

    }
    else
    {
      while((waitpid(dua, &how, 0)) > 0);
      tiga = fork();

      if(tiga == 0)
      {
        // dup2(da_pipe[0], STDIN_FILENO);

        int file = open("daftar.txt", O_WRONLY|O_CREAT, 0777);
        close(da_pipe[0]);
        // redir((char*)"./daftar.txt");
        dup2(file, STDOUT_FILENO);
        execv("bin/grep", do3);

        close(file);
      }

      close(da_pipe[0]);
      close(da_pipe[1]);

      while((waitpid(tiga, &how, 0)) > 0);


    }

}
