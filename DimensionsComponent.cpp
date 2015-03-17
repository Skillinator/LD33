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

Dimensions::Dimensions(){
	id = COMPONENT_DIMENSIONS;
	width = height = 0;
}

Dimensions::Dimensions(int gw, int gh){
	id = COMPONENT_DIMENSIONS;
	width = gw;
	height = gh;
}

Component *Dimensions::spawn(std::string sig, std::string args){
	std::vector<std::string> arguments = split(args, ' ');
	arguments.erase(arguments.begin());
	if(sig.compare("ii") == 0){
		return new Dimensions(stoi(arguments[0]), stoi(arguments[1]));
	}
	return new Dimensions();
}

int Dimensions::getWidth(){ return width; }
int Dimensions::getHeight(){ return height; }
void Dimensions::setWidth(int get){ width = get; }
void Dimensions::setHeight(int get){ height = get; }
