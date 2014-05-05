#include <iostream>
#include <cstring>
#include <string>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

const int kTupleNum=1000000;
int main(){
	int fd=open("foo", O_RDWR|O_CREAT|O_TRUNC, (mode_t)0600);
	int filesize=kTupleNum*sizeof(int);
	lseek(fd, filesize-1, SEEK_SET);
	write(fd, "", 1);
	char *data=(char*)mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	memset(data, 0, filesize);
	munmap(data, filesize);
	close(fd);
	std::cout<<"closed!"<<std::endl;
	return 0;
}
