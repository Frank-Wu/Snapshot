#include "buffer_ring.h"

int main(int argc, char *argv[]){
	if(argc!=2){
		printf("format: %s [buffer_size]", argv[0]);
		return -1;
	}
	int buffer_size=atoi(argv[1]);
	timeval t1, t2;
	Buffer_Ring<int> br(buffer_size);
	br.consumer_init();
	int temp;
	double counter=0;
	gettimeofday(&t1, NULL);
	while(1){
		++counter;
		temp=br.consumer_read();
		if(temp==9999){
			break;
		}
	}
	gettimeofday(&t2, NULL);
	double elapsed_time=(t2.tv_sec-t1.tv_sec)+(t2.tv_usec-t1.tv_usec)*1e-6;
	printf("elapse: %fs\n", elapsed_time);
	printf("count: %.0f\n", counter);
	double throughput=counter*sizeof(int)/elapsed_time/1000;
	printf("throughput: %fKB/s\n", throughput);
	br.consumer_close();
	return 0;
}
