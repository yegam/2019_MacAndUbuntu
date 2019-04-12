int partition(int* arr,int p, int r){
	int i,j,temp,x = arr[r];
	i = p-1;
	for(j = p ;j<r;j++){
		if(arr[j]<=x){
			i++;
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}
	temp = arr[i+1];
	arr[i+1] = arr[r];
	arr[r] = temp; 
	return i+1;
}

void quickSortMain(int* arr,int p,int r){
	int q;
	if( p < r ){
		q = partition(arr,p,r);
		quickSortMain(arr,p,q-1);
		quickSortMain(arr,q+1,r);
	}
}

void quickSort(int* arr, int size){
	quickSortMain(arr,0,size-1);
}
