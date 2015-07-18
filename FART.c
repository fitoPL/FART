#include<stdio.h>
#include<stdlib.h>
#include "FART.h"


FART FART_new(float alpha, float beta, float rho)
{
  FART ret;
  ret.templates=0;
  ret.size =0;
  ret.alpha = alpha;
  ret.beta = beta; 
  ret.rho = rho;
  return ret;
}

float * FART_resize_vector(float *data,int csize, int nsize)
{
  float *ret = malloc(sizeof(float)*nsize);
  int i;
  for(i=0; i!= csize; i++)
    ret[i]=data[i];
  for(;i < nsize; i++)
    ret[i]=1;
  return ret;
}


float FART_num(FARTtemplate *t1, FARTtemplate *t2)
{
  float  ret=0; 
  int size=t1->size;
  while(--size>=0)
    ret += t1->data[size]<t2->data[size]?t1->data[size]:t2->data[size];
  return ret; 
}

float FART_norm(FARTtemplate *t)
{
  int i;
  float ret=0;
  for(i=0; i!= t->size; i++)
    ret+=t->data[i];
  return ret;
}

float FART_choice_function(FARTtemplate *input, FARTtemplate *t,float alpha)
{
  return FART_num(input,t)/(alpha+FART_norm(t));
}

int FART_vigilance_match(FARTtemplate *input, FARTtemplate *t,float rho)
{
  float match; 
  //FARTtemplate and;
  match = FART_num(input,t)/(FART_norm(input));
  //printf ("rho is%f\n", match);
  return match > rho;
}

void FART_learn(FARTtemplate *input, FARTtemplate *t, float beta)
{
  FARTtemplate *updated = malloc(sizeof(FARTtemplate));
  updated->data = malloc(sizeof(float)*t->size);
  int i;
  for(i=0; i!= t->size; i++)
  {
      updated->data[i] = beta* (input->data[i] < t->data[i] ? input->data[i] : t->data[i]);
      updated->data[i]+= (1-beta)*t->data[i];
  }
  t->data=updated->data;
}


int FART_classify (float *input,int size,  FART *net)
{
  float maxClass=0,cmp,*ninput=0,*aux;
  int nsize,_class,choice=0,classCounter=0;
  FARTtemplate *iterator,tmp,*choiced; 

  if (net->size == 0 )
  {
    net->size=1;
    net->templates=malloc(sizeof(FARTtemplate));
    net->templates->data = malloc(sizeof(float)*size);
    net->templates->next=0;
    net->templates->size = size;
    memcpy(net->templates->data,input,sizeof(float)*size);
    return 0;
  }

  if (size == net->templates->size)
    ninput = input;
 
  if (size > net->templates->size)
  {
    iterator = net->templates;
    while(iterator)
    {
      aux =  FART_resize_vector(iterator->data,iterator->size, size);
      iterator->data = aux; 
      iterator->size = size; 
      iterator = iterator->next;
    }
    ninput  = input; 
  }

  if(size < net->templates->size)
    ninput = FART_resize_vector(input, size, net->templates->size);

  iterator = net->templates; 
  tmp.data = ninput; 
  tmp.size = iterator->size;  

  //find high template resonance  
  while(iterator) 
  {
    cmp = FART_choice_function(&tmp,iterator, net->alpha);
    if (cmp > maxClass)
    {
       maxClass = cmp; 
       choice = classCounter; 
       choiced = iterator; 
    }
    classCounter++;
    iterator = iterator->next;
  }

  iterator = net->templates; 
  while(iterator)
  {
    if ( FART_vigilance_match(&tmp, iterator,net->rho) ) 
    {
      FART_learn(&tmp, choiced, net->beta);
      return choice;
    }
    iterator=iterator->next;
  }
  
  //add ass new 
  iterator = net->templates;
  while(1)
  {
    if (!iterator->next)
    { 
      nsize = iterator->size;
      iterator->next = malloc(sizeof(FARTtemplate));
      iterator = iterator->next; 
      iterator->data = input;
      iterator->size = size;
      iterator->next = 0;
      iterator->label = net->size;
      net->size++;
      break; 
    }
    iterator=iterator->next;
  }
  return -1;

}

void FART_dump(FART net, int data)
{
  FARTtemplate *iterator = net.templates; 
  int i;
  printf("number of templates:%i\n", net.size);
  printf("cells per template:%i\n", net.templates->size);
  if (!data)
    return;
  while(iterator)
  {
    printf("\n[\n");
    for(i=0; i != iterator->size; i ++)
      printf(" %f ",iterator->data[i]);
    printf("\n]\n");
    iterator = iterator->next;
  }
}

int FART_store(FART *net, char *path)
{
  FILE *fd = fopen(path, "w");
  FARTtemplate *iterator = net->templates;
  if(!fd)
    return 0;
  fwrite(net, sizeof(net),1, fd);
  while(iterator)
  {
    fwrite(iterator, sizeof(FARTtemplate),1,fd); 
    fwrite(iterator->data,sizeof(float), iterator->size,fd);
    iterator=iterator->next;
  }
  fclose(fd);
  return 1;
}

int FART_load(FART **_net, char *path)
{
  FILE *fd = fopen(path, "r");
  int i;
  FART *net;
  FARTtemplate *iterator = 0; 
  if(!fd)
  {
    net = 0;
    return 0;
  }
  net = (FART *) malloc(sizeof(FART));
  //printf("file is open correctly\n");
  fread(net, sizeof(net),1, fd);
  //printf("reading first structure\m");
  for(int i=0; i != net->size; i++)
  {
    if (i==0)
    {
      net->templates = (FARTtemplate*)malloc(sizeof(FARTtemplate));
      fread(net->templates, sizeof(FARTtemplate),1,fd); 
      iterator = net->templates;
      //printf("first templeate correctly read\n");
    }else
    {
      iterator->next = (FARTtemplate*)malloc(sizeof(FARTtemplate));
      fread(iterator->next, sizeof(FARTtemplate),1,fd);
      iterator = iterator->next; 

      //printf("first template number %i read\n", i);  
    }
    iterator->data = (float*) malloc(sizeof(float) * iterator->size);
    fread(iterator->data, sizeof(float), iterator->size, fd);

  }
  iterator->next = 0;
  fclose(fd);
  *_net = net;
  return 0;

}



