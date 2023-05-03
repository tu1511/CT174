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
void SelectionSort(recordtype a[], int n){
	int i, j, lowindex;
	keytype lowkey;
	for(i = 0; i <= n-2; i++){
		lowkey = a[i].key;
		lowindex = i;
		for(j = i+1; j <= n-1; j++)
			if(a[j].key < lowkey){
				lowkey = a[j].key;
				lowindex = j;
			}
		Swap(&a[i], &a[lowindex]);
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
	printf("Thuat toan SelectionSort:\n");
	read(a, &n);
	printf("Thuat toan truoc khi sap xep: \n");
	print(a, n);
	SelectionSort(a, n);
	printf("Thuat toan sau khi sap xep: \n");
	print(a, n);
	return 0;
}
