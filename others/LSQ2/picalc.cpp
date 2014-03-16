#include <cmath>
#include <ctime>
#include <iostream>
#include <limits>
#include "ttmath/ttmath.h"

using namespace std;

typedef ttmath::Big<TTMATH_BITS(64), TTMATH_BITS(1024)> MyBig;


int main()
{
    MyBig pi = 0.;
    pi.SetPi();
    MyBig b = 1.;
    int n = 100;
    double* Sn = (double*)malloc(sizeof(double)*(n+1));
    Sn[0] = 0;
    Sn[1] = b.ToDouble();
    for (int i = 2; i <= n; i+=2) {
            MyBig t = (i+1)*i;
            b = MyBig(1) - t/(pi*pi)*b;
            Sn[i] = 0;
            Sn[i+1] = b.ToDouble();

    }

    for (int i = 1; i <= n; i += 2) {
        cout << "i = " << i << ", S(i) = " << Sn[i] << endl;
    }

    return 0;
}
