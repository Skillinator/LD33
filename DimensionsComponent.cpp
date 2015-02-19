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

Component *Dimensions::spawn(std::string, std::string){
	std::cout<<"DIMENSIONS STILL NEEDS SPAWN WRITTEN";
	return new Dimensions();
}

int Dimensions::getWidth(){ return width; }
int Dimensions::getHeight(){ return height; }
void Dimensions::setWidth(int get){ width = get; }
void Dimensions::setHeight(int get){ height = get; }
