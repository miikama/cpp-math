
#ifndef INPUT_OUTPUT_HPP
#define INPUT_OUTPUT_HPP

#include <iostream>
#include <fstream>

#include <Eigen/Dense>
#include "dist/json/json.h"

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
	void ReadConfig(){
		
		std::ifstream ifs("kagome_config.cfg");
		Json::Reader reader;
		Json::Value obj;
		reader.parse(ifs, obj); // reader can also read strings
		const Json::Value& characters = obj["characters"]; // array of characters
		for (int i = 0; i < characters.size(); i++){
			std::cout << "    name: " << characters[i]["name"].asString();
			std::cout << " chapter: " << characters[i]["chapter"].asUInt();
			std::cout << std::endl;
		}
		Json::Value& basis = obj["basis_vectors"];
		
		int a1x = basis["a1"]["x"].asUInt();
		int a1y = basis["a1"]["y"].asUInt();
		Eigen::Vector2i a1;
		a1 << a1x,a1y;
		
		std::cout << "ai\n" << a1 << std::endl;
	}
	
};














#endif