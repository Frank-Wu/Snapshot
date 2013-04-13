#include "shm_com.h"

int main(){
	srand(time(NULL));
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
	//set semaphore
	semun sem_empty_union;
	sem_empty_union.val=TEXT_SZ;
	semctl(semid_empty, 0, SETVAL, sem_empty_union);
	semun sem_full_union;
	sem_full_union.val=0;
	semctl(semid_full, 0, SETVAL, sem_full_union);

	//all things ready
	int pointer =0;
	int sndCh=0;
	while(1){
		sndCh=rand()%32767;
		semaphore_p(semid_empty);
		shared_stuff->some_text[pointer]=sndCh;
		printf("%d\n", sndCh);
		semaphore_v(semid_full);
		pointer=(pointer+1)%TEXT_SZ;
		if(sndCh==9999){
			break;
		}
	}
	sleep(5);
	///
	//delete semaphore
	semun sem_del_union;
	semctl(semid_empty, 0, IPC_RMID, sem_del_union);
	semctl(semid_full, 0, IPC_RMID, sem_del_union);
	
	//detach shared memory
	shmdt(shared_memory);
	//delete shared memory
	if(shmctl(shmid, IPC_RMID, 0)==-1){
		printf("unsuccessful!!");
	}
}




















