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
void InsertionSort(recordtype a[], int n){
	int i, j;
	for(i = 1; i <= n-1; i++){
		j = i;
		while(j > 0 && a[j].key < a[j-1].key){
			Swap(&a[j], &a[j-1]);
			j--;
		}
	
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
	printf("Thuat toan InsertionSort:\n");
	read(a, &n);
	printf("Thuat toan truoc khi sap xep: \n");
	print(a, n);
	InsertionSort(a, n);
	printf("Thuat toan sau khi sap xep: \n");
	print(a, n);
	return 0;
}
