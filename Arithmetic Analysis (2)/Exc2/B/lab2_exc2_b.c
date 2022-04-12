#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 100

double f1(double x1 ,double x2 ,double x3 ,double k){
	return pow(x1,3.0)+4.0*x1*pow(x2,2.0)+3.0*pow(x3,3.0)-10.0+73.208*(1.0-k/N);
}

double f2(double x1 ,double x2 ,double x3 ,double k){
	return pow(x1,2.0)+5.0*pow(x1,2.0)*pow(x2,2.0)-3.0*(x3,2.0)+5.0-2.84*(1.0-k/N);
}

double f3(double x1 ,double x2 ,double x3 , double k){
	return pow(x1,4.0)+5.0*x1*x2+2.0*x3-2.0+12.9984*(1.0-k/N);
}

double df1_x1(double x1 ,double x2 ,double x3){
	return 3.0*pow(x1,2.0)+4.0*pow(x2,2.0);
}

double df1_x2(double x1, double x2, double x3){
	return 8.0*x1*x2;
}

double df1_x3(double x1, double x2, double x3){
	return 9.0*pow(x3,2.0);
}

double df2_x1(double x1, double x2, double x3){
	return 2.0*x1+10.0*x1*pow(x2,2.0);
}

double df2_x2(double x1, double x2, double x3){
	return 10.0*x2*pow(x1,2.0);
}

double df2_x3(double x1, double x2, double x3){
	return -9.0*pow(x3,2.0);
}

double df3_x1(double x1, double x2, double x3){
	return 4.0*pow(x1,3.0)+5.0*x2;
}

double df3_x2(double x1, double x2, double x3){
	return 5.0*x1;
}

double df3_x3(double x1, double x2, double x3){
	return 2.0;
}

double det(double a11,double a12,double a13,double a21,double a22,double a23,double a31,double a32,double a33){
	double arr1[3][3]={{a11,a12,a13},{a21,a22,a23},{a31,a32,a33}};
	int i;
	double det1=0;
	for(i=0;i<3;i++){
      det1 = det1 + (arr1[0][i]*(arr1[1][(i+1)%3]*arr1[2][(i+2)%3] - arr1[1][(i+2)%3]*arr1[2][(i+1)%3]));
    }
	return det1;
}


int main(){
	int k=0, i =0 ;
    double akr=0.5*pow(10.0,-5);
    double dx1,dx2,dx3,error,DET,DX1,DX2,DX3;
    double x1=-0.2, x2=7.0, x3=-2.0;
    //vroxos epanalipseon pou ypologizei tis diorthoseis
    do{
    	i=0;
    	k=k+1;
    	printf("\n\n k: %3d",k);
    	printf("\n %10.5f %10.5f %10.5f",x1, x2, x3);
    	
	    do
	    {	
	        i = i+1;
	        //orizouses
	        DX1 = det(-f1(x1,x2,x3,k), df1_x2(x1,x2,x3), df1_x3(x1,x2,x3), -f2(x1,x2,x3,k), df2_x2(x1,x2,x3), df2_x3(x1,x2,x3), -f3(x1,x2,x3,k), df3_x2(x1,x2,x3), df3_x3(x1,x2,x3));
	        DX2 = det(df1_x1(x1,x2,x3), -f1(x1,x2,x3,k), df1_x3(x1,x2,x3), df2_x1(x1,x2,x3), -f2(x1,x2,x3,k), df2_x3(x1,x2,x3), df3_x1(x1,x2,x3), -f3(x1,x2,x3,k), df3_x3(x1,x2,x3));
	        DX3 = det(df1_x1(x1,x2,x3), df1_x2(x1,x2,x3), -f1(x1,x2,x3,k), df2_x1(x1,x2,x3), df2_x2(x1,x2,x3), -f2(x1,x2,x3,k), df3_x1(x1,x2,x3), df3_x2(x1,x2,x3), -f3(x1,x2,x3,k));
	        DET = det(df1_x1(x1,x2,x3), df1_x2(x1,x2,x3), df1_x3(x1,x2,x3), df2_x1(x1,x2,x3), df2_x2(x1,x2,x3), df2_x3(x1,x2,x3), df3_x1(x1,x2,x3), df3_x2(x1,x2,x3), df3_x3(x1,x2,x3));
	        //diorthwseis mesw tis methodou cramer
			dx1 = DX1/DET;
	        dx2 = DX2/DET;
	        dx3 = DX3/DET;
	        //nees proseggiseis
	        x1 = x1 + dx1;
	        x2 = x2 + dx2;
	        x3 = x3 + dx3;
	        //sfalma
	        error=fabs(dx1)+fabs(dx2)+fabs(dx3);
	        //apotelesmata
	        printf("\n i: %3d \n x1: %10.5f \n x2: %10.5f \n x3: %10.5f \n f1: %10.5f \n f2: %10.5f \n f3: %10.5f \n error: %10.5f \n", i , x1, x2, x3, f1(x1,x2,x3,k), f2(x1,x2,x3,k), f3(x1,x2,x3,k), error);
	    }while(error>=akr);

	}while(k < N);                            
    printf("\n");
    
	return 0;
}
