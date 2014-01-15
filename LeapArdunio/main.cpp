#include <iostream>
#include <fstream>
#include <stdio.h>

void readArdunioOutput()
{
  FILE* ardInput;
  char buffer[100];
  ardInput = fopen("/dev/cu.usbmodem641", "r");
  if(ardInput == NULL)
    perror("Error Ardunio not connected");
  else
    {
      while(true) {
	while(!feof(ardInput))
	  {
	    fgets(buffer, 100, ardInput);
	    printf("%s",buffer);
	  }
      }
    }
}

int main()
{
  FILE* ardOutput;
  char c;
  ardOutput = fopen("/dev/cu.usbmodem641", "w");
  if(ardOutput == NULL)
    perror("Error Ardunio not Connected");
  else
    {
      for(c = 'A'; c <= 'Z'; c++){
	putc(c,ardOutput);
      }
      fclose(ardOutput);
    }
}
