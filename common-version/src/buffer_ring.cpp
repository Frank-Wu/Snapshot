#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <unistd.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <errno.h>

#include "buffer_ring.h"

struct Buffer_Ring_HDR{
	volatile unsigned long flags;
	volatile unsigned long r_idx;
	volatile unsigned long w_idx;
};

struct Buffer_Ring{
	int shmid;
	int semid;
	unsigned long size;
	unsigned long flags;
	Buffer_Ring_HDR *hdr;
	char *shm;
	char *shm_e;
};

union semun{
	int val;
	struct semid_ds *buf;
	ushort *array;
};
