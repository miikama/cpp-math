#include "matrix.hpp"

#include <utility>
#include <iostream>

#include "dlib/dlib/matrix.h"

using namespace dlib;

int main() {
	/* 
	Vec2<double> a = Vec2<double>(std::make_pair(2,1) );
	
	Vec2<double> b = Vec2<double>(2,2);
	
	std::cout << "first vector: " << a << std::endl;
	
	std::cout << "second vector: " << b << std::endl;
	
	Vec2<double> c= a- b;
	
	c+= a;
	
	Vec2<double> d = -b;
	
	d = 1.0*d + -b;
	
	std::cout << "sum vector: " << c << std::endl;
	
	std::cout << "vector d: " << d << std::endl; */
	
	
	//time for dlib matrix stuff
	
	dlib::matrix<double,3,1> y;
	
	dlib::matrix<double,3,3> M;
	
	M = 1, 2,3,
		2, 3, 4,
		4, 6, 7;
		
	y = 3,4,5;
	
	dlib::matrix<double> x = dlib::inv(M)*y;
	
	std::cout << "x: \n" << x << std::endl;		
	
	std::cout <<  "M: \n" << M << std::endl;
	
	dlib::matrix<double> A = dlib::diag(M);
	
	std::cout <<  "A: \n" << A << std::endl;	
	
	eigenvalue_decomposition<matrix<double>> B = eigenvalue_decomposition<matrix<double>>(M);
	
	//complex_matrix<std::complex<double>>  = complex_matrix<std::complex<double>>(M); // = B.get_eigenvalues();
	
	//std::cout <<  "C: \n" << A << std::endl;
	
	return 0;
	
}
