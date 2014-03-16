//#ifndef _LINEAR_SINE_H_
//#define _LINEAR_SINE_H_
#ifndef _CHEBFUN_SINE_H_
#define _CHEBFUN_SINE_H_

#include <cmath>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iostream>
#include "sineTest.h"

// In c++, structs are much like classes, except they default to public
// class LinearSine : public SinePrototype would also work here

// Compute chebyshev interpolation using codes in numerical recipe
struct ChebfunSine : SinePrototype
{
		//const long double M_PI = 3.141592653589793238L;

   private:
        vector<double> xx;
        vector<double> sineX;
        int Npoints;
        int Nintervals;
		vector<double> c;
		vector<double> d;//recursive definition for coefficients of Chebfun

	vector<double> coefs;

    public:
    // Define your functions here 
    // Class Constructor
	
	//nn is the number of interpolation points, nn must be between 5 and 30 inclusive
		ChebfunSine(const int nn) : SinePrototype()  
    {
        // Initialize and prepare interpolation of sine
		
		//Generate coefficients for Chebychev interpolant
        //Npoints = nn ;
		
		//xx.resize(Npoints);
        //sineX.resize(Npoints);
		  //d.resize(Npoints+2);//
		//d[Npoints+1]=0;
	//	d[Npoints]=0;
		
		//for (int i=0;i<Npoints;i++){
		//	xx[i]=M_PI*(cos(M_PI*(2*i+1)/2./Npoints)+1.);
		//	sineX[i]=sin(xx[i]);
		//}
		

		
        //compute coefficients 
		//for (int j=0;j<Npoints;j++){
          //  c[j]=0;
           // for(int k=0;k<Npoints;k++){
            //        c[j]=c[j]+sineX[k]*cos(M_PI*j*(2*k+1)/2./Npoints);
             //   }
          //  c[j]=c[j]*2/Npoints;    
	//}		
	
	//updated, now which read in coefficients from text file
	ifstream inFile ("nonadapt_coef.txt");
	string line;
	int count,i;
	double intpart;
	double temp;
	bool dataReady=false;
	bool unfinish=true;
	while( getline(inFile,line) && unfinish )
	  {	temp=atof(line.c_str());
		if ((dataReady)  && (temp>nn)){unfinish=false;}
		if (dataReady && unfinish) {coefs.push_back(temp);}
		if (temp==nn) {dataReady=true;}
	  }
	  
	  Npoints=coefs.size();
	  c.resize(Npoints);//coefficients of Chebyshev interpolants
        d.resize(Npoints+2);//
		d[Npoints+1]=0;
		d[Npoints]=0;
	  for (int i=0;i<Npoints;i++){
			c[i]=coefs[Npoints-1-i];
		}		
    }

    // Your sine function
	double sine(double x) {
		//Evaluate Chebyshev using Clenshaw algorithm
		//rescale x
		double y;
		y=x/M_PI-1.;
	
		for (int j=Npoints-1;j>=1;j--){
            d[j]=2*y*d[j+1]-d[j+2]+c[j];
            }
        return y*d[1]-d[2]+c[0]/2.;
		
	  //double y=x/M_Pi-1.;
	  //double expterm=pow(x,coefs.size()-1);

	}

};
#endif
