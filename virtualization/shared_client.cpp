#include "process.h"
#include "hacker.h"

int main(int argc, char **argv){
	if(argc!=2){
		std::cout<<"please provide the parameter!"<<std::endl;
		return -1;
	}
	std::cout<<argv[1]<<std::endl;
	int tenantId=atoi(argv[1]);
	std::cout<<"tenantId="<<tenantId<<std::endl;
	srand(time(0));
	char *state=(char *)myAlloc(tenantId, kFileSize);
	printf("obtained hypervisor state!\n");
	int number=tenantId;
	if(tenantId!=10){
		memcpy(state+0*sizeof(int), &number, sizeof(int));
	}
	int mynum;
	memcpy(&mynum, state+0*sizeof(int), sizeof(int));
	//std::cout<<"mynum="<<mynum<<std::endl;
	Process(state);
	getchar();
	return 0;
}
