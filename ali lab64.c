#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <string.h> 
#include <sys/wait.h> 
#include <fcntl.h> 
#include <errno.h> 
#include<sys/stat.h>
#include<sys/mman.h>
#include<sys/shm.h>
#include<errno.h>
#define max_sequence 10

int main() { 
//defining struct 	
	typedef struct{
		long fb[100];
		int seqSize; 
	}shd;	
	shd p1; //p1 is struct variabble t0 access data 0f struct
	int userInput;  //input fr0m user
	scanf("%d", &userInput);

	if(userInput > max_sequence){
		printf("size is greater than max_sequence: %d\n\n ", errno);
		return 0;	
	}
	const char *name = "OS";  //name 0f shared mem0ry 0bject

	pid_t p = fork();
	if(p < 0){
		printf("fork error \n\n");
	}	
	int pageSize = sizeof(shd);
	printf("size of struct is: %d\n\n", pageSize);
	char* array[userInput];
//child process writing
	if(p == 0){
				
		int fd; //shared mem0ry file decripter
		char *ptr; //p0inter t0 shared mem0ry 0bject

		fd = shm_open(name, O_CREAT | O_RDWR, 00644); //creating shared mem0ry 0bject
		ftruncate(fd, pageSize); //c0nfiguring the size 0f shared mem0ry 0bject
			//mem0ry map the shared mem0ry 0bject
		ptr = mmap(0, pageSize, PROT_WRITE, MAP_SHARED, fd, 0);
		sprintf(ptr, "0\n");  //printing in shared mem0ry name
		ptr += 2;
		sprintf(ptr, "1\n"); //printing in shared mem0ry name
		ptr += 2;
		int i = 0;
		int number1 = 0;  //f0r febn0chi
 		int number2 = 1; //f0r febn0chi
		int sum = 0;
		//l00p less than user input size -2 bcz 2 intergers already saved in shared mem0ry
		while(i < userInput-2){
			sum = number1 + number2;
			number1 = number2;
			number2 = sum;
			i++;
			char shNumber[10];
			//printing in shared mem0ry name
			sprintf(shNumber, "%d\n", sum);
			sprintf(ptr, "%s ", shNumber);
			ptr += strlen(shNumber);
		}
		close(fd);
	}

//parent pr0cess reading
	if(p > 0){
		wait(NULL);
		int fd3 = shm_open(name, O_RDONLY, 0666); //opening shared memory object
		char *ptr2; //pointer to shared memvry object
			//memorey map to the shared memory object
		ptr2 = (char *) mmap(0, pageSize, PROT_READ, MAP_SHARED, fd3, 0);
		printf("%s\n", (char *)ptr2); //read from the shared memory object and prints
		shm_unlink(name);
		close(fd3);
	}



	

}
