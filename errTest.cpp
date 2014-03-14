#include "sineTest.h"
#include "LinearSine.h"
#include "chebSine.h"
#include "PadeSine.h"

#include <cmath>
#include <iostream>


using namespace std;

void genSineErr(SinePrototype *yoursine, const char *name);
#define NERR 1000

int main()
{
    // Instantiate machineSine, linearSine
    // Add your sine class and call EvaluateYourSine with your class instance.
    SinePrototype machineSine;
    LinearSine linear(10);
    ChebSine cheb(10);
    PadeSine pade(10);

    
    // NOTE: Only generate one sine at a time!
    //genSineErr(&machineSine, "machine sine");
    //genSineErr(&linear, "linear sine");
    genSineErr(&cheb, "cheb sine");
    //genSineErr(&pade, "pade sine");
}

void genSineErr(SinePrototype *yoursine, const char *name) {

    cout << "error for " << name << endl;
    double err;
    for (double x=0; x<2.*M_PI; x+=2.*M_PI/NERR) {
        err = abs(yoursine->sine(x) - sin(x));
        cout << x << " " << err << endl;
    }
}
