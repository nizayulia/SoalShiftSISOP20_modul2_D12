
Yulia Niza      - 05111840000043

M. Samsu Dhuha  - 05111840000155

Kelompok D12

## Soal 1
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan ketentuan sebagai berikut:

a. Program menerima 4 argumen berupa:

i. Detik: 0-59 atau * (any value)

ii. Menit: 0-59 atau * (any value)

iii. Jam: 0-23 atau * (any value)

iv. Path file .sh

b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai

c. Program hanya menerima 1 config cron

d. Program berjalan di background (daemon)

e. Tidak boleh menggunakan fungsi system()

Contoh: ./program \* 34 7 /home/somi/test.sh

Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap detik pada jam 07:34.

### Jawaban :
```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

int main(int argc, char** argv)
{
    int detik = atoi(argv[1]), menit = atoi(argv[2]), jam = atoi(argv[3]);
    int cek1 = 0, cek2 = 0, cek3 = 0, cek4 = 0, length;
    char bintang[] = "*";
    if (argc == 5) {
        // cek argumen 1
        if (strcmp (argv[1],bintang) == 0) {
            cek1 = 1;
        } if (isalpha(*argv[1]) != 0) {
            detik = -1;
        } else if (isdigit(*argv[1]) != 0) {
            detik = detik;
        }
        // cek argumen 2
        if (strcmp (argv[2],bintang) == 0) {
            cek2 = 1;
        } if (isalpha(*argv[2]) != 0) {
            menit = -1;
        } else if (isdigit(*argv[2]) != 0) {
            menit = menit;
        }
        // cek argumen 3
        if (strcmp (argv[3],bintang) == 0) {
            cek3 = 1;
        } if (isalpha(*argv[3]) != 0) {
            jam = -1;
        } else if (isdigit(*argv[3]) != 0) {
            jam = jam;
        }
        // cek argumen 4
        length = strlen(argv[4]);
        if (isalpha(*argv[4]) == 0) {
            jam = -1;
        } else if (argv[4][length-1] == 'h' && argv[4][length-2] == 's' && argv[4][length-3] == '.') {
            cek4 = 1;
        } else {
            printf("Argumen Tidak Valid\n");
            exit(EXIT_FAILURE);
        }
        // cek argumen sesuai yang diminta
        if ((detik > 59 || detik < 0) && cek1 == 0) {
            printf("Argumen Tidak Valid\n");
            exit(EXIT_FAILURE);
        } else if ((menit > 59 || menit < 0) && cek2 == 0) {
            printf("Argumen Tidak Valid\n");
            exit(EXIT_FAILURE);
        } else if ((jam > 23 || jam < 0) && cek3 == 0) {
            printf("Argumen Tidak Valid\n");
            exit(EXIT_FAILURE);
        }
        // copas contoh daemon di github waktu seslab
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
        while (1) {
            // manggil struct di library "time.h" dengan fungsi localtime()
            // referensi https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm
            time_t rawtime;
            struct tm *info;
            time( &rawtime );
            info = localtime( &rawtime );

            // sesuaiin localtime dengan inputan
            if ((info->tm_sec == detik || cek1 == 1) && (info->tm_min == menit || cek2 == 1)
                && (info->tm_hour == jam || cek3 == 1)){

                pid_t child_id;
                int status;

                child_id = fork();

                if (child_id < 0) {
                    exit(EXIT_FAILURE);
                }
                if (child_id == 0) {
                    char *exe[] = {"bash", argv[4], NULL};
                    execv("/bin/bash", exe);
                } else {
                    // this is parent
                    while ((wait(&status)) > 0);
                }
                sleep(1);
            }
        }
    } else {
        printf("Argumen Tidak Valid\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
```

### Penjelasan :

