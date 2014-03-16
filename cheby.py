from numpy import *
import math
import time 

N=10   # Number of chebychev polynomials to use in the approximation. Can change this
x=pi    # Place to evaluate the function. This should be an input parameter when calling the program

# Returns an NxN matrix of chebychev polynomial coefficients - one polynomial per row
# Input: number of chebychev polynomials to be used
def get_matrix(n):
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

	return a

# Returns an array of length n containing the chebychev coefficients
# Input: number of chebychev polynomials to be used
def cc(n):
        t0 = time.time()
        chebArray = []

        for j in range (0,n):
                sum = 0
                for k in range (0,n):
                        v = math.sin(math.cos(math.pi*(k+0.5)/n))*math.cos(math.pi*j*(k+0.5)/n)
                        sum += v
                cj = sum*(2.0/n)
                chebArray.append(cj)
        t1 = time.time()
#        print str(t1 - t0)

        return chebArray

# Returns an array of length N containing 1, x, x**2,...
# Input: number of chebychev polynomials to be used and the point to evalute
def x_vector(n, x):
	xArray = []
	for i in range(0, n):
		temp = x**i
		xArray.append(temp)
		
	return xArray


############# Begin script ############

# Get the matrix of chebychev polynomial coefficients
a = get_matrix(N)

# Get the vector of coefficients
b = cc(N)

# Get the vector of x's
c = x_vector(N, x)

# Get the sum
sum = 0
for i in range(0, N-1):
    term = b[i]*(dot(a[i,:],c))
    sum = sum + term

# Print the approximation of sin(x)
val = sum - b[0]/2.0
print "sin(x): %f" % val
print "error:  %f" %(sin(x) - val)
