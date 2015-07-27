#include<windows.h>
#include<stdio.h>
#include<winuser.h>
#include<windowsx.h>

#define BUFSIZE 80


int main(void)
{

  FILE *file;
  file=fopen("keylog","a+");
  fprintf(file, "\n--------------------------START--------------------------\n");
  fclose(file);
}  