```
int detik = atoi(argv[1]), menit = atoi(argv[2]), jam = atoi(argv[3]);
    int cek1 = 0, cek2 = 0, cek3 = 0, cek4 = 0, length;
    char bintang[] = "*";
    if (argc == 5) {
        // cek argumen 1
        if (strcmp (argv[1],bintang) == 0) {
            cek1 = 1;
        } if (isalpha(*argv[1]) != 0) {
            detik = -1;
        } else if (isdigit(*argv[1]) != 0) {
            detik = detik;
        }
        // cek argumen 2
        if (strcmp (argv[2],bintang) == 0) {
            cek2 = 1;
        } if (isalpha(*argv[2]) != 0) {
            menit = -1;
        } else if (isdigit(*argv[2]) != 0) {
            menit = menit;
        }
        // cek argumen 3
        if (strcmp (argv[3],bintang) == 0) {
            cek3 = 1;
        } if (isalpha(*argv[3]) != 0) {
            jam = -1;
        } else if (isdigit(*argv[3]) != 0) {
            jam = jam;
        }
        // cek argumen 4
        length = strlen(argv[4]);
        if (isalpha(*argv[4]) == 0) {
            jam = -1;
        } else if (argv[4][length-1] == 'h' && argv[4][length-2] == 's' && argv[4][length-3] == '.') {
            cek4 = 1;
        } else {
            printf("Argumen Tidak Valid\n");
            exit(EXIT_FAILURE);
        }
        // cek argumen sesuai yang diminta
        if ((detik > 59 || detik < 0) && cek1 == 0) {
            printf("Argumen Tidak Valid\n");
            exit(EXIT_FAILURE);
        } else if ((menit > 59 || menit < 0) && cek2 == 0) {
            printf("Argumen Tidak Valid\n");
            exit(EXIT_FAILURE);
        } else if ((jam > 23 || jam < 0) && cek3 == 0) {
            printf("Argumen Tidak Valid\n");
            exit(EXIT_FAILURE);
        }
 ```
 
 - Cek argumen sesuai yang diminta
 
 ```
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
while (1) {
    // manggil struct di library "time.h" dengan fungsi localtime()
    // referensi https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm
    time_t rawtime;
    struct tm *info;
    time( &rawtime );
    info = localtime( &rawtime );

    // sesuaiin localtime dengan inputan
    if ((info->tm_sec == detik || cek1 == 1) && (info->tm_min == menit || cek2 == 1)
        && (info->tm_hour == jam || cek3 == 1)){

        pid_t child_id;
        int status;

        child_id = fork();

        if (child_id < 0) {
            exit(EXIT_FAILURE);
        }
        if (child_id == 0) {
            char *exe[] = {"bash", argv[4], NULL};
            execv("/bin/bash", exe);
        } else {
            // this is parent
            while ((wait(&status)) > 0);
        }
        sleep(1);
    }
```

- menjalankan dengan daemon

```
while (1) {
    // manggil struct di library "time.h" dengan fungsi localtime()
    // referensi https://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm
    time_t rawtime;
    struct tm *info;
    time( &rawtime );
    info = localtime( &rawtime );

    // sesuaiin localtime dengan inputan
    if ((info->tm_sec == detik || cek1 == 1) && (info->tm_min == menit || cek2 == 1)
        && (info->tm_hour == jam || cek3 == 1)){

        pid_t child_id;
        int status;

        child_id = fork();

        if (child_id < 0) {
            exit(EXIT_FAILURE);
        }
        if (child_id == 0) {
            char *exe[] = {"bash", argv[4], NULL};
            execv("/bin/bash", exe);
        } else {
            // this is parent
            while ((wait(&status)) > 0);
        }
        sleep(1);
    }
 ```
 
 - dengan membuat localtime yang berjalan tiap detik, jika localtime sesuai 
 dengan yang diminta maka akan perintah dijalankan

## Soal 2
Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia
merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat
sebuah program.

a. Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat
sebuah program C yang per 30 detik membuat sebuah folder dengan nama
timestamp [YYYY-mm-dd_HH:ii:ss].

b. Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari
https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap
gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah
detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-
mm-dd_HH:ii:ss].

c. Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan
folder akan di delete(sehingga hanya menyisakan .zip).

d. Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-
generate sebuah program "killer" yang siap di run(executable) untuk

menterminasi semua operasi program tersebut. Setelah di run, program yang
menterminasi ini lalu akan mendelete dirinya sendiri.
e. Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu
MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan
dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen
-b. Ketika dijalankan dalam MODE_A, program utama akan langsung
menghentikan semua operasinya ketika program killer dijalankan. Untuk
MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi
membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua
folder terisi gambar, terzip lalu di delete).

Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi.
Buatlah program dalam mimpi Kiwa jadi nyata!
Catatan:
- Tidak boleh memakai system().
- Program utama harus ter-detach dari terminal
Hint:
- Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran
tertentu
- Epoch Unix bisa didapatkan dari time()

