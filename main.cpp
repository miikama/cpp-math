
#include <utility>
#include <iostream>
#include <vector>

#include <Eigen/Dense>


#include "lattice.hpp"
#include "input_output.hpp"
#include "options.hpp"
#include "crit_temperature_solver.hpp"
#include "gnuplot-iostream/gnuplot-iostream.h"

using namespace Eigen;


class MyFunction : public cppoptlib::Problem<float> {
	//using typename cppoptlib::Problem<double>::Scalar;
	//using typename cppoptlib::Problem<double>::TVector;
	
public:
	float value(const cppoptlib::Problem<float>::TVector& x){
		float result = 0;
		for( int i = 0; i < x.size(); i++){
			result += x(i)*x(i);			
		}
		return result;
	}
	
};


int main(int argc, char *argv[]) {
	
	//enables giving config file as command line argument
	std::string config_name = "kagome_config.json";
	if(argc > 1 ){
		config_name = argv[1];
	}
	
	//the simulation input/output
	InputOutput simuIO = InputOutput(config_name);	
	
	//readconfig returns a config object opt, that contains data read from json config file
	Options opt = simuIO.ReadConfig();


	//dimensionality
	int bands = opt.bands;	
	int dim = opt.dim;

	//creating the lattice
	Lattice lattice = Lattice(opt.basis, opt.R, opt.t_matrix);	
	
	std::cout << "basis:\n" << opt.basis << std::endl;
	//std::cout << "R:\n" << opt.R << std::endl;
	std::cout << "t:\n" << opt.t_matrix << std::endl;
	
	MatrixXf dispersionandk = lattice.CalculateDispersion(opt.k_min, opt.k_max);
	
	//moving on to free energy
	CritTemperatureSolver tcsolver(lattice,opt);
	
	//initial guess for minimizing delta
	VectorXf delta = 0.1*VectorXf::Ones(bands);

	tcsolver.free_energy_functional.minimize(tcsolver.free_energy,delta);
	
	//testing minimizing delta for one T
	//MatrixXf min_delta = tcsolver.MinimizeDelta(0.1, 1.0);

	//testing on looping over temperatures
	//tcsolver.LoopT(opt.mu_max);
	
	//testing on looping over chemical potentials
	tcsolver.LoopMu();
	
	
	//writing the results to file
	std::vector<std::string> headers;
	headers.push_back("kx");headers.push_back("ky");
	headers.push_back("E1");headers.push_back("E2");headers.push_back("E3");
	simuIO.WriteResults("testi", headers, dispersionandk);
	
	lattice.SaveKineticHamiltonians(opt.k_min, opt.k_max);
	
	
	MyFunction f;
	cppoptlib::BfgsSolver<MyFunction> solver;
	VectorXf x(3); x << 2,3,4;
	solver.minimize(f,x);
	
	
	
	
	
}


/* 	//lattice basis vectors
	Vector2f a1, a2;
	a1 << 1,0;
	a2 << 0.5, sqrt(3)/2;
	
	a1 = a1*d;
	a2 = a2*d;
	
	MatrixXf B(2,2);
	B.col(0) << a1;
	B.col(1) << a2;
	
	
	//gathering the coupling vectors
	//  R = r_aa r_ba r_ca
	//		r_ab r_bb r_cb
	//		r_ac r_bc r_cc
		
	Vector2f r_AB = a1/2;
	Vector2f r_BA = -r_AB;
	Vector2f r_AC = a2/2;
	Vector2f r_CA = -r_AC;
	Vector2f r_CB= (a1-a2)/2;
	Vector2f r_BC = -r_CB;
	
	MatrixXf R(dim*bands,bands);
	R << Vector2f::Zero(dim) , r_BA, r_CA,
		r_AB, Vector2f::Zero(dim), r_CB,
		r_AC, r_BC, Vector2f::Zero(dim); 

		
	// Hopping matrix	
	//t = tAA tBA tCA
	//	tAB tBB tCB
	//	tAC tBC tCC	
	
	MatrixXf t_matrix(bands,bands);
	t_matrix << 0, -t,-t,
				-t, 0, -t,
				-t, -t, 0; */

































