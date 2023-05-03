#include <stdio.h>
#define size 50

void ReadFile(int a[][size], int *n){
	FILE *f = fopen("tamgiacso.txt", "r");
	if(f==NULL){
		printf("File rong!\n");
		return;
	}
	int i =0, j;
	while(!feof(f)){
		for(j = 0; j <= i; j++){
			fscanf(f, "%d", &a[i][j]);			
		}
		i++;
	}
	*n = i;
	fclose(f);
}
void Print(int a[][size], int n){
	int i, j;
	printf("Tam giac so: \n");
	for(i = 0; i < n; i++){
		for(j = 0; j <= i; j++)
			printf("%3d", a[i][j]);
		printf("\n");
	}
}
int CS_max(int F[][size], int i, int j){
	if(j == 0)
		return (F[i-1][0]>F[i-1][1]?0:1);
	if(j == i)
		return i-1;
	if(j == i-1)
		return (F[i-1][i-2]>F[i-1][i-1])? i-2:i-1;
	if (F[i-1][j-1]>F[i-1][j]&&F[i-1][j-1]>F[i-1][j+1])
		return j-1;
	if (F[i-1][j]>F[i-1][j-1]&&F[i-1][j]>F[i-1][j+1])
		return j;
	if (F[i-1][j+1]>F[i-1][j]&&F[i-1][j+1]>F[i-1][j-1])
		return j+1;
}
void TaoBang(int a[][size], int n , int F[][size]){
	int i, j;
	F[0][0] = a[0][0];
	F[1][0] = a[1][0] + F[0][0];
	F[1][1]= a[1][1] + F[0][0];
	for (i=2; i<n; i++)
		for (j=0; j<=i; j++){
			int k=CS_max(F,i,j);
				F[i][j] = a[i][j]+ F[i-1][k];
		} 
}
void In_Bang(int n, int F[][size]){
	int i, j;
	printf("\nBang F\n");
	for(i=0; i<n; i++){
		for(j=0; j<=i; j++)
		 	printf("%3d", F[i][j]);
		printf("\n");
	}
}
int CS_max_dong_cuoi(int F[], int j){
	int max = F[0], temp = 0, i;
	for(i = 0; i <=j; i++)
		if(max < F[i]){
			max = F[i];
			temp = i;
		}
	return temp;
}
void TraBang(int a[][size], int n, int F[][size], int PA[]){
	int i, j;
	j = CS_max_dong_cuoi(F[n-1], n-1);
	PA[n-1] = a[n-1][j];
	for(i = n-1; i >=1; i--){
		j = CS_max(F, i, j);
		PA[n-1] = a[i-1][j];
	}
}
int giaPA(int PA[], int n){
	int i, sum = 0;
	for(i = 0; i <n; i++)
		sum+=PA[i];
	return sum;
}
void printPA(int PA[], int n){
	int i;
	printf("Phuong an: \n");
	printf("%d", PA[0]);
	for(i = 1; i < n; i++)
		printf(" -> %d", PA[i]);
	printf("Tong cac so tren duong di: %d\n", giaPA(PA, n));
}
int main(){
	int a[size][size];
	int n;
	ReadFile(a, &n);
	Print(a, n);
	int PA[n];
	int F[n][size];
	
	return 0;
}
