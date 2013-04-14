#include "buffer_ring.h"

int main(int argc, char *argv[]){
	if(argc!=2){
		printf("format: %s [buffer_size]", argv[0]);
	}
	int buffer_size=atoi(argv[1]);
	srand(time(NULL));
	Buffer_Ring<int> br(buffer_size);
	br.producer_init();
	int temp;
	while(1){
		temp=rand()%10000;
		br.producer_write(temp);
		if(temp==9999){
			break;
		}
	}
	br.producer_close();
}
