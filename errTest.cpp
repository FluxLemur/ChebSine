#include "sineTest.h"
#include "LinearSine.h"
#include "chebSine.h"
#include "PadeSine.h"
#include "PolyInterp.h"
#include "LsqSine2.h"
#include "RationalSine_3.h"
#include "LeastSquareSine.h"
#include "ChebfunSine.h"
//#include "ChebSine.h"

#include <cmath>
#include <iostream>


using namespace std;

void genSineErr(SinePrototype *yoursine, const char *name);
#define NERR 1000

int main()
{
    // Instantiate machineSine, linearSine
    // Add your sine class and call EvaluateYourSine with your class instance.
    //SinePrototype machineSine;
    //LinearSine linear(10);
    //ChebSine cheb(10);
    PadeSine pade(10);
    //PolySine poly(10);
    //LsqSine2 lsq(10, 10);
    //RationalSine rat(10);
    //LinearSine lin(10);
    //ChebfunSine chebfun(10);
    //ChebSine cheb_octopus(10, 100, 0, M_PI*2);
    
    // NOTE: Only generate one sine at a time!
    //genSineErr(&machineSine, "machine sine");
    //genSineErr(&linear, "linear sine");
    //genSineErr(&cheb, "cheb sine");
    genSineErr(&pade, "pade sine");
    //genSineErr(&poly, "Polynomial Interpolation");
    //genSineErr(&lsq, "Least Square Fit");
    //genSineErr(&rat, "Rational Function Interpolation");
    //genSineErr(&lin, "Least Square Polynomials");
    //genSineErr(&chebfun, "Chebfun");
    //genSineErr(&cheb_octopus, "Chebyshev Polynomials");
}

void genSineErr(SinePrototype *yoursine, const char *name) {

    cout << "error for " << name << endl;
    double err;
    for (double x=0; x<2.*M_PI; x+=2.*M_PI/NERR) {
        err = abs(yoursine->sine(x) - sin(x));
        cout << x << " " << err << endl;
    }
}
