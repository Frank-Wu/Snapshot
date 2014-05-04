#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ctime>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "../tools/time_measurer.h"

char *state;
const int kTupleNum=100000000;
TimeMeasurer timer;

void CreateState(){
	state=(char*)malloc(kTupleNum*sizeof(int));
	memset(state, 0, kTupleNum*sizeof(int));
}

void GetMMapState(){
	int fd=open("foo", O_RDWR);
	int filesize=kTupleNum*sizeof(int);
	state=(char*)mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	memset(state, 0, filesize);
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
	outfile.write(state, kTupleNum*sizeof(int));
	outfile.close();
}

void Process(){
	timer.StartTimer();
	WriteProcessRound(100);
	timer.EndTimer();
	std::cout<<"state size="<<kTupleNum*sizeof(int)/1024/1024<<"MB"<<std::endl;
	std::cout<<"elapsed time="<<timer.GetElapsedMilliSeconds()<<"ms"<<std::endl;
}

void ProcessRandom(){
	timer.StartTimer();
	WriteProcessRoundRandom(2);
	timer.EndTimer();
	std::cout<<"state size="<<kTupleNum*sizeof(int)/1024/1024<<"MB"<<std::endl;
	std::cout<<"elapsed time="<<timer.GetElapsedMilliSeconds()<<"ms"<<std::endl;
}

int main(){
	srand(time(0));
	CreateState();
	Process();
	ProcessRandom();
	GetMMapState();
	Process();
	ProcessRandom();
	getchar();
	free(state);
	return 0;
}
