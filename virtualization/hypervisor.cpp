#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

const int kTupleNum=100000000;
int main(){
	int fd=open("foo", O_RDWR|O_CREAT|O_TRUNC);
	int filesize=kTupleNum*sizeof(int);
	lseek(fd, filesize-1, SEEK_SET);
	write(fd, "", 1);
	char *data=(char*)mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	memset(data, 0, filesize);
	int value=23;
	memcpy(data, &value, sizeof(value));
	getchar();
	munmap(data, filesize);
	close(fd);
	std::cout<<"closed!"<<std::endl;
	return 0;
}
