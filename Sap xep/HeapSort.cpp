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
void PushDown(recordtype a[], int first, int last){
	int r = first;
	while(r <= (last-1)/2)
		if(last == 2*r+1){
			if(a[r].key < a[last].key) Swap(&a[r], &a[last]);
			r = last;
		}
		else
			if(a[r].key < a[2*r+1].key && a[2*r+1].key >= a[2*r+2].key){
				Swap(&a[r], &a[2*r+1]);
				r = 2*r+1;
			}else
				if(a[r].key < a[2*r+2].key){
					Swap(&a[r], &a[r*2+2]);
					r = r*2+2;
				}
				else
					r = last;
}
void HeapSort(recordtype a[], int n){
	int i;
	for(i = (n-2)/2; i >= 0; i--)
		PushDown(a, i, n-1);
	for(i = n-1; i >= 2; i--){
		Swap(&a[0], &a[i]);
		PushDown(a, 0, i-1);
	}
	Swap(&a[0], &a[1]);
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
	printf("Thuat toan HeapSort:\n");
	read(a, &n);
	printf("Thuat toan truoc khi sap xep: \n");
	print(a, n);
	HeapSort(a, n);
	printf("Thuat toan sau khi sap xep: \n");
	print(a, n);
	return 0;
}
