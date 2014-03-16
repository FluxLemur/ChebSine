#ifndef _CHEB_SINE_H_
#define _CHEB_SINE_H_
#include <cmath>
#include <vector>
#include "sineTest.h"


// In c++, structs are much like classes, except they default to public
// class LinearSine : public SinePrototype would also work here
struct ChebSine : SinePrototype
{
    private:
    
        int Npoints;
		vector<double> c;
		double aa, bb;

    public:
    // Define your functions here make
    // Class Constructor
	ChebSine(const int n, const int m, const double a, const double b) : SinePrototype()
    {

		// compute cheb coeffs
		int num = m; //total number of coefficients
		c.resize(num);
		aa = a;//min
		bb = b;//max
		Npoints = n; //total number of iterations
		int k,j;
		double norm,bpa,bma,y,sum;
		vector<double> f;
		double pi = 2.*M_PI;
		f.resize(num);
		bma=0.5*(b-a);
		bpa=0.5*(b+a);
		for (k=0;k<num;k++){
			y=cos(pi*(k+0.5)/num);
			f[k]=sin(y*bma+bpa);
		}
		double fac=2.0/num;
		for(j=0;j<num;j++){
			sum=0.0;
			for(k=0;k<num;k++){
				sum += f[k]*cos(pi*j*(k+0.5)/num);
			c[j]=fac*sum;
			}
		}
    }


    // Your sine function
	double sine(const double x) {
		
		double y,y2,d=0.0,dd=0.0,sv;
		int j,m;
		m= Npoints;
		y=(2.0*x-aa-bb)/(bb-aa);
		y2=2.0*y;
		
        for( j=m-1;j>0;j--){
			sv=d;
			d=y2*d-dd+c[j];
			dd=sv;
		}
		return y*d-dd+0.5*c[0];
	}

};
#endif
