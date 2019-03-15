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
#include <time.h>


int main()
{

    time_t y = time(NULL);
    struct tm tm = *localtime(&y);
    char here[100];
    snprintf(here, sizeof(here), "%d:%d:%d-%d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
            tm.tm_hour, tm.tm_min);

            // printf("%s\n", here);

    char *filename;
    if((filename = malloc(strlen("/home/Penunggu/")+strlen(here)+1)) != NULL){
        filename[0] = '\0';
        strcat(filename,"/home/Penunggu/");
        strcat(filename,here);
    }
    int this = mkdir(filename, 0700);


}
