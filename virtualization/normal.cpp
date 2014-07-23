#include <cstdlib>
#include <cstring>
#include <cstdio>

int main(){
	int *a=new int[100000000];
	memset(a, 0, sizeof(int)*100000000);
	printf("size=%d\n", sizeof(int)*100000000/1024/1024);
	getchar();
}
