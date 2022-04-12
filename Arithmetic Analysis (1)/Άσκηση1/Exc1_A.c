#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*oi ga kai gb apoteloun tis sunarthseis pou exoume se kathe erwthma(a kai b antistoixa).
me to na kanoume antikatastash ston kwdika opou bepoume Ga h Gb ,
 to Gb h to Ga antistoixa pernoume ta antistoixa apotelesmata gia to kathe erwthma*/
double gb(double x){
	return x- (pow(x,3)-pow(x,2)+1)/(pow(x,2)+4);
}

double ga(double x){
	return (pow(x,3)-pow(x,2)+x+1);
}

int main() { 
	int i=0; /* arxikopoihsh twn epanalipsewn*/
	double x,error; /* arxikopoihsh tou x kai tou error (to opoia to xreiazomaste gia thn euresh tou sfalmatos) */
	double x0 = 0.5; /* thetoume thn arxikh timh x0=0.5 */
	printf("\n Initial condition : %14.5f \n\n", x0); 
	printf("   i \t    x_new \t   g(x)\t          error\n ");  
	 
	do{  
		i++; /* auksish ths timhs kata ena me kathe epanahpsh*/
		x=gb(x0); /* arxikopoioume to x thetontas to me g(x0) */
		error= fabs(x-x0); /*orizoume ton tupo tou lathous mesw tou opoiou kathorizoume thn akribeia twn apotelesmatwn mas*/
 		printf("\n %3d %14.5f %14.5f %14.5f ", i, x, gb(x), error);
		x0=x; /* metathetoume sthn timh tou x0 to x gia na leitourgei h genikh epanaliptikh methodos */
	}while (error >= 0.5*pow(10,(-5))); /* orismos ths sunthkhs(mesw tou krithriou lathous) gia ton termatismo ths do-while*/
	
	printf("\n\n Root = %14.5f \n\n", x); 
	return 0;
}
