#include "FART.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
  FART *net=0;
  FART_load(&net, "trainedTest.raw");
  FART_dump(*net,1);
}
