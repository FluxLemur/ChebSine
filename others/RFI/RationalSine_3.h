/*  AstroPy's Rational Function Interpolation
    Our code is based off an example in Numerical Recipies; however, we have made several changes to improve speed and accuracy. 
*/
#ifndef _RATIONAL_SINE_H_
#define _RATIONAL_SINE_H_
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "sineTest.h"
#include "time.h"
#include "iostream"

// In c++, structs are much like classes, except they default to public
// class LinearSine : public SinePrototype would also work here
struct RationalSine : SinePrototype
{
private:
	int Npoints;
	int Nintervals;
  vector<double> xvector;
	vector<double> yvector;
	vector<double> cvector;
	vector<double> dvector;

public:
	// Define your functions here 
	// Class Constructor
	RationalSine(const int nn) : SinePrototype()
	{
		//Initialize and prepare interpolation of sine
		Nintervals = nn;
		Npoints = nn + 1;
		xvector.resize(Npoints);
		yvector.resize(Npoints);
		cvector.resize(Npoints);
		dvector.resize(Npoints);

		for (int i = 0; i < (Npoints - 1); i++)
		{
			xvector[i] = i*2.*M_PI / Nintervals;
			yvector[i] = sin(xvector[i]);
		}

	}

	// Your sine function
	double sine(double x)
	{
		int place = 0;
		double xmultiplier = 0.0;
		double cdmultiplier = 0.0;
		double y = 0.0;
		double dy = 0.0;
    float small = 1e-25;

		for (int k = 1; k<Nintervals; k++)
		{
			cvector[k] = yvector[k];
			dvector[k] = yvector[k] + small;
      
      // If the value is very close to an input value, just return the sine value and don't worry about trying to interpolate
      if (fabs(xvector[k]-x)<10e-15)
      {
        return yvector[k];
      }
		}

    place = (x / (2. * M_PI) * (Nintervals));
		y = yvector[place--];

		for (int m = 1; m<(Nintervals); m++)
		{
			for (int j = 1; j<(Nintervals - m); j++)
			{
        //This may seem a bit opaque. Please see the recursion formulas in Numerical Recipies for C and D. It will help make these clearer. 
				xmultiplier = ((xvector[j] - x)*dvector[j] / (xvector[j + m] - x));
				cdmultiplier = ((cvector[j + 1] - dvector[j]) / (xmultiplier - cvector[j + 1]));
				dvector[j] = cvector[j + 1] * cdmultiplier;
				cvector[j] = xmultiplier*cdmultiplier;
			}
			if (2 * place <(Nintervals - m))
			{
				dy = cvector[place+1];
			}
			else
			{
				dy = dvector[place];
				place = place--;
			}
			y = y + dy;     
		}  
		return y;
	}
};
#endif