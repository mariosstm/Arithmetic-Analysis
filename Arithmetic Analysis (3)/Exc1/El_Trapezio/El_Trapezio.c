#include <math.h>
#include <stdio.h>

//paromoia me ton prohgoumeno kwdika tha broume to El me th methodo tou trapeziou
//Ston kwdika den allazei kathiolou h diadikasia pera apth sunarthsh upologismou tou oloklhrwmatos

double El(const double ph){
	double ra=0.1,phA=35*(4*atan(1)/180),R=0.05,za=0.4,Q=pow(10,-6),k=9*pow(10,9);
	double a=sqrt(pow(ra,2)+pow(R,2)+pow(za,2));	
	
	return (k*Q*za)/(2*4*atan(1))*sqrt(pow(ra,2)+pow(R,2)-2*ra*R*cos(ph-phA))*pow(1/(pow(a,2)-2*ra*R*cos(ph-phA)),1.5);

}

double I_El(const int n, const double a, const double b){
	//omoiws me th simpson h methodos tou kanona tou trapeziou
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
  
    double I3 = I_El(n1, a, b), I4 = I_El(n, a, b);
   
    double error1=fabs(I3-I4);
   
	
	
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


