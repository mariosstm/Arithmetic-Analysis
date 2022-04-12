#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*theoroume ws sunarthsh thn cosx-x kai th thetoume ish me mhden (f(x)=cosx-x=0)*/
double f(double x){
	
	return cos(x) - x;
}


int main(){
	
	int j=0;
	double x,error;
	double x0 = -0.8, x1 = -0.55;/*upothetoume emeis 2 arxikes times gia to problhma eureshs lushs*/
	printf("\n  x0 = %14.10f  x1 = %14.10f\n", x0,x1);
	
	do{
		j++;/*prosthiki epanalipsewn*/
		x = x1 - (x1 - x0)/( f(x1)-f(x0) ) * f(x1);/*typos metavlitis xordis*/
		error = fabs(x - x1);/*typos sfalmatos*/
		printf("\n %3d %14.8f %14.8f %14.8f", j, x, f(x), error);
		
		x0 = x1;
		x1 = x;
		
	}while( error >= 0.5*pow(10.0,-8) &&fabs(f(x))>=pow(10,-8 ));/*apo thn ekfwnhsh exoume thesei oti to sfalma prepei na einai 0.5*10^(-8) (akribeia 8 psifeiwn), 
	opote ws periorismo thetoume oti to error prepei na einai megalutero h iso aythw ths timhs*/
	
	printf("\n\n ROOT = %14.8f \n\n",x);
	return 0;
}
