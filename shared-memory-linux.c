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


int main() { 

	const char *name = "OS";  //name 0f shared mem0ry 0bject

///////
	int fd = open("file1.txt", O_RDWR | O_CREAT, 00644);
	if(fd == -1){
		printf("file open error \n\n");
	}
	int siz;
	struct stat sb;
	if(fstat(fd, &sb) == -1){ 
		printf("stat command error \n\n");
	}
	int pageSize = sb.st_size;  //size f0r share mem0ry 0bject

	printf("%s is %ld byte long \n\n", "file1.txt", sb.st_size);
///////

	pid_t p = fork();
	if(p < 0){
		printf("fork error \n\n");
	}	
	
//child process writing
	if(p == 0){
				
		char array[pageSize];
		siz = read(fd, array, pageSize); //data in array f0r shared mem0ry
		close(fd);
		
		int fd2; //shared mem0ry file decripter
		char *ptr; //p0inter t0 shared mem0ry 0bject

		fd2 = shm_open(name, O_CREAT | O_RDWR, 00644); //creating shared mem0ry 0bject

		ftruncate(fd2, pageSize); //c0nfiguring the size 0f shared mem0ry 0bject

			//mem0ry map the shared mem0ry 0bject
		ptr = (char *)mmap(0, pageSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd2, 0);
		sprintf(ptr, "%s", array); //writing t0 the shared mem0ry 0bject

		close(fd2);
	}

//parent pr0cess reading
	if(p > 0){
		wait(NULL);
		int fd3 = shm_open(name, O_RDONLY, 0666);
		char *ptr2;
			//memorey map to the shared memory object
		ptr2 = mmap(0, pageSize, PROT_READ, MAP_SHARED, fd3, 0);
		printf("%s", ptr2); //read from the shared memory object
		shm_unlink(name);
		close(fd3);
	}



	

}
