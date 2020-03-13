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
