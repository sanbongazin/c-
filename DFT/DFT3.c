/*
H30-DFT2 
２次元配列の離散フーリエ変換のプログラム
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define Nx 8 /* データ数*/ 
#define Ny 8 /* データ数*/ 
#define Nz 8 /* データ数*/ 
#define pi (4.0*atan(1))


int main(void){
FILE *inim2, *DFT3, *IDFT3,*X1,*Y1,*Z1,*X2,*Y2; 
	
double mx[Nz][Ny][Nx];/*m[Nz][Ny][Nx]とすると, 整数のmとかぶるので mxとした*/
double Rm[Nz][Ny][Nx], Im[Nz][Ny][Nx];
double Rc[Nz][Ny][Nx], Ic[Nz][Ny][Nx];			
double Rtemp[Nz][Ny][Nx],Itemp[Nz][Ny][Nx]; 
double Ra[Nz][Ny][Nx], Ia[Nz][Ny][Nx];

	
int i,j,k,l,m,n; /* i,j,k が実空間のx成分,y成分,z成分 l,m,n がフーリエ空間のx成分,y成分,z成分に対応*/
	
inim2=fopen("inim2.dat","r");
DFT3=fopen("DFT3.dat","w");
IDFT3=fopen("IDFT3.dat","w");
	X1=fopen("X1.dat","w");
	Y1=fopen("Y1.dat","w");
	Z1=fopen("Z1.dat","w");
	X2=fopen("X2.dat","w");
	Y2=fopen("Y2.dat","w");
/*２次元配列データファイル inim2.datをmx[j][i][k]に読み込ませる*/
	for (k=0; k<Nz;k++){
		for (j=0;j<Ny;j++){
		for (i=0; i<Nx;i++){
 fscanf(inim2,"%lf",&mx[k][j][i]);
  }
	}
	}

	
/*他の配列は全てゼロを入れておく*/
	for(k=0;k<Nz;k++){
		for (j=0;j<Ny;j++){
			for (i=0; i<Nx;i++){
 Rm[k][j][i]=0.0;
 Im[k][j][i]=0.0;
 Rc[k][j][i]=0.0;
 Ic[k][j][i]=0.0;
 Rtemp[k][j][i]=0.0;
 Itemp[k][j][i]=0.0;
 Ra[k][j][i]=0.0;
 Ia[k][j][i]=0.0;
 }
  }
	}

/*x成分をDFT*/
	for(k=0;k<Nz;k++){
	for (j=0;j<Ny;j++){
	for (l=0;l<Nx;l++){
	for (i=0;i<Nx;i++){
 Rtemp[k][j][l] +=  mx[k][j][i]*cos(2.0*pi*i*l/Nx);
 Itemp[k][j][l] += -mx[k][j][i]*sin(2.0*pi*i*l/Nx);
				fprintf(X1,"%f %f\n", Rtemp[k][j][l],Itemp[k][j][l]);	}
		}
	}
	}
	
/*y成分をDFT*/
	for (l=0;l<Nx;l++){
		for (k=0;k<Nz;k++){
			for (m=0;m<Ny;m++){
				for (j=0;j<Ny;j++){
 Rc[k][m][l] += Rtemp[k][j][l]*cos(2.0*pi*j*m/Ny)+Itemp[k][j][l]*sin(2.0*pi*j*m/Ny);
 Ic[k][m][l] += -Rtemp[k][j][l]*sin(2.0*pi*j*m/Ny)+Itemp[k][j][l]*cos(2.0*pi*j*m/Ny);
					fprintf(Y1,"%f %f\n", Rc[k][m][l],Ic[k][m][l]);
				}
		}
	}
	}
		
/*z成分をDFT*/
	for (m=0;m<Ny;m++){
		for(l=0;l<Nx;l++){
			for(n=0;n<Nz;n++){
				for(k=0;k<Nz;k++){
	Ra[n][m][l] += Rc[k][m][l]*cos(2.0*pi*k*m/Ny)+Ic[k][m][l]*sin(2.0*pi*k*m/Ny);
	Ia[n][m][l] += -Rc[k][m][l]*sin(2.0*pi*k*m/Ny)+Ic[k][m][l]*cos(2.0*pi*k*m/Ny);
					fprintf(Z1,"%f %f\n", Ra[n][m][l],Ia[n][m][l]);
				}
			}
		}
	}
		
	/*フーリエ成分の配列をDFT3.datに書き込む*/
	for(n=0;n<Nz;n++){
		for(m=0;m<Ny;m++){
			for(l=0;l<Nx;l++){
				fprintf(DFT3, "%f %f\n", Ra[n][m][l],Ia[n][m][l]);
	}}}

	/*temporary配列をリセット*/
	for (k=0;k<Nz;k++){
		for (j=0;j<Ny;j++){
			for (i=0; i<Nx;i++){
				Rc[k][m][l]=0.0;
				Ic[k][m][l]=0.0;
				Rtemp[n][m][l]=0.0;
				Itemp[n][m][l]=0.0;
			}
		}
	}
	
/*逆DFTで元のデータにもどるかチェック*/
	
	/*x成分を逆DFT*/
	for(n=0;n<Nz;n++){
	for(m=0;m<Ny;m++){
	for(l=0;l<Nx;l++){
	for(i=0;i<Nx;i++){
	Rc[n][m][l] += Ra[n][m][l]*cos(2.0*pi*i*l/Nx)-Ia[n][m][l]*sin(2.0*pi*i*l/Nx);
	Ic[n][m][l] += Ra[n][m][l]*sin(2.0*pi*i*l/Nx)+Ia[n][m][l]*cos(2.0*pi*i*l/Nx);
  }
				Rc[n][m][l] = Rc[n][m][l]/
				Nx;
  Ic[n][m][l] = Ic[n][m][l]/Nx;
	fprintf(X2,"%f %f\n", Rc[n][m][l],Ic[n][m][l]);
	}}}
	
	
	/*y成分を逆DFT*/
	for(l=0;l<Nx;l++){
	for(n=0;n<Nz;n++){
	for(m=0;m<Ny;m++){
	for(j=0;j<Ny;j++){
	Rtemp[k][j][l]+= Rc[n][m][l]*cos(2.0*pi*j*m/Ny)-Ic[n][m][l]*sin(2.0*pi*j*m/Ny);
	Itemp[k][j][l]+= Rc[n][m][l]*sin(2.0*pi*j*m/Ny)+Ic[n][m][l]*cos(2.0*pi*j*m/Ny);
  }
	Rtemp[k][j][l] = Rtemp[k][j][l]/Ny;
	Itemp[k][j][l] = Itemp[k][j][l]/Ny;
	fprintf(Y2,"%f %f\n", Rtemp[k][j][l],Itemp[k][j][l]);
	}}}
				
	/*z成分をDFT*/
		for(i=0;i<Ny;i++){
		for(i=0;i<Nx;i++){
		for(k=0;k<Nz;k++){
		for(n=0;m<Nz;n++){
	Rm[k][j][i]+= Rtemp[k][j][l]*cos(2.0*pi*k*n/Nz)-Itemp[k][j][l]*sin(2.0*pi*k*n/Nz);
	Im[k][j][i]+= Rtemp[k][j][l]*sin(2.0*pi*k*n/Nz)+Itemp[k][j][l]*cos(2.0*pi*k*n/Nz);
	}
	Rm[k][j][i] = Rm[k][j][i]/Nz;
	Im[k][j][i] = Im[k][j][i]/Nz;
	printf("%f %f\n", Rm[k][j][i],Im[k][j][i]);
	}}}
				
	/*逆変換のデータをIDFT3.datに書き込む*/
	for(k=0;k<Nz;k++){
		for(j=0;j<Ny;j++){
			for(i=0;i<Nx;i++){
				fprintf(IDFT3, "%f %f\n", Rm[k][j][i], Im[k][j][i]);
			}
		}
	}

	/*inim2.datのデータとIDFT3.datのデータが一致している, かつ, IDFT3.datの虚部が全てゼロであればo.k. */






fclose(inim2);
fclose(DFT3);
fclose(IDFT3);

	return 0;
	}