### Jawaban :

### Penjelasan :
#### a. Membuat folder per 30 detik dengan nama timestamp [YYYY-mm-dd_HH:ii:ss].
```
while (1) 
  {
    child_a = fork();
    if (child_a < 0) 
    {
      exit(EXIT_FAILURE);
    }
    if (child_a == 0)
    { 
      time_t waktu = time(NULL);
      struct tm* now = localtime(&waktu);
      char newfolder[50];
      strftime(newfolder, sizeof(newfolder), "%Y-%m-%d_%H:%M:%S", now);

      child_b = fork ();
      if (child_b == 0)
      {
        char *mkd[] = {"mkdir", newfolder, NULL};
        execv("/bin/mkdir", mkd);
      }
```
Membuat nama file sesuai dengan timestamp [YYYY-mm-dd_HH:ii:ss] dengan menggunakan ```sturct tm* now = localtime(&waktu)``` untuk mengambil argument tipe data time_t waktu

Membuat child baru untuk menjalankan program untuk membuat folder menggunakan execv() dengan perintah ```mkdir``` 

Agar folder dapat terbuat setiap 30 detik, ada perintah sleep(30) pada akhir kodingan.


#### b. Mengisi folder dengan 20 gambar yang di download di https://picsum.photos/ dimana tiap gambar di download setiap 5 detik. Tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY- mm-dd_HH:ii:ss].
```
else 
      {
        while ((wait(&status)) > 0);
        for (i = 0; i < 20; i++)
        {
          child_c = fork();
          if (child_c == 0)
          {
            t = (int)time(NULL);
            t = (t % 1000) + 100;
            chdir(newfolder);
            time_t waktu_file = time(NULL);
            struct tm* file_now = localtime(&waktu_file);
        
            char isi[100];
            sprintf(isi, "https://picsum.photos/%d", t);

            char newfile[50];
            strftime(newfile, sizeof(newfile), "%Y-%m-%d_%H:%M:%S", file_now);
            char *mkfl[] = {"wget", isi, "-O", newfile, NULL};
            execv("/usr/bin/wget", mkfl);
          }
          sleep(5);
```
Menggunakan loop untuk mengiterasi sebanyak 20 kali gambar yang akan di download.

Membuat format nama file dengan timestamp [YYYY- mm-dd_HH:ii:ss].

mendownload gambar dari https://picsum.photos/ dengan ukuran (t % 1000 ) + 100 pixel, dimana t adalah Epoch Unix yang disimpan pada 'isi'.

Menggunakan perintah wget -O untuk mendownload gambar dari 'isi' dan menyimpan di file 'newfile' dengan format nama sesuai timestamp yang telah dibuat.

Agar file dapat terbuat setiap 5 detik, digunakan perintah 'sleep(5)'

#### c. folder akan di zip dan folder akan di delete(sehingga hanya menyisakan .zip)
```
}
        while ((wait(&status)) > 0);
        char dizip[100];
        sprintf(dizip, "%s.zip", newfolder);
        char *zip[] = {"zip", "-rm", dizip, newfolder, NULL};
        execv("/usr/bin/zip", zip);
```
Menggunakan perintah snprintf() memformat dan menyimpan nama dari zip ke array dizip
Melakukan perintah zip folder yang sudah terisi 20 file dan meremove folder tersebut dengan execv()


 
## Soal 3
Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia
memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan
(multiprocessing).
a. Program buatan jaya harus bisa membuat dua direktori di
“/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu
lima detik kemudian membuat direktori yang kedua bernama “sedaap”.
b. Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori
“/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak
hanya itu tugasnya.
c. Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di
dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan
pengelompokan, semua file harus dipindahkan ke
“/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke
“/home/[USER]/modul2/indomie/”.
d. Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/”
harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu
3 detik kemudian membuat file bernama “coba2.txt”.
(contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).
Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat
program tersebut.
Catatan :
- Tidak boleh memakai system().
- Tidak boleh memakai function C mkdir() ataupun rename().
- Gunakan exec dan fork
- Direktori “.” dan “..” tidak termasuk

