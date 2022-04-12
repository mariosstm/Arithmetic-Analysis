#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//laurio
//sunarthsh pou vriskei thn orizousa pinaka 4x4 gia thn euresh ths lushs tou susthmatos

double det(double a11, double a12, double a13, double a14, double a21, double a22, double a23, double a24, double a31,
	double a32, double a33, double a34, double a41, double a42, double a43, double a44){	
	double arr1[3][3]={{a22,a23,a24},{a32,a33,a34},{a42,a43,a44}};
	double arr2[3][3]={{a21,a23,a24},{a31,a33,a34},{a41,a43,a44}};
	double arr3[3][3]={{a21,a22,a24},{a31,a32,a34},{a41,a42,a44}};
	double arr4[3][3]={{a21,a22,a23},{a31,a32,a33},{a41,a42,a43}};
	int f,j;
	double det1=0, det2=0, det3=0, det4=0;
	for(f=0;f<3;f++){
      det1 = det1 + (arr1[0][f]*(arr1[1][(f+1)%3]*arr1[2][(f+2)%3] - arr1[1][(f+2)%3]*arr1[2][(f+1)%3]));
    }
  	f=0;
  	for(f=0;f<3;f++){
      det2 = det2 + (arr2[0][f]*(arr2[1][(f+1)%3]*arr2[2][(f+2)%3] - arr2[1][(f+2)%3]*arr2[2][(f+1)%3]));
	}
	f=0;
	for(f=0;f<3;f++){
      det3 = det3 + (arr3[0][f]*(arr3[1][(f+1)%3]*arr3[2][(f+2)%3] - arr3[1][(f+2)%3]*arr3[2][(f+1)%3]));
	}
	f=0;
	for(f=0;f<3;f++){
      det4 = det4 + (arr4[0][f]*(arr4[1][(f+1)%3]*arr4[2][(f+2)%3] - arr4[1][(f+2)%3]*arr4[2][(f+1)%3]));
	}	
	return a11*det1 - a12*det2 + a13*det3 - a14*det4;
}

int main(){
	//sumx, sumx2, sumx3, ... oi seires (stoixeia) tou prwtou pinaka tis selidas 5 tou pdf
	//n kai ns einai to antistoixo m tis ekfwnhshs
	double sumx=0,sumx2=0,sumx3=0,sumx4=0,sumx5=0,sumx6=0,sumy=0,sumyx=0,sumyx2=0,sumyx3=0;
	int i,n;
	double ns;
	
	ns=4.0;
	n=4;
	
	//oi times tou pinaka 1 gia to laurio
	double x[4] = {150.0,215.0,285.0,300.0};
	double y[4] = {307.0,427.0,563.0,594.0};
	
	//upologismos tou athroismatos twn seirwn
	for(i=0;i<n;i++)
	{
		sumx=sumx+x[i];
		sumx2=sumx2+x[i]*x[i];
		sumx3=sumx3+pow(x[i],3.0);
		sumx4=sumx4+pow(x[i],4.0);
		sumx5=sumx5+pow(x[i],5.0);
		sumx6=sumx6+pow(x[i],6.0);
		sumy=sumy+y[i];
		sumyx=sumyx+y[i]*x[i];
		sumyx2=sumyx2+y[i]*x[i]*x[i];
		sumyx3=sumyx3+y[i]*pow(x[i],3.0);
	}
	
	//epilush tou susthmatos
	double a0,a1,a2,a3,det0,det1,det2,det3,deta;
	det0=det(sumy,sumx,sumx2,sumx3,
		sumyx,sumx2,sumx3,sumx4,
		sumyx2,sumx3,sumx4,sumx5,
		sumyx3,sumx4,sumx5,sumx6);
	
	det1=det(ns,sumy,sumx2,sumx3,
		sumx,sumyx,sumx3,sumx4,
		sumx2,sumyx2,sumx4,sumx5,
		sumx3,sumyx3,sumx5,sumx6);
	
	det2=det(ns,sumx,sumy,sumx3,
		sumx,sumx2,sumyx,sumx4,
		sumx2,sumx3,sumyx2,sumx5,
		sumx3,sumx4,sumyx3,sumx6);
	
	det3=det(ns,sumx,sumx2,sumy,
		sumx,sumx2,sumx3,sumyx,
		sumx2,sumx3,sumx4,sumyx2,
		sumx3,sumx4,sumx5,sumyx3);
	
	deta=det(ns,sumx,sumx2,sumx3,
		sumx,sumx2,sumx3,sumx4,
		sumx2,sumx3,sumx4,sumx5,
		sumx3,sumx4,sumx5,sumx6);
	
	a0=det0/deta;
	a1=det1/deta;
	a2=det2/deta;
	a3=det3/deta;
	
	//ektupwsh twn apotelesmatwn poluwnumo 3ou vathmou
	printf("\n\nP(x) = %10.10f*x^3 + %10.10f*x^2 + %10.10f*x + %10.10f",a3,a2,a1,a0);
	
	//S einai to sfalma
	double S=0.0;
	
	//upologismos tou sfalmatos
	for(i=0; i<n; i++)
	{
		S=S+pow(y[i]-(a3*pow(x[i],3.0)+a2*pow(x[i],2.0)+a1*x[i]+a0),2.0); //tupos tou sfalmatos
	}
	printf("\n");
	//ektupwsh sfalmatos
	printf("S: %10.10f",S);
	
	return 0;
}
