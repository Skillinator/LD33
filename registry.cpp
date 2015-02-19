#include <iostream>
#include <ctime>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "SOIL.h"
#include "skilLib.h"
#include "systems.h"
#include "components.h"
#include "messages.h"


std::vector<std::string> split(std::string input, char delim){
	std::stringstream stream(input);
	std::vector<std::string> tmp;
	std::string item;

	while(std::getline(stream, item, delim)){
		tmp.push_back(item);
	}
	return tmp;
}



Registry::Registry(){

}

bool Registry::Register(Component* c, std::string name){
	for(int x = 0; x < components.size(); x++){
  		if(name.compare(components.at(x).name) == 0){
	 		components.at(x).seed = c;
    		return true;
   		}
   	}

   	return true;
}

bool Registry::declare(std::string name, std::vector<std::string> signatures){
	for(int x = 0; x < components.size(); x++){
  		if(name.compare(components.at(x).name) == 0){
  			// Do nothing, component already declared
    		return false;
   		}
   	}

	components.push_back(RegComponent(name, signatures));
	return true;
}

Component* Registry::getComponent(std::string args){
	std::string signature;
	std::vector<std::string> arguments = split(args, ' ');
	std::string name = arguments.at(0);


	for(int x = 1; x<arguments.size(); x++){
		std::string tmp=arguments.at(x);

		if(tmp[0] == '\'' || tmp[0] == '"'){
			signature.push_back('s');
		}else if(tmp == "true"){
			signature.push_back('b');
		}else if(tmp == "false"){
			signature.push_back('b');
		}else if(tmp.find('.') == std::string::npos){
			try {
				int tmpint = std::stoi(tmp);
				if(std::to_string(tmpint) == tmp){
					signature.push_back('i');
				}else{
					signature.push_back('s');
				}
			}
			catch (...) {
				signature.push_back('s');
			}
		}else{
			try {
				float tmpfloat = std::stof(tmp);
				if(std::to_string(tmpfloat).substr(0,tmp.size()) == tmp){
					signature.push_back('f');
				}else{
					signature.push_back('s');
				}
			}
			catch (...) {
				signature.push_back('s');
			}

		}
	}
	
	for(int x = 0; x < components.size(); x++){

  		if(name.compare(components.at(x).name) == 0){
  			std::cout<<"Component " << name << " Found!\n";
  			std::vector<std::string> sigs = components.at(x).signatures;
  			for(int y = 0; y < sigs.size(); y++){
  				if(sigs.at(y).compare(signature) == 0){
  					return components.at(x).seed->spawn(signature, args);
  				}
  			}
   		}else{
   			std::cout<<"Mismatch for Component " << name << "\n";
   		}
   	}
   	std::cout<<"failed to match";

}
