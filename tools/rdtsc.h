#pragma once
#ifndef __RDTSC_H__
#define __RDTSC_H__
#include <cstdlib>

#if defined(__i386__)
__inline__ unsigned long long rdtsc(void){
	unsigned long long int x;
	__asm__ volatile (".byte 0x0f, 0x31":"=A"(x));
	return x;
}
#elif defined(__x86_64__)
__inline__ unsigned long long rdtsc(void){
	unsigned hi, lo;
	__asm__ __volatile__ ("rdtsc":"=a"(lo), "=d"(hi));
	return ((unsigned long long)lo)|(((unsigned long long)hi)<<32);
}
#endif

//cpu_mhz: can be obtained by "cat /proc/cpuinfo"
static float get_run_time(const int &start, const int &end, const float &cpu_mhz){
	return (end-start)/(cpu_mhz*1000*1000);
}
#endif
