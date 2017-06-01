
#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <Eigen/Dense>

using namespace Eigen;

class Options{
	
public:
	Options(){}
		
	~Options(){}
	
	//save file name
	std::string save_file;
	
	//lattice spacing
	int d = 1;
	
	//hopping
	float t = 3;
	
	//on-site energy
	float U = 4*t;
	
	//dimensionality
	int bands = 3;	
	int dim = 2;
	
	//chemical potential
	float mu_up= 4;
	float mu_down = 4;
	
	//range of calculated k values
	float k_min = 0;
	float k_max = 2*3.14;
	
	//lattice basis vectors
	MatrixXf basis;
	
	//matrix containing coupling between A -> B
	MatrixXf t_matrix;
	
	//contains all vector pointing from A -> B
	MatrixXf R;
	
};


#endif