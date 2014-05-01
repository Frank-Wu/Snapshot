#include "buffer_ring.h"

int main(int argc, char *argv[]){
	if(argc!=3){
		printf("format: %s [buffer_size] [message_size]\n", argv[0]);
		return -1;
	}
	int buffer_size=atoi(argv[1]);
	int message_size=atoi(argv[2]);
	timeval t1, t2;
	Buffer_Ring<int> br(buffer_size, message_size);
	br.init();
	int *message=new int[message_size];
	double counter=0;
	gettimeofday(&t1, NULL);
	while(1){
		++counter;
		br.read(message);
		if(message[0]==-1){
			break;
		}
	}
	gettimeofday(&t2, NULL);
	double elapsed_time=(t2.tv_sec-t1.tv_sec)+(t2.tv_usec-t1.tv_usec)*1e-6;
	printf("elapse: %fs\n", elapsed_time);
	printf("count: %.0f, unit size: %luB\n", counter, sizeof(int));
	printf("buffer size: %luB, message size: %luB\n", sizeof(int)*buffer_size, sizeof(int)*message_size);
	double throughput=counter*message_size*sizeof(int)/elapsed_time/1000;
	printf("throughput: %fKB/s\n", throughput);
	br.close();
	return 0;
}
