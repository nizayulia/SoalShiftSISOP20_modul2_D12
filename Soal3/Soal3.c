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
