#include <math.h>
#include <stdio.h>

double Ez(const double ph){
	double ra=0.1,phA=35*(4*atan(1)/180),R=0.05,za=0.4,Q=pow(10,-6),k=9*pow(10,9);
	double a=sqrt(pow(ra,2)+pow(R,2)+pow(za,2));
	
    return (k*Q*za)/(2*4*atan(1))*pow(1/(pow(a,2)-2*ra*R*cos(ph-phA)),1.5);
}

double El(const double ph){
	double ra=0.1,phA=35*(4*atan(1)/180),R=0.05,za=0.4,Q=pow(10,-6),k=9*pow(10,9);
	double a=sqrt(pow(ra,2)+pow(R,2)+pow(za,2));	
	
	return (k*Q*za)/(2*4*atan(1))*sqrt(pow(ra,2)+pow(R,2)-2*ra*R*cos(ph-phA))*pow(1/(pow(a,2)-2*ra*R*cos(ph-phA)),1.5);

}

double I_Ez(const int n, const double a, const double b){
    int i;
    const double h = (b - a) / n;
    double I_Ez = 0;
    for (i = 0; i <= n; ++i) {
        I_Ez+= (i == 0 || i == n ? Ez(a + i * h) / 2 : Ez(a + i * h));
    }
    I_Ez*= h;
    return I_Ez ;
}

double I_El(const int n, const double a, const double b){
    int i;
    const double h = (b - a) / n;
    double I_El = 0;
    for (i = 0; i <= n; ++i) {
        I_El+= (i == 0 || i == n ? El(a + i * h) / 2 : El(a + i * h));
    }
    I_El*= h;
    return I_El ;
}


main(){
    double pi=4*atan(1);
    double a=0,b=2*pi;
    int n=2,n1=n/2;
    double I1 = I_Ez(n1, a, b), I2 = I_Ez(n, a, b);
    double I3 = I_El(n1, a, b), I4 = I_El(n, a, b);
    double error=fabs(I1-I2);
    double error1=fabs(I3-I4);
    printf("First Integral of Z-Axis.\n\n");
    do {
		printf(" a=%10.8f b=%10.8f\n n1=%d I1=%10.8f \n n2=%d I2=%10.8f\n error=%10.8f\n", a, b, n1, I1, n, I2, error);
    	n=2*n;
    	n1=n/2;
    	I1 = I_Ez(n1, a, b);
		I2 = I_Ez(n, a, b);
		error=fabs(I1-I2);
	}while(error>=0.5*pow(10,-8));
	
	n=2,n1=n/2;
	
	
	printf("\nSecond Integral perpedicular to the first.\n\n");
	do {
		printf(" a=%10.8f b=%10.8f\n n1=%d I1=%10.8f \n n2=%d I2=%10.8f\n error=%10.8f\n\n", a, b, n1, I3, n, I4, error1);
    	n=2*n;
    	n1=n/2;
    	I3 = I_El(n1, a, b);
		I4 = I_El(n, a, b);
		error1=fabs(I3-I4);
		
	}while(error1>=0.5*pow(10,-9));

    return 0;
}




