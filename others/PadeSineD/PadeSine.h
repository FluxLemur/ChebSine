#ifndef _PADE_SINE_H_
#define _PADE_SINE_H_
#include <cmath>
#include "Eigen/Dense"
#include "sineTest.h"
using namespace Eigen;
using namespace std;

// In c++, structs are much like classes, except they default to public
// class LinearSine : public SinePrototype would also work here
struct PadeSine : SinePrototype
{
private:
    //Pade variables
    int N; //Degree of approximation
    int n; //Degree of polynomials in approximation
    VectorXd coeffs; //Coefficients of Taylor expansion
    VectorXd xx; //Solution of intermediate linear equation
    VectorXd y;
    VectorXd num;
    VectorXd denom;
    VectorXd a;
    double coeff;
    MatrixXd q;
   

    

    long factorial(long n)
    {
        return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
    }
    
public:
    // Define your functions here
    // Class Constructor
	PadeSine(const int nn) : SinePrototype()
    {
        //nn must be odd
        // Initialize and prepare interpolation of sine
        N = nn; //Follows code
        n= (N-1)/2; //Follows code
        xx.resize(n); 
        y.resize(n);
        q.resize(n,n);
        num.resize(n);
        denom.resize(n+1);
        a.resize(n+1);
        coeffs.resize(N);
        
        //Create Taylor coefficients (Works as intended)
        
        for(int ii=0;ii<N;ii++){
            if(ii%2==1)
                coeff = pow(-1.0,(ii-1)/2)/(factorial(ii));
            else
                coeff = 0;
            coeffs(ii)=coeff;
        }
	
        //Create Pade Denominator
        for(int jj=0;jj<n;jj++){
            y(jj)= coeffs(n+jj+1);
            for(int kk=0;kk<n;kk++){
                q(jj,kk) = coeffs(jj-kk+n);
            }
        }
        xx = q.fullPivLu().solve(y);
        denom(0) = 1;
        for(int jj=0;jj<n;jj++){
            denom(jj+1) = -xx(jj);
        }
        //Create Pade Numerator
        for(int kk=1;kk<n+1;kk++){
        	double total = 0;
        	for(int mm=0;mm<kk+1;mm++){
           	 total += denom(mm)*coeffs(kk-mm);
       	 	}
        	a(kk) = total;
    	}
	num = a;
        return;
    }
    
    // Your sine function
	double sine(double x) {
        double numerator=0;
        double denominator=0;
        for(int jj=0;jj<n+1;jj++){
            numerator += num(jj)*pow(x,jj);
            denominator += denom(jj)*pow(x,jj);
        }
	return numerator/denominator;
	}
    
};
#endif
