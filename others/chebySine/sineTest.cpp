#include "sineTest.h"
// Add your header file here
#include "LinearSine.h"
#include "ChebSine.h"

#include <cmath>
#include <ctime>
#include <iostream>
#include <limits>

using namespace std;

void EvaluateYourSine(SinePrototype *yoursine, const char *name);
#define NTIME 10000000
#define NERR 1000000
// tunable parameters
static double randarr[NTIME];

int main()
{
    clock_t st, ed;

    // generate an array of random numbers to test the time
    for(int i=0; i<NTIME; i++) {
        randarr[i] = rand()*2.*M_PI/RAND_MAX;
    }

    // Instantiate machineSine, linearSine
    // Add your sine class and call EvaluateYourSine with your class instance.
    SinePrototype machineSine;
    LinearSine linear(18);
    //chebSine(number of iterations, number of coefficients, a , b )
	
    ChebSine chebSine1(18,200,0, 2.*M_PI);
    ChebSine chebSine2(15,200,0, 2.*M_PI);
    ChebSine chebSine3(7,200,0,2.*M_PI);

    EvaluateYourSine(&machineSine, "our machine sine");
    EvaluateYourSine(&linear, "linear sine (18 iterations)");
	EvaluateYourSine(&chebSine1, "chebSine (18 iterations) 200 coef");
    EvaluateYourSine(&chebSine2, "chebSine (15 iterations) 200 coef");
    EvaluateYourSine(&chebSine3, "chebSine (7 iterations) 200 coef");
	
	
}

void EvaluateYourSine(SinePrototype *yoursine, const char *name) {
    clock_t st, ed;
    double tmp=0.;

    st = clock();
    for(int i=0; i<NTIME; i++) {
    // We add up the results to keep the optimizing compiler from removing the line
        tmp += yoursine->sine(randarr[i]);
    }
    ed = clock();
    cout << "Time for " << name << ":" << endl;
    cout << (double(ed)-double(st))/CLOCKS_PER_SEC << "s per " << NTIME << " repetitions" << endl;

    // Evaluate errors
    double errorMax = 0.;
    double err;
    for(double t=0.; t<2.*M_PI; t += 2.*M_PI/NERR) {
       err = abs(yoursine->sine(t) - sin(t));
       if (errorMax <= err) errorMax = err; 
    }

    // print error
    cout << "Maximum Error = " << errorMax << endl << endl;
}