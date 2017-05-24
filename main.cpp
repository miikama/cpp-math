
#include <utility>
#include <iostream>
#include <vector>

#include <Eigen/Dense>

#include "lattice.hpp"
#include "input_output.hpp"
#include "options.hpp"

using namespace Eigen;



int main() {
	
	//the simulation input/output
	InputOutput simuIO = InputOutput("kagome_config.json");
	
	
	//readconfig would ideally return an option object which has all the parameters used here
	Options opt = simuIO.ReadConfig();
	
	//lattice spacing
	int d = 1;
	
	//hopping
	float t = opt.t;
	
	//on-site energy
	float U = opt.U;
	
	//dimensionality
	int bands = opt.bands;	
	int dim = opt.dim;
	
	double mu_up= 4;
	double mu_down = 4;
	
	//temperature
	int NT = 15;
	VectorXf T= VectorXf::LinSpaced(NT,1,10);
	
	//creating the lattice
	Lattice lattice = Lattice(opt.basis, opt.R, opt.t_matrix);	
	
	std::cout << "basis:\n" << opt.basis << std::endl;
	std::cout << "R:\n" << opt.R << std::endl;
	std::cout << "t:\n" << opt.t_matrix << std::endl;
	
	MatrixXf dispersionandk = lattice.CalculateDispersion();
	
	
	
	//writing the results to file
	std::vector<std::string> headers;
	headers.push_back("kx");headers.push_back("ky");
	headers.push_back("E1");headers.push_back("E2");headers.push_back("E3");
	simuIO.WriteResults("testi", headers, dispersionandk);
	
	
	
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

































