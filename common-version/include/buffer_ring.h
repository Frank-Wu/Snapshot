#ifndef __BUFFER_RING_H__
#define __BUFFER_RING_H__

#define RB_MODE_RD 1
#define RB_MODE_WR 2

extern int buffer_ring_init(void *p_cfg);
extern int buffer_ring_open(int id, unsigned long size, unsigned long flags);
extern int buffer_ring_close(int *p_desc);
extern int buffer_ring_write(int desc, char *buf, unsigned long len);
extern int buffer_ring_read(int desc, char *buf, unsigned long len);

#endif
