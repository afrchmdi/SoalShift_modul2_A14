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
  
--tambahan--

`while ((dirr = readdir(dir)) != NULL){ //code }`
berarti  *//code* yang ada dalam while loop akan dieksekusi selama dalam direktori *dir* masih ada file/subfolder yang dicek (isinya tidak NULL).

```sh
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
```
Apabila dirr bertipe direktori maka akan dilakukan rekursi pada subfolder dengan memasukkan kembali nama folder tersebut ke dalam fungsi *wat_list*.

selain dirr yang bertipe folder, maka akan dicek dalam `else`.

```sh
char *ext=strrchr(apa1, '.');
char *exx=strrchr(apa1, '_');
```
 strrchr(apa1, '.') akan memberikan sebuah pointer yang menunjuk pada '.' terakhir yang ada pada string apa1(dirr->d_name).
 sehingga apabila dir->d_name bernilai "ini.file.png" maka pointer ext akan menunjuk pada ".png"

`if (ext)` apabila dirr->d_name yang disimpan dalam variabel apa1 mengandung '.' maka

`if (strcmp(ext, ".png") == 0)` dilakukan pengecekan apakah file berekstensi ".png".

jika iya dilakukan pengecekan lagi apakah nama file mengandung "_"
`if (exx)`


```sh
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
```
`char *exx=strrchr(apa1, '_');`

variabel exx juga akan menunjukkan pointer dimana char '_' terakhir berada pada dirr->d_name apa1. 
apabila ketika apa1(dirr->d_name) dicompare dengan "_grey.png", maka file tidak perlu diubah namanya, hanya perlu dipindah ke folder gambar.
pemindahan file dilakukan dengan merename file dengan penambahan path. file yang berekstensi "_grey.png" akan diberi flag =1.

`if (flag==0)` berarti file tidak berekstensi "_grey.png" dan perlu untuk diubah.

```sh
strncpy(nameit, apa1, len-4);
strcat(nameit, "_grey.png");
```
nilai dirr->d_name yang disimpan dalam variabel apa1 dicopy ke variabel nameit hanya sampai sebelum ".png" (len-4).
lalu nameit di strcat dengan "_grey.png" sehingga sekarang nama file dirr->d_name yang salah sudah benar sesuai persyaratan soal.

  
----------------------------------
#### Revisi soal 1

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
                    snprintf(gimana, sizeof(gimana), "%s/%s", dari, apa1);
                    snprintf(dimana, sizeof(dimana), "%s/gambar/%s", apa1);
                    // printf("dari %s\n", gimana);
                    // printf("jadi %s\n", dimana);

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
                  snprintf(no, sizeof(no), "%s/%s", dari, dirr->d_name);
                  // strcpy(no, dirr->d_name);
                  // printf("file dari %s\n", no);
                  // printf("file jadi %s\n", posisi);
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

Revisi yang dilakukan adalah penambahan full path untuk file yang direname serta direktori yang akan direkursi ke fungsi wat_list untuk di list dan dicek.

```sh
snprintf(gimana, sizeof(gimana), "%s/%s", dari, apa1);
snprintf(dimana, sizeof(dimana), "%s/gambar/%s", dari, apa1);
```
Pada bagian `if (dirr->d_type == DT_DIR)`, dimana subfolder yang ada pada folder yang sedang dicek (variabel *dari*, parameter dari fungsi *wat_list*) akan dilist dan dicek dengan dimasukkan lagi (rekursif) ke fungsi wat_list.

Variabel *gimana* yang sebelumnya hanya berupa nama folder, menjadi full path dari folder yang akan dicek.

Penambahan full path juga dilakukan pada

```sh
snprintf(no, sizeof(no), "%s/%s", dari, dirr->d_name);
```
Yang ada pada pagian `if (flag==0)` dimana `dirr->d_name` adalah file yang namanya perlu diubah karena belum berakhiran *_grey.png*, file direname dengan menggunakan full path juga.
Jika merename tanpa menggunakan full path, seperti kodingan sebelumnya, maka pe-rename an akan gagal.
  

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

`sleep(3)` agar file program berjalan tiap 3 detik

-- tambahan --

pada penjalanan daemon perlu dilakukan sudo agar chmod dapat berjalan.

`sudo ./'executable-file-name'`

chmod tidak akan berjalan karena ketika kita menjalankan bash, user yang tercatat menjalankan bukan www-data, dimana hanya www-data saja yang bisa melakukan chmod.

untuk mengubah owner dan grup dari file elen.ku juga dilakukan secara manual (tidak dalam program) dengan cara 

```sh
$ sudo chown www-data elen.ku
$ sudo chgrp www-data elen.ku
```


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

Parent dari proses diatas adalah ketika dilakukan fork yang pertama kali. Lalu child pertama dari parent melakukan unzip. Setelah wait, fork kedua menghasilkan child kedua yang melakukan ls folder campur2. setelah itu dilakukan fork satu kali lagi yang melakukan grep semua list file .txt yang ada. Lalu hasil grep tadi dimasukkan ke file daftar.txt


