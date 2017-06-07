
#ifndef INPUT_OUTPUT_HPP
#define INPUT_OUTPUT_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <memory>

#include <Eigen/Dense>
#include "dist/json/json.h"
#include "options.hpp"

using namespace Eigen;

class InputOutput{
	
public:
	
	std::string config_name;
	
	//constructor
	InputOutput(std::string cfg): config_name(cfg){}
	
	//destructor
	~InputOutput(){}
	
	
	
	//write to file
	//writes data in columns with given headers
	void WriteResults(const std::string& filename,const std::vector<std::string>& headers, 
	const MatrixXf& data){
		std::ofstream myfile;
		std::string filetype = ".txt";
		
		myfile.open(filename+filetype);
		for(auto it = headers.begin(); it!=headers.end(); it++){
			myfile << *it<< ",";
		}
		myfile << std::endl;
		for(int i = 0; i < data.rows(); i++){
			for(int j =0; j < data.cols(); j++){
				myfile << data(i,j) << ", "; 
			}
			myfile << std::endl;
			
		}
		myfile.close();
	}
	
	
	//read configuration given configuration object
	Options ReadConfig(){
		
		Options opt;
		
		std::ifstream ifs(config_name);
		Json::Reader reader;
		Json::Value obj;
		reader.parse(ifs, obj); // reader can also read strings
		
		//the save file name 
		std::string save_name = obj["save_file"].asString();
		float U = obj["U"].asFloat();
		float t = obj["t"].asFloat();
		float k_min = obj["k_min"].asFloat();
		float k_max = obj["k_max"].asFloat();
		int n_T = obj["n_T"].asInt();
		opt.mu_min = obj["mu_min"].asFloat();
		opt.mu_max = obj["mu_max"].asFloat();
		opt.n_mu = obj["n_mu"].asInt();
		opt.plotting = obj["plotting"].asInt();
		opt.max_iter = obj["max_iter"].asInt();
		opt.xDelta = obj["xDelta"].asFloat();
		opt.fDelta = obj["fDelta"].asFloat();
		opt.condition = obj["condition"].asFloat();
		opt.delta0 = obj["delta0"].asFloat();
	
		
		//saving the basis vectors from config
		Json::Value& basis = obj["basis_vectors"];
		
		int dim = basis.size();
		
		MatrixXf basis_vectors(dim,dim );
		for (int i = 0; i < basis.size(); i++) {
			float x = basis[i]["x"].asFloat();
			float y = basis[i]["y"].asFloat();
			basis_vectors.col(i) << x,y;
		}
		
		//saving t_matrix
		Json::Value& t_mat = obj["t_matrix"];
		int bands = t_mat.size();
		MatrixXf t_matrix(bands,bands );	
		for (int i = 0; i < bands; i++) {
			for (int j = 0; j < bands; j++){
				t_matrix(i,j) = t_mat[i][j].asFloat();
			}
		}
		

		//saving R matrix
		Json::Value& R_mat = obj["r_matrix"];

		/* for lattices that have n different couplings between same lattice sites,
		  the different couplings are stored in r_matrix and all the different couplings 
		  are stored in r_matrix_vector
		 */
		std::vector<std::shared_ptr<MatrixXf>> r_matrix_vector;
		
		MatrixXf r_matrix(bands*dim,bands );
		//i goes from 0 to bands
		int most_comps = 0;
		for (int i = 0; i < bands; i++) {
			//j goes from 0 to bands
			for (int j = 0; j < bands; j++){
				
				Json::Value& components = R_mat[i][j];
				for(int n=0; n < components.size(); n++){
					
					//the length of r_matrix_vector is increased when we notice more couplings exist
					//initialize it to zeros
					if( n == most_comps) {
						std::shared_ptr<MatrixXf> point (new MatrixXf(bands*dim,bands ));
						*point = MatrixXf::Zero(bands*dim,bands);
						r_matrix_vector.push_back(point);
						most_comps += 1;
					}

					//r_matrix = MatrixXf::Zero(bands*dim,bands);
					MatrixXf vec = MatrixXf::Zero(dim,1);
					
					for(int m=0; m < components[n].size(); m++){
						float factor = components[n][m]["factor"].asFloat();
						vec += factor*basis_vectors.col( components[n][m]["b_vec"].asInt()-1 ) ;					
					}
					(*r_matrix_vector[n]).block(i*dim,j,dim,1) << vec;
					
					//r_matrix.block(i*dim,j,dim,1) << vec;
					//std::shared_ptr<MatrixXf> point (new MatrixXf(bands*dim,bands ));
					//*point = r_matrix;
					//r_matrix_vector.push_back(point);
				}
			}
		}
		std::cout << "r_matriisit, koko: " << r_matrix_vector.size() << std::endl;
		for (int i = 0; i < r_matrix_vector.size(); i++){
			std::cout << *r_matrix_vector[i] << std::endl;
		}
		
		
		//saving read values to option object
		opt.save_file = save_name;
		opt.U = U;
		opt.t = t;
		opt.dim = dim;
		opt.bands = bands;
		opt.k_min = k_min;
		opt.k_max = k_max;
		opt.n_T = n_T;
		
		opt.basis = basis_vectors;
		opt.R = r_matrix_vector;
		opt.t_matrix = t_matrix;
		
		
	
		return opt;
		
		
		//std::cout << "basis\n" << basis_vectors << std::endl;
		//std::cout << "t_matrix\n" << t_matrix << std::endl;
		//std::cout << "R matrix\n" << r_matrix << std::endl;
	}
	
};














#endif