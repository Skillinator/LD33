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

Vector::Vector(){
	id = COMPONENT_VECTOR;
	magnitude = 0.0;
	direction = 0.0;
}

Vector::Vector(float gmag, float gdir){
	magnitude = gmag;
	direction = gdir;
}

float Vector::getMagnitude(){ return magnitude; }
float Vector::getDirection(){ return direction; }