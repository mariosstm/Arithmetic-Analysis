#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f1(double x2, double x3, double x4){
    return 3.0*x2+x3*x4-7.9;
}
double f2(double x1, double x2, double x3, double x4){
    return x1+2.0*x2+x3+4.0*x4-20.7;
}
double f3(double x1, double x3, double x4){
    return pow(x1,3.0)+pow(x3,3.0)+x4-21.218;
}
double f4(double x1, double x2, double x4){
    return pow(x1,2.0)+2.0*x1*x2+pow(x4,3.0)-15.88;
}

double df1_x1(double x2, double x3, double x4){
	return 0;
}

double df1_x2(double x2, double x3, double x4){
	return 3.0;
}

double df1_x3(double x2, double x3, double x4){
	return x4;
}

double df1_x4(double x2, double x3, double x4){
	return x3;	
}

double df2_x1(double x1, double x2, double x3, double x4){
	return 1.0;
}

double df2_x2(double x1, double x2, double x3, double x4){
	return 2.0;
}

double df2_x3(double x1, double x2, double x3, double x4){
	return 1.0;
}

double df2_x4(double x1, double x2, double x3, double x4){
	return 4.0;
}

double df3_x1(double x1, double x3, double x4){
	return 3.0*pow(x1,2.0);
}

double df3_x2(double x1, double x3, double x4){
	return 0;
}

double df3_x3(double x1, double x3, double x4){
	return 3.0*pow(x3,2.0);
}

double df3_x4(double x1, double x3, double x4){
	return 1.0;
}

double df4_x1(double x1, double x2, double x4){
	return 2.0*x1 + 2.0*x2;
}

double df4_x2(double x1, double x2, double x4){
	return 2.0*x1;
}

double df4_x3(double x1, double x2, double x4){
	return 0;
}

double df4_x4(double x1, double x2, double x4){
	return 3.0*pow(x4,2.0);
}


double det(double a11, double a12, double a13, double a14, double a21, double a22, double a23, double a24, double a31,
	double a32, double a33, double a34, double a41, double a42, double a43, double a44){	
	double arr1[3][3]={{a22,a23,a24},{a32,a33,a34},{a42,a43,a44}};
	double arr2[3][3]={{a21,a23,a24},{a31,a33,a34},{a41,a43,a44}};
	double arr3[3][3]={{a21,a22,a24},{a31,a32,a34},{a41,a42,a44}};
	double arr4[3][3]={{a21,a22,a23},{a31,a32,a33},{a41,a42,a43}};
	int i,j;
	double det1=0, det2=0, det3=0, det4=0;
	
	for(i=0;i<3;i++)det1 = det1 + (arr1[0][i]*(arr1[1][(i+1)%3]*arr1[2][(i+2)%3] - arr1[1][(i+2)%3]*arr1[2][(i+1)%3]));
    
  	i=0;
  	for(i=0;i<3;i++)det2 = det2 + (arr2[0][i]*(arr2[1][(i+1)%3]*arr2[2][(i+2)%3] - arr2[1][(i+2)%3]*arr2[2][(i+1)%3]));
	i=0;
	for(i=0;i<3;i++)det3 = det3 + (arr3[0][i]*(arr3[1][(i+1)%3]*arr3[2][(i+2)%3] - arr3[1][(i+2)%3]*arr3[2][(i+1)%3]));
	
	i=0;
	for(i=0;i<3;i++)det4 = det4 + (arr4[0][i]*(arr4[1][(i+1)%3]*arr4[2][(i+2)%3] - arr4[1][(i+2)%3]*arr4[2][(i+1)%3]));
		
	return a11*det1 - a12*det2 + a13*det3 - a14*det4;
}


