#ifndef _POLY_SINE_H_
#define _POLY_SINE_H_
#include <cmath>
#include <vector>
#include "sineTest.h"
#include <iostream>


// In c++, structs are much like classes, except they default to public
// class LinearSine : public SinePrototype would also work here
struct PolySine : SinePrototype
{
 private:
  int n_interp;
  vector<double> xGrid;
  vector<double> sinGrid;

 public:
  // Define your functions here 
  // Class Constructor
 PolySine(const int n_interp) : SinePrototype()  
    {
      // Initialize and prepare interpolation of sine
      this->n_interp=n_interp;
      xGrid.resize(n_interp);
      sinGrid.resize(n_interp);
      const double delta=2*M_PI/n_interp;
      double xi=0;
      for(int i=0; i<n_interp; i++) {
	xGrid[i]=xi;
	sinGrid[i]=sin(xi);
	xi+=delta;
      }
    }

  // Your sine function
  double sine(double x) {
    //std::cout<<"The right sine was called"<<std::endl;
    double Q[n_interp][n_interp];
    x=fmod(x,2*3.141592653);
    //initialize the Q matrix to 0
    for(int i=0; i<n_interp; i++) {
      for(int j=0; j<n_interp; j++) {
	Q[i][j]=0;
      }
    }

    //initialize the leftmost column to the known values
    for(int i=0; i<n_interp; i++) {
      Q[i][0]=sinGrid[i];
    }
      
    //do the neville algorithm
    for(int i=1; i<n_interp; i++) {
      for(int j=1; j<=i; j++) {
	Q[i][j]=((x-xGrid[i-j])*(Q[i][j-1]) 
		 - (x-xGrid[i])*(Q[i-1][j-1]))/
	  (xGrid[i]-xGrid[i-j]);
      }
    }

    /*
      printf("Q matrix:\n");
      for (int i = 0; i < n_interp; i++) {
      for (int j = 0; j < n_interp; j++) {
      printf("%9f ", Q[i][j]);
      }
      printf("\n");
      }*/
    return Q[n_interp-1][n_interp-1];
  }

};
#endif
