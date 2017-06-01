
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
		for (int i = 0; i < bands; i++) {
			for (int j = 0; j < bands; j++){
				MatrixXf vec = MatrixXf::Zero(dim,1);
				Json::Value& components = R_mat[i][j];
				for(int m=0; m < components.size(); m++){
					float factor = components[m]["factor"].asFloat();
					vec += factor*basis_vectors.col( components[m]["b_vec"].asInt()-1 ) ;					
				}
				r_matrix.block(i*dim,j,dim,1) << vec;				
			}
		}
		
		
		//saving read values to option object
		opt.save_file = save_name;
		opt.U = U;
		opt.t = t;
		opt.dim = dim;
		opt.bands = bands;
		opt.k_min = k_min;
		opt.k_max = k_max;
		
		opt.basis = basis_vectors;
		opt.R = r_matrix;
		opt.t_matrix = t_matrix;
		
		
	
		return opt;
		
		
		std::cout << "basis\n" << basis_vectors << std::endl;
		std::cout << "t_matrix\n" << t_matrix << std::endl;
		std::cout << "R matrix\n" << r_matrix << std::endl;
	}
	
};














#endif