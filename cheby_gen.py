from numpy import *
import math
import time 
import sys

# Creates an NxN matrix of chebychev polynomial coefficients - one polynomial per row
# Input: number of chebychev polynomials to be used
# Output: 
def gen_matrix(n):
    if not n > 1:
        print "Please provide some n > 1"
        return

    a = zeros( (n,n) ) # initialize matrix of zeros

    a[0,0] = 1  # set a[0,0] and a[1,1] to one
    a[1,1] = 1

    for i in range(2,n):   # fill in the diagonal
        a[i,i] = 2*a[i-1,i-1]


    for i in range(2,n):   # fill in the first column
        a[i,0] = -a[i-2,0]

    for i in range(2,n):   # fill in the rest of the non-zero elements
        for j in range(1,n):
            if i > j:
                a[i,j] = 2*a[i-1,j-1] - a[i-2,j]

    f = open('coeffs.dat', 'w+')

    for i in xrange(0, n):
        for j in xrange(0, n):
            f.write(str(int(a[i, j])) + ' ')
        f.write('\n')

    f.close()

def cc(n):
    a = 0
    b = 2*math.pi
    f = open("coeffs.dat", 'a')
    for j in range (0,n):
        total = 0
        for k in range (0,n):
            #y = (k-.5*(a+b))/(.5*(b-a))
            fxk = math.cos(math.pi*(k+0.5)/n)
            fxkj = math.cos(math.pi*j*(k+0.5)/n)

            #fy = (fxk - .5*(b-a))/(.5 * (b+a))
            #fyj = (fxkj - .5*(b-a))/(.5 * (b+a))
            
            v = math.sin(fxk)*fxkj
            total += v

        cj = total*(2.0/n)
        f.write(str(cj) + " ")

    f.write('\n')
    f.close()

if len(sys.argv) < 2:
    print "Not enough arguments supplied"
else:
    try:
        n = int(sys.argv[1])
    except:
        print "Bad argument supplied:", sys.argv[1]
    gen_matrix(n)
    cc(n)
