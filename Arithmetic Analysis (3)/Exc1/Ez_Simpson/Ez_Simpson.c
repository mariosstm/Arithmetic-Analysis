#include <math.h>
#include <stdio.h>

double Ez(const double ph){
	double ra=0.1,phA=35*(4*atan(1)/180),R=0.05,za=0.4,Q=pow(10,-6),k=9*pow(10,9);
	double a=sqrt(pow(ra,2)+pow(R,2)+pow(za,2));
	
    return (k*Q*za)/(2*4*atan(1))*pow(1/(pow(a,2)-2*ra*R*cos(ph-phA)),1.5);
}


double I_Ez(const int n, const double a, const double b){
    int i;
    const double h = (b - a) / n;
    double I_Ez = 0;
    for (i = 0; i <= n; ++i) {
        if (i == 0 || i == n) {
            I_Ez += Ez(a + i * h);
        } else if (i % 2 == 0) {
            I_Ez += 2 * Ez(a + i * h);
        } else {
            I_Ez += 4 * Ez(a + i * h);
        }
    }
    I_Ez *= h / 3;
    return I_Ez;
}

main(){
   
    double pi=4*atan(1);
    double a=0,b=2*pi;
    int n=2,n1=n/2;
    double I1 = I_Ez(n1, a, b), I2 = I_Ez(n, a, b);

    double error=fabs(I1-I2);
    printf("First Integral of Z-Axis.\n\n");
    do {
		printf(" a=%10.8f b=%10.8f\n n1=%d I1=%10.8f \n n2=%d I2=%10.8f\n error=%10.8f\n\n", a, b, n1, I1, n, I2, error);
    	n=2*n;
    	n1=n/2;
    	I1 = I_Ez(n1, a, b);
		I2 = I_Ez(n, a, b);
		error=fabs(I1-I2);
	}while(error>=0.5*pow(10,-8));
	return 0;
}
