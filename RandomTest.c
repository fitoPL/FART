#include "FART.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
  int cells=81; 
  FILE *fd;
  FART net = FART_new(.5,.5,.5);
  int i=0,j;
  float s1[cells];
  char data[cells+1];
  float max=0; 

  fd = fopen("/dev/urandom","r");
  for(i=0;i!=400;i++)
  {
    fgets(&data,cells,fd);
    for(j=0; j!= cells;j++)
    {
      max = max > (float)(data[j]) ? max : (float)(data[j]); 
      s1[j] = (float)(data[j])/127; 
      s1[j] = s1[j] >= 0 ? s1[j] : -s1[j];
    }
    //printf("%f=, %f=\n", s1[0], s1[1]);
    FART_classify((float *)&s1 ,sizeof(s1)/sizeof(float), &net);   
  }
  fclose(fd);
  printf("max=%f\n",max);
  FART_dump(net,1);
}
