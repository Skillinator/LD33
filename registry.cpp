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

bool is_number(std::string s){
	for(int x = 0; x < s.size(); x++){
		if(s[x] >= 45 && s[x] <= 57 && s[x] != 47){
			// could still be a number
		}else{
			return false;
		}
	}
	return true;
}

std::vector<std::string> split(std::string input, char delim){
	std::stringstream stream(input);
	std::vector<std::string> tmp;
	std::string item;

	while(std::getline(stream, item, delim)){
		tmp.push_back(item);
	}
	return tmp;
}

std::vector<std::string> splitForStrings(std::string input, char delim){
	std::vector<std::string> arguments = split(input, delim);
	int openQuote;
	int quoteChar;
	for(int x = 1; x < arguments.size(); x++){
		if((arguments[x][0] == '"' || arguments[x][0] == 39)){
			openQuote = x;
			quoteChar = arguments[x][0];
			if(!(arguments[x][arguments[x].size()-1] == '"' || arguments[x][arguments[x].size()-1] == 39)){

				x++;
				while(arguments[x][arguments[x].size()-1] != quoteChar){
					arguments[openQuote] = arguments[openQuote] + " " + arguments[x];
					arguments.erase(arguments.begin()+x);
				}
				arguments[openQuote] = arguments[openQuote] + " " + arguments[x];
				arguments.erase(arguments.begin()+x);
			}
			arguments[openQuote] = arguments[openQuote].substr(1, arguments[openQuote].size()-2);
		}
	}
	return arguments;

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

   	return false;
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

RegTexture* Registry::getTexture(std::string name){
  for(int x=0; x< unmappedTextures.size(); x++){
    if(unmappedTextures.at(x).name == name){
      return &unmappedTextures.at(x);
    }
  }
  return &unmappedTextures.at(0);
}

RegTextureMapped* Registry::getTextureMapped(std::string name){
  for(int x=0; x<mappedTextures.size(); x++){
    if(mappedTextures.at(x).name == name){
      return &mappedTextures.at(x);
    }
  }
  std::cout<<"Error: Mapped Texture '"<<name<<"' not found. Using default.\n";
  return &mappedTextures.at(1);
}

Component* Registry::getComponent(std::string args){
	std::string signature;
	std::vector<std::string> arguments = splitForStrings(args, ' ');

	std::string name = arguments.at(0);

	for(int x = 1; x<arguments.size(); x++){

		std::string tmp=arguments.at(x);

		if(tmp[0] == '\'' || tmp[0] == '"'){
			signature.push_back('s');
		}else if(tmp == "void"){
			signature.push_back('void');
		}else if(tmp == "true"){
			signature.push_back('b');
		}else if(tmp == "false"){
			signature.push_back('b');
		}else if(tmp.find('.') == std::string::npos){
			if(is_number(tmp)){
				signature.push_back('i');
			}else{
				signature.push_back('s');
			}
		}else{
			if(is_number(tmp)){
				signature.push_back('f');
			}else{
				signature.push_back('s');
			}

		}
	}

	if(signature == "")
		signature = "void";
	
	for(int x = 0; x < components.size(); x++){

  		if(name.compare(components.at(x).name) == 0){
  			std::vector<std::string> sigs = components.at(x).signatures;
  			for(int y = 0; y < sigs.size(); y++){
  				if(sigs.at(y).compare(signature) == 0){
  					return components.at(x).seed->spawn(signature, args);
  				}
  			}
  			std::cout<<"Error: Signature " << signature << " not found for component " << name << "\n";
   			return new NullComponent();
   		}
   	}
   	std::cout<<"Error: Component " << name << " not found\n";
   	return new NullComponent();
}

bool Registry::addTextureUnmapped(std::string name, std::string path){
	for(int x = 0; x < unmappedTextures.size(); x++){
  		if(name.compare(unmappedTextures.at(x).name) == 0){
	 		return false;
   		}
   	}
	unmappedTextures.push_back(RegTexture(name, path));
   	return true;
}

bool Registry::addTextureMapped(std::string name, std::string source, float *gx, float *gy){
	for(int x = 0; x < mappedTextures.size(); x++){
  		if(name.compare(mappedTextures.at(x).name) == 0){
	 		return false;
   		}
   	}
	mappedTextures.push_back(RegTextureMapped(name, source, gx, gy));
   	return true;
}

void Registry::dump(){
  std::cout<<"\n\n\n\n===================================================\n\nBEGINNING REGISTRY DUMP\n\n";

  std::cout<<"===================================================\n";
	for(int x = 0; x < components.size(); x++){
		components[x].consoleDump();
	}
	for(int x = 0; x < unmappedTextures.size(); x++){
		unmappedTextures[x].consoleDump();
	}
	for(int y = 0; y < mappedTextures.size(); y++){
		mappedTextures[y].consoleDump();
	}
}

void Registry::rePoint(){
	for(int x = 0; x < mappedTextures.size(); x++){
		mappedTextures[x].rePoint();
	}
}