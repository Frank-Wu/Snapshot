#include "buffer_ring.h"

int main(){
	srand(time(NULL));
	Buffer_Ring<int> br;
	br.producer_init();
	int temp;
	while(1){
		temp=rand()%32767;
		br.producer_write(temp);
		printf("%d\n", temp);
		if(temp==9999){
			break;
		}
	}
	br.producer_close();
}
