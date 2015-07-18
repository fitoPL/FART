CC=gcc 
Library=libFART.so
RandomTest=RandomTest
ReadTest = ReadTest
SaveTest = SaveTest

all: $(Library) $(RandomTest) $(SaveTest) $(ReadTest)

$(Library): 
	$(CC) -fpic -c -Wall  FART.c 
	$(CC) -shared -o libFART.so FART.o

$(RandomTest):
	$(CC) -L ./ -lFART RandomTest.c -o RandomTest

$(SaveTest):
	$(CC) -L ./ -lFART SaveTest.c -o SaveTest

$(ReadTest):
	$(CC) -L ./ -lFART ReadTest.c -o ReadTest


