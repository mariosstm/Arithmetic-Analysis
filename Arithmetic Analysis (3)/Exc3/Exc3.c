#include <stdio.h>
#include <math.h>

#define PI 4*atan(1)

//Me tis sunarthseis double Li kai double Pn kataskevazoume to poluwnumo paremvolhs Lagrange 
//me tupo Pn=Lo(x)*f(xo)+L1(x)*f(x1)+...+Li(x)*f(xi).

double Li(int i, int n, double x[n+1], double X)
{
    int j;
    double li=1;
    for(j=0;j<=n;j++){
        if(j!=i)
            li=li*(X-x[j])/(x[i]-x[j]);
    }
        return li;
}

double Pn(int n, double x[n+1], double y[n+1], double X)
{
    double sum=0;
    int i;
    for(i=0; i<=n; i++){
        sum=sum+Li(i,n,x,X)*y[i];
    }
    return sum;
}


int main(){
	int i;
	double j=0;
	int n=180;
	double val;
	double X;
	double x[n+1]; //pinakas 1x181 pou exei gia times 0 ews 180 moires [0,1,2,...,179,180].
	double y[n+1]; //pinakas 1x181 pou exei gia times ta sine twn timwn tou x[n+1].
	val = PI / 180;
	//dhlwnoume tis times olwn twn stoixeiwn twn 2 pinakwn
	for(i = 0; i < 181; i++)
	{
     x[i]=j;
     y[i]=sin(j*val);
     j=j+1.0;
    }
	//ektupwsh apotelesmatwn sthn morfh moires:...    timh toy polywnymoy paremvolhs Largrange:...
	for(X=0.0; X<=180.0; X++)
	{
		printf("DEgrees: %10.0f \nPn: %10.7f \n",X,Pn(n,x,y,X));
	}

	return 0;
}
