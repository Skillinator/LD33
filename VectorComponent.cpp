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
#include <math.h>

Vector::Vector(){
	id = COMPONENT_VECTOR;
	magnitude = 0.0;
	direction = 0.0;
	updateComponents();
}

Vector::Vector(float gmag, float gdir){
	id = COMPONENT_VECTOR;
	magnitude = gmag;
	direction = gdir;
	updateComponents();
}

Vector::Vector(float gmag, float gdir, int gid){
	id = gid;
	magnitude = gmag;
	direction = gdir;
	updateComponents();
}


void Vector::updateComponents(){
	xComponent = magnitude * cos(direction);
	yComponent = magnitude * sin(direction);
}

void Vector::setMagnitude(float gmag){ magnitude = gmag; updateComponents(); }

void Vector::setDirection(float gdir){ direction = gdir; updateComponents(); }

float Vector::getMagnitude(){ return magnitude; }
float Vector::getDirection(){ return direction; }
float Vector::getXComponent(){ return xComponent; }
float Vector::getYComponent(){ return yComponent; }