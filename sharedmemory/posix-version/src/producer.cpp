#include "buffer_ring.h"

int main(int argc, char *argv[]){
	if(argc!=3){
		printf("format: %s [buffer_size] [message_size]\n", argv[0]);
		return -1;
	}
	int buffer_size=atoi(argv[1]);
	int message_size=atoi(argv[2]);
	srand(time(NULL));
	Buffer_Ring<int> br(buffer_size, message_size);
	br.init();
	int *message=new int[message_size];
	for(int i=0; i<100000000; ){
		for(int j=0; j<message_size; ++j){
			message[j]=i;
			++i;
		}
		br.write(message);
	}
	message[0]=-1;
	br.write(message);
	br.close();
	return 0;
}
