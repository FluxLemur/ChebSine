#ifndef _LSQ_SINE2_H_
#define _LSQ_SINE2_H_
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "sineTest.h"
#include <Eigen/Dense>

using Eigen::MatrixXf;
using Eigen::JacobiSVD;
using namespace Eigen;

// In c++, structs are much like classes, except they default to public
// class LinearSine : public SinePrototype would also work here
struct LsqSine2: SinePrototype
{
  private:
    vector<double> va;
    int N;
    int numPoints;

  public:
    // Define your functions here 
    // Class Constructor
    LsqSine2(const int nn, const int npoint) : SinePrototype()  
  {
    N=nn;
    numPoints=npoint;
    va.resize(N);
    VectorXd y = VectorXd::Zero(numPoints);
    MatrixXd vand(numPoints,N);
    MatrixXd legen(N,N);

    for(int i=0;i<numPoints;i++) {
      double x_i = (-numPoints + 2.0*i)/numPoints;
      y(i) = sin(M_PI * x_i);
      double temp = 1.0;
      for(int j=0; j<N;j++) {
        vand(i,j) = temp;
        temp *= x_i;
      }
    }

    VectorXd p_0 = VectorXd::Zero(N);
    VectorXd p_1 = VectorXd::Zero(N);
    p_0(0) = 1;
    p_1(1) = 1;

    VectorXd p_i;
    VectorXd p_i2;
    for(int i=0;i<N;i++) {
      if(i==0) {
        p_i=p_0;
      }
      else if(i==1) {
        p_i=p_1;
        p_i2=p_0;
      }
      else {
        VectorXd xPn(N);
        for (int k=N-1;k>0;k--) {
          xPn(k) = p_i(k-1);
        }
        xPn(0) = 0;
        VectorXd tempVec = p_i;
        p_i = ((2*i-1.0)*xPn - (i-1)*p_i2)/i;
        p_i2 = tempVec;
      }
      for(int j=0;j<N;j++) {
        legen(j,i) = p_i(j);
      }
    }	

    MatrixXd A = vand*legen;
    MatrixXd B = A.transpose()*A;
    SelfAdjointEigenSolver<MatrixXd> eigensolver(B);
    VectorXd eigens = eigensolver.eigenvalues();
    double max = -1;
    double min = -1;
    for(int i = 0; i<N; i++) {
      double temp = eigens(i);
      if(max < temp) {
        max = temp;
      }
      if(min == -1 || min > abs(temp)) {
        min = temp;
      }
    }
    //cout << "CONDITION NUMBER: " << max/min << "\n";
    VectorXd coeffs = B.jacobiSvd(ComputeThinU | ComputeThinV).solve(A.transpose()*y);
    MatrixXd vectorA = legen*coeffs;
    for (int j=0; j<N; j++) va[j]=vectorA(j,0);
  }

    // Your sine function
    double sine(double x) {
      double temp = 1.0;
      double xx=-(x-M_PI)/M_PI;
      double sum = 0;
      for(int i=0;i<N;i++) {
        sum += temp*va[i];
        temp *= xx;
      }
      return sum;
    }

};
#endif
