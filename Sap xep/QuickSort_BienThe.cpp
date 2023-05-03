#include <stdio.h>

typedef int keytype;
typedef float orthertype;
typedef struct{
	keytype key;
	orthertype otherfields;
}recordtype;
void Swap(recordtype *x, recordtype *y){
	recordtype temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
int FindPivot(recordtype a[], int i, int j){
	keytype firstkey;
	int k;
	k = i+1;
	firstkey = a[i].key;
	while(k <= j && a[k].key == firstkey)
		k++;
	if(k > j) return -1;
	if(a[k].key < firstkey) return k;
	return i;
}
int Partition(recordtype a[], int i, int j, keytype pivot){
	int L, R;
	L = i;
	R = j;
	while(L <= R){
		while(a[L].key <= pivot) L++;
		while(a[R].key > pivot) R--;
		if(L < R) Swap(&a[L], &a[R]);
	}
	return L;
}
void QuickSort(recordtype a[], int i, int j){
	keytype pivot;
	int pivotIndex, k;
	pivotIndex = FindPivot(a, i, j);
	if(pivotIndex != -1){
		pivot = a[pivotIndex].key;
		k = Partition(a, i, j, pivot);
		QuickSort(a, i, k-1);
		QuickSort(a, k, j);
	}
}
void read(recordtype a[], int *n){
	FILE *f;
	f = fopen("data.txt", "r");
	int i = 0;
	if(f!= NULL)
		while(!feof(f)){
			fscanf(f, "%d%f", &a[i].key, &a[i].otherfields);
			i++;
		}
	else
		printf("Loi mo file!\n");
	fclose(f);
	*n = i;
}
void print(recordtype a[], int n){
	int i;
	for(i = 0; i < n; i++)
		printf("%3d %5d %8.2f\n", i+1, a[i].key, a[i].otherfields);
}

int main(){
	recordtype a[100];
	int n;
	printf("Thuat toan QuickSort bien the: \n");
	read(a, &n);
	printf("Thuat toan truoc khi sap xep: \n");
	print(a, n);
	QuickSort(a, 0, n-1);
	printf("Thuat toan sau khi sap xep: \n");
	print(a, n);
	return 0;
}
