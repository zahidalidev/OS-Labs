#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main() 
{ 

	char *arr = (char *) calloc(100, sizeof(char));	
	char *arr2 = (char *) calloc(100, sizeof(char));	
	char *arr3 = (char *) calloc(100, sizeof(char));	
	int c;

	c = read(0, arr, 100);	

//writing to file1 from arr
	int fd = open("file1.txt", O_RDWR | O_CREAT, 00644);
	if(fd == -1){
		printf("file 0pen err0r\n\n");
	}	
	
	write(fd, arr, c);
	close(fd);

//copying from file1 to arr2
	int fd4 = open("file1.txt", O_RDWR | O_CREAT, 00644);
	if(fd4 == -1){
		printf("file 0pen err0r\n\n");
	}	
	
	read(fd4, arr2, c);
	close(fd4);


//writing to file2 from arr2
	int fd2 = open("file2.txt", O_RDWR | O_CREAT, 00644); 
	if (fd2 == -1) { 
		printf("Cannot open file\n\n"); 
		
	} 
	c = write(fd2, arr2 ,c);
	close(fd2);

//copying from file2 to arr3
	int fd3 = open("file2.txt", O_RDWR | O_CREAT, 00644); 
	if (fd3 == -1) 
	{ 
		printf("Cannot open file\n\n"); 
		
	} 
	read(fd3, arr3, c);
	printf("data from seconf file is: \n%s\n\n", arr3);	
	close(fd3);
	
	
	printf("fd1 of file1 is: %d\n\n", fd);
	printf("fd2 of file2 is: %d\n\n", fd2);
	printf("fd3 of file2 is: %d\n\n", fd3);
	printf("fd4 of file1 is: %d\n\n", fd4);
	return 0; 
}
