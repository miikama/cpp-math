
#ifndef FREE_ENERGY_HPP
#define FREE_ENERGY_HPP

#include <Eigen/Dense>
#include "./CppNumericalSolvers/include/cppoptlib/meta.h"
#include "./CppNumericalSolvers/include/cppoptlib/problem.h"
#include "./CppNumericalSolvers/include/cppoptlib/solver/bfgssolver.h"
#include "lattice.hpp"


#include <vector>

using namespace Eigen;

class FreeEnergy : public cppoptlib::Problem<float> {
	
	
public:

	std::vector<MatrixXf*> kinetic_matrices_;
	
	Lattice lattice;
	
	FreeEnergy(const Lattice& lattice_) : cppoptlib::Problem<float>(), lattice(lattice_){}

	float value(const cppoptlib::Problem<float>::TVector& x){
		float result = 0;
		for( int i = 0; i < x.size(); i++){
			result += x(i)*x(i);			
		}
		return result;
	}
	
	
	
	
};







#endif