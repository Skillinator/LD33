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
	x = y = 0.0;
}

Position::Position(float gx, float gy){
	id = COMPONENT_POSITION;
	x = gx;
	y = gy;
}

Component *Position::spawn(std::string, std::string){
	std::cout<<"Position STILL NEEDS SPAWN WRITTEN";
	return new Position();
}
float Position::getX(){ return x; }
float Position::getY(){ return y; }
void Position::setX(float get){ x = get; }
void Position::setY(float get){ y = get; }
