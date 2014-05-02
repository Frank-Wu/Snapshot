//in this example, we create two threads, one continuously write to a storage and the other periodically checkpoint the storage.

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
#include <thread>
#include <unistd.h>

char *state;
const int kTupleNum=10;

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

void WriteProcess(){
	int total=0;
	while(1){
		for(int i=0; i<kTupleNum; ++i){
			WriteState(i, total);
			++total;
		}
	}
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

void ReadSnapshot(const std::string &filename){
	std::ifstream infile(filename, std::ifstream::binary);
	infile.read(state, kTupleNum*sizeof(int));
	int total;
	for(int i=0; i<kTupleNum; ++i){
		ReadState(i, total);
		std::cout<<total<<" ";
	}
	std::cout<<std::endl;
	infile.close();
}

int main(){
	CreateState();
//	ReadSnapshot("snapshot.dat");
//	ReadSnapshot("final.dat");
	std::thread write_thread(WriteProcess);
	sleep(5);
	int pid=fork();
	if(pid==0){
		WriteSnapshot("snapshot.dat");
		free(state);
		return 0;
	}else{
		sleep(2);
		WriteSnapshot("final.dat");
		return 0;
	}
}