### Jawaban 
``` 
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>


int main() {
  pid_t child_a, child_b, child_c, child_d, child_e, child_f, child_g;
  int status;
  child_a = fork();
  if (child_a < 0) 
  {
    exit(EXIT_FAILURE); 
  }
  
  if (child_a == 0) 
  {
    char *mkd[] = {"mkdir", "/home/yulia/modul2/indomie", NULL};
    execv("/bin/mkdir", mkd);
  } 
  else 
  {
    child_b = fork();
    if (child_b < 0) 
    {
      exit(EXIT_FAILURE); 
    }
    if (child_b == 0)
   	{	
      while ((wait(&status)) > 0);
      sleep(5);
      char *argv[] = {"mkdir","/home/yulia/modul2/sedaap", NULL};
      execv("/bin/mkdir", argv);
    }
    else 
    {
      while ((wait(&status)) > 0);
      child_c = fork();
      if (child_c < 0) 
      {
        exit(EXIT_FAILURE); 
      }
      if(child_c == 0) 
      {
        char *unzip[]={"unzip", "/home/yulia/modul2/jpg.zip", NULL};
     	  execv("/usr/bin/unzip",unzip);
      }	  
      else 
      {
        while ((wait(&status)) > 0);
        DIR *d;
        struct dirent *dir; 
        d = opendir("jpg");
        if (d)
        {
          while ((dir = readdir(d)) != NULL)
          {
            child_d = fork ();
            if (child_d < 0) 
            {
              exit(EXIT_FAILURE); 
            }
            if (child_d == 0)
            {
              struct stat info;
              char namafile[1000];
              sprintf(namafile, "/home/yulia/modul2/jpg/%s", dir->d_name);
              if (stat(namafile, &info)) 
              {
                exit (EXIT_FAILURE);
              }
              if (strcmp(dir->d_name, "..") == 0 || strcmp(dir->d_name, ".") == 0);
              else if(dir->d_type == DT_REG)
              {
                char* move[] = {"mv", namafile, "/home/yulia/modul2/sedaap/", NULL};
                execv("/bin/mv", move);
              }
              else 
              {
                child_e = fork ();
                if (child_e < 0) 
                {
                  exit(EXIT_FAILURE); 
                }
                if(child_e == 0)
                {
                  char* move[] = {"mv", namafile, "/home/yulia/modul2/indomie/", NULL};
                  execv("/bin/mv", move);
                }
                else 
                {
                  while ((wait(&status)) > 0);
                  child_f = fork ();
                  if (child_f < 0) 
                  {
                    exit(EXIT_FAILURE); 
                  }
                  if(child_f == 0)
                  {
                    char pilihfolder[10000];
                    sprintf(pilihfolder, "/home/yulia/modul2/indomie/%s/coba1.txt", dir->d_name);
                    char* file1[] = {"touch", pilihfolder, NULL};
                    execv("/usr/bin/touch", file1);
                    
                  }
                  else 
                  {
                    while ((wait(&status)) > 0);
                    sleep(3);
                    char pilihfolder[10000];
                    sprintf(pilihfolder, "/home/yulia/modul2/indomie/%s/coba2.txt", dir->d_name);
                    char* file2[] = {"touch", pilihfolder, NULL};
                    execv("/usr/bin/touch", file2);
                  }
                }
              }
            }
          }
          closedir(d);
        }
      }
    }
  }
}


```
### Penjelasan :

#### a. Membuat direktori indomie, lalu 5 detik kemudian membuat direktori Sedaap
```
int main() {
  pid_t child_a, child_b, child_c, child_d, child_e, child_f;
  int status;
  if (child_a < 0) 
  {
    exit(EXIT_FAILURE); 
  }

  if (child_a == 0) 
  {
    char *mkd[] = {"mkdir", "/home/yulia/modul2/indomie", NULL};
    execv("/bin/mkdir", mkd);
  } 
```
Menginisiasi pid yang akan digunakan dan int status. Jika ```child_a < 0``` maka  gagal membuat proses baru, program akan berhenti. Child membuat directory baru dengan nama indomie.
```
else 
  {
    child_b = fork();
    if (child_b < 0) 
    {
      exit(EXIT_FAILURE); 
    }
    if (child_b == 0)
   	{	
      while ((wait(&status)) > 0);
      sleep(5);
      char *argv[] = {"mkdir","/home/yulia/modul2/sedaap", NULL};
      execv("/bin/mkdir", argv);
    }
    
  ```
 Membuat fork untuk melakukan proses baru yaitu membuat directory dengan nama 'sedaap' yang berjalan setelah 5 detik dari proses sebelumnya yang dibuat dengan menggunakan wait.
 
 
 
 #### b. Meng-ekstrak file jpg.zip di direktori “/home/yulia/modul2/”

