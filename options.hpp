
#ifndef OPTIONS_HPP
#define OPTIONS_HPP

#include <memory>
#include <vector>

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
	float t = 1;
	
	//on-site energy
	float U = -3*t;
	
	//dimensionality
	int bands = 3;	
	int dim = 2;
	
	//chemical potential
	float mu_up= 1;
	float mu_down = 1;
	
	//range of calculated k values
	float k_min = 0;
	float k_max = 2*3.14;
	
	//number of temperatures
	int n_T = 1;
	
	//min and max chemical potential and number of points
	float mu_min = -3;
	float mu_max = 3;
	int n_mu = 1;
	
	//do you want to plot 1 yes, 0 no
	int plotting = 1;
	
	//minimization options
	int max_iter = 300;
	float xDelta = 0.005;
	float fDelta = 0.005;
	float condition = 0.0005;
	float delta0 = 0.001;
	
	//lattice basis vectors
	MatrixXf basis;
	
	//matrix containing coupling between A -> B
	MatrixXf t_matrix;
	
	//contains all vector pointing from A -> B
	std::vector<std::shared_ptr<MatrixXf>> R;
	
};


#endif