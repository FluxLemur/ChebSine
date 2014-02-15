#include "sineTest.h"
#include "chebSine.h"


using namespace std;

int main() {
    ChebSine cheb(10);
    for (double x = 0.0; x < 2*3.14159; x += 0.01)
        cout << x << " " << cheb.sine(x) << endl;

    return 0;
}
