#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*theoroume ws sunarthsh thn cosx-x kai th thetoume ish me mhden (f(x)=cosx-x=0)*/
double f(double x){
	
	return exp(-0.002*x)*cos(sqrt(3.2-0.000004*pow(x,2)))-0.02;
}


int main(void){
	
	int j=0;
	double x,error;
	double x0 = -6, x1 = -5;/*upothetoume emeis 2 arxikes times gia to problhma eureshs lushs*/
	printf("\n  x0 = %14.6f  x1 = %14.6f\n", x0,x1);
	
	do{
		j++;/*prosthiki epanalipsewn*/
		x = x1 - (x1 - x0)/( f(x1)-f(x0) ) * f(x1);/*typos metavlitis xordis*/
		error = fabs(x - x1);/*typos sfalmatos*/
		printf("\n %3d %14.6f %14.6f %14.6f", j, x, f(x), error);
		
		x0 = x1;
		x1 = x;
		
	}while( error >= 0.5*pow(10.0,-6) && fabs(f(x))>=pow(10,-6 ));/*apo thn ekfwnhsh exoume thesei oti to sfalma prepei na einai 0.5*10^(-8) (akribeia 8 psifeiwn), 
	opote ws periorismo thetoume oti to error prepei na einai megalutero h iso aythw ths timhs*/
	
	printf("\n\n ROOT = %14.6f \n\n",x);
	return 0;
}
