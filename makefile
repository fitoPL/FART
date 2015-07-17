CC=gcc 
Library=libFART.so
RandomTest=RandomTest

all: $(Library) $(RandomTest)

$(Library): 
	$(CC) -fpic -c -Wall  FART.c 
	$(CC) -shared -o libFART.so FART.o

$(RandomTest):
	$(CC) -L ./ -lFART RandomTest.c -o RandomTest

