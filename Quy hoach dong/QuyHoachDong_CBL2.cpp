#include <stdio.h>
#include <malloc.h>

typedef struct{
	char tenDV[50];
	int TL, GT, PA, SL;
}DoVat;
typedef int bang[50][100];
DoVat *ReadFile(int *W, int *n){
	FILE *f = fopen("CBL2.txt", "r");
	fscanf(f, "%d", W);
	DoVat *dsdv;
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i=0;
 	 while (!feof(f)){
	   fscanf(f, "%d%d%d%[^\n]",&dsdv[i].TL,&dsdv[i].GT, &dsdv[i].SL, &dsdv[i].tenDV);
	   dsdv[i].PA=0;
	   i++;
	   dsdv=(DoVat*)realloc(dsdv,sizeof(DoVat)*(i+1));  
	 }
	 *n=i;
     fclose(f);
     return dsdv;
}
void InDSDV(DoVat *dsdv ,int n, int W){
	int i, TongTL=0, TongGT=0;
	printf("\nPhuong an Cai Ba lo 2 dung thuat toan QUY HOACH DONG nhu sau:\n");
		printf("|---|------------------|----------|---------|---------|-----------|\n");
		printf("|STT|     Ten Do Vat   | T Luong  | Gia Tri |So luong | Phuong an |\n");
		printf("|---|------------------|----------|---------|---------|-----------|\n");
	for(i=0;i<n;i++){
		printf("|%2d |%-18s|%5d     |%5d    |    %d    |%6d     |\n",
		i+1,dsdv[i].tenDV,dsdv[i].TL,dsdv[i].GT, dsdv[i].SL,dsdv[i].PA);
		TongTL=TongTL+dsdv[i].PA * dsdv[i].TL;
		TongGT=TongGT+dsdv[i].PA * dsdv[i].GT;
	}	
	printf("|---|------------------|----------|---------|---------|-----------|\n");	
	printf("Trong luong cua ba lo = %-9d\n",W);
	printf("Tong trong luong = %-9d\n",TongTL);
	printf("Tong gia tri = %-9d\n",TongGT);
}
int min(int a, int b){
	return a<b?a:b;
}
void TaoBang(DoVat *dsdv, int n, int W, bang F, bang X){
	int xk, yk, k;
 	int FMax, XMax, V;
 	for(V= 0; V<=W; V++) {
 		X[0][V] = min(V/dsdv[0].TL, dsdv[0].SL);
 		F[0][V] = X[0][V] * dsdv[0].GT;
 	}
 	
 	for(k= 1; k<n; k++)
		 for(V=0; V<=W; V++) {
			 FMax = F[k-1][V] ;
			 XMax = 0;
			 yk = min(V/dsdv[k].TL, dsdv[k].SL);
			 for(xk = 1; xk<=yk; xk++)
			 	if(F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT>FMax){
			 		FMax=F[k-1][V-xk*dsdv[k].TL]+xk*dsdv[k].GT;
			 		XMax= xk;
			 	}
			 F[k][V] = FMax;
			 X[k][V] = XMax;
	 	}
}
void InBang(int n, int W, bang F, bang X){
	int V, k;
	for(V = 0; V <= W; V++)
		printf("|   %d  ", V);
	printf("\n");
	for(k=0; k<n; k++){
		for(V=0; V<=W; V++)
		 	printf("|%4d%2d",F[k][V], X[k][V]);
		printf("\n");
	}
}

void TraBang(DoVat *dsdv, int n, int W, bang X) {
	int k, V;
	V = W;
	for(k= n-1; k>=0; k--) {
	 	dsdv[k].PA = X[k][V];
	 	V = V - X[k][V] * dsdv[k].TL;
	}
}
int main(){
	int n, W;
	bang X,F;
	DoVat *dsdv;
	dsdv=ReadFile(&W, &n);
	
	TaoBang(dsdv,n,W,F,X);
	InBang(n,W,F,X);
	printf("\n");
	TraBang(dsdv,n,W,X);
	InDSDV(dsdv,n,W);
	
	free(dsdv);
	return 0;
}
