#include <iostream>
#include <cstdlib>
#include <cstring>
#include "../tools/time_measurer.h"

char *state;
const int kTupleNum=10000;
TimeMeasurer timer;

void CreateState(){
	state=(char*)malloc(kTupleNum*sizeof(int));
	memset(state, 0, kTupleNum*sizeof(int));
}

void WriteState(const int &position, const int &number){
	memcpy(state+position*sizeof(int), &number, sizeof(int));
}

void ReadState(const int &position, int &number){
	memcpy(&number, state+position*sizeof(int), sizeof(int));
}

void WriteProcessRround(const int &round){
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
	CreateState();
	timer.StartTimer();
	WriteProcessRound(1000);
	timer.EndTimer();
	std::cout<<"elapsed time="<<timer.GetElapsedMilliSeconds()<<"ms"<<std::endl;
	WriteSnapshot("snapshot.dat");
	free(state);
	return 0;
}
