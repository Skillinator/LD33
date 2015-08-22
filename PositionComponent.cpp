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

Position::Position(){
	id = COMPONENT_POSITION;
	x = y = z = r = 0.0;
}

Position::Position(float gx, float gy){
	id = COMPONENT_POSITION;
	x = gx;
	y = gy;
	z = 0;
	r = 0.0;
}

Position::Position(float gx, float gy, float gz){
	id = COMPONENT_POSITION;
	x = gx;
	y = gy;
	r = 0;
}


Position::Position(float gx, float gy, float gz, float gr){
	id = COMPONENT_POSITION;
	x = gx;
	y = gy;
	r = gr;
}

Component *Position::spawn(std::string sig, std::string args){
	std::vector<std::string> arguments = split(args, ' ');
	arguments.erase(arguments.begin());
	if(sig.compare("ff") == 0){
		return new Position(stof(arguments[0]), stof(arguments[1]));
	}else if(sig.compare("ii") == 0){
		return new Position(stof(arguments[0]), stof(arguments[1]));
	}else if(sig.compare("fff")){
		return new Position(stof(arguments[0]), stof(arguments[1]), stof(arguments[2]));
	}else if(sig.compare("iii")){
		return new Position(stof(arguments[0]), stof(arguments[1]), stof(arguments[2]));
	}else if(sig.compare("ffff")){
		return new Position(stof(arguments[0]), stof(arguments[1]), stof(arguments[2]), stof(arguments[3]));
	}else if(sig.compare("iiii")){
		return new Position(stof(arguments[0]), stof(arguments[1]), stof(arguments[2]), stof(arguments[3]));
	}
	return new Position();
}

float Position::getX(){ return x; }
float Position::getY(){ return y; }
float Position::getZ(){ return z; }
float Position::getR(){ return r; }
void Position::setX(float get){ x = get; }
void Position::setY(float get){ y = get; }
void Position::setZ(float get){ z = get; }
void Position::setR(float get){ r = get; }