#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/time.h>

#define TEXT_SZ 5

template <class T>
struct shared_use_st{
	T some_text[TEXT_SZ];
};

union semun{
	int val;
	semid_ds *buf;
	unsigned short *array;
};

static void semaphore_p(int semid){
	sembuf sem_b;
	sem_b.sem_num=0;
	sem_b.sem_op=-1;
	sem_b.sem_flg=SEM_UNDO;
	semop(semid, &sem_b, 1);
}

static void semaphore_v(int semid){
	sembuf sem_b;
	sem_b.sem_num=0;
	sem_b.sem_op=1;
	sem_b.sem_flg=SEM_UNDO;
	semop(semid, &sem_b, 1);
}