```
 else 
    {
      while ((wait(&status)) > 0);
      child_c = fork();
      if (child_c < 0) 
      {
        exit(EXIT_FAILURE); 
      }
      if(child_c == 0) 
      {
        char *unzip[]={"unzip", "/home/yulia/modul2/jpg.zip", NULL};
     	  execv("/usr/bin/unzip",unzip);
      }	  
```
Membuat fork untuk melakukan proses baru yaitu meng-ekstrak file jpg.zip di direktori “/home/yulia/modul2/”.


#### c. hasil dari ekstrakan tersebut dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke “/home/yulia/modul2/sedaap/” dan semua direktori harus dipindahkan ke “/home/yulia/modul2/indomie/”

```
   else 
      {
        while ((wait(&status)) > 0);
        DIR *d;
        struct dirent *dir; 
        d = opendir("jpg");
        if (d)
        {
          while ((dir = readdir(d)) != NULL)
          {
            child_d = fork ();
            if (child_d < 0) 
            {
              exit(EXIT_FAILURE); 
            }
            if (child_d == 0)
            {
              struct stat info;
              char namafile[1000];
              sprintf(namafile, "/home/yulia/modul2/jpg/%s", dir->d_name);
              if (stat(namafile, &info)) 
              {
                exit (EXIT_FAILURE);
              }
              if (strcmp(dir->d_name, "..") == 0 || strcmp(dir->d_name, ".") == 0);
              else if(dir->d_type == DT_REG)
              {
                char* move[] = {"mv", namafile, "/home/yulia/modul2/sedaap/", NULL};
                execv("/bin/mv", move);
              }
```
Untuk mengetahui format isi dari sebuah direktori, kita menggunakan DIR. Lalu membuka dan membaca file dalam folder "jpg" selama folder tidak kosong. Membuat fork baru untuk melakukan proses pemindahan file dari "/home/yulia/modul2/jpg” ke "/home/yulia/modul2/sedaap”. 


```
else 
              {
                child_e = fork ();
                if (child_e < 0) 
                {
                  exit(EXIT_FAILURE); 
                }
                if(child_e == 0)
                {
                  char* move[] = {"mv", namafile, "/home/yulia/modul2/indomie/", NULL};
                  execv("/bin/mv", move);
                }
```
Membuat fork baru untuk melakukan proses pemindahan folder dari "/home/yulia/modul2/jpg” ke "/home/yulia/modul2/indomie”.


#### d. Membuat dua file kosong pada setiap folder yang berada dalam "/home/yulia/modul2/indomie” dengan nama coba1.txt dan coba2.txt yang terbuat 3 detik setelahnya.

```
else 
                {
                  while ((wait(&status)) > 0);
                  child_f = fork ();
                  if (child_f < 0) 
                  {
                    exit(EXIT_FAILURE); 
                  }
                  if(child_f == 0)
                  {
                    char pilihfolder[10000];
                    sprintf(pilihfolder, "/home/yulia/modul2/indomie/%s/coba1.txt", dir->d_name);
                    char* file1[] = {"touch", pilihfolder, NULL};
                    execv("/usr/bin/touch", file1);
                    
                  }
                  else 
                  {
                    while ((wait(&status)) > 0);
                    sleep(3);
                    char pilihfolder[10000];
                    sprintf(pilihfolder, "/home/yulia/modul2/indomie/%s/coba2.txt", dir->d_name);
                    char* file2[] = {"touch", pilihfolder, NULL};
                    execv("/usr/bin/touch", file2);
```

Membuat fork baru untuk melakukan proses pembuatan file coba1.txt dan coba2.txt.   



Referensi : 
http://man7.org/linux/man-pages/man3/readdir.3.html
https://www.mahirkoding.com/operasi-file-dalam-bahasa-c/
https://stackoverflow.com/questions/26357792/return-a-list-of-files-in-a-folder-in-c


