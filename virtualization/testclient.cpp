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
	int fd=open("foo", O_RDWR);
	int filesize=kTupleNum*sizeof(int);
	char *data=(char*)mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	int value;
	memcpy(&value, data, sizeof(value));
	std::cout<<"get value="<<value<<std::endl;
	getchar();
	munmap(data, filesize);
	close(fd);
	return 0;
}
