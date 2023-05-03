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
void BubbleSort(recordtype a[], int n){
	int i, j, temp;
	for(i = 0; i <= n-2; i++){
		for(j = n-1; j >= i+1; j--)
			if(a[j - 1].key > a[j].key)
				Swap(&a[j-1], &a[j]);
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
	printf("Thuat toan BubbleSort:\n");
	read(a, &n);
	printf("Thuat toan truoc khi sap xep: \n");
	print(a, n);
	BubbleSort(a, n);
	printf("Thuat toan sau khi sap xep: \n");
	print(a, n);
	return 0;
}
