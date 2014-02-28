# Makefile for interpolation template
#
# Add your headerfile to the sineTest: line.

sineTest: sineTest.h sineTest.cpp chebSine.h LinearSine.h
	g++ -O3 -o sineTest sineTest.cpp

errorTest: sineTest.h errTest.cpp chebSine.h LinearSine.h
	g++ -O3 -o errTest errTest.cpp

all: sineTest

clear:
	rm -f sineTest
	rm -f errorTest
