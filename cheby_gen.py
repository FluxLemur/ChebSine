from numpy import *
import math
import time 
import sys

# Creates an NxN matrix of chebychev polynomial coefficients - one polynomial per row
# Input: number of chebychev polynomials to be used
# Output: 
def gen_matrix(n):

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

if len(sys.argv) < 2:
    print "Not enough arguments supplied"
else:
    try:
        n = int(sys.argv[1])
    except:
        print "Bad argument supplied:", sys.argv[1]
    gen_matrix(n)
