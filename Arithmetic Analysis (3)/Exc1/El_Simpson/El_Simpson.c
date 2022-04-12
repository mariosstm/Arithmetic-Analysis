#include <math.h>
#include <stdio.h>
//dhlwnoume th sunarthsh pou mas zhthtai , antigraphontas ta 
//dedomena pou mas dinwntai kai tis metablhtes ths sunarthshs
double El(const double ph){
	double ra=0.1,phA=35*(4*atan(1)/180),R=0.05,za=0.4,Q=pow(10,-6),k=9*pow(10,9);
	double a=sqrt(pow(ra,2)+pow(R,2)+pow(za,2));	
	
	return (k*Q*za)/(2*4*atan(1))*sqrt(pow(ra,2)+pow(R,2)-2*ra*R*cos(ph-phA))*pow(1/(pow(a,2)-2*ra*R*cos(ph-phA)),1.5);

}


//ulopoioume th methodo simpson mesw sunarthshs gia na 
//thesoume epeita ta oloklhrwmata pou mas zhtounte
double I_El(const int n, const double a, const double b){
    int i;
    const double h = (b - a) / n;// to bhma tou oloklhrwmatos - akribeia upologismou
    double I_El = 0;//arxikopoihsh tou oloklhrwmatos
    
	//xrhsimopoiwntas enan epanalhptiko brogxo for mporoume na ulopoihsoume th methodo
	//Simpson kathws prepei na prosthetoume sto arxikopoihmeno oloklhrwma to apotelesma ths
	//sunarthshs El pou thesame prohgoymenos analoga me to bhma pou pragmatopoioume kathe fora
	for (i = 0; i <= n; ++i) {
        if (i == 0 || i == n) {
            I_El += El(a + i * h);
        } else if (i % 2 == 0) {
            I_El += 2 * El(a + i * h);
        } else {
            I_El += 4 * El(a + i * h);
        }
    }
    I_El *= h / 3;
    return I_El;
}



main(){
   //thetoume ta oria tou oloklhrwmatos kai polu mikrh akribeia
    double pi=4*atan(1);
    double a=0,b=2*pi;
    int n=2,n1=n/2;
    double I3 = I_El(n1, a, b), I4 = I_El(n, a, b);
  
    double error1=fabs(I3-I4);

	do {
		printf(" a=%10.8f b=%10.8f\n n1=%d I1=%10.8f \n n2=%d I2=%10.8f\n error=%10.8f\n\n", a, b, n1, I3, n, I4, error1);
    	n=2*n;//diplasiazoume thn akribeia kai etsi upodiplasiazoume to h kathe fora
    			//gia na petuxoume thn epithumhth akribeia etsi akrivws opws mas zhteitai
    	n1=n/2;
    	I3 = I_El(n1, a, b);
		I4 = I_El(n, a, b);
		error1=fabs(I3-I4);
		
	}while(error1>=0.5*pow(10,-9));

    return 0;
}
