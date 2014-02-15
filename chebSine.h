#ifndef _CHEB_TEST_H_
#define _CHEB_TEST_H
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

class ChebSine : public SinePrototype
{
    public:
        int **MAT;
        int *C;
        int N;

        // Overload the constructor
        ChebSine(const int n)
        {
            system("python chebygen 10");
            sleep(1);
            parseFile("matrix.txt");
            N = n;
            // When you overload this constructor, use it to initialize constants
            // and array storage 
        }

        ~ChebSine() {
            delete []MAT;
        }

        void parseFile(string filename) {
            ifstream file(filename.c_str());
            MAT = new int*[N];
            for (int i = 0; i < N; i++) {
                MAT[i] = new int[i];
            }
            int t;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    file >> t;
                    MAT[i][j] = t;
                    cout << MAT[i][j] << " " ;
                }
                cout << endl;
            }
        }


        // Overload the function with your function
        virtual double sine(double x) {
            double powerX[N];
            powerX[0] = 1;
            for(int  i = 1; i < N ; i++ ){
                powerX[i] = powerX[i-1]*x; 
            }

            double sineX = 0.0;
            double sum = 0.0;
            int ref = 0;

            for(int j = 0; j < N ; j++){
                for(int k=0; k < (j/2 + 1); k++){
                    ref = k*2 + j%2; //This takes care of the odd-even alternative multiplication
                    sum += MAT[j][ref]*powerX[ref];
                }
                sineX += C[j]*sum;
                sum = 0;
            }

            return sineX;
        }
};
#endif
