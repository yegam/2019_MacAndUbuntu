#include <stdio.h>
#include <unistd.h>

int main(){
	printf("Before exec() call\n");
	execl("/bin/ls","ls","-l",(char*)0);
	printf("After exec() call\n");
	return 0;
}
