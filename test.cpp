#include <cstdio>
using namespace std;

int main(){
	char test[10];
	char sndCh='a';
	for(int i=0; i<26; ++i){
		test[i%10]=sndCh;
		printf("%s\n", test);
		sndCh++;
	}

}
