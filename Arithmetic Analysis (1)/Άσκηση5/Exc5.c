#include <stdio.h>
#include <stdlib.h>
#include <math.h> 


double f( double x){
	
	return pow(0.01+pow(x,2),1.5)-9/(4*atan(1)*4*8.85)*x;
}

double df(double x){

	return 3*x*pow(0.01+pow(x,2),0.5)-9/(4*atan(1)*4*8.85);
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
	
	
	printf("\n %3d %14.10f %14.10f %14.10f" , i,x,f(x),error);
	x0=x;
}while((error>= 0.5*pow(10,-10)) );

printf("\nROOT1=%14.10f",x);


	x0=0;
	printf("\n\n\n Initial condition: %14.10f \n\n", x0);
	printf("\n    i      \tx      \tf(x)      \terror \n");

do{
	i=i+1;
	
	x=x0 - f(x0)/df(x0);
	error = fabs(x-x0);
	
	
	printf("\n %3d %14.10f %14.10f %14.10f" , i,x,f(x),error);
	x0=x;
}while((error>= 0.5*pow(10,-10)) );

printf("\nROOT2=%14.10f",x);


return 0;
}
