#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ctime>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include "../tools/time_measurer.h"

char *state;
const int kTupleNum=10000000;
const int kFileSize=kTupleNum*sizeof(int);
TimeMeasurer timer;

void CreateState(){
	state=(char*)malloc(kFileSize);
	memset(state, 0, kFileSize);
}

void GetHypervisorState(){
	int fd=shm_open("shm", O_RDWR, (mode_t)0600);
	state=(char*)mmap(NULL, kFileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
//	memset(state, 0, kFileSize);
}

void GetMMapState(){
	int fd=open("foo", O_RDWR|O_CREAT|O_TRUNC, (mode_t)0600);
	lseek(fd, kFileSize-1, SEEK_SET);
	write(fd, "", 1);
	state=(char*)mmap(NULL, kFileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	memset(state, 0, kFileSize);
}

void GetPrivateMMapState(){
	int fd=open("foo", O_RDWR|O_CREAT|O_TRUNC, (mode_t)0600);
	lseek(fd, kFileSize-1, SEEK_SET);
	write(fd, "", 1);
	state=(char*)mmap(NULL, kFileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	memset(state, 0, kFileSize);
}

void GetAnonState(){
	state=(char*)mmap(NULL, kFileSize, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANON, -1, 0);
	memset(state, 0, kFileSize);
}

void GetShmState(){
	int fd=shm_open("shm", O_RDWR|O_CREAT|O_TRUNC, (mode_t)0600);
	ftruncate(fd, kFileSize);
	state=(char*)mmap(NULL, kFileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	memset(state, 0, kFileSize);
}

void WriteState(const int &position, const int &number){
	memcpy(state+position*sizeof(int), &number, sizeof(int));
}

void ReadState(const int &position, int &number){
	memcpy(&number, state+position*sizeof(int), sizeof(int));
}

void WriteProcessRound(const int &round){
	int total=0;
	int r=0;
	for(; r<round; ++r){
		for(int i=0; i<kTupleNum; ++i){
			WriteState(i, total);
			++total;
		}
	}
	std::cout<<"round="<<r<<std::endl;
}

void WriteProcessRoundRandom(const int &round){
	int total=0;
	int r=0;
	for(; r<round; ++r){
		for(int i=0; i<kTupleNum; ++i){
			WriteState(rand()%kTupleNum, total);
			++total;
		}
	}
	std::cout<<"round="<<r<<std::endl;
}

void WriteSnapshot(const std::string &filename){
	std::ofstream outfile(filename, std::ofstream::binary);
	outfile.write(state, kFileSize);
	outfile.close();
}

void Process(){
	timer.StartTimer();
	WriteProcessRound(100);
	timer.EndTimer();
	std::cout<<"state size="<<kFileSize/1024/1024<<"MB"<<std::endl;
	std::cout<<"elapsed time="<<timer.GetElapsedMilliSeconds()<<"ms"<<std::endl;
}

void ProcessRandom(){
	timer.StartTimer();
	WriteProcessRoundRandom(10);
	timer.EndTimer();
	std::cout<<"state size="<<kFileSize/1024/1024<<"MB"<<std::endl;
	std::cout<<"elapsed time="<<timer.GetElapsedMilliSeconds()<<"ms"<<std::endl;
}

int main(){
	srand(time(0));
//	GetMMapState();
//	GetShmState();
	GetHypervisorState();
	printf("obtained hypervisor state!\n");
	Process();
//	ProcessRandom();
//	CreateState();
//	Process();
//	ProcessRandom();
	return 0;
}
