//************************************************************
//	Pade approximation of sin(x) from 0 to 2Pi				//
//	"padetable.h" contains pre-computed	(by MatLab) 		//
//	pade coefficients  in	numerator/denominator.			//
//	Here we set M=N for the numerator and denominator      	//
//	polynomial order. The total order this supports is      //
//  1 to 18.                                                //
//	This class has a method "changerange(double&)"	    	//
//	learnt from previous group "Ghost of Coco"              //
//  to increase accuracy.		                            //
//	It takes in x and casts it back into 0->Pi/2.			//
//															//
//	======================================					//
//	variables:										        //
//	======================================					//
//	N:		number of total terms in polynomials			//
//			= (M+N)	                    					//
//	size:	maximum of the number of terms in numerator and //
//			denominator (the # of terms are not the same)   //
//          especially when N is an odd number              //
//	invR:	pre-computed value of 2/Pi						//
//	endR:	pre-computed value of 2*Pi						//
//															//
//	Run      												//
//	======================================					//
//	Call PadeSine(const int nn)			                	//
//	change N to set different orders of the approximation	//
//															//
//	======================================================	//
//	Group:	MatLab2     									//
//	Date:	Feb 26 2014										//
//************************************************************

#ifndef _PADESINE_H_
#define _PADESINE_H_
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include "sineTest.h"
#include "padetable.h"

struct PadeSine : SinePrototype
{
	private:
	int N;
	int size;   	
	double invR;
	double endR;
	vector <double> Numerator;
	vector <double> Denominator;
	void changerange(double &);	
	
	public:
	// Class Constructor
	PadeSine(const int nn) : SinePrototype()  
	{
	invR=2./M_PI;
	endR=2.*M_PI;
	
   	N=nn;
	int sizeNum=Num[N-1][0];
	int sizeDen=Den[N-1][0];
	size = max(sizeNum,sizeDen);	
	
	Numerator.resize(size);
	Denominator.resize(size);
	
	for(int i=1;i<=size;i++){
	Numerator[i-1]=Num[N-1][i];
	Denominator[i-1]=Den[N-1][i]; 
	}
	}//end constructor
		
    	// Your sine function
	double sine(double x) {
	double sumN=0.,sumD=0.;
	//range reduction:
	changerange(x);	
		
	//Build Numerator: 
	double para = 1; 
	for(int i=0;i<size;i++){
		sumN += para*Numerator[i]; 
		sumD += para*Denominator[i];
		para *= x; 
		
	}
	return sumN/sumD;	
	}//end sine(x)
	
		
}; //end class

inline void PadeSine::changerange(double &x){
switch((int)(invR*x)){
case 0:
	return; 
case 3:
	x-=endR;
	return; 
default: 
	x=M_PI-x; 
	return;
}
}	

#endif

