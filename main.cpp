#include "matrix.hpp"

#include <utility>
#include <iostream>


int main() {
	
	Vec2<double> a = Vec2<double>(std::make_pair(2,1) );
	
	Vec2<double> b = Vec2<double>(2,2);
	
	std::cout << "first vector: " << a << std::endl;
	
	std::cout << "second vector: " << b << std::endl;
	
	Vec2<double> c= a- b;
	
	c+= a;
	
	Vec2<double> d = -b;
	
	d = 1.0*d + -b;
	
	std::cout << "sum vector: " << c << std::endl;
	
	std::cout << "vector d: " << d << std::endl;
	
	
	
	return 0;
	
}
