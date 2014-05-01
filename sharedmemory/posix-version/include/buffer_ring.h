#ifndef __BUFFER_RING_H__
#define __BUFFER_RING_H__

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

const key_t SHM_KEY=7755;
const char SEM_FULL_KEY[]="xxx";
const char SEM_EMPTY_KEY[]="yyy";


template <class T>
class Buffer_Ring{
public:
	Buffer_Ring(int buffer_size, int message_size){
		this->buffer_size=buffer_size;
		this->message_size=message_size;
	}
	void init(){
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
		sem_empty_id=sem_open(SEM_FULL_KEY, O_CREAT, 0644, buffer_size/message_size);
		if(sem_empty_id==SEM_FAILED){
			fprintf(stderr, "sem_open failed!\n");
			exit(EXIT_FAILURE);
		}
		sem_full_id=sem_open(SEM_EMPTY_KEY, O_CREAT, 0644, 0);
		if(sem_full_id==SEM_FAILED){
			fprintf(stderr, "sem_open failed!\n");
			exit(EXIT_FAILURE);
		}
		
	}

	void write(T *message){
		sem_wait(sem_empty_id);
		for(int i=0; i<message_size; ++i){
			shared_stuff[pointer+i]=message[pointer];
		}
		sem_post(sem_full_id);
		pointer=(pointer+message_size)%buffer_size;
	}

	void read(T *message){
		sem_wait(sem_full_id);
		for(int i=0; i<message_size; ++i){
			message[pointer+i]=shared_stuff[pointer];
		}
		sem_post(sem_empty_id);
		pointer=(pointer+message_size)%buffer_size;
	}

	void close(){
		sleep(1);
		//delete semaphore
		sem_close(sem_empty_id);
		sem_close(sem_full_id);
		sem_unlink(SEM_EMPTY_KEY);
		sem_unlink(SEM_FULL_KEY);
		//detach shared memory
		if(shmdt(shared_memory)==-1){
			fprintf(stderr, "shmdt failed!\n");
			exit(EXIT_FAILURE);
		}
		//delete shared memory
		shmctl(shm_id, IPC_RMID, 0);
	}
	
private:
	int buffer_size;
	int message_size;
	int pointer;
	int shm_id;
	sem_t *sem_empty_id;
	sem_t *sem_full_id;
	void *shared_memory;
	T *shared_stuff;
};

#endif



