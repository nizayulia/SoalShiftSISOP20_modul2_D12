#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <wait.h>
#include <time.h>


int main(int argc, char **argv)
{
  
  pid_t pid, sid, child_a, child_b, child_c;
  int status, t, i;

  pid = fork();
  if (pid < 0)
  {
    exit(EXIT_FAILURE);
  }
  if (pid > 0)
  {    
    exit(EXIT_SUCCESS);
  }  
  umask(0);
  sid = setsid();
  if (sid < 0) 
  {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

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
        }
        while ((wait(&status)) > 0);
        char dizip[100];
        sprintf(dizip, "%s.zip", newfolder);
        char *zip[] = {"zip", "-rm", dizip, newfolder, NULL};
        execv("/usr/bin/zip", zip);
      }
    }
    sleep(30);
  }
}
