#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

// daemon

int main ()

{

  struct stat dastat;

  stat("makan_enak.txt",&dastat);

  time_t filetime;
  filetime = dastat.st_atime;
  // printf("stat: %s", ctime(&dastat.st_atime));

   // =========================

   time_t wattime;
   wattime = time(NULL);
   double tik = difftime(wattime, filetime);
   printf("%f\n", tik);
   // if ( <= 30) {

   // timestr = ctime(&wattime);

   // printf("now: %s", timestr);

   // int len = strlen(ctime(&wattime));
   // char now[len];
   // char stat_is[len];
   int i;

   // for(i=0; i<len; i++)
   // {
   //   now[i] = '\0';
   //   stat_is[i] = '\0';
   // }
   // printf("-- len %d\n", len);
   // strcpy(stat_is, ctime(&dastat.st_atime));
   //
   // strcpy(now, ctime(&wattime));
 //
 //   if(strcmp(now, stat_is) != 0)
 //   {
 //
 //     char space[] = " ";
 //     printf("hehe\n");
 //
 //
 //     char nama[3];
 //    sprintf(nama,"%d",namafile);
 //    struct stat statFile;
 //    stat (pathFile, &statFile);
 //    time_t timeis = statFile.st_atime;
 //
 //    //mengecek waktu terakhir file dibuka
 //    if (difftime(time(NULL), timeis) <= 30) {
	// //membuat file diet
 //
	// char pathHasil[]="/home/bryan/Documents/makanan/makan_sehat";
	// strcat(pathHasil, nama);
	// strcat(pathHasil, ".txt");
 //
	// FILE *hasil = fopen(pathHasil, "w");
	// fclose(hasil);
	// namafile++;
	// }
 // }


  return 0;

}
