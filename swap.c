#include <stdio.h>

void swap(int& a, int& b){
	int temp;
	temp =a;
	a = b;
	b=temp;
}

int main(){
	int a,b;
	a = 10;
	b = 20;
	printf("before swap a= %d b= %d ",a,b);
	swap(a,b);
	printf("after swap a= %d b= %d ",a,b);

	return 0;
}
