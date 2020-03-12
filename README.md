# SoalShiftSISOP20_modul2_D12


Yulia Niza      - 05111840000043
M. Samsu Dhuha  - 05111840000155

Kelompok D12

## Soal 1
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut:
a. Program menerima 4 argumen berupa:
i. Detik: 0-59 atau * (any value)
ii. Menit: 0-59 atau * (any value)
iii. Jam: 0-23 atau * (any value)
iv. Path file .sh
b. Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai
c. Program hanya menerima 1 config cron
d. Program berjalan di background (daemon)
e. Tidak boleh menggunakan fungsi system()
Contoh: ./program \* 34 7 /home/somi/test.sh
Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap
detik pada jam 07:34.
### Jawaban :

### Penjelasan :

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
  pid_t child_a, child_b, child_c, child_d, child_e, child_f;
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
              char namafile[1000];
              sprintf(namafile, "/home/yulia/modul2/jpg/%s", dir->d_name);
              if (strcmp(dir->d_name, "..") == 0 || strcmp(dir->d_name, ".") == 0);
              else if(dir->d_type == DT_REG)
              {
                char* move[] = {"mv", namafile, "/home/yulia/modul2/sedaap/", NULL};
                execv("/bin/mv", move);
              }
              else if (dir->d_type == DT_DIR)
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
                    FILE *tujuan;
                    tujuan = fopen(pilihfolder, "w");
                    fclose(tujuan);
                    
                  }
                  else 
                  {
                    while ((wait(&status)) > 0);
                    sleep(3);
                    char pilihfolder[10000];
                    sprintf(pilihfolder, "/home/yulia/modul2/indomie/%s/coba2.txt", dir->d_name);
                    FILE *tujuan;
                    tujuan = fopen(pilihfolder, "w");
                    fclose(tujuan);
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
