#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int primeNumer[100]; //array to store prime number
int arrayIndexCounter=0; //to count index of aray
//to save range
int firstRange[2];
int secondRange[2];

void *prime(int range[]); 

int main(int argc, char *argument[]){
	
//saving ranges
	firstRange[0] = 0;
	firstRange[1] = atoi(argument[1])/2;
	secondRange[0] = atoi(argument[1])/2;
	secondRange[1] = atoi(argument[1]);
//threads
	pthread_t th1;
	pthread_t th2; 	
//creating thread 1
	pthread_create(&th1, NULL, prime, firstRange);
	pthread_join(th1,NULL);
//creating thread 2
	pthread_create(&th2, NULL, prime, secondRange);
	pthread_join(th2,NULL);
//printing prime numbers
	for(int i=0;i<arrayIndexCounter;i++){
		printf("%d  ",primeNumer[i]);
	}	
	return 0;
}

void *prime(int range[])
{
	int start=range[0],end=range[1];
	for(int i=start;i<end;i++){
		int c=0;
		for (int j = 1; j <= i; j++) {
     		if (i % j == 0) 
         		c++;
  		}
	  	if (c == 2) {
		  
		primeNumer[arrayIndexCounter]=i;
		arrayIndexCounter++;
		
		}
	}
	pthread_exit(0);
}
