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

  fd = fopen("/dev/urandom","r");
  for(i=0;i!=300;i++)
  {
    fgets(&data,cells,fd);
    for(j=0; j!= cells;j++)
    {
      s1[j] = (float)(data[j])/127; 
      s1[j] = s1[j] >= 0 ? s1[j] : -s1[j];
    }
    //printf("%f=, %f=\n", s1[0], s1[1]);
    FART_classify((float *)&s1 ,sizeof(s1)/sizeof(float), &net,1);   
  }
  fclose(fd);
  FART_dump(net,1);
  FART_store(&net, "trainedTest.raw");

}
