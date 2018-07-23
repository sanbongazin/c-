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
FILE *inim3, *DFT3, *IDFT3; 
	
double mx[Nz][Ny][Nx]; /*m[Nz][Ny][Nx]とすると, 整数のmとかぶるので mxとした*/
double Rm[Nz][Ny][Nx], Im[Nz][Ny][Nx];
double Rc[Nz][Ny][Nx], Ic[Nz][Ny][Nx];			
double Rtemp[Nz][Ny][Nx],Itemp[Nz][Ny][Nx]; 
double Rtemp2[Nz][Ny][Nx],Itemp2[Nz][Ny][Nx];
	

	
int i,j,k,l,m,n; /* i,j,kが実空間のx成分,y成分,z成分, l,m,nがフーリエ空間のx成分,y成分,z成分に対応*/
	
inim3=fopen("inim3.dat","r");
DFT3=fopen("DFT3.dat","w");
IDFT3=fopen("IDFT3.dat","w");
	
/*２次元配列データファイル inim3.datをmx[z][j][i]に読み込ませる*/
for (k=0;k<Nz;k++){
 for (j=0;j<Ny;j++){
  for (i=0; i<Nx;i++){
 fscanf(inim3,"%lf",&mx[k][j][i]);
  }
}}
	
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
 Rtemp2[k][j][i]=0.0;
 Itemp2[k][j][i]=0.0;
		 
				 
 }
}}
	

/*x成分をDFT*/
for(k=0;k<Nz;k++){
for (j=0;j<Ny;j++){
 for (l=0;l<Nx;l++){
  for (i=0;i<Nx;i++){
 Rtemp[k][j][l] +=  mx[k][j][i]*cos(2.0*pi*i*l/Nx);
 Itemp[k][j][l] += -mx[k][j][i]*sin(2.0*pi*i*l/Nx);
		}
		}
	}
}
	
	
/*y成分をDFT*/
for (l=0;l<Nx;l++){
for (k=0;k<Nz;k++){
 for (m=0;m<Ny;m++){
  for (j=0;j<Ny;j++){
 Rtemp2[k][m][l] +=  Rtemp[k][j][l]*cos(2.0*pi*j*m/Ny)+Itemp[k][j][l]*sin(2.0*pi*j*m/Ny);
 Itemp2[k][m][l] += -Rtemp[k][j][l]*sin(2.0*pi*j*m/Ny)+Itemp[k][j][l]*cos(2.0*pi*j*m/Ny);
				}
		}
	}
}


/*z成分をDFT*/
for (m=0;m<Ny;m++){
for(l=0;l<Nx;l++){
for(n=0;n<Nz;n++){
for(k=0;k<Nz;k++){
 Rc[n][m][l] +=  Rtemp2[k][m][l]*cos(2.0*pi*k*n/Nz)+Itemp2[k][m][l]*sin(2.0*pi*k*n/Nz);
 Ic[n][m][l] += -Rtemp2[k][m][l]*sin(2.0*pi*k*n/Nz)+Itemp2[k][m][l]*cos(2.0*pi*k*n/Nz);
			}
		}
	}
}
	
/*フーリエ成分の配列をDFT3.datに書き込む*/
for(n=0;n<Nz;n++){
for(m=0;m<Ny;m++){
	for(l=0;l<Nx;l++){
fprintf(DFT3, "%f %f\n", Rc[n][m][l],Ic[n][m][l]);
}}}


/*temporary配列をリセット*/
for (k=0;k<Nz;k++){
 for (j=0;j<Ny;j++){
  for (i=0; i<Nx;i++){
 Rtemp[k][j][i]=0.0;
 Itemp[k][j][i]=0.0;
 Rtemp2[k][j][i]=0.0;
 Itemp2[k][j][i]=0.0;
 }
  }
}
	
/*逆DFTで元のデータにもどるかチェック*/
	
/*x成分を逆DFT*/
for(n=0;n<Nz;n++){
for(m=0;m<Ny;m++){
 for(i=0;i<Nx;i++){
  for(l=0;l<Nx;l++){
  Rtemp2[n][m][i] += Rc[n][m][l]*cos(2.0*pi*i*l/(Nx))-Ic[n][m][l]*sin(2.0*pi*i*l/(Nx));
  Itemp2[n][m][i] += Rc[n][m][l]*sin(2.0*pi*i*l/(Nx))+Ic[n][m][l]*cos(2.0*pi*i*l/(Nx));
  }
  Rtemp2[n][m][i] = Rtemp2[n][m][i]/(Nx);
  Itemp2[n][m][i] = Itemp2[n][m][i]/(Nx);
  printf("%f %f\n", Rtemp2[n][m][i],Itemp2[n][m][i]);
}}}
	
	
/*y成分を逆DFT*/
for(i=0;i<Nx;i++){
 for(n=0;n<Nz;n++){
 for(j=0;j<Ny;j++){
  for(m=0;m<Ny;m++){
  Rtemp[n][j][i]+= Rtemp2[n][m][i]*cos(2.0*pi*j*m/(Ny))-Itemp2[n][m][i]*sin(2.0*pi*j*m/(Ny));
  Itemp[n][j][i]+= Rtemp2[n][m][i]*sin(2.0*pi*j*m/(Ny))+Itemp2[n][m][i]*cos(2.0*pi*j*m/(Ny));
  }
  Rtemp[n][j][i] = Rtemp[n][j][i]/(Ny);
  Itemp[n][j][i] = Itemp[n][j][i]/(Ny);
  printf("%f %f\n", Rtemp[n][j][i],Itemp[n][j][i]);
}}}

/*z成分を逆DFT*/
for(j=0;j<Ny;j++){
 for(i=0;i<Nx;i++){
 for(k=0;k<Nz;k++){
  for(n=0;n<Nz;n++){
  Rm[k][j][i]+= Rtemp[n][j][i]*cos(2.0*pi*k*n/(Nz))-Itemp2[n][j][i]*sin(2.0*pi*k*n/(Nz));
  Im[k][j][i]+= Rtemp[n][j][i]*sin(2.0*pi*k*n/(Nz))+Itemp2[n][j][i]*cos(2.0*pi*k*n/(Nz));
  }
  Rm[k][j][i] = Rm[k][j][i]/(Nz);
  Im[k][j][i] = Im[k][j][i]/(Nz);
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

	/*inim3.datのデータとIDFT3.datのデータが一致している, かつ, IDFT3.datの虚部が全てゼロであればo.k. */






fclose(inim3);
fclose(DFT3);
fclose(IDFT3);
	return 0;
}
