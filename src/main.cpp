#include "generator.h"

int main(int argc,char *argv[]){
	int times;
	if((times = getTimes(argc,argv)) == -1)return 1;
	srand((unsigned)time(NULL));
	loop_build(times);
	system("pause");
	return 0;
}
