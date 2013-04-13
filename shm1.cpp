#include "shm_com.h"

int main(){
	//create shared memory
	int shmid=shmget((key_t)4320, sizeof(shared_use_st<int>), 0666|IPC_CREAT);
	printf("id: %d\n", shmid);
	if(shmid==-1){
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	//attach shared memory
	void *shared_memory=shmat(shmid, (void *)0, 0);
	if(shared_memory==(void *)-1){
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}
	printf("Memory attached at %X\n", shared_memory);

	shared_use_st<int> *shared_stuff=(shared_use_st<int> *) shared_memory;
	
	//create semaphore
	int semid_empty=semget((key_t)4322, 1, 0666|IPC_CREAT);
	int semid_full=semget((key_t)4323, 1, 0666|IPC_CREAT);

	timeval t1, t2;
	//all things ready
	gettimeofday(&t1, NULL);
	int pointer=0;
	int counter=0;
	int getCh;
	while(1){
		++counter;
		semaphore_p(semid_full);
		getCh=shared_stuff->some_text[pointer];
		printf("%d\n", getCh);
		semaphore_v(semid_empty);
		pointer=(pointer+1)%TEXT_SZ;
		if(getCh==9999){
			break;
		}
	}
	gettimeofday(&t2, NULL);
	double elapsed_time=(t2.tv_sec-t1.tv_sec)+(t2.tv_usec-t1.tv_usec)*1e-6;
	printf("elapse: %fs\n", elapsed_time);
	///
	printf("counter=%d\n", counter);
	//detach shared memory
	shmdt(shared_memory);
}
























