#include <iostream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <ctime>

#include "../tools/time_measurer.h"

const int kTupleNum=100000000;
const int kFileSize=kTupleNum*sizeof(int);
void WriteState(char *state, const int &position, const int &number){
	memcpy(state+position*sizeof(int), &number, sizeof(int));
}

void ReadState(char *state, const int &position, int &number){
	memcpy(&number, state+position*sizeof(int), sizeof(int));
}

void WriteProcessRound(char *state, const int &round){
	int total=0;
	int r=0;
	for(; r<round; ++r){
		for(int i=0; i<kTupleNum; ++i){
			WriteState(state, i, total);
			++total;
		}
	}
	std::cout<<"round="<<r<<std::endl;
}

void WriteProcessRoundRandom(char *state, const int &round){
	int total=0;
	int r=0;
	for(; r<round; ++r){
		for(int i=0; i<kTupleNum; ++i){
			WriteState(state, rand()%kTupleNum, total);
			++total;
		}
	}
	std::cout<<"round="<<r<<std::endl;
}

void Process(char *state){
	TimeMeasurer timer;
	timer.StartTimer();
	WriteProcessRound(state, 100);
	timer.EndTimer();
	std::cout<<"state size="<<kFileSize/1024/1024<<"MB"<<std::endl;
	std::cout<<"elapsed time="<<timer.GetElapsedMilliSeconds()<<"ms"<<std::endl;
}

void ProcessRandom(char *state){
	TimeMeasurer timer;
	timer.StartTimer();
	WriteProcessRoundRandom(state, 10);
	timer.EndTimer();
	std::cout<<"state size="<<kFileSize/1024/1024<<"MB"<<std::endl;
	std::cout<<"elapsed time="<<timer.GetElapsedMilliSeconds()<<"ms"<<std::endl;
}

