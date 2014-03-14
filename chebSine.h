#ifndef _CHEB_TEST_H_
#define _CHEB_TEST_H
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>

using namespace std;

class ChebSine : public SinePrototype
{
    public:
        int **MAT;
        double *C;
        int N;
        double *powerX;

        // Overload the constructor
        ChebSine(const int n)
        {
            N = n;
            powerX = new double[N];
            stringstream ss;
            ss << "python cheby_gen.py ";
            ss << n;
            string s = ss.str();

            system(s.c_str());
            sleep(0.5);
            parseFile("coeffs.dat");
        }

        ~ChebSine() {
            delete []MAT;
            delete C;
            delete powerX;
        }

        void parseFile(string filename) {
            ifstream file(filename.c_str());

            MAT = new int*[N];
            for (int i = 0; i < N; i++) {
                MAT[i] = new int[N];
            }

            for (int i = 0; i < N; i++)
                for (int j = 0; j < N; j++)
                    file >> MAT[i][j];

            C = new double[N];
            for (int i = 0; i < N; i++)
                file >> C[i];
        }


        // Overload the function with your function
        virtual double sine(double x) {
	    int greater = 0;
	    if(x > M_PI){
		    greater = 1;
   		    x -= M_PI;
	    }

        if (x > M_PI/2.0) {
            x = M_PI - x;
        }

            double curr = 1.0;
            powerX[0] = curr;
            for (int i = 1; i < N ; i++) {
                curr *= x;
                powerX[i] = curr;
            }

            double sineX = 0.0;
            double sum = 0.0;
            int start = 0;

            for (int j = 0; j < N ; j++) {
                int *row = MAT[j];
                for (int k = start; k <= j; k += 2) {
                    sum += row[k] * powerX[k];
                }
                sineX += C[j]*sum;
                sum = 0;
                start = 1 - start;
            }
	    
	    if (!greater)
                 return sineX - C[0] / 2.0;
	    return -(sineX - C[0] / 2.0);
        }
};
#endif
