
#ifndef LATTICE_HPP
#define LATTICE_HPP

#include <vector>
#include <utility>
#include <complex>

#include <Eigen/Dense>

/**  class representing a general lattice structure
	parameters
		- lattice basis vectors
		- which lattice sites are coupled	
*/

using namespace Eigen;



//a structure given for making the lattice 
struct basis{
	//matrix that contains basis indexes
	std::vector<std::pair<int,double>> pairing;		
};

class Lattice{
	
public:
	
	//lattice basis vectors
	MatrixXf basis_vectors;
	
	//closest particle vectors 
	//  R = r_aa r_ba r_ca
	//		r_ab r_bb r_cb
	//		r_ac r_bc r_cc
	MatrixXf R;
	
	
	//t_matrix << 0, -t,-t,
	//			-t, 0, -t,
	//			-t, -t, 0;
	MatrixXf t_matrix;
	
	//the k_values of the first brillouin zone
	
	int bands;
	int dim;
	
	const std::complex<float> IF = std::complex<float>(0.0f, 1.0f); 
	
	//constructor 
	Lattice(const MatrixXf& basis, const MatrixXf& r, const MatrixXf& t_mat) : 
		basis_vectors(basis), bands(t_mat.cols()), dim(basis.cols()),
		R(r), t_matrix(t_mat) {}	
	
	//destructor
	~Lattice() {};
	
	
	//calculates the kinetic hamiltonian for a given k
	MatrixXcf KineticHamiltonian(const VectorXf& k){
		MatrixXcf H_kin(bands,bands);
		for(int i = 0; i<bands; i++){
			for(int j =0; j< bands; j++){

				//make a complex 1by1 matrix
				MatrixXcf dot_ra(1,1);
				//fill the imaginary part with i*dot(k*r_ab)
				dot_ra.imag() = ( R.block(i*dim,j,dim,1).transpose() * k );				
				dot_ra.real() = MatrixXf::Zero(1,1);
				
				//taking the term to direction -r_ab 
				MatrixXcf neg_dot_ra = dot_ra;				
				neg_dot_ra.imag() = -neg_dot_ra.imag();
				
				//summing the exponentials
				MatrixXcf coupling = dot_ra.array().exp() + neg_dot_ra.array().exp();
				
				//the coupling is multiplied by corresponding t
				H_kin.block(i,j,1,1) = -t_matrix(i,j) * coupling;
				
			}
		}
		return H_kin;	
	}
	
	
	//solves the eigenvalues of one k by selfadjointeigensolver of Eigen package
	//@return: column vector of eigenvalues with smallest eigenvalue first
	MatrixXf EigenvaluesOneK(const VectorXf& k){
		
	
		
		SelfAdjointEigenSolver<MatrixXcf> es(bands);
		
		es.compute(KineticHamiltonian(k));		
		
		return es.eigenvalues();
		
	}
	
	//calculates the dispersion over the first brillouin zone
	//returns a matrix of [kx ky E1 E2 E3]
	MatrixXf CalculateDispersion(const float& k_min, const float& k_max){
		
		int Nk = 20;
		VectorXf kx = VectorXf::LinSpaced(Nk,k_min,k_max);
		VectorXf ky = VectorXf::LinSpaced(Nk,k_min,k_max);
		
		MatrixXf k_values(Nk*Nk, dim);
		
		MatrixXf Energies(Nk*Nk, bands);

		for(int i = 0; i<Nk ; i++){
			for(int j = 0; j<Nk; j++){
				MatrixXf k(1,dim);
				k << kx(i),ky(j);
				k_values.row(i*Nk + j) = k;

				Energies.row(i*Nk + j) = EigenvaluesOneK(k.transpose()).transpose();
				
			}
		}
		
		MatrixXf returnable(Nk*Nk,dim+bands);
		returnable.leftCols(dim) = k_values;
		returnable.rightCols(bands) = Energies;
		return returnable;
		
	}
	
		
};










#endif