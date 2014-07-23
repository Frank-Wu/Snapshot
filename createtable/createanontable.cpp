#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../tools/time_measurer.h"

char *state;
char *shadow_state;
const int kStateSize=1000;
TimeMeasurer timer;

void GetAnonState(){
	int fd=open("foo", O_RDWR|O_CREAT|O_TRUNC, (mode_t)0600);
	state=(char*)mmap(NULL, kStateSize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	lseek(fd, kStateSize-1, SEEK_SET);
	write(fd, "", 1);

	int writetest=203;
	memcpy(state+sizeof(int)*20, &writetest, sizeof(writetest));
	std::cout<<"state[1] address="<<state[20]<<std::endl;
	
	int readtest=-1;
	memcpy(&readtest, state+sizeof(int)*20, sizeof(readtest));
	std::cout<<"read "<<readtest<<std::endl;
	shadow_state=(char*)mmap(state, kStateSize, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);

	int readtest1=-1;
	memcpy(&readtest1, shadow_state+sizeof(int)*20, sizeof(readtest1));
	std::cout<<"read1 "<<readtest1<<std::endl;
	writetest=205;
	memcpy(shadow_state+sizeof(int)*20, &writetest, sizeof(writetest));
	memcpy(&readtest1, state+sizeof(int)*20, sizeof(readtest1));
	std::cout<<"read1 "<<readtest1<<std::endl;
}

int main(){
	GetAnonState();
}
