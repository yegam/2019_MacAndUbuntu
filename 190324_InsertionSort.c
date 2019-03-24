#include<stdio.h>

void InsertionSort(int* arr);

int main(){
	int i;
	int arr[10]={9,2,10,6,3,18,1,7,5,4};
	for(i=0;i<10;i++)
		printf("%d ",arr[i]);
	printf("\n");

	InsertionSort(arr);

	for(i=0;i<10;i++)
		printf("%d ",arr[i]);
	printf("\n");
	return 0;
}
void InsertionSort(int* arr){
	int i,j,key;
	for(j=1;j<10;j++){
		key = arr[j];
		i=j-1;
		while(i>=0 && arr[i]>key){
			arr[i+1] = arr[i];
			i--;	
		}
		arr[i+1] = key;
	}
}
