#include "sineTest.h"
#include "RationalSine_3.h"
#include "LinearSine.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <ctime>
#include <iostream>
#include <limits>

using namespace std;

void EvaluateYourSine(SinePrototype *yoursine, const char *name);
#define NTIME 10000
#define NERR 1000
// tunable parameters
static double randarr[NTIME];

int main()
{
	clock_t st, ed;

	// generate an array of random numbers to test the time
	for (int i = 0; i<NTIME; i++) {
		randarr[i] = rand()*2.*M_PI / RAND_MAX;
	}

	// Instantiate machineSine, rationalSine
	// Add your sine class and call EvaluateYourSine with your class instance.
	SinePrototype machineSine;
	RationalSine rational(100);
  LinearSine linear(100);

	EvaluateYourSine(&machineSine, "our machine sine");
	EvaluateYourSine(&rational, "rational sine");
  EvaluateYourSine(&linear, "linear sine");
}

void EvaluateYourSine(SinePrototype *yoursine, const char *name) {
	clock_t st, ed;
	double tmp = 0.;

	st = clock();
	for (int i = 0; i<NTIME; i++) {
		// We add up the results to keep the optimizing compiler from removing the line
		tmp += yoursine->sine(randarr[i]);
	}
	ed = clock();
	cout << "Time for " << name << ":" << endl;
	cout << (double(ed) - double(st)) / CLOCKS_PER_SEC << "s per " << NTIME << " repetitions" << endl;


	// Evaluate errors
	double errorMax = 0.;
	double err=0.0;
	for (double t = 0.; t<2.*M_PI; t += 2.*M_PI / NERR) {
    err = abs(yoursine->sine(t) - sin(t));
		if (errorMax <= err) errorMax = err;
	}

	// print error
	cout << "Maximum Error = " << errorMax << endl << endl;

}
