#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct FARTtemplate;

typedef struct 
{
  float *data;
  char *label;
  int size;
  struct FARTtemplate *next; 
}FARTtemplate; 

typedef struct
{
  int size;
  float beta, rho, alpha;
  FARTtemplate *templates;
}FART;

FART FART_new(float, float, float);
float *FART_resize_vector(float* ,int, int);
float FART_num(FARTtemplate *, FARTtemplate*);
float FART_norm(FARTtemplate *);
float FART_choice_function(FARTtemplate*, FARTtemplate*,float);
int   FART_vigilance_match(FARTtemplate*,FARTtemplate*,float);
void FART_learn(FARTtemplate*,FARTtemplate*,float);
int FART_classify(float*,int, FART*);
void FART_dump(FART, int,unsigned short int);