----------------------------------
#### Revisi soal 3
```sh
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main()
{
  pid_t satu;
  pid_t dua;
  pid_t tiga;

  int how;
  int da_pipe[2];
  int de_pipe[2];

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
    if (pipe(de_pipe) == -1)
    {
      perror("pipe");
    }
    while((waitpid(satu, &how, 0)) > 0);

    dua = fork();

    if(dua == 0)
    {
      dup2(da_pipe[1], STDOUT_FILENO);
      close(da_pipe[1]);
      close(da_pipe[0]);
      execv("/bin/ls", do2);

    }
    else
    {
      while((waitpid(dua, &how, 0)) > 0);
      tiga = fork();

      if(tiga == 0)
      {
        dup2(da_pipe[0], STDIN_FILENO);
        dup2(de_pipe[1], STDOUT_FILENO);
        close(da_pipe[0]);
        close(da_pipe[1]);
        close(de_pipe[0]);
        close(de_pipe[1]);
        execv("bin/grep", do3);

      }
      FILE *tmp;
      FILE *file;
      char wat[100024];

      close(da_pipe[0]);
      close(da_pipe[1]);
      close(de_pipe[1]);
      tmp = fdopen(de_pipe[0], "r");
      file = fopen("/home/Penunggu/SoalShift_modul2_A14/soal3/daftar.txt", "w");
      while(fgets(wat, sizeof(wat), tmp) != NULL)
      {
        fprintf(file, "%s", wat);
      }
      fclose(file);

    }

}

```
`pid_t satu, dua, tiga;`

untuk menyimpan process id dari tiga fork yang akan dilakukan.

```sh
int da_pipe[2];
int de_pipe[2];

if(pipe(da_pipe) == -1)
 {
   perror("pipe");
 }

if (pipe(de_pipe) == -1)
    {
      perror("pipe");
    }
    
```
inisialisasi dan pembuatan pipe da_pipe dan de_pipe yang masing-masing mempunyai WRITE-END dan READ-END.

```sh
satu = fork();
 
  if(satu == 0)
  {
    execv("/usr/bin/unzip", do1);
 
  }

```
dilakukan fork, dan pada child dari proses fork yang pertama (satu) dilakukan unzip file campur2.zip dengan menggunakan execv.

```sh
while((waitpid(satu, &how, 0)) > 0);
 
    dua = fork();
 
    if(dua == 0)
    {
      dup2(da_pipe[1], STDOUT_FILENO);
      close(da_pipe[1]);
      close(da_pipe[0]);
      execv("/bin/ls", do2);
 
    }
    
```
Pada parent proses satu, setelah menunggu proses unzip selesai, dilakukan fork yang kedua.
pada child proses fork yang kedua, dilakukan ls pada folder campur2 hasil unzip campur2.zip.

```sh
else
    {
      while((waitpid(dua, &how, 0)) > 0);
      tiga = fork();
 
      if(tiga == 0)
      {
        dup2(da_pipe[0], STDIN_FILENO);
        dup2(de_pipe[1], STDOUT_FILENO);
        close(da_pipe[0]);
        close(da_pipe[1]);
        close(de_pipe[0]);
        close(de_pipe[1]);
        execv("bin/grep", do3);
 
      }
      FILE *tmp;
      FILE *file;
      char wat[100024];
 
      close(da_pipe[0]);
      close(da_pipe[1]);
      close(de_pipe[1]);
      tmp = fdopen(de_pipe[0], "r");
      file = fopen("/home/Penunggu/SoalShift_modul2_A14/soal3/daftar.txt", "w");
      while(fgets(wat, sizeof(wat), tmp) != NULL)
      {
        fprintf(file, "%s", wat);
      }
      fclose(file);
 
    }
    
```
Lalu pada parent proses nya, setelah menunggu ls selesai dilakukan, dilakukan fork sekali lagi (tiga).
Dimana child proses dari fork tiga dilakukan grep hasil ls folder campur2 untuk nama file yang berakhiran ".txt".
Lalu pada parent prosesnya hasil dari grep tadi disimpan ke file */home/Penunggu/SoalShift_modul2_A14/soal3/daftar.txt*.

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


```

----------------------------------
#### Revisi soal 4
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
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  int i = 1;

  while(1) {
    struct stat dastat;
    char nama[] = "/home/Penunggu/Documents/makanan";
    char tothis[200];
    char wat[] = "makan_sehat";


    stat("/home/Penunggu/Documents/makanan/makan_enak.txt",&dastat);
    time_t filetime;
    filetime = dastat.st_atime;

     time_t wattime;
     wattime = time(NULL);
     double tik = difftime(wattime, filetime);
     //printf("diff %f\n", tik);

     if (tik <= 30)
     {
       int j;
       for (j=0; j<strlen(tothis); j++)
       {
         tothis[j] = '\0';
       }
       snprintf(tothis, sizeof(tothis), "%s/%s%d.txt", nama, wat, i);
       i++;
       FILE *fh;
       fh=fopen(tothis,"w");
     }


    sleep(5);
  }

  exit(EXIT_SUCCESS);
}

```

`stat("/home/Penunggu/Documents/makanan/makan_enak.txt",&dastat);`

da_stat adalah pointer pada struct stat yang berisi atribut file */home/Penunggu/Documents/makanan/makan_enak.txt*.

```sh
time_t filetime;
filetime = dastat.st_atime;
```
variabel _filetime_ sebagai variabel yang menyimpan waktu akses dari file makan_enak.txt. 

```sh
time_t wattime;
wattime = time(NULL);
```
variabel _wattime_ sebagai variabel yang menyimpan waktu sekarang.

```sh
double tik = difftime(wattime, filetime);
```
digunakan fungsi difftime() untuk mendapatkan selisih waktu dari waktu sekarang dengan waktu file akses.
Apabila selisih waktu akses dan waktu sekarang kurang dari atau sama dengan 30 detik, maka akan dibuat file makan_sehat#.txt.

```sh
if (tik <= 30)
     {
       int j;
       for (j=0; j<strlen(tothis); j++)
       {
         tothis[j] = '\0';
       }
       snprintf(tothis, sizeof(tothis), "%s/%s%d.txt", nama, wat, i);
       i++;
       FILE *fh;
       fh=fopen(tothis,"w");
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
