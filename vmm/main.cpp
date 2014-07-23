#include <iostream>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int pid = (int) getpid();
	std::cout<<"pid="<<pid<<std::endl;
	size_t pageSize=(size_t)sysconf(_SC_PAGESIZE);
	std::cout<<"page size="<<pageSize<<std::endl;
	size_t pageNum=(size_t)sysconf(_SC_PHYS_PAGES);
	std::cout<<"page num="<<pageNum<<std::endl;
	std::cout<<"memorySize="<<pageSize*pageNum/1024/1024/1024<<std::endl;
	size_t availPage=(size_t)sysconf(_SC_AVPHYS_PAGES);
	std::cout<<"avail page num="<<availPage<<std::endl;
	std::cout<<"availSize="<<pageSize*availPage/1024/1024/1024<<std::endl;
	std::cout<<"num cores="<<(size_t)sysconf(_SC_NPROCESSORS_CONF)<<std::endl;
	std::cout<<"num avail="<<(size_t)sysconf(_SC_NPROCESSORS_ONLN)<<std::endl;
	
}
