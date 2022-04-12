#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

double f( double x){
	return pow(x,4)+ 2*pow(x,3)+pow(x,2)+12*x + 20;
}

double df(double x){
	return 4*pow(x,3) + 6*pow(x,2)+ 2*x + 12;
}

double g(double x){
	return f(x)/df(x);
}


double ddf (double x){
	return 12*pow(x,2)+12*x+2;
}



int main(){
	int i=0;
	double x,error;
	double x0=1;
	printf("\n Initial condition: %14.10f \n\n", x0);
	printf("\n    i      \tx      \tf(x)      \terror \n");

do{
	i=i+1;

	x=x0 - f(x0)/df(x0);
	error = fabs(x-x0);
	
	
	printf("\n %3d %14.8f %14.8f %14.8f" , i,x,f(x),error);
	x0=x;
}while((error>= 0.5*pow(10,-8)) || fabs(f(x0))>=0.5*pow(10,-8));

printf("\nROOT=%14.8f",x);

x0=1;
i=0;
do{
	i=i+1;
	x=x0 - (f(x0)*df(x0))/(pow(df(x0),2)-(f(x0)*ddf(x0)));

	error = fabs(x-x0);
	
	
	printf("\n %3d %14.8f %14.8f %14.8f" , i,x,f(x),error);
	x0=x;
}while((error>= 0.5*pow(10,-8)) || fabs(f(x0))>=0.5*pow(10,-8));

printf("\nROOT=%14.8f",x);
return 0;
}
