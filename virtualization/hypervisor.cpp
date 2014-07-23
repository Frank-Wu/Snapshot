#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

const size_t kTupleNum=5000000000;
const size_t kFileSize=kTupleNum*sizeof(int);
int main(){
	shm_unlink("shm");
	int fd=shm_open("shm", O_RDWR|O_CREAT|O_TRUNC, (mode_t)0600);
	if(fd==-1){
		printf("error, cannot open!\n");
		return -1;
	}
	ftruncate(fd, kFileSize);
	char *data=(char*)mmap(NULL, kFileSize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	memset(data, 0, kFileSize);
	printf("finished preparing hypervisor!\n");
	int pid=(int) getpid();
	std::cout<<"pid="<<pid<<std::endl;
	char arrpid[10];
	sprintf(arrpid, "%d", pid);
	std::string strpid=std::string(arrpid);
	std::string filename="/proc/"+strpid+"/smaps";
	std::ifstream infile(filename.c_str());
	std::string line;
	while(std::getline(infile, line)){
		std::cout<<"line="<<line<<std::endl;
	}
	infile.close();
	getchar();
	close(fd);
	shm_unlink("shm");
	return 0;
}
