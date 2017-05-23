#include "matrix.hpp"

#include <utility>
#include <iostream>
#include <vector>

#include <Eigen/Dense>

#include "lattice.hpp"
#include "input_output.hpp"

using namespace Eigen;



int main() {
	
	//the simulation input/output
	InputOutput simuIO = InputOutput("kagome_config.cfg");
	
	simuIO.ReadConfig();
	
	//lattice spacing
	int d = 1;
	
	//hopping
	double t = 3;
	
	//on-site energy
	double U = 4*t;
	
	//dimensionality
	int bands = 3;
	
	int dim = 2;
	
	double mu_up= 4;
	double mu_down = 4;
	
	//temperature
	int NT = 15;
	VectorXf T= VectorXf::LinSpaced(NT,1,10);
	
	
	
	
	//lattice basis vectors
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

		
	/** Hopping matrix	
	t = tAA tBA tCA
		tAB tBB tCB
		tAC tBC tCC	
	**/
	MatrixXf t_matrix(bands,bands);
	t_matrix << 0, -t,-t,
				-t, 0, -t,
				-t, -t, 0;
	
	Lattice lattice = Lattice(B, R, t_matrix);	
	
	std::cout << "R:\n" << R << std::endl;
	
	
	/*VectorXf k(2);
	k << 1,0;	
	
	MatrixXcf H_kin = lattice.KineticHamiltonian(k);*/
	
	//std::cout << "H_kin:\n" << H_kin << std::endl;
	
	//lattice.EigenvaluesOneK(k);
	
	MatrixXf dispersionandk = lattice.CalculateDispersion();
	
	
	
	
	//writing the results to file
	std::vector<std::string> headers;
	headers.push_back("kx");headers.push_back("ky");
	headers.push_back("E1");headers.push_back("E2");headers.push_back("E3");
	simuIO.WriteResults("testi", headers, dispersionandk);
	
	
	
}

































