#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifndef _FART_H
#define _FART_H 1 

#define LEARN_MODE 1
#define ONLY_CLASSIFY__MODE  0

//struct FARTtemplate; 

typedef struct 
{
  float *data;
  int size;
  struct _FARTtemplate *next; 
}FARTtemplate; 

typedef struct
{
  int size;
  float beta, rho, alpha;
  FARTtemplate *templates;
}FART;

FART  FART_new(float, float, float);
float *FART_resize_vector(float* ,int, int);
float FART_num(FARTtemplate *, FARTtemplate*);
float FART_norm(FARTtemplate *);
float FART_choice_function(FARTtemplate*, FARTtemplate*,float);
int   FART_vigilance_match(FARTtemplate*,FARTtemplate*,float);
void  FART_learn(FARTtemplate*,FARTtemplate*,float);
int   FART_classify(float*,int, FART*,int);
void  FART_dump(FART, int);
int   FART_store(FART *, const char*);
int   FART_load (FART **,const char*); 
#endif 
