#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
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
	for(int r=0; r<round; ++r){
		for(int i=0; i<kTupleNum; ++i){
			WriteState(i, total);
			++total;
		}
	}
}

void WriteSnapshot(const std::string &filename){
	std::ofstream outfile(filename, std::ofstream::binary);
	outfile.write(state, kTupleNum*sizeof(int));
	outfile.close();
}

int main(){
	//CreateState();
	GetMMapState();
	std::cout<<"mmap state obtained!"<<std::endl;
	timer.StartTimer();
	WriteProcessRound(10);
	timer.EndTimer();
	std::cout<<"state size="<<kTupleNum*sizeof(int)/1024/1024<<"MB"<<std::endl;
	std::cout<<"elapsed time="<<timer.GetElapsedMilliSeconds()<<"ms"<<std::endl;

	CreateState();
	timer.StartTimer();
	WriteProcessRound(10);
	timer.EndTimer();
	std::cout<<"state size="<<kTupleNum*sizeof(int)/1024/1024<<"MB"<<std::endl;
	std::cout<<"elapsed time="<<timer.GetElapsedMilliSeconds()<<"ms"<<std::endl;
	//WriteSnapshot("snapshot.dat");
	getchar();
	free(state);
	return 0;
}
