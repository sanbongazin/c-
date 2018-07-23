/*
H30-DFT2 
２次元配列の離散フーリエ変換のプログラム
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define Nx 16 /* データ数*/ 
#define Ny 16 /* データ数*/ 

#define pi (4.0*atan(1))


int main(void){
FILE *inim2, *DFT2, *IDFT2; 
	
double mx[Ny][Nx];/*m[Ny][Nx]とすると, 整数のmとかぶるので mxとした*/
double Rm[Ny][Nx], Im[Ny][Nx];
double Rc[Ny][Nx], Ic[Ny][Nx];			
double Rtemp[Ny][Nx],Itemp[Ny][Nx]; 
	

	
int i,j,l,m; /* i,j が実空間のx成分,y成分, l,m がフーリエ空間のx成分,y成分に対応*/
	
inim2=fopen("inim2.dat","r");
DFT2=fopen("DFT2.dat","w");
IDFT2=fopen("IDFT2.dat","w");
	
/*２次元配列データファイル inim2.datをmx[j][i]に読み込ませる*/
 for (j=0;j<Ny;j++){
  for (i=0; i<Nx;i++){
 fscanf(inim2,"%lf",&mx[j][i]);
  }
	}
	
/*他の配列は全てゼロを入れておく*/
 for (j=0;j<Ny;j++){
  for (i=0; i<Nx;i++){
 Rm[j][i]=0.0;
 Im[j][i]=0.0;
 Rc[j][i]=0.0;
 Ic[j][i]=0.0;
 Rtemp[j][i]=0.0;
 Itemp[j][i]=0.0;
 }
  }
	

/*x成分をDFT*/
for (j=0;j<Ny;j++){
 for (l=0;l<Nx;l++){
  for (i=0;i<Nx;i++){
 Rtemp[j][l] +=  mx[j][i]*cos(2.0*pi*i*l/Nx);
 Itemp[j][l] += -mx[j][i]*sin(2.0*pi*i*l/Nx);
			}
		}
	}
	
	
/*y成分をDFT*/
for (l=0;l<Nx;l++){
 for (m=0;m<Ny;m++){
  for (j=0;j<Ny;j++){
 Rc[m][l] += Rtemp[j][l]*cos(2.0*pi*j*m/Ny)+Itemp[j][l]*sin(2.0*pi*j*m/Ny);
 Ic[m][l] += -Rtemp[j][l]*sin(2.0*pi*j*m/Ny)+Itemp[j][l]*cos(2.0*pi*j*m/Ny);
			}
		}
	}
	
	
/*フーリエ成分の配列をDFT2.datに書き込む*/
	
for(m=0;m<Ny;m++){
 for(l=0;l<Nx;l++){
fprintf(DFT2, "%f %f\n", Rc[m][l],Ic[m][l]);
}}


	/*temporary配列をリセット*/
	
 for (j=0;j<Ny;j++){
  for (i=0; i<Nx;i++){
 Rtemp[j][i]=0.0;
 Itemp[j][i]=0.0;
 }
  }
	
	
/*逆DFTで元のデータにもどるかチェック*/
	
	/*x成分を逆DFT*/
for(m=0;m<Ny;m++){
 for(i=0;i<Nx;i++){
  for(l=0;l<Nx;l++){
  Rtemp[m][i] += Rc[m][l]*cos(2.0*pi*i*l/Nx)-Ic[m][l]*sin(2.0*pi*i*l/Nx);
  Itemp[m][i] += Rc[m][l]*sin(2.0*pi*i*l/Nx)+Ic[m][l]*cos(2.0*pi*i*l/Nx);
  }
  Rtemp[m][i] = Rtemp[m][i]/Nx;
  Itemp[m][i] = Itemp[m][i]/Nx;
  printf("%f %f\n", Rtemp[m][i],Itemp[m][i]);
  }}
	
	
	/*y成分をDFT*/
for(i=0;i<Nx;i++){
 for(j=0;j<Ny;j++){
  for(m=0;m<Ny;m++){
  Rm[j][i]+= Rtemp[m][i]*cos(2.0*pi*j*m/Ny)-Itemp[m][i]*sin(2.0*pi*j*m/Ny);
  Im[j][i]+= Rtemp[m][i]*sin(2.0*pi*j*m/Ny)+Itemp[m][i]*cos(2.0*pi*j*m/Ny);
  }
  Rm[j][i] = Rm[j][i]/Ny;
  Im[j][i] = Im[j][i]/Ny;
  printf("%f %f\n", Rm[j][i],Im[j][i]);
   }}
	
	/*逆変換のデータをIDFT2.datに書き込む*/
for(j=0;j<Ny;j++){
 for(i=0;i<Nx;i++){
fprintf(IDFT2, "%f %f\n", Rm[j][i], Im[j][i]);
		}
	}

	/*inim2.datのデータとIDFT2.datのデータが一致している, かつ, IDFT2.datの虚部が全てゼロであればo.k. */






fclose(inim2);
fclose(DFT2);
fclose(IDFT2);

	return 0;
}