int main(){
    int i =0 ;
    double akr=0.5*pow(10.0,-5); 
    double x1=1.0, x2=1.0, x3=1.0, x4=1.0;
    double dx1,dx2,dx3,dx4,error,DET,DX1,DX2,DX3,DX4;
    
    do
    {
        i = i+1;
        //upologismos twn 4 orizouswn
        DET=det(df1_x1(x2,x3,x4),df1_x2(x2,x3,x4),df1_x3(x2,x3,x4),df1_x4(x2,x3,x4),df2_x1(x1,x2,x3,x4),df2_x2(x1,x2,x3,x4),df2_x3(x1,x2,x3,x4),df2_x4(x1,x2,x3,x4),df3_x1(x1,x3,x4),df3_x2(x1,x3,x4),df3_x3(x1,x3,x4),df3_x4(x1,x3,x4),df4_x1(x1,x2,x4),df4_x2(x1,x2,x4),df4_x3(x1,x2,x4),df4_x4(x1,x2,x4));
        DX1=det(-f1(x2,x3,x4),df1_x2(x2,x3,x4),df1_x3(x2,x3,x4),df1_x4(x2,x3,x4),-f2(x1,x2,x3,x4),df2_x2(x1,x2,x3,x4),df2_x3(x1,x2,x3,x4),df2_x4(x1,x2,x3,x4),-f3(x1,x3,x4),df3_x2(x1,x3,x4),df3_x3(x1,x3,x4),df3_x4(x1,x3,x4),-f4(x1,x2,x4),df4_x2(x1,x2,x4),df4_x3(x1,x2,x4),df4_x4(x1,x2,x4));
        DX2=det(df1_x1(x2,x3,x4),-f1(x2,x3,x4),df1_x3(x2,x3,x4),df1_x4(x2,x3,x4),df2_x1(x1,x2,x3,x4),-f2(x1,x2,x3,x4),df2_x3(x1,x2,x3,x4),df2_x4(x1,x2,x3,x4),df3_x1(x1,x3,x4),-f3(x1,x3,x4),df3_x3(x1,x3,x4),df3_x4(x1,x3,x4),df4_x1(x1,x2,x4),-f4(x1,x2,x4),df4_x3(x1,x2,x4),df4_x4(x1,x2,x4));
        DX3=det(df1_x1(x2,x3,x4),df1_x2(x2,x3,x4),-f1(x2,x3,x4),df1_x4(x2,x3,x4),df2_x1(x1,x2,x3,x4),df2_x2(x1,x2,x3,x4),-f2(x1,x2,x3,x4),df2_x4(x1,x2,x3,x4),df3_x1(x1,x3,x4),df3_x2(x1,x3,x4),-f3(x1,x3,x4),df3_x4(x1,x3,x4),df4_x1(x1,x2,x4),df4_x2(x1,x2,x4),-f4(x1,x2,x4),df4_x4(x1,x2,x4));
        DX4=det(df1_x1(x2,x3,x4),df1_x2(x2,x3,x4),df1_x3(x2,x3,x4),-f1(x2,x3,x4),df2_x1(x1,x2,x3,x4),df2_x2(x1,x2,x3,x4),df2_x3(x1,x2,x3,x4),-f2(x1,x2,x3,x4),df3_x1(x1,x3,x4),df3_x2(x1,x3,x4),df3_x3(x1,x3,x4),-f3(x1,x3,x4),df4_x1(x1,x2,x4),df4_x2(x1,x2,x4),df4_x3(x1,x2,x4),-f4(x1,x2,x4));
        //diorthwseis mesw tis methodou cramer
		dx1 = DX1/DET; 
        dx2 = DX2/DET;
        dx3 = DX3/DET;
        dx4 = DX4/DET;
        //belltiwsh prosegkisewnn twn metablhtwn Xi , i=1,2,3,4
        x1 = x1 + dx1;
        x2 = x2 + dx2;
        x3 = x3 + dx3;
        x4 = x4 + dx4;
        //tupos sfalmatos gia 4 dx
        error=fabs(dx1)+fabs(dx2)+fabs(dx3)+fabs(dx4);
        //tupwsh twn apotelesmatwnn apotelesmata
        printf(" i: %3d \n x1: %10.5f \n x2: %10.5f \n x3: %10.5f \n x4: %10.5f \n f1: %10.5f \n f2: %10.5f \n f3: %10.5f \n f4: %10.5f \n error: %10.5f \n", i , x1, x2, x3, x4, f1(x2,x3,x4), f2(x1,x2,x3,x4), f3(x1,x3,x4), f4(x1,x2,x4), error);
        printf("\n");
    }while(error>=akr);
    printf("\n");

    return 0;
}
