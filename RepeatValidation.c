#include "FART.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
  FILE *fd;
  FART net;
  FART *_net;
  
  float s1[] = { .1, .1, .2, .3};
  float s2[] = { .1, .2, .3, .4};
  float s3[] = { .91, .87, .75, .84};
  float s4[] = { .88, .75, .94,.83};
  float s5[] = { .66,.75, .65,.83};
  float s6[] = { .44,.75, .91,.83};
  float s7[] = { .5, .31, .22, .18};


  if (access("SAVEDDATA.raw",F_OK))
  {
    net = FART_new(.5,.5,.5);
  }
  else 
  {
     FART_load(&_net,"SAVEDDATA.raw");
     net = *_net;
     printf("network loaded so reading from file");
  }
  FART_classify((float*)&s1, 4, &net,1);
  FART_classify((float*)&s2, 4, &net,1);
  FART_classify((float*)&s3, 4, &net,1);
  FART_classify((float*)&s4, 4, &net,1);
  FART_classify((float*)&s5, 4, &net,1);
  FART_classify((float*)&s6, 4, &net,1);
  FART_classify((float*)&s7, 4, &net,1);


  FART_dump(net,1);
  FART_store(&net,"SAVEDDATA.raw");
}
