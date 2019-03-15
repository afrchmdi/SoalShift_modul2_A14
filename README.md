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

Karena program C ini diminta dapat mengubah nama secara otomatis, maka dilakukan pengaplikasian daemon pada program.
Isi dari program C:

```sh
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
            // printf("%*s[%s]\n", indent, "", dirr->d_name);
            //printf("[%s]\n", dirr->d_name);
            //printf("from: %s\n", path);
            // listdir(path, indent + 2);
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


```

Program untuk merename file berekstensi png dimulai dari loop while(1) dalam fungsi main. Untuk merename nama file dan memindahkannya ke folder `/home/[User]/modul2/gambar` berada pada fungsi *wat_file* 

Pemanggilan fungsi dilakukan dengan memberikan parameter nama folder yang akan dieksekusi. Dalam program saya, folder yang di *passingkan* adalah folder */home/Penunggu/modul2*

`while(1) {

    wat_list("/home/Penunggu/modul2");

    sleep(20);
  }`
  
  Dalam fungsi *wat_file*, akan di list file-file dan direktori yang ada pada */home/Penunggu/modul2*. Lalu dari hasil list file yang didapat, dicari file yang berekstensi png
  
  ```sh 
  char *ext=strrchr(apa1, '.');
  char *exx=strrchr(apa1, '_');

  if (strcmp(ext, ".png") == 0)
  {
    //check jika file berakhiran _grey.png
    if(!strcmp(exx, "_grey.png"))
    {
      //direname dengan path yang ditentukan, /home/Penunggu/modul2/gambar/nama_file
    }
    else
    {
      //rename sehingga file berakhiran '_grey.png'
      strncpy(nameit, apa1, len-4);
      strcat(nameit, "_grey.png");
      snprintf(posisi, sizeof(posisi), "/home/Penunggu/modul2/gambar/%s", nameit);
      
      rename(no, posisi);
    }
    
  }
  
  //snippet 
  ```
  FIle yang berekstensi png di cek apakah berakhiran *_grey.png* atau tidak. Jika iya, maka file akan dipindah ke folder modul2/gambar. Jika tidak, file akan direname sesuai dengan ketentuan soal.
  

### 2. Soal 2
##### Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
##### Catatan: Tidak boleh menggunakan crontab

```sh
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

  if ((chdir("/home/Penunggu/modul2")) < 0) {
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

                if (chmod(here, 777))
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

```

Karena program harus berjalan secara otomatis tiap 3 detik, maka dilakukan pengaplikasian daemon.
Pertama-tama, dilakukan pencarian file dengan nama *elen.ku* pada folder */home/Penunggu/modul2/hatiku*. Untuk mendapatkan file yang dicari, cara yang digunakan kurang lebih sama seperti pencarian pada soal no 1.
Lalu file yang didapat di cek apakah owner dan grup dari file adalah *www-data*.

```sh
    who_u = getpwuid(this.st_uid);
    who_g = getgrgid(this.st_gid);

```
Jika owner dan grup file *elen.ku* adalah *www-data* maka file kenangan harus dihapus. Karena permission file tidak memungkinkan untuk secara otomatis menghapus file tersebut, maka perlu dilakukan `chmod`.

```sh
chmod(here, 777)
remove(here)

```

`sleep(30)` agar file program berjalan tiap 3 detik


### 3. Soal 3
##### Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
##### Buatlah program C yang dapat :
##### i)  mengekstrak file zip tersebut.
##### ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
##### Catatan:  
##### Gunakan fork dan exec.
##### Gunakan minimal 3 proses yang diakhiri dengan exec.
##### Gunakan pipe
##### Pastikan file daftar.txt dapat diakses dari text editor


```sh
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


```

File 


### 4. Soal 4
##### Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
##### Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

##### Contoh:
##### File makan_enak.txt terakhir dibuka pada detik ke-1
##### Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

##### Catatan: 
##### dilarang menggunakan crontab
##### Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst

File 

```sh
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

// daemon

int main ()

{

  struct stat dastat;

  stat("makan_enak.txt",&dastat);
  printf("stat: %s", ctime(&dastat.st_atime));

   // =========================

   time_t wattime;
   char* timestr;

   wattime = time(NULL);

   timestr = ctime(&wattime);

   printf("now: %s", timestr);

   int len = strlen(ctime(&wattime));
   char now[len];
   char stat_is[len];
   int i;

   for(i=0; i<len; i++)
   {
     now[i] = '\0';
     stat_is[i] = '\0';
   }
   // printf("-- len %d\n", len);
   strcpy(stat_is, ctime(&dastat.st_atime));

   strcpy(now, ctime(&wattime));

  return 0;

}

```

### 5. Soal 5
##### Kerjakan poin a dan b di bawah:
##### Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
##### Ket:
##### Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
##### Per menit memasukkan log#.log ke dalam folder tersebut
##### ‘#’ : increment per menit. Mulai dari 1
##### Buatlah program c untuk menghentikan program di atas.
##### NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

Sementara ini progres saya baru membuat folder dengan nama *[dd:MM:yyyy-hh:mm]*

```sh
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

    
    sleep(30);
  }
  
  exit(EXIT_SUCCESS);
}




```
