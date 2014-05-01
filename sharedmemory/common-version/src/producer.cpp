#include "buffer_ring.h"

int main(int argc, char *argv[]){
	if(argc!=2){
		printf("format: %s [buffer_size]\n", argv[0]);
		return -1;
	}
	int buffer_size=atoi(argv[1]);
	srand(time(NULL));
	Buffer_Ring<int> br(buffer_size);
	br.producer_init();
	int temp;
	for(int i=0; i<10000; ++i){
		temp=rand()%10000;
		br.producer_write(temp);
		if(temp==9999){
			break;
		}
	}
	br.producer_write(10000);
	br.producer_close();
	return 0;
}
