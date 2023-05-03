#include <stdio.h>
#define size 30

/*Khai bao*/
typedef struct {
	float do_dai;
	int dau, cuoi;
	int da_dung;
} canh;

void read_file(char file_name[], canh a[][size], int *n){
	int i,j;
	FILE *f;
	f=fopen(file_name, "r");
	if (f==NULL){
		printf("Loi mo file!!!\n");
		return;
	}
	
	fscanf(f,"%d",n); // Doc so dinh cua do thi n
	
	for(i=0; i<*n; i++)
		for(j=0; j<*n; j++){
			fscanf(f,"%f",&a[i][j].do_dai); 
				a[i][j].dau=i;
				a[i][j].cuoi=j;
				a[i][j].da_dung=0;;
			}
	fclose(f);
}

void in_ma_tran(canh a[][size], int n){
	int i,j;
	printf("\nMa tran TRONG SO cua do thi\n");
	for(i=0; i<n; i++){
		for(j=0; j<n; j++)
			printf(" %c%c =%5.2f  ",a[i][j].dau+97, a[i][j].cuoi+97, a[i][j].do_dai);
		printf("\n");
	}
}

void in_PA(canh PA[], int n){
	int i;
	float sum=0.0;
	printf("\nPHUONG AN TIM DUOC:\n");
	for(i=0; i<n; i++){
		sum+= PA[i].do_dai;
		printf(" Canh %c%c = %5.2f\n", PA[i].dau+97, PA[i].cuoi+97, PA[i].do_dai);
    }  
    printf("CHU TRINH : ");
	for(i=0; i<n; i++){
		printf("%c",PA[i].dau+97);
		printf("-> ");
    }  
	printf("%c",PA[0].dau+97);    
	printf("\nTong do dai cac canh cua chu trinh = %5.2f\n", sum);
}

// Tim canh nho nhat trong so cac canh chua them vao chu trinh

float canh_NN(canh a[][size], int n){
	float Cmin=3.40282e+38;
	int i,j;
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
			if(i!=j && !a[i][j].da_dung && a[i][j].do_dai<Cmin)	
				Cmin= a[i][j].do_dai;
	return Cmin;
}
	
float can_duoi(canh a[][size], float TGT, int n, int i){
	
	return TGT+ (n-i)*canh_NN(a,n);
}

// Ghi nhan phuong an tot nhat tam thoi

void Cap_Nhat_PA_TNTT(canh a[][size], int n, float TGT, float *GNNTT, canh x[], canh PA[]){
	 int i;
	 // mang x da co n-1 canh tu x[0] den x[n-2]
	 x[n-1]=a[x[n-2].cuoi][x[0].dau]; // Noi dinh cuoi cua x[n-2] voi dinh dau cua x[0] de co chu trinh
	 TGT= TGT + x[n-1].do_dai;		// Cong them vao TGT do dai cua canh noi dinh cuoi voi dinh dau
	 	 if(*GNNTT > TGT){
		 *GNNTT = TGT;
		 for(i=0; i<n; i++)
		 	PA[i]=x[i];
	 }
}
	
// Gia su ta co mot phuong an thanh phan x, voi k canh
// Neu ta di toi dinh ke_tiep ma dinh ke_tiep nay trung voi mot dinh dau cua mot canh nao do
// thi tao thanh chu trinh

int co_chu_trinh(canh x[], int k, int ke_tiep){
	int i=0, co_CT=0;
	while (i<k && !co_CT)
		if(ke_tiep==x[i].dau) co_CT=1;
		else i++;
	return co_CT;
}

void Nhanh_Can(canh a[][size], int n, int i, int dau, float *TGT, float *CD, float *GNNTT, canh x[], canh PA[]){
	 int j; 	// j la dinh ke tiep 
	 for(j=0; j<n; j++) 	
		
		if (dau!=j && !a[dau][j].da_dung && !co_chu_trinh(x,i,j)){
		// Ung voi mot gia tri cua j la mot nut tren cay 
	 	// Tinh 2 dai luong cua mot nut trong
	 		
		 *TGT = *TGT + a[dau][j].do_dai;
		 *CD = can_duoi(a, *TGT, n, i+1);
		  if(*CD < *GNNTT){ 	// Neu CD >= GNNTT thi cat tia 
		  // Neu khong co dieu kien nay thi chuong trinh la VET CAN
		  	x[i] = a[dau][j];
		  	a[dau][j].da_dung=1;
		  	a[j][dau].da_dung=1;
		  	
		   	if(i==n-2) { // Da xet het tat ca cac dinh nhung duong di moi co n-1 canh
			   	Cap_Nhat_PA_TNTT(a, n, *TGT, GNNTT, x, PA);
	    	}   	
		 	else
		 		Nhanh_Can(a, n, i+1, j, TGT, CD, GNNTT, x, PA); //Xet nut con cua nut i
	 	}
	 // Quay lui xet nut khac (ung voi gia tri khac cua j)
	 *TGT = *TGT - a[dau][j].do_dai;	// Tra lai Tong gia tri cua nut cha
	 a[dau][j].da_dung=0;	// Tra lai Canh vua xet la chua su dung	 
	 a[j][dau].da_dung=0;
    }	
}
	
//void reset(canh a[][size], int n){
//	int i,j;
//	for(i=0; i<n; i++)
//		for(j=0; j<n; j++)
//			a[i][j].da_dung=0;
//}
	
int main(){
	canh a[size][size];
	int n;
	printf("\nPhuong an TSP dung thuat toan NHANH CAN:\n");
	read_file("TSP1.txt",a,&n);
	canh PA[n];
	canh x[n];
	char tpxp, yn;
	//while (1){
		fflush(stdin);
		in_ma_tran(a,n);
		float TGT=0.0, CD = 0.0, GNNTT = 3.40282e+38;
		printf("\nXuat phat tu thanh pho nao? ");
		printf("\n Nhap mot trong cac thanh pho tu a den %c: ", n-1+97);
		scanf("%c", &tpxp);
		Nhanh_Can(a, n, 0, tpxp-97, &TGT, &CD, &GNNTT, x, PA);
		in_PA(PA,n);
		fflush(stdin);
//		printf("\nTiep tuc Y/N? ");
//		scanf("%c", &yn);
//		if (yn == 'N' || yn == 'n')
//			break;
//		reset(a,n);
//    }	    	
	return 0;
}

