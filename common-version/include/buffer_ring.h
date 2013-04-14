#ifndef __BUFFER_RING_H__
#define __BUFFER_RING_H__

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/time.h>

const key_t SHM_KEY=9000;
const key_t SEM_FULL_KEY=9001;
const key_t SEM_EMPTY_KEY=9002;

union semun{
	int val;
	semid_ds *buf;
	unsigned short *array;
};

template <class T>
class Buffer_Ring{
public:
	Buffer_Ring(int buffer_size){
		this->buffer_size=buffer_size;
	}
	void consumer_init(){
		pointer=0;
		//create shared memory
		shm_id=shmget(SHM_KEY, buffer_size*sizeof(T), 0666|IPC_CREAT);
		if(shm_id==-1){
			fprintf(stderr, "shmget failed!\n");
			exit(EXIT_FAILURE);
		}

		//attach shared memory
		shared_memory=shmat(shm_id, (void *)0, 0);
		if(shared_memory==(void *)-1){
			fprintf(stderr, "shmat failed!\n");
			exit(EXIT_FAILURE);
		}
		shared_stuff=(T *)shared_memory;

		//create semaphore
		sem_empty_id=semget(SEM_EMPTY_KEY, 1, 0666|IPC_CREAT);
		sem_full_id=semget(SEM_FULL_KEY, 1, 0666|IPC_CREAT);
		sem_p.sem_num=0;
		sem_p.sem_op=-1;
		sem_p.sem_flg=SEM_UNDO;
		sem_v.sem_num=0;
		sem_v.sem_op=1;
		sem_v.sem_flg=SEM_UNDO;
	}

	void producer_init(){
		//all things consumer done should be done
		consumer_init();
		//set semaphore
		semun sem_empty_union;
		sem_empty_union.val=buffer_size;
		semctl(sem_empty_id, 0, SETVAL, sem_empty_union);
		semun sem_full_union;
		sem_full_union.val=0;
		semctl(sem_full_id, 0, SETVAL, sem_full_union);
	}

	void producer_write(T value){
		semop(sem_empty_id, &sem_p, 1);
		shared_stuff[pointer]=value;
		semop(sem_full_id, &sem_v, 1);
		pointer=(pointer+1)%buffer_size;
	}

	T consumer_read(){
		int temp;
		semop(sem_full_id, &sem_p, 1);
		temp=shared_stuff[pointer];
		semop(sem_empty_id, &sem_v, 1);
		pointer=(pointer+1)%buffer_size;
		return temp;
	}

	void consumer_close(){
		//delete semaphore
		semun sem_del_union;
		semctl(sem_empty_id, 0, IPC_RMID, sem_del_union);
		semctl(sem_full_id, 0, IPC_RMID, sem_del_union);
		//detach shared memory
		if(shmdt(shared_memory)==-1){
			fprintf(stderr, "shmdt failed!\n");
			exit(EXIT_FAILURE);
		}
		//delete shared memory
		if(shmctl(shm_id, IPC_RMID, 0)==-1){
			fprintf(stderr, "shm delete failed!\n");
			exit(EXIT_FAILURE);
		}
	}
	
	void producer_close(){
		sleep(1);
		//detach shared memory
		if(shmdt(shared_memory)==-1){
			fprintf(stderr, "shmdt failed!\n");
			exit(EXIT_FAILURE);
		}
	}

private:
	int buffer_size;
	int pointer;
	int shm_id;
	int sem_empty_id;
	int sem_full_id;
	sembuf sem_p;
	sembuf sem_v;
	void *shared_memory;
	T *shared_stuff;
};

#endif



